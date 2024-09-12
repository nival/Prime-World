namespace EaselLevelEditor
{
  partial class RemovePointForm
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
      this.groupBox1 = new System.Windows.Forms.GroupBox();
      this.textIndex = new System.Windows.Forms.TextBox();
      this.btnOK = new System.Windows.Forms.Button();
      this.groupBox1.SuspendLayout();
      this.SuspendLayout();
      // 
      // groupBox1
      // 
      this.groupBox1.Controls.Add(this.textIndex);
      this.groupBox1.Location = new System.Drawing.Point(8, 8);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new System.Drawing.Size(124, 46);
      this.groupBox1.TabIndex = 0;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Select Point Index";
      // 
      // textIndex
      // 
      this.textIndex.Location = new System.Drawing.Point(13, 19);
      this.textIndex.Name = "textIndex";
      this.textIndex.Size = new System.Drawing.Size(98, 20);
      this.textIndex.TabIndex = 0;
      // 
      // btnOK
      // 
      this.btnOK.Location = new System.Drawing.Point(21, 60);
      this.btnOK.Name = "btnOK";
      this.btnOK.Size = new System.Drawing.Size(98, 23);
      this.btnOK.TabIndex = 1;
      this.btnOK.Text = "OK";
      this.btnOK.UseVisualStyleBackColor = true;
      this.btnOK.Click += new System.EventHandler(this.btnOK_Click);
      // 
      // RemovePointForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(141, 93);
      this.Controls.Add(this.btnOK);
      this.Controls.Add(this.groupBox1);
      this.Name = "RemovePointForm";
      this.Text = "RemovePointForm";
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.GroupBox groupBox1;
    private System.Windows.Forms.TextBox textIndex;
    private System.Windows.Forms.Button btnOK;
  }
}