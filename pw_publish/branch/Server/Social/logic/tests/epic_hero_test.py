import sys
sys.path.append('../')
from binascii import crc32
from base.helpers import *
sys.path.append('../..')
from enums import *
import MM

class epic_hero_test:

  def epic_hero_dec_dodge_test( self, env ):
    modeldata = env.acc.model

    for heroId in modeldata.Heroes:
      hero = modeldata.getHeroByID( heroId )
      if hero.Hired == True:
        hero = hero
        break

    modeldata.LordInfo.GuardInfo.NumberOfWins = 11.0
    hero.Master = True
    hero.Force = 1600.0

    modeldata.LordInfo.GuardInfo.RetiredTime = int(time.time()) + 100500
    modeldata.LordInfo.GuardInfo.Dodges = 5
    curTime = time.time()
    modeldata.LordInfo.lastDodgesUpdateTime_ = curTime

    assert modeldata.getLordStatus( hero, env.I.Config.getConfig( env.acc.userlocale ) ) == MM.ELordStatus.NORMAL
    
    modeldata.clearDodges()

    assert modeldata.LordInfo.GuardInfo.Dodges == 0
    assert modeldata.getLordStatus( hero, env.I.Config.getConfig( env.acc.userlocale ) ) == MM.ELordStatus.NORMAL
    assert modeldata.LordInfo.GuardInfo.RetiredTime == 0


  def epic_hero_get_retired_test( self, env ):
    modeldata = env.acc.model

    for heroId in modeldata.Heroes:
      hero = modeldata.getHeroByID( heroId )
      if hero.Hired == True:
        hero = hero
        break

    modeldata.LordInfo.GuardInfo.NumberOfWins = 11.0
    modeldata.LordInfo.GuardInfo.Dodges = 9
    hero.Master = True
    hero.Force = 1600.0

    assert modeldata.getLordStatus( hero, env.I.Config.getConfig( env.acc.userlocale ) ) == MM.ELordStatus.NORMAL

    modeldata.addDodge( env.I.WS, env.acc )

    assert modeldata.getLordStatus( hero, env.I.Config.getConfig( env.acc.userlocale ) ) == MM.ELordStatus.NORMAL


  def epic_hero_get_retired_then_guard_test( self, env ):
    modeldata = env.acc.model

    for heroId in modeldata.Heroes:
      hero = modeldata.getHeroByID( heroId )
      if hero.Hired == True:
        hero = hero
        break

    modeldata.LordInfo.GuardInfo.NumberOfWins = 11.0
    modeldata.LordInfo.GuardInfo.Dodges = 9
    hero.Master = True
    hero.Force = 1600.0

    assert modeldata.getLordStatus( hero, env.I.Config.getConfig( env.acc.userlocale ) ) == MM.ELordStatus.NORMAL

    modeldata.addDodge( env.I.WS, env.acc )

    assert modeldata.LordInfo.GuardInfo.RetiredTime != 0
    assert modeldata.getLordStatus( hero, env.I.Config.getConfig( env.acc.userlocale ) ) == MM.ELordStatus.NORMAL

    modeldata.LordInfo.GuardInfo.RetiredTime = int(round(time.time()))-100

    modeldata.clearDodges()

    assert modeldata.LordInfo.GuardInfo.RetiredTime == 0
    assert modeldata.getLordStatus( hero, env.I.Config.getConfig( env.acc.userlocale ) ) == MM.ELordStatus.NORMAL

