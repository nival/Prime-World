namespace EditorLib.Extensions
{
  partial class ImportRecursive
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
			this.checkBoxShowExternal = new System.Windows.Forms.CheckBox();
			this.buttonImport = new System.Windows.Forms.Button();
			this.buttonCancel = new System.Windows.Forms.Button();
			this.progressBarImport = new System.Windows.Forms.ProgressBar();
			this.backgroundWorkerSearch = new System.ComponentModel.BackgroundWorker();
			this.listViewObjects = new System.Windows.Forms.ListView();
			this.hdrObjects = new System.Windows.Forms.ColumnHeader();
			this.hdrTypes = new System.Windows.Forms.ColumnHeader();
			this.SuspendLayout();
			// 
			// checkBoxShowExternal
			// 
			this.checkBoxShowExternal.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left ) ) );
			this.checkBoxShowExternal.AutoSize = true;
			this.checkBoxShowExternal.Location = new System.Drawing.Point( 12, 440 );
			this.checkBoxShowExternal.Name = "checkBoxShowExternal";
			this.checkBoxShowExternal.Size = new System.Drawing.Size( 130, 17 );
			this.checkBoxShowExternal.TabIndex = 1;
			this.checkBoxShowExternal.Text = "Show external objects";
			this.checkBoxShowExternal.UseVisualStyleBackColor = true;
			this.checkBoxShowExternal.CheckedChanged += new System.EventHandler( this.checkBoxShowExternal_CheckedChanged );
			// 
			// buttonImport
			// 
			this.buttonImport.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.buttonImport.Enabled = false;
			this.buttonImport.Location = new System.Drawing.Point( 359, 436 );
			this.buttonImport.Name = "buttonImport";
			this.buttonImport.Size = new System.Drawing.Size( 75, 23 );
			this.buttonImport.TabIndex = 2;
			this.buttonImport.Text = "Import";
			this.buttonImport.UseVisualStyleBackColor = true;
			this.buttonImport.Click += new System.EventHandler( this.buttonImport_Click );
			// 
			// buttonCancel
			// 
			this.buttonCancel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
			this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
			this.buttonCancel.Location = new System.Drawing.Point( 440, 436 );
			this.buttonCancel.Name = "buttonCancel";
			this.buttonCancel.Size = new System.Drawing.Size( 75, 23 );
			this.buttonCancel.TabIndex = 3;
			this.buttonCancel.Text = "Cancel";
			this.buttonCancel.UseVisualStyleBackColor = true;
			// 
			// progressBarImport
			// 
			this.progressBarImport.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.progressBarImport.Location = new System.Drawing.Point( 12, 416 );
			this.progressBarImport.Name = "progressBarImport";
			this.progressBarImport.Size = new System.Drawing.Size( 503, 14 );
			this.progressBarImport.Style = System.Windows.Forms.ProgressBarStyle.Marquee;
			this.progressBarImport.TabIndex = 5;
			// 
			// backgroundWorkerSearch
			// 
			this.backgroundWorkerSearch.DoWork += new System.ComponentModel.DoWorkEventHandler( this.backgroundWorkerSearch_DoWork );
			this.backgroundWorkerSearch.RunWorkerCompleted += new System.ComponentModel.RunWorkerCompletedEventHandler( this.backgroundWorkerSearch_RunWorkerCompleted );
			// 
			// listViewObjects
			// 
			this.listViewObjects.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
									| System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.listViewObjects.AutoArrange = false;
			this.listViewObjects.CheckBoxes = true;
			this.listViewObjects.Columns.AddRange( new System.Windows.Forms.ColumnHeader[] {
            this.hdrObjects,
            this.hdrTypes} );
			this.listViewObjects.FullRowSelect = true;
			this.listViewObjects.HideSelection = false;
			this.listViewObjects.Location = new System.Drawing.Point( 12, 12 );
			this.listViewObjects.Name = "listViewObjects";
			this.listViewObjects.ShowGroups = false;
			this.listViewObjects.Size = new System.Drawing.Size( 503, 398 );
			this.listViewObjects.TabIndex = 6;
			this.listViewObjects.UseCompatibleStateImageBehavior = false;
			this.listViewObjects.View = System.Windows.Forms.View.Details;
			this.listViewObjects.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler( this.OnHeaderClick );
			// 
			// hdrObjects
			// 
			this.hdrObjects.Text = "Object";
			this.hdrObjects.Width = 430;
			// 
			// hdrTypes
			// 
			this.hdrTypes.Text = "Type";
			// 
			// ImportRecursive
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.CancelButton = this.buttonCancel;
			this.ClientSize = new System.Drawing.Size( 527, 469 );
			this.Controls.Add( this.listViewObjects );
			this.Controls.Add( this.progressBarImport );
			this.Controls.Add( this.buttonCancel );
			this.Controls.Add( this.buttonImport );
			this.Controls.Add( this.checkBoxShowExternal );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.SizableToolWindow;
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "ImportRecursive";
			this.ShowIcon = false;
			this.ShowInTaskbar = false;
			this.Text = "Collecting Objects...";
			this.ResumeLayout( false );
			this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.CheckBox checkBoxShowExternal;
    private System.Windows.Forms.Button buttonImport;
    private System.Windows.Forms.Button buttonCancel;
    private System.Windows.Forms.ProgressBar progressBarImport;
    private System.ComponentModel.BackgroundWorker backgroundWorkerSearch;
    private System.Windows.Forms.ListView listViewObjects;
    private System.Windows.Forms.ColumnHeader hdrObjects;
		private System.Windows.Forms.ColumnHeader hdrTypes;
  }
}