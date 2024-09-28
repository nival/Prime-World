using System;
using System.Collections.Generic;
using System.Text;

namespace MemoryMonitor.CallStack
{
  public class ModuleLayout
  {
    private class ModuleDesc
    {
      public readonly uint Start = 0;
      public readonly uint Length = 0;
      public readonly string FilePath = string.Empty;
      public readonly string Name = string.Empty;

      public ModuleDesc( uint start, uint length, string filename )
      {
        Start = start; Length = length; FilePath = filename;
        Name = System.IO.Path.GetFileName( FilePath );
      }
    }

    private List<ModuleDesc> modules = new List<ModuleDesc>();

    public void RegisterModule( string name, uint moduleStart, uint moduleLength )
    {
      modules.Add( new ModuleDesc( moduleStart, moduleLength, name ) );
    }

    public string GetModuleName( uint address )
    {
      foreach ( ModuleDesc module in modules )
      {
        if ( address >= module.Start && address < module.Start + module.Length )
          return module.Name;
      }
      return string.Empty;
    }

    public uint GetModuleBase( string moduleName )
    {
      foreach ( ModuleDesc module in modules )
      {
        if ( module.Name == moduleName )
          return module.Start;
      }

      return 0;
    }

    public string GetModulePath( string moduleName )
    {
      foreach ( ModuleDesc module in modules )
      {
        if ( module.Name == moduleName )
          return module.FilePath;
      }

      return string.Empty;
    }
  }
}
