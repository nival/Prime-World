import re
import os
import sys
import zlib
from string import Template
from Parser import _Parser
from Parser import Parser
from Parser import testForSimpleType

NativeToCSTypesMap = [
    ( 'nstl::vector', 'System.Collections.Generic.List' ),
    ( 'nstl::wstring', 'System.String' ),
    ( 'unsigned int', 'System.UInt32' ),
    ( 'uint', 'System.UInt32' ),
    ( 'int', 'System.Int32' ),
    ( 'unsigned short', 'System.UInt16' ),
    ( 'ushort', 'System.UInt16' ),
    ( 'short', 'System.Int16' ),
    ( 'unsigned char', 'System.Byte' ),
    ( 'signed char', 'System.SByte' ),
    ( 'char', 'System.SByte' ),
    ( 'float', 'System.Single' ),
    ( 'double', 'System.Double' ),
    ( 'unsigned long long', 'System.UInt64' ),
    ( 'long long', 'System.Int64' ),
    ( 'bool', 'System.Boolean' ),
    ( 'nstl::string', 'System.String' ),
    ( '*', '' ),
    ( '&', '' ),
    ]

NativeToCSReturnTypesMap = [
    ( 'nstl::vector<int>', 'ManagedRPC.OperatorVectorInt32' ),
    ( 'nstl::vector<uint>', 'ManagedRPC.OperatorVectorUInt32' ),
    ( 'nstl::vector<unsigned int>', 'ManagedRPC.OperatorVectorUInt32' ),

    ( 'nstl::vector<short>', 'ManagedRPC.OperatorVectorInt16' ),
    ( 'nstl::vector<signed short>', 'ManagedRPC.OperatorVectorInt16' ),
    ( 'nstl::vector<unsigned short>', 'ManagedRPC.OperatorVectorUInt16' ),
    ( 'nstl::vector<ushort>', 'ManagedRPC.OperatorVectorUInt16' ),

    ( 'nstl::vector<char>', 'ManagedRPC.OperatorVectorSByte' ),
    ( 'nstl::vector<signed char>', 'ManagedRPC.OperatorVectorSByte' ),
    ( 'nstl::vector<unsigned char>', 'ManagedRPC.OperatorVectorByte' ),

    ( 'nstl::vector<float>', 'ManagedRPC.OperatorVectorFloat' ),
    ( 'nstl::vector<double>', 'ManagedRPC.OperatorVectorDouble' ),

    ( 'nstl::vector<long long>', 'ManagedRPC.OperatorVectorInt64' ),
    ( 'nstl::vector<signed long long>', 'ManagedRPC.OperatorVectorInt64' ),
    ( 'nstl::vector<unsigned long long>', 'ManagedRPC.OperatorVectorUInt64' ),

    ( 'nstl::vector<nstl::wstring>', 'ManagedRPC.OperatorVectorString' ),
    ( 'nstl::vector<bool>', 'ManagedRPC.OperatorVectorBoolean' ),

    ( 'nstl::wstring', 'ManagedRPC.OperatorString' ),

    ( 'unsigned int', 'ManagedRPC.OperatorUInt32' ),
    ( 'uint', 'ManagedRPC.OperatorUInt32' ),
    ( 'int', 'ManagedRPC.OperatorInt32' ),
    
    ( 'unsigned short', 'ManagedRPC.OperatorUInt16' ),
    ( 'ushort', 'ManagedRPC.OperatorUInt16' ),
    ( 'signed short', 'ManagedRPC.OperatorInt16' ),
    ( 'short', 'ManagedRPC.OperatorInt16' ),
    
    ( 'unsigned char', 'ManagedRPC.OperatorByte' ),
    ( 'signed char', 'ManagedRPC.OperatorSByte' ),
    ( 'char', 'ManagedRPC.OperatorSByte' ),
    
    ( 'float', 'ManagedRPC.OperatorFloat' ),
    ( 'double', 'ManagedRPC.OperatorDouble' ),
    ( 'unsigned long long', 'ManagedRPC.OperatorUInt64' ),
    ( 'signed long long', 'ManagedRPC.OperatorInt64' ),
    ( 'long long', 'ManagedRPC.OperatorInt64' ),
    ( 'bool', 'ManagedRPC.OperatorBoolean' ),
    ( '*', '' ),
    ( '&', '' ),
    ]

def GetCSTypeFromNative( type, dict, typedefs ):
    res = type
    for (key, val) in typedefs:
        if type.replace("const","").replace("&","").replace("nstl::vector<","").replace(">","").strip() == key.strip():
            res = res.replace( key, val )
    res = res.replace( 'const', '' )
    for (key, val) in dict:
        res = res.replace( key, val )
    res = res.replace( '::', '.' )
    return res

def AddRToClassName( classname ):
    if classname.find('::') != -1:
        index = classname.rfind('::');
        index += 2
        res = classname[:index]+'R'+classname[index:]
        return res
    else:
        return 'R'+classname
    
class CodeGenRPC:

    def __init__( self, parser ):
        self.parser = parser

    def generateRCSFunc( self, func, index ):
        res = ''
        res += '  public void ' + func.funcname + '(  '

        params_str = '    object[] pars = new object[$___number___$] { '
        paridx = 0
        for (paramtype, paramname) in func.funcparams:
            if paramname:
                rawparam = GetCSTypeFromNative( ' '.join(paramtype), NativeToCSTypesMap, self.parser.typedefs )
                res += rawparam + ' ' + paramname + ', '
                params_str += paramname + ', '
                paridx += 1
        
        if func.funcreturn.find('void') == -1:
            rawparam = GetCSTypeFromNative( func.funcreturn, NativeToCSReturnTypesMap, self.parser.typedefs )
            if rawparam == func.funcreturn.replace('::','.').replace('const','').replace('&',''):
                if rawparam.find('nstl.vector<') != -1:
                    rawparam = rawparam.replace('nstl.vector<','',1)
                    rawparam = rawparam.replace('>','',1)
                    rawparam = 'ManagedRPC.OperatorVectorStruct<' + rawparam + '>'
                else:
                    rawparam = 'ManagedRPC.OperatorStruct<' + rawparam + '>'
            if rawparam != func.funcreturn and func.funcreturn.find('*') != -1:
                rawparam = 'ManagedRPC.OperatorRClassCallInfo'
            res += rawparam + ' ret, '

        if paridx != 0 or func.funcreturn.find('void') == -1:
            res = res[0:-2]
        if paridx != 0:
            params_str = params_str[0:-2]
        res += ' )\n'
        res += '  {\n'
        params_str += ' };\n'
        params_str = params_str.replace( '$___number___$', str(paridx) )
        res += params_str
        
        res += '    if ( info != null )\n'
        
        if func.funcreturn.find('void') != -1:
            res += '      ManagedRPC.EntitiesContainer.CallRClassMethod( info, ' + str(index) + ', pars );\n'
        else:
            res += '      ManagedRPC.EntitiesContainer.CallRClassMethodWithResult( info, ' + str(index) + ', pars, ret );\n'

        res += '  }\n'

        return res

    def generateLCSFunc( self, func, index ):
        res = ''
        
        res += '    case ' + str(index) + ':\n    {\n'
 
        if func.funcreturn.find('void') != -1:
            res += '      localObject.' + func.funcname + '( '

            paridx = 0
            for (paramtype, paramname) in func.funcparams:
                if paramname:
                    res += '( ' + GetCSTypeFromNative( ' '.join(paramtype), NativeToCSTypesMap, self.parser.typedefs ) + ' )( pars.GetValue( ' + str(paridx) + ' ) ), '
                    paridx += 1

            if paridx != 0:
                res = res[0:-2]
            res += ' );\n'
        else:
            res += '      ' + GetCSTypeFromNative( func.funcreturn, NativeToCSTypesMap, self.parser.typedefs )
            res += ' ret = localObject.' + func.funcname +'( '
            paridx = 0
            for (paramtype, paramname) in func.funcparams:
                if paramname:
                    res += '( ' + GetCSTypeFromNative( ' '.join(paramtype), NativeToCSTypesMap, self.parser.typedefs ) + ' )( pars.GetValue( ' + str(paridx) + ' ) ), '
                    paridx += 1
            if paridx != 0:
                res = res[0:-2]
            res += ' );\n'
            res += '      call.Call( ' + str(index) + ', ret );\n'

        res += '      break;\n    }\n'
        
        return res

    def generateLCSParamTypes( self, func, index ):
        res = ''
       
        res += '    case ' + str(index) + ':\n      {\n'
        
        params_str = '        object[] objs = new object[$___number___$] { '
        paridx = 0
        for (paramtype, paramname) in func.funcparams:
            if paramname:
                params_str += 'typeof( ' + GetCSTypeFromNative( ' '.join(paramtype), NativeToCSTypesMap, self.parser.typedefs ) + ' ), '
                paridx += 1
                
        if paridx != 0:
            params_str = params_str[0:-2]
        params_str += ' };\n'
        params_str = params_str.replace( '$___number___$', str(paridx) )
        res += params_str

        res += '        return objs;\n'
        
        res += '      }\n'
        return res

    def isLocalPtr(self, paramtype, paramname):
        if len(paramtype) == 0:
            return False
        if paramtype[-1].find('*') != -1:
            for param in paramtype:
                if param == 'char' or param == 'char*':
                    return False
            if len(paramtype) > 0 and paramtype[0] == 'NI_LPTR':
                return True
        return False

    def generateRFunc( self, func, index ):
        res = ''
        if func.funcreturn.find('void') != -1:
            res += '\t' + func.funcreturn.replace('virtual ','') + ' '+func.funcname + '(  '

            for (paramtype, paramname) in func.funcparams:
                if paramname:
                    res += ' '.join(paramtype) + ' ' + paramname + ', ' 

            res = res[0:-2]
            res += ' )\n'
            res += '\t{\n'

            res += '\t\thandler->Go(handler->Call( ' + str(index)
            for (paramtype, paramname) in func.funcparams:
                if paramname and (not paramname.startswith('__') and not paramname.endswith('__')):
                    if self.isLocalPtr(paramtype, paramname):
                        res += ', RemotePtr<' + AddRToClassName(paramtype[-1]).replace('*','') + ">(" + paramname + ")"
                    else:
                        res += ', ' + paramname
            res += ' ));\n'
            res += '\t}\n'
        else:
            res += self.generateAsyncStub(index, func, False)   
            res += self.generateAsyncStub(index, func, True)   
        return res.replace('\t', '  ')
           
    def generateAsyncStub(self, index, func, useContext):
        templateContext = '''
  template <typename T, typename C>
  rpc::ECallResult::Enum ${func_name}( ${func_params}T* object, void (T::*func)(${func_return} result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( ${func_index}$func_callparams );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::${func_functor}<T, ${func_returnf}, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  
'''         
        templateNoContext = '''
  template <typename T>
  rpc::ECallResult::Enum ${func_name}( ${func_params}T* object, void (T::*func)(${func_return} result) )
  {           
    rpc::Transaction* transaction = handler->Call( ${func_index}$func_callparams );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::${func_functor}<T, ${func_returnf}>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  
'''         
        if useContext:
            template = templateContext
        else:
            template = templateNoContext
            
        pres = ''
        for (paramtype, paramname) in func.funcparams:
            if paramname:
                pres += ' '.join(paramtype) + ' ' + paramname + ', ' 
                
        pres2 = ''        
        for (paramtype, paramname) in func.funcparams:
            if paramname:
                if self.isLocalPtr(paramtype, paramname):
                    pres2 += ', RemotePtr<' + AddRToClassName(paramtype[-1]).replace('*','') + ">(" + paramname + ")"
                else:
                    pres2 += ', ' + paramname
                
        params = {
            'func_name' : func.funcname,
            'func_params' : pres,
            'func_return' : func.funcreturn,
            'func_index' : str(index),
            'func_callparams' : pres2,
        }
        functorName = 'Functor'
        if useContext:
            functorName += 'Context'
        else:
            functorName += 'NoContext'
        if func.funcreturn.find('&') != -1:
            functorName = 'Ref' + functorName
            params['func_returnf'] = func.funcreturn.replace('&','')
        else:    
            params['func_returnf'] = func.funcreturn
        params['func_functor'] = functorName
            
        return Template(template).safe_substitute(params)    

    def generateLFunc( self, func, index ):
        string = ''
        full_func_name = self.parser.classnamespace + "::" + self.parser.classname + "::" + func.funcname
        string += '\t\t\tcase ' + str(index) + ': { NI_PROFILE_BLOCK("%s/%d");' % (full_func_name, index)

        if func.funcreturn.find('void') == -1:
            string += "\n\t\t\t{\n\t\t\t\t" + func.funcreturn + " result = "

        if func.typedef.istypedefed:
            string += "rpc::VCall( stack, localObject"
            string += ".Get()"
            string += ", " + func.typedef.ref + "(&" + full_func_name + "), popResult); "
        else:    
            string += "rpc::VCall( stack, localObject"
            string += ".Get()"
            string += ", &" + full_func_name + ", popResult); "

        if func.funcreturn.find('void') == -1:
            if testForSimpleType(func.funcreturn.split(' ')) or func.funcreturn.find('&') != -1 or func.funcreturn.find('*') != -1:
                string += "\n\t\t\t\tcall.Prepare(" + str(index) + ").Push(result);\n"
            else:
                string += "\n\t\t\t\tcall.Prepare(" + str(index) + ").PushByValue(result);\n"
            string += "\t\t\t}\n\t\t\t"

        string += '} break;\n'

        return string
        
    def OpenTemplate(self, path):
        head, tail = os.path.split(os.path.abspath(__file__))
        name = os.path.join(head, path)
        f = open( name, 'r' )
        return f.read()

    def generateRClassH( self ):
        template = self.OpenTemplate('RClassH.te')

        include_str = "#include \""+os.path.basename(self.parser.filename)+"\"";

        if self.parser.interfaceInheritance:
            template = Template( template ).safe_substitute( { 'rpc_includes' : include_str } )
            template = Template( template ).safe_substitute( { 'rpc_interface' : self.parser.classname } )
        else:
            template = Template( template ).safe_substitute( { 'rpc_includes' : '' } )
            template = Template( template ).safe_substitute( { 'rpc_interface' : 'rpc::IRemoteEntity' } )
                
        template = Template( template ).safe_substitute( { 'rpc_classname' : self.parser.classname } )

        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += 'namespace ' + namespace + '\n{\n'
        template = Template( template ).safe_substitute( { 'rpc_namespaces_start' : namespaces_str } )

        template = Template( template ).safe_substitute( { 'rpc_iid' : self.parser.classnamecrc32 } )
        template = Template( template ).safe_substitute( { 'rpc_crc32' : str(self.parser.crc32) } )
        template = Template( template ).safe_substitute( { 'rpc_fullnamespace' : self.parser.classnamespace } )
        
        index = 0
        funcs_str = ''
        for func in self.parser.funcs:
            funcs_str += self.generateRFunc( func, index )
            index += 1
        template = Template( template ).safe_substitute( { 'rpc_funcs' : funcs_str } )

        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += '}\n'
        template = Template( template ).safe_substitute( { 'rpc_namespaces_end' : namespaces_str } )
        
        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += namespace + '_'
        template = Template( template ).safe_substitute( { 'rpc_formatnamespace' : namespaces_str } )
        
        if self.parser.data:
            constructor_str = ""
            datafunc_str = ""
            rollback_synchronize_str = ""
            data_str = ""
            constructor_body_str = ""
            for datainfo in self.parser.data:
                constructor_str += datainfo.getConstructorStr()
                constructor_body_str += datainfo.getConstructorBodyStr()
                datafunc_str += datainfo.getFuncStr()
                data_str += datainfo.getDataStr()
            if datafunc_str:
                datafunc_str += """  virtual void Commit(bool publishAfterCommit=false)
  {
    handler->Commit(publishAfterCommit);
  }

  void Rollback()
  {
    handler->Rollback(this);
  }"""
                rollback_synchronize_str += """  virtual bool RollbackMember(byte member_id, rpc::ArgReader& s) 
  {
    switch (member_id)
    {
"""
                for datainfo in self.parser.data:
                    rollback_synchronize_str += datainfo.getRollbackStr()
                rollback_synchronize_str += """    default:
      return false;
    }
    return true;
  }

  virtual bool Synchronize(rpc::ArgWriter* args)
  {
"""
                for datainfo in self.parser.data:
                    rollback_synchronize_str += datainfo.getSynchronizeStr()
            
                rollback_synchronize_str += """    return true;
  }
"""                

            rvset_str = "  virtual bool vset(byte member_id, rpc::ArgReader& s)\n  {\n    switch (member_id)\n    {\n";
            for datainfo in self.parser.data:
                rvset_str += datainfo.getRVsetStr()
            rvset_str += "    default:\n      return false;\n    }\n  }\n"
            
            
            template = Template( template ).safe_substitute( { 'rpc_data_constructor' : constructor_str } )
            template = Template( template ).safe_substitute( { 'rpc_data_constructor_body' : constructor_body_str } )
            template = Template( template ).safe_substitute( { 'rpc_datafuncs' : datafunc_str } )
            template = Template( template ).safe_substitute( { 'rpc_rollback_synchronize' : rollback_synchronize_str } )
            template = Template( template ).safe_substitute( { 'rpc_data_rvset' : rvset_str } )
            template = Template( template ).safe_substitute( { 'rpc_data' : data_str } )
                
        else:
            template = Template( template ).safe_substitute( { 'rpc_data_constructor' : '' } )
            template = Template( template ).safe_substitute( { 'rpc_data_constructor_body' : '' } )
            template = Template( template ).safe_substitute( { 'rpc_datafuncs' : '' } )
            template = Template( template ).safe_substitute( { 'rpc_rollback_synchronize' : '' } )
            template = Template( template ).safe_substitute( { 'rpc_data' : '' } )
            template = Template( template ).safe_substitute( { 'rpc_data_rvset' : '' } )

        return template

    def generateLClassH( self ):
        if self.parser.classIsCObjectBase:
            fileName = 'LClassH_CObjectBase.te'
        else:
            fileName = 'LClassH.te'
        template = self.OpenTemplate(fileName)
        rpc_stack = ''

        if len(self.parser.funcs) > 0:
            rpc_stack += '''
    static const rpc::MethodInfo methods[] = 
    {
'''
            for index, func in enumerate(self.parser.funcs):
                recieve = 'false'
                if index in self.parser.recieve_time_func_indices:
                    recieve = 'true'
                full_function_name = '%s::%s::%s' % (self.parser.classnamespace, self.parser.classname, func.funcname)
                rpc_stack += '        { "%s", %d, %s, rpc::GetMethodCode(&%s) },\n' % (full_function_name, len(func.funcparams), recieve, full_function_name)

            rpc_stack += '''    };
    if (call.id >= sizeof(methods)/sizeof(rpc::MethodInfo) || call.id < 0)
    {
      return rpc::CallResult::WrongMethodId;
    }
'''
            rpc_stack += '    rpc::MethodCallStack stack = rpc::FillStack(call, args, paramsData, _paramsSize, methods[call.id]);'    
            rpc_stack += '\n    if (true || stack.methodCode == methods[call.id].methodCode)'
            rpc_stack += '\n    {'
            rpc_stack += '\n      if ( !stack.isValid ) return rpc::CallResult::DataCorruption;'
            rpc_stack += '\n      return vcall(call.id, resultCall, stack) ? rpc::CallResult::OK : rpc::CallResult::StackCorruption;'
            rpc_stack += '\n    }' 
            rpc_stack += '\n    else' 
            rpc_stack += '\n    {' 
            rpc_stack += '\n      return rpc::CallResult::WrongMethodCode;' 
            rpc_stack += '\n    }' 
        else:
            rpc_stack += '\n    return rpc::CallResult::DataCorruption;'

        template = Template( template ).safe_substitute( { 'rpc_classname' : self.parser.classname, 'rpc_stack' : rpc_stack } )
        template = Template( template ).safe_substitute( { 'rpc_classheader' : os.path.basename( self.parser.filename ) } )
        template = Template( template ).safe_substitute( { 'rpc_iid' : self.parser.classnamecrc32 } )
        template = Template( template ).safe_substitute( { 'rpc_crc32' : str(self.parser.crc32) } )
        template = Template( template ).safe_substitute( { 'rpc_fullnamespace' : self.parser.classnamespace } )

        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += 'namespace ' + namespace + '\n{\n'
        template = Template( template ).safe_substitute( { 'rpc_namespaces_start' : namespaces_str } )

        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += '}\n'
        template = Template( template ).safe_substitute( { 'rpc_namespaces_end' : namespaces_str } )
        
        if self.parser.data:
            vsetStr = "  virtual bool vset(byte member_id, rpc::ArgReader& s)\n  {\n    switch (member_id)\n    {\n"
            updateStr = "  virtual void Update(rpc::ArgWriter* args)\n  {\n"
            
            getMemberStr = "  virtual int GetMemberIndex(const void* memory)\n  {\n"
            for datainfo in self.parser.data:
                vsetStr += datainfo.getVsetStr()
                getMemberStr += datainfo.getMemberStr()
                updateStr += datainfo.getUpdateStr()
            vsetStr += "    default:\n      return false;\n    }\n    return true;\n  }\n"
            getMemberStr += "    return -1;\n  }\n"
            updateStr += "  }\n"
            
            template = Template( template ).safe_substitute( { 'rpc_data_vset' : vsetStr } )
            template = Template( template ).safe_substitute( { 'rpc_data_getmember' : getMemberStr } )
            template = Template( template ).safe_substitute( { 'rpc_data_update' : updateStr } )
        else:
            template = Template( template ).safe_substitute( { 'rpc_data_vset' : '' } )
            template = Template( template ).safe_substitute( { 'rpc_data_getmember' : '  virtual int GetMemberIndex( const void* ) { return -1; }\n' } )
            template = Template( template ).safe_substitute( { 'rpc_data_update' : '' } )

        return template

    def generateRClassCpp( self ):
        template = self.OpenTemplate('RClassCpp.te')
        
        template = Template( template ).safe_substitute( { 'rpc_classname' : self.parser.classname } )

        template = Template( template ).safe_substitute( { 'rpc_fullnamespace' : self.parser.classnamespace } )

        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += 'namespace ' + namespace + '\n{\n'
        template = Template( template ).safe_substitute( { 'rpc_namespaces_start' : namespaces_str } )

        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += '}\n'
        template = Template( template ).safe_substitute( { 'rpc_namespaces_end' : namespaces_str } )

        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += namespace + '_'
        template = Template( template ).safe_substitute( { 'rpc_formatnamespace' : namespaces_str } )

        return template
        
    def generateLClassCpp( self ):
        template = self.OpenTemplate('LClassCpp.te')
        
        template = Template( template ).safe_substitute( { 'rpc_classname' : self.parser.classname } )
        template = Template( template ).safe_substitute( { 'rpc_iid' : self.parser.classnamecrc32 } )
        template = Template( template ).safe_substitute( { 'rpc_fullnamespace' : self.parser.classnamespace } )

        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += 'namespace ' + namespace + '\n{\n'
        template = Template( template ).safe_substitute( { 'rpc_namespaces_start' : namespaces_str } )

        index = 0
        funcs_typedefs_str = ''
        for func in self.parser.funcs:
            if func.typedef.istypedefed:
                funcs_typedefs_str += func.typedef.typedef
            index += 1
        template = Template( template ).safe_substitute( { 'rpc_funcs_typedefs' : funcs_typedefs_str } )

        index = 0
        funcs_str = ''
        for func in self.parser.funcs:
            funcs_str += self.generateLFunc( func, index )
            index += 1
        template = Template( template ).safe_substitute( { 'rpc_funcs' : funcs_str } )

        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += '}\n'
        template = Template( template ).safe_substitute( { 'rpc_namespaces_end' : namespaces_str } )

        return template

    def generateRClassCS( self ):
        template = self.OpenTemplate('RCSClass.te')
        template = Template( template ).safe_substitute( { 'rpc_classname' : self.parser.classname } )
        template = Template( template ).safe_substitute( { 'rpc_iid' : self.parser.classnamecrc32 } )
        template = Template( template ).safe_substitute( { 'rpc_crc32' : str(self.parser.crc32) } )
        template = Template( template ).safe_substitute( { 'rpc_fullnamespace' : self.parser.classnamespace } )

        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += 'namespace ' + namespace + '\n{\n'
        template = Template( template ).safe_substitute( { 'rpc_namespaces_start' : namespaces_str } )
        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += '}\n'
        template = Template( template ).safe_substitute( { 'rpc_namespaces_end' : namespaces_str } )
        
        index = 0
        funcs_str = ''
        for func in self.parser.funcs:
            funcs_str += self.generateRCSFunc( func, index )
            index += 1
        template = Template( template ).safe_substitute( { 'rpc_cs_funcs' : funcs_str } )
        
        if self.parser.data:
            list_setinfo_str = ""
            rsetdata_str = ""
            rgetdatatype_str = ""
            dataproperties = ""
            datavalues = ""
            for data in self.parser.data:
                rsetdata_str += '      case ' + str(data.dataidx) + ':\n'
                csdatatype_str = GetCSTypeFromNative( data.datatype, NativeToCSTypesMap, self.parser.typedefs )
                if csdatatype_str.find( 'StrongMT<' ) != -1:
                    csdatatype_str = csdatatype_str.replace('StrongMT<','R').replace('>','',1)
                rgetdatatype_str += '      case ' + str(data.dataidx) + ':\n'
                rgetdatatype_str += '        return typeof( ' + csdatatype_str + ');\n'
                if csdatatype_str.find('System.Collections.Generic.List') != -1:
                    rsetdata_str += '        _' + data.dataname + '.SetList( (' + csdatatype_str + ')obj );\n'
                    rsetdata_str += '        break;\n'
                    list_setinfo_str += '    _' + data.dataname + '.SetInfo( info );\n'
                    datavalues += '  private ' + csdatatype_str.replace('System.Collections.Generic.List','ManagedRPC.RPCList')
                    datavalues += ' _' + data.dataname + ' = new '
                    datavalues += csdatatype_str.replace('System.Collections.Generic.List','ManagedRPC.RPCList') + '( ' + str(data.dataidx) + ' );\n'
                    dataproperties += '  public ' + csdatatype_str.replace('System.Collections.Generic.List','ManagedRPC.RPCList') + " " + data.dataname + '\n'
                    dataproperties += '  {\n    get { return _' + data.dataname + '; }\n'
                    dataproperties += '  }\n'
                else:
                    rsetdata_str += '        _' + data.dataname + ' = ( ' + csdatatype_str + ')obj;\n'
                    rsetdata_str += '        break;\n'
                    dataproperties += '  public ' + csdatatype_str + " " + data.dataname + '\n'
                    dataproperties += '  {\n    get { return _' + data.dataname + '; }\n'
                    if csdatatype_str.find('System.String') != -1:
                        datavalues += '  private ' + csdatatype_str +' _' + data.dataname + ' = "";\n'
                        dataproperties += '    set { _' + data.dataname + ' = (' + csdatatype_str + ')(info.SetMember( '
                        dataproperties += str(data.dataidx) +  ', (object)value, (object)_' + data.dataname + ', 0, 4, 0 )); }\n'
                    else:
                        datavalues += '  private ' + csdatatype_str +' _' + data.dataname + ' = new ' + csdatatype_str + '();\n'
                        dataproperties += '    set { _' + data.dataname + ' = (' + csdatatype_str + ')(info.Set( '
                        dataproperties += str(data.dataidx) +  ', (object)value, (object)_' + data.dataname + ' )); }\n'
                    dataproperties += '  }\n'
                
            template = Template( template ).safe_substitute( { 'rpc_list_setinfo' : list_setinfo_str } )
            template = Template( template ).safe_substitute( { 'rpc_cs_data_rsetdata' : rsetdata_str } )
            template = Template( template ).safe_substitute( { 'rpc_cs_data_rgetdatatype' : rgetdatatype_str } )
            template = Template( template ).safe_substitute( { 'rpc_cs_data_dataproperties' : dataproperties } )
            template = Template( template ).safe_substitute( { 'rpc_cs_data_datavalues' : datavalues } )
        else:
            template = Template( template ).safe_substitute( { 'rpc_list_setinfo' : '' } )
            template = Template( template ).safe_substitute( { 'rpc_cs_data_rsetdata' : '' } )
            template = Template( template ).safe_substitute( { 'rpc_cs_data_rgetdatatype' : '' } )
            template = Template( template ).safe_substitute( { 'rpc_cs_data_dataproperties' : '' } )
            template = Template( template ).safe_substitute( { 'rpc_cs_data_datavalues' : '' } )
        return template

    def generateLClassCS( self ):
        template = self.OpenTemplate('LCSClass.te')
        template = Template( template ).safe_substitute( { 'rpc_classname' : self.parser.classname } )
        template = Template( template ).safe_substitute( { 'rpc_iid' : self.parser.classnamecrc32 } )
        template = Template( template ).safe_substitute( { 'rpc_crc32' : str(self.parser.crc32) } )
        template = Template( template ).safe_substitute( { 'rpc_fullnamespace' : self.parser.classnamespace } )

        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += 'namespace ' + namespace + '\n{\n'
        template = Template( template ).safe_substitute( { 'rpc_namespaces_start' : namespaces_str } )
        namespaces_str = ''
        for namespace in self.parser.namespace.GetNamespaces( self.parser.classpos ):
            namespaces_str += '}\n'
        template = Template( template ).safe_substitute( { 'rpc_namespaces_end' : namespaces_str } )

        index = 0
        funcs_str = ''
        for func in self.parser.funcs:
            funcs_str += self.generateLCSFunc( func, index )
            index += 1
        template = Template( template ).safe_substitute( { 'rpc_cs_funcs' : funcs_str } )

        index = 0
        funcs_str = ''
        for func in self.parser.funcs:
            funcs_str += self.generateLCSParamTypes( func, index )
            index += 1
        template = Template( template ).safe_substitute( { 'rpc_cs_param_types' : funcs_str } )

        if self.parser.data:
            template = Template( template ).safe_substitute( { 'rpc_cs_data_nums' : str(len(self.parser.data)) } )
            data_names_str = ""
            lgetdata_str = ""
            lsetdata_str = ""
            for data in self.parser.data:
                data_names_str += 'localObject.' + data.dataname + ', '
                lgetdata_str += '      case ' + str(data.dataidx) + ':\n'
                lgetdata_str += '        return localObject.' + data.dataname + ';\n'
                lsetdata_str += '      case ' + str(data.dataidx) + ':\n'
                csdatatype_str = GetCSTypeFromNative( data.datatype, NativeToCSTypesMap, self.parser.typedefs )
                if csdatatype_str.find( 'StrongMT<' ) != -1:
                    csdatatype_str = csdatatype_str.replace('StrongMT<','R').replace('>','',1)
                lsetdata_str += '        localObject.' + data.dataname + ' = (' + csdatatype_str + ')obj;\n'
                lsetdata_str += '        break;\n'
            data_names_str = data_names_str[0:-2]
            template = Template( template ).safe_substitute( { 'rpc_cs_data_names' : data_names_str } )
            template = Template( template ).safe_substitute( { 'rpc_cs_data_lgetdata' : lgetdata_str } )
            template = Template( template ).safe_substitute( { 'rpc_cs_data_lsetdata' : lsetdata_str } )
        else:
            template = Template( template ).safe_substitute( { 'rpc_cs_data_nums' : '0' } )
            template = Template( template ).safe_substitute( { 'rpc_cs_data_names' : '' } )
            template = Template( template ).safe_substitute( { 'rpc_cs_data_lgetdata' : '' } )
            template = Template( template ).safe_substitute( { 'rpc_cs_data_lsetdata' : '' } )


        return template

class MetaCodeGenRPC:
    def __init__( self, dirname, filename, rcode_h, rcode_cpp, lcode_h, lcode_cpp, rcodecs, lcodecs, includes = [] ):
        self.dirname = dirname
        self.fullfilename = filename
        self.filename = os.path.splitext(os.path.basename(filename))[0]
        self.includes = includes
        self.rcode_h = rcode_h
        self.rcode_cpp = rcode_cpp
        self.lcode_h = lcode_h
        self.lcode_cpp = lcode_cpp
        self.rcodecs = rcodecs
        self.lcodecs = lcodecs
        
    def generateRFiles( self ):
        template = self.OpenTemplate('RFileH.te')
        template = Template( template ).safe_substitute( { 'rpc_classname' : self.filename.replace('.','_') } )
        template = Template( template ).safe_substitute( { 'rpc_filename' : self.filename } )
        includes_str = ''
        for addinc in self.includes:
            includes_str += '#include \"' + addinc + '\"\n';
        template = Template( template ).safe_substitute( { 'rpc_includes' : includes_str } )
        template = Template( template ).safe_substitute( { 'rpc_classhes' : self.rcode_h } )
        
        oldcode_h = ""
        filename_h = self.dirname + '/R' + self.filename + '.auto.h'
        if os.path.isfile( filename_h ):
            file = open( filename_h, 'r' )
            oldcode_h = file.read( )
            file.close()
        if template != oldcode_h:
            file = open( filename_h, 'w' )
            file.write( template )
            file.close()

        template = self.OpenTemplate('RFileCpp.te')
        template = Template( template ).safe_substitute( { 'rpc_classname' : self.filename.replace('.','_') } )
        template = Template( template ).safe_substitute( { 'rpc_filename' : self.filename } )
        template = Template( template ).safe_substitute( { 'rpc_classcpps' : self.rcode_cpp } )
            
        oldcode_cpp = ""
        filename_cpp = self.dirname + '/R' + self.filename + '.auto.cpp'
        if os.path.isfile( filename_cpp ):
            file = open( filename_cpp, 'r' )
            oldcode_cpp = file.read( )
            file.close()
        if template != oldcode_cpp:
            file = open( filename_cpp, 'w' )
            file.write( template )
            file.close()
            
        return [ filename_h, filename_cpp ]

    def generateLFiles( self ):
        template = self.OpenTemplate('LFileH.te')
        template = Template( template ).safe_substitute( { 'rpc_classname' : self.filename.replace('.','_') } )
        template = Template( template ).safe_substitute( { 'rpc_filename' : self.filename } )
        template = Template( template ).safe_substitute( { 'rpc_classheader' : os.path.basename( self.fullfilename ) } )
        template = Template( template ).safe_substitute( { 'rpc_classhes' : self.lcode_h } )
        includes_str = ''
        for addinc in self.includes:
            includes_str += '#include \"' + addinc + '\"\n';
        template = Template( template ).safe_substitute( { 'rpc_includes' : includes_str } )

        oldcode_h = ""
        filename_h = self.dirname + '/L' + self.filename + '.auto.h'
        if os.path.isfile( filename_h ):
            file = open( filename_h, 'r' )
            oldcode_h = file.read( )
            file.close()
        if template != oldcode_h:
            file = open( filename_h, 'w' )
            file.write( template )
            file.close()

        template = self.OpenTemplate('LFileCpp.te')
        template = Template( template ).safe_substitute( { 'rpc_classname' : self.filename.replace('.','_') } )
        template = Template( template ).safe_substitute( { 'rpc_filename' : self.filename } )
        template = Template( template ).safe_substitute( { 'rpc_classcpps' : self.lcode_cpp } )
            
        oldcode_cpp = ""
        filename_cpp = self.dirname + '/L' + self.filename + '.auto.cpp'
        if os.path.isfile( filename_cpp ):
            file = open( filename_cpp, 'r' )
            oldcode_cpp = file.read( )
            file.close()
        if template != oldcode_cpp:
            file = open( filename_cpp, 'w' )
            file.write( template )
            file.close()
            
        return [ filename_h, filename_cpp ]

    def generateRCSFiles( self ):
        oldcode = ""
        filename = self.dirname + '/R' + self.filename + '.auto.cs'
        if os.path.isfile( filename ):
            file = open( filename, 'r' )
            oldcode = file.read( )
            file.close()
        if self.rcodecs != oldcode:
            file = open( filename, 'w' )
            file.write( self.rcodecs )
            file.close()
          
        return [ filename ]

    def generateLCSFiles( self ):
        oldcode = ""
        filename = self.dirname + '/L' + self.filename + '.auto.cs'
        if os.path.isfile( filename ):
            file = open( filename, 'r' )
            oldcode = file.read( )
            file.close()
        if self.lcodecs != oldcode:
            file = open( filename, 'w' )
            file.write( self.lcodecs )
            file.close()
          
        return [ filename ]

    def OpenTemplate(self, path):
        head, tail = os.path.split(os.path.abspath(__file__))
        name = os.path.join(head, path)
        f = open( name, 'r' )
        return f.read()


def getFileName():
    return __file__

        
def main(path):
    parser = Parser( os.path.abspath( path ) )

    parser.parseNamespace()

    classes = parser.getAllClasses()

    rcode_h = ""
    rcode_cpp = ""
    lcode_h = ""
    lcode_cpp = ""
    rcodecs = ""
    lcodecs = ""

    for c in classes:
        parser.parseClass( c )
        funcs = parser.getAllFuncs()
        for func in funcs:
            parser.parseFunction( func )

        codegen = CodeGenRPC( parser )
        rcode_h += codegen.generateRClassH()
        rcode_cpp += codegen.generateRClassCpp()
        lcode_h += codegen.generateLClassH()
        lcode_cpp += codegen.generateLClassCpp()
        lcodecs += codegen.generateLClassCS()
        rcodecs += codegen.generateRClassCS()

    metacodegen = MetaCodeGenRPC( parser.filename, rcode_h, rcode_cpp, lcode_h, lcode_cpp, rcodecs, lcodecs, [] )
    metacodegen.generateRFiles()
    metacodegen.generateLFiles()
    metacodegen.generateRCSFiles()
    metacodegen.generateLCSFiles()
