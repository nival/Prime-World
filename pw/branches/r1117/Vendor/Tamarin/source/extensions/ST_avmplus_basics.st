// -*- mode: c -*-
//
// ***** BEGIN LICENSE BLOCK *****
// Version: MPL 1.1/GPL 2.0/LGPL 2.1
//
// The contents of this file are subject to the Mozilla Public License Version
// 1.1 (the "License"); you may not use this file except in compliance with
// the License. You may obtain a copy of the License at
// http://www.mozilla.org/MPL/
//
// Software distributed under the License is distributed on an "AS IS" basis,
// WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
// for the specific language governing rights and limitations under the
// License.
//
// The Original Code is [Open Source Virtual Machine.].
//
// The Initial Developer of the Original Code is
// Adobe System Incorporated.
// Portions created by the Initial Developer are Copyright (C) 2004-2006
// the Initial Developer. All Rights Reserved.
//
// Contributor(s):
//   Adobe AS3 Team
//
// Alternatively, the contents of this file may be used under the terms of
// either the GNU General Public License Version 2 or later (the "GPL"), or
// the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
// in which case the provisions of the GPL or the LGPL are applicable instead
// of those above. If you wish to allow use of your version of this file only
// under the terms of either the GPL or the LGPL, and not to allow others to
// use your version of this file under the terms of the MPL, indicate your
// decision by deleting the provisions above and replace them with the notice
// and other provisions required by the GPL or the LGPL. If you do not delete
// the provisions above, a recipient may use your version of this file under
// the terms of any one of the MPL, the GPL or the LGPL.
//
// ***** END LICENSE BLOCK ***** */

%%component avmplus
%%category basics

%%test unsigned_int

// Does right shift of unsigned quantities work?
%%verify (int)(~0U >> 1) > 0

%%test signed_int

// Does right shift of signed quantities work?
%%verify (-1 >> 1) == -1

// verify that the "latin1" literal string calls work properly for hi-bit latin1 chars
%%test equalsLatin1
    Stringp s = core->newConstantStringLatin1("ev\xADident");
	bool equals = s->equalsLatin1("ev\xADident");
%%verify equals == true

%%test containsLatin1
    Stringp s = core->newConstantStringLatin1("ev\xADident");
	bool found = s->containsLatin1("\xAD");
%%verify found == true

%%test indexOfLatin1
    Stringp s = core->newConstantStringLatin1("ev\xADident");
	int index = s->indexOfLatin1("\xAD");
%%verify index == 2

%%test matchesLatin1
    Stringp s = core->newConstantStringLatin1("ev\xADident");
	bool matches1 = s->matchesLatin1("\xADi", 2, 2);
%%verify matches1 == true

%%test matchesLatin1_caseless
    Stringp s = core->newConstantStringLatin1("ev\xADident");
	bool matches2 = s->matchesLatin1_caseless("\xADIDENT", 2, 2);
%%verify matches2 == true


