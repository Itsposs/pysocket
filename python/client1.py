
#!/usr/bin/python
# -*- coding: utf-8 -*-
# filename: client1.py

import time
import socket

HOST = '127.0.0.1'
PORT = 12345
LOG_INFO='LOG_INFO'

class Client(object):
    def __init__(self):
        self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._hostname = socket.gethostname()
        print('%s local host name: %s' %(LOG_INFO, self._hostname));

        while True:
            error_code = self._socket.connect_ex((HOST, PORT))
            if error_code != 0:
                print('%s client connect server failed, code: %d, msg: %s.' % (LOG_INFO, error_code, str(os.strerror(error_code))))
                time.sleep(3)
            else
                print('%s client connect server success...' % (LOG_INFO))
                break

    def __del__(self):
        self._sock.close()

    def run(self):
        for x in range(0, 6):
            data = self._sock.recv(32)
            print('%s data: %s' %(LOG_INFO, data))
            #break;


if __name__ == '__main__':
    c1 = Client()
    c1.run()
