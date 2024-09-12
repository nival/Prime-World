class ApplyBuildingLimits:
    def convertModelData( self, env, acc, md, dict ): 
        buildingNames = ["House_4","Production_Silver_fromRes1"]
        md.applyBuildingLimits( buildingNames, acc.SD )
        return md, acc.db