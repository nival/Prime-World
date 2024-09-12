class RemoveExtraBaths:
    def convertModelData( self, env, acc, md, dict ):
        buildingName = "Bathhouse"
        bathIds = []
        for constructionId, construction in md.ConstructionsKeeper.iteritems():
            staticConstruction = acc.SD.getStaticConstruction(construction)
            if staticConstruction and staticConstruction['persistentId'] == buildingName:
                bathIds.append(constructionId)

        if len(bathIds) > 1:
            maxLevel = 0
            bathToStay = bathIds[0]
            for constructionId in bathIds:
                construction = md.getConstructionByID(constructionId)
                if construction.Level >= maxLevel:
                    bathToStay = constructionId
                    maxLevel = construction.Level

            for constructionId in bathIds:
                if constructionId != bathToStay:
                    construction = md.getConstructionByID(constructionId)
                    staticConstruction = acc.SD.getStaticConstruction(construction)
                    price = acc.SD.getBuildingPrice(staticConstruction, construction.Level)
                    md.Buildings.remove( construction )
                    md.Pocket.remove( construction )
                    md.sell( price, None, False )
        return md, acc.db