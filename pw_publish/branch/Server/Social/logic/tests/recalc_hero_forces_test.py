import sys
sys.path.append('../')
sys.path.append('../..')
from logic.recalc_hero_forces import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class recalc_hero_forces_test:

    def recalc_hero_forces_test( self, env ):
        modeldata = env.acc.model
        modeldata.hireHero(crc32("highlander"), 0, env.I.WS, env.acc, env.I)
        hero, heroId = modeldata.findHeroByCrc32(crc32("highlander"))
        assert hero
        hero.TalentSets[0].Force = 3

        requests = [(Recalc_hero_forces, RecalcHeroForcesRequest(modeldata, {"hero_id" : ["" + str(hero.id) + ""],}, False))]
        changeList = env.execActions(requests)
        changeList = env.execActions(requests)
        assert hero.TalentSets[0].Force == hero.TalentSets[1].Force