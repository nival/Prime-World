namespace EditorLib.ObjectsBrowser
{
	partial class ItemSelectorForm<T>
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
      this.lstTypes = new System.Windows.Forms.CheckedListBox();
      this.btnOk = new System.Windows.Forms.Button();
      this.bntCancel = new System.Windows.Forms.Button();
      this.chkCheckAll = new System.Windows.Forms.CheckBox();
      this.label1 = new System.Windows.Forms.Label();
      this.txtFilter = new System.Windows.Forms.TextBox();
      this.lblSelectedItems = new System.Windows.Forms.Label();
      this.SuspendLayout();
      // 
      // lstTypes
      // 
      this.lstTypes.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.lstTypes.FormattingEnabled = true;
      this.lstTypes.IntegralHeight = false;
      this.lstTypes.Location = new System.Drawing.Point( 12, 32 );
      this.lstTypes.Name = "lstTypes";
      this.lstTypes.Size = new System.Drawing.Size( 244, 362 );
      this.lstTypes.TabIndex = 0;
      this.lstTypes.ItemCheck += new System.Windows.Forms.ItemCheckEventHandler( this.OnItemCheck );
      // 
      // btnOk
      // 
      this.btnOk.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
      this.btnOk.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.btnOk.Location = new System.Drawing.Point( 56, 452 );
      this.btnOk.Name = "btnOk";
      this.btnOk.Size = new System.Drawing.Size( 75, 23 );
      this.btnOk.TabIndex = 2;
      this.btnOk.Text = "OK";
      this.btnOk.UseVisualStyleBackColor = true;
      // 
      // bntCancel
      // 
      this.bntCancel.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
      this.bntCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.bntCancel.Location = new System.Drawing.Point( 137, 452 );
      this.bntCancel.Name = "bntCancel";
      this.bntCancel.Size = new System.Drawing.Size( 75, 23 );
      this.bntCancel.TabIndex = 3;
      this.bntCancel.Text = "Cancel";
      this.bntCancel.UseVisualStyleBackColor = true;
      // 
      // chkCheckAll
      // 
      this.chkCheckAll.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
      this.chkCheckAll.AutoSize = true;
      this.chkCheckAll.Location = new System.Drawing.Point( 12, 400 );
      this.chkCheckAll.Name = "chkCheckAll";
      this.chkCheckAll.Size = new System.Drawing.Size( 71, 17 );
      this.chkCheckAll.TabIndex = 1;
      this.chkCheckAll.Text = "Check All";
      this.chkCheckAll.UseVisualStyleBackColor = true;
      this.chkCheckAll.CheckedChanged += new System.EventHandler( this.OnCheckAllCheckedChanged );
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point( 12, 9 );
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size( 29, 13 );
      this.label1.TabIndex = 4;
      this.label1.Text = "Filter";
      // 
      // txtFilter
      // 
      this.txtFilter.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.txtFilter.Location = new System.Drawing.Point( 42, 6 );
      this.txtFilter.Name = "txtFilter";
      this.txtFilter.Size = new System.Drawing.Size( 214, 20 );
      this.txtFilter.TabIndex = 5;
      this.txtFilter.TextChanged += new System.EventHandler( this.OnFilterChanged );
      // 
      // lblSelectedItems
      // 
      this.lblSelectedItems.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.lblSelectedItems.AutoEllipsis = true;
      this.lblSelectedItems.ForeColor = System.Drawing.SystemColors.ControlDarkDark;
      this.lblSelectedItems.Location = new System.Drawing.Point( 12, 420 );
      this.lblSelectedItems.Name = "lblSelectedItems";
      this.lblSelectedItems.Size = new System.Drawing.Size( 244, 29 );
      this.lblSelectedItems.TabIndex = 6;
      this.lblSelectedItems.Text = "lblSelectedItems";
      // 
      // ItemSelectorForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 268, 483 );
      this.Controls.Add( this.lblSelectedItems );
      this.Controls.Add( this.txtFilter );
      this.Controls.Add( this.label1 );
      this.Controls.Add( this.chkCheckAll );
      this.Controls.Add( this.bntCancel );
      this.Controls.Add( this.btnOk );
      this.Controls.Add( this.lstTypes );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
      this.Name = "ItemSelectorForm";
      this.ShowInTaskbar = false;
      this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
      this.Text = "Select Extensions";
      this.ResumeLayout( false );
      this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button btnOk;
		private System.Windows.Forms.Button bntCancel;
		private System.Windows.Forms.CheckBox chkCheckAll;
		private System.Windows.Forms.CheckedListBox lstTypes;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox txtFilter;
    private System.Windows.Forms.Label lblSelectedItems;
	}
}