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
         System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(LoginForm));
         this.playButton = new System.Windows.Forms.Button();
         this.progressBar = new System.Windows.Forms.ProgressBar();
         this.label2 = new System.Windows.Forms.Label();
         this.button1 = new System.Windows.Forms.Button();
         this.button2 = new System.Windows.Forms.Button();
         this.button3 = new System.Windows.Forms.Button();
         this.grayButton = new System.Windows.Forms.Button();
         this.button4 = new System.Windows.Forms.Button();
         this.closeButton = new System.Windows.Forms.Button();
         this.button5 = new System.Windows.Forms.Button();
         this.SuspendLayout();
         // 
         // playButton
         // 
         this.playButton.BackColor = System.Drawing.SystemColors.ButtonHighlight;
         this.playButton.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("playButton.BackgroundImage")));
         this.playButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Bold);
         this.playButton.ForeColor = System.Drawing.Color.AliceBlue;
         this.playButton.Location = new System.Drawing.Point(0, 0);
         this.playButton.Name = "playButton";
         this.playButton.Size = new System.Drawing.Size(0, 0);
         this.playButton.TabIndex = 0;
         this.playButton.Text = "Играть!";
         this.playButton.UseVisualStyleBackColor = false;
         // 
         // progressBar
         // 
         this.progressBar.BackColor = System.Drawing.SystemColors.AppWorkspace;
         this.progressBar.ForeColor = System.Drawing.Color.Cyan;
         this.progressBar.Location = new System.Drawing.Point(167, 357);
         this.progressBar.Name = "progressBar";
         this.progressBar.Size = new System.Drawing.Size(509, 28);
         this.progressBar.TabIndex = 4;
         this.progressBar.Visible = false;
         // 
         // label2
         // 
         this.label2.AutoSize = true;
         this.label2.BackColor = System.Drawing.Color.Transparent;
         this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
         this.label2.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
         this.label2.Location = new System.Drawing.Point(163, 324);
         this.label2.Name = "label2";
         this.label2.Size = new System.Drawing.Size(0, 20);
         this.label2.TabIndex = 5;
         this.label2.Visible = false;
         // 
         // button1
         // 
         this.button1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("button1.BackgroundImage")));
         this.button1.Location = new System.Drawing.Point(772, 249);
         this.button1.Name = "button1";
         this.button1.Size = new System.Drawing.Size(60, 60);
         this.button1.TabIndex = 6;
         this.button1.UseVisualStyleBackColor = true;
         this.button1.Click += new System.EventHandler(this.button1_Click);
         // 
         // button2
         // 
         this.button2.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("button2.BackgroundImage")));
         this.button2.Location = new System.Drawing.Point(772, 183);
         this.button2.Name = "button2";
         this.button2.Size = new System.Drawing.Size(60, 60);
         this.button2.TabIndex = 7;
         this.button2.UseVisualStyleBackColor = true;
         this.button2.Click += new System.EventHandler(this.button2_Click);
         // 
         // button3
         // 
         this.button3.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("button3.BackgroundImage")));
         this.button3.Location = new System.Drawing.Point(772, 117);
         this.button3.Name = "button3";
         this.button3.Size = new System.Drawing.Size(60, 60);
         this.button3.TabIndex = 8;
         this.button3.UseVisualStyleBackColor = true;
         this.button3.Click += new System.EventHandler(this.button3_Click);
         // 
         // grayButton
         // 
         this.grayButton.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("grayButton.BackgroundImage")));
         this.grayButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 20F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(250)));
         this.grayButton.ForeColor = System.Drawing.SystemColors.ControlText;
         this.grayButton.Location = new System.Drawing.Point(696, 300);
         this.grayButton.Name = "grayButton";
         this.grayButton.Size = new System.Drawing.Size(0, 0);
         this.grayButton.TabIndex = 9;
         this.grayButton.Text = "Играть!";
         this.grayButton.UseVisualStyleBackColor = true;
         // 
         // button4
         // 
         this.button4.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("button4.BackgroundImage")));
         this.button4.Location = new System.Drawing.Point(772, 51);
         this.button4.Name = "button4";
         this.button4.Size = new System.Drawing.Size(60, 60);
         this.button4.TabIndex = 10;
         this.button4.UseVisualStyleBackColor = true;
         this.button4.Click += new System.EventHandler(this.button4_Click);
         // 
         // closeButton
         // 
         this.closeButton.BackColor = System.Drawing.Color.Transparent;
         this.closeButton.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("closeButton.BackgroundImage")));
         this.closeButton.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
         this.closeButton.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Transparent;
         this.closeButton.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
         this.closeButton.ForeColor = System.Drawing.Color.Transparent;
         this.closeButton.Location = new System.Drawing.Point(788, 1);
         this.closeButton.Name = "closeButton";
         this.closeButton.Size = new System.Drawing.Size(44, 44);
         this.closeButton.TabIndex = 12;
         this.closeButton.UseVisualStyleBackColor = false;
         this.closeButton.Click += new System.EventHandler(this.closeButton_Click);
         // 
         // button5
         // 
         this.button5.Font = new System.Drawing.Font("Microsoft Sans Serif", 14F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
         this.button5.Location = new System.Drawing.Point(696, 300);
         this.button5.Name = "button5";
         this.button5.Size = new System.Drawing.Size(0, 0);
         this.button5.TabIndex = 11;
         this.button5.Text = "Запустите лаунчер через сайт!";
         this.button5.UseVisualStyleBackColor = true;
         this.button5.Click += new System.EventHandler(this.button5_Click);
         // 
         // LoginForm
         // 
         this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
         this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
         this.BackColor = System.Drawing.SystemColors.ControlDarkDark;
         this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
         this.ClientSize = new System.Drawing.Size(844, 421);
         this.Controls.Add(this.closeButton);
         this.Controls.Add(this.button5);
         this.Controls.Add(this.button4);
         this.Controls.Add(this.grayButton);
         this.Controls.Add(this.button3);
         this.Controls.Add(this.button2);
         this.Controls.Add(this.button1);
         this.Controls.Add(this.label2);
         this.Controls.Add(this.progressBar);
         this.Controls.Add(this.playButton);
         this.Cursor = System.Windows.Forms.Cursors.Arrow;
         this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
         this.Name = "LoginForm";
         this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
         this.Text = "PW_Launcher";
         this.Load += new System.EventHandler(this.LoginForm_Load);
         this.ResumeLayout(false);
         this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.Button playButton;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button grayButton;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button closeButton;
        private System.Windows.Forms.Button button5;
    }
}

