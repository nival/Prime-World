# -*- coding: utf-8 -*-
import sys, time, json, os

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *

addRelPath("../modeldata", "../modeldata/SharedTypes")
import Friend

class PartyDataCustom( BaseObject ):
  def __init__(self):
    self.__dict__["_modelChangeWriter"] = None
    self.__dict__["_writeChanges"] = False
    
  def save( self, save_data=None ):
    self._serializator.setMode( False ) # For server side
    save_data = save_data or self.generateJsonDict()
    return json_dumps( save_data )

  def load( self, data ):
    if isinstance(data, basestring):
      data = json_loads( data )
    self._serializator.fromDict( data )
    
  # IChangeWriter
  def modelChange( self, path, op, val ):
    if self._modelChangeWriter:
      self._modelChangeWriter.writeStringToResponse( self.__class__.__name__, "auto", path, op, val ) 
            
  # включаем авто-запись изменений в нашей ModelData (в указанный changeWriter)
  def write( self, changeWriter ):
    self._modelChangeWriter = changeWriter
    self._writeChanges = (changeWriter is not None)
    
  # отключаем авто-запись изменений в нашей ModelData 
  def stop( self ):
    self._modelChangeWriter = None
    self._writeChanges = False

  # эмулируем доступ к элементу как у словаря, чтобы работал поиск по абсолютным путям
  def get( self, key ):
    return self.__dict__.get(key) 
    
  # находим по auid == Person.person_uid == Friend.person_uid
  def findPersonByUid(self, person_uid):
    for person_id,person in self.PersonKeeper.iteritems():
      if person.person_uid == person_uid:
        return person
        
  # находим по auid == PartyMember.person.person_uid == Person.person_uid == Friend.person_uid
  def findMemberByUid(self, person_uid):
    for member_id,member in self.PartyMemberKeeper.iteritems():
      if member.person.get() and member.person.person_uid == person_uid:
        return member

  ## заводим новую персону с id==auid: вообще-то это очень плохая идея, т.к. id-шники элементов в разных keeper-ах станут неуникальными, 
  ##  и при "удалении отовсюду по id" можем удалить не то
  #~ def newFixedIdFriend(self, auid):
    #~ var = Friend.Friend( self, auid, "PersonKeeper/"+str(auid) )
    #~ var.init_add()
    #~ self.PersonKeeper.add( auid, var )
    #~ return var, auid

  def getOurPartyMembersUids( self ):
    friendUids = []
    for friendId in self.members:
      friend = self.getPartyMemberByID( friendId )
      if friend:
        friendUids.append( friend.person.person_uid )
    return friendUids


  # очистка всех ошибок
  def eraseAllErrors( self ):
    for err in self.errors.keys():
      self.errors.remove( err )
    for err in self.ErrorKeeper.keys():
      self.ErrorKeeper.remove( err )
  
  # дополнительные (server-side) сериализуемые поля
  def generateBaseDict(self):
    return dict(
      next_uid_ = self.next_uid_
    )
