namespace EditorLib.Templates
{
	partial class DefineTemplateForm
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( DefineTemplateForm ) );
			this.panel1 = new System.Windows.Forms.Panel();
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			this.label1 = new System.Windows.Forms.Label();
			this.textBoxName = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.textBoxObject = new System.Windows.Forms.TextBox();
			this.buttonBrowse = new System.Windows.Forms.Button();
			this.buttonCancel = new System.Windows.Forms.Button();
			this.buttonNext = new System.Windows.Forms.Button();
			this.buttonBack = new System.Windows.Forms.Button();
			this.properties = new System.Windows.Forms.PropertyGrid();
			this.panel1.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
			this.SuspendLayout();
			// 
			// panel1
			// 
			this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
			this.panel1.Controls.Add( this.pictureBox1 );
			this.panel1.Location = new System.Drawing.Point( 12, 12 );
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size( 154, 304 );
			this.panel1.TabIndex = 0;
			// 
			// pictureBox1
			// 
			this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject( "pictureBox1.Image" )));
			this.pictureBox1.Location = new System.Drawing.Point( 0, 0 );
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size( 150, 300 );
			this.pictureBox1.TabIndex = 0;
			this.pictureBox1.TabStop = false;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point( 172, 14 );
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size( 219, 13 );
			this.label1.TabIndex = 1;
			this.label1.Text = "1. Specify Name for Newly Created Template";
			// 
			// textBoxName
			// 
			this.textBoxName.Location = new System.Drawing.Point( 175, 30 );
			this.textBoxName.Name = "textBoxName";
			this.textBoxName.Size = new System.Drawing.Size( 372, 20 );
			this.textBoxName.TabIndex = 2;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point( 172, 70 );
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size( 171, 13 );
			this.label2.TabIndex = 3;
			this.label2.Text = "2. Select Root Object for Template";
			// 
			// textBoxObject
			// 
			this.textBoxObject.Location = new System.Drawing.Point( 172, 86 );
			this.textBoxObject.Name = "textBoxObject";
			this.textBoxObject.Size = new System.Drawing.Size( 291, 20 );
			this.textBoxObject.TabIndex = 4;
			this.textBoxObject.TextChanged += new System.EventHandler( this.OnTextBoxObjectTextChanged );
			// 
			// buttonBrowse
			// 
			this.buttonBrowse.Location = new System.Drawing.Point( 472, 86 );
			this.buttonBrowse.Name = "buttonBrowse";
			this.buttonBrowse.Size = new System.Drawing.Size( 75, 20 );
			this.buttonBrowse.TabIndex = 5;
			this.buttonBrowse.Text = "Browse...";
			this.buttonBrowse.UseVisualStyleBackColor = true;
			this.buttonBrowse.Click += new System.EventHandler( this.OnBrowseClick );
			// 
			// buttonCancel
			// 
			this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonCancel.Location = new System.Drawing.Point( 472, 293 );
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size( 75, 23 );
			this.buttonCancel.TabIndex = 8;
			this.buttonCancel.Text = "Cancel";
			this.buttonCancel.UseVisualStyleBackColor = true;
			this.buttonCancel.Click += new System.EventHandler( this.OnCancelClick );
			// 
			// buttonNext
			// 
			this.buttonNext.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.buttonNext.Location = new System.Drawing.Point( 368, 293 );
			this.buttonNext.Name = "buttonNext";
			this.buttonNext.Size = new System.Drawing.Size( 75, 23 );
			this.buttonNext.TabIndex = 9;
			this.buttonNext.Text = "Next >>";
			this.buttonNext.UseVisualStyleBackColor = true;
			this.buttonNext.Click += new System.EventHandler( this.OnNextClick );
			// 
			// buttonBack
			// 
			this.buttonBack.Location = new System.Drawing.Point( 287, 293 );
			this.buttonBack.Name = "buttonBack";
			this.buttonBack.Size = new System.Drawing.Size( 75, 23 );
			this.buttonBack.TabIndex = 10;
			this.buttonBack.Text = "<< Back";
			this.buttonBack.UseVisualStyleBackColor = true;
			this.buttonBack.Click += new System.EventHandler( this.OnBackClick );
			// 
			// properties
			// 
			this.properties.HelpVisible = false;
			this.properties.Location = new System.Drawing.Point( 172, 132 );
			this.properties.Name = "properties";
			this.properties.PropertySort = System.Windows.Forms.PropertySort.NoSort;
			this.properties.Size = new System.Drawing.Size( 375, 155 );
			this.properties.TabIndex = 11;
			this.properties.ToolbarVisible = false;
			// 
			// DefineTemplateForm
			// 
			this.AcceptButton = this.buttonNext;
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.buttonCancel;
			this.ClientSize = new System.Drawing.Size( 559, 325 );
			this.Controls.Add( this.properties );
			this.Controls.Add( this.buttonBack );
			this.Controls.Add( this.buttonNext );
			this.Controls.Add( this.buttonCancel );
			this.Controls.Add( this.buttonBrowse );
			this.Controls.Add( this.textBoxObject );
			this.Controls.Add( this.label2 );
			this.Controls.Add( this.textBoxName );
			this.Controls.Add( this.label1 );
			this.Controls.Add( this.panel1 );
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "DefineTemplateForm";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Define New Template";
			this.panel1.ResumeLayout( false );
			((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.PictureBox pictureBox1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.TextBox textBoxName;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.TextBox textBoxObject;
		private System.Windows.Forms.Button buttonBrowse;
		private System.Windows.Forms.Button buttonCancel;
		private System.Windows.Forms.Button buttonNext;
		private System.Windows.Forms.Button buttonBack;
		private System.Windows.Forms.PropertyGrid properties;
	}
}