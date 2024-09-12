using System;
using System.Collections.Generic;
using libdb.Diagnostics;
using System.IO;
using System.Reflection;
using System.Text;
using System.Xml;
using libdb.IO;
using libdb.DB;

namespace EditorLib.Settings
{
	public sealed class SettingsManager
	{
		private readonly string appSettingsFolder = string.Empty;
		private readonly string userSettingsFolder = string.Empty;
		private readonly Dictionary<Type, IConfigObject> configs = new Dictionary<Type, IConfigObject>();
    private readonly Dictionary<Type, bool> configLoaded = new Dictionary<Type, bool>();

		private readonly Dictionary<string, Dictionary<ConfigFile, XmlNode>> configNodes =
			new Dictionary<string, Dictionary<ConfigFile, XmlNode>>();
		private readonly Dictionary<ConfigFile, bool> configFiles = new Dictionary<ConfigFile, bool>();
		private readonly ConfigFile defaultAppConfig = null;
		private readonly ConfigFile defaultUserConfig = null;
		private bool resetUserConfiguration = false;
		

		public SettingsManager( string applicationName )
		{
			appSettingsFolder = Path.GetFullPath( "..\\Profiles\\" );
			userSettingsFolder = Path.Combine( Environment.GetFolderPath( Environment.SpecialFolder.ApplicationData ), applicationName );
			
			defaultAppConfig = new ConfigFile( applicationName, ConfigStorage.Application );
			defaultUserConfig = new ConfigFile( "UserSettings", ConfigStorage.User );
			configFiles.Add( defaultAppConfig, true );
			configFiles.Add( defaultUserConfig, true );
			ConfigFile.DefaultAppConfig = defaultAppConfig;
			ConfigFile.DefaultUserConfig = defaultUserConfig;
		}

		private int ExtractTypeFromNode( XmlNode configNode, out string type )
		{
			type = string.Empty;

			try
			{
				XmlAttribute typeAttr;
				if ( ( typeAttr = configNode.Attributes["FullType"] ) != null )
          type = typeAttr.Value;
        else
        {
          Log.TraceWarning( "Cannot load configuration node \"{0}\". \"FullType\" attribute not defined", configNode.Name );
          return -1;
        }

				XmlAttribute versionAttr = configNode.Attributes["Version"];
				int version = 0;
				if ( versionAttr != null )
					int.TryParse( versionAttr.Value, out version );

				return Math.Max( 0, version );
			}
			catch ( Exception e )
			{
        Log.TraceWarning( "Cannot load configuration node \"{0}\". Exception {1}: {2}", configNode.Name, e.ToString(), e.Message );
				return -1;
			}
		}

		private string ResolveConfigFilename( ConfigFile file )
		{
			if ( file.Storage == ConfigStorage.Application )
				return Path.Combine( appSettingsFolder, file.FileName + ".config" );
			else
				return Path.Combine( userSettingsFolder, file.FileName + ".config" );
		}

    private void LoadConfiguration( ConfigFile file, ref Dictionary<string, int> versions )
		{
			string fileName = ResolveConfigFilename( file );
			if ( !File.Exists( fileName ) )
				return;

			try
			{
				XmlDocument configDoc = new XmlDocument();
				FileStream configFile = new FileStream( Path.GetFullPath( fileName ), FileMode.Open, FileAccess.Read );
				configDoc.Load( configFile );
				configFile.Close();

				foreach ( XmlNode configNode in configDoc.SelectNodes( "/Settings/*" ) )
				{
					string configType;
					int configVersion = ExtractTypeFromNode( configNode, out configType );
					if ( configType == null )
						continue;

					int existingVersion = 0;
					if ( versions.TryGetValue( configType, out existingVersion ) && existingVersion > configVersion )
						continue;

					if ( !configNodes.ContainsKey( configType ) )
						configNodes.Add( configType, new Dictionary<ConfigFile,XmlNode>() );
          configNodes[configType][file] = configNode;
				  versions[configType] = configVersion;
				}
			}
			catch ( Exception e )
			{
				Log.TraceWarning( "Cannot load settings from file \"{0}\". Exception {1}: {2}", fileName, e.ToString(), e.Message );
			}
		}

		// reading configuration
		public void Load()
		{
			// versions of loaded objects
      Dictionary<string, int> versions = new Dictionary<string, int>();
			List<ConfigFile> appConfigFiles = new List<ConfigFile>();
			List<ConfigFile> userConfigFiles = new List<ConfigFile>();
			foreach ( var configFile in configFiles.Keys )
			{
				if ( configFile.Storage == ConfigStorage.Application )
					appConfigFiles.Add( configFile );
				else
					userConfigFiles.Add( configFile );
			}
			appConfigFiles.Sort( (  a,  b ) =>  string.Compare( a.FileName, b.FileName, StringComparison.InvariantCultureIgnoreCase )  );
			userConfigFiles.Sort( (  a,  b ) =>   string.Compare( a.FileName, b.FileName, StringComparison.InvariantCultureIgnoreCase )  );

			foreach ( var configFile in appConfigFiles )
        LoadConfiguration( configFile, ref versions );

			foreach ( var configFile in userConfigFiles )
        LoadConfiguration( configFile, ref versions );
		}

		// store configuration
		private void StoreConfiguration( ConfigFile file )
		{
      XmlWriterSettings xmlSettings = new XmlWriterSettings() { ConformanceLevel = ConformanceLevel.Auto, Encoding = Encoding.UTF8, Indent = true, IndentChars = "  ", NewLineOnAttributes = false, OmitXmlDeclaration = true };

			StringBuilder contentString = new StringBuilder();
			XmlWriter contentWriter = XmlWriter.Create( contentString, xmlSettings );
			contentWriter.WriteStartElement( "Settings" );

      List<IConfigObject> outList = new List<IConfigObject>();

			foreach ( IConfigObject config in configs.Values )
			{
        if ( configLoaded[config.GetType()] || !configNodes.ContainsKey( config.GetType().FullName ) )
        {
					var configAttr = TypeUtils.GetAttribute<ConfigObjectAttribute>( config.GetType(), false );
					if ( configAttr == null )
						continue;

					if( config is SimpleConfigObject && !file.IsMatch(configAttr))
					{
						bool canSerizalize = false;
						foreach ( var memb in config.GetType().GetMembers() )
							if (  memb.MemberType == MemberTypes.Property || memb.MemberType == MemberTypes.Field )
							{
								var mattr= TypeUtils.GetAttribute<ConfigObjectFieldAttribute>( memb, false );
								if(mattr!=null && file.IsMatch(mattr))
								{
									canSerizalize = true;
									break;
								}
							}
						
						if ( !canSerizalize )
							continue;
					}
					else if ( !file.IsMatch( configAttr ) )
						continue;
        }

        outList.Add( config );
			}

      outList.Sort( ( x, y ) => { return string.Compare( x.GetType().FullName, y.GetType().FullName ); } );

      foreach ( IConfigObject config in outList )
      {
        if ( configLoaded[config.GetType()] || !configNodes.ContainsKey( config.GetType().FullName ) )
        {
          var configAttr = TypeUtils.GetAttribute<ConfigObjectAttribute>( config.GetType(), false );
          StringBuilder xmlString = new StringBuilder();
          XmlWriter xmlWriter = XmlWriter.Create( xmlString, xmlSettings );
          config.Serialize( xmlWriter, file );
          xmlWriter.Close();

          if ( xmlString.Length > 0 )
          {
            XmlDocument configNode = new XmlDocument();
            configNode.LoadXml( xmlString.ToString() );
            configNode.FirstChild.Attributes.RemoveAll();
            configNode.FirstChild.Attributes.Append( configNode.CreateAttribute( "Type" ) ).Value = config.GetType().Name;
            configNode.FirstChild.Attributes.Append( configNode.CreateAttribute( "FullType" ) ).Value = config.GetType().FullName;

            if ( configAttr.Version > 0 )
              configNode.FirstChild.Attributes.Append( configNode.CreateAttribute( "Version" ) ).Value = configAttr.Version.ToString();

            configNode.WriteContentTo( contentWriter );
          }
        }
        else
        {
          Dictionary<ConfigFile, XmlNode> nodes = null;
          XmlNode xmlNode = null;
          if ( configNodes.TryGetValue( config.GetType().FullName, out nodes ) )
            if ( nodes.TryGetValue( file, out xmlNode ) )
              contentWriter.WriteNode( new XmlNodeReader( xmlNode ), true );
        }
      }


			contentWriter.WriteEndElement();
			contentWriter.Close();

			XmlDocument configDoc = new XmlDocument();
			configDoc.LoadXml( contentString.ToString() );
			string fileName = ResolveConfigFilename( file );
			Directory.CreateDirectory( Path.GetDirectoryName( fileName ) );
			FileStream configFile = new FileStream( fileName, FileMode.Create, FileAccess.Write );
			configDoc.Save( configFile );
			configFile.Close();
		}

		public void Terminate()
		{
			List<ConfigFile> appConfigFiles = new List<ConfigFile>();
			List<ConfigFile> userConfigFiles = new List<ConfigFile>();
			foreach ( var configFile in configFiles.Keys )
			{
				if ( configFile.Storage == ConfigStorage.Application )
					appConfigFiles.Add( configFile );
				else
					userConfigFiles.Add( configFile );
			}

			appConfigFiles.Sort( (  a,  b ) => string.Compare( a.FileName, b.FileName, StringComparison.InvariantCultureIgnoreCase ) );
			userConfigFiles.Sort( ( a,  b ) => string.Compare( a.FileName, b.FileName, StringComparison.InvariantCultureIgnoreCase ) );

			foreach ( var configFile in appConfigFiles )
				StoreConfiguration( configFile );

			foreach ( var configFile in userConfigFiles )
			{
				if ( !ResetUserConfiguration )
					StoreConfiguration( configFile );
				else
				{
					string fileName = ResolveConfigFilename( configFile );
					if ( File.Exists( fileName ) )
						File.Delete( fileName );
				}
			}
		}

		public bool ResetUserConfiguration { get { return resetUserConfiguration; } set { resetUserConfiguration = value; } }

		/// <summary>
		/// Get configuration object of specified type. Object will created automaticly if doesn't registred
		/// </summary>
		public T Get<T>() where T : class, IConfigObject, new()
		{
			return Get( typeof( T ) ) as T;
		}

    public IConfigObject Get( Type type )
    {
      IConfigObject result = null;
      if ( !configs.TryGetValue( type, out result ) )
      {
        RegisterConfigObject( type );
        if ( !configs.TryGetValue( type, out result ) || result == null )
          return null;
      }

			if ( !configLoaded[type] && configNodes.ContainsKey(type.FullName) )
      {
				foreach ( var node in configNodes[type.FullName].Values )
					configLoaded[type] |= result.Deserialize( new XmlNodeReader(node) );
      }

			return result;
    }

		/// <summary>
		/// Get configuration object of specified type. Object will created automaticly if doesn't registred. Also this function can be used for
		/// register default instancies for configuration objects
		/// </summary>
		public void RegisterConfigObject( Type configObjectType )
		{
			if ( configObjectType.IsAbstract || configs.ContainsKey( configObjectType ) )
				return;

			ConstructorInfo constructor = configObjectType.GetConstructor( Type.EmptyTypes );
			if ( Log.Assert( constructor != null, "Cannot find default constructor for configuration object \"{0}\"",
			                 configObjectType.FullName ) )
				return;

			ConfigObjectAttribute configAttr = TypeUtils.GetAttribute<ConfigObjectAttribute>( configObjectType, false );
			if ( Log.Assert( configAttr != null, "Cannot register configuration object \"{0}\" without \"{1}\" attribute",
			                 configObjectType.FullName, typeof (ConfigObjectAttribute).Name ) )
				return;

			if ( !string.IsNullOrEmpty( configAttr.FileName ) )
			{
				ConfigFile configFile = new ConfigFile( configAttr.FileName,
				                                        configAttr.UserObject ? ConfigStorage.User : ConfigStorage.Application );
				if ( !configFiles.ContainsKey( configFile ) )
					configFiles.Add( configFile, true );
			}

			foreach (var memb in configObjectType.GetMembers( ))
			{
				if ( memb.MemberType != MemberTypes.Field && memb.MemberType != MemberTypes.Property )
					continue;

				var memAttr = TypeUtils.GetAttribute<ConfigObjectFieldAttribute>( memb, false );
				if ( memAttr == null || string.IsNullOrEmpty( memAttr.FileName ) )
					continue;

				var mconfigFile = new ConfigFile( memAttr.FileName,
				                                  memAttr.UserObject ? ConfigStorage.User : ConfigStorage.Application );
				if ( !configFiles.ContainsKey( mconfigFile ) )
					configFiles.Add( mconfigFile, true );
			}


			configs.Add( configObjectType, TypeUtils.CreateObject( configObjectType ) as IConfigObject );
			configLoaded.Add( configObjectType, false );
		}
	}
}
