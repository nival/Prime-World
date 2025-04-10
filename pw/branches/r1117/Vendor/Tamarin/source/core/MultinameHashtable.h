/* -*- Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
/* vi: set ts=4 sw=4 expandtab: (add to ~/.vimrc: set modeline modelines=5) */
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

#ifndef __avmplus_MultinameHashtable__
#define __avmplus_MultinameHashtable__

namespace avmplus
{
    typedef struct Binding_* Binding;
    enum BindingKind
    {
        BKIND_NONE              = 0,        // no such binding (id == 0)            000
        BKIND_METHOD            = 1,        // MethodEnv*                           001
        BKIND_VAR               = 2,        // int local slot number (r/w var)      010
        BKIND_CONST             = 3,        // int local slot number (r/o const)    011
        BKIND_unused            = 4,        // not in use                           100
        BKIND_GET               = 5,        // get-only property                    101
        BKIND_SET               = 6,        // set-only property                    110
        BKIND_GETSET            = 7         // readwrite property                   111
    };
    // A couple of common Binding results that are worth having constants for
    const Binding BIND_AMBIGUOUS = (Binding)-1;
    const Binding BIND_NONE      = (Binding)BKIND_NONE;      // no such binding

    /**
     * Hashtable for mapping <name, ns> pairs to a Binding
     */
    class MultinameHashtable : public MMgc::GCObject
    {
        friend class StMNHTIterator;

    private:
        class Quad // 33% better!
        {
        public:
            Stringp name;
            Namespacep ns;
            Binding value;
            // non-0 if the given name exists elsewhere w/ a different NS
            // (also the alignment gives a speed boost)
            uint32_t multiNS;
            API apis;   // bit flags for versions
        };

    private:

        /**
         * Finds the hash bucket corresponding to the key <name,ns>
         * in the hash table starting at t, containing tLen
         * quads.
         */
        // match if they are the same or if they have the same base ns and ns api is in apis
        static bool matchNS(uintptr uri, API apis, Namespacep ns);
        static int find(Stringp name, Namespacep ns, const Quad *t, unsigned tLen);
        void rehash(const Quad *oldAtoms, int oldlen, Quad *newAtoms, int newlen);

        /**
         * Called to grow the Hashtable, particularly by add.
         *
         * - Calculates the needed size for the new Hashtable
         *   (typically 2X the current size)
         * - Creates a new array of Atoms
         * - Rehashes the current table into the new one
         * - Deletes the old array of Atoms and sets the Atom
         *   pointer to our new array of Atoms
         *
         */
        void grow();

    public:
        /** kDefaultCapacity must be a power of 2 */
        const static int kDefaultCapacity = 8;

        /**
         * initialize with a known capacity.  i.e. we can fit minSize
         * elements in without rehashing.
         * @param heap
         * @param capacity  # of logical slots
         */
        MultinameHashtable(int capacity = kDefaultCapacity);

        ~MultinameHashtable();

        bool isFull() const;

        /**
         * @name operations on name/ns/binding quads
         */
        /*@{*/
        void    put(Stringp name, Namespacep ns, Binding value);
        Binding get(Stringp name, Namespacep ns) const;
        Binding get(Stringp name, NamespaceSetp nsset) const;
        Binding getName(Stringp name) const;
        Binding getMulti(const Multiname* name) const;
        Binding getMulti(const Multiname& name) const;

        // return the NS that unambigously matches in "match" (or null for none/ambiguous)
        Binding getMulti(const Multiname& name, Namespacep& match) const;
        /*@}*/

        /**
         * Adds a name/value pair to a hash table.  Automatically
         * grows the hash table if it is full.
         */
        void add(Stringp name, Namespacep ns, Binding value);

        // note: if you are just doing a single iteration thru a single MNHT,
        // it's more efficient (and easier) to use StMNHTIterator instead.
        int FASTCALL next(int index) const;
        Stringp keyAt(int index) const;
        Namespacep nsAt(int index) const;
        Binding valueAt(int index) const;
        API apisAt(int index) const;

        size_t allocatedSize() const;

    private:
        const Quad* getNSSet(Stringp name, NamespaceSetp nsset) const;

    protected:
        void Init(int capacity);

    // ------------------------ DATA SECTION BEGIN
    private:    Quad* m_quads;          // property hashtable (written with explicit WB)
    public:     int size;               // no. of properties
    public:     int numQuads;           // size of hashtable
    // ------------------------ DATA SECTION END
    };


    // Note: unlike MNHT::next(), StMNHTIterator::next()
    // doesn't advance past empty entries. it's the caller's
    // responsibility to call StMNHTIterator::key() and skip null
    // entries -- this is a useful optimization since the caller
    // typically is looping and extracting this value anyway -- this is
    // a substantial win since it avoids the loop-within-a-loop scenario.
    // proper usage is:
    //
    //      StMNHTIterator iter(mnht);
    //      while (iter.next()) {
    //          if (!iter.key()) continue;
    //          .. rest of loop ..
    //      }
    //
    class StMNHTIterator
    {
    private:
        MultinameHashtable* const volatile m_mnht; // kept just to ensure it doesn't get collected -- must be volatile!
        const MultinameHashtable::Quad* m_cur;
        const MultinameHashtable::Quad* const m_end; // one past the end

    public:
        StMNHTIterator(MultinameHashtable* mnht);
        bool next();
        Stringp key() const;
        Namespacep ns() const;
        Binding value() const;
        API apis() const;
    };
}

#endif /* __avmplus_MultinameHashtable__ */
