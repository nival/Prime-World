import sys
sys.path.append('../')
from logic.buy_premium_account import *
import time
sys.path.append('../..')
from enums import *

class buy_premium_account_test( ):

  def buy_premium_account_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_PRICE

    assert modeldata.LordInfo.PremiumAccountStart == 0
    assert modeldata.LordInfo.PremiumAccountEnd == 0

    requests = [ ( Buy_premium_account, BuyPremiumAccountRequest( modeldata, { "type" : ['0'] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Gold == 0
    assert modeldata.LordInfo.PremiumAccountEnd - modeldata.LordInfo.PremiumAccountStart ==  env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_DURATION
    assert modeldata.IsPremiumAccount()

  def buy_premium_account_no_money_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_PRICE - 1

    assert modeldata.LordInfo.PremiumAccountStart == 0
    assert modeldata.LordInfo.PremiumAccountEnd == 0

    requests = [ ( Buy_premium_account, BuyPremiumAccountRequest( modeldata, { "type" : ['0'] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Gold == env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_PRICE - 1
    assert modeldata.LordInfo.PremiumAccountStart == 0
    assert modeldata.LordInfo.PremiumAccountEnd == 0    
    assert not modeldata.IsPremiumAccount()

  def extend_premium_account_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_PRICE

    modeldata.LordInfo.PremiumAccountStart = time.time()
    modeldata.LordInfo.PremiumAccountEnd = modeldata.LordInfo.PremiumAccountStart + 3600

    requests = [ ( Buy_premium_account, BuyPremiumAccountRequest( modeldata, { "type" : ['0'] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Gold == 0
    assert modeldata.LordInfo.PremiumAccountEnd - modeldata.LordInfo.PremiumAccountStart == 3600 + env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_DURATION
    assert modeldata.IsPremiumAccount()

  def buy_premium_account_type2_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_PRICE2

    assert modeldata.LordInfo.PremiumAccountStart == 0
    assert modeldata.LordInfo.PremiumAccountEnd == 0

    requests = [ ( Buy_premium_account, BuyPremiumAccountRequest( modeldata, { "type" : ['1'] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Gold == 0
    assert modeldata.LordInfo.PremiumAccountEnd - modeldata.LordInfo.PremiumAccountStart ==  env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_DURATION2
    assert modeldata.IsPremiumAccount()

  def extend_premium_account_type2_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_PRICE2

    modeldata.LordInfo.PremiumAccountStart = time.time()
    modeldata.LordInfo.PremiumAccountEnd = modeldata.LordInfo.PremiumAccountStart + 3600

    requests = [ ( Buy_premium_account, BuyPremiumAccountRequest( modeldata, { "type" : ['1'] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Gold == 0
    assert modeldata.LordInfo.PremiumAccountEnd - modeldata.LordInfo.PremiumAccountStart == 3600 + env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_DURATION2
    assert modeldata.IsPremiumAccount()


  def buy_premium_account_type3_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_PRICE3

    assert modeldata.LordInfo.PremiumAccountStart == 0
    assert modeldata.LordInfo.PremiumAccountEnd == 0

    requests = [ ( Buy_premium_account, BuyPremiumAccountRequest( modeldata, { "type" : ['2'] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Gold == 0
    assert modeldata.LordInfo.PremiumAccountEnd - modeldata.LordInfo.PremiumAccountStart ==  env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_DURATION3
    assert modeldata.IsPremiumAccount()


  def extend_premium_account_type3_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Gold = env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_PRICE3

    modeldata.LordInfo.PremiumAccountStart = time.time()
    modeldata.LordInfo.PremiumAccountEnd = modeldata.LordInfo.PremiumAccountStart + 3600

    requests = [ ( Buy_premium_account, BuyPremiumAccountRequest( modeldata, { "type" : ['2'] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Gold == 0
    assert modeldata.LordInfo.PremiumAccountEnd - modeldata.LordInfo.PremiumAccountStart == 3600 + env.I.Config.getConfig( env.acc.userlocale ).PREMIUM_ACCOUNT_DURATION3
    assert modeldata.IsPremiumAccount()
