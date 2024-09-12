
namespace MainNS.MyNS
{

[Remote]
public class CSRemoteClass
{
  public void MyFunc()
  {
    int a = 0;
    a++;
  }

  public int GetInt()
  {
    return 10;
  }

  [Remote]
  public void Process()
  {
    DoSmth();
  }

  private void DoSmth()
  {
    DoNothing();
  }

  [Remote]
  public CVec2 GetVec()
  {
    return new CVec2( 10.0f, 20.0f );
  }

  public CVec2 GetVector()
  {
    return new CVec2( 10.0f, 20.0f );
  }

  [Remote]
  public void DoVecOp( CVec2 vec1, CVec2 vec2, int op )
  {
  }

  [Remote]
  public void DoStrings( string str1, List<string> strs )
  {
  }

  //REMOTEPTR Location.RLocationInstance
  [Remote]
  public void setLocation(Location.RLocationInstance inst)
  {
  }
}

}