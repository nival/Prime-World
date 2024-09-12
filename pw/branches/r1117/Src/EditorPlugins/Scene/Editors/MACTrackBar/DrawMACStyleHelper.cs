using System;
using System.Drawing;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace EConTech.Windows.MACUI
{
	/// <summary>
	/// Summary description for DrawMACStyleHelper.
	/// </summary>
	public sealed class DrawMACStyleHelper
	{
		/// <summary>
		/// The contructor 
		/// </summary>
		private DrawMACStyleHelper()
		{
			//
			// TODO: Add constructor logic here
			//
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="g"></param>
		/// <param name="drawRectF"></param>
		/// <param name="drawColor"></param>
		/// <param name="orientation"></param>
		public static void DrawAquaPill(Graphics g, RectangleF drawRectF, Color drawColor, Orientation orientation)
			
		{
			Color color1;
			Color color2;
			Color color3;
			Color color4;
			Color color5;
			System.Drawing.Drawing2D.LinearGradientBrush gradientBrush;
			System.Drawing.Drawing2D.ColorBlend colorBlend = new System.Drawing.Drawing2D.ColorBlend();

			color1 = ColorHelper.OpacityMix(Color.White, ColorHelper.SoftLightMix(drawColor, Color.Black, 100), 40);
			color2 = ColorHelper.OpacityMix(Color.White, ColorHelper.SoftLightMix(drawColor, ColorHelper.CreateColorFromRGB(64, 64, 64), 100), 20);
			color3 = ColorHelper.SoftLightMix(drawColor, ColorHelper.CreateColorFromRGB(128, 128, 128), 100);
			color4 = ColorHelper.SoftLightMix(drawColor, ColorHelper.CreateColorFromRGB(192, 192, 192), 100);
			color5 = ColorHelper.OverlayMix(ColorHelper.SoftLightMix(drawColor, Color.White, 100), Color.White, 75);
			
			//			
			colorBlend.Colors = new Color[]{color1, color2, color3, color4, color5};
			colorBlend.Positions = new float[]{0, 0.25f, 0.5f, 0.75f, 1};
			if(orientation == Orientation.Horizontal)
				gradientBrush = new System.Drawing.Drawing2D.LinearGradientBrush(new Point((int)drawRectF.Left, (int)drawRectF.Top-1), new Point((int)drawRectF.Left, (int)drawRectF.Top + (int)drawRectF.Height+1), color1, color5);
			else
				gradientBrush = new System.Drawing.Drawing2D.LinearGradientBrush(new Point((int)drawRectF.Left-1, (int)drawRectF.Top), new Point((int)drawRectF.Left + (int)drawRectF.Width+1, (int)drawRectF.Top), color1, color5);
			gradientBrush.InterpolationColors = colorBlend;
			FillPill(gradientBrush, drawRectF, g);

			//
			color2 = Color.White;
			colorBlend.Colors = new Color[]{color2, color3, color4, color5};
			colorBlend.Positions = new float[]{0, 0.5f, 0.75f, 1};
			if(orientation == Orientation.Horizontal)
				gradientBrush = new System.Drawing.Drawing2D.LinearGradientBrush(new Point((int)drawRectF.Left + 1, (int)drawRectF.Top), new Point((int)drawRectF.Left + 1, (int)drawRectF.Top + (int)drawRectF.Height - 1), color2, color5);
			else
				gradientBrush = new System.Drawing.Drawing2D.LinearGradientBrush(new Point((int)drawRectF.Left, (int)drawRectF.Top + 1), new Point((int)drawRectF.Left + (int)drawRectF.Width - 1, (int)drawRectF.Top + 1), color2, color5);
			gradientBrush.InterpolationColors = colorBlend;
			FillPill(gradientBrush, RectangleF.Inflate(drawRectF,-3,-3), g);

		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="g"></param>
		/// <param name="drawRectF"></param>
		/// <param name="drawColor"></param>
		/// <param name="orientation"></param>
		public static void DrawAquaPillSingleLayer(Graphics g, RectangleF drawRectF, Color drawColor, Orientation orientation)
		{
			Color color1;
			Color color2;
			Color color3;
			Color color4;
			System.Drawing.Drawing2D.LinearGradientBrush gradientBrush;
			System.Drawing.Drawing2D.ColorBlend colorBlend = new System.Drawing.Drawing2D.ColorBlend();

			color1 = drawColor;
			color2 = ControlPaint.Light(color1);
			color3 = ControlPaint.Light(color2);
			color4 = ControlPaint.Light(color3);

			colorBlend.Colors = new Color[]{color1, color2, color3, color4};
			colorBlend.Positions = new float[]{0, 0.25f, 0.65f, 1};

			if(orientation == Orientation.Horizontal)
				gradientBrush = new System.Drawing.Drawing2D.LinearGradientBrush(new Point((int)drawRectF.Left, (int)drawRectF.Top), new Point((int)drawRectF.Left, (int)drawRectF.Top + (int)drawRectF.Height), color1, color4);
			else
				gradientBrush = new System.Drawing.Drawing2D.LinearGradientBrush(new Point((int)drawRectF.Left, (int)drawRectF.Top), new Point((int)drawRectF.Left + (int)drawRectF.Width, (int)drawRectF.Top), color1, color4);
			gradientBrush.InterpolationColors = colorBlend;

			FillPill(gradientBrush, drawRectF, g);

		}


		/// <summary>
		/// 
		/// </summary>
		/// <param name="b"></param>
		/// <param name="rect"></param>
		/// <param name="g"></param>
		public static void FillPill(Brush b, RectangleF rect, Graphics g)
		{
			if (rect.Width > rect.Height) 
			{
				g.SmoothingMode = SmoothingMode.HighQuality;
				g.FillEllipse(b, new RectangleF(rect.Left, rect.Top, rect.Height, rect.Height));
				g.FillEllipse(b, new RectangleF(rect.Left + rect.Width - rect.Height, rect.Top, rect.Height, rect.Height));				

				float w = rect.Width - rect.Height;
				float l = rect.Left + ((rect.Height)/ 2);
				g.FillRectangle(b, new RectangleF(l, rect.Top, w, rect.Height));
				g.SmoothingMode = SmoothingMode.Default;
			} 
			else if (rect.Width < rect.Height) 
			{
				g.SmoothingMode = SmoothingMode.HighQuality;
				g.FillEllipse(b, new RectangleF(rect.Left, rect.Top, rect.Width, rect.Width));
				g.FillEllipse(b, new RectangleF(rect.Left, rect.Top + rect.Height - rect.Width, rect.Width, rect.Width));				

				float t = rect.Top + (rect.Width/ 2);
				float h = rect.Height - rect.Width;
				g.FillRectangle (b, new RectangleF(rect.Left, t, rect.Width, h));				
				g.SmoothingMode = SmoothingMode.Default;
			} 
			else if (rect.Width == rect.Height) 
			{
				g.SmoothingMode = SmoothingMode.HighQuality;
				g.FillEllipse(b, rect);
				g.SmoothingMode = SmoothingMode.Default;
			}
		}

	}
}
