using System;
using System.Drawing;
using System.IO;
using System.Net.Sockets;
using System.Reflection;
using System.Runtime.Remoting;
using System.Windows.Forms;
using log4net;
using log4net.Config;
using River.Bot.Properties;
using River.Core;

namespace River.Bot
{
	static class Program
	{
		private static NotifyIcon icon;
		private static ClientBot bot;
		private static OptionsForm optionsForm;

    private static AutoConnector connector = null;

    private static Guid lastSuiteID = Guid.Empty;

    private static readonly ILog logger = LogManager.GetLogger(typeof(Program));


		private static NotifyIcon CreateNotifyIcon()
		{
      XmlConfigurator.Configure();
			NotifyIcon result = new NotifyIcon();
			result.Icon = Resources.Offline;
			result.Text = "River.Bot";
			result.ContextMenuStrip = new ContextMenuStrip();
			result.ContextMenuStrip.Items.Add( "Show Console" ).Enabled = false;
			result.ContextMenuStrip.Items.Add( "Run Suite...", null, OnRunSuite ).Font = new Font( result.ContextMenuStrip.Font, FontStyle.Bold );
      result.ContextMenuStrip.Items.Add( "Halt Execution", null, OnHaltSuite );
			result.ContextMenuStrip.Items.Add( "Options...", null, OnShowOptions ).Enabled = false;
			result.ContextMenuStrip.Items.Add( new ToolStripSeparator() );
			result.ContextMenuStrip.Items.Add( "Online", null, OnOnline ).Image = Resources.Online.ToBitmap();
			result.ContextMenuStrip.Items.Add( "Offline", null, OnOffline ).Image = Resources.Offline.ToBitmap();
			result.ContextMenuStrip.Items.Add( new ToolStripSeparator() );
			result.ContextMenuStrip.Items.Add( "About..." ).Enabled = false;
			result.ContextMenuStrip.Items.Add( new ToolStripSeparator() );
			result.ContextMenuStrip.Items.Add( "Exit", null, OnExit );

			result.Visible = true;
			return result;
		}

		private static void OnRunSuite( object sender, EventArgs e )
		{
			OpenFileDialog dialog = new OpenFileDialog()
			{
				AutoUpgradeEnabled = true,
				CheckFileExists = true,
				Filter = "C# Code (*.cs)|*cs",
				FilterIndex = 0,
				Multiselect = false,
				RestoreDirectory = true,
				Title = "Select Source Code for Suite"
			};

			if ( dialog.ShowDialog() == DialogResult.OK )
			{
        lastSuiteID = Guid.NewGuid();
				bot.ExecuteSuite(Path.GetFileName(dialog.FileName), File.ReadAllText( dialog.FileName ), lastSuiteID );
			}
		}

 		private static void OnHaltSuite( object sender, EventArgs e )
    {
      if ( lastSuiteID == Guid.Empty )
        return;

      try
      {
        IMaster master = Activator.GetObject( typeof( IMaster ), Settings.Default.masterUrl ) as IMaster;
        master.HaltSuite( lastSuiteID );
      }
      catch ( Exception ex )
      {
        MessageBox.Show( ex.Message, ex.GetType().Name, MessageBoxButtons.OK, MessageBoxIcon.Error );
      }
    }


		private static void OnShowOptions( object sender, EventArgs e )
		{
			if ( optionsForm != null )
			{
				optionsForm.Activate();
			}
			else
			{
				optionsForm = new OptionsForm( Settings.Default.masterUrl );
				if ( optionsForm.ShowDialog() == DialogResult.OK )
				{
					bot.Disconnect();
          //Settings.Default.masterUrl = optionsForm.MasterUrl;
          bot.Connect( Settings.Default.masterUrl );
				}
				optionsForm = null;
			}
		}

		private static void OnOnline( object sender, EventArgs e )
		{
      icon.Icon = Resources.Connecting;
      connector = new AutoConnector(bot);
    }

		private static void OnOffline( object sender, EventArgs e )
		{
      connector.ShutDown();
      connector = null;
      icon.Icon = Resources.Offline;
		}

		private static void OnExit( object sender, EventArgs e )
		{
      bot.Halt();
      logger.InfoFormat("Exit bot {0}", bot.Description);
      Application.Exit();
		}

		private static void OnBotStatusChanged( ClientBot bot, ClientBot.BotStatus status, string statusMessage )
		{
			if ( status == ClientBot.BotStatus.Online )
			{
				icon.Icon = Resources.Online;
			}
			else
			{
				icon.Icon = connector == null ? Resources.Offline : Resources.Connecting;
			}
			icon.Text = statusMessage.Length > 63 ? statusMessage.Substring( 0, 62 ) + "…" : statusMessage;
		}

    private static void RunSuite( string fileName )
    {
      try
      {
        IMaster master = Activator.GetObject( typeof( IMaster ), Settings.Default.masterUrl ) as IMaster;
        lastSuiteID = Guid.NewGuid();
        master.ExecuteSuite(Path.GetFileName(fileName), null, File.ReadAllText(fileName), lastSuiteID, null, null);
      }
      catch ( Exception e )
      {
        MessageBox.Show( e.Message, e.GetType().Name, MessageBoxButtons.OK, MessageBoxIcon.Error );
      }
    }

		[STAThread]
    static void Main( string[] args )
		{
      logger.Info("Bot started");
      RemotingConfiguration.Configure( Path.GetFileName( Assembly.GetEntryAssembly().Location ) + ".config", false );

      if (args.Length == 1 && args[0].ToLower() == "--help")
      {
        MessageBox.Show(GetHelp(), "Help", MessageBoxButtons.OK, MessageBoxIcon.Information);
      }
      else if ( args.Length == 1 && args[0].ToLower() != "--connect" )
      {
        RunSuite( args[0] );
      }
      else
      {
        Application.EnableVisualStyles();
        Application.SetCompatibleTextRenderingDefault( false );

        icon = CreateNotifyIcon();
        bot = new ClientBot();
        bot.OnBotStatusChanged += OnBotStatusChanged;

        try
        {
          if (args.Length == 1 && args[0].ToLower() == "--connect")
          {
            icon.Icon = Resources.Connecting;
            connector = new AutoConnector(bot);
          }

          Application.Run();
        }
        catch (SocketException ex)
        {
          MessageBox.Show(ex.Message, "Ошибка соединения", MessageBoxButtons.OK, MessageBoxIcon.Error);
          logger.Error("Ошибка соединения", ex);
        }
        catch (Exception ex)
        {
          MessageBox.Show(ex.Message, "Exception", MessageBoxButtons.OK, MessageBoxIcon.Error);
          logger.Fatal("Unhandled exception", ex);
        }

        icon.Visible = false;
      }
    }

    private static string GetHelp()
    {
      var sb = new System.Text.StringBuilder();
      sb.AppendLine("Использование River.Bot:");
      sb.AppendLine(" river.bot --connect|--help|<scenario>\n");
      sb.AppendFormat(" {0,-15} - Запуск бота с автоматическим коннектом к мастеру\n", "--connect");
      sb.AppendFormat(" {0,-19} - Справка.\n", "--help");
      sb.AppendFormat(" {0,-14} - Запуск сценария на мастере.\n", "<scenario>");
      return sb.ToString();
    }
  }
}
