from base.helpers import *
from enums import *

class SwapTavernQuests:
	def convertModelData( self, env, acc, md, dict ): 
		try:
			for constructionId in md.ConstructionsKeeper:
				construction = md.getConstructionByID( constructionId )
				staticBuilding = acc.SD.getStaticConstruction( construction )
				if staticBuilding and staticBuilding['classType'] == "Tavern":
					if construction.BuildingQuest.Level == 14:
						construction.BuildingQuest.Level = 22
					elif construction.BuildingQuest.Level == 19:
						construction.BuildingQuest.Level = 23
					elif construction.BuildingQuest.Level == 22:
						construction.BuildingQuest.Level = 14
					elif construction.BuildingQuest.Level == 23:
						construction.BuildingQuest.Level = 19
					elif construction.BuildingQuest.Level == 29:
						construction.BuildingQuest.Level = 36
					elif construction.BuildingQuest.Level == 34:
						construction.BuildingQuest.Level = 37
					elif construction.BuildingQuest.Level == 36:
						construction.BuildingQuest.Level = 29
					elif construction.BuildingQuest.Level == 37:
						construction.BuildingQuest.Level = 34
		except:
			pass
		return md, acc.db