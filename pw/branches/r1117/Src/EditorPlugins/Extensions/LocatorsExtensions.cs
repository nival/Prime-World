using System;
using System.Collections.Generic;
using System.ComponentModel;
using EditorLib;
using EditorLib.FieldProcessor;
using EditorPlugins.Scene.Presets;

namespace EditorPlugins.Extensions
{
  public sealed class LocatorAttribute : Attribute
  {
  }

  public sealed class LocatorsValues : TwoTypedStandardValuesProvider<string, LocatorAttribute>
  {
    public LocatorsValues(IEditorWinApplication application, Attribute attribute) : base(application, attribute) { }

    public override bool IsStandardValuesExclusive(ITypeDescriptorContext context)
    {
      return true;
    }

    public override TypeConverter.StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
    {
      object instance = FullTypePropertyDescriptor.GetInstanceFromContext(context);
      List<string> newvalues = new List<string>();
      newvalues.Add("None");
      List<string> values = (instance as DefaultScenePreset.LocatorInfo).GetLocators();
      foreach (string _str in values)
      {
        newvalues.Add(_str);
      }
      return new TypeConverter.StandardValuesCollection(newvalues);
    }

    public override bool HasStandardValuesConvertor(ITypeDescriptorContext context)
    {
      return false;
    }

    public override Type GetStandardValuesType(ITypeDescriptorContext context)
    {
      return null;
    }

    protected override string ConvertFromStandardValueInternal(ITypeDescriptorContext context, object instance, object value)
    {
      return value as string;
    }
  }
}