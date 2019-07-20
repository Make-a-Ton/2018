from flask import Flask, render_template, request, jsonify
import pickle
import requests
import socket
import json
import threading

app = Flask(__name__)

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('0.0.0.0', 4000))
s.listen(10)

buffer = ['lets leave mathew']

def socket_handler():
    conn, addr = s.accept()
    with conn:
        data = conn.recv(1024)
        conn.send(u'yo what up dawg')
        while True:
            while (len(buffer)<1):
                pass
            data = buffer.pop()
            conn.send(json.dumps(data).encode())

t1 = threading.Thread(target=socket_handler)
t1.start()

@app.after_request
def after_request(response):
  response.headers.add('Access-Control-Allow-Origin', '*')
  response.headers.add('Access-Control-Allow-Headers', 'Content-Type,Authorization')
  response.headers.add('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE,OPTIONS')
  return response

@app.route('/givemedata', methods=['POST'])
def givemedata():
    

    return jsonify({'status':'success'}), 200

if __name__=="__main__":
	app.run(host='0.0.0.0')
