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


class Instruction
{
	/**
	 * @see AbcConstants
	 */
	int opcode;
	
	/**
	 *  Immediate operands as specified by the program,
	 *  symbolic references may still be present.
	 */
	Object[] operands;

	/**
	 *  Cooked immediate operands, symbolic references resolved.
	 */
	int [] imm;
	
	/**
	 *  Name reference for instructions that operate on a named entity.
	 */
	Name n;
	
	/**
	 *  Control-flow target for branch/jump instructions.
	 */
	Label target;
	
	Instruction(int opcode, Object[] operands)
	{
		this.opcode = opcode;
		this.operands = operands;
	}
	
	Instruction(int opcode, Object v)
	{
		this(opcode, new Object[]{v});
	}
	
	public String toString()
	{
		StringBuffer result = new StringBuffer(MethodBodyInfo.decodeOp(opcode));
		
		if ( n != null )
		{
			result.append(" ");
			result.append(n);
		}
		
		if ( target != null )
		{
			result.append(" ");
			result.append(target);
		}
		
		for ( Object x: operands)
		{
			result.append(" ");
			result.append(x);
		}
		
		return result.toString();
	}
}

