from base.helpers import *

class FixGuildBonus:
	def convertModelData( self, env, acc, md, dict ): 
		#md.validateGuildBonus(acc, env.I)		
		#if acc.guilddata:
			#guildLevel =acc.SD.getGuildLevel(acc.guilddata.GuildLevelInfo.Experience)
			#if guildLevel >= 0:
				#building = md.getGuildBuilding( acc.SD )
				#if building and building.Level >0:					
					#if guildLevel < building.Level:    						
						#info( "FixGuildBonus: change guildBuilding level from %d to %d" % (building.Level, guildLevel) )
						#building.Level = guildLevel
						#if guildLevel == 0:
							#building.emptyAndStopBuilding( md, env.I, acc )
						#md.resetGuildBonus()
						#building.getGuildBonusFull(acc, env.I) 	
						#return md, acc.db
		#heroStats = 0
		#for heroId in md.Heroes:
			#hero = md.getHeroByID( heroId )		
			#if hero:
				#heroStats += hero.GuildStats.Strength 
				#heroStats += hero.GuildStats.Intellect 
				#heroStats += hero.GuildStats.Agility
				#heroStats += hero.GuildStats.Cunning 
				#heroStats += hero.GuildStats.Fortitude
				#heroStats += hero.GuildStats.Will
				#heroStats += hero.GuildStats.Health
				#heroStats += hero.GuildStats.Mana
				#heroStats += hero.GuildStats.StatPoints    
			#break
		#guildStatpoints  = 0
		#guildLevel = md.getGuildBuildingLevel( acc.SD )
		#if guildLevel >= 0:
			#for lvl in xrange( 0, guildLevel + 1 ):
				#guildStatpoints += acc.SD.getGuildStatPointsBonus( lvl )
		#if heroStats != guildStatpoints:
			#info( "FixGuildBonus: change stat points from %d to %d" % (heroStats, guildStatpoints) )
			#md.resetGuildBonus()
			#if guildLevel >= 0:
				#building = md.getGuildBuilding( acc.SD )
				#if building:
					#building.getGuildBonusFull(acc, env.I) 	
		return md, acc.db