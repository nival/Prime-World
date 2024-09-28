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

import org.antlr.runtime.*;


import java.io.FileInputStream;

public class Main
{

	public static void main(String[] argv)
		throws Exception
	{
		AssemblerOptions options = new AssemblerOptions(argv);
		
		for ( String asmFile: options.asmFile )
		{
			assemble(asmFile, options);
		}
	}

	public static void assemble(String asmFile, AssemblerOptions options)
		throws Exception
	{
		if ( options.verbose )
			System.out.println("assembling " + asmFile );
		
		abcasmLexer lexer = new abcasmLexer(new ANTLRFileStream(asmFile));
		
		CommonTokenStream tokens = new CommonTokenStream();
		tokens.setTokenSource(lexer);
		abcasmParser parser = new abcasmParser(tokens);

		AssemblerCore core = new AssemblerCore(options);
		parser.asmCore = core;

		try
		{
			parser.translation_unit();
		}
		catch ( Throwable parser_fatal )
		{
			if ( options.expandedDiagnostics )
				parser_fatal.printStackTrace();
			core.syntaxErrors.add(parser_fatal.getMessage());
		}

		if ( core.syntaxErrors.size() > 0 )
		{
			System.err.println("Unable to assemble " + asmFile + " due to syntax errors:");
			for ( String s: core.syntaxErrors )
			{
				System.err.println(s);
			}

			return;
		}
		
		if ( options.dumpIl )
			core.dump(System.out);
		
		
		//  Parsing successful, do the results make sense?
		core.semanticAnalysis();
		
		if ( core.semanticErrors.size() > 0 )
		{
			System.err.println("Unable to assemble " + asmFile + " due to:");

			for ( String s: core.semanticErrors )
			{
				System.err.println(s);
			}

			return;
		}
		
		//  Emit the bytecode.
		try
		{
			String binary_file_name;
			int last_dot = asmFile.lastIndexOf(".");
			
			if ( last_dot == (asmFile.length() - 4) && asmFile.substring(last_dot).equalsIgnoreCase(".abs") )
				binary_file_name = asmFile.substring(0, last_dot) + ".abc";
			else
				binary_file_name = asmFile + ".abc";
			
			byte[] abc_binary = new AbcEmitter(core).emit();
			java.io.OutputStream output = new java.io.FileOutputStream(binary_file_name);
			output.write(abc_binary);
		}
		catch ( Exception ex )
		{
			System.err.println("Unable to emit due to: ");
			ex.printStackTrace();
			System.exit(1);
		}
	}
}
