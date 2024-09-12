using System;
using System.Net.Sockets;
using log4net;
using River.Bot.Properties;
using River.Core;

namespace River.Bot
{
  public class AutoConnector
  {
    private System.Windows.Forms.Timer timer = null;
    private ClientBot bot = null;
    private bool botConnected = false;
    IMaster master = null;

    private static readonly ILog logger = LogManager.GetLogger(typeof (AutoConnector));

    public AutoConnector( ClientBot _bot )
    {
      bot = _bot;
      logger.DebugFormat("Init AutoConnector on bot {0}", _bot.Description);

      timer = new System.Windows.Forms.Timer();
      timer.Interval = Settings.Default.MasterCheckInterval;
      timer.Tick += OnTimerTick;
      timer.Enabled = true;

      CheckIfMasterAppeared();
    }

    public void OnTimerTick( object sender, EventArgs e )
    {
      if ( botConnected )
        CheckIfMasterDisconnected();
      else
        CheckIfMasterAppeared();
    }

    private void CheckIfMasterAppeared()
    {
      try
      {
        //logger.Trace("Bot {0}. Attempt to connect to master {1}", bot.Description, Settings.Default.masterUrl); // fixme: gimme a trace
        if ( master == null )
          master = Activator.GetObject( typeof( IMaster ), Settings.Default.masterUrl ) as IMaster;
        if (master == null)
        {
          //logger.Trace("Master object was not found"); // fixme: gimme a trace
          return;
        }
        try
        {
          master.Ping();
        }
        catch(SocketException ex)
        {
          //logger.TraceException("Failed to ping master.", ex); // fixme: gimme a trace
          return;
        }
        bot.Connect( Settings.Default.masterUrl );
        logger.InfoFormat("Bot {0} connected to master {1}", bot.Description.ToString(), Settings.Default.masterUrl);
        botConnected = true;
      }
      catch(Exception ex)
      {
        logger.Debug("Unexpected exception.", ex);
      }
    }

    private void CheckIfMasterDisconnected()
    {
      try
      {
        master.Ping();
      }
      catch(Exception ex)
      {
        logger.Debug("Failed to ping master.", ex);
        master = null;
        bot.MasterDisconnected();
        botConnected = false;
      }
    }

    ~AutoConnector()
    {
      ShutDown();
    }

    public void ShutDown()
    {
      if ( timer != null )
        timer.Enabled = false;
      timer = null;
      if ( botConnected )
        bot.Disconnect();
    }
  }
}
