using System;
using System.ComponentModel;
using System.Globalization;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.FieldProcessor;
using libdb.Animated;

namespace EditorPlugins.Extensions
{
  [ApplicableForDeriver]
  public sealed class AnimatedExtensions : TypedStringConvertor<IAnimated>
  {
    public AnimatedExtensions(IEditorWinApplication application) : base(application) 
    {

    }

    public override bool SuppressProperties
    {
      get { return false; }
    }

    protected override IAnimated ConvertFromStringInternal(ITypeDescriptorContext context, object instance, CultureInfo culture, string value)
    {
      IAnimated result = context.PropertyDescriptor.GetValue(instance) as IAnimated;

      var converter = GetConverter(result.ValueType);

      var fakeContext = new FakeDescriptorContext(result.GetObjectValue(0));

      var anim = converter.ConvertFromString(fakeContext, culture, value);
      result.Clear(anim);

      return result;
    }

    protected override string ConvertToString(ITypeDescriptorContext context, object instance, CultureInfo culture, IAnimated value)
    {
      string result = string.Empty;

      if (value.Type == AnimatedType.None)
      {
        var converter = GetConverter(value.ValueType);

        if (converter != null)
        {
          result = converter.ConvertToString(context, culture, value.GetObjectValue(0));
        }
      }
      else
      {
        result = "not const";//string.Format("Length: {0}", value.Length);
      }

      return result;
    }

    private IStringConvertor GetConverter(Type type)
    {
      return Application.Application.Extensions.CreateStringConverter(type, null, Application);
    }

  }
}
