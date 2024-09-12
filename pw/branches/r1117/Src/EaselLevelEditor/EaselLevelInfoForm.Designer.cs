namespace EaselLevelEditor
{
  partial class EaselLevelInfoForm
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
      this.textBoardHeight = new System.Windows.Forms.TextBox();
      this.textBoardWidth = new System.Windows.Forms.TextBox();
      this.label2 = new System.Windows.Forms.Label();
      this.label1 = new System.Windows.Forms.Label();
      this.groupBox2 = new System.Windows.Forms.GroupBox();
      this.textControlPointsNum = new System.Windows.Forms.TextBox();
      this.textSplineDegree = new System.Windows.Forms.TextBox();
      this.label4 = new System.Windows.Forms.Label();
      this.label3 = new System.Windows.Forms.Label();
      this.listControlPointsData = new System.Windows.Forms.ListView();
      this.groupBox3 = new System.Windows.Forms.GroupBox();
      this.btnAddCP = new System.Windows.Forms.Button();
      this.btnRemoveCP = new System.Windows.Forms.Button();
      this.btnSaveLevel = new System.Windows.Forms.Button();
      this.cpNumHeader = new System.Windows.Forms.ColumnHeader();
      this.cpXCoordHeader = new System.Windows.Forms.ColumnHeader();
      this.cpYCoordHeader = new System.Windows.Forms.ColumnHeader();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.SuspendLayout();
      // 
      // groupBox1
      // 
      this.groupBox1.Controls.Add(this.textBoardHeight);
      this.groupBox1.Controls.Add(this.textBoardWidth);
      this.groupBox1.Controls.Add(this.label2);
      this.groupBox1.Controls.Add(this.label1);
      this.groupBox1.Location = new System.Drawing.Point(336, 12);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new System.Drawing.Size(188, 74);
      this.groupBox1.TabIndex = 0;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Logical Screen Dimenstions";
      // 
      // textBoardHeight
      // 
      this.textBoardHeight.Location = new System.Drawing.Point(78, 43);
      this.textBoardHeight.Name = "textBoardHeight";
      this.textBoardHeight.ReadOnly = true;
      this.textBoardHeight.Size = new System.Drawing.Size(100, 20);
      this.textBoardHeight.TabIndex = 3;
      // 
      // textBoardWidth
      // 
      this.textBoardWidth.Location = new System.Drawing.Point(78, 20);
      this.textBoardWidth.Name = "textBoardWidth";
      this.textBoardWidth.ReadOnly = true;
      this.textBoardWidth.Size = new System.Drawing.Size(100, 20);
      this.textBoardWidth.TabIndex = 2;
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(7, 47);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(70, 13);
      this.label2.TabIndex = 1;
      this.label2.Text = "Board height:";
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(7, 23);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(66, 13);
      this.label1.TabIndex = 0;
      this.label1.Text = "Board width:";
      // 
      // groupBox2
      // 
      this.groupBox2.Controls.Add(this.textControlPointsNum);
      this.groupBox2.Controls.Add(this.textSplineDegree);
      this.groupBox2.Controls.Add(this.label4);
      this.groupBox2.Controls.Add(this.label3);
      this.groupBox2.Location = new System.Drawing.Point(336, 92);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new System.Drawing.Size(187, 82);
      this.groupBox2.TabIndex = 1;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Trajectory params:";
      // 
      // textControlPointsNum
      // 
      this.textControlPointsNum.Location = new System.Drawing.Point(107, 47);
      this.textControlPointsNum.Name = "textControlPointsNum";
      this.textControlPointsNum.ReadOnly = true;
      this.textControlPointsNum.Size = new System.Drawing.Size(70, 20);
      this.textControlPointsNum.TabIndex = 6;
      // 
      // textSplineDegree
      // 
      this.textSplineDegree.Location = new System.Drawing.Point(84, 24);
      this.textSplineDegree.Name = "textSplineDegree";
      this.textSplineDegree.ReadOnly = true;
      this.textSplineDegree.Size = new System.Drawing.Size(94, 20);
      this.textSplineDegree.TabIndex = 4;
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point(8, 50);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(97, 13);
      this.label4.TabIndex = 5;
      this.label4.Text = "Control points num:";
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(8, 26);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(75, 13);
      this.label3.TabIndex = 4;
      this.label3.Text = "Spline degree:";
      // 
      // listControlPointsData
      // 
      this.listControlPointsData.AccessibleRole = System.Windows.Forms.AccessibleRole.List;
      this.listControlPointsData.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.cpNumHeader,
            this.cpXCoordHeader,
            this.cpYCoordHeader});
      this.listControlPointsData.FullRowSelect = true;
      this.listControlPointsData.Location = new System.Drawing.Point(25, 33);
      this.listControlPointsData.MultiSelect = false;
      this.listControlPointsData.Name = "listControlPointsData";
      this.listControlPointsData.Size = new System.Drawing.Size(294, 265);
      this.listControlPointsData.TabIndex = 2;
      this.listControlPointsData.UseCompatibleStateImageBehavior = false;
      // 
      // groupBox3
      // 
      this.groupBox3.Location = new System.Drawing.Point(12, 12);
      this.groupBox3.Name = "groupBox3";
      this.groupBox3.Size = new System.Drawing.Size(318, 297);
      this.groupBox3.TabIndex = 3;
      this.groupBox3.TabStop = false;
      this.groupBox3.Text = "Trajectory control points";
      // 
      // btnAddCP
      // 
      this.btnAddCP.Location = new System.Drawing.Point(336, 180);
      this.btnAddCP.Name = "btnAddCP";
      this.btnAddCP.Size = new System.Drawing.Size(188, 25);
      this.btnAddCP.TabIndex = 4;
      this.btnAddCP.Text = "Add Control Point";
      this.btnAddCP.UseVisualStyleBackColor = true;
      this.btnAddCP.Click += new System.EventHandler(this.btnAddCP_Click);
      // 
      // btnRemoveCP
      // 
      this.btnRemoveCP.Location = new System.Drawing.Point(336, 211);
      this.btnRemoveCP.Name = "btnRemoveCP";
      this.btnRemoveCP.Size = new System.Drawing.Size(188, 25);
      this.btnRemoveCP.TabIndex = 5;
      this.btnRemoveCP.Text = "Remove Control Point";
      this.btnRemoveCP.UseVisualStyleBackColor = true;
      this.btnRemoveCP.Click += new System.EventHandler(this.btnRemoveCP_Click);
      // 
      // btnSaveLevel
      // 
      this.btnSaveLevel.Location = new System.Drawing.Point(336, 273);
      this.btnSaveLevel.Name = "btnSaveLevel";
      this.btnSaveLevel.Size = new System.Drawing.Size(188, 25);
      this.btnSaveLevel.TabIndex = 6;
      this.btnSaveLevel.Text = "Save Level to File";
      this.btnSaveLevel.UseVisualStyleBackColor = true;
      this.btnSaveLevel.Click += new System.EventHandler(this.btnSaveLevel_Click);
      // 
      // cpNumHeader
      // 
      this.cpNumHeader.Text = "CP Num";
      // 
      // cpXCoordHeader
      // 
      this.cpXCoordHeader.Text = "X Coordinate";
      // 
      // cpYCoordHeader
      // 
      this.cpYCoordHeader.Text = "Y Coordinate";
      // 
      // EaselLevelInfo
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(541, 325);
      this.Controls.Add(this.btnSaveLevel);
      this.Controls.Add(this.btnRemoveCP);
      this.Controls.Add(this.btnAddCP);
      this.Controls.Add(this.listControlPointsData);
      this.Controls.Add(this.groupBox2);
      this.Controls.Add(this.groupBox1);
      this.Controls.Add(this.groupBox3);
      this.Name = "EaselLevelInfo";
      this.Text = "EaselLevelInfo";
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.ResumeLayout(false);

    }

    #endregion

    private System.Windows.Forms.GroupBox groupBox1;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.TextBox textBoardHeight;
    private System.Windows.Forms.TextBox textBoardWidth;
    private System.Windows.Forms.GroupBox groupBox2;
    private System.Windows.Forms.TextBox textControlPointsNum;
    private System.Windows.Forms.TextBox textSplineDegree;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.ListView listControlPointsData;
    private System.Windows.Forms.GroupBox groupBox3;
    private System.Windows.Forms.Button btnAddCP;
    private System.Windows.Forms.Button btnRemoveCP;
    private System.Windows.Forms.Button btnSaveLevel;
    private System.Windows.Forms.ColumnHeader cpNumHeader;
    private System.Windows.Forms.ColumnHeader cpXCoordHeader;
    private System.Windows.Forms.ColumnHeader cpYCoordHeader;
  }
}