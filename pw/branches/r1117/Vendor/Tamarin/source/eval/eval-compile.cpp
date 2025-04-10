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

#include "avmplus.h"

#ifdef VMCFG_EVAL

#include "eval.h"
#ifdef _MSC_VER
#  define snprintf _snprintf
#endif

namespace avmplus
{
	namespace RTC
	{

		// Assume that the number of unique identifiers in a program is roughly the square root
		// of the raw length of the program.  Needs experimental verification.  May only be
		// true for programs above a certain size; may want a lower limit on the table size.
		//
		// Using this "arbitrary" value for k we have to use mod when computing the hash bucket
		// when interning.  Faster would be to round k up to a power of 2, then use k-1 as a
		// mask in intern().

		static Str** makeStrTable(Allocator* allocator, uint32_t tableSize)
		{
			Str** strTable = (Str**)allocator->alloc(sizeof(Str*) * tableSize);
			for ( uint32_t i=0 ; i < tableSize ; i++ )
				strTable[i] = NULL;
			return strTable;
		}

		static const wchar default_filename[] = { '(', 'e', 'v', 'a', 'l', ' ', 's', 't', 'r', 'i', 'n', 'g', ')', 0 };
		
		Compiler::Compiler(HostContext* context, const wchar* filename, const wchar* src, uint32_t srclen)
			: context(context)
			, allocator(new Allocator(this))
			, filename(filename != NULL ? filename : default_filename)
			, tableSize(uint32_t(sqrt((double)srclen)))
			, es3_keywords(false)		// ActionScript: false
			, liberal_idents(true)		// ActionScript: true
			, local_functions(true)		// ActionScript: true
			, octal_literals(false)		// ActionScript: false
			, origin_is_file(filename != NULL)
			, debugging(true)
			, namespace_counter(1)
			, strTable(makeStrTable(allocator, tableSize))
			, lexer(this, src, srclen)
			, parser(this, &lexer)
			, abc(this)
			, SYM_(intern(""))
			, SYM_Array(intern("Array"))
			, SYM_Namespace(intern("Namespace"))
			, SYM_Object(intern("Object"))
			, SYM_RegExp(intern("RegExp"))
			, SYM_XML(intern("XML"))
			, SYM_XMLList(intern("XMLList"))
			, SYM_anonymous(intern("anonymous"))
			, SYM_arguments(intern("arguments"))
			, SYM_children(intern("children"))
			, SYM_each(intern("each"))
			, SYM_get(intern("get"))
			, SYM_include(intern("include"))
			, SYM_length(intern("length"))
			, SYM_namespace(intern("namespace"))
#ifdef DEBUG
			, SYM_print(intern("print"))
#endif
			, SYM_prototype(intern("prototype"))
			, SYM_set(intern("set"))
			, SYM_static(intern("static"))
			, SYM_to(intern("to"))
			, SYM_use(intern("use"))
			, SYM_xml(intern("xml"))
			, str_filename(intern(this->filename, NULL))
			, NS_public(abc.addNamespace(CONSTANT_Namespace, abc.addString(SYM_)))
			, ID_Array(abc.addQName(NS_public, abc.addString(SYM_Array)))
			, ID_Namespace(abc.addQName(NS_public, abc.addString(SYM_Namespace)))
			, ID_Object(abc.addQName(NS_public, abc.addString(SYM_Object)))
			, ID_RegExp(abc.addQName(NS_public, abc.addString(SYM_RegExp)))
			, ID_XML(abc.addQName(NS_public, abc.addString(SYM_XML)))
			, ID_XMLList(abc.addQName(NS_public, abc.addString(SYM_XMLList)))
			, ID_children(abc.addQName(NS_public, abc.addString(SYM_children)))
			, ID_length(abc.addQName(NS_public, abc.addString(SYM_length)))
#ifdef DEBUG
			, ID_print(abc.addQName(NS_public, abc.addString(SYM_print)))
#endif
			, NSS_public(abc.addNsset(ALLOC(Seq<uint32_t>, (NS_public))))
			, MNL_public(abc.addMultinameL(NSS_public, false))
			, MNL_public_attr(abc.addMultinameL(NSS_public, true))
		{
		}

		void Compiler::destroy()
		{
			delete allocator;
		}

		void Compiler::compile()
		{
#if 0 && defined DEBUG
			lexer.trace();
#endif
			Program* program = parser.parse();

			ABCTraitsTable* global_traits = ALLOC(ABCTraitsTable, (this));
			ABCMethodInfo* global_info = ALLOC(ABCMethodInfo, (this, abc.addString("script$init"), 0, NULL, 0));
			ABCMethodBodyInfo* global_body = ALLOC(ABCMethodBodyInfo, (this, global_info, global_traits, 1));
			program->cogen(&global_body->cogen);
			global_info->setFlags(global_body->getFlags() | MethodInfo::SETS_DXNS);

			ALLOC(ABCScriptInfo, (this, global_info, global_traits));

			global_body->clearTraits();		// the traits belong to the script, so don't emit them with the body too
			
			abc.serialize(context->obtainStorageForResult(abc.size()));
		}

		void Compiler::internalError(uint32_t lineno, const char* fmt, ...)
		{
			char buf[500];
			char lbuf[12];
			if (lineno != 0)
				sprintf(lbuf, "%d", lineno);
			else
				strcpy(lbuf, "Unknown");
			{
				char fbuf[500];
				formatUtf8(fbuf, sizeof(fbuf), filename);
				snprintf(buf, sizeof(buf), "%s:%s: Internal error: ", fbuf, lbuf);
				buf[sizeof(buf)-1] = 0;
			}
			int k = int(strlen(buf));
			va_list args;
			va_start(args,fmt);
			vsnprintf(buf+k, sizeof(buf)-k, fmt, args);
			va_end(args);
			
			context->throwInternalError(buf);
		}
		
		void Compiler::syntaxError(uint32_t lineno, const char* fmt, ...)
		{
			char buf[500];
			char lbuf[12];
			if (lineno != 0)
				sprintf(lbuf, "%d", lineno);
			else
				strcpy(lbuf, "Unknown");
			{
				char fbuf[500];
				formatUtf8(fbuf, sizeof(fbuf), filename);
				snprintf(buf, sizeof(buf), "%s:%s: Syntax error: ", fbuf, lbuf);
				buf[sizeof(buf)-1] = 0;
			}
			int k = int(strlen(buf));
			va_list args;
			va_start(args,fmt);
			vsnprintf(buf+k, sizeof(buf)-k, fmt, args);
			va_end(args);
			
			context->throwSyntaxError(buf);
		}
		
		Str* Compiler::intern(const char* s)
		{
			StringBuilder b(this);
			b.append(s);
			return b.str();
		}

		Str* Compiler::intern(uint32_t u)
		{
			wchar buf[12];
			uint32_t i = 0;
			if (u == 0)
				buf[i++] = '0';
			else {
				while (u != 0) {
					buf[i++] = '0' + (u % 10);
					u /= 10;
				}
				for ( uint32_t j=0, k=i-1 ; j < k ; j++, k-- ) {
					wchar c = buf[j];
					buf[j] = buf[k];
					buf[k] = c;
				}
			}
			return intern(buf, i);
		}

		Str* Compiler::intern(const wchar* chars, uint32_t nchars)
		{
			// '%' may not be the best here, see comment above about how to speed it up
			// if it turns out to be a bottleneck.
			
			uint32_t h = hashString(chars, nchars) % tableSize;
			for ( Str* p = strTable[h] ; p != NULL ; p = p->next ) {
				if (p->hash == h) 
					if (p->length == nchars)
						if (memcmp(p->s, chars, sizeof(wchar)*nchars) == 0)
							return p;
			}

			// The string is not known yet

			Str* str = (Str*)allocator->alloc(sizeof(Str) + sizeof(wchar)*(nchars - 1 + 1));	// -1 for the elt in Str, +1 for the NUL
			memcpy(str->s, chars, sizeof(wchar)*nchars);
			str->s[nchars] = 0;
			str->hash = h;
			str->ident = ~0U;
			str->next = strTable[h];
			str->length = nchars;
			strTable[h] = str;
#if 0 && defined DEBUG
			char buf[200];
			printf(">>> Interning: %s\n", getn(buf, str, sizeof(buf)));
#endif
			return str;
		}
	}
}

#endif // VMCFG_EVAL
