using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using libdb.DB;

namespace EditorPlugins.Wizards
{
  public partial class MayaImportFileExists : Form
  {
    private DBResource finalTarget = null;
    public DBResource Target { get { return finalTarget; } }
    private DBTypes.DBSceneObject targetSceneObject = null;
    private DBTypes.DBSceneComponent targetProxy = null;

    public MayaImportFileExists( DBTypes.DBSceneObject _targetSceneObject, DBTypes.DBSceneComponent _targetProxy )
    {
      InitializeComponent();

      targetProxy = _targetProxy;
      targetSceneObject = _targetSceneObject;

      if ( null != targetProxy )
      {
        radioButtonPRXY.Enabled = true;
        radioButtonPRXY.Checked = true;
        radioButtonPRXY.Text += targetProxy.DBId.FileName;
      }
      if ( null != targetSceneObject )
      {
        radioButtonSOBJ.Enabled = true;
        radioButtonSOBJ.Checked = true;
        radioButtonSOBJ.Text += targetSceneObject.DBId.FileName;
      }
    }

    private void radioButtonSOBJ_CheckedChanged( object sender, EventArgs e )
    {
      if ( radioButtonSOBJ.Checked )
      {
        finalTarget = targetSceneObject;
      }
    }

    private void radioButtonPRXY_CheckedChanged( object sender, EventArgs e )
    {
      if ( radioButtonPRXY.Checked )
      {
        finalTarget = targetProxy;
      }
    }
  }
}
