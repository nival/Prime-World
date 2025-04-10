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

inline Token Lexer::lex(uint32_t* linep, TokenValue* valuep)
{
	Token t = lexImpl();
	*linep = lineno;
	*valuep = val;
#ifdef DEBUG
	if (traceflag)
		print(t, *linep, *valuep);
#endif
	return t;
}

inline Token Lexer::regexp(uint32_t* linep, TokenValue* valuep)
{
	Token t = regexpImpl();
	*linep = lineno;
	*valuep = val;
#ifdef DEBUG
	if (traceflag)
		print(t, *linep, *valuep);
#endif
	return t;
}

inline Token Lexer::divideOperator(uint32_t* linep)
{
	Token t = divideOperatorImpl();
	*linep = lineno;
#ifdef DEBUG
	if (traceflag) {
		TokenValue garbage;
		garbage.i = 0;
		print(t, *linep, garbage);
	}
#endif
	return t;
}

inline Token Lexer::xmlAtom(uint32_t* linep, TokenValue* valuep)
{
	Token t = xmlAtomImpl();
	*linep = lineno;
	*valuep = val;
#ifdef DEBUG
	if (traceflag) {
		TokenValue garbage;
		garbage.i = 0;
		print(t, *linep, garbage);
	}
#endif
	return t;
}

inline Token Lexer::rightAngle(uint32_t* linep)
{
	Token t = rightAngleImpl();
	*linep = lineno;
#ifdef DEBUG
	if (traceflag) {
		TokenValue garbage;
		garbage.i = 0;
		print(t, *linep, garbage);
	}
#endif
	return t;
}

inline Token Lexer::rightShiftOrRelationalOperator(uint32_t* linep)
{
	Token t = rightShiftOrRelationalOperatorImpl();
	*linep = lineno;
#ifdef DEBUG
	if (traceflag) {
		TokenValue garbage;
		garbage.i = 0;
		print(t, *linep, garbage);
	}
#endif
	return t;
}

inline bool Lexer::octalDigits(int k) { return digits(k, CHAR_ATTR_OCTAL); }
inline bool Lexer::decimalDigits(int k) { return digits(k, CHAR_ATTR_DECIMAL); }
inline bool Lexer::hexDigits(int k) { return digits(k, CHAR_ATTR_HEX); }
		
// mis-named, isSubsequent would be better?
inline bool Lexer::notPartOfIdent(int c)
{
	return (c < 128 && (char_attrs[c] & CHAR_ATTR_SUBSEQUENT) == 0) || !isUnicodeIdentifierPart(c);
}

inline void Lexer::xmlPushback(wchar c)
{
	(void)c;
	AvmAssert(idx > src && idx[-1] == c);
	idx--;
}

#ifdef DEBUG

inline void Lexer::trace()
{
	traceflag = true;
}

inline bool Lexer::getTrace() const
{
	return traceflag;
}

#endif
