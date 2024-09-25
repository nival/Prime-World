/* -*- tab-width: 4; indent-tabs-mode: nil -*- */
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

package abcasm;

//
// Please keep this file in sync with utils/abc-constants.as
//

interface AbcConstants {

    // method flags
    int NEED_ARGUMENTS =    0x01;
    int NEED_ACTIVATION =   0x02;
    int NEED_REST =         0x04;
    int HAS_OPTIONAL =      0x08;
    int IGNORE_REST =       0x10;
    int NATIVE =            0x20;
    int HAS_ParamNames =    0x80;

    int CONSTANT_Utf8                = 0x01;
    int CONSTANT_Int                 = 0x03;
    int CONSTANT_UInt                = 0x04;
    int CONSTANT_PrivateNs           = 0x05; // non-shared namespace
    int CONSTANT_Double              = 0x06;
    int CONSTANT_Qname               = 0x07; // o.ns::name, ct ns, ct name
    int CONSTANT_Namespace           = 0x08;
    int CONSTANT_Multiname           = 0x09; // o.name, ct nsset, ct name
    int CONSTANT_False               = 0x0A;
    int CONSTANT_True                = 0x0B;
    int CONSTANT_Null                = 0x0C;
    int CONSTANT_QnameA              = 0x0D; // o.@ns::name, ct ns, ct attr-name
    int CONSTANT_MultinameA          = 0x0E; // o.@name, ct attr-name
    int CONSTANT_RTQname             = 0x0F; // o.ns::name, rt ns, ct name
    int CONSTANT_RTQnameA            = 0x10; // o.@ns::name, rt ns, ct attr-name
    int CONSTANT_RTQnameL            = 0x11; // o.ns::[name], rt ns, rt name
    int CONSTANT_RTQnameLA           = 0x12; // o.@ns::[name], rt ns, rt attr-name
    int CONSTANT_NameL               = 0x13;    // o.[], ns=public implied, rt name
    int CONSTANT_NameLA              = 0x14; // o.@[], ns=public implied, rt attr-name
    int CONSTANT_NamespaceSet        = 0x15;
    int CONSTANT_PackageNs           = 0x16;
    int CONSTANT_PackageInternalNs   = 0x17;
    int CONSTANT_ProtectedNs         = 0x18;
    int CONSTANT_StaticProtectedNs   = 0x19;
    int CONSTANT_StaticProtectedNs2  = 0x1a;
    int CONSTANT_MultinameL          = 0x1B;
    int CONSTANT_MultinameLA         = 0x1C;
    int CONSTANT_TypeName            = 0x1D;

    String[] constantKinds = { "0", "utf8", "2",
        "int", "uint", "private", "double", "qname", "namespace",
        "multiname", "false", "true", "null", "@qname", "@multiname", "rtqname",
        "@rtqname", "[qname]", "@[qname]", "[name]", "@[name]", "nsset"
    };

    int TRAIT_Var        = 0x00;
    int TRAIT_Method     = 0x01;
    int TRAIT_Getter     = 0x02;
    int TRAIT_Setter     = 0x03;
    int TRAIT_Class      = 0x04;
    int TRAIT_Function   = 0x05;
    int TRAIT_Const      = 0x06;

    int TRAIT_FLAG_final    = 0x01;
    int TRAIT_FLAG_override = 0x02;
    int TRAIT_FLAG_metadata = 0x04;

    String[] traitKinds = {
        "var", "function", "function get", "function set", "class", "function", "    final"
    };

    int OP_bkpt = 0x01;
    int OP_nop = 0x02;
    int OP_throw = 0x03;
    int OP_getsuper = 0x04;
    int OP_setsuper = 0x05;
    int OP_dxns = 0x06;
    int OP_dxnslate = 0x07;
    int OP_kill = 0x08;
    int OP_label = 0x09;
    int OP_ifnlt = 0x0C;
    int OP_ifnle = 0x0D;
    int OP_ifngt = 0x0E;
    int OP_ifnge = 0x0F;
    int OP_jump = 0x10;
    int OP_iftrue = 0x11;
    int OP_iffalse = 0x12;
    int OP_ifeq = 0x13;
    int OP_ifne = 0x14;
    int OP_iflt = 0x15;
    int OP_ifle = 0x16;
    int OP_ifgt = 0x17;
    int OP_ifge = 0x18;
    int OP_ifstricteq = 0x19;
    int OP_ifstrictne = 0x1A;
    int OP_lookupswitch = 0x1B;
    int OP_pushwith = 0x1C;
    int OP_popscope = 0x1D;
    int OP_nextname = 0x1E;
    int OP_hasnext = 0x1F;
    int OP_pushnull = 0x20;
    int OP_pushundefined = 0x21;
    int OP_pushconstant = 0x22;
    int OP_nextvalue = 0x23;
    int OP_pushbyte = 0x24;
    int OP_pushshort = 0x25;
    int OP_pushtrue = 0x26;
    int OP_pushfalse = 0x27;
    int OP_pushnan = 0x28;
    int OP_pop = 0x29;
    int OP_dup = 0x2A;
    int OP_swap = 0x2B;
    int OP_pushstring = 0x2C;
    int OP_pushint = 0x2D;
    int OP_pushuint = 0x2E;
    int OP_pushdouble = 0x2F;
    int OP_pushscope = 0x30;
    int OP_pushnamespace = 0x31;
    int OP_hasnext2 = 0x32;
    int OP_li8 = 0x35;
    int OP_li16 = 0x36;
    int OP_li32 = 0x37;
    int OP_lf32 = 0x38;
    int OP_lf64 = 0x39;
    int OP_si8 = 0x3A;
    int OP_si16 = 0x3B;
    int OP_si32 = 0x3C;
    int OP_sf32 = 0x3D;
    int OP_sf64 = 0x3E;
    int OP_newfunction = 0x40;
    int OP_call = 0x41;
    int OP_construct = 0x42;
    int OP_callmethod = 0x43;
    int OP_callstatic = 0x44;
    int OP_callsuper = 0x45;
    int OP_callproperty = 0x46;
    int OP_returnvoid = 0x47;
    int OP_returnvalue = 0x48;
    int OP_constructsuper = 0x49;
    int OP_constructprop = 0x4A;
    int OP_callsuperid = 0x4B;
    int OP_callproplex = 0x4C;
    int OP_callinterface = 0x4D;
    int OP_callsupervoid = 0x4E;
    int OP_callpropvoid = 0x4F;
    int OP_sxi1 = 0x50;
    int OP_sxi8 = 0x51;
    int OP_sxi16 = 0x52;
    int OP_applytype = 0x53;
    int OP_newobject = 0x55;
    int OP_newarray = 0x56;
    int OP_newactivation = 0x57;
    int OP_newclass = 0x58;
    int OP_getdescendants = 0x59;
    int OP_newcatch = 0x5A;
    int OP_findpropstrict = 0x5D;
    int OP_findproperty = 0x5E;
    int OP_finddef = 0x5F;
    int OP_getlex = 0x60;
    int OP_setproperty = 0x61;
    int OP_getlocal = 0x62;
    int OP_setlocal = 0x63;
    int OP_getglobalscope = 0x64;
    int OP_getscopeobject = 0x65;
    int OP_getproperty = 0x66;
    int OP_getouterscope = 0x67;
    int OP_initproperty = 0x68;
    int OP_setpropertylate = 0x69;
    int OP_deleteproperty = 0x6A;
    int OP_deletepropertylate = 0x6B;
    int OP_getslot = 0x6C;
    int OP_setslot = 0x6D;
    int OP_getglobalslot = 0x6E;
    int OP_setglobalslot = 0x6F;
    int OP_convert_s = 0x70;
    int OP_esc_xelem = 0x71;
    int OP_esc_xattr = 0x72;
    int OP_convert_i = 0x73;
    int OP_convert_u = 0x74;
    int OP_convert_d = 0x75;
    int OP_convert_b = 0x76;
    int OP_convert_o = 0x77;
    int OP_checkfilter = 0x78;
    int OP_coerce = 0x80;
    int OP_coerce_b = 0x81;
    int OP_coerce_a = 0x82;
    int OP_coerce_i = 0x83;
    int OP_coerce_d = 0x84;
    int OP_coerce_s = 0x85;
    int OP_astype = 0x86;
    int OP_astypelate = 0x87;
    int OP_coerce_u = 0x88;
    int OP_coerce_o = 0x89;
    int OP_negate = 0x90;
    int OP_increment = 0x91;
    int OP_inclocal = 0x92;
    int OP_decrement = 0x93;
    int OP_declocal = 0x94;
    int OP_typeof = 0x95;
    int OP_not = 0x96;
    int OP_bitnot = 0x97;
    int OP_add_d = 0x9B;
    int OP_add = 0xA0;
    int OP_subtract = 0xA1;
    int OP_multiply = 0xA2;
    int OP_divide = 0xA3;
    int OP_modulo = 0xA4;
    int OP_lshift = 0xA5;
    int OP_rshift = 0xA6;
    int OP_urshift = 0xA7;
    int OP_bitand = 0xA8;
    int OP_bitor = 0xA9;
    int OP_bitxor = 0xAA;
    int OP_equals = 0xAB;
    int OP_strictequals = 0xAC;
    int OP_lessthan = 0xAD;
    int OP_lessequals = 0xAE;
    int OP_greaterthan = 0xAF;
    int OP_greaterequals = 0xB0;
    int OP_instanceof = 0xB1;
    int OP_istype = 0xB2;
    int OP_istypelate = 0xB3;
    int OP_in = 0xB4;
    int OP_increment_i = 0xC0;
    int OP_decrement_i = 0xC1;
    int OP_inclocal_i = 0xC2;
    int OP_declocal_i = 0xC3;
    int OP_negate_i = 0xC4;
    int OP_add_i = 0xC5;
    int OP_subtract_i = 0xC6;
    int OP_multiply_i = 0xC7;
    int OP_getlocal0 = 0xD0;
    int OP_getlocal1 = 0xD1;
    int OP_getlocal2 = 0xD2;
    int OP_getlocal3 = 0xD3;
    int OP_setlocal0 = 0xD4;
    int OP_setlocal1 = 0xD5;
    int OP_setlocal2 = 0xD6;
    int OP_setlocal3 = 0xD7;
    int OP_debug = 0xEF;
    int OP_debugline = 0xF0;
    int OP_debugfile = 0xF1;
    int OP_bkptline = 0xF2;

    String[] opNames = {
        "OP_0x00       ",
        "bkpt          ",
        "nop           ",
        "throw         ",
        "getsuper      ",
        "setsuper      ",
        "dxns          ",
        "dxnslate      ",
        "kill          ",
        "label         ",
        "OP_0x0A       ",
        "OP_0x0B       ",
        "ifnlt         ",
        "ifnle         ",
        "ifngt         ",
        "ifnge         ",
        "jump          ",
        "iftrue        ",
        "iffalse       ",
        "ifeq          ",
        "ifne          ",
        "iflt          ",
        "ifle          ",
        "ifgt          ",
        "ifge          ",
        "ifstricteq    ",
        "ifstrictne    ",
        "lookupswitch  ",
        "pushwith      ",
        "popscope      ",
        "nextname      ",
        "hasnext       ",
        "pushnull      ",
        "pushundefined ",
        "pushconstant  ",
        "nextvalue     ",
        "pushbyte      ",
        "pushshort     ",
        "pushtrue      ",
        "pushfalse     ",
        "pushnan       ",
        "pop           ",
        "dup           ",
        "swap          ",
        "pushstring    ",
        "pushint       ",
        "pushuint      ",
        "pushdouble    ",
        "pushscope     ",
        "pushnamespace ",
        "hasnext2      ",
        "OP_0x33       ", // lix8 (internal)
        "OP_0x34       ", // lix16 (internal)
        "li8           ",
        "li16          ",
        "li32          ",
        "lf32          ",
        "lf64          ",
        "si8           ",
        "si16          ",
        "si32          ",
        "sf32          ",
        "sf64          ",
        "OP_0x3F       ",
        "newfunction   ",
        "call          ",
        "construct     ",
        "callmethod    ",
        "callstatic    ",
        "callsuper     ",
        "callproperty  ",
        "returnvoid    ",
        "returnvalue   ",
        "constructsuper",
        "constructprop ",
        "callsuperid   ",
        "callproplex   ",
        "callinterface ",
        "callsupervoid ",
        "callpropvoid  ",
        "sxi1          ",
        "sxi8          ",
        "sxi16         ",
        "applytype     ",
        "OP_0x54       ",
        "newobject     ",
        "newarray      ",
        "newactivation ",
        "newclass      ",
        "getdescendants",
        "newcatch      ",
        "OP_0x5B       ", // findpropglobalstrict (internal)
        "OP_0x5C       ", // findpropglobal (internal)
        "findpropstrict",
        "findproperty  ",
        "finddef       ",
        "getlex        ",
        "setproperty   ",
        "getlocal      ",
        "setlocal      ",
        "getglobalscope",
        "getscopeobject",
        "getproperty   ",
        "getouterscope ",
        "initproperty  ",
        "OP_0x69       ",
        "deleteproperty",
        "OP_0x6B       ",
        "getslot       ",
        "setslot       ",
        "getglobalslot ",
        "setglobalslot ",
        "convert_s     ",
        "esc_xelem     ",
        "esc_xattr     ",
        "convert_i     ",
        "convert_u     ",
        "convert_d     ",
        "convert_b     ",
        "convert_o     ",
        "checkfilter   ",
        "OP_0x79       ",
        "OP_0x7A       ",
        "OP_0x7B       ",
        "OP_0x7C       ",
        "OP_0x7D       ",
        "OP_0x7E       ",
        "OP_0x7F       ",
        "coerce        ",
        "coerce_b      ",
        "coerce_a      ",
        "coerce_i      ",
        "coerce_d      ",
        "coerce_s      ",
        "astype        ",
        "astypelate    ",
        "coerce_u      ",
        "coerce_o      ",
        "OP_0x8A       ",
        "OP_0x8B       ",
        "OP_0x8C       ",
        "OP_0x8D       ",
        "OP_0x8E       ",
        "OP_0x8F       ",
        "negate        ",
        "increment     ",
        "inclocal      ",
        "decrement     ",
        "declocal      ",
        "typeof        ",
        "not           ",
        "bitnot        ",
        "OP_0x98       ",
        "OP_0x99       ",
        "OP_0x9A       ",
        "add_d         ",
        "OP_0x9C       ",
        "OP_0x9D       ",
        "OP_0x9E       ",
        "OP_0x9F       ",
        "add           ",
        "subtract      ",
        "multiply      ",
        "divide        ",
        "modulo        ",
        "lshift        ",
        "rshift        ",
        "urshift       ",
        "bitand        ",
        "bitor         ",
        "bitxor        ",
        "equals        ",
        "strictequals  ",
        "lessthan      ",
        "lessequals    ",
        "greaterthan   ",
        "greaterequals ",
        "instanceof    ",
        "istype        ",
        "istypelate    ",
        "in            ",
        "OP_0xB5       ",
        "OP_0xB6       ",
        "OP_0xB7       ",
        "OP_0xB8       ",
        "OP_0xB9       ",
        "OP_0xBA       ",
        "OP_0xBB       ",
        "OP_0xBC       ",
        "OP_0xBD       ",
        "OP_0xBE       ",
        "OP_0xBF       ",
        "increment_i   ",
        "decrement_i   ",
        "inclocal_i    ",
        "declocal_i    ",
        "negate_i      ",
        "add_i         ",
        "subtract_i    ",
        "multiply_i    ",
        "OP_0xC8       ",
        "OP_0xC9       ",
        "OP_0xCA       ",
        "OP_0xCB       ",
        "OP_0xCC       ",
        "OP_0xCD       ",
        "OP_0xCE       ",
        "OP_0xCF       ",
        "getlocal0     ",
        "getlocal1     ",
        "getlocal2     ",
        "getlocal3     ",
        "setlocal0     ",
        "setlocal1     ",
        "setlocal2     ",
        "setlocal3     ",
        "OP_0xD8       ",
        "OP_0xD9       ",
        "OP_0xDA       ",
        "OP_0xDB       ",
        "OP_0xDC       ",
        "OP_0xDD       ",
        "OP_0xDE       ",
        "OP_0xDF       ",
        "OP_0xE0       ",
        "OP_0xE1       ",
        "OP_0xE2       ",
        "OP_0xE3       ",
        "OP_0xE4       ",
        "OP_0xE5       ",
        "OP_0xE6       ",
        "OP_0xE7       ",
        "OP_0xE8       ",
        "OP_0xE9       ",
        "OP_0xEA       ",
        "OP_0xEB       ",
        "OP_0xEC       ",
        "OP_0xED       ",
        "OP_0xEE       ",
        "debug         ",
        "debugline     ",
        "debugfile     ",
        "bkptline      ",
        "timestamp     ",
        "OP_0xF4       ",
        "OP_0xF5       ",
        "OP_0xF6       ",
        "OP_0xF7       ",
        "OP_0xF8       ",
        "OP_0xF9       ",
        "OP_0xFA       ",
        "OP_0xFB       ",
        "OP_0xFC       ",
        "OP_0xFD       ",
        "OP_0xFE       ",
        "OP_0xFF       "
    };

    int ATTR_final           = 0x01; // 1=final, 0=virtual
    int ATTR_override        = 0x02; // 1=override, 0=new
    int ATTR_metadata        = 0x04; // 1=has metadata, 0=no metadata
    int ATTR_public          = 0x08; // 1=add public namespace
    
    int CLASS_FLAG_sealed    = 0x01;
    int CLASS_FLAG_final     = 0x02;
    int CLASS_FLAG_interface = 0x04;

    int METHOD_Arguments     = 0x1;
    int METHOD_Activation    = 0x2;
    int METHOD_Needrest      = 0x4;
    int METHOD_HasOptional   = 0x8;
    int METHOD_IgnoreRest    = 0x10;
    int METHOD_Native        = 0x20;
    int METHOD_Setsdxns      = 0x40;
    int METHOD_HasParamNames = 0x80;
}
