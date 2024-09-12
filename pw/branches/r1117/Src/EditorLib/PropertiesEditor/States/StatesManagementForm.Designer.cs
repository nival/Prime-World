namespace EditorLib.PropertiesEditor.States
{
  partial class StatesManagementForm
  {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose( bool disposing )
    {
      if ( disposing && ( components != null ) )
      {
        components.Dispose();
      }
      base.Dispose( disposing );
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.listBoxStates = new System.Windows.Forms.ListBox();
      this.buttonAdd = new System.Windows.Forms.Button();
      this.buttonDelete = new System.Windows.Forms.Button();
      this.buttonOk = new System.Windows.Forms.Button();
      this.buttonCancel = new System.Windows.Forms.Button();
      this.textBoxEditName = new System.Windows.Forms.TextBox();
      this.buttonRename = new System.Windows.Forms.Button();
      this.SuspendLayout();
      // 
      // listBoxStates
      // 
      this.listBoxStates.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.listBoxStates.FormattingEnabled = true;
      this.listBoxStates.Location = new System.Drawing.Point( 12, 12 );
      this.listBoxStates.Name = "listBoxStates";
      this.listBoxStates.Size = new System.Drawing.Size( 208, 238 );
      this.listBoxStates.TabIndex = 0;
      // 
      // buttonAdd
      // 
      this.buttonAdd.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonAdd.Location = new System.Drawing.Point( 226, 12 );
      this.buttonAdd.Name = "buttonAdd";
      this.buttonAdd.Size = new System.Drawing.Size( 75, 23 );
      this.buttonAdd.TabIndex = 1;
      this.buttonAdd.Text = "Add";
      this.buttonAdd.UseVisualStyleBackColor = true;
      this.buttonAdd.Click += new System.EventHandler( this.buttonAdd_Click );
      // 
      // buttonDelete
      // 
      this.buttonDelete.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonDelete.Location = new System.Drawing.Point( 226, 70 );
      this.buttonDelete.Name = "buttonDelete";
      this.buttonDelete.Size = new System.Drawing.Size( 75, 23 );
      this.buttonDelete.TabIndex = 2;
      this.buttonDelete.Text = "Delete";
      this.buttonDelete.UseVisualStyleBackColor = true;
      this.buttonDelete.Click += new System.EventHandler( this.buttonDelete_Click );
      // 
      // buttonOk
      // 
      this.buttonOk.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonOk.Location = new System.Drawing.Point( 226, 198 );
      this.buttonOk.Name = "buttonOk";
      this.buttonOk.Size = new System.Drawing.Size( 75, 23 );
      this.buttonOk.TabIndex = 3;
      this.buttonOk.Text = "OK";
      this.buttonOk.UseVisualStyleBackColor = true;
      this.buttonOk.Click += new System.EventHandler( this.buttonOk_Click );
      // 
      // buttonCancel
      // 
      this.buttonCancel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.buttonCancel.Location = new System.Drawing.Point( 226, 227 );
      this.buttonCancel.Name = "buttonCancel";
      this.buttonCancel.Size = new System.Drawing.Size( 75, 23 );
      this.buttonCancel.TabIndex = 4;
      this.buttonCancel.Text = "Cancel";
      this.buttonCancel.UseVisualStyleBackColor = true;
      this.buttonCancel.Click += new System.EventHandler( this.buttonCancel_Click );
      // 
      // textBoxEditName
      // 
      this.textBoxEditName.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      this.textBoxEditName.Location = new System.Drawing.Point( 35, 120 );
      this.textBoxEditName.Name = "textBoxEditName";
      this.textBoxEditName.Size = new System.Drawing.Size( 208, 20 );
      this.textBoxEditName.TabIndex = 7;
      this.textBoxEditName.Visible = false;
      this.textBoxEditName.Leave += new System.EventHandler( this.textBoxEditName_Leave );
      this.textBoxEditName.KeyPress += new System.Windows.Forms.KeyPressEventHandler( this.textBoxEditName_KeyPress );
      // 
      // buttonRename
      // 
      this.buttonRename.Location = new System.Drawing.Point( 226, 41 );
      this.buttonRename.Name = "buttonRename";
      this.buttonRename.Size = new System.Drawing.Size( 75, 23 );
      this.buttonRename.TabIndex = 8;
      this.buttonRename.Text = "Rename";
      this.buttonRename.UseVisualStyleBackColor = true;
      this.buttonRename.Click += new System.EventHandler( this.buttonRename_Click );
      // 
      // StatesManagementForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.buttonCancel;
      this.ClientSize = new System.Drawing.Size( 313, 260 );
      this.Controls.Add( this.buttonRename );
      this.Controls.Add( this.textBoxEditName );
      this.Controls.Add( this.buttonCancel );
      this.Controls.Add( this.buttonOk );
      this.Controls.Add( this.buttonDelete );
      this.Controls.Add( this.buttonAdd );
      this.Controls.Add( this.listBoxStates );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
      this.Name = "StatesManagementForm";
      this.ShowInTaskbar = false;
      this.Text = "Manage States";
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.ListBox listBoxStates;
    private System.Windows.Forms.Button buttonAdd;
    private System.Windows.Forms.Button buttonDelete;
    private System.Windows.Forms.Button buttonOk;
    private System.Windows.Forms.Button buttonCancel;
    private System.Windows.Forms.TextBox textBoxEditName;
    private System.Windows.Forms.Button buttonRename;
  }
}