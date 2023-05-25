from datetime import datetime
from .Generators.BoardGenerator import generate_boards
from .Generators.PinoutGenerator import generate_pinout
from termcolor import colored

import time
import os

dst_path        = "/".join(__file__.split("/")[:-1])
timestamp_path  = f"{dst_path}/last_update.txt"
now             = time.time()
before          = 0

if os.path.exists(timestamp_path):
    file = open(timestamp_path, "r")
    before = float(file.read())
    file.close()

elapsed = now - before
print(colored('[Hypertest]      ->', 'blue'),f" {elapsed} seconds from last library update...")

if elapsed > 30:
    print(colored('[Hypertest]      ->', 'blue'),f" Updating library")
    generate_boards(dst_path)
    generate_pinout(dst_path)
    file = open(timestamp_path, "w")
    file.write(str(time.time()))
    file.close()
