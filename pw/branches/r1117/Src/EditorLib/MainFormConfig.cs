using System;
using System.Drawing;
using System.Windows.Forms;
using EditorLib.Settings;
using System.IO;
using libdb.Diagnostics;
using WeifenLuo.WinFormsUI.Docking;
using System.Xml;

namespace EditorLib
{
  [ConfigObject( true )]
  public sealed class MainFormConfig : SimpleConfigObject
  {
  	public MonitorConfig oneMonitorConfig = new MonitorConfig();
		public MonitorConfig twoMonitorConfig = new MonitorConfig();

    public void ApplyToForm( Form form, DockPanel dockPanel, DeserializeDockContent deserializeDockContent )
    {
    	MonitorConfig monitorConfig = GetActualConfig();

			if ( !string.IsNullOrEmpty( monitorConfig.dockPanelConfig ) )
      {
				byte[] dockPanelData = System.Text.Encoding.UTF8.GetBytes( monitorConfig.dockPanelConfig );

        using(Stream dockPanelStream = new MemoryStream( dockPanelData, false ))
        {
					try
					{
						dockPanel.LoadFromXml( dockPanelStream, deserializeDockContent, true );
					}
					catch ( XmlException err )
					{
						Log.TraceWarning("Config Parsing Error: {0}", err.ToString());
					}        	
        }
      }

			if ( monitorConfig.Width > 0 && monitorConfig.Height > 0 && Enum.IsDefined( typeof( FormWindowState ), monitorConfig.State ) )
      {
        form.StartPosition = FormStartPosition.Manual;
				form.Location = new Point( monitorConfig.X, monitorConfig.Y );
				form.Width = monitorConfig.Width;
				form.Height = monitorConfig.Height;
				form.WindowState = monitorConfig.State;
      }
    }

    public void GetFromForm( Form form, DockPanel dockPanel )
    {
			MonitorConfig monitorConfig = GetActualConfig();

			monitorConfig.State = form.WindowState == FormWindowState.Minimized ? FormWindowState.Normal : form.WindowState;

      if ( form.WindowState != FormWindowState.Normal )
        SaveBoundsData( form.RestoreBounds, monitorConfig );
      else
        SaveBoundsData( form.Bounds, monitorConfig );

      using(Stream dockPanelStream = new MemoryStream())
      {
				dockPanel.SaveAsXml( dockPanelStream, System.Text.Encoding.UTF8, true );
				dockPanelStream.Seek( 0, SeekOrigin.Begin );

				using(StreamReader dockPanelStreamReader = new StreamReader( dockPanelStream, System.Text.Encoding.UTF8 ))
				{
					monitorConfig.dockPanelConfig = dockPanelStreamReader.ReadToEnd();	
				}

				dockPanelStream.Close();	
      }
    }

		private MonitorConfig GetActualConfig()
		{
			if ( IsTwoMonitors )
				return twoMonitorConfig;

			return oneMonitorConfig;
		}

		private static bool IsTwoMonitors
		{
			get
			{
				return Screen.AllScreens.Length > 1;	
			}
		}
		
		private static void SaveBoundsData( Rectangle bounds, MonitorConfig monitorConfig )
		{
			monitorConfig.X = bounds.X;
			monitorConfig.Y = bounds.Y;
			monitorConfig.Width = bounds.Width;
			monitorConfig.Height = bounds.Height;
		}
  }

	[Serializable]
	public sealed class MonitorConfig
	{
		public int Width = 0;
		public int Height = 0;
		public int X = 0;
		public int Y = 0;
		public FormWindowState State = FormWindowState.Normal;
		public string dockPanelConfig = string.Empty;
	}
}
