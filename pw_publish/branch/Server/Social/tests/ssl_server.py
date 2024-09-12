import socket, ssl

CERT_PATH = "ssl_ca/"

def do_something(connstream, data):
    print "do_something data:", data
    connstream.write("ok")
    print "/OK"
    return False

def deal_with_client(connstream):
   data = connstream.read()
   # null data means the client is finished with us
   while data:
      if not do_something(connstream, data):
         # we'll assume do_something returns False
         # when we're finished with client
         break
      data = connstream.read()
   # finished with client
   connstream.close()

# -------------------------------------------------------

error_names = [
    "SSL_ERROR_ZERO_RETURN", \
    "SSL_ERROR_WANT_READ", \
    "SSL_ERROR_WANT_WRITE", \
    "SSL_ERROR_WANT_X509_LOOKUP", \
    "SSL_ERROR_SYSCALL", \
    "SSL_ERROR_SSL", \
    "SSL_ERROR_WANT_CONNECT", \
    "SSL_ERROR_EOF", \
    "SSL_ERROR_INVALID_ERROR_CODE"
]
for e in error_names:
    value = getattr(ssl, e)
    print "error %s=%s" % (e, value)

bindsocket = socket.socket()
bindsocket.bind(('127.0.0.1', 10023))
print "listen.."
bindsocket.listen(5)

# When one did, you d call accept() on the socket to get the new socket from the other end, and use wrap_socket() to create a server-side SSL context for it:

while True:
    try:
        newsocket, fromaddr = bindsocket.accept()
        connstream = ssl.wrap_socket( newsocket,
                                    server_side = True,
                                    cert_reqs = ssl.CERT_REQUIRED,
                                    certfile = CERT_PATH + "ca.crt",
                                    keyfile = CERT_PATH + "ca.key", 
                                    ca_certs = CERT_PATH + "ca.crt",
                                    )
                                    #ssl_version=ssl.PROTOCOL_TLSv1)
        deal_with_client(connstream)
        
    except ssl.SSLError, err:
        print "SSLError:", str(err)
        # print "SSLError: args %s, errno %s, filename %s, message %s, strerror %s" % (err.args, err.errno, err.filename, err.message, err.strerror)
        try:
            connstream.close()
        except:
            pass

    except:
        print "non-ssl exception"
        raise
        

#Then you d read data from the connstream and do something with it till you are finished with the client (or the client is finished with you):

