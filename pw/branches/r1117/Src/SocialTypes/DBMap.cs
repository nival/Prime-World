//#include "..\PF_Types\SocialClient\DBSocialResources.cs"

using System.Collections.Generic;
using System.ComponentModel;
using Foundation.DBSystem;
using libdb.DB;
using PF_Types.SocialClient;

namespace SocialTypes.DBTypes
{
  public class DBMap : DBResource
  {
    [Description( "Map size in sections." )]
    public Vec2 MapSize;

    [Description( "Map center for Unity 3D coordinates." )]
    public Vec3 MapCenter;
    [Description( "Section size for Unity drawing." )]
    public float SectionSize;

    [Description( "Castle maps grades. Grade 0 is initial map state." )]
    public List<MapGrade> Grades;
  }

  public class MapGrade
  {
    [Description( "List of sections for current grade. Default state is open for building and decoration." )]
    public DBPtr<SectionsSet> Sections;
    public ResourcesTable price;
    public List<BuildedConstruction> BuildedConstructions;
    public int sectionsCount;
  }

  public class IntVec2
  {
    public int x;
    public int y;
  }
}
