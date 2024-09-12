namespace EaselLevelEditor
{
  partial class AddPointForm
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
      this.textPointYCoord = new System.Windows.Forms.TextBox();
      this.textPointXCoord = new System.Windows.Forms.TextBox();
      this.textPointIndex = new System.Windows.Forms.TextBox();
      this.label3 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.label1 = new System.Windows.Forms.Label();
      this.btnAddPoint = new System.Windows.Forms.Button();
      this.groupBox1.SuspendLayout();
      this.SuspendLayout();
      // 
      // groupBox1
      // 
      this.groupBox1.Controls.Add(this.textPointYCoord);
      this.groupBox1.Controls.Add(this.textPointXCoord);
      this.groupBox1.Controls.Add(this.textPointIndex);
      this.groupBox1.Controls.Add(this.label3);
      this.groupBox1.Controls.Add(this.label2);
      this.groupBox1.Controls.Add(this.label1);
      this.groupBox1.Location = new System.Drawing.Point(13, 13);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new System.Drawing.Size(225, 101);
      this.groupBox1.TabIndex = 0;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Point data";
      // 
      // textPointYCoord
      // 
      this.textPointYCoord.Location = new System.Drawing.Point(98, 66);
      this.textPointYCoord.Name = "textPointYCoord";
      this.textPointYCoord.Size = new System.Drawing.Size(110, 20);
      this.textPointYCoord.TabIndex = 5;
      // 
      // textPointXCoord
      // 
      this.textPointXCoord.Location = new System.Drawing.Point(98, 44);
      this.textPointXCoord.Name = "textPointXCoord";
      this.textPointXCoord.Size = new System.Drawing.Size(110, 20);
      this.textPointXCoord.TabIndex = 4;
      // 
      // textPointIndex
      // 
      this.textPointIndex.Location = new System.Drawing.Point(98, 21);
      this.textPointIndex.Name = "textPointIndex";
      this.textPointIndex.Size = new System.Drawing.Size(110, 20);
      this.textPointIndex.TabIndex = 3;
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(18, 69);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(75, 13);
      this.label3.TabIndex = 2;
      this.label3.Text = "Point Y Coord:";
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(18, 46);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(75, 13);
      this.label2.TabIndex = 1;
      this.label2.Text = "Point X Coord:";
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(18, 24);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(62, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Point index:";
      // 
      // btnAddPoint
      // 
      this.btnAddPoint.Location = new System.Drawing.Point(163, 121);
      this.btnAddPoint.Name = "btnAddPoint";
      this.btnAddPoint.Size = new System.Drawing.Size(75, 23);
      this.btnAddPoint.TabIndex = 1;
      this.btnAddPoint.Text = "Add Point";
      this.btnAddPoint.UseVisualStyleBackColor = true;
      this.btnAddPoint.Click += new System.EventHandler(this.btnAddPoint_Click);
      // 
      // AddPointForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(250, 156);
      this.Controls.Add(this.btnAddPoint);
      this.Controls.Add(this.groupBox1);
      this.Name = "AddPointForm";
      this.Text = "AddPointForm";
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.GroupBox groupBox1;
    private System.Windows.Forms.TextBox textPointYCoord;
    private System.Windows.Forms.TextBox textPointXCoord;
    private System.Windows.Forms.TextBox textPointIndex;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Button btnAddPoint;
  }
}