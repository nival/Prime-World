import sys
sys.path.append('../')
sys.path.append('../..')
from logic.guild_destroy import *
from binascii import crc32
from base.helpers import *
from enums import *

class guild_destroy_test:

  def guild_destroy_test( self, env ):
    modeldata = env.acc.model
    fullname = "boobs"
    shortname = "O_O"
    modeldata.Resources.Silver = silver = 1000000

    env.acc.db.guildAuid = '314159265'
    
    hero = env.add_hero(modeldata, 'mowgly')
    hero.TalentSets[0].GuildStats.StatPoints = 50
    hero.TalentSets[0].GuildStats.Health = 100

    requests =  [ ( Guild_destroy, GuildDestroyRequest( modeldata, {  }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert env.acc.db.guildAuid == 0
    assert hero.TalentSets[0].GuildStats.StatPoints == 0
    assert hero.TalentSets[0].GuildStats.Health == 0