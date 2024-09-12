using System;
using System.Diagnostics;
using EditorLib;
using EditorLib.Binds;
using EditorLib.Extensions;
using EditorLib.PropertiesEditor;
using EditorLib.States;
using EditorNative;
using EditorNative.SceneElements.SceneObjects;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;

namespace EditorPlugins.Scene.Viewers.Effect
{
  [EditorAttribute("Texture", true, "65956d65-b0b4-4314-9de7-9ec3f3cdef95" )]
  [ApplicableForDeriver]
  public sealed class TextureViewer : Editor<DBTypes.Texture>, ISceneControlExtension
  {
    #region Private members.

    private SimpleSceneControl sceneControl;
    private IEditorWinApplication application;

    private DBPtr<DBTypes.Texture> resource;

    #endregion

    #region Initialization.

    protected override bool Initialize(DBPtr<DBTypes.Texture> _resource, IEditorWinApplication _application)
    {
      resource = _resource;
      application = _application;
     
      try
      {
        SuspendLayout();
        TabText = GetTabText(_resource);

        sceneControl = new SimpleSceneControl(this,
                                              Application.Panels.GetSingletonPanel<PropertiesEditorPanel>(),
                                              Application.Application.Settings, null);
        sceneControl.ConfigSection = ConfigSection;
        sceneControl.Initialize(_application.Application);
        sceneControl.Substate = new MainState(this);

        sceneControl.Scene.SetTexture(_resource);

        Controls.Add(sceneControl);
        sceneControl.ShowGrid = true;
      }
      catch (Exception e)
      {
        Log.TraceError(e.Message);
        Log.TraceError("Native scene creation failed.");

        return false;
      }
      finally
      {
        ResumeLayout(true);
      }


      return true;
    }

    void OnDbResourceChanged(DBID dbid)
    {
      sceneControl.Scene.OnDbResourceChanged(dbid);
    }

    #endregion

    #region Overrides.

    protected override void OnActivateEditor()
    {
      EditorRender.SetFFTT(true);
      base.OnActivateEditor();
      DataBase.ChangeDBResourceEvent += OnDbResourceChanged;
      Application.Panels.GetSingletonPanel<PropertiesEditorPanel>().SelectedObject = resource.Get();
    }

    protected override void OnDeactivateEditor()
    {
      DataBase.ChangeDBResourceEvent -= OnDbResourceChanged;
      EditorRender.SetFFTT(false);
      base.OnDeactivateEditor();
    }

    #endregion

    #region Methods to override.

    public EditorSceneObject CreateSceneObject(DBPtr<DBTypes.Texture> _resource)
    {
      return new EditorSceneObject(_resource.DBId);
    }

    public string GetTabText(DBPtr<DBTypes.Texture> _resource)
    {
      return string.Format( "Texture {0}x{1}", _resource.Get().size.width, _resource.Get().size.height );
    }

    public string ConfigSection
    {
      get { return "Texture"; }
    }

    #endregion

    EditorNative.Manipulators.IObjectTransformControllersProvider ISceneControlExtension.TransformControllersProvider
    {
      get { return null; }
    }

    void ISceneControlExtension.AddBinds()
    {
    }

    public IEditorWinApplication Application
    {
      get { return application; }
    }

    public SimpleSceneControl SceneControl
    {
      get { return sceneControl; }
    }

    protected override sealed void OnClosed( EventArgs e )
    {
      base.OnClosed(e);
    }

    public event Operation ResourceChanged = null;

    public void CallResourceChanged()
    {
      if (ResourceChanged != null)
        ResourceChanged();
    }

    public DBID ResourceId
    {
      get { return resource.DBId; }
    }

    private sealed class MainState : State
    {
      private readonly TextureViewer viewer;

      internal MainState(TextureViewer viewer)
      {
        this.viewer = viewer;
      }

      public override void OnUpdate()
      {
      }
    }

    public BindsManager BindsManager
    {
      get { return Application.BindsManager; }
    }

    public string StatusLabel
    {
      set
      {
        application.StatusLabel = value;
      }
    }

  }

  [EditorAttribute("DxTex", false)]
  [ApplicableForDeriver]
  public sealed class DxTexViewer : Editor<DBTypes.Texture>
  {
    protected override sealed bool Initialize(DBPtr<DBTypes.Texture> resource, IEditorWinApplication editor) 
    {
      string texFileName = FileUtils.CopyFileToTemp(editor.Application.FileSystem, resource.Get().textureFileName);
      Process p = Process.Start("dxtex.exe", "\"" + texFileName + "\"");
      return true;
    }
    public override bool NeedWindow
    {
      get {return false;}
    }
  }
}




