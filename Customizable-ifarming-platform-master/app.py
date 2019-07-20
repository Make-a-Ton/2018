import firebase_admin
import socket
import datetime
import threading
from firebase_admin import credentials, firestore

cred = credentials.Certificate("/Users/ashwin/Documents/Projects/MakathonCUSAT2019/hardwareInterface/firbase_private_key_makathon.json")
firebase_admin.initialize_app(cred)

db = firestore.client()

data_ref = db.collection(u'data')

# data_ref.add({
#     'address': '127.0.0.1',
#     'deviceID': '1',
#     'deviceName': 'device1',
#     'deviceType': 'humidity',
#     'inputValue': 'something',
#     'timestamp': datetime.datetime.now()
# })

# docs = data_ref.get()

# for doc in docs:
#     print(u'{} => {}'.format(doc.id, doc.to_dict()))

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind(('0.0.0.0', 3000))
s.listen(10)

print("listening on  port 3000")

class MyThread(threading.Thread):

    def __init__(self, connec):
        threading.Thread.__init__(self)
        self.conn = connec[0]
        self.addr = connec[1]

    def on_snapshot(self, col_snapshot, changes, read_time):
        print(u'Callback received query snapshot.')
        print("changes: ")
        print(changes)
        # print(col_snapshot)
        # for doc in col_snapshot:
        #     print(u'{}'.format(doc.id))

    def sendValuesToFirestore(self, obj):
        try:
            res = data_ref.where('addressdeviceIDdeviceNamedeviceType', '==', obj['address'] + obj['deviceId'] + obj['deviceName'] + obj['deviceType'])
            if res:
                res.on_snapshot(self.on_snapshot)
                print("updating")
                print("updating")
                res = [f for f in res.get()]
                if len(res)>0:
                    res = res[0]
                    print("res")
                    print(res)
                    print(obj)
                    res = res.getReference()
                    res.update({
                        'inputValue': obj['inputValue']
                    })
                else:
                    print("creating")
                    print("creating")
                    data_ref.add({
                        'address': obj['address'],
                        'deviceID': obj['deviceId'],
                        'deviceName': obj['deviceName'],
                        'deviceType': obj['deviceType'],
                        'inputValue': obj['inputValue'],
                        'port': obj['port'],
                        'time': datetime.datetime.now(),
                        'addressdeviceIDdeviceNamedeviceType': obj['address'] + obj['deviceId'] + obj['deviceName'] + obj['deviceType']
                    })
        except Exception as error:
            print("exception occured: ")
            print(error)
            print("creating")
            print("creating")
            data_ref.add({
                'address': obj['address'],
                'deviceID': obj['deviceId'],
                'deviceName': obj['deviceName'],
                'deviceType': obj['deviceType'],
                'inputValue': obj['inputValue'],
                'port': obj['port'],
                'time': datetime.datetime.now(),
                'addressdeviceIDdeviceNamedeviceType': obj['address'] + obj['deviceId'] + obj['deviceName'] + obj['deviceType']
            })

    def run(self):
        while True:
            print("connection received from: ", self.addr);
            data = self.conn.recv(1024).decode()
            print("data: ")
            print(data)
            data = [d.split('=') for d in data.split('&')]
            obj = dict()
            for d in data:
                obj[d[0]] = d[1]
            obj['address'] = self.addr[0]
            obj['port'] = self.addr[1]
            self.sendValuesToFirestore(obj)
            # self.col_query = data_ref.where('address', '==', self.addr[0])
            # self.query_watch = self.col_query.on_snapshot(self.on_snapshot)

g = []

while True:
    try:
        g.append(MyThread(s.accept()))
        g[-1].start()
        
    except Exception as error:
        print("Error occured: ")
        print(error)

