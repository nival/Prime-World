from base.helpers import *

class ConvertIdToPersistentId:
    def convertModelData( self, env, acc, md, dict ): 
        for constructionId in md.ConstructionsKeeper:
            construction = md.getConstructionByID( constructionId )
            try:
                construction.PersistentId = dict["ModelData"]["ConstructionsKeeper"]["Keeper"][str(construction.id)]["Construction"]["PlanID"]
            except KeyError:
                pass
                
        for heroId in md.HeroesKeeper:
            hero = md.getHeroByID( heroId )
            try:
                hero.PersistentId = dict["ModelData"]["HeroesKeeper"]["Keeper"][str(hero.id)]["Hero"]["class_id"]
            except KeyError:
                pass
        for talentId in md.ItemsKeeper:
            talent = md.getTalentByID( talentId )
            try:
                talent.PersistentId = dict["ModelData"]["ItemsKeeper"]["Keeper"][str(talent.id)]["Talent"]["TalentID"]
            except KeyError:
                pass
        return md, acc.db