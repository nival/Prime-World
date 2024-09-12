using System;
using System.Collections.Generic;
using System.Reflection;
using DBCodeGen.VisualStudioSupport;
using libdb.DB;
using System.IO;
using System.Diagnostics;

namespace DBCodeGen
{
	internal sealed partial class DBCodeGen
	{
		private static bool IsValidType( Type type )
		{
			return !type.IsInterface && !type.IsAbstract && !type.IsSubclassOf( typeof( Attribute ) ) && CodeFile.IsValidType( type );
		}

    private static bool CheckCustomAttribute( Type type, string customName )
    {
      return GetFields( type, false, customName, null ).Length > 0;
    }

		private static void LoadTypesFromAssembly( Assembly assembly, ref Dictionary<CodeFile, List<Type>> files, string customName )
		{		
			foreach ( Type type in assembly.GetTypes() )
			{
				if ( !IsValidType( type ) )
					continue;

        CodeFile file = null;
        if ( !string.IsNullOrEmpty( customName ) )
        {
          if ( !CheckCustomAttribute( type, customName ) )
            continue;
          file = CodeFile.CreateFile( customName );
        } 
        else
          file = CodeFile.CreateFile( type );
				
        if ( file == null )
					continue;

				List<Type> types = null;
				if ( !files.TryGetValue( file, out types ) )
				{
					types = new List<Type>();
					files.Add( file, types );
				}

				types.Add( type );
			}

      RegisterTypesFromAssembly( assembly );
      foreach ( AssemblyName refAssemblyName in assembly.GetReferencedAssemblies() )
      {
        Assembly refAssembly = null;
        string relFileName = Path.Combine( Path.GetDirectoryName( assembly.Location ), refAssemblyName.Name ) + ".dll";
        if ( File.Exists( relFileName ) )
          refAssembly = Assembly.LoadFrom( relFileName );
        else
          refAssembly = Assembly.Load( refAssemblyName.FullName );
        if (SourceCompiler.SourceCompiler.IsSameLocation(refAssembly, assembly) || SourceCompiler.SourceCompiler.IsSameLocation(refAssembly, Assembly.GetEntryAssembly()))
          RegisterTypesFromAssembly(refAssembly);
      }

      if ( !string.IsNullOrEmpty( customName ) && files.Count == 1 )
      {
        CodeFile file = CodeFile.CreateFile( customName );
        List<Type> types = null;
        files.TryGetValue( file, out types );

        Dictionary<Type, object> knownTypes = new Dictionary<Type, object>();
        foreach ( var type in types )
          knownTypes.Add( type, null );

        List<Type> collectParents = new List<Type>();
        List<Type> dependTypes = new List<Type>();
        foreach ( var type in types )
        {
          if ( IsSimpleType( type ) || type.IsEnum )
            continue;

          collectParents.Add( type );
          foreach ( var fieldType in GetFieldsTypes( type, customName ) )
          {
            if ( TypeUtils.IsDBPtr( fieldType ) )
            {
              var resFieldType = TypeUtils.GetTypeFromPtr( fieldType );
              if ( !knownTypes.ContainsKey( resFieldType ) )
              {
                knownTypes.Add( resFieldType, null );
                dependTypes.Add( resFieldType );
                collectParents.Add( resFieldType );
              }
            }
            else
            {
              if ( !knownTypes.ContainsKey( fieldType ) )
              {
                knownTypes.Add( fieldType, null );
                dependTypes.Add( fieldType );
              }
            }
          }
        }

        foreach ( var type in collectParents )
        {
          Type baseType = type.BaseType;
          while ( !IsSimpleType( baseType ) && baseType != typeof( DBResource ) && baseType != typeof( object ) )
          {
            if ( !knownTypes.ContainsKey( baseType ) )
            {
              knownTypes.Add( baseType, null );
              dependTypes.Add( baseType );
            }
            baseType = baseType.BaseType;
          }
        }

        types.AddRange( dependTypes );
      }

      foreach ( List<Type> types in files.Values )
        types.Sort( TypeUtils.Compare );

      if ( files.Count == 0 )
      {
        Trace.TraceWarning( "No types found in assembly \"{0}\"", assembly.GetName().Name );
        return;
      }
    }

		private static void RegisterTypesFromAssembly( Assembly assembly )
		{
			//Trace.TraceInformation( "Register types from assembly \"{0}\"... ", assembly.GetName().Name );
			foreach ( Type type in assembly.GetTypes() )
			{
        if(type.Name == "TraceArray2Attribute")
        {
          Trace.TraceInformation("Register type {0} from assembly {1}... ", type.Name, assembly.GetName().Name);
        }

        //Trace.TraceInformation("Register type {0} from assembly {1}... ", type.Name, assembly.GetName().Name);
				if ( IsValidType( type ) )
				{
					CheckTypeAttributes( type );
					//MaterialCompiler.CheckTypeAttributes( type );
				}
			}
		}
	}
}