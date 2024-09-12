namespace EditorPlugins.Scene.Viewers
{
  partial class PresetCopyForm
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
      this.textBox1 = new System.Windows.Forms.TextBox();
      this.OK_Button = new System.Windows.Forms.Button();
      this.Cancel_Button = new System.Windows.Forms.Button();
      this.SuspendLayout();
      // 
      // textBox1
      // 
      this.textBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                  | System.Windows.Forms.AnchorStyles.Right)));
      this.textBox1.Location = new System.Drawing.Point(12, 12);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new System.Drawing.Size(276, 20);
      this.textBox1.TabIndex = 2;
      this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
      // 
      // OK_Button
      // 
      this.OK_Button.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.OK_Button.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.OK_Button.Location = new System.Drawing.Point(132, 46);
      this.OK_Button.Name = "OK_Button";
      this.OK_Button.Size = new System.Drawing.Size(75, 23);
      this.OK_Button.TabIndex = 0;
      this.OK_Button.Text = "OK";
      this.OK_Button.UseVisualStyleBackColor = true;
      // 
      // Cancel_Button
      // 
      this.Cancel_Button.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
      this.Cancel_Button.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.Cancel_Button.Location = new System.Drawing.Point(213, 46);
      this.Cancel_Button.Name = "Cancel_Button";
      this.Cancel_Button.Size = new System.Drawing.Size(75, 23);
      this.Cancel_Button.TabIndex = 1;
      this.Cancel_Button.Text = "Cancel";
      this.Cancel_Button.UseVisualStyleBackColor = true;
      // 
      // PresetCopyForm
      // 
      this.AcceptButton = this.OK_Button;
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.Cancel_Button;
      this.ClientSize = new System.Drawing.Size(300, 81);
      this.Controls.Add(this.Cancel_Button);
      this.Controls.Add(this.OK_Button);
      this.Controls.Add(this.textBox1);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = "PresetCopyForm";
      this.ShowIcon = false;
      this.ShowInTaskbar = false;
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.Text = "Enter Preset Name";
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.TextBox textBox1;
    private System.Windows.Forms.Button OK_Button;
    private System.Windows.Forms.Button Cancel_Button;
  }
}