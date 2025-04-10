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

import static abcasm.AbcConstants.*;
import java.util.*;

class Function
{
		String name;
		int    method_id;
		//  FIXME: Move this somewhere else!
		static int method_table_count = 0;
		
		List<Block> blocks = new LinkedList<Block>();
		Map<Label, Block> blocksByLabel = new TreeMap<Label, Block>();
		Map<Block, String> labelsByBlock = new HashMap<Block, String>();

		int max_stack = 0;
		int max_scope = 0;
		int max_local = 1;	//  FIXME: Should start at param count
		int max_slot  = 0;
		
		/**
		 *  Block currently being built; used during the function's construction. 
		 */
		Block currentBlock;

		Function(String fname)
		{
			this.name = fname;
			this.method_id = method_table_count++;
			startBlock();
		}
		
		void startBlock(Label name)
		{
			assert(name != null && !blocksByLabel.containsKey(name));

			//  If a branch insn just started a block,
			//  starting a new one is redundant.
			if ( !currentBlock.insns.isEmpty() )
			{
				startBlock();
			}
		
			blocksByLabel.put(name, currentBlock);
			labelsByBlock.put(currentBlock, name.toString());
		}

		void startBlock()
		{
			this.currentBlock = new Block();
			blocks.add(currentBlock);
		}
		public void insn(int opcode, int[] imm)
		{
			this.currentBlock.insns.add(new Instruction(opcode, imm));	
		}
		
		void insn(int opcode, Name name, int[] imm)
		{
			Instruction i = new Instruction(opcode, imm);
			this.currentBlock.insns.add(i);
			i.n = name;
		}
		
		void insn(int opcode, Label target)
		{
			Instruction i = new Instruction(opcode, new int[0]);
			this.currentBlock.insns.add(i);
			i.target = target;
		}
		
		public void insn(int opcode, Object pooledValue)
		{
			Instruction i = new Instruction(opcode, pooledValue);
			this.currentBlock.insns.add(i);
		}
		
		/**
		 *  Compute a functions's max_stack, max_scope, and slot count.
		 */
		void computeFrameCounts()
		{
			Map<Block,Integer>stkin = new HashMap<Block,Integer>();
			Map<Block,Integer>scpin = new HashMap<Block,Integer>();
			
			
			int stkdepth = 0;
			int scpdepth = 0;

			for ( Block b: blocks )
			{	
				if ( stkin.containsKey(b))
				{
					//  FIXME: should check that these agree.
					stkdepth = stkin.get(b);
					scpdepth = scpin.get(b);
				}

				for (Instruction i: b.insns)
				{
					boolean ignored_insn = false;
					
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
						ignored_insn = true;
							//  no effect on stack, scope, or slots
					}
					
					if ( i.target != null )
					{
						Block target_block = blocksByLabel.get(i.target);
						assert(target_block != null);
						//  FIXME: Check that these agree.
						stkin.put(target_block, stkdepth);
						scpin.put(target_block, scpdepth);
					}
					
					/*
					if ( !ignored_insn )
						System.out.println(opNames[i.opcode] + " " + stkdepth + " " + scpdepth + " " + max_local);
					else
						System.out.println("..ignored:" + opNames[i.opcode]);
					*/
				}
			}
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
				System.err.println("Warning: stack underflow in function " + name);
			if ( stkdepth > this.max_stack)
				this.max_stack = stkdepth;
			return stkdepth;
		}
		
		private int adjustScopeStack(int scpdepth, int incr)
		{
			scpdepth += incr;
			
			if ( scpdepth < 0 )
				System.err.println("Warning: scope stack underflow in function " + name);
			if ( scpdepth > this.max_scope)
				this.max_scope = scpdepth;
			return scpdepth;
		}

		void dump(java.io.PrintStream out)
		{
			out.println("function " + this.name);
			
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
		return max_stack;
	}
	
	public int getLocalCount()
	{
		return max_local;
	}

	public int getScopeDepth()
	{
		return max_scope;
	}

	public Block getBlock(Label target)
	{
		assert(this.blocksByLabel.containsKey(target));
		return this.blocksByLabel.get(target);
	}
}
