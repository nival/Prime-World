namespace UnityUI
{
  public interface IFullscreen
  {
    bool IsInputEnabled { get; }
    void UpdateInput( bool enabled );
  }

  public static class DeployUtils
  {
    public static IFullscreen UIRoot { get; set; }

    public static void ReleaseUIRoot()
    {
      UIRoot = null;
    }
  }
}
