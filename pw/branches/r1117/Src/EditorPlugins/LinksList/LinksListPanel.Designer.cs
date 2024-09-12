namespace EditorPlugins.LinksList
{
  partial class LinksListPanel
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
      this.toolStrip1 = new System.Windows.Forms.ToolStrip();
      this.toolStripLabel1 = new System.Windows.Forms.ToolStripLabel();
      this.levelsCountText = new System.Windows.Forms.ToolStripTextBox();
      this.moreLevelsButton = new System.Windows.Forms.ToolStripButton();
      this.lessLevelsButton = new System.Windows.Forms.ToolStripButton();
      this.allLevelsButton = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
      this.lockFileNameButton = new System.Windows.Forms.ToolStripButton();
      this.fileNameText = new System.Windows.Forms.ToolStripTextBox();
      this.listView = new System.Windows.Forms.ListView();
      this.number = new System.Windows.Forms.ColumnHeader();
      this.fileName = new System.Windows.Forms.ColumnHeader();
      this.type = new System.Windows.Forms.ColumnHeader();
      this.toolStrip1.SuspendLayout();
      this.SuspendLayout();
      // 
      // toolStrip1
      // 
      this.toolStrip1.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.toolStripLabel1,
            this.levelsCountText,
            this.moreLevelsButton,
            this.lessLevelsButton,
            this.allLevelsButton,
            this.toolStripSeparator1,
            this.lockFileNameButton,
            this.fileNameText} );
      this.toolStrip1.Location = new System.Drawing.Point( 0, 0 );
      this.toolStrip1.Name = "toolStrip1";
      this.toolStrip1.Size = new System.Drawing.Size( 511, 25 );
      this.toolStrip1.TabIndex = 0;
      this.toolStrip1.Text = "toolStrip1";
      // 
      // toolStripLabel1
      // 
      this.toolStripLabel1.Name = "toolStripLabel1";
      this.toolStripLabel1.Size = new System.Drawing.Size( 81, 22 );
      this.toolStripLabel1.Text = "Layers shown:";
      // 
      // levelsCountText
      // 
      this.levelsCountText.Name = "levelsCountText";
      this.levelsCountText.ReadOnly = true;
      this.levelsCountText.Size = new System.Drawing.Size( 30, 25 );
      // 
      // moreLevelsButton
      // 
      this.moreLevelsButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.moreLevelsButton.Image = global::EditorPlugins.EditorPluginResources.ZoomIn;
      this.moreLevelsButton.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.moreLevelsButton.Name = "moreLevelsButton";
      this.moreLevelsButton.Size = new System.Drawing.Size( 23, 22 );
      this.moreLevelsButton.Text = "toolStripButton1";
      this.moreLevelsButton.ToolTipText = "Show more levels in hierarchy";
      this.moreLevelsButton.Click += new System.EventHandler( this.moreLevelsButton_Click );
      // 
      // lessLevelsButton
      // 
      this.lessLevelsButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.lessLevelsButton.Image = global::EditorPlugins.EditorPluginResources.ZoomOut;
      this.lessLevelsButton.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.lessLevelsButton.Name = "lessLevelsButton";
      this.lessLevelsButton.Size = new System.Drawing.Size( 23, 22 );
      this.lessLevelsButton.Text = "toolStripButton1";
      this.lessLevelsButton.ToolTipText = "Show less levels of hierarchy";
      this.lessLevelsButton.Click += new System.EventHandler( this.lessLevelsButton_Click );
      // 
      // allLevelsButton
      // 
      this.allLevelsButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.allLevelsButton.Image = global::EditorPlugins.EditorPluginResources.add_create;
      this.allLevelsButton.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.allLevelsButton.Name = "allLevelsButton";
      this.allLevelsButton.Size = new System.Drawing.Size( 23, 22 );
      this.allLevelsButton.Text = "toolStripButton1";
      this.allLevelsButton.ToolTipText = "Show all linked files";
      this.allLevelsButton.Click += new System.EventHandler( this.allLevelsButton_Click );
      // 
      // toolStripSeparator1
      // 
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new System.Drawing.Size( 6, 25 );
      // 
      // lockFileNameButton
      // 
      this.lockFileNameButton.CheckOnClick = true;
      this.lockFileNameButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.lockFileNameButton.Image = global::EditorPlugins.EditorPluginResources.LockObjects;
      this.lockFileNameButton.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.lockFileNameButton.Name = "lockFileNameButton";
      this.lockFileNameButton.Size = new System.Drawing.Size( 23, 22 );
      this.lockFileNameButton.Text = "toolStripButton1";
      this.lockFileNameButton.ToolTipText = "Lock selected file";
      // 
      // fileNameText
      // 
      this.fileNameText.MaxLength = 256;
      this.fileNameText.Name = "fileNameText";
      this.fileNameText.ReadOnly = true;
      this.fileNameText.Size = new System.Drawing.Size( 400, 23 );
      // 
      // listView
      // 
      this.listView.Columns.AddRange( new System.Windows.Forms.ColumnHeader[] {
            this.number,
            this.fileName,
            this.type} );
      this.listView.Dock = System.Windows.Forms.DockStyle.Fill;
      this.listView.FullRowSelect = true;
      this.listView.Location = new System.Drawing.Point( 0, 25 );
      this.listView.MultiSelect = false;
      this.listView.Name = "listView";
      this.listView.ShowItemToolTips = true;
      this.listView.Size = new System.Drawing.Size( 511, 241 );
      this.listView.Sorting = System.Windows.Forms.SortOrder.Ascending;
      this.listView.TabIndex = 1;
      this.listView.UseCompatibleStateImageBehavior = false;
      this.listView.View = System.Windows.Forms.View.Details;
      this.listView.MouseClick += new System.Windows.Forms.MouseEventHandler( this.listView_MouseClick );
      this.listView.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler( this.listView_ColumnClick );
      // 
      // number
      // 
      this.number.Text = "Level";
      this.number.Width = 40;
      // 
      // fileName
      // 
      this.fileName.DisplayIndex = 2;
      this.fileName.Text = "File name";
      this.fileName.Width = 400;
      // 
      // type
      // 
      this.type.DisplayIndex = 1;
      this.type.Text = "Type";
      this.type.Width = 120;
      // 
      // LinksListPanel
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 511, 266 );
      this.Controls.Add( this.listView );
      this.Controls.Add( this.toolStrip1 );
      this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.Name = "LinksListPanel";
      this.Text = "LinksListPanel";
      this.toolStrip1.ResumeLayout( false );
      this.toolStrip1.PerformLayout();
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.ToolStrip toolStrip1;
    private System.Windows.Forms.ToolStripLabel toolStripLabel1;
    private System.Windows.Forms.ToolStripTextBox levelsCountText;
    private System.Windows.Forms.ToolStripButton moreLevelsButton;
    private System.Windows.Forms.ToolStripButton lessLevelsButton;
    private System.Windows.Forms.ToolStripButton allLevelsButton;
    private System.Windows.Forms.ToolStripTextBox fileNameText;
    private System.Windows.Forms.ListView listView;
    private System.Windows.Forms.ColumnHeader number;
    private System.Windows.Forms.ColumnHeader fileName;
    private System.Windows.Forms.ColumnHeader type;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
    private System.Windows.Forms.ToolStripButton lockFileNameButton;
  }
}