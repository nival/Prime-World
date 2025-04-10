// -*- mode: c++ -*-
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
%%category  peephole
%%ifdef     AVMPLUS_PEEPHOLE_OPTIMIZER

%%decls

private:
#ifdef AVMPLUS_DIRECT_THREADED
    void** opcode_labels; // the name is not arbitrary
#endif

%%prologue

#ifdef AVMPLUS_DIRECT_THREADED
	opcode_labels = interpGetOpcodeLabels();
#endif

%%epilogue

#ifdef AVMPLUS_DIRECT_THREADED
    opcode_labels = NULL; // interpGetOpcodeLables() returns a pointer to static data
#endif

%%test get2locals

    WordcodeEmitter* t = new WordcodeEmitter(core, NULL);

     t->emitOp1(WOP_getlocal, 5);
     t->emitOp1(WOP_getlocal, 4);
     t->emitOp1(WOP_getlocal, 65536);
     t->emitOp1(WOP_getlocal, 7);
     t->emitOp1(WOP_getlocal, 6);
     uintptr_t* code;
uint32_t len = (uint32_t)t->epilogue(&code);

%%verify len == 6
%%verify code[0] == NEW_OPCODE(WOP_get2locals)
%%verify code[1] == ((4 << 16) | 5)
%%verify code[2] == NEW_OPCODE(WOP_getlocal)
%%verify code[3] == 65536
%%verify code[4] == NEW_OPCODE(WOP_get2locals)
%%verify code[5] == ((6 << 16) | 7)

    delete t;

