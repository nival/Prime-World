namespace libdb
{

  public interface IBasicDBValue : IOwnerable
  {
    void Reset();
    bool IsDerivedFromParent();
    void SetParent( object parent );
    void Assign( object source );
  }

  public interface ICompositeDBValue : IBasicDBValue
  {
    void ResetField( string fieldName );
    bool IsFieldDerivedFromParent( string fieldName );
    bool HasParent();
  }

}
