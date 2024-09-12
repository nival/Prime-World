# coding: utf8


import sys

sys.path.append('tornado')
sys.path.append('cfg')
sys.path.append('base')
sys.path.append('.')

import tornadoredis
import tornado
from tornado.ioloop import IOLoop
import coord_cfg
from helpers import * 
import functools
from ifactory import IfaceFactory
import isql

c = tornadoredis.Client( io_loop=tornado.ioloop.IOLoop.instance(), host=coord_cfg.COORDINATOR_REDIS_CONFIG["redis_addr"], port=coord_cfg.COORDINATOR_REDIS_CONFIG["redis_port"] )
c.connect()


m = IfaceFactory.makeIDataInterface("mongo", coord_cfg.COORDINATOR_MONGO_CONFIG, isql.ISql(), num_threads=coord_cfg.COORDINATOR_MONGO_THREADS) 

guilds_fin = 0
steam_fin = 0

def test_data_redis():
    def cb(i, response): pass

    for i in range(1000):
        c.zadd('guildRatings', i*45545643, i, callback=functools.partial(cb, i))
    c.incr('steamOrder', callback=cb)

def log(m):
    sys.stdout.write("{0}\r\n".format(m))
    sys.stdout.flush()
   

def guilds():

    def cb(response):
        global guilds_fin
        max_entry = len(response) - 1

        if response == []:
            guilds_fin = 1

        log("guilds: received response from redis: {0}".format(str(response)))

        def cb(i, response):
            global guilds_fin
            log("guilds: received response #{0}".format(i))

            if i == max_entry:
               guilds_fin = 1

        for i, (auid, rating) in enumerate(response):
            log("guilds: sent query #{2} for auid: {0}, rating: {1}".format(auid, rating, i))
            m.update('guilds', 'guilds', {"key": auid} , {"data.guildAllDaysRating": rating}, callback=functools.partial(cb, i))

    c.zrange('guildRatings', 0, -1, True, cb)
    
def steam():
    def cb(response):
        log("steam: received response from redis")
        def cb(response):
            log("steam: received response from mongo")
            global steam_fin
            steam_fin = 1
        m.update("counters", "counters", {"name": "steamOrder"}, {"ammount": int(response or 0)}, callback=cb)
    c.get("steamOrder", cb)

def progress():
    global steam_fin
    global guilds_fin

    if steam_fin and guilds_fin:

        sys.stdout.write(" OK\n")
        sys.stdout.flush()
        IOLoop.instance().stop()
    else:
        sys.stdout.write(".")
        sys.stdout.flush()

log("Start")
tornado.ioloop.PeriodicCallback(progress, 100).start()
guilds()
steam()

IOLoop.instance().start()
