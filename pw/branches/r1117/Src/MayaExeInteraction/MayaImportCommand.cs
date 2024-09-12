using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace Tools.MayaExeInteraction
{
  [Serializable]
  class MayaImportCommand : MayaCommand
  {
    public string Scene { get; set; }
    public string OutFile { get; set; }   
    public bool IsCrcRequired { get; set; }
    
    public override string CreateCommand()
    {
      var result = new StringBuilder();

      result.Append( Name );
      
      //Scene
      result.AppendFormat( " \"{0}\"", Scene );

      //Crc
    	if(IsCrcRequired)
    		result.AppendFormat(" \"{0}\"", GetFileHash(Scene));

    	//OutFile
      result.AppendFormat( " \"{0}\"", OutFile );

      //Other parameters  
      foreach( var paramName in GetParameters() )
      {
        string paramValue;
        if(Parameters.TryGetValue(paramName, out paramValue))
        {
          result.AppendFormat( " \"{0}\"", paramValue );
        }
      }

      return result.ToString();
    }

    private static string GetFileHash( string _filePath )
    {
      if( string.IsNullOrEmpty( _filePath ) || !File.Exists( _filePath ) )
      {
        return "";
      }

      var md5 = MD5.Create();
      byte[] hash;

      FileInfo fileInfo = new FileInfo( _filePath );
      int size = (int)fileInfo.Length;

      using( var stream = new BufferedStream( File.OpenRead( _filePath ), size ) )
      {
        hash = md5.ComputeHash( stream );
      }

      string result = string.Empty;

      if( hash.Length > 0 )
        result = BitConverter.ToString( hash ).Replace( "-", "" ).ToLower();

      return result;
    }
  }
}
