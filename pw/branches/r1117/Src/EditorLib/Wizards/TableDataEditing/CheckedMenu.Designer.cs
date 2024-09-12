namespace EditorLib.Wizards.TableDataEditing
{
  partial class CheckedMenu
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
      if( disposing && ( components != null ) )
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
			this.lstArrayTypes = new System.Windows.Forms.CheckedListBox();
			this.btnOk = new System.Windows.Forms.Button();
			this.btnCancel = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// lstArrayTypes
			// 
			this.lstArrayTypes.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
									| System.Windows.Forms.AnchorStyles.Left)
									| System.Windows.Forms.AnchorStyles.Right)));
			this.lstArrayTypes.BackColor = System.Drawing.SystemColors.Control;
			this.lstArrayTypes.BorderStyle = System.Windows.Forms.BorderStyle.None;
			this.lstArrayTypes.CheckOnClick = true;
			this.lstArrayTypes.FormattingEnabled = true;
			this.lstArrayTypes.IntegralHeight = false;
			this.lstArrayTypes.Location = new System.Drawing.Point(0, 0);
			this.lstArrayTypes.Name = "lstArrayTypes";
			this.lstArrayTypes.Size = new System.Drawing.Size(135, 124);
			this.lstArrayTypes.TabIndex = 0;
			this.lstArrayTypes.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler(this.OnItemCheck);
			// 
			// btnOk
			// 
			this.btnOk.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
			this.btnOk.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.btnOk.Location = new System.Drawing.Point(10, 130);
			this.btnOk.Name = "btnOk";
			this.btnOk.Size = new System.Drawing.Size(56, 24);
			this.btnOk.TabIndex = 1;
			this.btnOk.Text = "OK";
			this.btnOk.UseVisualStyleBackColor = true;
			// 
			// btnCancel
			// 
			this.btnCancel.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
			this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.btnCancel.Location = new System.Drawing.Point(72, 130);
			this.btnCancel.Name = "btnCancel";
			this.btnCancel.Size = new System.Drawing.Size(56, 24);
			this.btnCancel.TabIndex = 1;
			this.btnCancel.Text = "Cancel";
			this.btnCancel.UseVisualStyleBackColor = true;
			// 
			// CheckedMenu
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(138, 158);
			this.ControlBox = false;
			this.Controls.Add(this.btnCancel);
			this.Controls.Add(this.btnOk);
			this.Controls.Add(this.lstArrayTypes);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.Name = "CheckedMenu";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Load += new System.EventHandler(this.CheckedMenu_Load);
			this.LocationChanged += new System.EventHandler(this.CheckedMenu_LocationChanged);
			this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.CheckedListBox lstArrayTypes;
		private System.Windows.Forms.Button btnOk;
		private System.Windows.Forms.Button btnCancel;
  }
}