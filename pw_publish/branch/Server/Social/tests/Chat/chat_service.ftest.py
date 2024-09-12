import sys
sys.path.append('../..')
sys.path.append('../../base')
sys.path.append('../../cfg')
sys.path.append('../../thrift_pw/statistics/gen-py')
import chat_service
import time
    
class Context:

    def OnConnect(self):
        print 'connected OK'

    def OnConnectFail(self):
        print 'connected FAIL'

    def OnData(self, data):
        print 'Data', repr(data)

    def OnDisconnect(self, connectionLost):
        print 'disconnected', connectionLost

#p = chat_service.SimpleSocketPoller( ('127.0.0.1', 6697) )
import select
select.EPOLLIN = 1 
select.EPOLLPRI = 2
select.EPOLLOUT = 8
select.EPOLLHUP = 16
select.EPOLLERR = 32

class DummyEpoll:
    def __init__(self):
        self.fd = {}

    def register(self, fd, events=select.EPOLLIN | select.EPOLLPRI):
        print 'register', fd
        self.fd[fd] = events

    def poll(self, timeout):
        result = []
        for fd, events in self.fd.items():
            result.append( (fd, select.EPOLLIN) )
        return result

    def unregister(self, fd):
        print 'unregister', fd
        del self.fd[fd]

    def close(self):
        pass    

select.epoll = DummyEpoll

p = EPollPoller( ('127.0.0.1', 6697) )

c = Context()
p.Register(c)

i = 0
quit = False
while True:
    p.Update()
    time.sleep(0.25)
    i += 1
    if i == 5:
        c1 = Context()
        p.Register(c1)
        quit = True
    if quit and len(p.s2c) == 1:
        break


