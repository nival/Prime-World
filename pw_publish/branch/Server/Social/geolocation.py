# -*- coding: utf-8 -*-
import sys, os
from base.helpers import addRelPath

addRelPath("libs") # for geoip
#sys.path.append(os.path.join( os.path.dirname(os.path.abspath(__file__)),"libs"))
import pygeoip

from geo_cfg import EGeoLocation, GEO_LOCATIONS, DEFAULT_GEO_LOCATION, COUNTRY_2_LOC, LONG_LAT_2_LOC

class GeoLocator:

    def __init__(self, path_dat="vendor/pygeoip/data/GeoIPCity.dat"):
        self.geo = pygeoip.GeoIP( path_dat, pygeoip.MMAP_CACHE  )
        
    def getLocationInfoByIP(self, addr ):
        location, aux_info = DEFAULT_GEO_LOCATION, {}
    
        # для начала попробуем найти полный location, с широтой/долготой
        found = False   
        record = self.geo.record_by_name( addr )
        if record:
            longitude = record.get("longitude")
            latitude = record.get("latitude")
            if (longitude is not None) and (latitude is not None):
                # попробуем прикинуть ближайшую локацию чисто по широте-долготе
                for rect in LONG_LAT_2_LOC:
                    if rect.long1 <= longitude and longitude <= rect.long2 and rect.lat1 <= latitude and latitude <= rect.lat2:
                        location = rect.geo
                        found = True
                        break
        
            aux_info = record
        
        if not found:
            # нету record, давайте хоть страну попробуем достать
            try:
                countryCode = self.geo.country_code_by_name( addr )
            except:
                countryCode = None
            
            if countryCode:
                _location = COUNTRY_2_LOC.get(countryCode, None)
                if _location is not None:
                    aux_info = { "country_code": countryCode }
                    location = _location
        
        if location != DEFAULT_GEO_LOCATION and location not in GEO_LOCATIONS:
            location = DEFAULT_GEO_LOCATION
        
        return location, aux_info

def initGeoIP( path_dat="vendor/pygeoip/data/GeoLiteCity.dat" ):
    assert 0

