class DataInfo:

    def __init__( self, type, name, dataidx ):
        self.dataname = name
        self.datatype = type
        self.dataidx = dataidx
        if self.datatype.find('nstl::vector<') != -1 and self.datatype.find('StrongMT<') != -1:
            self.datarawtype = self.datatype.replace('nstl::vector<','')
            self.datarawtype = self.datarawtype.replace('>','')
            self.dataraw2type = self.datarawtype.replace('StrongMT<','')
            self.dataraw2type = self.dataraw2type.replace('>','')
        elif self.datatype.find('nstl::vector<') != -1:
            self.datarawtype = self.datatype.replace('nstl::vector<','')
            self.datarawtype = self.datarawtype.replace('>','')
        elif self.datatype.find('StrongMT<') != -1:
            self.datarawtype = self.datatype.replace('StrongMT<','')
            self.datarawtype = self.datarawtype.replace('>','')

    def testForRefOrPointer( self ):
        if self.datatype.find('*') != -1 or self.datatype.find('&') != -1:
            return True
        return False

    def getConstructorStr( self ):
        if self.datatype.find('nstl::vector<') != -1 or self.datatype.find('nstl::string') != -1 or self.datatype.find('nstl::wstring') != -1:
            return "  ,  _"+self.dataname+"_accessor("+str(self.dataidx)+")\n,  _"+self.dataname+"(&_"+self.dataname+"_accessor)\n"
        return ""
        
    def getConstructorBodyStr(self):
        if self.datatype.find('nstl::vector<') != -1 or self.datatype.find('nstl::string') != -1 or self.datatype.find('nstl::wstring') != -1:
            return "  _"+self.dataname+"_accessor.Init(this);\n"
        return ""

    def getFuncStr( self ):
        res = ""
        if self.datatype.find('nstl::vector<') != -1 and self.datatype.find('StrongMT<') != -1:
            res += "  void set"+self.dataname+"(int index, StrongMT<R"+self.dataraw2type+">& value )\n"
            res += "  {\n"
            res += "    if ( handler->IsReadOnly() ) return;\n"
            res += "    _"+self.dataname+"_accessor.Set(index, value, _"+self.dataname+"[index]);\n"
            res += "    _"+self.dataname+"[index] = value;\n"
            res += "  }\n"
            res += "  rpc::vector< StrongMT< R"+self.dataraw2type+" > >& get"+self.dataname+"() { return _"+self.dataname+"; }\n"
            res += "  __declspec(property(get=get"+self.dataname+", put=set"+self.dataname+")) rpc::vector< StrongMT< R"+self.dataraw2type+" > > "+self.dataname+";\n\n"
        elif self.datatype.find('nstl::vector<') != -1:
            res += "  void set"+self.dataname+"(int index, "+self.datarawtype+"value )\n"
            res += "  {\n"
            res += "    if ( handler->IsReadOnly() ) return;\n"
            res += "    _"+self.dataname+"_accessor.Set<"+self.datarawtype+">(index, value, _"+self.dataname+"[index]);\n"
            res += "    _"+self.dataname+"[index] = value;\n"
            res += "  }\n"
            res += "  rpc::vector<"+self.datarawtype+">& get"+self.dataname+"() { return _"+self.dataname+"; }\n"
            res += "  __declspec(property(get=get"+self.dataname+", put=set"+self.dataname+")) rpc::vector<"+self.datarawtype+"> "+self.dataname+";\n\n"
        elif self.datatype.find('StrongMT<') != -1:
            res += "  void set"+self.dataname+"(R"+self.datarawtype+"* value)\n"
            res += "  {\n"
            res += "    if ( handler->IsReadOnly() ) return;\n"
            res += "    handler->Set(this, "+str(self.dataidx)+", value, _"+self.dataname+");\n"
            res += "  }\n"
            res += "  StrongMT<R"+self.datarawtype+">& get"+self.dataname+"() { return _"+self.dataname+"; }\n"
            res += "  __declspec(property(get=get"+self.dataname+", put=set"+self.dataname+")) StrongMT<R"+self.datarawtype+"> "+self.dataname+";\n\n"
        elif self.datatype.find('nstl::string') != -1:
            res += "  void set"+self.dataname+"(const char* value)\n"
            res += "  {\n"
            res += "    if ( handler->IsReadOnly() ) return;\n"
            res += "    _"+self.dataname+".assign(value, true);\n"
            res += "  }\n"
            res += "  void set"+self.dataname+"(int index, char value)\n"
            res += "  {\n"
            res += "    if ( handler->IsReadOnly() ) return;\n"
            res += "    _"+self.dataname+"_accessor.Set(index, value, _"+self.dataname+"[index]);\n"
            res += "    _"+self.dataname+"[index] = value;\n"
            res += "  }\n"
            res += "  rpc::rpcstring& get"+self.dataname+"() { return _"+self.dataname+"; }\n"
            res += "  __declspec(property(get=get"+self.dataname+", put=set"+self.dataname+")) rpc::rpcstring "+self.dataname+";\n\n"
        elif self.datatype.find('nstl::wstring') != -1:
            res += "  void set"+self.dataname+"(const wchar_t* value)\n"
            res += "  {\n"
            res += "    if ( handler->IsReadOnly() ) return;\n"
            res += "    _"+self.dataname+".assign(value, true);\n"
            res += "  }\n"
            res += "  void set"+self.dataname+"(int index, wchar_t value)\n"
            res += "  {\n"
            res += "    if ( handler->IsReadOnly() ) return;\n"
            res += "    _"+self.dataname+"_accessor.Set(index, value, _"+self.dataname+"[index]);\n"
            res += "    _"+self.dataname+"[index] = value;\n"
            res += "  }\n"
            res += "  rpc::rpcwstring& get"+self.dataname+"() { return _"+self.dataname+"; }\n"
            res += "  __declspec(property(get=get"+self.dataname+", put=set"+self.dataname+")) rpc::rpcwstring "+self.dataname+";\n\n"
        else:
            res += "  void set"+self.dataname+"("+self.datatype+" value)\n"
            res += "  {\n"
            res += "    if ( handler->IsReadOnly() ) return;\n"
            res += "    handler->Set(this, "+str(self.dataidx)+", value, _"+self.dataname+");\n"
            res += "  }\n"
            res += "  "+self.datatype+" get"+self.dataname+"() const { return _"+self.dataname+"; }\n"
            res += "  __declspec(property(get=get"+self.dataname+", put=set"+self.dataname+")) "+self.datatype+" "+self.dataname+";\n\n"
        return res

    def getRollbackStr( self ):
        return "        case "+str(self.dataidx)+": s.Rollback(_"+self.dataname+"); break;\n"
        
    def getSynchronizeStr( self ):
        res = ""
        if self.datatype.find('nstl::vector<') != -1 and self.datatype.find('StrongMT<') != -1:
            res += "      args->Sync("+str(self.dataidx)+", (nstl::vector< StrongMT< R"+self.dataraw2type+" > >&)_"+self.dataname+");\n"
        elif self.datatype.find('nstl::vector<') != -1:
            res += "      args->Sync("+str(self.dataidx)+", (nstl::vector< "+self.datarawtype+" >&)_"+self.dataname+");\n"
        elif self.datatype.find('nstl::string') != -1:
            res += "      args->Sync("+str(self.dataidx)+", (nstl::string&)_"+self.dataname+");\n"
        elif self.datatype.find('nstl::wstring') != -1:
            res += "      args->Sync("+str(self.dataidx)+", (nstl::wstring&)_"+self.dataname+");\n"
        else:
            res += "      args->Sync("+str(self.dataidx)+", _"+self.dataname+");\n"
        return res

    def getUpdateStr( self ):
        res = "      args->Sync("+str(self.dataidx)+", localObject->"+self.dataname+");\n"
        return res
        
    def getDataStr( self ):
        res = ""
        if self.datatype.find('nstl::vector<') != -1 and self.datatype.find('StrongMT<') != -1:
            res += "  rpc::VectorAccessor _"+self.dataname+"_accessor;\n"
            res += "  rpc::vector< StrongMT< R"+self.dataraw2type+" > > _"+self.dataname+";\n"
        elif self.datatype.find('nstl::vector<') != -1:
            res += "  rpc::VectorAccessor _"+self.dataname+"_accessor;\n"
            res += "  rpc::vector< "+self.datarawtype+" > _"+self.dataname+";\n"
        elif self.datatype.find('StrongMT<') != -1:
            res += "  StrongMT<R"+self.datarawtype+"> _"+self.dataname+";\n"
        elif self.datatype.find('nstl::string') != -1:
            res += "  rpc::StringAccessor _"+self.dataname+"_accessor;\n"
            res += "  rpc::rpcstring _"+self.dataname+";\n"
        elif self.datatype.find('nstl::wstring') != -1:
            res += "  rpc::WStringAccessor _"+self.dataname+"_accessor;\n"
            res += "  rpc::rpcwstring _"+self.dataname+";\n"
        else:
            res += "  "+self.datatype+" _"+self.dataname+";\n"
        return res
        

    def getVsetStr( self ):
        return "    case "+str(self.dataidx)+": s.Assign(localObject->"+self.dataname+"); break;\n"
        
    def getRVsetStr( self ):
        res = ""
        if self.datatype.find('nstl::vector<') != -1 and self.datatype.find('StrongMT<') != -1:
            res += "      case "+str(self.dataidx)+": return s.Assign( (nstl::vector< StrongMT< R"+self.dataraw2type+" > >&)_"+self.dataname+" );\n"
        elif self.datatype.find('nstl::vector<') != -1:
            res += "      case "+str(self.dataidx)+": return s.Assign( (nstl::vector< "+self.datarawtype+" >&)_"+self.dataname+" );\n"
        elif self.datatype.find('nstl::string') != -1:
            res += "      case "+str(self.dataidx)+": return s.Assign( (nstl::string&)_"+self.dataname+" );\n"
        elif self.datatype.find('nstl::wstring') != -1:
            res += "      case "+str(self.dataidx)+": return s.Assign( (nstl::wstring&)_"+self.dataname+" );\n"
        else:
            res += "      case "+str(self.dataidx)+": return s.Assign( _"+self.dataname+" );\n"
        return res
        
    def getMemberStr( self ):
        return "    if (&localObject->"+self.dataname+" == memory) return "+str(self.dataidx)+";\n"

    def __repr__( self ):
        return str( self )

    def __str__( self ):
        res = ''
        res += 'Data type: ' + self.datatype + '\n'
        res += 'Data name: ' + self.dataname + '\n'
        res += 'Data idx: ' + str(self.dataidx) + '\n'
        return res
