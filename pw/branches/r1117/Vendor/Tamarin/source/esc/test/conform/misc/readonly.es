/* -*- mode: java; tab-width: 4; insert-tabs-mode: nil; indent-tabs-mode: nil -*- */
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

/* Writing to read-only globals causes exception to be thrown.

undefined = 10;  print("UNDEFINED " + undefined);
NaN = 10; print("NaN " + NaN);
Infinity = 10; print("Infinity " + Infinity);

x = Object;   Object = 10; print("OBJECT " + (Object === x));
x = Function; Function = 10; print("FUNCTION " + (Function === x));
x = Array;    Array = 10; print("ARRAY " + (Array === x));
x = String;   String = 10; print("STRING " + (String === x));
x = Number;   Number = 10; print("NUMBER " + (Number === x));
x = Boolean;  Boolean = 10; print("BOOLEAN " + (Boolean === x));
x = Date;     Date = 10; print("DATE " + (Date === x));
x = RegExp;   RegExp = 10; print("REGEXP " + (RegExp === x));
x = Error;    Error = 10; print("ERROR " + (Error === x));
x = EvalError; EvalError = 10; print("EVALERROR " + (EvalError === x));
x = RangeError; RangeError = 10; print("RANGEERROR " + (RangeError === x));
x = ReferenceError; ReferenceError = 10; print("REFERENCEERROR " + (ReferenceError === x));
x = SyntaxError; SyntaxError = 10; print("SYNTAXERROR " + (SyntaxError === x));
x = TypeError; TypeError = 10; print("TYPEERROR " + (TypeError === x));
x = URIError; URIError = 10; print("URIERROR " + (URIError === x));
*/

print("DONE");
