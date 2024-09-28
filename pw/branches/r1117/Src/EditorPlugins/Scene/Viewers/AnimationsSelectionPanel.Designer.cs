namespace EditorPlugins.Scene.Viewers
{
	partial class AnimationsSelectionPanel
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
      this.noResourceLabel = new System.Windows.Forms.Label();
      this.animationsListView = new System.Windows.Forms.ListView();
      this.hdrName = new System.Windows.Forms.ColumnHeader();
      this.hdrLength = new System.Windows.Forms.ColumnHeader();
      this.SuspendLayout();
      // 
      // noResourceLabel
      // 
      this.noResourceLabel.BackColor = System.Drawing.SystemColors.Control;
      this.noResourceLabel.Dock = System.Windows.Forms.DockStyle.Fill;
      this.noResourceLabel.ForeColor = System.Drawing.Color.Blue;
      this.noResourceLabel.Location = new System.Drawing.Point(0, 0);
      this.noResourceLabel.Name = "noResourceLabel";
      this.noResourceLabel.Size = new System.Drawing.Size(337, 199);
      this.noResourceLabel.TabIndex = 2;
      this.noResourceLabel.Text = "No resource loaded or no animations in loaded resource";
      this.noResourceLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      // 
      // animationsListView
      // 
      this.animationsListView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.hdrName,
            this.hdrLength});
      this.animationsListView.Dock = System.Windows.Forms.DockStyle.Fill;
      this.animationsListView.FullRowSelect = true;
      this.animationsListView.GridLines = true;
      this.animationsListView.LabelWrap = false;
      this.animationsListView.Location = new System.Drawing.Point(0, 0);
      this.animationsListView.MultiSelect = false;
      this.animationsListView.Name = "animationsListView";
      this.animationsListView.ShowGroups = false;
      this.animationsListView.Size = new System.Drawing.Size(337, 199);
      this.animationsListView.Sorting = System.Windows.Forms.SortOrder.Ascending;
      this.animationsListView.TabIndex = 3;
      this.animationsListView.UseCompatibleStateImageBehavior = false;
      this.animationsListView.View = System.Windows.Forms.View.Details;
      this.animationsListView.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.OnHeaderClick);
      this.animationsListView.Click += new System.EventHandler(this.OnPlayClick);
      // 
      // hdrName
      // 
      this.hdrName.Text = "Name";
      // 
      // hdrLength
      // 
      this.hdrLength.Text = "Length";
      // 
      // AnimationsSelectionPanel
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.SystemColors.Control;
      this.Controls.Add(this.animationsListView);
      this.Controls.Add(this.noResourceLabel);
      this.Name = "AnimationsSelectionPanel";
      this.Size = new System.Drawing.Size(337, 199);
      this.ResumeLayout(false);

		}

		#endregion

    private System.Windows.Forms.Label noResourceLabel;
    private System.Windows.Forms.ListView animationsListView;
    private System.Windows.Forms.ColumnHeader hdrLength;
    private System.Windows.Forms.ColumnHeader hdrName;
	}
}
