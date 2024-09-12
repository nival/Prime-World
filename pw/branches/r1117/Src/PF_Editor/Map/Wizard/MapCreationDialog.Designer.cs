namespace PF_Editor.Map.Wizard
{
	partial class MapCreationDialog
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
			if ( disposing && (components != null) )
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
      this.numWidth = new System.Windows.Forms.NumericUpDown();
      this.numHeight = new System.Windows.Forms.NumericUpDown();
      this.label1 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.btnCancel = new System.Windows.Forms.Button();
      this.btnCreate = new System.Windows.Forms.Button();
      this.groupBox1 = new System.Windows.Forms.GroupBox();
      this.numResolution = new System.Windows.Forms.NumericUpDown();
      this.label5 = new System.Windows.Forms.Label();
      this.label4 = new System.Windows.Forms.Label();
      this.txtLightEnvironment = new System.Windows.Forms.TextBox();
      this.btnLightEnvironment = new System.Windows.Forms.Button();
      this.lblName = new System.Windows.Forms.Label();
      this.txtName = new System.Windows.Forms.TextBox();
      this.lblMapType = new System.Windows.Forms.Label();
      this.cboMapType = new System.Windows.Forms.ComboBox();
      this.cbEditableNatureMap = new System.Windows.Forms.CheckBox();
      ((System.ComponentModel.ISupportInitialize)(this.numWidth)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.numHeight)).BeginInit();
      this.groupBox1.SuspendLayout();
      ((System.ComponentModel.ISupportInitialize)(this.numResolution)).BeginInit();
      this.SuspendLayout();
      // 
      // numWidth
      // 
      this.numWidth.Location = new System.Drawing.Point(101, 32);
      this.numWidth.Margin = new System.Windows.Forms.Padding(4);
      this.numWidth.Maximum = new decimal(new int[] {
            64,
            0,
            0,
            0});
      this.numWidth.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
      this.numWidth.Name = "numWidth";
      this.numWidth.Size = new System.Drawing.Size(169, 22);
      this.numWidth.TabIndex = 0;
      this.numWidth.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
      // 
      // numHeight
      // 
      this.numHeight.Location = new System.Drawing.Point(101, 64);
      this.numHeight.Margin = new System.Windows.Forms.Padding(4);
      this.numHeight.Maximum = new decimal(new int[] {
            64,
            0,
            0,
            0});
      this.numHeight.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
      this.numHeight.Name = "numHeight";
      this.numHeight.Size = new System.Drawing.Size(169, 22);
      this.numHeight.TabIndex = 1;
      this.numHeight.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(8, 34);
      this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(67, 17);
      this.label1.TabIndex = 0;
      this.label1.Text = "Width (X)";
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(8, 66);
      this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(72, 17);
      this.label2.TabIndex = 2;
      this.label2.Text = "Height (Y)";
      // 
      // btnCancel
      // 
      this.btnCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.btnCancel.Location = new System.Drawing.Point(171, 320);
      this.btnCancel.Margin = new System.Windows.Forms.Padding(4);
      this.btnCancel.Name = "btnCancel";
      this.btnCancel.Size = new System.Drawing.Size(100, 28);
      this.btnCancel.TabIndex = 7;
      this.btnCancel.Text = "Cancel";
      this.btnCancel.UseVisualStyleBackColor = true;
      // 
      // btnCreate
      // 
      this.btnCreate.Location = new System.Drawing.Point(63, 320);
      this.btnCreate.Margin = new System.Windows.Forms.Padding(4);
      this.btnCreate.Name = "btnCreate";
      this.btnCreate.Size = new System.Drawing.Size(100, 28);
      this.btnCreate.TabIndex = 6;
      this.btnCreate.Text = "Create";
      this.btnCreate.UseVisualStyleBackColor = true;
      this.btnCreate.Click += new System.EventHandler(this.btnCreate_Click);
      // 
      // groupBox1
      // 
      this.groupBox1.Controls.Add(this.numResolution);
      this.groupBox1.Controls.Add(this.label5);
      this.groupBox1.Controls.Add(this.label1);
      this.groupBox1.Controls.Add(this.numWidth);
      this.groupBox1.Controls.Add(this.numHeight);
      this.groupBox1.Controls.Add(this.label2);
      this.groupBox1.Location = new System.Drawing.Point(16, 106);
      this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
      this.groupBox1.Size = new System.Drawing.Size(295, 140);
      this.groupBox1.TabIndex = 3;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Map size in terrain patches";
      // 
      // numResolution
      // 
      this.numResolution.Enabled = false;
      this.numResolution.Location = new System.Drawing.Point(101, 96);
      this.numResolution.Margin = new System.Windows.Forms.Padding(4);
      this.numResolution.Maximum = new decimal(new int[] {
            40,
            0,
            0,
            0});
      this.numResolution.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
      this.numResolution.Name = "numResolution";
      this.numResolution.Size = new System.Drawing.Size(169, 22);
      this.numResolution.TabIndex = 2;
      this.numResolution.Value = new decimal(new int[] {
            20,
            0,
            0,
            0});
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Location = new System.Drawing.Point(8, 98);
      this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size(75, 17);
      this.label5.TabIndex = 4;
      this.label5.Text = "Resolution";
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point(12, 255);
      this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(121, 17);
      this.label4.TabIndex = 10;
      this.label4.Text = "Light environment";
      // 
      // txtLightEnvironment
      // 
      this.txtLightEnvironment.Location = new System.Drawing.Point(16, 275);
      this.txtLightEnvironment.Margin = new System.Windows.Forms.Padding(4);
      this.txtLightEnvironment.Name = "txtLightEnvironment";
      this.txtLightEnvironment.ReadOnly = true;
      this.txtLightEnvironment.Size = new System.Drawing.Size(239, 22);
      this.txtLightEnvironment.TabIndex = 4;
      this.txtLightEnvironment.Text = "/Tech/Natural.LTEN";
      // 
      // btnLightEnvironment
      // 
      this.btnLightEnvironment.Location = new System.Drawing.Point(264, 275);
      this.btnLightEnvironment.Margin = new System.Windows.Forms.Padding(4);
      this.btnLightEnvironment.Name = "btnLightEnvironment";
      this.btnLightEnvironment.Size = new System.Drawing.Size(47, 25);
      this.btnLightEnvironment.TabIndex = 5;
      this.btnLightEnvironment.Text = "...";
      this.btnLightEnvironment.UseVisualStyleBackColor = true;
      this.btnLightEnvironment.Click += new System.EventHandler(this.btnLightEnvironment_Click);
      // 
      // lblName
      // 
      this.lblName.AutoSize = true;
      this.lblName.Location = new System.Drawing.Point(12, 11);
      this.lblName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
      this.lblName.Name = "lblName";
      this.lblName.Size = new System.Drawing.Size(45, 17);
      this.lblName.TabIndex = 7;
      this.lblName.Text = "Name";
      // 
      // txtName
      // 
      this.txtName.Location = new System.Drawing.Point(67, 7);
      this.txtName.Margin = new System.Windows.Forms.Padding(4);
      this.txtName.Name = "txtName";
      this.txtName.Size = new System.Drawing.Size(243, 22);
      this.txtName.TabIndex = 0;
      // 
      // lblMapType
      // 
      this.lblMapType.AutoSize = true;
      this.lblMapType.Location = new System.Drawing.Point(12, 43);
      this.lblMapType.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
      this.lblMapType.Name = "lblMapType";
      this.lblMapType.Size = new System.Drawing.Size(40, 17);
      this.lblMapType.TabIndex = 9;
      this.lblMapType.Text = "Type";
      // 
      // cboMapType
      // 
      this.cboMapType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
      this.cboMapType.FormattingEnabled = true;
      this.cboMapType.Location = new System.Drawing.Point(67, 39);
      this.cboMapType.Margin = new System.Windows.Forms.Padding(4);
      this.cboMapType.Name = "cboMapType";
      this.cboMapType.Size = new System.Drawing.Size(243, 24);
      this.cboMapType.TabIndex = 1;
      // 
      // cbEditableNatureMap
      // 
      this.cbEditableNatureMap.AutoSize = true;
      this.cbEditableNatureMap.Location = new System.Drawing.Point(15, 75);
      this.cbEditableNatureMap.Name = "cbEditableNatureMap";
      this.cbEditableNatureMap.Size = new System.Drawing.Size(157, 21);
      this.cbEditableNatureMap.TabIndex = 2;
      this.cbEditableNatureMap.Text = "Editable nature map";
      this.cbEditableNatureMap.UseVisualStyleBackColor = true;
      // 
      // MapCreationDialog
      // 
      this.AcceptButton = this.btnCreate;
      this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.btnCancel;
      this.ClientSize = new System.Drawing.Size(333, 361);
      this.Controls.Add(this.cbEditableNatureMap);
      this.Controls.Add(this.cboMapType);
      this.Controls.Add(this.lblMapType);
      this.Controls.Add(this.txtName);
      this.Controls.Add(this.lblName);
      this.Controls.Add(this.btnLightEnvironment);
      this.Controls.Add(this.txtLightEnvironment);
      this.Controls.Add(this.label4);
      this.Controls.Add(this.groupBox1);
      this.Controls.Add(this.btnCreate);
      this.Controls.Add(this.btnCancel);
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
      this.Margin = new System.Windows.Forms.Padding(4);
      this.Name = "MapCreationDialog";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
      this.Text = "New map";
      ((System.ComponentModel.ISupportInitialize)(this.numWidth)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.numHeight)).EndInit();
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      ((System.ComponentModel.ISupportInitialize)(this.numResolution)).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.NumericUpDown numWidth;
		private System.Windows.Forms.NumericUpDown numHeight;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Button btnCancel;
		private System.Windows.Forms.Button btnCreate;
    private System.Windows.Forms.GroupBox groupBox1;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.TextBox txtLightEnvironment;
		private System.Windows.Forms.Button btnLightEnvironment;
    private System.Windows.Forms.NumericUpDown numResolution;
    private System.Windows.Forms.Label label5;
    private System.Windows.Forms.Label lblName;
    private System.Windows.Forms.TextBox txtName;
    private System.Windows.Forms.Label lblMapType;
    private System.Windows.Forms.ComboBox cboMapType;
    private System.Windows.Forms.CheckBox cbEditableNatureMap;
	}
}