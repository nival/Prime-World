import sys
sys.path.append('../')
from binascii import crc32
sys.path.append('../..')
from enums import *

sys.path.append('../../modeldata')
from changes import *

class md_validators_test:
  def empty_talent_id_in_ui_test( self, env ):
    modeldata = env.acc.model

    talent_id = modeldata.addNewTalent( )
    talent = modeldata.getTalentByID( talent_id )
    talent.PersistentId = 100500
    talent.IsNew = False
    modeldata.UserInventory.add( talent )

    inventoryCount = len(modeldata.UserInventory)

    modeldata.validateEmptyTalentPersistentId(env.acc.SD,0)

    assert len(modeldata.UserInventory) == inventoryCount - 1

  def empty_talent_id_in_talent_production_building_test( self, env ):
    modeldata = env.acc.model

    construction = env.add_construction(modeldata, "Talent_Production")

    construction.CraftedTalents.append( 100500 )

    talentsCount = len(construction.CraftedTalents)

    modeldata.validateEmptyTalentPersistentId(env.acc.SD, 0)

    assert len(construction.CraftedTalents) == talentsCount - 1

  def empty_talent_id_in_ts_test( self, env ):
    modeldata = env.acc.model

    for heroId in modeldata.HeroesKeeper:
      hero = modeldata.getHeroByID( heroId )
      hero.Hired = True
      break
    for tsSlotId in hero.TalentSets[0].Talents:
      tid= modeldata.getHeroByID(heroId).TalentSets[0].Talents.get(tsSlotId)
      talent = modeldata.getTalentByID(tid)
      talent.PersistentId = 100500
      break

    count = len(modeldata.getHeroByID(heroId).TalentSets[0].Talents)

    modeldata.validateEmptyTalentPersistentId(env.acc.SD, 0)

    assert len(modeldata.getHeroByID(heroId).TalentSets[0].Talents) == count - 1
    
  def validate_skin_test( self, env ):
    modeldata = env.acc.model
    staticSkins = env.acc.SD.data['Skins']
    staticSkin1 = staticSkins[staticSkins.keys()[0]]
    staticSkin2 = staticSkins[staticSkins.keys()[1]]
    staticSkin3 = staticSkins[staticSkins.keys()[2]]
    tmp_staticSkin1 = staticSkin1
    staticSkin1['legal'] = False
    
    hero = env.add_hero( modeldata, "highlander" )
    
    skin1, skin_id1 = modeldata.newSkin()
    skin1.PersistentId = crc32(staticSkin1['persistentId'])
    
    skin2, skin_id2 = modeldata.newSkin()
    skin2.PersistentId = crc32("highlander_S1_A")
    
    skin3, skin_id3 = modeldata.newSkin()
    skin3.PersistentId = crc32(staticSkin3['persistentId'])
    
    skin4, skin_id4 = modeldata.newSkin()
    skin4.PersistentId = crc32("holy_sheet")
    
    hero.HeroSkins.Skins.add(skin1)
    hero.HeroSkins.CurrentSkin = skin1
    hero.HeroSkins.Skins.add(skin2)
    hero.HeroSkins.Skins.add(skin3)
    hero.HeroSkins.Skins.add(skin4)
    
    env.acc.getConfig().INVALID_SKINS.append(staticSkin3['persistentId'])
    
    assert len(hero.HeroSkins.Skins) == 4
    assert len(env.acc.getConfig().INVALID_SKINS) == 1
    
    modeldata.validateSkins(env.acc.getConfig(), env.acc )
    
    assert len(hero.HeroSkins.Skins) == 1
    assert hero.HeroSkins.CurrentSkin == IGuidGenerator.InvalidUID
    
    staticSkin1 = tmp_staticSkin1
    
    
    
    
    
    
    
    
    
    