using System.Net.Mime;
using System.Reflection;
using System.Text;
using EditorLib;
using libdb.DB;
using EditorPlugins;
using EditorLib.Operations;

namespace PF_Editor
{
	internal sealed class EditorApplication : EditorWinApplication
	{
		internal EditorApplication()
		{
		}

		protected override string[] PluginsFileNames
		{
			get { return new string[] { "EditorLib.dll", "EditorPlugins.dll", "PF_Editor.exe" }; }
		}

		protected override string[] TypePluginsFileNames
		{
			get { return new string[] { "Types.DBTypes.dll", "PF_Types.DBTypes.dll", "SocialTypes.DBTypes.dll" }; }
		}

		public override string ApplicationName
		{
			get { return "PF_Editor"; }
		}

		public override string ApplicationTitle
		{
			get { return "Prime World Editor"; }
		}

		public override string IconAssembly
		{
			get { return "PF_TypeIcons.dll"; }
		}

    protected override bool InitializeApplication( IOperationContext context )
    {
      DataBase.LoadTypes( new string[] { "EditorLib.dll" } );
      return base.InitializeApplication( context );
    }

	  private string applicationVersion;

	  public string ApplicationVersion
	  {
	    get
	    {
        if(string.IsNullOrEmpty( applicationVersion ))
        {
          StringBuilder result = new StringBuilder();
          AssemblyConfigurationAttribute config = TypeUtils.GetAttribute<AssemblyConfigurationAttribute>( Assembly.GetEntryAssembly(), false );
          if( config != null )
            result.AppendFormat( "-{0}", config.Configuration );
          AssemblyFileVersionCustomAttribute version = TypeUtils.GetAttribute<AssemblyFileVersionCustomAttribute>(Assembly.GetEntryAssembly(), false);
          if( version != null )
            result.AppendFormat( "-{0}", version.Version );

          applicationVersion = result.ToString(); 
        }

	      return applicationVersion;
	    }
	  }
	}
}
