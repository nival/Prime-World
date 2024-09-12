using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using EditorLib;
using EditorLib.Binds;
using EditorLib.PropertiesEditor;
using EditorNative;
using EditorNative.Manipulators;
using EditorNative.SceneElements;
using EditorNative.SceneElements.SceneObjects;
using EditorNative.Terrain;
using EditorPlugins.ObjectLayers;
using EditorPlugins.Scene.Editors.Drawing.TerrainHeightTool;
using EditorPlugins.Scene.Editors.Drawing.TerrainLayers;
using EditorPlugins.Scene.Editors.Splines;
using EditorPlugins.Scene.Editors.Terrain;
using EditorPlugins.Scene.Editors.Widgets;
using libdb.DB;
using libdb.Diagnostics;
using Pair = System.Collections.Generic.KeyValuePair<System.Windows.Forms.ToolStripButton, System.EventHandler>;
using EditorPlugins.Scene.Editors.Drawing;

namespace EditorPlugins.Scene.Editors
{
  public partial class EditorControl : UserControl, ISceneControlExtension, IObjectTransformControllersProvider
  {
    private const float MIN_SCALE = 0.7f;
    private const float MAX_SCALE = 1.3f;

    public event EventHandler ResetRotation;
    public event EventHandler ResetRotationByTerrain;
    public event EventHandler RandomRotation;
    public event EventHandler RandomScale;

    public TileMap TileMap { get; private set; }

    private bool isRandomScaleActive;
    public bool IsRandomScaleActive
    {
      get { return isRandomScaleActive; }
    }

    public bool IsCommonCenter
    {
      get { return btnManipulatorsMode.Checked; }
      private set
      {
        const string COMMON_CENTERS = "Common Selection Centers";
        const string EACH_CENTERS = "Each Selection Centers";

        btnManipulatorsMode.Checked = value;
        btnManipulatorsMode.Text = btnManipulatorsMode.ToolTipText = value ? COMMON_CENTERS : EACH_CENTERS;
      }
    }

    public bool IsGlobal
    {
      get { return btnGlobalLocal.Checked; }
      private set
      {
        btnGlobalLocal.Checked = value;
        btnGlobalLocal.Text = btnGlobalLocal.ToolTipText = value ? "Global" : "Local";
        Scene.IsGlobalManipulatorsMode = value;
      }
    }

    private float minRandomScale = MIN_SCALE;
    public float MinRandomScale
    {
      get { return minRandomScale; }
    }

    private float maxRandomScale = MAX_SCALE;
    public float MaxRandomScale
    {
      get { return maxRandomScale; }
    }

    private readonly IEditorWinApplication application;
    private IEditorControlExtension extension;
    private readonly SceneControl sceneControl;
    private readonly TerrainController terrainController;
    private readonly MainState mainState;
    private readonly EditorControlWidgetCollection widgetCollector = new EditorControlWidgetCollection();
    internal ToolStrip ToolStrip { get { return toolStrip; } }
    private readonly DrawTerrainLayerExtension drawTerrainLayerExtension;
    public enum TerrainType { NatureMap, Neutral, Gnome, Elf };

    #region Binds

    private Bind cameraMoveMode;
    private Bind rotate;
    private Bind pickLeft;
    private Bind pickRight;
    private Bind pickRightShift;
    private Bind pickMiddle;
    private Bind nonTileMoving;
    private Bind copy;
    private Bind cut;
    private Bind paste;
    private Bind delete;
    private Bind subtract;
    private Bind add;
    private Bind levelTcvs;
    private Bind hideSelection;
    private Bind switchTerrainElementsCanBeSelected;
    private Bind showMoving;
    private Bind showRotation;
    private Bind showScaling;
    private Bind resetManipulatorSize;
    private Bind increaseManipulator;
    private Bind decreaseManipulator;
    private Bind increaseManipulatorNumpad;
    private Bind decreaseManipulatorNumpad;
    private Bind cancel;
    private Bind cameraFocus;
    private Bind setDefaultCamera;
    private Bind storeDefaultCamera;
    private Bind resetAngles;
    private Bind resetAnglesByTerrain;
    private Bind cameraLookDown;
    private Bind cameraMoveForward;
    private Bind cameraMoveBackward;
    private Bind cameraMoveRight;
    private Bind cameraMoveLeft;
    private Bind randomRotate;
    private Bind randomScale;
    private Bind selectObjectsByType;
    private Bind selectObjectsByAsset;
    private Bind showHideTiles;
    private Bind globalLocalManipulatorsMode;
    private Bind showSymmetricLine; 
    private Bind setScriptGroupName;
    private Bind mirrorSelectedTCVs;

    #endregion

    public event EventHandler<EventArgs> TerrainUpdated;

    public EditorControl( IEditorWinApplication application, IEditorControlExtension extension, DBTypes.Terrain terrain )
    {
      this.application = application;
      this.extension = extension;

      sceneControl = new SceneControl( this, application.Application.Settings )
      {
        ConfigSection = extension.ConfigSection, Dock = DockStyle.Fill
      };

      application.MainMenu.UpdateMenu();

      mainState = new MainState( this );

      InitializeComponent();

      Controls.Add( sceneControl );
      sceneControl.Substate = mainState;

      terrainController = new TerrainController( terrain );

      sceneControl.Scene.SceneTerrain = terrainController.Terrain;

      drawTerrainLayerExtension = new DrawTerrainLayerExtension( terrain, terrainController.Terrain, sceneControl, application.Application.FileSystem );

      sceneControl.Scene.InitLightScene();

      InitToolbar();
    }

    private void OnLayersCountChanged()
    {
      drawTerrainLayerExtension.OnLayersChanged();
    }

    public EditorLib.Settings.SettingsManager Settings
    {
      get { return application.Application.Settings; }
    }

    private void DrawSymmetricLine( int mode )
    {
      if ( mode > 0 )
      {
        var sizeX = TerrainUtils.PatchSize*terrainController.Resource.elemXCount;
        var sizeY = TerrainUtils.PatchSize*terrainController.Resource.elemYCount;

        if ( mode == 1 )
        {
          EditorRender.DrawLine3D( new Vector3( sizeX/2, 0, 0 ), new Vector3( sizeX/2, sizeY, 0 ), Color.White, false );
          EditorRender.DrawLine3D( new Vector3( 0, sizeY/2, 0 ), new Vector3( sizeX, sizeY/2, 0 ), Color.White, false );
        }
        else
        {
          for ( int i = 0; i < 3; i++ )
          {
            EditorRender.DrawLine3D( new Vector3( sizeX / 2, 0, -5 + 5 * i ), new Vector3( sizeX / 2, sizeY, -5 + 5 * i ),
                                     Color.White, false );
            EditorRender.DrawLine3D( new Vector3( 0, sizeY / 2, -5 + 5 * i ), new Vector3( sizeX, sizeY / 2, -5 + 5 * i ),
                                     Color.White, false );
          }

        }
      }
    }

    public void Activate()
    {
      TerrainLayersEditorPanel.Controller = drawTerrainLayerExtension;
      ObjectLayersPanel.AttachEditorControl( this, extension.Resource.Get() );

      if ( TileMap == null )
        TileMap = new TileMap( sceneControl.Scene, extension.Resource.Get().cameraSettings );

      terrainController.LayersCountChanged += OnLayersCountChanged;

      Scene.SelectedObjectChanged += OnSelectedObjectChanged;
      Scene.SceneCamera.ParametersChanged += OnCameraParametersChanged;

      DataBase.StoreDBResourceEvent += OnStoreDBResource;
      DataBase.ChangeDBResourceEvent += OnChangeDBResource;

      //TODO refactor this
      TerrainHeightPanel.brushTypeButton.Click += OnBrushClick;
      TerrainHeightPanel.gizmoTypeButton.Click += OnGizmoClick;

      TerrainType t_type = (TerrainType)cboTerrainType.SelectedItem;
      btnNatureMapMode.Enabled = terrainController.Terrain.IsNatureMapEditable && t_type == TerrainType.NatureMap;
    }

    public void Deactivate()
    {
      TerrainLayersEditorPanel.Controller = null;
      ObjectLayersPanel.DetachScene();
      sceneControl.Substate = null;

      Scene.SelectedObjectChanged -= OnSelectedObjectChanged;
      Scene.SceneCamera.ParametersChanged -= OnCameraParametersChanged;

      DataBase.StoreDBResourceEvent -= OnStoreDBResource;
      DataBase.ChangeDBResourceEvent -= OnChangeDBResource;

      TerrainHeightPanel.brushTypeButton.Click -= OnBrushClick;
      TerrainHeightPanel.gizmoTypeButton.Click -= OnGizmoClick;

      terrainController.Unsubscribe();
      terrainController.LayersCountChanged -= OnLayersCountChanged;

      extension = null;
    }

    #region Binds registration

    void ISceneControlExtension.AddBinds()
    {
      cameraMoveMode = RegisterBind( "cameraMoveMode", Keys.Menu );
      rotate = RegisterBind( "rotate", Keys.Z );
      pickLeft = RegisterBind( "pickLeft", new BindConfig
      {
        mouseButtons = MouseButtons.Left,
        ignoreKeys = true,
        badKeys = new List<Keys> { Keys.Menu }
      } );

      pickRight = RegisterBind( "pickRight", new BindConfig
      {
        mouseButtons = MouseButtons.Right,
        badKeys = new List<Keys> { Keys.ShiftKey }
      } );

      pickRightShift = RegisterBind( "pickRightShift", new BindConfig
      {
        mouseButtons = MouseButtons.Right,
        keys = new List<Keys> { Keys.ShiftKey }
      } );

      add = RegisterBind( "add", Keys.ShiftKey );
      pickMiddle = RegisterBind( "pickMiddle", new BindConfig { mouseButtons = MouseButtons.Middle } );
      nonTileMoving = RegisterBind( "nonTileMoving1", Keys.X );
      copy = RegisterBind( "copy", Keys.C, Keys.ControlKey );
      cut = RegisterBind( "cut", Keys.X, Keys.ControlKey );
      paste = RegisterBind( "paste", Keys.V, Keys.ControlKey );
      delete = RegisterBind( "delete", Keys.Delete );
      subtract = RegisterBind( "subtract", Keys.ControlKey );
      levelTcvs = RegisterBind( "levelTcvs", Keys.T, Keys.ControlKey );
      hideSelection = RegisterBind( "hideSelection1", Keys.Tab );
      switchTerrainElementsCanBeSelected = RegisterBind( "switchTerrainElementsCanBeSelected", Keys.F1 );
      showMoving = RegisterBind( "showMoving", Keys.W );
      showRotation = RegisterBind( "showRotation", Keys.E );
      showScaling = RegisterBind( "showScaling", Keys.R );
      cancel = RegisterBind( "cancel1", Keys.Escape );
      cameraFocus = RegisterBind( "cameraFocus", Keys.F );
      setDefaultCamera = RegisterBind( "setDefaultCamera", Keys.Home );
      storeDefaultCamera = RegisterBind( "storeDefaultCamera", Keys.Home, Keys.ControlKey );

      // Сброс углов
      resetAngles = RegisterBind( "resetAngles", Keys.Menu, Keys.W );
      /// Сброс углов относительно террейна
      resetAnglesByTerrain = RegisterBind( "resetAnglesByTerrain", Keys.Menu, Keys.Q );
      /// Поставить камеру вертикально вниз
      cameraLookDown = RegisterBind( "cameraLookDown", Keys.ControlKey, Keys.D );
      cameraMoveForward = RegisterBind( "cameraMoveForward", Keys.Up );
      cameraMoveBackward = RegisterBind( "cameraMoveBackward", Keys.Down );
      cameraMoveRight = RegisterBind( "cameraMoveRight", Keys.Right );
      cameraMoveLeft = RegisterBind( "cameraMoveLeft", Keys.Left );
      randomRotate = RegisterBind( "randomRotate", Keys.Menu, Keys.A );
      randomScale = RegisterBind( "randomScale", Keys.Menu, Keys.S );
      selectObjectsByType = RegisterBind( "selectObjectsByType", Keys.ControlKey, Keys.J );
      selectObjectsByAsset = RegisterBind( "selectObjectsByAsset", new BindConfig { keys = new List<Keys> { Keys.J }, badKeys = new List<Keys> { Keys.ControlKey } } );

      showHideTiles = RegisterBind( "showHideTiles", new BindConfig { keys = new List<Keys> { Keys.T }, badKeys = new List<Keys> { Keys.ControlKey } } );
      showSymmetricLine = RegisterBind( "showSymmetricLine", new BindConfig { keys = new List<Keys> { Keys.G }, badKeys = new List<Keys> { Keys.ControlKey } } );
      setScriptGroupName = RegisterBind( "setScriptGroupName", new BindConfig { keys = new List<Keys> { Keys.G, Keys.ControlKey } } );

      resetManipulatorSize = RegisterBind( "resetManipulatorSize", Keys.ControlKey, Keys.D0 );
      //const Keys equalsKey = Keys.LButton | Keys.RButton | Keys.Back | Keys.ShiftKey | Keys.Space | Keys.F17;
      //resetManipulatorSize = RegisterBind( "resetManipulatorSize", new BindConfig { keys = new List<Keys> { equalsKey }, badKeys = new List<Keys> { Keys.ShiftKey } } );
      increaseManipulator = RegisterBind( "increaseManipulator", Keys.Oemplus );
      decreaseManipulator = RegisterBind( "decreaseManipulator", Keys.OemMinus );
      increaseManipulatorNumpad = RegisterBind( "increaseManipulatorNumpad", Keys.Add );
      decreaseManipulatorNumpad = RegisterBind( "decreaseManipulatorNumpad", Keys.Subtract );
      globalLocalManipulatorsMode = RegisterBind( "globalLocalManipulatorsMode", Keys.Menu, Keys.D );
      mirrorSelectedTCVs = RegisterBind( "mirrorSelectedTCVs", Keys.ControlKey, Keys.Menu, Keys.M );
    }

    private Bind RegisterBind( string _bindName, params Keys[] _keys )
    {
      BindConfig bindConfig = new BindConfig();
      bindConfig.keys = new List<Keys>( _keys );

      return BindsManager.RegisterBind( GetType().ToString(), _bindName, bindConfig );
    }

    private Bind RegisterBind( string _bindName, BindConfig _bindConfig )
    {
      return BindsManager.RegisterBind( GetType().ToString(), _bindName, _bindConfig );
    }

    protected override void OnLostFocus( EventArgs e )
    {
      base.OnLostFocus( e );
      BindsManager.ResetPressedKeys();
    }

    #endregion

    public void Relight()
    {
      DateTime start = DateTime.UtcNow;
      
      DateTime operationTime = DateTime.UtcNow;
      Scene.TryFullReload();
      Log.TraceMessage( "Scene.TryFullReload time: {0:0.####} s", ( DateTime.UtcNow - operationTime ).TotalSeconds );

      operationTime = DateTime.UtcNow;
      Scene.SceneTerrain.TryFullLoad();
      Log.TraceMessage( "Scene.SceneTerrain.TryFullLoad time: {0:0.####} s", ( DateTime.UtcNow - operationTime ).TotalSeconds );

      operationTime = DateTime.UtcNow;
      Scene.InitBakedLighting( extension.bakedLighting );
      Log.TraceMessage( "InitBakedLighting time: {0:0.####} s", ( DateTime.UtcNow - operationTime ).TotalSeconds );

      operationTime = DateTime.UtcNow;
      Scene.SetDayLightEnvironment(extension.DayLighting == null ? DBID.Empty : extension.DayLighting.DBId);
      Log.TraceMessage( "SetDayLightEnvironment time: {0:0.####} s", ( DateTime.UtcNow - operationTime ).TotalSeconds );

      operationTime = DateTime.UtcNow;
      Scene.SetNightLightEnvironment(extension.NightLighting == null ? DBID.Empty : extension.NightLighting.DBId);
      Log.TraceMessage("SetNightLightEnvironment time: {0:0.####} s", (DateTime.UtcNow - operationTime).TotalSeconds);

      operationTime = DateTime.UtcNow;
      Scene.CalculateLighting();
      Log.TraceMessage( "CalculateLighting time: {0:0.####} s", ( DateTime.UtcNow - operationTime ).TotalSeconds );

      operationTime = DateTime.UtcNow;
      DataBase.ChangeCallback( extension.Resource.DBId );
      Log.TraceMessage( "DataBase.ChangeCallback( extension.Resource.DBId ) time: {0:0.####} s", ( DateTime.UtcNow - operationTime ).TotalSeconds );

      operationTime = DateTime.UtcNow;
      DataBase.ChangeCallback( terrainController.Resource.DBId );
      Log.TraceMessage( "DataBase.ChangeCallback( terrainController.Resource.DBId ) time: {0:0.####} s", ( DateTime.UtcNow - operationTime ).TotalSeconds );

      operationTime = DateTime.UtcNow;
      RaiseTerrainUpdated();
      Log.TraceMessage( "RaiseTerrainUpdated time: {0:0.####} s", ( DateTime.UtcNow - operationTime ).TotalSeconds );

      operationTime = DateTime.UtcNow;
      ObjectLayersPanel.ApplyPresets();
      Log.TraceMessage( "ObjectLayersPanel.ApplyPresets time: {0:0.####} s", ( DateTime.UtcNow - operationTime ).TotalSeconds );

      Log.TraceMessage( "Summary Relight time: {0:0.####} s", ( DateTime.UtcNow - start ).TotalSeconds );
    }

    public void EnableEffects(bool enable)
    {
      Scene.TryFullReload();
      Scene.EnableEffectsInScene( enable );
      Relight();
    }

    public void ImmediateLightingUpdate()
    {
      if ( ImmediateLighting )
        Scene.SceneTerrain.TryFullLoad();
      Scene.SetImmediateLightingUpdate( ImmediateLighting );
      RaiseTerrainUpdated();
    }

    private void InitToolbar()
    {
      toolStrip.SuspendLayout();

      cboTerrainType.Items.AddRange( new object[]
      {
        TerrainType.NatureMap,
        TerrainType.Neutral,
        TerrainType.Gnome,
        TerrainType.Elf                                       
      } );
      cboTerrainType.SelectedIndex = 0;


      cboResolution.Items.AddRange( new object[]
      {
        CinemaMode.None,  
        CinemaMode.Mode4x3,
        CinemaMode.Mode5x4,
        CinemaMode.Mode16x9,
        CinemaMode.Mode16x10 
      } );
      cboResolution.SelectedIndex = 0;


      txtMinScale.ToolTipText = @"Min value : " + minRandomScale;
      txtMinScale.Text = minRandomScale.ToString();


      txtMaxScale.ToolTipText = @"Max value : " + maxRandomScale;
      txtMaxScale.Text = maxRandomScale.ToString();

      btnViewMode.Click += OnModeChaned;
      btnTerraFormingMode.Click += OnModeChaned;
      btnLayersMode.Click += OnModeChaned;
      btnNatureMapMode.Click += OnModeChaned;

      IsGlobal = true;
      IsCommonCenter = false;

      toolStrip.ResumeLayout();
      toolStrip.PerformLayout();
    }

    private void OnModeChaned( object sender, EventArgs e )
    {
      btnViewMode.Checked = false;
      btnTerraFormingMode.Checked = false;
      btnLayersMode.Checked = false;
      btnNatureMapMode.Checked = false;

      ToolStripButton currentButton = sender as ToolStripButton;
      if ( currentButton == null )
        return;

      currentButton.Checked = true;

      ObjectLayersPanel.ApplyPresets();
      ObjectLayersPanel.Enabled = false;

      if ( currentButton == btnViewMode )
      {
        ViewModeChecked();
        ObjectLayersPanel.ApplyPresets();
        ObjectLayersPanel.Enabled = true;
      }
      else if ( currentButton == btnTerraFormingMode )
        TerraFormingChecked();
      else if ( currentButton == btnLayersMode )
        LayersChecked();
      else if ( currentButton == btnNatureMapMode )
        NatureMapChecked();
    }

    private void ViewModeChecked()
    {
      TerrainHeightPanel.Enabled = false;
      TerrainLayersEditorPanel.Enabled = false;
      NatureMapPanel.Enabled = false;

      Scene.SceneTerrain.TryFullLoad();
      sceneControl.Substate = mainState;
      terrainController.MarkersVisible = false;
      terrainController.TerrainElementsSelectable = false;
      extension.ObjectsSelectable = true;
      RaiseTerrainUpdated();
    }

    private void TerraFormingChecked()
    {
      TerrainHeightPanel.Enabled = true;
      TerrainLayersEditorPanel.Enabled = false;
      NatureMapPanel.Enabled = false;

      Scene.SceneTerrain.TryFullLoad();

      if ( TerrainHeightPanel.brushTypeButton.Checked )
        ToBrushAffectType();
      if ( TerrainHeightPanel.gizmoTypeButton.Checked )
        ToGizmoAffectType();

      RaiseTerrainUpdated();
    }

    private void LayersChecked()
    {
      application.Panels.ShowSingletonPanel( TerrainLayersEditorPanel );
      TerrainHeightPanel.Enabled = false;
      TerrainLayersEditorPanel.Enabled = true;
      NatureMapPanel.Enabled = false;

      Scene.SceneTerrain.TryFullLoad();

      sceneControl.Substate = new DrawModeState( this, drawTerrainLayerExtension );
      terrainController.MarkersVisible = false;
      terrainController.TerrainElementsSelectable = false;
      extension.ObjectsSelectable = false;

      RaiseTerrainUpdated();
    }

    private void NatureMapChecked()
    {
      application.Panels.ShowSingletonPanel(NatureMapPanel);
      TerrainHeightPanel.Enabled = false;
      TerrainLayersEditorPanel.Enabled = false;
      NatureMapPanel.Enabled = true;

      Scene.SceneTerrain.TryFullLoad();
      Scene.TryFullReload();

      sceneControl.Substate = new NatureMapToolState(this);
      terrainController.MarkersVisible = false;
      terrainController.TerrainElementsSelectable = false;
      extension.ObjectsSelectable = false;

      RaiseTerrainUpdated();
    }

    private void ToBrushAffectType()
    {
      extension.ObjectsSelectable = false;
      terrainController.MarkersVisible = true;
      sceneControl.Substate = new TerrainHeightToolState( this );
      terrainController.TerrainElementsSelectable = false;
    }

    private void ToGizmoAffectType()
    {
      extension.ObjectsSelectable = false;
      terrainController.MarkersVisible = true;
      sceneControl.Substate = mainState;
      terrainController.TerrainElementsSelectable = true;
    }

    private void OnChangeDBResource( DBID dbid )
    {
      bool needRelight = false;

      if (Scene.IsImmediateLighting())
      {
        if (extension.DayLighting != null && extension.DayLighting.DBId == dbid)
          needRelight = true;

        if (extension.NightLighting != null && extension.NightLighting.DBId == dbid)
          needRelight = true;
      }

      if (needRelight)
        Relight();

      //sound update
      if ( DataBase.Get<DBTypes.DBSoundSceneComponent>( dbid ).IsValid )
      {
        Scene.ReloadSounds();
      }

      List<DBID> backlinks = new List<DBID>();
      backlinks.Add( dbid );
      DBID.ProcessBacklinkDelegate myDelegate = x => { backlinks.Add( x ); return true; };
      dbid.ProcessBacklinks( myDelegate );

      foreach ( DBID res in backlinks )
      {
        if ( res.FileName.ToLower().IndexOf( ".sobj" ) != -1 )
        {
          Scene.ReloadDBIDs( res.FileName );
        }
      }
    }

    private void OnSelectedObjectChanged( object sender, EventArgs e )
    {
      if ( selectionLocked )
        return;

      if ( Scene.SelectedObjects.Count == 1 )
      {
        var selected = Scene.SelectedObjects[0];

        if ( selected is SplineControlElement )
        {
          PropertiesEditorPanel.SelectedObject = ( selected as SplineControlElement ).ControlPoint;
        }
        else if ( selected is CameraSplineControlElement )
        {
          PropertiesEditorPanel.SelectedObject = ( selected as CameraSplineControlElement ).ControlPoint;
        }
        else if ( selected is SplineWidthElement )
        {
          PropertiesEditorPanel.SelectedObject = ( selected as SplineWidthElement ).ControlElement.ControlPoint;
        }
        else
        {
          extension.OnObjectSelected( selected );
        }
      }
      else
        extension.OnObjectSelected( null );
    }

    public void StoreMap()
    {
      OnStoreDBResource( terrainController.Resource.DBId );
    }

    private void OnStoreDBResource( DBID dbId )
    {
      if ( terrainController.Resource.DBId == dbId || extension.Resource.DBId == dbId )
      {
        DateTime start = DateTime.UtcNow;

        Scene.TryFullReload();
        Scene.SceneTerrain.TryFullLoad();
        Scene.InitBakedLighting( extension.bakedLighting );
        Scene.SetDayLightEnvironment(extension.DayLighting == null ? DBID.Empty : extension.DayLighting.DBId);
        Scene.SetNightLightEnvironment(extension.NightLighting == null ? DBID.Empty : extension.NightLighting.DBId);
        Scene.CalculateLighting();
        RaiseTerrainUpdated();
        DateTime dt = DateTime.UtcNow;
        Scene.SceneTerrain.StoreBinaryData( TerrainController.ElementsOrder );
        Log.TraceMessage( "SceneTerrain.StoreBinaryData: {0:0.####} s", ( DateTime.UtcNow - dt ).TotalSeconds );

        Scene.CalcObjectHeightMap();
        Scene.SaveObjectLayer( extension.Resource.Get().ObjectsLayerFileName );

        ObjectLayersPanel.ApplyPresets();

        Log.TraceMessage( "EditorControl.OnStoreDBResource: {0:0.####} s", ( DateTime.UtcNow - start ).TotalSeconds );
      }
    }

    private void OnCameraParametersChanged( object sender, EventArgs e )
    {
      if ( !ReferenceEquals( terrainController, null ) )
      {
        terrainController.UpdateTcvMarkers();
      }
    }

    private void OnBrushClick( object sender, EventArgs e )
    {
      ToBrushAffectType();
    }

    private void OnGizmoClick( object sender, EventArgs e )
    {
      ToGizmoAffectType();
    }


    private void RaiseTerrainUpdated()
    {
      EventHandler<EventArgs> temp = TerrainUpdated;
      if ( temp != null )
        temp( this, EventArgs.Empty );

    }

    public bool ImmediateLighting
    {
      get { return btnImmediateLighting.Checked; }
      set { btnImmediateLighting.Checked = value; }
    }

    public bool Night
    {
      get { return btnNightLighting.Checked; }
      set { btnNightLighting.Checked = value; }
    }

    public bool LockObjectMode
    {
      get { return btnLockObjects.Checked; }
      set
      {
        btnLockObjects.Checked = value;
        OnLockObjectsClick( btnLockObjects, null );
      }
    }

    public bool SplineSelectionMode
    {
      get { return btnSplineSelection.Checked; }
      set
      {
        btnSplineSelection.Checked = value;
        OnSplineSelectionClick( btnSplineSelection, null );
      }
    }

    public SceneControl SceneControl
    {
      get { return sceneControl; }
    }

    public EditorScene Scene
    {
      get { return SceneControl.Scene; }
    }

    public TerrainController TerrainController
    {
      get { return terrainController; }
    }

    public BindsManager BindsManager
    {
      get { return application.BindsManager; }
    }

    public string StatusLabel
    {
      set
      {
        application.StatusLabel = value;
      }
    }

    private bool snapObjectsToTerrain = false;
    public bool SnapObjectsToTerrain
    {
      get
      {
        return snapObjectsToTerrain;
      }
    }

    private bool randomZRotationEnabled;
    public bool RandomZRotationEnabled
    {
      get { return randomZRotationEnabled; }
    }

    [Browsable( false )]
    public bool IsShowTileSet { get; set; }

    [Browsable( false )]
    public int ShowSymmetricLineMode { get; set; }

    private void NextSymmetricLineMode()
    {
      ShowSymmetricLineMode++;
      if ( ShowSymmetricLineMode > 2 )
        ShowSymmetricLineMode = 0;
    }

    public virtual void SetScriptGroupName()
    {
    }

    public bool InlineSpawners { get; private set; }

    public void BeginEntityAddition( AddEntityController controller )
    {
      sceneControl.Substate = new ObjectAdditionState( this, controller );
      sceneControl.Focus();
      Scene.CurrentManipulator = ManipulatorTypes.None;
    }

    IObjectTransformControllersProvider ISceneControlExtension.TransformControllersProvider
    {
      get { return this; }
    }

    IObjectTransformController IObjectTransformControllersProvider.GetObjectTransformController( SceneElement obj )
    {
      return obj as IObjectTransformController;
    }

    private NatureMapPanel NatureMapPanel
    {
      get { return application.Panels.GetSingletonPanel<NatureMapPanel>(); }
    }

    private TerrainHeightPanel TerrainHeightPanel
    {
      get { return application.Panels.GetSingletonPanel<TerrainHeightPanel>(); }
    }

    private TerrainLayersEditorPanel TerrainLayersEditorPanel
    {
      get { return application.Panels.GetSingletonPanel<TerrainLayersEditorPanel>(); }
    }

    private PropertiesEditorPanel PropertiesEditorPanel
    {
      get { return application.Panels.GetSingletonPanel<PropertiesEditorPanel>(); }
    }

    private ObjectLayersPanel ObjectLayersPanel
    {
      get { return application.Panels.GetSingletonPanel<ObjectLayersPanel>(); }
    }

    internal void OnAfterSelectionChanged()
    {
      Scene.CurrentManipulator = ManipulatorTypes.None;

      IList<SceneElement> selected = Scene.SelectedObjects;
      if ( selected == null || selected.Count == 0 )
        return;

      if ( selected.Count == 1 )
      {
        GameSceneObject gso = selected[0] as GameSceneObject;
        if ( gso == null )
          return;
        if ( widgetCollector.HasWidgets( gso ) )
        {
          if ( WidgetState.CallBackWidjet != null )
            SceneControl.Substate = WidgetState.CallBackWidjet;
          else
            SceneControl.Substate = new WidgetState( this, gso, widgetCollector.CreateWidgets( this, gso ) );
        }
      }
    }

    public void SelectObjectAtCursor()
    {
      PickResult pickResult = SceneControl.Pick();
      SceneElement pickedElement = pickResult.PickedElements.Length == 0 ? null : pickResult.PickedElements[0];
      SelectObject( pickedElement );

      OnAfterSelectionChanged();
    }

    public void SelectObjectByRect( float left, float top, float right, float bottom )
    {
      EditorScene.ElementsFilter filter = element =>
      {
        if ( element is TerrainElement )
          return terrainController.TerrainElementsCanBeSelected;
        else if ( element is TcvMarker )
          return !terrainController.TerrainElementsCanBeSelected;
        else
          return true;
      };

      if ( !add.IsActive && !subtract.IsActive )
        Scene.DeselectAll();
      Scene.SelectByFrame( left, top, right, bottom, filter, add.IsActive, subtract.IsActive );

      OnAfterSelectionChanged();
    }

    public void SelectObject( SceneElement pickedElement )
    {
      RestoreLockedSelection();
      ReleaseSelection();

      if ( SplineSelectionMode && !IsSpline( pickedElement as GameSceneObject ) )
      {
        return;
      }

      ProcessSelection( pickedElement );
    }

    private bool IsSpline( GameSceneObject pickedElement )
    {
      List<Type> widgets = widgetCollector.GetWidgets( pickedElement );

      foreach ( Type widgetType in widgets )
      {
        if ( TypeUtils.IsSubclassOf( widgetType, typeof( SplineWidgetBase<> ) ) || TypeUtils.IsSubclassOf( widgetType, typeof( CameraSplineWidgetBase<> ) ) )
          return true;
      }

      return false;
    }

    public void PreselectObject( SceneElement pickedElement )
    {
      RestoreLockedSelection();

      ProcessSelection( pickedElement );
    }

    private void ProcessSelection( SceneElement pickedElement )
    {
      if ( pickedElement == null )
      {
        if ( !add.IsActive && !subtract.IsActive )
          Scene.DeselectAll();
      }
      else
      {
        if ( add.IsActive )
        {
          if ( pickedElement.IsSelected )
            Scene.Deselect( pickedElement );
          else
            Scene.Select( pickedElement );
        }
        else if ( subtract.IsActive )
          Scene.Deselect( pickedElement );
        else if ( !pickedElement.IsSelected )
        {
          Scene.DeselectAll();
          Scene.Select( pickedElement );
        }
      }
    }

    #region Preselection management

    private bool selectionLocked = false;
    private readonly List<SceneElement> rememberedSelection = new List<SceneElement>();

    public void LockSelection()
    {
      selectionLocked = true;
      rememberedSelection.Clear();
      rememberedSelection.AddRange( Scene.SelectedObjects );
    }

    public void ReleaseSelection()
    {
      rememberedSelection.Clear();
      selectionLocked = false;
    }

    public void RestoreLockedSelection()
    {
      if ( !selectionLocked )
        return;

      Scene.DeselectAll();
      foreach ( SceneElement item in rememberedSelection )
        Scene.Select( item );
    }

    #endregion

    #region Toolbar Event Handlers

    private void OnRelightClick( object sender, EventArgs e )
    {
      Relight();
    }

    private void OnImmediateLightingCheckedChanged( object sender, EventArgs e )
    {
      ImmediateLightingUpdate();
    }

    private void OnTerrainTypeChanged( object sender, EventArgs e )
    {
      Scene.TryFullReload( false );
      ToolStripComboBox comboBox = sender as ToolStripComboBox;
      TerrainType t_type = (TerrainType)comboBox.SelectedItem;

      if ( t_type != TerrainType.NatureMap && btnNatureMapMode.Checked )
        OnModeChaned( btnViewMode, new EventArgs() );
      btnNatureMapMode.Enabled = terrainController.Terrain.IsNatureMapEditable && t_type == TerrainType.NatureMap;

      TerrainController.Terrain.SetNatureMap( (int)t_type );
      SceneControl.Scene.UpdateAllMSO();
      Scene.EnableEffectsInScene( Scene.IsEnabledEffectsInScene );
      RaiseTerrainUpdated();
    }

    private void OnResolutionSelected( object sender, EventArgs e )
    {
      ToolStripComboBox comboBox = sender as ToolStripComboBox;

      if ( comboBox == null )
        return;

      CinemaMode mode = (CinemaMode)comboBox.SelectedItem;
      SceneControl.Scene.ScreenMode = mode;
      //None
      if ( mode == CinemaMode.None )
      {
        SceneControl.SetLimitCamera( false );
      }
      else
      {
        EditorConfigObject config = application.Application.Settings.Get<EditorConfigObject>();
        if ( config != null )
        {
          SceneControl.Scene.SceneCamera.Pitch = config.DefaultPitch;
          SceneControl.Scene.SceneCamera.Rod = config.DefaultRod;
          SceneControl.Scene.SceneCamera.Roll = config.DefaultRoll;
          SceneControl.Scene.SceneCamera.Yaw = config.DefaultYaw;
          SceneControl.Scene.UpdateCamera( 0.0f, 0.0f, 0.0f, new Vector2( 0.0f, 0.0f ), new Vector2( 0.0f, 0.0f ) );
        }

        SceneControl.SetLimitCamera( true );
      }
    }

    private void OnLockObjectsClick( object sender, EventArgs e )
    {
      application.Application.Settings.Get<AdvMapEditorConfig>().lockObjectsMode = LockObjectMode;
    }

    private void OnSplineSelectionClick( object sender, EventArgs e )
    {
      application.Application.Settings.Get<AdvMapEditorConfig>().splineSelectionMode = SplineSelectionMode;
    }

    private void OnSnapToTerrainCheckedChanged( object sender, EventArgs e )
    {
      snapObjectsToTerrain = btnSnapToTerrain.Checked;
    }

    private void OnRotateZCheckedChanged( object sender, EventArgs e )
    {
      randomZRotationEnabled = btnRandomRotateZ.Checked;
    }

    private void OnRandomScaleCheckedChanged( object sender, EventArgs e )
    {
      isRandomScaleActive = btnRandomScale.Checked;
      txtMinScale.Enabled = isRandomScaleActive;
      txtMaxScale.Enabled = isRandomScaleActive;
    }

    private void OnMinScaleLeave( object sender, EventArgs e )
    {
      if ( !float.TryParse( txtMinScale.Text, out minRandomScale ) )
      {
        txtMinScale.Text = MIN_SCALE.ToString();
      }

      minRandomScale = ( minRandomScale >= MIN_SCALE ? minRandomScale : MIN_SCALE );
      minRandomScale = ( minRandomScale <= MAX_SCALE ? minRandomScale : MAX_SCALE );
      minRandomScale = ( minRandomScale < maxRandomScale ? minRandomScale : MIN_SCALE );
      txtMinScale.Text = minRandomScale.ToString();
    }

    private void OnMaxScaleLeave( object sender, EventArgs e )
    {
      if ( !float.TryParse( txtMaxScale.Text, out maxRandomScale ) )
      {
        txtMaxScale.Text = MAX_SCALE.ToString();
      }

      maxRandomScale = ( maxRandomScale >= MIN_SCALE ? maxRandomScale : MIN_SCALE );
      maxRandomScale = ( maxRandomScale <= MAX_SCALE ? maxRandomScale : MAX_SCALE );
      maxRandomScale = ( maxRandomScale > minRandomScale ? maxRandomScale : MAX_SCALE );
      txtMaxScale.Text = maxRandomScale.ToString();
    }

    private void OnAlignTcvClick( object sender, EventArgs e )
    {
      foreach ( TcvMarker marker in Scene.SceneTerrain.TcvMarkers )
      {
        marker.Location = new Vector3(
          (float)Math.Round( marker.Location.X / 10 ) * 10,
          (float)Math.Round( marker.Location.Y / 10 ) * 10,
          marker.Location.Z );
      }
    }

    private void OnWeldClick( object sender, EventArgs e )
    {
      Scene.SceneTerrain.TryFullLoad();
      Scene.SceneTerrain.WeldVertices();
      Scene.SceneTerrain.Changed = true;
      DataBase.ChangeCallback( terrainController.Resource.DBId );
      RaiseTerrainUpdated();
    }

    private void OnFullLoadClick( object sender, EventArgs e )
    {
      Scene.TryFullReload();
      RaiseTerrainUpdated();
    }

    private void OnInlineSpawnersCheckedChanged( object sender, EventArgs e )
    {
      InlineSpawners = btnInlineSpawners.Checked;
    }

    private void OnLocalGlobalClick( object sender, EventArgs e )
    {
      IsGlobal = !IsGlobal;
    }

    private void OnManipulatorsModeClick( object sender, EventArgs e )
    {
      IsCommonCenter = !IsCommonCenter;
    }

    private void OnNightLightingCheckedChanged(object sender, EventArgs e)
    {
      if (Night)
      {
        if (extension.DayLighting == null)
          return;
        if (extension.NightLighting == null)
          return;
      }

      Scene.NightLighting = Night;
    }

    #endregion
  }
}