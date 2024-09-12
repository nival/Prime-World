namespace EditorPlugins.Editors.AnimatedCurves
{
	partial class AnimatedCurvesPanel
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
			this.animatedCurvesControl = new EditorPlugins.Editors.AnimatedCurves.AnimatedCurvesControl();
			this.SuspendLayout();
			// 
			// animatedCurvesControl
			// 
			this.animatedCurvesControl.Dock = System.Windows.Forms.DockStyle.Fill;
			this.animatedCurvesControl.Location = new System.Drawing.Point( 0, 0 );
			this.animatedCurvesControl.Name = "animatedCurvesControl";
			this.animatedCurvesControl.Size = new System.Drawing.Size( 648, 476 );
			this.animatedCurvesControl.TabIndex = 0;
			// 
			// AnimatedCurvesPanel
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 648, 476 );
			this.Controls.Add( this.animatedCurvesControl );
			this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
			this.Name = "AnimatedCurvesPanel";
			this.TabText = "Animation Curves";
			this.Text = "Animation Curves";
			this.ResumeLayout( false );

		}

		#endregion

		private EditorPlugins.Editors.AnimatedCurves.AnimatedCurvesControl animatedCurvesControl;

	}
}