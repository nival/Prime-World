# -*- coding: utf-8 -*-
from base.helpers import *
from binascii import crc32

'''
Setting all talentSets crc in selectedHeroes at -1, in order to call validate class talents
PF-107425
'''

selectedHeroes = ["crusader_A", "crusader_B"]

class FixCrusaderClassTalents:
    def convertModelData( self, env, acc, md, dict ):

        heroesList = [md.findHeroByCrc32(crc32(heroName))[0] for heroName in selectedHeroes]

        if not any(v is None for v in heroesList):
            return md, acc.db

        info('FixCrusaderClassTalents script TalentSets Crc Before. Format (\'HERO\':[crcTsId1, crcTsId2, crcTsId3]) {}'.format(
            {acc.SD.getStaticHero(hero)['id']: [ts.TalentSetCrc for _, ts in hero.TalentSets.iteritems()] for hero
             in heroesList if hero}))

        for hero in [x for x in heroesList if x]:
            for _, ts in hero.TalentSets.iteritems():
                ts.TalentSetCrc = -1

        info('FixCrusaderClassTalents script heroes TalentSets Crc After {}'.format(
            {acc.SD.getStaticHero(hero)['id']: [ts.TalentSetCrc for _, ts in hero.TalentSets.iteritems()] for hero in
             heroesList if hero}))

        return md, acc.db






