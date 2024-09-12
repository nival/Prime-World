# -*- coding: utf-8 -*-
# this file is to be loaded through execfile() called from some config class' method
# so `self.` refers to the loader method's object

##----------------------------------------------------------------------------------------------------------------------
## блок оверрайдов для StaticData 
# self.overrideData( "/GuildLevels.GUILDLEVELS:84C1022C-3D64-482D-A131-8B95D11BF0DA::cycle.percents.Item.[2]", "2" )
# self.overrideData( "/GuildLevels.GUILDLEVELS:84C1022C-3D64-482D-A131-8B95D11BF0DA::cycle.priceToStart.Silver", "123" )

# self.overrideData( "/GuildLevels.GUILDLEVELS:84C1022C-3D64-482D-A131-8B95D11BF0DA::BAD.priceToStart.Silver", "123" ) #DEBUG: BAD index
# self.overrideData( "/GuildLevels.GUILDLEVELS:84C1022C-3D64-482D-A131-8B95D11BF0DA::cycle.percents.Item.[BAD]", "2" ) #DEBUG: BAD index
# self.overrideData( "/GuildLevels.GUILDLEVELS:84C1022C-3D64-482D-A131-8B95D11BF0DA::cycle.percents.Item.[2]", "aDFADGHAFBSGJ" ) #DEBUG: BAD VALUE (should assign as string)

self.overrideData("/Social.ROOT::ClanWarsData.guildWarEventData.duration", "1")