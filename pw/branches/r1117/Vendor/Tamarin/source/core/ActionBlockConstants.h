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

#ifndef __avmplus_ActionBlockConstants__
#define __avmplus_ActionBlockConstants__


namespace avmplus
{
	/**
	 * Constants for all of the opcodes in the AVM+ instruction set.
	 */
	namespace ActionBlockConstants
	{
		/** @name cpool tags */
		/*@{*/
		enum CPoolKind {
			CONSTANT_unused_0x00		= 0x00,
			CONSTANT_Utf8               = 0x01,
			CONSTANT_Int	            = 0x03,
			CONSTANT_UInt               = 0x04,
			CONSTANT_PrivateNs	        = 0x05, // non-shared namespace
			CONSTANT_Double             = 0x06,
			CONSTANT_Qname              = 0x07, // o.ns::name, ct ns, ct name
			CONSTANT_Namespace	        = 0x08,
			CONSTANT_Multiname          = 0x09, // o.name, ct nsset, ct name
			CONSTANT_False              = 0x0A,
			CONSTANT_True               = 0x0B,
			CONSTANT_Null               = 0x0C,
			CONSTANT_QnameA             = 0x0D, // o.@ns::name, ct ns, ct attr-name
			CONSTANT_MultinameA         = 0x0E, // o.@name, ct attr-name
			CONSTANT_RTQname	        = 0x0F, // o.ns::name, rt ns, ct name
			CONSTANT_RTQnameA	        = 0x10, // o.@ns::name, rt ns, ct attr-name
			CONSTANT_RTQnameL	        = 0x11, // o.ns::[name], rt ns, rt name
			CONSTANT_RTQnameLA	        = 0x12, // o.@ns::[name], rt ns, rt attr-name
			CONSTANT_NamespaceSet       = 0x15,
            CONSTANT_PackageNamespace   = 0x16,
            CONSTANT_PackageInternalNs  = 0x17,
            CONSTANT_ProtectedNamespace = 0x18,
            CONSTANT_ExplicitNamespace  = 0x19,
			CONSTANT_StaticProtectedNs  = 0x1A,
			CONSTANT_MultinameL         = 0x1B,
			CONSTANT_MultinameLA        = 0x1C,
			CONSTANT_TypeName	        = 0x1D
		};
		/*@}*/

		/** @name traits kinds */
		/*@{*/

		enum TraitKind {
			TRAIT_Slot			= 0x00,
			TRAIT_Method		= 0x01,
			TRAIT_Getter		= 0x02,
			TRAIT_Setter		= 0x03,
			TRAIT_Class			= 0x04,
			TRAIT_Const			= 0x06,
			TRAIT_COUNT			= TRAIT_Const+1,
			TRAIT_mask			= 15
		};
		/*@}*/

		/** @name attributes */
		/*@{*/
		const int ATTR_final			= 0x10; // 1=final, 0=virtual
		const int ATTR_override         = 0x20; // 1=override, 0=new
        const int ATTR_metadata         = 0x40; // 1=has metadata, 0=no metadata
		/*@}*/

		/** @name opcodes */
		enum AbcOpcode 
		{
			OP_nop = 0x02,
			OP_throw = 0x03,
			OP_getsuper = 0x04,
			OP_setsuper = 0x05,
			OP_dxns = 0x06,
			OP_dxnslate = 0x07,
			OP_kill = 0x08,
			OP_label = 0x09,
			OP_ifnlt = 0x0C,
			OP_ifnle = 0x0D,
			OP_ifngt = 0x0E,
			OP_ifnge = 0x0F,
			OP_jump = 0x10,
			OP_iftrue = 0x11,
			OP_iffalse = 0x12,
			OP_ifeq = 0x13,
			OP_ifne = 0x14,
			OP_iflt = 0x15,
			OP_ifle = 0x16,
			OP_ifgt = 0x17,
			OP_ifge = 0x18,
			OP_ifstricteq = 0x19,
			OP_ifstrictne = 0x1A,
			OP_lookupswitch = 0x1B,
			OP_pushwith = 0x1C,
			OP_popscope = 0x1D,
			OP_nextname = 0x1E,
			OP_hasnext = 0x1F,
			OP_pushnull = 0x20,
			OP_pushundefined = 0x21,
			OP_nextvalue = 0x23,
			OP_pushbyte = 0x24,
			OP_pushshort = 0x25,
			OP_pushtrue = 0x26,
			OP_pushfalse = 0x27,
			OP_pushnan = 0x28,
			OP_pop = 0x29,
			OP_dup = 0x2A,
			OP_swap = 0x2B,
			OP_pushstring = 0x2C,
			OP_pushint = 0x2D,
			OP_pushuint = 0x2E,
			OP_pushdouble = 0x2F,
			OP_pushscope = 0x30,
			OP_pushnamespace = 0x31,
			OP_hasnext2 = 0x32,
			OP_lix8 = 0x33, // NEW internal only
			OP_lix16 = 0x34, // NEW internal only
			OP_li8 = 0x35,
			OP_li16 = 0x36,
			OP_li32 = 0x37,
			OP_lf32 = 0x38,
			OP_lf64 = 0x39,
			OP_si8 = 0x3A,
			OP_si16 = 0x3B,
			OP_si32 = 0x3C,
			OP_sf32 = 0x3D,
			OP_sf64 = 0x3E,
			OP_newfunction = 0x40,
			OP_call = 0x41,
			OP_construct = 0x42,
			OP_callmethod = 0x43,
			OP_callstatic = 0x44,
			OP_callsuper = 0x45,
			OP_callproperty = 0x46,
			OP_returnvoid = 0x47,
			OP_returnvalue = 0x48,
			OP_constructsuper = 0x49,
			OP_constructprop = 0x4A,
			OP_callsuperid = 0x4B,
			OP_callproplex = 0x4C,
			OP_callinterface = 0x4D,
			OP_callsupervoid = 0x4E,
			OP_callpropvoid = 0x4F,
			OP_sxi1 = 0x50,
			OP_sxi8 = 0x51,
			OP_sxi16 = 0x52,
			OP_applytype = 0x53,
			OP_newobject = 0x55,
			OP_newarray = 0x56,
			OP_newactivation = 0x57,
			OP_newclass = 0x58,
			OP_getdescendants = 0x59,
			OP_newcatch = 0x5A,
			OP_findpropglobalstrict = 0x5B, // NEW internal only
			OP_findpropglobal = 0x5C, // NEW internal only 
			OP_findpropstrict = 0x5D,
			OP_findproperty = 0x5E,
			OP_finddef = 0x5F,
			OP_getlex = 0x60,
			OP_setproperty = 0x61,
			OP_getlocal = 0x62,
			OP_setlocal = 0x63,
			OP_getglobalscope = 0x64,
			OP_getscopeobject = 0x65,
			OP_getproperty = 0x66,
			OP_getouterscope = 0x67,
			OP_initproperty = 0x68,
			OP_deleteproperty = 0x6A,
			OP_getslot = 0x6C,
			OP_setslot = 0x6D,
			OP_getglobalslot = 0x6E,
			OP_setglobalslot = 0x6F,
			OP_convert_s = 0x70,
			OP_esc_xelem = 0x71,
			OP_esc_xattr = 0x72,
			OP_convert_i = 0x73,
			OP_convert_u = 0x74,
			OP_convert_d = 0x75,
			OP_convert_b = 0x76,
			OP_convert_o = 0x77,
			OP_checkfilter = 0x78,
			OP_coerce = 0x80,
			OP_coerce_b = 0x81,
			OP_coerce_a = 0x82,
			OP_coerce_i = 0x83,
			OP_coerce_d = 0x84,
			OP_coerce_s = 0x85,
			OP_astype = 0x86,
			OP_astypelate = 0x87,
			OP_coerce_u = 0x88,
			OP_coerce_o = 0x89,
			OP_negate = 0x90,
			OP_increment = 0x91,
			OP_inclocal = 0x92,
			OP_decrement = 0x93,
			OP_declocal = 0x94,
			OP_typeof = 0x95,
			OP_not = 0x96,
			OP_bitnot = 0x97,
			OP_add = 0xA0,
			OP_subtract = 0xA1,
			OP_multiply = 0xA2,
			OP_divide = 0xA3,
			OP_modulo = 0xA4,
			OP_lshift = 0xA5,
			OP_rshift = 0xA6,
			OP_urshift = 0xA7,
			OP_bitand = 0xA8,
			OP_bitor = 0xA9,
			OP_bitxor = 0xAA,
			OP_equals = 0xAB,
			OP_strictequals = 0xAC,
			OP_lessthan = 0xAD,
			OP_lessequals = 0xAE,
			OP_greaterthan = 0xAF,
			OP_greaterequals = 0xB0,
			OP_instanceof = 0xB1,
			OP_istype = 0xB2,
			OP_istypelate = 0xB3,
			OP_in = 0xB4,
			OP_increment_i = 0xC0,
			OP_decrement_i = 0xC1,
			OP_inclocal_i = 0xC2,
			OP_declocal_i = 0xC3,
			OP_negate_i = 0xC4,
			OP_add_i = 0xC5,
			OP_subtract_i = 0xC6,
			OP_multiply_i = 0xC7,
			OP_getlocal0 = 0xD0,
			OP_getlocal1 = 0xD1,
			OP_getlocal2 = 0xD2,
			OP_getlocal3 = 0xD3,
			OP_setlocal0 = 0xD4,
			OP_setlocal1 = 0xD5,
			OP_setlocal2 = 0xD6,
			OP_setlocal3 = 0xD7,
			OP_abs_jump = 0xEE,
			OP_debug = 0xEF,
			OP_debugline = 0xF0,
			OP_debugfile = 0xF1,
			OP_timestamp = 0xF3
		};
		
		struct AbcOpcodeInfo
		{
			int8_t operandCount;    // uses -1 for "invalid", we can avoid that if necessary
			int8_t canThrow;		// always 0 or 1
			int8_t stack;           // stack movement not taking into account run-time names or function arguments
#if defined AVMPLUS_WORD_CODE
			uint16_t wordCode;		// a map used during translation
#endif
#if defined AVMPLUS_VERBOSE || defined DEBUGGER
			const char* name;		// instruction name or OP_0xNN for undefined instructions
#endif
		};

		extern const AbcOpcodeInfo opcodeInfo[];
		
		extern const unsigned char kindToPushOp[];
		
#ifdef AVMPLUS_VERBOSE
		/** @name debugger string names */
		/*@{*/
		extern const char * const constantNames[];
		extern const char * const traitNames[];
		/*@}*/
#endif

	}
}

#endif /* __avmplus_ActionBlockConstants__ */
