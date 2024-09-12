from logic.add_statistic import *
from binascii import crc32
from base.helpers import *
sys.path.append('../')
sys.path.append('../..')
from enums import *

class add_statistic_test:

  def add_statistic_test( self, env ):
    modeldata = env.acc.model
    id = modeldata.next_uid_ + 1
    value = 100500
    assert len(modeldata.StatisticEvents) == 0
        
    requests = [ ( Add_statistic, AddStatisticRequest( modeldata, { "actionType" : [StatisticEventType.SESSION_RESOURCE] , "description" : ['test'], "value" : [value]}, False ) ) ]
    changeList = env.execActions( requests )
    
    assert len(modeldata.StatisticEvents) == 1
    
    statisticEvent = modeldata.getStatisticEventByID( id )
    assert statisticEvent.actionType == StatisticEventType.SESSION_RESOURCE
    assert statisticEvent.description == 'test'
    assert statisticEvent.value == value
    
  def add_statistic_nullstring_test( self, env ):
    modeldata = env.acc.model
    id = modeldata.next_uid_ + 1
    value = 100500
    assert len(modeldata.StatisticEvents) == 0
        
    requests = [ ( Add_statistic, AddStatisticRequest( modeldata, { "actionType" : [StatisticEventType.SESSION_RESOURCE] , "description" : [''], "value" : [value]}, False ) ) ]
    changeList = env.execActions( requests )
    
    assert len(modeldata.StatisticEvents) == 1
    
    statisticEvent = modeldata.getStatisticEventByID( id )
    assert statisticEvent.actionType == StatisticEventType.SESSION_RESOURCE
    assert statisticEvent.description == ''
    assert statisticEvent.value == value

  def add_statistic_missed_string_parameter_test( self, env ):
    modeldata = env.acc.model
    id = modeldata.next_uid_ + 1
    value = 100500
    assert len(modeldata.StatisticEvents) == 0
        
    requests = [ ( Add_statistic, AddStatisticRequest( modeldata, { "actionType" : [StatisticEventType.SESSION_RESOURCE] ,  "value" : [value]}, False ) ) ]
    changeList = env.execActions( requests )
    
    assert len(modeldata.StatisticEvents) == 1
    
    statisticEvent = modeldata.getStatisticEventByID( id )
    assert statisticEvent.actionType == StatisticEventType.SESSION_RESOURCE
    assert statisticEvent.description == ''
    assert statisticEvent.value == value
    
    
    
    