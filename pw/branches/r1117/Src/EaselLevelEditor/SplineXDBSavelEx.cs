using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Xml;
using System.Collections;

namespace EaselLevelEditor
{
  /// <summary>
  /// real XDB saving mechanism to both splines into the real XDB
  /// </summary>
  class SplineXDBSaverEx
  {
    protected readonly EaselSpline easelSpline1;
    protected readonly EaselSpline easelSpline2;
    protected readonly EaselScaler easelScaler;

    public SplineXDBSaverEx(EaselSpline _easelSpline1,EaselSpline _easelSpline2,EaselScaler _easelScaler)
    {
      easelSpline1 = _easelSpline1;
      easelSpline2 = _easelSpline2;
      easelScaler  = _easelScaler;
    }

    public bool SaveData(string strFileName)
    {
      XmlDocument xml = new XmlDocument();

      // загружаю xml
      xml.Load(strFileName);

      XmlNodeList _splines = xml.SelectNodes("DBEaselSpline/path/Item/DBEaselPath/spline");
      if (_splines == null)
        return false;

      if (_splines.Count > 2 || _splines.Count <= 0)
        return false;

      if(_splines.Count == 1)
      {
        _splines[0].RemoveAll();
        SaveControlPoints(xml, _splines[0], easelSpline1);
      }
      else
      {
        _splines[0].RemoveAll();
        SaveControlPoints(xml, _splines[0], easelSpline1);
        _splines[1].RemoveAll();
        SaveControlPoints(xml, _splines[1], easelSpline2);
      }

      xml.Save(strFileName);
      return true;
    }

    protected virtual void SaveControlPoints(XmlDocument xml, XmlNode splineNode, EaselSpline _spline)
    {
      XmlNode degreeNode = xml.CreateNode(XmlNodeType.Element, "degree", null);
      degreeNode.InnerText = _spline.CurveDegree.ToString();
      splineNode.AppendChild(degreeNode);

      XmlNode cpnumNode = xml.CreateNode(XmlNodeType.Element, "cpnum", null);
      cpnumNode.InnerText = _spline.ControlPointsNum.ToString();
      splineNode.AppendChild(cpnumNode);

      XmlNode pointsNode = xml.CreateNode(XmlNodeType.Element, "points", null);
      splineNode.AppendChild(pointsNode);
                  
      Point[] points = _spline.ControlPoints;

      XmlNode pointNode = xml.CreateNode(XmlNodeType.Element, "point", null);

      for (int i = 0; i < points.Length; i++)
      {
        XmlNode itemNode = xml.CreateNode(XmlNodeType.Element, "Item", null);

        XmlNode xNode = xml.CreateNode(XmlNodeType.Element, "x", null);
        xNode.InnerText = points[i].X.ToString();
        itemNode.AppendChild(xNode);

        XmlNode yNode = xml.CreateNode(XmlNodeType.Element, "y", null);
        yNode.InnerText = points[i].Y.ToString();
        itemNode.AppendChild(yNode);

        pointNode.AppendChild(itemNode);
      }

      pointsNode.AppendChild(pointNode);
    }
  }
}
