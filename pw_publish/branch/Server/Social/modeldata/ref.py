# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Vadim Petrov 2011
#
# collections for modeldata

from changes import *

class Ref(ChangeHandler):
    """ здесь лежат только ID-шник объекта (сами объект лежат в соотв. Keeper-е); для авто-удаления поддерживается refcounting """ 
    def __init__( self, modeldata, realdict=None, path="", name="" ):
        _dict = self.__dict__
        ##ChangeHandler.__init__( self, path, modeldata )
        _dict["_changeWriter"] = modeldata
        _dict["path"] = path
        _dict["object"] = IGuidGenerator.InvalidUID
        _dict["realdict"] = realdict
        _dict["name"] = name

    def init( self, realdict, path, changeWriter, name ):
        _dict = self.__dict__
        ##ChangeHandler.init( self, path, changeWriter )
        _dict["_changeWriter"] = changeWriter
        _dict["path"] = path
        _dict["realdict"] = realdict
        _dict["name"] = name

    def set( self, val ):
        if val == None or val == IGuidGenerator.InvalidUID:
            if self.__dict__["object"] != IGuidGenerator.InvalidUID:
                if self._changeWriter._writeChanges:
                    self.propertyUpdate( self.name, IGuidGenerator.InvalidUID )
                self.get().decRef()
                self.realdict.remove( self.__dict__["object"] )
                self.object = IGuidGenerator.InvalidUID
            return
        if isinstance(val, Identified):
            key = val.getID()
            value = val
        else:
            key = val
            value = self.realdict[key]
        
        if key == IGuidGenerator.InvalidUID:
            return

        if value == None:
            if self.__dict__["object"] != IGuidGenerator.InvalidUID:
                self.get().decRef()
                self.realdict.remove( self.__dict__["object"] )
            if self._changeWriter._writeChanges:
                self.propertyUpdate( self.name, IGuidGenerator.InvalidUID )
            self.object = IGuidGenerator.InvalidUID
            return

        if self.object != key:
            if self.__dict__["object"] != IGuidGenerator.InvalidUID:
                self.get().decRef()
                self.realdict.remove( self.__dict__["object"] )
            self.realdict[key] = value
            self.object = key
            self.get().addRef()
            if self._changeWriter._writeChanges:
                self.propertyUpdate( self.name,  self.__dict__["object"])
            
    def load_set( self, int_key ):
        # используется при десериализации, насильно ставим реф на id-шник, объект для которого может быть еще не загружен
        self.__dict__["object"] = int_key

    def deleteByID( self, id ):
        if self.object == id:
            self.set( IGuidGenerator.InvalidUID )


    def isValid( self ):
        return self.object != IGuidGenerator.InvalidUID

    def get(self):
        return self.realdict[self.object]

    def __getattr__( self, name ):
        return self.realdict[self.object].__getattribute__(name)

    def __setattr__(self, key, value):
        if key not in self.__dict__:
            setattr(self.realdict[self.object], key, value)
        else:
            self.__dict__[key] = value

    def __eq__( self, other ):
        if isinstance( other, Identified ):
            key = other.getID()
        else:
            key = other
        return self.object == key

    def __ne__( self, other ):
        return not self.__eq__( other )

    def getJsonDict( self ):
        return toint( self.object )
