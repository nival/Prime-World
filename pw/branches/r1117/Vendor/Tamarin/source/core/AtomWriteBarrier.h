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

#ifndef __avmplus_AtomWriteBarrier__
#define __avmplus_AtomWriteBarrier__


namespace avmplus
{
		// Optimized Atom write barrier
		class AtomWB
		{
		public:
			explicit AtomWB() : m_atom(nullObjectAtom) 
			{
				// nothing
			}

			explicit AtomWB(Atom t)  // : m_atom(t) -- not necessary, atomWriteBarrier_ctor handles it
			{ 
				MMgc::GC* const gc = MMgc::GC::GetGC(this);
				void* const container = gc->FindBeginningFast(this);
				AvmCore::atomWriteBarrier_ctor(gc, container, &m_atom, t);
			}

			~AtomWB() 
			{ 
				AvmCore::atomWriteBarrier_dtor(&m_atom);
			}

			Atom operator=(Atom tNew)
			{
				MMgc::GC* const gc = MMgc::GC::GetGC(this);
				void* const container = gc->FindBeginningFast(this);
				set(gc, container, tNew);
				return tNew;
			}
			
			// if you know the container, this saves a call to FindBeginningFast...
			// which adds up in (e.g.) heavy E4X usage
			inline void set(MMgc::GC* gc, const void* container, Atom atomNew)
			{
				if (m_atom != atomNew)
				{
					AvmCore::atomWriteBarrier(gc, container, &m_atom, atomNew);
				}
			}

			inline operator const Atom&() const { return m_atom; }

		private:
			explicit AtomWB(const AtomWB& toCopy); // unimplemented
			void operator=(const AtomWB& wb); // unimplemented
			
			Atom set(Atom atomNew)
			{
				if (m_atom != atomNew)
				{
					MMgc::GC* gc = MMgc::GC::GetGC(this);
					AvmCore::atomWriteBarrier(gc, gc->FindBeginningFast(this), &m_atom, atomNew);
				}
				return atomNew;
			}
			Atom m_atom;
		};
#define ATOM_WB AtomWB
#define WBATOM(gc, c, a, v) AvmCore::atomWriteBarrier(gc, c, a, v)
}

#endif /* __avmplus_AtomWriteBarrier__ */
