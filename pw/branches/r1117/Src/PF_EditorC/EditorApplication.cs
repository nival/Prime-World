using System.Reflection;
using System.Text;
using EditorPlugins;
using libdb.DB;

namespace PF_EditorC
{
	internal sealed class EditorApplication : EditorConApplication
	{
		private static EditorApplication application = new EditorApplication();
		public static EditorApplication Editor { get { return application; } }

		public override string ApplicationName { get { return "PF_Editor"; } }

		private string[] pluginsFileNames = new string[3] { "EditorLib.dll", "EditorPlugins.dll", "PF_EditorC.exe" };
		protected override string[] PluginsFileNames { get { return pluginsFileNames; } }

		private string[] typePluginsFileNames = new string[3] { "Types.DBTypes.dll", "PF_Types.DBTypes.dll", "SocialTypes.DBTypes.dll" };
		protected override string[] TypePluginsFileNames { get { return typePluginsFileNames; } }


    private string applicationVersion;

    public string ApplicationVersion
    {
      get
      {
        if( string.IsNullOrEmpty( applicationVersion ) )
        {
          StringBuilder result = new StringBuilder();
          AssemblyConfigurationAttribute config = TypeUtils.GetAttribute<AssemblyConfigurationAttribute>( Assembly.GetEntryAssembly(), false );
          if( config != null )
            result.AppendFormat( "-{0}", config.Configuration );
          AssemblyFileVersionAttribute version = TypeUtils.GetAttribute<AssemblyFileVersionAttribute>( Assembly.GetEntryAssembly(), false );
          if( version != null )
            result.AppendFormat( "-{0}", version.Version );

          applicationVersion = result.ToString();
        }

        return applicationVersion;
      }
    }
	}
}
