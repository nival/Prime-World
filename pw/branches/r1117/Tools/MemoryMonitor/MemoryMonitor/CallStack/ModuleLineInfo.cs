using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Windows.Forms;

namespace MemoryMonitor.CallStack
{
  public class ModuleLineInfo
  {
    public readonly string Name = string.Empty;

    private bool isLoaded = false;
    Dia2Lib.DiaSourceClass diaSrcClass = null;
    Dia2Lib.IDiaSession diaSession = null;

    private class FunctionDesc
    {
      public readonly string Name;
      public readonly uint Address;

      public FunctionDesc( string name, uint address ) { Name = name; Address = address; }
    }

    public ModuleLineInfo( string pdbName )
    {
      Name = pdbName;
    }

    public string GetLineInfo( uint address )
    {
      if ( !isLoaded )
        return Path.GetFileName( Name ) + string.Format( ", no line info (+{0:X8})", address );

      string result = Path.GetFileName( Name );
      try
      {
        Dia2Lib.IDiaSymbol diaFunc = null;
        diaSession.findSymbolByRVA( address, Dia2Lib.SymTagEnum.SymTagFunction, out diaFunc );
        result = diaFunc.name;

        Dia2Lib.IDiaEnumLineNumbers diaFuncLines = null;
        diaSession.findLinesByRVA( diaFunc.relativeVirtualAddress, (uint)diaFunc.length, out diaFuncLines );
        for ( uint i = 0; i < diaFuncLines.count; ++i )
        {
          Dia2Lib.IDiaLineNumber item = diaFuncLines.Item( i );
          if ( address >= item.relativeVirtualAddress && address < item.relativeVirtualAddress + item.length )
          {
            result += string.Format( " ({1}, {0})", item.lineNumber, Path.GetFileName( item.sourceFile.fileName ) );
            break;
          }
        }
      }
      catch ( Exception e )
      {
        result += ", exception: " + e.Message;
      }

      return result;
    }

    public void LoadLines()
    {
      try
      {
        diaSrcClass = new Dia2Lib.DiaSourceClass();

        diaSrcClass.loadDataFromPdb( Name );
        diaSrcClass.openSession( out diaSession );
        isLoaded = true;
      }
      catch ( Exception e )
      {
        MessageBox.Show( "PDB read failed:\n" + e.Message );
      }
    }
  }
}
