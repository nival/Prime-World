using System;
using EditorPlugins.Scene.Editors;

namespace EditorPlugins.Scene.Editors.Drawing
{
	partial class NatureMapPanel
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
      this.FactionGroupBox = new System.Windows.Forms.GroupBox();
      this.fromAnyButton = new System.Windows.Forms.RadioButton();
      this.fromBurnButton = new System.Windows.Forms.RadioButton();
      this.fromFreezeButton = new System.Windows.Forms.RadioButton();
      this.fromNeutralButton = new System.Windows.Forms.RadioButton();
      this.BrushSizeGroupBox = new System.Windows.Forms.GroupBox();
      this.brushSizeUpDown = new System.Windows.Forms.NumericUpDown();
      this.label2 = new System.Windows.Forms.Label();
      this.label1 = new System.Windows.Forms.Label();
      this.brushSizeSlider = new System.Windows.Forms.TrackBar();
      this.groupBox1 = new System.Windows.Forms.GroupBox();
      this.toBurnButton = new System.Windows.Forms.RadioButton();
      this.toFreezeButton = new System.Windows.Forms.RadioButton();
      this.toNeutralButton = new System.Windows.Forms.RadioButton();
      this.FactionGroupBox.SuspendLayout();
      this.BrushSizeGroupBox.SuspendLayout();
      ( (System.ComponentModel.ISupportInitialize)( this.brushSizeUpDown ) ).BeginInit();
      ( (System.ComponentModel.ISupportInitialize)( this.brushSizeSlider ) ).BeginInit();
      this.groupBox1.SuspendLayout();
      this.SuspendLayout();
      // 
      // FactionGroupBox
      // 
      this.FactionGroupBox.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.FactionGroupBox.Controls.Add( this.fromAnyButton );
      this.FactionGroupBox.Controls.Add( this.fromBurnButton );
      this.FactionGroupBox.Controls.Add( this.fromFreezeButton );
      this.FactionGroupBox.Controls.Add( this.fromNeutralButton );
      this.FactionGroupBox.Location = new System.Drawing.Point( 1, 9 );
      this.FactionGroupBox.Margin = new System.Windows.Forms.Padding( 2 );
      this.FactionGroupBox.Name = "FactionGroupBox";
      this.FactionGroupBox.Padding = new System.Windows.Forms.Padding( 2 );
      this.FactionGroupBox.Size = new System.Drawing.Size( 190, 84 );
      this.FactionGroupBox.TabIndex = 0;
      this.FactionGroupBox.TabStop = false;
      this.FactionGroupBox.Text = "From faction ";
      this.FactionGroupBox.Enter += new System.EventHandler( this.FactionGroupBox_Enter );
      // 
      // fromAnyButton
      // 
      this.fromAnyButton.Appearance = System.Windows.Forms.Appearance.Button;
      this.fromAnyButton.Checked = true;
      this.fromAnyButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
      this.fromAnyButton.Location = new System.Drawing.Point( 11, 21 );
      this.fromAnyButton.Margin = new System.Windows.Forms.Padding( 2 );
      this.fromAnyButton.Name = "fromAnyButton";
      this.fromAnyButton.Size = new System.Drawing.Size( 163, 23 );
      this.fromAnyButton.TabIndex = 3;
      this.fromAnyButton.TabStop = true;
      this.fromAnyButton.Text = "Any";
      this.fromAnyButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      this.fromAnyButton.UseVisualStyleBackColor = true;
      this.fromAnyButton.CheckedChanged += new System.EventHandler( this.radioButton4_CheckedChanged );
      // 
      // fromBurnButton
      // 
      this.fromBurnButton.Appearance = System.Windows.Forms.Appearance.Button;
      this.fromBurnButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
      this.fromBurnButton.Location = new System.Drawing.Point( 128, 50 );
      this.fromBurnButton.Margin = new System.Windows.Forms.Padding( 2 );
      this.fromBurnButton.Name = "fromBurnButton";
      this.fromBurnButton.Size = new System.Drawing.Size( 50, 23 );
      this.fromBurnButton.TabIndex = 6;
      this.fromBurnButton.Text = "Burn";
      this.fromBurnButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      this.fromBurnButton.UseVisualStyleBackColor = true;
      // 
      // fromFreezeButton
      // 
      this.fromFreezeButton.Appearance = System.Windows.Forms.Appearance.Button;
      this.fromFreezeButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
      this.fromFreezeButton.Location = new System.Drawing.Point( 68, 50 );
      this.fromFreezeButton.Margin = new System.Windows.Forms.Padding( 2 );
      this.fromFreezeButton.Name = "fromFreezeButton";
      this.fromFreezeButton.Size = new System.Drawing.Size( 50, 23 );
      this.fromFreezeButton.TabIndex = 5;
      this.fromFreezeButton.Text = "Freeze";
      this.fromFreezeButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      this.fromFreezeButton.UseVisualStyleBackColor = true;
      // 
      // fromNeutralButton
      // 
      this.fromNeutralButton.Appearance = System.Windows.Forms.Appearance.Button;
      this.fromNeutralButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
      this.fromNeutralButton.Location = new System.Drawing.Point( 7, 50 );
      this.fromNeutralButton.Margin = new System.Windows.Forms.Padding( 2 );
      this.fromNeutralButton.Name = "fromNeutralButton";
      this.fromNeutralButton.Size = new System.Drawing.Size( 50, 23 );
      this.fromNeutralButton.TabIndex = 4;
      this.fromNeutralButton.Text = "Neutral";
      this.fromNeutralButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      this.fromNeutralButton.UseVisualStyleBackColor = true;
      // 
      // BrushSizeGroupBox
      // 
      this.BrushSizeGroupBox.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.BrushSizeGroupBox.Controls.Add( this.brushSizeUpDown );
      this.BrushSizeGroupBox.Controls.Add( this.label2 );
      this.BrushSizeGroupBox.Controls.Add( this.label1 );
      this.BrushSizeGroupBox.Controls.Add( this.brushSizeSlider );
      this.BrushSizeGroupBox.Location = new System.Drawing.Point( 4, 162 );
      this.BrushSizeGroupBox.Margin = new System.Windows.Forms.Padding( 2 );
      this.BrushSizeGroupBox.Name = "BrushSizeGroupBox";
      this.BrushSizeGroupBox.Padding = new System.Windows.Forms.Padding( 2 );
      this.BrushSizeGroupBox.Size = new System.Drawing.Size( 190, 89 );
      this.BrushSizeGroupBox.TabIndex = 2;
      this.BrushSizeGroupBox.TabStop = false;
      this.BrushSizeGroupBox.Text = "Brush Size";
      // 
      // brushSizeUpDown
      // 
      this.brushSizeUpDown.DecimalPlaces = 1;
      this.brushSizeUpDown.Location = new System.Drawing.Point( 20, 60 );
      this.brushSizeUpDown.Maximum = new decimal( new int[] {
            50,
            0,
            0,
            0} );
      this.brushSizeUpDown.Minimum = new decimal( new int[] {
            1,
            0,
            0,
            0} );
      this.brushSizeUpDown.Name = "brushSizeUpDown";
      this.brushSizeUpDown.Size = new System.Drawing.Size( 71, 20 );
      this.brushSizeUpDown.TabIndex = 3;
      this.brushSizeUpDown.Value = new decimal( new int[] {
            5,
            0,
            0,
            0} );
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point( 5, 15 );
      this.label2.Margin = new System.Windows.Forms.Padding( 2, 0, 2, 0 );
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size( 21, 13 );
      this.label2.TabIndex = 2;
      this.label2.Text = "5m";
      // 
      // label1
      // 
      this.label1.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point( 155, 15 );
      this.label1.Margin = new System.Windows.Forms.Padding( 2, 0, 2, 0 );
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size( 27, 13 );
      this.label1.TabIndex = 1;
      this.label1.Text = "50m";
      // 
      // brushSizeSlider
      // 
      this.brushSizeSlider.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.brushSizeSlider.Location = new System.Drawing.Point( 16, 22 );
      this.brushSizeSlider.Margin = new System.Windows.Forms.Padding( 2 );
      this.brushSizeSlider.Maximum = 50;
      this.brushSizeSlider.Name = "brushSizeSlider";
      this.brushSizeSlider.Size = new System.Drawing.Size( 152, 45 );
      this.brushSizeSlider.TabIndex = 0;
      this.brushSizeSlider.TickFrequency = 5;
      this.brushSizeSlider.Value = 5;
      // 
      // groupBox1
      // 
      this.groupBox1.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.groupBox1.Controls.Add( this.toBurnButton );
      this.groupBox1.Controls.Add( this.toFreezeButton );
      this.groupBox1.Controls.Add( this.toNeutralButton );
      this.groupBox1.Location = new System.Drawing.Point( 1, 97 );
      this.groupBox1.Margin = new System.Windows.Forms.Padding( 2 );
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Padding = new System.Windows.Forms.Padding( 2 );
      this.groupBox1.Size = new System.Drawing.Size( 190, 61 );
      this.groupBox1.TabIndex = 3;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "To faction ";
      // 
      // toBurnButton
      // 
      this.toBurnButton.Appearance = System.Windows.Forms.Appearance.Button;
      this.toBurnButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
      this.toBurnButton.Location = new System.Drawing.Point( 128, 24 );
      this.toBurnButton.Margin = new System.Windows.Forms.Padding( 2 );
      this.toBurnButton.Name = "toBurnButton";
      this.toBurnButton.Size = new System.Drawing.Size( 50, 23 );
      this.toBurnButton.TabIndex = 6;
      this.toBurnButton.Text = "Burn";
      this.toBurnButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      this.toBurnButton.UseVisualStyleBackColor = true;
      // 
      // toFreezeButton
      // 
      this.toFreezeButton.Appearance = System.Windows.Forms.Appearance.Button;
      this.toFreezeButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
      this.toFreezeButton.Location = new System.Drawing.Point( 68, 24 );
      this.toFreezeButton.Margin = new System.Windows.Forms.Padding( 2 );
      this.toFreezeButton.Name = "toFreezeButton";
      this.toFreezeButton.Size = new System.Drawing.Size( 50, 23 );
      this.toFreezeButton.TabIndex = 5;
      this.toFreezeButton.Text = "Freeze";
      this.toFreezeButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      this.toFreezeButton.UseVisualStyleBackColor = true;
      // 
      // toNeutralButton
      // 
      this.toNeutralButton.Appearance = System.Windows.Forms.Appearance.Button;
      this.toNeutralButton.Checked = true;
      this.toNeutralButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
      this.toNeutralButton.Location = new System.Drawing.Point( 7, 24 );
      this.toNeutralButton.Margin = new System.Windows.Forms.Padding( 2 );
      this.toNeutralButton.Name = "toNeutralButton";
      this.toNeutralButton.Size = new System.Drawing.Size( 50, 23 );
      this.toNeutralButton.TabIndex = 4;
      this.toNeutralButton.TabStop = true;
      this.toNeutralButton.Text = "Neutral";
      this.toNeutralButton.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
      this.toNeutralButton.UseVisualStyleBackColor = true;
      // 
      // NatureMapPanel
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 197, 256 );
      this.Controls.Add( this.groupBox1 );
      this.Controls.Add( this.BrushSizeGroupBox );
      this.Controls.Add( this.FactionGroupBox );
      this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.Margin = new System.Windows.Forms.Padding( 2 );
      this.Name = "NatureMapPanel";
      this.ShowHint = WeifenLuo.WinFormsUI.Docking.DockState.Float;
      this.Text = "NatureMapPanel";
      this.FactionGroupBox.ResumeLayout( false );
      this.BrushSizeGroupBox.ResumeLayout( false );
      this.BrushSizeGroupBox.PerformLayout();
      ( (System.ComponentModel.ISupportInitialize)( this.brushSizeUpDown ) ).EndInit();
      ( (System.ComponentModel.ISupportInitialize)( this.brushSizeSlider ) ).EndInit();
      this.groupBox1.ResumeLayout( false );
      this.ResumeLayout( false );

		}

		#endregion

    private System.Windows.Forms.GroupBox FactionGroupBox;
    private System.Windows.Forms.GroupBox BrushSizeGroupBox;
    private System.Windows.Forms.RadioButton fromNeutralButton;
		private System.Windows.Forms.RadioButton fromBurnButton;
    private System.Windows.Forms.RadioButton fromFreezeButton;
    private System.Windows.Forms.TrackBar brushSizeSlider;
		private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.NumericUpDown brushSizeUpDown;
    private System.Windows.Forms.RadioButton fromAnyButton;
    private System.Windows.Forms.GroupBox groupBox1;
    private System.Windows.Forms.RadioButton toBurnButton;
    private System.Windows.Forms.RadioButton toFreezeButton;
    private System.Windows.Forms.RadioButton toNeutralButton;

	}
}