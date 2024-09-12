using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Xml;
using DBCodeGen.Utils;
using DBCodeGen.VisualStudioSupport;
using libdb.DB;
using System.Diagnostics;

namespace DBCodeGen.MaterialsGeneration
{
	public static class MaterialCompiler
	{
		public const string SAMPLER_CLASS_NAME = "Render::Sampler";
		public const string RENDERSTATE_CLASS_NAME = "Render::RenderState";
		public const string RENDERSTATE_NDB_CLASS_NAME = "NDb::RenderState";
		public const string MATERIAL_SPEC_FILE_NAME = "MaterialSpec";
		public const string BASE_MATERIAL_CLASS_NAME = "BaseMaterial";
		public const string BASE_MATERIAL_INTERFACE_NAME = "IBaseMaterial";
		public const string RUNTIME_PINS_CLASS_NAME = "RuntimePins";
		public const string RENDER_MATERIAL_CLASS_NAME = "Render::Material";
		public const string SHADERS_FOLDER_NAME = "Shaders";

		private delegate bool TypeOperator( Type type );
		private static bool ExtractTypesFromAssembly( Assembly assembly, bool includeReferences, TypeOperator operation )
		{
			foreach ( Type type in assembly.GetTypes() )
			{
				if ( !operation( type ) )
					return false;
			}

			if ( includeReferences )
			{
				foreach ( AssemblyName refAssemblyName in assembly.GetReferencedAssemblies() )
				{
          Assembly refAssembly = null;
          string relFileName = Path.Combine( Path.GetDirectoryName( assembly.Location ), refAssemblyName.Name ) + ".dll";
          if ( File.Exists( relFileName ) )
            refAssembly = Assembly.LoadFrom( relFileName );
          else
            refAssembly = Assembly.Load( refAssemblyName.FullName );
          if ( !ExtractTypesFromAssembly( refAssembly, false, operation ) )
						return false;
				}
			}

			return true;
		}

		private static TValue GetValue<TKey, TValue>( Dictionary<TKey, TValue> dict, TKey key ) where TValue : class, new()
		{
			TValue result = null;
			if ( !dict.TryGetValue( key, out result ) )
			{
				result = new TValue();
				dict.Add( key, result );
			}

			return result;
		}

		private delegate bool EqualOperator<T>( T item1, T item2 );
		private static bool AddUnique<T>( List<T> list, T element, EqualOperator<T> operation )
		{
			if ( list.Exists( item => operation( item, element ) ) )
				return false;

			list.Add( element );
			return true;
		}

		public static bool GenerateMaterialSpecs( Solution solution, Assembly assembly, string finalMaterialProjectName, bool dryRun )
		{
			Type baseMaterialType = null;
			ExtractTypesFromAssembly( assembly, true, type => { if ( !TypeUtils.HasAttribute<BaseMaterialTypeAttribute>( type, false ) ) return true; baseMaterialType = type; return false; } );

			List<Type> types = new List<Type>();
			ExtractTypesFromAssembly( assembly, false, type => { if ( TypeUtils.IsSubclassOf( type, baseMaterialType ) ) types.Add( type ); return true; } );

			if ( !string.IsNullOrEmpty( finalMaterialProjectName ) )
			{
				if ( !Solution.IsNullOrEmpty( solution ) && solution.GetProject( finalMaterialProjectName ) == null )
				{
					Trace.TraceError( "Cannot find project \"{0}\" in solution", finalMaterialProjectName );
					return false;
				}
			}

			types.Sort( TypeUtils.Compare );

			// collect pins and runtimePins for projects
			List<string> usedProjectsNames = new List<string>();
			if ( !string.IsNullOrEmpty( finalMaterialProjectName ) )
				usedProjectsNames.Add( finalMaterialProjectName );
			Dictionary<string, List<Type>> pins = new Dictionary<string, List<Type>>();
			Dictionary<string, List<KeyValuePair<Type, string>>> runtimePins = new Dictionary<string, List<KeyValuePair<Type, string>>>();
			Dictionary<string, FunctionsCollection> functions = new Dictionary<string, FunctionsCollection>();
			Dictionary<string, List<CodeFile>> dependencies = new Dictionary<string, List<CodeFile>>();
			Dictionary<Type, List<MaterialPinDefenition>> materialsPins = new Dictionary<Type, List<MaterialPinDefenition>>();
			List<KeyValuePair<Type, string>> allRuntimePins = new List<KeyValuePair<Type, string>>();
			foreach ( Type type in types )
			{
				string materialProject = CodeFile.GetProject( type );
				AddUnique( usedProjectsNames, materialProject, ( item1, item2 ) => ( item1 == item2 ) );
        if (TypeUtils.HasAttribute<MaterialGroupAttribute>(type, true))
        {
          GetValue(functions, TypeUtils.GetAttribute<MaterialGroupAttribute>(type, true).GroupName).FillFromMaterialType(type);
        }

        AddUnique(GetValue(dependencies, materialProject), CodeFile.CreateFile(type), (item1, item2) => (item1 == item2));
        foreach ( FieldInfo field in DBCodeGen.GetFields( type, true, string.Empty, null ) )
				{
					if ( !DBCodeGen.IsSimpleType( field.FieldType ) && !TypeUtils.HasAttribute<NoCodeAttribute>( field, true ) && !TypeUtils.HasAttribute<NoCodeAttribute>( field.FieldType, true ) )
						AddUnique( GetValue( dependencies, materialProject ), CodeFile.CreateFile( field.FieldType ), ( item1, item2 ) => ( item1 == item2 ) );

					Pin2Attribute pinAttr = TypeUtils.GetAttribute<Pin2Attribute>( field, true );
					if ( pinAttr != null )
					{
						string pinProject = CodeFile.GetProject( field.FieldType );
						AddUnique( GetValue( pins, pinProject ), field.FieldType, ( item1, item2 ) => ( item1 == item2 ) );
						AddUnique( usedProjectsNames, pinProject, ( item1, item2 ) => ( item1 == item2 ) );
						if ( pinAttr.IsRuntime )
						{
							KeyValuePair<Type, string> runtimePin = new KeyValuePair<Type, string>( field.FieldType, field.Name );
							AddUnique( GetValue( runtimePins, materialProject ), runtimePin, ( item1, item2 ) => ( item1.Value == item2.Value ) );
							AddUnique( allRuntimePins, runtimePin, ( item1, item2 ) => ( item1.Value == item2.Value ) );
						}

						GetValue( materialsPins, type ).Add( new MaterialPinDefenition( field.Name, field.FieldType, pinAttr.IsRuntime ) );
					}
				}
			}

			// sort founded collections
			allRuntimePins.Sort( ( item1, item2 ) => string.Compare( item1.Value, item2.Value ) );
			foreach ( KeyValuePair<string, List<Type>> pin in pins )
				pin.Value.Sort( TypeUtils.Compare );
			foreach ( KeyValuePair<string, List<KeyValuePair<Type, string>>> runtimePin in runtimePins )
				runtimePin.Value.Sort( ( item1, item2 ) => ( string.Compare( item1.Value, item2.Value ) ) );
			foreach ( KeyValuePair<string, List<CodeFile>> dependency in dependencies )
				dependency.Value.Sort( CodeFile.Compare );
			foreach ( KeyValuePair<Type, List<MaterialPinDefenition>> materialPins in materialsPins )
			{
				materialPins.Value.Sort( MaterialPinDefenition.Compare );
				int multiplier = 1;
				foreach ( MaterialPinDefenition pin in materialPins.Value )
					multiplier = pin.SetPinMultiplier( multiplier );
			}

			foreach ( string usedProjectName in usedProjectsNames )
			{
				Project usedProject = Solution.IsNullOrEmpty( solution ) ? new NullProject( usedProjectName ) : solution.GetProject( usedProjectName );
				if ( usedProject == null )
				{
					Trace.TraceError( "Cannot find project \"{0}\" in solution", usedProjectName );
					continue;
				}

				CodeWriter hFile = usedProject.CreateFile( MATERIAL_SPEC_FILE_NAME + ".h" );
				CodeWriter cppFile = usedProject.CreateFile( MATERIAL_SPEC_FILE_NAME + ".cpp" );

				// generate MaterialSpec code and header
				MaterialSpec spec = new MaterialSpec( usedProjectName, DBCodeGen.GetTypeName( baseMaterialType ),
          GetValue( runtimePins, usedProjectName ),
          GetValue( dependencies, usedProjectName ) );

        foreach (Type type in types)
        {
          if (TypeUtils.HasAttribute<NonTerminalAttribute>(type, false))
            continue;

          if (type != baseMaterialType && CodeFile.GetProject(type) == usedProjectName)
          {
            string groupName = "Render::Material";
            if (TypeUtils.HasAttribute<MaterialGroupAttribute>(type, true))
            {
              groupName = TypeUtils.GetAttribute<MaterialGroupAttribute>(type, true).GroupName;
              spec.AddGroupDeclaration(groupName, TypeUtils.GetAttribute<MaterialGroupAttribute>(type, true).BaseGroupName, functions[groupName]);
              spec.AddMaterialDeclaration(type, GetValue(materialsPins, type), groupName, functions[groupName], usedProject, Solution.IsNullOrEmpty(solution) ? null : solution.GetProject(CodeFile.GetProject(type)));
            }
            else
            {
              spec.AddMaterialDeclaration(type, GetValue(materialsPins, type), groupName, null, usedProject, Solution.IsNullOrEmpty(solution) ? null : solution.GetProject(CodeFile.GetProject(type)));
            }

          }
        }

        spec.InitializeFinal(usedProjectsNames, allRuntimePins);

        if (!string.IsNullOrEmpty(finalMaterialProjectName) && finalMaterialProjectName == usedProjectName)
				{
          hFile.WriteLines(0, PatternFormatter.Format(Patterns.Patterns.MaterialSpecFinalHeader, spec));
          cppFile.WriteLines( 0, PatternFormatter.Format( Patterns.Patterns.MaterialSpecFinalCode, spec ) );
				}
				else
				{
          hFile.WriteLines( 0, PatternFormatter.Format( Patterns.Patterns.MaterialSpecHeader, spec ) );
          cppFile.WriteLines( 0, PatternFormatter.Format( Patterns.Patterns.MaterialSpecCode, spec ) );
				}

				hFile.Close( dryRun );
				cppFile.Close( dryRun );

				// generate MaterialSpec hlsl defines
				CodeWriter hlslFile = usedProject.CreateFile( Path.Combine( SHADERS_FOLDER_NAME, MATERIAL_SPEC_FILE_NAME + ".hlsl" ) );
				Dictionary<string, string> usedValues = new Dictionary<string, string>();
				foreach ( Type pinType in GetValue( pins, usedProjectName ) )
				{
					string enumName = DBCodeGen.GetTypeName( pinType );
					hlslFile.WriteLine( 0, "// {0}", enumName );

					FieldInfo[] fields = pinType.GetFields( BindingFlags.Public | BindingFlags.Static );
					foreach ( FieldInfo field in fields )
					{
						string valueName = field.Name.ToUpper();
						string value = field.GetRawConstantValue().ToString();

						string usedValue = string.Empty;
						if ( !usedValues.TryGetValue( valueName, out usedValue ) )
						{
							hlslFile.WriteLine( 0, "#define {0} {1}", valueName, value );
							usedValues.Add( valueName, string.Empty ); // use Add( valueName, value ) and MaterialCompiler will support names with same values
						}
						else if ( value != usedValue )
							throw new InvalidOperationException( string.Format( "Value \"{0}\" defined twice in pins' enums", valueName ) );
					}
				}
				hlslFile.Close( dryRun );

				// generate MaterialSpec xml defines for ShaderCompiler
				CodeWriter xmlFile = usedProject.CreateFile( Path.Combine( SHADERS_FOLDER_NAME, MATERIAL_SPEC_FILE_NAME + ".xml" ) );
				List<Type> materials = new List<Type>();
				foreach ( Type type in types )
				{
          if (TypeUtils.HasAttribute<NonTerminalAttribute>(type, false))
            continue;

          if ( CodeFile.GetProject( type ) == usedProjectName && type != baseMaterialType )
						materials.Add( type );
				}
				materials.Sort( TypeUtils.Compare );
				XmlDocument xml = new XmlDocument();
				XmlNode shaders = xml.AppendChild( xml.CreateElement( "shaders" ) );
				foreach ( Type material in materials )
				{
					XmlNode materialItem = shaders.AppendChild( xml.CreateElement( "Item" ) );
					materialItem.AppendChild( xml.CreateElement( "shaderName" ) ).InnerText = material.Name;
					XmlNode materialPins = materialItem.AppendChild( xml.CreateElement( "pins" ) );
					foreach ( MaterialPinDefenition pin in GetValue( materialsPins, material ) )
					{
						XmlNode pinItem = materialPins.AppendChild( xml.CreateElement( "Item" ) );
						pinItem.AppendChild( xml.CreateElement( "pinName" ) ).InnerText = pin.PinName;
						pinItem.AppendChild( xml.CreateElement( "maxPinValue" ) ).InnerText = pin.PinValuesCount.ToString();
						pinItem.AppendChild( xml.CreateElement( "pinMultiplier" ) ).InnerText = pin.PinMultiplier.ToString();
					}
				}

				xml.Save( xmlFile.Writer );
				xmlFile.Close( dryRun );
			}

			return true;
		}
	}
}
