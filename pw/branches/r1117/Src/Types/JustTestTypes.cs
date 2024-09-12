//#include "Foundation.cs"

using System;
using System.Collections.Generic;
using Foundation.DBSystem;
using libdb.DB;

namespace libdb.DBTestTypes
{
  public class SimpleTestProperty
  {
    public string name = string.Empty;
    public string field = string.Empty;
  }

  public enum SimpleEnum
  {
    Zero=0,
    One=0x01,
    Two=0x02,
    Four=0x04,
    Five=0x05,
    Eight=0x08,
    Fifteen=0x0F,
    Sixteen=0x10,
  }

  [Flags]
  public enum FlagEnum
  {
    Zero=0,
    One=0x01,
    Two=0x02,
    Four=0x04,
    Five=0x05,
    Eight=0x08,
    Fifteen=0x0F,
    Sixteen=0x10,
  }

  public class JustTestStruct
  {
    public int _intValue = 0;
    public SimpleEnum _enumValue = SimpleEnum.Zero;
    public DBPtr<JustTestType> childObject;
  }

  [HasStates]
  public class JustTestType : DBResource
  {
    public AnimatedInt _ints = new AnimatedInt();
    public AnimatedVec3 _vecs = new AnimatedVec3( 1.0f, 2.0f, 3.0f );
    public AnimatedQuat _quats = new AnimatedQuat();

    public SimpleEnum simple = SimpleEnum.Zero;
    public FlagEnum flags = FlagEnum.Zero;

    public Vec3 v3;
    public Quat quat;
    public AnimatedVec3 avec3;
    public AnimatedQuat aquat;

    [SrcFile( "Maya files", "*.tga" )]
    public string srcFileName = string.Empty;

    public TextRef text = new TextRef();

    [FileRef( "*.tga" )]
    public string file = string.Empty;

    public JustTestStruct nestedStruct;

    public DBPtr<JustTestType> childObject;
  }

  public class JustTestType2 : JustTestType
  {
    public List<int> intList = new List<int>();
    public List<SimpleTestProperty> structList = new List<SimpleTestProperty>();
    public List<DBPtr<JustTestType>> ptrList = new List<DBPtr<JustTestType>>();
  }

  public class ObjectLockMaskT
  {
    public float tileSize = 0.5f;
    public List<ObjectLockItemT> mask = new List<ObjectLockItemT>();
  }


  public class ObjectLockItemT
  {
    public int x;
    public int y;
  }

  public class JustTestType3 : DBResource
  {
    public ObjectLockMaskT lockMask;
  }

  public class LofSimpleInheritable : DBResource
  {
    public bool _bool = false;
    public int _int = 0;
    public float _float = 0.0f;
    public string _string = string.Empty;
  }

  public class LofHardInheritable : DBResource
  {
    public int _int = 0;
    public List<int> _list = new List<int>();
  }

  [NeedEqualOperator]
  public class PseudoStruct
  {
    public int x;
    public int y;
  }

  public class LofComplexInheritable : DBResource
  {
    public int _int = 0;
    public List<PseudoStruct> _list = new List<PseudoStruct>();
  }

  public class LofSimpleChild : LofSimpleInheritable
  {
    public DBPtr<LofSimpleInheritable> twin;
    public PseudoStruct _data;
  }
}
