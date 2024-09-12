using System;

namespace libdb
{
  public interface IRichList
  {
    Type EnumType { get; }
 		bool CanAdd { get; }
    bool CanInsert { get; }
    bool CanDelete { get; }
    bool CanMoveItems { get; }

    int Count { get; }
    int MinCount { get; }
    int MaxCount { get; }

    void ResetElement( int index );
    bool IsElementDerivedFromParent( int index );
  }
}
