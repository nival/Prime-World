import sys
sys.path.append('../')
from logic.update_tournament_info import *
from binascii import crc32
import time
sys.path.append('../..')
from enums import *
import EC
import cfg

class update_tournament_info_test:
  def add_win( self, env ):
    modeldata = env.acc.model
    time = 100
    cfg.TOURNAMENT_SERVER = True
    requests = [ ( Update_tournament_info, UpdateTournamentInfoRequest( modeldata, { "type": ["win"], "time" : [time] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.TournamentInfo.TournamentTicket.Wins == 1
    assert modeldata.TournamentInfo.TournamentTicket.Losses == 0
    assert modeldata.TournamentInfo.TournamentTicket.LastGameTime != 0
    assert modeldata.TournamentInfo.TournamentTicket.State != TicketState.TournamentLost


  def add_defeat( self, env ):
    modeldata = env.acc.model
    time = 100
    cfg.TOURNAMENT_SERVER = True
    ticketState = modeldata.TournamentInfo.TournamentTicket.State
    requests = [ ( Update_tournament_info, UpdateTournamentInfoRequest( modeldata, { "type": ["defeat"], "time" : [time] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.TournamentInfo.TournamentTicket.Wins == 0
    assert modeldata.TournamentInfo.TournamentTicket.Losses == 1
    assert modeldata.TournamentInfo.TournamentTicket.LastGameTime != 0
    assert modeldata.TournamentInfo.TournamentTicket.State == ticketState

  def add_time_dodge( self, env ):
    modeldata = env.acc.model
    cfg.TOURNAMENT_SERVER = True
    time = 100500

    requests = [ ( Update_tournament_info, UpdateTournamentInfoRequest( modeldata, { "type": ["timeDodge"], "time" : [time] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.TournamentInfo.TournamentTicket.Wins == 0
    assert modeldata.TournamentInfo.TournamentTicket.Losses == 1
    assert modeldata.TournamentInfo.TournamentTicket.LastGameTime == time
    assert modeldata.TournamentInfo.TournamentTicket.State == TicketState.TournamentLost