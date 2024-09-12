import sys
sys.path.append('../')
sys.path.append('../..')
from logic.get_guild_requests_list import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC
from guild.GuildWarsDataCustom import GuildWarsDataCustom

class get_guild_requests_list_test:

  def get_guild_requests_list_test( self, env ):
    ratingPositionChange = GuildWarsDataCustom.GetRatingPositionChange(10)
    assert ratingPositionChange == RatingPositionChange.Increased