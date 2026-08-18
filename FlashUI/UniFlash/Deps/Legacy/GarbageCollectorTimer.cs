using System;
using System.Collections;
using System.Diagnostics;
using System.Runtime.InteropServices;
using Lobby.Configs;
using NivalCLI;
using UnityEngine;
using Debug = UnityEngine.Debug;

public class GarbageCollectorTimer : MonoBehaviour
{
  private float _timer;
  private static bool _is64Bit;
  private static long _memorySize;

  private static bool _isInitialized; 

  [DllImport("kernel32.dll", SetLastError = true, CallingConvention = CallingConvention.Winapi)]
  [return: MarshalAs(UnmanagedType.Bool)]
  public static extern bool IsWow64Process([In] IntPtr hProcess, [Out] out bool lpSystemInfo);

  private static bool Is64Bit()
  {
    bool retVal;
    IsWow64Process(Process.GetCurrentProcess().Handle, out retVal);
    return retVal;
  }

  private static void Init()
  {
    _is64Bit = Is64Bit();
    _memorySize = SystemInfo.systemMemorySize * 1024L * 1024L;
    _isInitialized = true;
  }

  private void Update()
  {
    if (Config.GcPeriod > 0)
    {
      _timer += Time.deltaTime;

      if (_timer > Config.GcPeriod)
      {
        _timer = 0;

        Collect();
      }
    }
  }

  public static bool IsNeedCollect()
  {
    if (!_isInitialized)
    {
      Init();
    }

    var needCollect = false;
    var alocatedMemory = GC.GetTotalMemory(false);

    if (_is64Bit)
    {
      if (_memorySize <= Config.Gc64Threshold && alocatedMemory >= Config.Gc32Threshold)
      {
        needCollect = true;
      }

      if (_memorySize > Config.Gc64Threshold && alocatedMemory >= Config.Gc64Threshold)
      {
        needCollect = true;
      }
    }
    else
    {
      if (alocatedMemory >= Config.Gc32Threshold)
      {
        needCollect = true;
      }
    }

    return needCollect;
  }

  public static void Collect()
  {
    if (IsNeedCollect())
    {
      GC.Collect();
    }
  }
}
