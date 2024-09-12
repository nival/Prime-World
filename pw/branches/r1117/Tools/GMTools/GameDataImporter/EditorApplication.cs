using System;
using System.Reflection;
using System.Text;
using EditorLib;
using EditorLib.Operations;
using libdb.DB;

namespace GameDataImporter
{
  internal sealed class EditorApplication : EditorCommonApplication, IEditorConApplication
  {
    private static EditorApplication application = new EditorApplication();
    public static EditorApplication Editor { get { return application; } }

    public override string ApplicationName { get { return "GameDataImporter"; } }

    private string[] pluginsFileNames = new[] { "EditorLib.dll", "GameDataImporter.exe" };
    protected override string[] PluginsFileNames { get { return pluginsFileNames; } }

    private string[] typePluginsFileNames = new[] { "Types.DBTypes.dll", "PF_Types.DBTypes.dll", "SocialTypes.DBTypes.dll" };
    protected override string[] TypePluginsFileNames { get { return typePluginsFileNames; } }
    
    protected override void RegisterExtensions()
    {
      Extensions.RegisterExtensions(this);
    }

    protected override bool InitializeApplication(IOperationContext context)
    {
      return true;
    }

    protected override void TerminateApplication()
    {
    }

    private NoThreadExecutor operationExecutor = new NoThreadExecutor();

    public override Executor OperationExecutor
    {
      get { return operationExecutor; }
    }

    public IEditorCommonApplication Application
    {
      get { return this; }
    }

    private string applicationVersion;

    public string ApplicationVersion
    {
      get
      {
        if (string.IsNullOrEmpty(applicationVersion))
        {
          StringBuilder result = new StringBuilder();
          AssemblyConfigurationAttribute config = TypeUtils.GetAttribute<AssemblyConfigurationAttribute>(Assembly.GetEntryAssembly(), false);
          if (config != null)
            result.AppendFormat("-{0}", config.Configuration);
          AssemblyFileVersionAttribute version = TypeUtils.GetAttribute<AssemblyFileVersionAttribute>(Assembly.GetEntryAssembly(), false);
          if (version != null)
            result.AppendFormat("-{0}", version.Version);

          applicationVersion = result.ToString();
        }

        return applicationVersion;
      }
    }
  }
}