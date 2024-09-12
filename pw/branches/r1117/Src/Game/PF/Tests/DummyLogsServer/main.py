from BaseHTTPServer import BaseHTTPRequestHandler, HTTPServer
import json
import urlparse


class MyHandler(BaseHTTPRequestHandler):

    def do_POST(self):
        try:
            logging.debug('POST_URI:'+self.path)
            content_len = int(self.headers.getheader('content-length'))
            post_body = self.rfile.read(content_len)
            logging.debug('POST_BODY:'+post_body)
            
            index = self.path.find('?')
            if index >= 0:
                qs = urlparse.parse_qs(self.path[index+1:])
                pid = qs['pid'][0]
                sid = qs['sid'][0]
                host = qs['host'][0]
            else:
                raise Exception('No parameters defined')

            data = json.loads(post_body)
            assert type(data) == list
            for msg in data:
                msg['tm']
                msg['type']
                msg['msg']
                msg['channel']
                msg['file']
                msg['line']

            self.send_response(200)
            self.send_header('Content-type',    'text/plain')
            self.end_headers()
            self.wfile.write('OK(%s)' % self.path)
        except Exception, details:
            self.send_error(400,'Server error: %r' % details)

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


