using Foundation.DBSystem;
using libdb.DB;
using System.ComponentModel;

namespace SocialTypes.DBTypes
{
  public class CommonConstructionsSettings : DBResource
  {
    [Description( "Смещение префаба здания относительно левой верхней клетки знимаемой площади" )]
    public Vec3 Offset;
  }
}
