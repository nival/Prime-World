from base.helpers import *
 	
class RestructurizeFlags:
    def convertModelData( self, env, acc, md, dict ):
        try:
            if "FlagsKeeper" in dict["ModelData"]:     
                for flagId, flag in dict["ModelData"]["FlagsKeeper"]["Keeper"].iteritems():
                    md.Flags.append(flag["OwnedFlag"]["PersistentId"])
                    info("Flag '%s' was converted for user %s", flag["OwnedFlag"]["PersistentId"], acc.db.auid)
        except Exception:
                catch()	

        return md, acc.db
        