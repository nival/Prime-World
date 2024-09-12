using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;

namespace EaselLevelEditor
{
  /// <summary>
  /// common information form 
  /// </summary>
  public partial class EaselLevelInfoForm : Form
  {
    private EaselSpline      easelSpline;  // spline class
    private EaselScaler      easelScaler;  // scaler class
    private EaselLevelEditor easelEditor;  // easel editor

    public EaselLevelInfoForm(EaselSpline _easelSpline,
                          EaselScaler _easelScaler,
                          EaselLevelEditor _easelEditor) : base()
    {
      easelSpline = _easelSpline;
      easelScaler = _easelScaler;
      easelEditor = _easelEditor;

      // common initialization
      InitializeComponent();
      
      // internal initialization 
      ReinitDataFields();
    }

    private void ReinitDataFields()
    {
      textBoardHeight.Text = easelScaler.LogicalHeight.ToString();
      textBoardWidth.Text  = easelScaler.LogicalWidth.ToString();

      textControlPointsNum.Text = easelSpline.ControlPointsNum.ToString();
      textSplineDegree.Text = easelSpline.CurveDegree.ToString();

      //listControlPointsData.Columns.Add("CP Num", -2, HorizontalAlignment.Center);
      //listControlPointsData.Columns.Add("X Coord", -2, HorizontalAlignment.Center);
      //listControlPointsData.Columns.Add("Y Coord", -2, HorizontalAlignment.Center);

      // setting details view
      listControlPointsData.Items.Clear();
      listControlPointsData.View = View.Details;
      
      // filling view with control points
      Point[] cpPoints = easelSpline.ControlPoints;
      for(int i=0; i<cpPoints.Length; i++)
      {
        ListViewItem item = new ListViewItem((i + 1).ToString());
        item.SubItems.Add(cpPoints[i].X.ToString());
        item.SubItems.Add(cpPoints[i].Y.ToString());
        listControlPointsData.Items.Add(item);
      }
    }

    private void btnAddCP_Click(object sender, EventArgs e)
    {
      AddPointForm addForm = new AddPointForm(0, 0, easelSpline.ControlPointsNum);
      DialogResult dlgRes = addForm.ShowDialog();
      if (dlgRes == DialogResult.OK)
      {
        // рассчитать логическую точку вставки
        Point pointToAdd = new Point();
        pointToAdd.X = addForm.X;
        pointToAdd.Y = addForm.Y;
        
        // добавить точку
        easelSpline.AddControlPointAtNumber(pointToAdd, addForm.Index);
        ReinitDataFields();

        easelEditor.Invalidate();
      }
    }

    private void btnRemoveCP_Click(object sender, EventArgs e)
    {
      ListView.SelectedListViewItemCollection selection = listControlPointsData.SelectedItems;
      IEnumerator selectionEnum = selection.GetEnumerator();
      if ( selectionEnum.MoveNext()  )
      {
        ListViewItem item = (ListViewItem)selectionEnum.Current;
        int cpIndex = System.Convert.ToInt32(item.SubItems[0].Text, 10);
        easelSpline.RemoveControlPointAtNumber(cpIndex);
        ReinitDataFields();

        easelEditor.Invalidate();
      }
    }

    private void btnSaveLevel_Click(object sender, EventArgs e)
    {
      SaveFileDialog fileDlg = new SaveFileDialog();
      fileDlg.InitialDirectory = "c:\\";
      fileDlg.Filter = "XML Files|*.xml";
      DialogResult dlgRes = fileDlg.ShowDialog();
      if (dlgRes == DialogResult.OK)
      {
        SplineXMLSaver saver = new SplineXMLSaver(easelSpline, easelScaler);
        saver.SaveData((fileDlg.FileName));
      }      
    }
  }
}
