using DBTypes;
using EditorLib;
using EditorPlugins.Scene;
using EditorNative;
using EditorNative.SceneElements.SceneObjects;
using libdb.DB;
using libdb.UndoRedo;
using EditorPlugins.Scene.Editors;

namespace EditorPlugins.Scene.Viewers
{
  public class ComponentSceneElementCs : ComponentSceneElement
  {
    public ComponentSceneElementCs( EditorSceneComponent component, libdb.UndoRedo.UndoRedoManager manager )
    : base( component, manager )
    {
      if ( component != null )
      {
        EditorSceneObject so = component.sceneObject;
        DBID dbid = so.DbId;
        DBPtr<DBSceneResource> dbso = DataBase.Get<DBSceneResource>( dbid );

        AttachedSceneComponent asc = FindAttachedSceneComponentByDBID( dbso.Get().attached, component.GetDBID() );
        if ( asc != null )
        {
          Placement pos = new Placement();
          pos.location = asc.placement.pos.GetValue( 0.0f );
          pos.scale = asc.placement.scale.GetValue( 0.0f );
          pos.rotation = asc.placement.rot.GetValue( 0.0f );
          InitPlacement( pos );
        }
      }
    }

    bool CloseTest( AttachedSceneComponent sc )
    {
      Placement dbPlacement1 = GetDBPlacement();

      Vec3 pos = sc.placement.pos.GetValue( 0.0f );
      Scale scale = sc.placement.scale.GetValue( 0.0f );
      Quat rot = sc.placement.rot.GetValue( 0.0f );

      return System.Math.Abs( pos.x - dbPlacement1.location.x ) < 0.01f 
             && System.Math.Abs( pos.y - dbPlacement1.location.y ) < 0.01f
             && System.Math.Abs( pos.z - dbPlacement1.location.z ) < 0.01f
             && System.Math.Abs( scale.x - dbPlacement1.scale.x ) < 0.01f
             && System.Math.Abs( scale.y - dbPlacement1.scale.y ) < 0.01f
             && System.Math.Abs( scale.z - dbPlacement1.scale.z ) < 0.01f
             && System.Math.Abs( rot.x - dbPlacement1.rotation.x ) < 0.01f
             && System.Math.Abs( rot.y - dbPlacement1.rotation.y ) < 0.01f
             && System.Math.Abs( rot.z - dbPlacement1.rotation.z ) < 0.01f
             && System.Math.Abs( rot.w - dbPlacement1.rotation.w ) < 0.01f;
    }

    AttachedSceneComponent FindAttachedSceneComponentByDBID( libdb.IChangeableList<AttachedSceneComponent> attacheds, DBID dbid )
    {
      for ( int i = 0; i < attacheds.Count; i++ )
      {
      	if (attacheds[i].component == null)
      		continue;

      	if (attacheds[i].component.DBId == dbid && CloseTest(attacheds[i]))
      		return attacheds[i];

      	AttachedSceneComponent res = FindAttachedSceneComponentByDBID( attacheds[i].component.Get().attached, dbid );

      	if (res != null)
      		return res;
      }

      return null;
    }

    public override void Apply( bool isMoved, bool isRotated, bool isScaled )
    {
      if ( !isMoved && !isRotated && !isScaled )
        return;

    	if (sceneComponent == null) return;

    	EditorSceneObject so = sceneComponent.sceneObject;
    	DBID dbid = so.DbId;
    	DBPtr<DBSceneResource> dbso = DataBase.Get<DBSceneResource>( dbid );

    	AttachedSceneComponent asc = FindAttachedSceneComponentByDBID( dbso.Get().attached, sceneComponent.GetDBID() );

    	if (asc == null) return;
    	
			using ( var trans = new UndoRedoTransaction( "Change component pos" ) )
    	{
    		Placement pos = GetInitPlacement();

    		if ( isMoved )
    			asc.placement.pos.Clear( pos.location );

    		if ( isRotated )
    			asc.placement.rot.Clear( pos.rotation );

    		if ( isScaled )
    			asc.placement.scale.Clear( pos.scale );

    		trans.Commit();
    		DataBase.ChangeCallback( asc.GetOwner().DBId );	
    	}
    }
  }

  public enum ManipulatorMode
  {
    AABB,
    Locators,
    Component,
  }

  public class ManipulatorControl
  {
    private ManipulatorSceneObject manipulator = null;
    private AABBSceneElement aabbse = null;
    private LocatorSceneElement locatorse = null;
    private ComponentSceneElementCs componentse = null;

    private IEditorWinApplication application = null;
    private SimpleSceneControl sceneControl = null;
		private TimeSlider timeSlider = null;

    private EditorSceneComponent activeSceneComponent = null;
    private string activeLocator = string.Empty;
    private EditorSceneComponent saveActiveSceneComponent = null;
    private string saveActiveLocator = string.Empty;

    private bool isActive = false;

    private ManipulatorMode mode = ManipulatorMode.AABB;

    private void ResetElements()
    {
      sceneControl.Scene.Remove( aabbse );
      aabbse = null;

      sceneControl.Scene.Remove( locatorse );
      locatorse = null;

    	if (activeSceneComponent != null)
    		activeSceneComponent.sceneObject.SelectLocator(string.Empty);
    }

    public void ResetManipulator()
    {
      sceneControl.Scene.Remove( manipulator );
      manipulator = null;
      sceneControl.SetManipulator( manipulator );
    }

    public ManipulatorControl( EditorSceneComponent component, SimpleSceneControl sceneControl, IEditorWinApplication application, TimeSlider timeSlider )
    {
      this.activeSceneComponent = component;
      this.sceneControl = sceneControl;
      this.application = application;
			this.timeSlider = timeSlider;
      this.mode = ManipulatorMode.AABB;
    }

    public void SetComponents( EditorSceneComponent component, string locator )
    {
			this.activeSceneComponent = component;		
			this.activeLocator = locator;
    }

    public void SwitchToAABBMode( Quat quat )
    {
      mode = ManipulatorMode.AABB;
      
			if ( isActive )
      {
        TurnOn();
      }
      else
      {
        ResetElements();
        aabbse = new AABBSceneElement( activeSceneComponent, application.Application.UndoRedo );
        if ( quat != null )
            aabbse.SetPlacementRot(quat.x, quat.y, quat.z, quat.w);
        sceneControl.Scene.Add( aabbse );
      }
    }

    public void SwitchToComponentMode()
    {
      mode = ManipulatorMode.Component;
      if ( isActive )
      {
        TurnOn();
      }
      else
      {
        ResetElements();
      }
    }

    public void SwitchToLocatorMode()
    {
      mode = ManipulatorMode.Locators;
      if ( isActive )
      {
        TurnOn();
      }
      else
      {
        ResetElements();
        activeSceneComponent.sceneObject.SelectLocator( activeLocator );
      }
    }

    public void TurnOn()
    {
			ManipulatorTypes currentMoveMode = ManipulatorTypes.None;
			if(manipulator != null)
				currentMoveMode = manipulator.GetMode();

      activeSceneComponent.sceneObject.SelectLocator( string.Empty );
      saveActiveSceneComponent = activeSceneComponent;
      saveActiveLocator = activeLocator;
			TurnOff();
		
			activeSceneComponent = saveActiveSceneComponent;
      activeLocator = saveActiveLocator;
			timeSlider.Paused = true;
      activeSceneComponent.sceneObject.SelectLocator( string.Empty );

      if ( mode == ManipulatorMode.AABB )
      {
        manipulator = new ManipulatorSceneObject( aabbse );
        sceneControl.Scene.Add( manipulator );
        sceneControl.SetManipulator( manipulator );
      }
      else if ( mode == ManipulatorMode.Locators )
      {
        locatorse = new LocatorSceneElement( activeSceneComponent, application.Application.UndoRedo, activeLocator );
        manipulator = new ManipulatorSceneObject( locatorse );
        sceneControl.Scene.Add( locatorse );
        sceneControl.Scene.Add( manipulator );
        sceneControl.SetManipulator( manipulator );
      }
      else if ( mode == ManipulatorMode.Component )
      {
        componentse = new ComponentSceneElementCs( activeSceneComponent, application.Application.UndoRedo );
        manipulator = new ManipulatorSceneObject( componentse );
        sceneControl.Scene.Add( componentse );
        sceneControl.Scene.Add( manipulator );
        sceneControl.SetManipulator( manipulator );
      }

			if ( manipulator != null && currentMoveMode != ManipulatorTypes.None )
				manipulator.SetMode( currentMoveMode );

      isActive = true;
    }

    public void TurnOff()
    {
			if ( !isActive )
				return;
    	isActive = false;

      ResetElements();
      if ( manipulator != null )
      {
				manipulator.Apply( false, false, false );
      }
        
      ResetManipulator();
    }

    public bool IsActive()
    {
      return isActive;
    }

    public void SetMode( ManipulatorTypes _mode )
    {
      if ( manipulator != null )
      {
        manipulator.SetMode( _mode );
      }
    }
  }
}