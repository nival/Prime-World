using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing.Design;
using EditorLib.Extensions;
using EditorLib.PropertiesEditor;
using libdb.DB;
using libdb.Diagnostics;
using EditorLib.Settings;
using EditorLib.PropertiesEditor.PropertyPresets;
using libdb;

namespace EditorLib.FieldProcessor
{
  /// <summary>
  /// Provide full information about field and/or type
  /// </summary>
  public sealed class FullTypeDescriptor
  {
    private class CustomStandardValuesProviderForString : TypedStandardValuesProvider<string>
    {
      private string[] values = null;

      public CustomStandardValuesProviderForString( IEditorWinApplication application, Type enumType )
        : base( application )
      {
        if( !enumType.IsEnum )
        {
          values = new string[0];
          return;
        }

        values = Enum.GetNames( enumType );
      }

      public override bool IsStandardValuesExclusive( System.ComponentModel.ITypeDescriptorContext context )
      {
        return false;
      }

      public override TypeConverter.StandardValuesCollection GetStandardValues( System.ComponentModel.ITypeDescriptorContext context )
      {
        return new TypeConverter.StandardValuesCollection( values );
      }

      public override bool HasStandardValuesConvertor( System.ComponentModel.ITypeDescriptorContext context )
      {
        return false;
      }

      public override Type GetStandardValuesType( System.ComponentModel.ITypeDescriptorContext context )
      {
        throw new NotImplementedException();
      }

      protected override string ConvertFromStandardValueInternal( System.ComponentModel.ITypeDescriptorContext context, object instance, object value )
      {
        throw new NotImplementedException();
      }
    }

    enum TypeDecriptor
    {
      Simple,
      Complex,
      DBPtr,
      List
    };

    private TypeDecriptor typeDescriptor = TypeDecriptor.Simple;

    private static PropertyDescriptorCollection emptyProperties = new PropertyDescriptorCollection( new PropertyDescriptor[0] );

    private PropertyDescriptorCollection properties = null;

    private IValueEditor valueEditor = null;
    private IValuePainter valuePainter = null;

    private readonly UITypeEditor editor = null;
    private readonly TypeConverter convertor = null;
    private readonly IStringConvertor stringConverter = null;
    private readonly IStandardValuesProvider standardValuesProvider = null;
    
    private readonly Type type = null;

    private readonly IEditorWinApplication application;

    private readonly List<Attribute> attributes = new List<Attribute>();

    #region Initialization

    public static FullTypeDescriptor Create( Type type, IEditorWinApplication application, Attribute[] customAttributes, string fieldSignature )
    {
      FullTypeDescriptor descriptor = new FullTypeDescriptor( type, application, customAttributes, fieldSignature );
      return descriptor;
    }

    public static FullTypeDescriptor Create( Type type, IEditorWinApplication application, Attribute[] customAttributes )
    {
      FullTypeDescriptor descriptor = new FullTypeDescriptor( type, application, customAttributes );
      return descriptor;
    }

    public static FullTypeDescriptor Create( Type type, IEditorWinApplication application )
    {
      return Create( type, application, null );
    }

    public static FullTypeDescriptor Create( Object instance, IEditorWinApplication application )
    {
      return Create( instance.GetType(), application, null );
    }

    private FullTypeDescriptor( Type _type, IEditorWinApplication _application, Attribute[] customAttributes )
    {
      application = _application;
      type = _type;

      // initialize type attributes
      Attribute[] attrs = TypeUtils.GetAttributes<Attribute>( type, true );
      if ( null != attrs )
        attributes.AddRange( attrs );
      if( null != customAttributes )
        attributes.AddRange( customAttributes );

      if ( !TypeUtils.IsSimpleType( type ) )
      {
        if ( TypeUtils.IsList( Type ) )
          typeDescriptor = TypeDecriptor.List;
        else if ( null != TypeUtils.GetTypeFromPtr( Type ) )
          typeDescriptor = TypeDecriptor.DBPtr;
        else
          typeDescriptor = TypeDecriptor.Complex;
      }
      
      // check converters for this type using extensions manager
      if ( null != Extensions )
      {       
        foreach ( Attribute attr in attributes )
        {
          if(Extensions.HasStringConverter( type, attr.GetType() ))
            stringConverter = Extensions.CreateStringConverter( type, attr, application );

					if ( Extensions.HasStandardValueProvider( type, attr.GetType() ) )
            standardValuesProvider = Extensions.CreateStandardValuesProvider( type, attr, application );

          if( valueEditor == null )
          {
            if ( Extensions.HasValueEditors( type, attr.GetType() ) )
              valueEditor = Extensions.CreateValueEditor( Type, attr, application );
            else if ( standardValuesProvider != null )
              valueEditor = new DefaultListEditor( application );  
          }
          
          if ( Extensions.HasValuePainter( type, attr.GetType() ) )
            valuePainter = Extensions.CreateValuePainter( type, attr, application );
        }

        if (stringConverter == null)
          stringConverter = Extensions.CreateStringConverter( type, null, application );

				if ( null == standardValuesProvider )
          standardValuesProvider = Extensions.CreateStandardValuesProvider( Type, null, application );
        if ( null == valueEditor )
          valueEditor = Extensions.CreateValueEditor( Type, null, application );
        if ( null == valuePainter )
          valuePainter = Extensions.CreateValuePainter( Type, null, application );
      }
      
      convertor = new FullTypeConverter( this );
      editor = new FullTypeEditorWrapper( this );
    }

    private FullTypeDescriptor( Type _type, IEditorWinApplication _application, Attribute[] customAttributes, string fieldSignature )
      : this( _type, _application, customAttributes )
    {
      if ( null != Extensions )
      {
        Type enumType = Extensions.GetCustomValueProviderType( fieldSignature );
        if ( enumType != null )
        {
          if ( type == typeof( string ) )
            standardValuesProvider = new CustomStandardValuesProviderForString( application, enumType );
        }
      }
    }

    #endregion

    #region Properties methods

    /// <summary>
    /// Returns is type or field has properties
    /// </summary>
    public bool HasProperties( ITypeDescriptorContext context )
    {
      return GetPropertiesSupported( context ) && ( stringConverter == null || !stringConverter.SuppressProperties );
    }

    public bool HasProperties()
    {
      return HasProperties( null );
    }

    private bool GetPropertiesSupported( ITypeDescriptorContext context )
    {
      if( typeDescriptor == TypeDecriptor.Simple )
        return false;

      if (typeDescriptor == TypeDecriptor.Complex)
      {
        if (context != null && context.PropertyDescriptor != null)
        {
          object obj = context.PropertyDescriptor.GetValue(FullTypePropertyDescriptor.GetInstanceFromContext(context));
          if ( obj != null )
          {
            return GetFields(obj.GetType()).Length > 0;
          }
          else
          {
            return GetFields(Type).Length > 0;
          }
        }
        else
        {
          return GetFields(Type).Length > 0;
        }
      }


      if ( null == context || null == context.Instance || null == context.PropertyDescriptor )
        return false;

      object instance = context.PropertyDescriptor.GetValue( FullTypePropertyDescriptor.GetInstanceFromContext( context ) );
      if ( null == instance )
        return false;

      if( typeDescriptor == TypeDecriptor.DBPtr  )
      {
        DBResource resource = ( instance as DBPtrBase ).Get<DBResource>();
        if ( null != resource )
        {
          Type internalType = resource.GetType();
          return GetFields( internalType ).Length > 0;
        }
      }
      else if ( typeDescriptor == TypeDecriptor.List )
      {
        IEnumerable enumerable = instance as IEnumerable;
        if ( null != enumerable )
          foreach ( object item in enumerable )
            return true;
      }

      return false;
    }

    private static Dictionary<Type, DBFieldInfo[]> fieldInfoCache = new Dictionary<Type, DBFieldInfo[]>();
    private static DBFieldInfo[] GetFields( Type type )
    {
      if ( fieldInfoCache.ContainsKey( type ) )
        return fieldInfoCache[type];
      else
      {
        List<DBFieldInfo> fieldList = new List<DBFieldInfo>( TypeUtils.GetFields( type, true ) );
        fieldList.RemoveAll( IsNotBrowsable );

        DBFieldInfo[] fields = fieldList.ToArray();
        fieldInfoCache[type] = fields;
        return fields;
      }
    }

    private static bool IsNotBrowsable( DBFieldInfo info )
    {
      if ( info.IsDefined( typeof( BrowsableAttribute ), true ) )
      {
        BrowsableAttribute[] attrs = info.GetCustomAttributes<BrowsableAttribute>( true );
        return !attrs[0].Browsable;
      }
      return false;
    }

    private void EvaluateProperties(object instance)
    {
      if ( null != properties )
        return;

      // lazy initialization
      DBFieldInfo[] fields;
      if (instance != null)
      {
        fields = GetFields( instance.GetType() );
      }
      else
      {
        fields = GetFields( type );
      }
      if( fields.Length > 0 )
      {
        PropertyDescriptor[] descriptors = new PropertyDescriptor[fields.Length];
        for ( int index = 0; index < fields.Length; ++index )
        {
          string fieldSignature = type.Name + "." + fields[index].Name;
          Type customEnumType = ( Extensions == null ) ? null : Extensions.GetCustomValueProviderType( fieldSignature );
          if ( customEnumType != null && fields[index].FieldType == typeof( int ) )
            descriptors[index] = new CustomIntPropertyDescriptor( fields[index], application, customEnumType );
          else
            descriptors[index] = new FieldDescriptor( fields[index], application, fieldSignature );
        }

        properties = new PropertyDescriptorCollection( descriptors );
      }
    }

    private static Dictionary<Type, PropertyDescriptorCollection> dbptrPropertiesCache = new Dictionary<Type, PropertyDescriptorCollection>();
    private static Dictionary<int, PropertyDescriptorCollection> listPropertiesCache = new Dictionary<int, PropertyDescriptorCollection>();
    private bool EvaluateDynamicProperties( ITypeDescriptorContext context )
    {
      if ( !HasProperties( context ) )
        return false;

      object instance = null;
      if (context != null && context.PropertyDescriptor != null)
      {
        instance = context.PropertyDescriptor.GetValue(FullTypePropertyDescriptor.GetInstanceFromContext(context));
      }
      
      if (typeDescriptor == TypeDecriptor.Complex)
      {
        EvaluateProperties(instance);
        return true;
      }
      
      
      if ( typeDescriptor == TypeDecriptor.DBPtr )
      {
        DBResource resource = ( instance as DBPtrBase ).Get<DBResource>();
        if ( null != resource )
        {
          Type hash = resource.GetType();
          if ( !dbptrPropertiesCache.ContainsKey( hash ) )
          {
            DBFieldInfo[] fields = GetFields( hash );
            PropertyDescriptor[] descriptors = new PropertyDescriptor[fields.Length];

            for ( int index = 0; index < fields.Length; ++index )
            {
              string fieldSignature = resource.GetType().Name + "." + fields[index].Name;
              Type customEnum = ( Extensions == null ) ? null : Extensions.GetCustomValueProviderType( fieldSignature );
              if ( customEnum != null && fields[index].FieldType == typeof( int ) )
                descriptors[index] = new CustomIntPropertyDescriptor( fields[index], application, customEnum );
              else
                descriptors[index] = new FieldDescriptor( fields[index], application, fieldSignature );
            }
            properties = new PropertyDescriptorCollection( descriptors );

            dbptrPropertiesCache[hash] = properties;
          }
          else
          {
            properties = dbptrPropertiesCache[hash];
          }
        }
      }
      else if( typeDescriptor == TypeDecriptor.List )
      {
        PopulateListElements( context.PropertyDescriptor.ComponentType, context.PropertyDescriptor.Name, instance );
      }

      return true;
    }

    private void PopulateListElements( Type componentType, string fieldName, object instance )
    {
      IEnumerable enumerable = instance as IEnumerable;
      IOwnerable ownerable = instance as IOwnerable;
      if ( null != enumerable )
      {
        int hash = 0;
        foreach ( object item in enumerable )
          ++hash;

        hash ^= enumerable.GetHashCode();
        if ( !listPropertiesCache.ContainsKey( hash ) )
        {
          List<PropertyDescriptor> descriptors = new List<PropertyDescriptor>();
          int index = 0;
          Type enumType = null;
          string[] enumNames = null;
          if ( instance is libdb.IRichList )
          {
            enumType = ( instance as libdb.IRichList ).EnumType;
            if ( enumType != null )
              enumNames = Enum.GetNames( enumType );
          }

          foreach ( object item in enumerable )
          {
            string fieldSignature = ( ownerable == null ) ? string.Empty : ownerable.GetOwner().GetType().Name + "." + fieldName;
            Type customEnum = ( Extensions == null ) ? null : Extensions.GetCustomValueProviderType( fieldSignature );
            if( enumType != null )
            {
              if( customEnum != null && item.GetType() == typeof( int ) )
                descriptors.Add( new CustomIntPropertyDescriptor( index, enumNames[index],
                  item.GetType(), componentType, Attributes, application, customEnum ) );
              else
                descriptors.Add( new ListElementDescriptor( index, enumNames[index],
                  item.GetType(), componentType, Attributes, application, fieldSignature ) );
            }
            else
            {
              if ( customEnum != null && item.GetType() == typeof( int ) )
                descriptors.Add( new CustomIntPropertyDescriptor( index,
                  item.GetType(), componentType, Attributes, application, customEnum ) );
              else
                descriptors.Add( new ListElementDescriptor( index,
                  item.GetType(), componentType, Attributes, application, fieldSignature ) );
            }
            ++index;
          }

          properties = new PropertyDescriptorCollection( descriptors.ToArray() );
          listPropertiesCache[hash] = properties;
        }
        else
        {
          properties = listPropertiesCache[hash];
        }
      }
    }

    private bool HasIndexField( Type itemType )
    {
      Type typeToCheck = itemType.IsSubclassOf( typeof( DBPtrBase ) ) ? TypeUtils.GetTypeFromPtr( itemType ) : itemType;

      return TypeUtils.HasAttribute<IndexFieldAttribute>( typeToCheck, true );
    }

    /// <summary>
    /// Returns collection of properties for type or field
    /// </summary>
    public PropertyDescriptorCollection GetProperties( ITypeDescriptorContext context, object value, Attribute[] filter )
    {
      // Crutch for selecting lists in Outliner
      if ( context == null && value != null && typeDescriptor == TypeDecriptor.List )
      {
        PopulateListElements( value.GetType(), string.Empty, value );
        return properties;
      }

      if ( !EvaluateDynamicProperties( context ) )
        return emptyProperties;

      if ( filter == null || filter.Length == 0 )
        return properties;

      // Filter fields
      return ArrangeProperties( context );
    }

    private PropertyDescriptorCollection ArrangeProperties(ITypeDescriptorContext context)
    {
      //Reset read-onlies
      foreach (PropertyDescriptor desc in properties)
      {
        if (desc is FieldDescriptor)
          (desc as FieldDescriptor).IsForcedReadOnly = false;
      }

      PropertyPresetConfig configSet = application.Application.Settings.Get<PropertyPresetConfig>();
      PropertyPresetConfig.PresetConfigItem config;
      if ( configSet.selectedPreset >= 0 && configSet.selectedPreset < configSet.configPresets.Count )
        config = configSet.configPresets[configSet.selectedPreset];
      else
        return properties;

      Type resType = type;
      if ( type.IsSubclassOf( typeof( DBPtrBase ) ) )
      {
        object instance = context.PropertyDescriptor.GetValue( FullTypePropertyDescriptor.GetInstanceFromContext( context ) );
        DBResource resource = ( instance as DBPtrBase ).Get<DBResource>();
        if ( null != resource )
          resType = resource.GetType();
      }

      return config.FilterProperties( resType, properties );
    }
    
    #endregion

    public IStringConvertor StringConverter { get { return stringConverter; } }
    public IStandardValuesProvider StandardValuesProvider { get { return standardValuesProvider; } }
    public IValueEditor ValueEditor { get { return valueEditor; } }
    public IValuePainter ValuePainter { get { return valuePainter; } }
    public TypeConverter Converter { get { return convertor; } }
    public UITypeEditor Editor { get { return editor; } }
    public Attribute[] Attributes { get { return attributes.ToArray(); } }

    public Type Type { get { return type; } }
    public IEditorWinApplication Application { get { return application; } }
    public ExtensionsManager Extensions { get { return application.Application.Extensions; } }
  }
}
