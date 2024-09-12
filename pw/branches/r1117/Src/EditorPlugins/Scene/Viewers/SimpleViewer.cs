using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Binds;
using EditorLib.Extensions;
using EditorPlugins.Forms;
using EditorLib.ObjectsBrowser;
using EditorLib.PropertiesEditor;
using EditorNative;
using EditorNative.Manipulators;
using EditorNative.SceneElements.SceneObjects;
using EditorPlugins.Editors.AnimGraph;
using EditorPlugins.Scene.Editors;
using EditorPlugins.Scene.Presets;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Scene.Viewers
{
	[System.Runtime.InteropServices.GuidAttribute( "9F518561-54FD-4BFC-981E-94FC18CE585D" )]
	public abstract partial class SimpleViewer<TResource> : Editor<TResource>, 
                                                          ISceneControlExtension,
	                                                        IAnimationSelectionPanelExtension,
	                                                        ISkinsSelectionPanelExtension,
																													ISceneHierarchyPanelExtension
    where TResource : DBResource, new()
	{
		#region Private members.

		private string activeLocator = string.Empty;
		private DBID activeSceneComponentDBID;

		private AGController agc1;
		private AGController agc2;
		private IEditorWinApplication application;

		private ToolStripButton collisionButton;
	  private ToolStripButton locatorsButton;

		protected bool isActive;
		protected EditorSceneObject mainSceneObject;
		private ManipulatorControl manipulator;
		private ToolStripComboBox presetsComboBox;
		protected DBPtr<TResource> resource;

		private Bind restart;
		private SimpleSceneControl sceneControl;
		private SceneInfo sceneInfo = new SceneInfo();
		private Bind showGrid;
		private TimeSlider timeControl;
		private Bind toggleRotate;
		private Bind toggleScale;
		private Bind toggleTranslate;
		private ToolStrip toolStrip;
        private Quat quat;

		#endregion

		#region Initialization.

		protected override sealed bool Initialize(DBPtr<TResource> _resource, IEditorWinApplication _application)
		{
			activeSceneComponentDBID = DBID.Empty;
			resource = _resource;
			application = _application;

			SuspendLayout();
			try
			{
				TabText = GetTabText( _resource );

				sceneControl = new SimpleSceneControl( this,
				                                       PropertiesEditor,
				                                       Application.Application.Settings, sceneInfo.GetType() )
				               	{ConfigSection = ConfigSection};

				sceneControl.Initialize( _application.Application );
				sceneControl.Substate = new MainState( this );

				InitPresetsAndControls();

				sceneInfo.Init( sceneControl.Scene );
				sceneInfo.Preset.Init( sceneControl.Scene );
				sceneInfo.Preset.SetControllers( agc1, agc2 );
				mainSceneObject = CreateSceneObject( resource );
				sceneInfo.Preset.SetMainObject( resource.DBId, mainSceneObject );
				sceneInfo.Preset.Rebuild();
				mainSceneObject = sceneInfo.Preset.GetMainObject();
				SceneControl.Scene.CalcFrameNumbers( mainSceneObject );
				Controls.Add( sceneControl );
				Controls.Add( timeControl );

				sceneControl.timer.Tick += OnSceneTimeTick;

				manipulator = new ManipulatorControl( SceneHierarchy.SelectedComponent, sceneControl, Application, timeControl );
        timeControl.Paused = false;
				sceneControl.ShowGrid = true;

				AnimGraph.UpdateSceneNeeded += OnUpdateSceneNeeded;
			}
			catch (Exception e)
			{
				if ( mainSceneObject != null )
				{
					mainSceneObject = null;
				}
				Log.TraceError( e.Message );
				Log.TraceError( "Native scene creation failed." );

				return false;
			}
			ResumeLayout( true );

			return true;
		}

    private void OnUpdateSceneNeeded(object _sender, EventArgs _e)
		{
			if ( sceneInfo.Preset != null )
			{
				ResetAGPanel();
				ApplyLastTrack();

				if(timeControl.Paused)
					RestoreLastFrame();
				else
					sceneControl.Scene.SetCurrentFrame(mainSceneObject, 0);
			}
		}

		private void OnSceneTimeTick( object sender, EventArgs e )
		{
			if ( mainSceneObject == null || sceneControl == null || timeControl.SliderCapture )
				return;

			int frames = sceneControl.Scene.GetFrameNumbers( mainSceneObject );
			timeControl.FrameNumbers = frames;

			int currentFrame = sceneControl.Scene.GetCurrentFrame( mainSceneObject );
			timeControl.CurrentFrame = currentFrame;
		}

	  private string lastTrack = string.Empty;

    public void ApplyTrack( string track )
    {
      if ( sceneInfo != null && sceneInfo.Preset != null )
      {
        EditorSceneObject mso = sceneInfo.Preset.GetMainObject();
        mso.ApplyTrack( track );
        lastTrack = track;
      }
    }

    public void ApplyLastTrack( )
    {
      ApplyTrack( lastTrack );
    }

		private void prst_ScenePresetUpdated(ScenePreset _preset)
		{
      EditorSceneObject mso = _preset.GetMainObject();
			_preset.Release();
      _preset.SetMainObject( resource.DBId, mso );
			_preset.Rebuild();
			SceneHierarchy.Rebuild();
		}

		private void TogglePresetOptions()
		{
			PropertiesEditor.SelectedObject = null;
			PropertiesEditor.SelectedObject = sceneInfo;
		}

		private void InitPresetsAndControls()
		{
			ScenePresets scenePresetsTypes = application.Application.Extensions.GetTypesCollector<ScenePresets>();
			List<ScenePreset> presets = scenePresetsTypes.GetPresets( resource.DBId, application.Application.Settings );

			toolStrip = new ToolStrip();
			toolStrip.SuspendLayout();

			collisionButton = new ToolStripButton( EditorPluginResources.Collision ) {CheckOnClick = true, Checked = false};
			collisionButton.ToolTipText = "Collision";
			collisionButton.Click += (_1, _2) => mainSceneObject.CollisionGeometryVisible = collisionButton.Checked;
			toolStrip.Items.Add( collisionButton );

			locatorsButton = new ToolStripButton( EditorPluginResources.Locator ) {CheckOnClick = false, Checked = false};
			locatorsButton.ToolTipText = "Locators";
		  locatorsButton.Click += delegate
		  {
		    EditorRender.ToggleShowLocators();
        locatorsButton.Checked = !locatorsButton.Checked;
		  };

			toolStrip.Items.Add( locatorsButton );

			presetsComboBox = new ToolStripComboBox();
			presetsComboBox.Size = new Size( 150, 25 );
		  presetsComboBox.MaxDropDownItems = 100;      
      presetsComboBox.IntegralHeight = true;

			if ( presets.Count == 0 )
			{
				Log.TraceError( "Compatible preset not found!" );
				return;
			}

			int selectedIndex = 0;
			foreach (var prst in presets)
			{
				prst.ScenePresetUpdated += prst_ScenePresetUpdated;
				presetsComboBox.Items.Add( prst );
				PresetSaver.PresetInfo info = Application.Application.Settings.Get<PresetSaver>().Get( resource );
				if ( info != null && prst.GetName() == info.name && prst.GetType().Name == info.typeName )
					selectedIndex = presetsComboBox.Items.Count - 1;
			}
			presetsComboBox.SelectedIndex = selectedIndex;
			sceneInfo.Preset = presetsComboBox.SelectedItem as ScenePreset;

			presetsComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
			presetsComboBox.FlatStyle = FlatStyle.Flat;
			presetsComboBox.SelectedIndexChanged += OnPresetSelected;
			toolStrip.Items.Add( presetsComboBox );

			ToolStripButton button03 = new ToolStripButton( EditorPluginResources.Options )
			                           	{CheckOnClick = false, Checked = false};
			button03.ToolTipText = "Options";
			button03.Click += (_1, _2) => TogglePresetOptions();
			toolStrip.Items.Add( button03 );

			ToolStripButton button04 = new ToolStripButton( EditorPluginResources.Copy ) {CheckOnClick = false, Checked = false};
			button04.ToolTipText = "Copy";
			button04.Click += (_1, _2) => ToggleCopyPreset();
			toolStrip.Items.Add( button04 );
			ToolStripButton button05 = new ToolStripButton( EditorPluginResources.Delete )
			                           	{CheckOnClick = false, Checked = false};
			button05.ToolTipText = "Delete";
			button05.Click += (_1, _2) => ToggleDeletePreset();
			toolStrip.Items.Add( button05 );

			ToolStripComboBox resolutionComboBox = new ToolStripComboBox();
			resolutionComboBox.Size = new Size( 80, 25 );
			resolutionComboBox.Items.Add( CinemaMode.None );
			resolutionComboBox.SelectedIndex = resolutionComboBox.Items.Count - 1;
			SceneControl.SetLimitCamera( false );
			resolutionComboBox.Items.Add( CinemaMode.Mode4x3 );
			resolutionComboBox.Items.Add( CinemaMode.Mode5x4 );
			resolutionComboBox.Items.Add( CinemaMode.Mode16x9 );
			resolutionComboBox.Items.Add( CinemaMode.Mode16x10 );
			resolutionComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
			resolutionComboBox.FlatStyle = FlatStyle.Flat;
			resolutionComboBox.SelectedIndexChanged += OnResolutionSelected;
			toolStrip.Items.Add( resolutionComboBox );
			

			//Для MSO объектов отображаем выпадающий список типа террейна
			if(resource.Get() is MultiStateObject)
			{
				ToolStripComboBox terrainTypeComboBox = new ToolStripComboBox();
				terrainTypeComboBox.Size = new Size( 90, 25 );
				terrainTypeComboBox.Items.Add( EditorControl.TerrainType.Neutral );
				terrainTypeComboBox.SelectedIndex = terrainTypeComboBox.Items.Count - 1;
				terrainTypeComboBox.Items.Add( EditorControl.TerrainType.Gnome );
				terrainTypeComboBox.Items.Add( EditorControl.TerrainType.Elf );
				terrainTypeComboBox.DropDownStyle = ComboBoxStyle.DropDownList;
				terrainTypeComboBox.FlatStyle = FlatStyle.Flat;
				terrainTypeComboBox.SelectedIndexChanged += OnTerrainTypeChange;
				toolStrip.Items.Add( terrainTypeComboBox );				
			}


      //инициализируем timeControl
      InitTimeControl();

			if ( ConfigSection == "GMOB" )
			{
				ToolStripButton button06 = new ToolStripButton( EditorPluginResources.TileSet )
				                           	{CheckOnClick = true, Checked = false};
				button06.ToolTipText = "TileSet";
				button06.Click += (_1, _2) => ToggleEditTileSet();
				toolStrip.Items.Add( button06 );
			}

			toolStrip.ResumeLayout( false );
			toolStrip.PerformLayout();

			Controls.Add( toolStrip );

      sceneControl.PresetTick = sceneInfo.Preset.OnTimerTick;
		}

    private void InitTimeControl()
    {
      timeControl = new TimeSlider
      {
        Dock = DockStyle.Bottom
      };

    	timeControl.MeasureInFrames = AnimGraph.MeasureInFrames;

      timeControl.SliderScroll += delegate
      {
        sceneControl.Scene.SetCurrentFrame(mainSceneObject, timeControl.CurrentFrame);
      };

      timeControl.SliderValueChanged += delegate
      {
        if (timeControl.Paused)
        {
          sceneControl.Scene.SetCurrentFrame(mainSceneObject, timeControl.CurrentFrame);
        }
      };

      timeControl.PausedChanged += delegate
      {
      	if ( sceneControl != null )
					sceneControl.SetTimeControl( timeControl.AnimationSpeed );

				if ( timeControl.Paused )
      		RestoreLastFrame();
      };

      timeControl.AnimationSpeedChanged += delegate
      {
        if (!timeControl.Paused)
        {
          sceneControl.SetTimeControl(timeControl.AnimationSpeed);
        }
      };

      timeControl.KeyDown += (obj, args) =>
      {
        sceneControl.Focus();
        BindsManager.OnKeyDown(args);
      };

      timeControl.SliderCaptureChanged += delegate
      {
        if (!timeControl.Paused)
        {
          sceneControl.SetTimeControl(timeControl.SliderCapture ? PlaySpeed.Pause : timeControl.AnimationSpeed);
        }
      };

      timeControl.MeasureChanged += delegate
      {
        if (Application != null) 
					AnimGraph.MeasureInFrames = timeControl.MeasureInFrames;
      };
    }

		protected virtual void ToggleEditTileSet()
		{
		}

		private void ToggleDeletePreset()
		{
			PresetDeleteForm deleteForm = new PresetDeleteForm( sceneInfo.Preset.GetName(), true );
			DialogResult result = deleteForm.ShowDialog();
			if ( result == DialogResult.OK )
			{
				bool isDelete = sceneInfo.Preset.Delete( Application.Application.Settings );
				if ( isDelete )
				{
					presetsComboBox.Items.Remove( sceneInfo.Preset );
					presetsComboBox.SelectedIndex = presetsComboBox.Items.Count - 1;
				}
			}
		}

		private void ToggleCopyPreset()
		{
			PresetCopyForm copyForm = new PresetCopyForm();
			DialogResult result = copyForm.ShowDialog();
			if ( result == DialogResult.OK && copyForm.textString != string.Empty )
			{
				ScenePreset preset = sceneInfo.Preset.Copy( Application.Application.Settings, copyForm.textString, false );
				if ( preset == null )
				{
					PresetDeleteForm rewriteForm = new PresetDeleteForm( copyForm.textString, false );
					DialogResult rewrite = rewriteForm.ShowDialog();

					if ( rewrite == DialogResult.OK )
					{
						ScenePreset todel = null;
						foreach (ScenePreset prst in presetsComboBox.Items)
						{
							if ( prst.GetName() == copyForm.textString )
							{
								todel = prst;
								break;
							}
						}
						presetsComboBox.Items.Remove( todel );
						preset = sceneInfo.Preset.Copy( Application.Application.Settings, copyForm.textString, true );
					}
					else
					{
						return;
					}
				}

				presetsComboBox.Items.Add( preset );
				preset.ScenePresetUpdated += prst_ScenePresetUpdated;
				presetsComboBox.SelectedIndex = presetsComboBox.Items.Count - 1;
			}
		}

		private void OnResolutionSelected(object sender, EventArgs e)
		{
			ToolStripComboBox comboBox = sender as ToolStripComboBox;
			
			if(comboBox == null)
				return;

			EditorNative.CinemaMode mode = (EditorNative.CinemaMode)comboBox.SelectedItem;

			SceneControl.Scene.SetCinemaMode( (int)mode );
			//None
			if ( mode == EditorNative.CinemaMode.None )
			{
				SceneControl.SetLimitCamera( false );
			}
			else
			{
				SceneControl.SetLimitCamera( true );
			}
		}

    private bool SelectObjectFromMSO( EditorControl.TerrainType terrainType )
    {
      int soIndex = 0;

      switch( terrainType )
      {
      case EditorControl.TerrainType.Neutral:
        soIndex = 0;
        break;
      case EditorControl.TerrainType.Gnome:
        soIndex = 1;
        break;
      case EditorControl.TerrainType.Elf:
        soIndex = 2;
        break;
      default:
        return false;
      }

      if ( resource.Get() is DBTypes.MultiStateObject )
      {
        SceneControl.Scene.Remove( mainSceneObject );
        mainSceneObject = new EditorSceneObject( ( resource.Get() as DBTypes.MultiStateObject ).sceneObjects[soIndex].DBId );
        sceneInfo.Preset.SetMainObject( resource.DBId, mainSceneObject );
        return true;
      }
      return false;
    }

		private void OnTerrainTypeChange( object sender, EventArgs e )
		{
      ToolStripComboBox comboBox = sender as ToolStripComboBox;
      if ( comboBox != null )
      {
        EditorControl.TerrainType terrainType = (EditorControl.TerrainType)comboBox.SelectedItem;
        if ( SelectObjectFromMSO( terrainType ) )
        {
          RefreshScene();
        }
      }
		}

    private void OnPresetSelected( object sender, EventArgs e )
    {
      ToolStripComboBox comboBox = sender as ToolStripComboBox;
      EditorSceneObject mso = sceneInfo.Preset.GetMainObject();
      sceneInfo.Preset.Release();
      sceneInfo.Preset = comboBox.SelectedItem as ScenePreset;
      sceneControl.PresetTick = sceneInfo.Preset.OnTimerTick;
      sceneInfo.Preset.Init( sceneControl.Scene );
      sceneInfo.Preset.SetControllers( agc1, agc2 );
      sceneInfo.Preset.SetMainObject( resource.DBId, mso );
      sceneInfo.Preset.Rebuild();
      PropertiesEditor.SelectedObject = null;
      PropertiesEditor.SelectedObject = sceneInfo;
      SceneHierarchy.Rebuild();
      mainSceneObject.CollisionGeometryVisible = collisionButton.Checked;
      RefreshScene();
    }

		#endregion

		#region Overrides.

		protected override void OnActivateEditor()
		{
			if ( sceneControl == null ) return;

      DataBase.ChangeDBResourceEvent += OnDbResourceChanged;

      sceneControl.StartTimer();
			isActive = true;
			
      if ( sceneInfo != null && sceneInfo.Preset != null )
			{
				sceneInfo.Preset.Rebuild();
			}
			else
			{
				sceneInfo.Preset = presetsComboBox.SelectedItem as ScenePreset;
				sceneInfo.Preset.Init( sceneControl.Scene );
				sceneInfo.Preset.SetControllers( agc1, agc2 );
				sceneInfo.Preset.SetMainObject( resource.DBId, mainSceneObject );
				sceneInfo.Preset.Rebuild();
			}

			mainSceneObject = sceneInfo.Preset.GetMainObject();
			SceneControl.Scene.CalcFrameNumbers( mainSceneObject );
			EditorRender.SetFFTT( true );
			base.OnActivateEditor();
			SceneHierarchy.SetController( this );
			SceneHierarchy.SelectFirstNode( mainSceneObject );
			AnimationsSelectionPanel.Controller = this;
			SkinsSelectionPanel.Controller = this;
			SkinsSelectionPanel.SelectStartSkins( 1 );

			PropertiesEditor.SelectedObject = resource.Get();
			mainSceneObject.CollisionGeometryVisible = collisionButton.Checked;
		}

		protected override void OnDeactivateEditor()
		{
      DataBase.ChangeDBResourceEvent -= OnDbResourceChanged;

      if(locatorsButton.Checked)
      {
        locatorsButton.Checked = false;
        EditorRender.ToggleShowLocators();
      }
      
			if ( sceneInfo != null && sceneInfo.Preset != null )
			{
				sceneInfo.Preset.Release();
			}
			if ( sceneControl != null )
				sceneControl.StopTimer();
			manipulator.TurnOff();
			SceneHierarchy.SetController( null );
			EditorRender.SetFFTT( false );
			base.OnDeactivateEditor();
			if ( sceneInfo != null && sceneInfo.Preset != null )
			{
				PresetSaver.PresetInfo info = new PresetSaver.PresetInfo();
				info.name = sceneInfo.Preset.GetName();
				info.typeName = sceneInfo.Preset.GetType().Name;
				Application.Application.Settings.Get<PresetSaver>().Modify( resource, info );
				sceneInfo.Preset = null;
			}
      ObjectsBrowser.ReselectCurrentItem();
      AnimGraph.SetControllers( null, null );
      AnimationsSelectionPanel.Controller = null;
			isActive = false;
		}

	  private void OnDbResourceChanged( DBID dbid )
	  {
	    FormUtils.Invoke(this, OnChangeDBResource, dbid);
	  }

    protected virtual void OnChangeDBResource( DBID dbid )
    {
      if ( isActive )
      {
        int currentFrame = SceneControl.Scene.GetCurrentFrame( mainSceneObject );

        sceneControl.Scene.OnDbResourceChanged( dbid );
        sceneInfo.Preset.Rebuild();
        SceneHierarchy.Rebuild();
        manipulator.ResetManipulator();
        mainSceneObject.CollisionGeometryVisible = collisionButton.Checked;
        manipulator.SetComponents( SceneHierarchy.SelectedComponent, activeLocator );
        ResetAGPanel();

        SceneControl.Scene.CalcFrameNumbers( mainSceneObject );
        SceneControl.Scene.SetCurrentFrame( mainSceneObject, currentFrame );

        AnimationsSelectionPanel.RebuildAnimationsList();
      }
    }

	  #endregion

		#region Methods to override.

		protected abstract string ConfigSection { get; }
		protected abstract EditorSceneObject CreateSceneObject(DBPtr<TResource> _resource);
		protected abstract string GetTabText(DBPtr<TResource> _resource);

		#endregion

		#region Internal methods.

		internal void PauseAnimation(bool _pause)
		{
			if ( !ReferenceEquals( SceneControl, null ) )
			{
				SceneControl.PauseAllAnimations( _pause );
			}
		}

		#endregion

		protected IEditorWinApplication Application
		{
			get { return application; }
		}

		protected SimpleSceneControl SceneControl
		{
			get { return sceneControl; }
		}

		private SceneHierarchyPanel SceneHierarchy
		{
			get { return Application.Panels.GetSingletonPanel<SceneHierarchyPanel>(); }
		}

	  private AnimGraphPanel AnimGraph
	  {
      get { return Application.Panels.GetSingletonPanel<AnimGraphPanel>(); }
	  }

		private AnimationsSelectionPanel AnimationsSelectionPanel
		{
      get { return AnimGraph.AnimationsPanel; }
		}

		private SkinsSelectionPanel SkinsSelectionPanel
		{
			get { return Application.Panels.GetSingletonPanel<SkinsSelectionPanel>(); }
		}

	  protected PropertiesEditorPanel PropertiesEditor
	  {
      get { return Application.Panels.GetSingletonPanel<PropertiesEditorPanel>(); }
	  }

	  private ObjectsBrowserPanel ObjectsBrowser
	  {
      get { return Application.Panels.GetSingletonPanel<ObjectsBrowserPanel>(); }
	  }

    public void SetQuat( Quat _quat )
    {
        quat = _quat;
    }

		#region IAnimationSelectionPanelExtension Members

    public void StartAnimation( int animationIndex )
		{
			if ( mainSceneObject != null )
			{
				if(agc1 != null)
					agc1.SwitchToAnims();

				if(agc2 != null)
					agc2.SwitchToAnims();

				mainSceneObject.StartAnimation( animationIndex, activeSceneComponentDBID );
				SceneControl.Scene.CalcFrameNumbers( mainSceneObject );

				//for debugging
				//System.Diagnostics.Debug.Print( "frames: {0}", SceneControl.Scene.GetFrameNumbers( mainSceneObject ) );
			}
		}

		void IAnimationSelectionPanelExtension.PauseAnimation(bool pause)
		{
			PauseAnimation( pause );
		}

    public IList<AnimInfo> GetAnimInfos()
    {
      if (mainSceneObject != null)
      {
      	if(agc1 != null)
      		return agc1.GetAnimInfos();

      	if(agc2 != null)
      		return agc2.GetAnimInfos();
      }

      return new List<AnimInfo>();
    }

		IList<Animation> IResourceParametersPanelExtension<Animation>.Items
		{
			get
			{
				if ( !activeSceneComponentDBID.IsEmpty )
				{
					DBPtr<DBResource> activeResource = DataBase.Get<DBResource>( activeSceneComponentDBID );
					if ( activeResource != null )
					{
						return GetAnimations( activeResource );
					}
				}
				else if ( resource != null )
				{
					return GetAnimations( resource );
				}

				return null;
			}
		}

		public virtual DBID ResourceId
		{
			get { return resource.DBId; }
		}

		#endregion

		#region ISceneHierarchyPanelExtension

		void ISceneHierarchyPanelExtension.ShowComponent( EditorSceneComponent _component, bool _isManipulatorOff )
		{
			if ( _isManipulatorOff )
				manipulator.TurnOff();

			SelectComponent( _component );
			manipulator.SwitchToComponentMode();

			if ( timeControl.Paused )
				RestoreLastFrame();
		}

		void ISceneHierarchyPanelExtension.SelectLocator( Locator _locator )
		{
			activeLocator = _locator.name;
			SceneHierarchy.SelectedComponent.sceneObject.SelectLocator( _locator.name );
			manipulator.SetComponents( SceneHierarchy.SelectedComponent, activeLocator );			
			manipulator.SwitchToLocatorMode();
		}

		void ISceneHierarchyPanelExtension.ApplyTrack( SceneObjectTrack _track )
		{
			ApplyTrack( _track.name );
		}

		void ISceneHierarchyPanelExtension.SelectAABB()
		{
			manipulator.SetComponents( SceneHierarchy.SelectedComponent, activeLocator );
			manipulator.SwitchToAABBMode( quat );
		}

		IList<EditorSceneComponent> IResourceParametersPanelExtension<EditorSceneComponent>.Items
		{
			get
			{
				if ( resource != null )
				{
					//TODO
					List<EditorSceneComponent> res = new List<EditorSceneComponent>();
					foreach (var eso in sceneControl.Scene.GetSceneElements())
					{
						if ( eso is EditorSceneObject )
						{
							res.Add( (eso as EditorSceneObject).GetRootEditorSceneComponent() );
						}
					}
					return res;
				}

				return null;
			}
		}

		#endregion

		#region ISceneControlExtension Members

		IObjectTransformControllersProvider ISceneControlExtension.TransformControllersProvider
		{
			get { return null; }
		}

		public BindsManager BindsManager
		{
			get { return Application.BindsManager; }
		}

		public string StatusLabel
		{
			set { application.StatusLabel = value; }
		}

		void ISceneControlExtension.AddBinds()
		{
			showGrid = BindsManager.RegisterBind(
				GetType().ToString(),
				"showGrid2",
				new BindConfig
					{
						keys = new List<Keys> {Keys.G}
					}
				);

			restart = BindsManager.RegisterBind(
				GetType().ToString(),
				"restart",
				new BindConfig
					{
						keys = new List<Keys> {Keys.Space}
					},
				new BindConfig
					{
						keys = new List<Keys> {Keys.F5}
					}
				);

			toggleTranslate = BindsManager.RegisterBind(
				GetType().ToString(),
				"toggleTranslate",
				new BindConfig
					{
						keys = new List<Keys> {Keys.W}
					}
				);

			toggleRotate = BindsManager.RegisterBind(
				GetType().ToString(),
				"toggleRotate",
				new BindConfig
					{
						keys = new List<Keys> {Keys.E}
					}
				);

			toggleScale = BindsManager.RegisterBind(
				GetType().ToString(),
				"toggleScale",
				new BindConfig
					{
						keys = new List<Keys> {Keys.R}
					}
				);
		}

		#endregion

		#region IAnimationGraphPanelExtension

		public AnimGraphCreator GetAnimGraphCreator()
		{
			if ( DataBase.Get<DBSceneComponent>( activeSceneComponentDBID ).Get() is DBAnimatedSceneComponent )
			{
				DBAnimatedSceneComponent skel = DataBase.Get<DBAnimatedSceneComponent>( activeSceneComponentDBID );

				if ( skel == null )
				{
					return null;
				}
				return skel.animGraph.Get();
			}
			return null;
		}

		#endregion

		#region ISkinsSelectionPanelExtension Members

		void ISkinsSelectionPanelExtension.ShowSkin(int skinName, bool show)
		{
			if ( mainSceneObject != null )
			{
				mainSceneObject.ShowSkin( skinName, show, activeSceneComponentDBID );
				if ( sceneInfo.Preset != null )
					sceneInfo.Preset.AfterRebuild();
			}
		}

		IList<SkinPart> IResourceParametersPanelExtension<SkinPart>.Items
		{
			get
			{
				if ( !activeSceneComponentDBID.IsEmpty )
				{
					DBPtr<DBResource> activeResource = DataBase.Get<DBResource>( activeSceneComponentDBID );
					if ( activeResource != null )
					{
						return GetSkins( activeResource );
					}
				}
				else if ( resource != null )
				{
					return GetSkins( resource );
				}

				return null;
			}
		}

		#endregion

		protected override sealed void OnClosed(EventArgs e)
		{
			base.OnClosed( e );
			DataBase.ChangeDBResourceEvent -= OnChangeDBResource;
			
			if ( sceneInfo != null && sceneInfo.Preset != null )
			{
				sceneInfo.Preset.Release();
			}
			sceneControl = null;
		}

		private void ResetAGPanel()
		{
			if (SceneHierarchy.SelectedComponent == null)
				return;

			//DBResource dbResource = DataBase.Get<DBResource>( SceneHierarchy.SelectedComponent.GetDBID() ).Get();
			//DBAnimatedSceneComponent animatedComponent = dbResource as DBAnimatedSceneComponent;

			//if ( animatedComponent == null ) //данная компонента не может содержать анимграф
			//  return;

			ResetAgController( SceneHierarchy.SelectedComponent, AnimGraphType.Main, ref agc1 );
			ResetAgController( SceneHierarchy.SelectedComponent, AnimGraphType.Additional, ref agc2 );	

			AnimGraph.SetControllers(agc1, agc2);

			if (sceneInfo.Preset != null)
			{
				sceneInfo.Preset.SetControllers(agc1, agc2);
			}
		}

		private void ResetAgController( EditorSceneComponent _sceneComponent, AnimGraphType _agType, ref AGController _agController )
    {
			if ( _agController == null )
			{
				_agController = new AGController( _sceneComponent, _agType, SceneControl.Scene );
				if ( !_agController.IsValid() )
				{
					_agController = null;
				}
			}
			else
			{
				if ( !DataBase.UndoRedoManager.IsCommandStarted )
				{
					_agController.SwitchToAG();
					_agController.Reset( _sceneComponent, _agType );
				}
			}
    }

		private IList<Animation> GetAnimations<TR>(DBPtr<TR> _resource)
      where TR : DBResource, new()
		{
			if ( _resource.Get() is DBAnimatedSceneComponent )
			{
				return (_resource.Get() as DBAnimatedSceneComponent).animations;
			}
			if ( _resource.Get() is DBSceneObject )
			{
				DBSceneObject dso_attached = _resource.Get() as DBSceneObject;
				if ( dso_attached.attached.Count > 0 )
				{
					for ( int i = 0; i < dso_attached.attached.Count; i++ )
					{
						if ( dso_attached.attached[0] is AttachedSceneComponent )
						{
							AttachedSceneComponent asc_attached = dso_attached.attached[0];
							if ( asc_attached.component.Get() is DBAnimatedSceneComponent )
							{
                return ( (DBAnimatedSceneComponent)asc_attached.component.Get() ).animations;
							}
						}
					}
				}
			}
			return null;
		}

		private IList<SkinPart> GetSkins<TR>(DBPtr<TR> _resource)
      where TR : DBResource, new()
		{
			if ( _resource.Get() is DBAnimatedSceneComponent )
			{
				return (_resource.Get() as DBAnimatedSceneComponent).skins;
			}
			if ( _resource.Get() is DBSceneObject )
			{
				DBSceneObject dso_attached = _resource.Get() as DBSceneObject;
				if ( dso_attached.attached.Count > 0 )
				{
					for ( int i = 0; i < dso_attached.attached.Count; i++ )
					{
						if ( dso_attached.attached[0] is AttachedSceneComponent )
						{
							AttachedSceneComponent asc_attached = dso_attached.attached[0];
							if ( asc_attached.component.Get() is DBAnimatedSceneComponent )
							{
								return (asc_attached.component.Get() as DBAnimatedSceneComponent).skins;
							}
						}
					}
				}
			}
			return null;
		}

		private void SelectComponent(EditorSceneComponent _component)
		{
			activeLocator = string.Empty;

			lastTrack = "";

			manipulator.SetComponents( _component, activeLocator );

			activeSceneComponentDBID = _component.GetDBID();
			
			mainSceneObject = _component.sceneObject;
			mainSceneObject.ClearVisibleSkins();
			
			AnimationsSelectionPanel.RebuildAnimationsList();
			SkinsSelectionPanel.RebuildSkinsList();

			List<int> activeSkins = mainSceneObject.GetActiveSkins( mainSceneObject.GetRootEditorSceneComponent().GetDBID() );
			if ( !activeSkins.Contains( 0 ) )
			{
				activeSkins.Add( 0 );
			}
			
			SkinsSelectionPanel.SelectSkins( activeSkins );
      
			if(!timeControl.Paused)
				ResetAGPanel();
		}

    public void RefreshScene()
    {
			int currentFrame = sceneControl.Scene.GetCurrentFrame( mainSceneObject );

			if ( sceneInfo.Preset != null )
			{
				sceneInfo.Preset.Rebuild();
				SceneHierarchy.Rebuild();

				ResetAGPanel();
				ApplyLastTrack();

				mainSceneObject.CollisionGeometryVisible = collisionButton.Checked;

				sceneControl.SetTimeControl( timeControl.AnimationSpeed );
				sceneControl.Scene.CalcFrameNumbers( mainSceneObject );		

				if(timeControl.Paused)
					sceneControl.Scene.SetCurrentFrame( mainSceneObject, currentFrame );
			}

    	OnRefreshScene();
    }

		private void RestoreLastFrame()
		{
			if ( sceneControl != null )
			{
				//надо выставлять предыдущий или последующий кадр, потом текущий кадр, иначе анимация может застрять между кадров
				int currentFrame = sceneControl.Scene.GetCurrentFrame( mainSceneObject );
				sceneControl.Scene.SetCurrentFrame( mainSceneObject, currentFrame == 0 ? 1 : currentFrame - 1 );
				sceneControl.Scene.SetCurrentFrame( mainSceneObject, currentFrame );
			}
		}

		//NVI pattern
		protected virtual void OnRefreshScene()
		{
			
		}
	}
}