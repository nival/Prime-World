namespace EditorPlugins.Templates
{
	partial class NewObjectTemplateForm
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
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( NewObjectTemplateForm ) );
      this.panel1 = new System.Windows.Forms.Panel();
      this.pictureBox1 = new System.Windows.Forms.PictureBox();
      this.buttonCancel = new System.Windows.Forms.Button();
      this.buttonCreate = new System.Windows.Forms.Button();
      this.properties = new System.Windows.Forms.PropertyGrid();
      this.labelModifiedFields = new System.Windows.Forms.Label();
      this.textBoxObject = new System.Windows.Forms.TextBox();
      this.labelObjectName = new System.Windows.Forms.Label();
      this.textBoxName = new System.Windows.Forms.TextBox();
      this.labelTemplateName = new System.Windows.Forms.Label();
      this.buttonCommit = new System.Windows.Forms.Button();
      this.checkBoxAutoImport = new System.Windows.Forms.CheckBox();
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
      // buttonCancel
      // 
      this.buttonCancel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.buttonCancel.Location = new System.Drawing.Point( 472, 321 );
      this.buttonCancel.Name = "buttonCancel";
      this.buttonCancel.Size = new System.Drawing.Size( 75, 23 );
      this.buttonCancel.TabIndex = 5;
      this.buttonCancel.Text = "Cancel";
      this.buttonCancel.UseVisualStyleBackColor = true;
      this.buttonCancel.Click += new System.EventHandler( this.OnCancelClick );
      // 
      // buttonCreate
      // 
      this.buttonCreate.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonCreate.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.buttonCreate.Enabled = false;
      this.buttonCreate.Location = new System.Drawing.Point( 391, 321 );
      this.buttonCreate.Name = "buttonCreate";
      this.buttonCreate.Size = new System.Drawing.Size( 75, 23 );
      this.buttonCreate.TabIndex = 4;
      this.buttonCreate.Text = "Create";
      this.buttonCreate.UseVisualStyleBackColor = true;
      this.buttonCreate.Click += new System.EventHandler( this.OnCreateClick );
      // 
      // properties
      // 
      this.properties.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.properties.Enabled = false;
      this.properties.HelpVisible = false;
      this.properties.Location = new System.Drawing.Point( 175, 108 );
      this.properties.Name = "properties";
      this.properties.PropertySort = System.Windows.Forms.PropertySort.NoSort;
      this.properties.Size = new System.Drawing.Size( 372, 204 );
      this.properties.TabIndex = 3;
      this.properties.ToolbarVisible = false;
      this.properties.ViewBackColor = System.Drawing.SystemColors.Control;
      // 
      // labelModifiedFields
      // 
      this.labelModifiedFields.AutoSize = true;
      this.labelModifiedFields.Location = new System.Drawing.Point( 172, 92 );
      this.labelModifiedFields.Name = "labelModifiedFields";
      this.labelModifiedFields.Size = new System.Drawing.Size( 77, 13 );
      this.labelModifiedFields.TabIndex = 17;
      this.labelModifiedFields.Text = "Modified Fields";
      // 
      // textBoxObject
      // 
      this.textBoxObject.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.textBoxObject.Location = new System.Drawing.Point( 175, 69 );
      this.textBoxObject.Name = "textBoxObject";
      this.textBoxObject.Size = new System.Drawing.Size( 291, 20 );
      this.textBoxObject.TabIndex = 1;
      // 
      // labelObjectName
      // 
      this.labelObjectName.AutoSize = true;
      this.labelObjectName.Location = new System.Drawing.Point( 172, 53 );
      this.labelObjectName.Name = "labelObjectName";
      this.labelObjectName.Size = new System.Drawing.Size( 69, 13 );
      this.labelObjectName.TabIndex = 15;
      this.labelObjectName.Text = "Object Name";
      // 
      // textBoxName
      // 
      this.textBoxName.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.textBoxName.Location = new System.Drawing.Point( 175, 30 );
      this.textBoxName.Name = "textBoxName";
      this.textBoxName.ReadOnly = true;
      this.textBoxName.Size = new System.Drawing.Size( 372, 20 );
      this.textBoxName.TabIndex = 14;
      // 
      // labelTemplateName
      // 
      this.labelTemplateName.AutoSize = true;
      this.labelTemplateName.Location = new System.Drawing.Point( 172, 14 );
      this.labelTemplateName.Name = "labelTemplateName";
      this.labelTemplateName.Size = new System.Drawing.Size( 82, 13 );
      this.labelTemplateName.TabIndex = 13;
      this.labelTemplateName.Text = "Template Name";
      // 
      // buttonCommit
      // 
      this.buttonCommit.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonCommit.Location = new System.Drawing.Point( 472, 68 );
      this.buttonCommit.Name = "buttonCommit";
      this.buttonCommit.Size = new System.Drawing.Size( 75, 21 );
      this.buttonCommit.TabIndex = 2;
      this.buttonCommit.Text = "Commit";
      this.buttonCommit.UseVisualStyleBackColor = true;
      this.buttonCommit.Click += new System.EventHandler( this.OnCommitClick );
      // 
      // checkBoxAutoImport
      // 
      this.checkBoxAutoImport.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
      this.checkBoxAutoImport.AutoSize = true;
      this.checkBoxAutoImport.Checked = true;
      this.checkBoxAutoImport.CheckState = System.Windows.Forms.CheckState.Checked;
      this.checkBoxAutoImport.Location = new System.Drawing.Point( 175, 325 );
      this.checkBoxAutoImport.Name = "checkBoxAutoImport";
      this.checkBoxAutoImport.Size = new System.Drawing.Size( 195, 17 );
      this.checkBoxAutoImport.TabIndex = 18;
      this.checkBoxAutoImport.Text = "Import created objects automatically";
      this.checkBoxAutoImport.UseVisualStyleBackColor = true;
      // 
      // NewObjectTemplateForm
      // 
      this.AcceptButton = this.buttonCreate;
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.buttonCancel;
      this.ClientSize = new System.Drawing.Size( 559, 356 );
      this.Controls.Add( this.checkBoxAutoImport );
      this.Controls.Add( this.buttonCommit );
      this.Controls.Add( this.labelModifiedFields );
      this.Controls.Add( this.textBoxObject );
      this.Controls.Add( this.labelObjectName );
      this.Controls.Add( this.textBoxName );
      this.Controls.Add( this.labelTemplateName );
      this.Controls.Add( this.properties );
      this.Controls.Add( this.buttonCreate );
      this.Controls.Add( this.buttonCancel );
      this.Controls.Add( this.panel1 );
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.MinimumSize = new System.Drawing.Size( 567, 383 );
      this.Name = "NewObjectTemplateForm";
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Show;
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.Text = "Create New Object From Template";
      this.panel1.ResumeLayout( false );
      ( (System.ComponentModel.ISupportInitialize)( this.pictureBox1 ) ).EndInit();
      this.ResumeLayout( false );
      this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.PictureBox pictureBox1;
		private System.Windows.Forms.Button buttonCancel;
		private System.Windows.Forms.Button buttonCreate;
		private System.Windows.Forms.PropertyGrid properties;
		private System.Windows.Forms.Label labelModifiedFields;
		private System.Windows.Forms.TextBox textBoxObject;
		private System.Windows.Forms.Label labelObjectName;
		private System.Windows.Forms.TextBox textBoxName;
		private System.Windows.Forms.Label labelTemplateName;
		private System.Windows.Forms.Button buttonCommit;
    private System.Windows.Forms.CheckBox checkBoxAutoImport;
	}
}