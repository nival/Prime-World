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

#ifndef __axtam_IUnknownConsumer__
#define __axtam_IUnknownConsumer__


namespace axtam
{
	// base class for a JS object wrapping an IUnknown for 'consumption'
	// (ie, the object is implemented externally and 'consumed' by ES.
	class IUnknownConsumer : public ScriptObject
	{
		friend class IUnknownConsumerClass;
	protected:
		IUnknownConsumer(VTable* vtable, ScriptObject* prototype, IUnknown *pUnk, const IID &_iid)
			: ScriptObject(vtable, prototype),
			  ob(pUnk), iid(_iid)
		{
			AvmAssert(pUnk!= 0);
		}
		~IUnknownConsumer() {ob = NULL; memset((void *)&iid, 0, sizeof(IID));}

	public:
		// On success, returns a new COM reference
		HRESULT get(const IID &iid, void **ret);
		// Using a 'const &' isn't possible as we need to zero it!
		IID iid;
		CComPtr<IUnknown> ob;
	};

		class IUnknownConsumerClass : public ClassClosure
	{
	public:
		IUnknownConsumerClass(VTable* cvtable);
		~IUnknownConsumerClass();

		// Create an instance from native code.
		IUnknownConsumer* create(IUnknown *pDisp, const IID &iid = __uuidof(0));

		DECLARE_NATIVE_MAP(IUnknownConsumerClass)
	};

}
#endif // __axtam_IUnknownConsumer__
