import os
import sys
import re

class ChatParser:

    def __init__(self):
        self.logins = {}

    def Authorize(self, line ):
        m = re.search( r'user authorized \(login=(?P<login_name>\w+)\s+id=(?P<login_id>\w+)\s+gender=(?P<gender>\w+)\)', line )
        if m:
            self.logins[ int(m.group('login_id')) ] = (m.group('login_name'), m.group('gender') )
            
    def Parse(self, line):
        if 'user authorized' in line:
            self.Authorize(line)
            
    def Get(self, clientId):
        if clientId in self.logins:
            return self.logins[clientId]
        return '<'+str(clientId)+'>'
               
class SessionParser:

    def __init__(self):
        self.sessions = {}
        self.asynced = []

    def FindToken(self, template, token):
        s = template+'='
        index = token.find(s)
        if index >= 0:
            return int(token[index+len(s):])
        return -1            
        
    def Extract(self, template, token):
        s = template
        index = line.find(s)
        if index >= 0:
          return line[index+len(s):].replace(')', '').replace('(', '').split()
        return None    
        
    def Parse(self, line):
        if 'AddClient' in line:
            self.AddClient(line)
        if 'Async detected' in line:
            self.AsyncDetected(line)
    
    def AddClient(self, line):
        tokens = self.Extract('AddClient', line)
        if tokens != None:
          client = None
          session = None
          for token in tokens:
            value = self.FindToken('sid', token)
            if value >= 0:
                session = value
            value = self.FindToken('c', token)
            if value >= 0:
                client = value
          if not client or not session:
            assert 0
          else:
            if session not in self.sessions:
              self.sessions[session] = []
            self.sessions[session].append(client)
                

    def AsyncDetected(self, line):
        tokens = self.Extract('Async detected', line)
        if tokens != None:
          client = None
          session = None
          for token in tokens:
            value = self.FindToken('sid', token)
            if value >= 0:
                session = value
            value = self.FindToken('cid', token)
            if value >= 0:
                client = value
          if not client or not session:
            assert 0, line
          else:
            if session not in self.asynced:
                self.asynced.append(session)
                
    def Get(self, session):
        clients = self.sessions[session]
        return set(clients)

c = ChatParser()        
p = SessionParser()
f = file(sys.argv[1], 'rb')
for line in f.readlines():
    p.Parse(line)
        
if len(sys.argv) > 2:        
    f = file(sys.argv[2], 'rb')
    for line in f.readlines():  
        c.Parse(line)
    
def OutputClients(c, clients):
    for client in clients:
        print c.Get(client)

def OutputAsync(p, c, *sessions):
    print 'Asynced intersection for', sessions
    result = set()
    index = 0
    for s in sessions:
        if index == 0:
            result = p.Get(s)
        else:
            result &= p.Get(s)
        index += 1        
    if len(result) > 0:
        OutputClients(c, result)
    else:
        print '    No intersections'    
            
print p.asynced
OutputClients(c, p.Get(22))
OutputAsync(p, c, 12, 15, 17, 20)
OutputAsync(p, c, 10, 11, 13)
