using System.Collections.Generic;
using System.ComponentModel;
using libdb.DB;
using Foundation.DBSystem;

namespace PF_GameLogic.DBStats
{

  [UseTypeName("TTIP")]
  public class DBTooltip : DBResource
  {
    public TextRef friendStyle = new TextRef();
    public TextRef enemyStyle  = new TextRef();

    public TextRef heroInfo   = new TextRef();
    public TextRef unitInfo   = new TextRef();
  }

}