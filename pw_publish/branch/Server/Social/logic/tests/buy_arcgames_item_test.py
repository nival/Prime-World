import sys
sys.path.append('../')
sys.path.append('../..')
sys.path.append('../../cfg')

from logic.buy_arcgames_item import Buy_arcgames_item
from logic.requests.BuyArcGamesItemRequest import BuyArcGamesItemRequest
from logic.requests.KeepaliveRequest import KeepaliveRequest
from logic.keepalive import Keepalive
from base.helpers import *
from enums import *
import EC
import iarcgames
import coord_cfg as cfg
import pwconst
import time

class buy_arcgames_item_test:

  def buy_arcgames_item_test(self, env):
    modeldata = env.acc.model
    ARCGAMES = iarcgames.IRealArcGames(cfg.COORDINATOR_ARCGAMES_APPID,
                                       cfg.COORDINATOR_ARCGAMES_APPABBR,
                                       cfg.COORDINATOR_ARCGAMES_APP_SECRET,
                                       cfg.COORDINATOR_ARCGAMES_URL,
                                       cfg.COORDINATOR_ARCGAMES_BILLING_URL,
                                       cfg.COORDINATOR_ARCGAMES_ZONEID,
                                       cfg.COORDINATOR_ARCGAMES_IS_TEST,
                                       env.I.HTTP, env.I.AGG)
    #ARCGAMES_PS = IfaceFactory.makeArcGamesPaymentsInterface( 'real', env.I.HTTP, cfg.ARCGAMES_PAYMENTS_URL, cfg.ARCGAMES_PAYMENTS_SECRET )
    env.I.ARCGAMES = ARCGAMES
    #env.I.ARCGAMES = ARCGAMES_PS
    env.acc.snid='arc'
    env.acc.db.arcgamesTransaction = 0
    env.acc.db.arcgamesOrders = {}
    env.acc.arcgames = env.I.ARCGAMES.attachTo(env.acc.auid, env.acc.snid)


    gold = modeldata.Resources.Gold = 300

    requests =  [ ( Buy_arcgames_item, BuyArcGamesItemRequest( modeldata, { "itemId" : [ 1 ] }, False ) ) ]
    changeList = env.execActions( requests )
    pwconst.KEEPALIVE_TIMINGS.updateGold = 1
    requests =  [ ( Keepalive, KeepaliveRequest( modeldata, { "itemId" : [ 1 ] }, False ) ) ]
    changeList = env.execActions( requests )

