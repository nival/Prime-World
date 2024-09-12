using PWLocalizator.Properties;

namespace PWLocalizator
{
	public static class UserSettings
	{
		public static string DataFolder 
		{
			get { return Settings.Default.DataFolder; }
			set 
			{ 
				Settings.Default.DataFolder = value; 
				Settings.Default.Save();
			}
		}
	}
}
