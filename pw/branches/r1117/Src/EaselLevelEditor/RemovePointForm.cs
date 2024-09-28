using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace EaselLevelEditor
{
  public partial class RemovePointForm : Form
  {
    public int Index
    {
      get { return pointIndex; }
    }

    private int pointIndex;

    public RemovePointForm()
    {
      InitializeComponent();
      pointIndex = 0;

      textIndex.Text = pointIndex.ToString();
    }

    public RemovePointForm(int _index)
    {
      InitializeComponent();

      pointIndex = _index;
      textIndex.Text = pointIndex.ToString();
    }

    private void btnOK_Click(object sender, EventArgs e)
    {
      pointIndex = System.Convert.ToInt32(textIndex.Text, 10);
      
      this.DialogResult = DialogResult.OK;
      this.Close();
    }
  }
}
