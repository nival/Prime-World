namespace EditorLib.PropertiesEditor
{
  partial class FastOutlinerColoursForm
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
      this.buttonOk = new System.Windows.Forms.Button();
      this.buttonCancel = new System.Windows.Forms.Button();
      this.listBoxColours = new System.Windows.Forms.ListBox();
      this.buttonAdd = new System.Windows.Forms.Button();
      this.buttonEdit = new System.Windows.Forms.Button();
      this.buttonRemove = new System.Windows.Forms.Button();
      this.buttonUp = new System.Windows.Forms.Button();
      this.buttonDown = new System.Windows.Forms.Button();
      this.colorDialog1 = new System.Windows.Forms.ColorDialog();
      this.SuspendLayout();
      // 
      // buttonOk
      // 
      this.buttonOk.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonOk.DialogResult = System.Windows.Forms.DialogResult.OK;
      this.buttonOk.Location = new System.Drawing.Point( 201, 271 );
      this.buttonOk.Name = "buttonOk";
      this.buttonOk.Size = new System.Drawing.Size( 75, 23 );
      this.buttonOk.TabIndex = 0;
      this.buttonOk.Text = "Ok";
      this.buttonOk.UseVisualStyleBackColor = true;
      this.buttonOk.Click += new System.EventHandler( this.buttonOk_Click );
      // 
      // buttonCancel
      // 
      this.buttonCancel.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
      this.buttonCancel.Location = new System.Drawing.Point( 201, 300 );
      this.buttonCancel.Name = "buttonCancel";
      this.buttonCancel.Size = new System.Drawing.Size( 75, 23 );
      this.buttonCancel.TabIndex = 1;
      this.buttonCancel.Text = "Cancel";
      this.buttonCancel.UseVisualStyleBackColor = true;
      this.buttonCancel.Click += new System.EventHandler( this.buttonCancel_Click );
      // 
      // listBoxColours
      // 
      this.listBoxColours.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( ( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom )
                  | System.Windows.Forms.AnchorStyles.Left )
                  | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.listBoxColours.DrawMode = System.Windows.Forms.DrawMode.OwnerDrawFixed;
      this.listBoxColours.FormattingEnabled = true;
      this.listBoxColours.IntegralHeight = false;
      this.listBoxColours.Location = new System.Drawing.Point( 12, 12 );
      this.listBoxColours.Name = "listBoxColours";
      this.listBoxColours.Size = new System.Drawing.Size( 183, 311 );
      this.listBoxColours.TabIndex = 2;
      this.listBoxColours.DrawItem += new System.Windows.Forms.DrawItemEventHandler( this.listBoxColours_DrawItem );
      this.listBoxColours.SelectedIndexChanged += new System.EventHandler( this.listBoxColours_SelectedIndexChanged );
      this.listBoxColours.DoubleClick += new System.EventHandler( this.listBoxColours_DoubleClick );
      // 
      // buttonAdd
      // 
      this.buttonAdd.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonAdd.Location = new System.Drawing.Point( 201, 12 );
      this.buttonAdd.Name = "buttonAdd";
      this.buttonAdd.Size = new System.Drawing.Size( 75, 23 );
      this.buttonAdd.TabIndex = 3;
      this.buttonAdd.Text = "Add";
      this.buttonAdd.UseVisualStyleBackColor = true;
      this.buttonAdd.Click += new System.EventHandler( this.buttonAdd_Click );
      // 
      // buttonEdit
      // 
      this.buttonEdit.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonEdit.Location = new System.Drawing.Point( 201, 41 );
      this.buttonEdit.Name = "buttonEdit";
      this.buttonEdit.Size = new System.Drawing.Size( 75, 23 );
      this.buttonEdit.TabIndex = 4;
      this.buttonEdit.Text = "Edit";
      this.buttonEdit.UseVisualStyleBackColor = true;
      this.buttonEdit.Click += new System.EventHandler( this.buttonEdit_Click );
      // 
      // buttonRemove
      // 
      this.buttonRemove.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonRemove.Location = new System.Drawing.Point( 201, 70 );
      this.buttonRemove.Name = "buttonRemove";
      this.buttonRemove.Size = new System.Drawing.Size( 75, 23 );
      this.buttonRemove.TabIndex = 5;
      this.buttonRemove.Text = "Remove";
      this.buttonRemove.UseVisualStyleBackColor = true;
      this.buttonRemove.Click += new System.EventHandler( this.buttonRemove_Click );
      // 
      // buttonUp
      // 
      this.buttonUp.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonUp.Location = new System.Drawing.Point( 204, 131 );
      this.buttonUp.Name = "buttonUp";
      this.buttonUp.Size = new System.Drawing.Size( 75, 23 );
      this.buttonUp.TabIndex = 6;
      this.buttonUp.Text = "Up";
      this.buttonUp.UseVisualStyleBackColor = true;
      this.buttonUp.Click += new System.EventHandler( this.buttonUp_Click );
      // 
      // buttonDown
      // 
      this.buttonDown.Anchor = ( (System.Windows.Forms.AnchorStyles)( ( System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right ) ) );
      this.buttonDown.Location = new System.Drawing.Point( 204, 160 );
      this.buttonDown.Name = "buttonDown";
      this.buttonDown.Size = new System.Drawing.Size( 75, 23 );
      this.buttonDown.TabIndex = 7;
      this.buttonDown.Text = "Down";
      this.buttonDown.UseVisualStyleBackColor = true;
      this.buttonDown.Click += new System.EventHandler( this.buttonDown_Click );
      // 
      // colorDialog1
      // 
      this.colorDialog1.AnyColor = true;
      this.colorDialog1.Color = System.Drawing.Color.Transparent;
      this.colorDialog1.FullOpen = true;
      this.colorDialog1.SolidColorOnly = true;
      // 
      // FastOutlinerColoursForm
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF( 6F, 13F );
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.CancelButton = this.buttonCancel;
      this.ClientSize = new System.Drawing.Size( 288, 335 );
      this.Controls.Add( this.buttonDown );
      this.Controls.Add( this.buttonUp );
      this.Controls.Add( this.buttonRemove );
      this.Controls.Add( this.buttonEdit );
      this.Controls.Add( this.buttonAdd );
      this.Controls.Add( this.listBoxColours );
      this.Controls.Add( this.buttonCancel );
      this.Controls.Add( this.buttonOk );
      this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = "FastOutlinerColoursForm";
      this.Text = "Outliner Colors";
      this.ResumeLayout( false );

    }

    #endregion

    private System.Windows.Forms.Button buttonOk;
    private System.Windows.Forms.Button buttonCancel;
    private System.Windows.Forms.ListBox listBoxColours;
    private System.Windows.Forms.Button buttonAdd;
    private System.Windows.Forms.Button buttonEdit;
    private System.Windows.Forms.Button buttonRemove;
    private System.Windows.Forms.Button buttonUp;
    private System.Windows.Forms.Button buttonDown;
    private System.Windows.Forms.ColorDialog colorDialog1;
  }
}