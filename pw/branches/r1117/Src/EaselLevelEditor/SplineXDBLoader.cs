using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Xml;
using System.Collections;

namespace EaselLevelEditor
{
  class SplineXDBLoader : SplineXMLLoader
  {
    public SplineXDBLoader(EaselSpline _easelSpline,EaselScaler _easelScaler) : base(_easelSpline,_easelScaler)
    {

    }

    protected override bool ObtainPointsData(XmlDocument xml, out List<Point> splinePoints)
    {
      XmlNodeList _points = xml.SelectNodes("DBEaselSpline/spline/points/point/Item");
      if (_points == null)
      {
        splinePoints = new List<Point>();
        return false;
      }

      splinePoints = new List<Point>(_points.Count);
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

      return true;
    }
  }
}
