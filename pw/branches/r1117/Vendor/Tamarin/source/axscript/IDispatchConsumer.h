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
 * The Original Code is [ActiveScripting implemented with Tamarin].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2007
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Mark Hammond
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

#ifndef __axtam_IDispatchConsumer__
#define __axtam_IDispatchConsumer__

#include "IUnknownConsumer.h"

namespace axtam
{
	// A JS object wrapping an IDispatch, exposing it as 'scriptable'
	class IDispatchConsumer : public IUnknownConsumer {
	public:
		IDispatchConsumer(VTable* vtable, ScriptObject* prototype, IDispatch *pDisp);

		IDispatch *getDispatch() const {return (IDispatch *)(IUnknown *)ob;}
		// Use the typeinfo to pre-populate the maps we use at runtime
		void populateFromTypeInfo(ITypeInfo *ti);

		// expose all the methods and properties from this object "globally"
		// into the domain.  This means that while in that domain, the 
		// properties etc can be referenced without the leading 'foo.'
		// qualifier.  Assumes populateFromTypeInfo() was called to create
		// the maps used to enumerate the items to expose.
		void exposeToDomain(ScriptEnv *env, DomainEnv *domainEnv);
	private:

		virtual Atom call(int argc, Atom* argv);
		virtual Atom callProperty(Multiname* name, int argc, Atom* argv);
		virtual Atom getAtomProperty(Atom name) const;
		virtual void setMultinameProperty(Multiname* name, Atom value);
		// note we MUST NOT implement the has*Property() functions - we
		// rely on the default impl returning False if the name if not
		// an expando...
		//bool hasMultinameProperty(Multiname* multiname) const;
		// The 'integer' methods.  The default impl winds up just
		// looking in the hashtable, not doing the whole string thing.
		// Until we have a better handle on how to optimize indexed
		// access to the DOM, just delegate to our string-based impl.
		virtual Atom getUintProperty(uint32 i) const
		{
			return getAtomProperty(core()->internUint32(i)->atom());
		}
		virtual void setUintProperty(uint32 i, Atom value)
		{
			setAtomProperty(core()->internUint32(i)->atom(), value);
		}
		virtual bool delUintProperty(uint32 i)
		{
			return deleteAtomProperty(core()->internUint32(i)->atom());
		}
		virtual bool hasUintProperty(uint32 i) const
		{
			return hasAtomProperty(core()->internUint32(i)->atom());
		}

	};

	class IDispatchConsumerClass : public ClassClosure
	{
	public:
		IDispatchConsumerClass(VTable* cvtable);
		~IDispatchConsumerClass();

		// Create an instance from native code.
		IDispatchConsumer * create(IDispatch *pDisp);

		DECLARE_NATIVE_MAP(IDispatchConsumerClass )
	};

	class AXTam;
	// a helper to manage memory for our VARIANT array, and convert from
	// an argc array to a DISPPARAMS.
	class DISPPARAMS_helper : public DISPPARAMS {
	public:
		DISPPARAMS_helper() : vars(NULL) {memset(&params, 0, sizeof(params));}
		DISPPARAMS_helper(AXTam *core, int argc, Atom* argv) : vars(NULL) {memset(&params, 0, sizeof(params));fill(core, argc, argv);}
		// WARNING: can't rely on dtor being call with exceptions :(
		~DISPPARAMS_helper() {clear();}

		operator DISPPARAMS *() {return &params;}
		void fill(AXTam *core, int argc, Atom* argv);
		void clear() {if (vars) {delete [] vars; vars=NULL;} memset(&params, 0, sizeof(params));}
		DISPPARAMS params;
		// unmanaged pointer
		CComVariant *vars;
	};
}

#endif /* __axtam_IDispatchConsumer__ */
