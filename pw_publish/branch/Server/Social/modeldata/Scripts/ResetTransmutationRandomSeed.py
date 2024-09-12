class ResetTransmutationRandomSeed:
    def convertModelData( self, env, acc, md, dict ): 
        md.setTransmutationRandomSeed( env.I.Config.GoodSeeds )
        return md, acc.db