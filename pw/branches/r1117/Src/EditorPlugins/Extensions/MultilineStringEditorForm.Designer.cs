namespace EditorPlugins.Extensions
{
    partial class MultilineStringEditorForm
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
      this.btnOk = new System.Windows.Forms.Button();
      this.btnCancel = new System.Windows.Forms.Button();
      this.rtbCode = new ScintillaNET.Scintilla();
      ((System.ComponentModel.ISupportInitialize)(this.rtbCode)).BeginInit();
      this.SuspendLayout();
      // 
      // btnOk
      // 
      this.btnOk.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.btnOk.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.btnOk.Location = new System.Drawing.Point(286, 269);
      this.btnOk.Name = "btnOk";
      this.btnOk.Size = new System.Drawing.Size(75, 23);
      this.btnOk.TabIndex = 1;
      this.btnOk.Text = "OK";
      this.btnOk.UseVisualStyleBackColor = true;
      // 
      // btnCancel
      // 
      this.btnCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.btnCancel.Location = new System.Drawing.Point(367, 269);
      this.btnCancel.Name = "btnCancel";
      this.btnCancel.Size = new System.Drawing.Size(75, 23);
      this.btnCancel.TabIndex = 1;
      this.btnCancel.Text = "Cancel";
      this.btnCancel.UseVisualStyleBackColor = true;
      // 
      // rtbCode
      // 
      this.rtbCode.ConfigurationManager.Language = "cs";
      this.rtbCode.Dock = System.Windows.Forms.DockStyle.Top;
      this.rtbCode.Location = new System.Drawing.Point(0, 0);
      this.rtbCode.Name = "rtbCode";
      this.rtbCode.Size = new System.Drawing.Size(454, 258);
      this.rtbCode.TabIndex = 2;
      // 
      // MultilineStringEditorForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.btnCancel;
      this.ClientSize = new System.Drawing.Size(454, 304);
      this.Controls.Add(this.rtbCode);
      this.Controls.Add(this.btnCancel);
      this.Controls.Add(this.btnOk);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
      this.MinimumSize = new System.Drawing.Size(277, 219);
      this.Name = "MultilineStringEditorForm";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.Text = "MultilineStringEditorForm";
      ((System.ComponentModel.ISupportInitialize)(this.rtbCode)).EndInit();
      this.ResumeLayout(false);

		}

		#endregion

    private System.Windows.Forms.Button btnOk;
		private System.Windows.Forms.Button btnCancel;
    private ScintillaNET.Scintilla rtbCode;
	}
}