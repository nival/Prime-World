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
		
		/*
		 static const struct TokenMapping {
			 unsigned isOpAssign:1;
			 unsigned isMultiplicative:1;
			 unsigned isAdditive:1;
			 unsigned isRelational:1;
			 unsigned isEquality:1;
			 unsigned isShift:1;
			 unsigned unaryOp:8;
			 unsigned binaryOp:8;
		 };
		 */
		const Parser::TokenMapping Parser::tokenMapping[] = {
		{ 0, 0, 0, 0, 0, 0, 0,              OPR_as },           // T_As
		{ 0, 0, 0, 0, 0, 0, 0,              OPR_assign },       // T_Assign,
		{ 0, 0, 0, 0, 0, 0, 0,              OPR_bitwiseAnd },   // T_BitwiseAnd,
		{ 1, 0, 0, 0, 0, 0, 0,              OPR_bitwiseAnd },   // T_BitwiseAndAssign,
		{ 0, 0, 0, 0, 0, 0, OPR_bitwiseNot, 0 },                // T_BitwiseNot,
		{ 0, 0, 0, 0, 0, 0, 0,              OPR_bitwiseOr },    // T_BitwiseOr,
		{ 1, 0, 0, 0, 0, 0, 0,              OPR_bitwiseOr },    // T_BitwiseOrAssign,
		{ 0, 0, 0, 0, 0, 0, 0,              OPR_bitwiseXor },   // T_BitwiseXor,
		{ 1, 0, 0, 0, 0, 0, 0,              OPR_bitwiseXor },   // T_BitwiseXorAssign,
		{ 0, 0, 0, 0, 0, 0, OPR_delete,     0 },                // T_Delete,
		{ 0, 1, 0, 0, 0, 0, 0,              OPR_divide },       // T_Divide,
		{ 1, 0, 0, 0, 0, 0, 0,              OPR_divide },       // T_DivideAssign,
		{ 0, 0, 0, 0, 1, 0, 0,              OPR_equal },        // T_Equal,
		{ 0, 0, 0, 1, 0, 0, 0,              OPR_greater },      // T_GreaterThan,
		{ 0, 0, 0, 1, 0, 0, 0,              OPR_greaterOrEqual }, // T_GreaterThanOrEqual,
		{ 0, 0, 0, 1, 0, 0, 0,              OPR_in },           // T_In,
		{ 0, 0, 0, 1, 0, 0, 0,              OPR_instanceof },   // T_InstanceOf,
		{ 0, 0, 0, 1, 0, 0, 0,              OPR_is },           // T_Is,
		{ 0, 0, 0, 0, 0, 1, 0,              OPR_leftShift },    // T_LeftShift,
		{ 1, 0, 0, 0, 0, 0, 0,              OPR_leftShift },    // T_LeftShiftAssign,
		{ 0, 0, 0, 1, 0, 0, 0,              OPR_less },         // T_LessThan,
		{ 0, 0, 0, 1, 0, 0, 0,              OPR_lessOrEqual },  // T_LessThanOrEqual,
		{ 0, 0, 0, 0, 0, 0, 0,              OPR_logicalAnd },   // T_LogicalAnd,
		{ 1, 0, 0, 0, 0, 0, 0,              OPR_logicalAnd },   // T_LogicalAndAssign,
		{ 0, 0, 0, 0, 0, 0, 0,              OPR_logicalOr },    // T_LogicalOr,
		{ 1, 0, 0, 0, 0, 0, 0,              OPR_logicalOr },    // T_LogicalOrAssign,
		{ 0, 0, 1, 0, 0, 0, OPR_unminus,    OPR_minus },        // T_Minus,
		{ 1, 0, 0, 0, 0, 0, 0,              OPR_minus },        // T_MinusAssign,
		{ 0, 0, 0, 0, 0, 0, OPR_preDecr,    OPR_postDecr },     // T_MinusMinus, note binop slot encodes postfix form
		{ 0, 1, 0, 0, 0, 0, 0,              OPR_multiply },     // T_Multiply,
		{ 1, 0, 0, 0, 0, 0, 0,              OPR_multiply },     // T_MultiplyAssign,
		{ 0, 0, 0, 0, 0, 0, OPR_not,        0 },                // T_Not,
		{ 0, 0, 0, 0, 1, 0, 0,              OPR_notEqual },     // T_NotEqual,
		{ 0, 0, 1, 0, 0, 0, OPR_unplus,     OPR_plus },         // T_Plus,
		{ 1, 0, 0, 0, 0, 0, 0,              OPR_plus },         // T_PlusAssign,
		{ 0, 0, 0, 0, 0, 0, OPR_preIncr,    OPR_postIncr },     // T_PlusPlus, note binop slot encodes postfix form
		{ 0, 1, 0, 0, 0, 0, 0,              OPR_remainder },    // T_Remainder,
		{ 1, 0, 0, 0, 0, 0, 0,              OPR_remainder },    // T_RemainderAssign,
		{ 0, 0, 0, 0, 0, 1, 0,              OPR_rightShift },   // T_RightShift,
		{ 1, 0, 0, 0, 0, 0, 0,              OPR_rightShift },   // T_RightShiftAssign,
		{ 0, 0, 0, 0, 1, 0, 0,              OPR_strictEqual },  // T_StrictEqual,
		{ 0, 0, 0, 0, 1, 0, 0,              OPR_strictNotEqual }, // T_StrictNotEqual,
		{ 0, 0, 0, 0, 0, 0, 0,              OPR_to },           // T_To
		{ 0, 0, 0, 0, 0, 0, OPR_typeof,     0 },                // T_TypeOf,
		{ 0, 0, 0, 0, 1, 0, 0,              OPR_rightShiftUnsigned }, // T_UnsignedRightShift,
		{ 1, 0, 0, 0, 0, 0, 0,              OPR_rightShiftUnsigned }, // T_UnsignedRightShiftAssign,
		{ 0, 0, 0, 0, 0, 0, OPR_void,       0 }                 // T_Void,
		};

		Parser::BindingRib::BindingRib(Allocator* allocator, BindingRib* next, RibType tag)
			: bindings(allocator)
			, functionDefinitions(allocator)
			, namespaces(allocator)
			, tag(tag)
			, uses_finally(false)
			, uses_catch(false)
			, uses_arguments(false)
			, uses_dxns(false)
			, is_void(false)
			, optional_arguments(false)
			, next(next)
		{
		}

		Parser::Parser(Compiler* compiler, Lexer* lexer, uint32_t first_line) 
			: compiler(compiler)
			, allocator(compiler->allocator)
			, line_offset(first_line-1)
			, topRib(NULL)
			, lexerStack(NULL)
			, lexer(lexer)
			, T0(T_LAST)
			, T1(T_LAST)
			, LP(0)
			, L0(0)
			, L1(0)
			, included_input(NULL)
		{
		}
		
		Program* Parser::parse()
		{
			start();
			return program();
		}
		
		/*
		 * <program> ::= <package>* <directive>*
		 */
		Program* Parser::program()
		{
			pushBindingRib(RIB_Program);
			while (hd() == T_Package) 
				package();
			Seq<Stmt*>* stmts = directives(SFLAG_Toplevel);
			Program* prog = ALLOC(Program, (topRib->bindings.get(), topRib->functionDefinitions.get(), topRib->namespaces.get(), stmts));
			popBindingRib();
			return prog;
		}
		
		// FIXME: must open the package namespaces inside the package
		// FIXME: must record the package name as a compound name prefix inside the package
		// FIXME: must record that we're inside a package so that namespace qualifiers can be checked
		void Parser::package()
		{
			SeqBuilder<Str*> name(allocator);
			eat(T_Package);
			while (hd() == T_Identifier) {
				name.addAtEnd(identValue());
				eat(T_Identifier);
				if (!match(T_Dot))
					break;
			}
			eat(T_LeftBrace);
			directives(SFLAG_Package);
			eat(T_RightBrace);
		}
		
		// This checks that a directive is only used where allowed.
		//
		// This also checks constraints between qualifier and directive: no "native class",
		// "native interface", and so on.  It avoids redundant checks with namespaceQualifier(),
		// so does not check for "prototype class", which cannot occur (prototype is only
		// recognized inside a class, but "class" is not allowed there).
		//
		// There is a language absurdity here; since "prototype" is a syntactic identifier
		// it may be defined as the name of a namespace, and that namespace may possibly be
		// used to qualify a definition that will look like, but not be, a prototype
		// property.
		
		Seq<Stmt*>* Parser::directives(int flags, Seq<Stmt*>** out_instance_init)
		{
			(void)out_instance_init;
			SeqBuilder<Stmt*> stmts(allocator);		// In a class body, this is also the class_init
			Qualifier qual;
			while (hd() != T_RightBrace && hd() != T_EOS) {
				switch (hd())
				{
					case T_Native:
					case T_Private:
					case T_Protected:
					case T_Public:
					case T_Internal:
					case T_Identifier:
						if (flags & SFLAG_Interface)
							compiler->syntaxError(position(), "Qualifier not allowed here");
						if (namespaceQualifier(flags, &qual))
							break;

						AvmAssert(hd() == T_Identifier);

						if (identValue() == compiler->SYM_include && hd2() == T_StringLiteral && L0 == L1) {
							if (qual.tag != QUAL_none || qual.is_native || qual.is_static || qual.is_prototype)
								compiler->syntaxError(position(), "Illegal 'include' directive");
							includeDirective();
						}
						else if (hd() == T_Identifier && identValue() == compiler->SYM_namespace) {
							if (qual.is_native || qual.is_static || qual.is_prototype)
								compiler->syntaxError(position(), "Illegal 'namespace' directive");
							namespaceDefinition(flags, &qual);
						}
						else
							goto default_case;
						break;
						
					case T_Const:
					case T_Var:
						if (flags & SFLAG_Interface)
							compiler->syntaxError(position(), "Variable or constant definition not allowed in interface");
						if (qual.is_native || qual.is_prototype)
							compiler->syntaxError(position(), "Variable or constant may not be 'native' or 'prototype'");
						if (flags & (SFLAG_Toplevel|SFLAG_Package|SFLAG_Class)) {
							// FIXME: if inside a class, the statement goes into the instance initializer ... except if static...
							stmts.addAtEnd(variableDefinition(&qual));
							break;
						}
						else {
							if (qual.is_static || qual.tag != QUAL_none)
								compiler->syntaxError(position(), "Variable or constant may not be qualified except at the top level or inside a class");
							goto default_case;
						}
						
					case T_Function:
						if (!(flags & (SFLAG_Toplevel|SFLAG_Package|SFLAG_Class)))
							if (qual.tag != QUAL_none || qual.is_native)
								compiler->syntaxError(position(), "Illegal qualified function definition.");
						// FIXME: if inside a class or interface, we want to pick up the methods.
						// FIXME: if inside a class, it goes into the instance... except if static...
						functionDefinition(&qual);
						break;

					case T_Class:
						if (!(flags & (SFLAG_Toplevel|SFLAG_Package)))
							compiler->syntaxError(position(), "Class not allowed here");
						if (qual.is_native)
							compiler->syntaxError(position(), "Class may not be 'native'");
						classDefinition(flags, &qual);
						break;
						
					case T_Interface:
						if (!(flags & (SFLAG_Toplevel|SFLAG_Package)))
							compiler->syntaxError(position(), "Interface not allowed here");
						if (qual.is_native)
							compiler->syntaxError(position(), "Interface may not be 'native'");
						interfaceDefinition(flags, &qual);
						break;
						
					default:
					default_case:
						if (flags & SFLAG_Interface)
							compiler->syntaxError(position(), "Statements not allowed in interface");
						if (qual.tag != QUAL_none || qual.is_native)
							compiler->syntaxError(position(), "Illegal statement.");
						stmts.addAtEnd(statement());
						break;
				}
			}
			return stmts.get();
		}
		
		// Handles 'static' and 'prototype' too.
		// Returns true if we took it, false to go to the default case (for identifier).
		//
		// This checks constraints among qualifiers: that there are no duplicates, that
		// they are internally consistent (no "native prototype", no "<ns> prototype",
		// no "static prototype"), that keyworded qualifiers are only used where they
		// make sense ("prototype" and "static" in classes, etc).

		bool Parser::namespaceQualifier(int flags, Qualifier* qual)
		{
			switch (hd()) {
				case T_Native:
					if (!(flags & (SFLAG_Class|SFLAG_Package|SFLAG_Toplevel)) || qual->is_native || qual->is_prototype)
						compiler->syntaxError(position(), "'native' not allowed here");
					eat(T_Native);
					qual->is_native = true;
					return true;
				case T_Private:
					if (!(flags & SFLAG_Class) || qual->tag != QUAL_none || qual->is_prototype)
						compiler->syntaxError(position(), "'private' not allowed here");
					eat(T_Private);
					qual->tag = QUAL_private;
					return true;
				case T_Protected:
					if (!(flags & SFLAG_Class) || qual->tag != QUAL_none || qual->is_prototype)
						compiler->syntaxError(position(), "'protected' not allowed here");
					eat(T_Protected);
					qual->tag = QUAL_protected;
					return true;
				case T_Public:
					if (!(flags & (SFLAG_Class|SFLAG_Package)) || qual->tag != QUAL_none || qual->is_prototype)
						compiler->syntaxError(position(), "'public' not allowed here");
					eat(T_Protected);
					qual->tag = QUAL_public;
					return true;
				case T_Internal:
					if (!(flags & (SFLAG_Class|SFLAG_Package)) || qual->tag != QUAL_none || qual->is_prototype)
						compiler->syntaxError(position(), "'internal' not allowed here");
					eat(T_Internal);
					qual->tag = QUAL_internal;
					return true;
				case T_Identifier:
					if (identValue() == compiler->SYM_namespace)
						return false;
					if ((flags & SFLAG_Class) && identValue() == compiler->SYM_static) {
						if (qual->is_static || qual->is_prototype)
							compiler->syntaxError(position(), "'static' not allowed here");
						next();
						qual->is_static = true;
						return true;
					}
					if ((flags & SFLAG_Class) && identValue() == compiler->SYM_prototype) {
						if (qual->is_static || qual->is_prototype || qual->is_native || qual->tag != QUAL_none)
							compiler->syntaxError(position(), "'prototype' not allowed here");
						next();
						qual->is_prototype = true;
						return true;
					}
					if (qual->tag != QUAL_none)
						return false;
					if (qual->is_native)
						goto consume;
					switch (hd2()) {
						case T_Function:
						case T_Var:
						case T_Const:
						case T_Class:
						case T_Interface:
							goto consume;
						default:
							return false;
					}
				consume:
					qual->tag = QUAL_name;
					qual->name = identValue();
					eat(T_Identifier);
					return true;
				default:
					compiler->internalError(position(), "Unexpected namespace qualifier");
					/*NOTREACHED*/
					return false;
			}
		}
		
		// Qualifiers are known to be appropriate for 'class'
		void Parser::classDefinition(int /*flags*/, Qualifier* qual)
		{
			// FIXME: pick up the methods plus all other flags somehow, these are available from the binding ribs
			// Maybe time to package them up conveniently (FunctionDefinition needs it too).
			eat(T_Class);
			Str* name = identifier();
			Str* extends = NULL;
			SeqBuilder<Str*> implements(allocator);
			if (match(T_Extends)) {
				extends = identifier();
			}
			if (match(T_Implements)) {
				do {
					implements.addAtEnd(identifier());
				} while (match(T_Comma));
			}
			eat(T_LeftBrace);
			pushBindingRib(RIB_Class);
			pushBindingRib(RIB_Instance);
			Seq<Stmt*>* instance_init = NULL;
			Seq<Stmt*>* class_init = directives(SFLAG_Class, &instance_init);
			popBindingRib();
			popBindingRib();
			eat(T_RightBrace);
			addClass(ALLOC(ClassDefn, (qual, name, extends, implements.get(), class_init, instance_init)));
		}
		
		void Parser::interfaceDefinition(int /*flags*/, Qualifier* qual)
		{
			// FIXME: pick up the methods somehow, these are available from the binding ribs
			eat(T_Interface);
			Str* name = identifier();
			SeqBuilder<Str*> extends(allocator);
			if (match(T_Extends)) {
				do {
					extends.addAtEnd(identifier());
				} while (match(T_Comma));
			}
			eat(T_LeftBrace);
			pushBindingRib(RIB_Instance);
			directives(SFLAG_Interface);
			popBindingRib();
			eat(T_RightBrace);
			addInterface(ALLOC(InterfaceDefn, (qual, name, extends.get())));
		}
		
		// Namespaces are:
		//  - disallowed at the top level or in packages according to Jeff, but E4X test suite uses them on the global level
		//  - allowed at the top level of classes
		//  - allowed in functions and blocks
		//  - hoisted to the function level and scoped to the entire function
		//  - initialized on entry to the function (so defining them in blocks is pretty silly)
		
		// FIXME: don't discard the qualifier in namespace definitions
		void Parser::namespaceDefinition(int flags, Qualifier* /*qual*/)
		{
			uint32_t pos = position();
			if (!(flags & (SFLAG_Function|SFLAG_Toplevel)))	// no classes yet...
				compiler->syntaxError(pos, "'namespace' definition not allowed here");
			eat(T_Identifier);
			Str * name = identifier();
			if (match(T_Assign)) {
				if (hd() == T_Identifier || hd() == T_StringLiteral)
					addNamespaceBinding(name, primaryExpression());
				else
					compiler->syntaxError(pos, "Illegal 'namespace' definition");
			}
			else
				addNamespaceBinding(name, NULL);
			semicolon();
		}

		void Parser::includeDirective()
		{
			eat(T_Identifier);
			Str* newFile = stringValue();
			uint32_t pos = position();
			eat(T_StringLiteral);
			semicolon();
			if (!compiler->origin_is_file)
				compiler->syntaxError(pos, "The 'include' directive is only allowed in programs whose origin is a file");
			
			// The current lexer state - including the state variables that are a part of the
			// parser object - gets pushed onto a stack, a new lexer is created for the new
			// input, and is installed.  Then we return, the caller must continue parsing as
			// if nothing had happened.  When the current lexer sees EOS it calls onEOS()
			// on the parser, which pops the lexer stack and generates a token from the popped
			// lexer.  The normal token processing path does not slow down at all and the
			// machinery is almost entirely transparent to the parser.
			
			pushLexerState();
			T0 = T1 = T_LAST;
			LP = L0 = L1 = 0;

			uint32_t inputlen;
			const wchar* input = compiler->context->readFileForEval(compiler->filename, newFile->s, &inputlen);
			if (input == NULL)
				compiler->syntaxError(pos, "An include file could not be opened or read");
			
			included_input = input;		// freed in onEOS below
#ifdef DEBUG
			bool doTrace = lexer->getTrace();
#endif
			lexer = ALLOC(Lexer, (compiler, input, inputlen));
#ifdef DEBUG
			if (doTrace) lexer->trace();
#endif
			start();
		}
	
		Token Parser::onEOS(uint32_t* linep, TokenValue* valuep)
		{
			if (lexerStack == NULL)
				return T_EOS;
			
			compiler->context->freeInput(included_input);
			popLexerState();

			if (T0 == T_LAST)
				next();
			*linep = L0;
			*valuep = V0;
			return T0;
		}

		void Parser::pushLexerState()
		{
			LexerState* s = ALLOC(LexerState, ());
			s->lexer = lexer;
			s->next = lexerStack;
			s->T0 = T0;
			s->T1 = T1;
			s->V0 = V0;
			s->LP = LP;
			s->L0 = L0;
			s->L1 = L1;
			s->included_input = included_input;
			lexerStack = s;
		}
		
		void Parser::popLexerState()
		{
			T0 = lexerStack->T0;
			T1 = lexerStack->T1;
			V0 = lexerStack->V0;
			V1 = lexerStack->V1;
			LP = lexerStack->LP;
			L0 = lexerStack->L0;
			L1 = lexerStack->L1;
			included_input = lexerStack->included_input;
			lexer = lexerStack->lexer;
			lexerStack = lexerStack->next;
		}
		
		void Parser::pushBindingRib(RibType tag)
		{
			topRib = ALLOC(BindingRib, (allocator, topRib, tag));
		}
		
		void Parser::popBindingRib()
		{
			topRib = topRib->next;
		}

		// Only makes sense in the context of a scope; compares name components only
		static bool sameName(NameComponent* n1, NameComponent* n2)
		{
			if (n1 == NULL && n2 == NULL)
				return true;
			if (n1 == NULL || n2 == NULL)
				return false;
			if (n1->tag() != n2->tag())
				return false;
			switch (n1->tag()) {
				case TAG_simpleName:
					return ((SimpleName*)n1)->name == ((SimpleName*)n2)->name;	// Str is interned, so pointer comparison works
				case TAG_wildcardName:
					return true;
				case TAG_computedName:
					return false;
				default:
					return false;
			}
		}
		
		static bool sameName(QualifiedName* n1, QualifiedName* n2)
		{
			// ActionScript allows eg 'var n:Number; var n;".
			if (n1 == NULL || n2 == NULL)
				return true;
			return sameName(n1->qualifier, n2->qualifier) && sameName(n1->name, n2->name);
		}
		
		Binding* Parser::findBinding(Str* name, BindingKind kind, BindingRib* rib)
		{
			if (rib == NULL)
				rib = topRib;
			for ( Seq<Binding*>* bindings = rib->bindings.get() ; bindings != NULL ; bindings = bindings->tl ) {
				if (bindings->hd->name == name) {
					if (bindings->hd->kind != kind)
						compiler->syntaxError(0, "Conflicting binding of name");
					return bindings->hd;
				}
			}
			return NULL;
		}
		
		void Parser::addClass(ClassDefn* cls)
		{
			(void)cls;
			compiler->internalError(0, "Class definitions cannot be processed");
		}
		
		void Parser::addInterface(InterfaceDefn* iface)
		{
			(void)iface;
			compiler->internalError(0, "Interface definitions cannot be processed");
		}
		
		void Parser::addFunctionBinding(FunctionDefn* fn)
		{
			addVarBinding(fn->name, NULL);
			topRib->functionDefinitions.addAtEnd(fn);
		}

		void Parser::addVarBinding(Str* name, QualifiedName* type_name)
		{
			Binding* b = findBinding(name, TAG_varBinding);
			if (!b)
				topRib->bindings.addAtEnd(ALLOC(Binding, (name, type_name, TAG_varBinding)));
			else if (!sameName(b->type_name, type_name))
				compiler->syntaxError(0, "Conflicting binding of names: mismatching types");
		}
		
		void Parser::addConstBinding(Str* name, QualifiedName* type_name)
		{
			if (findBinding(name, TAG_constBinding))
				compiler->syntaxError(0, "Redundant constant binding");
			topRib->bindings.addAtEnd(ALLOC(Binding, (name, type_name, TAG_constBinding)));
		}
		
		void Parser::addMethodBinding(FunctionDefn* fn, BindingRib* rib)
		{
			if (findBinding(fn->name, TAG_methodBinding, rib))
				compiler->syntaxError(0, "Redundant method binding");
			rib->bindings.addAtEnd(ALLOC(Binding, (fn->name, NULL, TAG_methodBinding)));
			rib->functionDefinitions.addAtEnd(fn);
		}
		
		void Parser::addNamespaceBinding(Str* name, Expr* expr)
		{
			if (findBinding(name, TAG_namespaceBinding))
				compiler->syntaxError(0, "Redundant namespace binding");
			topRib->bindings.addAtEnd(ALLOC(Binding, (name, NULL, TAG_namespaceBinding)));	// FIXME: type for 'Namespace'
			topRib->namespaces.addAtEnd(ALLOC(NamespaceDefn, (name, expr)));
		}

		void Parser::setUsesFinally()
		{
			topRib->uses_finally = true;
		}
		
		void Parser::setUsesCatch()
		{
			topRib->uses_catch = true;
		}

		void Parser::functionDefinition(Qualifier* qual)
		{
			FunctionDefn* fn = functionGuts(qual, true);
			if (topRib->tag == RIB_Instance) {
				// class or interface
				if (qual->is_static) {
					AvmAssert(topRib->next->tag == RIB_Class);
					addMethodBinding(fn, topRib->next);
				}
				else
					addMethodBinding(fn, topRib);
			}
			else
				addFunctionBinding(fn);
		}
		
		Stmt* Parser::variableDefinition(Qualifier* qual)
		{
			(void)qual;
			// FIXME: discards qualifiers on variable definitions!
			return statement();
		}

		FunctionDefn* Parser::functionGuts(Qualifier* qual, bool require_name)
		{
			if (qual->is_native)
				compiler->syntaxError(position(), "'native' functions are not supported.");

			uint32_t numparams = 0;
			bool default_value_required = false;
			eat(T_Function);
			uint32_t pos = position();
			Str* name = NULL;
			FunctionParam * rest_param = NULL;
			if (require_name || hd() == T_Identifier)
				name = identifier();
			pushBindingRib(RIB_Function);
			eat(T_LeftParen);
			SeqBuilder<FunctionParam*> params(allocator);
			if (hd() != T_RightParen) {
				for (;;)
				{
					if (hd() == T_TripleDot) {
						Str* rest_name = NULL;
						QualifiedName* rest_type_name = NULL;
						eat(T_TripleDot);
						rest_name = identifier();
						if (match(T_Colon))
							rest_type_name = typeExpression();
						addVarBinding(rest_name, rest_type_name);
						rest_param = ALLOC(FunctionParam, (rest_name, rest_type_name, NULL));
						break;
					}
					++numparams;
					Str* param_name = identifier();
					QualifiedName* param_type_name = NULL;
					Expr* param_default_value = NULL;
					if (match(T_Colon))
						param_type_name = typeExpression();
					if (match(T_Assign)) {
						default_value_required = true;
						param_default_value = assignmentExpression(0);
					}
					else if (default_value_required)
						compiler->syntaxError(pos, "Default value required here.");
					addVarBinding(param_name, param_type_name);
					params.addAtEnd(ALLOC(FunctionParam, (param_name, param_type_name, param_default_value)));
					if (hd() == T_RightParen)
						break;
					eat(T_Comma);
				}
			}
			eat(T_RightParen);
			topRib->optional_arguments = default_value_required;
			QualifiedName* return_type_name = NULL;
			if (match(T_Colon)) {
				if (match(T_Void))
					topRib->is_void = true;
				else
					return_type_name = typeExpression();
			}
			eat(T_LeftBrace);
			Seq<Stmt*>* stmts = directives(SFLAG_Function);
			eat(T_RightBrace);
			// Rest takes precedence over 'arguments'
			if (topRib->uses_arguments) {
				if (rest_param == NULL)
					addVarBinding(compiler->SYM_arguments, NULL);
				else
					topRib->uses_arguments = false;
			}
			Seq<FunctionDefn*>* fndefs = topRib->functionDefinitions.get();
			Seq<Binding*>* bindings = topRib->bindings.get();
			Seq<NamespaceDefn*>* namespaces = topRib->namespaces.get();
			bool uses_arguments = topRib->uses_arguments;
			bool uses_dxns = topRib->uses_dxns;
			bool optional_arguments = topRib->optional_arguments;
			popBindingRib();
			return ALLOC(FunctionDefn, (name, bindings, params.get(), numparams, rest_param, return_type_name, fndefs, namespaces, stmts, 
										uses_arguments, 
										uses_dxns, 
										optional_arguments));
		}

		// Token queue abstractions
		// BEGIN
		
		// Token queue
		//
		// T0 is the current token, L0 its line number
		// T1 is the next token, L1 its line number
		// LP is the line number of the previous token
		//
		// The line number of a token is the 1-based line number of
		// the last character of the token.
		//
		// Invariants:
		//   T0 is LAST only before start() and when the stream is exhausted.
		//   T1 is LAST whenever it's invalid
		//   L1 is invalid iff T1 is invalid
		//   LP, L0, and L1 are 0 if there is "no information"
		//   The scanner never returns Eol
		//
		// Every token passes through this interface so we try to save time
		// when possible.
		//
		// Current optimizations:
		//   * avoid function calls
		//     - Lexer::lex() is shallow
		//     - Token::tokenKind and Token::tokenText have been in-lined
		//   * avoid allocations
		//     - Communicate with lexer via multiple variables rather than 
		//       using multiple return values
		
		void Parser::start() 
		{
			T0 = lexer->lex(&L0, &V0);
		}
		
		Token Parser::divideOperator() 
		{
			AvmAssert( T0 == T_BreakSlash && T1 == T_LAST );
			T0 = lexer->divideOperator(&L0);
			return hd();
		}
		
		Token Parser::regexp() 
		{
			AvmAssert( T0 == T_BreakSlash && T1 == T_LAST );
			T0 = lexer->regexp(&L0, &V0);
			return hd();
		}
		
		Token Parser::rightAngle() 
		{
			AvmAssert( T0 == T_BreakRightAngle && T1 == T_LAST );
			T0 = lexer->rightAngle(&L0);
			return hd();
		}
		
		Token Parser::rightShiftOrRelationalOperator() 
		{
			AvmAssert( T0 == T_BreakRightAngle && T1 == T_LAST );
			T0 = lexer->rightShiftOrRelationalOperator(&L0);
			return hd();
		}
		
		Token Parser::hd2()
		{
			if (T1 == T_LAST)
				T1 = lexer->lex(&L1, &V1);
			return T1;
		}
		
		void Parser::next() 
		{
			LP = L0;
			T0 = T1;
			L0 = L1;
			V0 = V1;
			T1 = T_LAST;
			if (T0 == T_LAST)
				T0 = lexer->lex(&L0, &V0);
		}
		
		// Token queue abstractions
		// END
		
		// If the current token is not tc then throw an error.
		// Otherwise consume the token.
		
		void Parser::eat(Token tc)
		{
			Token tk = hd();
			if (tk != tc)
				compiler->syntaxError(position(), "Wrong token, expected %d got %d", tc, tk);
			next();
		}
		
		bool Parser::match (Token tc)
		{
			Token tk = hd();
			if (tk != tc)
				return false;
			next();
			return true;
		}
		
		Str* Parser::identifier()
		{
			if (hd() != T_Identifier)
				compiler->syntaxError(position(), "Expected identifier");
			Str* name = V0.s;
			next();
			return name;
		}
		
		Str* Parser::doubleToStr(double d)
		{
			char buf[380];
			compiler->context->doubleToString(d, buf, sizeof(buf));
			return compiler->intern(buf);
		}
		
		CodeBlock::~CodeBlock()
		{
		}
    }
}

#endif // VMCFG_EVAL
