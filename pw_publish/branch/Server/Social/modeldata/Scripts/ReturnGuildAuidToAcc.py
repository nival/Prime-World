from base.helpers import *
from binascii import crc32   # zlib version is not cross-platform
from enums import *

class ReturnGuildAuidToAcc:
    def convertModelData( self, env, acc, md, dict ):
        try:
            if str(acc.db.auid) in env.auidToGuildAuidMap:
                acc.db.guildAuid = env.auidToGuildAuidMap[str(acc.db.auid)]
        except:
            catch()  

        return md, acc.db
