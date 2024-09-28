// Generated from ST_avmplus_peephole.st
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

#include "avmshell.h"
#ifdef AVMPLUS_SELFTEST
#if defined AVMPLUS_PEEPHOLE_OPTIMIZER
namespace avmplus {
class ST_avmplus_peephole : public Selftest {
public:
ST_avmplus_peephole(AvmCore* core);
virtual void run(int n);
virtual void prologue();
virtual void epilogue();
private:
static const char* ST_names[];
void test0();

private:
#ifdef AVMPLUS_DIRECT_THREADED
    void** opcode_labels; // the name is not arbitrary
#endif

};
ST_avmplus_peephole::ST_avmplus_peephole(AvmCore* core)
    : Selftest(core, "avmplus", "peephole", ST_avmplus_peephole::ST_names)
{}
const char* ST_avmplus_peephole::ST_names[] = {"get2locals", NULL };
void ST_avmplus_peephole::run(int n) {
switch(n) {
case 0: test0(); return;
}
}
void ST_avmplus_peephole::prologue() {

#ifdef AVMPLUS_DIRECT_THREADED
	opcode_labels = interpGetOpcodeLabels();
#endif

}
void ST_avmplus_peephole::epilogue() {

#ifdef AVMPLUS_DIRECT_THREADED
    opcode_labels = NULL; // interpGetOpcodeLables() returns a pointer to static data
#endif

}
void ST_avmplus_peephole::test0() {

    WordcodeEmitter* t = new WordcodeEmitter(core, NULL);

     t->emitOp1(WOP_getlocal, 5);
     t->emitOp1(WOP_getlocal, 4);
     t->emitOp1(WOP_getlocal, 65536);
     t->emitOp1(WOP_getlocal, 7);
     t->emitOp1(WOP_getlocal, 6);
     uintptr_t* code;
uint32_t len = (uint32_t)t->epilogue(&code);

verifyPass(len == 6, "len == 6", __FILE__, __LINE__);
verifyPass(code[0] == NEW_OPCODE(WOP_get2locals), "code[0] == NEW_OPCODE(WOP_get2locals)", __FILE__, __LINE__);
verifyPass(code[1] == ((4 << 16) | 5), "code[1] == ((4 << 16) | 5)", __FILE__, __LINE__);
verifyPass(code[2] == NEW_OPCODE(WOP_getlocal), "code[2] == NEW_OPCODE(WOP_getlocal)", __FILE__, __LINE__);
verifyPass(code[3] == 65536, "code[3] == 65536", __FILE__, __LINE__);
verifyPass(code[4] == NEW_OPCODE(WOP_get2locals), "code[4] == NEW_OPCODE(WOP_get2locals)", __FILE__, __LINE__);
verifyPass(code[5] == ((6 << 16) | 7), "code[5] == ((6 << 16) | 7)", __FILE__, __LINE__);

    delete t;


}
void create_avmplus_peephole(AvmCore* core) { new ST_avmplus_peephole(core); }
}
#endif
#endif
