import time

class ChangeHeroesBuildingLevel:
	def convertModelData( self, env, acc, md, dict ): 
		needRecalc = False
		for buildingId in md.Buildings.keys():
			building = md.getConstructionByID(buildingId)
			staticBuilding = acc.SD.getStaticConstruction( building )
			if staticBuilding and staticBuilding['classType'] == "HeroesBuilding":
				if building.Level <= 4:
					needRecalc = True
					md.Pocket.add( building )
					md.Buildings.remove( building )	
		if needRecalc:
			md.recalcPopulation( acc.SD, acc.guest )
		for buildingId in md.Pocket:
			building = md.getConstructionByID(buildingId)
			staticBuilding = acc.SD.getStaticConstruction( building )
			if staticBuilding and staticBuilding['classType'] == "HeroesBuilding":
				if building.Level <= 4:
					building.Level = ((building.Level +1)*4)-1
		return md, acc.db