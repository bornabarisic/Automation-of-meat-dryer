import socket
from threading import Thread

class Server(Thread):
    def __init__(self, window):
        Thread.__init__(self)
        self.window = window
        self.conn = None
        self.s = None

    def run(self):
        HOST = '192.168.5.152'
        PORT = 8080

        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        print('Socket created')

        try:
           self.s.bind((HOST, PORT))
        except socket.error:
            print('Bind Failed')

        self.s.listen(1)
        print('Socket awaiting msg')

        (self.conn, addr) = self.s.accept()
        print('Connected')
        self.window.send_first_msg()

        while True:
            msg = self.conn.recv(1024)
            self.recived_smg(msg)

    def send_msg(self, msg):
        if(self.conn == None):
            print('No client connected')
            return
        print('I send a msg > ' + msg)
        self.conn.send(msg)

    def recived_msg(self, msg):
        print('I got a msg > ' + msg)
        self.window.process_server_msg(msg)

