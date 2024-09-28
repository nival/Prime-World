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


#include "avmplus.h"
#ifdef AVMC_STANDALONE
#  include "../utils/avmc/avmplus.h"
#endif

namespace avmplus
{
	namespace ActionBlockConstants
	{
		const unsigned char kindToPushOp[] = {
			0,
			OP_pushstring, // CONSTANT_Utf8=1
			0, 
			OP_pushint,  // CONSTANT_Int=3
			OP_pushuint,  // CONSTANT_UInt=4
			OP_pushnamespace, // CONSTANT_PrivateNs=5
			OP_pushdouble, // CONSTANT_Double=6
			0,
			OP_pushnamespace, // CONSTANT_Namespace=8
			0,
			OP_pushfalse, // CONSTANT_False=10
			OP_pushtrue, // CONSTANT_True=11
			OP_pushnull, // CONSTANT_Null=12
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			OP_pushnamespace, //CONSTANT_PackageNamespace=22
			OP_pushnamespace, //CONSTANT_PackageInternalNs=23
			OP_pushnamespace, //CONSTANT_ProtectedNamespace=24
			OP_pushnamespace, //CONSTANT_ExplicitNamespace=25
			OP_pushnamespace, //CONSTANT_StaticProtectedNs=26
			0,
		};
			

#ifdef AVMPLUS_VERBOSE
		const char * const constantNames[] = {
			"const-0",
			"utf8",//const int CONSTANT_Utf8         = 0x01;
			"const-2",
			"int",//const int CONSTANT_Int = 0x03;
			"uint",//const int CONSTANT_UInt = 0x04;
			"private",//const int CONSTANT_PrivateNS = 0x05;
			"double",//const int CONSTANT_Double       = 0x06;
			"qname",//const int CONSTANT_Qname        = 0x07;
			"namespace",//const int CONSTANT_Namespace    = 0x08;
			"multiname",//const int CONSTANT_Multiname    = 0x09;
			"false",//const inst CONSTANT_False = 0x0A;
			"true",//const int CONSTANT_True         = 0x0B;
			"null",//const int CONSTANT_Null         = 0x0C;
			"@qname",//const int CONSTANT_QnameAttr    = 0x0D;
			"@multiname",//const int CONSTANT_MultinameAttr= 0x0E;
			"rtqname",//const int CONSTANT_RTQname		= 0x0F; // ns::name, var qname, const name
			"@rtqname",//const int CONSTANT_RTQnameA		= 0x10; // @ns::name, var qname, const name
			"rtqnamelate",//const int CONSTANT_RTQnameL		= 0x11; // ns::[], var qname
			"@rtqnamelate",//const int CONSTANT_RTQnameLA	= 0x12; // @ns::[], var qname
			"", //const int CONSTANT_NameL		= 0x13,	// o.[], ns=public implied, rt name
			"", //CONSTANT_NameLA		= 0x14, // o.@[], ns=public implied, rt attr-name
			"namespaceset", //CONSTANT_NamespaceSet = 0x15
            "namespace", //PackageNamespace and Namespace are the same as far as the VM is concerned
			"internal",//const int CONSTANT_PackageInternalNS = 0x17
			"protected",//const int CONSTANT_ProtectedNamespace = 0x18
			"explicit",//const int CONSTANT_ExplicitNamespace = 0x19
			"staticprotected",//const int CONSTANT_StaticProtectedNs = 0x1A,
			"multinamelate", //const int CONSTANT_MultinameL		= 0x1B,	// o.[], ns, rt name
			"@multinamelate", //CONSTANT_MultinameLA		= 0x1C, // o.@[], ns, rt attr-name
			"typename", //CONSTANT_TypeName = 0x1D
		};

		const char * const traitNames[] = {
			"slot",//const int TRAIT_Slot			    = 0x00;
			"method",//const int TRAIT_Method			= 0x01;
			"getter",//const int TRAIT_Getter			= 0x02;
			"setter",//const int TRAIT_Setter			= 0x03;
			"class",//const int TRAIT_Class			    = 0x04;
			"",		//obsolete 'function' traits = 0x05
			"const",//const int TRAIT_Const             = 0x06;
		};
#endif // AVMPLUS_VERBOSE

#if defined AVMPLUS_VERBOSE || defined DEBUGGER
#  define N(x)  , x
#else
#  define N(x)
#endif
#if defined AVMPLUS_WORD_CODE
#  define W(x)  , x
#else
#  define W(x)
#endif
		
		const AbcOpcodeInfo opcodeInfo[] = {
		// For stack movement ("stk") only constant movement is accounted for; variable movement,
		// as for arguments to CALL, CONSTRUCT, APPLYTYPE, et al, and for run-time parts of
		// names, must be handled separately.
		
		// BEGIN
		// opd throw stk
		{   -1,  0,   0    W(0)                   N("OP_0x00") },
		{    0,  0,   0    W(0)                   N("OP_0x01") },
		{    0,  0,   0    W(0)                   N("nop") },
		{    0,  1,  -1    W(WOP_throw)           N("throw") },
		{    1,  1,   0    W(WOP_getsuper)        N("getsuper") },
		{    1,  1,  -2    W(WOP_setsuper)        N("setsuper") },
		{    1,  1,   0    W(WOP_dxns)            N("dxns") },
		{    0,  1,  -1    W(WOP_dxnslate)        N("dxnslate") },
		{    1,  0,   0    W(0)                   N("kill") },
		{    0,  0,   0    W(0)                   N("label") },
		{   -1,  0,   0    W(0)                   N("OP_0x0A") },
		{   -1,  0,   0    W(0)                   N("OP_0x0B") },
		{    1,  1,  -2    W(WOP_ifnlt)           N("ifnlt") },
		{    1,  1,  -2    W(WOP_ifnle)           N("ifnle") },
		{    1,  1,  -2    W(WOP_ifngt)           N("ifngt") },
		{    1,  1,  -2    W(WOP_ifnge)           N("ifnge") },
		{    1,  0,   0    W(WOP_jump)            N("jump") },
		{    1,  0,  -1    W(WOP_iftrue)          N("iftrue") },
		{    1,  0,  -1    W(WOP_iffalse)         N("iffalse") },
		{    1,  1,  -2    W(WOP_ifeq)            N("ifeq") },
		{    1,  1,  -2    W(WOP_ifne)            N("ifne") },
		{    1,  1,  -2    W(WOP_iflt)            N("iflt") },
		{    1,  1,  -2    W(WOP_ifle)            N("ifle") },
		{    1,  1,  -2    W(WOP_ifgt)            N("ifgt") },
		{    1,  1,  -2    W(WOP_ifge)            N("ifge") },
		{    1,  0,  -2    W(WOP_ifstricteq)      N("ifstricteq") },
		{    1,  0,  -2    W(WOP_ifstrictne)      N("ifstrictne") },
		{    2,  0,  -1    W(WOP_lookupswitch)    N("lookupswitch") },
		{    0,  0,  -1    W(WOP_pushwith)        N("pushwith") },
		{    0,  0,   0    W(WOP_popscope)        N("popscope") },
		{    0,  1,  -1    W(WOP_nextname)        N("nextname") },
		{    0,  1,  -1    W(WOP_hasnext)         N("hasnext") },
		{    0,  0,   1    W(WOP_pushnull)        N("pushnull") },
		{    0,  0,   1    W(WOP_pushundefined)   N("pushundefined") },
		{   -1,  0,   0    W(0)                   N("OP_0x22") },
		{    0,  1,  -1    W(WOP_nextvalue)       N("nextvalue") },
		{    1,  0,   1    W(0)                   N("pushbyte") },
		{    1,  0,   1    W(0)                   N("pushshort") },
		{    0,  0,   1    W(WOP_pushtrue)        N("pushtrue") },
		{    0,  0,   1    W(WOP_pushfalse)       N("pushfalse") },
		{    0,  0,   1    W(WOP_pushnan)         N("pushnan") },
		{    0,  0,  -1    W(WOP_pop)             N("pop") },
		{    0,  0,   1    W(WOP_dup)             N("dup") },
		{    0,  0,   0    W(WOP_swap)            N("swap") },
		{    1,  0,   1    W(WOP_pushstring)      N("pushstring") },
		{    1,  0,   1    W(0)                   N("pushint") },
		{    1,  0,   1    W(0)                   N("pushuint") },
		{    1,  0,   1    W(WOP_pushdouble)      N("pushdouble") },
		{    0,  0,  -1    W(WOP_pushscope)       N("pushscope") },
		{    1,  0,   1    W(WOP_pushnamespace)   N("pushnamespace") },
		{    2,  1,   1    W(WOP_hasnext2)        N("hasnext2") },
		{   0,   1,   0    W(WOP_lix8)            N("lix8") }, // NEW internal only
		{   0,   1,   0    W(WOP_lix16)           N("lix16") }, // NEW internal only
		{   0,   1,   0    W(WOP_li8)             N("li8") },
		{   0,   1,   0    W(WOP_li16)            N("li16") },
		{   0,   1,   0    W(WOP_li32)            N("li32") },
		{   0,   1,   0    W(WOP_lf32)            N("lf32") },
		{   0,   1,   0    W(WOP_lf64)            N("lf64") },
		{   0,   1,  -2    W(WOP_si8)             N("si8") },
		{   0,   1,  -2    W(WOP_si16)            N("si16") },
		{   0,   1,  -2    W(WOP_si32)            N("si32") },
		{   0,   1,  -2    W(WOP_sf32)            N("sf32") },
		{   0,   1,  -2    W(WOP_sf64)            N("sf64") },
		{   -1,  0,   0    W(0)                   N("OP_0x3F") },
		{    1,  1,   1    W(WOP_newfunction)     N("newfunction") },
		{    1,  1,  -1    W(WOP_call)            N("call") },
		{    1,  1,   0    W(WOP_construct)       N("construct") },
		{    2,  1,   0    W(WOP_callmethod)      N("callmethod") },
		{    2,  1,   0    W(WOP_callstatic)      N("callstatic") },
		{    2,  1,   0    W(WOP_callsuper)       N("callsuper") },
		{    2,  1,   0    W(WOP_callproperty)    N("callproperty") },
		{    0,  0,   0    W(WOP_returnvoid)      N("returnvoid") },
		{    0,  0,  -1    W(WOP_returnvalue)     N("returnvalue") },
		{    1,  1,  -1    W(WOP_constructsuper)  N("constructsuper") },
		{    2,  1,   0    W(WOP_constructprop)   N("constructprop") },
		{   -1,  1,   0    W(0)                   N("callsuperid") },
		{    2,  1,   0    W(WOP_callproplex)     N("callproplex") },
		{   -1,  1,   0    W(0)                   N("callinterface") },
		{    2,  1,  -1    W(WOP_callsupervoid)   N("callsupervoid") },
		{    2,  1,  -1    W(WOP_callpropvoid)    N("callpropvoid") },
		{    0,  0,   0    W(WOP_sxi1)            N("sxi1") },
		{    0,  0,   0    W(WOP_sxi8)            N("sxi8") },
		{    0,  0,   0    W(WOP_sxi16)           N("sxi16") },
		{    1,  1,   0    W(WOP_applytype)       N("applytype") },
		{   -1,  0,   0    W(0)                   N("OP_0x54") },
		{    1,  1,   1    W(WOP_newobject)       N("newobject") },
		{    1,  1,   1    W(WOP_newarray)        N("newarray") },
		{    0,  1,   1    W(WOP_newactivation)   N("newactivation") },
		{    1,  1,   0    W(WOP_newclass)        N("newclass") },
		{    1,  1,   0    W(WOP_getdescendants)  N("getdescendants") },
		{    1,  1,   1    W(WOP_newcatch)        N("newcatch") },
		{    1,  1,   0    W(WOP_findpropglobalstrict) N("findpropglobalstrict") }, // NEW internal only
		{    1,  1,   0    W(WOP_findpropglobal)  N("findpropglobal") }, // NEW internal only
		{    1,  1,   1    W(WOP_findpropstrict)  N("findpropstrict") },
		{    1,  1,   1    W(WOP_findproperty)    N("findproperty") },
		{    1,  1,   1    W(WOP_finddef)         N("finddef") },
		{    1,  1,   1    W(WOP_getlex)          N("getlex") },
		{    1,  1,  -2    W(WOP_setproperty)     N("setproperty") },
		{    1,  0,   1    W(WOP_getlocal)        N("getlocal") },
		{    1,  0,  -1    W(WOP_setlocal)        N("setlocal") },
		{    0,  0,   1    W(WOP_getglobalscope)  N("getglobalscope") },
		{    1,  0,   1    W(WOP_getscopeobject)  N("getscopeobject") },
		{    1,  1,   0    W(WOP_getproperty)     N("getproperty") },
		{    1,  0,   1    W(WOP_getouterscope)   N("getouterscope") },
		{    1,  1,  -2    W(WOP_initproperty)    N("initproperty") },
		{   -1,  0,   0    W(0)                   N("OP_0x69") },
		{    1,  1,   0    W(WOP_deleteproperty)  N("deleteproperty") },
		{   -1,  0,   0    W(0)                   N("OP_0x6B") },
		{    1,  1,   0    W(WOP_getslot)         N("getslot") },
		{    1,  1,  -2    W(WOP_setslot)         N("setslot") },
		{    1,  0,   1    W(WOP_getglobalslot)   N("getglobalslot") },
		{    1,  0,  -1    W(WOP_setglobalslot)   N("setglobalslot") },
		{    0,  1,   0    W(WOP_convert_s)       N("convert_s") },
		{    0,  1,   0    W(WOP_esc_xelem)       N("esc_xelem") },
		{    0,  1,   0    W(WOP_esc_xattr)       N("esc_xattr") },
		{    0,  1,   0    W(WOP_convert_i)       N("convert_i") },
		{    0,  1,   0    W(WOP_convert_u)       N("convert_u") },
		{    0,  1,   0    W(WOP_convert_d)       N("convert_d") },
		{    0,  1,   0    W(WOP_convert_b)       N("convert_b") },
		{    0,  1,   0    W(WOP_convert_o)       N("convert_o") },
		{    0,  1,   0    W(WOP_checkfilter)     N("checkfilter") },
		{   -1,  0,   0    W(0)                   N("OP_0x79") },
		{   -1,  0,   0    W(0)                   N("OP_0x7A") },
		{   -1,  0,   0    W(0)                   N("OP_0x7B") },
		{   -1,  0,   0    W(0)                   N("OP_0x7C") },
		{   -1,  0,   0    W(0)                   N("OP_0x7D") },
		{   -1,  0,   0    W(0)                   N("OP_0x7E") },
		{   -1,  0,   0    W(0)                   N("OP_0x7F") },
		{    1,  1,   0    W(WOP_coerce)          N("coerce") },
		{    0,  1,   0    W(WOP_convert_b)       N("coerce_b") },   // convert_b is the same operation as coerce_b
		{    0,  1,   0    W(0)                   N("coerce_a") },
		{    0,  1,   0    W(WOP_convert_i)       N("coerce_i") },   // convert_i is the same operation as coerce_i
		{    0,  1,   0    W(WOP_convert_d)       N("coerce_d") },
		{    0,  1,   0    W(WOP_coerce_s)        N("coerce_s") },   // convert_d is the same operation as coerce_d
		{    1,  1,   0    W(WOP_astype)          N("astype") },
		{    0,  1,  -1    W(WOP_astypelate)      N("astypelate") },
		{    0,  1,   0    W(WOP_convert_u)       N("coerce_u") },   // convert_u is the same operation as coerce_u
		{    0,  1,   0    W(WOP_coerce_o)        N("coerce_o") },
		{   -1,  0,   0    W(0)                   N("OP_0x8A") },
		{   -1,  0,   0    W(0)                   N("OP_0x8B") },
		{   -1,  0,   0    W(0)                   N("OP_0x8C") },
		{   -1,  0,   0    W(0)                   N("OP_0x8D") },
		{   -1,  0,   0    W(0)                   N("OP_0x8E") },
		{   -1,  0,   0    W(0)                   N("OP_0x8F") },
		{    0,  1,   0    W(WOP_negate)          N("negate") },
		{    0,  1,   0    W(WOP_increment)       N("increment") },
		{    1,  1,   0    W(WOP_inclocal)        N("inclocal") },
		{    0,  1,   0    W(WOP_decrement)       N("decrement") },
		{    1,  1,   0    W(WOP_declocal)        N("declocal") },
		{    0,  0,   0    W(WOP_typeof)          N("typeof") },
		{    0,  0,   0    W(WOP_not)             N("not") },
		{    0,  1,   0    W(WOP_bitnot)          N("bitnot") },
		{   -1,  0,   0    W(0)                   N("OP_0x98") },
		{   -1,  0,   0    W(0)                   N("OP_0x99") },
		{   -1,  0,   0    W(0)                   N("OP_0x9A") },
		{   -1,  0,   0    W(0)                   N("OP_0x9B") },
		{   -1,  0,   0    W(0)                   N("OP_0x9C") },
		{   -1,  0,   0    W(0)                   N("OP_0x9D") },
		{   -1,  0,   0    W(0)                   N("OP_0x9E") },
		{   -1,  0,   0    W(0)                   N("OP_0x9F") },
		{    0,  1,  -1    W(WOP_add)             N("add") },
		{    0,  1,  -1    W(WOP_subtract)        N("subtract") },
		{    0,  1,  -1    W(WOP_multiply)        N("multiply") },
		{    0,  1,  -1    W(WOP_divide)          N("divide") },
		{    0,  1,  -1    W(WOP_modulo)          N("modulo") },
		{    0,  1,  -1    W(WOP_lshift)          N("lshift") },
		{    0,  1,  -1    W(WOP_rshift)          N("rshift") },
		{    0,  1,  -1    W(WOP_urshift)         N("urshift") },
		{    0,  1,  -1    W(WOP_bitand)          N("bitand") },
		{    0,  1,  -1    W(WOP_bitor)           N("bitor") },
		{    0,  1,  -1    W(WOP_bitxor)          N("bitxor") },
		{    0,  1,  -1    W(WOP_equals)          N("equals") },
		{    0,  1,  -1    W(WOP_strictequals)    N("strictequals") },
		{    0,  1,  -1    W(WOP_lessthan)        N("lessthan") },
		{    0,  1,  -1    W(WOP_lessequals)      N("lessequals") },
		{    0,  1,  -1    W(WOP_greaterthan)     N("greaterthan") },
		{    0,  1,  -1    W(WOP_greaterequals)   N("greaterequals") },
		{    0,  1,  -1    W(WOP_instanceof)      N("instanceof") },
		{    1,  1,   0    W(WOP_istype)          N("istype") },
		{    0,  1,  -1    W(WOP_istypelate)      N("istypelate") },
		{    0,  1,  -1    W(WOP_in)              N("in") },
		{   -1,  0,   0    W(0)                   N("OP_0xB5") },
		{   -1,  0,   0    W(0)                   N("OP_0xB6") },
		{   -1,  0,   0    W(0)                   N("OP_0xB7") },
		{   -1,  0,   0    W(0)                   N("OP_0xB8") },
		{   -1,  0,   0    W(0)                   N("OP_0xB9") },
		{   -1,  0,   0    W(0)                   N("OP_0xBA") },
		{   -1,  0,   0    W(0)                   N("OP_0xBB") },
		{   -1,  0,   0    W(0)                   N("OP_0xBC") },
		{   -1,  0,   0    W(0)                   N("OP_0xBD") },
		{   -1,  0,   0    W(0)                   N("OP_0xBE") },
		{   -1,  0,   0    W(0)                   N("OP_0xBF") },
		{    0,  1,   0    W(WOP_increment_i)     N("increment_i") },
		{    0,  1,   0    W(WOP_decrement_i)     N("decrement_i") },
		{    1,  1,   0    W(WOP_inclocal_i)      N("inclocal_i") },
		{    1,  1,   0    W(WOP_declocal_i)      N("declocal_i") },
		{    0,  1,   0    W(WOP_negate_i)        N("negate_i") },
		{    0,  1,  -1    W(WOP_add_i)           N("add_i") },
		{    0,  1,  -1    W(WOP_subtract_i)      N("subtract_i") },
		{    0,  1,  -1    W(WOP_multiply_i)      N("multiply_i") },
		{   -1,  0,   0    W(0)                   N("OP_0xC8") },
		{   -1,  0,   0    W(0)                   N("OP_0xC9") },
		{   -1,  0,   0    W(0)                   N("OP_0xCA") },
		{   -1,  0,   0    W(0)                   N("OP_0xCB") },
		{   -1,  0,   0    W(0)                   N("OP_0xCC") },
		{   -1,  0,   0    W(0)                   N("OP_0xCD") },
		{   -1,  0,   0    W(0)                   N("OP_0xCE") },
		{   -1,  0,   0    W(0)                   N("OP_0xCF") },
		{    0,  0,   1    W(WOP_getlocal0)       N("getlocal0") },
		{    0,  0,   1    W(WOP_getlocal1)       N("getlocal1") },
		{    0,  0,   1    W(WOP_getlocal2)       N("getlocal2") },
		{    0,  0,   1    W(WOP_getlocal3)       N("getlocal3") },
		{    0,  0,  -1    W(WOP_setlocal0)       N("setlocal0") },
		{    0,  0,  -1    W(WOP_setlocal1)       N("setlocal1") },
		{    0,  0,  -1    W(WOP_setlocal2)       N("setlocal2") },
		{    0,  0,  -1    W(WOP_setlocal3)       N("setlocal3") },
		{   -1,  0,   0    W(0)                   N("OP_0xD8") },
		{   -1,  0,   0    W(0)                   N("OP_0xD9") },
		{   -1,  0,   0    W(0)                   N("OP_0xDA") },
		{   -1,  0,   0    W(0)                   N("OP_0xDB") },
		{   -1,  0,   0    W(0)                   N("OP_0xDC") },
		{   -1,  0,   0    W(0)                   N("OP_0xDD") },
		{   -1,  0,   0    W(0)                   N("OP_0xDE") },
		{   -1,  0,   0    W(0)                   N("OP_0xDF") },
		{   -1,  0,   0    W(0)                   N("OP_0xE0") },
		{   -1,  0,   0    W(0)                   N("OP_0xE1") },
		{   -1,  0,   0    W(0)                   N("OP_0xE2") },
		{   -1,  0,   0    W(0)                   N("OP_0xE3") },
		{   -1,  0,   0    W(0)                   N("OP_0xE4") },
		{   -1,  0,   0    W(0)                   N("OP_0xE5") },
		{   -1,  0,   0    W(0)                   N("OP_0xE6") },
		{   -1,  0,   0    W(0)                   N("OP_0xE7") },
		{   -1,  0,   0    W(0)                   N("OP_0xE8") },
		{   -1,  0,   0    W(0)                   N("OP_0xE9") },
		{   -1,  0,   0    W(0)                   N("OP_0xEA") },
		{   -1,  0,   0    W(0)                   N("OP_0xEB") },
		{   -1,  0,   0    W(0)                   N("OP_0xEC") },
		{   -1,  0,   0    W(0)                   N("OP_0xED") },
		{    2,  0,   0    W(0)                   N("abs_jump") },
#  if defined DEBUGGER || !defined AVMPLUS_WORD_CODE
		{    4,  1,   0    W(WOP_debug)           N("debug") },
		{    1,  1,   0    W(WOP_debugline)       N("debugline") },
		{    1,  1,   0    W(WOP_debugfile)       N("debugfile") },
#else
		// we must process (and ignore) these ABC bytecodes, so that
		// ABC with them embedded does not fail verification in non-debug builds
		{    4,  0,   0    W(0)                   N("OP_0xEF") },
		{    1,  0,   0    W(0)                   N("OP_0xF0") },
		{    1,  0,   0    W(0)                   N("OP_0xF1") },
#endif
		{    1,  0,   0    W(0)                   N("OP_0xF2") },
		{    0,  0,   0    W(0)                   N("timestamp") },
		{   -1,  0,   0    W(0)                   N("OP_0xF4") },
		{   -1,  0,   0    W(0)                   N("OP_0xF5") },
		{   -1,  0,   0    W(0)                   N("OP_0xF6") },
		{   -1,  0,   0    W(0)                   N("OP_0xF7") },
		{   -1,  0,   0    W(0)                   N("OP_0xF8") },
		{   -1,  0,   0    W(0)                   N("OP_0xF9") },
		{   -1,  0,   0    W(0)                   N("OP_0xFA") },
		{   -1,  0,   0    W(0)                   N("OP_0xFB") },
		{   -1,  0,   0    W(0)                   N("OP_0xFC") },
		{   -1,  0,   0    W(0)                   N("OP_0xFD") },
		{   -1,  0,   0    W(0)                   N("OP_0xFE") },
		{   -1,  0,   0    W(0)                   N("OP_0xFF") },
		// END
		};
	}
}
