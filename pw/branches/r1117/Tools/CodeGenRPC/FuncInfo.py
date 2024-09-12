class FuncTypeDefInfo:
    def __init__( self ):
        self.istypedefed = False
        self.typedef = ""
        self.ref = ""

class FuncInfo:

    def __init__( self, name, funcidx ):
        self.funcstr = None
        self.funcname = name
        self.funcparams = []
        self.funcreturn = None
        self.funcidx = funcidx
        self.typedef = FuncTypeDefInfo()

    def setFuncStr( self, string ):
        self.funcstr = string
        self.funcstr = self.funcstr.replace( 'virtual ', '' )
        self.funcstr = self.funcstr.replace( 'REMOTE ', '' )

    def setFuncParams( self, params ):
        self.funcparams = params

    def setFuncReturn( self, ret ):
        self.funcreturn = ret
        self.funcreturn = self.funcreturn.replace( 'virtual ', '' )
        self.funcreturn = self.funcreturn.replace( 'REMOTE ', '' )

    def __repr__( self ):
        return str( self )

    def __str__( self ):
        res = ''
        res += 'Func name: ' + self.funcname + '\n'
        res += 'Func idx: ' + str(self.funcidx) + '\n'
        res += 'Func string: ' + self.funcstr + '\n'
        res += 'Func return: ' + self.funcreturn + '\n'
        res += 'Func params: ' + str(self.funcparams) + '\n'
        return res
