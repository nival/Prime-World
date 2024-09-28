namespace EditorPlugins.Scene
{
	partial class DebugVarsFilterForm
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
			if ( disposing && (components != null) )
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
      this.panel1 = new System.Windows.Forms.Panel();
      this.okButton = new System.Windows.Forms.Button();
      this.cancelButton = new System.Windows.Forms.Button();
      this.debugVarsListBox = new System.Windows.Forms.ListBox();
      this.filterTextBox = new System.Windows.Forms.TextBox();
      this.panel1.SuspendLayout();
      this.SuspendLayout();
      // 
      // panel1
      // 
      this.panel1.Controls.Add( this.okButton );
      this.panel1.Controls.Add( this.cancelButton );
      this.panel1.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.panel1.Location = new System.Drawing.Point( 0, 496 );
      this.panel1.Name = "panel1";
      this.panel1.Size = new System.Drawing.Size( 295, 35 );
      this.panel1.TabIndex = 1;
      // 
      // okButton
      // 
      this.okButton.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.okButton.Location = new System.Drawing.Point( 127, 3 );
      this.okButton.Name = "okButton";
      this.okButton.Size = new System.Drawing.Size( 75, 23 );
      this.okButton.TabIndex = 1;
      this.okButton.Text = "OK";
      this.okButton.UseVisualStyleBackColor = true;
      this.okButton.Click += new System.EventHandler( this.OnOkButtonClick );
      // 
      // cancelButton
      // 
      this.cancelButton.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.cancelButton.Location = new System.Drawing.Point( 208, 3 );
      this.cancelButton.Name = "cancelButton";
      this.cancelButton.Size = new System.Drawing.Size( 75, 23 );
      this.cancelButton.TabIndex = 0;
      this.cancelButton.Text = "Cancel";
      this.cancelButton.UseVisualStyleBackColor = true;
      // 
      // debugVarsListBox
      // 
      this.debugVarsListBox.Dock = System.Windows.Forms.DockStyle.Fill;
      this.debugVarsListBox.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
      this.debugVarsListBox.FormattingEnabled = true;
      this.debugVarsListBox.IntegralHeight = false;
      this.debugVarsListBox.Location = new System.Drawing.Point( 0, 0 );
      this.debugVarsListBox.Name = "debugVarsListBox";
      this.debugVarsListBox.Size = new System.Drawing.Size( 295, 476 );
      this.debugVarsListBox.TabIndex = 2;
      this.debugVarsListBox.DrawItem += new System.Windows.Forms.DrawItemEventHandler( this.OnDebugVarsListBoxDrawItem );
      this.debugVarsListBox.DoubleClick += new System.EventHandler( this.OnDebugVarsListBoxDoubleClick );
      // 
      // filterTextBox
      // 
      this.filterTextBox.BackColor = System.Drawing.SystemColors.Info;
      this.filterTextBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
      this.filterTextBox.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.filterTextBox.ForeColor = System.Drawing.SystemColors.InfoText;
      this.filterTextBox.Location = new System.Drawing.Point( 0, 476 );
      this.filterTextBox.Name = "filterTextBox";
      this.filterTextBox.Size = new System.Drawing.Size( 295, 20 );
      this.filterTextBox.TabIndex = 3;
      this.filterTextBox.TextChanged += new System.EventHandler( this.OnFilterTextBoxTextChanged );
      this.filterTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler( this.OnFilterTextBoxKeyPress );
      // 
      // DebugVarsFilterForm
      // 
      this.AcceptButton = this.okButton;
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.cancelButton;
      this.ClientSize = new System.Drawing.Size( 295, 531 );
      this.Controls.Add( this.debugVarsListBox );
      this.Controls.Add( this.filterTextBox );
      this.Controls.Add( this.panel1 );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
      this.Name = "DebugVarsFilterForm";
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
      this.Text = "Select Debug Variables";
      this.panel1.ResumeLayout( false );
      this.ResumeLayout( false );
      this.PerformLayout();

		}

		#endregion

    private System.Windows.Forms.Panel panel1;
    private System.Windows.Forms.Button okButton;
    private System.Windows.Forms.Button cancelButton;
    private System.Windows.Forms.ListBox debugVarsListBox;
    private System.Windows.Forms.TextBox filterTextBox;

  }
}