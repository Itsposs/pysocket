
#!/usr/bin/python
# -*- coding: utf-8 -*-
# filename: server1.py

import socket 

HOST='127.0.0.1'
PORT=12345
LOG_INFO='LOG_INFO'

class Server(object):
    def __init__(self):
        self._socket = socket.socket()
        self._socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self._host = self._sock.getsockname()
        print('%s local host name: %s' %(LOG_INFO, self._host));
        self._sock.bind((HOST, PORT))
        print('%s server bind %s %d' %(LOG_INFO, self._host, PORT))

        self._sock.listen(5)

    def __del(self):
        self._sock.close()

    def run(self):
        while True:
            conn, addr = self._sock.accept()
            print('%s peer host: %s' %(LOG_INFO, conn))
            for x in range(0, 6):
                conn.send('hello world!\n')
                #break;

if __name__ == '__main__':
    s1 = Server()
    s1.run()

