from communication.Packet import *
from cProfile import Profile
from pstats import Stats, SortKey
from SIMULINK.API import *
from SHUTUP.API import *


def manual_test(freq : int, simulink : SimulinkAPI, shutup : ShutupAPI):
    voltage = 0.0
    while True:
        shutup.write("PF1", voltage)
        shutup.write("PF0", voltage)
        voltage += 0.
        if voltage > 3.3:
            voltage = 0
        sleep(1/freq)
        print("asasd")
        
def automatic_test(simulink : SimulinkAPI, shutup : ShutupAPI):
    
    def shutup_callback(packet):
        simulink.send(packet.PWM)
        
    def simulink_callback(packet):
        airgap_voltage = (packet.Airgap - 65) * 3.3 / 40
        curent_voltage = (packet.Current + 100) * 3.3/ 200
        shutup.write("PF1", airgap_voltage)
        shutup.write("PF0", curent_voltage)
        
    simulink.receive(simulink_callback, "Airgap", "Current")
    shutup.stream(10000, shutup_callback, ("PWM", "PA1"));
    simulink.join_threads()
    simulink.close()

def one_dof():
    print("[1DOF]       -> Starting one dof")
    shutup      = ShutupAPI()
    simulink    = SimulinkAPI()
    
    automatic_test(simulink, shutup)
    #manual_test(1, simulink, shutup)
        
    shutup.close()
    print("[1DOF]       -> Closing connections")

def main():
        one_dof()        

main()
