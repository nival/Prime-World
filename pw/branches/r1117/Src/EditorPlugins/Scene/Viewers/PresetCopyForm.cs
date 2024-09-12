using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace EditorPlugins.Scene.Viewers
{
  public partial class PresetCopyForm : Form
  {
    public string textString = string.Empty;

    public PresetCopyForm()
    {
      InitializeComponent();
    }

    private void textBox1_TextChanged(object sender, EventArgs e)
    {
      textString = (sender as TextBox).Text;
    }
  }
}
