from base.helpers import *
from datetime import datetime

class ShiftTimeToUTC:
    def convertModelData( self, env, acc, md, dict ):
        return md, acc.db
