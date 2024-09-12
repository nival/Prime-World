using System;
using System.Collections.Generic;
using System.Text;
using EditorLib.Settings;

namespace EditorLib.OutputPanel
{
  [ConfigObject( true )]
  public class OutputPanelConfig : SimpleConfigObject
	{
		public bool infoButtonPressed = true;
		public bool warningButtonPressed = true;
		public bool errorButtonPressed = true;
	}
}
