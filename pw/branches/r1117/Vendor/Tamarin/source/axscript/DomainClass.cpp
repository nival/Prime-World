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

// This is a clone of the shell's file of the same name, but header and namespaces changed.
// Now its been changed to handle a NULL 'parent' better

#include "axtam.h"
class ByteArrayObject;
class ByteArray;
#include "DataIO.h"
#include "ByteArrayGlue.h"
#include "DomainClass.h"
#include "mscom.h"

namespace axtam
{
	BEGIN_NATIVE_MAP(DomainClass)
		NATIVE_METHOD(axtam_Domain_Domain, DomainObject::constructFromDomain)
		NATIVE_METHOD(axtam_Domain_loadBytes, DomainObject::loadBytes)
		NATIVE_METHOD(axtam_Domain_addNamedScriptObject, DomainObject::addNamedScriptObject)
		NATIVE_METHOD(axtam_Domain_exposeGlobalMembers, DomainObject::exposeGlobalMembers)
		NATIVE_METHOD(axtam_Domain_currentDomain_get, DomainClass::get_currentDomain)
		NATIVE_METHOD(axtam_Domain_getClass, DomainObject::getClass)
		NATIVE_METHOD(axtam_Domain_global_get, DomainObject::get_global)
	END_NATIVE_MAP()
	
	DomainObject::DomainObject(VTable *vtable, ScriptObject *delegate)
		: ScriptObject(vtable, delegate)
	{
	}

	DomainObject::~DomainObject()
	{
	}

	void DomainObject::constructFromDomain(DomainObject *parentDomain, Atom aGlobalObject)
	{
		// XXX - this is still an experiment-in-progress.  Attempts at hooking up this
		// global aren't complete.
		AXTam *core = (AXTam*) this->core();

		Domain* baseDomain;
		if (parentDomain) {
			baseDomain = parentDomain->domainEnv->getDomain();
		} else {
			baseDomain = core->builtinDomain;
		}

		DomainEnv* baseDomainEnv = NULL;
		domain = new (core->GetGC()) Domain(core, baseDomain);

		if (parentDomain) {
			domainToplevel = parentDomain->domainToplevel;
			baseDomainEnv  = parentDomain->domainEnv;
		} else {
			domainToplevel = core->initAXTamBuiltins(false);
			baseDomainEnv = domainToplevel->domainEnv();
		}
		domainEnv = new (core->GetGC()) DomainEnv(core, domain, baseDomainEnv);

		// Create a new 'scriptEnv' for the domain, suitable for sticking our own 'global'
		// objects in.
		AbcEnv* abcEnv = core->toplevel->object_vtable->abcEnv;
		Traits *scriptTraits = core->traits.object_itraits;
		ScopeChain* emptyScope = ScopeChain::create(core->GetGC(), core->traits.object_itraits->scope, NULL, core->newNamespace(core->kEmptyString));
		VTable* scriptVTable = core->newVTable(scriptTraits, NULL, emptyScope, abcEnv, core->toplevel);
		scriptEnv = new (core->GetGC()) ScriptEnv(scriptTraits->init, scriptVTable);
		//scriptVTable->init = scriptEnv;
		if (core->isNull(aGlobalObject)) {
			scriptEnv->initGlobal();
		} else if (core->isObject(aGlobalObject)) {
			// init things manually such that the specified object is the global.
			scriptVTable->resolveSignatures();
			AvmAssert(scriptTraits->getNativeScriptInfo()==NULL); // not a native script
			scriptTraits->resolveSignatures(domainToplevel);
			scriptEnv->global = core->atomToScriptObject(aGlobalObject);
		} else {
			toplevel()->throwTypeError(kCantUseInstanceofOnNonObjectError);
		}

	}

	void DomainObject::addNamedScriptObject(Stringp name)
	{
		// The script code has already done 'domain.global[name] = ob' -  but we still
		// need to stick it in namedScripts, which script code can't do.
		domainEnv->namedScripts->add(name, core()->publicNamespace, (Binding)(ScriptEnv *)scriptEnv);
	}
	void DomainObject::exposeGlobalMembers(Atom aObject, Atom aTypeinfo)
	{
		/**** XXX - this is dead and should be removeed...
		AXTam *core = (AXTam*) this->core();
		if (!core->isObject(aObject) || !core->isObject(aTypeinfo))
			toplevel()->throwTypeError(kCantUseInstanceofOnNonObjectError);
		// XXX - Need to typecheck this!
		IDispatchConsumer *ob = (IDispatchConsumer *)core->atomToScriptObject(aObject);
		IUnknownConsumer *obti = (IUnknownConsumer *)core->atomToScriptObject(aTypeinfo);
		// ack - keep all the type-unsafe stuff together...
		AvmAssert(obti->iid == __uuidof(ITypeInfo));
		//ITypeInfo *ti = (ITypeInfo *)(IUnknown *)obti->ob;


		AbcEnv* abcEnv = core->toplevel->object_vtable->abcEnv;
		Traits *traits = core->traits.object_itraits;
		ScopeChain* emptyScope = ScopeChain::create(core->GetGC(), core->traits.object_itraits->scope, NULL, core->newNamespace(core->kEmptyString));
		VTable* vtable = core->newVTable(traits, NULL, emptyScope, abcEnv, core->toplevel);
		ScriptEnv *scriptEnv = new (core->GetGC()) ScriptEnv(traits->init, vtable);
		// and instead of:
		// scriptEnv->initGlobal();
		// init things manually such that our object is the global.
		vtable->resolveSignatures();
		AvmAssert(traits->getNativeScriptInfo()==NULL); // not a native script

		Toplevel* toplevel = core->toplevel;
		traits->resolveSignatures(toplevel);
		scriptEnv->global = ob;
		***/
	}


	Atom DomainObject::loadBytes(ByteArrayObject *b)
	{
		AvmCore* core = this->core();
		if (!b)
			toplevel()->throwTypeError(kNullArgumentError, core->toErrorString("bytes"));

		axtam::CodeContext* codeContext = new (core->GetGC()) axtam::CodeContext(domainEnv);

		// parse new bytecode
		size_t len = b->get_length();
		ScriptBuffer code = core->newScriptBuffer(len);
		memcpy(code.getBuffer(), &b->GetByteArray()[0], len);
		Toplevel *toplevel = domainToplevel;
		return core->handleActionBlock(code, 0,
								  domainEnv,
								  toplevel,
								  NULL, NULL, NULL, codeContext);
	}

	ScriptObject* DomainObject::finddef(Multiname* multiname,
										DomainEnv* domainEnv)
	{
		Toplevel* toplevel = this->toplevel();

		ScriptEnv* script = (ScriptEnv*) domainEnv->getScriptInit(multiname);
		if (script == (ScriptEnv*)BIND_AMBIGUOUS)
            toplevel->throwReferenceError(kAmbiguousBindingError, multiname);

		if (script == (ScriptEnv*)BIND_NONE)
            toplevel->throwReferenceError(kUndefinedVarError, multiname);

		if (script->global == NULL)
		{
			script->initGlobal();
			Atom argv[1] = { script->global->atom() };
			script->coerceEnter(0, argv);
		}

		return script->global;
	}

	Atom DomainObject::get_global()
	{
		return scriptEnv->global->atom();
	}
	
	ClassClosure* DomainObject::getClass(Stringp name)
	{
		AvmCore *core = this->core();

		if (name == NULL) {
			toplevel()->throwArgumentError(kNullArgumentError, core->toErrorString("name"));
		}
			
		// Search for a dot from the end.
		int dot;
		for (dot=name->length()-1; dot >= 0; dot--)
			if ((*name)[dot] == (wchar)'.')
				break;
		
		// If there is a '.', this is a fully-qualified
		// class name in a package.  Must turn it into
		// a namespace-qualified multiname.
		Namespace* ns;
		Stringp className;
		if (dot != -1) {
			Stringp uri = core->internString(new (core->GetGC()) String(name, 0, dot));
			ns = core->internNamespace(core->newNamespace(uri));
			className = core->internString(new (core->GetGC()) String(name, dot+1, name->length()-(dot+1)));
		} else {
			ns = core->publicNamespace;
			className = core->internString(name);
		}

		Multiname multiname(ns, className);

		axtam::CodeContext* codeContext = (axtam::CodeContext*)core->codeContext();
		
		ScriptObject *container = finddef(&multiname, codeContext->domainEnv());
		if (!container) {
			toplevel()->throwTypeError(kClassNotFoundError, core->toErrorString(&multiname));
		}
		Atom atom = toplevel()->getproperty(container->atom(),
											&multiname,
											container->vtable);

		if (!core->istype(atom, core->traits.class_itraits)) {
			toplevel()->throwTypeError(kClassNotFoundError, core->toErrorString(&multiname));
		}			
		return (ClassClosure*)AvmCore::atomToScriptObject(atom);
	}

	DomainClass::DomainClass(VTable *cvtable)
		: ClassClosure(cvtable)
	{
		createVanillaPrototype();
	}

	ScriptObject* DomainClass::createInstance(VTable *ivtable,
											  ScriptObject *prototype)
	{
		return new (core()->GetGC(), ivtable->getExtraSize()) DomainObject(ivtable, prototype);
	}

	DomainObject* DomainClass::get_currentDomain()
	{
		//axtam::CodeContext* codeContext = (axtam::CodeContext*)core()->codeContext();

		DomainObject* domainObject = (DomainObject*) createInstance(ivtable(), prototype);
		AXTam *core = (AXTam *)this->core();

		domainObject->domainEnv = core->toplevel->domainEnv(); // MarkH - codeContext->domainEnv();
		domainObject->domainToplevel = toplevel();
		
		return domainObject;
	}
}
