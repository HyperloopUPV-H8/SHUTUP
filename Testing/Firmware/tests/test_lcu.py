import Hypertest.Boards.Generator
from Hypertest.Boards.LCU import LCU_MASTER

lcu_slave   = LCU_MASTER("192.168.0.9", "192.168.1.4", 50400, 50500, is_slave = True)

def test_airgaps():
    print("test airgaps")

def test_current():
    print("test current")

def test_temperatures():
    print("test temperatures")

def close_all_tests():
    global lcu
    lcu.close()

import Hypertest.Test