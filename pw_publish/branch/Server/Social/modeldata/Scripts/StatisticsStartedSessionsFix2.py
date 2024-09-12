
class StatisticsStartedSessionsFix2:
    def convertModelData( self, env, acc, md, dict ): 
        if md.Statistics.SessionsStarted == 0:
            md.Statistics.SessionsStarted = 1
        return md, acc.db