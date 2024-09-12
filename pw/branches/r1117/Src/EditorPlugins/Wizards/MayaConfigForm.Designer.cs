namespace EditorPlugins.Wizards
{
  partial class MayaConfigForm
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
		this.btnCancel = new System.Windows.Forms.Button();
		this.btnOk = new System.Windows.Forms.Button();
		this.label1 = new System.Windows.Forms.Label();
		this.txtPathToMaya = new System.Windows.Forms.TextBox();
		this.btnBrowse = new System.Windows.Forms.Button();
		this.SuspendLayout();
		// 
		// btnCancel
		// 
		this.btnCancel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
		this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
		this.btnCancel.Location = new System.Drawing.Point( 212, 51 );
		this.btnCancel.Name = "btnCancel";
		this.btnCancel.Size = new System.Drawing.Size( 61, 23 );
		this.btnCancel.TabIndex = 5;
		this.btnCancel.Text = "Cancel";
		this.btnCancel.UseVisualStyleBackColor = true;
		// 
		// btnOk
		// 
		this.btnOk.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
		this.btnOk.DialogResult = System.Windows.Forms.DialogResult.Cancel;
		this.btnOk.Location = new System.Drawing.Point( 145, 51 );
		this.btnOk.Name = "btnOk";
		this.btnOk.Size = new System.Drawing.Size( 61, 23 );
		this.btnOk.TabIndex = 6;
		this.btnOk.Text = "Ok";
		this.btnOk.UseVisualStyleBackColor = true;
		this.btnOk.Click += new System.EventHandler( this.btnOk_Click );
		// 
		// label1
		// 
		this.label1.AutoSize = true;
		this.label1.Location = new System.Drawing.Point( 9, 9 );
		this.label1.Name = "label1";
		this.label1.Size = new System.Drawing.Size( 70, 13 );
		this.label1.TabIndex = 7;
		this.label1.Text = "Path to Maya";
		// 
		// txtPathToMaya
		// 
		this.txtPathToMaya.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
								| System.Windows.Forms.AnchorStyles.Right ) ) );
		this.txtPathToMaya.Location = new System.Drawing.Point( 12, 25 );
		this.txtPathToMaya.Name = "txtPathToMaya";
		this.txtPathToMaya.Size = new System.Drawing.Size( 226, 20 );
		this.txtPathToMaya.TabIndex = 8;
		// 
		// btnBrowse
		// 
		this.btnBrowse.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
		this.btnBrowse.Location = new System.Drawing.Point( 241, 23 );
		this.btnBrowse.Name = "btnBrowse";
		this.btnBrowse.Size = new System.Drawing.Size( 32, 23 );
		this.btnBrowse.TabIndex = 9;
		this.btnBrowse.Text = "...";
		this.btnBrowse.UseVisualStyleBackColor = true;
		this.btnBrowse.Click += new System.EventHandler( this.btnBrowse_Click );
		// 
		// MayaConfigForm
		// 
		this.AcceptButton = this.btnOk;
		this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
		this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
		this.CancelButton = this.btnCancel;
		this.ClientSize = new System.Drawing.Size( 281, 86 );
		this.Controls.Add( this.btnBrowse );
		this.Controls.Add( this.txtPathToMaya );
		this.Controls.Add( this.label1 );
		this.Controls.Add( this.btnOk );
		this.Controls.Add( this.btnCancel );
		this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
		this.MaximizeBox = false;
		this.Name = "MayaConfigForm";
		this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
		this.Text = "MayaConfigForm";
		this.Load += new System.EventHandler( this.MayaConfigForm_Load );
		this.ResumeLayout( false );
		this.PerformLayout();

	}

	#endregion

	private System.Windows.Forms.Button btnCancel;
	private System.Windows.Forms.Button btnOk;
	private System.Windows.Forms.Label label1;
	private System.Windows.Forms.TextBox txtPathToMaya;
	private System.Windows.Forms.Button btnBrowse;
  }
}