from base.helpers import *
import datetime, time
from enums import MapType

class EventMap:

  def __repr__( self ):
    if self.isFullDate:
      return str(self.startTime)+"   "+str(self.endTime)+"   "+self.map+"   "+str(self.mapType)
    return str(self.startHour)+":"+str(self.startMin)+"   "+str(self.endHour)+":"+str(self.endMin)+"   "+self.map+"   "+str(self.mapType)


  def isActual( self ):
    if not self.isValid:
      return False
    
    if self.isFullDate:
      now = int(round(time.time()))
      return now > self.startTime and now < self.endTime
    
    curTime = datetime.datetime.now() 
    curHour = curTime.hour
    curMin = curTime.minute
    curDay = curTime.strftime( "%a" ).lower()
    
    if self.weekDay != curDay and self.weekDay != "all":
      return False

    if self.startHour < curHour and self.endHour > curHour:
      return True
    if self.startHour == curHour and self.endHour > curHour:
      return self.startMin <= curMin
    if self.startHour < curHour and self.endHour == curHour:
      return self.endMin >= curMin
    if self.startHour == curHour and self.endHour == curHour:
      return self.endMin >= curMin and self.startMin <= curMin

    return False


  def calcShift( self, timestamp, hours, mins, addDay ):
    resultTimeStamp = timestamp
    if addDay:
      resultTimeStamp += 86400 # add 1 day
    resultTimeStamp += hours*3600 # add hours
    resultTimeStamp += mins*60 # add minutes
    return resultTimeStamp


  def getStartTime( self ):
    if self.isFullDate:
      return self.startTime      
      
    curTime = datetime.datetime.now()     
    curDay = curTime.strftime( "%a" ).lower()  
    curTime = curTime.replace(hour=self.startHour, minute = self.startMin, second=0, microsecond=0)
    
    timestamp = int(round(time.mktime(curTime.timetuple())))
    
    if self.weekDay != curDay and self.weekDay != "all":
      timestamp += 86400 # add 1 day
    
    return timestamp


  def getEndTime( self ):
    if self.isFullDate:
      return self.endTime       
    
    curTime = datetime.datetime.now()     
    curDay = curTime.strftime( "%a" ).lower()  
    curTime = curTime.replace(hour=self.endHour, minute = self.endMin, second=0, microsecond=0)
    
    timestamp = int(round(time.mktime(curTime.timetuple())))
    
    if self.weekDay != curDay and self.weekDay != "all":
      timestamp += 86400 # add 1 day
    
    return timestamp    

  def __init__( self, event ):
    self.isValid = False
    self.isForBan = False
    
    #week_day
    weekDay = event["newValue"]["day"].lower()
    if len( weekDay ) != 3:
      print ( "Bad line format(week_day), skip: %r" % event["newValue"]["day"] )
      return
        
    #start_date
    startTime = event["newValue"]["startHour"]
    try:
      startTimeHour = int(startTime.split(":")[0])
      startTimeMin = int(startTime.split(":")[1])
    except:
      print ( "Bad line format(start_date->parsing), skip: %r" % event["newValue"]["startHour"] )
      return
  
    #end_date
    endTime = event["newValue"]["endHour"]
    try:
      endTimeHour = int(endTime.split(":")[0])
      endTimeMin = int(endTime.split(":")[1])
    except:
      print ( "Bad line format(end_date->parsing), skip: %r" % event["newValue"]["endHour"] )
      return
    
    #map_type
    if event["newValue"]["mapType"] == -1:
      mapType = MapType.CTF 
    else:
      mapType = event["newValue"]["mapType"].upper().strip()
      if mapType == "CTF":
        mapType = MapType.CTF
      elif mapType == "PVP":
        mapType = MapType.PVP
      elif mapType == "":
        self.isForBan = True
        mapType = MapType.Tutorial
      else:
        print ( "Bad line format(map_type), skip: %r" % event["newValue"]["mapType"] )
        return
    
    if self.isForBan and (event["newValue"]["mapEnabled"] or event["newValue"]["mapDbid"] == ""):
      return    
    if startTimeHour > endTimeHour:
      return
    if event["startTime"] > event["endTime"] or event["endTime"] < int(round(time.time())):
      print ( "Not actual eventMap, skip: %r" % event )
      return      

    self.id = event["persistentId"]
    self.weekDay = weekDay
    self.startHour = startTimeHour
    self.startMin = startTimeMin
    self.endHour = endTimeHour
    self.endMin = endTimeMin
    self.startTime = event["startTime"]
    self.endTime = event["endTime"]
    self.map = event["newValue"]["mapDbid"]
    self.isValid = True
    self.mapType = mapType
    self.enabled = event["newValue"]["mapEnabled"]
    self.isFullDate = self.weekDay == "all" and startTimeHour == 0 and startTimeMin == 0 \
                      and endTimeHour == 23 and endTimeMin == 59
