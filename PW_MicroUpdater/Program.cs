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
        const string binariesPath = "_ShippingSingleExe";

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
            string destinationFolder = AppDomain.CurrentDomain.BaseDirectory;

            using (ZipFile zip = ZipFile.Read(zipFilePath))
            {
                foreach (ZipEntry entry in zip)
                {
                    entry.Extract(destinationFolder, ExtractExistingFileAction.OverwriteSilently);
                }
            }

            return true;
        }

        static bool LaunchPWGame(string args)
        {
            string fullPath = Path.Combine(AppDomain.CurrentDomain.BaseDirectory, binariesPath + "/PW_Game.exe");

            if (!File.Exists(fullPath))
            {
                return false;
            }

            ProcessStartInfo startInfo = new ProcessStartInfo
            {
                FileName = fullPath,
                Arguments = args,
                UseShellExecute = true,
                WorkingDirectory = AppDomain.CurrentDomain.BaseDirectory,
            };
            Process.Start(startInfo);

            return true;
        }

        static void WaitWhilePWGameIsRunning()
        {
            Thread.Sleep(1000);
            //PROCESSENTRY32 pe32 = new PROCESSENTRY32();
            //pe32.dwSize = (uint)Marshal.SizeOf(typeof(PROCESSENTRY32));

            //IntPtr hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

            //if (hProcessSnap == IntPtr.Zero)
            //{
            //    Console.WriteLine("CreateToolhelp32Snapshot failed.");
            //    return;
            //}

            //if (Process32First(hProcessSnap, ref pe32))
            //{
            //    do
            //    {
            //       // string processName = Encoding.Default.GetString(pe32.szExeFile).Trim('\0');
                    
            //       // Console.WriteLine("Process Name: " + pe32.szExeFile);
            //        Console.WriteLine("Process ID: " + pe32.th32ProcessID);
                    

            //        // Check if the process you are looking for is running
            //        //if (pe32.szExeFile.Equals("process_name.exe", StringComparison.OrdinalIgnoreCase))
            //        //{
            //        //    Console.WriteLine("Process is running.");
            //        //    break;
            //        //}

            //    } while (Process32Next(hProcessSnap, ref pe32));
            //}

            //if (hProcessSnap != IntPtr.Zero)
            //{
            //    // Close the handle
            //    Marshal.FreeHGlobal(hProcessSnap);
            //}
        }

        static void Main(string[] args)
        {
            string clientVer = GetVersion();

            bool isOK = true;

            string updateFileName = clientVer + ".zip";

            isOK &= DownloadUpdate(updateFileName);
            isOK &= UnpackUpdate(updateFileName);

            WaitWhilePWGameIsRunning();

            isOK &= LaunchPWGame(args[0]); ;

            if (!isOK)
            {
                MessageBox.Show("Update Failed! Please reinstall game!");
            }
        }
    }
}
