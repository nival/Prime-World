using System;
using System.Collections.Generic;
using System.IO;

namespace DBCodeGen.Utils
{
  public class LinesReader : IEnumerable<string>, IDisposable
  {
    #region private class LinesEnumerator : IEnumerator<string>

    private class LinesEnumerator : IEnumerator<string>
    {
      private readonly StreamReader reader;
      private bool canReset = true;
      private string line;

      public LinesEnumerator( Stream stream ) { reader = new StreamReader( stream, true ); }

      public void Dispose()
      {
        reader.Close();
        reader.Dispose();
      }

      public string Current { get { return line; } }
      object System.Collections.IEnumerator.Current { get { return Current; } }

      public bool MoveNext()
      {
        canReset = false;
        if ( reader.EndOfStream )
          return false;
        line = reader.ReadLine();
        return line != null;
      }

      public void Reset()
      {
        if ( !canReset )
          throw new InvalidOperationException( "Cannot reset stream from LinesReader" );
      }
    }

    #endregion

    private readonly Stream stream;

    public LinesReader( Stream stream ) { this.stream = stream; }

    #region IDisposable Members

    public void Dispose()
    {
      if ( stream != null )
        stream.Dispose();
    }

    #endregion

    #region IEnumerable<string> Members

    public IEnumerator<string> GetEnumerator()
    {
      if ( stream == null )
        return new List<string>().GetEnumerator();
      else
        return new LinesEnumerator( stream );
    }

    #endregion

    #region IEnumerable Members

    System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
    {
      return GetEnumerator();
    }

    #endregion
  }
}
