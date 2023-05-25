from Hypertest.Simulink.API import SimulinkAPI
from src.Shutup.API import ShutupAPI
from pstats import Stats, SortKey
from src.Boards.LCU import LCU
from time import time, sleep
from cProfile import Profile

from src.Shutup.Pcan.Packet import *
from src.Shutup.Pin import TUD_ID

def automatic_test(simulink : SimulinkAPI, shutup : ShutupAPI):
    
    def shutup_callback(packet : ValuePacket):
        PWM = 0

        if(packet.PWM != 0):
            PWM = -packet.PWM / 255.0 * 100
        if(packet.PWM2 != 0):
            PWM = packet.PWM2 / 255.0 * 100

        simulink.send(PWM)
        if(time() - packet.t1 > 1):
            print(f"CAN -> {packet.receive_count}       {PWM}")
            packet.receive_count = 0
            packet.t1 =  time()

    def simulink_callback(simulink: SimulinkAPI):
        airgap_voltage = (simulink.Airgap - 68.75) / 17.04545
        curent_voltage = (simulink.Current - 72.1461) / -45.6621
        shutup.write("PF0", TUD_ID.TUD_A, airgap_voltage)
        shutup.write("PF1", TUD_ID.TUD_A, curent_voltage)
        if(time() - simulink.t1 > 1):
            print(f'TCP -> {simulink.receive_count} {simulink.Current}')
            simulink.receive_count = 0
            simulink.t1 = time()
    
    shutup.turn_on_logging()
    simulink.turn_on_logging()
    simulink.receive(simulink_callback, "Airgap", "Current")
    shutup.stream(200, TUD_ID.TUD_A, shutup_callback, ("PWM", "PD12"), ("PWM2", "PB4"))

    simulink.join_threads()

    shutup.plot("PWM")
    shutup.plot("PWM2")
    simulink.plot("Current")
    simulink.plot("Airgap")

    print(f"Total count -> {simulink.total_receives}")

def one_dof():
    print("[1DOF]       -> Starting one dof")
    shutup         = ShutupAPI()
    shutup.write("PF1", TUD_ID.TUD_A, 72.1461 / 45.6621)
    shutup.write("PF0", TUD_ID.TUD_A, 1.65)
    lcu            = LCU("192.168.1.4", 50501)
    simulink       = SimulinkAPI()
    t1 = time()

    lcu.start_control()
    automatic_test(simulink, shutup)

    simulink.close()
    shutup.write("PF1", TUD_ID.TUD_A, 1.5799)
    shutup.close()
    print("[1DOF]       -> Closing connections")
    print(f"[1DOF]      -> Time ellapsed {time() - t1}")

def main():
        one_dof()        

main()
