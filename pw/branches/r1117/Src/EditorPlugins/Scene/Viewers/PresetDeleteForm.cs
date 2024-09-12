using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace EditorPlugins.Scene.Viewers
{
  public partial class PresetDeleteForm : Form
  {
    public PresetDeleteForm( string name, bool isDelete )
    {
      InitializeComponent();
      if ( isDelete )
      {
        label1.Text = "Are you sure delete \"" + name + "\" preset?";
      }
      else
      {
        label1.Text = "This preset is already exist. Rewrite \"" + name + "\" preset?";
      }
      label1.Size = new System.Drawing.Size(135, 13);
    }
  }
}
