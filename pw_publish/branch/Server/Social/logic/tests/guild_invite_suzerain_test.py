import sys
sys.path.append('../')
sys.path.append('../..')
from logic.guild_invite_suzerain import *
from logic.guild_create import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class guild_invite_suzerain_test:

  def guild_invite_suzerain_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Silver = silver = 1000000
    modeldata.Resources.Gold = gold = 1000
    requests =  [ ( Guild_create, GuildCreateRequest( modeldata, { "fullname" : ['MyGuild'], "shortname" : ['MyGuild'] }, False ) ) ]
    changeList = env.execActions( requests )

    requests =  [ ( Guild_invite_suzerain, GuildInviteSuzerainRequest ( modeldata, { "person_uid" : [2], "guildId" : [2] }, False ) ) ]
    changeList = env.execActions( requests )


