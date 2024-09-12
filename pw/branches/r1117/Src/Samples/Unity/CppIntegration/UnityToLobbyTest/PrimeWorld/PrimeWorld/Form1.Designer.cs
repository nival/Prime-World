using System;
using System.Diagnostics;
using System.Drawing;
using System.Runtime.InteropServices;



namespace PrimeWorld
{
	partial class Form1
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
			this.pictureBox1 = new System.Windows.Forms.PictureBox();
			( (System.ComponentModel.ISupportInitialize)( this.pictureBox1 ) ).BeginInit();
			this.SuspendLayout();
			// 
			// pictureBox1
			// 
			this.pictureBox1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.pictureBox1.Location = new System.Drawing.Point( 0, 0 );
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new System.Drawing.Size( 284, 262 );
			this.pictureBox1.TabIndex = 0;
			this.pictureBox1.TabStop = false;
			this.pictureBox1.Image = Image.FromFile("C:/Work/UnityToLobbyTest/PrimeWorld/PrimeWorld/bin/Debug/LobbyScreen.png");
			// 
			// Form1
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 284, 262 );
			this.Controls.Add( this.pictureBox1 );
			this.Name = "Form1";
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Prime World";
			this.Load += new System.EventHandler( this.Form1_Load );
			( (System.ComponentModel.ISupportInitialize)( this.pictureBox1 ) ).EndInit();
			this.ResumeLayout( false );

		}
		#endregion

		private System.Windows.Forms.PictureBox pictureBox1;
	}
}

