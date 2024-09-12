using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorLib.Extensions
{
  internal class TwoTypedExtensionContainer<T> : TypedExtensionContainer<T>
    where T : class
  {
    private Dictionary<Type, Dictionary<Type, List<ExtensionInfo>>> extensions = new Dictionary<Type, Dictionary<Type, List<ExtensionInfo>>>();

    public TwoTypedExtensionContainer( bool supportMultiplyPlugins ) : base( supportMultiplyPlugins ) { }

		private bool RegisterExtensionType( Type type, Type addType, ConstructorInfo constructor, ApplicableForDeriverAttribute applicableForDeriver)
    {
      if ( constructor == null )
        return false;

      Dictionary<Type, List<ExtensionInfo>> addExtensions = null;
      if ( !extensions.TryGetValue( type, out addExtensions ) )
      {
        addExtensions = new Dictionary<Type, List<ExtensionInfo>>();
        extensions.Add( type, addExtensions );
      }

      List<ExtensionInfo> constructors = null;
      if ( !addExtensions.TryGetValue( addType, out constructors ) )
      {
        constructors = new List<ExtensionInfo>();
        addExtensions.Add( addType, constructors );
      }

      if ( constructors.Count == 1 && !SupportMultiplyExtensions )
      {
        Log.TraceWarning( "Extensions container for \"{0}\" doesn support multiply extensions. It already has extension \"{1}\" and extension \"{2}::{3}\" cannot be registered", typeof( T ).Name, constructors[0].ExtensionType.Name, type.Name, addType.Name );
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
    public bool TryRegisterExtensionType( Type extensionType, bool canBeSingleTyped )
    {
    	if(TypeUtils.GetTypeFromGeneric(extensionType, 1) == null && canBeSingleTyped)
    		return TryRegisterExtensionType(extensionType);

    	if(!TypeUtils.IsSubclassOf(extensionType, typeof(T)) || extensionType == typeof(T) || extensionType.IsAbstract)
    	{
    		return false;
    	}

    	ConstructorInfo constructor =
    		extensionType.GetConstructor(new Type[2] {typeof(IEditorWinApplication), typeof(Attribute)});
    	if(null == constructor)
    		constructor = extensionType.GetConstructor(new Type[1] {typeof(IEditorWinApplication)});
    	if(null == constructor)
    		constructor = extensionType.GetConstructor(Type.EmptyTypes);

    	if(constructor == null)
    	{
    		Log.TraceWarning("Cannot find default constructor for extension \"{0}\"", extensionType.Name);
    		return false;
    	}

    	Type editType = TypeUtils.GetTypeFromGeneric(extensionType, 0);
    	if(editType == null)
    	{
    		Log.TraceWarning("Cannot extract edit type for extension \"{0}\"", extensionType.Name);
    		return false;
    	}

    	Type addType = TypeUtils.GetTypeFromGeneric(extensionType, 1);
    	if(addType == null)
    	{
    		Log.TraceWarning("Cannot extract additional type for extension \"{0}\"", extensionType.Name);
    		return false;
    	}

    	ApplicableForDeriverAttribute attr = TypeUtils.GetAttribute<ApplicableForDeriverAttribute>(extensionType, true);

			return RegisterExtensionType( editType, addType, constructor, attr );
    }

    protected List<ExtensionInfo> GetExtensionsInfos( Type type, Type additionalType )
    {
      if ( additionalType == null )
        return base.GetExtensionsInfos( type );

      List<ExtensionInfo> result = new List<ExtensionInfo>();

      foreach ( Type interfaceType in type.GetInterfaces() )
      {
        Dictionary<Type, List<ExtensionInfo>> addExtensions = null;
        if ( extensions.TryGetValue( interfaceType, out addExtensions ) )
        {
          List<ExtensionInfo> typeExtensions = null;
          if ( addExtensions.TryGetValue( additionalType, out typeExtensions ) )
          {
            foreach ( ExtensionInfo extension in typeExtensions )
            {
              if ( extension.ApplicableForDeriver )
              {
								result.Add( extension );
              }
            }
          }
        }
      }

    	Type tmpType = type;
			while ( tmpType != null )
      {
        Dictionary<Type, List<ExtensionInfo>> addExtensions = null;
				if ( extensions.TryGetValue( tmpType, out addExtensions ) )
        {
          List<ExtensionInfo> typeExtensions = null;
          if ( addExtensions.TryGetValue( additionalType, out typeExtensions ) )
          {
            foreach ( ExtensionInfo extension in typeExtensions )
            {
							if ( tmpType == type || extension.ApplicableForDeriver )
              {
								if(extension.Exclude.Contains(type))
									break;

								result.Add( extension );				
              }
                
            }
          }
        }

				tmpType = tmpType.BaseType;
      }

      return result;
    }

    /// <summary>
    /// Return amount of extensions for specified type and additional type
    /// </summary>
    /// <param name="resourceType">Type</param>
    /// <param name="additionalType">Additional type. Can be null in this case return extensions from base container</param>
    /// <returns>Amount of extensions for specified type and additional type</returns>
    public int GetExtensionsCount( Type resourceType, Type additionalType )
    {
      return GetExtensionsInfos( resourceType, additionalType ).Count;
    }

    /// <summary>
    /// Return plugins for specified type and additional type
    /// </summary>
    /// <param name="resourceType">Type</param>
    /// <param name="additionalType">Additional type. Can be null in this case return extensions from base container</param>
    /// <returns>List with plugins for specified type. Returns empty list if no plugins found</returns>
    public List<T> GetExtensions( Type resourceType, Type additionalType )
    {
      List<ExtensionInfo> extensions = GetExtensionsInfos( resourceType, additionalType );

      List<T> result = new List<T>();
      foreach ( ExtensionInfo extensionInfo in extensions )
      {
        T extension = extensionInfo.CreateExtension() as T;
        if ( extension != null )
          result.Add( extension );
      }

      return result;
    }

    public T TryGetExtension( Type resourceType, Type additionalType, Type prefferedExtensionType )
    {
      List<ExtensionInfo> extensions = GetExtensionsInfos( resourceType, additionalType );

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

    public T TryGetExtension<Param1, Param2>( Type resourceType, Type additionalType, Type prefferedExtensionType, Param1 param1, Param2 param2 )
    {
      List<ExtensionInfo> extensions = GetExtensionsInfos( resourceType, additionalType );

      if ( extensions.Count == 0 )
        return null;

      if ( extensions.Count == 1 )
        return extensions[0].CreateExtension( param1, param2 ) as T;

      foreach ( ExtensionInfo extensionInfo in extensions )
      {
        if ( extensionInfo.ExtensionType == prefferedExtensionType )
          return extensionInfo.CreateExtension( param1, param2 ) as T;
      }

      Log.TraceWarning( "Cannot select extension for type \"{0}\". Workaround for multiply plugins not implemented yet", resourceType.Name );
      return null;
    }

    public Type[] GetExtensionsTypes( Type resourceType )
    {
      Dictionary<Type, List<ExtensionInfo>> addExtensions = null;
      if ( !extensions.TryGetValue( resourceType, out addExtensions ) )
        return Type.EmptyTypes;

      List<Type> extensionsTypes = new List<Type>();
      foreach ( Type extensionsType in addExtensions.Keys )
        extensionsTypes.Add( extensionsType );

      return extensionsTypes.ToArray();
    }
  }
}
