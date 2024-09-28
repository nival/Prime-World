using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Settings;

namespace libdb.DB
{
	public enum ConfigStorage
	{
		User = 0,
		Application = 1,
	}

	public class ConfigFile
	{
		private string fileName = string.Empty;
		private ConfigStorage storage = ConfigStorage.User;
		public static ConfigFile DefaultAppConfig;
		public static ConfigFile DefaultUserConfig;


		public ConfigFile( string fileName, ConfigStorage storage )
		{
			this.fileName = fileName;
			this.storage = storage;
		}

		public string FileName { get { return fileName; } }
		public ConfigStorage Storage { get { return storage; } }
		
		public override bool Equals( object obj )
		{
			ConfigFile cfg = obj as ConfigFile;
			if ( cfg == null )
				return false;

			return string.Compare( cfg.fileName, fileName, StringComparison.InvariantCultureIgnoreCase ) == 0 && cfg.storage == storage;
		}

		public override int GetHashCode()
		{
			return fileName.ToLower().GetHashCode() ^ storage.GetHashCode();
		}

		public bool IsMatch( ConfigObjectAttribute attribute )
		{
			if ( string.IsNullOrEmpty( attribute.FileName ) )
			{
				return ( !attribute.UserObject && this.Equals( DefaultAppConfig ) )
								|| ( attribute.UserObject && this.Equals( DefaultUserConfig ) );
			}
			else
			{
				return ( attribute.UserObject == ( storage == ConfigStorage.User ) )
							 && attribute.FileName == this.FileName;
			}
		}

		public bool IsMatch( ConfigObjectFieldAttribute attribute )
		{
			if( string.IsNullOrEmpty(attribute.FileName))
			{
				return (!attribute.UserObject && this.Equals( DefaultAppConfig )) 
								|| (attribute.UserObject && this.Equals( DefaultUserConfig ));
			}
			else
			{
				return (attribute.UserObject == (storage == ConfigStorage.User))
				       && attribute.FileName == this.FileName;
			}
		}
	}
}
