using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Xml;
using System.Collections;

namespace EaselLevelEditor
{
  /// <summary>
  /// xml to spline loading mechanism
  /// </summary>
  class SplineXMLLoader
  {
    protected readonly EaselSpline easelSpline;
    protected readonly EaselScaler easelScaler;

    public SplineXMLLoader(EaselSpline _easelSpline,EaselScaler _easelScaler)
    {
      easelSpline = _easelSpline;
      easelScaler = _easelScaler;
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

     private bool ObtainSplineData(XmlDocument xml)
     {
       XmlNode cpNumNode = xml.SelectSingleNode("DBEaselSpline/spline/cpnum");
       if(cpNumNode == null)
         return false;

       // получаю список точек
       List<Point> splinePoints;
       if (ObtainPointsData(xml, out splinePoints) == false)
         return false;

       // инициализирую сплайн новыми данными
       easelSpline.InitSpline(splinePoints, System.Convert.ToInt32(cpNumNode.InnerText, 10));

       return true;
     }

     protected virtual bool ObtainPointsData(XmlDocument xml, out List<Point> splinePoints)
     {
       XmlNodeList _points = xml.SelectNodes("DBEaselSpline/spline/points/point");
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
