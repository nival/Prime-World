using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;
using System.Xml;

namespace EaselLevelEditor
{
  /// <summary>
  /// spline to xml saving mechanism
  /// </summary>
  public class SplineXMLSaver
  {
    protected readonly EaselSpline easelSpline;
    protected readonly EaselScaler easelScaler;

    public SplineXMLSaver(EaselSpline _easelSpline,EaselScaler _easelScaler)
    {
      easelSpline = _easelSpline;
      easelScaler = _easelScaler;
    }

    public void SaveData(string strFileName)
    {
      XmlDocument xml = new XmlDocument();

      // создать декларацию документа
      CreateXmlDeclaration(xml);
       
      // cоздать базовый нод
      XmlNode nodeLevel = xml.CreateNode(XmlNodeType.Element, "DBEaselSpline", null);
      
      // добавить данные по доске
      SaveBoardData(xml, nodeLevel);
   
      // добавить данные по сплайну
      SaveSplineData(xml, nodeLevel);
            
      // добавить базовый нод в xml
      xml.AppendChild(nodeLevel);

      // cохранить xml
      xml.Save(strFileName);
    }

    #region internal data savers
    private void CreateXmlDeclaration(XmlDocument xml)
    {
      XmlNode declar = xml.CreateNode(XmlNodeType.XmlDeclaration, "?xml version='1.0'?", null);
      xml.AppendChild(declar);
    }

    private void SaveBoardData(XmlDocument xml,XmlNode levelNode)
    {
      // создать Board нод
      XmlNode boardNode = xml.CreateNode(XmlNodeType.Element, "board", null);

      XmlNode widthNode = xml.CreateNode(XmlNodeType.Element, "width", null);
      widthNode.InnerText = easelScaler.LogicalWidth.ToString();
      boardNode.AppendChild(widthNode);

      XmlNode heightNode = xml.CreateNode(XmlNodeType.Element, "height", null);
      heightNode.InnerText = easelScaler.LogicalHeight.ToString();
      boardNode.AppendChild(heightNode);

      levelNode.AppendChild(boardNode);
    }

    private void SaveSplineData(XmlDocument xml, XmlNode levelNode)
    {
      // создать сплайн нод
      XmlNode splineNode = xml.CreateNode(XmlNodeType.Element, "spline", null);

      XmlNode degreeNode = xml.CreateNode(XmlNodeType.Element, "degree", null);
      degreeNode.InnerText = easelSpline.CurveDegree.ToString();
      splineNode.AppendChild(degreeNode);

      XmlNode cpnumNode = xml.CreateNode(XmlNodeType.Element, "cpnum", null);
      cpnumNode.InnerText = easelSpline.ControlPointsNum.ToString();
      splineNode.AppendChild(cpnumNode);

      XmlNode pointsNode = xml.CreateNode(XmlNodeType.Element, "points", null);

      // добавляю контрольные точки сплайна
      SaveControlPoints(xml, pointsNode);

      splineNode.AppendChild(pointsNode);

      levelNode.AppendChild(splineNode);
    }

    protected virtual void SaveControlPoints(XmlDocument xml,XmlNode cpNode)
    {
      Point[] points = easelSpline.ControlPoints;

      for(int i=0; i<points.Length; i++)
      {
        XmlNode pointNode = xml.CreateNode(XmlNodeType.Element, "point", null);

        XmlNode xNode = xml.CreateNode(XmlNodeType.Element, "x", null);
        xNode.InnerText = points[i].X.ToString();
        pointNode.AppendChild(xNode);

        XmlNode yNode = xml.CreateNode(XmlNodeType.Element, "y", null);
        yNode.InnerText = points[i].Y.ToString();
        pointNode.AppendChild(yNode);
        
        cpNode.AppendChild(pointNode);
      }
    }
    #endregion
  }
}
