using System;
using System.ComponentModel;
using EditorLib.Extensions;
using libdb.DB;

namespace EditorLib.FieldProcessor
{
  public class FullTypeDescriptorWrapper : ICustomTypeDescriptor
  {
    private object value = null;
    private FullTypeDescriptor descriptor = null;

    # region Initializing

    public FullTypeDescriptorWrapper( object instance, IEditorWinApplication _application )
    {
      value = instance;
      descriptor = FullTypeDescriptor.Create( value, _application );
    }

    public FullTypeDescriptorWrapper( object instance, IEditorWinApplication _application, Attribute[] customAttributes )
    {
      value = instance;
      descriptor = FullTypeDescriptor.Create( value.GetType(), _application, customAttributes );
    }

    # endregion

    # region ICustomTypeDescriptor implementation (redirection)

    public AttributeCollection GetAttributes() { return new AttributeCollection( descriptor.Attributes ); }
    public string GetClassName() { return descriptor.Type.ToString(); }
    public string GetComponentName() { return TypeDescriptor.GetComponentName( descriptor.Type ); }
    public TypeConverter GetConverter() { return descriptor.Converter; }
    public EventDescriptor GetDefaultEvent() { return null; }
    public PropertyDescriptor GetDefaultProperty() { return null; }
    public object GetEditor( Type editorBaseType ) { return descriptor.Editor; }
    public EventDescriptorCollection GetEvents( Attribute[] attributes ) { return new EventDescriptorCollection( new EventDescriptor[0], true ); }
    public EventDescriptorCollection GetEvents() { return GetEvents( null ); }
    public PropertyDescriptorCollection GetProperties( Attribute[] attributes ) { return descriptor.GetProperties( null, value, attributes ); }
    public PropertyDescriptorCollection GetProperties() { return GetProperties( null ); }
    public object GetPropertyOwner(PropertyDescriptor pd) { return value; }
    public object GetPropertyOwner() { return value; }

    #endregion
  }
}
