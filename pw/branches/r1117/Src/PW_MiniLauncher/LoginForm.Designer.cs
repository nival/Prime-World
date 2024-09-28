namespace PW_MiniLauncher
{
  partial class LoginForm
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
      this.playButton = new System.Windows.Forms.Button();
      this.input = new System.Windows.Forms.TextBox();
      this.label1 = new System.Windows.Forms.Label();
      this.specButton = new System.Windows.Forms.Button();
      this.SuspendLayout();
      // 
      // playButton
      // 
      this.playButton.Location = new System.Drawing.Point( 258, 12 );
      this.playButton.Name = "playButton";
      this.playButton.Size = new System.Drawing.Size( 54, 24 );
      this.playButton.TabIndex = 0;
      this.playButton.Text = "Играть!";
      this.playButton.UseVisualStyleBackColor = true;
      // 
      // input
      // 
      this.input.Location = new System.Drawing.Point( 54, 15 );
      this.input.Name = "input";
      this.input.Size = new System.Drawing.Size( 198, 20 );
      this.input.TabIndex = 1;
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point( 12, 18 );
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size( 36, 13 );
      this.label1.TabIndex = 2;
      this.label1.Text = "Login:";
      // 
      // specButton
      // 
      this.specButton.Location = new System.Drawing.Point( 318, 12 );
      this.specButton.Name = "specButton";
      this.specButton.Size = new System.Drawing.Size( 68, 24 );
      this.specButton.TabIndex = 3;
      this.specButton.Text = "Смотреть!";
      this.specButton.UseVisualStyleBackColor = true;
      // 
      // LoginForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 392, 50 );
      this.Controls.Add( this.specButton );
      this.Controls.Add( this.label1 );
      this.Controls.Add( this.input );
      this.Controls.Add( this.playButton );
      this.Cursor = System.Windows.Forms.Cursors.Arrow;
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
      this.Name = "LoginForm";
      this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
      this.Text = "PW_Launcher";
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button playButton;
    private System.Windows.Forms.TextBox input;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Button specButton;
  }
}

