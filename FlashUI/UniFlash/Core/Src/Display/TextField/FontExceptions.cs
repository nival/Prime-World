using System;

namespace Flash
{
  internal sealed class MainStorageLostException : Exception
  {
    public MainStorageLostException()
    {
    }
    public MainStorageLostException( string message )
      : base( message )
    {
    }
  }

  internal sealed class PlaceCharacterException : Exception
  {
    public PlaceCharacterException()
    {
    }
    public PlaceCharacterException( string message )
      : base( message )
    {
    }
  }
}


