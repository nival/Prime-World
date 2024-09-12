using System;
using System.Collections.Generic;
using System.Windows.Forms;
using DBTypes;
using EditorNative.SceneElements;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Scene.Editors.Polygons;
using libdb.DB;

namespace EditorPlugins.Scene.Editors.Widgets
{
  [EditorControlWidget( typeof( ScriptPolygonArea ) )]
  public class PolygonWidget : EditorControlWidget
  {
    private MainElement mainElement = null;
    private GameSceneObject gameSceneObject = null;
    private ScriptPolygonArea polyArea = null;

    protected IList<Vec2> points;
    protected IList<IList<int>> polygons;

    private ToolStripButton tsbAddPoint = null;
    private ToolStripButton tsbDeletePoint = null;
    private ToolStripButton tsbCreatePoly = null;
    private ToolStripButton tsbSubdivideEdge = null;
    private ToolStripSeparator tssSpline = null;

    public PolygonWidget( EditorControl _control )
      : base( _control )
    {
    }

    public override bool IsSelected
    {
      get { return mainElement.IsSelected; }
    }
    private ToolStripButton InitBtn( System.Drawing.Bitmap bmp, string name, string tooltip,  EventHandler onClick )
    {
      ToolStripButton res = new ToolStripButton( bmp );
      res.Name = name;
      res.Enabled = false;
      res.Click += onClick;
      res.ToolTipText = tooltip;
      EditorControl.ToolStrip.Items.Add( res );
      return res;
    }
    public override void Create( GameSceneObject _target )
    {
      gameSceneObject = _target;
      polyArea = gameSceneObject.GetGameObject() as ScriptPolygonArea;

      EditorControl.ToolStrip.SuspendLayout();

      tssSpline = new ToolStripSeparator();
      EditorControl.ToolStrip.Items.Add( tssSpline );
      tsbAddPoint = InitBtn( EditorPluginResources.PolygonPointAdd, "AddPoint", "Add new point", OnAddPoint );
      tsbDeletePoint = InitBtn( EditorPluginResources.PolygonPointRemove, "DeletePoint", "Delete selected points and edges", OnDeletePoint );
      tsbCreatePoly = InitBtn( EditorPluginResources.PolygonPolyCreate, "CreatePoly", "Create polygon from selected points", OnCreatePoly );
      tsbSubdivideEdge = InitBtn( EditorPluginResources.PolygonEdgeSubdivide, "SubdivideEdge", "Break selected edge with new point", OnSubdivideEdge );

      EditorControl.ToolStrip.ResumeLayout( false );
      EditorControl.ToolStrip.PerformLayout();

      mainElement = new MainElement( EditorControl.SceneControl, polyArea, polyArea.points, polyArea.polygons );

      mainElement.UpdateToolbarItemsEvent += UpdateButtonsHandler;
      mainElement.AddToScene( EditorControl.SceneControl.Scene );
    }

    public override void Destroy()
    {
      EditorControl.ToolStrip.SuspendLayout();
      EditorControl.ToolStrip.Items.Remove( tssSpline );
      EditorControl.ToolStrip.Items.Remove( tsbAddPoint );
      EditorControl.ToolStrip.Items.Remove( tsbDeletePoint );
      EditorControl.ToolStrip.Items.Remove( tsbCreatePoly );
      EditorControl.ToolStrip.Items.Remove( tsbSubdivideEdge );
      EditorControl.ToolStrip.ResumeLayout( false );
      EditorControl.ToolStrip.PerformLayout();

      mainElement.RemoveFromScene();
    }

    public override void Update()
    {
    }

    public override bool HasThisWidget( GameSceneObject target ) { return true; }
    #region Event Handlers

    private void OnAddPoint( object sender, EventArgs e )
    {
      DataBase.UndoRedoManager.Start( (sender as ToolStripButton).ToolTipText );
      mainElement.AddPoint( gameSceneObject.Location.X, gameSceneObject.Location.Y );
      DataBase.UndoRedoManager.Commit();
    }

    private void OnDeletePoint( object sender, EventArgs e )
    {
      DataBase.UndoRedoManager.Start( ( sender as ToolStripButton ).ToolTipText );
      IList<SceneElement> selected = EditorControl.Scene.SelectedObjects;

      for ( int i = selected.Count - 1; i >= 0; --i )
      {
        SceneElement item = selected[i];
        PointElement element = item as PointElement;
        if ( element != null )
          mainElement.DeletePoint( element );
      }

      gameSceneObject.IsSelected = true;
      DataBase.UndoRedoManager.Commit();
    }

    private void OnCreatePoly( object sender, EventArgs e )
    {
      DataBase.UndoRedoManager.Start( ( sender as ToolStripButton ).ToolTipText );
      mainElement.CreatePolygon();
      DataBase.UndoRedoManager.Commit();
    }
    private void OnSubdivideEdge( object sender, EventArgs e )
    {
      DataBase.UndoRedoManager.Start( ( sender as ToolStripButton ).ToolTipText );
      mainElement.SubdivideEdge();
      DataBase.UndoRedoManager.Commit();
    }
    private void UpdateButtonsHandler( PermittedOperations ops )
    {
      tsbAddPoint.Enabled = ops.addPoint;
      tsbDeletePoint.Enabled = ops.deletePoint;
      tsbCreatePoly.Enabled = ops.createPolygon;
      tsbSubdivideEdge.Enabled = ops.subdivideEdge;
    }

    #endregion
  }

}
