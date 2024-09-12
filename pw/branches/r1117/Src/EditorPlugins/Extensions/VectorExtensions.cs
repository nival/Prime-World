using System.ComponentModel;
using System.Globalization;
using System.Text;
using DBTypes;
using EditorLib;
using EditorLib.FieldProcessor;
using EditorPlugins.Editors.MatrixType;

namespace EditorPlugins.Extensions
{
  public sealed class Vec2StringConvertor : TypedStringConvertor<Vec2>
  {
    public Vec2StringConvertor(IEditorWinApplication application) : base(application) { }

    public override bool SuppressProperties
    {
      get { return false; }
    }

    protected override Vec2 ConvertFromStringInternal(ITypeDescriptorContext context, object instance, CultureInfo culture, string value)
    {
      DBTypes.Vec2 result = context.PropertyDescriptor.GetValue(instance) as DBTypes.Vec2;

      if(result != null)
      {
        float[] vec;
        if (VectorExtensions.TryParse(value, 2, out vec))
        {
          result.x = vec[0];
          result.y = vec[1];
        }
      }

      return result;
    }

    protected override string ConvertToString(ITypeDescriptorContext context, object instance, CultureInfo culture, Vec2 value)
    {
      return VectorExtensions.GetString(value.x, value.y);
    }
  }

  public sealed class Vec3StringConvertor : TypedStringConvertor<Vec3>
  {
    public Vec3StringConvertor(IEditorWinApplication application) : base(application) { }

    public override bool SuppressProperties
    {
      get { return false; }
    }

    protected override Vec3 ConvertFromStringInternal(ITypeDescriptorContext context, object instance, CultureInfo culture, string value)
    {
      DBTypes.Vec3 result = context.PropertyDescriptor.GetValue(instance) as DBTypes.Vec3;

      if(result != null)
      {
        float[] vec;
        if (VectorExtensions.TryParse(value, 3, out vec))
        {
          result.x = vec[0];
          result.y = vec[1];
          result.z = vec[2];
        }
      }

      return result;
    }

    protected override string ConvertToString(ITypeDescriptorContext context, object instance, CultureInfo culture, Vec3 value)
    {
      return VectorExtensions.GetString(value.x, value.y, value.z);
    }
  }

  public sealed class ScaleStringConvertor : TypedStringConvertor<DBTypes.Scale>
  {
    public ScaleStringConvertor(IEditorWinApplication application) : base(application) { }

    public override bool SuppressProperties
    {
      get { return false; }
    }

    protected override Scale ConvertFromStringInternal(ITypeDescriptorContext context, object instance, CultureInfo culture, string value)
    {
      DBTypes.Scale result = context.PropertyDescriptor.GetValue(instance) as DBTypes.Scale;

      if(result != null)
      {
        float[] vec;
        if (VectorExtensions.TryParse(value, 3, out vec))
        {
          result.x = vec[0];
          result.y = vec[1];
          result.z = vec[2];
        }
      }

      return result;
    }

    protected override string ConvertToString(ITypeDescriptorContext context, object instance, CultureInfo culture, Scale value)
    {
      return VectorExtensions.GetString(value.x, value.y, value.z);
    }
  }

  public sealed class QuatStringConvertor : TypedStringConvertor<Quat>
  {
    public QuatStringConvertor(IEditorWinApplication application) : base(application) { }

    public override bool SuppressProperties
    {
      get { return true; }
    }

    protected override Quat ConvertFromStringInternal(ITypeDescriptorContext context, object instance, CultureInfo culture, string value)
    {
      DBTypes.Quat result = context.PropertyDescriptor.GetValue(instance) as DBTypes.Quat;

      if(result != null)
      {
        float[] vec;
        if(VectorExtensions.TryParse(value, 3, out vec))
        {
          var converter = new DBTypes.AnimatedQuat.Converter();
          result = converter.ConvertTo(vec);
        }
      }

      return result;
    }

    protected override string ConvertToString(ITypeDescriptorContext context, object instance, CultureInfo culture, Quat value)
    {
      float rotateX, rotateY, rotateZ;

      MatrixUtils.ToEuler(value, out rotateX, out rotateY, out rotateZ);

      //Z и X поменяны местами, см. DBTypes.AnimatedQuat.Converter.ConvertFrom<>
      return VectorExtensions.GetString(rotateZ, rotateY, rotateX);
    }
  }

  internal class VectorExtensions
  {
    public static bool TryParse(string value, int count, out float[] vec)
    {
      string sep = CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator;
      value = value.Trim().Replace(".", sep).Replace(",", sep);

      string[] parts = value.Split(new []{" "}, System.StringSplitOptions.RemoveEmptyEntries);

      vec = new float[count];

      int partsCount = parts.Length;

      if (partsCount == 1)
      {
        float initAll;

        if (float.TryParse(parts[0], out initAll))
        {
          for (int i = 0; i < count; ++i)
          {
            vec[i] = initAll;
          }
          return true;
        }
      }
      else if ((partsCount > 1) && (partsCount <= count))
      {
        for (int i = 0; i < partsCount; ++i)
        {
          if (!float.TryParse(parts[i], out vec[i]))
          {
            return false;
          }
        }
        return true;
      }
 
      return false;
    }

    public static string GetString(params float[] values)
    {
      if (values == null || values.Length == 0)
        return string.Empty;

      StringBuilder sb = new StringBuilder();

      foreach (var item in values)
      {
        sb.AppendFormat("{0:0.##} ", item);
      }

      return sb.ToString(0, sb.Length - 1);
    }
  }
}
