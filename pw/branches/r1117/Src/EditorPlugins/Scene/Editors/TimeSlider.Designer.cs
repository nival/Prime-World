namespace EditorPlugins.Scene.Editors
{
  partial class TimeSlider
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
      this.trackBarSpeed = new System.Windows.Forms.TrackBar();
      this.btnPlay = new System.Windows.Forms.Button();
      this.label1 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.label3 = new System.Windows.Forms.Label();
      this.label4 = new System.Windows.Forms.Label();
      this.label5 = new System.Windows.Forms.Label();
      this.label6 = new System.Windows.Forms.Label();
      this.label7 = new System.Windows.Forms.Label();
      this.label8 = new System.Windows.Forms.Label();
      this.label9 = new System.Windows.Forms.Label();
      this.label10 = new System.Windows.Forms.Label();
      this.llMeasure = new System.Windows.Forms.LinkLabel();
      this.lblCurrentValue = new System.Windows.Forms.Label();
      this.trackBarTimeSlider = new EConTech.Windows.MACUI.MACTrackBar();
      ( (System.ComponentModel.ISupportInitialize)( this.trackBarSpeed ) ).BeginInit();
      this.SuspendLayout();
      // 
      // trackBarSpeed
      // 
      this.trackBarSpeed.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.trackBarSpeed.AutoSize = false;
      this.trackBarSpeed.Cursor = System.Windows.Forms.Cursors.Hand;
      this.trackBarSpeed.LargeChange = 1;
      this.trackBarSpeed.Location = new System.Drawing.Point( 467, 17 );
      this.trackBarSpeed.Margin = new System.Windows.Forms.Padding( 0 );
      this.trackBarSpeed.Maximum = 9;
      this.trackBarSpeed.Name = "trackBarSpeed";
      this.trackBarSpeed.Size = new System.Drawing.Size( 150, 36 );
      this.trackBarSpeed.TabIndex = 3;
      this.trackBarSpeed.TickStyle = System.Windows.Forms.TickStyle.TopLeft;
      this.trackBarSpeed.Value = 5;
      this.trackBarSpeed.ValueChanged += new System.EventHandler( this.trackBarSpeed_ValueChanged );
      this.trackBarSpeed.KeyDown += new System.Windows.Forms.KeyEventHandler( this.OnInternalKeyDown );
      // 
      // btnPlay
      // 
      this.btnPlay.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left ) ) );
      this.btnPlay.Location = new System.Drawing.Point( 3, 7 );
      this.btnPlay.Name = "btnPlay";
      this.btnPlay.Size = new System.Drawing.Size( 51, 50 );
      this.btnPlay.TabIndex = 0;
      this.btnPlay.Text = "Pause";
      this.btnPlay.UseVisualStyleBackColor = true;
      this.btnPlay.Click += new System.EventHandler( this.btnPlay_Click );
      this.btnPlay.KeyDown += new System.Windows.Forms.KeyEventHandler( this.OnInternalKeyDown );
      // 
      // label1
      // 
      this.label1.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.label1.AutoSize = true;
      this.label1.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.label1.Location = new System.Drawing.Point( 467, 10 );
      this.label1.Margin = new System.Windows.Forms.Padding( 0 );
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size( 19, 9 );
      this.label1.TabIndex = 3;
      this.label1.Text = "1fps";
      // 
      // label2
      // 
      this.label2.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.label2.AutoSize = true;
      this.label2.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.label2.Location = new System.Drawing.Point( 483, 10 );
      this.label2.Margin = new System.Windows.Forms.Padding( 0 );
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size( 19, 9 );
      this.label2.TabIndex = 4;
      this.label2.Text = "1/16";
      // 
      // label3
      // 
      this.label3.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.label3.AutoSize = true;
      this.label3.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.label3.Location = new System.Drawing.Point( 500, 10 );
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size( 15, 9 );
      this.label3.TabIndex = 5;
      this.label3.Text = "1/8";
      // 
      // label4
      // 
      this.label4.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.label4.AutoSize = true;
      this.label4.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.label4.Location = new System.Drawing.Point( 513, 10 );
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size( 15, 9 );
      this.label4.TabIndex = 6;
      this.label4.Text = "1/4";
      // 
      // label5
      // 
      this.label5.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.label5.AutoSize = true;
      this.label5.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.label5.Location = new System.Drawing.Point( 528, 10 );
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size( 15, 9 );
      this.label5.TabIndex = 7;
      this.label5.Text = "1/2";
      // 
      // label6
      // 
      this.label6.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.label6.AutoSize = true;
      this.label6.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.label6.Location = new System.Drawing.Point( 544, 10 );
      this.label6.Name = "label6";
      this.label6.Size = new System.Drawing.Size( 9, 9 );
      this.label6.TabIndex = 8;
      this.label6.Text = "1";
      // 
      // label7
      // 
      this.label7.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.label7.AutoSize = true;
      this.label7.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.label7.Location = new System.Drawing.Point( 558, 10 );
      this.label7.Name = "label7";
      this.label7.Size = new System.Drawing.Size( 9, 9 );
      this.label7.TabIndex = 9;
      this.label7.Text = "2";
      // 
      // label8
      // 
      this.label8.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.label8.AutoSize = true;
      this.label8.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.label8.Location = new System.Drawing.Point( 571, 10 );
      this.label8.Name = "label8";
      this.label8.Size = new System.Drawing.Size( 9, 9 );
      this.label8.TabIndex = 10;
      this.label8.Text = "4";
      // 
      // label9
      // 
      this.label9.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.label9.AutoSize = true;
      this.label9.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.label9.Location = new System.Drawing.Point( 584, 10 );
      this.label9.Name = "label9";
      this.label9.Size = new System.Drawing.Size( 9, 9 );
      this.label9.TabIndex = 11;
      this.label9.Text = "8";
      // 
      // label10
      // 
      this.label10.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.label10.AutoSize = true;
      this.label10.Font = new System.Drawing.Font( "Microsoft Sans Serif", 6F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.label10.Location = new System.Drawing.Point( 596, 10 );
      this.label10.Name = "label10";
      this.label10.Size = new System.Drawing.Size( 13, 9 );
      this.label10.TabIndex = 12;
      this.label10.Text = "16";
      // 
      // llMeasure
      // 
      this.llMeasure.Anchor = System.Windows.Forms.AnchorStyles.Top;
      this.llMeasure.Cursor = System.Windows.Forms.Cursors.Hand;
      this.llMeasure.Font = new System.Drawing.Font( "Microsoft Sans Serif", 7F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.llMeasure.LinkBehavior = System.Windows.Forms.LinkBehavior.HoverUnderline;
      this.llMeasure.LinkColor = System.Drawing.Color.RoyalBlue;
      this.llMeasure.Location = new System.Drawing.Point( 256, 3 );
      this.llMeasure.Margin = new System.Windows.Forms.Padding( 0 );
      this.llMeasure.Name = "llMeasure";
      this.llMeasure.Size = new System.Drawing.Size( 72, 21 );
      this.llMeasure.TabIndex = 2;
      this.llMeasure.TabStop = true;
      this.llMeasure.Text = "milliseconds";
      this.llMeasure.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
      this.llMeasure.VisitedLinkColor = System.Drawing.Color.RoyalBlue;
      this.llMeasure.PreviewKeyDown += new System.Windows.Forms.PreviewKeyDownEventHandler( this.llMeasure_PreviewKeyDown );
      this.llMeasure.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler( this.llMeasure_LinkClicked );
      // 
      // lblCurrentValue
      // 
      this.lblCurrentValue.Anchor = System.Windows.Forms.AnchorStyles.Top;
      this.lblCurrentValue.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.lblCurrentValue.Location = new System.Drawing.Point( 190, 8 );
      this.lblCurrentValue.Name = "lblCurrentValue";
      this.lblCurrentValue.Size = new System.Drawing.Size( 63, 13 );
      this.lblCurrentValue.TabIndex = 13;
      this.lblCurrentValue.Text = "0";
      this.lblCurrentValue.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
      // 
      // trackBarTimeSlider
      // 
      this.trackBarTimeSlider.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.trackBarTimeSlider.BackColor = System.Drawing.SystemColors.ControlLight;
      this.trackBarTimeSlider.BorderColor = System.Drawing.SystemColors.ActiveBorder;
      this.trackBarTimeSlider.Cursor = System.Windows.Forms.Cursors.Hand;
      this.trackBarTimeSlider.Font = new System.Drawing.Font( "Verdana", 6F );
      this.trackBarTimeSlider.ForeColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 123 ) ) ) ), ( (int)( ( (byte)( 125 ) ) ) ), ( (int)( ( (byte)( 123 ) ) ) ) );
      this.trackBarTimeSlider.IndentHeight = 0;
      this.trackBarTimeSlider.IndentWidth = 3;
      this.trackBarTimeSlider.Location = new System.Drawing.Point( 60, 24 );
      this.trackBarTimeSlider.Maximum = 10;
      this.trackBarTimeSlider.Minimum = 0;
      this.trackBarTimeSlider.Name = "trackBarTimeSlider";
      this.trackBarTimeSlider.Size = new System.Drawing.Size( 404, 29 );
      this.trackBarTimeSlider.TabIndex = 1;
      this.trackBarTimeSlider.TickColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 148 ) ) ) ), ( (int)( ( (byte)( 146 ) ) ) ), ( (int)( ( (byte)( 148 ) ) ) ) );
      this.trackBarTimeSlider.TickHeight = 2;
      this.trackBarTimeSlider.TrackerColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 24 ) ) ) ), ( (int)( ( (byte)( 130 ) ) ) ), ( (int)( ( (byte)( 198 ) ) ) ) );
      this.trackBarTimeSlider.TrackerImage = global::EditorPlugins.EditorPluginResources.TimeTracker;
      this.trackBarTimeSlider.TrackerSize = new System.Drawing.Size( 16, 16 );
      this.trackBarTimeSlider.TrackLineColor = System.Drawing.Color.FromArgb( ( (int)( ( (byte)( 90 ) ) ) ), ( (int)( ( (byte)( 93 ) ) ) ), ( (int)( ( (byte)( 90 ) ) ) ) );
      this.trackBarTimeSlider.TrackLineHeight = 1;
      this.trackBarTimeSlider.Value = 0;
      this.trackBarTimeSlider.ValueChanged += new EConTech.Windows.MACUI.ValueChangedHandler( this.trackBarTimeSlider_ValueChanged );
      this.trackBarTimeSlider.Scroll += new System.EventHandler( this.trackBarTimeSlider_Scroll );
      this.trackBarTimeSlider.MouseDown += new System.Windows.Forms.MouseEventHandler( this.trackBarTimeSlider_MouseDown );
      this.trackBarTimeSlider.MouseUp += new System.Windows.Forms.MouseEventHandler( this.trackBarTimeSlider_MouseUp );
      this.trackBarTimeSlider.ClientSizeChanged += new System.EventHandler( this.trackBarTimeSlider_ClientSizeChanged );
      this.trackBarTimeSlider.KeyDown += new System.Windows.Forms.KeyEventHandler( this.OnInternalKeyDown );
      // 
      // TimeSlider
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.Controls.Add( this.lblCurrentValue );
      this.Controls.Add( this.label10 );
      this.Controls.Add( this.label9 );
      this.Controls.Add( this.label8 );
      this.Controls.Add( this.label7 );
      this.Controls.Add( this.label6 );
      this.Controls.Add( this.label5 );
      this.Controls.Add( this.label4 );
      this.Controls.Add( this.label3 );
      this.Controls.Add( this.label2 );
      this.Controls.Add( this.label1 );
      this.Controls.Add( this.btnPlay );
      this.Controls.Add( this.trackBarSpeed );
      this.Controls.Add( this.trackBarTimeSlider );
      this.Controls.Add( this.llMeasure );
      this.Name = "TimeSlider";
      this.Size = new System.Drawing.Size( 616, 58 );
      ( (System.ComponentModel.ISupportInitialize)( this.trackBarSpeed ) ).EndInit();
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

		private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.Label label5;
    private System.Windows.Forms.Label label6;
    private System.Windows.Forms.Label label7;
    private System.Windows.Forms.Label label8;
    private System.Windows.Forms.Label label9;
    private System.Windows.Forms.Label label10;
		private System.Windows.Forms.LinkLabel llMeasure;
    private System.Windows.Forms.Button btnPlay;
    private System.Windows.Forms.TrackBar trackBarSpeed;
    private EConTech.Windows.MACUI.MACTrackBar trackBarTimeSlider;
    private System.Windows.Forms.Label lblCurrentValue;
  }
}
