using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;

namespace EaselLevelEditor
{
  /// <summary>
  /// scaler class is used to provide proper scaling
  /// between logical easel coordinates and current window dimensions
  /// </summary>
  public class EaselScaler
  {
    public int LogicalWidth
    {
      get { return logicalWidth; }
      set
      {
        if (value > 0)
          logicalWidth = value;
      }
    }

    public int LogicalHeight
    {
      get { return logicalHeight; }
      set
      {
        if (value > 0)
          logicalHeight = value;
      }
    }

    public int ScreenHeight
    {
      get { return screenHeight; }
      set 
      {
        if (value > 0)
          screenHeight = value;
      }
    }

    public int ScreenWidth
    {
      get { return screenWidth; }
      set 
      {
        if (value > 0)
          screenWidth = value;
      }
    }

    // max logical coords
    private int logicalWidth;
    private int logicalHeight;

    // max screen coords
    private int screenHeight;
    private int screenWidth;
    
    // constructor
    public EaselScaler(int _logicalWidth,
                       int _logicalHeght,
                       int _screenWidth,
                       int _screenHeight)
    {
      logicalHeight = _logicalHeght;
      logicalWidth  = _logicalWidth;

      screenHeight = _screenHeight;
      screenWidth  = _screenWidth;
    }

    // point recalculation method
    // coordinates here come in logical unit, out - screen units
    public bool RecalculateToScaledCoordinate(Point coord,out Point recalcCoord)
    {
      if(coord.X > logicalWidth || coord.Y > logicalHeight)
      {
        recalcCoord = new Point();
        recalcCoord.X = 0;
        recalcCoord.Y = 0;
        return false;
      }

      recalcCoord = new Point();
      recalcCoord.X = (coord.X * screenWidth) / logicalWidth;
      recalcCoord.Y = (coord.Y * screenHeight) / logicalHeight;
      
      return true;
    }

    public bool RecalculateToLogicalCoordinate(Point coord,out Point recalcCooord)
    {
      if(coord.X > screenWidth || coord.Y > screenHeight)
      {
        recalcCooord = new Point();
        recalcCooord.X = 0;
        recalcCooord.Y = 0;
        return false;
      }

      recalcCooord = new Point();
      recalcCooord.X = (coord.X * logicalWidth) / screenWidth;
      recalcCooord.Y = (coord.Y * logicalHeight) / screenHeight;

      return true;
    }

    public bool RecalculateToScaledWidth(int width,out int scaledWidth)
    {
      scaledWidth = width * screenWidth / logicalWidth;
      return true;
    }

    public bool RecalcutaeToScaledHeight(int height,out int scaledHeight)
    {
      scaledHeight = height * screenHeight / logicalHeight;
      return true;
    }

    public bool RecalculateToLogicalWidth(int width, out int _logicalWidth)
    {
      _logicalWidth = logicalWidth * width / screenWidth;
      return true;
    }

    public bool RecalculateToLogicalHeight(int height, out int _logicalHeight)
    {
      _logicalHeight = logicalHeight * height / screenHeight;
      return true;
    }
  }
}
