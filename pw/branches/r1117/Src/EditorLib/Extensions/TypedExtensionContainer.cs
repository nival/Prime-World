using System;
using System.Collections.Generic;
using libdb.DB;
using libdb.Diagnostics;
using System.Reflection;

namespace EditorLib.Extensions
{
  internal class ExtensionInfo
  {
    private readonly ConstructorInfo cotr = null;
    private readonly bool applicableForDeriver = false;
  	private readonly List<Type> exclude;

    public ExtensionInfo( ConstructorInfo _cotr, bool _applicableForDeriver, Type[] _exclude ) 
		{ 
			cotr = _cotr; 
			applicableForDeriver = _applicableForDeriver;
    	exclude = new List<Type>(_exclude ?? new Type[0]);
		}

    public object CreateExtension()
    {
      ParameterInfo[] parameters = cotr.GetParameters();
      if ( null == parameters || parameters.Length != 0 )
      {
        Log.TraceError( "Can't create extension by default constructor" );
        return null;
      }

      return cotr.Invoke( new object[0] );
    }

    public object CreateExtension( object param1 )
    {
      ParameterInfo[] parameters = cotr.GetParameters();
      if ( null == parameters || parameters.Length != 1 )
      {
        Log.TraceError( "Can't create extension by constructor with 1 parameter: {0}", param1.ToString() );
        return null;
      }

      return cotr.Invoke( new object[1] { param1 } );
    }

    public object CreateExtension( object param1, object param2 )
    {
      ParameterInfo[] parameters = cotr.GetParameters();
      if ( null == parameters || parameters.Length != 2 )
      {
        Log.TraceError( "Can't create extension by constructor with 2 parameters: {0}, {1}", param1.ToString(), param2.ToString() );
        return null;
      }

      return cotr.Invoke( new object[2] { param1, param2 } );
    }

    public Type ExtensionType { get { return cotr.DeclaringType; } }
    public bool ApplicableForDeriver { get { return applicableForDeriver; } }
		public List<Type> Exclude { get { return exclude; } }
  }

  internal class TypedExtensionContainer<T> where T : class
  {
    private readonly bool supportMultiplyExtensions = false;
    protected bool SupportMultiplyExtensions { get { return supportMultiplyExtensions; } }

    private Dictionary<Type, List<ExtensionInfo>> extensions = new Dictionary<Type, List<ExtensionInfo>>();

    public TypedExtensionContainer( bool supportMultiplyPlugins )
    {
      this.supportMultiplyExtensions = supportMultiplyPlugins;
    }

		private bool RegisterExtensionType( Type type, ConstructorInfo constructor, ApplicableForDeriverAttribute applicableForDeriver )
    {
      if ( constructor == null )
        return false;

      List<ExtensionInfo> constructors = null;
      if ( !extensions.TryGetValue( type, out constructors ) )
      {
        constructors = new List<ExtensionInfo>();
        extensions.Add( type, constructors );
      }

      if ( constructors.Count == 1 && !SupportMultiplyExtensions )
      {
        Log.TraceWarning( "Extensions container for \"{0}\" doesn't support multiply extensions. It already has extension \"{1}\" and extension \"{2}\" cannot be registered", typeof( T ).Name, constructors[0].ExtensionType.Name, type.Name );
        return false;
      }

			Type[] exclude = new Type[0];

			if ( applicableForDeriver != null )
				exclude = applicableForDeriver.Exclude;

    	constructors.Add( new ExtensionInfo( constructor, applicableForDeriver != null, exclude ) );
      return true;
    }

    /// <summary>
    /// Register plugin type in container
    /// </summary>
    /// <param name="pluginType">Type of plugin. Type must be generic. First parameter of generic specify applicable type</param>
    /// <returns>false in any fault. Check log for details</returns>
    public bool TryRegisterExtensionType( Type extensionType )
    {
      if ( !TypeUtils.IsSubclassOf( extensionType, typeof( T ) ) || 
           extensionType == typeof( T ) || extensionType.IsAbstract || !extensionType.IsPublic)
      {
        //if ( !dontTraceInvalidTypeError )
        //Log.TraceWarning( "Cannot register extension \"{0}\" in extensions container \"{1}\"", extensionType.Name, typeof( T ).Name );
        return false;
      }

      ConstructorInfo constructor = extensionType.GetConstructor( new Type[2] { typeof( IEditorWinApplication ), typeof( Attribute ) } );
      if ( null == constructor )
        constructor = extensionType.GetConstructor( new Type[1] { typeof( IEditorWinApplication ) } );
      if ( null == constructor )
        constructor = extensionType.GetConstructor( Type.EmptyTypes );

      if( constructor == null )
      {
        Log.TraceWarning( "Cannot find constructors for extension \"{0}\"", extensionType.Name );
        return false;
      }

      Type editType = TypeUtils.GetTypeFromGeneric( extensionType, 0 );
      if ( editType == null )
      {
        if( extensionType != typeof( FieldProcessor.DefaultListEditor ) )
        {
          Log.TraceWarning( "Cannot extract edit type for extension \"{0}\"", extensionType.Name ); 
        }
        return false;
      }

      return RegisterExtensionType( editType, constructor, TypeUtils.GetAttribute<ApplicableForDeriverAttribute>( extensionType, true ) );
    }

    internal List<ExtensionInfo> GetExtensionsInfos( Type type )
    {
      List<ExtensionInfo> result = new List<ExtensionInfo>();

      foreach ( Type interfaceType in type.GetInterfaces() )
      {
        List<ExtensionInfo> typeExtensions = null;
        if ( extensions.TryGetValue( interfaceType, out typeExtensions ) )
        {
          foreach ( ExtensionInfo extension in typeExtensions )
          {
						if ( extension.ApplicableForDeriver )
              result.Add( extension );
          }
        }
      }

    	Type tmpType = type;
			while ( tmpType != null )
      {
        List<ExtensionInfo> typeExtensions = null;
				if ( extensions.TryGetValue( tmpType, out typeExtensions ) )
        {
          foreach ( ExtensionInfo extension in typeExtensions )
          {
						if ( tmpType == type || extension.ApplicableForDeriver )
            {
							if ( extension.Exclude.Contains( type ) )
								break;

							result.Add( extension );
            }
          }
        }
				tmpType = tmpType.BaseType;
      }

      return result;
    }

    /// <summary>
    /// Return amount of extensions for specified type
    /// </summary>
    /// <param name="resourceType">Type</param>
    /// <returns>Amount of extensions for specified type</returns>
    public int GetExtensionsCount( Type resourceType )
    {
      return GetExtensionsInfos( resourceType ).Count;
    }

    /// <summary>
    /// Return extensions for specified type
    /// </summary>
    /// <param name="resourceType">Type</param>
    /// <returns>List with extensions for specified type. Returns empty list if no extensions found</returns>
    public List<T> GetExtensions( Type resourceType )
    {
      List<ExtensionInfo> extensions = GetExtensionsInfos( resourceType );

      List<T> result = new List<T>();
      foreach ( ExtensionInfo extensionInfo in extensions )
      {
        T extension = extensionInfo.CreateExtension() as T;
        if ( extension != null )
          result.Add( extension );
      }

      return result;
    }

    public T TryGetExtension( Type resourceType, Type prefferedExtensionType )
    {
      List<ExtensionInfo> extensions = GetExtensionsInfos( resourceType );

      if ( extensions.Count == 0 )
        return null;

      if ( extensions.Count == 1 )
        return extensions[0].CreateExtension() as T;

      foreach ( ExtensionInfo extensionInfo in extensions )
      {
        if ( extensionInfo.ExtensionType == prefferedExtensionType )
          return extensionInfo.CreateExtension() as T;
      }

      Log.TraceWarning( "Cannot select extension for type \"{0}\". Workaround for multiply plugins not implemented yet", resourceType.Name );
      return null;
    }

    public T TryGetExtension<T1>( Type resourceType, Type prefferedExtensionType, T1 param1 )
    {
      List<ExtensionInfo> extensions = GetExtensionsInfos( resourceType );

      if ( extensions.Count == 0 )
        return null;

      if ( extensions.Count == 1 )
        return extensions[0].CreateExtension( param1 ) as T;

      foreach ( ExtensionInfo extensionInfo in extensions )
      {
        if ( extensionInfo.ExtensionType == prefferedExtensionType )
          return extensionInfo.CreateExtension( param1 ) as T;
      }

      Log.TraceWarning( "Cannot select extension for type \"{0}\". Workaround for multiply plugins not implemented yet", resourceType.Name );
      return null;
    }
  }
}
