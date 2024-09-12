from base.helpers import *

class MoveFieldsToLordInfo:
    def convertModelData( self, env, acc, md, dict ):
        try:
            md.LordInfo.Fame = dict["ModelData"]["Fame"]
        except KeyError:
            pass

        try:
            md.LordInfo.Reliability = dict["ModelData"]["Reliability"]
        except KeyError:
            pass

        try:
            md.LordInfo.LevelOfExpansion = dict["ModelData"]["LevelOfExpansion"]
        except KeyError:
            pass

        return md, acc.db