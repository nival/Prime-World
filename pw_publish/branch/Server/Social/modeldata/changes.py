# -*- coding: utf-8 -*-

#
# (C) Vadim Petrov 2011
#
# change generator for modeldata

from baseclasses import *
from base.helpers import *

CHANGE_OP_CODES = ['init', 'add', 'upd', 'del', 'swp', 'push']

def MakeModelChangeString( comment, path, op, params ):
    return { comment : [ [path, op, params] ] }

# -----------------------------------------------------------------------------------------------------

class IGuidGenerator(object):
    InvalidUID = 0
    """ абстрактный интерфейс для генерации GUID (реальный генератор надо брать у IWebServer) """
    def nextGUID( self ):
        raise NotImplementedError()
        
class AutoIncGuidGenerator( IGuidGenerator ):
    """ заглушка, тривиальный auto-inc (нифига не Глобально Уникальные id) """
    def __init__( self, startValue=IGuidGenerator.InvalidUID ):
        self.__dict__["next_uid_"] = startValue
        
    def nextGUID( self ):
        self.__dict__["next_uid_"] += 1
        return self.next_uid_

# -----------------------------------------------------------------------------------------------------

class IChangeWriter(object):
    writeChanges = False
    """ абстрактный интерфейс для заворачивания model changes в пределах ModelData """
    def modelChange( self, path, op, val ):
        pass
    def canWrite( self ):
        pass

class DummyChangeWriter( IChangeWriter ):
    """ заглушка: тупо пишем в лог """
    def __init__( self, name="" ):
        self._name = name
        
    def modelChange( self, path, op, val ):
        print "[-- auto model change %s--]" % self._name, repr(path), repr(op), repr(val) # в заглушечном варианте просто логаем

# -----------------------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------------------

class IRequestChangeWriter(object):
    writeChanges = False
    """ абстрактный интерфейс для заворачивания model changes, внутри RequestHandler """
    def writeStringToResponse( self, comment, path, op, val ):
        pass
    def canWrite( self ):
        pass

# -----------------------------------------------------------------------------------------------------
class DummyRequestWriter(IRequestChangeWriter):
    """ заглушка: эмулирует интерфейс внешнего request handler """
    def __init__( self, name="" ):
        self._name = name
        
    def writeStringToResponse( self, key, comment, path, op, val ):
        print "[-- auto model change %s--]" % self._name, repr(key), repr(path), repr(op), repr(val) # в заглушечном варианте просто логаем
        
# -----------------------------------------------------------------------------------------------------
class PendingChangeWriter( IRequestChangeWriter ):
    def __init__( self, pending_acc, comment_prefix="" ):
        self.pending_acc = pending_acc
        self.setPrefix(comment_prefix)
        
    def setPrefix(self, comment_prefix=""):
        self.comment_prefix = comment_prefix
        
    def writeStringToResponse(self, key, comment, path, op, params):
        new_comment = self.comment_prefix + comment
        self.pending_acc.pending_changes.append( { key : MakeModelChangeString(new_comment, path, op, params) } )

class GroupPendingChangeWriter( PendingChangeWriter ):
    def writeStringToResponse(self, key, comment, path, op, params):
        new_comment = self.comment_prefix + comment
        if self.pending_acc.pending_changes and len(self.pending_acc.pending_changes) and isinstance(params, dict):
            last_entry = self.pending_acc.pending_changes[-1]
            if last_entry and isinstance(last_entry, dict):
                last_key_entry = last_entry.get(key)
                if last_key_entry and isinstance(last_key_entry, dict):
                    last_comment_entry = last_key_entry.get(new_comment)
                    if last_comment_entry and isinstance(last_comment_entry, list):
                        try:
                            last_triad = last_comment_entry[-1]
                            last_path = last_triad[0]
                            if last_path == path:
                                # пути совпадают, добавляем прямо к словарю params {}
                                last_params = last_triad[2]
                                if isinstance(last_params, dict):
                                    last_params.update( params )
                                    return
                                
                        except:
                            catch()
                            pass
                                
                        # key и comment совпадают, но пути разные; добавляем к списку [[ ]]
                        last_comment_entry.append( [path, op, params] )
                        return
        
        # если группировать не с чем, пишем как раньше, каждый event отдельной строчкой с массой скобочек
        PendingChangeWriter.writeStringToResponse(self, key, comment, path, op, params)

# -----------------------------------------------------------------------------------------------------
# -----------------------------------------------------------------------------------------------------

class IChangeHandler(object):
    """ абстрактный интерфейс для авто-генерации model changes """
    def __init__( self, path, changeWriter ):
        pass

    def propertyInit( self, serialized_val ):
        pass
        
    def propertyAdd( self, key, val ):
        pass

    def propertyPush( self, val ):
        pass

    def propertyDelete( self, key ):
        pass

    def propertyUpdate( self, key, val ):
        pass

    # меняем местами два объекта (по обоим ключам должны находиться объекты) ИЛИ переносим объект из одного ключа key1 в другой key2 (по которому сейчас ничего не лежит!)
    def propertySwap( self, key1, key2 ):
        pass
        
    # любой сериализуемый объект должен уметь возвращать "простой словарь" со своим содержимым, для легкой паковки в JSON
    def getJsonDict( self ):
        pass


class ChangeHandler( IChangeHandler ):
    _changeFields = {}
    
    def __init__( self, path, changeWriter ):
        self.__dict__["_changeWriter"] = changeWriter
        self.__dict__["path"] = path

    def init( self, path, changeWriter ):
        self.__dict__["_changeWriter"] = changeWriter
        self.__dict__["path"] = path
        
    def propertyInit( self, serialized_val ):
        if self._changeWriter._writeChanges:
            self._changeWriter.modelChange( self.path, "init", serialized_val )
        
    def propertyAdd( self, key, val ):
        if self._changeWriter._writeChanges:
            if isinstance(val, Identified):
                # в случае добавления объекта (Hero, Talent и т.п.), высылаем только ID
                self._changeWriter.modelChange( self.path, "add", { key:{ "id": val.getID() } } )
            else:
                self._changeWriter.modelChange( self.path, "add", { key:val } )

    def propertyPush( self, val ):
        if self._changeWriter._writeChanges:
            self._changeWriter.modelChange( self.path, "push", val )

    def propertyDelete( self, key ):
        if self._changeWriter._writeChanges:
            self._changeWriter.modelChange( self.path, "del", key )
            ## err( "%s del jsonDict[%s]" % (self, key) )

    def propertyUpdate( self, key, val ):
        if self._changeWriter._writeChanges:
            self._changeWriter.modelChange( self.path, "upd", { key:val } )

    def propertySwap( self, key1, key2 ):
        if self._changeWriter._writeChanges:
            self._changeWriter.modelChange( self.path, "swp", [key1,key2] )
        
    def __setattr__( self, name, value ):
        ##warn( "ChangeHandler.__setattr__(type=%s, name=%s, value=%s)" % (type(self), str(name), str(value)[:128]) )
        if self.__dict__.get(name) != value:
            self.__dict__[name] = value
            if self._changeWriter._writeChanges:
                if name in self._changeFields:
                    ##warn( "UPDATE ChangeHandler.__setattr__(type=%s, name=%s, value=%s)" % (type(self), str(name), str(value)[:128]) )
                    self.propertyUpdate( name, value )

    def __delattr__( self, name ):
        if hasattr( self, name ):
            if name in self._changeFields:
                self.propertyDelete( name )
            self.__dict__.pop(name)
            
    #~ # любой сериализуемый объект должен уметь возвращать "простой словарь" со своим содержимым, для легкой паковки в JSON
    #~ def getJsonDict( self ):
        #~ return self._jsonDict


# -----------------------------------------------------------------------------------------------------
        
class DummyModelDataRequestHandler( IChangeWriter, AutoIncGuidGenerator ):
    """ заглушка, умеет притворяться web request handler-ом; берет на себя запись model changes и генерацию гуидов """
    def __init__( self ):
        AutoIncGuidGenerator.__init__( self )
        self._response = {}
    
    def modelChange( self, path, op, val ):
        if not self._response.has_key("ModelData"):
            self._response["ModelData"] = []
            
        self._response["ModelData"].append( { "auto" : [ [path, op, val] ] } )