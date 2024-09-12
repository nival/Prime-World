using EditorLib;
using EditorLib.Menu;

namespace EditorPlugins.MipMapCommand
{
  public sealed class MipMapCommand : IEditorCommand
  {
    private bool mipMapsVisible = false;

    public override void Execute( IEditorWinApplication application )
    {
      EditorNative.EditorRender.ToggleMipMaps();
      PF_EditorNative.Utils.ResetRecolorableTextureCache();
      mipMapsVisible = !mipMapsVisible;
    }

    public override string Name
    {
      get { return "Show MipMaps"; }
    }

    public override bool IsChecked
    {
      get { return mipMapsVisible; }
    }
  }
}
