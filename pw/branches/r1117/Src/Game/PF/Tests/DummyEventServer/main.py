from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import time

class MyHandler(BaseHTTPRequestHandler):

    def do_GET(self):
        try:
            logging.debug('GET:'+self.path)
            self.send_response(200)
            self.send_header('Content-type',    'text/plain')
            self.end_headers()
            self.wfile.write('OK(%s)' % self.path)
            #self.wfile.write('{ec:0,tm:1}')
            #time.sleep(10.0)
        except:
            self.send_error(500,'Server error')

    def do_POST(self):
        try:
            logging.debug('POST:'+self.path)
            self.send_response(200)
            self.send_header('Content-type',    'text/plain')
            self.end_headers()
            self.wfile.write('OK(%s)' % self.path)
        except:
            self.send_error(500,'Server error')

import logging

def loggingSeverity( name ):
    return getattr( logging, name.upper(), 0) if name else 0

def main():
    logfile = 'access.log'
    logging.basicConfig( filename=logfile, filemode="w", level=loggingSeverity( 'debug' ), format='[%(asctime)s %(levelname)8s] %(message)s' )

    try:
        port = 8080
        server = HTTPServer(('', port), MyHandler)
        print 'started httpserver on port %d ...' % port
        server.serve_forever()
    except KeyboardInterrupt:
        print '^C received, shutting down server'
        server.socket.close()

if __name__ == '__main__':
    main()


