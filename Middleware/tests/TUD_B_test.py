from Shutup.API import *

def main():
    shutup = ShutupAPI()
    print(f"[SHUTUP]     -> Reg in: {shutup.read('PA6', TUD_ID.TUD_B)}")
    print(f"[SHUTUP]     -> Voltage: {shutup.read('PA7', TUD_ID.TUD_B) / 0.109109148}")
    print(f"[SHUTUP]     -> Current: {shutup.read('PC4', TUD_ID.TUD_B) / (22.0 / 1000)}")
    
    print(f"[SHUTUP]     -> IC PB4 : {shutup.read('PB4', TUD_ID.TUD_B)}")
    print(f"[SHUTUP]     -> IC PA1 : {shutup.read('PA1', TUD_ID.TUD_B)}")
    print(f"[SHUTUP]     -> IC PB1 : {shutup.read('PB1', TUD_ID.TUD_B)}")
    print(f"[SHUTUP]     -> IC PB5 : {shutup.read('PB5', TUD_ID.TUD_B)}")
    print(f"[SHUTUP]     -> IC PD13: {shutup.read('PD13', TUD_ID.TUD_B)}")
    print(f"[SHUTUP]     -> IC PD12: {shutup.read('PD12', TUD_ID.TUD_B)}")
    print(f"[SHUTUP]     -> IC PD14: {shutup.read('PD14', TUD_ID.TUD_B)}")
    print(f"[SHUTUP]     -> IC PD15: {shutup.read('PD15', TUD_ID.TUD_B)}")
    print(f"[SHUTUP]     -> IC PE14: {shutup.read('PE14', TUD_ID.TUD_B)}")
    print(f"[SHUTUP]     -> IC PE9 : {shutup.read('PE9', TUD_ID.TUD_B)}")
    print(f"[SHUTUP]     -> IC PE13: {shutup.read('PE13', TUD_ID.TUD_B)}")
    
    shutup.write('PF13', TUD_ID.TUD_B, 1.65)
    shutup.write('PF12', TUD_ID.TUD_B, 1.65)
    shutup.write('PF11', TUD_ID.TUD_B, 1.65)
    shutup.write('PF3' , TUD_ID.TUD_B, 1.65)
    
    shutup.write("PC9" , TUD_ID.TUD_B, 5)
    shutup.write("PA2" , TUD_ID.TUD_B, 5)
    shutup.write("PC7" , TUD_ID.TUD_B, 5)
    shutup.write("PA3" , TUD_ID.TUD_B, 5)
    shutup.write("PC8" , TUD_ID.TUD_B, 5)
    shutup.write("PF14", TUD_ID.TUD_B, 5)
    shutup.write("PC6" , TUD_ID.TUD_B, 5)
    shutup.write("PB14", TUD_ID.TUD_B, 5)
    
    shutup.write("PA5" , TUD_ID.TUD_B, 1)
    shutup.write("PB11", TUD_ID.TUD_B, 1)
    shutup.write("PB10", TUD_ID.TUD_B, 1)

    shutup.write("PC13", TUD_ID.TUD_B, 1)
    shutup.write("PC14", TUD_ID.TUD_B, 1)
    shutup.write("PG10", TUD_ID.TUD_B, 1)
    shutup.write("PB7" , TUD_ID.TUD_B, 1)
    shutup.write("PC2" , TUD_ID.TUD_B, 1)
    shutup.write("PC1" , TUD_ID.TUD_B, 1)
    shutup.write("PC0" , TUD_ID.TUD_B, 1)
    shutup.write("PE4" , TUD_ID.TUD_B, 1)
    shutup.write("PE5" , TUD_ID.TUD_B, 1)
    shutup.write("PF8" , TUD_ID.TUD_B, 1)
    shutup.write("PF9" , TUD_ID.TUD_B, 1)
    shutup.write("PG1" , TUD_ID.TUD_B, 1)
    shutup.write("PE6" , TUD_ID.TUD_B, 1)
    shutup.write("PF6" , TUD_ID.TUD_B, 1)
    shutup.write("PF7" , TUD_ID.TUD_B, 1)
    
    shutup.cancel_streams()
    sleep(1)
    
    print(f"[SHUTUP]     -> Actuator 1: {shutup.read('PA5', TUD_ID.TUD_B)}")
    print(f"[SHUTUP]     -> Actuator 2: {shutup.read('PB11', TUD_ID.TUD_B)}")
    print(f"[SHUTUP]     -> Actuator 3: {shutup.read('PB10', TUD_ID.TUD_B)}")
    
    
main()