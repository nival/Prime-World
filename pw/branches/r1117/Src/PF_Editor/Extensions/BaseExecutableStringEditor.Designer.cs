namespace PF_Editor.Extensions
{
	partial class BaseExecutableStringEditor
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
            this.rtbFormula = new ScintillaNET.Scintilla();
            this.cbWordWrap = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.rtbFormula)).BeginInit();
            this.SuspendLayout();
            // 
            // btnOk
            // 
            this.btnOk.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.btnOk.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnOk.Location = new System.Drawing.Point(314, 258);
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
            this.btnCancel.Location = new System.Drawing.Point(395, 258);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(75, 23);
            this.btnCancel.TabIndex = 1;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = true;
            // 
            // rtbFormula
            // 
            this.rtbFormula.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.rtbFormula.ConfigurationManager.Language = "cpp";
            this.rtbFormula.Location = new System.Drawing.Point(10, 10);
            this.rtbFormula.Margin = new System.Windows.Forms.Padding(1);
            this.rtbFormula.Name = "rtbFormula";
            this.rtbFormula.Size = new System.Drawing.Size(460, 242);
            this.rtbFormula.TabIndex = 2;
            // 
            // cbWordWrap
            // 
            this.cbWordWrap.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.cbWordWrap.AutoSize = true;
            this.cbWordWrap.Location = new System.Drawing.Point(12, 262);
            this.cbWordWrap.Name = "cbWordWrap";
            this.cbWordWrap.Size = new System.Drawing.Size(81, 17);
            this.cbWordWrap.TabIndex = 4;
            this.cbWordWrap.Text = "Word Wrap";
            this.cbWordWrap.UseVisualStyleBackColor = true;
            this.cbWordWrap.CheckedChanged += new System.EventHandler(this.cbWordWrap_CheckedChanged);
            // 
            // BaseExecutableStringEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.btnCancel;
            this.ClientSize = new System.Drawing.Size(482, 293);
            this.Controls.Add(this.cbWordWrap);
            this.Controls.Add(this.rtbFormula);
            this.Controls.Add(this.btnCancel);
            this.Controls.Add(this.btnOk);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
            this.MinimumSize = new System.Drawing.Size(277, 219);
            this.Name = "BaseExecutableStringEditor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "ExecutableBaseStringEditor";
            this.Load += new System.EventHandler(this.BaseExecutableStringEditor_Load);
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.BaseExecutableStringEditor_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.rtbFormula)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

		}

		#endregion

    private System.Windows.Forms.Button btnOk;
		private System.Windows.Forms.Button btnCancel;
    private ScintillaNET.Scintilla rtbFormula;
    private System.Windows.Forms.CheckBox cbWordWrap;
	}
}