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


#ifndef __avmplus_DomainEnv__
#define __avmplus_DomainEnv__

namespace avmplus
{
	class DomainEnv : public MMgc::GCObject
	{
	  public:
		DomainEnv(AvmCore *core, Domain *domain, DomainEnv* base);
		
		// these peek into base DomainEnv as appropriate
		MethodEnv* getScriptInit(Namespacep ns, Stringp name) const;
		MethodEnv* getScriptInit(const Multiname& multiname) const;

		inline ScriptEnv* getNamedScript(Stringp name) const { return (ScriptEnv*)m_namedScripts->getName(name); }
		inline ScriptEnv* getNamedScript(Stringp name, Namespacep ns) const { return (ScriptEnv*)m_namedScripts->get(name, ns); }
		inline void addNamedScript(Stringp name, Namespacep ns, ScriptEnv* scriptEnv) { m_namedScripts->add(name, ns, Binding(scriptEnv)); }

		inline Domain* domain() const { return m_domain; }
		inline DomainEnv* base() const { return m_base; }

		/**
		 * Allow caller to enumerate the named entries in the table.
		 */
		int scriptNext(int index) const;
		Stringp scriptNameAt(int index) const;
		Namespace* scriptNsAt(int index) const;

		Toplevel* toplevel() const;
		void setToplevel(Toplevel *t) { m_toplevel = t; }
		
	// ------------------------ DATA SECTION BEGIN
	private:
		Domain* const				m_domain;		// Domain associated with this DomainEnv 
		DomainEnv* const			m_base;			// Parent DomainEnv 
		DWB(MultinameHashtable*)	m_namedScripts;	// table of named program init functions. (ns,name => MethodEnv) 
		DWB(Toplevel*)				m_toplevel;
	// ------------------------ DATA SECTION END
	};
}

#endif /* __avmplus_DomainEnv__ */
