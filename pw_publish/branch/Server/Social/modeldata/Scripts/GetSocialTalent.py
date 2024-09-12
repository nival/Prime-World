from base.helpers import *

class GetSocialTalent:
    def convertModelData( self, env, acc, md, dict ): 
        info("GetSocialTalent: acc.sn_count=%s" % acc.sn_count)
        if acc.sn_count > 0:
            md.giveBonusTalent( acc.sn_count, [], acc.getConfig(), acc, env.I )
        return md, acc.db