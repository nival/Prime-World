import time

class SetAllowedLamps:
    def convertModelData( self, env, acc, md, dict ): 
        md.MarketingEventsInfo.LampEventInfo.AllowedLampsGoldStatus = md.MarketingEventsInfo.LampEventInfo.AllowedLamps 
        return md, acc.db