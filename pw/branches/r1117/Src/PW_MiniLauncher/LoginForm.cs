using System.Diagnostics;
using System.IO;
using System.Windows.Forms;

namespace PW_MiniLauncher
{
  public partial class LoginForm : Form
  {
    public LoginForm( string defaultName )
    {
      InitializeComponent();

      playButton.Click += ( s, e ) => Play();
      playButton.Enabled = false;

      specButton.Click += ( s, e ) => Spectate();
      specButton.Enabled = false;

      input.TextChanged += ( s, e ) =>
                           {
                             playButton.Enabled = !string.IsNullOrEmpty( input.Text );
                             specButton.Enabled = !string.IsNullOrEmpty( input.Text );
                           };

      input.Text = defaultName;
      input.KeyDown += OnInputKeyDown;
    }

    private void OnInputKeyDown(object sender, KeyEventArgs e)
    {
      OnButtonDown(e);
    }

    protected override void OnKeyDown( KeyEventArgs e )
    {
      base.OnKeyDown(e);

      OnButtonDown(e);
    }

    private void OnButtonDown(KeyEventArgs e)
    {
      if (e.KeyCode == Keys.Enter)
      {
        Play();
      }
    }

    public static void LaunchGame(string name, bool spectate )
    {
      Debug.Print("Launch PW with Login = " + name);

      string fullPath = Application.StartupPath + "\\PW_Game.exe";

      if (!File.Exists(fullPath))
      {
        MessageBox.Show("Положите Laucher рядом с файлом PW_Game.exe", "Файл не найден", MessageBoxButtons.OK);
        return;
      }

      string cmd = "";
      if (spectate)
        cmd += "spectator ";

      Process.Start(fullPath, cmd + "-dev_login " + name);
    }

    private void Play( )
    {
      if (string.IsNullOrEmpty(input.Text) )
        return;

      LaunchGame(input.Text, false);
      Close();
    }

    private void Spectate()
    {
      if ( string.IsNullOrEmpty( input.Text ) )
        return;

      LaunchGame(input.Text, true);
      Close();
    }
  }
}
