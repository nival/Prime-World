import socket

def IsAddressInternal(address):
    tokens = address.split('.')
    if len(tokens) > 0:
        if int(tokens[0]) in [10, 192, 127]:
            return True
    return False

def GetHost(useExternal=False, useOpposite=False):
    name = socket.gethostname()
    name, aliases, ips = socket.gethostbyname_ex(socket.gethostname())
    return FindHost(ips, useExternal, useOpposite)

def FindHost(ips, useExternal=False, useOpposite=False):
    if len(ips) > 0:
        internal = []
        external = [] 
        for ip in ips:
            if IsAddressInternal(ip):
                internal.append(ip)
            else:
                external.append(ip)
        if useExternal:
            if len(external) > 0:
                return external[0]
            elif useOpposite:
                return internal[0]
        else:
            if len(internal) > 0:
                return internal[0]
            elif useOpposite:
                return external[0]
    raise Exception('No host found (external=%d ips=%s)' % (useExternal, ips))

def GetHosts():
    name = socket.gethostname()
    name, aliases, ips = socket.gethostbyname_ex(socket.gethostname())
    return ips
