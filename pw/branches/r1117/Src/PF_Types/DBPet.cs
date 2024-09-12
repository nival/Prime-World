using System.Collections.Generic;
using System.ComponentModel;
using Scene.DBScene;
using libdb.DB;

namespace PF_GameLogic.DBUnit
{
	[TypeId(0x11624C43)]
	[UseTypeName("PTOB")]
  public class BasePet : Creature
  {
    public float test = 0.15f;
  }
}