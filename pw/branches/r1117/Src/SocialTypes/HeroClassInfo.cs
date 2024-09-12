using System.Collections.Generic;
using libdb.DB;
using PF_Types.SocialClient;

namespace SocialTypes.DBTypes
{
  public class HeroClassInfo
  {
    public HeroClassEnum Class;
    public TextRef Name = new TextRef();
    public TextRef Description = new TextRef();
  }

  public class HeroClassInfoTable : DBResource
  {
    public List<HeroClassInfo> HeroClasses;
  }
}
