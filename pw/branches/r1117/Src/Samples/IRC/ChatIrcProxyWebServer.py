import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--host', default='irc.freenode.net', help='Irc host')
parser.add_argument('--port', type=int, default=6667, help='Irc port')
parser.add_argument('--channel', default='#unity3d', help='Channel')
parser.add_argument('--nickname', default='MySmartBot', help='Nickname')
parser.add_argument('--sport', type=int, default=8080, help='Host port')

args = parser.parse_args()
print args

handler = None
import socket
import threading
import string
import base64

class Channel(threading.Thread):

    def __init__(self, host, port):
        super(Channel, self).__init__()
        self.s = socket.socket()
        self.cache = ''
        self.__serving = True
        self.lock = threading.Lock()
        self.s.connect( (host, port))

    def shutdown(self):
        self.__serving = False                    

    def recv(self, length):
        return self.s.recv(length)

    def send(self, message):
        print '-----------------', repr(message)
        self.s.send(message+'\r\n')

    def run(self):
        readbuffer = ''
        while self.__serving:
            readbuffer=readbuffer+self.s.recv(1024)
            index = readbuffer.rfind('\n')
            if index >= 0:
                newLines = readbuffer[:index+1]
                print newLines
                readbuffer = readbuffer[index+1:]
                self.lock.acquire()
                self.cache += newLines
                self.lock.release()

                temp=string.split(newLines, "\n")
                for line in temp:
                    line=string.rstrip(line)
                    if line:
                        line=string.split(line)

                        if(line[0]=="PING"):
                            self.send("PONG %s" % line[1])

    def retrieve(self, data):
        self.lock.acquire()
        self.send(data)
        result = self.cache
        self.cache = ''
        self.lock.release() 
        return result

class IRCHandler:

    def __init__(self, host, port, channel, nickname):
        self.channel = Channel(host, port)
        self.channel.start()
        self.channel.send("NICK %s" % nickname)
        self.channel.send("USER %s %s bla :%s" % (nickname, host, nickname))
        self.channel.send("JOIN %s" % channel)

    def send(self, data):
        return self.channel.retrieve(data)
        
    def shutdown(self):
        return self.channel.shutdown()

from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer

import sys, traceback


def printException(exceptionInfoList):
    exceptionType, exceptionValue, exceptionTraceback = exceptionInfoList
    strList = traceback.format_exception(exceptionType, exceptionValue, exceptionTraceback)
    return ''.join(strList)

import cgi
import json

class MyHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        self.send_error(404,'Get not supported')

    def do_POST(self):
        try:
            data = None
            ctype, pdict = cgi.parse_header(self.headers.getheader('content-type'))
            if ctype == 'application/x-www-form-urlencoded':
                length = int(self.headers.getheader('content-length'))
                data = self.rfile.read(length)
            global handler
            if data:
                print '**** IN:'+repr(data)
                params = json.loads(data)
                indata = ''
                if 'irc' in params:
                    indata = base64.b64decode(params['irc']) 
                outdata = handler.send(indata)
                params = {
                    'error' : 0
                }
                if outdata:
                    params['chat'] = base64.b64encode(outdata)
                data = json.dumps(params)
            else:
                data = '{}'    

            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            print '**** OUT:'+repr(data)
            self.wfile.write(data)
        except :
            message = printException(sys.exc_info())
            self.send_response(200)
            self.send_header('Content-type',    'text/html')
            self.end_headers()
            data = {  
                'error' : 1,
                'message' : message
            }
            self.wfile.write(json.dumps(data))

def main():
    try:
        global handler
        handler = IRCHandler(args.host, args.port, args.channel, args.nickname)
        server = HTTPServer(('', args.sport), MyHandler)
        print 'started httpserver on port %d...' % args.sport
        server.serve_forever()
    except KeyboardInterrupt:
        print '^C received, shutting down server'
        server.socket.close()
        handler.shutdown()

if __name__ == '__main__':
    main()

