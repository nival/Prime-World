namespace EditorPlugins.Scene.Viewers
{
	partial class AnimatedMeshSettingsControl
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

		#region Component Designer generated code

		/// <summary> 
		/// Required method for Designer support - do not modify 
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.selectMeshButton = new System.Windows.Forms.Button();
			this.meshTextBox = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// selectMeshButton
			// 
			this.selectMeshButton.Location = new System.Drawing.Point(0, 29);
			this.selectMeshButton.Name = "selectMeshButton";
			this.selectMeshButton.Size = new System.Drawing.Size(75, 23);
			this.selectMeshButton.TabIndex = 0;
			this.selectMeshButton.Text = "Select...";
			this.selectMeshButton.UseVisualStyleBackColor = true;
			this.selectMeshButton.Click += new System.EventHandler(this.OnSelectMeshButtonClick);
			// 
			// meshTextBox
			// 
			this.meshTextBox.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
									| System.Windows.Forms.AnchorStyles.Right)));
			this.meshTextBox.Location = new System.Drawing.Point(0, 3);
			this.meshTextBox.Name = "meshTextBox";
			this.meshTextBox.ReadOnly = true;
			this.meshTextBox.Size = new System.Drawing.Size(303, 20);
			this.meshTextBox.TabIndex = 1;
			// 
			// AnimatedMeshSettingsControl
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.Controls.Add(this.meshTextBox);
			this.Controls.Add(this.selectMeshButton);
			this.Name = "AnimatedMeshSettingsControl";
			this.Size = new System.Drawing.Size(309, 313);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button selectMeshButton;
		private System.Windows.Forms.TextBox meshTextBox;
	}
}
