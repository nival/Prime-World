namespace EditorLib.OutputPanel
{
	partial class OutputPanel
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

		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
      this.components = new System.ComponentModel.Container();
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(OutputPanel));
      this.listView = new System.Windows.Forms.ListView();
      this.iconHeader = new System.Windows.Forms.ColumnHeader();
      this.timeHeader = new System.Windows.Forms.ColumnHeader();
      this.headerMessage = new System.Windows.Forms.ColumnHeader();
      this.cntxMnuOutput = new System.Windows.Forms.ContextMenuStrip(this.components);
      this.copyToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.copyToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
      this.selectAllToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.toolStrip1 = new System.Windows.Forms.ToolStrip();
      this.buttonErrors = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
      this.buttonWarnings = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
      this.buttonMessages = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
      this.clear = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator4 = new System.Windows.Forms.ToolStripSeparator();
      this.save = new System.Windows.Forms.ToolStripButton();
      this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
      this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
      this.cntxMnuOutput.SuspendLayout();
      this.toolStrip1.SuspendLayout();
      this.SuspendLayout();
      // 
      // listView
      // 
      this.listView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.iconHeader,
            this.timeHeader,
            this.headerMessage});
      this.listView.ContextMenuStrip = this.cntxMnuOutput;
      this.listView.Dock = System.Windows.Forms.DockStyle.Fill;
      this.listView.FullRowSelect = true;
      this.listView.GridLines = true;
      this.listView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
      this.listView.Location = new System.Drawing.Point(0, 25);
      this.listView.Name = "listView";
      this.listView.Size = new System.Drawing.Size(514, 438);
      this.listView.TabIndex = 1;
      this.listView.UseCompatibleStateImageBehavior = false;
      this.listView.View = System.Windows.Forms.View.Details;
      // 
      // iconHeader
      // 
      this.iconHeader.Text = "";
      this.iconHeader.Width = 25;
      // 
      // headerMessage
      // 
      this.headerMessage.Text = "Message";
      this.headerMessage.Width = 300;
      // 
      // cntxMnuOutput
      // 
      this.cntxMnuOutput.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.copyToolStripMenuItem,
            this.copyToolStripMenuItem1,
            this.selectAllToolStripMenuItem});
      this.cntxMnuOutput.Name = "cntxMnuOutput";
      this.cntxMnuOutput.Size = new System.Drawing.Size(193, 70);
      // 
      // copyToolStripMenuItem
      // 
      this.copyToolStripMenuItem.Name = "copyToolStripMenuItem";
      this.copyToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C)));
      this.copyToolStripMenuItem.Size = new System.Drawing.Size(192, 22);
      this.copyToolStripMenuItem.Text = "Copy selected";
      this.copyToolStripMenuItem.Click += new System.EventHandler(this.copyToolStripMenuItem_Click);
      // 
      // copyToolStripMenuItem1
      // 
      this.copyToolStripMenuItem1.Name = "copyToolStripMenuItem1";
      this.copyToolStripMenuItem1.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.Insert)));
      this.copyToolStripMenuItem1.Size = new System.Drawing.Size(192, 22);
      this.copyToolStripMenuItem1.Text = "Copy";
      this.copyToolStripMenuItem1.Visible = false;
      // 
      // selectAllToolStripMenuItem
      // 
      this.selectAllToolStripMenuItem.Name = "selectAllToolStripMenuItem";
      this.selectAllToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A)));
      this.selectAllToolStripMenuItem.Size = new System.Drawing.Size(192, 22);
      this.selectAllToolStripMenuItem.Text = "Copy All Text";
      this.selectAllToolStripMenuItem.Click += new System.EventHandler(this.selectAllToolStripMenuItem_Click);
      // 
      // toolStrip1
      // 
      this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
      this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.buttonErrors,
            this.toolStripSeparator2,
            this.buttonWarnings,
            this.toolStripSeparator1,
            this.buttonMessages,
            this.toolStripSeparator3,
            this.clear,
            this.toolStripSeparator4,
            this.save,
            this.toolStripButton1});
      this.toolStrip1.Location = new System.Drawing.Point(0, 0);
      this.toolStrip1.Name = "toolStrip1";
      this.toolStrip1.Size = new System.Drawing.Size(514, 25);
      this.toolStrip1.TabIndex = 0;
      this.toolStrip1.Text = "toolStrip1";
      // 
      // buttonErrors
      // 
      this.buttonErrors.Checked = true;
      this.buttonErrors.CheckOnClick = true;
      this.buttonErrors.CheckState = System.Windows.Forms.CheckState.Checked;
      this.buttonErrors.Image = global::EditorLib.EditorLibResources.errorA;
      this.buttonErrors.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
      this.buttonErrors.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.buttonErrors.Name = "buttonErrors";
      this.buttonErrors.Size = new System.Drawing.Size(50, 22);
      this.buttonErrors.Text = "Error";
      this.buttonErrors.Click += new System.EventHandler(this.OnFilterClick);
      // 
      // toolStripSeparator2
      // 
      this.toolStripSeparator2.Name = "toolStripSeparator2";
      this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
      // 
      // buttonWarnings
      // 
      this.buttonWarnings.Checked = true;
      this.buttonWarnings.CheckOnClick = true;
      this.buttonWarnings.CheckState = System.Windows.Forms.CheckState.Checked;
      this.buttonWarnings.Image = global::EditorLib.EditorLibResources.warningA;
      this.buttonWarnings.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
      this.buttonWarnings.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.buttonWarnings.Name = "buttonWarnings";
      this.buttonWarnings.Size = new System.Drawing.Size(66, 22);
      this.buttonWarnings.Text = "Warning";
      this.buttonWarnings.Click += new System.EventHandler(this.OnFilterClick);
      // 
      // toolStripSeparator1
      // 
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
      // 
      // buttonMessages
      // 
      this.buttonMessages.Checked = true;
      this.buttonMessages.CheckOnClick = true;
      this.buttonMessages.CheckState = System.Windows.Forms.CheckState.Checked;
      this.buttonMessages.Image = global::EditorLib.EditorLibResources.infoA;
      this.buttonMessages.ImageScaling = System.Windows.Forms.ToolStripItemImageScaling.None;
      this.buttonMessages.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.buttonMessages.Name = "buttonMessages";
      this.buttonMessages.Size = new System.Drawing.Size(82, 22);
      this.buttonMessages.Text = "Information";
      this.buttonMessages.Click += new System.EventHandler(this.OnFilterClick);
      // 
      // toolStripSeparator3
      // 
      this.toolStripSeparator3.Name = "toolStripSeparator3";
      this.toolStripSeparator3.Size = new System.Drawing.Size(6, 25);
      // 
      // clear
      // 
      this.clear.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
      this.clear.Image = ((System.Drawing.Image)(resources.GetObject("clear.Image")));
      this.clear.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.clear.Name = "clear";
      this.clear.Size = new System.Drawing.Size(36, 22);
      this.clear.Text = "Clear";
      this.clear.Click += new System.EventHandler(this.OnClearClick);
      // 
      // toolStripSeparator4
      // 
      this.toolStripSeparator4.Name = "toolStripSeparator4";
      this.toolStripSeparator4.Size = new System.Drawing.Size(6, 25);
      // 
      // save
      // 
      this.save.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
      this.save.Image = ((System.Drawing.Image)(resources.GetObject("save.Image")));
      this.save.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.save.Name = "save";
      this.save.Size = new System.Drawing.Size(35, 22);
      this.save.Text = "Save";
      this.save.Click += new System.EventHandler(this.OnSaveClick);
      // 
      // toolStripButton1
      // 
      this.toolStripButton1.Alignment = System.Windows.Forms.ToolStripItemAlignment.Right;
      this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
      this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
      this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.toolStripButton1.Name = "toolStripButton1";
      this.toolStripButton1.Size = new System.Drawing.Size(79, 22);
      this.toolStripButton1.Text = "Copy selected";
      this.toolStripButton1.Click += new System.EventHandler(this.copyToolStripMenuItem_Click);
      // 
      // saveFileDialog1
      // 
      this.saveFileDialog1.Filter = "Plain Text|*.txt";
      this.saveFileDialog1.RestoreDirectory = true;
      this.saveFileDialog1.Title = "Save in Text File";
      // 
      // OutputPanel
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(514, 463);
      this.Controls.Add(this.listView);
      this.Controls.Add(this.toolStrip1);
      this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
      this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
      this.Name = "OutputPanel";
      this.TabText = "Output";
      this.Text = "Output";
      this.cntxMnuOutput.ResumeLayout(false);
      this.toolStrip1.ResumeLayout(false);
      this.toolStrip1.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.ListView listView;
		private System.Windows.Forms.ToolStrip toolStrip1;
		private System.Windows.Forms.ToolStripButton buttonWarnings;
		private System.Windows.Forms.ToolStripButton buttonMessages;
		private System.Windows.Forms.ToolStripButton buttonErrors;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator3;
		private System.Windows.Forms.ToolStripButton clear;
		private System.Windows.Forms.ToolStripSeparator toolStripSeparator4;
		private System.Windows.Forms.ToolStripButton save;
		private System.Windows.Forms.ColumnHeader iconHeader;
		private System.Windows.Forms.ColumnHeader headerMessage;
		private System.Windows.Forms.SaveFileDialog saveFileDialog1;
    private System.Windows.Forms.ToolStripButton toolStripButton1;
    private System.Windows.Forms.ContextMenuStrip cntxMnuOutput;
    private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem copyToolStripMenuItem1;
    private System.Windows.Forms.ToolStripMenuItem selectAllToolStripMenuItem;
    private System.Windows.Forms.ColumnHeader timeHeader;
	}
}
