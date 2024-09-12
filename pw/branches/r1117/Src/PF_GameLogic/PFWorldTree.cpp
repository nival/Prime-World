/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PFWorldTree.h"
#include "TileMap.h"
#include "../Terrain/Terrain.h"
#include "PFClientTree.h"


/////////////////////////////////////////////////////////////////////////////////
// Defines
/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
// Static data
/////////////////////////////////////////////////////////////////////////////////

namespace NWorld
{

// debug: set command to last craeted tree
static PFWorldTree    *s_tree = NULL;

/////////////////////////////////////////////////////////////////////////////////
// Methods
/////////////////////////////////////////////////////////////////////////////////
PFWorldTree::PFWorldTree(PFWorld *pWorld, const NDb::AdvMapObject &dbObject)
:PFWorldObjectBase(pWorld)
{
  CreateClientObject<NGameX::PFClientTree>(dbObject, pWorld->GetScene());
  s_tree = this;
}
  
void    PFWorldTree::DropTree(const CVec3 &dir)
{
  NGameX::PFClientTree *clientTree = (NGameX::PFClientTree*)ClientObject();
  clientTree->DropTree(dir);
}
void    PFWorldTree::RestoreTree()
{
  NGameX::PFClientTree *clientTree = (NGameX::PFClientTree*)ClientObject();
  clientTree->RestoreTree();
}


/////////////////////////////////////////////////////////////////////////////////
// Commands
/////////////////////////////////////////////////////////////////////////////////


bool CommandDropTree(const char *name, const vector<wstring> &params)
{
  CVec3 dir(0, -1.0f, 0);
  if (s_tree)
    s_tree->DropTree(dir);
  return true;
}

bool CommandRestTree(const char *name, const vector<wstring> &params)
{
  if (s_tree)
    s_tree->RestoreTree();
  return true;
}

REGISTER_CMD( droptree, CommandDropTree );
REGISTER_CMD( resttree, CommandRestTree );



} // name space

REGISTER_WORLD_OBJECT_NM(PFWorldTree, NWorld)

