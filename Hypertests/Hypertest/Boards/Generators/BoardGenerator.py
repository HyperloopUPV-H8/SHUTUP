from openpyxl.worksheet.worksheet import Worksheet
from .GoogleDrive.Files import export_file

import openpyxl
import json
import os

def read_packet_structure(packets, measurements, sheet: Worksheet):
    columns = [x for x in sheet.columns][15:]
    
    for column in columns:
        packet_name = column[3].value
        measurement_index = 4
        measurement = column[measurement_index].value
        if packet_name == None or measurement == None:
            continue
        while measurement_index < len(column) and measurement != None:
            packets[packet_name]["fields"].append(measurement)
            packets[packet_name]["measurements"].append(measurements[measurement]["type"])
            packets[packet_name]["size"] += measurements[measurement]["size"]
            measurement_index += 1
            measurement = column[measurement_index].value
            
    for k in packets:
        packets[k]
        packets[k]["struct"] = "<H" + "".join(packets[k]["measurements"])

def read_packets(packets, sheet: Worksheet):
    rows = [x for x in sheet.rows]
    for row in rows[3:]:
        id      = row[1].value
        name    = row[2].value
        type    = row[3].value
        
        if id == None or name == None or type == None:
                return
        
        packet  = { "id" : id, "name" : name, "measurements": [], "fields" : [], "size" : 0 , "type" : type}
        packets[name] = packet

def read_meassurements(measurements, sheet: Worksheet):
    rows = [x for x in sheet.rows]
    for row in rows[3:]:
        id      = row[5].value
        type    = row[7].value
        size    = 0
        
        if id == None or type == None:
            return
        
        if "float32"    in type:
            type = "f"
            size = 4
        if "float64"    in type:
            type = "d"
            size = 8
        if "bool"       in type:
            type = "?"
            size = 1
        if "uint16"     in type:
            type = "H"
            size = 2
        if "int16"      in type:
            type = "h"
            size = 2
        if "enum"       in type:
            type = "c"
            size = 1
        
        measurements[id] = { "type" : type, "size" : size }

def get_board_name(sheet_name: str):
    return sheet_name.split(" ")[-1]

def get_attributes_initailization(packets, measurements):
    results = []
    for packet in packets.values():
        for field in packet["fields"]:
            results.append(f"self.{field} = None")
    return """
        """.join(results)

def get_orders(packets, measurements):
    result = []
    for packet in packets.values():
        if packet["type"] == "order":
            atributes =  ",".join(["self"] + packet["fields"])
            values = ",".join([str(int(packet["id"]))] + packet["fields"])
            result.append("""
    def """ + packet["name"] + """(""" + atributes +  """):
        self.socket_tcp.send(pack('""" + packet["struct"] + """', """ +  values + """))
    """)
    return "".join(result)

def generate_code(sheet_name, packets, measurements):
    board_name = get_board_name(sheet_name)
    attributes_initializaton = get_attributes_initailization(packets, measurements)
    packet_dictionary = json.dumps(packets)
    orders = get_orders(packets, measurements)
    
    return f"""
from struct import pack, unpack
from threading  import Thread
from time import sleep
from socket import *

class """ + board_name +""":

    def __init__(self, backend_ip: str, board_ip: str, port_tcp: int, port_udp: int, is_slave = False):
        self.packets = """ + packet_dictionary + """
        """ + attributes_initializaton + """
        self.init_connection(backend_ip, board_ip, port_tcp, port_udp, is_slave)
        
    def init_connection(self, backend_ip: str, board_ip: str, port_tcp: int, port_udp: int, is_slave: bool):
        self.backend_ip = backend_ip
        self.board_ip   = board_ip
        self.port_tcp   = port_tcp
        self.port_udp   = port_udp
        self.is_slave   = is_slave
        print("["""+board_name+"""]        -> Waiting for connection")
        self.start_connection()
        print("["""+board_name+"""]        -> Connection stablished")

    def start_connection(self):
        if not self.is_slave:
            self.socket_tcp    = socket(AF_INET, SOCK_STREAM)
            self.socket_tcp.connect((self.board_ip, self.port_tcp))
            
            self.socket_udp    = socket(AF_INET, SOCK_DGRAM)
            self.socket_udp.bind((self.backend_ip, self.port_udp))
            self.socket_udp.settimeout(0.1)
            
            self.running = True
            self.threads     = [ Thread(target=self.reading_thread) ]
            self.threads[0].start()
        else:
            self.socket_tcp    = socket(AF_INET, SOCK_STREAM)
            self.socket_tcp.settimeout(0.1)
            self.socket_tcp.bind((self.board_ip, self.port_tcp))
            self.socket_tcp.listen()
            self.socket_tcp     = self.socket_tcp.accept()

            self.socket_udp    = socket(AF_INET, SOCK_DGRAM)
            self.socket_udp.connect((self.backend_ip, self.port_udp))
            
            self.running     = True
            self.threads     = [ Thread(target=self.reading_thread) ]
            self.threads[0].start()
    
    def reading_thread(self):
        while self.running:
            try:
                socket = self.socket_udp
                if self.is_slave:
                    socket = self.socket_tcp
                message, _ = socket.recvfrom(1000)
                packet_id  = unpack("<H", message[0:2])[0]            
                packet     = self.packets[packet_id]
                values     = unpack(packet["struct"], message[2:packet["size"] + 2])
                for k,v in zip(packet["fields"], values):
                    setattr(self, k, v)
            except:
                pass
        self.socket_tcp.shutdown(SHUT_RDWR)
        self.socket_tcp.close()
        self.socket_udp.close()
        print("["""+board_name+"""]        -> Shutting down connections")
    """ + orders + """
    def close(self):
        self.running = False
    """

def generate_boards(dst_path : str):
    global packets, measurements
    file_id = "132UjLzDR7fAbLctsX5nUsoe3ahTx3iDy4ZzlYHo2JUw"
    path = "./Packet.xlsx"
    
    export_file(file_id, path)   
    wb = openpyxl.load_workbook(filename=path)
    
    for sheet_name, sheet in zip(wb.sheetnames[1:], wb.worksheets[1:]):
        packets         = { }
        measurements    = { }
        board_name      = sheet_name.split(" ")[1]
        board_name      = board_name.split("_")[0]
        read_meassurements(measurements, sheet)
        read_packets(packets, sheet)
        read_packet_structure(packets, measurements, sheet)
        file = open(f"{dst_path}/{board_name}.py", "w")
        file.write(generate_code(sheet_name, packets, measurements))
        file.close()
        
    os.remove(path)

if __name__ == "__main__":
    generate_boards("./")