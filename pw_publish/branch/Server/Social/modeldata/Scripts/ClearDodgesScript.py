from base.helpers import *

class ClearDodgesScript:
    def convertModelData( self, env, acc, md, dict ): 
        info("ClearDodgesScript: auid=%r" % acc.db.auid)
        md.clearDodges()
        return md, acc.db