import time

class SetFameUpdateTime:
    def convertModelData( self, env, acc, md, dict ): 
        if not hasattr( md.LordInfo, "lastFameUpdateTime_" ) or not md.LordInfo.lastFameUpdateTime_:
            md.LordInfo.lastFameUpdateTime_ = time.time()
        return md, acc.db