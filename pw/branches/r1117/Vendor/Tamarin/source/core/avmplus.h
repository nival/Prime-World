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
 * Portions created by the Initial Developer are Copyright (C) 1993-2006
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


#ifndef __avmplus__
#define __avmplus__

/*! \mainpage AVM+ Documentation
 *
 * \section intro Introduction
 *
 * AVM+ is the ActionScript Virtual Machine
 *
 * AVM+ offers an order of magnitude performance increase over
 * the "Classic AVM" in Flash Player 7.  Our performance target is 10X.
 *
 * AVM+ implements ActionScript 3.0, the new version of the ActionScript
 * language that is based on ECMAScript, 3rd Edition (ES3) and
 * ECMAScript for XML (E4X), and which also incorporates many
 * extensions to those languages, including packages, classes, interfaces,
 * and optional type annotations.
 *
 * AVM+ is also built for modularity.  It will be part of the Flash Player,
 * but is a self-contained module which can be incorporated into other
 * programs with ease.
 *
 * \section usage Using This Document
 *
 * This documentation is a reference manual for C++ developers working
 * with AVM+, either in the context of the Flash Player or in another
 * application.  It can be useful for developers enhancing AVM+
 * itself, or for developer who wish to understand its internals
 * in order to better interface with it.
 *
 * \section begin Where To Begin
 *
 * The avmplus::AvmCore class is the main entry point of the
 * AVM+ virtual machine, and is probably a good place to start
 * when trying to comprehend the codebase.
 *
 * \section contact Who To Contact
 *
 * For questions about AVM+, contact information, and so on please see:
 *
 * https://developer.mozilla.org/En/Tamarin
 */
 
#include "VMPI.h"			// also includes avmfeatures.h
#include "avmbuild.h"			// old-style configuration, may disappear, handles a few things not yet handled by the feature system

#include "GCTypes.h"
#include "avmplusVersion.h"
#include "AvmDebug.h"
#include "AvmLog.h"
#include "atom.h"
#include "ActionBlockConstants.h"
#include "wopcodes.h"
#include "ErrorConstants.h"
#include "NativeObjectHelpers.h"

using namespace avmplus::AtomConstants;
using namespace avmplus::ActionBlockConstants;
using namespace avmplus::ErrorConstants;

/**
 * Incomplete class definitions for everything in AVM+
 */
namespace avmplus
{
	class AbcGen;
	class AbcEnv;
	class AbcParser;
	class Accessor;
	class ArrayClass;
	class ArrayObject;
	class Atan2Method;
	class AtomArray;
	class AvmCore;
    class AvmPlusScriptableObject;
	class MethodFrame;
	class BooleanClass;
	class BuiltinTraits;
	class CallStackNode;
	class ClassClass;
	class ClassClosure;
	class Closure;
	class CodeContext;	
	class Console;
	class Date;
	class DateClass;
	class DateObject;
	class Debugger;
#ifdef DEBUGGER
	class DebuggerMethodInfo;
#endif
	class DescribeTypeClass;
	class Domain;
	class DomainEnv;
	class E4XNode;
	class ErrorClass;
	class ErrorObject;
	class Exception;
	class ExceptionFrame;
	class ExceptionHandler;
	class ExceptionHandlerTable;
	class FixedBitSet;
	class FrameState;
    class GlobalMemoryProvider;
    class GlobalMemorySubscriber;
	class HeapHashtable;
	class HeapMultiname;
	class InlineHashtable;
	class IntVectorObject;
	class DoubleVectorObject;
	class UIntVectorObject;
	class ObjectVectorObject;
	class Java;
	class MathClass;
	class MathUtils;
	class MethodClosure;
	class MethodEnv;
	class MethodInfo;
	class MethodSignature;
	class Multiname;
	class Namespace;
	class NamespaceSet;
	class NamespaceClass;
	class NativeInitializer;
	struct NativeMethodInfo;
	class NumberClass;
	class IntClass;
	class UIntClass;
	class OSDep;
	class ObjectClass;
	class OutputStream;
	class PoolObject;
	class PrintWriter;
	class Profiler;
	class RegExpClass;
	class RegExpObject;
	class Sampler;
	class ScopeChain;
	class ScopeTypeChain;
	class ScriptBuffer;
	class ScriptEnv;
	class ScriptObject;
	class StackTrace;
	class StringBuffer;
	class StringClass;
	class String;
	class Toplevel;
	class Traits;
	class TraitsBindings;
	class TraitsMetadata;
#ifdef AVMPLUS_WORD_CODE
	class TranslatedCode;
	class WordcodeTranslator;
	class WordcodeEmitter;
#endif
	class UnicodeUtils;
	class Value;
	class Verifier; 
	class VTable; 
	class VoidClass;
	class XMLClass;
	class XMLListClass;
	class XMLObject;
	class XMLListObject;
	class QNameClass;
	class QNameObject;
	class XMLParser;
	class XMLTag;

	struct WordOpcodeAttr;

	typedef Traits* Traitsp;
	// Stringp and Namespacep should be const, but RCObject doens't allow it yet
	typedef String* Stringp;
	typedef Namespace* Namespacep;
	typedef const NamespaceSet* NamespaceSetp;
	typedef const TraitsBindings* TraitsBindingsp;
	typedef const TraitsMetadata* TraitsMetadatap;
	typedef const MethodSignature* MethodSignaturep;
	
	typedef struct FramePtr_* FramePtr;
}

#ifdef VMCFG_AOT
struct ABCInfo;
#endif

#include "avm.h"

namespace avmplus
{
	// conversion routines -- intended only for Tamarin internal use
	// but, other the short term, clients may need to make use of them as
	// they adapt to the new api
	#define AVM_MAP(EXT, INT) \
		inline avm::EXT avmTo##EXT(const avmplus::INT e) { return (avm::EXT)e; } \
		inline avmplus::INT avmFrom##EXT(avm::EXT m) { return (avmplus::INT)m; } \
	
	AVM_MAP(Instance, AvmCore*)
	AVM_MAP(Object, ScriptObject*)
	AVM_MAP(CodeContext, CodeContext*)
	
	#undef AVM_MAP
}

#include "MMgc.h"
#include "QCache.h"
#include "MathUtils.h"
#include "UnicodeUtils.h"
#include "OSDep.h"
#include "OutputStream.h"
#include "ScriptBuffer.h"
#include "avmplusList.h"
#include "avmplusStack.h"
#include "SortedMap.h"
#include "BitSet.h"
#include "AvmPlusScriptableObject.h"
#include "Namespace.h"
#include "StringObject.h"
#include "MultinameHashtable.h"
#include "PrintWriter.h"
#include "BuiltinTraits.h"
#include "NamespaceSet.h"
#include "Multiname.h"
#include "Sampler.h"
#include "AvmCore.h"
#include "AtomWriteBarrier.h"
#include "avmplusHashtable.h"
#include "Traits.h"
#include "VTable.h"
#include "ScriptObject.h"
#include "NativeFunction.h"
#include "BuiltinNatives.h"
#include "Coder.h"
#include "WordcodeTranslator.h"
#include "WordcodeEmitter.h"
#include "MethodInfo.h"
#include "PoolObject.h"
#include "AbcEnv.h"
#include "TraitsIterator.h"
#include "ScopeChain.h"
#include "MethodEnv.h"
#include "CodeContext.h"
#include "avmplusProfiler.h"
#include "StringBuffer.h"
#include "AtomArray.h"
#include "Verifier.h"
#include "ClassClosure.h"
#include "ClassClass.h"
#include "FunctionClass.h"
#include "MethodClosure.h"
#include "StackTrace.h"
#include "Exception.h"
#include "MethodInfo.h"
#include "NamespaceClass.h"
#include "ArrayObject.h"
#include "MethodClosure.h"
#include "BooleanClass.h"
#include "NumberClass.h"
#include "IntClass.h"
#include "ArrayClass.h"
#include "VectorClass.h"
#include "StringClass.h"
#include "Date.h"
#include "DateClass.h"
#include "DateObject.h"
#include "DescribeTypeClass.h"
#include "Domain.h"
#include "DomainEnv.h"
#include "ObjectClass.h"
#include "ErrorClass.h"
#include "MathClass.h"
#ifdef VMCFG_EVAL
#include "eval-avmplus.h"
#endif
#include "Toplevel.h"
#include "AbcParser.h"
#include "RegExpObject.h"
#include "RegExpClass.h"
#include "XMLClass.h"
#include "XMLListClass.h"
#include "XMLObject.h"
#include "XMLListObject.h"
#include "XMLParser16.h"
#include "Interpreter.h"
#include "avmplusDebugger.h"
#include "E4XNode.h"
#include "AbcGen.h"
#include "instr.h"
#ifdef VMCFG_AOT
#include "AOTCompiler.h"
#endif

// inline implementations
#include "AbcEnv-inlines.h"
#include "AbcParser-inlines.h"
#include "atom-inlines.h"
#include "AvmCore-inlines.h"
#include "Coder-inlines.h"
#include "instr-inlines.h"
#include "MethodEnv-inlines.h"
#include "MethodInfo-inlines.h"
#include "Multiname-inlines.h"
#include "MultinameHashtable-inlines.h"
#include "NamespaceSet-inlines.h"
#include "PoolObject-inlines.h"
#include "ScopeChain-inlines.h"
#include "Toplevel-inlines.h"
#include "Traits-inlines.h"
#include "Verifier-inlines.h"
#include "VTable-inlines.h"

#endif /* __avmplus__ */ 
