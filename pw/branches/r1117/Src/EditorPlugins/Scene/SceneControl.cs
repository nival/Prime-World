using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Windows.Forms;
using EditorLib.Binds;
using EditorLib.Settings;
using EditorLib.States;
using EditorNative;
using EditorNative.SceneElements.SceneObjects;
using PF_EditorNative;
using EditorLib;

namespace EditorPlugins.Scene
{
  public class PickCache
  {
		public Vector2 cursorPosition;
    public PickResult result;
  }

	public sealed class SceneControl : UserControl
	{
		#region class SceneControlState

		private abstract class SceneControlState : State
		{
			private readonly SceneControl sceneControl;

			protected SceneControlState( SceneControl sceneControl )
			{
				this.sceneControl = sceneControl;
			}

			protected SceneControl SceneControl
			{
				get { return sceneControl; }
			}
		}

		#endregion

		#region class MainState

		private sealed class MainState : SceneControlState
		{
			private readonly StateMachine substatesMachine = new StateMachine();

			internal MainState( SceneControl sceneControl )
				: base( sceneControl )
			{
			}

			internal State Substate
			{
        get { return substatesMachine.State; }
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

		public Timer timer = new Timer() { Interval = 100 };
		private bool paused = false;
		private DateTime beginTime = DateTime.Now;
		private TimeSpan prevTickDelta = TimeSpan.Zero;

		private EditorScene scene;

    private Bind cameraYaw;
    private Bind cameraPitch;
    private Bind cameraDistance;
    private Bind cameraDistanceX;
    private Bind cameraDistanceY;
    private Bind cameraX;
    private Bind cameraY;
    private Bind dragX;
    private Bind dragY;

    public float mouseX;
    public float mouseY;
		private bool showGrid;

    PickCache pickCache;

    private bool isLimitCamera = true;
    private GameCameraLimits cameraLimits = new GameCameraLimits();

		private readonly MainState mainState;
		private readonly StateMachine stateMachine;
		private SettingsManager settingsManager;

		#endregion

    public void SetLimitCamera( bool _val )
    {
      isLimitCamera = _val;
      if ( isLimitCamera )
      {
        CheckCameraLimits();
      }
    }

		#region Initialization.

		public SceneControl(ISceneControlExtension extension, SettingsManager settingsManager)
		{
			this.extension = extension;
			this.settingsManager = settingsManager;

			Dock = DockStyle.Fill;

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


      #endregion

			DoubleBuffered = false;
			SetStyle( ControlStyles.UserPaint, true );
			SetStyle( ControlStyles.AllPaintingInWmPaint, true );
			SetStyle( ControlStyles.ResizeRedraw, true );
			SetStyle( ControlStyles.Opaque, true );
			UpdateStyles();

      scene = new EditorScene( Handle, Size, extension.TransformControllersProvider, true );
      extension.AddBinds();

			stateMachine = new StateMachine();
			mainState = new MainState( this );
			stateMachine.State = mainState;

      pickCache = new PickCache();
      pickCache.cursorPosition = CursorPosition;
      pickCache.result = Scene.Pick( CursorPosition );

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

		public void Initialize( IEditorCommonApplication application )
		{
		}

		#endregion

		#region Public methods.

		public void PauseAllAnimations( bool _pause )
		{
			if ( _pause != paused )
			{
				paused = _pause;
				if ( !paused )
				{
					beginTime = DateTime.Now - prevTickDelta;
				}
			}
		}

		public void ResetTime( TimeSpan time )
		{
			beginTime = DateTime.Now - time;
			prevTickDelta = time;
		}
		
		public PickResult Pick()
		{
      if( pickCache.cursorPosition.X != CursorPosition.X || pickCache.cursorPosition.Y != CursorPosition.Y )
      {
        pickCache.cursorPosition = CursorPosition;
        pickCache.result = scene.Pick( CursorPosition );
      }
      return pickCache.result;
    }

		public bool TryCaptureManipulator()
		{
			return scene.TryCaptureManipulator( CursorPosition );
		}

		#endregion

		#region Public properties.

		[Browsable(false)]
		[EditorBrowsable( EditorBrowsableState.Never )]
		public EditorScene Scene
		{
			get { return scene; }
		}

		[Browsable( false )]
		[EditorBrowsable( EditorBrowsableState.Never )]
		public Vector2 CursorPosition
		{
			get { return new Vector2( mouseX, mouseY ); }
		}

		[Browsable( false )]
		[EditorBrowsable( EditorBrowsableState.Never )]
		public Vector2 CursorDelta
		{
			get { return new Vector2( dragX.Delta, dragY.Delta ); }
		}

		[Browsable( false )]
		[EditorBrowsable( EditorBrowsableState.Never )]
		public Vector2 Center
		{
			get { return new Vector2( Width / 2f, Height / 2f ); }
		}

		[Browsable( false )]
		[EditorBrowsable( EditorBrowsableState.Never )]
		public State Substate
		{
      get { return mainState.Substate; }
			set { mainState.Substate = value; }
		}

		[Browsable( true )]
		[EditorBrowsable( EditorBrowsableState.Always )]
		public string ConfigSection { get; set; }

		[Browsable( true )]
		[EditorBrowsable( EditorBrowsableState.Always )]
		public bool ShowGrid
		{
			get { return showGrid; }
			set
			{
				showGrid = value;
				if ( showGrid )
					scene.ShowMayaGrid( 10.0f, 10, 107.0f );
				else
					scene.HideGrid();
			}
		}

    [Browsable( false )]
    public bool IsShowAttackSpace { get; set; }

		#endregion

		#region Event handlers.

		private void OnTimerTick( object sender, EventArgs e)
		{
      if( scene.IsValid() )
      {
        scene.ScreenSize = Size;
				scene.SetDrawCollisionSelection( settingsManager.Get<SceneSettingsConfig>().drawCollisionSelection );

        stateMachine.Update();

        Draw();
        if( IsShowAttackSpace && (scene != null) && (scene.SceneTerrain != null) )
          scene.SceneTerrain.ShowAttackSpace();
        
        extension.BindsManager.Update();

        UpdateStatusLabel();
      }
		}

	  private void UpdateStatusLabel()
	  {
	    if( pickCache.result.HasTerrainIntersection )
	    {
	      var sb = new StringBuilder();

	      sb.AppendFormat( "Position: {0} {1}    ", pickCache.result.TerrainIntersection.X,
	                       pickCache.result.TerrainIntersection.Y );

	      if( Scene.SelectedObjects.Count == 1 )
	      {
	        var selectedObject = Scene.SelectedObjects[0] as GameSceneObject;

	        var gobj = ( selectedObject == null ) ? null : selectedObject.GetGameObject();

	        if( gobj != null )
	        {
	          sb.Append( gobj.GetType().Name );

	          if( gobj.DBId.IsInlined )
	          {
	            sb.AppendFormat( " inlined in {0}", gobj.DBId.FileName );
	          }
	          else
	          {
	            sb.AppendFormat( ": {0}", gobj.DBId.FileName );
	          }
	        }
	        else
	        {
	          sb.Append( Scene.SelectedObjects[0].GetType().Name );
	        }
	      }
	      else
	      {
	        sb.AppendFormat( "{0} objects", Scene.SelectedObjects.Count );
	      }

	      extension.StatusLabel = sb.ToString();
	    }
	  }

	  protected override void OnMouseDown( MouseEventArgs e )
		{
			base.OnMouseDown( e );
			Focus();
      extension.BindsManager.OnMouseDown( e );
      OnTimerTick( this, EventArgs.Empty );
      //stateMachine.Update();
    }

		protected override void OnMouseUp( MouseEventArgs e )
		{
			base.OnMouseUp( e );
      extension.BindsManager.OnMouseUp( e );
      OnTimerTick( this, EventArgs.Empty );
      //stateMachine.Update();
    }

		protected override void OnMouseMove( MouseEventArgs e )
		{
			base.OnMouseMove( e );
      mouseY = e.Y;
      mouseX = e.X;
      extension.BindsManager.OnMouseMove( e );
      //OnTimerTick( this, EventArgs.Empty );
      //stateMachine.Update();
		}

		protected override void OnMouseWheel( MouseEventArgs e )
		{
			base.OnMouseWheel( e );
      extension.BindsManager.OnMouseWheel( e );
      //OnTimerTick( this, EventArgs.Empty );
      //stateMachine.Update();
    }

		protected override bool IsInputKey( Keys keyData )
		{
			if ( keyData == Keys.Up || keyData == Keys.Down || keyData == Keys.Right || keyData == Keys.Left || keyData == Keys.Tab ||
				keyData == Keys.Menu || keyData == Keys.ShiftKey || keyData == Keys.ControlKey )
				return true;
			else
				return base.IsInputKey( keyData );
		}

		protected override void OnKeyDown( KeyEventArgs e )
		{
			base.OnKeyDown( e );
      extension.BindsManager.OnKeyDown( e );
      OnTimerTick( this, EventArgs.Empty );
			e.Handled = true;
		}

		protected override void OnKeyUp( KeyEventArgs e )
		{
			base.OnKeyUp( e );
      extension.BindsManager.OnKeyUp( e );
      OnTimerTick( this, EventArgs.Empty );
      //stateMachine.Update();
		}

		protected override void Dispose( bool disposing )
		{
			if ( disposing )
			{
				scene.Dispose();
			}
		}

		protected override void OnPaint( PaintEventArgs e )
		{
			if ( DesignMode )
				base.OnPaint( e );
			else
				Draw();
		}

		protected override void OnSizeChanged( EventArgs e )
		{
			base.OnSizeChanged( e );
			UpdateCamera();
		}

    protected override void  OnLostFocus(EventArgs e)
    {
      base.OnLostFocus(e);
      extension.BindsManager.ResetPressedKeys();
      extension.BindsManager.Update();
      OnTimerTick( this, EventArgs.Empty );
    }
		#endregion

		#region Private helper methods and properties.

		private void UpdateCamera()
		{
			if ( Width > 0 && Height > 0 )
			{
        if ( cameraYaw.Delta != 0 || cameraPitch.Delta != 0 || cameraDistance.Delta != 0
          || cameraDistanceX.Delta != 0 || cameraDistanceY.Delta != 0 || cameraX.Delta != 0
          || cameraY.Delta != 0 )
        {
          Scene.UpdateCamera( 
            cameraYaw.Delta / (float)Width, 
            cameraPitch.Delta / (float)Height, 
            cameraDistance.Delta + ((float)( cameraDistanceX.Delta + cameraDistanceY.Delta )) / 40.0f,
            new Vector2( cameraX.Delta, cameraY.Delta ), 
            CursorPosition 
            );
          if ( isLimitCamera )
          {
            CheckCameraLimits();
          }
        }
			}
		}

    //private void FocusCamera()
    //{
    //  if ( scene.HasSelectedObject )
    //  {
    //    scene.SceneCamera.Anchor = scene.SelectedObjectsGroupCenter;
    //  }
    //  else
    //  {
    //    var pickResult = Pick();
    //    if ( pickResult.HasTerrainIntersection )
    //    {
    //      scene.SceneCamera.Anchor = pickResult.TerrainIntersection;
    //    }
    //    else
    //    {
    //      scene.SceneCamera.Anchor = Vector3.Zero;
    //    }
    //  }
    //}

		private void Draw()
		{
			if ( IsHandleCreated && !IsDisposed )
			{
				TimeSpan currentTickDelta = !paused ? DateTime.Now - beginTime : prevTickDelta;
        DateTime dynaProfDrawStart = DateTime.Now;
				scene.Draw(
					Handle,
					(float)(currentTickDelta.TotalMilliseconds / 1000),
					(float)((currentTickDelta.TotalMilliseconds - prevTickDelta.TotalMilliseconds) / 1000)
					);
        TimeSpan drawTimeTaken = DateTime.Now - dynaProfDrawStart;
        int desiredFPSPF = drawTimeTaken.Milliseconds * 2;
        if (desiredFPSPF < 10)
          desiredFPSPF = 10;
        if (desiredFPSPF > 1000)
          desiredFPSPF = 1000;
        timer.Interval = desiredFPSPF;
				prevTickDelta = currentTickDelta;
			}
		}

    private void CheckCameraLimits()
    {
      scene.CheckCameraLimits( cameraLimits.MaxYaw, cameraLimits.MinYaw, cameraLimits.MaxPitch,
        cameraLimits.MinPitch, cameraLimits.MaxRod, cameraLimits.MinRod, cameraLimits.MaxFov, cameraLimits.MinFov );
    }

		#endregion
	}
}
