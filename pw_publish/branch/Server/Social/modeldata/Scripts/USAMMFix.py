from base.helpers import *
from binascii import crc32   # zlib version is not cross-platform
from enums import *

class USAMMFix:
    def getTalentPointsToLevel( self, staticTalent, SD ):
        intRarity = getattr(ETalentRarity, staticTalent['rarity'])
        if intRarity < len(SD.data['TalentLevelToPointsAndRarity']['Item']) and SD.data['TalentLevelToPointsAndRarity']['Item'][intRarity]:
            pointsToLevel = SD.data['TalentLevelToPointsAndRarity']['Item'][intRarity]['levelToPoints']
            if 'Item' in pointsToLevel:
                return pointsToLevel['Item']        



    def addThreeRandomBlueTalents( self, env, md ):
        randValue = md.LordInfo.OrdinaryForgeRoll.TransmutationRandomSeed
        for x in range( 0, 3 ):
            talent_id = md.addNewTalent()
            talent = md.getTalentByID( talent_id )
            talent.IsNew = True
            talent.ActionBarIdx = -1
            talent.PersistentId = env.acc.SD.getRandomTalent( "excellent", "", randValue>>8 )
            randValue = md.getRandomPure(randValue)
            md.UserInventory.add(talent)

        md.LordInfo.TransmutationRandomSeed = randValue



    def convertModelData( self, env, acc, md, dict ):
        if env.deployName != "USA":
            info( "Not apply script USAMMFix, deploy %r" % env.deployName )
            return md, acc.db

        try:
            goldReplenish = 0
            for heroId in md.HeroesKeeper:
                hero = md.getHeroByID( heroId )
                if hero.Rating > 1500:
                    diff = int(hero.Rating - 1500)
                    goldReplenish += diff
                    hero.Rating = 1500

                for talentId in hero.TalentSet.keys():
                    talent = hero.TalentSet.get(talentId)  
                    if talent:
                        staticTalent = acc.SD.getStaticTalent(talent)
                        if staticTalent != "None" and staticTalent != None:
                            if staticTalent['rarity'] == "exclusive":
                                talent.ActionBarIdx = -1
                                md.UserInventory.add(talent)
                                hero.TalentSet.remove(talentId)
                                
                hero.CalcForce( md, None, acc )

            info( "Gold for rating %d" % goldReplenish )
            orangeTalents = 0
            for talentId in md.ItemsKeeper.keys():
                talent = md.getTalentByID( talentId )
                if talent:
                    staticTalent = acc.SD.getStaticTalent(talent)
                    if staticTalent != "None" and staticTalent != None:
                        if staticTalent['rarity'] == "exclusive":
                            orangeTalents += 1
                            talent.Soulbound = 0
                            goldReplenish += 50
                            self.addThreeRandomBlueTalents( env, md )
                        pointsToLevel = self.getTalentPointsToLevel( staticTalent, env.staticUSA )
                        talentLevel = env.staticUSA.getTalentLevelByPoints( talent.Points, staticTalent )
                        if talentLevel >= 2:
                            pearls = env.staticUSA.getTalentMergePrice( pointsToLevel[2]-1, talent.Points, staticTalent )
                            talent.Points = pointsToLevel[2]-1
                            if pearls > 0:
                                goldReplenish += pearls
                                price = md.createResourcesTable( Perl = pearls ) 
                                if price:
                                    md.sell( price, acc, False )

            info( "Orange talents %d" % orangeTalents )
            info( "Total gold %d" % goldReplenish )
            if goldReplenish:
                env.I.BILL.replenish( acc.db.auid, goldReplenish, "GoldForMMFix", None )

        except:
            catch()  

        return md, acc.db
