namespace EditorLib.PropertiesEditor.PropertyPresets
{
  partial class PresetConfigManager
  {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null))
      {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.buttonClose = new System.Windows.Forms.Button();
      this.listBoxPresets = new System.Windows.Forms.ListBox();
      this.buttonAdd = new System.Windows.Forms.Button();
      this.buttonDelete = new System.Windows.Forms.Button();
      this.buttonRename = new System.Windows.Forms.Button();
      this.textBoxEditName = new System.Windows.Forms.TextBox();
      this.buttonEdit = new System.Windows.Forms.Button();
      this.buttonCopy = new System.Windows.Forms.Button();
      this.SuspendLayout();
      // 
      // buttonClose
      // 
      this.buttonClose.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonClose.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.buttonClose.Location = new System.Drawing.Point( 285, 192 );
      this.buttonClose.Name = "buttonClose";
      this.buttonClose.Size = new System.Drawing.Size( 75, 23 );
      this.buttonClose.TabIndex = 0;
      this.buttonClose.Text = "Close";
      this.buttonClose.UseVisualStyleBackColor = true;
      this.buttonClose.Click += new System.EventHandler( this.buttonClose_Click );
      // 
      // listBoxPresets
      // 
      this.listBoxPresets.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.listBoxPresets.FormattingEnabled = true;
      this.listBoxPresets.Location = new System.Drawing.Point( 12, 12 );
      this.listBoxPresets.Name = "listBoxPresets";
      this.listBoxPresets.Size = new System.Drawing.Size( 267, 173 );
      this.listBoxPresets.TabIndex = 1;
      this.listBoxPresets.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler( this.listBoxPresets_MouseDoubleClick );
      this.listBoxPresets.SelectedIndexChanged += new System.EventHandler( this.listBoxPresets_SelectedIndexChanged );
      // 
      // buttonAdd
      // 
      this.buttonAdd.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonAdd.Location = new System.Drawing.Point( 285, 12 );
      this.buttonAdd.Name = "buttonAdd";
      this.buttonAdd.Size = new System.Drawing.Size( 75, 23 );
      this.buttonAdd.TabIndex = 2;
      this.buttonAdd.Text = "Add";
      this.buttonAdd.UseVisualStyleBackColor = true;
      this.buttonAdd.Click += new System.EventHandler( this.buttonAdd_Click );
      // 
      // buttonDelete
      // 
      this.buttonDelete.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonDelete.Enabled = false;
      this.buttonDelete.Location = new System.Drawing.Point( 285, 99 );
      this.buttonDelete.Name = "buttonDelete";
      this.buttonDelete.Size = new System.Drawing.Size( 75, 23 );
      this.buttonDelete.TabIndex = 4;
      this.buttonDelete.Text = "Delete";
      this.buttonDelete.UseVisualStyleBackColor = true;
      this.buttonDelete.Click += new System.EventHandler( this.buttonDelete_Click );
      // 
      // buttonRename
      // 
      this.buttonRename.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonRename.Enabled = false;
      this.buttonRename.Location = new System.Drawing.Point( 285, 41 );
      this.buttonRename.Name = "buttonRename";
      this.buttonRename.Size = new System.Drawing.Size( 75, 23 );
      this.buttonRename.TabIndex = 3;
      this.buttonRename.Text = "Rename";
      this.buttonRename.UseVisualStyleBackColor = true;
      this.buttonRename.Click += new System.EventHandler( this.buttonRename_Click );
      // 
      // textBoxEditName
      // 
      this.textBoxEditName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      this.textBoxEditName.Location = new System.Drawing.Point( -17, 131 );
      this.textBoxEditName.Name = "textBoxEditName";
      this.textBoxEditName.Size = new System.Drawing.Size( 242, 20 );
      this.textBoxEditName.TabIndex = 6;
      this.textBoxEditName.Visible = false;
      this.textBoxEditName.Leave += new System.EventHandler( this.textBoxEditName_Leave );
      this.textBoxEditName.KeyPress += new System.Windows.Forms.KeyPressEventHandler( this.textBoxEditName_KeyPress );
      // 
      // buttonEdit
      // 
      this.buttonEdit.Enabled = false;
      this.buttonEdit.Location = new System.Drawing.Point( 285, 70 );
      this.buttonEdit.Name = "buttonEdit";
      this.buttonEdit.Size = new System.Drawing.Size( 75, 23 );
      this.buttonEdit.TabIndex = 7;
      this.buttonEdit.Text = "Edit...";
      this.buttonEdit.UseVisualStyleBackColor = true;
      this.buttonEdit.Click += new System.EventHandler( this.buttonEdit_Click );
      // 
      // buttonCopy
      // 
      this.buttonCopy.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonCopy.Location = new System.Drawing.Point( 285, 131 );
      this.buttonCopy.Name = "buttonCopy";
      this.buttonCopy.Size = new System.Drawing.Size( 75, 23 );
      this.buttonCopy.TabIndex = 8;
      this.buttonCopy.Text = "Copy";
      this.buttonCopy.UseVisualStyleBackColor = true;
      this.buttonCopy.Click += new System.EventHandler( this.buttonCopy_Click );
      // 
      // PresetConfigManager
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.buttonClose;
      this.ClientSize = new System.Drawing.Size( 372, 227 );
      this.ControlBox = false;
      this.Controls.Add( this.buttonCopy );
      this.Controls.Add( this.buttonEdit );
      this.Controls.Add( this.textBoxEditName );
      this.Controls.Add( this.buttonRename );
      this.Controls.Add( this.buttonDelete );
      this.Controls.Add( this.buttonAdd );
      this.Controls.Add( this.listBoxPresets );
      this.Controls.Add( this.buttonClose );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = "PresetConfigManager";
      this.Text = "PresetConfigManager";
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button buttonClose;
    private System.Windows.Forms.ListBox listBoxPresets;
    private System.Windows.Forms.Button buttonAdd;
    private System.Windows.Forms.Button buttonDelete;
    private System.Windows.Forms.Button buttonRename;
    private System.Windows.Forms.TextBox textBoxEditName;
    private System.Windows.Forms.Button buttonEdit;
    private System.Windows.Forms.Button buttonCopy;
  }
}