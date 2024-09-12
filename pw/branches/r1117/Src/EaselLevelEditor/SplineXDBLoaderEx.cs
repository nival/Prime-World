using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Xml;
using System.Collections;

namespace EaselLevelEditor
{
  /// <summary>
  /// real XDB loading mechanism to both splines
  /// </summary>
  class SplineXDBLoaderEx
  {
    protected readonly EaselSpline easelSpline1;
    protected readonly EaselSpline easelSpline2;
    protected readonly EaselScaler easelScaler;

    public SplineXDBLoaderEx(EaselSpline _easelSpline1,EaselSpline _easelSpline2,EaselScaler _easelScaler)
    {
      easelSpline1 = _easelSpline1;
      easelSpline2 = _easelSpline2;
      easelScaler  = _easelScaler;
    }

    public bool LoadData(string strFileName)
    {
      XmlDocument xml = new XmlDocument();

      // загружаю xml
      xml.Load(strFileName);

      // получаю Board данные и гружу их
      if (ObtainBoardData(xml) == false)
        return false;

      // получаю сплайн данные и гружу их
      if (ObtainSplineData(xml) == false)
        return false;

      return true;
    }

    private bool ObtainBoardData(XmlDocument xml)
    {
      XmlNode widthNode = xml.SelectSingleNode("DBEaselSpline/board/width");
      if (widthNode == null)
        return false;

      XmlNode heightNode = xml.SelectSingleNode("DBEaselSpline/board/height");
      if (heightNode == null)
        return false;

      easelScaler.LogicalWidth = System.Convert.ToInt32(widthNode.InnerText, 10);
      easelScaler.LogicalHeight = System.Convert.ToInt32(heightNode.InnerText, 10);

      return true;
    }

    private bool ObtainSplineData(XmlDocument _xml)
    {
      XmlNodeList _splines = _xml.SelectNodes("DBEaselSpline/path/Item/DBEaselPath/spline");
      if(_splines == null)
        return false;

      if (_splines.Count > 2 || _splines.Count < 0)
        return false;

      if(_splines.Count == 0)
      {
        List<Point> points1 = new List<Point>(0);
        easelSpline1.InitSpline(points1, 0);

        List<Point> points2 = new List<Point>(0);
        easelSpline2.InitSpline(points2, 0);

        return true;
      }
      else if(_splines.Count == 1)
      {
        XmlNode _spline1 = _splines[0];

        List<Point> points2 = new List<Point>(0);
        easelSpline2.InitSpline(points2, 0);

        return ObtainPointsData(_spline1, easelSpline1);
      }
      else  // count = 2
      {
        bool fRes = false;

        XmlNode _spline1 = _splines[0];
        XmlNode _spline2 = _splines[1];

        if (ObtainPointsData(_spline1, easelSpline1))
          if (ObtainPointsData(_spline2, easelSpline2))
            fRes = true;

        return fRes;
      }
    }

    protected virtual bool ObtainPointsData(XmlNode _splineNode, EaselSpline _spline)
    {
      XmlNode cpNumNode = _splineNode.SelectSingleNode("cpnum");
      if (cpNumNode == null)
        return false;

      XmlNodeList _points = _splineNode.SelectNodes("points/point/Item");
      if (_points == null)
      {
        _spline.InitSpline(new List<Point>(), 0);
        return false;
      }

      List<Point> splinePoints = new List<Point>(_points.Count);
      for (int i = 0; i < _points.Count; i++)
      {
        XmlNode point = _points.Item(i);

        XmlNode xNode = point.SelectSingleNode("x");
        if (xNode == null)
          return false;

        XmlNode yNode = point.SelectSingleNode("y");
        if (yNode == null)
          return false;

        Point _point = new Point();
        _point.X = System.Convert.ToInt32(xNode.InnerText, 10);
        _point.Y = System.Convert.ToInt32(yNode.InnerText, 10);

        splinePoints.Add(_point);
      }
      
      return _spline.InitSpline(splinePoints, System.Convert.ToInt32(cpNumNode.InnerText));
    }
  }
}
