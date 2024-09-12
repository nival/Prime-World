import sys
sys.path.append('../')
sys.path.append('../..')
from logic.upgrade_talent import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class upgrade_talent_test:

  def upgrade_talent_in_UI_test( self, env ):
    modeldata = env.acc.model    
    target_talent = env.add_talent(modeldata, "G137")
    modeldata.UserInventory.add( target_talent )
    points_to_add = 1
    points = target_talent.Points

    requests = [ ( Upgrade_talent, UpgradeTalentRequest( modeldata, { "target_talent_id" : ["" + str(target_talent.id) + ""], "points" : ["" + str(points_to_add) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert target_talent.id in modeldata.UserInventory
    
    assert target_talent.Points == points + points_to_add
    
  def upgrade_talent_in_TS_test( self, env ):
    modeldata = env.acc.model    
    target_talent = env.add_talent(modeldata, "G137")
    hero = env.add_hero(modeldata, "mowgly")
    target_staticTalent = env.acc.SD.getStaticTalent(target_talent)
    tsSlotId = target_staticTalent['minLevel'] + 1
    hero.TalentSets[0].Talents.add(tsSlotId, target_talent)
    
    points_to_add = 1
    points = target_talent.Points

    requests = [ ( Upgrade_talent, UpgradeTalentRequest( modeldata, { "target_talent_id" : ["" + str(target_talent.id) + ""], "points" : ["" + str(points_to_add) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(hero.TalentSets[0].Talents) == 1
    
    assert target_talent.Points == points + points_to_add
    
  def upgrade_talent_negative_points_test( self, env ):
    modeldata = env.acc.model    
    target_talent = env.add_talent(modeldata, "G137")
    modeldata.UserInventory.add( target_talent )
    points_to_add = -100500
    points = target_talent.Points

    requests = [ ( Upgrade_talent, UpgradeTalentRequest( modeldata, { "target_talent_id" : ["" + str(target_talent.id) + ""], "points" : ["" + str(points_to_add) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert target_talent.id in modeldata.UserInventory
    
    assert target_talent.Points == 0
    
  def upgrade_talent_maximum_points_test( self, env ):
    modeldata = env.acc.model    
    target_talent = env.add_talent(modeldata, "G137")
    modeldata.UserInventory.add( target_talent )
    points_to_add = 100500
    points = target_talent.Points

    requests = [ ( Upgrade_talent, UpgradeTalentRequest( modeldata, { "target_talent_id" : ["" + str(target_talent.id) + ""], "points" : ["" + str(points_to_add) + ""] }, False ) ) ]
    changeList = env.execActions( requests )
    
    max_points = env.acc.SD.getTalentMaxPoints(target_talent)  

    assert target_talent.id in modeldata.UserInventory
    
    assert target_talent.Points == max_points
    
  def upgrade_class_talent_test( self, env ):
    modeldata = env.acc.model    
    target_talent = env.add_talent(modeldata, "Archeress_A0")
    modeldata.UserInventory.add( target_talent )
    points_to_add = 1
    points = target_talent.Points

    requests = [ ( Upgrade_talent, UpgradeTalentRequest( modeldata, { "target_talent_id" : ["" + str(target_talent.id) + ""], "points" : ["" + str(points_to_add) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert target_talent.id in modeldata.UserInventory    
    assert target_talent.Points == points
    
    assert changeList[0].get('ec') == EC.DEBUG_MESSAGE