using System.ComponentModel;
using System.Drawing;
using EditorLib.FieldProcessor;
using System;
using EditorLib;
using System.Globalization;
using System.Drawing.Design;
using System.Windows.Forms;

namespace EditorPlugins.Extensions
{
  public sealed class ColorValuePainter : TypedValuePainter<DBTypes.Color>
  {
    public ColorValuePainter( IEditorWinApplication application ) : base( application ) { }

    protected override void PaintValue( ITypeDescriptorContext context, object instance, DBTypes.Color value, Graphics graphics, Rectangle bounds )
    {
      using ( SolidBrush brush = new SolidBrush( Color.FromArgb( value.R, value.G, value.B ) ) )
      {
        graphics.FillRectangle( brush, bounds );
      }
    }
  }

  public sealed class ColorValueEditor : TypedValueEditor<DBTypes.Color>
  {
    public ColorValueEditor( IEditorWinApplication application ) : base( application ) { }

    public override bool IsDropDownResizable { get { return false; } }

    public override UITypeEditorEditStyle EditorEditStyle { get { return UITypeEditorEditStyle.Modal; } }

    protected override DBTypes.Color EditValue( ITypeDescriptorContext context, object instance, IServiceProvider provider, DBTypes.Color value )
    {
      ColorDialog dlg = new ColorDialog() { AllowFullOpen = true, AnyColor = true, Color = Color.FromArgb( value.R, value.G, value.B ), FullOpen = true, ShowHelp = false, SolidColorOnly = false };
      if ( dlg.ShowDialog() != DialogResult.OK )
        return value;

      DBTypes.Color result = new DBTypes.Color();
      result.A = value.A;
      result.R = dlg.Color.R;
      result.G = dlg.Color.G;
      result.B = dlg.Color.B;

      return result;
    }
  }

  public sealed class ColorStringConvertor : TypedStringConvertor<DBTypes.Color>
  {
    public ColorStringConvertor( IEditorWinApplication application ) : base( application ) { }

    public override bool SuppressProperties
    {
      get { return false; }
    }

    protected override DBTypes.Color ConvertFromStringInternal( ITypeDescriptorContext context, object instance, CultureInfo culture, string value )
    {
    	DBTypes.Color result = context.PropertyDescriptor.GetValue(instance) as DBTypes.Color;

			if(result == null)
				return result;

			string v1 = value.Trim();
			string[] parts = v1.Split( new[] { ' ', ',', '.' } );

      if ( parts.Length < 3 || parts.Length > 4 )
        return result;

      int[] rgba = new int[4] { 255, 255, 255, 255 };

      for ( int i = 0; i < parts.Length; ++i )
      {
				if ( !int.TryParse( parts[i], out rgba[i] ) )
					return result;
      }

      result.R = rgba[0];
      result.G = rgba[1];
      result.B = rgba[2];
      result.A = rgba[3];


      return result;
    }

    protected override string ConvertToString( ITypeDescriptorContext context, object instance, CultureInfo culture, DBTypes.Color value )
    {
      return string.Format( "{0} {1} {2} {3}", value.R, value.G, value.B, value.A );
    }
  }

  public sealed class HDRColorValuePainter : TypedValuePainter<DBTypes.HDRColor>
  {
    public HDRColorValuePainter( IEditorWinApplication application ) : base( application ) { }

    protected override void PaintValue( ITypeDescriptorContext context, object instance, DBTypes.HDRColor value, Graphics graphics, Rectangle bounds )
    {
      int r = Math.Min( 255, Math.Max( 0, (int)Math.Round( value.R * 255.0f ) ) );
      int g = Math.Min( 255, Math.Max( 0, (int)Math.Round( value.G * 255.0f ) ) );
      int b = Math.Min( 255, Math.Max( 0, (int)Math.Round( value.B * 255.0f ) ) );

      using ( SolidBrush brush = new SolidBrush( Color.FromArgb( r, g, b ) ) )
      {
        graphics.FillRectangle( brush, bounds );
      }
    }
  }

  public sealed class HDRColorValueEditor : TypedValueEditor<DBTypes.HDRColor>
  {
    public HDRColorValueEditor( IEditorWinApplication application ) : base( application ) { }

    public override bool IsDropDownResizable { get { return false; } }

    public override UITypeEditorEditStyle EditorEditStyle { get { return UITypeEditorEditStyle.Modal; } }

    protected override DBTypes.HDRColor EditValue( ITypeDescriptorContext context, object instance, IServiceProvider provider, DBTypes.HDRColor value )
    {
      int r = Math.Min( 255, Math.Max( 0, (int)Math.Round( value.R * 255.0f ) ) );
      int g = Math.Min( 255, Math.Max( 0, (int)Math.Round( value.G * 255.0f ) ) );
      int b = Math.Min( 255, Math.Max( 0, (int)Math.Round( value.B * 255.0f ) ) );
      ColorDialog dlg = new ColorDialog() { AllowFullOpen = true, AnyColor = true, Color = Color.FromArgb( r, g, b ), FullOpen = true, ShowHelp = false, SolidColorOnly = false };
      if ( dlg.ShowDialog() != DialogResult.OK )
        return value;
   
      DBTypes.HDRColor result = new DBTypes.HDRColor();
      result.A = value.A;
      result.R = (float)dlg.Color.R / 255.0f;
      result.G = (float)dlg.Color.G / 255.0f;
      result.B = (float)dlg.Color.B / 255.0f;

      return result;
    }
  }

  public sealed class HDRColorStringConvertor : TypedStringConvertor<DBTypes.HDRColor>
  {
    public HDRColorStringConvertor( IEditorWinApplication application ) : base( application ) { }

    public override bool SuppressProperties
    {
      get { return false; }
    }

    protected override DBTypes.HDRColor ConvertFromStringInternal( ITypeDescriptorContext context, object instance, CultureInfo culture, string value )
    {
      DBTypes.HDRColor result = context.PropertyDescriptor.GetValue( instance ) as DBTypes.HDRColor;

			if ( result == null )
				return result;

			string sep = CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator;
			value = value.Trim().Replace( ".", sep ).Replace( ",", sep );

			string[] parts = value.Split( new [] { ' ' } );

      if ( parts.Length < 3 || parts.Length > 4 )
        return result;

      float[] rgba = new float[4] { 1, 1, 1, 1 };

			for ( int i = 0; i < parts.Length; ++i )
			{
				if ( !float.TryParse( parts[i], out rgba[i] ) )
					return result;
			}

			result.R = rgba[0];
			result.G = rgba[1];
			result.B = rgba[2];
			result.A = rgba[3];

      return result;
    }

    protected override string ConvertToString( ITypeDescriptorContext context, object instance, CultureInfo culture, DBTypes.HDRColor value )
    {
      return string.Format( "{0} {1} {2} {3}", value.R, value.G, value.B, value.A );
    }
  }
}