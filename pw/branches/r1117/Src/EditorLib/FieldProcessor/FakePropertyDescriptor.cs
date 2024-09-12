using System;
using System.ComponentModel;

namespace EditorLib.FieldProcessor
{
  public class FakePropertyDescriptor : PropertyDescriptor
  {
    private readonly Type propertyType;

    public FakePropertyDescriptor() 
      : this(typeof(object))
    {
    }

    public FakePropertyDescriptor( Type _propertyType )
      : base( "fakeProperty", new Attribute[0] )
    {
      propertyType = _propertyType;
    }

    public override object GetValue( object component )
    {
      return component;
    }

    #region We don't interested in this methods and properties

    public override void SetValue( object component, object value )
    {

    }

    public override Type ComponentType
    {
      get { return typeof( object ); }
    }

    public override bool IsReadOnly
    {
      get { return false; }
    }

    public override Type PropertyType
    {
      get 
      {
        return propertyType; 
      }
    }

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
  }
}