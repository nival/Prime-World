namespace EditorLib.ObjectsBrowser
{
  partial class ChangeTypeForm
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
      this.buttonOk = new System.Windows.Forms.Button();
      this.buttonCancel = new System.Windows.Forms.Button();
      this.listBoxTypes = new System.Windows.Forms.ListBox();
      this.tbSearch = new System.Windows.Forms.TextBox();
      this.SuspendLayout();
      // 
      // buttonOk
      // 
      this.buttonOk.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
      this.buttonOk.Enabled = false;
      this.buttonOk.Location = new System.Drawing.Point( 12, 318 );
      this.buttonOk.Name = "buttonOk";
      this.buttonOk.Size = new System.Drawing.Size( 75, 23 );
      this.buttonOk.TabIndex = 0;
      this.buttonOk.Text = "OK";
      this.buttonOk.UseVisualStyleBackColor = true;
      this.buttonOk.Click += new System.EventHandler( this.buttonOk_Click );
      // 
      // buttonCancel
      // 
      this.buttonCancel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.buttonCancel.Location = new System.Drawing.Point( 131, 318 );
      this.buttonCancel.Name = "buttonCancel";
      this.buttonCancel.Size = new System.Drawing.Size( 75, 23 );
      this.buttonCancel.TabIndex = 1;
      this.buttonCancel.Text = "Cancel";
      this.buttonCancel.UseVisualStyleBackColor = true;
      // 
      // listBoxTypes
      // 
      this.listBoxTypes.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.listBoxTypes.FormattingEnabled = true;
      this.listBoxTypes.IntegralHeight = false;
      this.listBoxTypes.Location = new System.Drawing.Point( 12, 38 );
      this.listBoxTypes.Name = "listBoxTypes";
      this.listBoxTypes.Size = new System.Drawing.Size( 194, 274 );
      this.listBoxTypes.TabIndex = 2;
      this.listBoxTypes.SelectedIndexChanged += new System.EventHandler( this.listBoxTypes_SelectedIndexChanged );
      this.listBoxTypes.DoubleClick += new System.EventHandler( this.listBoxTypes_DoubleClick );
      // 
      // tbSearch
      // 
      this.tbSearch.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.tbSearch.Location = new System.Drawing.Point( 12, 12 );
      this.tbSearch.Name = "tbSearch";
      this.tbSearch.Size = new System.Drawing.Size( 194, 20 );
      this.tbSearch.TabIndex = 3;
      this.tbSearch.TextChanged += new System.EventHandler( this.tbSearch_TextChanged );
      this.tbSearch.KeyUp += new System.Windows.Forms.KeyEventHandler( this.tbSearch_KeyUp );
      // 
      // ChangeTypeForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.buttonCancel;
      this.ClientSize = new System.Drawing.Size( 218, 353 );
      this.ControlBox = false;
      this.Controls.Add( this.tbSearch );
      this.Controls.Add( this.listBoxTypes );
      this.Controls.Add( this.buttonCancel );
      this.Controls.Add( this.buttonOk );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.MinimumSize = new System.Drawing.Size( 200, 300 );
      this.Name = "ChangeTypeForm";
      this.ShowIcon = false;
      this.Text = "Change Resource Type";
      this.Shown += new System.EventHandler( this.ChangeTypeForm_Shown );
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button buttonOk;
    private System.Windows.Forms.Button buttonCancel;
    private System.Windows.Forms.ListBox listBoxTypes;
    private System.Windows.Forms.TextBox tbSearch;
  }
}