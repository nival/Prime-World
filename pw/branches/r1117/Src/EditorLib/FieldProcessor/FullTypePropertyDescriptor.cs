using System;
using System.ComponentModel;
using libdb.Diagnostics;
using System.Reflection;
using libdb.DB;
using libdb.IO;
using EditorLib.PropertiesEditor;

namespace EditorLib.FieldProcessor
{
  public abstract class FullTypePropertyDescriptor : PropertyDescriptor
  {
    private readonly FullTypeDescriptor descriptor = null;
    private bool readOnly = false;

		public static object GetInstanceFromContext( ITypeDescriptorContext context )
		{
			if ( context == null )
				return null;
			ICustomTypeDescriptor typeDesc = context.Instance as ICustomTypeDescriptor;
			if ( typeDesc != null )
				return typeDesc.GetPropertyOwner( context.PropertyDescriptor );

			DBPtrBase ptr = context.Instance as DBPtrBase;
			if ( ptr != null )
				return ptr.Get<DBResource>();

			return context.Instance;
		}

    protected FullTypePropertyDescriptor( FullTypeDescriptor descriptor, string name, Attribute[] attrs )
      : base( name, attrs )
    {
      this.descriptor = descriptor;

      foreach ( Attribute attr in attrs )
      {
        if ( attr is ReadOnlyAttribute )
        {
          readOnly = ( attr as ReadOnlyAttribute ).IsReadOnly;
          break;
        }
      }
    }


    #region Methods for support default value and serialization. Functionality for these methods not implemented yet

    public override bool CanResetValue( object component )
    {
      return false;
    }

    public override void ResetValue( object component )
    {

    }

    public override bool ShouldSerializeValue( object component )
    {
      return false;
    }

    #endregion

    private bool TryEvaluateDBPtr( object value, out object result )
    {
      result = value;

      if ( null == value )
        return false;

      if ( !TypeUtils.IsSubclassOf( value.GetType(), typeof( DBPtrBase ) ) )
        return false;

      DBResource resource = ( value as DBPtrBase ).Get<DBResource>();
      if ( ( value as DBPtrBase ).IsValid && ( null == resource || !TypeUtils.IsSubclassOf( resource.GetType(), TypeUtils.GetTypeFromPtr( PropertyType ) ) ) )
      {
        Log.TraceWarning( "Set value type differ from PropertyType" );
        return false;
      }

      ConstructorInfo constructor = PropertyType.GetConstructor( new Type[2] { typeof( DBID ), TypeUtils.GetTypeFromPtr( PropertyType ) } );
      if ( null == constructor )
      {
        Log.TraceWarning( "Cannot call constructor for type {0}", PropertyType.ToString() );
        return false;
      }

      DBPtrBase ptr = constructor.Invoke( new object[2] { ( value as DBPtrBase ).DBId, null } ) as DBPtrBase;
      result = ptr;
      if ( null != ptr && ptr.IsValid )
        return ptr.Get<DBResource>() != null;

      // to show "{empty}"
      return true;
    }

    private bool TryEvaluateValue( object value, out object result )
    {
      result = value;

      if ( !TypeUtils.IsSubclassOf( PropertyType, typeof( DBPtrBase ) ) )
        return true;
      else
        return TryEvaluateDBPtr( value, out result );
    }

    private object EvaluateDBPtr( object value )
    {
      if ( null != value && TypeUtils.IsSubclassOf( value.GetType(), typeof( DBPtrBase ) ) )
        return ( value as DBPtrBase ).Get<DBResource>();
      else
        return value;
    }

    protected abstract object GetValueInternal( object component );

    protected abstract void SetValueInternal( object component, object value );

    public override object GetValue( object component )
    {
      if ( component == null )
      {
        Log.TraceWarning( "Cannot get property for null component" );
        return null;
      }

      object instance = EvaluateDBPtr( component );
      if ( null != instance )
        return GetValueInternal( instance );
      else
        return instance;
    }

    public override void SetValue( object component, object value )
    {
      object instance = EvaluateDBPtr( component );
      object result = null;

      if ( component == null )
      {
        Log.TraceWarning( "Cannot set property for null component" );
        return;
      }

      if ( TryEvaluateValue( value, out result ) )
      {
        SetValueInternal( instance, result );
        OnValueChanged( this, EventArgs.Empty ); 
      }
      else
      {
        SetValueInternal( instance, GetValueInternal( instance ) );
        OnValueChanged( this, EventArgs.Empty );
      } 
    }
    
    public override TypeConverter Converter 
    {
      get { return descriptor.Converter; }
    }

    public override object GetEditor( Type editorBaseType )
    {
      return descriptor.Editor;
    }

    public override bool IsReadOnly
    {
      get { return readOnly; }
    }

    public override Type PropertyType
    {
      get { return descriptor.Type; }
    }
  }
}
