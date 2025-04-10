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


import java.util.*;
import java.lang.reflect.Field;
import static abcasm.AbcConstants.*;

class AssemblerCore
{
	AssemblerOptions options;

	/**
	 *  Scripts defined by this translation unit.
	 */
	Vector<ScriptInfo> scripts = new Vector<ScriptInfo>();
	
	/**
	 * Functions defined by this translation unit in method ID order.
	 */
	Vector<MethodInfo> methodSignatures = new Vector<MethodInfo>();
	int methodMasterId = 0;

	Map<String,Integer> methodsByName = new HashMap<String,Integer>();

	/**
	 *  Method bodies, in entry order.
	 */
	List<MethodBodyInfo> methodBodies = new ArrayList<MethodBodyInfo>();
	
	List<String> syntaxErrors = new LinkedList<String>();
	List<String> semanticErrors = new LinkedList<String>();

	/*
	 *  ABC pools.
	 */
	Pool<Name> namePool = new Pool<Name>(1);
	Pool<String> stringPool = new Pool<String>(1);
	Pool<Integer> intPool = new Pool<Integer>(1);
	Pool<Long> uintPool = new Pool<Long>(1);
	Pool<Double> doublePool = new Pool<Double>(1);
	Pool<Namespace> nsPool = new Pool<Namespace>(1);
	Pool<Nsset> nssetPool = new Pool<Nsset>(1);

	AssemblerCore(AssemblerOptions options)
	{
		this.options = options;
	}

	void addMethodInfo(MethodInfo new_function)
	{
		if ( methodsByName.containsKey(new_function.methodName) )
		{
			throw new IllegalArgumentException (
				"Duplicate method name: " + new_function.methodName
			);
		}
		methodSignatures.add(new_function);
		new_function.methodId = methodMasterId++;

		if ( new_function.methodName != null )
		{
			createPoolId(new_function.methodName);
			methodsByName.put(new_function.methodName, new_function.methodId);
		}
	}

	void addMethodBodyInfo(MethodBodyInfo new_body)
	{
		methodBodies.add(new_body);
	}

	Integer createPoolId(Object value)
	{
		if ( value instanceof Integer )
		{
			Integer iKey = (Integer)value;
			return intPool.add(iKey);
		}
		else if ( value instanceof Long )
		{
			Long lKey = (Long)value;
			return uintPool.add(lKey);
		}
		else if ( value instanceof Double )
		{
			Double dKey = (Double)value;
			return doublePool.add(dKey);
		}
		else if ( value instanceof String )
		{
			String sKey = (String)value;
			return stringPool.add(sKey);
		}
		else if ( value instanceof Namespace )
		{
			Namespace nsKey = (Namespace)value;
			if ( nsKey.name.equals("*") )
				return 0;
			else
				return nsPool.add(nsKey);
		}
		else
			throw new IllegalArgumentException("Don't have a pool for " + value.getClass().getSimpleName());
	}
	
	int getPoolId(Object value )
	{
		if ( null == value )
		{
			throw new IllegalArgumentException("null object has no pool value");
		}
		else if ( value instanceof Integer )
		{
			Integer iKey = (Integer)value;
			return intPool.id(iKey);
		}
		else if ( value instanceof Long )
		{
			Long lKey = (Long)value;
			return uintPool.id(lKey);
		}
		else if ( value instanceof Double )
		{
			Double dKey = (Double)value;
			return doublePool.id(dKey);
		}
		else if ( value instanceof String )
		{
			String sKey = (String)value;
			return stringPool.id(sKey);
		}
		else
			throw new IllegalArgumentException("Don't have a pool for " + value.getClass().getSimpleName());
	}

	void semanticAssertion(boolean cond, String diagnostic )
	{
		if (!cond)
			semanticErrors.add(diagnostic);
	}

	void syntaxError(String diagnostic)
	{
		syntaxErrors.add(diagnostic);
	}
	
	void dump(java.io.PrintStream out)
	{
		for ( String fname: methodsByName.keySet() )
			/* FIXME: not working right now... functionsByName.get(fname).dump(out) */;
	}

	Name getName(String unqualifiedName)
	{
		//  Ensure the package namespace is present.
		getNamespace("package");
		Name result = new Name(unqualifiedName);
		
		if ( !"*".equals(unqualifiedName))
		{
			namePool.add(result);
			stringPool.add(unqualifiedName);
		}

		return result;
	}
	
	Name getName(Nsset qualifiers, String baseName)
	{
		Name result = new Name(qualifiers, baseName);
		
		namePool.add(result);
		stringPool.add(baseName);
		return result;
	}
	
	Namespace getNamespace(String nsName)
	{
		Namespace result;
		String nsPoolName;

		if ( "Package".equalsIgnoreCase(nsName))
		{
			nsPoolName = "";
			result = new Namespace(CONSTANT_PackageNs, "");
		}
		else if ( "Private".equalsIgnoreCase(nsName))
		{
			nsPoolName = "";
			result = new Namespace(CONSTANT_PrivateNs, "");
		}
		else if ( "Namespace".equalsIgnoreCase(nsName))
		{
			nsPoolName = "";
			result = new Namespace(CONSTANT_Namespace, "");
		}
		else
		{
			nsPoolName = nsName;
			result = new Namespace(CONSTANT_Namespace, nsName);
		}
		
		stringPool.add(nsPoolName);
		nsPool.add(result);
		return result;
	}
	
	Nsset getNsset(Vector<Namespace> namespaces)
	{
		Nsset result = new Nsset(namespaces);
		this.nssetPool.add(result);
		return result;
	}
	
	/**
	 *  Supports a convenience in the syntax:
	 *  if a multiname doesn't have qualfiers,
	 *  then hack together a Nsset with the
	 *  commonly-searched namespaces.
	 * 	@return
	 */
	Nsset getUsualSuspectNamespaces()
	{
		Vector<Namespace> namespaces = new Vector<Namespace>();
		namespaces.add(getNamespace("package"));
		namespaces.add(getNamespace("private"));
		
		return getNsset(namespaces);
	}
	
	Label getLabel(String labelName)
	{
		return new Label(labelName);
	}
	
	int generated_label_serial = 0;
	Label generateLabel(String labelPrefix)
	{
		return getLabel(labelPrefix + " #" + generated_label_serial++);
	}
	
	void addScript(ScriptInfo s)
	{
		scripts.add(s);
	}
	
	void semanticAnalysis()
	{
		//  Add a default script if none was specified.
		if ( scripts.isEmpty() )
		{
			scripts.add(new ScriptInfo());
		}
		else
		{
			for ( ScriptInfo s: scripts )
			{
				s.init_id  = translateImmediate(s.init_id);
				finishTraits(s.traits);
			}
		}
		
		//  TODO: Classes change these semantics.
		if ( scripts.size() == 1 )
			pushTraits(scripts.elementAt(0).traits);
		
		for ( MethodBodyInfo info: methodBodies)
		{
			info.methodId = translateImmediate(info.methodId);
			finishTraits(info.traits);
			
			pushTraits(info.traits);
			for ( Block b: info.blocks )
			{
				for ( Instruction insn: b.insns)
				{
					if ( insn.operands != null )
					{
						insn.imm = new int[insn.operands.length];
						for ( int i = 0; i < insn.operands.length; i++)
						{
							try
							{
								insn.imm[i] = translateImmediate(insn.operands[i]);
							}
							catch ( IllegalArgumentException ex )
							{
								System.err.println("Method " + this.methodSignatures.elementAt(info.getMethodId()).methodName 
										+ " insn " + insn.toString() + " untranslatable: " + ex.getMessage() );
								throw ex;
							}
						}
					}
				}
			}
			popTraits();
		}
		
		if ( scripts.size() == 1 )
			popTraits();
	}
	
	/**
	 * Ensure that all required traits entries are present.
	 * @param traits - the traits to finish.
	 */
	private void finishTraits(Traits traits)
	{	
		int slot_id = 1;
		
		for ( Trait t: traits )
		{
			if ( TRAIT_Var == t.getKind())
			{
				if ( t.hasAttr("slot_id") )
				{
					slot_id = Math.max(t.getIntAttr("slot_id") + 1, slot_id);
				}
				else
				{
					t.setAttr("slot_id", new Integer(slot_id++));
				}
				
				if ( !t.hasAttr("type_name"))
				{
					//  Unspecified type is type ANY.
					t.setAttr("type_name", new Name("*"));
				}
			}
		}
	}

	Integer translateImmediate(Object immediate_operand)
	{
		if ( null == immediate_operand )
		{
			throw new IllegalArgumentException("Unable to translate null operand");
		}

		Integer result = null;
		if ( immediate_operand instanceof Integer )
		{
			//  ID was specified.
			result = (Integer) immediate_operand;
		}
		else if ( immediate_operand instanceof SymbolicReference )
		{
			SymbolicReference symconst = (SymbolicReference) immediate_operand;
			
			if ( SymbolicReference.function_id == symconst.kind )
			{
				//  ID should be in the table.
				if ( methodsByName.containsKey(symconst.symbolicReference))
					result = methodsByName.get(symconst.symbolicReference);
			}
			else if ( SymbolicReference.slot_id == symconst.kind )
			{
				
				for ( int i = staticScopes.size() -1; i >= 0 && null == result; i-- )
				{
					result = staticScopes.elementAt(i).getSlotId(symconst.symbolicReference);
				}
			}
		}

		if ( null == result )
		{
			throw new IllegalArgumentException("Unknown operand " + immediate_operand + ", type " + immediate_operand.getClass().getCanonicalName());
		}
		
		return result;
	}
	
	int getNameId(Name n)
	{
		if ( null == n  || n.baseName.equals("*"))
			return 0;
		else
			return namePool.id(n);
	}

	MethodInfo getMethod(Object method_key)
	{
		int method_index = translateImmediate(method_key);
		return methodSignatures.elementAt(method_index);
	}
	java.util.Vector<Traits> staticScopes = new java.util.Vector<Traits>();
	
	void pushTraits(Traits traits) 
	{	
		staticScopes.add(traits);
	}
	
	
	void popTraits()
	{
		staticScopes.remove(staticScopes.size()-1);
	}
}
