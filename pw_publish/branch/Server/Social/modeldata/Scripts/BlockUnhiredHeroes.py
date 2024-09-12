from base.helpers import *

class BlockUnhiredHeroes:
    def convertModelData( self, env, acc, md, dict ): 
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            if acc.sex == 2 and hero.PersistentId in acc.SD.data['Heroes']:
                if acc.SD.data['Heroes'][hero.PersistentId]['lobbyData']['IsHeroHiredByDefaultFemale'] == 'true':
                    hero.Hired = True
                else:
                    hero.Hired = False    
            elif hero.PersistentId in acc.SD.data['Heroes']:
                if acc.SD.data['Heroes'][hero.PersistentId]['lobbyData']['IsHeroHiredByDefaultMale'] == 'true':
                    hero.Hired = True
                else:
                    hero.Hired = False              
        return md, acc.db
