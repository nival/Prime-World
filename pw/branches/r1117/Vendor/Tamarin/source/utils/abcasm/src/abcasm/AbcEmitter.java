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

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.BitSet;
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

class AbcEmitter
{
	AssemblerCore core;
	AbcWriter w;
	
	public AbcEmitter(AssemblerCore core)
	{
		this.core = core;
		this.w = new AbcWriter();
	}
	
	public byte[] emit()
	throws Exception
	{
		w.writeU16(16);
		w.writeU16(46);

		int pos = w.size();
		w.writeU30(core.intPool.size());
		for (int x: core.intPool.getValues())
			w.writeU30(x);
		
		pos = w.size();
		
		w.writeU30(core.uintPool.size());
		for (long x: core.uintPool.getValues())
			w.writeU30((int)x);

		pos = w.size();
		
		w.writeU30(core.doublePool.size());
		for (double x: core.doublePool.getValues())
			w.write64(Double.doubleToLongBits(x));

		pos = w.size();

		w.writeU30(core.stringPool.size());
		for (String s: core.stringPool.getValues())
		{
			w.writeU30(s.length());
			w.write(s.getBytes("UTF-8"));
		}
		
		pos = w.size();
		
		w.writeU30(core.nsPool.size());
		for (Namespace ns: core.nsPool.getValues())
			emitNamespace(ns);
		pos = w.size();
		
		w.writeU30(core.nssetPool.size());
		for (Nsset nsset: core.nssetPool.getValues())
		{
			w.writeU30(nsset.length());
			for (Namespace ns: nsset)
				w.writeU30(core.nsPool.id(ns));
		}
		pos = w.size();
		
		w.writeU30(core.namePool.size());
		for (Name n: core.namePool.getValues())
		{
			w.write(n.kind);
			switch (n.kind)
			{
			case CONSTANT_Qname:
			case CONSTANT_QnameA:
				w.writeU30(core.nsPool.id(n.getSingleQualifier()));
				w.writeU30(core.stringPool.id(n.baseName));
				break;
			case CONSTANT_Multiname:
			case CONSTANT_MultinameA:
				w.writeU30(core.stringPool.id(n.baseName));
				w.writeU30(core.nssetPool.id(n.qualifiers));
				break;
			/*
			case CONSTANT_RTQname:
			case CONSTANT_RTQnameA:
				w.writeU30(core.stringPool.id(n.name));
				break;
			case CONSTANT_MultinameL:
			case CONSTANT_MultinameLA:
				w.writeU30(core.nssetPool.id(n.nsset));
				break;
			case CONSTANT_RTQnameL:
			case CONSTANT_RTQnameLA:
				break;
			case CONSTANT_TypeName:
				throw new IllegalArgumentException("Not implemented.");
				*/
			default:
				{
					assert (false);
					throw new IllegalArgumentException("Not implemented.");
				}
			}
		}

		pos = w.size();
			
		w.writeU30(core.methodSignatures.size());

		int method_id=0;
		for (MethodInfo mi: core.methodSignatures)
			emitMethodInfo(mi);
		/*
		for (Method m: core.nativeFunctions.values)
			emitMethod(abc, w, method_id++, m);
		*/
		
		w.writeU30(0);
		/*
		w.writeU30(core.metaPool.size());
		for (Metadata md: core.metaPool.values)
		{
			w.writeU30(core.stringPool.id(md.name));
			w.writeU30(md.attrs.length);
			for (Attr a: md.attrs)
				w.writeU30(core.stringPool.id(a.name));
			for (Attr a: md.attrs)
				w.writeU30(core.stringPool.id(a.value));
		}
		*/
		
		w.writeU30(0);
		/*
		w.writeU30(core.classes.size());
		for (Type c: core.classes)
		{
			Type t = c.itype;
			w.writeU30(core.namePool.id(t.getName()));
			w.writeU30(core.typeRef(t.base));
			w.write(t.flags);
			if (t.hasProtectedNs())
				w.writeU30(core.nsPool.id(t.protectedNs));
			w.writeU30(t.interfaces.length);
			for (Type i: t.interfaces)
				w.writeU30(core.interfaceRef(i));
			w.writeU30(core.methodId(t.init));
			emitTraits(w, abc, t);
		}
		/*
		for (Type c: core.classes)
		{
			w.writeU30(core.methodId(c.init));
			emitTraits(w, abc, c);
		}
		*/

		w.writeU30(core.scripts.size());
		for (ScriptInfo s: core.scripts)
		{
			emitScriptInfo(s);
		}
		
		w.writeU30(core.methodBodies.size());
		for ( MethodBodyInfo f: core.methodBodies)
		{
			emitMethodBody(f);
		}
	
		return w.toByteArray();
	}
	
	private void emitTraits(AbcWriter w, Traits traits)
	{
		w.writeU30(traits.getTraitCount());
		
		for ( Trait t: traits)
		{
			w.writeU30(core.namePool.id(t.getNameAttr("name")));
			w.write(t.kind_byte);

			switch (t.getKind())
			{
			case TRAIT_Var:
					w.writeU30(t.getIntAttr("slot_id"));
					w.writeU30(core.getNameId(t.getNameAttr("type_name")));
					//  TODO: vindex and vkind
					w.writeU30(0);
					// w.write(0); //  TODO: write vkind when vindex !0
				break;
			case TRAIT_Method:
			case TRAIT_Function:
			case TRAIT_Getter:
			case TRAIT_Setter:

				if (t.hasAttr("disp_id"))
					w.writeU30(t.getIntAttr("disp_id"));
				else
					w.writeU30(0);

				w.writeU30(core.translateImmediate(t.getAttr("method_id")));
				break;
			default:
				throw new IllegalArgumentException("Unknown trait kind " + t.getKind());
			}
		}
	}

	private void emitScriptInfo(ScriptInfo info)
	{
		w.writeU30(info.getInitId());
		emitTraits(w, info.getTraits());
	}

	private void emitMethodInfo(MethodInfo info)
	{
		w.writeU30(info.paramTypes.size());
		w.writeU30(core.getNameId(info.returnType));

		for (int i=0, n=info.paramTypes.size(); i < n; i++)
			w.writeU30(core.getNameId(info.paramTypes.elementAt(i)));

		w.writeU30(core.getPoolId(info.methodName));
		w.write(info.flags);		
	}

	private void emitMethodBody(MethodBodyInfo f)
	throws Exception
	{
		MethodInfo signature = core.getMethod(f.methodId);
		
		w.writeU30(signature.methodId);
		f.computeFrameCounts();

		w.writeU30(f.getMaxStack());
		
		int max_local = f.getLocalCount();
		if ( signature.getParamCount() > max_local )
			max_local = signature.getParamCount();
		
		w.writeU30(max_local);
		
		w.writeU30(f.getInitScopeDepth());
		w.writeU30(f.getMaxScopeDepth());
		
		emitCode(f);
		
		emitTraits(w, f.traits);
	}

	private void emitCode(MethodBodyInfo f) 
	throws Exception
	{		
			Map<Block,Integer> padding = new HashMap<Block,Integer>();
			Map<Block,AbcWriter> writers = new HashMap<Block,AbcWriter>();

			// emit the code and leave room for the branch offsets,
			// and compute the final position of each block.
			Map<Block,Integer> pos = new HashMap<Block,Integer>();
			Map<Block,Integer> blockends = new HashMap<Block,Integer>();
			int code_len = 0;

			//  First, generate code for each block.
			//  Keep a running tally of the code length,
			//  which corresponds to the starting position
			//  of each block.
			for ( Block b: f.blocks)
			{
				pos.put(b,code_len);
				AbcWriter blockWriter = new AbcWriter();
				writers.put(b, blockWriter);

				emitBlock(b, blockWriter);
				
				code_len += blockWriter.size();
				
				//  Blocks with no instructions are
				//  valid assembly constructs.
				if ( b.insns.size() == 0)
					continue;
		
				//  If the last instruction in the block
				//  is a jump, leave room for the instruction,
				//  but don't emit it yet.
				Instruction last = b.insns.lastElement();
		
				if (null != last.target)
				{
					//  if it's a single branch/fallthrough
					//  Reserve space for the jump instruction.
					code_len += 4;
					padding.put(b, 4);
				}
				/*
				else  FIXME: multibranch support
				{
					Block target_block = f.getBlock(last.target);
					if (work.isEmpty() || target_block != work.peekFirst())
					{
						code_len += 8;
						padding.put(b, 8);
					}
					else
					{
						code_len += 4;
						padding.put(b, 4);
					}
				}
				*/
				blockends.put(b,code_len);
			}

			w.writeU30(code_len);
			int code_start = w.size();
			
			for (Block b: f.blocks)
			{
				writers.get(b).writeTo(w);
				if (padding.containsKey(b))
				{
					Instruction last = b.insns.lastElement();
					
					if (last.target != null)
					{
						assert(padding.containsKey(b));
						emitBranch(last.opcode, f.getBlock(last.target), code_start, pos);
					}

					if ( OP_lookupswitch == last.opcode )
					{
						throw new IllegalStateException("OP_lookupswitch not implemented.");
						//emitLookupswitch(out, last, code_start, pos);
					}
				}
			}
			
			emitExceptionInfo(f, w, f.exceptions, pos);
	}

	private void emitBranch(int opcode, Block target, int code_start, Map<Block, Integer> pos)
	{
		w.write(opcode);
		int to = code_start + pos.get(target);
		int from = w.size()+3;
		w.writeS24(to-from);
	}

	void emitBlock(Block b, AbcWriter blockWriter)
	{
		for ( int i = 0; i < b.insns.size() && b.insns.elementAt(i).target == null; i++)
		{
			Instruction insn = b.insns.elementAt(i);
			
			blockWriter.write(insn.opcode);
			switch (insn.opcode)
			{
			case OP_hasnext2:
				blockWriter.writeU30(insn.imm[0]);
				blockWriter.writeU30(insn.imm[1]);
				break;
			case OP_findproperty:
			case OP_findpropstrict:
			case OP_getlex:
			case OP_getsuper: case OP_setsuper:
			case OP_getproperty: case OP_setproperty:
			case OP_deleteproperty: case OP_getdescendants:
			case OP_initproperty:
			case OP_istype:
			case OP_coerce:
			case OP_astype:
			case OP_finddef:
					blockWriter.writeU30(core.namePool.id(insn.n));
				break;
			case OP_callproperty:
			case OP_callproplex:
			case OP_callpropvoid:
			case OP_callsuper:
			case OP_callsupervoid:
			case OP_constructprop:
				blockWriter.writeU30(core.namePool.id(insn.n));
				blockWriter.writeU30(argc(insn));
				break;
			case OP_constructsuper:
			case OP_call:
			case OP_construct:
			case OP_newarray:
			case OP_newobject:
				blockWriter.writeU30(argc(insn));
				break;
			case OP_getlocal:
			case OP_setlocal:
			case OP_getslot:
			case OP_setslot:
			case OP_kill:
			case OP_inclocal:
			case OP_declocal:
			case OP_inclocal_i:
			case OP_declocal_i:
			case OP_newcatch:
			case OP_getglobalslot:
			case OP_setglobalslot:
				blockWriter.writeU30(insn.imm[0]);
				break;
			case OP_newclass:
				//blockWriter.writeU30(abc.classId(e.c));
				throw new IllegalStateException("Not implemented.");
				//break;
			case OP_newfunction:
				blockWriter.writeU30(insn.imm[0]);
				break;
			case OP_applytype:
				blockWriter.writeU30(insn.imm[0]);
				break;
			case OP_callstatic:
				blockWriter.writeU30(insn.imm[0]);
				blockWriter.writeU30(insn.imm[1]);
				break;
			case OP_pushshort:
				blockWriter.writeU30(insn.imm[0]);
				break;
			case OP_pushbyte:
				blockWriter.write(insn.imm[0]);
				break;
			case OP_getscopeobject:
				blockWriter.write(insn.imm[0]);
				break;
			case OP_pushstring:
			case OP_dxns:
			case OP_debugfile:
				blockWriter.writeU30(insn.imm[0]);
				break;
			case OP_pushnamespace:
				blockWriter.writeU30(insn.imm[0]);
				break;
			case OP_pushint:
				blockWriter.writeU30(insn.imm[0]);
				break;
			case OP_pushuint:
				blockWriter.writeU30(insn.imm[0]);
				break;
			case OP_pushdouble:
				blockWriter.writeU30(insn.imm[0]);
				break;
			case OP_debugline:
			case OP_bkptline:
				blockWriter.writeU30(insn.imm[0]);
				break;
			case OP_debug:
				blockWriter.write(insn.imm[0]);
				blockWriter.writeU30(insn.imm[1]);
				blockWriter.write(insn.imm[2]);
				blockWriter.writeU30(insn.imm[3]);
				break;
			}
		}
	}

	private int argc(Instruction insn)
	{
		int argc;
		
		/*
		 * GlobalOptimizer makes this more complex,
		 * but the assembler puts all argcounts
		 * in the 0th immediate operand.
		switch(insn.opcode)
		{
		case OP_callproperty:
		case OP_callpropvoid:
			argc = insn.imm[0];
			break;
	
		default:
			
			throw new IllegalArgumentException("Unable to compute argument count for insn: " + insn.opcode);
		}
		*/
		argc = insn.imm[0];
		return argc;
	}

	private void emitNamespace(Namespace ns)
	{
		w.write(ns.kind);
		w.writeU30(core.getPoolId(ns.name));
	}
	
	private void emitExceptionInfo(MethodBodyInfo f, AbcWriter w, Vector<ExceptionInfo> exceptions, Map<Block, Integer> pos) 
	{
		w.writeU30(exceptions.size());
		
		for ( ExceptionInfo ex: exceptions)
		{
			w.writeU30(pos.get(f.getBlock(ex.from)));
			w.writeU30(pos.get(f.getBlock(ex.to)));
			w.writeU30(pos.get(f.getBlock(ex.target)));
			w.writeU30(ex.exc_type);
			w.writeU30(ex.name_id);
		}
	}

	class AbcWriter extends ByteArrayOutputStream
	{
		void rewind(int n)
		{
			super.count -= n;
		}
		void writeU16(int i)
		{
			write(i);
			write(i>>8);
		}
		
		void writeS24(int i)
		{
			writeU16(i);
			write(i>>16);
		}
		
		void write64(long i)
		{
			writeS24((int)i);
			writeS24((int)(i>>24));
			writeU16((int)(i>>48));
		}
		
		void writeU30(int v)
		{
			if (v < 128 && v >= 0)
			{
				write(v);
			}
			else if (v < 16384 && v >= 0)
			{
				write(v & 0x7F | 0x80);
				write(v >> 7);
			}
			else if (v < 2097152 && v >= 0)
			{
				write(v & 0x7F | 0x80);
				write(v >> 7 | 0x80);
				write(v >> 14);
			}
			else if (v < 268435456 && v >= 0)
			{
				write(v & 0x7F | 0x80);
				write(v >> 7 | 0x80);
				write(v >> 14 | 0x80);
				write(v >> 21);
			}
			else
			{
				write(v & 0x7F | 0x80);
				write(v >> 7 | 0x80);
				write(v >> 14 | 0x80);
				write(v >> 21 | 0x80);
				write(v >> 28);
			}
		}
		
		int sizeOfU30(int v)
		{
			if (v < 128 && v >= 0)
			{
				return 1;
			}
			else if (v < 16384 && v >= 0)
			{
				return 2;
			}
			else if (v < 2097152 && v >= 0)
			{
				return 3;
			}
			else if (v < 268435456 && v >= 0)
			{
				return 4;
			}
			else
			{
				return 5;
			}
		}
	}
}
