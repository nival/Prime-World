using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Net;
using System.Runtime.InteropServices;
using System.Data;
using Ionic.Zip;
using System.Diagnostics;
using System.Windows.Forms;
using System.Threading;

namespace PW_MicroUpdater
{
    
    class Program
    {
        const string serverURL = "https://rekongstor.github.io/update/client/";
        const string binariesPath = "Bin";

        [DllImport("wininet.dll", SetLastError = true)]
        public static extern IntPtr InternetOpen(string lpszAgent, int dwAccessType, string lpszProxyName, string lpszProxyBypass, int dwFlags);

        [DllImport("wininet.dll", SetLastError = true)]
        public static extern IntPtr InternetOpenUrl(IntPtr hInternet, string lpszUrl, string lpszHeaders, int dwHeadersLength, int dwFlags, int dwContext);

        [DllImport("wininet.dll", SetLastError = true)]
        public static extern bool InternetReadFile(IntPtr hFile, byte[] lpBuffer, int dwNumberOfBytesToRead, out int lpdwNumberOfBytesRead);

        [DllImport("wininet.dll", SetLastError = true)]
        public static extern bool InternetCloseHandle(IntPtr hInternet);

        [DllImport("shell32.dll", CharSet = CharSet.Unicode)]
        public static extern int SHFileOperation(ref SHFILEOPSTRUCT FileOp);

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        public struct SHFILEOPSTRUCT
        {
            public IntPtr hwnd;
            public uint wFunc;
            public string pFrom;
            public string pTo;
            public ushort fFlags;
            public int fAnyOperationsAborted;
            public IntPtr hNameMappings;
            public string lpszProgressTitle;
        }

        [DllImport("Lz32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr LZOpenFile(string lpFileName, ref OFSTRUCT lpReOpenBuf, uint wStyle);

        [DllImport("Lz32.dll", CharSet = CharSet.Auto)]
        public static extern int LZRead(IntPtr hFile, byte[] lpBuffer, int cbRead);

        [DllImport("Lz32.dll", CharSet = CharSet.Auto)]
        public static extern int LZClose(IntPtr hFile);

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct OFSTRUCT
        {
            public byte cBytes;
            public byte fFixedDisk;
            public ushort nErrCode;
            public ushort Reserved1;
            public ushort Reserved2;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 128)]
            public string szPathName;
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        public struct PROCESSENTRY32
        {
            public uint dwSize;
            public uint cntUsage;
            public uint th32ProcessID;
            public IntPtr th32DefaultHeapID;
            public uint th32ModuleID;
            public uint cntThreads;
            public uint th32ParentProcessID;
            public int pcPriClassBase;
            public uint dwFlags;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
            public char[] szExeFile;
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern IntPtr CreateToolhelp32Snapshot(uint dwFlags, uint th32ProcessID);

        [DllImport("kernel32.dll")]
        public static extern bool Process32First(IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

        [DllImport("kernel32.dll")]
        public static extern bool Process32Next(IntPtr hSnapshot, ref PROCESSENTRY32 lppe);

        public const uint TH32CS_SNAPPROCESS = 0x00000002;
        //" red +5 orange +7 fiol +9 sin +10"
        static string GetVersion()
        {
            string url = serverURL + "/check";
            StringBuilder sb = new StringBuilder();

            IntPtr hInternet = InternetOpen("PWClassic", 0, null, null, 0);
            if (hInternet != IntPtr.Zero)
            {
                IntPtr hUrl = InternetOpenUrl(hInternet, url, null, 0, 0, 0);
                if (hUrl != IntPtr.Zero)
                {
                    byte[] buffer = new byte[4096];
                    int bytesRead;
                    
                    while (InternetReadFile(hUrl, buffer, buffer.Length, out bytesRead) && bytesRead > 0)
                    {
                        sb.Append(Encoding.UTF8.GetString(buffer, 0, bytesRead));
                    }

                    InternetCloseHandle(hUrl);
                }

                InternetCloseHandle(hInternet);
            }

            return sb.ToString();
        }

        static bool DownloadUpdate(string filename)
        {
            string url = serverURL + "/" + filename;
            StringBuilder sb = new StringBuilder();

            IntPtr hInternet = InternetOpen("PWClassic", 0, null, null, 0);
            if (hInternet != IntPtr.Zero)
            {
                IntPtr hUrl = InternetOpenUrl(hInternet, url, null, 0, 0, 0);
                if (hUrl != IntPtr.Zero)
                {
                    byte[] buffer = new byte[4096];
                    int bytesRead;

                    using (FileStream fs = new FileStream(filename, FileMode.Create))
                    {
                        while (InternetReadFile(hUrl, buffer, buffer.Length, out bytesRead) && bytesRead > 0)
                        {
                            fs.Write(buffer, 0, bytesRead);
                        }
                    }

                    InternetCloseHandle(hUrl);
                }

                InternetCloseHandle(hInternet);
            }

            return true;
        }

        static bool UnpackUpdate(string filename)
        {

         string zipFilePath = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, filename);
         string fullPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "7za.exe");

         if (!File.Exists(fullPath))
         {
            return false;
         }

         ProcessStartInfo startInfo = new ProcessStartInfo
         {
            FileName = fullPath,
            Arguments = "x -y " + filename,
            UseShellExecute = false,
            WorkingDirectory = AppDomain.CurrentDomain.BaseDirectory,
         };
         var process = Process.Start(startInfo);
         process.WaitForExit();
         System.IO.File.Delete(zipFilePath);
         return true;
      }

        static bool LaunchPWGame(string args)
        {
            string fullPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, binariesPath + "\\LaunchGame.bat");

            if (!File.Exists(fullPath))
            {
                return false;
            }

         ProcessStartInfo startInfo = new ProcessStartInfo
         {
            FileName = fullPath,
            Arguments = args,
            UseShellExecute = true,
            WorkingDirectory = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, binariesPath)
            };
            Process.Start(startInfo);

            return true;
        }

      static bool IsProcessRunning(string processName)
      {
         // Получаем все процессы с именем processName
         var processes = Process.GetProcessesByName(processName);

         // Проверяем, если ли такие процессы
         return processes.Length > 0;
      }

      static void WaitWhilePWGameIsRunning()
        {
         while (IsProcessRunning("PW_Game.exe"))
         {
            var processes = Process.GetProcessesByName("PW_Game.exe");
            processes[0].Kill();
         }
      }

        static void Main(string[] args)
        {
            string clientVer = GetVersion();

            bool isOK = true;

            string updateFileName = clientVer + ".zip";

            isOK &= DownloadUpdate(updateFileName);
            WaitWhilePWGameIsRunning();

            isOK &= UnpackUpdate(updateFileName);

            isOK &= LaunchPWGame(args[0]); ;

            if (!isOK)
            {
                MessageBox.Show("Update Failed! Please reinstall game!");
            }
        }
    }
}
