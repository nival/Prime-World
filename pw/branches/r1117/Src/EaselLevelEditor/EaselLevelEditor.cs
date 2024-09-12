using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Collections;

using EaselLevelEditor.Layers;

namespace EaselLevelEditor
{
  /// <summary>
  /// Layers enumeration
  /// </summary>
  public enum ELayers
  {
    Background,
    ControlPoints1,
    Spline1,
    SplinePath1,
    ControlPoints2,
    Spline2,
    SplinePath2,
  }
  
  /// <summary>
  /// Base editor form with its functionality
  /// </summary>
  public partial class EaselLevelEditor : Form
  {
    #region events

    public event DrawEditorData       eventDraw;
    public event UpdateEditorData     eventUpdate1;
    public event UpdateEditorData     eventUpdate2;
    public event ResizeEditorBegin    eventResizeBegin;
    public event ResizeEditor         eventResize;
    public event ResizeEditorEnd      eventResizeEnd;
    public event EditorMouseDblClick  eventMouseDblkClick;
    public event EditorMouseClick     eventMouseClick;
    public event EditorMouseBtnDown   eventMouseBtnDown;
    public event EditorMouseBtnUp     eventMousBtnUp;
    public event EditorMouseMove      eventMouseMove;
    public event LoadEditorBackground eventNeedLoadBackground;
    public event EventHandler         eventNeedCleanBackground;

    #endregion

    #region internal data
    //private Bitmap      backgroundImage; // background
    private EaselSpline easelSpline1;      // current Spline1 object
    private EaselSpline easelSpline2;      // current Spline2 object
    private EaselScaler easelScaler;       // coordinate scaling mechanism
    private string      easelDir;          // initial data directory

    Dictionary<ELayers, EaselEditorLayer> editorLayers;

    //private bool isCPShowChecked;
    #endregion

    #region constructors
    public EaselLevelEditor()
    {
      easelScaler = new EaselScaler(10000, 10000,
                                    this.ClientRectangle.Width,
                                    this.ClientRectangle.Height);

      easelDir = "c:\\";

      InitializeComponent();
      InitializeEmptySpline();

      editorLayers = new Dictionary<ELayers, EaselEditorLayer>();
      InitializeBackgroundLayer();
      InitializeSplineCPLayer();
      InitializeSplineLayer();      

      //isCPShowChecked = false;
      //this.ResizeRedraw = false;
      
      SendUpdateEvent();
    }
    #endregion

    #region Initialization methods

    // background layer initialization
    private void InitializeBackgroundLayer()
    {
      EaselEditorBackgroundLayer layer = new EaselEditorBackgroundLayer();

      this.eventResize += new ResizeEditor(layer.ResizeHandler);
      this.eventDraw   += new DrawEditorData(layer.DrawHandler);

      this.eventNeedLoadBackground  += new LoadEditorBackground(layer.LoadBackgroundHandler);
      this.eventNeedCleanBackground += new EventHandler(layer.ClearBackgroundHandler);
      
      editorLayers.Add(ELayers.Background, layer);
    }

    // spline layer initialization
    private void InitializeSplineLayer()
    {
      InitializeSplineLayer_1();
      InitializeSplineLayer_2();
    }

    private void InitializeSplineLayer_1()
    {
      EaselEditorSplineLayer layer = new EaselEditorSplineLayer();

      this.eventUpdate1 += new UpdateEditorData(layer.UpdateHandler);
      this.eventDraw += new DrawEditorData(layer.DrawHandler);

      editorLayers.Add(ELayers.Spline1, layer);
    }

    private void InitializeSplineLayer_2()
    {
      EaselEditorSplineLayer layer = new EaselEditorSplineLayer();

      this.eventUpdate2 += new UpdateEditorData(layer.UpdateHandler);
      this.eventDraw += new DrawEditorData(layer.DrawHandler);

      editorLayers.Add(ELayers.Spline2, layer);

      layer.Enabled = false;
    }

    // spline CP layer initialization
    private void InitializeSplineCPLayer()
    {
      InitializeSplineCPLayer_1();
      InitializeSplineCPLayer_2();
    }

    private void InitializeSplineCPLayer_1()
    {
      EaselEditorCPLayer layer = new EaselEditorCPLayer(this);

      this.eventUpdate1 += new UpdateEditorData(layer.UpdateHandler);
      this.eventDraw += new DrawEditorData(layer.DrawHandler);
      this.eventMouseDblkClick += new EditorMouseDblClick(layer.EditorMouseDblClickHandler);
      this.eventMouseMove += new EditorMouseMove(layer.EditorMouseMoveHandler);
      this.eventMouseClick += new EditorMouseClick(layer.EditorMouseClickHandler);
      this.eventMousBtnUp += new EditorMouseBtnUp(layer.EditorMouseBtnUpHandler);
      this.eventMouseBtnDown += new EditorMouseBtnDown(layer.EditorMouseBtnDownHandler);

      editorLayers.Add(ELayers.ControlPoints1, layer);
    }

    private void InitializeSplineCPLayer_2()
    {
      EaselEditorCPLayer layer = new EaselEditorCPLayer(this);

      this.eventUpdate2 += new UpdateEditorData(layer.UpdateHandler);
      this.eventDraw += new DrawEditorData(layer.DrawHandler);
      this.eventMouseDblkClick += new EditorMouseDblClick(layer.EditorMouseDblClickHandler);
      this.eventMouseMove += new EditorMouseMove(layer.EditorMouseMoveHandler);
      this.eventMouseClick += new EditorMouseClick(layer.EditorMouseClickHandler);
      this.eventMousBtnUp += new EditorMouseBtnUp(layer.EditorMouseBtnUpHandler);
      this.eventMouseBtnDown += new EditorMouseBtnDown(layer.EditorMouseBtnDownHandler);

      editorLayers.Add(ELayers.ControlPoints2, layer);

      layer.Enabled = false;
    }

    private void InitializeEmptySpline()
    {
      // инициализирую пустой сплайн
      easelSpline1 = new EaselSpline();
      easelSpline2 = new EaselSpline();
            
      List<Point> points = new List<Point>(0);
      easelSpline1.InitSpline(points, 0);

      List<Point> points1 = new List<Point>(0);
      easelSpline2.InitSpline(points1, 0);
    }
    #endregion

    #region paint operations
    protected override void OnPaintBackground(PaintEventArgs e)
    {
      //
    }

    protected override void OnPaint(PaintEventArgs e)
    {
      DrawEventArgs drawArgs = new DrawEventArgs();
      drawArgs.graphics = e.Graphics;
      eventDraw(this, drawArgs);
    }
    #endregion

    #region resize window operations 
    
    // resize window operations 
    protected override void  OnResize(EventArgs e)
    {
      if((Control.ModifierKeys & Keys.Shift) == Keys.Shift )
        this.Height = this.Width;
      
      easelScaler.ScreenWidth = this.ClientRectangle.Width;
      easelScaler.ScreenHeight = this.ClientRectangle.Height;

      ResizeEditorArgs args = new ResizeEditorArgs();
      args.editor = this;
      if(eventResize != null)
        eventResize(this, args);

      SendUpdateEvent();

      this.Invalidate();
    }

    protected override void OnResizeBegin(EventArgs e)
    {
      ResizeEditorArgs args = new ResizeEditorArgs();
      args.editor = this;
      if(eventResizeBegin != null)
        eventResizeBegin(this, args);

      SendUpdateEvent();
    }

    protected override void OnResizeEnd(EventArgs e)
    {
      easelScaler.ScreenWidth  = this.ClientRectangle.Width;
      easelScaler.ScreenHeight = this.ClientRectangle.Height;

      ResizeEditorArgs args = new ResizeEditorArgs();
      args.editor = this;
      if(eventResizeEnd != null)
        eventResizeEnd(this, args);

      SendUpdateEvent();

      this.Invalidate();
    }

    private void SendUpdateEvent()
    {
      UpdateEventArgs updateArgs = new UpdateEventArgs();
      updateArgs.scaler = easelScaler;
      updateArgs.spline = easelSpline1;
      if (eventUpdate1 != null)
        eventUpdate1(this, updateArgs);

      UpdateEventArgs updateArgs2 = new UpdateEventArgs();
      updateArgs2.scaler = easelScaler;
      updateArgs2.spline = easelSpline2;
      if (eventUpdate2 != null)
        eventUpdate2(this, updateArgs2);
    }

    #endregion

    #region mouse event delegates methods
    // mouse events delegates ....
    protected override void OnMouseDoubleClick(MouseEventArgs e)
    {
      if (eventMouseDblkClick != null)
        eventMouseDblkClick(this, e);
    }

    protected override void OnMouseClick(MouseEventArgs e)
    {
      if (eventMouseClick != null)
        eventMouseClick(this, e);
    }

    protected override void OnMouseDown(MouseEventArgs e)
    {
      if (eventMouseBtnDown != null)
        eventMouseBtnDown(this, e);
    }

    protected override void OnMouseUp(MouseEventArgs e)
    {
      if (eventMousBtnUp != null)
        eventMousBtnUp(this, e);
    }

    protected override void OnMouseMove(MouseEventArgs e)
    {
      if (eventMouseMove != null)
        eventMouseMove(this, e);
    }

    #endregion

    #region background menu element delegate methods
    // background menu element delegate methods
    private void loadBackgroundToolStripMenuItem_Click(object sender, EventArgs e)
    {
      LoadBackgroundEventArgs args = new LoadBackgroundEventArgs();
      args._editor = this;
      if(eventNeedLoadBackground != null)
        eventNeedLoadBackground(this, args);

      this.Invalidate();
    }

    private void clearBackgroundToolStripMenuItem_Click(object sender, EventArgs e)
    {
      if(eventNeedCleanBackground != null)
        eventNeedCleanBackground(this, EventArgs.Empty);
      this.Invalidate();
    }
    #endregion
    
    #region file menu element delegate methods
    private void newLevelToolStripMenuItem_Click(object sender, EventArgs e)
    {
      InitializeEmptySpline();
      SendUpdateEvent();
      Invalidate();
    }

    private void saveLevelToolStripMenuItem_Click(object sender, EventArgs e)
    {
      saveSplineToXML(easelSpline1);
    }

    private void loadLevelToolStripMenuItem_Click(object sender, EventArgs e)
    {
      loadSplineFromXML(easelSpline1);
    }

    private void saveLevelToXDBToolStripMenuItem_Click(object sender, EventArgs e)
    {
      saveSplineToXDB(easelSpline1);
    }

    private void loadLevelFromXDBToolStripMenuItem_Click(object sender, EventArgs e)
    {
      loadSplineFromXDB(easelSpline1);
    }

    private void saveSpline2ToXMLToolStripMenuItem_Click(object sender, EventArgs e)
    {
      saveSplineToXML(easelSpline2);
    }

    private void loadSpline2FromXMLToolStripMenuItem_Click(object sender, EventArgs e)
    {
      loadSplineFromXML(easelSpline2);
    }

    private void saveSpline2ToXDBToolStripMenuItem_Click(object sender, EventArgs e)
    {
      saveSplineToXDB(easelSpline2);
    }

    private void loadSpline2FromXDBToolStripMenuItem_Click(object sender, EventArgs e)
    {
     loadSplineFromXDB(easelSpline2); 
    }

    private void loadSplineFromXDB(EaselSpline _spline)
    {
      OpenFileDialog fileDlg = new OpenFileDialog();
      //fileDlg.InitialDirectory = "c:\\";
      fileDlg.InitialDirectory = easelDir;
      fileDlg.Filter = "XDB files|*.xdb";
      DialogResult dlgRes = fileDlg.ShowDialog();
      if (dlgRes == DialogResult.OK)
      {
        SplineXDBLoader loader = new SplineXDBLoader(_spline, easelScaler);
        if (loader.LoadData(fileDlg.FileName) == false)
          InitializeEmptySpline();

        easelDir = fileDlg.FileName;

        SendUpdateEvent();
        Invalidate();
      }
    }

    private void saveSplineToXDB(EaselSpline _spline)
    {
      SaveFileDialog fileDlg = new SaveFileDialog();
      //fileDlg.InitialDirectory = "c:\\";
      fileDlg.InitialDirectory = easelDir;
      fileDlg.Filter = "XDB Files|*.xdb";
      DialogResult dlgRes = fileDlg.ShowDialog();
      if (dlgRes == DialogResult.OK)
      {
        SplineXDBSaver saver = new SplineXDBSaver(_spline, easelScaler);
        saver.SaveData((fileDlg.FileName));

        easelDir = fileDlg.FileName;
      }
    }

    private void loadSplineFromXML(EaselSpline _spline)
    {
      OpenFileDialog fileDlg = new OpenFileDialog();
      //fileDlg.InitialDirectory = "c:\\";
      fileDlg.InitialDirectory = easelDir;
      fileDlg.Filter = "Xml files|*.xml";
      DialogResult dlgRes = fileDlg.ShowDialog();
      if (dlgRes == DialogResult.OK)
      {
        SplineXMLLoader loader = new SplineXMLLoader(_spline, easelScaler);
        if (loader.LoadData(fileDlg.FileName) == false)
          InitializeEmptySpline();

        easelDir = fileDlg.FileName;

        SendUpdateEvent();
        Invalidate();
      }
    }

    private void saveSplineToXML(EaselSpline _spline)
    {
      SaveFileDialog fileDlg = new SaveFileDialog();
      //fileDlg.InitialDirectory = "c:\\";
      fileDlg.InitialDirectory = easelDir;
      fileDlg.Filter = "XML Files|*.xml";
      DialogResult dlgRes = fileDlg.ShowDialog();
      if (dlgRes == DialogResult.OK)
      {
        SplineXMLSaver saver = new SplineXMLSaver(_spline, easelScaler);
        saver.SaveData((fileDlg.FileName));

        easelDir = fileDlg.FileName;
      }
    }

    #endregion

    #region view menu element delegate methods
    private void hideControlPointsToolStripMenuItem_Click(object sender, EventArgs e)
    {
      editorLayers[ELayers.ControlPoints1].Enabled = !editorLayers[ELayers.ControlPoints1].Enabled;
      if ( editorLayers[ELayers.ControlPoints1].Enabled  )
      {
        editorLayers[ELayers.ControlPoints2].Enabled = false;
      }

      SendUpdateEvent();
      Invalidate();
    }

    private void hideSplineToolStripMenuItem_Click(object sender, EventArgs e)
    {
      editorLayers[ELayers.Spline1].Enabled = !editorLayers[ELayers.Spline1].Enabled;
      Invalidate();
    }

    private void hideBackgroundToolStripMenuItem_Click(object sender, EventArgs e)
    {
      editorLayers[ELayers.Background].Enabled = !editorLayers[ELayers.Background].Enabled;
      Invalidate();
    }

    private void hideSpline2ToolStripMenuItem_Click(object sender, EventArgs e)
    {
      editorLayers[ELayers.Spline2].Enabled = !editorLayers[ELayers.Spline2].Enabled;
      Invalidate();
    }

    private void hideControlPoints2ToolStripMenuItem_Click(object sender, EventArgs e)
    {
      editorLayers[ELayers.ControlPoints2].Enabled = !editorLayers[ELayers.ControlPoints2].Enabled;
      if ( editorLayers[ELayers.ControlPoints2].Enabled  )
      {
        editorLayers[ELayers.ControlPoints1].Enabled = false;
      }

      SendUpdateEvent();
      Invalidate();
    }

    #endregion 

    private void loadXDBToolStripMenuItem_Click(object sender, EventArgs e)
    {
      OpenFileDialog fileDlg = new OpenFileDialog();
      //fileDlg.InitialDirectory = "c:\\";
      fileDlg.InitialDirectory = easelDir;
      fileDlg.RestoreDirectory = true;
      fileDlg.Filter = "XDB files|*.xdb";
      DialogResult dlgRes = fileDlg.ShowDialog();
      if (dlgRes == DialogResult.OK)
      {
        SplineXDBLoaderEx loader = new SplineXDBLoaderEx(easelSpline1,easelSpline2,easelScaler);
        if (loader.LoadData(fileDlg.FileName) == false)
          InitializeEmptySpline();

        easelDir = fileDlg.FileName;  

        SendUpdateEvent();
        Invalidate();
      }
    }

    private void saveXDBToolStripMenuItem_Click(object sender, EventArgs e)
    {
      SaveFileDialog fileDlg = new SaveFileDialog();
      //fileDlg.InitialDirectory = "c:\\";
      fileDlg.InitialDirectory = easelDir;
      fileDlg.Filter = "XDB files|*.xdb";
      DialogResult dlgRes = fileDlg.ShowDialog();
      if (dlgRes == DialogResult.OK)
      {
        SplineXDBSaverEx saver = new SplineXDBSaverEx(easelSpline1, easelSpline2, easelScaler);
        if (saver.SaveData(fileDlg.FileName) == false)
          MessageBox.Show("Unable to save XDB file");

        easelDir = fileDlg.FileName;
      }
    }

    private void fileToolStripMenuItem_Click(object sender, EventArgs e)
    {

    }
  }
}
