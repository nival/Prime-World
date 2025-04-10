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



#include "avmplus.h"
#include "BuiltinNatives.h"

using namespace MMgc;

namespace avmplus
{
	// ---------------

#ifndef VMCFG_AOT
	NativeInitializer::NativeInitializer(AvmCore* _core, 
											const uint8_t* _abcData,
											uint32_t _abcDataLen,
											uint32_t _methodCount,
											uint32_t _classCount) :
		core(_core),
		abcData(_abcData),
		abcDataLen(_abcDataLen),
		methods((MethodType*)core->GetGC()->Calloc(_methodCount, sizeof(MethodType), GC::kZero)),
		classes((ClassType*)core->GetGC()->Calloc(_classCount, sizeof(ClassType), GC::kZero)),
		methodCount(_methodCount),
		classCount(_classCount)
	{
	}
#else
	NativeInitializer::NativeInitializer(AvmCore* _core, 
											const AOTInfo *_aotInfo,
											uint32_t _methodCount,
											uint32_t _classCount) :
		core(_core),
		abcData(_aotInfo->abcBytes),
		abcDataLen(_aotInfo->nABCBytes),
		methods((MethodType*)core->GetGC()->Calloc((_methodCount>0 ? _methodCount : 1), sizeof(MethodType), GC::kZero)),
		classes((ClassType*)core->GetGC()->Calloc((_classCount>0 ? _classCount : 1), sizeof(ClassType), GC::kZero)),
		methodCount(_methodCount),
		classCount(_classCount)
	    , aotInfo(_aotInfo)
		, compiledMethods(_aotInfo->abcMethods)
		, compiledMethodCount(_aotInfo->nABCMethods)
	{
	}
#endif


#ifdef AVMPLUS_STATIC_POINTERS
	void NativeInitializer::fillInMethods(const NativeMethodInfo* _methodEntry)
	{
		while (_methodEntry->method_id != -1)
		{
			// if we overwrite a native method mapping, something is hosed
			AvmAssert(methods[_methodEntry->method_id] == NULL);
			methods[_methodEntry->method_id] = _methodEntry;
			_methodEntry++;
		}
	}

	void NativeInitializer::fillInClasses(const NativeClassInfo* _classEntry)
	{
		while (_classEntry->class_id != -1)
		{
			// if we overwrite a native class mapping, something is hosed
			AvmAssert(classes[_classEntry->class_id]  == NULL);
			classes[_classEntry->class_id] = _classEntry;
			_classEntry++;
		}
	}
#else
	void NativeInitializer::fillIn(NativeInitializer::FillInProc p)
	{
		(*p)(methods, classes);
	}
#endif // AVMPLUS_STATIC_POINTERS
	
	PoolObject* NativeInitializer::parseBuiltinABC(Domain* domain)
	{
		AvmAssert(domain != NULL);
		
		ScriptBuffer code = ScriptBuffer(new (core->GetGC()) ConstDataScriptBufferImpl(abcData, abcDataLen));

		return core->parseActionBlock(code, /*start*/0, /*toplevel*/NULL, domain, this, ApiUtils::getLargestAPI(core)/*active api*/);
	}
	
	NativeInitializer::~NativeInitializer()
	{
		// might as well explicitly free now
		core->GetGC()->Free(methods);
		core->GetGC()->Free(classes);
	}

#ifdef VMCFG_AOT
	bool NativeInitializer::getCompiledInfo(NativeMethodInfo *info, Multiname &returnTypeName, uint32_t i) const
	{
		info->thunker = (AvmThunkNativeThunker)0;

		if (i < compiledMethodCount && compiledMethods[i])
		{
			bool isNumberRetType = false;
			if (NUMBER_TYPE) {
				Multiname numberTypeName(NUMBER_TYPE->ns(), NUMBER_TYPE->name());
				isNumberRetType = returnTypeName.matches(&numberTypeName);
			}
			info->thunker = isNumberRetType ? (AvmThunkNativeThunker)aotThunkerN : (AvmThunkNativeThunker)aotThunker;
			info->handler.function = compiledMethods[i];
			return true;
		}
		else
		{
			info->handler.function = (AvmThunkNativeFunctionHandler)0;
			return false;
		}
	}
#endif
}
