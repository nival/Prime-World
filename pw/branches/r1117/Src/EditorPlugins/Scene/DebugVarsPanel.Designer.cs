namespace EditorPlugins.Scene
{
  partial class DebugVarsPanel
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

    #region Component Designer generated code

    /// <summary> 
    /// Required method for Designer support - do not modify 
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.components = new System.ComponentModel.Container();
      this.debugVarsList = new EditorPlugins.Scene.DoubleBufferedListBox();
      this.configureLinkLabel = new System.Windows.Forms.LinkLabel();
      this.refreshTimer = new System.Windows.Forms.Timer( this.components );
      this.SuspendLayout();
      // 
      // debugVarsList
      // 
      this.debugVarsList.Dock = System.Windows.Forms.DockStyle.Fill;
      this.debugVarsList.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
      this.debugVarsList.FormattingEnabled = true;
      this.debugVarsList.IntegralHeight = false;
      this.debugVarsList.Location = new System.Drawing.Point( 0, 0 );
      this.debugVarsList.Name = "debugVarsList";
      this.debugVarsList.Size = new System.Drawing.Size( 290, 327 );
      this.debugVarsList.TabIndex = 0;
      this.debugVarsList.DrawItem += new System.Windows.Forms.DrawItemEventHandler( this.OnDebugVarsListDrawItem );
      // 
      // configureLinkLabel
      // 
      this.configureLinkLabel.AutoSize = true;
      this.configureLinkLabel.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.configureLinkLabel.Location = new System.Drawing.Point( 0, 327 );
      this.configureLinkLabel.Name = "configureLinkLabel";
      this.configureLinkLabel.Size = new System.Drawing.Size( 61, 13 );
      this.configureLinkLabel.TabIndex = 1;
      this.configureLinkLabel.TabStop = true;
      this.configureLinkLabel.Text = "Configure...";
      this.configureLinkLabel.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler( this.OnConfigureLinkLabelClicked );
      // 
      // refreshTimer
      // 
      this.refreshTimer.Enabled = true;
      this.refreshTimer.Interval = 50;
      this.refreshTimer.Tick += new System.EventHandler( this.OnRefreshTimerTick );
      // 
      // DebugVarsPanel
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size( 290, 340 );
      this.Controls.Add( this.debugVarsList );
      this.Controls.Add( this.configureLinkLabel );
      this.Font = new System.Drawing.Font( "Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ( (byte)( 204 ) ) );
      this.Name = "DebugVarsPanel";
      this.TabText = "Debug Variables";
      this.Text = "Debug Variables";
      this.ResumeLayout( false );
      this.PerformLayout();

    }

    #endregion

    private DoubleBufferedListBox debugVarsList;
    private System.Windows.Forms.LinkLabel configureLinkLabel;
    private System.Windows.Forms.Timer refreshTimer;
  }
}
