namespace EditorPlugins.Editors.AnimatedCurves
{
	partial class AnimatedCurvesControl
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
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager( typeof( AnimatedCurvesControl ) );
			this.txtTime = new System.Windows.Forms.ToolStripTextBox();
			this.listBoxTracks = new System.Windows.Forms.ListBox();
			this.lblTime = new System.Windows.Forms.ToolStripLabel();
			this.lblValue = new System.Windows.Forms.ToolStripLabel();
			this.toolStrip1 = new System.Windows.Forms.ToolStrip();
			this.txtValue = new System.Windows.Forms.ToolStripTextBox();
			this.animEditor = new EditorPlugins.Editors.Animated.AnimatedEditor();
			this.splitContainer1 = new System.Windows.Forms.SplitContainer();
			this.toolStrip1.SuspendLayout();
			this.splitContainer1.Panel1.SuspendLayout();
			this.splitContainer1.Panel2.SuspendLayout();
			this.splitContainer1.SuspendLayout();
			this.SuspendLayout();
			// 
			// txtTime
			// 
			this.txtTime.Enabled = false;
			this.txtTime.Name = "txtTime";
			this.txtTime.Size = new System.Drawing.Size( 75, 25 );
			this.txtTime.Validating += new System.ComponentModel.CancelEventHandler( this.OnTimeValidating );
			this.txtTime.Validated += new System.EventHandler( this.OnTimeValidated );
			this.txtTime.KeyPress += new System.Windows.Forms.KeyPressEventHandler( this.OnEditBoxKeyPress );
			// 
			// listBoxTracks
			// 
			this.listBoxTracks.BackColor = System.Drawing.SystemColors.Control;
			this.listBoxTracks.Dock = System.Windows.Forms.DockStyle.Fill;
			this.listBoxTracks.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
			this.listBoxTracks.FormattingEnabled = true;
			this.listBoxTracks.IntegralHeight = false;
			this.listBoxTracks.Location = new System.Drawing.Point( 0, 0 );
			this.listBoxTracks.Name = "listBoxTracks";
			this.listBoxTracks.SelectionMode = System.Windows.Forms.SelectionMode.MultiExtended;
			this.listBoxTracks.Size = new System.Drawing.Size( 164, 402 );
			this.listBoxTracks.TabIndex = 2;
			this.listBoxTracks.DrawItem += new System.Windows.Forms.DrawItemEventHandler( this.OnDrawItem );
			this.listBoxTracks.SelectedIndexChanged += new System.EventHandler( this.OnSelectItem );
			// 
			// lblTime
			// 
			this.lblTime.Name = "lblTime";
			this.lblTime.Size = new System.Drawing.Size( 37, 22 );
			this.lblTime.Text = "Time:";
			// 
			// lblValue
			// 
			this.lblValue.Name = "lblValue";
			this.lblValue.Size = new System.Drawing.Size( 39, 22 );
			this.lblValue.Text = "Value:";
			// 
			// toolStrip1
			// 
			this.toolStrip1.GripStyle = System.Windows.Forms.ToolStripGripStyle.Hidden;
			this.toolStrip1.Items.AddRange( new System.Windows.Forms.ToolStripItem[] {
            this.lblTime,
            this.txtTime,
            this.lblValue,
            this.txtValue} );
			this.toolStrip1.Location = new System.Drawing.Point( 0, 0 );
			this.toolStrip1.Name = "toolStrip1";
			this.toolStrip1.Size = new System.Drawing.Size( 463, 25 );
			this.toolStrip1.TabIndex = 4;
			this.toolStrip1.Text = "toolStrip1";
			// 
			// txtValue
			// 
			this.txtValue.Enabled = false;
			this.txtValue.Name = "txtValue";
			this.txtValue.Size = new System.Drawing.Size( 125, 25 );
			this.txtValue.Validating += new System.ComponentModel.CancelEventHandler( this.OnValueValidating );
			this.txtValue.Validated += new System.EventHandler( this.OnValueValidated );
			this.txtValue.KeyPress += new System.Windows.Forms.KeyPressEventHandler( this.OnEditBoxKeyPress );
			// 
			// animEditor
			// 
			this.animEditor.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
									| System.Windows.Forms.AnchorStyles.Left )
									| System.Windows.Forms.AnchorStyles.Right ) ) );
			this.animEditor.Location = new System.Drawing.Point( 0, 28 );
			this.animEditor.Name = "animEditor";
			this.animEditor.SelectionArea = new System.Drawing.Rectangle( 0, 0, 0, 0 );
			this.animEditor.Size = new System.Drawing.Size( 460, 371 );
			this.animEditor.TabIndex = 0;
			this.animEditor.VisibleArea = ( (System.Drawing.RectangleF)( resources.GetObject( "animEditor.VisibleArea" ) ) );
			this.animEditor.SelectedItemsMoved += new System.EventHandler( this.OnSelectedItemsMoved );
			this.animEditor.SelectedItemsChanged += new System.EventHandler( this.OnSelectedItemsChanged );
			// 
			// splitContainer1
			// 
			this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.splitContainer1.Location = new System.Drawing.Point( 0, 0 );
			this.splitContainer1.Margin = new System.Windows.Forms.Padding( 0 );
			this.splitContainer1.Name = "splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this.splitContainer1.Panel1.Controls.Add( this.listBoxTracks );
			// 
			// splitContainer1.Panel2
			// 
			this.splitContainer1.Panel2.Controls.Add( this.toolStrip1 );
			this.splitContainer1.Panel2.Controls.Add( this.animEditor );
			this.splitContainer1.Size = new System.Drawing.Size( 631, 402 );
			this.splitContainer1.SplitterDistance = 164;
			this.splitContainer1.TabIndex = 4;
			// 
			// AnimatedCurvesControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add( this.splitContainer1 );
			this.Name = "AnimatedCurvesControl";
			this.Size = new System.Drawing.Size( 631, 402 );
			this.toolStrip1.ResumeLayout( false );
			this.toolStrip1.PerformLayout();
			this.splitContainer1.Panel1.ResumeLayout( false );
			this.splitContainer1.Panel2.ResumeLayout( false );
			this.splitContainer1.Panel2.PerformLayout();
			this.splitContainer1.ResumeLayout( false );
			this.ResumeLayout( false );

		}

		#endregion

		private System.Windows.Forms.ToolStripTextBox txtTime;
		private System.Windows.Forms.ListBox listBoxTracks;
		private System.Windows.Forms.ToolStripLabel lblTime;
		private System.Windows.Forms.ToolStripLabel lblValue;
		private System.Windows.Forms.ToolStrip toolStrip1;
		private System.Windows.Forms.ToolStripTextBox txtValue;
		private EditorPlugins.Editors.Animated.AnimatedEditor animEditor;
		private System.Windows.Forms.SplitContainer splitContainer1;
	}
}
