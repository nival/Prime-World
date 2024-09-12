from base.helpers import *

import pickle
from binascii import crc32


class LockTalents:
    def convertModelData( self, env, acc, md, dict ):
        #read talents from AlphaPush7 StaticData
        try:
            dir_7 = os.path.dirname( os.path.realpath(__file__) )
            hero_file_read_7 = open( os.path.join( dir_7, "SD_AP7.pck" ), "rb", 32*1024 )
            root_heroes_7 = pickle.load( hero_file_read_7 )
        except:
            err("ap7 static data loading failed")
            catch()

        
        #err("Talents total: " + str(len(md.ItemsKeeper)))
        talents_moved = 0
        talents_created = 0
        #err("Placing default talents in heroes")
        for heroId in md.HeroesKeeper:
            mdHero = md.getHeroByID( heroId )
            if mdHero.PersistentId in acc.SD.data['Heroes']:
                staticHero7 = root_heroes_7.HEROES.get(root_heroes_7.INDEX_HEROES.get(mdHero.PersistentId) )
                staticHero8 = acc.SD.data['Heroes'][mdHero.PersistentId]

            
            if staticHero7:
                #moving all hero talents to UserInventory
                for key in mdHero.TalentSet.keys():
                    talent = mdHero.TalentSet.get(key)
                    md.UserInventory.add(talent)
                    mdHero.TalentSet.remove(key)
                    talents_moved += 1


                rowCount = 0
                for row in staticHero8['defaultTalentsSets']['Item'][0]['levels']['Item']:
                    itemCount = 1
                    for pos in row['talents']['Item']:
                        if 'persistentId' in pos['talent'] and pos['talent']['persistentId']:
                            talentId = md.addNewTalent()
                            createdTalent = md.getTalentByID( talentId )
                            createdTalent.PersistentId = crc32(pos['talent']['persistentId'])
                            createdTalent.IsNew = False
                            createdTalent.ActionBarIdx = -1
                            position = rowCount * 6 + itemCount
                            mdHero.TalentSet.add( position, createdTalent)

                            talents_created += 1
                        itemCount += 1
                    rowCount += 1
          

                 
        #err("Talents added: " + str(talents_created))
        #err("Talents moved: " + str(talents_moved))
        #creation list of talents to be removed
        talentsToDelete = []
        for heroId in md.HeroesKeeper:
            mdHero = md.getHeroByID( heroId )
            staticHero7 = root_heroes_7.HEROES.get(root_heroes_7.INDEX_HEROES.get(mdHero.PersistentId) )
            #err("Static data: " + str(staticHero) )                         
            if staticHero7:
                for row in staticHero7.talents:
                    #move all talents to UserInventory                    
                    for staticTalent in row:
                        talentsToDelete.append(staticTalent.CRC32)
                            
   
        #err("Deleting " + str(len(talentsToDelete)) + " talents")
        for talentId in md.UserInventory.keys():
            mdTalent = md.getTalentByID( talentId )
            if mdTalent.PersistentId in talentsToDelete:
                #err("Removing talent" + str(mdHero.TalentSet.get(position).PersistentId) + " from RemoveList")
                talentsToDelete.remove(mdTalent.PersistentId)
                #err("Done")
                #err("Removing talent" + str(mdHero.TalentSet.get(position).PersistentId) + " from UserInventory")
                md.UserInventory.remove(mdTalent.id)
                #err("Done")
                #err(str(len(talentsToDelete)) + " talents left in remove list")
        
        #for talentToDelete in talentsToDelete:
            #err("Not found talent: " + str(talentToDelete))
        
        #err("Talents total: " + str(len(md.ItemsKeeper)))

        return md, acc.db