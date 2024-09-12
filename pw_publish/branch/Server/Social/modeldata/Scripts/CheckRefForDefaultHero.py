# -*- coding: utf-8 -*-
from base.helpers import *
from binascii import crc32

class CheckRefForDefaultHero:
    def convertModelData( self, env, acc, md, dict ):
        HeroesRef = {}
        for hid, hero in md.HeroesKeeper.iteritems():
            if hid in md.Heroes:
                HeroesRef[hid] = HeroesRef.get(hid, 0) + 1
            else:
                md.Heroes.realdict[hid] = hero
                md.Heroes.dictionary[hid] = hid
                HeroesRef[hid] = HeroesRef.get(hid, 0) + 1
        '''
        for talentId, talent in md.UserInventory.items():
            if talent.defaultForHero and talent.defaultForHero.get():
                h = talent.defaultForHero.get()
                HeroesRef[h.id] = HeroesRef.get(h.id, 0) + 1
            if talent.Owner and talent.Owner.get():
                h = talent.Owner.get()
                HeroesRef[h.id] = HeroesRef.get(h.id, 0) + 1
            if talent.Soulbound and talent.Soulbound.get():
                h = talent.Soulbound.get()
                HeroesRef[h.id] = HeroesRef.get(h.id, 0) + 1
        '''
        for talentId, talent in md.ItemsKeeper.iteritems():
            if talent.defaultForHero and talent.defaultForHero.object:
                #h = talent.defaultForHero.get()
                HeroesRef[talent.defaultForHero.object] = HeroesRef.get(talent.defaultForHero.object, 0) + 1
            if talent.Owner and talent.Owner.object:
                #h = talent.Owner.get()
                HeroesRef[talent.Owner.object] = HeroesRef.get(talent.Owner.object, 0) + 1
            if talent.Soulbound and talent.Soulbound.object:
                #h = talent.Soulbound.get()
                HeroesRef[talent.Soulbound.object] = HeroesRef.get(talent.Soulbound.object, 0) + 1


        for cid, constr in md.ConstructionsKeeper.iteritems():
            for hid, h in constr.HeroesInBuilding.items():
                HeroesRef[hid] = HeroesRef.get(hid, 0) + 1

        for hid, hero in md.HeroesKeeper.iteritems():
            if hid in HeroesRef:
                if HeroesRef[hid] >= hero.__dict__["refCounter"]:
                    warn("Bad ref for hero(PersistentId=%s, hero_id=%s, name=%s) [real count of references to hero is %s] != [refCounter is %s]", hero.PersistentId, hid, hero.class_name, HeroesRef[hid], hero.__dict__["refCounter"])
                    hero.__dict__["refCounter"] += HeroesRef[hid] - hero.__dict__["refCounter"] + 1
            else:
                warn("Strange ref for hero(PersistentId=%s, hero_id=%s, name=%s) [real count of references to hero is unknown] != [refCounter is %s]", hero.PersistentId, hid, hero.class_name, hero.__dict__["refCounter"])
        return md, acc.db
