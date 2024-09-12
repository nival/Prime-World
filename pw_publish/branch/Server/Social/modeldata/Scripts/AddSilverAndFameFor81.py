class AddSilverAndFameFor81:
    def convertModelData( self, env, acc, md, dict ): 
        md.Resources.Silver += 325000
        md.LordInfo.Fame += 40500
        return md, acc.db