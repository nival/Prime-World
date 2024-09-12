namespace EditorLib.Scripts
{
  partial class ScriptsPanel
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
			this.toolStrip = new System.Windows.Forms.ToolStrip();
			this.buttonAdd = new System.Windows.Forms.ToolStripButton();
			this.buttonRemove = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
			this.buttonRun = new System.Windows.Forms.ToolStripButton();
			this.buttonStop = new System.Windows.Forms.ToolStripButton();
			this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
			this.lvScripts = new System.Windows.Forms.ListView();
			this.colFileName = new System.Windows.Forms.ColumnHeader();
			this.colFilePath = new System.Windows.Forms.ColumnHeader();
			this.colAbout = new System.Windows.Forms.ColumnHeader();
			this.toolStrip.SuspendLayout();
			this.SuspendLayout();
			// 
			// toolStrip
			// 
			this.toolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
			this.toolStrip.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.buttonAdd,
            this.buttonRemove,
            this.toolStripSeparator1,
            this.buttonRun,
            this.buttonStop} );
			this.toolStrip.Location = new System.Drawing.Point( 0, 0 );
			this.toolStrip.Name = "toolStrip";
			this.toolStrip.Size = new System.Drawing.Size( 335, 25 );
			this.toolStrip.TabIndex = 0;
			this.toolStrip.Text = "toolStrip1";
			// 
			// buttonAdd
			// 
			this.buttonAdd.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.buttonAdd.Image = global::EditorLib.EditorLibResources.add_script;
			this.buttonAdd.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.buttonAdd.Name = "buttonAdd";
			this.buttonAdd.Size = new System.Drawing.Size( 23, 22 );
			this.buttonAdd.Text = "Add";
			this.buttonAdd.Click += new System.EventHandler( this.OnAddClick );
			// 
			// buttonRemove
			// 
			this.buttonRemove.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.buttonRemove.Image = global::EditorLib.EditorLibResources.remove_script;
			this.buttonRemove.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.buttonRemove.Name = "buttonRemove";
			this.buttonRemove.Size = new System.Drawing.Size( 23, 22 );
			this.buttonRemove.Text = "Remove";
			this.buttonRemove.Click += new System.EventHandler( this.OnRemoveClick );
			// 
			// toolStripSeparator1
			// 
			this.toolStripSeparator1.Name = "toolStripSeparator1";
			this.toolStripSeparator1.Size = new System.Drawing.Size( 6, 25 );
			// 
			// buttonRun
			// 
			this.buttonRun.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.buttonRun.Image = global::EditorLib.EditorLibResources.run_script;
			this.buttonRun.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.buttonRun.Name = "buttonRun";
			this.buttonRun.Size = new System.Drawing.Size( 23, 22 );
			this.buttonRun.Text = "Run script";
			this.buttonRun.Click += new System.EventHandler( this.OnRunClick );
			// 
			// buttonStop
			// 
			this.buttonStop.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.buttonStop.Image = global::EditorLib.EditorLibResources.stop_script;
			this.buttonStop.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.buttonStop.Name = "buttonStop";
			this.buttonStop.Size = new System.Drawing.Size( 23, 22 );
			this.buttonStop.Text = "toolStripButton4";
			this.buttonStop.Visible = false;
			// 
			// openFileDialog
			// 
			this.openFileDialog.Filter = "C# files (*.cs)|*.cs|All files (*.*)|*.*";
			this.openFileDialog.RestoreDirectory = true;
			this.openFileDialog.Title = "Select Script Source File";
			// 
			// lvScripts
			// 
			this.lvScripts.Columns.AddRange( new System.Windows.Forms.ColumnHeader[] {
            this.colFileName,
            this.colFilePath,
            this.colAbout} );
			this.lvScripts.Dock = System.Windows.Forms.DockStyle.Fill;
			this.lvScripts.FullRowSelect = true;
			this.lvScripts.GridLines = true;
			this.lvScripts.Location = new System.Drawing.Point( 0, 25 );
			this.lvScripts.Name = "lvScripts";
			this.lvScripts.Size = new System.Drawing.Size( 335, 239 );
			this.lvScripts.TabIndex = 2;
			this.lvScripts.UseCompatibleStateImageBehavior = false;
			this.lvScripts.View = System.Windows.Forms.View.Details;
			// 
			// colFileName
			// 
			this.colFileName.Text = "File Name";
			this.colFileName.Width = 80;
			// 
			// colFilePath
			// 
			this.colFilePath.Text = "Path";
			this.colFilePath.Width = 100;
			// 
			// colAbout
			// 
			this.colAbout.Text = "About";
			this.colAbout.Width = 150;
			// 
			// ScriptsPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 335, 264 );
			this.Controls.Add( this.lvScripts );
			this.Controls.Add( this.toolStrip );
			this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "ScriptsPanel";
			this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.Float;
			this.TabText = "Scripts";
			this.Text = "Scripts";
			this.toolStrip.ResumeLayout( false );
			this.toolStrip.PerformLayout();
			this.ResumeLayout( false );
			this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.ToolStrip toolStrip;
    private System.Windows.Forms.ToolStripButton buttonAdd;
    private System.Windows.Forms.ToolStripButton buttonRemove;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
    private System.Windows.Forms.ToolStripButton buttonRun;
    private System.Windows.Forms.ToolStripButton buttonStop;
    private System.Windows.Forms.OpenFileDialog openFileDialog;
    private System.Windows.Forms.ListView lvScripts;
    private System.Windows.Forms.ColumnHeader colFileName;
    private System.Windows.Forms.ColumnHeader colFilePath;
		private System.Windows.Forms.ColumnHeader colAbout;
  }
}