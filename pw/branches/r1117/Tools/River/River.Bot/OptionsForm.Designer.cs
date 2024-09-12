namespace River.Bot
{
	partial class OptionsForm
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( OptionsForm ) );
			this.masterLabel = new System.Windows.Forms.Label();
			this.masterTextBox = new System.Windows.Forms.TextBox();
			this.verifyLabel = new System.Windows.Forms.LinkLabel();
			this.buttonsPanel = new System.Windows.Forms.Panel();
			this.okButton = new System.Windows.Forms.Button();
			this.cancelButton = new System.Windows.Forms.Button();
			this.resultLabel = new System.Windows.Forms.Label();
			this.buttonsPanel.SuspendLayout();
			this.SuspendLayout();
			// 
			// masterLabel
			// 
			this.masterLabel.AutoSize = true;
			this.masterLabel.Location = new System.Drawing.Point( 12, 15 );
			this.masterLabel.Name = "masterLabel";
			this.masterLabel.Size = new System.Drawing.Size( 42, 13 );
			this.masterLabel.TabIndex = 0;
			this.masterLabel.Text = "Master:";
			// 
			// masterTextBox
			// 
			this.masterTextBox.Location = new System.Drawing.Point( 60, 12 );
			this.masterTextBox.Name = "masterTextBox";
			this.masterTextBox.Size = new System.Drawing.Size( 270, 20 );
			this.masterTextBox.TabIndex = 1;
			// 
			// verifyLabel
			// 
			this.verifyLabel.ActiveLinkColor = System.Drawing.Color.Navy;
			this.verifyLabel.AutoSize = true;
			this.verifyLabel.Location = new System.Drawing.Point( 336, 15 );
			this.verifyLabel.Name = "verifyLabel";
			this.verifyLabel.Size = new System.Drawing.Size( 36, 13 );
			this.verifyLabel.TabIndex = 4;
			this.verifyLabel.TabStop = true;
			this.verifyLabel.Text = "Verify!";
			this.verifyLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler( this.OnVerify );
			// 
			// buttonsPanel
			// 
			this.buttonsPanel.BackColor = System.Drawing.SystemColors.Control;
			this.buttonsPanel.Controls.Add( this.okButton );
			this.buttonsPanel.Controls.Add( this.cancelButton );
			this.buttonsPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
			this.buttonsPanel.Location = new System.Drawing.Point( 0, 56 );
			this.buttonsPanel.Name = "buttonsPanel";
			this.buttonsPanel.Size = new System.Drawing.Size( 384, 40 );
			this.buttonsPanel.TabIndex = 6;
			// 
			// okButton
			// 
			this.okButton.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.okButton.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.okButton.Location = new System.Drawing.Point( 225, 13 );
			this.okButton.Name = "okButton";
			this.okButton.Size = new System.Drawing.Size( 75, 23 );
			this.okButton.TabIndex = 7;
			this.okButton.Text = "OK";
			this.okButton.UseVisualStyleBackColor = true;
			// 
			// cancelButton
			// 
			this.cancelButton.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.cancelButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.cancelButton.Location = new System.Drawing.Point( 306, 13 );
			this.cancelButton.Name = "cancelButton";
			this.cancelButton.Size = new System.Drawing.Size( 75, 23 );
			this.cancelButton.TabIndex = 6;
			this.cancelButton.Text = "Cancel";
			this.cancelButton.UseVisualStyleBackColor = true;
			// 
			// resultLabel
			// 
			this.resultLabel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
			this.resultLabel.AutoSize = true;
			this.resultLabel.ForeColor = System.Drawing.Color.Red;
			this.resultLabel.Location = new System.Drawing.Point( 12, 35 );
			this.resultLabel.Name = "resultLabel";
			this.resultLabel.Size = new System.Drawing.Size( 150, 13 );
			this.resultLabel.TabIndex = 9;
			this.resultLabel.Text = "River.Master server not found!";
			this.resultLabel.Visible = false;
			// 
			// OptionsForm
			// 
			this.AcceptButton = this.okButton;
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.BackColor = System.Drawing.SystemColors.Window;
			this.CancelButton = this.cancelButton;
			this.ClientSize = new System.Drawing.Size( 384, 96 );
			this.Controls.Add( this.buttonsPanel );
			this.Controls.Add( this.resultLabel );
			this.Controls.Add( this.verifyLabel );
			this.Controls.Add( this.masterTextBox );
			this.Controls.Add( this.masterLabel );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Icon = ( (System.Drawing.Icon)( resources.GetObject( "$this.Icon" ) ) );
			this.Name = "OptionsForm";
			this.ShowIcon = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "River.Bot Options";
			this.buttonsPanel.ResumeLayout( false );
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label masterLabel;
		private System.Windows.Forms.TextBox masterTextBox;
		private System.Windows.Forms.LinkLabel verifyLabel;
		private System.Windows.Forms.Panel buttonsPanel;
		private System.Windows.Forms.Button okButton;
		private System.Windows.Forms.Button cancelButton;
		private System.Windows.Forms.Label resultLabel;
	}
}