from base.helpers import *

import pickle
from binascii import crc32


class SetAP81TalentsSets:
    def convertModelData( self, env, acc, md, dict ):

        for heroId in md.HeroesKeeper:
            mdHero = md.getHeroByID( heroId )

            for key in mdHero.TalentSet.keys():
                talent = mdHero.TalentSet.get(key)
                if talent:
                    md.UserInventory.add(talent)
                    mdHero.TalentSet.remove(key)


        dir_8 = os.path.dirname( os.path.realpath(__file__) )
        file_read = open( os.path.join( dir_8, "talents_to_delete_ap8.pck" ), "rb", 32*1024 )
        talentsToDelete = pickle.load( file_read )
                                     
                                                 
   
        for talentId in md.UserInventory.keys():
            mdTalent = md.getTalentByID( talentId )
            if mdTalent.PersistentId in talentsToDelete:
                talentsToDelete.remove(mdTalent.PersistentId)
                md.UserInventory.remove(mdTalent.id)

        return md, acc.db