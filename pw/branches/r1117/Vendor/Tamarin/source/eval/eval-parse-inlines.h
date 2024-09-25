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

// This file is included into eval.h

inline bool Parser::newline() 
{
    return LP < L0;
}

inline uint32_t Parser::position() 
{
    return L0 + line_offset;
}

inline Token Parser::hd()
{
    return T0;
}

inline Str* Parser::identValue()
{
	AvmAssert(T0 == T_Identifier);
	return V0.s;
}

inline Str* Parser::stringValue()
{
	AvmAssert(T0 == T_StringLiteral);
	return V0.s;
}

inline Str* Parser::regexValue()
{
	AvmAssert(T0 == T_RegexpLiteral);
	return V0.s;
}

inline int32_t Parser::intValue()
{
	AvmAssert(T0 == T_IntLiteral);
	return V0.i;
}

inline uint32_t Parser::uintValue() 
{
	AvmAssert(T0 == T_UIntLiteral);
	return V0.u;
}

inline double Parser::doubleValue() 
{
	AvmAssert(T0 == T_DoubleLiteral);
	return V0.d;
}

inline bool Parser::isOpAssign(Token t)
{
	return t < T_OPERATOR_SENTINEL && tokenMapping[t].isOpAssign;
}

inline bool Parser::isMultiplicative(Token t)
{
	return t < T_OPERATOR_SENTINEL && tokenMapping[t].isMultiplicative;
}

inline bool Parser::isAdditive(Token t)
{
	return t < T_OPERATOR_SENTINEL && tokenMapping[t].isAdditive;
}

inline bool Parser::isRelational(Token t, bool in_allowed)
{
	return t < T_OPERATOR_SENTINEL && tokenMapping[t].isRelational && (in_allowed || t != T_In);
}

inline bool Parser::isEquality(Token t)
{
	return t < T_OPERATOR_SENTINEL && tokenMapping[t].isEquality;
}

inline bool Parser::isShift(Token t)
{
	return t < T_OPERATOR_SENTINEL && tokenMapping[t].isShift;
}

inline Unop Parser::tokenToUnaryOperator(Token t)
{
	AvmAssert(t < T_OPERATOR_SENTINEL);
	return (Unop)tokenMapping[t].unaryOp;
}

inline Binop Parser::tokenToBinaryOperator(Token t)
{
	AvmAssert(t < T_OPERATOR_SENTINEL);
	return (Binop)tokenMapping[t].binaryOp;
}

inline void Parser::setUsesArguments()
{
	topRib->uses_arguments = true;
}

inline void Parser::setUsesDefaultXmlNamespace()
{
	topRib->uses_dxns = true;
}

inline void Parser::xmlAtom() 
{
	T0 = lexer->xmlAtom(&L0, &V0);
}

inline void Parser::xmlPushback(wchar c)
{
	lexer->xmlPushback(c);
}
