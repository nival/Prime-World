using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Text;
using System.Windows.Forms;
using System.Drawing;

namespace EaselLevelEditor.Layers
{
  /// <summary>
  /// control points layer class
  /// </summary>
  class EaselEditorCPLayer : EaselEditorLayer
  {
    private System.Windows.Forms.ContextMenuStrip pointsMenuStrip;

    private EaselSpline      spline;
    private EaselScaler      scaler;
    private EaselLevelEditor editor;

    private Point mousePos;
    
    private const int CONTROL_POINT_OFFSET = 10;

    private EditorPoint[] editorPoints;
    private EditorPoint   draggedPoint;   // точка, которую перетаскивают

    public System.Windows.Forms.ContextMenuStrip PopupMenu
    {
      get { return pointsMenuStrip; }
    }

    public EaselEditorCPLayer(EaselLevelEditor _editor) :  base()
    {
      editor = _editor;

      InitPopupMenu();

      mousePos = new Point();
      mousePos.X = 0;
      mousePos.Y = 0;

      UpdateControlPoints();
    }

    protected override void vDraw(Graphics _graphics)
    {
      if (spline != null)
      {
        // рисуем линии
        if(editorPoints == null || editorPoints.Length ==0)
            return;

        Pen controlLinePen = new Pen(Color.Black, 2);

        Point basePoint, scaledBasePoint;
        Point currentPoint, scaledCurrentPoint;
                
        basePoint = editorPoints[0].Coord;
        scaler.RecalculateToScaledCoordinate(basePoint, out scaledBasePoint);
        
        for (int i = 1; i < editorPoints.Length; i++)
        {
          // отрисовать контрольную точку
          currentPoint = editorPoints[i].Coord;
          scaler.RecalculateToScaledCoordinate(currentPoint, out scaledCurrentPoint);

          // отрисовать линию между контрольными точками
          _graphics.DrawLine(controlLinePen, scaledBasePoint, scaledCurrentPoint);
          scaledBasePoint = scaledCurrentPoint;
        }

        // рисуем точки
        foreach (EditorPoint pt in editorPoints)
        {
          pt.DrawPoint(_graphics);
        }
      }
    }

    protected override void vUpdate(EaselSpline _spline, EaselScaler _scaler)
    {
      spline = _spline;
      scaler = _scaler;

      UpdateControlPoints();
    }

    private void UpdateControlPoints()
    {
      if (spline == null)
      {
         editorPoints = new EditorPoint[0];
         return;
      }

      Point[] controlPoints = spline.ControlPoints;

      editorPoints = new EditorPoint[controlPoints.Length];
      for(int i=0;i<controlPoints.Length;i++)
         editorPoints[i] = new EditorPoint(scaler, i + 1, controlPoints[i]);
    }

    protected override void vDblClick(MouseEventArgs _args)
    {
      if (_args.Button == MouseButtons.Left)
      {
        AddPointAtEnd(_args.X, _args.Y);

        UpdateControlPoints();
        editor.Invalidate();
      }
    }

    protected override void vClick(MouseEventArgs _args) 
    {
      if (_args.Button == MouseButtons.Right)
      {
        mousePos = _args.Location;
        pointsMenuStrip.Show(editor, mousePos);
      }
    }

    protected override void vMouseDown(MouseEventArgs _args) 
    {
      if (editorPoints == null)
        return;

      Point hitPoint;
      scaler.RecalculateToLogicalCoordinate(_args.Location,out hitPoint);

      // проверить попадание мышкой в элемент ...
      for(int i=0 ; i<editorPoints.Length; i++)
      {
        if ( editorPoints[i].CheckHit(hitPoint)  )
        {
          draggedPoint = editorPoints[i];
          return;
        }
      }

      draggedPoint = null; // попадания нету
    }

    protected override void vMouseUp(MouseEventArgs _args) 
    {
      draggedPoint = null; // точку больше ненужно тащить
    }

    protected override void vMouseMove(MouseEventArgs _args)
    {
      if(draggedPoint != null)  // у нас перетаскивается точка
      {
        int pointNum = draggedPoint.PointNumber;

        Point newCoords;
        scaler.RecalculateToLogicalCoordinate(_args.Location, out newCoords);

        spline.ReplaceControlPointAtNumber(newCoords, pointNum);
        
        // обновляю контрольные точки
        UpdateControlPoints();
        draggedPoint = editorPoints[pointNum - 1];

        // отрисовываю
        editor.Invalidate();
      }
    }

    protected override void vEnableDisable(bool fEnable)
    {
      
    }

    #region helper methods

    private void AddPointAtEnd(int xCoord, int yCoord)
    {
      Point pointToAdd = new Point();

      pointToAdd.X = xCoord;
      pointToAdd.Y = yCoord;

      Point pointLogical = new Point();
      scaler.RecalculateToLogicalCoordinate(pointToAdd, out pointLogical);

      // добавление точки в конец
      spline.AddControlPointAtEnd(pointLogical);
    }

    #endregion

    #region popup menu delegate operations
    // point menu strip item delegates
    private void pointsMenuStrip_Opening(object sender, CancelEventArgs e)
    {
      //
      // UDNONE !!! нужно проверять регион точки ....
      //
    }

    private void addPointToolStripMenuItem_Click(object sender, EventArgs e)
    {
      // отобразить меню с  списоком точек
      AddPointForm addForm = new AddPointForm(mousePos.X, mousePos.Y, spline.ControlPointsNum);
      DialogResult dlgRes = addForm.ShowDialog();
      if (dlgRes == DialogResult.OK)
      {
        // рассчитать логическую точку вставки
        Point pointToAdd = new Point();
        pointToAdd.X = addForm.X;
        pointToAdd.Y = addForm.Y;

        Point pointLogical = new Point();
        scaler.RecalculateToLogicalCoordinate(pointToAdd, out pointLogical);

        // добавить точку
        spline.AddControlPointAtNumber(pointLogical, addForm.Index);

        UpdateControlPoints();
        editor.Invalidate();
      }
    }

    private void pickPointToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Int64 lenght = 0;

      Point mouseLogic;
      scaler.RecalculateToLogicalCoordinate(mousePos, out mouseLogic);
      if (spline.GetLengthByCoords(mouseLogic,out lenght, 100) == 0)
        MessageBox.Show(lenght.ToString());
    }

    private void addPointAtEndToolStripMenuItem_Click(object sender, EventArgs e)
    {
      AddPointAtEnd(mousePos.X, mousePos.Y);
      UpdateControlPoints();
      editor.Invalidate();
    }

    private void removePointToolStripMenuItem_Click(object sender, EventArgs e)
    {
      RemovePointForm removeForm = new RemovePointForm(spline.ControlPointsNum);
      DialogResult dlgRes = removeForm.ShowDialog();
      if (dlgRes == DialogResult.OK)
      {
        spline.RemoveControlPointAtNumber(removeForm.Index);

        UpdateControlPoints();
        editor.Invalidate();
      }
    }

    private void showInfoToolStripMenuItem_Click(object sender, EventArgs e)
    {
      EaselLevelInfoForm levelInfo = new EaselLevelInfoForm(spline, scaler, editor);
      levelInfo.ShowDialog();
    }

    private void removePointAtEndToolStripMenuItem_Click(object sender, EventArgs e)
    {
      spline.RemoveControlPointAtNumber(spline.ControlPointsNum);

      UpdateControlPoints();
      editor.Invalidate();
    }

    #endregion

    #region popup menu initialization
    private void InitPopupMenu()
    {
      this.pointsMenuStrip = new System.Windows.Forms.ContextMenuStrip();
      this.pointsMenuStrip.Name = "pointsMenuStrip";
      this.pointsMenuStrip.Size = new System.Drawing.Size(61, 4);

      this.addPointAtEndToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.addPointToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.removePointToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
      this.showInfoToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.removePointAtEndToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.pickPointToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();

      pointsMenuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.pickPointToolStripMenuItem,
            this.toolStripSeparator2,
            this.addPointAtEndToolStripMenuItem,
            this.addPointToolStripMenuItem,
            this.removePointToolStripMenuItem,
            this.removePointAtEndToolStripMenuItem,
            this.toolStripSeparator1,
            this.showInfoToolStripMenuItem});
      pointsMenuStrip.Name = "pointsMenuStrip";
      pointsMenuStrip.Size = new System.Drawing.Size(183, 142);
      pointsMenuStrip.Opening += new System.ComponentModel.CancelEventHandler(this.pointsMenuStrip_Opening);
      
      //
      // pickPointToolStripMenuItem
      //
      this.pickPointToolStripMenuItem.Name = "pickPointToolStripMenuItem";
      this.pickPointToolStripMenuItem.Size = new System.Drawing.Size(182, 22);
      this.pickPointToolStripMenuItem.Text = "Pick Spline Point Lenght";
      this.pickPointToolStripMenuItem.Click += new System.EventHandler(this.pickPointToolStripMenuItem_Click);

      // 
      // toolStripSeparator2
      // 
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new System.Drawing.Size(179, 6);

      // 
      // addPointAtEndToolStripMenuItem
      // 
      this.addPointAtEndToolStripMenuItem.Name = "addPointAtEndToolStripMenuItem";
      this.addPointAtEndToolStripMenuItem.Size = new System.Drawing.Size(182, 22);
      this.addPointAtEndToolStripMenuItem.Text = "AddPoint at end";
      this.addPointAtEndToolStripMenuItem.Click += new System.EventHandler(this.addPointAtEndToolStripMenuItem_Click);
      // 
      // addPointToolStripMenuItem
      // 
      this.addPointToolStripMenuItem.Name = "addPointToolStripMenuItem";
      this.addPointToolStripMenuItem.Size = new System.Drawing.Size(182, 22);
      this.addPointToolStripMenuItem.Text = "AddPoint";
      this.addPointToolStripMenuItem.Click += new System.EventHandler(this.addPointToolStripMenuItem_Click);
      // 
      // removePointToolStripMenuItem
      // 
      this.removePointToolStripMenuItem.Name = "removePointToolStripMenuItem";
      this.removePointToolStripMenuItem.Size = new System.Drawing.Size(182, 22);
      this.removePointToolStripMenuItem.Text = "RemovePoint";
      this.removePointToolStripMenuItem.Click += new System.EventHandler(this.removePointToolStripMenuItem_Click);
      // 
      // toolStripSeparator1
      // 
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new System.Drawing.Size(179, 6);
      // 
      // showInfoToolStripMenuItem
      // 
      this.showInfoToolStripMenuItem.Name = "showInfoToolStripMenuItem";
      this.showInfoToolStripMenuItem.Size = new System.Drawing.Size(182, 22);
      this.showInfoToolStripMenuItem.Text = "Show Info";
      this.showInfoToolStripMenuItem.Click += new System.EventHandler(this.showInfoToolStripMenuItem_Click);
      // 
      // removePointAtEndToolStripMenuItem
      // 
      this.removePointAtEndToolStripMenuItem.Name = "removePointAtEndToolStripMenuItem";
      this.removePointAtEndToolStripMenuItem.Size = new System.Drawing.Size(182, 22);
      this.removePointAtEndToolStripMenuItem.Text = "RemovePoint at end";
      this.removePointAtEndToolStripMenuItem.Click += new System.EventHandler(this.removePointAtEndToolStripMenuItem_Click);
    }

    private System.Windows.Forms.ToolStripMenuItem addPointAtEndToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem addPointToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem removePointToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem removePointAtEndToolStripMenuItem;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
    private System.Windows.Forms.ToolStripMenuItem showInfoToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem pickPointToolStripMenuItem;

    #endregion
  }
}
