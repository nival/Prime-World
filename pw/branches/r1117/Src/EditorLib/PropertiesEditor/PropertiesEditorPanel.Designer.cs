using System.Windows.Forms;
namespace EditorLib.PropertiesEditor
{
	partial class PropertiesEditorPanel
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

		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( PropertiesEditorPanel ) );
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.improvedOutliner1 = new EditorLib.PropertiesEditor.ImprovedOutliner();
			this.propertiesEditorControl = new EditorLib.PropertiesEditor.PropertiesEditorControl();
			this.propertyPanelToolStrip = new System.Windows.Forms.ToolStrip();
			this.PinProperties = new System.Windows.Forms.ToolStripButton();
			this.tsbLockSelection = new System.Windows.Forms.ToolStripButton();
			this.toolStripButtonShowOutliner = new System.Windows.Forms.ToolStripButton();
			this.toolStripSeparator3 = new System.Windows.Forms.ToolStripSeparator();
			this.SelectConfiguration = new System.Windows.Forms.ToolStripComboBox();
			this.tsbOutlinerColours = new System.Windows.Forms.ToolStripButton();
			this.nameLabel = new System.Windows.Forms.Label();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			this.propertyPanelToolStrip.SuspendLayout();
			this.SuspendLayout();
			// 
			// splitContainer1
			// 
			this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer1.Location = new System.Drawing.Point( 0, 16 );
			this.splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this.splitContainer1.Panel1.Controls.Add( this.improvedOutliner1 );
			this.splitContainer1.Panel1.Controls.Add( this.propertyPanelToolStrip );
			// 
			// splitContainer1.Panel2
			// 
			this.splitContainer1.Panel2.Controls.Add( this.propertiesEditorControl );
			this.splitContainer1.Size = new System.Drawing.Size( 569, 463 );
			this.splitContainer1.SplitterDistance = 246;
			this.splitContainer1.TabIndex = 0;
			this.splitContainer1.TabStop = false;
			this.splitContainer1.SplitterMoved += new System.Windows.Forms.SplitterEventHandler( this.splitContainer1_SplitterMoved );
			// 
			// improvedOutliner1
			// 
			this.improvedOutliner1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.improvedOutliner1.LinkedPropertiesEditor = this.propertiesEditorControl;
			this.improvedOutliner1.Location = new System.Drawing.Point( 0, 25 );
			this.improvedOutliner1.Name = "improvedOutliner1";
			this.improvedOutliner1.SelectedObject = null;
			this.improvedOutliner1.SelectedPreset = null;
			this.improvedOutliner1.Size = new System.Drawing.Size( 246, 438 );
			this.improvedOutliner1.TabIndex = 1;
			// 
			// propertiesEditorControl
			// 
			this.propertiesEditorControl.Dock = System.Windows.Forms.DockStyle.Fill;
			this.propertiesEditorControl.ImprovedOutliner = this.improvedOutliner1;
			this.propertiesEditorControl.Location = new System.Drawing.Point( 0, 0 );
			this.propertiesEditorControl.Name = "propertiesEditorControl";
			this.propertiesEditorControl.SelectedObject = null;
			this.propertiesEditorControl.Size = new System.Drawing.Size( 319, 463 );
			this.propertiesEditorControl.TabIndex = 0;
			// 
			// propertyPanelToolStrip
			// 
			this.propertyPanelToolStrip.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
			this.propertyPanelToolStrip.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.PinProperties,
            this.tsbLockSelection,
            this.toolStripButtonShowOutliner,
            this.toolStripSeparator3,
            this.SelectConfiguration,
            this.tsbOutlinerColours} );
			this.propertyPanelToolStrip.Location = new System.Drawing.Point( 0, 0 );
			this.propertyPanelToolStrip.Name = "propertyPanelToolStrip";
			this.propertyPanelToolStrip.Size = new System.Drawing.Size( 246, 25 );
			this.propertyPanelToolStrip.TabIndex = 9;
			// 
			// PinProperties
			// 
			this.PinProperties.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.PinProperties.Enabled = false;
			this.PinProperties.Image = global::EditorLib.EditorLibResources.Pin;
			this.PinProperties.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.PinProperties.Name = "PinProperties";
			this.PinProperties.Size = new System.Drawing.Size( 23, 22 );
			this.PinProperties.Text = "Pin Property Editor";
			this.PinProperties.Click += new System.EventHandler( this.PinProperties_Click );
			// 
			// tsbLockSelection
			// 
			this.tsbLockSelection.CheckOnClick = true;
			this.tsbLockSelection.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbLockSelection.Image = global::EditorLib.EditorLibResources.Lock;
			this.tsbLockSelection.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbLockSelection.Name = "tsbLockSelection";
			this.tsbLockSelection.Size = new System.Drawing.Size( 23, 22 );
			this.tsbLockSelection.Text = "toolStripButton1";
			this.tsbLockSelection.ToolTipText = "Lock current selection in outliner";
			this.tsbLockSelection.CheckStateChanged += new System.EventHandler( this.tsbLockSelection_CheckStateChanged );
			// 
			// toolStripButtonShowOutliner
			// 
			this.toolStripButtonShowOutliner.CheckOnClick = true;
			this.toolStripButtonShowOutliner.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.toolStripButtonShowOutliner.Image = global::EditorLib.EditorLibResources.Outliner;
			this.toolStripButtonShowOutliner.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.toolStripButtonShowOutliner.Name = "toolStripButtonShowOutliner";
			this.toolStripButtonShowOutliner.Size = new System.Drawing.Size( 23, 22 );
			this.toolStripButtonShowOutliner.Text = "Outliner";
			this.toolStripButtonShowOutliner.ToolTipText = "Show/hide Outliner";
			this.toolStripButtonShowOutliner.CheckStateChanged += new System.EventHandler( this.toolStripButtonShowOutliner_CheckStateChanged );
			// 
			// toolStripSeparator3
			// 
			this.toolStripSeparator3.Name = "toolStripSeparator3";
			this.toolStripSeparator3.Size = new System.Drawing.Size( 6, 25 );
			// 
			// SelectConfiguration
			// 
			this.SelectConfiguration.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.SelectConfiguration.FlatStyle = System.Windows.Forms.FlatStyle.Standard;
			this.SelectConfiguration.Name = "SelectConfiguration";
			this.SelectConfiguration.Size = new System.Drawing.Size( 121, 25 );
			this.SelectConfiguration.ToolTipText = "Select Property visibility preset";
			this.SelectConfiguration.SelectedIndexChanged += new System.EventHandler( this.SelectConfiguration_SelectedIndexChanged );
			// 
			// tsbOutlinerColours
			// 
			this.tsbOutlinerColours.CheckOnClick = true;
			this.tsbOutlinerColours.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
			this.tsbOutlinerColours.Image = global::EditorLib.EditorLibResources.Rainbow;
			this.tsbOutlinerColours.ImageTransparentColor = System.Drawing.Color.Magenta;
			this.tsbOutlinerColours.Name = "tsbOutlinerColours";
			this.tsbOutlinerColours.Size = new System.Drawing.Size( 23, 22 );
			this.tsbOutlinerColours.Text = "toolStripButton1";
			this.tsbOutlinerColours.ToolTipText = "Switch Outliner colouring on/off; right-click to set colours";
			this.tsbOutlinerColours.CheckedChanged += new System.EventHandler( this.tsbOutlinerColours_CheckedChanged );
			this.tsbOutlinerColours.MouseDown += new System.Windows.Forms.MouseEventHandler( this.tsbOutlinerColours_MouseDown );
			// 
			// nameLabel
			// 
			this.nameLabel.BackColor = System.Drawing.SystemColors.Highlight;
			this.nameLabel.Dock = System.Windows.Forms.DockStyle.Top;
			this.nameLabel.ForeColor = System.Drawing.SystemColors.HighlightText;
			this.nameLabel.Location = new System.Drawing.Point( 0, 0 );
			this.nameLabel.Name = "nameLabel";
			this.nameLabel.Size = new System.Drawing.Size( 569, 16 );
			this.nameLabel.TabIndex = 9;
			this.nameLabel.Text = "No object selected";
			this.nameLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
			this.nameLabel.MouseClick += new System.Windows.Forms.MouseEventHandler( this.nameLabel_MouseClick );
			// 
			// PropertiesEditorPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 569, 479 );
			this.Controls.Add( this.splitContainer1 );
			this.Controls.Add( this.nameLabel );
			this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
			this.HideOnClose = true;
			this.Icon = ( (System.Drawing.Icon)( resources.GetObject( "$this.Icon" ) ) );
			this.MaximizeBox = false;
			this.MinimizeBox = false;
			this.Name = "PropertiesEditorPanel";
			this.TabText = "Properties Editor";
			this.Text = "Properties Editor";
			this.splitContainer1.Panel1.ResumeLayout( false );
			this.splitContainer1.Panel1.PerformLayout();
			this.splitContainer1.Panel2.ResumeLayout( false );
			this.splitContainer1.ResumeLayout( false );
			this.propertyPanelToolStrip.ResumeLayout( false );
			this.propertyPanelToolStrip.PerformLayout();
			this.ResumeLayout( false );

		}

		#endregion

    private SplitContainer splitContainer1;
    private Label nameLabel;
    private PropertiesEditorControl propertiesEditorControl;
    //private FastOutlinerControl outlinerControl;
    private ToolStrip propertyPanelToolStrip;
    private ToolStripButton PinProperties;
    private ToolStripButton toolStripButtonShowOutliner;
    private ToolStripSeparator toolStripSeparator3;
    private ToolStripComboBox SelectConfiguration;
    private ToolStripButton tsbLockSelection;
		private ToolStripButton tsbOutlinerColours;
		private ImprovedOutliner improvedOutliner1;

	}
}
