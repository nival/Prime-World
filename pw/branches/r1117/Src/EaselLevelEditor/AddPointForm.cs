using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace EaselLevelEditor
{
  public partial class AddPointForm : Form
  {
    #region Properties
    public int X
    {
      get { return xCoord; }
    }

    public int Y
    {
      get { return yCoord; }
    }

    public int Index
    {
      get { return index; }
    }
    
    #endregion

    private int xCoord;
    private int yCoord;
    private int index;

    #region constructors
    public AddPointForm()
    {
      InitializeComponent();

      xCoord = 0;
      yCoord = 0;
      index = 0;

      ShowTexts();
    }

    public AddPointForm(int _xCoord,int _yCoord)
    {
      InitializeComponent();

      index  = 0;
      xCoord = _xCoord;
      yCoord = _yCoord;

      ShowTexts();
    }

    public AddPointForm(int _xCoord,int _yCoord,int _index)
    {
      InitializeComponent();

      index  = _index;
      xCoord = _xCoord;
      yCoord = _yCoord;

      ShowTexts();
    }

    private void ShowTexts()
    {
      textPointIndex.Text = index.ToString();
      textPointXCoord.Text = xCoord.ToString();
      textPointYCoord.Text = yCoord.ToString();
    }
    
    #endregion

    private void btnAddPoint_Click(object sender, EventArgs e)
    {
      xCoord = System.Convert.ToInt32(textPointXCoord.Text, 10);
      yCoord = System.Convert.ToInt32(textPointYCoord.Text, 10);
      index = System.Convert.ToInt32(textPointIndex.Text, 10);

      this.DialogResult = DialogResult.OK;
      this.Close();
    }
  }
}
