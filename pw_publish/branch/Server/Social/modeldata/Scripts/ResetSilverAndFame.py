class ResetSilverAndFame:
    def convertModelData( self, env, acc, md, dict ): 
        md.Resources.Silver = 0
        md.LordInfo.Fame = 0
        return md, acc.db