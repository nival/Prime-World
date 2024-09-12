import sys
sys.path.append('../')
sys.path.append('../..')
from logic.buy_tournament_ticket import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class buy_tournament_ticket_test:

  def buy_tournament_ticket_gold_test( self, env ):
    modeldata = env.acc.model
    amount = 100500

    gold = amount
    modeldata.Resources.Gold = amount
    config = env.I.Config.getConfig( env.acc.userlocale )
    config.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyTournamentTicketEvent" )
    modeldata.TournamentInfo.TournamentState = TournamentState.TicketSale

    requests = [ ( Buy_tournament_ticket, BuyTournamentTicketRequest( modeldata, { "paymentType" : [TicketPaymentType.Gold]}, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Gold == gold - config.TournamentSettings.GOLDEN_TICKET_PRICE

    assert modeldata.TournamentInfo.TournamentTicket.UserAuid == env.acc.auid
    assert modeldata.TournamentInfo.TournamentTicket.TicketId == "Tournament1"
    assert modeldata.TournamentInfo.TournamentTicket.State == TicketState.InTournament
    assert modeldata.TournamentInfo.TournamentTicket.TicketBoughtType == TicketBoughtType.BoughtForGold
    assert "tournament0_ticket_dlc" in env.acc.db.dlcs

  def buy_tournament_ticket_fail_no_gold_test( self, env ):
    modeldata = env.acc.model

    config = env.I.Config.getConfig( env.acc.userlocale )
    config.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyTournamentTicketEvent" )
    modeldata.TournamentInfo.TournamentState = TournamentState.TicketSale

    requests = [ ( Buy_tournament_ticket, BuyTournamentTicketRequest( modeldata, { "paymentType" : [TicketPaymentType.Gold]}, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Gold == 0

    assert modeldata.TournamentInfo.TournamentTicket.UserAuid != env.acc.auid
    assert modeldata.TournamentInfo.TournamentTicket.TicketId != "Tournament1"
    assert modeldata.TournamentInfo.TournamentTicket.State == TicketState.NotActivated
    assert modeldata.TournamentInfo.TournamentTicket.TicketBoughtType == TicketBoughtType.BoughtForGold
    assert "tournament0_ticket_dlc" not in env.acc.db.dlcs

  def buy_tournament_ticket_fail_no_silver_test( self, env ):
    modeldata = env.acc.model

    config = env.I.Config.getConfig( env.acc.userlocale )
    config.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyTournamentTicketEvent" )
    modeldata.TournamentInfo.TournamentState = TournamentState.TicketSale
    modeldata.Resources.Silver = 0

    requests = [ ( Buy_tournament_ticket, BuyTournamentTicketRequest( modeldata, { "paymentType" : [TicketPaymentType.Silver]}, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Silver == 0

    assert modeldata.TournamentInfo.TournamentTicket.UserAuid != env.acc.auid
    assert modeldata.TournamentInfo.TournamentTicket.TicketId != "Tournament1"
    assert modeldata.TournamentInfo.TournamentTicket.State == TicketState.NotActivated
    assert "tournament0_ticket_dlc" not in env.acc.db.dlcs

  def buy_tournament_ticket_silver_test( self, env ):
    modeldata = env.acc.model
    config = env.I.Config.getConfig( env.acc.userlocale )
    amount = config.TournamentSettings.SILVER_TICKET_PRICE + 1

    silver = amount
    modeldata.Resources.Silver = amount
    config.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyTournamentTicketEvent" )
    modeldata.TournamentInfo.TournamentState = TournamentState.TicketSale

    requests = [ ( Buy_tournament_ticket, BuyTournamentTicketRequest( modeldata, { "paymentType" : [TicketPaymentType.Silver]}, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Silver == silver - config.TournamentSettings.SILVER_TICKET_PRICE
    assert modeldata.TournamentInfo.TournamentTicket.UserAuid == env.acc.auid
    assert modeldata.TournamentInfo.TournamentTicket.TicketId == "Tournament1"
    assert modeldata.TournamentInfo.TournamentTicket.State == TicketState.InTournament
    assert modeldata.TournamentInfo.TournamentTicket.TicketBoughtType == TicketBoughtType.BoughtForSilver
    assert "tournament0_ticket_dlc" in env.acc.db.dlcs


  def buy_tournament_ticket_for_real_money( self, env ):
    modeldata = env.acc.model
    config = env.I.Config.getConfig( env.acc.userlocale )
    amount = config.TournamentSettings.INSTANT_PAYMENT_SIZE
    config.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyTournamentTicketEvent" )
    modeldata.TournamentInfo.TournamentState = TournamentState.TicketSale

    assert modeldata.Resources.Gold == 0

    modeldata.registerPayment( env.acc, env.I, amount, "KIWI", 1 )

    assert modeldata.TournamentInfo.TournamentTicket.UserAuid == env.acc.auid
    assert modeldata.TournamentInfo.TournamentTicket.TicketId == "Tournament1"
    assert modeldata.TournamentInfo.TournamentTicket.State == TicketState.InTournament
    assert modeldata.TournamentInfo.TournamentTicket.TicketBoughtType == TicketBoughtType.GiftedWithPayment
    assert "tournament0_ticket_dlc" in env.acc.db.dlcs

  def buy_tournament_ticket_fail_action_expired_test( self, env ):
    modeldata = env.acc.model

    config = env.I.Config.getConfig( env.acc.userlocale )
    if "/UI/Content/MarketingEvents/BuyTournamentTicketEvent" in config.MARKETING_EVENTS:
      config.MARKETING_EVENTS.remove( "/UI/Content/MarketingEvents/BuyTournamentTicketEvent" )

    modeldata.TournamentInfo.TournamentState = TournamentState.TicketSale
    modeldata.Resources.Silver = config.TournamentSettings.SILVER_TICKET_PRICE

    requests = [ ( Buy_tournament_ticket, BuyTournamentTicketRequest( modeldata, { "paymentType" : [TicketPaymentType.Silver]}, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Silver == config.TournamentSettings.SILVER_TICKET_PRICE
    assert modeldata.TournamentInfo.TournamentTicket.UserAuid != env.acc.auid
    assert modeldata.TournamentInfo.TournamentTicket.TicketId != "Tournament1"
    assert modeldata.TournamentInfo.TournamentTicket.State == TicketState.NotActivated
    assert "tournament0_ticket_dlc" not in env.acc.db.dlcs

  def buy_tournament_ticket_fail_wrong_tournament_state_test( self, env ):
    modeldata = env.acc.model

    config = env.I.Config.getConfig( env.acc.userlocale )
    config.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyTournamentTicketEvent" )
    modeldata.TournamentInfo.TournamentState = TournamentState.InProgress
    modeldata.Resources.Silver = config.TournamentSettings.SILVER_TICKET_PRICE

    requests = [ ( Buy_tournament_ticket, BuyTournamentTicketRequest( modeldata, { "paymentType" : [TicketPaymentType.Silver]}, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Silver == config.TournamentSettings.SILVER_TICKET_PRICE

    assert modeldata.TournamentInfo.TournamentTicket.UserAuid != env.acc.auid
    assert modeldata.TournamentInfo.TournamentTicket.TicketId != "Tournament1"
    assert modeldata.TournamentInfo.TournamentTicket.State == TicketState.NotActivated
    assert "tournament0_ticket_dlc" not in env.acc.db.dlcs


  def create_tournament_modeldata_test( self, env ):
    env.I.Config.getMainConfig().TournamentSettings.IS_TOURNAMENT_SERVER = True
    env.I.MD.newModel( env.acc, env.I, "1.2.3", random_heroes=-1, random_items=-1, fraction=env.acc.db.fraction, db = env.acc.db, guest = env.acc.guest, old_md = None )
    modeldata = env.acc.model

    assert modeldata.Resources.Silver == 1000000
    assert modeldata.Resources.Perl == 1000000
    assert modeldata.Resources.Resource1 == 0
    assert modeldata.Resources.Resource1 == 0
    assert modeldata.Resources.Resource1 == 0

    assert len(modeldata.ItemsKeeper) > 100
    assert len(modeldata.HeroesKeeper) > 2
    assert modeldata.LordInfo.Fame == env.acc.SD.data['LevelToFameTable']['Levels']['Item'][-1]
