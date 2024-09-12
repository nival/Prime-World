
class StatisticsStartedSessionsFix:
    def convertModelData( self, env, acc, md, dict ): 
        md.Statistics.SessionsStarted = 1
        return md, acc.db