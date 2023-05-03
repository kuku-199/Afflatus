from typing import Counter
import serial
import serial.tools.list_ports
import time
import datetime

print('正在搜索串口……')
port_list = list(serial.tools.list_ports.comports())
print('发现串口：')
for i in range(0, len(port_list)):
    print(port_list[i])
print('')

port = input('请输入串口号，并按回车确认: ')
print('')

ser = serial.Serial(port, 22333, timeout=5)

run = True
count = 0
starttime = int(round(time.time() * 1000))

print(datetime.datetime.now().strftime('%H:%M:%S.%f') + '：开始测试单片机向上位机发送数据……')
ser.write('S'.encode('utf-8'))
while (run):
    ser.read(2048) # 接收来自单片机的数据
    count += 1
    currenttime = int(round(time.time() * 1000))
    run = False if (currenttime - starttime) >= 1000 else True

ser.write('E'.encode('utf-8'))
print(datetime.datetime.now().strftime('%H:%M:%S.%f') + '：结束测试，速度约为 ' + str(count * 2048 / 1000) + 'K Byte/s\n')

sendbuf = bytes(2048)
run = True
count = 0
starttime = int(round(time.time() * 1000))

print(datetime.datetime.now().strftime('%H:%M:%S.%f') + '：开始测试单片机接收上位机的数据……')
while (run):
    count += ser.write(sendbuf) # 向单片机发送数据
    currenttime = int(round(time.time() * 1000))
    run = False if (currenttime - starttime) >= 1000 else True

print(datetime.datetime.now().strftime('%H:%M:%S.%f') + '：结束测试，速度约为 ' + str(count / 1000) + 'K Byte/s\n')

ser.close()
exit()
