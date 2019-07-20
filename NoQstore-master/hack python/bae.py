import serial
import time

from firebase import firebase
fb = firebase.FirebaseApplication('https://sweetheart-934f2.firebaseio.com', None)


ser = serial.Serial('com3', 9600)
time.sleep(2)
prev = 0

user = "heera"

while True:
    current = float(ser.readline()[0:5])
    if current - prev > .08:
        print(prev)
        number = fb.get(user + "/cart", "phone")

        fb.put(user+"/cart", "phone", number+1)  # "path","property_Name",property_Value
        print(number+1)
        print("done1")
    if current - prev < -.08:
        print(current)
        number = fb.get(user+"/cart", "phone")

        fb.put(user + "/cart", "phone", number - 1)
        print(number - 1)
        print("done")

    prev = current
