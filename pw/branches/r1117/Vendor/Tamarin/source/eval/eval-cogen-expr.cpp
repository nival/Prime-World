/* -*- tab-width: 4 -*- */
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

namespace avmplus
{
	namespace RTC
	{
		using namespace ActionBlockConstants;
		
		// Abstracts the name computation.  For stack allocation.
		
		class Name {
		public:
			Name(Cogen* cogen, Expr* expr, bool strict);
			Name(Cogen* cogen, QualifiedName* name);
			~Name();
			
			void setup();
			
			Cogen * const cogen;
			uint32_t nsreg;
			uint32_t namereg;
			uint32_t sym;

		private:
			void computeName(QualifiedName* qname);
		};

		// Compute the base object (on the stack) and the name information.
		Name::Name(Cogen* cogen, Expr* expr, bool strict)
			: cogen(cogen)
			, nsreg(0)
			, namereg(0)
		{
			Tag tag = expr->tag();
			AvmAssert( tag == TAG_objectRef || tag == TAG_qualifiedName );
			if (tag == TAG_objectRef)
				((ObjectRef*)expr)->obj->cogen(cogen);
			computeName(tag == TAG_objectRef ? ((ObjectRef*)expr)->name : (QualifiedName*)expr);
			if (tag == TAG_qualifiedName) {
				if (strict)
					cogen->I_findpropstrict(sym);
				else
					cogen->I_findproperty(sym);
			}
		}

		// Compute the name information.
		Name::Name(Cogen* cogen, QualifiedName* qname)
			: cogen(cogen)
			, nsreg(0)
			, namereg(0)
		{
			computeName(qname);
		}
		
		// Significant performance improvements for qualified names if the namespace can be resolved at compile time.
		// See notes in the implementation of the 'namespace' definition; the machinery has to be implemented for
		// 'use default namespace' in any case.

		void Name::computeName(QualifiedName* qname)
		{
			Compiler* compiler = cogen->compiler;
			bool ns_wildcard = false;
			if (qname->qualifier != NULL) {
				switch (qname->qualifier->tag()) {
					case TAG_simpleName: {
						uint32_t id = cogen->abc->addQName(compiler->NS_public, 
														   cogen->emitString(((SimpleName*)(qname->qualifier))->name),
														   false);
						nsreg = cogen->getTemp();
						cogen->I_findpropstrict(id);
						cogen->I_getproperty(id);
						cogen->I_coerce(compiler->ID_Namespace);
						cogen->I_setlocal(nsreg);
						break;
					}
					case TAG_wildcardName:
						ns_wildcard = true;
						break;
					default:
						compiler->internalError(qname->pos, "QName qualifiers can't be computed names");
				}
			}
			NameComponent* name = qname->name;
			switch (name->tag()) {
				case TAG_simpleName:
					if (nsreg != 0) {
						AvmAssert(!ns_wildcard);
						sym = cogen->abc->addRTQName(cogen->emitString(((SimpleName*)name)->name),
													 qname->is_attr);
					}
					else
						sym = cogen->abc->addQName((ns_wildcard ? 0 : compiler->NS_public), 
												   cogen->emitString(((SimpleName*)name)->name),
												   qname->is_attr);
					break;
				case TAG_wildcardName:
					if (nsreg != 0)
						sym = cogen->abc->addRTQName(0, qname->is_attr);
					else
						sym = cogen->abc->addMultiname(compiler->NSS_public, 0, qname->is_attr);
					break;
				case TAG_computedName:
					if (ns_wildcard)
						compiler->syntaxError(qname->pos, "Illegal qualified name");
					namereg = cogen->getTemp();
					((ComputedName*)name)->expr->cogen(cogen);
					cogen->I_setlocal(namereg);
					if (nsreg != 0)
						sym = cogen->abc->addRTQNameL(qname->is_attr);
					else {
						if (qname->is_attr)
							sym = compiler->MNL_public_attr;
						else
							sym = compiler->MNL_public;
					}
					break;
			}
		}
		
		Name::~Name()
		{
			if (nsreg != 0) cogen->I_kill(nsreg);
			if (namereg != 0) cogen->I_kill(namereg);
		}
		
		void Name::setup()
		{
			if (nsreg)
				cogen->I_getlocal(nsreg);
			if (namereg)
				cogen->I_getlocal(namereg);
		}
		
		void QualifiedName::cogen(Cogen* cogen)
		{
			Name n(cogen, this);
			n.setup();
			cogen->I_findpropstrict(n.sym);
			n.setup();
			cogen->I_getproperty(n.sym);
		}
		
		void ObjectRef::cogen(Cogen* cogen)
		{
			obj->cogen(cogen);
			if ((name->qualifier == NULL || name->qualifier->tag() == TAG_wildcardName) && name->name->tag() == TAG_wildcardName && !name->is_attr)
				cogen->I_callproperty(cogen->compiler->ID_children, 0);
			else {
				Name n(cogen, name);
				n.setup();
				cogen->I_getproperty(n.sym);
			}
		}
		
		void RefLocalExpr::cogen(Cogen* cogen)
		{
			cogen->I_getlocal(local);
		}

		void ConditionalExpr::cogen(Cogen* cogen)
		{
			Label* L0 = cogen->newLabel();
			Label* L1 = cogen->newLabel();
			
			e1->cogen(cogen);
			cogen->I_iffalse(L0);
			e2->cogen(cogen);
			cogen->I_coerce_a();
			cogen->I_jump(L1);
			cogen->I_label(L0);
			e3->cogen(cogen);
			cogen->I_coerce_a();
			cogen->I_label(L1);
		}

		void AssignExpr::cogen(Cogen* cogen)
		{
			AvmAssert( lhs->tag() == TAG_objectRef || lhs->tag() == TAG_qualifiedName );

			// Compute the object onto the stack, and elements of the name into locals if necessary
			bool is_assign = op == OPR_assign || op == OPR_init;
			Name n(cogen, lhs, !is_assign);

			// Read the value if we need it
			if (!is_assign) {
				cogen->I_dup();
				n.setup();
				cogen->I_getproperty(n.sym);
			}
			
			// Compute the rhs
			rhs->cogen(cogen);
			
			// Compute the operator if we need it
			if (!is_assign) {
				bool isNegated;
				cogen->I_opcode(cogen->binopToOpcode(op, &isNegated));
				if (isNegated)
					cogen->I_not();
			}
			
			// Perform the update and generate the result
			uint32_t t = cogen->getTemp();
			cogen->I_setlocal(t);
			n.setup();
			cogen->I_getlocal(t);
			if (op == OPR_assign)
				cogen->I_setproperty(n.sym);
			else
				cogen->I_initproperty(n.sym);
			cogen->I_getlocal(t);
			cogen->I_kill(t);
		}

		void BinaryExpr::cogen(Cogen* cogen)
		{
			if (op == OPR_logicalAnd) {
				Label* L0 = cogen->newLabel();
				
				lhs->cogen(cogen);
				cogen->I_coerce_a();  // wrong, should coerce to LUB of lhs and rhs
				cogen->I_dup();
				cogen->I_coerce_b();
				cogen->I_iffalse(L0);
				cogen->I_pop();
				rhs->cogen(cogen);
				cogen->I_coerce_a();  // wrong, should coerce to LUB of lhs and rhs
				cogen->I_label(L0);
			}
			else if (op == OPR_logicalOr) {
				Label* L0 = cogen->newLabel();
				
				lhs->cogen(cogen);
				cogen->I_coerce_a();  // wrong, should coerce to LUB of lhs and rhs
				cogen->I_dup();
				cogen->I_coerce_b();
				cogen->I_iftrue(L0);
				cogen->I_pop();
				rhs->cogen(cogen);
				cogen->I_coerce_a();  // wrong, should coerce to LUB of lhs and rhs
				cogen->I_label(L0);
			}
			else if (op == OPR_comma) {
				lhs->cogen(cogen);
				cogen->I_pop();
				rhs->cogen(cogen);
			}
			else {
				lhs->cogen(cogen);
				rhs->cogen(cogen);
				bool isNegated;
				cogen->I_opcode(cogen->binopToOpcode(op, &isNegated));
				if (isNegated)
					cogen->I_not();
			}
		}

		void UnaryExpr::cogen(Cogen* cogen)
		{
			Compiler* compiler = cogen->compiler;
			switch (op) {
				case OPR_delete: {
					if (expr->tag() == TAG_qualifiedName || expr->tag() == TAG_objectRef) {
						Name n(cogen, expr, false);
						n.setup();
						cogen->I_deleteproperty(n.sym);
					}
					else {
						// FIXME: e4x requires that if the value computed here is an XMLList then a TypeError (ID 1119) is thrown.
						expr->cogen(cogen);
						cogen->I_pop();
						cogen->I_pushtrue();
					}
					break;
				}
					
				case OPR_void:
					expr->cogen(cogen);
					cogen->I_pop();
					cogen->I_pushundefined();
					break;

				case OPR_typeof:
					if (expr->tag() == TAG_qualifiedName) {
						Name n(cogen, (QualifiedName*)expr);
						n.setup();
						cogen->I_findproperty(n.sym);
						n.setup();
						cogen->I_getproperty(n.sym);
					}
					else 
						expr->cogen(cogen);
					cogen->I_typeof();
					break;

				case OPR_preIncr: 
					incdec(cogen, true, true); 
					break;
					
				case OPR_preDecr: 
					incdec(cogen, true, false); 
					break;
					
				case OPR_postIncr: 
					incdec(cogen, false, true); 
					break;
					
				case OPR_postDecr: 
					incdec(cogen, false, false); 
					break;
					
				case OPR_unplus:
					expr->cogen(cogen);
					cogen->I_coerce_d();
					break;
					
				case OPR_unminus:
					expr->cogen(cogen);
					cogen->I_negate();
					break;
					
				case OPR_bitwiseNot:
					expr->cogen(cogen);
					cogen->I_bitnot();
					break;
					
				case OPR_not:
					expr->cogen(cogen);
					cogen->I_not();
					break;
					
				default:
					compiler->internalError(pos, "Unimplemented unary operation");
			}
		}
		
		void UnaryExpr::incdec(Cogen* cogen, bool pre, bool inc)
		{
			Name n(cogen, expr, true);
			cogen->I_dup();
			n.setup();
			cogen->I_getproperty(n.sym);

			uint32_t t = cogen->getTemp();

			if (pre) {
				if (inc)
					cogen->I_increment();
				else
					cogen->I_decrement();
				cogen->I_dup();
				cogen->I_setlocal(t);
			}
			else {
				// Postfix ops return value after conversion to number.
				cogen->I_coerce_d();
				cogen->I_dup();
				cogen->I_setlocal(t);
				if (inc)
					cogen->I_increment();
				else
					cogen->I_decrement();
			}

			n.setup();
			cogen->I_setproperty(n.sym);

			cogen->I_getlocal(t);
			cogen->I_kill(t);
		}
		
		void ThisExpr::cogen(Cogen* cogen)
		{
			cogen->I_getlocal(0);
		}
		
		void LiteralFunction::cogen(Cogen* cogen)
		{
			if (function->name != NULL) {
				// For a named function expression F with name N, create a new 
				// expression (function() { F; return N })() and generate code
				// for that instead.  Note that F then becomes a local function
				// definition.
				Allocator* allocator = cogen->allocator;
				Expr* e = ALLOC(CallExpr, 
								(ALLOC(LiteralFunction, 
									   (ALLOC(FunctionDefn, 
											  (NULL, 
											   ALLOC(Seq<Binding*>, 
													 (ALLOC(Binding, 
															(function->name, NULL, TAG_varBinding)))), 
											   NULL, 
											   0,
											   NULL,
											   NULL,
											   ALLOC(Seq<FunctionDefn*>, 
													 (function)), 
											   NULL, 
											   ALLOC(Seq<Stmt*>, 
													 (ALLOC(ReturnStmt, 
															(0, ALLOC(QualifiedName, 
																	  (NULL, ALLOC(SimpleName, 
																				   (function->name)),
																	   false,
																	   0)))))),
											  false,
											  false,
											  false)))),
								 NULL,
								 0));
				e->cogen(cogen);
			}
			else {
				ABCMethodInfo* fn_info;
				ABCMethodBodyInfo* fn_body;
				function->cogenGuts(cogen->compiler, &fn_info, &fn_body);
				cogen->I_newfunction(fn_info->index);
			}
		}

		void LiteralObject::cogen(Cogen* cogen)
		{
			uint32_t i=0;
			for ( Seq<LiteralField*>* fields = this->fields ; fields != NULL ; fields = fields->tl ) {
				cogen->I_pushstring(cogen->emitString(fields->hd->name));
				fields->hd->value->cogen(cogen);
				i++;
			}
			cogen->I_newobject(i);
		}
		
		void LiteralArray::cogen(Cogen* cogen)
		{
			uint32_t i = 0;
			Seq<Expr*>* exprs = elements;
			Compiler* compiler = cogen->compiler;
			
			// Use newarray to construct the dense prefix
			for ( ; exprs != NULL ; exprs = exprs->tl ) {
				Expr* e = exprs->hd;
				if (e == NULL)
					break;
				e->cogen(cogen);
				i++;
			}
			cogen->I_newarray(i);
			
			// Then init the other defined slots one by one
			if (exprs != NULL) {
				bool last_was_undefined = false;
				for ( ; exprs != NULL ; exprs = exprs->tl, i++ ) {
					Expr* e = exprs->hd;
					if (e != NULL) {
						cogen->I_dup();
						e->cogen(cogen);
						cogen->I_setproperty(cogen->abc->addQName(compiler->NS_public,cogen->emitString(compiler->intern(i))));
						last_was_undefined = false;
					}
					else
						last_was_undefined = true;
				}
				if (last_was_undefined) {
					cogen->I_dup();
					cogen->I_pushint(cogen->emitInt(i));
					cogen->I_setproperty(compiler->ID_length);
				}
			}
		}

		void LiteralRegExp::cogen(Cogen* cogen)
		{
			Compiler* compiler = cogen->compiler;
			
			// value is "/.../flags"
			//
			// OPTIMIZEME: silly to recompile the regular expression every time it's evaluated, even if
			// ES3.1 allows it (not sure what AS3 allows / requires; ES3 requires compilation once).
			const wchar* s = value->s;
			const wchar* t = s + value->length - 1;
			while (*t != '/')
				t--;
			
			// FIXME: semantics: creating a new RegExp object every time is not compatible with ES3
			//
			// FIXME: semantics: findpropstrict(""::RegExp) is not quite right here.
			// Doing so creates a spoofing hole / surprising trap.  We want an OP_newregexp instruction.
			cogen->I_findpropstrict(compiler->ID_RegExp);
			cogen->I_pushstring(cogen->emitString(compiler->intern(s+1, uint32_t(t-s-1))));
			cogen->I_pushstring(cogen->emitString(compiler->intern(t+1, uint32_t(value->length-(t-s+1)))));
			cogen->I_constructprop(compiler->ID_RegExp, 2);
		}

		void LiteralNull::cogen(Cogen* cogen)
		{
			cogen->I_pushnull();
		}
		
		void LiteralUndefined::cogen(Cogen* cogen)
		{
			cogen->I_pushundefined();
		}
		
		void LiteralInt::cogen(Cogen* cogen)
		{
			if (value >= -128 && value < 128)
				cogen->I_pushbyte((uint8_t)(value & 0xFF));
			else
				cogen->I_pushint(cogen->emitInt(value));
		}

		void LiteralUInt::cogen(Cogen* cogen)
		{
			if (value < 128)
				cogen->I_pushbyte((uint8_t)(value & 0xFF));
			else
				cogen->I_pushuint(cogen->emitUInt(value));
		}
		
		void LiteralDouble::cogen(Cogen* cogen)
		{
			if (MathUtils::isNaN(value))
				cogen->I_pushnan();
			else
				cogen->I_pushdouble(cogen->emitDouble(value));
		}
			
		void LiteralBoolean::cogen(Cogen* cogen)
		{
			if (value)
				cogen->I_pushtrue();
			else
				cogen->I_pushfalse();
		}

		void LiteralString::cogen(Cogen* cogen)
		{
			cogen->I_pushstring(cogen->emitString(value));
		}

		uint32_t Cogen::arguments(Seq<Expr*>* args)
		{
			uint32_t i = 0;
			for ( ; args != NULL ; args = args->tl, i++ )
				args->hd->cogen(this);
			return i;
		}

		void CallExpr::cogen(Cogen* cogen)
		{
			switch (fn->tag()) {
				case TAG_qualifiedName: {
					Name n(cogen, fn, true);
					n.setup();
					cogen->I_callproplex(n.sym, cogen->arguments(arguments));
					break;
				}
				case TAG_objectRef: {
					Name n(cogen, fn, false);
					n.setup();
					cogen->I_callproperty(n.sym, cogen->arguments(arguments));
					break;
				}
				default:
					fn->cogen(cogen);
					cogen->I_pushnull();
					cogen->I_call(cogen->arguments(arguments));
			}
		}

		void NewExpr::cogen(Cogen* cogen)
		{
			fn->cogen(cogen);
			cogen->I_construct(cogen->arguments(arguments));
		}

		void XmlInitializer::cogen(Cogen* cogen)
		{
			Compiler* compiler = cogen->compiler;
			uint32_t id = is_list ? compiler->ID_XMLList : compiler->ID_XML;
			
			cogen->I_findpropstrict(id);
			cogen->I_getproperty(id);
			cogen->I_pushstring(cogen->emitString(compiler->SYM_));
			for ( Seq<Expr*>* exprs = this->exprs ; exprs != NULL ; exprs = exprs->tl ) {
				exprs->hd->cogen(cogen);
				cogen->I_convert_s();
				cogen->I_add();
			}
#if 0 && defined DEBUG
			cogen->I_dup();
			cogen->I_findpropstrict(compiler->ID_print);
			cogen->I_swap();
			cogen->I_callpropvoid(compiler->ID_print, 1);
#endif
			cogen->I_construct(1);
		}
		
		void EscapeExpr::cogen(Cogen* cogen)
		{
			expr->cogen(cogen);
			switch (esc) {
				case ESC_attributeValue:
					cogen->I_esc_xattr();
					break;
				case ESC_elementValue:
					cogen->I_esc_xelem();
					break;
				default:
					break;
			}
		}

		// OPTIMIZEME?  A more space-conserving method would be to pass a predicate
		// and an object to a common filter function.  But it only makes a difference
		// if filter expressions are very common, and they probably aren't.
		
		void FilterExpr::cogen(Cogen* cogen)
		{
			Compiler* compiler = cogen->compiler;
			uint32_t t_xmllist = cogen->getTemp();
			uint32_t t_length = cogen->getTemp();
			uint32_t t_result = cogen->getTemp();
			uint32_t t_result_index = cogen->getTemp();
			uint32_t t_index = cogen->getTemp();
			uint32_t t_scope = cogen->getTemp();
			uint32_t t_item = cogen->getTemp();
			Label* L_again = cogen->newLabel();
			Label* L_skip = cogen->newLabel();
			Label* L_done = cogen->newLabel();

			obj->cogen(cogen);
			cogen->I_checkfilter();

			// convert to XMLList
			cogen->I_coerce_a();
			cogen->I_setlocal(t_xmllist);
			cogen->I_findpropstrict(compiler->ID_XMLList);
			cogen->I_getproperty(compiler->ID_XMLList);
			cogen->I_pushnull();
			cogen->I_getlocal(t_xmllist);
			cogen->I_call(1);
			cogen->I_coerce_a();
			cogen->I_setlocal(t_xmllist);
			
			// get the length of the list and save it
			cogen->I_getlocal(t_xmllist);
			cogen->I_callproperty(compiler->ID_length, 0);
			cogen->I_coerce_a();
			cogen->I_setlocal(t_length);
			
			// create a new, empty list for the result
			cogen->I_findpropstrict(compiler->ID_XMLList);
			cogen->I_getproperty(compiler->ID_XMLList);
			cogen->I_construct(0);
			cogen->I_coerce_a();
			cogen->I_setlocal(t_result);
			cogen->I_pushbyte(0);
			cogen->I_setlocal(t_result_index);
			
			// set up loop
			cogen->I_pushbyte(0);
			cogen->I_setlocal(t_index);
			
			// iterate across the list
			cogen->I_label(L_again);
			
			// while index < length
			cogen->I_getlocal(t_index);
			cogen->I_getlocal(t_length);
			cogen->I_ifge(L_done);
			
			// item := list[index]
			cogen->I_getlocal(t_xmllist);
			cogen->I_getlocal(t_index);
			cogen->I_getproperty(compiler->MNL_public);
			cogen->I_coerce_a();
			cogen->I_setlocal(t_item);
			
			// with (item) b := <filter>
			cogen->I_getlocal(t_item);
			cogen->I_pushwith();
			filter->cogen(cogen);
			cogen->I_popscope();
			
			// if b result += item
			cogen->I_iffalse(L_skip);
			// Add it
			cogen->I_getlocal(t_result);
			cogen->I_getlocal(t_result_index);
			cogen->I_getlocal(t_item);
			cogen->I_setproperty(compiler->MNL_public);
			cogen->I_inclocal_i(t_result_index);
			
			cogen->I_label(L_skip);
			
			// index++;
			cogen->I_inclocal_i(t_index);
			cogen->I_jump(L_again);
			
			// post-loop
			cogen->I_label(L_done);
			cogen->I_getlocal(t_result);
			cogen->I_kill(t_xmllist);
			cogen->I_kill(t_length);
			cogen->I_kill(t_result);
			cogen->I_kill(t_result_index);
			cogen->I_kill(t_index);
			cogen->I_kill(t_scope);
			cogen->I_kill(t_item);
		}
		
		void DescendantsExpr::cogen(Cogen* cogen)
		{
			obj->cogen(cogen);
			Name n(cogen, name);
			n.setup();
			cogen->I_getdescendants(n.sym);
		}
	}
}

#endif // VMCFG_EVAL
