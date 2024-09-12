namespace EditorPlugins.Templates
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
			this.buttonCreate = new System.Windows.Forms.Button();
			this.properties = new System.Windows.Forms.PropertyGrid();
			this.label3 = new System.Windows.Forms.Label();
			this.textBoxFieldName = new System.Windows.Forms.TextBox();
			this.textBoxObjectNamePattern = new System.Windows.Forms.TextBox();
			this.labelObjectNamePatern = new System.Windows.Forms.Label();
			this.panel1.SuspendLayout();
			( (System.ComponentModel.ISupportInitialize)( this.pictureBox1 ) ).BeginInit();
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
			this.pictureBox1.Image = ( (System.Drawing.Image)( resources.GetObject( "pictureBox1.Image" ) ) );
			this.pictureBox1.Location = new System.Drawing.Point( 0, 0 );
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size( 150, 300 );
			this.pictureBox1.TabIndex = 0;
			this.pictureBox1.TabStop = false;
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point( 172, 53 );
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size( 82, 13 );
			this.label1.TabIndex = 1;
			this.label1.Text = "Template Name";
			// 
			// textBoxName
			// 
			this.textBoxName.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.textBoxName.Location = new System.Drawing.Point( 175, 69 );
			this.textBoxName.Name = "textBoxName";
			this.textBoxName.Size = new System.Drawing.Size( 372, 20 );
			this.textBoxName.TabIndex = 3;
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point( 172, 14 );
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size( 126, 13 );
			this.label2.TabIndex = 3;
			this.label2.Text = "Root Object for Template";
			// 
			// textBoxObject
			// 
			this.textBoxObject.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.textBoxObject.BackColor = System.Drawing.SystemColors.Window;
			this.textBoxObject.Location = new System.Drawing.Point( 175, 30 );
			this.textBoxObject.Name = "textBoxObject";
			this.textBoxObject.ReadOnly = true;
			this.textBoxObject.Size = new System.Drawing.Size( 291, 20 );
			this.textBoxObject.TabIndex = 1;
			this.textBoxObject.TextChanged += new System.EventHandler( this.OnTextBoxObjectTextChanged );
			// 
			// buttonBrowse
			// 
			this.buttonBrowse.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.buttonBrowse.Location = new System.Drawing.Point( 472, 30 );
			this.buttonBrowse.Name = "buttonBrowse";
			this.buttonBrowse.Size = new System.Drawing.Size( 75, 20 );
			this.buttonBrowse.TabIndex = 2;
			this.buttonBrowse.Text = "Browse...";
			this.buttonBrowse.UseVisualStyleBackColor = true;
			this.buttonBrowse.Click += new System.EventHandler( this.OnBrowseClick );
			// 
			// buttonCancel
			// 
			this.buttonCancel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonCancel.Location = new System.Drawing.Point( 472, 322 );
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size( 75, 23 );
			this.buttonCancel.TabIndex = 8;
			this.buttonCancel.Text = "Cancel";
			this.buttonCancel.UseVisualStyleBackColor = true;
			this.buttonCancel.Click += new System.EventHandler( this.OnCancelClick );
			// 
			// buttonCreate
			// 
			this.buttonCreate.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.buttonCreate.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.buttonCreate.Location = new System.Drawing.Point( 391, 322 );
			this.buttonCreate.Name = "buttonCreate";
			this.buttonCreate.Size = new System.Drawing.Size( 75, 23 );
			this.buttonCreate.TabIndex = 7;
			this.buttonCreate.Text = "Create";
			this.buttonCreate.UseVisualStyleBackColor = true;
			this.buttonCreate.Click += new System.EventHandler( this.OnCreateClick );
			// 
			// properties
			// 
			this.properties.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
									| System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.properties.HelpVisible = false;
			this.properties.Location = new System.Drawing.Point( 175, 147 );
			this.properties.Name = "properties";
			this.properties.PropertySort = System.Windows.Forms.PropertySort.NoSort;
			this.properties.Size = new System.Drawing.Size( 372, 143 );
			this.properties.TabIndex = 5;
			this.properties.ToolbarVisible = false;
			this.properties.SelectedGridItemChanged += new System.Windows.Forms.SelectedGridItemChangedEventHandler( this.OnSelectedGridItemChanged );
			this.properties.PropertyValueChanged += new System.Windows.Forms.PropertyValueChangedEventHandler( this.OnPropertyValueChanged );
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point( 172, 131 );
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size( 85, 13 );
			this.label3.TabIndex = 12;
			this.label3.Text = "Modifiable Fields";
			// 
			// textBoxFieldName
			// 
			this.textBoxFieldName.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.textBoxFieldName.Location = new System.Drawing.Point( 175, 296 );
			this.textBoxFieldName.Name = "textBoxFieldName";
			this.textBoxFieldName.Size = new System.Drawing.Size( 372, 20 );
			this.textBoxFieldName.TabIndex = 6;
			this.textBoxFieldName.TextChanged += new System.EventHandler( this.OnFieldNameTextChanged );
			// 
			// textBoxObjectNamePattern
			// 
			this.textBoxObjectNamePattern.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.textBoxObjectNamePattern.Location = new System.Drawing.Point( 175, 108 );
			this.textBoxObjectNamePattern.Name = "textBoxObjectNamePattern";
			this.textBoxObjectNamePattern.Size = new System.Drawing.Size( 372, 20 );
			this.textBoxObjectNamePattern.TabIndex = 4;
			// 
			// labelObjectNamePatern
			// 
			this.labelObjectNamePatern.AutoSize = true;
			this.labelObjectNamePatern.Location = new System.Drawing.Point( 172, 92 );
			this.labelObjectNamePatern.Name = "labelObjectNamePatern";
			this.labelObjectNamePatern.Size = new System.Drawing.Size( 248, 13 );
			this.labelObjectNamePatern.TabIndex = 14;
			this.labelObjectNamePatern.Text = "Object Name Pattern (Use \'$\' as name placeholder)";
			// 
			// DefineTemplateForm
			// 
			this.AcceptButton = this.buttonCreate;
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.buttonCancel;
			this.ClientSize = new System.Drawing.Size( 559, 356 );
			this.Controls.Add( this.textBoxObjectNamePattern );
			this.Controls.Add( this.labelObjectNamePatern );
			this.Controls.Add( this.textBoxFieldName );
			this.Controls.Add( this.label3 );
			this.Controls.Add( this.properties );
			this.Controls.Add( this.buttonCreate );
			this.Controls.Add( this.buttonCancel );
			this.Controls.Add( this.buttonBrowse );
			this.Controls.Add( this.textBoxObject );
			this.Controls.Add( this.label2 );
			this.Controls.Add( this.textBoxName );
			this.Controls.Add( this.label1 );
			this.Controls.Add( this.panel1 );
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.MinimumSize = new System.Drawing.Size( 567, 383 );
			this.Name = "DefineTemplateForm";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Define New Template";
			this.panel1.ResumeLayout( false );
			( (System.ComponentModel.ISupportInitialize)( this.pictureBox1 ) ).EndInit();
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
		private System.Windows.Forms.Button buttonCreate;
		private System.Windows.Forms.PropertyGrid properties;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox textBoxFieldName;
		private System.Windows.Forms.TextBox textBoxObjectNamePattern;
		private System.Windows.Forms.Label labelObjectNamePatern;
	}
}