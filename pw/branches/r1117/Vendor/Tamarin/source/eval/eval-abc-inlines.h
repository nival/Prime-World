/* -*- tab-width: 4 -*- */
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
 * Portions created by the Initial Developer are Copyright (C) 2008
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

// This file is included into eval.h

inline uint32_t ABCFile::addMethod(ABCMethodInfo* m) 
{
	methods.addAtEnd(m);
	return methodCount++;
}

inline uint32_t ABCFile::addMetadata(ABCMetadataInfo* m)
{
	metadatas.addAtEnd(m);
	return metadataCount++;
}

inline uint32_t ABCFile::addClassAndInstance(ABCClassInfo* c, ABCInstanceInfo* i)
{
	uint32_t x = addClass(c);
	DEBUG_ONLY( uint32_t y = ) addInstance(i);
	AvmAssert( x == y );
	return x;
}

inline uint32_t ABCFile::addInstance(ABCInstanceInfo* i)
{
	instances.addAtEnd(i);
	return instanceCount++;
}

inline uint32_t ABCFile::addClass(ABCClassInfo* c)
{
	classes.addAtEnd(c);
	return classCount++;
}

inline uint32_t ABCFile::addScript(ABCScriptInfo* s)
{
	scripts.addAtEnd(s);
	return scriptCount++;
}

inline uint32_t ABCFile::addMethodBody(ABCMethodBodyInfo* m)
{
	bodies.addAtEnd(m);
	return methodbodyCount++;
}

inline uint8_t ABCMethodBodyInfo::getFlags()
{
	return cogen.getFlags();
}

inline void ABCMethodInfo::setFlags(uint8_t flags)
{
	AvmAssert(this->flags == ~0U);
	this->flags = flags;
}

inline uint32_t ABCTraitsTable::addTrait(ABCTrait* t) 
{
	traits.addAtEnd(t);
	return traitsCount++;
}

inline uint32_t ABCFile::addQName(uint32_t ns, uint32_t name, bool is_attr)
{
	using namespace ActionBlockConstants;
	return multinameLookup((uint8_t)(is_attr ? CONSTANT_QnameA : CONSTANT_Qname), ns, name);
}

inline uint32_t ABCFile::addRTQName(uint32_t name, bool is_attr)
{
	using namespace ActionBlockConstants;
	return multinameLookup((uint8_t)(is_attr ? CONSTANT_RTQnameA : CONSTANT_RTQname), NO_VALUE, name);
}

inline uint32_t ABCFile::addRTQNameL(bool is_attr)
{
	using namespace ActionBlockConstants;
	return multinameLookup((uint8_t)(is_attr ? CONSTANT_RTQnameLA : CONSTANT_RTQnameL), NO_VALUE, NO_VALUE);
}

inline uint32_t ABCFile::addMultiname(uint32_t nsset, uint32_t name, bool is_attr)
{
	using namespace ActionBlockConstants;
	return multinameLookup((uint8_t)(is_attr ? CONSTANT_MultinameA : CONSTANT_Multiname), nsset, name);
}

inline uint32_t ABCFile::addMultinameL(uint32_t nsset, bool is_attr)
{
	using namespace ActionBlockConstants;
	return multinameLookup((uint8_t)(is_attr ? CONSTANT_MultinameLA : CONSTANT_MultinameL), nsset, NO_VALUE);
}

inline void ABCMethodBodyInfo::clearTraits()
{
	traits = NULL;
}

inline uint32_t ABCExceptionTable::addAtEnd(ABCExceptionInfo* e)
{
	exceptions.addAtEnd(e);
	return exceptionCount++;
}
