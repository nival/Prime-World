using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using EditorLib.Binds;
using EditorLib.FieldProcessor;
using EditorLib.PropertiesEditor;
using EditorLib.Settings;
using EditorLib.States;
using EditorNative;
using EditorNative.SceneElements.SceneObjects;
using PF_EditorNative;
using EditorLib;

namespace EditorPlugins.Scene
{
	public enum PlaySpeed
	{
		OneFPS = 0, 
		X1_16 = 1, 
		X1_8 = 2, 
		X1_4 = 3, 
		X1_2 = 4, 
		X1 = 5, 
		X2 = 6, 
		X4 = 7, 
		X8 = 8, 
		X16 = 9, 
		Pause = 10
	} ;

  public sealed class SimpleSceneControl : UserControl
	{
		#region class SceneControlState

		private abstract class SimpleSceneControlState : State
		{
			private readonly SimpleSceneControl sceneControl;

			protected SimpleSceneControlState(SimpleSceneControl sceneControl)
			{
				this.sceneControl = sceneControl;
			}

			protected SimpleSceneControl SceneControl
			{
				get { return sceneControl; }
			}
		}

		#endregion

		#region class MainState

		private sealed class MainState : SimpleSceneControlState
		{
			private readonly StateMachine substatesMachine = new StateMachine();

			internal MainState(SimpleSceneControl sceneControl)
				: base(sceneControl)
			{
			}

			internal State Substate
			{
				set { substatesMachine.State = value; }
			}

			public override void OnUpdate()
			{
        SceneControl.UpdateCamera();
        substatesMachine.Update();
			}
		}

		#endregion

		#region Private members.

		ISceneControlExtension extension;

		public readonly Timer timer = new Timer() { Interval = 50 };
		private bool paused = false;
		private DateTime beginTime = DateTime.Now;
		private TimeSpan prevTickDelta = TimeSpan.Zero;

		private SimpleEditorScene scene;

		private readonly Bind cameraMoveMode;

		private PlaySpeed timeControl;

		private Bind cameraYaw;
		private Bind cameraPitch;
		private Bind cameraDistance;
		private Bind cameraDistanceX;
		private Bind cameraDistanceY;
		private Bind cameraX;
		private Bind cameraY;
		private Bind dragX;
		private Bind dragY;
    private Bind togglePassMask;

    private ManipulatorSceneObject manipulator;

		private float mouseX;
		private float mouseY;
    private bool showGrid;

    private bool isLimitCamera = true;
    private Type UpdatedType = null;

    private GameCameraLimits cameraLimits = new GameCameraLimits();

		private readonly MainState mainState;
		private readonly StateMachine stateMachine;

    private PropertiesEditorPanel propertiesPanel;

    public delegate void OnTileClickHandle(SimplePickResult res);
    public event OnTileClickHandle OnTileClick = null;
		public event OnTileClickHandle OnTileMove = null;
		private bool isMouseDown = false;

    public float lineDistance = 10.0f;
    public int subDivision = 10;
    public float areaSize = 100.0f;

		public delegate void ScenePresetTick( float time, float delta );
    public ScenePresetTick PresetTick = null;
    
		#endregion

    public void SetLimitCamera(bool _val)
    {
      isLimitCamera = _val;
      if (isLimitCamera)
      {
        CheckCameraLimits();
      }
      if (propertiesPanel != null)
      {
        // This condition prevents flicker (unnecessary RefreshView-s) in the property editor when a different object is selected
        FullTypeDescriptorWrapper so = propertiesPanel.SelectedObject as FullTypeDescriptorWrapper;
        if (so != null && so.GetPropertyOwner().GetType() == UpdatedType || UpdatedType == null)
          propertiesPanel.RefreshView(false);
      }
    }

		#region Initialization.

		public SimpleSceneControl()
      : this(null as ISceneControlExtension, null as PropertiesEditorPanel, null as SettingsManager, null as Type)
		{
		}

		public SimpleSceneControl(ISceneControlExtension extension, PropertiesEditorPanel _propertiesPanel, SettingsManager settingsManager, Type _type)
			: this(
					(handle, size) => new SimpleEditorScene(handle, size),
					extension,
          settingsManager
					)
		{
      propertiesPanel = _propertiesPanel;
      UpdatedType = _type;
		}

		public SimpleSceneControl(Function<SimpleEditorScene, IntPtr, Size> createScene, SettingsManager settingsManager)
			: this(createScene, null as ISceneControlExtension, settingsManager)
		{
		}

		public SimpleSceneControl(
			Function<SimpleEditorScene, IntPtr, Size> createScene,
			ISceneControlExtension extension,
      SettingsManager settingsManager
			)
		{
			this.extension = extension;

			Dock = DockStyle.Fill;

			#region Binary binds.

      cameraMoveMode = extension.BindsManager.RegisterBind(
        GetType().ToString(),
        "cameraMoveMode",
				new BindConfig()
				{
					keys = new List<Keys>() { Keys.Menu }
				}
				);

			#endregion

			#region Value binds.

      cameraYaw = extension.BindsManager.RegisterBind(
        GetType().ToString(),
        "cameraYaw",
				new BindConfig()
				{
					mouseAxis = MouseAxis.X,
					mouseButtons = MouseButtons.Left,
					deltaSpeed = 4,
					keys = new List<Keys>() { Keys.Menu }
				}
				);

      cameraPitch = extension.BindsManager.RegisterBind(
        GetType().ToString(),
        "cameraPitch",
				new BindConfig()
				{
					mouseAxis = MouseAxis.Y,
					mouseButtons = MouseButtons.Left,
					deltaSpeed = 4,
					keys = new List<Keys>() { Keys.Menu }
				}
				);

      cameraDistance = extension.BindsManager.RegisterBind(
        GetType().ToString(),
        "cameraDistance",
				new BindConfig()
				{
					mouseAxis = MouseAxis.Wheel,
					deltaSpeed = 1,
					keys = new List<Keys>() { Keys.Menu }
				},
				new BindConfig()
				{
					deltaSpeed = 1,
					keys = new List<Keys>() { Keys.Menu, Keys.PageUp }
				},
				new BindConfig()
				{
					deltaSpeed = -1,
					keys = new List<Keys>() { Keys.Menu, Keys.PageDown }
				}
				);

      cameraDistanceX = extension.BindsManager.RegisterBind(
        GetType().ToString(),
        "cameraDistanceX",
				new BindConfig()
				{
					mouseAxis = MouseAxis.X,
					mouseButtons = MouseButtons.Right,
					deltaSpeed = -1,
					keys = new List<Keys>() { Keys.Menu }
				}
				);

      cameraDistanceY = extension.BindsManager.RegisterBind(
        GetType().ToString(),
        "cameraDistanceY",
				new BindConfig()
				{
					mouseAxis = MouseAxis.Y,
					mouseButtons = MouseButtons.Right,
					deltaSpeed = -1,
					keys = new List<Keys>() { Keys.Menu }
				}
				);

      cameraX = extension.BindsManager.RegisterBind(
        GetType().ToString(),
        "cameraX",
				new BindConfig()
				{
					mouseAxis = MouseAxis.X,
					mouseButtons = MouseButtons.Middle,
					deltaSpeed = 1,
					keys = new List<Keys>() { Keys.Menu }
				}
				);

      cameraY = extension.BindsManager.RegisterBind(
        GetType().ToString(),
        "cameraY",
				new BindConfig()
				{
					mouseAxis = MouseAxis.Y,
					mouseButtons = MouseButtons.Middle,
					deltaSpeed = 1,
					keys = new List<Keys>() { Keys.Menu }
				}
				);

      dragX = extension.BindsManager.RegisterBind(
        GetType().ToString(),
        "dragX",
				new BindConfig()
				{
					mouseAxis = MouseAxis.X,
					mouseButtons = MouseButtons.Left,
					deltaSpeed = -1
				}
				);

      dragY = extension.BindsManager.RegisterBind(
        GetType().ToString(),
        "dragY",
				new BindConfig()
				{
					mouseAxis = MouseAxis.Y,
					mouseButtons = MouseButtons.Left,
					deltaSpeed = -1
				}
				);

      togglePassMask = extension.BindsManager.RegisterBind(
        GetType().ToString(),
        "togglePassMask", 
        new BindConfig() 
        { 
          mouseButtons = MouseButtons.Left 
        } 
        );

			#endregion

			DoubleBuffered = false;
			SetStyle(ControlStyles.UserPaint, true);
			SetStyle(ControlStyles.AllPaintingInWmPaint, true);
			SetStyle(ControlStyles.ResizeRedraw, true);
			SetStyle(ControlStyles.Opaque, true);
			UpdateStyles();

			if (!ReferenceEquals(extension, null))
			{
				scene = createScene(Handle, Size);
				extension.AddBinds();
			}
			else
			{
				scene = createScene(Handle, Size);
			}

			stateMachine = new StateMachine();
			mainState = new MainState(this);
			stateMachine.State = mainState;

      scene.SetPostFX( settingsManager.Get<SceneSettingsConfig>().usePostFX );

			timer.Tick += OnTimerTick;
			timer.Start();
		}

    public void StartTimer()
    {
      timer.Start();
    }

    public void StopTimer()
    {
      timer.Stop();
    }

		public void Initialize(IEditorCommonApplication application)
		{
		}

		#endregion

		#region Public methods.

		public void PauseAllAnimations(bool _pause)
		{
			if (_pause != paused)
			{
				paused = _pause;
				if (!paused)
				{
					beginTime = DateTime.Now - prevTickDelta;
				}
			}
		}

		public void ResetTime(TimeSpan time)
		{
			beginTime = DateTime.Now - time;
			prevTickDelta = time;
		}

    public SimplePickResult Pick()
    {
      return scene.Pick(CursorPosition);
    }

		#endregion

		#region Public properties.

		[Browsable(false)]
		[EditorBrowsable(EditorBrowsableState.Never)]
		public SimpleEditorScene Scene
		{
			get { return scene; }
		}

		[Browsable(false)]
		[EditorBrowsable(EditorBrowsableState.Never)]
		public Vector2 CursorPosition
		{
			get { return new Vector2(mouseX, mouseY); }
		}

		[Browsable(false)]
		[EditorBrowsable(EditorBrowsableState.Never)]
		public Vector2 CursorDelta
		{
			get { return new Vector2(dragX.Delta, dragY.Delta); }
		}

		[Browsable(false)]
		[EditorBrowsable(EditorBrowsableState.Never)]
		public Vector2 Center
		{
			get { return new Vector2(Width / 2f, Height / 2f); }
		}

		[Browsable(false)]
		[EditorBrowsable(EditorBrowsableState.Never)]
		public State Substate
		{
			set { mainState.Substate = value; }
		}

		[Browsable(true)]
		[EditorBrowsable(EditorBrowsableState.Always)]
		public string ConfigSection { get; set; }

		[Browsable(true)]
		[EditorBrowsable(EditorBrowsableState.Always)]
		public bool ShowGrid
		{
			get { return showGrid; }
			set
			{
				showGrid = value;
				if (showGrid)
          scene.ShowMayaGrid( lineDistance, subDivision, areaSize );
				else
					scene.HideGrid();
			}
		}

		#endregion

    public void SetTimeControl( PlaySpeed _playSpeed )
    {
      timeControl = _playSpeed;
    }

    public void SetManipulator( ManipulatorSceneObject _manipulator )
    {
      manipulator = _manipulator;
    }

		#region Event handlers.

		private void OnTimerTick(object sender, EventArgs e)
		{
      if ( scene.IsValid() )
      {
        if ( manipulator != null && !cameraMoveMode.IsActive )
        {
          manipulator.CalculateNewLocation( CursorPosition, CursorDelta, Scene );
        }

        scene.ScreenSize = Size;

        stateMachine.Update();

				DateTime dynaProfDrawStart = DateTime.Now;
				TimeSpan currentTickDelta = !paused ? DateTime.Now - beginTime : prevTickDelta;
				float time = (float)( currentTickDelta.TotalMilliseconds / 1000 );
				float delta = (float)( ( currentTickDelta.TotalMilliseconds - prevTickDelta.TotalMilliseconds ) / 1000 );

				if ( PresetTick != null )
					PresetTick( time, delta );
        Draw( time, delta );
        extension.BindsManager.Update();

				TimeSpan drawTimeTaken = DateTime.Now - dynaProfDrawStart;
				int desiredFPSPF = drawTimeTaken.Milliseconds * 2;
				if ( desiredFPSPF < 10 )
					desiredFPSPF = 10;
				if ( desiredFPSPF > 1000 )
					desiredFPSPF = 1000;
				timer.Interval = desiredFPSPF;
				prevTickDelta = currentTickDelta;
      }
		}

		protected override void OnMouseDown(MouseEventArgs e)
		{
      if ( OnTileClick != null && e.Button == MouseButtons.Left && !cameraMoveMode.IsActive )
      {
				SimplePickResult result = Pick();
				OnTileClick( result );
        isMouseDown = true;
      }

      if ( manipulator != null && !cameraMoveMode.IsActive )
      {
        manipulator.Select( CursorPosition, Scene );
      }

			base.OnMouseDown( e );
			Focus();
      extension.BindsManager.OnMouseDown( e );
		}

		protected override void OnMouseUp(MouseEventArgs e)
		{
			isMouseDown = false;
			base.OnMouseUp( e );
      extension.BindsManager.OnMouseUp( e );
		}

		protected override void OnMouseMove(MouseEventArgs e)
		{
			base.OnMouseMove( e );
			extension.BindsManager.OnMouseMove( e );
			mouseY = e.Y;
			mouseX = e.X;

      if ( OnTileMove != null && isMouseDown && !cameraMoveMode.IsActive )
			{
				SimplePickResult result = Pick();
				OnTileMove( result );
			}

			//base.OnMouseMove(e);
			//extension.BindsManager.OnMouseMove( e );
			//mouseY = e.Y;
			//mouseX = e.X;
		}

		protected override void OnMouseWheel(MouseEventArgs e)
		{
			base.OnMouseWheel(e);
      extension.BindsManager.OnMouseWheel( e );
		}

		protected override bool IsInputKey(Keys keyData)
		{
			if (
				keyData == Keys.Up ||
				keyData == Keys.Down ||
				keyData == Keys.Right ||
				keyData == Keys.Left ||
				keyData == Keys.Tab
				)
			{
				return true;
			}
			else
			{
				return base.IsInputKey(keyData);
			}
		}

		protected override void OnKeyDown(KeyEventArgs e)
		{
			base.OnKeyDown(e);
      extension.BindsManager.OnKeyDown( e );
		}

		protected override void OnKeyUp(KeyEventArgs e)
		{
			base.OnKeyUp(e);
      extension.BindsManager.OnKeyUp( e );
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing)
			{
				scene.Dispose();
			}
		}

		protected override void OnPaint(PaintEventArgs e)
		{
			if (DesignMode)
				base.OnPaint(e);
			else
				Draw( 0.0f, 0.0f );
		}

		protected override void OnSizeChanged(EventArgs e)
		{
			base.OnSizeChanged(e);
			UpdateCamera();
		}

    protected override void OnLostFocus( EventArgs e )
    {
      base.OnLostFocus( e );
      extension.BindsManager.ResetPressedKeys();
    }

		#endregion

		#region Private helper methods and properties.

		private void UpdateCamera()
		{
			if (Width > 0 && Height > 0)
			{
        if (cameraYaw.Delta != 0 || cameraPitch.Delta != 0 || cameraDistance.Delta != 0 
            || cameraDistanceX.Delta != 0 || cameraDistanceY.Delta != 0 || cameraX.Delta != 0 
            || cameraY.Delta != 0)
        {
          Scene.UpdateCamera(
            cameraYaw.Delta / (float)Width,
            cameraPitch.Delta / (float)Height,
            cameraDistance.Delta + (cameraDistanceX.Delta + cameraDistanceY.Delta) / 2,
            new Vector2(cameraX.Delta, cameraY.Delta),
            CursorPosition
            );

          if (isLimitCamera)
          {
            CheckCameraLimits();
          }

          if (propertiesPanel != null )
          {
            // This condition prevents flicker (unnecessary RefreshView-s) in the property editor when a different object is selected
            FullTypeDescriptorWrapper so = propertiesPanel.SelectedObject as FullTypeDescriptorWrapper;
            if ( so != null && so.GetPropertyOwner().GetType() == UpdatedType || UpdatedType == null )
              propertiesPanel.RefreshView(false);
          }
        }
			}
		}

    private void CheckCameraLimits()
    {
      Scene.CheckCameraLimits( cameraLimits.MaxYaw, cameraLimits.MinYaw, cameraLimits.MaxPitch,
        cameraLimits.MinPitch, cameraLimits.MaxRod, cameraLimits.MinRod, cameraLimits.MaxFov, cameraLimits.MinFov );
    }

		private void Draw( float time, float delta )
		{
			if (IsHandleCreated && !IsDisposed)
			{
        switch (timeControl)
        {
        case PlaySpeed.OneFPS:
          delta /= 30;
          Scene.TimeSpeed = 1.0f / 30.0f;
          break;
				case PlaySpeed.X1_16:
          delta /= 16;
          Scene.TimeSpeed = 1.0f / 16.0f;
          break;
        case PlaySpeed.X1_8:
          delta /= 8;
          Scene.TimeSpeed = 1.0f / 8.0f;
          break;
        case PlaySpeed.X1_4:
          delta /= 4;
          Scene.TimeSpeed = 1.0f / 4.0f;
          break;
				case PlaySpeed.X1_2:
          delta /= 2;
          Scene.TimeSpeed = 1.0f / 2.0f;
          break;
				case PlaySpeed.X1:
          Scene.TimeSpeed = 1.0f;
          break;
				case PlaySpeed.X2:
          delta *= 2;
          Scene.TimeSpeed = 2.0f;
          break;
				case PlaySpeed.X4:
          delta *= 4;
          Scene.TimeSpeed = 4.0f;
          break;
				case PlaySpeed.X8:
          delta *= 8;
          Scene.TimeSpeed = 8.0f;
          break;
				case PlaySpeed.X16:
          delta *= 16;
          Scene.TimeSpeed = 16.0f;
          break;
				case PlaySpeed.Pause:
          delta = 0;
          Scene.TimeSpeed = 0.0f;
          break;
        default:
          break;
        }
        
        scene.Draw( Handle, time, delta );
			}
		}

		#endregion
	}
}
