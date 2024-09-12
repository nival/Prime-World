import sys
from binascii import crc32
import fnmatch
import os
import shutil
import string
import json
realpath = os.path.dirname( __file__ )
sys.path.append(os.path.join(realpath, '../..'))
sys.path.append(os.path.join(realpath, '../../base'))
sys.path.append(os.path.join(realpath, '../../cfg'))
from guild.GuildData import GuildData
from helpers import *


if os.path.isdir( "./guilds" ):
  auidToGuildAuidMap = {}

  for root, dirnames, filenames in os.walk( "./guilds" ):
    for filename in fnmatch.filter(filenames, '*.json'):
      logFileName = os.path.join( root, filename )
      auidStr = string.split(os.path.splitext( filename )[0], "_" )[1]
      guildauid = long(auidStr)

      with open(logFileName) as f:
        data_str = f.read()
      data = json_loads( data_str )

      guilddata = GuildData()
      guilddata.load( data["data"] )
      guilddata.init( changeWriter=None )
      assert guilddata.GuildAuid == guildauid

      for memberId in guilddata.GuildMemberKeeper:
        member = guilddata.getGuildMemberByID( memberId )
        memberAuid = member.Person
        auidToGuildAuidMap[memberAuid] = guildauid
      
  with open('data.json', 'w') as outfile:  
    json.dump(auidToGuildAuidMap, outfile)

else:
  print "guilds directory not found!"

