namespace EditorLib.Wizards.TableDataEditing
{
  partial class TableDataPanel
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
			this.components = new System.ComponentModel.Container();
			this.grdData = new System.Windows.Forms.DataGridView();
			this.mnuPopup = new System.Windows.Forms.ContextMenuStrip( this.components );
			this.mnuCopy = new System.Windows.Forms.ToolStripMenuItem();
			this.mnuPaste = new System.Windows.Forms.ToolStripMenuItem();
			this.mnuPasteForSelection = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
			this.mnuSelectAll = new System.Windows.Forms.ToolStripMenuItem();
			this.mnuReset = new System.Windows.Forms.ToolStripMenuItem();
			this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
			this.mnuShowPE = new System.Windows.Forms.ToolStripMenuItem();
			this.cboColumns = new System.Windows.Forms.ComboBox();
			this.txtFilter = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.cboPreset = new System.Windows.Forms.ComboBox();
			this.label2 = new System.Windows.Forms.Label();
			this.btnLoad = new System.Windows.Forms.Button();
			this.panel3 = new System.Windows.Forms.Panel();
			this.panel2 = new System.Windows.Forms.Panel();
			this.btnManagePreset = new System.Windows.Forms.Button();
			this.panel4 = new System.Windows.Forms.Panel();
			this.lblNoData = new System.Windows.Forms.Label();
			( (System.ComponentModel.ISupportInitialize)( this.grdData ) ).BeginInit();
			this.mnuPopup.SuspendLayout();
			this.panel3.SuspendLayout();
			this.panel2.SuspendLayout();
			this.panel4.SuspendLayout();
			this.SuspendLayout();
			// 
			// grdData
			// 
			this.grdData.AllowUserToAddRows = false;
			this.grdData.AllowUserToDeleteRows = false;
			this.grdData.AllowUserToOrderColumns = true;
			this.grdData.AllowUserToResizeRows = false;
			this.grdData.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
			this.grdData.ContextMenuStrip = this.mnuPopup;
			this.grdData.Dock = System.Windows.Forms.DockStyle.Fill;
			this.grdData.Location = new System.Drawing.Point( 4, 40 );
			this.grdData.Name = "grdData";
			this.grdData.RowHeadersVisible = false;
			this.grdData.Size = new System.Drawing.Size( 733, 469 );
			this.grdData.TabIndex = 4;
			this.grdData.ColumnHeaderMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler( this.OnColumnHeaderClick );
			this.grdData.CellParsing += new System.Windows.Forms.DataGridViewCellParsingEventHandler( this.OnCellParsing );
			this.grdData.CellFormatting += new System.Windows.Forms.DataGridViewCellFormattingEventHandler( this.OnCellFormatting );
			this.grdData.KeyUp += new System.Windows.Forms.KeyEventHandler( this.grdData_KeyUp );
			// 
			// mnuPopup
			// 
			this.mnuPopup.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.mnuCopy,
            this.mnuPaste,
            this.mnuPasteForSelection,
            this.toolStripMenuItem1,
            this.mnuSelectAll,
            this.mnuReset,
            this.toolStripMenuItem2,
            this.mnuShowPE} );
			this.mnuPopup.Name = "mnuPupup";
			this.mnuPopup.Size = new System.Drawing.Size( 247, 148 );
			// 
			// mnuCopy
			// 
			this.mnuCopy.Name = "mnuCopy";
			this.mnuCopy.ShortcutKeyDisplayString = "";
			this.mnuCopy.ShortcutKeys = ( (System.Windows.Forms.Keys)( ( System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.C ) ) );
			this.mnuCopy.Size = new System.Drawing.Size( 246, 22 );
			this.mnuCopy.Text = "Copy";
			this.mnuCopy.Click += new System.EventHandler( this.mnuCopy_Click );
			// 
			// mnuPaste
			// 
			this.mnuPaste.Name = "mnuPaste";
			this.mnuPaste.ShortcutKeyDisplayString = "";
			this.mnuPaste.ShortcutKeys = ( (System.Windows.Forms.Keys)( ( System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.V ) ) );
			this.mnuPaste.Size = new System.Drawing.Size( 246, 22 );
			this.mnuPaste.Text = "Paste";
			this.mnuPaste.Click += new System.EventHandler( this.mnuPaste_Click );
			// 
			// mnuPasteForSelection
			// 
			this.mnuPasteForSelection.Name = "mnuPasteForSelection";
			this.mnuPasteForSelection.Size = new System.Drawing.Size( 246, 22 );
			this.mnuPasteForSelection.Text = "Paste for Selection";
			this.mnuPasteForSelection.Click += new System.EventHandler( this.mnuPasteForSelection_Click );
			// 
			// toolStripMenuItem1
			// 
			this.toolStripMenuItem1.Name = "toolStripMenuItem1";
			this.toolStripMenuItem1.Size = new System.Drawing.Size( 243, 6 );
			// 
			// mnuSelectAll
			// 
			this.mnuSelectAll.Name = "mnuSelectAll";
			this.mnuSelectAll.ShortcutKeys = ( (System.Windows.Forms.Keys)( ( System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.A ) ) );
			this.mnuSelectAll.Size = new System.Drawing.Size( 246, 22 );
			this.mnuSelectAll.Text = "Select All";
			this.mnuSelectAll.Click += new System.EventHandler( this.mnuSelectAll_Click );
			// 
			// mnuReset
			// 
			this.mnuReset.Name = "mnuReset";
			this.mnuReset.Size = new System.Drawing.Size( 246, 22 );
			this.mnuReset.Text = "Reset";
			this.mnuReset.Click += new System.EventHandler( this.mnuReset_Click );
			// 
			// toolStripMenuItem2
			// 
			this.toolStripMenuItem2.Name = "toolStripMenuItem2";
			this.toolStripMenuItem2.Size = new System.Drawing.Size( 243, 6 );
			// 
			// mnuShowPE
			// 
			this.mnuShowPE.Name = "mnuShowPE";
			this.mnuShowPE.ShortcutKeyDisplayString = "";
			this.mnuShowPE.ShortcutKeys = ( (System.Windows.Forms.Keys)( ( System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.E ) ) );
			this.mnuShowPE.Size = new System.Drawing.Size( 246, 22 );
			this.mnuShowPE.Text = "Show in Properties Editor";
			this.mnuShowPE.Click += new System.EventHandler( this.mnuShowPE_Click );
			// 
			// cboColumns
			// 
			this.cboColumns.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cboColumns.FormattingEnabled = true;
			this.cboColumns.Location = new System.Drawing.Point( 37, 3 );
			this.cboColumns.Name = "cboColumns";
			this.cboColumns.Size = new System.Drawing.Size( 162, 21 );
			this.cboColumns.TabIndex = 2;
			// 
			// txtFilter
			// 
			this.txtFilter.Location = new System.Drawing.Point( 205, 3 );
			this.txtFilter.Name = "txtFilter";
			this.txtFilter.Size = new System.Drawing.Size( 129, 20 );
			this.txtFilter.TabIndex = 3;
			this.txtFilter.TextChanged += new System.EventHandler( this.OnFilterTextChanged );
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point( 6, 8 );
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size( 37, 13 );
			this.label1.TabIndex = 3;
			this.label1.Text = "Preset";
			// 
			// cboPreset
			// 
			this.cboPreset.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cboPreset.FormattingEnabled = true;
			this.cboPreset.Location = new System.Drawing.Point( 49, 4 );
			this.cboPreset.Name = "cboPreset";
			this.cboPreset.Size = new System.Drawing.Size( 162, 21 );
			this.cboPreset.TabIndex = 0;
			this.cboPreset.SelectedIndexChanged += new System.EventHandler( this.OnPresetSelected );
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point( 2, 7 );
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size( 29, 13 );
			this.label2.TabIndex = 6;
			this.label2.Text = "Filter";
			// 
			// btnLoad
			// 
			this.btnLoad.Enabled = false;
			this.btnLoad.Location = new System.Drawing.Point( 267, 3 );
			this.btnLoad.Name = "btnLoad";
			this.btnLoad.Size = new System.Drawing.Size( 75, 23 );
			this.btnLoad.TabIndex = 1;
			this.btnLoad.Text = "Load";
			this.btnLoad.UseVisualStyleBackColor = true;
			this.btnLoad.Click += new System.EventHandler( this.OnLoadClick );
			// 
			// panel3
			// 
			this.panel3.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.panel3.Controls.Add( this.cboColumns );
			this.panel3.Controls.Add( this.txtFilter );
			this.panel3.Controls.Add( this.label2 );
			this.panel3.Location = new System.Drawing.Point( 393, 3 );
			this.panel3.Name = "panel3";
			this.panel3.Size = new System.Drawing.Size( 337, 29 );
			this.panel3.TabIndex = 9;
			// 
			// panel2
			// 
			this.panel2.Controls.Add( this.btnLoad );
			this.panel2.Controls.Add( this.btnManagePreset );
			this.panel2.Controls.Add( this.label1 );
			this.panel2.Controls.Add( this.cboPreset );
			this.panel2.Location = new System.Drawing.Point( 3, 3 );
			this.panel2.Name = "panel2";
			this.panel2.Size = new System.Drawing.Size( 345, 29 );
			this.panel2.TabIndex = 8;
			// 
			// btnManagePreset
			// 
			this.btnManagePreset.Image = global::EditorLib.EditorLibResources.manage;
			this.btnManagePreset.Location = new System.Drawing.Point( 217, 3 );
			this.btnManagePreset.Name = "btnManagePreset";
			this.btnManagePreset.Size = new System.Drawing.Size( 23, 23 );
			this.btnManagePreset.TabIndex = 11;
			this.btnManagePreset.UseVisualStyleBackColor = true;
			this.btnManagePreset.Click += new System.EventHandler( this.btnManagePreset_Click );
			// 
			// panel4
			// 
			this.panel4.Controls.Add( this.panel2 );
			this.panel4.Controls.Add( this.panel3 );
			this.panel4.Dock = System.Windows.Forms.DockStyle.Top;
			this.panel4.Location = new System.Drawing.Point( 4, 4 );
			this.panel4.MinimumSize = new System.Drawing.Size( 648, 36 );
			this.panel4.Name = "panel4";
			this.panel4.Size = new System.Drawing.Size( 733, 36 );
			this.panel4.TabIndex = 10;
			// 
			// lblNoData
			// 
			this.lblNoData.BackColor = System.Drawing.SystemColors.AppWorkspace;
			this.lblNoData.Dock = System.Windows.Forms.DockStyle.Fill;
			this.lblNoData.Font = new System.Drawing.Font( "Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
			this.lblNoData.Location = new System.Drawing.Point( 4, 40 );
			this.lblNoData.Name = "lblNoData";
			this.lblNoData.Size = new System.Drawing.Size( 733, 469 );
			this.lblNoData.TabIndex = 11;
			this.lblNoData.Text = "No Data Loaded";
			this.lblNoData.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			// 
			// TableDataPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.AutoScroll = true;
			this.ClientSize = new System.Drawing.Size( 741, 513 );
			this.Controls.Add( this.lblNoData );
			this.Controls.Add( this.grdData );
			this.Controls.Add( this.panel4 );
			this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
			this.Name = "TableDataPanel";
			this.Padding = new System.Windows.Forms.Padding( 4 );
			this.Text = "TableDataForm";
			( (System.ComponentModel.ISupportInitialize)( this.grdData ) ).EndInit();
			this.mnuPopup.ResumeLayout( false );
			this.panel3.ResumeLayout( false );
			this.panel3.PerformLayout();
			this.panel2.ResumeLayout( false );
			this.panel2.PerformLayout();
			this.panel4.ResumeLayout( false );
			this.ResumeLayout( false );

    }

    #endregion

		private System.Windows.Forms.DataGridView grdData;
		private System.Windows.Forms.ContextMenuStrip mnuPopup;
		private System.Windows.Forms.ToolStripMenuItem mnuCopy;
		private System.Windows.Forms.ToolStripMenuItem mnuPaste;
		private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
		private System.Windows.Forms.ToolStripMenuItem mnuReset;
		private System.Windows.Forms.TextBox txtFilter;
		private System.Windows.Forms.ComboBox cboColumns;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.ComboBox cboPreset;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Button btnLoad;
    private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
    private System.Windows.Forms.ToolStripMenuItem mnuShowPE;
    private System.Windows.Forms.Panel panel2;
    private System.Windows.Forms.Panel panel3;
    private System.Windows.Forms.Panel panel4;
		private System.Windows.Forms.ToolStripMenuItem mnuSelectAll;
		private System.Windows.Forms.ToolStripMenuItem mnuPasteForSelection;
		private System.Windows.Forms.Button btnManagePreset;
		private System.Windows.Forms.Label lblNoData;

  }
}