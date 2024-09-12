using System.Collections.Generic;
using System.Windows.Forms;
using EditorLib.Menu;
using EditorLib.Settings;
using EditorLib;
using EditorPlugins.Scene;
using EditorLib.Binds;

namespace EditorPlugins.Binds
{
  [ConfigObject( true, "BindsCommandConfig" )]
  public sealed class BindsCommandConfig : SimpleConfigObject
  {
    public bool IsCasualBindings = false;
  }

  internal sealed class MayaBindsCommand : IEditorCommand
  {
    private readonly BindsCommandConfig config;

    public MayaBindsCommand( IEditorWinApplication _application )
    {
      config = _application.Application.Settings.Get<BindsCommandConfig>();
    }

    public override void Execute( IEditorWinApplication _application )
    {
      config.IsCasualBindings = false;
      SceneControlBinds( _application );
      SimpleSceneControlBinds( _application );
    }

    private void SimpleSceneControlBinds( IEditorWinApplication _application )
    { 
      //EditorLib.Scene.SimpleSceneControl
      string section = typeof( SimpleSceneControl ).ToString();

      _application.BindsManager.AssignBind(
        section,
        "cameraX",
        new BindConfig()
        {
          mouseAxis = MouseAxis.X,
          mouseButtons = MouseButtons.Middle,
          deltaSpeed = 1,
          keys = new List<Keys>() { Keys.Menu }
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraY",
        new BindConfig()
        {
          mouseAxis = MouseAxis.Y,
          mouseButtons = MouseButtons.Middle,
          deltaSpeed = 1,
          keys = new List<Keys>() { Keys.Menu }
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraYaw",
        new BindConfig()
        {
          mouseAxis = MouseAxis.X,
          mouseButtons = MouseButtons.Left,
          deltaSpeed = 4,
          keys = new List<Keys>() { Keys.Menu }
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraPitch",
        new BindConfig()
        {
          mouseAxis = MouseAxis.Y,
          mouseButtons = MouseButtons.Left,
          deltaSpeed = 4,
          keys = new List<Keys>() { Keys.Menu }
        }
        );

      _application.BindsManager.AssignBind(
        section,
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
    }

    private void SceneControlBinds( IEditorWinApplication _application )
    {
      //EditorLib.Scene.SceneControl
      string section = typeof( SceneControl ).ToString();
      
      _application.BindsManager.AssignBind(
        section,
        "cameraX",
        new BindConfig()
        {
          mouseAxis = MouseAxis.X,
          mouseButtons = MouseButtons.Middle,
          deltaSpeed = 1,
          keys = new List<Keys>() { Keys.Menu }
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraY",
        new BindConfig()
        {
          mouseAxis = MouseAxis.Y,
          mouseButtons = MouseButtons.Middle,
          deltaSpeed = 1,
          keys = new List<Keys>() { Keys.Menu }
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraYaw",
        new BindConfig()
        {
          mouseAxis = MouseAxis.X,
          mouseButtons = MouseButtons.Left,
          deltaSpeed = 4,
          keys = new List<Keys>() { Keys.Menu }
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraPitch",
        new BindConfig()
        {
          mouseAxis = MouseAxis.Y,
          mouseButtons = MouseButtons.Left,
          deltaSpeed = 4,
          keys = new List<Keys>() { Keys.Menu }
        }
        );

      _application.BindsManager.AssignBind(
        section,
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
    }

    public override string Name
    {
      get { return "Maya-like Keyboard Bindings"; }
    }

    public override bool IsChecked
    {
      get { return !config.IsCasualBindings; }
    }
  }

  internal sealed class CasualBindsCommand : IEditorCommand
  {
    private BindsCommandConfig config;

    public CasualBindsCommand( IEditorWinApplication _application )
    {
      config = _application.Application.Settings.Get<BindsCommandConfig>();
    }

    public override void Execute( IEditorWinApplication _application )
    {
      config.IsCasualBindings = true;
      SceneControlBinds( _application );
      SimpleSceneControlBinds( _application );
    }

    private static void SimpleSceneControlBinds( IEditorWinApplication _application )
    {
      //EditorLib.Scene.SimpleSceneControl
      string section = typeof( SimpleSceneControl ).ToString();


      _application.BindsManager.AssignBind(
        section,
        "cameraX",
        new BindConfig()
        {
          deltaSpeed = -20,
          keys = new List<Keys>() { Keys.Left }
        },
        new BindConfig()
        {
          deltaSpeed = 20,
          keys = new List<Keys>() { Keys.Right }
        },
        new BindConfig()
        {
          mouseAxis = MouseAxis.X,
          mouseButtons = MouseButtons.Middle,
          deltaSpeed = 1,
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraY",
        new BindConfig()
        {
          deltaSpeed = -20,
          keys = new List<Keys>() { Keys.Up }
        },
        new BindConfig()
        {
          deltaSpeed = 20,
          keys = new List<Keys>() { Keys.Down }
        },
        new BindConfig()
        {
          mouseAxis = MouseAxis.Y,
          mouseButtons = MouseButtons.Middle,
          deltaSpeed = 1,
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraYaw",
        new BindConfig()
        {
          mouseAxis = MouseAxis.X,
          mouseButtons = MouseButtons.Right,
          deltaSpeed = 4,
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraPitch",
        new BindConfig()
        {
          mouseAxis = MouseAxis.Y,
          mouseButtons = MouseButtons.Right,
          deltaSpeed = 4,
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraDistance",
        new BindConfig()
        {
          mouseAxis = MouseAxis.Wheel,
          deltaSpeed = 1,
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
    }

    private static void SceneControlBinds( IEditorWinApplication _application )
    {
      //EditorLib.Scene.SceneControl
      string section = typeof( SceneControl ).ToString();

      _application.BindsManager.AssignBind(
        section,
        "cameraX",
        new BindConfig()
        {
          deltaSpeed = -20,
          keys = new List<Keys>() { Keys.Left }
        },
        new BindConfig()
        {
          deltaSpeed = 20,
          keys = new List<Keys>() { Keys.Right }
        },
        new BindConfig()
        {
          mouseAxis = MouseAxis.X,
          mouseButtons = MouseButtons.Middle,
          deltaSpeed = 1,
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraY",
        new BindConfig()
        {
          deltaSpeed = -20,
          keys = new List<Keys>() { Keys.Up }
        },
        new BindConfig()
        {
          deltaSpeed = 20,
          keys = new List<Keys>() { Keys.Down }
        },
        new BindConfig()
        {
          mouseAxis = MouseAxis.Y,
          mouseButtons = MouseButtons.Middle,
          deltaSpeed = 1,
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraYaw",
        new BindConfig()
        {
          mouseAxis = MouseAxis.X,
          mouseButtons = MouseButtons.Right,
          deltaSpeed = 4,
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraPitch",
        new BindConfig()
        {
          mouseAxis = MouseAxis.Y,
          mouseButtons = MouseButtons.Right,
          deltaSpeed = 4,
        }
        );

      _application.BindsManager.AssignBind(
        section,
        "cameraDistance",
        new BindConfig()
        {
          mouseAxis = MouseAxis.Wheel,
          deltaSpeed = 1,
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
    }

    public override string Name
    {
      get { return "Casual Keyboard Bindings"; }
    }

    public override bool IsChecked
    {
      get { return config.IsCasualBindings; }
    }
  }
}
