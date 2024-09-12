namespace EditorLib.PropertiesEditor
{
	partial class PropertiesEditorControl
	{
		/// <summary> 
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;



		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
      this.propertyGrid = new System.Windows.Forms.PropertyGrid();
      this.messageLabel = new System.Windows.Forms.Label();
      this.propertyEditorToolStrip = new System.Windows.Forms.ToolStrip();
      this.AddItemLast = new System.Windows.Forms.ToolStripButton();
      this.AddListItem = new System.Windows.Forms.ToolStripButton();
      this.DeleteListItem = new System.Windows.Forms.ToolStripButton();
      this.ClearList = new System.Windows.Forms.ToolStripButton();
      this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
      this.btnMoveUpItem = new System.Windows.Forms.ToolStripButton();
      this.btnMoveDownItem = new System.Windows.Forms.ToolStripButton();
      this.cboStates = new System.Windows.Forms.ToolStripComboBox();
      this.propertyEditorToolStrip.SuspendLayout();
      this.SuspendLayout();
      // 
      // propertyGrid
      // 
      this.propertyGrid.Dock = System.Windows.Forms.DockStyle.Fill;
      this.propertyGrid.LineColor = System.Drawing.SystemColors.ControlLight;
      this.propertyGrid.Location = new System.Drawing.Point( 0, 25 );
      this.propertyGrid.Name = "propertyGrid";
      this.propertyGrid.PropertySort = System.Windows.Forms.PropertySort.NoSort;
      this.propertyGrid.Size = new System.Drawing.Size( 412, 428 );
      this.propertyGrid.TabIndex = 4;
      this.propertyGrid.TabStop = false;
      this.propertyGrid.ToolbarVisible = false;
      this.propertyGrid.SelectedGridItemChanged += new System.Windows.Forms.SelectedGridItemChangedEventHandler( this.propertyGrid_SelectedGridItemChanged );
      this.propertyGrid.PropertyValueChanged += new System.Windows.Forms.PropertyValueChangedEventHandler( this.propertyGrid_PropertyValueChanged );
      // 
      // messageLabel
      // 
      this.messageLabel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
      this.messageLabel.Dock = System.Windows.Forms.DockStyle.Fill;
      this.messageLabel.Location = new System.Drawing.Point( 0, 0 );
      this.messageLabel.Name = "messageLabel";
      this.messageLabel.Size = new System.Drawing.Size( 412, 453 );
      this.messageLabel.TabIndex = 6;
      this.messageLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      // 
      // propertyEditorToolStrip
      // 
      this.propertyEditorToolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
      this.propertyEditorToolStrip.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.AddItemLast,
            this.AddListItem,
            this.DeleteListItem,
            this.ClearList,
            this.toolStripSeparator1,
            this.btnMoveUpItem,
            this.btnMoveDownItem,
            this.cboStates} );
      this.propertyEditorToolStrip.Location = new System.Drawing.Point( 0, 0 );
      this.propertyEditorToolStrip.Name = "propertyEditorToolStrip";
      this.propertyEditorToolStrip.Size = new System.Drawing.Size( 412, 25 );
      this.propertyEditorToolStrip.TabIndex = 9;
      // 
      // AddItemLast
      // 
      this.AddItemLast.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.AddItemLast.Enabled = false;
      this.AddItemLast.Image = global::EditorLib.EditorLibResources.InsertLast;
      this.AddItemLast.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.AddItemLast.Name = "AddItemLast";
      this.AddItemLast.Size = new System.Drawing.Size( 23, 22 );
      this.AddItemLast.Text = "Add ListItem to end of list";
      this.AddItemLast.ToolTipText = "Add an item to the end of the selected list";
      this.AddItemLast.Click += new System.EventHandler( this.AddItemLast_Click );
      // 
      // AddListItem
      // 
      this.AddListItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.AddListItem.Enabled = false;
      this.AddListItem.Image = global::EditorLib.EditorLibResources.InsertBefore;
      this.AddListItem.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.AddListItem.Name = "AddListItem";
      this.AddListItem.Size = new System.Drawing.Size( 23, 22 );
      this.AddListItem.Text = "Add ListItem";
      this.AddListItem.ToolTipText = "Insert an item into the selected list";
      this.AddListItem.Click += new System.EventHandler( this.AddListItem_Click );
      // 
      // DeleteListItem
      // 
      this.DeleteListItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.DeleteListItem.Enabled = false;
      this.DeleteListItem.Image = global::EditorLib.EditorLibResources.RemoveItem;
      this.DeleteListItem.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.DeleteListItem.Name = "DeleteListItem";
      this.DeleteListItem.Size = new System.Drawing.Size( 23, 22 );
      this.DeleteListItem.Text = "Delete ListItem";
      this.DeleteListItem.ToolTipText = "Remove the selected list element";
      this.DeleteListItem.Click += new System.EventHandler( this.DeleteListItem_Click );
      // 
      // ClearList
      // 
      this.ClearList.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.ClearList.Enabled = false;
      this.ClearList.Image = global::EditorLib.EditorLibResources.ClearItems;
      this.ClearList.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.ClearList.Name = "ClearList";
      this.ClearList.Size = new System.Drawing.Size( 23, 22 );
      this.ClearList.Text = "Clear List";
      this.ClearList.ToolTipText = "Clear the selected list";
      this.ClearList.Click += new System.EventHandler( this.ClearList_Click );
      // 
      // toolStripSeparator1
      // 
      this.toolStripSeparator1.Name = "toolStripSeparator1";
      this.toolStripSeparator1.Size = new System.Drawing.Size( 6, 25 );
      // 
      // btnMoveUpItem
      // 
      this.btnMoveUpItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnMoveUpItem.Enabled = false;
      this.btnMoveUpItem.Image = global::EditorLib.EditorLibResources.move_up;
      this.btnMoveUpItem.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnMoveUpItem.Name = "btnMoveUpItem";
      this.btnMoveUpItem.Size = new System.Drawing.Size( 23, 22 );
      this.btnMoveUpItem.Text = "Move Item Up";
      this.btnMoveUpItem.Click += new System.EventHandler( this.MoveUpListItem_Click );
      // 
      // btnMoveDownItem
      // 
      this.btnMoveDownItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
      this.btnMoveDownItem.Enabled = false;
      this.btnMoveDownItem.Image = global::EditorLib.EditorLibResources.move_down;
      this.btnMoveDownItem.ImageTransparentColor = System.Drawing.Color.Magenta;
      this.btnMoveDownItem.Name = "btnMoveDownItem";
      this.btnMoveDownItem.RightToLeftAutoMirrorImage = true;
      this.btnMoveDownItem.Size = new System.Drawing.Size( 23, 22 );
      this.btnMoveDownItem.Text = "Move Item Down";
      this.btnMoveDownItem.Click += new System.EventHandler( this.MoveDownListItem );
      // 
      // cboStates
      // 
      this.cboStates.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
      this.cboStates.FlatStyle = System.Windows.Forms.FlatStyle.Standard;
      this.cboStates.Name = "cboStates";
      this.cboStates.Size = new System.Drawing.Size( 121, 25 );
      // 
      // PropertiesEditorControl
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.Controls.Add( this.propertyGrid );
      this.Controls.Add( this.propertyEditorToolStrip );
      this.Controls.Add( this.messageLabel );
      this.Name = "PropertiesEditorControl";
      this.Size = new System.Drawing.Size( 412, 453 );
      this.propertyEditorToolStrip.ResumeLayout( false );
      this.propertyEditorToolStrip.PerformLayout();
      this.ResumeLayout( false );
      this.PerformLayout();

		}

		#endregion

    private System.Windows.Forms.PropertyGrid propertyGrid;
    private System.Windows.Forms.Label messageLabel;
    private System.Windows.Forms.ToolStrip propertyEditorToolStrip;
    private System.Windows.Forms.ToolStripButton AddItemLast;
    private System.Windows.Forms.ToolStripButton AddListItem;
    private System.Windows.Forms.ToolStripButton DeleteListItem;
    private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
    private System.Windows.Forms.ToolStripButton ClearList;
    private System.Windows.Forms.ToolStripButton btnMoveUpItem;
    private System.Windows.Forms.ToolStripButton btnMoveDownItem;
    private System.Windows.Forms.ToolStripComboBox cboStates;


	}
}
