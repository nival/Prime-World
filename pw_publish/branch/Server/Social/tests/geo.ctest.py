# -*- coding: utf-8 -*-
import random
import sys
import os

os.chdir('..')
sys.path.append( os.path.abspath('.') )
sys.path.append( os.path.abspath("libs") )
sys.path.append( os.path.abspath("vendor") )
sys.path.append( os.path.abspath("cfg") )

from base.helpers import *

#~ import pygeoip

#~ geo = pygeoip.GeoIP( "vendor/pygeoip/data/GeoLiteCity.dat", pygeoip.MMAP_CACHE  )

#~ print "localhost city(%s):%s" % ( addr, geo.record_by_addr( addr ) )

#~ country = None
#~ try:
    #~ country = geo.country_code_by_addr( addr )
#~ except:
    #~ pass
#~ print "localhost country:%s" % country

#~ print "my city record(%s):%s" % ( billing_addr, geo.record_by_addr( billing_addr ) )
#~ print "my city record by name(%s):%s" % ( billing_addr, geo.record_by_name( billing_addr ) )

addr = '85.176.148.41'
addr = '82.198.168.98'
billing_addr = addr

#@profile
def main():
    from geolocation import GeoLocator
    
    geo = GeoLocator("vendor/pygeoip/data/GeoIPCity.dat")

    loc, aux_info = geo.getLocationInfoByIP( billing_addr )
    print "location: %s, aux_info: %r (class %s)" % ( loc, aux_info, aux_info.__class__ )

    if isinstance(aux_info, dict):
        country = aux_info.get("country_code", "")
        city = aux_info.get("city", "")
        print "city: %r" % city 
        if city:
            geolocation = "%s,%s" % (country, city)
        else:
            longitude = aux_info.get("longitude", "?")
            latitude = aux_info.get("latitude", "?")
            geolocation = "%s(%s:%s)" % (country, longitude, latitude)
        print "shorthand geolocation: %r" % geolocation 
        utf8_geolocation = utf8convert( unicode(geolocation, "latin1") )
        print "utf8convert geolocation: %r" % utf8_geolocation
        json_geolocation = json_dumps(utf8_geolocation)
        print "json_geolocation: %r" % json_geolocation
        
        uni_geolocation = unicode(geolocation, "latin1")
        print "unicode geolocation: %r" % uni_geolocation
        print "utf8 geolocation: %r" % utf8convert(uni_geolocation)
        print "latin1 geolocation: %r" % uni_geolocation.encode("latin1")
        
        f = open("geo.txt", "wt")
        f.write( uni_geolocation.encode("latin1") )
        
        f.write( "\n" )
        unjson_geolocation = json_loads(json_geolocation)
        f.write( unjson_geolocation.encode("latin1") )


main()

#~ exit(0)

#~ name = 'pw.zzima.com'
#~ print "my country(%s):%s" % ( name, geo.country_code_by_name( addr ) )

#~ for i in xrange(100):
    #~ addr = "%d.%d.%d.%d" % (random.randint(0,255), random.randint(0,255), random.randint(0,255), random.randint(0,255))
    #~ print "----\n city record(%s):%s" % ( addr, geo.record_by_name( addr ) )
    
    #~ try:
        #~ country = geo.country_code_by_name( addr )
    #~ except:
        #~ pass
    #~ print " country(%s):%s" % ( addr, country )
    
    #~ loc, info = getLocationInfoByIP( addr )
    #~ print "location: %s, info: %s" % ( loc, info )
    
    
