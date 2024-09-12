import re
import os
import sys
import zlib
from string import Template
from Namespace import Namespace
from FuncInfo import FuncInfo
from DataInfo import DataInfo
from CsParser import CsParser

def findLine( fstr, classname, funcname ):
    idxClass = fstr.find( classname )
    if idxClass == -1:
        return 0
    idxFunc = fstr.find( funcname, idxClass )
    if idxClass == -1:
        return 0

    lineIdx = 1

    for c in fstr:
        if c == '\n':
            lineIdx = lineIdx + 1
        if idxFunc <= 0:
            break
        idxFunc = idxFunc - 1

    return lineIdx

def findLeft( string, substr, pos ):
    curpos = string.find( substr )
    lastpos = curpos

    while curpos != -1 and curpos <= pos:
        lastpos = curpos
        curpos = string.find( substr, curpos+1 )

    return lastpos

def testForSimpleType( strings ):
    simpleparams = ['int', 'ushort', 'char', 'bool', 'float', 'byte', 'short', 'double', 'long', 'char*', 'string&', 'nstl::string&', 'string', 'nstl::string','nstl::wstring&', 'wstring&', 'wstring', 'nstl::wstring']
    for string in strings:
        for sp in simpleparams:
            if string == sp:
                return True
    return False

def testForRef( strings ):
    findRef = False
    findChar = False
    for string in strings:
        if string.find('*') != -1:
            findRef = True
        if string == 'char' or string == 'char*':
            findChar = True
    if findChar:
        return False

    return findRef

def comment_remover(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return ""
        else:
            return s
    pattern = re.compile(r'//.*?$|/\*.*?\*/|"(?:\\.|[^\\"])*"', re.S | re.M)
    return re.sub(pattern, replacer, text)

class _Parser:
    
    def __init__( self, filename, original_text, text, maxparams = 7, maxfuncs = 56 ):
        self.namespace = Namespace()
        self.classname = None
        self.classnamespace = None
        self.classpos = None
        self.classstr = None
        self.crc32 = None
        self.classnamecrc32 = ""
        self.funcs = []
        self.recieve_time_func_indices = []
        self.original_text = original_text
        self.classIsCObjectBase = 0
        self.maxparams = maxparams
        self.maxfuncs = maxfuncs
        self.text = text
        self.filename = filename
        self.data = []
        self.typedefs = []
        self.interfaceInheritance = False
    
    def findEndofNamespace( self, startpos ):
        numSK = 1
        nextpos = self.text.find( '{', startpos )
        while numSK or nextpos > len(self.text):
            nextpos = nextpos+1
            if self.text[nextpos] == '{': numSK += 1
            elif self.text[nextpos] == '}': numSK -= 1
        return nextpos

    def parseNamespace( self ):
        for m in re.finditer( r'namespace\s+(?P<namespace_name>\w+)\s+{', self.text ):
            endpos = self.findEndofNamespace( m.start() )
            self.namespace.Add( Namespace.NamespaceInfo( m.start(), endpos, m.group('namespace_name') ) )
        for m in re.finditer( '//REMOTE\s+(?P<typedef_name>\w+(\:*\w*)*)\s+(?P<typedef_val>\w+(\:*\w*\<*\w*\>*)*)', self.original_text ):
            self.typedefs.append( ( m.group('typedef_name'), m.group('typedef_val') ) )
#       print self.namespace
#       print self.namespace.GetNamespaceName( 5500 )

    def getAllClasses( self ):
        res = []

        for m in re.finditer( r'REMOTE\s+struct\s+(?P<class_name>\w+)[^;^\{]*\{', self.text ):
            res.append( m.group('class_name') )
        for m in re.finditer( r'REMOTE\s+class\s+(?P<class_name>\w+)[^;^\{]*\{', self.text ):
            res.append( m.group('class_name') )
        return res

    def getAllFuncs( self ):
        res = []
#       for m in re.finditer( r'REMOTE\s+(\s*\w*\:*\w*\&*\**\s+)*\s+(?P<func_name>\w+)\s*\((\s*\w*\s*\:*\<*\>*\&*\**\,*\s*)*\)', self.classstr ):
        for m in re.finditer( r'REMOTE\s+(\s*\w*\:*\w*\<*\w*\:*\w*\>*\&*\**\s+)*(\&*\**)*(?P<func_name>\w+)\s*\(', self.classstr ):
            res.append( m.group('func_name') )
        return res

    def getAllData( self ):
        res = []
        for m in re.finditer( r'REMOTE\s+(?P<data_type>\s*\w*\:*\w*\<*\w*\>*\**\s+)*(?P<data_name>\w+)\s*\;', self.classstr ):
            typle = ( m.group('data_type'), m.group('data_name') )
            res.append( typle )
        for m in re.finditer( r'REMOTE\s+(?P<data_type>nstl::vector<\s*StrongMT\s*\w*\:*\w*\<*\w*\>*\s*\**\s*>\s+)*(?P<data_name>\w+)\s*\;', self.classstr ):
            typle = ( m.group('data_type'), m.group('data_name') )
            res.append( typle )
        return res

    def parseClass( self, classname ):
        self.resetFuncs()
        classRegression = re.compile( r'REMOTE\s+struct\s+'+classname+r'(\s+|\:)+[^;^\{]*\{', re.I | re.U )
        match = classRegression.search( self.text )
        if not match:
            classRegression = re.compile( r'REMOTE\s+class\s+'+classname+r'(\s+|\:)+[^;^\{]*\{', re.I | re.U )
            match = classRegression.search( self.text )
            
        if not match:
            raise Exception( 'Can not find class ' + classname )

        endpos = self.findEndofNamespace( match.start() )
        self.classstr = self.text[match.start()+len("REMOTE"):endpos+1]
        if self.classstr.find('rpc::IRemoteEntity') != -1:
            self.interfaceInheritance = True
        else:
            self.interfaceInheritance = False
        self.classname = classname
        self.classnamespace = self.namespace.GetNamespaceName( match.start() )

        self.classpos = match.start();
#       print '%02d-%02d: %s' % (match.start(), endpos, match.group(0))
#       print self.text[match.start():endpos+1]

        if self.classstr.find( 'BaseObjectMT' ) > -1 or self.classstr.find( 'IBaseInterfaceMT' ) > -1:
            self.classIsCObjectBase = 1
#           print 'class %s is CObjectBase' % self.classname;

    def findFunc( self, funcname ):
        startidx = 0
        for func in self.funcs:
            if func.funcname == funcname:
                startidx = func.funcidx+1

        funcidx = -1
        funcidx = self.classstr.find( ' ' + funcname + ' ', startidx )
        if funcidx == -1:
            funcidx = self.classstr.find( '\t' + funcname + ' ', startidx )
        if funcidx == -1:
            funcidx = self.classstr.find( '&' + funcname + ' ', startidx )
        if funcidx == -1:
            funcidx = self.classstr.find( '*' + funcname + ' ', startidx )
        if funcidx == -1:
            funcidx = self.classstr.find( ' ' + funcname + '\t', startidx )
        if funcidx == -1:
            funcidx = self.classstr.find( '\t' + funcname + '\t', startidx )
        if funcidx == -1:
            funcidx = self.classstr.find( '&' + funcname + '\t', startidx )
        if funcidx == -1:
            funcidx = self.classstr.find( '*' + funcname + '\t', startidx )
        if funcidx == -1:
            funcidx = self.classstr.find( ' ' + funcname + '(', startidx )
        if funcidx == -1:
            funcidx = self.classstr.find( '\t' + funcname + '(', startidx )
        if funcidx == -1:
            funcidx = self.classstr.find( '&' + funcname + '(', startidx )
        if funcidx == -1:
            funcidx = self.classstr.find( '*' + funcname + '(', startidx )
        if funcidx == -1:
                print self.classstr
                print funcname
                raise Exception( 'Can not find function ' + funcname )
        return funcidx


    def parseFunction( self, funcname ):
        funcidx = self.findFunc( funcname )

        startidx1 = findLeft( self.classstr, ';', funcidx )
        startidx2 = findLeft( self.classstr, '\n', funcidx )
        if startidx2 > startidx1:
            startidx = startidx2
        else:
            startidx = startidx1
        endidx = self.classstr.find( ';', funcidx )

        funcRegression = re.compile( r'(}|;|\n)(\s*\w*\:*\w*\<*\w*\:*\w*\>*\&*\**\s+)*(\&*\**)*'+funcname+'\s*\((\s*\w*\/*\s*\:*\<*\>*\&*\**\,*\s*)*\)', re.I | re.U )
        match = funcRegression.search( self.classstr[startidx:endidx] )

        if not match:
            raise Exception( 'Can not find function ' + funcname )

        func = FuncInfo( funcname, funcidx )
        func.setFuncStr( match.group(0)[1:].strip() )
        ( isRefError, isNumError, isStructError ) = self.parseParams( func, len(self.funcs) )
        errorLine = str(findLine( self.original_text, self.classname, funcname ))
        errorPlace = self.filename + "(" + errorLine + ") : error in " + self.classname + "::" + funcname + ": "

        if isRefError:
            raise Exception( errorPlace + "Pointers in parameters are not supported" )
        if isNumError:
            raise Exception( errorPlace + "Too many parameters(>" + str(self.maxparams) + ") not supported" )
        #if isStructError:
            #raise Exception( errorPlace + "Structs by value are not supported" )

        endidx = func.funcstr.find( funcname )
        func.setFuncReturn( func.funcstr[0:endidx].strip() )
        #if func.funcreturn.find('*') != -1:
            #raise Exception( errorPlace + "Pointers in return parameters are not supported" )

        if func.funcname == self.classname:
            for f in self.funcs:
                if f.funcname == func.funcname and len(f.funcparams) == len(func.funcparams):
                    raise Exception( errorPlace + "Two or more constructors with same parameters" )

        for (paramtype, paramname) in func.funcparams:
            for pt in paramtype:
                if pt.find( '&' ) != -1:
                    func.typedef.istypedefed = True

        if func.typedef.istypedefed:
            func.typedef.typedef = "\ttypedef " + func.funcreturn + " "
            func.typedef.typedef +=  "(" + self.classnamespace + "::" + self.classname + "::*T" + func.funcname + ")("
            index = 0
            for (paramtype, paramname) in func.funcparams:
                if index != 0:
                    func.typedef.typedef += ","
                for pt in paramtype:
                    func.typedef.typedef += " " + pt.replace('&','*')
                func.typedef.typedef += " " + paramname
                index+=1
            func.typedef.typedef += ");\n"
            
            func.typedef.ref = "T" + func.funcname
            

        self.funcs.append( func )

        if len( self.funcs ) > self.maxfuncs:
            raise Exception( errorPlace + "Too many functions in class" )

        #print func

    def resetFuncs( self ):
        self.funcs = []
        self.recieve_time_func_indices = []

    def parseParams( self, func, index ):
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

                if paramname.find('*') != -1:
                    paramname = paramname.replace( '*', '' )
                    paramtype[-1] += '*'

                if paramname == '__miscInfo__' and 'Transport::MessageMiscInfo&' in paramtype >= 0:
                    self.recieve_time_func_indices.append(index)

                funcparams.append( ( paramtype, paramname ) )
        func.setFuncParams( funcparams )
        isRefError = False
        isNumError = False
        isStructError = False
        paramNumber = 0
        for (paramtype, paramname) in funcparams:
            paramNumber = paramNumber + 1
            if paramname:
                rawparamtype = ' '.join(paramtype)
                if testForRef( paramtype ):
                    isRefError = False
                if not testForSimpleType( paramtype ) and rawparamtype.find('&') == -1:
                    isStructError = True
        if paramNumber > self.maxparams:
            isNumError = True
        return isRefError, isNumError, False# isStructError
    
    def parseData( self, data ):
        self.data = []
        dataIdx = 0
        for ( type, val ) in data:
            datainfo = DataInfo( type, val, dataIdx )
            if datainfo.testForRefOrPointer():
                errorLine = str(findLine( self.original_text, self.classname, val ))
                errorPlace = self.filename + "(" + errorLine + ") : error in " + self.classname + " " + type + " " + val
                raise Exception( errorPlace + "Ref or pointer types are not supported" )

            self.data.append( datainfo )
            dataIdx += 1
        
        crc32_str = self.classnamespace + '::' + self.classname;
        classnamecrc32_str = self.classnamespace + '::' + self.classname;
        for f in self.funcs:
            crc32_str += f.funcname
            crc32_str += ' '.join(f.funcreturn)
            for (paramtype, paramname) in f.funcparams:
                rawparamtype = ' '.join(paramtype)
                crc32_str += rawparamtype
        for ( type, val ) in data:
            crc32_str += type
            crc32_str += val

        crc = zlib.crc32( crc32_str )
        crc = crc & 0xffffffff
        self.crc32 = "0x%x" % crc

        crc = zlib.crc32( classnamecrc32_str )
        crc = crc & 0xffffffff
        self.classnamecrc32 = "0x%x" % crc

def Parser( filename, maxparams = 7, maxfuncs = 56 ):
    file = open( filename, 'r' )
    original_text = file.read()
    text = comment_remover( original_text )
    file.close()
    if filename.find('.cs') != -1:
        converter = CsParser( text, original_text )
        text = converter.ConvertFromCsToCpp()
    return _Parser(filename, original_text, text, maxparams, maxfuncs)
