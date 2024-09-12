from base.helpers import *
import datetime, time
from binascii import crc32 

class EventSkin:

  def __repr__( self ):
    info = "EventSkin: %r %r " % ( self.startTime, self.endTime )
    return info + self.skin_persistent_id

  def getSkin( self ):
    return crc32(self.skin_persistent_id)

  def isActual( self ):
    if not self.isValid:
      return False

    now = time.time()
    start = time.mktime(self.startTime.timetuple())
    end = time.mktime(self.endTime.timetuple())
    if now >= start and now <= end :
      return True

    return False


  def __init__( self, line ):
    self.isValid = False

    #start_date
    startIdx = line.find( "\"", 0 ) + 1
    endIdx = line.find( "\"", startIdx )
    if endIdx == -1:
      err( "Bad line format(start_date), skip: %r" % line )
      return
    startTime = line[startIdx:endIdx]
    try:
      self.startTime = datetime.datetime.strptime(startTime, "%d.%m.%Y %H:%M")
    except:
      err( "Bad line format(start_date->parsing), skip: %r" % line )
      return

    #end_date
    startIdx = endIdx+3
    endIdx = line.find( "\"", startIdx )
    if endIdx == -1:
      err( "Bad line format(end_date), skip: %r" % line )
      return
    endTime = line[startIdx:endIdx]
    try:
      self.endTime = datetime.datetime.strptime(endTime, "%d.%m.%Y %H:%M")
    except:
      err( "Bad line format(end_date->parsing), skip: %r" % line )
      return

    #skin_name
    startIdx = endIdx+3
    endIdx = line.find( "\"", startIdx )
    if endIdx == -1:
      err( "Bad line format(end_date), skip: %r" % line )
      return
    self.skin_persistent_id = line[startIdx:endIdx]

    self.isValid = True
  
