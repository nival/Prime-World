namespace EditorLib.PropertiesEditor.PropertyPresets
{
  partial class EditorConfigEditForm
  {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null))
      {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.listViewSelected = new System.Windows.Forms.ListView();
      this.columnVis = new System.Windows.Forms.ColumnHeader();
      this.columnEdit = new System.Windows.Forms.ColumnHeader();
      this.columnExpand = new System.Windows.Forms.ColumnHeader();
      this.columnName = new System.Windows.Forms.ColumnHeader();
      this.listViewAll = new System.Windows.Forms.ListView();
      this.columnHeader1 = new System.Windows.Forms.ColumnHeader();
      this.buttonOk = new System.Windows.Forms.Button();
      this.buttonCancel = new System.Windows.Forms.Button();
      this.buttonMoveUp = new System.Windows.Forms.Button();
      this.buttonMoveDown = new System.Windows.Forms.Button();
      this.labelLeft = new System.Windows.Forms.Label();
      this.labelRight = new System.Windows.Forms.Label();
      this.buttonReset = new System.Windows.Forms.Button();
      this.checkBoxShowAll = new System.Windows.Forms.CheckBox();
      this.SuspendLayout();
      // 
      // listViewSelected
      // 
      this.listViewSelected.Columns.AddRange( new System.Windows.Forms.ColumnHeader[] {
            this.columnVis,
            this.columnEdit,
            this.columnExpand,
            this.columnName} );
      this.listViewSelected.FullRowSelect = true;
      this.listViewSelected.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
      this.listViewSelected.HideSelection = false;
      this.listViewSelected.Location = new System.Drawing.Point( 235, 25 );
      this.listViewSelected.MultiSelect = false;
      this.listViewSelected.Name = "listViewSelected";
      this.listViewSelected.OwnerDraw = true;
      this.listViewSelected.ShowGroups = false;
      this.listViewSelected.Size = new System.Drawing.Size( 275, 420 );
      this.listViewSelected.TabIndex = 1;
      this.listViewSelected.UseCompatibleStateImageBehavior = false;
      this.listViewSelected.View = System.Windows.Forms.View.Details;
      this.listViewSelected.SelectedIndexChanged += new System.EventHandler( this.listViewSelected_SelectedIndexChanged );
      this.listViewSelected.MouseUp += new System.Windows.Forms.MouseEventHandler( this.listViewSelected_MouseUp );
      this.listViewSelected.DrawSubItem += new System.Windows.Forms.DrawListViewSubItemEventHandler( this.listViewSelected_DrawSubItem );
      // 
      // columnVis
      // 
      this.columnVis.Text = "Visible";
      this.columnVis.Width = 14;
      // 
      // columnEdit
      // 
      this.columnEdit.Text = "Edit";
      this.columnEdit.Width = 14;
      // 
      // columnExpand
      // 
      this.columnExpand.Text = "Expand";
      this.columnExpand.Width = 14;
      // 
      // columnName
      // 
      this.columnName.Text = "Name";
      this.columnName.Width = 222;
      // 
      // listViewAll
      // 
      this.listViewAll.Columns.AddRange( new System.Windows.Forms.ColumnHeader[] {
            this.columnHeader1} );
      this.listViewAll.FullRowSelect = true;
      this.listViewAll.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.None;
      this.listViewAll.HideSelection = false;
      this.listViewAll.Location = new System.Drawing.Point( 12, 25 );
      this.listViewAll.Name = "listViewAll";
      this.listViewAll.Size = new System.Drawing.Size( 217, 420 );
      this.listViewAll.TabIndex = 2;
      this.listViewAll.UseCompatibleStateImageBehavior = false;
      this.listViewAll.View = System.Windows.Forms.View.Details;
      this.listViewAll.SelectedIndexChanged += new System.EventHandler( this.listViewAll_SelectedIndexChanged );
      // 
      // columnHeader1
      // 
      this.columnHeader1.Width = 212;
      // 
      // buttonOk
      // 
      this.buttonOk.Location = new System.Drawing.Point( 516, 393 );
      this.buttonOk.Name = "buttonOk";
      this.buttonOk.Size = new System.Drawing.Size( 75, 23 );
      this.buttonOk.TabIndex = 3;
      this.buttonOk.Text = "OK";
      this.buttonOk.UseVisualStyleBackColor = true;
      this.buttonOk.Click += new System.EventHandler( this.buttonOk_Click );
      // 
      // buttonCancel
      // 
      this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.buttonCancel.Location = new System.Drawing.Point( 516, 422 );
      this.buttonCancel.Name = "buttonCancel";
      this.buttonCancel.Size = new System.Drawing.Size( 75, 23 );
      this.buttonCancel.TabIndex = 4;
      this.buttonCancel.Text = "Cancel";
      this.buttonCancel.UseVisualStyleBackColor = true;
      this.buttonCancel.Click += new System.EventHandler( this.buttonCancel_Click );
      // 
      // buttonMoveUp
      // 
      this.buttonMoveUp.Enabled = false;
      this.buttonMoveUp.Location = new System.Drawing.Point( 516, 158 );
      this.buttonMoveUp.Name = "buttonMoveUp";
      this.buttonMoveUp.Size = new System.Drawing.Size( 75, 23 );
      this.buttonMoveUp.TabIndex = 5;
      this.buttonMoveUp.Text = "Up";
      this.buttonMoveUp.UseVisualStyleBackColor = true;
      this.buttonMoveUp.Click += new System.EventHandler( this.buttonMoveUp_Click );
      // 
      // buttonMoveDown
      // 
      this.buttonMoveDown.Enabled = false;
      this.buttonMoveDown.Location = new System.Drawing.Point( 516, 238 );
      this.buttonMoveDown.Name = "buttonMoveDown";
      this.buttonMoveDown.Size = new System.Drawing.Size( 75, 23 );
      this.buttonMoveDown.TabIndex = 6;
      this.buttonMoveDown.Text = "Down";
      this.buttonMoveDown.UseVisualStyleBackColor = true;
      this.buttonMoveDown.Click += new System.EventHandler( this.buttonMoveDown_Click );
      // 
      // labelLeft
      // 
      this.labelLeft.AutoSize = true;
      this.labelLeft.Location = new System.Drawing.Point( 12, 9 );
      this.labelLeft.Name = "labelLeft";
      this.labelLeft.Size = new System.Drawing.Size( 105, 13 );
      this.labelLeft.TabIndex = 7;
      this.labelLeft.Text = "Types for this config:";
      // 
      // labelRight
      // 
      this.labelRight.AutoSize = true;
      this.labelRight.Location = new System.Drawing.Point( 232, 8 );
      this.labelRight.Name = "labelRight";
      this.labelRight.Size = new System.Drawing.Size( 113, 13 );
      this.labelRight.TabIndex = 8;
      this.labelRight.Text = "Label for right ListView";
      // 
      // buttonReset
      // 
      this.buttonReset.Location = new System.Drawing.Point( 154, 451 );
      this.buttonReset.Name = "buttonReset";
      this.buttonReset.Size = new System.Drawing.Size( 75, 23 );
      this.buttonReset.TabIndex = 9;
      this.buttonReset.Text = "Reset";
      this.buttonReset.UseVisualStyleBackColor = true;
      this.buttonReset.Click += new System.EventHandler( this.buttonReset_Click );
      // 
      // checkBoxShowAll
      // 
      this.checkBoxShowAll.AutoSize = true;
      this.checkBoxShowAll.Location = new System.Drawing.Point( 12, 455 );
      this.checkBoxShowAll.Name = "checkBoxShowAll";
      this.checkBoxShowAll.Size = new System.Drawing.Size( 99, 17 );
      this.checkBoxShowAll.TabIndex = 10;
      this.checkBoxShowAll.Text = "Show All Types";
      this.checkBoxShowAll.UseVisualStyleBackColor = true;
      this.checkBoxShowAll.CheckedChanged += new System.EventHandler( this.checkBoxShowAll_CheckedChanged );
      // 
      // EditorConfigEditForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.buttonCancel;
      this.ClientSize = new System.Drawing.Size( 603, 480 );
      this.Controls.Add( this.checkBoxShowAll );
      this.Controls.Add( this.buttonReset );
      this.Controls.Add( this.labelRight );
      this.Controls.Add( this.labelLeft );
      this.Controls.Add( this.buttonMoveDown );
      this.Controls.Add( this.buttonMoveUp );
      this.Controls.Add( this.buttonCancel );
      this.Controls.Add( this.buttonOk );
      this.Controls.Add( this.listViewAll );
      this.Controls.Add( this.listViewSelected );
      this.DoubleBuffered = true;
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
      this.Name = "EditorConfigEditForm";
      this.ShowInTaskbar = false;
      this.Text = "Edit Config Preset: ";
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.ListView listViewSelected;
    private System.Windows.Forms.ColumnHeader columnVis;
    private System.Windows.Forms.ColumnHeader columnEdit;
    private System.Windows.Forms.ColumnHeader columnName;
    private System.Windows.Forms.ListView listViewAll;
    private System.Windows.Forms.ColumnHeader columnHeader1;
    private System.Windows.Forms.Button buttonOk;
    private System.Windows.Forms.Button buttonCancel;
    private System.Windows.Forms.Button buttonMoveUp;
    private System.Windows.Forms.Button buttonMoveDown;
    private System.Windows.Forms.Label labelLeft;
    private System.Windows.Forms.Label labelRight;
    private System.Windows.Forms.Button buttonReset;
    private System.Windows.Forms.CheckBox checkBoxShowAll;
    private System.Windows.Forms.ColumnHeader columnExpand;
  }
}