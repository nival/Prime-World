using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;
using libdb.Diagnostics;

namespace EditorLib.OutputPanel
{
	internal sealed class OutputTraceListener : IDumper
	{
		private readonly List<OutputMessage> messages = new List<OutputMessage>();
		private OutputPanel attachedPanel = null;

		private static void BeginInvoke<T1, T2>( Control control, Operation<T1, T2> operation, T1 param1, T2 param2 )
		{
			if ( control.InvokeRequired )
				control.BeginInvoke( operation, param1, param2 );
			else
				operation( param1, param2 );
		}

		public void Trace( Log.Level level, System.TimeSpan time, int threadId, string fileName, int lineNumber, string message )
		{
			lock ( messages )
			{
			  var msg = new OutputMessage( level, message );
				messages.Add( msg );
				if ( attachedPanel != null )
					BeginInvoke( attachedPanel, attachedPanel.Trace, msg, true );
			}
		}

		public void AttachPanel( OutputPanel panel )
		{
			lock ( messages )
			{
				attachedPanel = panel;
				foreach ( OutputMessage message in messages )
					attachedPanel.Trace( message, true );
			}
		}

		public void DetachPanel()
		{
			attachedPanel = null;
		}

		public void ResyncWithPanel()
		{
			if ( attachedPanel == null )
				return;

			lock ( messages )
			{
				foreach ( OutputMessage message in messages )
					attachedPanel.Trace( message, false );
			}
		}

		public void SaveToFile( string fileName )
		{
			lock ( messages )
			{
				using ( StreamWriter writer = new StreamWriter( new FileStream( fileName, FileMode.Create, FileAccess.Write ) ) )
				{
					foreach ( OutputMessage message in messages )
            writer.WriteLine( "[{0}]\t{1}\t{2}", message.level, message.time, message.message );
					writer.Flush();
					writer.Close();
				}
			}
		}

		public void Clear()
		{
			lock ( messages )
			{
				messages.Clear();
			}
		}
	}
}
