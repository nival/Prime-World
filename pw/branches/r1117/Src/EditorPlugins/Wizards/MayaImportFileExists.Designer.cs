namespace EditorPlugins.Wizards
{
  partial class MayaImportFileExists
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
      this.buttonUpdate = new System.Windows.Forms.Button();
      this.buttonCancel = new System.Windows.Forms.Button();
      this.radioButtonSOBJ = new System.Windows.Forms.RadioButton();
      this.radioButtonPRXY = new System.Windows.Forms.RadioButton();
      this.labelText = new System.Windows.Forms.Label();
      this.SuspendLayout();
      // 
      // buttonUpdate
      // 
      this.buttonUpdate.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.buttonUpdate.Location = new System.Drawing.Point( 140, 91 );
      this.buttonUpdate.Name = "buttonUpdate";
      this.buttonUpdate.Size = new System.Drawing.Size( 75, 23 );
      this.buttonUpdate.TabIndex = 0;
      this.buttonUpdate.Text = "Update";
      this.buttonUpdate.UseVisualStyleBackColor = true;
      // 
      // buttonCancel
      // 
      this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.buttonCancel.Location = new System.Drawing.Point( 254, 91 );
      this.buttonCancel.Name = "buttonCancel";
      this.buttonCancel.Size = new System.Drawing.Size( 75, 23 );
      this.buttonCancel.TabIndex = 1;
      this.buttonCancel.Text = "Cancel";
      this.buttonCancel.UseVisualStyleBackColor = true;
      // 
      // radioButtonSOBJ
      // 
      this.radioButtonSOBJ.AutoSize = true;
      this.radioButtonSOBJ.Enabled = false;
      this.radioButtonSOBJ.Location = new System.Drawing.Point( 15, 38 );
      this.radioButtonSOBJ.Name = "radioButtonSOBJ";
      this.radioButtonSOBJ.Size = new System.Drawing.Size( 58, 17 );
      this.radioButtonSOBJ.TabIndex = 2;
      this.radioButtonSOBJ.TabStop = true;
      this.radioButtonSOBJ.Text = "SOBJ: ";
      this.radioButtonSOBJ.UseVisualStyleBackColor = true;
      this.radioButtonSOBJ.CheckedChanged += new System.EventHandler( this.radioButtonSOBJ_CheckedChanged );
      // 
      // radioButtonPRXY
      // 
      this.radioButtonPRXY.AutoSize = true;
      this.radioButtonPRXY.Enabled = false;
      this.radioButtonPRXY.Location = new System.Drawing.Point( 15, 61 );
      this.radioButtonPRXY.Name = "radioButtonPRXY";
      this.radioButtonPRXY.Size = new System.Drawing.Size( 60, 17 );
      this.radioButtonPRXY.TabIndex = 3;
      this.radioButtonPRXY.TabStop = true;
      this.radioButtonPRXY.Text = "PRXY: ";
      this.radioButtonPRXY.UseVisualStyleBackColor = true;
      this.radioButtonPRXY.CheckedChanged += new System.EventHandler( this.radioButtonPRXY_CheckedChanged );
      // 
      // labelText
      // 
      this.labelText.AutoSize = true;
      this.labelText.Location = new System.Drawing.Point( 12, 9 );
      this.labelText.Name = "labelText";
      this.labelText.Size = new System.Drawing.Size( 273, 13 );
      this.labelText.TabIndex = 4;
      this.labelText.Text = "Target object(s) already exist. Update from Maya scene?";
      // 
      // MayaImportFileExists
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.buttonCancel;
      this.ClientSize = new System.Drawing.Size( 468, 126 );
      this.ControlBox = false;
      this.Controls.Add( this.labelText );
      this.Controls.Add( this.radioButtonPRXY );
      this.Controls.Add( this.radioButtonSOBJ );
      this.Controls.Add( this.buttonCancel );
      this.Controls.Add( this.buttonUpdate );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = "MayaImportFileExists";
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.Text = "Target File Already Exists";
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button buttonUpdate;
    private System.Windows.Forms.Button buttonCancel;
    private System.Windows.Forms.RadioButton radioButtonSOBJ;
    private System.Windows.Forms.RadioButton radioButtonPRXY;
    private System.Windows.Forms.Label labelText;
  }
}