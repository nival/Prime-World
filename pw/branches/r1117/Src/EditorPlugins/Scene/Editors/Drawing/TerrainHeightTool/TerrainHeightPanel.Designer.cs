using System;
using EditorPlugins.Scene.Editors;

namespace EditorPlugins.Scene.Editors.Drawing.TerrainHeightTool
{
	partial class TerrainHeightPanel
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
			this.brushTypeButton = new System.Windows.Forms.RadioButton();
			this.AffectTypeGroupBox = new System.Windows.Forms.GroupBox();
			this.flattenButton = new System.Windows.Forms.RadioButton();
			this.smoothButton = new System.Windows.Forms.RadioButton();
			this.downButton = new System.Windows.Forms.RadioButton();
			this.upButton = new System.Windows.Forms.RadioButton();
			this.BrushTypeGroupBox = new System.Windows.Forms.GroupBox();
			this.flatAffectButton = new System.Windows.Forms.RadioButton();
			this.quadAffectButton = new System.Windows.Forms.RadioButton();
			this.BrushSizeGroupBox = new System.Windows.Forms.GroupBox();
			this.label2 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.brushSizeSlider = new System.Windows.Forms.TrackBar();
			this.PressureGroupBox = new System.Windows.Forms.GroupBox();
			this.label4 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.pressureSlider = new System.Windows.Forms.TrackBar();
			this.panel1 = new System.Windows.Forms.Panel();
			this.gizmoTypeButton = new System.Windows.Forms.RadioButton();
			this.AffectTypeGroupBox.SuspendLayout();
			this.BrushTypeGroupBox.SuspendLayout();
			this.BrushSizeGroupBox.SuspendLayout();
			( (System.ComponentModel.ISupportInitialize)( this.brushSizeSlider ) ).BeginInit();
			this.PressureGroupBox.SuspendLayout();
			( (System.ComponentModel.ISupportInitialize)( this.pressureSlider ) ).BeginInit();
			this.panel1.SuspendLayout();
			this.SuspendLayout();
			// 
			// brushTypeButton
			// 
			this.brushTypeButton.Appearance = System.Windows.Forms.Appearance.Button;
			this.brushTypeButton.Location = new System.Drawing.Point( 67, 15 );
			this.brushTypeButton.Name = "brushTypeButton";
			this.brushTypeButton.Size = new System.Drawing.Size( 50, 23 );
			this.brushTypeButton.TabIndex = 1;
			this.brushTypeButton.Text = "Brush";
			this.brushTypeButton.UseVisualStyleBackColor = true;
			// 
			// AffectTypeGroupBox
			// 
			this.AffectTypeGroupBox.Controls.Add( this.flattenButton );
			this.AffectTypeGroupBox.Controls.Add( this.smoothButton );
			this.AffectTypeGroupBox.Controls.Add( this.downButton );
			this.AffectTypeGroupBox.Controls.Add( this.upButton );
			this.AffectTypeGroupBox.Location = new System.Drawing.Point( 1, 65 );
			this.AffectTypeGroupBox.Name = "AffectTypeGroupBox";
			this.AffectTypeGroupBox.Size = new System.Drawing.Size( 281, 80 );
			this.AffectTypeGroupBox.TabIndex = 0;
			this.AffectTypeGroupBox.TabStop = false;
			this.AffectTypeGroupBox.Text = "Affect Type";
			// 
			// flattenButton
			// 
			this.flattenButton.Appearance = System.Windows.Forms.Appearance.Button;
			this.flattenButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
			this.flattenButton.Location = new System.Drawing.Point( 179, 31 );
			this.flattenButton.Name = "flattenButton";
			this.flattenButton.Size = new System.Drawing.Size( 50, 23 );
			this.flattenButton.TabIndex = 7;
			this.flattenButton.Text = "Flatten";
			this.flattenButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this.flattenButton.UseVisualStyleBackColor = true;
			// 
			// smoothButton
			// 
			this.smoothButton.Appearance = System.Windows.Forms.Appearance.Button;
			this.smoothButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
			this.smoothButton.Location = new System.Drawing.Point( 123, 31 );
			this.smoothButton.Name = "smoothButton";
			this.smoothButton.Size = new System.Drawing.Size( 50, 23 );
			this.smoothButton.TabIndex = 6;
			this.smoothButton.Text = "Smooth";
			this.smoothButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this.smoothButton.UseVisualStyleBackColor = true;
			// 
			// downButton
			// 
			this.downButton.Appearance = System.Windows.Forms.Appearance.Button;
			this.downButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
			this.downButton.Location = new System.Drawing.Point( 67, 31 );
			this.downButton.Name = "downButton";
			this.downButton.Size = new System.Drawing.Size( 50, 23 );
			this.downButton.TabIndex = 5;
			this.downButton.Text = "Down";
			this.downButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this.downButton.UseVisualStyleBackColor = true;
			// 
			// upButton
			// 
			this.upButton.Appearance = System.Windows.Forms.Appearance.Button;
			this.upButton.Checked = true;
			this.upButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
			this.upButton.Location = new System.Drawing.Point( 11, 31 );
			this.upButton.Name = "upButton";
			this.upButton.Size = new System.Drawing.Size( 50, 23 );
			this.upButton.TabIndex = 4;
			this.upButton.TabStop = true;
			this.upButton.Text = "Up";
			this.upButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this.upButton.UseVisualStyleBackColor = true;
			// 
			// BrushTypeGroupBox
			// 
			this.BrushTypeGroupBox.Controls.Add( this.flatAffectButton );
			this.BrushTypeGroupBox.Controls.Add( this.quadAffectButton );
			this.BrushTypeGroupBox.Location = new System.Drawing.Point( 1, 151 );
			this.BrushTypeGroupBox.Name = "BrushTypeGroupBox";
			this.BrushTypeGroupBox.Size = new System.Drawing.Size( 281, 80 );
			this.BrushTypeGroupBox.TabIndex = 1;
			this.BrushTypeGroupBox.TabStop = false;
			this.BrushTypeGroupBox.Text = "Brush Type";
			// 
			// flatAffectButton
			// 
			this.flatAffectButton.Appearance = System.Windows.Forms.Appearance.Button;
			this.flatAffectButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
			this.flatAffectButton.Location = new System.Drawing.Point( 67, 31 );
			this.flatAffectButton.Name = "flatAffectButton";
			this.flatAffectButton.Size = new System.Drawing.Size( 50, 23 );
			this.flatAffectButton.TabIndex = 8;
			this.flatAffectButton.Text = "Flat";
			this.flatAffectButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this.flatAffectButton.UseVisualStyleBackColor = true;
			// 
			// quadAffectButton
			// 
			this.quadAffectButton.Appearance = System.Windows.Forms.Appearance.Button;
			this.quadAffectButton.Checked = true;
			this.quadAffectButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
			this.quadAffectButton.Location = new System.Drawing.Point( 11, 31 );
			this.quadAffectButton.Name = "quadAffectButton";
			this.quadAffectButton.Size = new System.Drawing.Size( 50, 23 );
			this.quadAffectButton.TabIndex = 8;
			this.quadAffectButton.TabStop = true;
			this.quadAffectButton.Text = "Quad";
			this.quadAffectButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
			this.quadAffectButton.UseVisualStyleBackColor = true;
			// 
			// BrushSizeGroupBox
			// 
			this.BrushSizeGroupBox.Controls.Add( this.label2 );
			this.BrushSizeGroupBox.Controls.Add( this.label1 );
			this.BrushSizeGroupBox.Controls.Add( this.brushSizeSlider );
			this.BrushSizeGroupBox.Location = new System.Drawing.Point( 1, 237 );
			this.BrushSizeGroupBox.Name = "BrushSizeGroupBox";
			this.BrushSizeGroupBox.Size = new System.Drawing.Size( 281, 80 );
			this.BrushSizeGroupBox.TabIndex = 2;
			this.BrushSizeGroupBox.TabStop = false;
			this.BrushSizeGroupBox.Text = "Brush Size";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point( 23, 29 );
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size( 21, 13 );
			this.label2.TabIndex = 2;
			this.label2.Text = "5m";
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point( 194, 29 );
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size( 27, 13 );
			this.label1.TabIndex = 1;
			this.label1.Text = "30m";
			// 
			// brushSizeSlider
			// 
			this.brushSizeSlider.Location = new System.Drawing.Point( 37, 29 );
			this.brushSizeSlider.Maximum = 30;
			this.brushSizeSlider.Minimum = 5;
			this.brushSizeSlider.Name = "brushSizeSlider";
			this.brushSizeSlider.Size = new System.Drawing.Size( 160, 45 );
			this.brushSizeSlider.TabIndex = 0;
			this.brushSizeSlider.Value = 10;
			// 
			// PressureGroupBox
			// 
			this.PressureGroupBox.Controls.Add( this.label4 );
			this.PressureGroupBox.Controls.Add( this.label3 );
			this.PressureGroupBox.Controls.Add( this.pressureSlider );
			this.PressureGroupBox.Location = new System.Drawing.Point( 1, 323 );
			this.PressureGroupBox.Name = "PressureGroupBox";
			this.PressureGroupBox.Size = new System.Drawing.Size( 281, 80 );
			this.PressureGroupBox.TabIndex = 3;
			this.PressureGroupBox.TabStop = false;
			this.PressureGroupBox.Text = "Pressure";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Location = new System.Drawing.Point( 194, 29 );
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size( 13, 13 );
			this.label4.TabIndex = 4;
			this.label4.Text = "1";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point( 23, 29 );
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size( 22, 13 );
			this.label3.TabIndex = 3;
			this.label3.Text = "0.1";
			// 
			// pressureSlider
			// 
			this.pressureSlider.LargeChange = 1;
			this.pressureSlider.Location = new System.Drawing.Point( 37, 29 );
			this.pressureSlider.Name = "pressureSlider";
			this.pressureSlider.Size = new System.Drawing.Size( 160, 45 );
			this.pressureSlider.TabIndex = 1;
			this.pressureSlider.Value = 8;
			// 
			// panel1
			// 
			this.panel1.Controls.Add( this.brushTypeButton );
			this.panel1.Controls.Add( this.gizmoTypeButton );
			this.panel1.Location = new System.Drawing.Point( 1, 12 );
			this.panel1.Name = "panel1";
			this.panel1.Size = new System.Drawing.Size( 281, 47 );
			this.panel1.TabIndex = 4;
			// 
			// gizmoTypeButton
			// 
			this.gizmoTypeButton.Appearance = System.Windows.Forms.Appearance.Button;
			this.gizmoTypeButton.Checked = true;
			this.gizmoTypeButton.Location = new System.Drawing.Point( 11, 15 );
			this.gizmoTypeButton.Name = "gizmoTypeButton";
			this.gizmoTypeButton.Size = new System.Drawing.Size( 50, 23 );
			this.gizmoTypeButton.TabIndex = 0;
			this.gizmoTypeButton.TabStop = true;
			this.gizmoTypeButton.Text = "Gizmo";
			this.gizmoTypeButton.UseVisualStyleBackColor = true;
			// 
			// TerrainHeightPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 284, 421 );
			this.Controls.Add( this.panel1 );
			this.Controls.Add( this.PressureGroupBox );
			this.Controls.Add( this.BrushSizeGroupBox );
			this.Controls.Add( this.BrushTypeGroupBox );
			this.Controls.Add( this.AffectTypeGroupBox );
			this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
			this.Name = "TerrainHeightPanel";
			this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.Float;
			this.Text = "TerrainHeightPanel";
			this.AffectTypeGroupBox.ResumeLayout( false );
			this.BrushTypeGroupBox.ResumeLayout( false );
			this.BrushSizeGroupBox.ResumeLayout( false );
			this.BrushSizeGroupBox.PerformLayout();
			( (System.ComponentModel.ISupportInitialize)( this.brushSizeSlider ) ).EndInit();
			this.PressureGroupBox.ResumeLayout( false );
			this.PressureGroupBox.PerformLayout();
			( (System.ComponentModel.ISupportInitialize)( this.pressureSlider ) ).EndInit();
			this.panel1.ResumeLayout( false );
			this.ResumeLayout( false );

		}

		#endregion

		private System.Windows.Forms.GroupBox AffectTypeGroupBox;
		private System.Windows.Forms.GroupBox BrushTypeGroupBox;
		private System.Windows.Forms.GroupBox BrushSizeGroupBox;
		private System.Windows.Forms.GroupBox PressureGroupBox;
		private System.Windows.Forms.RadioButton upButton;
		private System.Windows.Forms.RadioButton flattenButton;
		private System.Windows.Forms.RadioButton smoothButton;
		private System.Windows.Forms.RadioButton downButton;
		private System.Windows.Forms.RadioButton flatAffectButton;
		private System.Windows.Forms.RadioButton quadAffectButton;
		private System.Windows.Forms.TrackBar brushSizeSlider;
		private System.Windows.Forms.TrackBar pressureSlider;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Panel panel1;
		public System.Windows.Forms.RadioButton gizmoTypeButton;
		public System.Windows.Forms.RadioButton brushTypeButton;

	}
}