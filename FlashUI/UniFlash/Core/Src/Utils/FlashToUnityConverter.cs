using SwfDotNet.IO.Tags.Types;
using UnityEngine;

namespace Flash.Utils
{
  public class FlashToUnityConverter
  {
    public const float TWIPS_TO_PIXELS = 0.05F;
    private static readonly float[] _normByte = new float[256];

    static FlashToUnityConverter()
    {
      for (int i = 0; i < 256; ++i)
      {
        float f = (float)i / 255;
        _normByte[i] = f;
      }
    }
    public static Vector3 ConvertPosition(int x, int y)
    {
      return new Vector3(x * TWIPS_TO_PIXELS, y * TWIPS_TO_PIXELS, 0);
    }
    public static float TwipsToPixels(float twips)
    {
      return twips * TWIPS_TO_PIXELS;
    }
    public static Color ConvertColor(RGBColor rgbColor)
    {
      Color color;

      if (rgbColor is RGBA)
        color = new Color(_normByte[rgbColor.red], _normByte[rgbColor.green], _normByte[rgbColor.blue], _normByte[(rgbColor as RGBA).alpha]);
      else
        color = new Color(_normByte[rgbColor.red], _normByte[rgbColor.green], _normByte[rgbColor.blue], 1);

      return color;
    }
    public static Color ConvertColor(System.Drawing.Color color)
    {
      Color result = Color.white;
      result.r = color.R / 255F;
      result.g = color.G / 255F;
      result.b = color.B / 255F;
      result.a = color.A / 255F;
      return result;
    }
    public static Matrix4x4 ConvertBitmapMatrix(Matrix matrix)
    {
      if (matrix == null)
        return Matrix4x4.identity;

      Matrix4x4 result = Matrix4x4.identity;
      float[,] matrixData = matrix.MatrixData;

      result[0, 0] = matrixData[0, 0] * TWIPS_TO_PIXELS;
      result[0, 1] = matrixData[0, 1] * TWIPS_TO_PIXELS;
      result[0, 2] = 0;
      result[0, 3] = matrixData[0, 2] * TWIPS_TO_PIXELS;

      result[1, 0] = matrixData[1, 0] * TWIPS_TO_PIXELS;
      result[1, 1] = matrixData[1, 1] * TWIPS_TO_PIXELS;
      result[1, 2] = 0;
      result[1, 3] = matrixData[1, 2] * TWIPS_TO_PIXELS;

      result[2, 0] = matrixData[2, 0] * TWIPS_TO_PIXELS;
      result[2, 1] = matrixData[2, 1] * TWIPS_TO_PIXELS;
      result[2, 2] = 1;
      result[2, 3] = 0;

      result[3, 0] = 0;
      result[3, 1] = 0;
      result[3, 2] = 0;
      result[3, 3] = 1;

      return result;
    }
    public static Matrix4x4 ConvertGradientMatrix(Matrix matrix)
    {
      if (matrix == null)
        return Matrix4x4.identity;

      Matrix4x4 result = Matrix4x4.identity;
      float[,] matrixData = matrix.MatrixData;

      result[0, 0] = matrixData[0, 0];
      result[0, 1] = matrixData[0, 1];
      result[0, 2] = 0;
      result[0, 3] = matrixData[0, 2] * TWIPS_TO_PIXELS;

      result[1, 0] = matrixData[1, 0];
      result[1, 1] = matrixData[1, 1];
      result[1, 2] = 0;
      result[1, 3] = matrixData[1, 2] * TWIPS_TO_PIXELS;

      result[2, 0] = matrixData[2, 0];
      result[2, 1] = matrixData[2, 1];
      result[2, 2] = 1;
      result[2, 3] = 0;

      result[3, 0] = 0;
      result[3, 1] = 0;
      result[3, 2] = 0;
      result[3, 3] = 1;

      return result;
    }
    public static Matrix4x4 ConvertTransformMatrix(Matrix matrix)
    {
      if (matrix == null)
        return Matrix4x4.identity;

      Matrix4x4 result = Matrix4x4.identity;
      float[,] matrixData = matrix.MatrixData;

      result[0, 0] = matrixData[0, 0];
      result[0, 1] = matrixData[0, 1];
      result[0, 2] = 0;
      result[0, 3] = matrixData[0, 2] * TWIPS_TO_PIXELS;

      result[1, 0] = matrixData[1, 0];
      result[1, 1] = matrixData[1, 1];
      result[1, 2] = 0;
      result[1, 3] = matrixData[1, 2] * TWIPS_TO_PIXELS;

      result[2, 0] = matrixData[2, 0];
      result[2, 1] = matrixData[2, 1];
      result[2, 2] = 1;
      result[2, 3] = 0;

      result[3, 0] = 0;
      result[3, 1] = 0;
      result[3, 2] = 0;
      result[3, 3] = 1;

      return result;
    }
  }
}