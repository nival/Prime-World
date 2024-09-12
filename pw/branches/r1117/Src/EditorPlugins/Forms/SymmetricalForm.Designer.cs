namespace EditorPlugins.Forms
{
  partial class SymmetricalForm
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
      this.checkBox1 = new System.Windows.Forms.CheckBox();
      this.button1 = new System.Windows.Forms.Button();
      this.checkedListBox1 = new System.Windows.Forms.CheckedListBox();
      this.checkBox2 = new System.Windows.Forms.CheckBox();
      this.checkBox3 = new System.Windows.Forms.CheckBox();
      this.checkBox4 = new System.Windows.Forms.CheckBox();
      this.comboBox1 = new System.Windows.Forms.ComboBox();
      this.SuspendLayout();
      // 
      // checkBox1
      // 
      this.checkBox1.AutoSize = true;
      this.checkBox1.Location = new System.Drawing.Point( 6, 411 );
      this.checkBox1.Name = "checkBox1";
      this.checkBox1.Size = new System.Drawing.Size( 70, 17 );
      this.checkBox1.TabIndex = 0;
      this.checkBox1.Text = "Check all";
      this.checkBox1.UseVisualStyleBackColor = true;
      this.checkBox1.CheckedChanged += new System.EventHandler( this.checkBox1_CheckedChanged );
      // 
      // button1
      // 
      this.button1.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.button1.Location = new System.Drawing.Point( 181, 406 );
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size( 44, 25 );
      this.button1.TabIndex = 1;
      this.button1.Text = "Run";
      this.button1.UseVisualStyleBackColor = true;
      // 
      // checkedListBox1
      // 
      this.checkedListBox1.FormattingEnabled = true;
      this.checkedListBox1.Location = new System.Drawing.Point( 6, 81 );
      this.checkedListBox1.Name = "checkedListBox1";
      this.checkedListBox1.Size = new System.Drawing.Size( 219, 319 );
      this.checkedListBox1.TabIndex = 2;
      // 
      // checkBox2
      // 
      this.checkBox2.AutoSize = true;
      this.checkBox2.Location = new System.Drawing.Point( 6, 35 );
      this.checkBox2.Name = "checkBox2";
      this.checkBox2.Size = new System.Drawing.Size( 81, 17 );
      this.checkBox2.TabIndex = 3;
      this.checkBox2.Text = "Point Lights";
      this.checkBox2.UseVisualStyleBackColor = true;
      // 
      // checkBox3
      // 
      this.checkBox3.AutoSize = true;
      this.checkBox3.Location = new System.Drawing.Point( 6, 12 );
      this.checkBox3.Name = "checkBox3";
      this.checkBox3.Size = new System.Drawing.Size( 105, 17 );
      this.checkBox3.TabIndex = 4;
      this.checkBox3.Text = "Terrain Elements";
      this.checkBox3.UseVisualStyleBackColor = true;
      // 
      // checkBox4
      // 
      this.checkBox4.AutoSize = true;
      this.checkBox4.Location = new System.Drawing.Point( 6, 58 );
      this.checkBox4.Name = "checkBox4";
      this.checkBox4.Size = new System.Drawing.Size( 83, 17 );
      this.checkBox4.TabIndex = 5;
      this.checkBox4.Text = "Script Areas";
      this.checkBox4.UseVisualStyleBackColor = true;
      // 
      // comboBox1
      // 
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Items.AddRange( new object[] {
            "Left to Right",
            "Right to Left"} );
      this.comboBox1.Location = new System.Drawing.Point( 82, 407 );
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new System.Drawing.Size( 93, 21 );
      this.comboBox1.TabIndex = 6;
      // 
      // SymmetricalForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 230, 440 );
      this.Controls.Add( this.comboBox1 );
      this.Controls.Add( this.checkBox4 );
      this.Controls.Add( this.checkBox3 );
      this.Controls.Add( this.checkBox2 );
      this.Controls.Add( this.checkedListBox1 );
      this.Controls.Add( this.button1 );
      this.Controls.Add( this.checkBox1 );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
      this.Name = "SymmetricalForm";
      this.Text = "Symmetrical Script";
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.CheckBox checkBox1;
    private System.Windows.Forms.Button button1;
    private System.Windows.Forms.CheckedListBox checkedListBox1;
    private System.Windows.Forms.CheckBox checkBox2;
    private System.Windows.Forms.CheckBox checkBox3;
    private System.Windows.Forms.CheckBox checkBox4;
    private System.Windows.Forms.ComboBox comboBox1;
  }
}