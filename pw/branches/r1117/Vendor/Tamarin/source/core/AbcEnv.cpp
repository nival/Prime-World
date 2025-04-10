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

#include "avmplus.h"

namespace avmplus
{
	AbcEnv::AbcEnv(PoolObject* _pool,
		   DomainEnv* _domainEnv,
		   CodeContext * _codeContext)
		: m_pool(_pool),
		  m_domainEnv(_domainEnv),
		  m_codeContext(_codeContext),
		  m_privateScriptEnvs(new(_pool->core->GetGC()) MultinameHashtable())
#ifdef DEBUGGER
		  , m_invocationCounts(NULL)
#endif
#ifdef VMCFG_NANOJIT
		  , m_core(_pool->core)
#endif
	{
#ifdef DEBUGGER
		if (_pool->core->debugger())
		{
			m_invocationCounts = (uint64_t*)_pool->core->GetGC()->Alloc(_pool->methodCount() * sizeof(uint64_t), MMgc::GC::kZero);
		}
#endif		
	}

	AbcEnv::~AbcEnv()
    {
        #ifdef VMCFG_NANOJIT
        // if any AbcEnv goes away, we have to flush the BindingCache entries for all 
        // extant pools. Since AvmCore keeps a list of all live pools, we just set a flag 
        // in AvmCore that triggers the flush in postsweep(). (Note that we can't rely on our pool
        // being valid here; it might have already been collected!)
        m_core->flushBindingCachesNextSweep();
        #endif
    }

	ScriptEnv* AbcEnv::getScriptEnv(Stringp name, Namespacep ns)
	{		
		if (ns->isPrivate())
		{
			return (ScriptEnv*)m_privateScriptEnvs->get(name, ns);
		}
		else
		{
			return (ScriptEnv*)m_domainEnv->getScriptInit(ns, name);
		}
	}

	ScriptEnv* AbcEnv::getScriptEnv(const Multiname& multiname)
	{
		ScriptEnv *se = (ScriptEnv*)m_domainEnv->getScriptInit(multiname);
		if(!se)
		{	
			// check privates
			se = (ScriptEnv*)m_privateScriptEnvs->getMulti(multiname);
		}
		return se;
	}
}
