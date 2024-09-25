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

#ifndef __avmplus_CodeContext__
#define __avmplus_CodeContext__

namespace avmplus
{
	// CodeContext is used to track which security context we are in.
	// When an AS3 method is called, the AS3 method will ensure that core->codeContext() will return its context.
	class CodeContext : public MMgc::GCObject
	{
	public:		
		virtual ~CodeContext() {}
#ifdef DEBUGGER
		virtual DomainEnv* domainEnv() const = 0;
#endif
	};

	class EnterCodeContext
	{
	public:
		inline explicit EnterCodeContext(AvmCore* core, CodeContext* new_cc) : m_core(core)
		{
			m_frame.enter(m_core, new_cc);
		}
		inline ~EnterCodeContext()
		{
			m_frame.exit(m_core);
		}
	private:
		AvmCore* const m_core;
		MethodFrame m_frame;
	};
}

#endif /* __avmplus_CodeContext__ */
