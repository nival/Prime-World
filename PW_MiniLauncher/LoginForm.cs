using Microsoft.Win32;
using System;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.IO;
using System.IO.Compression;
using System.Net.Http;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace PW_MiniLauncher
{  
    public partial class LoginForm : Form
    {
        private string currentGameVersion = "0.2";
        private string currentLauncherVersion = "1.0"; // текущая версия лаунчера

        private const string baseUrlLauncher = "https://playpw.fun/update/launcher/"; // URL for all files of launcher
        private const string baseUrlGame = "https://playpw.fun/update/client/"; // URL for all files of game
        private string endFileName = ".zip"; // file with new launcher
        private string newLauncherFile;
        private const string launcherVersionFile = "check"; // version launcher file
        private string newGameFile;
        private const string gameVersionFile = "check"; // game version file
        private string gameDirectory; // The game directory
        private const string launcherPath = "PW_MiniLauncher.exe"; // launcher name
        private bool status = false;
        private string web_token;
        private string copyDefaultName;
        
        public LoginForm(string defaultName)
        {
            InitializeComponent();
            copyDefaultName = defaultName;
            this.Load += async (s, e) => await CheckVersionAndLaunch();

            string[] args = defaultName.Split('/');

         foreach (Control control in this.Controls) {
                if (control is Button button)
                {
                    button.FlatStyle = FlatStyle.Flat;
                    button.FlatAppearance.BorderSize = 0;
                }
            }

            MakeButtonCircular(button1, button2, button3, button4);
            playButton.Enabled = true;
            grayButton.Visible = false;

            if (status) {
                playButton.Enabled = true;
            }
            button5.Visible = !(args.Length > 2);

         if (args.Length > 2)
         {
            web_token = args[2];
            playButton.Click += (s, e) => Play();
         }

      }

        private async Task CheckVersionAndLaunch()
        {
            try
            {
                
                var serverVersion = await GetVersionFromServer(baseUrlLauncher + launcherVersionFile);
                newLauncherFile = EditArchive(serverVersion);
                var launcherPath = GetLauncherDirectory();
                var newLauncherPath = Path.Combine(launcherPath, "PW_MiniLauncher.exe");

                if ((serverVersion != currentLauncherVersion) && System.IO.File.Exists(newLauncherPath))
                {
                    playButton.Enabled = false;
                    await DownloadAndUpdateLauncher();
                }
                

                await CheckGameVersionUpdate();
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Ошибка при проверке версии: {ex.Message}", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        // change archive name
        private string EditArchive(string versionFile)
        {
            return newLauncherFile = versionFile + endFileName;
        }

        private async Task DownloadAndUpdateLauncher()
        {
            label2.Visible = true;
            label2.Text = "Обновление лаунчера...";
            progressBar.Visible = true;

            var launcherDirectory = GetLauncherDirectory();
            var tempFilePath = Path.Combine(launcherDirectory, newLauncherFile);

            using (var httpClient = new HttpClient())
            {
                var response = await httpClient.GetAsync(baseUrlLauncher + newLauncherFile, HttpCompletionOption.ResponseHeadersRead);
                response.EnsureSuccessStatusCode();

                var totalBytes = response.Content.Headers.ContentLength ?? -1L;
                long totalReadBytes = 0;


                using (var fs = new FileStream(tempFilePath, FileMode.Create, FileAccess.Write, FileShare.None))
                using (var contentStream = await response.Content.ReadAsStreamAsync()) 
                {
                    var buffer = new byte[4096];
                    int readBytes;
                    while ((readBytes = await contentStream.ReadAsync(buffer, 0, buffer.Length)) > 0)
                    {
                        await fs.WriteAsync(buffer, 0, readBytes);
                        totalReadBytes += readBytes;

                        if (totalBytes > 0)
                        {
                            int progressPercentage = (int)((totalReadBytes * 100) / totalBytes);
                            UpdateProgressBar(progressPercentage);
                        }
                    }
                }
            }

            UpdateFiles(launcherDirectory, tempFilePath);

            string updateScriptPath = Path.Combine(launcherDirectory, "UpdateLauncher.cmd");
  
            if (File.Exists(updateScriptPath))
            {
                ProcessStartInfo startInfo = new ProcessStartInfo
                {
                    FileName = updateScriptPath,
                    Arguments = copyDefaultName,
                    UseShellExecute = true,
                    WorkingDirectory = launcherDirectory,
                };
                
                Process.Start(startInfo);
            }
            else
            {
                Console.WriteLine("Файл UpdateLauncher.cmd не найден");
            }

            label2.Visible = false;
            progressBar.Visible = false;
        }

        private async Task<string> GetVersionFromServer(string versionFile)
        {
            using (var httpClient = new HttpClient())
            {
                try
                {
                    var response = await httpClient.GetAsync(versionFile);
                    response.EnsureSuccessStatusCode();

                    var content = await response.Content.ReadAsStringAsync();
                    Console.WriteLine(content);
                    return await response.Content.ReadAsStringAsync();
                    
                }
                catch (HttpRequestException ex)
                {
                    MessageBox.Show($"Ошибка при получении версии: {ex.Message}", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    throw; 
                }
                catch (Exception ex)
                {
                    MessageBox.Show($"Произошла ошибка: {ex.Message}", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    throw;  
                }
            }
        }



        private async Task CheckGameVersionUpdate()
        {
            
            var serverGameVersion = await GetVersionFromServer(baseUrlGame + gameVersionFile);
            gameDirectory = GetGameInstallationDirectory(); // Get game installation directory

            newGameFile = EditArchive(serverGameVersion);

            if (serverGameVersion != currentGameVersion)
            {
                playButton.Enabled = false;
                grayButton.Visible = false;
                status = false;
                await DownloadAndUpdateGame();
            }
            else
            {
                playButton.Enabled = true;
                status = true;
                playButton.PerformClick();
            }        
        }

        private async Task DownloadAndUpdateGame()
        {
            label2.Visible = true;
            label2.Text = "Обновление игры...";
            progressBar.Visible = true;

            var gameDirectory = GetGameInstallationDirectory();
            var tempGameFilePath = Path.Combine(gameDirectory, newGameFile);

            using (var httpClient = new HttpClient())
            {
                var response = await httpClient.GetAsync(baseUrlGame + newGameFile, HttpCompletionOption.ResponseHeadersRead);
                response.EnsureSuccessStatusCode();

                var totalBytes = response.Content.Headers.ContentLength ?? -1L;
                long totalReadBytes = 0;

                using (var fs = new FileStream(tempGameFilePath, FileMode.Create, FileAccess.Write, FileShare.None))
                using (var contentStream = await response.Content.ReadAsStreamAsync())
                {
                    var buffer = new byte[4096];
                    int readBytes;
                    while ((readBytes = await contentStream.ReadAsync(buffer, 0, buffer.Length)) > 0)
                    {
                        await fs.WriteAsync(buffer, 0, readBytes);
                        totalReadBytes += readBytes;

                        if (totalBytes > 0)
                        {
                            int progressPercentage = (int)((totalReadBytes * 100) / totalBytes);
                            UpdateProgressBar(progressPercentage);
                        }
                    } 
                }
            }

            UpdateFiles(gameDirectory, tempGameFilePath);
            progressBar.Visible = false;
            label2.Visible = false;
            status = true;
            
        }

        private void UpdateFiles(string targetDirectory, string zipPath)
        {
            var tempDir = Path.Combine(Path.GetTempPath(), "tempUpdate");

            try
            {
                Directory.CreateDirectory(tempDir);
                ZipFile.ExtractToDirectory(zipPath, tempDir);

                foreach (var file in Directory.GetFiles(tempDir, "*.*", SearchOption.AllDirectories))
                {
                    var relativePath = GetRelativePath(tempDir, file);
                    var destinationPath = Path.Combine(targetDirectory, relativePath);

                    Directory.CreateDirectory(Path.GetDirectoryName(destinationPath));

                    if (!File.Exists(destinationPath) || File.GetLastWriteTime(file) > File.GetLastWriteTime(destinationPath))
                    {
                        File.Move(file, destinationPath);
                        Console.WriteLine($"Файл скопирован: {relativePath}");
                    }
                }
            }
            catch (Exception ex)
            {
                Console.Error.WriteLine($"Ошибка при обновлении файлов: {ex.Message}");
            }
            finally
            {
                if (Directory.Exists(tempDir))
                {
                    try
                    {
                        Directory.Delete(tempDir, true);
                        Console.WriteLine("Временная директория удалена.");
                    }
                    catch (Exception ex)
                    {
                        Console.Error.WriteLine($"Ошибка при удалении временной директории: {ex.Message}");
                    }
                }
            }
        }

        private void OnInputKeyDown(object sender, KeyEventArgs e)
        {
            OnButtonDown(e);
        }

        protected override void OnKeyDown(KeyEventArgs e)
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

        public static void LaunchGame(string name, bool spectate)
        {
            Debug.Print("Launch PW with Login = " + name);

            string fullPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "PW_Game.exe");

            if (!File.Exists(fullPath))
            {
                MessageBox.Show("Положите лаунчер рядом с файлом PW_Game.exe", "Файл не найден", MessageBoxButtons.OK);
                return;
            }
            ProcessStartInfo startInfo = new ProcessStartInfo
            {
                FileName = fullPath,
                Arguments = "web_token " + name,
                UseShellExecute = false,
                WorkingDirectory = AppDomain.CurrentDomain.BaseDirectory,
            };
            Process.Start(startInfo);
        }

        private void Play()
        {           
                if (!status)
                {
                    return;
                }
            grayButton.Visible = false;
         System.Threading.Thread.Sleep(1000);
         LaunchGame(web_token, false);
            Close();
        }

        private string GetGameInstallationDirectory()
        {
            string installDir = string.Empty;

            // Checking the registry
            using (var key = Registry.LocalMachine.OpenSubKey(@"SOFTWARE\WOW6432Node\PW_Game"))
            {
                if (key != null)
                    installDir = key.GetValue("InstallLocation") as string;
            }

            // Verification of existence PW_Game.exe
            if (!string.IsNullOrWhiteSpace(installDir) && File.Exists(Path.Combine(installDir, "PW_Game.exe")))
            {
                return installDir;
            }

            return string.Empty;
        }

        private string GetLauncherDirectory()
        {
            return AppDomain.CurrentDomain.BaseDirectory; // Returns the launcher directory
        }

        private static string GetRelativePath(string basePath, string fullPath)
        {
            var baseUri = new Uri(basePath);
            var fullUri = new Uri(fullPath);
            Uri relativeUri = baseUri.MakeRelativeUri(fullUri);
            return Uri.UnescapeDataString(relativeUri.ToString().Replace('/', Path.DirectorySeparatorChar));
        }

        private void LoginForm_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void UpdateProgressBar(int value)
        {
            if (InvokeRequired)
            {
                Invoke((MethodInvoker)delegate {  progressBar.Value = value; });
            }
            else
            {
                progressBar.Value = value;
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            Process.Start(new ProcessStartInfo("https://playpw.fun") { UseShellExecute = true });
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Process.Start(new ProcessStartInfo("https://discord.gg/bCS3Hfm2s3") { UseShellExecute = true });
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Process.Start(new ProcessStartInfo("https://vk.com/primeworldclassic") { UseShellExecute = true });
        }

        private void MakeButtonCircular(params Button[] buttons)
        {
            foreach (Button button in buttons)
            {
                using (GraphicsPath path = new GraphicsPath())
                {
                    path.AddEllipse(0, 0, button.Width, button.Height);
                    button.Region = new Region(path);
                }
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Process.Start(new ProcessStartInfo("https://t.me/primeworldclassic") { UseShellExecute = true });
        }

        private void closeButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

      private void button5_Click(object sender, EventArgs e)
      {
         Process.Start(new ProcessStartInfo("https://playpw.fun") { UseShellExecute = true });
      }
   }
}
