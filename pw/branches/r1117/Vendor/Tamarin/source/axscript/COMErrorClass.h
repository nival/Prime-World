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
 * The Original Code is [axtam].
 *
 * The Initial Developer of the Original Code is Mozilla Corp.
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

namespace axtam {
	/**
	 * class COMError.  Our base class - only subclasses should be thrown
	 */
	class COMErrorClass : public ClassClosure
	{
	protected:
		COMErrorClass(VTable* cvtable);
	public:
//		DECLARE_NATIVE_MAP(COMErrorClass)

		Atom call(int argc, Atom* argv)
		{
			return construct(argc, argv);
		}

		// override ctor just so we can get 'hresult' :(
		Atom construct(int argc, Atom* argv);
	
		//ScriptObject *createInstance(VTable *ivtable, ScriptObject *delegate);


		/**
		 * throwError is a convenience function for throwing
		 * an exception with a hresult and optionally an EXCEPINFO.
		   NOTE: The EXCEPINFO ownership is taken by this function!
		 */
		void throwError(HRESULT hr, EXCEPINFO *pei = NULL);

		/** @name static methods */
		/*@{*/
		Stringp getErrorMessage(int errorID) const;
	};

	class COMErrorObject : public ScriptObject
	{
		friend class COMErrorClass;
	protected:
		COMErrorObject(VTable *vtable, ScriptObject *delegate);
		~COMErrorObject() {
#ifdef DEBUGGER
			stackTrace = 0; 
#endif
		}
	public:
		HRESULT getHRESULT() const;
		Stringp stackTraceToString() const;
	private:
		Atom atomhresult; // would prefer to fetch this from script object...
#ifdef DEBUGGER
		StackTrace *getStackTrace() const { return stackTrace; }

	private:
		StackTrace *stackTrace;
#endif /* DEBUGGER */
	};

	// An error specific to "com providers" - ie, classes which implement
	// COM interfaces.  An exception of this type is thrown whenever the object
	// wishes to return a failure HRESULT.  The HRESULT is returned directly
	// to whoever is using the COM interface - the user never sees these
	// kinds of exceptions.
	// In other words, these are thrown by script code and caught by native code.
	class COMProviderErrorClass : public COMErrorClass
	{
	public:
		COMProviderErrorClass(VTable* cvtable);
		ScriptObject *createInstance(VTable *ivtable, ScriptObject *delegate);
		DECLARE_NATIVE_MAP(COMProviderErrorClass)
	};

	class COMProviderErrorObject : public COMErrorObject
	{
	public:
		COMProviderErrorObject(VTable *vtable, ScriptObject *delegate)
			: COMErrorObject(vtable, delegate)
				{;}
	};

	// Exceptions specific to "com consumers" - ie, classes which use COM
	// objects.  For example, interaction with the Window object would cause
	// one of these exceptions if the underlying COM calls behind the window
	// return an unexpected error code.  These exceptions are treated like all 
	// other exceptions - a traceback will be written, the script host will be
	// notified of the error, etc.
	// In other words, these are thrown by native code and caught (or not!) by 
	// script code.
	class COMConsumerErrorClass : public COMErrorClass
	{
	public:
		COMConsumerErrorClass(VTable* cvtable);
		ScriptObject *createInstance(VTable *ivtable, ScriptObject *delegate);
		DECLARE_NATIVE_MAP(COMConsumerErrorClass)
	};

	class COMConsumerErrorObject : public COMErrorObject
	{
	public:
		COMConsumerErrorObject(VTable *vtable, ScriptObject *delegate)
			: COMErrorObject(vtable, delegate)
				{;}
	};
};
