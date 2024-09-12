def predicate( a, b ):
    if a.startpos > b.startpos:
        return 1
    elif a.startpos < b.startpos:
        return -1
    else:
        return 0

class Namespace:

    class NamespaceInfo:
    
        def __init__( self, start, end, name ):
            self.startpos = start
            self.endpos = end
            self.name = name

    def __init__( self ):
        self.namespaces = []

    def Add( self, info ):
        self.namespaces.append( info )
        self.namespaces.sort( predicate )

    def __repr__( self ):
        return str( self )

    def __str__( self ):
        res = ''
        for ns in self.namespaces:
            res += '%02d-%02d: %s\n' % ( ns.startpos, ns.endpos, ns.name )
        return res

    def GetNamespaceName( self, pos ):
        res = ''
        for ns in self.namespaces:
            if ns.startpos <= pos and ns.endpos >= pos:
                res += ns.name+'::'
        return res[0:-2]

    def GetNamespaces( self, pos ):
        res = []
        for ns in self.namespaces:
            if ns.startpos <= pos and ns.endpos >= pos:
                res.append( ns.name )
        return res
