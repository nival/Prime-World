/* -*- mode: c++; tab-width: 4 -*- */
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

/**
 * The inside the compiler acts as a coordinating class, managing memory, interning strings, 
 * knowing about settings, etc.  Pretty much everyone points to a compiler instance,
 * which in turn provides the host context and allocator instances.
 */
class Compiler {
public:
	Compiler(HostContext* context, const wchar* filename, const wchar* src, uint32_t srclen);
	~Compiler() { destroy(); }

	void compile();
	void destroy();										// clean up all resources

	Str* intern(const wchar* w, uint32_t nchars);		// intern a string
	Str* intern(const char* w);							// intern a NUL-terminated string
	Str* intern(uint32_t u);							// convert to base-10 string, then intern it

	// A lineno of 0 is ignored here
	void syntaxError(uint32_t lineno, const char* fmt, ...);
	void internalError(uint32_t lineno, const char* fmt, ...);
	
	HostContext * const context;	// For access to the host environment
	Allocator* const allocator;		// Compiler-private bump-a-pointer never-free heap
	const wchar * const filename;	// Some human-readable name of the originator of the script, NUL-terminated
	const uint32_t tableSize;		// Number of elements in strTable; the abc layer uses this for the multiname table size too
	
	// Flags, currently somewhat ad-hoc, that are used by the compiler to control the
	// language accepted.

	const bool es3_keywords;	// True iff we should only recognize ECMAScript 3.0 keywords
	const bool liberal_idents;	// True iff we allow the use of \u to create identifers that look like keywords, or non-E262-sanctioned characters in identifiers
	const bool local_functions;	// True iff we allow block-local function definitions with SpiderMonkey semantics (hoist name, init when reached)
	const bool octal_literals;	// True iff we should recognize 0[0-7]+ as octal (not in AS3)
	const bool origin_is_file;	// True iff input came from file, so "include" should be allowed
	const bool debugging;		// True iff we should generate debug information
	
	uint32_t namespace_counter;	// Counter for anonymous namespaces

private:
	Str** const		strTable;	// fixed-length hash table using chaining on collision, chained through 'next' (in private heap)

public:
	// Compiler components
	Lexer		   lexer;
	Parser		   parser;
	ABCFile		   abc;			// must be initialized before the ID_ members
	
	// Intern all strings after strTable has been initialized

	// Pre-interned strings signifying themselves, keep alphabetical
	Str * const SYM_;			// ""
	Str * const SYM_Array;
	Str * const SYM_Namespace;
	Str * const SYM_Object;
	Str * const SYM_RegExp;
	Str * const SYM_XML;
	Str * const SYM_XMLList;
	Str * const SYM_anonymous;
	Str * const SYM_arguments;
	Str * const SYM_children;
	Str * const SYM_each;
	Str * const SYM_get;
	Str * const SYM_include;
	Str * const SYM_length;
	Str * const SYM_namespace;
#ifdef DEBUG
	Str * const SYM_print;
#endif
	Str * const SYM_prototype;
	Str * const SYM_set;
	Str * const SYM_static;
	Str * const SYM_to;
	Str * const SYM_use;
	Str * const SYM_xml;

	// Pre-interned strings for other uses
	Str * const str_filename;	// Str representation of the 'filename' member above

	// Namespaces and names that are commonly used
	const uint32_t NS_public;		// public
	const uint32_t ID_Array;		// public::Array
	const uint32_t ID_Namespace;	// public::Namespace
	const uint32_t ID_Object;		// public::Object
	const uint32_t ID_RegExp;		// public::RegExp
	const uint32_t ID_XML;			// public::XML
	const uint32_t ID_XMLList;		// public::XMLList
	const uint32_t ID_children;		// public::children
	const uint32_t ID_length;		// public::length
#ifdef DEBUG
	const uint32_t ID_print;		// public::print
#endif
	const uint32_t NSS_public;		// [public]
	const uint32_t MNL_public;		// [public]::<>
	const uint32_t MNL_public_attr;	// [public]::<> for @attr names
};
