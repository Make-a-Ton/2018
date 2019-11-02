import psutil
import time
import serial

limit = int(input("Enter the cut off battery percentage : "))

while 1:
	battery = psutil.sensors_battery()
	plugged = battery.power_plugged
	percent = battery.percent
	print(percent)
	if percent>=limit:
		break
	time.sleep(1)
	
s=serial.Serial()
s.port='COM4'
s.baudrate=115200
s.open()
s.write(b'0')
s.close()