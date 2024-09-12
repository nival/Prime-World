using System;
using System.Collections.Generic;
using DBCodeGen.Utils;
using DBCodeGen.VisualStudioSupport;
using libdb.DB;

namespace DBCodeGen.CodeGeneration
{
	internal static class Header
	{
		public static void WriteHeader( CodeWriter header )
		{
			header.WriteLine( "#pragma once" );
			header.WriteLine( "// Automatically generated file, don't change it manually!" );
		}

		public static void WriteIncludes( CodeWriter header, IEnumerable<CodeFile> dependencies )
		{
			header.WriteLine();
			header.WriteLine( "#include \"../libdb/Db.h\"" );
			header.WriteLine( "#include \"../libdb/Animated.h\"" );
			header.WriteLine( "#include \"../libdb/AnimatedAlgorithms.h\"" );

			foreach ( CodeFile file in dependencies )
			{
				if (file.Project == "libdb" && file.Name == "DB")
					continue;
				if (file.Project == "Scripts" && file.Name == "TypeWrapper")
					continue;

				header.WriteLine( "#include \"../{0}/{1}.h\"", file.Project, file.Name );
			}

			header.WriteLine();
			header.WriteLine( "struct IXmlSaver;" );
		}

		public static void WriteOpenNamespace( CodeWriter header )
		{
			header.WriteLine();
			header.WriteLine( "namespace NDb" );
			header.WriteLine( "{" );
		}

		public static void WriteForwardDeclarations( CodeWriter header, IEnumerable<Type> forwards )
		{
			bool hasForwards = false;
			foreach ( Type type in forwards )
			{
                if (type.Name == "DBResource")
                    continue;

				hasForwards = true;
				if ( !TypeUtils.HasAttribute<NoCodeAttribute>(type, false) )
					header.WriteLine( "struct {0};", DBCodeGen.GetTypeName( type ) );
			}
			if ( hasForwards )
				header.WriteLine();
		}

		public static void WriteCloseNamespace( CodeWriter header )
		{
			header.WriteLine( "}; // namespace NDb" );
		}

		private static int CompareClassNames( string a, string b )
		{
			bool nameSpaceA = a.IndexOf( "::" ) >= 0;
			bool nameSpaceB = b.IndexOf( "::" ) >= 0;
			if ( nameSpaceA == nameSpaceB )
				return string.Compare( a, b );

			return nameSpaceA ? -1 : 1;
		}

		public static void WriteFactoryForwardDeclarations( CodeWriter header, IEnumerable<string> forwards )
		{
			List<string> forwardDeclarations = new List<string>( forwards );
			if ( forwardDeclarations.Count == 0 )
				return;

			header.WriteLine( "// forward declarations for factories" );
			forwardDeclarations.Sort( CompareClassNames );
			string nameSpace = string.Empty;
			foreach ( string forward in forwards )
			{
				int nameSpacePos = forward.IndexOf( "::" );
				string thisNameSpace = nameSpacePos < 0 ? string.Empty : forward.Substring( 0, nameSpacePos );
				string className = nameSpacePos < 0 ? forward : forward.Substring( nameSpacePos + 2 );
				if ( thisNameSpace != nameSpace )
				{
					if ( !string.IsNullOrEmpty( nameSpace ) )
						header.WriteLine( "}}; //namespace {0}", nameSpace );
					nameSpace = thisNameSpace;
					if ( !string.IsNullOrEmpty( nameSpace ) )
					{
						header.WriteLine( "namespace {0}", nameSpace );
						header.WriteLine( "{" );
					}
				}
				header.WriteLine( string.IsNullOrEmpty( nameSpace ) ? 0 : 1, "class {0};", className );
			}
			if ( !string.IsNullOrEmpty( nameSpace ) )
				header.WriteLine( "}}; //namespace {0}", nameSpace );
		}

		public static void WriteFactoryDeclaration( CodeWriter header, FactoryBaseAttribute factory )
		{
			header.WriteLine( 1, "virtual {0} {1}({2}{3}{2}) const;", factory.GetReturnType(), factory.FactoryFunctionName, factory.Args.Length > 0 ? " " : "", string.Join( ", ", factory.Args ) );
		}
	}
}
