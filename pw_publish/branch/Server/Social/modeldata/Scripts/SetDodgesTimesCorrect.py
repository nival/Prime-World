import time

class SetDodgesTimesCorrect:
    def convertModelData( self, env, acc, md, dict ): 
        if not hasattr( md.LordInfo, "lastDodgesUpdateTime_" ) or not md.LordInfo.lastDodgesUpdateTime_:
            md.LordInfo.lastDodgesUpdateTime_ = time.time()
        return md, acc.db