from typing import Counter
import serial
import serial.tools.list_ports
import time
import datetime
print('Searching serial port……')
while True:  
    port_list = list(serial.tools.list_ports.comports())
    if port_list :
        break
print('List serial port：')
for i in range(0, len(port_list)):
    print(port_list[i])
print('')

port = input('Enter the serial port number and press Enter to confirm: ')
print('')

ser = serial.Serial(port, 22333, timeout=5)

run = True
count = 0
starttime = int(round(time.time() * 1000))

print(datetime.datetime.now().strftime('%H:%M:%S.%f') + '：Testing MCU to send data to the up machine……')
ser.write('T'.encode('utf-8'))
while (run):
    ser.read(2048) 
    count += 1
    currenttime = int(round(time.time() * 1000))
    run = False if (currenttime - starttime) >= 1000 else True

ser.write('R'.encode('utf-8'))
print(datetime.datetime.now().strftime('%H:%M:%S.%f') + '：The speed is about ' + str(count * 2048 / 1000) + 'K Byte/s\n')

sendbuf = bytes(2048)
run = True
count = 0
starttime = int(round(time.time() * 1000))

print(datetime.datetime.now().strftime('%H:%M:%S.%f') + '：Testing mcu to receive data from upper computer……')
while (run):
    count += ser.write(sendbuf) 
    currenttime = int(round(time.time() * 1000))
    run = False if (currenttime - starttime) >= 1000 else True

print(datetime.datetime.now().strftime('%H:%M:%S.%f') + '：The speed is about ' + str(count / 1000) + 'K Byte/s\n')

ser.close()
exit()
