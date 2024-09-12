using System;
using System.ComponentModel;

namespace EditorLib.FieldProcessor
{
  public class FakeDescriptorContext : ITypeDescriptorContext
  {
    private readonly object instance;

    public FakeDescriptorContext( object _instance )
    {
      instance = _instance;
    }

    public IContainer Container
    {
      get { return null; }
    }

    public object Instance
    {
      get { return instance; }
    }

    public PropertyDescriptor PropertyDescriptor
    {
      get 
      { 
        if(instance != null)
          return new FakePropertyDescriptor(instance.GetType());

        return new FakePropertyDescriptor(); 
      }
    }

    #region We don't interested in this methods and properties

    public void OnComponentChanged()
    {
    }

    public bool OnComponentChanging()
    {
      return false;
    }

    public object GetService( Type serviceType )
    {
      return new object();
    }

    #endregion
  }
}