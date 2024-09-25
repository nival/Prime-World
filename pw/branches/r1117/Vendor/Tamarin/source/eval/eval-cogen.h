/* -*- mode: c++; tab-width: 4 -*- */
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

class Label {
public:
	Label() : address(~0U), backpatches(NULL) {}
	uint32_t address;			// either ~0U or the address of the label
	Seq<uint32_t>* backpatches;	// not a SeqBuilder so that we don't have to spend space on storing an allocator in every label object
};

/**
 * Instruction and value emitter.
 *
 * A 'cogen' abstracts away the details of emitting bytecodes and constant
 * values.
 */
class Cogen {
public:
	Cogen(Compiler* compiler, ABCFile* abc, ABCTraitsTable* traits, ABCMethodBodyInfo* body, uint32_t first_temp=1);
	
	/* Instruction emitters.  Most of these are trivially expanded
	 * inline to other calls; some have more complex logic.  For
	 * example, I_getlocal(0) expands to OP_getlocal0, the
	 * dxns instructions set the uses_dxns flag, and the debug
	 * instructions check whether debugging is enabled.  All methods
	 * help compute the heights of the value and scope stacks.
	 *
	 * Please maintain an alphabetical list.
	 */
	void I_add();
	void I_add_i();
	void I_astype(uint32_t index);
	void I_astypelate();
	void I_bitand();
	void I_bitnot();
	void I_bitor();
	void I_bitxor();
	void I_call(uint32_t argc);
	void I_callmethod(uint32_t index, uint32_t nargs);
	void I_callproperty(uint32_t index, uint32_t nargs);
	void I_callproplex(uint32_t index, uint32_t nargs);
	void I_callpropvoid(uint32_t index, uint32_t nargs);
	void I_callstatic(uint32_t index, uint32_t nargs);			
	void I_callsuper(uint32_t index, uint32_t nargs);
	void I_callsupervoid(uint32_t index, uint32_t nargs);
	void I_construct(uint32_t argc);
	void I_constructprop(uint32_t index, uint32_t nargs);
	void I_constructsuper(uint32_t argc);
	void I_checkfilter();
	void I_coerce(uint32_t index);
	void I_coerce_a();
	void I_coerce_s();
	void I_coerce_b();
	void I_coerce_d();
	void I_coerce_i();
	void I_coerce_u();
	void I_convert_o();
	void I_convert_s();
	void I_debug(uint8_t debug_type, uint32_t index, uint8_t reg, uint32_t extra=0);
	void I_debugfile(uint32_t index);
	void I_debugline(uint32_t linenum);
	void I_declocal(uint32_t reg);
	void I_declocal_i(uint32_t reg);
	void I_decrement();
	void I_decrement_i();
	void I_deleteproperty(uint32_t index);
	void I_divide();
	void I_dxns(uint32_t index);
	void I_dxnslate();
	void I_dup();
	void I_equals();
	void I_esc_xattr();
	void I_esc_xelem();
	void I_findproperty(uint32_t index);
	void I_findpropstrict(uint32_t index);
	void I_getdescendants(uint32_t index);
	void I_getglobalscope();
	void I_getglobalslot(uint32_t index);
	void I_getlex(uint32_t index);
	void I_getlocal(uint32_t index);
	void I_getouterscope(uint32_t index);
	void I_getproperty(uint32_t index);
	void I_getscopeobject(uint32_t index);
	void I_getslot(uint32_t index);
	void I_getsuper(uint32_t index);
	void I_greaterequals();
	void I_greaterthan();
	void I_hasnext();
	void I_hasnext2(uint32_t object_reg, uint32_t index_reg);
	void I_ifeq(Label* label);
	void I_iffalse(Label* label);
	void I_ifge(Label* label);
	void I_ifgt(Label* label);
	void I_ifle(Label* label);
	void I_iflt(Label* label);
	void I_ifne(Label* label);
	void I_ifnge(Label* label);
	void I_ifngt(Label* label);
	void I_ifnle(Label* label);
	void I_ifnlt(Label* label);
	void I_ifstricteq(Label* label);
	void I_ifstrictne(Label* label);
	void I_iftrue(Label* label);
	void I_in();
	void I_inclocal(uint32_t reg);
	void I_inclocal_i(uint32_t reg);
	void I_increment();
	void I_increment_i();
	void I_initproperty(uint32_t index);
	void I_instanceof();
	void I_istype(uint32_t index);
	void I_istypelate();
	void I_jump(Label* label);
	void I_kill(uint32_t index);
	void I_label(Label* label);
	void I_lessequals();
	void I_lessthan();
	void I_lookupswitch(Label* default_label, Label** case_labels, uint32_t ncases);  // unclear semantics for now
	void I_lshift();
	void I_modulo();
	void I_multiply();
	void I_multiply_i();
	void I_negate();
	void I_negate_i();
	void I_newactivation();
	void I_newarray(uint32_t nvalues);
	void I_newcatch(uint32_t index);
	void I_newclass(uint32_t index);
	void I_newfunction(uint32_t index);
	void I_newobject(uint32_t npairs);
	void I_newvoid(uint32_t index);
	void I_nextname();
	void I_nextvalue();
	void I_nop();
	void I_not();
	void I_pop();
	void I_popscope();
	void I_pushbyte(int8_t b);
	void I_pushfalse();
	void I_pushdouble(uint32_t index);
	void I_pushint(uint32_t index);
	void I_pushnamespace(uint32_t index);
	void I_pushnan();
	void I_pushnull();
	void I_pushscope();
	void I_pushshort(int16_t v);
	void I_pushstring(uint32_t index);
	void I_pushtrue();
	void I_pushuint(uint32_t index);
	void I_pushundefined();
	void I_pushwith();
	void I_returnvalue();
	void I_returnvoid();
	void I_rshift();
	void I_setglobalslot(uint32_t index);
	void I_setlocal(uint32_t index);
	void I_setproperty(uint32_t index);
	void I_setslot(uint32_t index);
	void I_setsuper(uint32_t index);
	void I_strictequals();
	void I_subtract();
	void I_subtract_i();
	void I_swap();
	void I_throw();
	void I_typeof();
	void I_urshift();
	void I_opcode(AbcOpcode opcode);

	uint32_t emitString(Str* value);	// cpool index
	uint32_t emitInt(int32_t value);	// cpool index
	uint32_t emitUInt(uint32_t value);	// cpool index
	uint32_t emitDouble(double value);	// cpool index
	uint32_t emitNamespace(uint32_t name);
	uint32_t emitSlotTrait(uint32_t name, uint32_t type);
	uint32_t emitConstTrait(uint32_t name, uint32_t type);
	uint32_t emitMethodTrait(uint32_t name, uint32_t method);
	uint32_t emitException(uint32_t from, uint32_t to, uint32_t target, uint32_t type, uint32_t name_index);
	
	static uint32_t emitTypeName(Compiler* abc, QualifiedName* t);

	Label*   newLabel();
	uint32_t getTemp();
	void unstructuredControlFlow(Ctx* ctx, bool (hit)(Ctx*,void*), void* package, bool jump, const char* msg, uint32_t pos=0);
	void standardMethod(bool is_function, Seq<Str*>* params, Seq<FunctionDefn*>* functions, Seq<Str*>* vars, Seq<Stmt*>* stmts);
	uint32_t arguments(Seq<Expr*>* args);
    void startCatch();

	AbcOpcode binopToOpcode(Binop op, bool* isNegated);
	
	Compiler* const compiler;
	ABCFile* const abc;
	Allocator * const allocator;

	uint32_t getMaxStack() const;
	uint32_t getMaxScope() const;
	uint32_t getLocalCount() const;
	uint32_t getCodeLength() const;
	uint8_t getFlags() const;
	uint8_t* serializeCodeBytes(uint8_t* b) const;
	
private:
	void callMN(AbcOpcode op, uint32_t index, uint32_t nargs);
	void propU30(AbcOpcode op, uint32_t index);
	void emitOp(AbcOpcode op);
	void emitOpU30(AbcOpcode op, uint32_t u30);
	void emitOpU30Special(AbcOpcode op, uint32_t u30, uint32_t stack_adjust);
	void emitOpU30U30(AbcOpcode op, uint32_t u30_1, uint32_t u30_2);
	void emitOpU8(AbcOpcode op, uint8_t b);
	void emitOpS8(AbcOpcode op, int8_t b);
	void emitOpS16(AbcOpcode op, uint16_t s);
	void emitJump(AbcOpcode op, Label* label);
	void fixupBackpatches(uint8_t* b) const;
	void stackMovement(AbcOpcode opcode);
	void stackMovement(AbcOpcode opcode, bool hasRTNS, bool hasRTName, uint32_t argc);

	// Mapping from subset of tokens to attributes and operator values
	static const struct BinopMapping {
		unsigned isNegated:1;
		unsigned abcOpcode:8;
	} binopMapping[];
	
	ByteBuffer code;
	
	SeqBuilder<Label*> labels;
	ABCTraitsTable * const traits;
	ABCMethodBodyInfo * const body;
	uint32_t last_linenum;
	uint32_t label_counter;
	uint32_t temp_counter;
	bool sets_dxns;
	bool need_activation;
	uint32_t stack_depth;
	uint32_t max_stack_depth;
	uint32_t scope_depth;
};

