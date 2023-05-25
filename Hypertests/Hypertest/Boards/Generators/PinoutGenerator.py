from .GoogleDrive.Files import  download_file

import openpyxl
import os
import re

def generate_pinout(dst_path : str):
    file_id = "1ta8l_fTHkXY-oZ5ay6gI1QfL4k__s9JW"
    path = "./HSI.xlsx"
    pin_re = re.compile("([A-Z]+[0-9]+).*")
    download_file(file_id, path)
    
    wb = openpyxl.load_workbook(path)
    ws = wb.get_sheet_by_name(name="Pin table")
    
    file = open(f"{dst_path}/Pinout.py", "w")
    file.write("from enum import Enum\n\n")
    rows = [x for x in ws.rows]
    
    for column in range(5, 12):
        board = rows[0][column].value
        board = list(reversed(board.split("/")))[0]
        file.write(f"class {board}(Enum):\n")
        for row in rows[1:]:
            key     = row[column].value
            value   = pin_re.match(row[1].value)
            
            if key and value and len(key) != 0 and key[0] != "=" and value:
                value = value.groups()[0]
                key = key.replace(" ", "_")
                value = value.replace(" ", "_")
                file.write(f'    {key} = \'{value}\'\n')
        file.write("\n")
            
    file.close()
    os.remove(path)
            
if __name__ == "__main__":
    generate_pinout("./")