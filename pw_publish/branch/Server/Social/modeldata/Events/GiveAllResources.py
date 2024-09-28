from base.helpers import *
from binascii import crc32

class GiveAllResources:
  def convertModelData( self, acc, sd, config, stats ):
    acc.model.Resources.Resource1 = 1000000
    acc.model.Resources.Resource2 = 1000000
    acc.model.Resources.Resource3 = 1000000
    acc.model.Resources.Silver = 1000000
    acc.model.Resources.Perl = 1000000
    acc.model.Resources.RedPerl = 1000000

    return acc.model    
