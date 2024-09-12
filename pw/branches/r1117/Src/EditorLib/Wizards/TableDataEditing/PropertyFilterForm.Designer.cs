namespace EditorLib.Wizards.TableDataEditing
{
	partial class PropertyFilterForm
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
			this.txtFilter = new System.Windows.Forms.TextBox();
			this.btnSaveFilter = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// txtFilter
			// 
			this.txtFilter.Location = new System.Drawing.Point( 11, 14 );
			this.txtFilter.Name = "txtFilter";
			this.txtFilter.Size = new System.Drawing.Size( 183, 20 );
			this.txtFilter.TabIndex = 0;
			this.txtFilter.KeyUp += new System.Windows.Forms.KeyEventHandler( this.OnKeyUp );
			// 
			// btnSaveFilter
			// 
			this.btnSaveFilter.DialogResult = System.Windows.Forms.DialogResult.OK;
			this.btnSaveFilter.Location = new System.Drawing.Point( 200, 12 );
			this.btnSaveFilter.Name = "btnSaveFilter";
			this.btnSaveFilter.Size = new System.Drawing.Size( 75, 23 );
			this.btnSaveFilter.TabIndex = 1;
			this.btnSaveFilter.Text = "Save";
			this.btnSaveFilter.UseVisualStyleBackColor = true;
			this.btnSaveFilter.KeyUp += new System.Windows.Forms.KeyEventHandler( this.OnKeyUp );
			// 
			// PropertyFilterForm
			// 
			this.AcceptButton = this.btnSaveFilter;
			this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size( 286, 46 );
			this.Controls.Add( this.btnSaveFilter );
			this.Controls.Add( this.txtFilter );
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Name = "PropertyFilterForm";
			this.ShowInTaskbar = false;
			this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
			this.Text = "Enter Filter";
			this.KeyUp += new System.Windows.Forms.KeyEventHandler( this.OnKeyUp );
			this.ResumeLayout( false );
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox txtFilter;
		private System.Windows.Forms.Button btnSaveFilter;
	}
}