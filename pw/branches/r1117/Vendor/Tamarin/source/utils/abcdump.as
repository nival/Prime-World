/* -*- indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

package abcdump
{
    import flash.utils.ByteArray
    import avmplus.System

    include "abc-constants.as"
    
    var usage = [
    "Displays the contents of abc or swf files",
    "",
    "Usage:",
    "",
    "    abcdump [options] file ...",
    "",
    "Each file can be an ABC or SWF/SWC format file",
    "",
    "Options:",
    "",
    " -a   Extract the ABC blocks from the SWF/SWC, but do not",
    "      otherwise display their contents.  The file names are",
    "      of the form file<n>.abc where \"file\" is the name",
    "      of the input file minus the .swf/.swc extension;",
    "      and <n> is omitted if it is 0.",
    "",
    " -i   Print information about the ABC, but do not dump the byte code.",
    "",
    " -abs Print the bytecode, but no information about the ABC",
    ].join("\n");

    const TAB = "  "
    
    var totalSize:int
    var opSizes:Array = new Array(256)

    function dumpPrint(s) {
        if (doExtractAbs)
            print(s);
    }

    function infoPrint(s) {
        if (doExtractInfo)
            print((doExtractAbs ? "// " : "") + s)
    }

    class Multiname
    {
        var nsset:Array
        var name:String
        function Multiname(nsset:Array, name:String)
        {
            this.nsset = nsset
            this.name = name
        }
        
        public function toString()
        {
            return /*'{' + nsset + '}::' + */name
        }
    }
    
    class TypeName
    {
        var name;
        var types:Array;
        function TypeName(name, types)
        {
            this.name = name;
            this.types = types;
        }
        
        public function toString()
        {
            var s : String = name.toString();
            s += ".<"
            for( var i = 0; i < types.length; ++i )
                s += types[i] != null ? types[i].toString() : "*" + " ";
            s += ">"
            return s;
        }
    }
    
    dynamic class MetaData
    {
        var name:String
        public function toString():String 
        {
            var last:String
            var s:String = last = '['+name+'('
            var n
            for (n in this)
                s = (last = s + n + "=" + '"' + this[n] + '"') + ','
            return last + ')]'
        }
    }
    
    class MemberInfo
    {
        var id:int
        var kind:int
        var name
        var metadata:Array
    }

    dynamic class LabelInfo
    {
        var count:int
        function labelFor (target:int):String
        {
            if (target in this)
                return this[target]
            return this[target] = "L" + (++count)
        }
    }
    
    class MethodInfo extends MemberInfo
    {
        var method_id:int
        var dumped:Boolean
        var flags:int
        var debugName
        var paramTypes
        var optionalValues
        var returnType
        var local_count:int
        var max_scope:int
        var max_stack:int
        var code_length:uint
        var code:ByteArray
        var activation:Traits

        public function toString():String
        {
            return format()
        }
        
        public function format():String
        {
            var name = this.name ? this.name : "function"

            return name + "(" + paramTypes + "):" + returnType + "\t/* disp_id=" + id + " method_id=" + method_id + " */"
        }

        function dump(abc:Abc, indent:String, attr:String="")
        {
            dumped = true
            dumpPrint("")

            if (metadata) {
                for each (var md in metadata)
                    dumpPrint(indent+md)
            }

            var s:String = ""
            if (flags & NATIVE)
                s = "native "
            s += traitKinds[kind] + " " 

            dumpPrint(indent+attr+s+format())
            if (code)
            {
                dumpPrint(indent+"{")
                var oldindent = indent
                indent += TAB
                if (flags & NEED_ACTIVATION) {
                    dumpPrint(indent+"activation {")
                    activation.dump(abc, indent+TAB, "")
                    dumpPrint(indent+"}")
                }
                dumpPrint(indent+"// local_count="+local_count+
                          " max_scope=" + max_scope +
                          " max_stack=" + max_stack +
                          " code_len=" + code.length) 
                code.position = 0
                var labels:LabelInfo = new LabelInfo()
                while (code.bytesAvailable > 0)
                {
                    var start:int = code.position
                    var s = indent + start
                    while (s.length < 12) s += ' ';
                    var opcode = code.readUnsignedByte()

                    if (opcode == OP_label || ((code.position-1) in labels)) {
                        dumpPrint(indent)
                        dumpPrint(indent + labels.labelFor(code.position-1) + ": ")
                    }

                    s += opNames[opcode]
                    s += opNames[opcode].length < 8 ? "\t\t" : "\t"
                        
                    switch(opcode)
                    {
                        case OP_debugfile:
                        case OP_pushstring:
                            s += '"' + abc.strings[readU32()].replace(/\n/g,"\\n").replace(/\t/g,"\\t") + '"'
                            break
                        case OP_pushnamespace:
                            s += abc.namespaces[readU32()]
                            break
                        case OP_pushint:
                            var i:int = abc.ints[readU32()]
                            s += i + "\t// 0x" + i.toString(16)
                            break
                        case OP_pushuint:
                            var u:uint = abc.uints[readU32()]
                            s += u + "\t// 0x" + u.toString(16)
                            break;
                        case OP_pushdouble:
                            s += abc.doubles[readU32()]
                            break;
                        case OP_getsuper: 
                        case OP_setsuper: 
                        case OP_getproperty: 
                        case OP_initproperty: 
                        case OP_setproperty: 
                        case OP_getlex: 
                        case OP_findpropstrict: 
                        case OP_findproperty:
                        case OP_finddef:
                        case OP_deleteproperty: 
                        case OP_istype: 
                        case OP_coerce: 
                        case OP_astype: 
                        case OP_getdescendants:
                            s += abc.names[readU32()]
                            break;
                        case OP_constructprop:
                        case OP_callproperty:
                        case OP_callproplex:
                        case OP_callsuper:
                        case OP_callsupervoid:
                        case OP_callpropvoid:
                            s += abc.names[readU32()]
                            s += " (" + readU32() + ")"
                            break;
                        case OP_newfunction: {
                            var method_id = readU32()
                            s += abc.methods[method_id]
                            break;
                        }
                        case OP_callstatic:
                            s += abc.methods[readU32()]
                            s += " (" + readU32() + ")"
                            break;
                        case OP_newclass: 
                            s += abc.instances[readU32()]
                            break;
                        case OP_lookupswitch:
                            var pos = code.position-1;
                            var target = pos + readS24()
                            var maxindex = readU32()
                            s += "default:" + labels.labelFor(target) // target + "("+(target-pos)+")"
                            s += " maxcase:" + maxindex
                            for (var i:int=0; i <= maxindex; i++) {
                                target = pos + readS24();
                                s += " " + labels.labelFor(target) // target + "("+(target-pos)+")"
                            }
                            break;
                        case OP_jump:
                        case OP_iftrue:     case OP_iffalse:
                        case OP_ifeq:       case OP_ifne:
                        case OP_ifge:       case OP_ifnge:
                        case OP_ifgt:       case OP_ifngt:
                        case OP_ifle:       case OP_ifnle:
                        case OP_iflt:       case OP_ifnlt:
                        case OP_ifstricteq: case OP_ifstrictne:
                            var offset = readS24()
                            var target = code.position+offset
                            //s += target + " ("+offset+")"
                            s += labels.labelFor(target)
                            if (!((code.position) in labels))
                                s += "\n"
                            break;
                        case OP_inclocal:
                        case OP_declocal:
                        case OP_inclocal_i:
                        case OP_declocal_i:
                        case OP_getlocal:
                        case OP_kill:
                        case OP_setlocal:
                        case OP_debugline:
                        case OP_getglobalslot:
                        case OP_getslot:
                        case OP_setglobalslot:
                        case OP_setslot:
                        case OP_pushshort:
                        case OP_newcatch:
                            s += readU32()
                            break
                        case OP_debug:
                            s += code.readUnsignedByte() 
                            s += " " + readU32()
                            s += " " + code.readUnsignedByte()
                            s += " " + readU32()
                            break;
                        case OP_newobject:
                            s += "{" + readU32() + "}"
                            break;
                        case OP_newarray:
                            s += "[" + readU32() + "]"
                            break;
                        case OP_call:
                        case OP_construct:
                        case OP_constructsuper:
                        case OP_applytype:
                            s += "(" + readU32() + ")"
                            break;
                        case OP_pushbyte:
                        case OP_getscopeobject:
                            s += code.readByte()
                            break;
                        case OP_hasnext2:
                            s += readU32() + " " + readU32()
                        default:
                            /*if (opNames[opcode] == ("0x"+opcode.toString(16).toUpperCase()))
                                s += " UNKNOWN OPCODE"*/
                            break
                    }
                    var size:int = code.position - start
                    totalSize += size
                    opSizes[opcode] = int(opSizes[opcode]) + size
                    dumpPrint(s)
                }
                dumpPrint(oldindent+"}\n")
            }
        }
        
        function readU32():int
        {
            var result:int = code.readUnsignedByte();
            if (!(result & 0x00000080))
                return result;
            result = result & 0x0000007f | code.readUnsignedByte()<<7;
            if (!(result & 0x00004000))
                return result;
            result = result & 0x00003fff | code.readUnsignedByte()<<14;
            if (!(result & 0x00200000))
                return result;
            result = result & 0x001fffff | code.readUnsignedByte()<<21;
            if (!(result & 0x10000000))
                return result;
            return   result & 0x0fffffff | code.readUnsignedByte()<<28;
        }
        
        function readS24():int
        {
            var b:int = code.readUnsignedByte()
            b |= code.readUnsignedByte()<<8
            b |= code.readByte()<<16
            return b
        }
    }
    
    class SlotInfo extends MemberInfo
    {
        var type
        var value
        public function format():String
        {
            return traitKinds[kind] + " " + name + ":" + type + 
                (value !== undefined ? (" = " + (value is String ? ('"'+value+'"') : value)) : "") + 
                "\t/* slot_id " + id + " */"
        }
        function dump(abc:Abc, indent:String, attr:String="")
        {
            if (kind == TRAIT_Const || kind == TRAIT_Slot)
            {
                if (metadata) {
                    for each (var md in metadata)
                        dumpPrint(indent+md)
                }
                dumpPrint(indent+attr+format())
                return
            }
            
            // else, class
            
            var ct:Traits = value
            var it:Traits = ct.itraits
            dumpPrint('')
            if (metadata) {
                for each (var md in metadata)
                    dumpPrint(indent+md)
            }
            var def:String;
            if (it.flags & CLASS_FLAG_interface)
                def = "interface"
            else {
                def = "class";
                if (!(it.flags & CLASS_FLAG_sealed))
                    def = "dynamic " + def;
                if (it.flags & CLASS_FLAG_final)
                    def = "final " + def;
                    
            }
            dumpPrint(indent+attr+def+" "+name+" extends "+it.base)
            var oldindent = indent
            indent += TAB
            if (it.interfaces.length > 0)
                dumpPrint(indent+"implements "+it.interfaces)
            dumpPrint(oldindent+"{")
            it.init.dump(abc,indent)
            it.dump(abc,indent)
            ct.dump(abc,indent,"static ")
            ct.init.dump(abc,indent,"static ")
            dumpPrint(oldindent+"}\n")
        }
    }
    
    class Traits
    {
        var name
        var init:MethodInfo
        var itraits:Traits
        var base
        var flags:int
        var protectedNs:Namespace
        const interfaces:Array = []
        const names:Object = {}
        const slots:Array = []
        const methods:Array = []
        const members:Array = []
        
        public function toString():String
        {
            return String(name)
        }
        
        public function dump(abc:Abc, indent:String, attr:String="")
        {
            for each (var m in members)
                m.dump(abc, indent, attr)
        }
    }

    class Abc
    {
        private var data:ByteArray
        
        var major:int
        var minor:int
        
        var ints:Array
        var uints:Array
        var doubles:Array
        var strings:Array
        var namespaces:Array
        var nssets:Array
        var names:Array
        
        var defaults:Array = new Array(constantKinds.length)
        
        var methods:Array
        var instances:Array
        var classes:Array
        var scripts:Array
        
        var publicNs = new Namespace("")
        var anyNs = new Namespace("*")

        var magic:int
        
        function Abc(data:ByteArray)
        {
            data.position = 0
            this.data = data
            magic = data.readInt()

            infoPrint("magic " + magic.toString(16))

            if (magic != (46<<16|14) && magic != (46<<16|15) && magic != (46<<16|16))
                throw new Error("not an abc file.  magic=" + magic.toString(16))
            
            parseCpool()
            
            defaults[CONSTANT_Utf8] = strings
            defaults[CONSTANT_Int] = ints
            defaults[CONSTANT_UInt] = uints
            defaults[CONSTANT_Double] = doubles
            defaults[CONSTANT_Int] = ints
            defaults[CONSTANT_False] = { 10:false }
            defaults[CONSTANT_True] = { 11:true }
            defaults[CONSTANT_Namespace] = namespaces
            defaults[CONSTANT_PrivateNs] = namespaces
            defaults[CONSTANT_PackageNs] = namespaces
            defaults[CONSTANT_PackageInternalNs] = namespaces
            defaults[CONSTANT_ProtectedNs] = namespaces
            defaults[CONSTANT_StaticProtectedNs] = namespaces
            defaults[CONSTANT_StaticProtectedNs2] = namespaces
            defaults[CONSTANT_Null] = { 12: null }      
            
            parseMethodInfos()
            parseMetadataInfos()
            parseInstanceInfos()
            parseClassInfos()
            parseScriptInfos()
            parseMethodBodies()

            if (doExtractAbc==true)
                data.writeFile(nextAbcFname());
        }
    
        function readU32():int
        {
            var result:int = data.readUnsignedByte();
            if (!(result & 0x00000080))
                return result;
            result = result & 0x0000007f | data.readUnsignedByte()<<7;
            if (!(result & 0x00004000))
                return result;
            result = result & 0x00003fff | data.readUnsignedByte()<<14;
            if (!(result & 0x00200000))
                return result;
            result = result & 0x001fffff | data.readUnsignedByte()<<21;
            if (!(result & 0x10000000))
                return result;
            return   result & 0x0fffffff | data.readUnsignedByte()<<28;
        }
        
        function parseCpool()
        {
            var i:int, j:int
            var n:int
            var kind:int

            var start:int = data.position
            
            // ints
            n = readU32()
            ints = [0]
            for (i=1; i < n; i++)
                ints[i] = readU32()
                
            // uints
            n = readU32()
            uints = [0]
            for (i=1; i < n; i++)
                uints[i] = uint(readU32())
                
            // doubles
            n = readU32()
            doubles = [NaN]
            for (i=1; i < n; i++)
                doubles[i] = data.readDouble()

            infoPrint("Cpool numbers size "+(data.position-start)+" "+int(100*(data.position-start)/data.length)+" %")
            start = data.position
            
            // strings
            n = readU32()
            strings = [""]
            for (i=1; i < n; i++)
                strings[i] = data.readUTFBytes(readU32())

            infoPrint("Cpool strings count "+ n +" size "+(data.position-start)+" "+int(100*(data.position-start)/data.length)+" %")
            start = data.position
            
            // namespaces
            n = readU32()
            namespaces = [publicNs]
            for (i=1; i < n; i++)
                switch (data.readByte())
                {
                case CONSTANT_Namespace:
                case CONSTANT_PackageNs:
                case CONSTANT_PackageInternalNs:
                case CONSTANT_ProtectedNs:
                case CONSTANT_StaticProtectedNs:
                case CONSTANT_StaticProtectedNs2:
                {
                    namespaces[i] = new Namespace(strings[readU32()])
                    // todo mark kind of namespace.
                    break;
                }
                case CONSTANT_PrivateNs:
                    readU32();
                    namespaces[i] = new Namespace(null, "private")
                    break;
                }

            infoPrint("Cpool namespaces count "+ n +" size "+(data.position-start)+" "+int(100*(data.position-start)/data.length)+" %")
            start = data.position
            
            // namespace sets
            n = readU32()
            nssets = [null]
            for (i=1; i < n; i++)
            {
                var count:int = readU32()
                var nsset = nssets[i] = []
                for (j=0; j < count; j++)
                    nsset[j] = namespaces[readU32()]
            }

            infoPrint("Cpool nssets count "+ n +" size "+(data.position-start)+" "+int(100*(data.position-start)/data.length)+" %")
            start = data.position
            
            // multinames
            n = readU32()
            names = [null]
            namespaces[0] = anyNs
            strings[0] = "*" // any name
            for (i=1; i < n; i++)
                switch (data.readByte())
                {
                case CONSTANT_Qname:
                case CONSTANT_QnameA:
                    names[i] = new QName(namespaces[readU32()], strings[readU32()])
                    break;
                
                case CONSTANT_RTQname:
                case CONSTANT_RTQnameA:
                    names[i] = new QName(strings[readU32()])
                    break;
                
                case CONSTANT_RTQnameL:
                case CONSTANT_RTQnameLA:
                    names[i] = null
                    break;
                
                case CONSTANT_NameL:
                case CONSTANT_NameLA:
                    names[i] = new QName(new Namespace(""), null)
                    break;
                
                case CONSTANT_Multiname:
                case CONSTANT_MultinameA:
                    var name = strings[readU32()]
                    names[i] = new Multiname(nssets[readU32()], name)
                    break;

                case CONSTANT_MultinameL:
                case CONSTANT_MultinameLA:
                    names[i] = new Multiname(nssets[readU32()], null)
                    break;
                    
                case CONSTANT_TypeName:
                    var name = names[readU32()];
                    var count = readU32();
                    var types = [];
                    for( var t=0; t < count; ++t )
                        types.push(names[readU32()]);
                    names[i] = new TypeName(name, types);
                    break;
                    
                default:
                    throw new Error("invalid kind " + data[data.position-1])
                }

            infoPrint("Cpool names count "+ n +" size "+(data.position-start)+" "+int(100*(data.position-start)/data.length)+" %")
            start = data.position

            namespaces[0] = publicNs
            strings[0] = "*"
        }
        
        function parseMethodInfos()
        {
            var start:int = data.position
            names[0] = new QName(publicNs,"*")
            var method_count:int = readU32()
            methods = []
            for (var i:int=0; i < method_count; i++)
            {
                var m = methods[i] = new MethodInfo()
                m.method_id = i
                var param_count:int = readU32()
                m.returnType = names[readU32()]
                m.paramTypes = []
                for (var j:int=0; j < param_count; j++)
                    m.paramTypes[j] = names[readU32()]
                m.debugName = strings[readU32()]
                m.flags = data.readByte()
                if (m.flags & HAS_OPTIONAL)
                {
                    // has_optional
                    var optional_count:int = readU32();
                    m.optionalValues = []
                    for( var k:int = param_count-optional_count; k < param_count; ++k)
                    {
                        var index = readU32()    // optional value index
                        var kind:int = data.readByte() // kind byte for each default value
                        if (index == 0)
                        {
                            // kind is ignored, default value is based on type
                            m.optionalValues[k] = undefined
                        }
                        else
                        {
                            if (!defaults[kind])
                                print("ERROR kind="+kind+" method_id " + i)
                            else
                                m.optionalValues[k] = defaults[kind][index]
                        }
                    }
                }
                if (m.flags & HAS_ParamNames)
                {
                    // has_paramnames
                    for( var k:int = 0; k < param_count; ++k)
                    {
                        readU32();
                    }
                }
            }
            infoPrint("MethodInfo count " +method_count+ " size "+(data.position-start)+" "+int(100*(data.position-start)/data.length)+" %")
        }

        function parseMetadataInfos()
        {
            var count:int = readU32()
            metadata = []
            for (var i:int=0; i < count; i++)
            {
                // MetadataInfo
                var m = metadata[i] = new MetaData()
                m.name = strings[readU32()];
                var values_count:int = readU32();
                var names:Array = []
                for(var q:int = 0; q < values_count; ++q)
                    names[q] = strings[readU32()] // name 
                for(var q:int = 0; q < values_count; ++q)
                    m[names[q]] = strings[readU32()] // value
            }
        }

        function parseInstanceInfos()
        {
            var start:int = data.position
            var count:int = readU32()
            instances = []
            for (var i:int=0; i < count; i++)
            {
                var t = instances[i] = new Traits()
                t.name = names[readU32()]
                t.base = names[readU32()]
                t.flags = data.readByte()
                if (t.flags & 8)
                    t.protectedNs = namespaces[readU32()]
                var interface_count = readU32()
                for (var j:int=0; j < interface_count; j++)
                    t.interfaces[j] = names[readU32()]
                var m = t.init = methods[readU32()]
                m.name = t.name
                m.kind = TRAIT_Method
                m.id = -1
                parseTraits(t)
            }
            infoPrint("InstanceInfo count " + count + " size "+(data.position-start)+" "+int(100*(data.position-start)/data.length)+" %")
        }
        
        function parseTraits(t:Traits)
        {
            var namecount = readU32()
            for (var i:int=0; i < namecount; i++)
            {
                var name = names[readU32()]
                var tag = data.readByte()
                var kind = tag & 0xf
                var member
                switch(kind) {
                case TRAIT_Slot:
                case TRAIT_Const:
                case TRAIT_Class:
                    var slot = member = new SlotInfo()
                    slot.id = readU32()
                    t.slots[slot.id] = slot
                    if (kind==TRAIT_Slot || kind==TRAIT_Const)
                    {
                        slot.type = names[readU32()]
                        var index=readU32()
                        if (index)
                            slot.value = defaults[data.readByte()][index]
                    }
                    else // (kind == TRAIT_Class)
                    {
                        slot.value = classes[readU32()]
                    }
                    break;
                case TRAIT_Method:
                case TRAIT_Getter:
                case TRAIT_Setter:
                    var disp_id = readU32()
                    var method = member = methods[readU32()]
                    t.methods[disp_id] = method
                    method.id = disp_id
                    //print("\t",traitKinds[kind],name,disp_id,method,"// disp_id", disp_id)
                    break;
                }
                if (!member)
                    print("error trait kind "+kind)
                member.kind = kind
                member.name = name
                t.names[String(name)] = t.members[i] = member
                
                if ( (tag >> 4) & ATTR_metadata ) {
                    member.metadata = []
                    for(var j:int=0, mdCount:int=readU32(); j < mdCount; ++j)
                        member.metadata[j] = metadata[readU32()]
                }
            }
        }

        function parseClassInfos()
        {
            var start:int = data.position
            var count:int = instances.length
            classes = []
            for (var i:int=0; i < count; i++)
            {
                var t:Traits = classes[i] = new Traits()
                t.init = methods[readU32()]
                t.base = "Class"
                t.itraits = instances[i]
                t.name = t.itraits.name + "$"
                t.init.name = t.itraits.name + "$cinit"
                t.init.kind = TRAIT_Method
                parseTraits(t)
            }           
            infoPrint("ClassInfo count " + count + " size "+(data.position-start)+" "+int(100*(data.position-start)/data.length)+"%")
        }

        function parseScriptInfos()
        {
            var start:int = data.position
            var count:int = readU32()
            scripts = []
            for (var i:int=0; i < count; i++)
            {
                var t = new Traits()
                scripts[i] = t
                t.name = "script" + i
                t.base = names[0] // Object
                t.init = methods[readU32()]
                t.init.name = t.name + "$init"
                t.init.kind = TRAIT_Method      
                parseTraits(t)
            }
            infoPrint("ScriptInfo size "+(data.position-start)+" "+int(100*(data.position-start)/data.length)+" %")
        }

        function parseMethodBodies()
        {
            var start:int = data.position
            var count:int = readU32()
            for (var i:int=0; i < count; i++)
            {
                var m = methods[readU32()]
                m.max_stack = readU32()
                m.local_count = readU32()
                var initScopeDepth = readU32()
                var maxScopeDepth = readU32()
                m.max_scope = maxScopeDepth - initScopeDepth
                var code_length = readU32()
                m.code = new ByteArray()
                m.code.endian = "littleEndian"
                if (code_length > 0)
                    data.readBytes(m.code, 0, code_length)
                var ex_count = readU32()
                for (var j:int = 0; j < ex_count; j++)
                {
                    var from = readU32()
                    var to = readU32()
                    var target = readU32()
                    var type = names[readU32()]
                    //print("magic " + magic.toString(16))
                    //if (magic >= (46<<16|16))
                        var name = names[readU32()];
                }
                parseTraits(m.activation = new Traits)
            }
            infoPrint("MethodBodies count " + count + " size "+(data.position-start)+" "+int(100*(data.position-start)/data.length)+" %")
        }
        
        function dump(indent:String="")
        {
            for each (var t in scripts)
            {
                dumpPrint("// " + indent+t.name)
                t.dump(this,indent)
                t.init.dump(this,indent)
            }

            for each (var m in methods)
            {
                if (!m.dumped)
                    m.dump(this,indent)
            }

            infoPrint("OPCODE\tSIZE\t% OF "+totalSize)
            var done = []
            for (;;)
            {
                var max:int = -1;
                var maxsize:int = 0;
                for (var i:int=0; i < 256; i++)
                {
                    if (opSizes[i] > maxsize && !done[i])
                    {
                        max = i;
                        maxsize = opSizes[i];
                    }
                }
                if (max == -1)
                    break;
                done[max] = 1;
                infoPrint(opNames[max]+"\t"+int(opSizes[max])+"\t"+int(100*opSizes[max]/totalSize)+"%")
            }
        }
    }
    
    class Rect
    {
        var nBits:int
        var xMin:int, xMax:int
        var yMin:int, yMax:int
        public function toString()
        {
            return "[Rect "+xMin+" "+yMin+" "+xMax+" "+yMax+"]"
        }
    }
    
    const stagDoABC                 :int = 72;   // embedded .abc (AVM+) bytecode
    const stagSymbolClass               :int = 76;
    const stagDoABC2                  :int = 82;   // revised ABC version with a name

    var tagNames:Array = [
        "End",                  // 00
        "ShowFrame",            // 01
        "DefineShape",          // 02
        "FreeCharacter",        // 03
        "PlaceObject",          // 04
        "RemoveObject",         // 05
        "DefineBits",           // 06
        "DefineButton",         // 07
        "JPEGTables",           // 08
        "SetBackgroundColor",   // 09

        "DefineFont",           // 10
        "DefineText",           // 11
        "DoAction",             // 12
        "DefineFontInfo",       // 13

        "DefineSound",          // 14
        "StartSound",           // 15
        "StopSound",            // 16

        "DefineButtonSound",    // 17

        "SoundStreamHead",      // 18
        "SoundStreamBlock",     // 19

        "DefineBitsLossless",   // 20
        "DefineBitsJPEG2",      // 21

        "DefineShape2",         // 22
        "DefineButtonCxform",   // 23

        "Protect",              // 24

        "PathsArePostScript",   // 25

        "PlaceObject2",         // 26
        "27 (invalid)",         // 27
        "RemoveObject2",        // 28

        "SyncFrame",            // 29
        "30 (invalid)",         // 30
        "FreeAll",              // 31

        "DefineShape3",         // 32
        "DefineText2",          // 33
        "DefineButton2",        // 34
        "DefineBitsJPEG3",      // 35
        "DefineBitsLossless2",  // 36
        "DefineEditText",       // 37

        "DefineVideo",          // 38

        "DefineSprite",         // 39
        "NameCharacter",        // 40
        "ProductInfo",          // 41
        "DefineTextFormat",     // 42
        "FrameLabel",           // 43
        "DefineBehavior",       // 44
        "SoundStreamHead2",     // 45
        "DefineMorphShape",     // 46
        "FrameTag",             // 47
        "DefineFont2",          // 48
        "GenCommand",           // 49
        "DefineCommandObj",     // 50
        "CharacterSet",         // 51
        "FontRef",              // 52

        "DefineFunction",       // 53
        "PlaceFunction",        // 54

        "GenTagObject",         // 55

        "ExportAssets",         // 56
        "ImportAssets",         // 57

        "EnableDebugger",       // 58

        "DoInitAction",         // 59
        "DefineVideoStream",    // 60
        "VideoFrame",           // 61

        "DefineFontInfo2",      // 62
        "DebugID",              // 63
        "EnableDebugger2",      // 64
        "ScriptLimits",         // 65

        "SetTabIndex",          // 66

        "DefineShape4",         // 67
        "DefineMorphShape2",    // 68

        "FileAttributes",       // 69

        "PlaceObject3",         // 70
        "ImportAssets2",        // 71

        "DoABC",                // 72
        "73 (invalid)",         // 73
        "74 (invalid)",         // 74
        "75 (invalid)",         // 75
        "SymbolClass",          // 76
        "77 (invalid)",         // 77
        "78 (invalid)",         // 78
        "79 (invalid)",         // 79
        "80 (invalid)",         // 80
        "81 (invalid)",         // 81
        "DoABC2",               // 82
        "83 (invalid)"          // 83
    ]
    
    
    class Swf
    {
        private var bitPos:int
        private var bitBuf:int
        
        private var data:ByteArray

        function Swf(data:ByteArray)
        {
            this.data = data
            infoPrint("size "+decodeRect())
            infoPrint("frame rate "+(data.readUnsignedByte()<<8|data.readUnsignedByte()))
            infoPrint("frame count "+data.readUnsignedShort())
            decodeTags()            
        }
        
        private function decodeTags()
        {
            var type:int, h:int, length:int
            var offset:int
    
            while (data.position < data.length)
            {
                type = (h = data.readUnsignedShort()) >> 6;
    
                if (((length = h & 0x3F) == 0x3F))
                    length = data.readInt();

                infoPrint(tagNames[type]+" "+length+"b "+int(100*length/data.length)+"%")
                switch (type)
                {
                case 0: return
                case stagDoABC2:
                    var pos1:int = data.position
                    data.readInt()
                    infoPrint("\nabc name "+readString())
                    length -= (data.position-pos1)
                    // fall through
                case stagDoABC:
                    var data2 = new ByteArray
                    data2.endian = "littleEndian"
                    data.readBytes(data2,0,length)
                    new Abc(data2).dump("  ")
                    infoPrint("")
                    break 
                default:
                    data.position += length
                }
            }
        }

        private function readString():String
        {
            var s:String = ""
            var c:int

            while (c=data.readUnsignedByte())
                s += String.fromCharCode(c)

            return s
        }
        
        private function syncBits() 
        {
            bitPos = 0
        }
        
        private function decodeRect():Rect
        {
            syncBits();
    
            var rect:Rect = new Rect();
    
            var nBits:int = readUBits(5)
            rect.xMin = readSBits(nBits);
            rect.xMax = readSBits(nBits);
            rect.yMin = readSBits(nBits);
            rect.yMax = readSBits(nBits);
    
            return rect;
        }
        
        function readSBits(numBits:int):int
        {
            if (numBits > 32)
                throw new Error("Number of bits > 32");

            var num:int = readUBits(numBits);
            var shift:int = 32-numBits;
            // sign extension
            num = (num << shift) >> shift;
            return num;
        }
        
        function readUBits(numBits:int):uint
        {
            if (numBits == 0)
                return 0
    
            var bitsLeft:int = numBits;
            var result:int = 0;
    
            if (bitPos == 0) //no value in the buffer - read a byte
            {
                bitBuf = data.readUnsignedByte()
                bitPos = 8;
            }
    
            while (true)
            {
                var shift:int = bitsLeft - bitPos;
                if (shift > 0)
                {
                    // Consume the entire buffer
                    result |= bitBuf << shift;
                    bitsLeft -= bitPos;
    
                    // Get the next byte from the input stream
                    bitBuf = data.readUnsignedByte();
                    bitPos = 8;
                }
                else
                {
                    // Consume a portion of the buffer
                    result |= bitBuf >> -shift;
                    bitPos -= bitsLeft;
                    bitBuf &= 0xff >> (8 - bitPos); // mask off the consumed bits
    
    //                if (print) System.out.println("  read"+numBits+" " + result);
                    return result;
                }
            }
        }
    }

    function help()
    {
        print(usage);
        System.exit(1)
    }

    function processArg(arg:String)
    {
        if (arg == '-a') {
            doExtractAbc = true;
            doExtractInfo = false
            doExtractAbs = false
        } else if (arg == '-i') {
            // suppress abs output
            doExtractAbs = false;
        } else if (arg == '-abs') {
            // suppress info output   
            doExtractInfo = false
        } else {
            print('Unknown option '+arg)
            help()
        }
    } 

    function nextAbcFname():String
    {
        var s = currentFname
        if (currentFcount>0)
            s = s.concat(currentFcount);
        currentFcount++
        return s+'.abc'
    }   
    
    // main
    var doExtractAbc = false
    var doExtractInfo = true
    var doExtractAbs = true
    var currentFname = ''
    var currentFcount = 0
    for each (var file in System.argv)
    {
        if (file.indexOf('-')==0) 
        {
            processArg(file)
            continue
        }
        
        var x;
        if ((x = file.lastIndexOf(".swf")) != -1 || (x = file.lastIndexOf(".swc")) != -1)
            currentFname = file.substring(0,x);
        else
            currentFname = file;
        var data:ByteArray = ByteArray.readFile(file)
        data.endian = "littleEndian"
        var version:uint = data.readUnsignedInt()
        switch (version) {
        case 46<<16|14:
        case 46<<16|15:
        case 46<<16|16:
            var abc:Abc = new Abc(data)
            abc.dump()
            break
        case 67|87<<8|83<<16|10<<24: // SWC10
        case 67|87<<8|83<<16|9<<24: // SWC9
        case 67|87<<8|83<<16|8<<24: // SWC8
        case 67|87<<8|83<<16|7<<24: // SWC7
        case 67|87<<8|83<<16|6<<24: // SWC6
            var udata:ByteArray = new ByteArray
            udata.endian = "littleEndian"
            data.position = 8
            data.readBytes(udata,0,data.length-data.position)
            var csize:int = udata.length
            udata.uncompress()
            infoPrint("decompressed swf "+csize+" -> "+udata.length)
            udata.position = 0
            /*var swf:Swf =*/ new Swf(udata)
            break
        case 70|87<<8|83<<16|10<<24: // SWF10
        case 70|87<<8|83<<16|9<<24: // SWF9
        case 70|87<<8|83<<16|8<<24: // SWF8
        case 70|87<<8|83<<16|7<<24: // SWF7
        case 70|87<<8|83<<16|6<<24: // SWF6
        case 70|87<<8|83<<16|5<<24: // SWF5
        case 70|87<<8|83<<16|4<<24: // SWF4
            data.position = 8 // skip header and length
            /*var swf:Swf =*/ new Swf(data)
            break
        default:
            print('unknown format '+version)
            break
        }
    }

    if (System.argv<2)
        help();
}

