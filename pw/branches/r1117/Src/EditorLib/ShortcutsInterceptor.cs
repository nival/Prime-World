using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using libdb.Diagnostics;
using System.Security.Permissions;
using EditorLib.Menu;

namespace EditorLib
{
	public class ShortcutsInterceptor : IMessageFilter
	{
		IEditorWinApplication application = null;
		public ShortcutsInterceptor( IEditorWinApplication _application )
		{
			application = _application;
		}
		[System.Runtime.InteropServices.DllImport( "user32", CharSet = System.Runtime.InteropServices.CharSet.Auto )]
		private static extern ushort GetKeyState( int nVirtKey );
		//private static ushort GetKeyState( int nVirtKey ){return Win32.User.GetKeyState(nVirtKey);}
		private const int WM_KEYDOWN = 0x100;
		private const int WM_KEYUP = 0x101;
		private const int WM_SYSKEYDOWN = 0x104;
		private const int WM_SYSKEYUP = 0x105;
		private const int KF_ALTDOWN = 0x20000000;
		private const int VK_CONTROL = 0x11;
		private const int VK_ALT = 0x12;
		private const int VK_SHIFT = 0x10;
		Dictionary<Keys, IEditorCommand> commands = new Dictionary<Keys, IEditorCommand>();
		public void RegisterShortcutCommand( IEditorCommand _command, Keys wantedHotkey )
		{
			if ( wantedHotkey != Keys.None )
				commands[wantedHotkey] = _command;

		}
		public bool PreFilterMessage( ref Message m )
		{
			// Blocks all the messages relating to the left mouse button.

			if ( m.Msg == WM_KEYDOWN || m.Msg == WM_SYSKEYDOWN )
			{
				//Log.TraceMessage( m.Msg.ToString() + ":" + m.WParam.ToString() + ";" + m.LParam.ToString() );
				switch ( m.WParam.ToInt32() )
				{
					/*case ((int)Keys.ControlKey):
						{
							isControl = true;
						} break;
					case ((int)Keys.Alt):
						{
							isAlt = true;
						} break;*/
					default:
						{
							Keys keys = Keys.None;

							if ( GetKeyState( VK_CONTROL ) >> 15 > 0 )
							{
								keys |= Keys.Control;
							}
							if ( GetKeyState( VK_ALT ) >> 15 > 0 )
							{
								keys |= Keys.Alt;
							}
							if ( GetKeyState( VK_SHIFT ) >> 15 > 0 )
							{
								keys |= Keys.Shift;
							}
							keys |= (Keys)m.WParam;
							if ( commands.ContainsKey( keys ) )
							{
								commands[keys].Execute( application );
                application.MainMenu.UpdateMenu();
								//Log.TraceMessage( keys.ToString() + ";" + GetKeyState( VK_SHIFT ) + ";" + GetKeyState( VK_ALT ) + ";" + GetKeyState( VK_CONTROL ) );
								return true;
							}

						} break;
				}
			}
			else if ( m.Msg == WM_KEYUP )
			{

			}
			return false;
		}
	}

}
