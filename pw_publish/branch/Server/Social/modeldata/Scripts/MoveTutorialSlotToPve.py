from base.helpers import *
from binascii import crc32   # zlib version is not cross-platform
from enums import *

class MoveTutorialSlotToPve:
	def convertModelData( self, env, acc, md, dict ):
		try:
			trainMapInfo = md.LordInfo.MapsByType.get(MapType.Tutorial)
			trainMapDesc = acc.SD.data['DefaultMaps']['Item'][MapType.Tutorial]
			if trainMapInfo and trainMapDesc and trainMapDesc['map']  and 'dbid' in trainMapDesc['map']:		
				if trainMapInfo.MapId != trainMapDesc['map']['dbid']:
					tutId = trainMapInfo.MapId
					tutEnabled = trainMapInfo.Enabled
					info( "Reset training mapInfo to default: mapId '%s'" % trainMapDesc['map']['dbid'] )
					trainMapInfo.MapId = trainMapDesc['map']['dbid']
					trainMapInfo.Enabled = trainMapDesc['enabled']					
					pveMapInfo = md.LordInfo.MapsByType.get(MapType.PVE)
					if pveMapInfo:
						info( "Move tutorial mapInfo to PvE slot: mapId '%s'" % tutId )
						pveMapInfo.MapId = tutId
						pveMapInfo.Enabled = tutEnabled
		except:
			pass  
		return md, acc.db