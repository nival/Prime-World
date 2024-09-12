from base.helpers import *
from enums import *

class MoveTalentInBuilding:
	def convertModelData( self, env, acc, md, dict ): 
		for constructionId in md.ConstructionsKeeper:
			construction = md.getConstructionByID( constructionId )
			try:				
				temp = dict["ModelData"]["ConstructionsKeeper"]["Keeper"][str(construction.id)]["Construction"]["TalentsInBuilding"]["Collection"]
				if temp:
					keys = temp.keys()
					if len(keys) > 0 and not temp.get(keys[0]): #perls
						if construction.ProductionState == ProductionState.Busy:
							info( "Set ProductionCustomValue to '%s' within construction '%s'" % (len(keys),  constructionId) )
							construction.ProductionCustomValue = len(keys)							
						elif construction.ProductionState == ProductionState.Idle:
							info( "Sell '%s' perls within construction '%s'" % (len(keys),  constructionId) )
							price = md.createResourcesTable( Perl = len(keys) )		
							md.sell( price, acc )
					else:
						construction.ProductionCustomValue = len(keys)	
						for key in keys:
							talentId = temp.get(key)
							if talentId:
								talent = md.getTalentByID(talentId)
								if talent:
									info( "Move talent id '%s' PersistentId '%s' within construction '%s'" % (talentId, talent.PersistentId, constructionId) )
									construction.CraftedTalents.append(talent.PersistentId)									
									talent.decRef()
									md.ItemsKeeper.remove(talentId)
			except:
				pass
		return md, acc.db
