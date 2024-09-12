using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Xml;

namespace EaselLevelEditor
{
  class SplineXDBSaver : SplineXMLSaver
  {
    public SplineXDBSaver(EaselSpline _easelSpline,EaselScaler _easelScaler) : base(_easelSpline,_easelScaler)
    {

    }

    protected override void SaveControlPoints(XmlDocument xml, XmlNode cpNode)
    {
      Point[] points = easelSpline.ControlPoints;

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

      cpNode.AppendChild(pointNode);
    }
  }
}
