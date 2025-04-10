#!/usr/bin/env python
# ***** BEGIN LICENSE BLOCK *****
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Original Code is [Open Source Virtual Machine].
#
# The Initial Developer of the Original Code is
# Adobe System Incorporated.
# Portions created by the Initial Developer are Copyright (C) 2007
# the Initial Developer. All Rights Reserved.
#
# Contributor(s):
#   Adobe AS3 Team
#
# Alternatively, the contents of this file may be used under the terms of
# either the GNU General Public License Version 2 or later (the "GPL"), or
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ***** END LICENSE BLOCK *****

import optparse, struct, os, sys
from optparse import OptionParser
from struct import *
from os import path
from math import floor
from sys import stderr

import sys

haveSecrets = False
try:
	import nativegen_secret as secrets
	haveSecrets = True
except ImportError:
	pass

parser = OptionParser(usage="usage: %prog [--directthunks] [importfile [, importfile]...] file...")
parser.add_option("-n", "--nativemapname", help="no longer supported")
parser.add_option("-u", "--directthunks", action="store_true", default=False, help="generate a unique (direct) thunk for every native method (don't recycle thunks with similar signatures)")
parser.add_option("-v", "--thunkvprof", action="store_true", default=False)
parser.add_option("-e", "--externmethodandclassetables", action="store_true", default=False, help="generate extern decls for method and class tables")
parser.add_option("--native-id-namespace", dest="nativeIDNS", default="avmplus::NativeID", help="Specifies the C++ namespace in which all generated should be in.")
parser.add_option("--root-implementation-namespace", dest="rootImplNS", default="avmplus", help="Specifies the C++ namespace in under which all implementation classes can be found.")
opts, args = parser.parse_args()

if not args:
	parser.print_help()
	exit(2)

if opts.nativemapname:
	raise Error("--nativemapname is no longer supported")

NEED_ARGUMENTS		= 0x01
NEED_ACTIVATION		= 0x02
NEED_REST			= 0x04
HAS_OPTIONAL		= 0x08
IGNORE_REST			= 0x10
NATIVE				= 0x20
HAS_ParamNames		= 0x80

CONSTANT_Utf8               = 0x01
CONSTANT_Int	            = 0x03
CONSTANT_UInt               = 0x04
CONSTANT_PrivateNs	        = 0x05
CONSTANT_Double             = 0x06
CONSTANT_Qname              = 0x07
CONSTANT_Namespace	        = 0x08
CONSTANT_Multiname          = 0x09
CONSTANT_False              = 0x0A
CONSTANT_True               = 0x0B
CONSTANT_Null               = 0x0C
CONSTANT_QnameA             = 0x0D
CONSTANT_MultinameA         = 0x0E
CONSTANT_RTQname	        = 0x0F
CONSTANT_RTQnameA	        = 0x10
CONSTANT_RTQnameL	        = 0x11
CONSTANT_RTQnameLA	        = 0x12
CONSTANT_NameL				= 0x13
CONSTANT_NameLA				= 0x14
CONSTANT_NamespaceSet       = 0x15
CONSTANT_PackageNs			= 0x16
CONSTANT_PackageInternalNs  = 0x17
CONSTANT_ProtectedNs		= 0x18
CONSTANT_ExplicitNamespace  = 0x19
CONSTANT_StaticProtectedNs  = 0x1A
CONSTANT_MultinameL         = 0x1B
CONSTANT_MultinameLA        = 0x1C
CONSTANT_TypeName	        = 0x1D

TRAIT_Slot			= 0x00
TRAIT_Method		= 0x01
TRAIT_Getter		= 0x02
TRAIT_Setter		= 0x03
TRAIT_Class			= 0x04
TRAIT_Const			= 0x06
TRAIT_mask			= 15

ATTR_final			= 0x10
ATTR_override       = 0x20
ATTR_metadata       = 0x40

CTYPE_VOID			= 0
CTYPE_ATOM			= 1
CTYPE_BOOLEAN		= 2
CTYPE_INT			= 3
CTYPE_UINT			= 4
CTYPE_DOUBLE		= 5
CTYPE_STRING		= 6
CTYPE_NAMESPACE		= 7
CTYPE_OBJECT		= 8

MPL_HEADER = "/* ***** BEGIN LICENSE BLOCK *****\n" \
            " * Version: MPL 1.1/GPL 2.0/LGPL 2.1\n" \
            " *\n" \
            " * The contents of this file are subject to the Mozilla Public License Version\n" \
            " * 1.1 (the \"License\"); you may not use this file except in compliance with\n" \
            " * the License. You may obtain a copy of the License at\n" \
            " * http://www.mozilla.org/MPL/\n" \
            " *\n" \
            " * Software distributed under the License is distributed on an \"AS IS\" basis,\n" \
            " * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License\n" \
            " * for the specific language governing rights and limitations under the\n" \
            " * License.\n" \
            " *\n" \
            " * The Original Code is [Open Source Virtual Machine].\n" \
            " *\n" \
            " * The Initial Developer of the Original Code is\n" \
            " * Adobe System Incorporated.\n" \
            " * Portions created by the Initial Developer are Copyright (C) 2008\n" \
            " * the Initial Developer. All Rights Reserved.\n" \
            " *\n" \
            " * Contributor(s):\n" \
            " *   Adobe AS3 Team\n" \
            " *\n" \
            " * Alternatively, the contents of this file may be used under the terms of\n" \
            " * either the GNU General Public License Version 2 or later (the \"GPL\"), or\n" \
            " * the GNU Lesser General Public License Version 2.1 or later (the \"LGPL\"),\n" \
            " * in which case the provisions of the GPL or the LGPL are applicable instead\n" \
            " * of those above. If you wish to allow use of your version of this file only\n" \
            " * under the terms of either the GPL or the LGPL, and not to allow others to\n" \
            " * use your version of this file under the terms of the MPL, indicate your\n" \
            " * decision by deleting the provisions above and replace them with the notice\n" \
            " * and other provisions required by the GPL or the LGPL. If you do not delete\n" \
            " * the provisions above, a recipient may use your version of this file under\n" \
            " * the terms of any one of the MPL, the GPL or the LGPL.\n" \
            " *\n" \
            " * ***** END LICENSE BLOCK ***** */" 

# Python 2.5 and earlier didn't reliably handle float("nan") and friends uniformly
# across all platforms. This is a workaround that appears to be more reliable.
# if/when we require Python 2.6 or later we can use a less hack-prone approach
kPosInf = 1e300000
kNegInf = -1e300000
kNaN = kPosInf / kPosInf

def is_nan(val):
	strValLower = str(val).lower()
	return strValLower == "nan"

def is_pos_inf(val):
	# [-]1.#INF on Windows in Python 2.5.2!
	strValLower = str(val).lower()
	return strValLower.endswith("inf") and not strValLower.startswith("-")

def is_neg_inf(val):
	# [-]1.#INF on Windows in Python 2.5.2!
	strValLower = str(val).lower()
	return strValLower.endswith("inf") and strValLower.startswith("-")

class Error(Exception):
	nm = ""
	def __init__(self, n):
		self.nm = n
	def __str__(self):
		return self.nm

TMAP = {
	CTYPE_OBJECT:		("o", "AvmObject"),
	CTYPE_ATOM:			("a", "AvmBox"),
	CTYPE_VOID:			("v", "void"),
	CTYPE_BOOLEAN:		("b", "AvmBool32"),
	CTYPE_INT:			("i", "int32_t"),
	CTYPE_UINT:			("u", "uint32_t"),
	CTYPE_DOUBLE:		("d", "double"),
	CTYPE_STRING:		("s", "AvmString"),
	CTYPE_NAMESPACE:	("n", "AvmNamespace")
};

def uint(i):
	return int(i) & 0xffffffff

def sigchar_from_enum(ct, allowObject):
	if ct == CTYPE_OBJECT and not allowObject:
		ct = CTYPE_ATOM
	return TMAP[ct][0]

def sigchar_from_traits(t, allowObject):
	return sigchar_from_enum(t.ctype, allowObject)

def ctype_from_enum(ct, allowObject):
	if ct == CTYPE_OBJECT and not allowObject:
		ct = CTYPE_ATOM
	return TMAP[ct][1]

def ctype_from_traits(t, allowObject):
	return ctype_from_enum(t.ctype, allowObject)

def to_cname(nm):
	nm = str(nm)
	nm = nm.replace("+", "_");
	nm = nm.replace("-", "_");
	nm = nm.replace("?", "_");
	nm = nm.replace("!", "_");
	nm = nm.replace("<", "_");
	nm = nm.replace(">", "_");
	nm = nm.replace("=", "_");
	nm = nm.replace("(", "_");
	nm = nm.replace(")", "_");
	nm = nm.replace("\"", "_");
	nm = nm.replace("'", "_");
	nm = nm.replace("*", "_");
	nm = nm.replace(" ", "_");
	nm = nm.replace(".", "_");
	nm = nm.replace("$", "_");
	nm = nm.replace("::", "_");
	nm = nm.replace(":", "_");
	nm = nm.replace("/", "_");
	return nm

def ns_prefix(ns, iscls):
	if not ns.isPublic() and not ns.isInternal():
		if ns.isPrivate() and not iscls:
			return "private_";
		if ns.isProtected():
			return "protected_";
		if ns.srcname != None:
			return to_cname(str(ns.srcname)) + "_"
	p = to_cname(ns.uri);
	if len(p) > 0:
		p += "_"
	return p

class Namespace:
	uri = ""
	kind = 0
	srcname = None
	def __init__(self, uri, kind):
		self.uri = uri
		self.kind = kind
	def __str__(self):
		return self.uri
	def isPublic(self):
		return self.kind in [CONSTANT_Namespace, CONSTANT_PackageNs] and self.uri == ""
	def isInternal(self):
		return self.kind in [CONSTANT_PackageInternalNs]
	def isPrivate(self):
		return self.kind in [CONSTANT_PrivateNs]
	def isProtected(self):
		return self.kind in [CONSTANT_ProtectedNs, CONSTANT_StaticProtectedNs]

class QName:
	ns = None
	name = ""
	def __init__(self, ns, name):
		self.ns = ns
		self.name = name
	def __str__(self):
		if str(self.ns) == "":
			return self.name
		if self.ns == None:
			return "*::" + self.name
		return str(self.ns) + "::" + self.name

class Multiname:
	nsset = None
	name = ""
	def __init__(self, nsset, name):
		self.nsset = nsset
		self.name = name
	def __str__(self):
		nsStrings = map(lambda ns: u'"' + ns.decode("utf8") + u'"', self.nsset)
		stringForNSSet = u'[' + u', '.join(nsStrings) + u']'
		return stringForNSSet + u'::' + unicode(self.name.decode("utf8"))

def stripVersion(ns):
	# version markers are 3 bytes beginning with 0xE0 or greater
	if len(ns.uri) < 3:
	    return ns
	if ns.uri[len(ns.uri)-3] > chr(0xE0):
	    ns.uri = ns.uri[0:len(ns.uri)-3]
	return ns

def isVersionedNamespace(ns):
	# version markers are 3 bytes beginning with 0xE0 or greater
	if len(ns.uri) < 3:
	    return False
	if ns.uri[len(ns.uri)-3] > chr(0xE0):
	    ns.uri = ns.uri[0:len(ns.uri)-3]
	    return True
	return False

def isVersionedName(name):
	if isinstance(name, QName):
            return isVersionedNamespace(name.ns)
	for ns in name.nsset:
            if isVersionedNamespace(ns):
                return True
        return False

class TypeName:
	name = ""
	types = None
	def __init__(self, name, types):
		self.name = name
		self.types = types
	def __str__(self):
		# @todo horrible special-casing, improve someday
		s = str(self.name)
		t = str(self.types[0])
		if t == "int":
			s += "$int"
		elif t == "uint":
			s += "$uint"
		elif t == "Number":
			s += "$double"
		else:
			s += "$object"
		return s

class MetaData:
	name = ""
	attrs = {}
	def __init__(self, name):
		self.name = name
		self.attrs = {}

class MemberInfo:
	id = -1
	kind = -1
	name = ""
	metadata = None

class MethodInfo(MemberInfo):
	flags = 0
	debugName = ""
	paramTypes = None
	paramNames = None
	optional_count = 0
	optionalValues = None
	returnType = None
	local_count = 0
	max_scope = 0
	max_stack = 0
	code_length = 0
	code = None
	activation = None
	native_id_name = None
	native_method_name = None
	final = False
	override = False
	receiver = None
	unbox_this = -1 # -1 == undetermined, 0 = no, 1 = yes

	def isNative(self):
		return (self.flags & NATIVE) != 0

	def needRest(self):
		return (self.flags & NEED_REST) != 0

	def hasOptional(self):
		return (self.flags & HAS_OPTIONAL) != 0

	def assign_names(self, traits, prefix):
		self.receiver = traits
		
		if not self.isNative():
			return
		
		if self == traits.init:
			raise Error("ctors cannot be native")

		assert(isinstance(self.name, QName))
		self.native_id_name = prefix + ns_prefix(self.name.ns, False) + self.name.name
		self.native_method_name = self.name.name
		
		if self.kind == TRAIT_Getter:
			self.native_id_name += "_get"
			self.native_method_name = "get_" + self.native_method_name
		elif self.kind == TRAIT_Setter:
			self.native_id_name += "_set"		
			self.native_method_name = "set_" + self.native_method_name

		if self.name.ns.srcname != None:
			self.native_method_name = str(self.name.ns.srcname) + "_" + self.native_method_name

		# if we are an override, prepend the classname to the C method name.
		# (native method implementations must not be virtual, and some compilers
		# will be unhappy if a subclass overrides a method with the same name and signature
		# without it being virtual.) Note that we really only need to do this if the ancestor
		# implementation is native, rather than pure AS3, but we currently do it regardless.
		if self.override:
			self.native_method_name = traits.name.name + "_" + self.native_method_name

		self.native_method_name = to_cname(self.native_method_name)
					
class SlotInfo(MemberInfo):
	type = ""
	value = ""
	fileOffset = -1

class NativeInfo:
	class_name = None
	instance_name = None
	gen_method_map = False
	method_map_name = None
	constSetters = False
	
	def set_class(self, name):
		if self.class_name != None:
			raise Error("native(cls) may not be specified multiple times for the same class: %s %s" % (self.class_name, name))
		self.class_name = name

	def set_instance(self, name):
		if self.instance_name != None:
			raise Error("native(instance) may not be specified multiple times for the same class: %s %s" % (self.instance_name, name))
		self.instance_name = name
		
	def validate(self):
		if self.gen_method_map and self.class_name == None and self.instance_name == None:
			raise Error("cannot specify native(methods) without native(cls)")
		if self.class_name != None or self.instance_name != None:
			# if nothing specified, use ClassClosure/ScriptObject.
			if self.class_name == None:
				self.class_name = "ClassClosure"
			if self.instance_name == None:
				self.instance_name = "ScriptObject"
			

BMAP = {
	"Object": CTYPE_ATOM, # yes, items of exactly class "Object" are stored as Atom; subclasses are stored as pointer-to-Object
	"null": CTYPE_ATOM,
	"*": CTYPE_ATOM,
	"void": CTYPE_VOID,
	"int": CTYPE_INT,
	"uint": CTYPE_UINT,
	"Number": CTYPE_DOUBLE,
	"Boolean": CTYPE_BOOLEAN,
	"String": CTYPE_STRING,
	"Namespace": CTYPE_NAMESPACE
};

class Traits:
	name = ""
	qname = None
	init = None
	itraits = None
	base = None
	flags = 0
	protectedNs = 0
	is_interface = False
	interfaces = None
	names = None
	slots = None
	tmethods = None
	members = None
	class_id = -1
	ctype = CTYPE_OBJECT
	metadata = None
	ni = None
	niname = None
	nextSlotId = 0
	def __init__(self, name):
		self.names = {}
		self.slots = []
		self.tmethods = []
		self.name = name
		if BMAP.has_key(str(name)):
			self.ctype = BMAP[str(name)]
	def __str__(self):
		return str(self.name)

NULL = Traits("*")
UNDEFINED = Traits("void")

class ByteArray:
	data = None
	pos = 0
	def __init__(self, data):
		self.data = data
		self.pos = 0
		
	def readU8(self):
		r = unpack_from("B", self.data, self.pos)[0]
		self.pos += 1
		assert(r >= 0 and r <= 255)
		return r

	def readU16(self):
		r = unpack_from("<h", self.data, self.pos)[0]
		self.pos += 2
		assert(r >= 0 and r <= 65535)
		return r

	def readDouble(self):
		r = unpack_from("<d", self.data, self.pos)[0]
		self.pos += 8
		return r

	def readBytes(self, lenbytes):
		r = self.data[self.pos:self.pos+lenbytes]
		self.pos += lenbytes
		return r

	def readUTF8(self):
		lenbytes = self.readU30()
		return self.readBytes(lenbytes)

	def readU30(self):
		result = self.readU8()
		if not result & 0x00000080:
			return result
		result = (result & 0x0000007f) | (self.readU8() << 7)
		if not result & 0x00004000:
			return result
		result = (result & 0x00003fff) | (self.readU8() << 14)
		if not result & 0x00200000:
			return result
		result = (result & 0x001fffff) | (self.readU8() << 21)
		if not result & 0x10000000:
			return result
		result = (result & 0x0fffffff) | (self.readU8() << 28)
		return result

class Abc:
	data = None
	major = 0
	minor = 0
	ints = None
	uints = None
	doubles = None
	strings = None
	namespaces = None
	nssets = None
	names = None
	defaults = None
	methods = None
	instances = None
	metadata = None
	classes = None
	scripts = None
	scriptName = ""
	publicNs = Namespace("", CONSTANT_Namespace)
	anyNs = Namespace("*", CONSTANT_Namespace)

	magic = 0
	
	qnameToName = {}
	nameToQName = {}
		
	def __init__(self, data, scriptName):
		self.scriptName = scriptName
		self.data = ByteArray(data)

		if self.data.readU16() != 16 or self.data.readU16() != 46:
			raise Error("Bad Abc Version")

		self.parseCpool()
		
		self.defaults = [ (None, 0) ] * 32
		self.defaults[CONSTANT_Utf8] = (self.strings, CTYPE_STRING)
		self.defaults[CONSTANT_Int] = (self.ints, CTYPE_INT)
		self.defaults[CONSTANT_UInt] = (self.uints, CTYPE_UINT)
		self.defaults[CONSTANT_Double] = (self.doubles, CTYPE_DOUBLE)
		self.defaults[CONSTANT_False] = ({ CONSTANT_False: False }, CTYPE_BOOLEAN)
		self.defaults[CONSTANT_True] = ({ CONSTANT_True: True }, CTYPE_BOOLEAN)
		self.defaults[CONSTANT_Namespace] = (self.namespaces, CTYPE_NAMESPACE)
		self.defaults[CONSTANT_PrivateNs] = (self.namespaces, CTYPE_NAMESPACE)
		self.defaults[CONSTANT_PackageNs] = (self.namespaces, CTYPE_NAMESPACE)
		self.defaults[CONSTANT_PackageInternalNs] = (self.namespaces, CTYPE_NAMESPACE)
		self.defaults[CONSTANT_ProtectedNs] = (self.namespaces, CTYPE_NAMESPACE)
		self.defaults[CONSTANT_StaticProtectedNs] = (self.namespaces, CTYPE_NAMESPACE)
		self.defaults[CONSTANT_ExplicitNamespace] = (self.namespaces, CTYPE_NAMESPACE)
		self.defaults[CONSTANT_Null] = ({ CONSTANT_Null: None }, CTYPE_ATOM)	
		
		self.parseMethodInfos()
		self.parseMetadataInfos()
		self.parseInstanceInfos()
		self.parseClassInfos()
		self.parseScriptInfos()
		self.parseMethodBodies()

		for i in range(0, len(self.classes)):
			c = self.classes[i]
			assert(isinstance(c.name, QName))
			prefix = ns_prefix(c.name.ns, True) + to_cname(c.name.name)
			c.class_id = i
			c.ni = self.find_class_nativeinfo(c)
			c.niname = c.ni.class_name
			self.assign_names(c, prefix)
			if c.itraits:
				c.itraits.ni = c.ni
				c.itraits.niname = c.ni.instance_name
				self.assign_names(c.itraits, prefix)
		
		for i in range(0, len(self.scripts)):
			script = self.scripts[i]
			if script != None:
				for j in range(0, len(script.tmethods)):
					m = script.tmethods[j]
					if m.metadata != None:
						for md in m.metadata:
							if md.name == "native":
								if md.attrs.has_key("script"):
									raise Error("native(script) is no longer supported; please use a native(\"function-name\") instead: " + str(m.name))
								if len(md.attrs) != 1 or not md.attrs.has_key(""):
									raise Error("native(\"function-name\") is the only form supported here" + str(m.name))
								if not m.isNative():
									raise Error("native(\"function-name\") can only be used on native functions" + str(m.name))
								m.receiver = None
								m.native_method_name = md.attrs[""]     # override 
								m.native_id_name = "native_script_function_" + ns_prefix(m.name.ns, False) + m.name.name
								#m.native_id_name = "native_script_function_" + to_cname(m.native_method_name)
								m.gen_method_map = True


	def assign_names(self, traits, prefix):
		if traits.init != None:
			traits.init.assign_names(traits, prefix)
		for j in range(0, len(traits.tmethods)):
			traits.tmethods[j].assign_names(traits, prefix)

	def default_ctype_and_value(self,d):
		kind, index = d
		deftable = self.defaults[kind]
		if deftable[0] != None:
			val = str(deftable[0][index])
			ct = deftable[1]
		else:
			assert(kind == 0 and index == 0)
			val = "kAvmThunkUndefined"
			ct = CTYPE_ATOM # yes, not void
		rawval = val
		if ct == CTYPE_DOUBLE:
			# Python apparently doesn't have isNaN, isInf
			if is_nan(val):
				val = "kAvmThunkNaN"
			elif is_neg_inf(val):
				val = "kAvmThunkNegInfinity"
			elif is_pos_inf(val):
				val = "kAvmThunkInfinity"
			elif float(val) >= -2147483648.0 and float(val) <= 2147483647.0 and float(val) == floor(float(val)):
				ct = CTYPE_INT
				val = "%.0f" % float(val)
			elif float(val) >= 0.0 and float(val) <= 4294967295.0 and float(val) == floor(float(val)):
				ct = CTYPE_UINT
				val = "%.0fU" % float(val)
		elif ct == CTYPE_STRING:
			for i in range(0, len(self.strings)):
				if (self.strings[i] == str(val)):
					val = "AvmThunkConstant_AvmString("+str(i)+")/* \""+self.strings[i]+"\" */";
					break
		elif ct == CTYPE_BOOLEAN:
			assert(str(val) == "False" or str(val) == "True")
			if str(val) == "False":
				val = "false"
			else:
				val = "true"
		if str(val) == "None":
			val = "kAvmThunkNull"
		return ct,val,rawval
	
	def parseCpool(self):
		
		n = self.data.readU30()
		self.ints = [0] * max(1,n)
		for i in range(1, n):
			ii = self.data.readU30()
			if float(ii) > 2147483647.0:
				ii = int(ii - 4294967296.0)
			assert(int(ii) >= -2147483648 and int(ii) <= 2147483647)
			self.ints[i] = int(ii)
			
		n = self.data.readU30()
		self.uints = [0] * max(1,n)
		for i in range(1, n):
			self.uints[i] = uint(self.data.readU30())
			
		n = self.data.readU30()
		self.doubles = [ kNaN ] * max(1,n)
		for i in range(1, n):
			self.doubles[i] = self.data.readDouble()

		n = self.data.readU30()
		self.strings = [""] * max(1,n)
		for i in range(1, n):
			self.strings[i] = self.data.readUTF8()

		n = self.data.readU30()
		self.namespaces = [self.anyNs] * max(1,n)
		for i in range(1, n):
			nskind = self.data.readU8()
			if nskind in [CONSTANT_Namespace, 
							CONSTANT_PackageNs, 
							CONSTANT_PackageInternalNs,
							CONSTANT_ProtectedNs,
							CONSTANT_ExplicitNamespace,
							CONSTANT_StaticProtectedNs]:
				self.namespaces[i] = Namespace(self.strings[self.data.readU30()], nskind)
			elif nskind in [CONSTANT_PrivateNs]:
				self.data.readU30() # skip
				self.namespaces[i] = Namespace("private", CONSTANT_PrivateNs)

		n = self.data.readU30()
		self.nssets = [ None ] * max(1,n)
		for i in range(1, n):
			count = self.data.readU30()
			self.nssets[i] = []
			for j in range(0, count):
				self.nssets[i].append(self.namespaces[self.data.readU30()])

		n = self.data.readU30()
		self.names = [ None ] * max(1,n)
		for i in range(1, n):
			namekind = self.data.readU8()
			if namekind in [CONSTANT_Qname, CONSTANT_QnameA]:
				self.names[i] = QName(self.namespaces[self.data.readU30()], self.strings[self.data.readU30()])

			elif namekind in [CONSTANT_RTQname, CONSTANT_RTQnameA]:
				self.names[i] = QName(self.anyNs, self.strings[self.data.readU30()])

			elif namekind in [CONSTANT_RTQnameL, CONSTANT_RTQnameLA]:
				self.names[i] = None

			elif namekind in [CONSTANT_NameL, CONSTANT_NameLA]:
				self.names[i] = QName(Namespace(""), None)

			elif namekind in [CONSTANT_Multiname, CONSTANT_MultinameA]:
				name = self.strings[self.data.readU30()]
				nsset = self.nssets[self.data.readU30()]
				self.names[i] = Multiname(nsset, name)

			elif namekind in [CONSTANT_MultinameL, CONSTANT_MultinameLA]:
				nsset = self.nssets[self.data.readU30()]
				self.names[i] = Multiname(nsset, None)

			elif namekind in [CONSTANT_TypeName]:
				name = self.names[self.data.readU30()];
				count = self.data.readU30();
				types = []
				for j in range(0, count):
					types.append(self.names[self.data.readU30()]);
				self.names[i] = TypeName(name, types);
			else:
				raise Error("Bad Kind")

	def parseMethodInfos(self):
		self.names[0] = QName(self.publicNs,"*")
		method_count = self.data.readU30()
		self.methods = [ None ] * method_count
		for i in range(0, method_count):
			m = MethodInfo()
			self.methods[i] = m
			param_count = self.data.readU30()
			m.returnType = self.names[self.data.readU30()]
			m.paramTypes = [ None ] * param_count
			m.paramNames = [ "" ] * param_count
			m.optional_count = 0
			for j in range(0, param_count):
				m.paramTypes[j] = self.names[self.data.readU30()]
			m.debugName = self.strings[self.data.readU30()]
			m.flags = self.data.readU8()
			if m.hasOptional():
				m.optional_count = self.data.readU30();
				m.optionalValues = [ (-1, -1) ] * param_count
				for k in range(param_count-m.optional_count, param_count):
					index = self.data.readU30()
					kind = self.data.readU8()
					m.optionalValues[k] = (kind, index)
			if (m.flags & HAS_ParamNames) != 0:
				for j in range(0, param_count):
					m.paramNames[j] = self.strings[self.data.readU30()]

	def parseMetadataInfos(self):
		count = self.data.readU30()
		self.metadata = [ None ] * count
		for i in range (0, count):
			mname = self.strings[self.data.readU30()]
			m = MetaData(mname)
			self.metadata[i] = m
			values_count = self.data.readU30()
			names = [ None ] * values_count
			for q in range(0, values_count):
				names[q] = self.strings[self.data.readU30()]
			for q in range(0, values_count):
				m.attrs[names[q]] = self.strings[self.data.readU30()] 

	def parseInstanceInfos(self):
		count = self.data.readU30()
		self.instances = [ None ] * count
		instancesDict = {}
		for i in range (0, count):
			tname = self.names[self.data.readU30()]
			t = Traits(tname)
			self.instances[i] = t
			instancesDict[id(tname)] = t
			t.base = self.names[self.data.readU30()]
			t.flags = self.data.readU8()
			if (t.flags & 4) != 0:
				t.is_interface = True
			if (t.flags & 8) != 0:
				t.protectedNs = self.namespaces[self.data.readU30()]
			interface_count = self.data.readU30()
			t.interfaces = [None] * interface_count
			for j in range(0, interface_count):
				t.interfaces[j] = self.names[self.data.readU30()]
			methid = self.data.readU30()
			t.init = self.methods[methid]
			t.init.name = t.name
			t.init.kind = TRAIT_Method
			t.init.id = methid
			self.parseTraits(t, instancesDict.get(id(t.base), None))
	
	@staticmethod
	def __qname(name):
		if isinstance(name, QName):
			return name
		if len(name.nsset) == 0:
			return QName(Namespace("", CONSTANT_Namespace), name.name)
		return QName(stripVersion(name.nsset[0]), name.name)
	
	def qname(self, name):
		if (not self.nameToQName.has_key(id(name))):
			try:
				result = self.__qname(name)
			except:
				print dir(name)
				raise
			self.qnameToName[id(result)] = name
			self.nameToQName[id(name)] = result
			return result
		return self.nameToQName[id(name)]
	
	def parseTraits(self, t, baseTraits=None):
		lastBaseTraitsSlotId = 0 if baseTraits is None else baseTraits.nextSlotId
		namecount = self.data.readU30()
		t.members = [ None ] * namecount
		for i in range(0, namecount):
			name_index = self.data.readU30()
			name = self.names[name_index]
			name = self.qname(name)
			bindingOffset = self.data.pos
			tag = self.data.readU8()
			kind = tag & 0xf
			member = None
			if kind in [TRAIT_Slot, TRAIT_Const, TRAIT_Class]:
				member = SlotInfo()
				member.fileOffset = bindingOffset
				memberId = self.data.readU30()
				member.id = (memberId - 1) if memberId != 0 else (len(t.slots) + lastBaseTraitsSlotId)
				memberIndex = member.id - lastBaseTraitsSlotId
				while len(t.slots) <= memberIndex:
					t.slots.append(None)
				t.slots[member.id - lastBaseTraitsSlotId] = member
				t.nextSlotId = max(t.nextSlotId, member.id + 1)
				if kind in [TRAIT_Slot, TRAIT_Const]:
					member.type = self.names[self.data.readU30()]
					index = self.data.readU30()
					if index:
						deftable = self.defaults[self.data.readU8()]
						member.value = deftable[0][index]
						if deftable[1] == CTYPE_NAMESPACE:
							assert(isinstance(member.value, Namespace))
							member.value.srcname = name.name
				else:
					member.value = self.classes[self.data.readU30()]
					member.value.qname = name
			elif kind in [TRAIT_Method, TRAIT_Getter, TRAIT_Setter]:
				self.data.readU30()	# disp_id, ignored
				methid = self.data.readU30()
				member = self.methods[methid]
				t.tmethods.append(member)
				member.id = methid
				member.final = (tag & ATTR_final) != 0
				member.override = (tag & ATTR_override) != 0
			member.kind = kind
			member.name = name
			t.members[i] = member
			t.names[str(name)] = member
			
			if (tag & ATTR_metadata) != 0:
				mdCount = self.data.readU30()
				member.metadata = [ None ] * mdCount
				for j in range(0, mdCount):
					member.metadata[j] = self.metadata[self.data.readU30()]
				# stash class metadata in the ctraits and itraits too, makes it much easier later
				if kind == TRAIT_Class:
					member.value.metadata = member.metadata
					member.value.itraits.metadata = member.metadata

	def find_nativeinfo(self, m, ni):
		if m != None:
			for md in m:
				if md.name == "native":
					if md.attrs.has_key("script"):
						raise Error("native scripts are no longer supported; please use a native class instead and wrap with AS3 code as necessary.")
					if md.attrs.has_key("cls"):
						ni.set_class(md.attrs["cls"])
					if md.attrs.has_key("instance"):
						ni.set_instance(md.attrs["instance"])
					if md.attrs.has_key("methods"):
						v = md.attrs["methods"]
						ni.gen_method_map = True
						if v != "auto":
							ni.method_map_name = v
					if md.attrs.has_key("constsetters"):
						v = md.attrs.get("constsetters")
						if (v == "true"):
							ni.constSetters = True
						elif (v != "false"):
							raise Error(u'native metadata specified illegal value, "%s" for constsetters field.	 Value must be "true" or "false".' % unicode(v))
					if (ni.class_name == None) and (ni.instance_name == None):
						raise Error("native metadata must specify (cls,instance)")

	def find_class_nativeinfo(self, t):
		ni = NativeInfo()
		self.find_nativeinfo(t.metadata, ni)
		if ni.instance_name != None and t.itraits.is_interface:
			raise Error("interfaces may not specify native(instance)")
		ni.validate()
		return ni
		
	def parseClassInfos(self):
		count = len(self.instances)
		self.classes = [ None ] * count
		for i in range(0, count):
			itraits = self.instances[i]
			tname = QName(itraits.name.ns, (str(itraits.name.name) + "$"))
			t = Traits(tname)
			self.classes[i] = t
			t.init = self.methods[self.data.readU30()]
			t.base = "Class"
			t.itraits = itraits
			t.init.name = str(t.itraits.name) + "$cinit"
			t.init.kind = TRAIT_Method
			self.parseTraits(t)

	def parseScriptInfos(self):
		count = self.data.readU30()
		self.scripts = [ None ] * count
		for i in range(0, count):
			tname = self.scriptName + "_script_" + str(i)
			t = Traits(tname)
			self.scripts[i] = t
			t.init = self.methods[self.data.readU30()]
			t.base = self.names[0]
			t.itraits = None
			t.init.name = t.name + "$init"
			t.init.kind = TRAIT_Method	    
			self.parseTraits(t)

	def parseMethodBodies(self):
		count = self.data.readU30()
		for i in range(0, count):
			m = self.methods[self.data.readU30()]
			m.max_stack = self.data.readU30()
			m.local_count = self.data.readU30()
			initScopeDepth = self.data.readU30()
			maxScopeDepth = self.data.readU30()
			m.max_scope = maxScopeDepth - initScopeDepth
			code_length = self.data.readU30()
			m.code = self.data.readBytes(code_length)
			ex_count = self.data.readU30()
			for j in range(0, ex_count):
				frm = self.data.readU30()
				to = self.data.readU30()
				target = self.data.readU30()
				type = self.names[self.data.readU30()]
				name = self.names[self.data.readU30()];
			m.activation = Traits(None)
			self.parseTraits(m.activation)


class IndentingPrintWriter:
	f = None
	indent = 0
	do_indent = True

	def __init__(self, file):
		self.f = file

	def dent(self):
		if self.do_indent:
			for i in range(0, self.indent):
				self.f.write("    ")
			self.do_indent = False

	def prnt(self, s):
		self.dent();
		self.f.write(s)

	def println(self, s):
		self.dent();
		self.f.write(s)
		self.f.write("\n")
		self.do_indent = True


def outputBasicSlotDecl(output, slotDict):
	output.println(u'%(type)s m_%(name)s;' % slotDict)
	
def outputWBRCSlotDecl(output, slotDict):
	output.println(u'DRCWB(%(type)s) m_%(name)s;' % slotDict)

def outputWBAtomSlotDecl(output, slotDict):
	output.println(u'ATOM_WB m_%(name)s;' % slotDict)

CTYPE_TO_SLOT_DECL = {
	ctype_from_enum(CTYPE_OBJECT, True) : outputWBRCSlotDecl,
	ctype_from_enum(CTYPE_ATOM, False) : outputWBAtomSlotDecl,
	ctype_from_enum(CTYPE_VOID, True) : lambda output, slotDict: None,
	ctype_from_enum(CTYPE_BOOLEAN, True) : outputBasicSlotDecl,
	ctype_from_enum(CTYPE_INT, True) : outputBasicSlotDecl,
	ctype_from_enum(CTYPE_UINT, True) : outputBasicSlotDecl,
	ctype_from_enum(CTYPE_DOUBLE, True) : outputBasicSlotDecl,
	ctype_from_enum(CTYPE_STRING, True) : outputWBRCSlotDecl,
	ctype_from_enum(CTYPE_NAMESPACE, True) : outputWBRCSlotDecl
}

def outputBasicGetMethodDecl(output, slotDict):
	output.println(u'REALLY_INLINE %(type)s get_%(name)s() const { return m_%(name)s; }' % slotDict)

def outputWBRCGetMethodDecl(output, slotDict):
	output.println(u'REALLY_INLINE %(type)s get_%(name)s() const { return m_%(name)s; }' % slotDict)

def outputWBAtomGetMethodDecl(output, slotDict):
	output.println(u'REALLY_INLINE %(type)s get_%(name)s() const { return m_%(name)s; }' % slotDict)

CTYPE_TO_GET_METHOD_DECL = {
	ctype_from_enum(CTYPE_OBJECT, True) : outputWBRCGetMethodDecl,
	ctype_from_enum(CTYPE_ATOM, False) : outputWBAtomGetMethodDecl,
	ctype_from_enum(CTYPE_VOID, True) : lambda output, slotDict: None,
	ctype_from_enum(CTYPE_BOOLEAN, True) : outputBasicGetMethodDecl,
	ctype_from_enum(CTYPE_INT, True) : outputBasicGetMethodDecl,
	ctype_from_enum(CTYPE_UINT, True) : outputBasicGetMethodDecl,
	ctype_from_enum(CTYPE_DOUBLE, True) : outputBasicGetMethodDecl,
	ctype_from_enum(CTYPE_STRING, True) : outputWBRCGetMethodDecl,
	ctype_from_enum(CTYPE_NAMESPACE, True) : outputWBRCGetMethodDecl
}

def outputBasicSetMethodDecl(output, slotDict):
	output.println(u'void set_%(name)s(%(type)s newVal);' % slotDict)

def outputWBRCSetMethodDecl(output, slotDict):
	output.println(u'void set_%(name)s(%(native)s* obj, %(type)s newVal);' % slotDict)

def outputWBAtomSetMethodDecl(output, slotDict):
	output.println(u'void set_%(name)s(%(native)s* obj, %(type)s newVal);' % slotDict)

CTYPE_TO_SET_METHOD_DECL = {
	ctype_from_enum(CTYPE_OBJECT, True) : outputWBRCSetMethodDecl,
	ctype_from_enum(CTYPE_ATOM, False) : outputWBAtomSetMethodDecl,
	ctype_from_enum(CTYPE_VOID, True) : lambda output, slotDict: None,
	ctype_from_enum(CTYPE_BOOLEAN, True) : outputBasicSetMethodDecl,
	ctype_from_enum(CTYPE_INT, True) : outputBasicSetMethodDecl,
	ctype_from_enum(CTYPE_UINT, True) : outputBasicSetMethodDecl,
	ctype_from_enum(CTYPE_DOUBLE, True) : outputBasicSetMethodDecl,
	ctype_from_enum(CTYPE_STRING, True) : outputWBRCSetMethodDecl,
	ctype_from_enum(CTYPE_NAMESPACE, True) : outputWBRCSetMethodDecl
}

def outputBasicSetMethodBody(output, slotDict):
	output.println(u'REALLY_INLINE void %(struct)s::set_%(name)s(%(type)s newVal) { m_%(name)s = newVal; }' % slotDict)

def outputWBRCSetMethodBody(output, slotDict):
	output.println(u'REALLY_INLINE void %(struct)s::set_%(name)s(%(native)s* obj, %(type)s newVal)' % slotDict)
	output.println(u'{')
	output.indent += 1
	output.println(u'm_%(name)s.set(((ScriptObject*)obj)->gc(), obj, newVal);' % slotDict)
	output.indent -= 1
	output.println('}')

def outputWBAtomSetMethodBody(output, slotDict):
	output.println(u'REALLY_INLINE void %(struct)s::set_%(name)s(%(native)s* obj, %(type)s newVal)' % slotDict)
	output.println(u'{')
	output.indent += 1
	output.println(u'm_%(name)s.set(((ScriptObject*)obj)->gc(), obj, newVal);' % slotDict)
	output.indent -= 1
	output.println('}')

CTYPE_TO_SET_METHOD_BODY = {
	ctype_from_enum(CTYPE_OBJECT, True) : outputWBRCSetMethodBody,
	ctype_from_enum(CTYPE_ATOM, False) : outputWBAtomSetMethodBody,
	ctype_from_enum(CTYPE_VOID, True) : lambda output, slotDict: None,
	ctype_from_enum(CTYPE_BOOLEAN, True) : outputBasicSetMethodBody,
	ctype_from_enum(CTYPE_INT, True) : outputBasicSetMethodBody,
	ctype_from_enum(CTYPE_UINT, True) : outputBasicSetMethodBody,
	ctype_from_enum(CTYPE_DOUBLE, True) : outputBasicSetMethodBody,
	ctype_from_enum(CTYPE_STRING, True) : outputWBRCSetMethodBody,
	ctype_from_enum(CTYPE_NAMESPACE, True) : outputWBRCSetMethodBody
}

def outputBasicSetMethodMacroThunk(output, slotDict):
	output.println(u'REALLY_INLINE void set_%(name)s(%(type)s newVal) { %(instance)s.set_%(name)s(newVal); } \\' % slotDict)

def outputWBRCSetMethodMacroThunk(output, slotDict):
	output.println(u'REALLY_INLINE void set_%(name)s(%(type)s newVal) { %(instance)s.set_%(name)s(this, newVal); } \\' % slotDict)

def outputWBAtomSetMethodMacroThunk(output, slotDict):
	output.println(u'REALLY_INLINE void set_%(name)s(%(type)s newVal) { %(instance)s.set_%(name)s(this, newVal); } \\' % slotDict)

CTYPE_TO_SET_METHOD_MACRO_THUNK = {
	ctype_from_enum(CTYPE_OBJECT, True) : outputWBRCSetMethodMacroThunk,
	ctype_from_enum(CTYPE_ATOM, False) : outputWBAtomSetMethodMacroThunk,
	ctype_from_enum(CTYPE_VOID, True) : lambda output, slotDict: None,
	ctype_from_enum(CTYPE_BOOLEAN, True) : outputBasicSetMethodMacroThunk,
	ctype_from_enum(CTYPE_INT, True) : outputBasicSetMethodMacroThunk,
	ctype_from_enum(CTYPE_UINT, True) : outputBasicSetMethodMacroThunk,
	ctype_from_enum(CTYPE_DOUBLE, True) : outputBasicSetMethodMacroThunk,
	ctype_from_enum(CTYPE_STRING, True) : outputWBRCSetMethodMacroThunk,
	ctype_from_enum(CTYPE_NAMESPACE, True) : outputWBRCSetMethodMacroThunk
}

NON_POINTER_4_BYTE_SLOT_BUCKET = 0
POINTER_SLOT_BUCKET = 1
NON_POINTER_8_BYTE_SLOT_BUCKET = 2

CTYPE_TO_SLOT_SORT_BUCKET = {
	# following types are 4 bytes
	ctype_from_enum(CTYPE_INT, True) : NON_POINTER_4_BYTE_SLOT_BUCKET,
	ctype_from_enum(CTYPE_UINT, True) : NON_POINTER_4_BYTE_SLOT_BUCKET,
	ctype_from_enum(CTYPE_BOOLEAN, True) : NON_POINTER_4_BYTE_SLOT_BUCKET,
	# following types are pointer size ( either 4 or 8 bytes )
	ctype_from_enum(CTYPE_OBJECT, True) : POINTER_SLOT_BUCKET,
	ctype_from_enum(CTYPE_ATOM, False) : POINTER_SLOT_BUCKET,
	ctype_from_enum(CTYPE_STRING, True) : POINTER_SLOT_BUCKET,
	ctype_from_enum(CTYPE_NAMESPACE, True) : POINTER_SLOT_BUCKET,
	# doubles are 8 bytes
	ctype_from_enum(CTYPE_DOUBLE, True) : NON_POINTER_8_BYTE_SLOT_BUCKET,
	# slots should never be of type void
	ctype_from_enum(CTYPE_VOID, True) : -1
}

CTYPE_TO_NEED_FORWARD_DECL = {
	ctype_from_enum(CTYPE_INT, True) : False,
	ctype_from_enum(CTYPE_UINT, True) : False,
	ctype_from_enum(CTYPE_BOOLEAN, True) : False,
	ctype_from_enum(CTYPE_OBJECT, True) : True,
	ctype_from_enum(CTYPE_ATOM, False) : False,
	ctype_from_enum(CTYPE_STRING, True) : True,
	ctype_from_enum(CTYPE_NAMESPACE, True) : True,
	ctype_from_enum(CTYPE_DOUBLE, True) : False,
	ctype_from_enum(CTYPE_VOID, True) : False
}

GLUECLASSES_WITHOUT_SLOTS = frozenset((
	'bool',
	'double',
	'int32_t',
	'Namespace',
	'String',
	'uint32_t'))
	

class AbcThunkGen:
	abc = None
	abcs = []
	out_h = None
	out_c = None
	all_thunks = []
	lookup_traits = None

	def addAbc(self, a):
		self.abcs.append(a)
		self.lookup_traits = None

	def class_native_name(self, c):
		return ns_prefix(c.qname.ns, True) + to_cname(c.qname.name)

	def class_id_name(self, c):
		return "abcclass_" + self.class_native_name(c)

	@staticmethod
	def __parseCPPNamespaceStr(nsStr):
		return nsStr.split(u'::')
	
	@staticmethod
	def __parseCPPClassName(className):
		prependRootNS = (len(opts.rootImplNS) > 0)
		if (className.startswith('::')):
			prependRootNS = False
		fullyQualifiedName = (opts.rootImplNS + '::' + className) if prependRootNS else className
		fullyQualifiedNameComponents = fullyQualifiedName.split('::')
		if (len(fullyQualifiedNameComponents) < 2):
			fullyQualifiedNameComponents = (u'', fullyQualifiedNameComponents)
		return ('::'.join(filter(lambda ns: len(ns) > 0, fullyQualifiedNameComponents[:-1])), fullyQualifiedNameComponents[-1])

	def emit(self, abc, name, out_h, out_c):
		self.abc = abc;
		self.out_h = out_h;
		self.out_c = out_c;
		self.all_thunks = []
		self.lookup_traits = None

		for i in range(0, len(abc.scripts)):
			script = abc.scripts[i]
			if script != None:
				self.processTraits(script)

		out_h.println(MPL_HEADER);
		out_c.println(MPL_HEADER);

		out_h.println('')
		out_h.println("/* machine generated file -- do not edit */");
		out_h.println('')
		out_c.println('')
		out_c.println("/* machine generated file -- do not edit */");
		out_c.println('')

		out_h.println("#define AVMTHUNK_VERSION 5");
		out_h.println('')
		
		self.forwardDeclareGlueClasses(out_h)
		
		nativeIDNamespaces = self.__parseCPPNamespaceStr(opts.nativeIDNS)
		#turn list of namespaces [foo, bar, baz] into "namespace foo { namespace bar { namespace baz{"
		out_h.println(' '.join(map(lambda ns: u'namespace %s {' % ns, nativeIDNamespaces)))
		out_h.println('')
		out_c.println(' '.join(map(lambda ns: u'namespace %s {' % ns, nativeIDNamespaces)))
		out_c.println('')
		
		out_h.println("extern const uint32_t "+name+"_abc_class_count;")
		out_h.println("extern const uint32_t "+name+"_abc_script_count;")
		out_h.println("extern const uint32_t "+name+"_abc_method_count;")
		out_h.println("extern const uint32_t "+name+"_abc_length;")
		out_h.println("extern const uint8_t "+name+"_abc_data[];");

		out_c.println("const uint32_t "+name+"_abc_class_count = "+str(len(abc.classes))+";");
		out_c.println("const uint32_t "+name+"_abc_script_count = "+str(len(abc.scripts))+";");
		out_c.println("const uint32_t "+name+"_abc_method_count = "+str(len(abc.methods))+";");
		out_c.println("const uint32_t "+name+"_abc_length = "+str(len(abc.data.data))+";");

		out_h.println("AVMTHUNK_DECLARE_NATIVE_INITIALIZER(%s)" % (name));
		
		out_h.println('')
		out_h.println("/* classes */");
		for i in range(0, len(abc.classes)):
			c = abc.classes[i]
			self.out_h.println("const uint32_t " + self.class_id_name(c) + " = " + str(c.class_id) + ";");

		out_h.println('')
		out_h.println("/* methods */");
		for i in range(0, len(abc.methods)):
			m = abc.methods[i]
			if m.native_id_name != None:
				assert(m.id == i)
				if m.isNative():
					out_h.println("const uint32_t "+m.native_id_name+" = "+str(m.id)+";");
				else:
					# not sure if we want to expose method id's for non-native methods; emit as comments for now
					out_h.println("/* const uint32_t "+m.native_id_name+" = "+str(m.id)+"; */");
		out_h.println('')

		unique_thunk_sigs = {}
		for receiver,m in self.all_thunks:
			sig = self.thunkSig(receiver, m)
			if not unique_thunk_sigs.has_key(sig):
				unique_thunk_sigs[sig] = {}
			unique_thunk_sigs[sig][m.native_id_name] = (receiver, m)
		out_c.println("");
		out_c.println("/* thunks (%d unique signatures, %d total) */" % (len(unique_thunk_sigs.keys()), len(self.all_thunks)));
		if opts.thunkvprof:
			out_c.println("#define DOPROF")
			out_c.println('#include "../vprof/vprof.h"')
		if opts.directthunks:
			out_c.println("")
			out_c.println("#ifdef AVMPLUS_INDIRECT_NATIVE_THUNKS")
			out_c.println("  #error nativegen.py: --directthunks requires AVMFEATURE_INDIRECT_NATIVE_THUNKS=0")
			out_c.println("#endif")
			out_c.println("")
			for receiver,m in self.all_thunks:
				thunkname = m.native_id_name;
				self.emitThunkProto(thunkname, receiver, m);
				self.emitThunkBody(thunkname, receiver, m, True);
		else:
			out_c.println("")
			out_c.println("#ifndef AVMPLUS_INDIRECT_NATIVE_THUNKS")
			out_c.println("  #error nativegen.py: --directthunks requires AVMFEATURE_INDIRECT_NATIVE_THUNKS=1")
			out_c.println("#endif")
			out_c.println("")
			for sig in unique_thunk_sigs:
				users = unique_thunk_sigs[sig]
				receiver = None;
				m = None;
				out_c.println('')
				for native_name in users:
					out_c.println("// "+native_name);
					receiver = users[native_name][0];
					m = users[native_name][1];
				thunkname = name+"_"+sig;
				self.emitThunkProto(thunkname, receiver, m);
				for native_name in users:
					# use #define here (rather than constants) to avoid the linker including them and thus preventing dead-stripping
					# (sad but true, happens in some environments)
					out_h.println("#define "+native_name+"_thunk  "+thunkname+"_thunk")
				out_h.println("")
				# if there's only one client of the thunk, emit a direct call even if direct thunks aren't requested
				do_direct = (len(users) == 1)
				self.emitThunkBody(thunkname, receiver, m, do_direct)

		out_c.println("")
		self.printStructAsserts(out_c, abc)
		out_c.println("")
		
		for i in range(0, len(abc.classes)):
			c = abc.classes[i]
			if c.ni.gen_method_map:
				formatDict = { u'nativeClass' : c.ni.class_name, u'nativeClassBaseName' : self.__baseNINameForNIName(c.ni.class_name) }
				out_c.println("AVMTHUNK_NATIVE_CLASS_GLUE(%(nativeClassBaseName)s, %(nativeClass)s, SlotOffsetsAndAsserts::do%(nativeClassBaseName)sAsserts)" % formatDict)

		out_c.println("");
		out_c.println("AVMTHUNK_BEGIN_NATIVE_TABLES(%s)" % self.abc.scriptName)
		out_c.indent += 1

		out_c.println("");
		out_c.println("AVMTHUNK_BEGIN_NATIVE_METHODS(%s)" % self.abc.scriptName)
		out_c.indent += 1
		for i in range(0, len(abc.methods)):
			m = abc.methods[i]
			if m.isNative() and (m.receiver == None or m.receiver.ni.gen_method_map):
				assert(m.native_method_name != None)
				assert(m.native_id_name != None)
				if m.receiver == None:
					self.out_c.println("AVMTHUNK_NATIVE_FUNCTION(%s, %s)" % (m.native_id_name, m.native_method_name))
				else:
					# special-case the two oddballs of the group: String and Namespace
					# don't descend from ScriptObject and so need a little extra love.
					if str(m.receiver.name) == "String":
						nmout = "AVMTHUNK_NATIVE_METHOD_STRING"
					elif str(m.receiver.name) == "Namespace":
						nmout = "AVMTHUNK_NATIVE_METHOD_NAMESPACE"
					else:
						nmout = "AVMTHUNK_NATIVE_METHOD"
					method_map_name = m.receiver.niname
					if m.receiver.ni.method_map_name != None and m.receiver.itraits == None:
						method_map_name = m.receiver.ni.method_map_name
					self.out_c.println("%s(%s, %s::%s)" % (nmout, m.native_id_name, method_map_name, m.native_method_name))
		out_c.indent -= 1
		out_c.println("AVMTHUNK_END_NATIVE_METHODS()")

		out_c.println("");
		out_c.println("AVMTHUNK_BEGIN_NATIVE_CLASSES(%s)" % self.abc.scriptName)
		out_c.indent += 1
		for i in range(0, len(abc.classes)):
			c = abc.classes[i]
			if c.ni.class_name != None or c.ni.instance_name != None:
				if c.ni.gen_method_map:
					offsetOfSlotsClass = "SlotOffsetsAndAsserts::s_slotsOffset%s" % self.__baseNINameForNIName(c.ni.class_name)
					offsetOfSlotsInstance = "SlotOffsetsAndAsserts::s_slotsOffset%s" % self.__baseNINameForNIName(c.ni.instance_name)
					out_c.println("AVMTHUNK_NATIVE_CLASS(%s, %s, %s, %s, %s, %s)" % (self.class_id_name(c), self.__baseNINameForNIName(c.ni.class_name), c.ni.class_name, offsetOfSlotsClass, c.ni.instance_name, offsetOfSlotsInstance))
				else:
					out_c.println("NATIVE_CLASS(%s, %s, %s)" % (self.class_id_name(c), c.ni.class_name, c.ni.instance_name))
		out_c.indent -= 1
		out_c.println("AVMTHUNK_END_NATIVE_CLASSES()")

		out_c.println("");
		out_c.indent -= 1
		out_c.println("AVMTHUNK_END_NATIVE_TABLES()")

		out_c.println("");
		out_c.println("AVMTHUNK_DEFINE_NATIVE_INITIALIZER(%s)" % (name));

		if opts.externmethodandclassetables:
			out_c.println("");
			out_c.println("extern const NativeClassInfo* "+name+"_classEntriesExtern = "+name+"_classEntries;");
			out_c.println("extern const NativeMethodInfo* "+name+"_methodEntriesExtern = "+name+"_methodEntries;");

		out_c.println("");
		out_c.println("/* abc */");
		n = len(abc.data.data)
		out_c.println("const uint8_t "+name+"_abc_data["+str(n)+"] = {");
		for i in range(0, n):
			x = ord(abc.data.data[i]) & 255;
			out_c.prnt("%3d" % x)
			if i+1 < n: 
				out_c.prnt(", ")
			if i%16 == 15:
				out_c.println("");
		out_c.println("};");
		out_c.println('')
		
		self.printStructInfoForClasses(out_h)
		
		if haveSecrets:
			secrets.emit(self, name, CTYPE_OBJECT)
		
		out_h.println(' '.join(('}',) * len(nativeIDNamespaces)))
		out_c.println(' '.join(('}',) * len(nativeIDNamespaces)))

	def forwardDeclareGlueClasses(self, out_h):
		#find all the native glue classes and write forward declarations for them
		cppNamespaceToGlueClasses = {}
		traitsSet = set()
		for i in range(0, len(self.abc.classes)):
			c = self.abc.classes[i]
			if c.ni.class_name != None:
				traitsSet.add(c)
			if (c.ni.instance_name != None):
				traitsSet.add(c.itraits)
		
		for t in frozenset(traitsSet):
			filteredSlots = filter(lambda s: s is not None, t.slots)
			for s in filteredSlots:
				slotTraits = self.lookupTraits(s.type)
				traitsSet.add(slotTraits)
		
		glueClassToTraits = {}
		for t in traitsSet:
			if ((t.niname is not None) and (CTYPE_TO_NEED_FORWARD_DECL[ctype_from_traits(t, True)])):
				(classNS, glueClassName) = self.__parseCPPClassName(t.niname)
				# special hack because the meta data for the class Math says its instance data is of type double
				if (CTYPE_TO_NEED_FORWARD_DECL.get(glueClassName, True)):
					cppNamespaceToGlueClasses.setdefault(classNS, set()).add(glueClassName)
					glueClassToTraits[classNS + u'::' + glueClassName] = t
		for (nsStr, glueClasses) in cppNamespaceToGlueClasses.iteritems():
			#turn list of namespaces [foo, bar, baz] into "namespace foo { namespace bar { namespace baz{"
			nsList = self.__parseCPPNamespaceStr(nsStr)
			out_h.println(' '.join(map(lambda ns: u'namespace %s {' % ns, nsList)))
			out_h.indent += 1
			
			for glueClass in sorted(glueClasses):
				traits = glueClassToTraits[nsStr + u'::' + glueClass]
				out_h.println('class %s; //%s' % (glueClass, str(traits.name)))
			out_h.indent -= 1
			out_h.println(' '.join(('}',) * len(nsList)))
			out_h.println('')

	@staticmethod
	def cmpSlots(slotA, slotB, slotsTypeInfo):
		if (slotA is slotB):
			return 0;
		
		# slotA or slotB could be None, which means they are an anonymous slot.
		# Anonymous slots should be at the end of the pointer slots.
		slotBBucket = CTYPE_TO_SLOT_SORT_BUCKET[slotsTypeInfo[id(slotB)][0]] if (slotB is not None) else POINTER_SLOT_BUCKET
		if (slotA is None):
			if (slotBBucket <= POINTER_SLOT_BUCKET):
				return 1
			else:
				return -1
		
		assert slotA is not None
		slotABucket = CTYPE_TO_SLOT_SORT_BUCKET[slotsTypeInfo[id(slotA)][0]]
		if (slotB is None):
			if (slotBBucket <= POINTER_SLOT_BUCKET):
				return -1
			else:
				return 1
				
		assert slotB is not None
		slotBucketCmp = cmp(slotABucket, slotBBucket)
		if (slotBucketCmp != 0):
			return slotBucketCmp
		return cmp(slotA.fileOffset, slotB.fileOffset)

	@staticmethod
	def slotsStructNameForTraits(t, isClassTraits):
		return to_cname(t.niname) + u'Slots'
	
	@staticmethod
	def __baseNINameForNIName(niname):
		return AbcThunkGen.__parseCPPClassName(niname)[1]
	
	@staticmethod
	def slotsInstanceNameForTraits(t, isClassTraits):
		return u'm_slots_' + AbcThunkGen.__baseNINameForNIName(t.niname)
		
	@staticmethod
	def needsInstanceSlotsStruct(c):
		return (c.ni.instance_name is not None) and (c.ni.instance_name != "ScriptObject")

	@staticmethod
	def hashSlots(c):
		return False

	def printStructInfoForClasses(self, out_h):
		out_h.println(u'class SlotOffsetsAndAsserts;')
		
		visitedGlueClasses = set()
		
		for i in range(0, len(self.abc.classes)):
			c = self.abc.classes[i]
			if (c.ni.class_name is not None):
				self.printStructInfoForTraits(out_h, c, visitedGlueClasses, True)
				if (self.needsInstanceSlotsStruct(c)):
					self.printStructInfoForTraits(out_h, c.itraits, visitedGlueClasses, False)
			else:
				assert not self.needsInstanceSlotsStruct(c)

	def printStructInfoForTraits(self, out_h, t, visitedGlueClasses, isClassTraits):
		if (t.base is not None):
			baseTraits = self.lookupTraits(t.base)
			if (((isClassTraits) and (baseTraits.ni.class_name is None)) or ((not isClassTraits) and (baseTraits.ni.instance_name is None))):
				glueClassName = t.ni.class_name if isClassTraits else t.ni.instance_name
				raise Error(u'Native class %s(%s) extends %s which is not a native class' % (unicode(t.name), glueClassName, unicode(t.base)))
		
		if (t.niname in visitedGlueClasses):
			if (len(t.slots) > 0):
				raise Error(u'C++ glue classes for AS3 classes that have slots may only be referenced by meta data for one AS3 class: %s(%s)' % (unicode(t.name), t.niname))
			else:
				return
				
		visitedGlueClasses.add(t.niname)
		if (t.niname in GLUECLASSES_WITHOUT_SLOTS):
			return
			
		memberVars = []
		structName = self.slotsStructNameForTraits(t, isClassTraits)
		slotsInstanceName = self.slotsInstanceNameForTraits(t, isClassTraits)
		out_h.println(u'// %s' % str(t.name))
		out_h.println(u'//-----------------------------------------------------------')
		out_h.println(u'class %(struct)s' % {u'struct' : structName})
		out_h.println(u'{')
		out_h.indent += 1
		out_h.println(u'friend class SlotOffsetsAndAsserts;')
		out_h.indent -= 1
		out_h.println(u'public:')
		out_h.indent += 1
		
		filteredSlots = filter(lambda s: s is not None, t.slots)
		
		slotsTypeInfo = {}
		for slot in filteredSlots:
			slotTraits = self.lookupTraits(slot.type)
			slotCType = ctype_from_traits(slotTraits, True)
			slotNIType = (slotTraits.niname + u'*') if ((slotTraits.niname is not None) and (slotCType == ctype_from_enum(CTYPE_OBJECT, True))) else slotCType
			slotsTypeInfo[id(slot)] = (slotCType, slotNIType)
			
		sortedSlots = sorted(t.slots, lambda x,y: self.cmpSlots(x, y, slotsTypeInfo))
		
		for slot in sortedSlots:
			if (slot is not None):
				assert slot.kind in (TRAIT_Slot, TRAIT_Const)
				(slotCType, slotNIType) = slotsTypeInfo[id(slot)]
				slotDict = { u'struct' : structName, u'native' : t.niname, u'instance' : slotsInstanceName, u'type' : slotNIType, u'name' : to_cname(slot.name) }
				CTYPE_TO_GET_METHOD_DECL[slotCType](out_h, slotDict)
				if ((slot.kind == TRAIT_Slot) or (t.ni.constSetters)):
					CTYPE_TO_SET_METHOD_DECL[slotCType](out_h, slotDict)
		out_h.indent -= 1
		out_h.println(u'private:')
		out_h.indent += 1
		
		anonCount = 0
		for slot in sortedSlots:
			if (slot is not None):
				assert slot.kind in (TRAIT_Slot, TRAIT_Const)
				(slotCType, slotNIType) = slotsTypeInfo[id(slot)]
				slotDict = { u'struct' : structName, u'native' : t.niname, u'instance' : slotsInstanceName, u'type' : slotNIType, u'name' : to_cname(slot.name) }
				CTYPE_TO_SLOT_DECL[slotCType](out_h, slotDict)
			else:
				out_h.println(u'ATOM_WB __anonymous_slot_%u;' % (anonCount,))
				anonCount = anonCount + 1
		baseTraits = self.lookupTraits(t.base)
			
		out_h.indent -= 1
		out_h.println(u'};')
		
		for slot in sortedSlots:
			assert slot.kind in (TRAIT_Slot, TRAIT_Const)
			(slotCType, slotNIType) = slotsTypeInfo[id(slot)]
			slotDict = { u'struct' : structName, u'native' : t.niname, u'instance' : slotsInstanceName, u'type' : slotNIType, u'name' : to_cname(slot.name) }
			if ((slot.kind == TRAIT_Slot) or (t.ni.constSetters)):
				CTYPE_TO_SET_METHOD_BODY[slotCType](out_h, slotDict)
		out_h.println(u'#define DECLARE_SLOTS_' + self.__baseNINameForNIName(t.niname) + u' \\')
		out_h.indent += 1
		out_h.println(u'private: \\')
		out_h.indent += 1
		out_h.println(u'friend class %s::SlotOffsetsAndAsserts; \\' % opts.nativeIDNS)
		out_h.indent -= 1
		if (len(t.slots) > 0):
			out_h.println(u'protected: \\')
			out_h.indent += 1
			for slot in sortedSlots:
				assert slot.kind in (TRAIT_Slot, TRAIT_Const)
				(slotCType, slotNIType) = slotsTypeInfo[id(slot)]
				slotDict = { u'struct' : structName, u'native' : t.niname, u'instance' : slotsInstanceName, u'type' : slotNIType, u'name' : to_cname(slot.name) }
				out_h.println(u'REALLY_INLINE %(type)s get_%(name)s() const { return %(instance)s.get_%(name)s(); } \\' % slotDict);
				if ((slot.kind == TRAIT_Slot) or (t.ni.constSetters)):
					CTYPE_TO_SET_METHOD_MACRO_THUNK[slotCType](out_h, slotDict)
			out_h.indent -= 1
			out_h.println(u'private: \\')
			out_h.indent += 1
			out_h.println(u'%(nativeIDNS)s::%(struct)s %(instance)s' % { u'nativeIDNS' : opts.nativeIDNS, u'struct' : structName, u'instance' : slotsInstanceName} )
			out_h.indent -= 1
		else:
			out_h.indent += 1
			out_h.println(u'typedef %s::%s EmptySlotsStruct_%s' % (opts.nativeIDNS, structName, self.__baseNINameForNIName(t.niname)))
			out_h.indent -= 1
		out_h.indent -= 1
		out_h.println(u'//-----------------------------------------------------------')
		out_h.println(u'')
	
	def printStructAsserts(self, out_c, abc):
		namesDict = {}
		for i in range(1, len(abc.names)):
			if (not isinstance(abc.names[i], TypeName)):
				namesDict[id(abc.qname(abc.names[i]))] = i
		
		out_c.println(u'class SlotOffsetsAndAsserts')
		out_c.println(u'{')
		out_c.println(u'private:')
		out_c.indent += 1
		out_c.println(u'static uint32_t getSlotOffset(Traits* t, int nameId);')
		out_c.indent -= 1
		out_c.println(u'public:')
		out_c.indent += 1
		visitedNativeClasses = set()
		for i in range(0, len(abc.classes)):
			c = abc.classes[i]
			if (c.ni.gen_method_map):
				if (c.ni.class_name not in visitedNativeClasses):
					visitedNativeClasses.add(c.ni.class_name)
					if (len(c.slots) > 0):
						out_c.println(u'static const uint16_t s_slotsOffset%(nativeClassBaseName)s = offsetof(%(nativeClass)s, %(slotsInstance)s);' %
							{ u'nativeClass' : c.ni.class_name
							, u'nativeClassBaseName' : self.__baseNINameForNIName(c.ni.class_name)
							, u'slotsInstance' : self.slotsInstanceNameForTraits(c, True) } )
					else:
						out_c.println(u'static const uint16_t s_slotsOffset%s = 0;' % self.__baseNINameForNIName(c.ni.class_name))
				if (c.ni.instance_name not in visitedNativeClasses):
					visitedNativeClasses.add(c.ni.instance_name)
					if (len(c.itraits.slots) > 0):
						out_c.println(u'static const uint16_t s_slotsOffset%(nativeClassBaseName)s = offsetof(%(nativeClass)s, %(slotsInstance)s);' %
							{ u'nativeClass' : c.ni.instance_name
							, u'nativeClassBaseName' : self.__baseNINameForNIName(c.ni.instance_name)
							, u'slotsInstance' : self.slotsInstanceNameForTraits(c.itraits, False) } )
					else:
						out_c.println(u'static const uint16_t s_slotsOffset%s = 0;' % self.__baseNINameForNIName(c.ni.instance_name))
				out_c.println(u'static void do%sAsserts(Traits* cTraits, Traits* iTraits);' % self.__baseNINameForNIName(c.ni.class_name))
		
		out_c.indent -= 1
		out_c.println(u'};')
		for i in range(0, len(abc.classes)):
			c = abc.classes[i]
			if (c.ni.class_name is not None):
				out_c.println(u'REALLY_INLINE void SlotOffsetsAndAsserts::do%sAsserts(Traits* cTraits, Traits* iTraits)' % self.__baseNINameForNIName(c.ni.class_name))
				out_c.println(u'{')
				out_c.indent += 1
				out_c.println(u'(void)cTraits; (void)iTraits;')
				noSlotsStaticAssertStr = u'// MMGC_STATIC_ASSERT(sizeof(%(nativeClass)s::EmptySlotsStruct_%(nativeClassBaseName)s) >= 0);'
				assert (c.ni.class_name is not None)
				if (len(c.slots) > 0):
					self.printStructAssertsForTraits(namesDict, out_c, c, True, u'cTraits')
				elif (c.ni.class_name not in GLUECLASSES_WITHOUT_SLOTS):
					out_c.println(noSlotsStaticAssertStr % { u'nativeClass' : c.ni.class_name, u'nativeClassBaseName' : self.__baseNINameForNIName(c.ni.class_name) })
				if (self.needsInstanceSlotsStruct(c)):
					if (len(c.itraits.slots) > 0):
						self.printStructAssertsForTraits(namesDict, out_c, c.itraits, False, u'iTraits')
					elif (c.ni.instance_name not in GLUECLASSES_WITHOUT_SLOTS):
						out_c.println(noSlotsStaticAssertStr % { u'nativeClass' : c.ni.instance_name, u'nativeClassBaseName' : self.__baseNINameForNIName(c.ni.instance_name) })
				
				out_c.indent -= 1
				out_c.println(u'}')
	
	def printStructAssertsForTraits(self, namesDict, out_c, t, isClassTraits, traitsVarName):
		if (len(t.slots) == 0):
			return
		filteredSlots = filter(lambda s: s is not None, t.slots)
		structName = self.slotsStructNameForTraits(t, isClassTraits)
		slotsInstanceName = self.slotsInstanceNameForTraits(t, isClassTraits)
		formatDict = {
				u'nativeClass' : t.niname
			,	u'nativeClassBaseName' : self.__baseNINameForNIName(t.niname)
			,	u'slotsInstance' : slotsInstanceName
			,	u'structName' : structName
		}
		out_c.println(u'MMGC_STATIC_ASSERT(offsetof(%(nativeClass)s, %(slotsInstance)s) == s_slotsOffset%(nativeClassBaseName)s);' % formatDict)
		out_c.println(u'MMGC_STATIC_ASSERT(offsetof(%(nativeClass)s, %(slotsInstance)s) <= 0xFFFF);' % formatDict)
		out_c.println(u'MMGC_STATIC_ASSERT(sizeof(%(nativeClass)s) <= 0xFFFF);' % formatDict)
		for slot in filteredSlots:
			formatDict = {
					u'traits' : traitsVarName
				,	u'nameId' : namesDict[id(slot.name)]
				,	u'nativeClass' : t.niname
				,	u'slotsInstance' : slotsInstanceName
				,	u'structName' : structName
				,	u'slotName' : to_cname(slot.name)
			}
			out_c.println(u'AvmAssert(getSlotOffset(%(traits)s, %(nameId)u) == (offsetof(%(nativeClass)s, %(slotsInstance)s) + offsetof(%(structName)s, m_%(slotName)s)));' % formatDict)


	def argTraits(self, receiver, m):
		argtraits = [ receiver ]
		for i in range(0, len(m.paramTypes)):
			argtraits.append(self.lookupTraits(m.paramTypes[i]))
		return argtraits

	def thunkDecl(self, name, ret):
		assert(ret != "AvmObject")
		if ret != "double":
			ret = "AvmBox"
		decl = ret+" "+name+"_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)"
		return decl

	def emitThunkProto(self, name, receiver, m):
		ret = ctype_from_traits(self.lookupTraits(m.returnType), False);
		# see note in thunkSig() about setter return types
		if m.kind == TRAIT_Setter:
			ret = "void"
		decl = self.thunkDecl(name, ret)
		self.out_h.println("extern "+decl+";");

	def emitThunkBody(self, name, receiver, m, directcall):
		rettraits = self.lookupTraits(m.returnType)
		ret = ctype_from_traits(rettraits, False);
		# see note in thunkSig() about setter return types
		if m.kind == TRAIT_Setter:
			ret = "void"
		decl = self.thunkDecl(name, ret)
		
		unbox_receiver = self.calc_unbox_this(m)

		self.out_c.println(decl);
		self.out_c.println("{");
		self.out_c.indent += 1;

		if opts.thunkvprof:
			self.out_c.println('_nvprof("%s", 1);' % name)

		param_count = len(m.paramTypes);
		optional_count = m.optional_count;

		argtraits = self.argTraits(receiver, m)

		argszprev = "0"
		self.out_c.println("enum {");
		self.out_c.indent += 1;
		for i in range(0, len(argtraits)):
			cts = ctype_from_traits(argtraits[i], True);
			if i == 0:
				self.out_c.println("argoff0 = 0");
			else:
				self.out_c.println(", argoff"+str(i)+" = argoff"+str(i-1)+" + "+argszprev+"");
			argszprev = "AvmThunkArgSize_"+cts;
		self.out_c.indent -= 1;
		self.out_c.println("};");
	
		if m.needRest():
			self.out_c.println("const uint32_t argoffV = argoff"+str(len(argtraits)-1)+" + "+argszprev+";");
		
		args = []
		
		cts = ctype_from_traits(argtraits[0], True)
		assert(cts in ["AvmObject","AvmString","AvmNamespace"])
		if unbox_receiver:
			val = "AvmThunkUnbox_AvmAtomReceiver("+cts+", argv[argoff0])";
		else:
			val = "AvmThunkUnbox_AvmReceiver("+cts+", argv[argoff0])";
		if directcall and argtraits[0].niname != None:
			val = "(%s*)%s" % (argtraits[0].niname, val)
		args.append((val, cts))

		for i in range(1, len(argtraits)):
			cts = ctype_from_traits(argtraits[i], True)
			val = "AvmThunkUnbox_"+cts+"(argv[argoff" + str(i) + "])";
			if directcall and cts == "AvmObject" and argtraits[i].niname != None:
				val = "(%s*)%s" % (argtraits[i].niname, val)
			# argtraits includes receiver at 0, optionalValues does not
			if i > param_count - optional_count:
				dct,defval,defvalraw = self.abc.default_ctype_and_value(m.optionalValues[i-1]);
				dts = ctype_from_enum(dct, True)
				if dts != cts:
					defval = "AvmThunkCoerce_"+dts+"_"+cts+"("+defval+")";
				val = "(argc < "+str(i)+" ? "+defval+" : "+val+")";
				if directcall and cts == "AvmObject" and argtraits[i].niname != None:
					val = "(%s*)%s" % (argtraits[i].niname, val)
			args.append((val, cts))

		if m.needRest():
			args.append(("(argc <= "+str(param_count)+" ? NULL : argv + argoffV)", "AvmBox*"))
			args.append(("(argc <= "+str(param_count)+" ? 0 : argc - "+str(param_count)+")", "uint32_t"))

		if not m.hasOptional() and not m.needRest():
			self.out_c.println("(void)argc;");

		if directcall:
			self.out_c.println("(void)env;") # avoid "unreferenced formal parameter" in non-debugger builds
			if m.receiver == None:
				recname = "ScriptObject"
			else:
				recname = m.receiver.niname
			self.out_c.println("%s* const obj = %s;" % (recname, args[0][0]))
			if ret != "void":
				if rettraits.ctype == CTYPE_OBJECT:
					if rettraits.niname == None:
						self.out_c.prnt("%s const ret = " % ("AvmObject"))
					else:
						self.out_c.prnt("%s* const ret = " % (rettraits.niname))
				else:
					self.out_c.prnt("%s const ret = " % (ret))
			if m.receiver == None:
				self.out_c.prnt("%s(obj" % m.native_method_name)
				need_comma = True
			else:
				native_method_name = m.native_method_name
				if m.receiver.ni.method_map_name != None and m.receiver.itraits == None:
					native_method_name = m.receiver.ni.method_map_name + "::" + m.native_method_name
				self.out_c.prnt("obj->%s(" % native_method_name)
				need_comma = False
			if len(args) > 1:
				self.out_c.println("")
				self.out_c.indent += 1
				for i in range(1, len(args)):
					if need_comma:
						self.out_c.prnt(", ")
					self.out_c.println("%s" % args[i][0]);
					need_comma = True
				self.out_c.indent -= 1
			self.out_c.println(");")
			if ret != "void":
				if ret == "double":
					self.out_c.println("return ret;")
				else:
					self.out_c.println("return (AvmBox) ret;")
		else:
			if m.receiver == None:
				self.out_c.prnt("typedef AvmRetType_%s (*FuncType)(AvmObject" % (ret))
				for i in range(1, len(args)):
					self.out_c.prnt(", " + args[i][1]);
				self.out_c.println(");");
				self.out_c.println("const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_FUNCTION_HANDLER(env));")
				if ret != "void":
					if ret == "double":
						self.out_c.prnt("return ")
					else:
						self.out_c.prnt("return (AvmBox)")
				self.out_c.println("(*func)(%s" % (args[0][0]))
				self.out_c.indent += 1
				for i in range(1, len(args)):
					self.out_c.println(", " + args[i][0]);
				self.out_c.indent -= 1
				self.out_c.println(");")
			else:
				self.out_c.prnt("typedef AvmRetType_%s (%sT::*FuncType)(" % (ret, args[0][1]))
				for i in range(1, len(args)):
					if i > 1:
						self.out_c.prnt(", ")
					self.out_c.prnt(args[i][1]);
				self.out_c.println(");");
				self.out_c.println("const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));")
				if ret != "void":
					if ret == "double":
						self.out_c.prnt("return ")
					else:
						self.out_c.prnt("return (AvmBox)")
				self.out_c.println("(*(%s).*(func))(" % (args[0][0]))
				self.out_c.indent += 1
				for i in range(1, len(args)):
					if i > 1:
						self.out_c.prnt(", ")
					self.out_c.println(args[i][0]);
				self.out_c.indent -= 1
				self.out_c.println(");")

		if ret == "void":
			self.out_c.println("return kAvmThunkUndefined;")
		self.out_c.indent -= 1
		self.out_c.println("}")

	# inefficient, but doesn't really matter
	def find_override_base(self, mi):
		if mi.override and mi.receiver.base != None:
			bt = self.lookupTraits(mi.receiver.base)
			for j in range(0, len(bt.tmethods)):
				bmi = bt.tmethods[j]
				if bmi.name.name == mi.name.name and bmi.name.ns == mi.name.ns and bmi != mi:
					#print "OVER", str(mi.name), str(mi.receiver)
					#print "BASE", str(bmi.name), str(bmi.receiver)
					return bt,bmi
		return None,None

	def calc_unbox_this(self, mi):
		if mi.unbox_this < 0:
			bt,bmi = self.find_override_base(mi)
			if bmi == None:
				mi.unbox_this = 0 # no need to unbox
			elif bmi.unbox_this > 0:
				mi.unbox_this = 1 # unbox_this is sticky, down the inheritance tree
			elif len(bmi.paramTypes) > 0:
				param0 = self.lookupTraits(bmi.paramTypes[0])
				if mi.receiver.ctype in [CTYPE_OBJECT,CTYPE_STRING,CTYPE_NAMESPACE] and param0.ctype == CTYPE_ATOM:
					mi.unbox_this = 1 # unbox_this is sticky, down the inheritance tree
		return mi.unbox_this > 0

	def lookupTraits(self, name):
		name = str(name)
		if self.lookup_traits == None:
			self.lookup_traits = {}
			self.lookup_traits["*"] = NULL
			self.lookup_traits["void"] = UNDEFINED
			for a in self.abcs:
				for t in a.scripts:
					if self.lookup_traits.has_key(str(t)):
						raise Error("duplicate name found: " + name)
					self.lookup_traits[str(t)] = t
				for t in a.classes:
					if self.lookup_traits.has_key(str(t)):
						raise Error("duplicate name found: " + name)
					self.lookup_traits[str(t)] = t
				for t in a.instances:
					if self.lookup_traits.has_key(str(t)):
						raise Error("duplicate name found: " + name)
					self.lookup_traits[str(t)] = t
		if not self.lookup_traits.has_key(name):
			raise Error("name not found: " + name)
		return self.lookup_traits[name]
		
	def thunkSig(self, receiver, m):
		sig = sigchar_from_traits(self.lookupTraits(m.returnType), False);
		# many setters are declared as returning "undefined" in as3 but return "void" in C++.
		# we could force them to be explicitly "void" in AS3, but I'm loathe to risk compatibility issues...
		# so let's just force their native impl (and sig) to return void. (modifying the sig is important,
		# otherwise we might combine some setters with some non-setters, which could have disastrous results)
		if m.kind == TRAIT_Setter:
			sig = "v"
		sig += "2"
		if m.returnType.name == "Number":
			sig += "d"
		else:
			sig += "a"
		sig += "_";
		argtraits = self.argTraits(receiver, m)
		for i in range(0, len(argtraits)):
			sig += sigchar_from_traits(argtraits[i], True)
		if m.hasOptional():
			param_count = len(m.paramTypes)
			for i in range(param_count - m.optional_count, param_count):
				dct,defval,defvalraw = self.abc.default_ctype_and_value(m.optionalValues[i]);
				sig += "_opt" + sigchar_from_enum(dct, True) + to_cname(defval)
		if m.needRest():
			sig += "_rest"
		if self.calc_unbox_this(m):
			sig += "_u"
		# native script functions can't share thunk with native class methods, add a prefix to force uniqueness
		if m.receiver == None:
			sig = "func_" + sig
		return sig;

	def gatherThunk(self, receiver, m):
		if m.native_id_name == None:
			raise Error("name not specified for native method " + str(m.name))
		self.all_thunks.append((receiver, m))	

	def processClass(self, b):
		c = b.value
		self.processTraits(c)
		self.processTraits(c.itraits)

	def processMethod(self, receiver, m):
		if m.isNative():
			self.gatherThunk(receiver, m)

	def processTraits(self, s):
		if s.init != None:
			if s.init.isNative():
				raise Error("native constructors are not allowed: " + str(s))
			self.processMethod(s, s.init)
		for i in range(0, len(s.members)):
			if s.members[i].kind in [TRAIT_Method,TRAIT_Getter,TRAIT_Setter]:
				self.processMethod(s, s.members[i])
			elif s.members[i].kind in [TRAIT_Class]:
				self.processClass(s.members[i]);
	
ngen = AbcThunkGen();
abcGenFor = None
abcGenName = ""
for file in args:
	try:
		f = open(file,"rb")
		data = f.read()
	finally:
		f.close()

	abcScriptName = os.path.splitext(os.path.split(file)[1])[0]
	#print "read %s" % abcScriptName
	abcGenFor = Abc(data, abcScriptName)
	ngen.addAbc(abcGenFor)
	abcGenName = os.path.splitext(file)[0]

if abcGenFor:
	hf = None
	hc = None
	try:
		hf = open(abcGenName+".h2","w")
		hc = open(abcGenName+".cpp2","w")
		h = IndentingPrintWriter(hf)
		c = IndentingPrintWriter(hc)
		ngen.emit(abcGenFor, abcScriptName, h, c);
	except Exception, e:
		sys.stderr.write("ERROR: "+str(e)+"\n")
		exit(1)
	finally:
		if hf != None:
			hf.close()
		if hc != None:
			hc.close()
