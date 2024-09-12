namespace EditorPlugins.Wizards
{
  partial class MayaImportWizardForm
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
			this.components = new System.ComponentModel.Container();
			this.buttonRun = new System.Windows.Forms.Button();
			this.buttonExit = new System.Windows.Forms.Button();
			this.treeViewContents = new System.Windows.Forms.TreeView();
			this.imageListTypeIcons = new System.Windows.Forms.ImageList( this.components );
			this.radioButtonSceneObject = new System.Windows.Forms.RadioButton();
			this.groupBoxCreateTarget = new System.Windows.Forms.GroupBox();
			this.radioButtonProxy = new System.Windows.Forms.RadioButton();
			this.checkBoxAutoImport = new System.Windows.Forms.CheckBox();
			this.groupBoxCreateTarget.SuspendLayout();
			this.SuspendLayout();
			// 
			// buttonRun
			// 
			this.buttonRun.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.buttonRun.Location = new System.Drawing.Point( 259, 440 );
			this.buttonRun.Name = "buttonRun";
			this.buttonRun.Size = new System.Drawing.Size( 75, 23 );
			this.buttonRun.TabIndex = 0;
			this.buttonRun.Text = "Create!";
			this.buttonRun.UseVisualStyleBackColor = true;
			this.buttonRun.Click += new System.EventHandler( this.buttonRun_Click );
			// 
			// buttonExit
			// 
			this.buttonExit.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.buttonExit.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonExit.Location = new System.Drawing.Point( 259, 467 );
			this.buttonExit.Name = "buttonExit";
			this.buttonExit.Size = new System.Drawing.Size( 75, 23 );
			this.buttonExit.TabIndex = 1;
			this.buttonExit.Text = "Exit";
			this.buttonExit.UseVisualStyleBackColor = true;
			// 
			// treeViewContents
			// 
			this.treeViewContents.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
									| System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.treeViewContents.CheckBoxes = true;
			this.treeViewContents.ImageIndex = 0;
			this.treeViewContents.ImageList = this.imageListTypeIcons;
			this.treeViewContents.Location = new System.Drawing.Point( 12, 12 );
			this.treeViewContents.Name = "treeViewContents";
			this.treeViewContents.SelectedImageIndex = 0;
			this.treeViewContents.Size = new System.Drawing.Size( 322, 406 );
			this.treeViewContents.TabIndex = 3;
			this.treeViewContents.AfterCheck += new System.Windows.Forms.TreeViewEventHandler( this.treeViewContents_AfterCheck );
			this.treeViewContents.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler( this.treeViewContents_NodeMouseClick );
			// 
			// imageListTypeIcons
			// 
			this.imageListTypeIcons.ColorDepth = System.Windows.Forms.ColorDepth.Depth32Bit;
			this.imageListTypeIcons.ImageSize = new System.Drawing.Size( 16, 16 );
			this.imageListTypeIcons.TransparentColor = System.Drawing.Color.Transparent;
			// 
			// radioButtonSceneObject
			// 
			this.radioButtonSceneObject.AutoSize = true;
			this.radioButtonSceneObject.Checked = true;
			this.radioButtonSceneObject.Location = new System.Drawing.Point( 6, 19 );
			this.radioButtonSceneObject.Name = "radioButtonSceneObject";
			this.radioButtonSceneObject.Size = new System.Drawing.Size( 87, 17 );
			this.radioButtonSceneObject.TabIndex = 4;
			this.radioButtonSceneObject.TabStop = true;
			this.radioButtonSceneObject.Text = "SceneObject";
			this.radioButtonSceneObject.UseVisualStyleBackColor = true;
			// 
			// groupBoxCreateTarget
			// 
			this.groupBoxCreateTarget.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
			this.groupBoxCreateTarget.Controls.Add( this.radioButtonProxy );
			this.groupBoxCreateTarget.Controls.Add( this.radioButtonSceneObject );
			this.groupBoxCreateTarget.Location = new System.Drawing.Point( 12, 424 );
			this.groupBoxCreateTarget.Name = "groupBoxCreateTarget";
			this.groupBoxCreateTarget.Size = new System.Drawing.Size( 185, 43 );
			this.groupBoxCreateTarget.TabIndex = 5;
			this.groupBoxCreateTarget.TabStop = false;
			this.groupBoxCreateTarget.Text = "Create";
			// 
			// radioButtonProxy
			// 
			this.radioButtonProxy.AutoSize = true;
			this.radioButtonProxy.Location = new System.Drawing.Point( 128, 19 );
			this.radioButtonProxy.Name = "radioButtonProxy";
			this.radioButtonProxy.Size = new System.Drawing.Size( 51, 17 );
			this.radioButtonProxy.TabIndex = 5;
			this.radioButtonProxy.Text = "Proxy";
			this.radioButtonProxy.UseVisualStyleBackColor = true;
			// 
			// checkBoxAutoImport
			// 
			this.checkBoxAutoImport.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
			this.checkBoxAutoImport.AutoSize = true;
			this.checkBoxAutoImport.Checked = true;
			this.checkBoxAutoImport.CheckState = System.Windows.Forms.CheckState.Checked;
			this.checkBoxAutoImport.Location = new System.Drawing.Point( 12, 473 );
			this.checkBoxAutoImport.Name = "checkBoxAutoImport";
			this.checkBoxAutoImport.Size = new System.Drawing.Size( 142, 17 );
			this.checkBoxAutoImport.TabIndex = 6;
			this.checkBoxAutoImport.Text = "Run Import automatically";
			this.checkBoxAutoImport.UseVisualStyleBackColor = true;
			// 
			// MayaImportWizardForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.buttonExit;
			this.ClientSize = new System.Drawing.Size( 346, 502 );
			this.Controls.Add( this.checkBoxAutoImport );
			this.Controls.Add( this.groupBoxCreateTarget );
			this.Controls.Add( this.treeViewContents );
			this.Controls.Add( this.buttonExit );
			this.Controls.Add( this.buttonRun );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "MayaImportWizardForm";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
			this.Text = "Import Maya Scene";
			this.TopMost = true;
			this.groupBoxCreateTarget.ResumeLayout( false );
			this.groupBoxCreateTarget.PerformLayout();
			this.ResumeLayout( false );
			this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button buttonRun;
    private System.Windows.Forms.Button buttonExit;
    private System.Windows.Forms.TreeView treeViewContents;
    private System.Windows.Forms.ImageList imageListTypeIcons;
    private System.Windows.Forms.RadioButton radioButtonSceneObject;
    private System.Windows.Forms.GroupBox groupBoxCreateTarget;
    private System.Windows.Forms.RadioButton radioButtonProxy;
    private System.Windows.Forms.CheckBox checkBoxAutoImport;
  }
}