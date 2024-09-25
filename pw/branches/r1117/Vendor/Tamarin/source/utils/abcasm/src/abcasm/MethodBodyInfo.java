/* -*- Mode: Java; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4 -*- */
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
 * Portions created by the Initial Developer are Copyright (C) 2009
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
package abcasm;

import java.lang.reflect.Field;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;
import java.util.Vector;


import static abcasm.AbcConstants.*;

class MethodBodyInfo
{
	Object methodId;
	
	int max_stack;
	int max_scope;
	int max_local;  //  Note: if not explicitly initialized, starts at parameter count
	int max_slot;  //  Max slot # in the code or traits size
	
	Integer explicit_max_stack;
	Integer explicit_init_scope;
	Integer explicit_max_scope;
	Integer explicit_max_local;
	Integer explicit_max_slot;

	Traits traits = new Traits();
	
	List<Block> blocks = new LinkedList<Block>();
	private Map<Label, Block> blocksByLabel = new TreeMap<Label, Block>();
	Map<Block, Label> labelsByBlock = new HashMap<Block, Label>();
	Vector<ExceptionInfo> exceptions = new Vector<ExceptionInfo>();
	
	/**
	 *  Block currently being built; used during the function's construction. 
	 */
	Block currentBlock;

	MethodBodyInfo()
	{
		startBlock();
	}
	
	int getMethodId()
	{
		if ( this.methodId instanceof Integer )
		{
			return (Integer)this.methodId;
		}
		else
			throw new IllegalArgumentException("Unknown function " + methodId.toString());
	}
	
	Traits getTraits()
	{
		return traits;
	}
	
	void startBlock(Label block_label)
	{
		assert(block_label != null);
		
		if ( blocksByLabel.containsKey(block_label))
			throw new IllegalArgumentException("Duplicate label " + block_label.toString());

		//  If a branch insn just started a block,
		//  starting a new one is redundant.
		if ( !currentBlock.insns.isEmpty() )
		{
			startBlock();
		}
	
		blocksByLabel.put(block_label, currentBlock);
		labelsByBlock.put(currentBlock, block_label);
	}

	void startBlock()
	{
		this.currentBlock = new Block();
		blocks.add(currentBlock);
	}
	
	void insn(org.antlr.runtime.Token opcode_token, Name name, Object imm)
	{
		insn(decodeOpcodeName(opcode_token.getText()), name, new Object[]{imm});
	}

	void insn(org.antlr.runtime.Token opcode_token, Name name)
	{
		insn(decodeOpcodeName(opcode_token.getText()), name, new Object[0]);
	}
	
	void insn(org.antlr.runtime.Token opcode_token)
	{
		insn( decodeOpcodeName(opcode_token.getText()), new Object[0]);
	}
	
	void insn(org.antlr.runtime.Token opcode_token, Label label)
	{
		insn( decodeOpcodeName(opcode_token.getText()), label);
	}

	void insn(org.antlr.runtime.Token opcode_token, java.util.ArrayList<Integer> imm_list)
	{
		insn(decodeOpcodeName(opcode_token.getText()), imm_list.toArray());
	}

	void insn(org.antlr.runtime.Token opcode_token, Object[] imm)
	{
		insn(decodeOpcodeName(opcode_token.getText()), imm);
	}

	void insn(int opcode, java.util.ArrayList<Object> imm_list)
	{	
		insn(opcode, imm_list.toArray());
	}
	
	void insn(Integer opcode, java.util.ArrayList<Integer> imm_list)
	{	
		insn(opcode.intValue(), imm_list.toArray());
	}
	public void insn(int opcode, Object[] imm)
	{
		this.currentBlock.insns.add(new Instruction(opcode, imm));	
	}
	
	void insn(int opcode, Name name, Object[] imm)
	{
		Instruction i = new Instruction(opcode, imm);
		this.currentBlock.insns.add(i);
		i.n = name;
	}
	
	void insn(int opcode, Label target)
	{
		Instruction i = new Instruction(opcode, null);
		this.currentBlock.insns.add(i);
		i.target = target;
	}
	
	public void insn(org.antlr.runtime.Token opcode_token, Object pooledValue)
	{
		Instruction i = new Instruction(decodeOpcodeName(opcode_token.getText()), pooledValue);
		this.currentBlock.insns.add(i);
	}
	
	public void insn(int opcode, Object pooledValue)
	{
		Instruction i = new Instruction(opcode, pooledValue);
		this.currentBlock.insns.add(i);
	}
	
	/**
	 *  Compute a functions's max_stack, max_scope, and slot count.
	 *  @note noop if all counts were explicitly provided.
	 */
	void computeFrameCounts()
	{
		if ( this.explicit_max_stack != null && this.explicit_max_scope != null && this.explicit_max_local != null && this.explicit_max_slot != null )
		{
			//  All counts explicitly provided.
			return;
		}
		
		Map<Block,Integer>stkin = new HashMap<Block,Integer>();
		Map<Block,Integer>scpin = new HashMap<Block,Integer>();
		
		int stkdepth = 0;
		int scpdepth = 0;

		for ( Block b: blocks )
		{	
			if ( isCatchTarget(b))
			{
				stkdepth = 1;
				scpdepth = 0;
			}
			else if ( stkin.containsKey(b))
			{
				//  FIXME: should check that these agree.
				stkdepth = stkin.get(b);
				scpdepth = scpin.get(b);
			}

			for (Instruction i: b.insns)
			{	
				switch (i.opcode)
				{
				case OP_add:
				case OP_add_i:
				case OP_astypelate:
				case OP_bitand:
				case OP_bitnot:
				case OP_bitor:
				case OP_bitxor:
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
				
				case OP_call:
					stkdepth = adjustValueStack(stkdepth,-(i.imm[0] + 1));
					break;
				
				case OP_callmethod:
					stkdepth = adjustValueStack(stkdepth,-i.imm[0]);
					break;
					
				case OP_callproperty:
				case OP_callproplex:
				case OP_callpropvoid:
				case OP_callstatic:
				case OP_callsuper:
				case OP_callsupervoid:
				case OP_construct:
				case OP_constructprop:
				case OP_constructsuper:
					//  FIXME: Doesn't consider runtime names,
					//  for those cases where they might occur.
					stkdepth = adjustValueStack(stkdepth,-i.imm[0]);
					break;
					
				case OP_deleteproperty:
				//  FIXME: Doesn't consider runtime names.
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
				
				case OP_divide:
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
				case OP_dup:
					stkdepth = adjustValueStack(stkdepth,1);
					break;
				case OP_dxnslate:
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
				case OP_equals:
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
				case OP_finddef:
				case OP_findproperty:
				case OP_findpropstrict:
					//  FIXME: runtime names.
					stkdepth = adjustValueStack(stkdepth,1);
					break;
					
				case OP_getdescendants:
				case OP_getproperty:
				case OP_getsuper:
					//  FIXME: runtime names.
					break;
				
				case OP_getglobalscope:
				case OP_getglobalslot:
				case OP_getlex:
					stkdepth = adjustValueStack(stkdepth,1);
					break;
					
				case OP_getlocal:
					stkdepth = adjustValueStack(stkdepth,1);
					adjustMaxLocal(i.imm[0]);
					break;
				case OP_getlocal0:
				case OP_getlocal1:
				case OP_getlocal2:
				case OP_getlocal3:
					stkdepth = adjustValueStack(stkdepth,1);
					adjustMaxLocal(i.opcode - OP_getlocal0);
					break;
					
				case OP_getslot:
					stkdepth = adjustValueStack(stkdepth,1);
					if ( i.imm[0] > max_slot )
						max_slot = i.imm[0];
					break;
					
				case OP_getscopeobject:
					stkdepth = adjustValueStack(stkdepth,1);
					break;
					
				case OP_greaterequals:
				case OP_greaterthan:
				case OP_hasnext:
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
				case OP_hasnext2:
					stkdepth = adjustValueStack(stkdepth,1);
					break;
				case OP_ifeq:
				case OP_ifge:
				case OP_ifgt:
				case OP_ifle:
				case OP_iflt:
				case OP_ifnge:
				case OP_ifngt:
				case OP_ifnle:
				case OP_ifnlt:
				case OP_ifne:
				case OP_ifstricteq:
				case OP_ifstrictne:
					stkdepth = adjustValueStack(stkdepth,-2);
					break;
				case OP_iffalse:
				case OP_iftrue:
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
					
				case OP_in:
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
					
				case OP_initproperty:
					//  FIXME: Runtime names.
					stkdepth = adjustValueStack(stkdepth,-2);
					break;
					
				case OP_instanceof:
				case OP_istypelate:
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
					
				case OP_lessequals:
				case OP_lessthan:
				case OP_lookupswitch:
				case OP_lshift:
				case OP_modulo:
				case OP_multiply:
				case OP_multiply_i:
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
				
				case OP_newactivation:
				case OP_newcatch:
				case OP_newfunction:
					stkdepth = adjustValueStack(stkdepth,1);
					break;
					
				case OP_newarray:
					stkdepth = adjustValueStack(stkdepth,i.imm[0]-1);
					break;
					
				case OP_newobject:
					stkdepth = adjustValueStack(stkdepth,i.imm[0]*2-1);
					break;
					
				case OP_nextname:
				case OP_nextvalue:
				case OP_pop:
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
					
				case OP_popscope:
					scpdepth = adjustScopeStack(scpdepth,-1);
					break;
					
				case OP_pushbyte:
				case OP_pushdouble:
				case OP_pushfalse:
				case OP_pushint:
				case OP_pushnamespace:
				case OP_pushnan:
				case OP_pushnull:
				case OP_pushshort:
				case OP_pushstring:
				case OP_pushtrue:
				case OP_pushuint:
				case OP_pushundefined:
					stkdepth = adjustValueStack(stkdepth,1);
					break;
					
				case OP_pushscope:
				case OP_pushwith:
					stkdepth = adjustValueStack(stkdepth,-1);
					scpdepth = adjustScopeStack(scpdepth,1);
					break;
					
				case OP_returnvalue:
				case OP_rshift:
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
					
				case OP_setlocal:
					stkdepth = adjustValueStack(stkdepth,-1);
					adjustMaxLocal(i.imm[0]);
					break;
				case OP_setlocal0:
				case OP_setlocal1:
				case OP_setlocal2:
				case OP_setlocal3:
					stkdepth = adjustValueStack(stkdepth,-1);
					adjustMaxLocal(i.opcode - OP_setlocal0);
					break;
					
				case OP_setglobalslot:
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
					
				case OP_setproperty:
				case OP_setsuper:
					//  FIXME: Runtime names.
					stkdepth = adjustValueStack(stkdepth,-2);
					break;
					
				case OP_setslot:
					stkdepth = adjustValueStack(stkdepth,-1);
					if ( max_slot < i.imm[0])
						max_slot = i.imm[0];
					break;
					
				case OP_strictequals:
				case OP_subtract:
				case OP_subtract_i:
				case OP_throw:
				case OP_urshift:
					stkdepth = adjustValueStack(stkdepth,-1);
					break;
						
				default:
						//  no effect on stack, scope, or slots
				}
				
				if ( i.target != null )
				{
					Block target_block = blocksByLabel.get(i.target);
					if (null == target_block)
						throw new IllegalArgumentException("Label " + i.target + " was referenced, but never defined.");
					
					//  FIXME: Check that these agree.
					stkin.put(target_block, stkdepth);
					scpin.put(target_block, scpdepth);
				}
			}
		}
	}

	private boolean isCatchTarget(Block b)
	{
		Label block_label = labelsByBlock.get(b);

		if ( block_label != null )
		{
			for ( ExceptionInfo info: this.exceptions)
			{
				if ( info.target.equals(block_label))
					return true;
			}
		}
		
		return false;
	}

	private void adjustMaxLocal(int idx)
	{
		if ( max_local <= idx)
			max_local = idx+1;
	}

	private int adjustValueStack(int stkdepth, int incr)
	{
		stkdepth += incr;

		if ( stkdepth < 0 )
			System.err.println("Warning: stack underflow.");
		if ( stkdepth > this.max_stack)
			this.max_stack = stkdepth;
		return stkdepth;
	}
	
	private int adjustScopeStack(int scpdepth, int incr)
	{
		scpdepth += incr;
		
		if ( scpdepth < 0 )
			System.err.println("Warning: scope stack underflow.");
		if ( scpdepth > this.max_scope)
			this.max_scope = scpdepth;
		return scpdepth;
	}

	void dump(java.io.PrintStream out)
	{	
		for ( Block b: blocks )
		{
			if ( labelsByBlock.containsKey(b) )
			{
				out.println(labelsByBlock.get(b) + ":");
			}
			else
			{
				out.println("<unnamed>:");
			}
			
			for (Instruction i: b.insns )
			{
				out.println("\t" + i);
				if ( i.target != null )
				{
					if ( !blocksByLabel.containsKey(i.target) )
					{
						out.println("\t... ? unresolved target \"" + i.target + "\"");
					}
				}
			}
		}
	}

	public int getMaxStack()
	{
		if ( explicit_max_stack != null )
			return explicit_max_stack;
		else
			return max_stack;
	}
	
	public int getLocalCount()
	{
		if ( explicit_max_local != null )
			return explicit_max_local;
		else
			return max_local;
	}
	
	public int getMaxSlotCount()
	{
		if ( explicit_max_slot != null )
			return explicit_max_slot;
		else if ( max_slot < traits.size() )
			return traits.size();
		else
			return max_slot;
	}
	
	public int getMaxScopeDepth()
	{
		if ( explicit_max_scope != null )
			return explicit_max_scope;
		else
			return max_scope;
	}
	
	public Block getBlock(Label target)
	{
		if (! blocksByLabel.containsKey(target))
			throw new IllegalArgumentException("Label " + target.toString() + " was referenced, but never defined.");
		return blocksByLabel.get(target);
	}
	
	public void addExceptionInfo(ExceptionInfo ex)
	{
		this.exceptions.add(ex);
	}
	
	/*
	 * Opcode mappings extracted from AbcConstants
	 */
	static Map<String, Integer> opcodeNameToOpcode = new HashMap<String, Integer>();
	static Map<Integer, String> opcodeToOpcodeName = new HashMap<Integer, String>();

	int decodeOpcodeName(String opcodeName)
	{
		String opcodeKey = opcodeName.toLowerCase();
		
		if ( opcodeNameToOpcode.size() == 0)
		{
			loadOpcodes();
		}
		
		if ( !opcodeNameToOpcode.containsKey(opcodeKey) )
			throw new IllegalArgumentException("opcode: \"" + opcodeName + "\" has no value in AbcConstants.");
		
		return opcodeNameToOpcode.get(opcodeKey);
	}

	static private void loadOpcodes()
	{
		//  Traverse the names of the OP_foo constants
		//  in AbcConstants and load their values.
		for ( Field f: AbcConstants.class.getFields())
		{
			String field_name = f.getName();
			
			if ( field_name.startsWith("OP_"))
			{
				String opcode = field_name.substring(3);
				try
				{
					int field_value = f.getInt(null);
					opcodeNameToOpcode.put(opcode, field_value);
					opcodeToOpcodeName.put(field_value, opcode);
				}
				catch ( Exception noFieldValue)
				{
					//  Ignore, continue...
				}
					
			}
		}
	}
	
	static String decodeOp(int opcode)
	{
		if ( opcodeToOpcodeName.containsKey(opcode))
			return opcodeToOpcodeName.get(opcode);
		else
			return "OP_" + Integer.toHexString(opcode);
	}

	public int getInitScopeDepth() 
	{
		if ( this.explicit_init_scope != null )
			return explicit_init_scope;
		else
			return 0;
	}

}
