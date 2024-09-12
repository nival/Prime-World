using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using DBTypes;
using EditorLib;
using EditorLib.Binds;
using EditorNative;
using EditorNative.SceneElements;
using EditorNative.Terrain;
using EditorPlugins.Scene.Editors;
using PF_Editor.Map.AdvMapObjects;
using PF_EditorNative;
using libdb.DB;
using libdb.UndoRedo;

namespace PF_Editor
{
  public class PFEditorControl : EditorControl
  {
    private bool setScriptGroupNameOnce = false;

    public PFEditorControl(IEditorWinApplication application, IEditorControlExtension extension, DBTypes.Terrain terrain)
      : base(application, extension, terrain) 
    {
      EditorScene    scene = Scene;
      EditorTerrain  eter  = scene.SceneTerrain;
      eter.UpdateHeightsController();
    }

    #region Private members.

    private readonly EditorPassabilityMask editorPassabilityMask = new EditorPassabilityMask();
    
    #endregion
    
    public EditorPassabilityMask  ScenePassabilityMask
    {
      get
      {
        return editorPassabilityMask;
      }
    }
    
    // Just to test compiler
    void Test()
    {
      ScenePassabilityMask.AllocateScenePassabilityMask(116, 16, 2.6f);
    }

    public static DialogResult InputBox( string title, string promptText, ref string value )
    {
      Form form = new Form();
      Label label = new Label();
      TextBox textBox = new TextBox();
      Button buttonOk = new Button();
      Button buttonCancel = new Button();

      form.Text = title;
      label.Text = promptText;
      textBox.Text = value;

      buttonOk.Text = "OK";
      buttonCancel.Text = "Cancel";
      buttonOk.DialogResult = DialogResult.OK;
      buttonCancel.DialogResult = DialogResult.Cancel;

      label.SetBounds( 9, 20, 372, 13 );
      textBox.SetBounds( 12, 36, 372, 20 );
      buttonOk.SetBounds( 228, 72, 75, 23 );
      buttonCancel.SetBounds( 309, 72, 75, 23 );

      label.AutoSize = true;
      textBox.Anchor = textBox.Anchor | AnchorStyles.Right;
      buttonOk.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
      buttonCancel.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;

      form.ClientSize = new Size( 396, 107 );
      form.Controls.AddRange( new Control[] { label, textBox, buttonOk, buttonCancel } );
      form.ClientSize = new Size( Math.Max( 300, label.Right + 10 ), form.ClientSize.Height );
      form.FormBorderStyle = FormBorderStyle.FixedDialog;
      form.StartPosition = FormStartPosition.CenterScreen;
      form.MinimizeBox = false;
      form.MaximizeBox = false;
      form.AcceptButton = buttonOk;
      form.CancelButton = buttonCancel;

      DialogResult dialogResult = form.ShowDialog();
      value = textBox.Text;
      return dialogResult;
    }

    public override void SetScriptGroupName()
    {
      if ( setScriptGroupNameOnce ) return;
      setScriptGroupNameOnce = true;
      string scriptGroupName = "";
      if ( InputBox( "SetScriptGroupName", "ScriptGroupName:", ref scriptGroupName ) == DialogResult.OK )
      {
        DataBase.UndoRedoManager.Start( "SetScriptGroupName" );
        foreach ( SceneElement obj in Scene.SelectedObjects )
        {
          if ( obj is ControllableVisualObject )
          {
            if( (obj as ControllableVisualObject).Resource is AdvMapObject )
            {
              AdvMapObject advMapObj = ( obj as ControllableVisualObject ).Resource as AdvMapObject;
              advMapObj.scriptGroupName = scriptGroupName;
            }
          }
        }
        DataBase.UndoRedoManager.Commit();
      }
      setScriptGroupNameOnce = false;
    }

    
  }
}
