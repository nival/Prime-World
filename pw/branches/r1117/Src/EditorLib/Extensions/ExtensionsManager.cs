using System;
using System.Collections.Generic;
using libdb.Diagnostics;
using System.Drawing.Design;
using System.IO;
using System.Reflection;
using System.Windows.Forms;
using EditorLib.IO;
using EditorLib.Panels;
using EditorLib.Plugin;
using EditorLib.Settings;
using libdb;
using libdb.DB;
using EditorLib.FieldProcessor;
using System.Drawing;
using EditorLib.Wizards;
using WeifenLuo.WinFormsUI.Docking;

namespace EditorLib.Extensions
{
  public sealed class ExtensionsManager
  {
    #region Private members.

    private List<Type> extensionTypes = new List<Type>();
    private Dictionary<string, bool> tags = new Dictionary<string, bool>();

    private TypedExtensionContainer<IImporter> importers = new TypedExtensionContainer<IImporter>( false );
    private TwoTypedExtensionContainer<IStructImporter> structImporters = new TwoTypedExtensionContainer<IStructImporter>( false );
    private TypedExtensionContainer<IChecker> checkers = new TypedExtensionContainer<IChecker>( true );

    private TypedExtensionContainer<AbstractEditor> editors = new TypedExtensionContainer<AbstractEditor>( true );
    private TwoTypedExtensionContainer<AbstractPropertyEditor> propertyEditors = new TwoTypedExtensionContainer<AbstractPropertyEditor>( false );

    private TwoTypedExtensionContainer<IStringConvertor> stringConverters = new TwoTypedExtensionContainer<IStringConvertor>( false );
    private TwoTypedExtensionContainer<IStandardValuesProvider> standardValuesProviders = new TwoTypedExtensionContainer<IStandardValuesProvider>( false );
    private TwoTypedExtensionContainer<IValueEditor> valueEditors = new TwoTypedExtensionContainer<IValueEditor>( false );
    private TwoTypedExtensionContainer<IValuePainter> valuePainters = new TwoTypedExtensionContainer<IValuePainter>( false );

    private readonly Dictionary<Type, ITypesCollector> typesCollectors = new Dictionary<Type, ITypesCollector>();

    private Dictionary<string, Type> customValueProviders = new Dictionary<string, Type>();

    private ImageList imagesForTypes = new ImageList();

    private WizardsManager wizards = new WizardsManager();

    #endregion

    public T GetTypesCollector<T>() where T : ITypesCollector
    {
      ITypesCollector typesColletor = null;
      if ( !typesCollectors.TryGetValue( typeof( T ), out typesColletor ) )
        return default( T );

      return (T)typesCollectors[typeof( T )];
    }
    public WizardsManager Wizards { get { return wizards; } }

    #region Initialization.

    public void LoadAssemblies( IEnumerable<string> extensionAssembliesFiles )
    {
      extensionTypes.Clear();
      string entryAssemblyPath = Path.GetDirectoryName( Assembly.GetEntryAssembly().Location );
      foreach ( string extensionAssemblyFile in extensionAssembliesFiles )
      {
        string fullExtensionAssemblyFile = Path.Combine( entryAssemblyPath, extensionAssemblyFile );
        if ( !File.Exists( fullExtensionAssemblyFile ) )
          fullExtensionAssemblyFile = Path.GetFullPath( extensionAssemblyFile );
        if ( !File.Exists( fullExtensionAssemblyFile ) )
        {
          Log.TraceWarning( "Plugin file \"{0}\" not found", extensionAssemblyFile );
          continue;
        }
        try
        {
          Assembly extensionAssembly = Assembly.LoadFile( fullExtensionAssemblyFile );
          if ( extensionAssembly == null )
          {
            Log.TraceWarning( "Cannot load plugin \"{0}\"", extensionAssemblyFile );
            continue;
          }

          foreach ( Type extensionType in extensionAssembly.GetTypes() )
            extensionTypes.Add( extensionType );
        }
        catch ( ReflectionTypeLoadException e )
        {
          var info = e.LoaderExceptions;
        }
        catch ( Exception e )
        {
          Log.TraceWarning( "Cannot load plugin \"{0}\". Exception {1}: {2}", extensionAssemblyFile, e.ToString(), e.Message );
        }
      }
    }

    #endregion

    #region Extension registration section

    internal void RegisterConfigObjects( IEditorCommonApplication application )
    {
      foreach ( Type extensionType in extensionTypes )
      {
        if ( TypeUtils.IsSubclassOf( extensionType, typeof( IConfigObject ) ) )
          application.Settings.RegisterConfigObject( extensionType );
      }
    }

    internal void RegisterCommonExtensions( IEditorCommonApplication application )
    {
      foreach ( Type extensionType in extensionTypes )
      {
        if ( TypeUtils.IsSubclassOf( extensionType, typeof( IConfigFileSystem ) ) )
          application.FileSystem.RegisterFileSystemType( extensionType );


        if ( TypeUtils.IsSubclassOf( extensionType, typeof( ITypesCollector ) ) )
        {
          if ( extensionType.GetConstructor( Type.EmptyTypes ) != null )
          {
            ITypesCollector typesCollector = TypeUtils.CreateInstance( extensionType ) as ITypesCollector;
            if ( typesCollector != null )
              typesCollectors.Add( extensionType, typesCollector );
          }
        }

        if ( TypeUtils.IsSubclassOf( extensionType, typeof( IConsoleCommand ) ) )
          application.Commands.RegisterCommand( extensionType );

        importers.TryRegisterExtensionType( extensionType );
        checkers.TryRegisterExtensionType( extensionType );
        structImporters.TryRegisterExtensionType( extensionType, false );

        wizards.TryRegisterType( extensionType );
      }
    }

    private void ProcessTypesCollectors()
    {
      foreach ( Type extensionType in extensionTypes )
      {
        foreach ( ITypesCollector typesCollector in typesCollectors.Values )
          typesCollector.TryRegisterType( extensionType );
      }
    }

    public void RegisterExtensions( IEditorWinApplication application )
    {
      RegisterCommonExtensions( application.Application );

      foreach ( Type extensionType in extensionTypes )
      {
        if ( TypeUtils.IsSubclassOf( extensionType, typeof( EditorPanel ) ) && extensionType != typeof( EditorPanel ) )
          application.Panels.RegisterSingletonPanel( extensionType );

        editors.TryRegisterExtensionType( extensionType );
        propertyEditors.TryRegisterExtensionType( extensionType );

        stringConverters.TryRegisterExtensionType( extensionType, true );
        standardValuesProviders.TryRegisterExtensionType( extensionType, true );
        valueEditors.TryRegisterExtensionType( extensionType, true );
        valuePainters.TryRegisterExtensionType( extensionType, true );

        if ( extensionType.IsEnum && TypeUtils.HasAttribute<CustomStandardValuesForAttribute>( extensionType, true ) )
        {
          CustomStandardValuesForAttribute attr = TypeUtils.GetAttribute<CustomStandardValuesForAttribute>( extensionType, true );
          customValueProviders.Add( attr.name, extensionType );
        }
      }

      ProcessTypesCollectors();
    }

    public void RegisterExtensions( IEditorConApplication application )
    {
      RegisterCommonExtensions( application.Application );
    }

    #endregion

    #region Editors and property editors

    public int GetEditorsCount( Type type )
    {
      return editors.GetExtensionsCount( type );
    }

    public List<Type> GetEditorTypes( DBResource resource )
    {
      List<Type> editorTypes = new List<Type>();
      List<ExtensionInfo> editorInfos = editors.GetExtensionsInfos( resource.GetType() );
      foreach ( ExtensionInfo item in editorInfos )
        editorTypes.Add( item.ExtensionType );

      return editorTypes;
    }

    public void EditorStoreMap(DBID id, IEditorWinApplication application)
    {
        DBResource resource = DataBase.Get<DBResource>(id).Get();
        if (resource == null)
        {
            Log.TraceWarning("Cannot edit resource \"{0}\". Cannot load resource", id.Name);
            return;
        }

        AbstractEditor editor = editors.TryGetExtension(resource.GetType(), null);
        if (editor == null)
            return;

        if (editor.InitializeInternal(id, application))
        {
          editor.StoreMap();
          DataBase.Store();
          editor.Close();
        }
    }

    public AbstractEditor OpenEditor( DBID id, IEditorWinApplication application, Type prefferedEditorType, bool newInstance )
    {
      DBResource resource = DataBase.Get<DBResource>( id ).Get();
      if ( resource == null )
      {
        Log.TraceWarning( "Cannot edit resource \"{0}\". Cannot load resource", id.Name );
        return null;
      }

      AbstractEditor editor = EditorsPool.GetEditorForObject( id );
      if ( editor != null )
      {
        editor.Activate();
      }
      else
      {
        editor = CreateEditor( prefferedEditorType, resource );
        if ( editor == null )
          return null;

        EditorAttribute editorAttr = TypeUtils.GetAttribute<EditorAttribute>( editor.GetType(), true );

        Rectangle wantedRectangle = new Rectangle( 0, 0, 0, 0 );
        
        if ( !newInstance && editorAttr.guid != Guid.Empty )
        {
          AbstractEditor existsEditor = EditorsPool.GetEditorByType( editorAttr.guid );
          if ( existsEditor != null )
          {
            if ( existsEditor.DockState == DockState.Float )
              wantedRectangle = existsEditor.Pane.FloatWindow.Bounds;

            existsEditor.Close();
          }
        }

        if ( editor.InitializeInternal( id, application ) )
        {
          if ( editor.NeedWindow )
          {
            if ( wantedRectangle.IsEmpty )
              application.Panels.Add( editor );
            else
            {
              editor.ShowHint = DockState.Float;
              application.Panels.Add( editor, wantedRectangle );
            }
          }
          else
            editor.Close();
        }
      }
      editor.ToolTipText = id.FileName;
      return editor;
    }

    private AbstractEditor CreateEditor( Type prefferedEditorType, DBResource resource )
    {
      if ( null == prefferedEditorType && editors.GetExtensionsCount( resource.GetType() ) > 1 )
      {
        List<Type> editorTypes = GetEditorTypes( resource );
        foreach ( Type item in editorTypes )
        {
          EditorAttribute attr = TypeUtils.GetAttribute<EditorAttribute>( item, true );
          if ( null == attr )
          {
            Log.TraceWarning( "EditorAttribute for {0} is not set.", item.FullName );
            continue;
          }

          if ( attr.isDefault )
          {
            prefferedEditorType = item;
            break;
          }
        }
      }

      return editors.TryGetExtension( resource.GetType(), prefferedEditorType );
    }
    public UITypeEditor CreatePropertyEditor( Type resourceType, Attribute[] attributes, IEditorWinApplication application )
    {
      AbstractPropertyEditor result = null;
      if ( attributes != null )
      {
        foreach ( Attribute attribute in attributes )
        {
          result = propertyEditors.TryGetExtension( resourceType, attribute.GetType(), null );
          if ( result != null )
            break;
        }
      }

      if ( result == null )
        result = propertyEditors.TryGetExtension( resourceType, null );

      if ( result != null )
        result.SetApplication( application );

      return result;
    }

    #endregion

    #region Inporters and checkers

    #region Resource importer

    public IImporter CreateImporter( DBID id, IEditorCommonApplication application, bool fast )
    {
      DBResource resource = DataBase.Get<DBResource>( id ).Get();
      if ( resource == null )
        Log.TraceWarning( "Cannot import resource \"{0}\". Cannot load resource", id.Name );
      else if ( !HasImporter( resource.GetType() ) )
        Log.TraceWarning( "Cannot import resource \"{0}\". No importer for type \"{1}\"", id.Name, resource.GetType().Name );
      else
      {
        IImporter importer = importers.TryGetExtension( resource.GetType(), null );
        if ( importer != null )
        {
          importer.Initialize( id, application, fast );
          return importer;
        }
      }

      return null;
    }

    public void Import( DBID id, IEditorCommonApplication application, bool fast )
    {
      IImporter importer = CreateImporter( id, application, fast );
      if ( importer != null )
        application.OperationExecutor.Start( importer.Import );
    }

    public bool HasImporter( Type type ) { return importers.GetExtensionsCount( type ) > 0; }

    #endregion

    #region Struct importer

    public IStructImporter CreateImporter( IOwnerable ownerable, IEditorCommonApplication application, bool fast )
    {
      if ( ownerable == null )
      {
        Log.TraceWarning( "Cannot import {{null}} struct" );
        return null;
      }
      else if ( ownerable.GetOwner() == null || ownerable.GetOwner().DBId.IsEmpty )
      {
        Log.TraceWarning( "Cannot import struct withour owner" );
        return null;
      }

      IStructImporter importer = structImporters.TryGetExtension( ownerable.GetOwner().GetType(), ownerable.GetType(), null );
      if ( importer == null )
      {
        Log.TraceWarning( "Cannot import struct \"{0}\" from resource \"{1}\". Importer not found", ownerable.GetType(), ownerable.GetOwner().DBId.Name );
        return null;
      }

      importer.Initialize( ownerable, application, fast );
      return importer;
    }

    public void Import( IOwnerable ownerable, IEditorCommonApplication application, bool fast )
    {
      IStructImporter importer = CreateImporter( ownerable, application, fast );
      if ( importer != null )
        application.OperationExecutor.Start( importer.Import );
    }

    public bool HasImporter( Type resourceType, Type fieldType ) { return structImporters.GetExtensionsCount( resourceType, fieldType ) > 0; }

    public Type[] GetStructImporters( Type resourceType ) { return structImporters.GetExtensionsTypes( resourceType ); }

    #endregion

    public void Check( DBID id, IEditorCommonApplication application, bool fixErrors )
    {
      DBResource resource = DataBase.Get<DBResource>( id ).Get();
      if ( resource == null )
        Log.TraceWarning( "Cannot check resource \"{0}\". Cannot load resource", id.Name );
      else if ( !HasCheckers( resource.GetType() ) )
        Log.TraceWarning( "Cannot check resource \"{0}\". No checkers for type \"{1}\"", id.Name, resource.GetType().Name );
      else
      {
        List<IChecker> typeCheckers = checkers.GetExtensions( resource.GetType() );
        foreach ( IChecker checker in typeCheckers )
          checker.Check( id, application, fixErrors );
      }
    }

    public bool CheckImmediate( DBID id, IEditorCommonApplication application, bool fixErrors )
    {
      DBResource resource = DataBase.Get<DBResource>( id ).Get();
      if ( resource == null )
        Log.TraceWarning( "Cannot check resource \"{0}\". Cannot load resource", id.Name );
      else if ( !HasCheckers( resource.GetType() ) )
        Log.TraceMessage( "Skipping resource \"{0}\". No checkers for type \"{1}\"", id.Name, resource.GetType().Name );
      else
      {
        List<IChecker> typeCheckers = checkers.GetExtensions( resource.GetType() );
        foreach ( IChecker checker in typeCheckers )
        {
          if ( !checker.CheckImmediate( id, application, fixErrors ) )
            return false;
        }
      }
      return true;
    }

    public bool HasCheckers( Type type ) { return checkers.GetExtensionsCount( type ) > 0; }

    #endregion

    #region TypeDescriptor

    #region StringConverter

    public bool HasStringConverter( Type type, Type attributeType ) 
    { 
      return stringConverters.GetExtensionsCount( type, attributeType ) > 0; 
    }

    public IStringConvertor CreateStringConverter( Type type, IEditorWinApplication application )
    {
      return CreateStringConverter( type, null, application );
    }

    public IStringConvertor CreateStringConverter( Type type, Attribute attribute, IEditorWinApplication application )
    {
      Type attributeType = attribute != null ? attribute.GetType() : null;
      if( HasStringConverter( type, attributeType ) )
      {
        if( null != attributeType )
        {
          return stringConverters.TryGetExtension<IEditorWinApplication, Attribute>( type, attributeType, null, application, attribute );
        }

        return stringConverters.TryGetExtension<IEditorWinApplication>( type, null, application );
      }
      
      return null;
    }

    #endregion

    #region StandardValueProvider

    public bool HasStandardValueProvider( Type type, Type attributeType ) { return standardValuesProviders.GetExtensionsCount( type, attributeType ) > 0; }

    public IStandardValuesProvider CreateStandardValuesProvider( Type type, Attribute attribute, IEditorWinApplication application )
    {
      Type attributeType = attribute != null ? attribute.GetType() : null;
      if ( HasStandardValueProvider( type, attributeType ) )
      {
        if ( null != attributeType )
          return standardValuesProviders.TryGetExtension<IEditorWinApplication, Attribute>( type, attributeType, null, application, attribute );
        else
          return standardValuesProviders.TryGetExtension<IEditorWinApplication>( type, null, application );
      }
      else
        return null;
    }

    #endregion

    #region ValueEditor

    public bool HasValueEditors( Type type, Type attributeType ) { return valueEditors.GetExtensionsCount( type, attributeType ) > 0; }

    public IValueEditor CreateValueEditor( Type type, Attribute attribute, IEditorWinApplication application )
    {
      Type attributeType = attribute != null ? attribute.GetType() : null;
      if ( HasValueEditors( type, attributeType ) )
      {
        if ( null != attributeType )
          return valueEditors.TryGetExtension<IEditorWinApplication, Attribute>( type, attributeType, null, application, attribute );
        else
          return valueEditors.TryGetExtension<IEditorWinApplication>( type, null, application );
      }
      else
        return null;
    }

    #endregion

    #region ValuePainter

    public bool HasValuePainter( Type type, Type attributeType ) { return valuePainters.GetExtensionsCount( type, attributeType ) > 0; }

    public IValuePainter CreateValuePainter( Type type, Attribute attribute, IEditorWinApplication application )
    {
      Type attributeType = attribute != null ? attribute.GetType() : null;
      if ( HasValuePainter( type, attributeType ) )
      {
        if ( null != attributeType )
          return valuePainters.TryGetExtension<IEditorWinApplication, Attribute>( type, attributeType, null, application, attribute );
        else
          return valuePainters.TryGetExtension<IEditorWinApplication>( type, null, application );
      }
      else
        return null;
    }

    #endregion

    #endregion

    #region Project-Specific Standard Values

    public Type GetCustomValueProviderType( string className, string fieldName )
    {
      return GetCustomValueProviderType( className + '.' + fieldName );
    }

    public Type GetCustomValueProviderType( string fieldSignature )
    {
      if ( customValueProviders.ContainsKey( fieldSignature ) )
        return customValueProviders[fieldSignature];
      else
        return null;
    }

    #endregion

    #region Type Icons

    public void RegisterAssemblyWithIcons( string _assemblyFile )
    {
      imagesForTypes.Images.Clear();
      System.Drawing.Bitmap defaultImage = new System.Drawing.Bitmap( 16, 16 );
      imagesForTypes.Images.Add( defaultImage );
      string fullExtensionAssemblyFile = Path.Combine( Path.GetDirectoryName( Assembly.GetEntryAssembly().Location ), _assemblyFile );
      if ( !File.Exists( fullExtensionAssemblyFile ) )
        fullExtensionAssemblyFile = Path.GetFullPath( _assemblyFile );
      if ( !File.Exists( fullExtensionAssemblyFile ) )
      {
        Log.TraceWarning( "Icon assembly file \"{0}\" not found", _assemblyFile );
        return;
      }
      try
      {
        Assembly iconAssembly = Assembly.LoadFile( fullExtensionAssemblyFile );
        if ( iconAssembly == null )
        {
          Log.TraceWarning( "Cannot load icon assembly \"{0}\"", _assemblyFile );
          return;
        }

        string[] resourceNames = iconAssembly.GetManifestResourceNames();
        foreach ( string name in resourceNames )
        {
          string[] parts = name.Split( '.' );
          if ( parts.Length < 2 || parts[parts.Length - 1] == "resources" )
            continue;

          string key = parts[parts.Length - 2];
          System.IO.Stream file = iconAssembly.GetManifestResourceStream( name );
          Image img = Image.FromStream( file );
          imagesForTypes.Images.Add( key, img );
        }

      }
      catch ( Exception e )
      {
        Log.TraceWarning( "Cannot load icon assembly \"{0}\". Exception {1}: {2}", _assemblyFile, e.ToString(), e.Message );
      }

    }

    public ImageList GetTypesImageList()
    {
      return imagesForTypes;
    }

    public int GetTypeIconIndex( Type _type, bool _inherit )
    {
      lock ( imagesForTypes )
      {
        if ( null == _type )
          return -1;

        Type parentType = _type;
        do
        {
          if ( imagesForTypes.Images.ContainsKey( parentType.Name ) )
            return imagesForTypes.Images.IndexOfKey( parentType.Name );

          parentType = parentType.BaseType;
        } while ( _inherit && parentType != null );

        if ( TypeUtils.IsList( _type ) )
          return imagesForTypes.Images.IndexOfKey( "IFixedEnumList" );
        else if ( TypeUtils.IsSubclassOf( _type, typeof( IOwnerable ) ) )
          return imagesForTypes.Images.IndexOfKey( "IOwnerable" );
      }

      return -1;
    }

    public Image GetTypeIcon( Type _type, bool _inherit )
    {
      int index = GetTypeIconIndex( _type, _inherit );
      
      if( index >= 0 )
        return imagesForTypes.Images[index];

      return null;
    }

    #endregion
  }
}
