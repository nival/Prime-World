from base.helpers import *

class SetLastRankedGameTime:
    def convertModelData(self, env, acc, md, dict):
        lastGameTime = acc.db.registration_date
        for heroId in md.Heroes:
            hero = md.getHeroByID(heroId)
            if hero.lastPlayed > lastGameTime:
                lastGameTime = hero.lastPlayed
        md.LordInfo.LastRankedGameTime = lastGameTime
        return md, acc.db