
#!/usr/bin/python
# -*- coding: utf-8 -*-
# filename: client1.py

import socket

HOST='127.0.0.1'
PORT=12345
LOG_INFO='LOG_INFO'

class Client(object):
    def __init__(self):
        self._sock = socket.socket()
        self._host = socket.gethostname()
        print('%s local host name: %s' %(LOG_INFO, self._host));
        self._sock.connect((HOST, PORT))
        print('%s client start connect server...' %(LOG_INFO))

    def __del__(self):
        self._sock.close()

    def run(self):
        while True:
            data = self._sock.recv(1024)
            print('%s data: %s' %(LOG_INFO, data))
            break;


if __name__ == '__main__':
    c1 = Client()
    c1.run()
