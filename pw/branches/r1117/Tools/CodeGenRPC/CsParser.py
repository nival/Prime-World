import re
import os
import sys
from FuncInfo import FuncInfo

CSToNativeTypesMap = [
    ( 'List<string>', 'const nstl::vector<nstl::wstring>&' ),
    ( 'List<String>', 'const nstl::vector<nstl::wstring>&' ),
    ( 'List<int>', 'const nstl::vector<int>&'),
    ( 'List<uint>', 'const nstl::vector<uint>&'),
    ( 'List<bool>', 'const nstl::vector<bool>&'),
    ( 'List<short>', 'const nstl::vector<short>&'),
    ( 'List<ushort>', 'const nstl::vector<ushort>&'),
    ( 'List<float>', 'const nstl::vector<float>&'),
    ( 'List<double>', 'const nstl::vector<double>&'),
    ( 'List<SByte>', 'const nstl::vector<char>&'),
    ( 'List<Byte>', 'const nstl::vector<unsigned char>&'),
    ( 'List<Int64>', 'const nstl::vector<long long>&'),
    ( 'List<UInt64>', 'const nstl::vector<unsigned long long>&'),
    ( 'string', 'const nstl::wstring& '),
    ( 'String', 'const nstl::wstring& '),
    ( 'Boolean', 'bool' ),
    ( 'int', 'int' ),
    ( 'uint', 'uint' ),
    ( 'bool', 'bool' ),
    ( 'float', 'float' ),
    ( 'double', 'double' ),
    ( 'short', 'short' ),
    ( 'ushort', 'ushort' ),
    ( 'SByte', 'char' ),
    ( 'Byte', 'unsigned char' ),
    ( 'Int64', 'long long' ),
    ( 'UInt64', 'unsigned long long' ),
    ( 'void', 'void' ),
    ]

class CsParser:
    def __init__( self, csCode, originalCode ):
        self.text = csCode
        self.original = originalCode
        self.classstr = ""
        self.funcstr = ""
        self.funcs = []
        self.ptrs = []
        self.datastr = ""
        self.data = []

    def findEndofNamespace( self, startpos ):
        numSK = 1
        nextpos = self.text.find( '{', startpos )
        while numSK or nextpos > len(self.text):
            nextpos = nextpos+1
            if self.text[nextpos] == '{': numSK += 1
            elif self.text[nextpos] == '}': numSK -= 1
        return nextpos

    def parseParams( self, func ):
        startidx = func.funcstr.find( '(' )
        endidx = func.funcstr.find( ')' )
        paramsstr = func.funcstr[startidx+1:endidx].strip()
        rawparams = paramsstr.split(',')
        funcparams = []
        for rawparam in rawparams:
            if len( rawparam.split() ):
                paramtype = rawparam.split()[0:-1]
                paramname = rawparam.split()[-1]

                if paramname.find('&') != -1:
                    paramname = paramname.replace( '&', '' )
                    paramtype[-1] += '&'

                funcparams.append( ( paramtype, paramname ) )
        func.setFuncParams( funcparams )

    def GetCSFromNative( self, param ):
        result = param.strip()
        for key in self.ptrs:
            if result == key:
                return False, result.replace('.','::')+'*'
        
        for ( key, val ) in CSToNativeTypesMap:
            if result == key:
                return False, val
            
        if result.find('List<') != -1:
            result = result.replace('List','nstl::vector',1)
        
        return True, result.replace('.','::')

    def parseCSData( self, dataname, dataidx ):
        result = ""
        funcRegression = re.compile( r'\[RemoteData\]\s+public\s+\w+\<*\w*\>*\s+'+dataname, re.I | re.U )
        match = funcRegression.search( self.text )
        if not match:
            raise Exception( 'Can not find data ' + dataname )
        
        endpos = self.findEndofNamespace( match.start() )
        self.datastr = match.group(0)[len("[RemoteData]"):].strip()
        self.datastr = self.datastr.replace( "public", "" )
        self.datastr = self.datastr.replace( dataname, "" )
        self.datastr = self.datastr.strip()
        isStruct, param = self.GetCSFromNative( self.datastr )
        param = param.replace( '&', '' )
        param = param.replace( 'List', 'nstl::vector' )
        
        result += "REMOTE "
        result += param + " "
        result += dataname + ";\n"
        
        return result

    def parseCSFunc( self, funcname, funcidx ):
        result = ""
        funcRegression = re.compile( r'\[Remote\]\s+public\s+\w+\.*\w*\<*\w*\.*\w*\>*\s+'+funcname+r'\s*\((\s*\w*\.*\<*\w*\>*\,*\s*)*\)', re.I | re.U )
        match = funcRegression.search( self.text )
        if not match:
            raise Exception( 'Can not find func ' + funcname )
        
        endpos = self.findEndofNamespace( match.start() )
        self.funcstr = self.text[match.start()+len("[Remote]"):endpos+1]

        func = FuncInfo( funcname, funcidx )
        func.setFuncStr( match.group(0)[len("[Remote]"):].strip() )
        func.funcstr = func.funcstr.replace( 'public','' )
        self.parseParams( func )
        endidx = func.funcstr.find( funcname )
        func.setFuncReturn( func.funcstr[0:endidx].strip() )
        
        result += "REMOTE "

        isStruct, param = self.GetCSFromNative( func.funcreturn )
        if isStruct:
            param = param + " "
        result += param + " "
        result += funcname + "( "
        
        for ( paramtype, paramname ) in func.funcparams:
            isStruct, param = self.GetCSFromNative( ' '.join(paramtype) )
            if isStruct:
                param = "const " + param + "& "
            result += param + " " + paramname + ", "
            
        if len( func.funcparams ) > 0:
            result = result[0:-2]
        result += " );\n"
        
        return result
    
    def parseCSClass( self, classname ):
        result = ""
        classRegression = re.compile( r'\[Remote\]\s+public\s+class\s+'+classname+r'[^;^\{]*\{', re.I | re.U )
        match = classRegression.search( self.text )
        if not match:
            raise Exception( 'Can not find class ' + classname )
        
        endpos = self.findEndofNamespace( match.start() )
        #result = self.text[match.start():endpos+1]
        self.classstr = self.text[match.start()+len("[Remote]"):endpos+1]

        result += "REMOTE class " + classname + "\n{\n  RPC_ID();\n"
        
        dataidx = 0
        for m in re.finditer( r'\[RemoteData\]\s+public\s+\w+\<*\w*\>*\s*(?P<data_name>\w+)\s*\=', self.classstr ):
            result += self.parseCSData( m.group('data_name'), dataidx )
            dataidx += 1
        for m in re.finditer( r'\[RemoteData\]\s+public\s+\w+\<*\w*\>*\s*(?P<data_name>\w+)\s*;', self.classstr ):
            result += self.parseCSData( m.group('data_name'), dataidx )
            dataidx += 1


        funcidx = 0
        for m in re.finditer( r'\[Remote\]\s+public\s+\w+\.*\w*\<*\w*\.*\w*\>*\s+(?P<func_name>\w+)\s*\(', self.classstr ):
            result += self.parseCSFunc( m.group('func_name'), funcidx )
            funcidx += 1
        
        #result = result.replace("[Remote]","REMOTE")
        #result = result.replace('public','')
        #result = result.replace('private','')
        
        #for (key, val) in CSToNativeTypesMap:
        #    result = result.replace( key, val )
        
        result += "}\n"

        return result
        
    def ConvertFromCsToCpp( self ):
        result = ""
        namespaceCs = []
        namespaceCppStart = ""
        namespaceCppEnd = ""

        for m in re.finditer( r'//REMOTEPTR\s+(?P<ptr_name>\w+(\.*\w*)*)', self.original ):
            self.ptrs.append(m.group('ptr_name'))

        for m in re.finditer( r'namespace\s+(?P<namespace_name>\w+(\.*\w*)*)\s+{', self.text ):
            namespaceCs = m.group('namespace_name').split('.')
            break

        for namespace in namespaceCs:
            namespaceCppStart += "namespace " + namespace + "\n{\n"
            namespaceCppEnd += "}\n"
        
        result += namespaceCppStart

        for m in re.finditer( r'\[Remote\]\s+public\s+class\s+(?P<class_name>\w+)[^;^\{]*\{', self.text ):
            classname = m.group('class_name')
            result += self.parseCSClass( classname )
        
        result += namespaceCppEnd
        
        return result
