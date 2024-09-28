from base.helpers import *

class RemoveInvalidTalentUpgradeEntities:
  def convertModelData( self, env, acc, md, dict ):

    valid_ents = md.TalentUpgradeEntities.keys()
    print json_dumps(valid_ents)
    for id, ent in md.TalentUpgradeEntitiesKeeper.items():
      if ent.id not in valid_ents:
        ent.refCounter = 0
        debug("try remove ent {0}".format(ent.id))
        md.TalentUpgradeEntitiesKeeper.deleteByID(ent.id)

    return md, acc.db