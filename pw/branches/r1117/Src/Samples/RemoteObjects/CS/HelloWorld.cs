using System;

namespace test
{

class HelloWorld
{
  public HelloWorld()
  {
  }

  public void Print( String msg )
  {
    System.Console.WriteLine( msg );
  }
  public void Write( String msg )
  {
    System.Console.WriteLine( msg );
  }
  public int GetInt( int val )
  {
    return 10 * val;
  }
}

}