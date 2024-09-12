namespace EditorPlugins.Editors.MatrixType
{
	partial class MatrixTypePropertyEditorForm
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
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.textBox2 = new System.Windows.Forms.TextBox();
			this.textBox3 = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.textBox4 = new System.Windows.Forms.TextBox();
			this.textBox5 = new System.Windows.Forms.TextBox();
			this.textBox6 = new System.Windows.Forms.TextBox();
			this.textBox7 = new System.Windows.Forms.TextBox();
			this.button1 = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Location = new System.Drawing.Point( 14, 23 );
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size( 47, 13 );
			this.label1.TabIndex = 0;
			this.label1.Text = "Position:";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Location = new System.Drawing.Point( 126, 23 );
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size( 50, 13 );
			this.label2.TabIndex = 4;
			this.label2.Text = "Rotation:";
			// 
			// textBox1
			// 
			this.textBox1.Location = new System.Drawing.Point( 16, 49 );
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size( 81, 20 );
			this.textBox1.TabIndex = 1;
			// 
			// textBox2
			// 
			this.textBox2.Location = new System.Drawing.Point( 16, 75 );
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new System.Drawing.Size( 81, 20 );
			this.textBox2.TabIndex = 2;
			// 
			// textBox3
			// 
			this.textBox3.Location = new System.Drawing.Point( 16, 101 );
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new System.Drawing.Size( 81, 20 );
			this.textBox3.TabIndex = 3;
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Location = new System.Drawing.Point( 244, 23 );
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size( 37, 13 );
			this.label3.TabIndex = 5;
			this.label3.Text = "Scale:";
			// 
			// textBox4
			// 
			this.textBox4.Location = new System.Drawing.Point( 129, 49 );
			this.textBox4.Name = "textBox4";
			this.textBox4.Size = new System.Drawing.Size( 88, 20 );
			this.textBox4.TabIndex = 4;
			// 
			// textBox5
			// 
			this.textBox5.Location = new System.Drawing.Point( 129, 75 );
			this.textBox5.Name = "textBox5";
			this.textBox5.Size = new System.Drawing.Size( 88, 20 );
			this.textBox5.TabIndex = 5;
			// 
			// textBox6
			// 
			this.textBox6.Location = new System.Drawing.Point( 129, 101 );
			this.textBox6.Name = "textBox6";
			this.textBox6.Size = new System.Drawing.Size( 88, 20 );
			this.textBox6.TabIndex = 6;
			// 
			// textBox7
			// 
			this.textBox7.Location = new System.Drawing.Point( 247, 49 );
			this.textBox7.Name = "textBox7";
			this.textBox7.Size = new System.Drawing.Size( 85, 20 );
			this.textBox7.TabIndex = 7;
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point( 247, 75 );
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size( 85, 46 );
			this.button1.TabIndex = 8;
			this.button1.Text = "OK";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler( this.button1_Click );
			// 
			// MatrixTypePropertyEditorForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 345, 134 );
			this.ControlBox = false;
			this.Controls.Add( this.button1 );
			this.Controls.Add( this.textBox7 );
			this.Controls.Add( this.textBox4 );
			this.Controls.Add( this.textBox5 );
			this.Controls.Add( this.textBox6 );
			this.Controls.Add( this.label3 );
			this.Controls.Add( this.label2 );
			this.Controls.Add( this.textBox3 );
			this.Controls.Add( this.textBox2 );
			this.Controls.Add( this.textBox1 );
			this.Controls.Add( this.label1 );
			this.Name = "MatrixTypePropertyEditorForm";
			this.ShowIcon = false;
			this.Text = "Matrix Edit";
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Label label1;
		public System.Windows.Forms.TextBox textBox1;
		public System.Windows.Forms.TextBox textBox2;
		public System.Windows.Forms.TextBox textBox3;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		public System.Windows.Forms.TextBox textBox4;
		public System.Windows.Forms.TextBox textBox5;
		public System.Windows.Forms.TextBox textBox6;
		public System.Windows.Forms.TextBox textBox7;
		private System.Windows.Forms.Button button1;
	}
}