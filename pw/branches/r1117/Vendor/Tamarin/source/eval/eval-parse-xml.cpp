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
		// xmlInitializer is the only entry point.

		class XmlContext {
		public:
			XmlContext(Compiler* compiler)
				: allocator(compiler->allocator)
				, exprs(allocator)
				, text(compiler)
				, text_start(0)
			{
			}

			void addExpr(Expr* e);
			void addText(Str* s);
			void addText(const char* s);
			void addText(wchar c);
			Seq<Expr*>* get();

		private:
			void flush();

			Allocator * const allocator;
			SeqBuilder<Expr*> exprs;
			StringBuilder text;
			uint32_t text_start;
		};

		void XmlContext::addExpr(Expr* e)
		{
			flush();
			exprs.addAtEnd(e);
		}
		
		void XmlContext::addText(Str* s)
		{
			text.append(s);
		}

		void XmlContext::addText(const char* s)
		{
			while (*s)
				text.append(*s++);
		}
		
		void XmlContext::addText(wchar c)
		{
			text.append(c);
		}

		Seq<Expr*>* XmlContext::get()
		{
			flush();
			return exprs.get();
		}
		
		void XmlContext::flush() {
			if (text.length() > 0) {
				exprs.addAtEnd(ALLOC(LiteralString, (text.str(), text_start)));
				/*
				char buf[500];
				getn(buf, text.str(), 500);
				puts(buf);
				 */
				text.clear();
			}
		}
		
		Expr* Parser::xmlInitializer()
		{
			AvmAssert( (T0 == T_BreakXml || T0 == T_LessThan) && T1 == T_LAST );

			XmlContext ctx(compiler);
			bool is_list = false;
			uint32_t pos = position();

			if (T0 == T_LessThan)
				xmlPushback('<');
			xmlAtom();
			switch (T0) {
				case T_XmlComment:
				case T_XmlCDATA:
				case T_XmlProcessingInstruction:
					xmlAssert(&ctx, T0);
					break;

				case T_XmlLeftAngle:
					xmlAssert(&ctx, T0);
					xmlAtomSkipSpace();
					if (T0 == T_XmlRightAngle) {
						is_list = true;
						xmlListInitializer(&ctx);
					}
					else
						xmlElement(&ctx);
					break;

				default:
					compiler->internalError(position(), "error state in xml handling");
					/*NOTREACHED*/
					break;
			}

			next();				// Re-synchronize the lexer for normal lexing
			return ALLOC(XmlInitializer, (ctx.get(), is_list, pos));
		}

		// IN:  T0 is ">"
		// OUT: T0 is ">"
		
		void Parser::xmlListInitializer(XmlContext* ctx)
		{
			xmlAssert(ctx, T_XmlRightAngle);
			xmlElementContent(ctx);
			xmlAssert(ctx, T_XmlLeftAngleSlash);
			xmlAtomSkipSpace();
			xmlAssert(ctx, T_XmlRightAngle);
		}

		// IN:  T0 is first non-space token of tag name
		// OUT: T0 is ">" or "/>"
		
		void Parser::xmlElement(XmlContext* ctx)
		{
			xmlTagName(ctx);
			if (T0 != T_XmlRightAngle && T0 != T_XmlSlashRightAngle) {
				ctx->addText(" ");
				xmlAttributes(ctx);
			}
			if (T0 == T_XmlRightAngle) {
				xmlAssert(ctx, T0);
				xmlElementContent(ctx);
				xmlAssert(ctx, T_XmlLeftAngleSlash);
				xmlAtomSkipSpace();
				xmlTagName(ctx);
				xmlAssert(ctx, T_XmlRightAngle);
			}
			else
				xmlAssert(ctx, T_XmlSlashRightAngle);
		}
		
		// IN:  T0 is first non-space token of name
		// OUT: T0 is first non-space token following name
		
		void Parser::xmlTagName(XmlContext* ctx)
		{
			if (T0 == T_XmlLeftBrace)
				xmlExpression(ctx, ESC_none);
			else
				xmlAssert(ctx, T_XmlName);
			xmlAtomSkipSpace();
		}

		// IN:  T0 is first non-space token of first attribute (or /> or >)
		// OUT: T0 is /> or >

		void Parser::xmlAttributes(XmlContext* ctx)
		{
			bool first = true;
			while (T0 != T_XmlRightAngle && T0 != T_XmlSlashRightAngle) {
				if (!first) {
					ctx->addText(" ");
					first = false;
				}
				if (T0 == T_XmlLeftBrace) {
					xmlExpression(ctx, ESC_attributeValue);
					xmlAtomSkipSpace();
					// {E} = V is an extension required by the test suite, not in Ecma-357
					if (T0 == T_XmlEquals) 
						goto attrvalue;
				}
				else {
					xmlAssert(ctx, T_XmlName);
					xmlAtomSkipSpace();
				attrvalue:
					xmlAssert(ctx, T_XmlEquals);
					xmlAtomSkipSpace();
					if (T0 == T_XmlLeftBrace) {
						ctx->addText("\"");
						xmlExpression(ctx, ESC_attributeValue);
						ctx->addText("\"");
					}
					else
						xmlAssert(ctx, T_XmlString, ESC_attributeValue);
					xmlAtomSkipSpace();
				}
			}
		}
		
		// IN:  T0 is ">"
		// OUT: T0 is "</"

		void Parser::xmlElementContent(XmlContext* ctx)
		{
			for (;;) {
				xmlAtom();
				switch (T0) {
					case T_XmlProcessingInstruction:
					case T_XmlComment:
					case T_XmlCDATA:
					case T_XmlName:
					case T_XmlWhitespaces:
					case T_XmlText:
					case T_XmlString:
					case T_XmlRightBrace:
					case T_XmlRightAngle:
					case T_XmlSlashRightAngle:
					case T_XmlEquals:
						xmlAssert(ctx, T0);
						continue;
					case T_XmlLeftBrace:
						xmlExpression(ctx, ESC_elementValue);
						continue;
					case T_XmlLeftAngle:
						xmlAssert(ctx, T0);
						xmlAtomSkipSpace();
						xmlElement(ctx);
						continue;
					case T_XmlLeftAngleSlash:
						return;
					default:
						compiler->internalError(position(), "Unexpected state in XML parsing");
				}
			}
		}

		// IN:  T0 is "{"
		// OUT: T0 is "}"

		void Parser::xmlExpression(XmlContext* ctx, Escapement esc)
		{
			AvmAssert( T0 == T_XmlLeftBrace );
			next();		// re-enter normal lexing
			Expr* expr = commaExpression(0);
			if (esc != ESC_none) 
				expr = ALLOC(EscapeExpr, (expr, esc));
			ctx->addExpr(expr);
			AvmAssert( T0 == T_RightBrace && T1 == T_LAST );
			xmlPushback('}');
			xmlAtom();
			xmlAssert(ctx, T_XmlRightBrace);
		}
		
		void Parser::xmlEscape(XmlContext* ctx, const wchar* cs, const wchar* limit, bool is_attr)
		{
			while ( cs < limit ) {
				wchar c;
				switch (c = *cs++) {
					case '<':
						ctx->addText("&lt;");
						continue;
					case '&':
						ctx->addText("&amp;");
						continue;
					case '"':
						if (!is_attr) break;
						ctx->addText("&quot;");
						continue;
					case '>':
						if (is_attr) break;
						ctx->addText("&gt;");
						continue;
					case '\\':
						// This is weird but apparently according to spec
						if (!is_attr) break;
						if (cs + 5 <= limit &&
							cs[0] == 'u' &&
							cs[1] == '0' &&
							cs[2] == '0' &&
							cs[3] == '0') {
							switch (cs[4]) {
								case 'A': case 'a':
									cs += 4;
									ctx->addText("&#xA;");
									continue;
								case 'D': case 'd':
									cs += 4;
									ctx->addText("&#xD;");
									continue;
								case '9':
									cs += 4;
									ctx->addText("&#x9;");
									continue;
								default:
									goto add_char;
							}
						}
					add_char:
						break;
				}
				ctx->addText(c);
			}
		}
		
		void Parser::xmlAssert(XmlContext* ctx, Token t, Escapement esc)
		{
			if (T0 != t)
				compiler->syntaxError(position(), "Unexpected token in XML parsing");
			switch (t) {
				case T_XmlProcessingInstruction:
				case T_XmlComment:
				case T_XmlCDATA:
				case T_XmlLeftBrace:
				case T_XmlName:
				case T_XmlWhitespaces:
				case T_XmlText:
					ctx->addText(V0.s);
					break;
				case T_XmlString:
					switch (esc) {
						case ESC_attributeValue:
						case ESC_elementValue:
							// Spec seems broken
							/*
							ctx->addText(V0.s->s[0]);
							xmlEscape(ctx, V0.s->s + 1, V0.s->s + V0.s->length - 1, esc == ESC_attributeValue);
							ctx->addText(V0.s->s[0]);
							break;
							 */
						default:
							ctx->addText(V0.s);
							break;
					}
					break;
				case T_XmlRightBrace:
					// no text added
					break;
				case T_XmlRightAngle:
					ctx->addText(">");
					break;
				case T_XmlSlashRightAngle:
					ctx->addText("/>");
					break;
				case T_XmlEquals:
					ctx->addText("=");
					break;
				case T_XmlLeftAngle:
					ctx->addText("<");
					break;
				case T_XmlLeftAngleSlash:
					ctx->addText("</");
					break;
				default:
					compiler->internalError(position(), "Unexpected token in XML parsing");
			}					
		}
		
		void Parser::xmlAtomSkipSpace()
		{
			do {
				xmlAtom();
			} while (T0 == T_XmlWhitespaces);
		}
    }
}

#endif // VMCFG_EVAL
