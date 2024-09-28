using System;
using System.IO;

namespace libdb.Diagnostics
{
  public sealed class FileDumper : IDumper, IDisposable
  {
    private readonly object sync = new object();

    public string OutputFile { get; set; }

    private StreamWriter logWriter = null;

    public FileDumper()
    {
      OutputFile = string.Format( "OutputFile_{0}.log", DateTime.Now.ToShortDateString() );
    }

    public FileDumper(string _outputFile)
    {
      OutputFile = _outputFile;
    }

    public void Trace( Log.Level level, TimeSpan time, int threadId, string fileName, int lineNumber, string message )
    {
      Log.Assert( !disposed, "FileDumper already disposed" );

      lock( sync )
      {
        if( logWriter == null)
        {
          string dir = Path.GetDirectoryName( OutputFile );
          if(!string.IsNullOrEmpty( dir ))
            Directory.CreateDirectory(dir);  
          
          logWriter = new StreamWriter( OutputFile, true );
        }
          
        
        logWriter.WriteLine( "{0}\t{1}\tThreadId:{2}\tFile:{3}\tLine:{4}\t{5}", 
                             DateTime.Now, level, threadId, Path.GetFileName(fileName), lineNumber, message );
        logWriter.Flush();
      }
    }

    private bool disposed;

    public void Dispose()
    {
      if(!disposed)
      {
        logWriter.Close();
        
        logWriter = null;
        disposed = true;
      }
    }
  }
}
