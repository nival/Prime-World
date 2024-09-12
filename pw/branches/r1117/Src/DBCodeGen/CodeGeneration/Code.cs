using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using DBCodeGen.Utils;
using DBCodeGen.VisualStudioSupport;
using libdb.DB;

namespace DBCodeGen.CodeGeneration
{
	internal static class Code
	{
		public static void WriteHeader( CodeWriter code, CodeFile file, IEnumerable<CodeFile> forwardFiles )
		{
			code.WriteLine( "// Automatically generated file, don't change it manually!" );
			code.WriteLine( "#include \"stdafx.h\"" );
			code.WriteLine( "#include \"../libdb/Checksum.h\"" );
			code.WriteLine( "#include \"../libdb/XmlSaver.h\"" );
			code.WriteLine( "#include \"../Scripts/lua.hpp\"" );
			code.WriteLine( "#include \"../Scripts/ScriptMacroses.h\"" );
            code.WriteLine( "#include \"System/StrUtils.h\"" );

			code.WriteLine();
      foreach ( CodeFile forwardFile in forwardFiles )
      {
        if ( string.IsNullOrEmpty( forwardFile.ForcedIncludeFile ) )
          code.WriteLine( "#include \"../{0}/{1}.h\"", forwardFile.Project, forwardFile.Name );
        else
          code.WriteLine( "#include \"{0}\"", forwardFile.ForcedIncludeFile );
      }
			code.WriteLine( "#include \"{0}.h\"", file.Name );
		}

		public static void WriteOpenNamespace( CodeWriter code )
		{
			code.WriteLine();
			code.WriteLine( "namespace NDb" );
			code.WriteLine( "{" );
		}

		public static void WriteCloseNamespace( CodeWriter code )
		{
			code.WriteLine( "}; // namespace NDb" );
		}

    public static void WriteRegistration( CodeWriter code, IEnumerable<Type> classes, string customName )
		{
			code.WriteLine( FormatHelper.CommentLine );
			foreach ( Type type in classes )
			{
				if ( ( !TypeUtils.HasAttribute<NoCodeAttribute>( type, false ) && !TypeUtils.HasAttribute<CrapTypeNameAttribute>( type, false ) ) || DBCodeGen.CheckCustomAttribute( type, customName, false ) )
				{
					if ( TypeUtils.CanCreate( type ) )
						code.WriteLine( "REGISTER_DBRESOURCE( {0} );", DBCodeGen.GetTypeName( type ) );
					else
						code.WriteLine( "BASIC_REGISTER_DBRESOURCE( {0} );", DBCodeGen.GetTypeName( type ) );
				}
			}
			code.WriteLine( FormatHelper.CommentLine );
		}

		public static void WriteFactoryIncludes( CodeWriter code, Dictionary<string, List<string>> includes )
		{
			if ( includes.Count == 0 )
				return;
			code.WriteLine();
			code.WriteLine( "// includes for factories" );
			
			List<string> defines = new List<string>( includes.Keys );
			defines.Sort();
			foreach ( string define in defines )
			{
				if ( !string.IsNullOrEmpty( define ) )
					code.WriteLine( "#if{0}def {1}", define[0] == '!' ? "n" : "", define.TrimStart( '!' ) );
				foreach ( string include in includes[define] )
					code.WriteLine( "#include \"{0}\"", include );
				if ( !string.IsNullOrEmpty( define ) )
					code.WriteLine( "#endif // #if{0}def {1}", define[0] == '!' ? "n" : "", define.TrimStart( '!' ) );
			}
		}

		private static string ExtractNameFromArgument( string arg )
		{
			Match m = Regex.Match( arg, @".*\s+(&|\*)*([A-Za-z_]?[A-Za-z_0-9]*)", RegexOptions.Compiled );
			if ( !m.Success || m.Groups.Count < 3 )
				return string.Empty;

			return m.Groups[2].Value;
		}

		public static void WriteFactoryImplementation( CodeWriter code, Type type, FactoryBaseAttribute factoryBase, FactoryImplAttribute factoryImpl )
		{
			code.WriteLine( "{0} {1}::{2}({3}{4}{3}) const", factoryBase.GetReturnType(), DBCodeGen.GetTypeName( type ), factoryBase.FactoryFunctionName, factoryBase.Args.Length > 0 ? " " : "", string.Join( ", ", factoryBase.Args ) );
			code.WriteLine( "{" );
			if ( factoryImpl == null )
				code.WriteLine( 1, "return ( {0} )(0);", factoryBase.GetReturnType() );
			else
			{
				string createFunction = string.Empty;
				if ( string.IsNullOrEmpty( factoryImpl.CreateFunction ) )
					createFunction = "new " + factoryImpl.ClassName;
				else
				{
					createFunction = factoryImpl.CreateFunction;
					bool inClass = createFunction.StartsWith( "$::" );
					bool needTemplate = createFunction.EndsWith( "<>" );
					if ( inClass )
						createFunction = factoryImpl.ClassName + "::" + createFunction.Substring( 3 );
					if ( needTemplate )
						createFunction = createFunction.Substring( 0, createFunction.Length - 2 ) + "<" + factoryImpl.ClassName + ">";
				}

				List<string> args = new List<string>();
				args.Add( string.Empty );
				args.AddRange( factoryBase.Args );
				for ( int i = 0; i < args.Count; ++i )
					args[i] = ExtractNameFromArgument( args[i] );

				code.WriteLine( 1, "return {0}( *this{1} );", createFunction, string.Join( ", ", args.ToArray() ) );
			}
			code.WriteLine( "}" );
		}
	}
}
