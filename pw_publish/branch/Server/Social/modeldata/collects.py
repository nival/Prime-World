# -*- coding: utf-8 -*-

#
# (C) Vadim Petrov 2011
#
# collections for modeldata

from changes import *
from ref import *


class Keeper(ChangeHandler):
    """ в этой коллекции лежат объекты (используется для реализации Keeper-ов) """
    def __init__( self, modeldata ):
        ChangeHandler.__init__( self, "", modeldata )
        self.__dict__["dictionary"] = {}
        #self.__dict__["_priv_jsonDict"] = {}
        self.isDeleting = False

    def init( self, path, changeWriter, keeperTypeName ):
        ChangeHandler.init( self, path, changeWriter )
        self.keeperTypeName = keeperTypeName
        for key in self.__dict__["dictionary"]:
            self.__dict__["dictionary"][key].init()

    def add( self, key, val ):
        #err( "Keeper add: self=%s, key=%s, val=%s" % (self, key, val) )
        if key == IGuidGenerator.InvalidUID:
            return
        if key not in self.dictionary:
            self.dictionary[key] = val
            #self.__dict__["_priv_jsonDict"][key] = val.getJsonDict()
            if self._changeWriter._writeChanges:
                self.propertyAdd( key, val )

    def remove( self, key ):
        if key == IGuidGenerator.InvalidUID:
            return
        if key in self.dictionary:
            if self.dictionary[key].canDel():
                if self._changeWriter._writeChanges:
                    self.propertyDelete( key )
                del self.dictionary[key]
                #self.__dict__["_priv_jsonDict"].pop( key, None )

    def deleteByID( self, id ):
        if not self.isDeleting:
            self.isDeleting = True
            for key, val in self.dictionary.items():
                val.deleteByID( id )
                if key == id:
                    self.remove( key )

            self.isDeleting = False



    # ---------------------------------------------------------------
    # эмулируем интерфейс словаря (с итерацией по элементам и т.п.)
    def __getitem__( self, key ):
        return self.dictionary.get(key)

    def get( self, key ):
        return self.dictionary.get(key)

    def __setitem__( self, key, val ):
        return self.add( key, val )

    def pop( self, key):
        return self.remove(key)

    def __iter__( self ):
        return self.dictionary.__iter__()

    def iteritems( self ):
        return self.dictionary.iteritems()

    def itervalues( self ):
        return self.dictionary.itervalues()

    def keys( self ):
        return self.dictionary.keys()

    def items(self):
        return self.dictionary.items()

    def __len__( self ):
        return self.dictionary.__len__()

    def __delitem__( self, key ):
        del self.dictionary[key]

    # ---------------------------------------------------------------

    def getJsonDict( self ):
        #return { "Keeper": self._priv_jsonDict }
        return { "Keeper": "OBSOLETE METHOD! getJsonDict" }

    def generateJsonDict( self ):
        dct = {}
        for key, val in self.dictionary.iteritems():
            dct[key] = val.generateJsonDict()
        return { "Keeper": dct }


class SimpleList(ChangeHandler):
    """ обычный C#-List """
    def __init__( self, modeldata ):
        ChangeHandler.__init__( self, "", modeldata )
        self.__dict__["list"] = []

    def init( self, path, changeWriter ):
        ChangeHandler.init( self, path, changeWriter )

    def deleteByID( self, id ):
        pass

    def append( self, val ):
        self.list.append( val )
        self.propertyPush( val )

    def remove( self, val ):
        self.list.remove( val )
        self.propertyDelete( val )

    def __getitem__( self, key ):
        return self.list[key]

    def __delitem__( self, key ):
        val = self.list[key]
        del self.list[key]
        self.propertyDelete( val )

    def __setitem__( self, key, val ):
        self.list[key] = val
        self.propertyUpdate( key, val )

    def pop( self, index=None ):
        val = None
        if index == None:
            val = self.list.pop()
        else:
            val = self.list.pop( index )
        self.propertyDelete( val )
        return val

    def keys( self ):
        return self.list

    def __len__( self ):
        return self.list.__len__()

    def __contains__( self, val ):
        return val in self.list

    # ---------------------------------------------------------------
    def getJsonDict( self ):
        return { "SimpleList" : self.list[:] }

    def generateJsonDict( self ):
        return { "SimpleList" : self.list[:] }

    def serializeToFile( self, file, name ):
        for val in self.list:
            file.write( "self."+name+".append("+repr(val)+")\n")



class Set(ChangeHandler):
    """ в этой коллекции лежат только ID-шники объектов (сами объекты лежат в соотв. Keeper-е); для авто-удаления поддерживается refcounting """
    def __init__( self, modeldata ):
        ChangeHandler.__init__( self, "", modeldata )
        self.__dict__["dictionary"] = {}
        self.__dict__["realdict"] = None
        ##self.__dict__["_jsonDict"] = self.dictionary
        self.isDeleting = False

    def init( self, realdict, path, changeWriter ):
        ChangeHandler.init( self, path, changeWriter )
        self.__dict__["realdict"] = realdict

    def add( self, val ):
        if isinstance(val, Ref):
            val = val.get()
        if isinstance(val, Identified):
            key = val.getID()
            value = val
        else:
            key = val
            value = self.realdict[key]

        if key == IGuidGenerator.InvalidUID:
            return
        if key not in self.dictionary:
            value.addRef()
            self.realdict[key] = value
            self.dictionary[key] = key
            if self._changeWriter._writeChanges:
                self.propertyAdd( key, key )

    def remove( self, val ):
        if isinstance(val, Ref):
            val = val.get()
        if isinstance(val, Identified):
            key = val.getID()
            value = val
        else:
            key = val
            value = self.realdict[key]

        if key == IGuidGenerator.InvalidUID:
            return
        if key in self.dictionary:
            if self._changeWriter._writeChanges:
                self.propertyDelete( key )
            value.decRef()
            self.realdict.remove( key )
            del self.dictionary[key]

    def deleteByID( self, id ):
        if not self.isDeleting:
            self.isDeleting = True
            for key, val in self.dictionary.items():
                self.realdict[key].deleteByID( id )
                if key == id:
                    self.remove( key )

            self.isDeleting = False

    def swap( self, key1, key2 ):
        if (key1 in self.dictionary) and (key2 in self.dictionary):
            if self._changeWriter._writeChanges:
                self.propertySwap( key1, key2 )
            self.dictionary[key1], self.dictionary[key2] = self.dictionary[key2], self.dictionary[key1]

    # ---------------------------------------------------------------
    # IChangeHandler
    # коллекции не должны ничего удалять из _jsonDict, т.к. в него кладется прямой указатель на self.dictionary
    def propertyDelete( self, key ):
        self._changeWriter.modelChange( self.path, "del", key )

    # коллекции не должны ничего добавлять в _jsonDict, т.к. в него кладется прямой указатель на self.dictionary
    def propertyUpdate( self, key, val ):
        self._changeWriter.modelChange( self.path, "upd", { key:val } )

    # ---------------------------------------------------------------
    # эмулируем интерфейс словаря (с итерацией по элементам и т.п.)
    def __getitem__( self, key ):
        return self.realdict.get(key)

    def get( self, key ):
        if key in self:
            return self.__getitem__( key )
        else:
            return None

    def pop( self, key):
        return self.remove(key)

    def __iter__( self ):
        return self.dictionary.__iter__()

    def iteritems( self ): # возвращаем не свои пары (k,k), а пары (k,keeper_value)
        for k in self.dictionary:
            yield (k, self.realdict.get(k))

    def items( self ): # возвращаем список пар, но не своих пар (k,k), а пар (k,keeper_value)
        return [(k, self.realdict.get(k)) for k in self.dictionary.iterkeys()]

    def keys( self ):
        return self.dictionary.keys()

    def __len__( self ):
        return self.dictionary.__len__()

    def getJsonDict( self ):
        return { "Set" : self.dictionary.copy() }

    def values( self ):
        return [self.realdict.get(k) for k in self.dictionary.iterkeys()]

    def itervalues( self ): # возвращаем не свои пары (k,k), а пары (k,keeper_value)
        for k in self.dictionary:
            yield self.realdict.get(k)

    #def __contains__( self, val ):
    #    return val in self.realdict.values()
    getValues = values # for compatibility


class Collection(ChangeHandler):
    """ в этой коллекции лежат ID-шники объектов, адресуемые по произвольным ключам, != id самого объекта (сами объекты лежат в соотв. Keeper-е);
        для авто-удаления поддерживается refcounting
    """
    def __init__( self, modeldata ):
        ChangeHandler.__init__( self, "", modeldata )
        self.__dict__["dictionary"] = {} # основное индексирование (key:id)
        self.__dict__["reverse"] = {} # обратное индексирование (id:key)
        self.__dict__["realdict"] = None
        ##self.__dict__["_jsonDict"] = self.dictionary
        self.isDeleting = False

    def init( self, realdict, path, changeWriter ):
        ChangeHandler.init( self, path, changeWriter )
        self.__dict__["realdict"] = realdict

    def add( self, key, val ):
        if isinstance(val, Ref):
            val = val.get()
        if isinstance(val, Identified):
            id = val.getID()
            value = val
        else:
            id = val
            value = self.realdict[id]

        if id == IGuidGenerator.InvalidUID:
            return
        if key not in self.dictionary:
            if id != None:
                value.addRef()
                self.realdict[id] = value
                self.reverse[id] = key
            self.dictionary[key] = id
            if self._changeWriter._writeChanges:
                self.propertyAdd( key, id )

    def remove( self, key ):
        if isinstance(key, Ref):
            key = key.get()
        if isinstance(key, Identified):
            # на самом деле просят убрать по значению, а не по ключу
            value = key
            id = value.getID()
            key = self.reverse[id]
        else:
            id = self.dictionary.get( key )

        if id == IGuidGenerator.InvalidUID:
            return
        if key in self.dictionary:
            if self._changeWriter._writeChanges:
                self.propertyDelete( key )
            value = self.get(key)
            if value:
                value.decRef()
                self.reverse.pop( id )
            self.realdict.remove( id )
            del self.dictionary[ key ]

    def deleteRefByIndex(self, key):
        if isinstance(key, Ref):
            self.dictionary[ key ].set(0)
            del self.dictionary[ key ]
            if key in self.dictionary:
                if self._changeWriter._writeChanges:
                    self.propertyDelete( key )

    def addRefIndex(self, key ,val):
        if isinstance(val, Ref):
            if not key in self.dictionary:
                self.dictionary[key] = val
                if self._changeWriter._writeChanges:
                    self.propertyAdd( key, val )

    def deleteByID( self, id ):
        if not self.isDeleting:
            self.isDeleting = True
            for key, val in self.dictionary.items():
                if self.realdict[val]:
                    self.realdict[val].deleteByID( id ) #TODO разобраться и документировать, зачем операция выполняется для КАЖДОГО элемента?!
                if val == id:
                    self.remove( key )

            self.isDeleting = False

    # меняем местами два объекта (по обоим ключам должны находиться объекты!)
    def swap( self, key1, key2 ):
        if (key1 in self.dictionary) and (key2 in self.dictionary):
            if self._changeWriter._writeChanges:
                self.propertySwap( key1, key2 )
            id2, id1 = self.dictionary[key2], self.dictionary[key1]
            self.dictionary[key1], self.dictionary[key2] = id2, id1
            self.reverse[id1], self.reverse[id2] = key2, key1

    # переносим объект из одного ключа в другой (по которому сейчас ничего не лежит!)
    def move( self, srckey, destkey ):
        if (srckey in self.dictionary) and (destkey not in self.dictionary):
            if self._changeWriter._writeChanges:
                self.propertySwap( srckey, destkey )
            id = self.dictionary[srckey]
            self.dictionary[destkey] = id
            self.dictionary.pop(srckey)
            self.reverse[id] = destkey

    # ---------------------------------------------------------------
    # IChangeHandler
    # коллекции не должны ничего удалять из _jsonDict, т.к. в него кладется прямой указатель на self.dictionary
    def propertyDelete( self, key ):
        self._changeWriter.modelChange( self.path, "del", key )

    # коллекции не должны ничего добавлять в _jsonDict, т.к. в него кладется прямой указатель на self.dictionary
    def propertyUpdate( self, key, val ):
        self._changeWriter.modelChange( self.path, "upd", { key:val } )

    # ---------------------------------------------------------------
    # эмулируем интерфейс словаря (с итерацией по элементам и т.п.)
    def __getitem__( self, key ):
        return self.realdict.get(self.dictionary.get(key))

    def get( self, key ):
        return self.__getitem__( key )

    def __setitem__( self, key, val ):
        return self.add( key, val )

    def pop( self, key):
        return self.remove(key)

    def __iter__( self ):
        return self.dictionary.__iter__()

    def iteritems( self ): # возвращаем не свои пары (k,k), а пары (k,keeper_value)
        for k,v in self.dictionary.iteritems():
            yield (k, self.realdict.get(v))

    def items( self ): # возвращаем список пар, но не своих пар (k,k), а пар (k,keeper_value)
        return [(k, self.realdict.get(v)) for k, v in self.dictionary.iteritems()]

    def keys( self ):
        return self.dictionary.keys()

    def values( self ):
        return self.dictionary.values()

    def __len__( self ):
        return self.dictionary.__len__()
    # ---------------------------------------------------------------

    # бывает и так, что нас интересует именно id :)
    def getID( self, key, default=None ):
        return self.dictionary.get(key, default)

    def findKey( self, item ):
        id = item.getID() if isinstance(item, Identified) else item
        return self.reverse.get( id )

    def ids( self ):
        return self.reverse.keys()

    def getJsonDict( self ):
        return { "Collection" : self.dictionary.copy() }

    def getValues( self ):
        #return [self.get( k ) for k in self.dictionary]
        #optimized version:
        return [self.realdict.get(id) for id in self.dictionary.itervalues()]


    # ---------------------------------------------------------------


class SimpleDict(ChangeHandler):
    """ обычный C#-Dictionary """
    def __init__( self, modeldata ):
        ChangeHandler.__init__( self, "", modeldata )
        self.__dict__[ "dictionary" ] = {}

    def init( self, path, changeWriter ):
        ChangeHandler.init( self, path, changeWriter )

    def deleteByID( self, id ):
        pass

    def set(self, key, val):
        if key not in self.dictionary:
            self.add(key, val)
        else:
            self[key] = val


    def add( self, key, val ):
        if key not in self.dictionary:
            self.dictionary[ key ] = val
            if self._changeWriter._writeChanges:
                self.propertyAdd( key, val )

    def remove( self, key ):
        if key in self.dictionary:
            if self._changeWriter._writeChanges:
                self.propertyDelete( key )
            del self.dictionary[ key ]

    # ---------------------------------------------------------------
    # эмулируем интерфейс словаря (с итерацией по элементам и т.п.)
    def __getitem__( self, key, default=None ):
        if default is None:
            val = self.dictionary.get( key )
        else:
            val = self.dictionary.get(key, default)
        return val

    def get( self, key, default=None ):
        return self.__getitem__( key, default )

    def __setitem__( self, key, val ):
        self.dictionary.update( {key : val} )
        self.propertyUpdate( key, val )

    def __delitem__( self, key ):
        del self.dictionary[key]
        self.propertyDelete( key )

    def __iter__( self ):
        return self.dictionary.__iter__()

    def iteritems( self ):
        return self.dictionary.iteritems()

    def keys( self ):
        return self.dictionary.keys()

    def values( self ):
        return self.dictionary.values()

    def __len__( self ):
        return self.dictionary.__len__()

    # ---------------------------------------------------------------
    def getJsonDict( self ):
        return { "SimpleDict" : self.dictionary.copy() }

    def generateJsonDict( self ):
        return { "SimpleDict" : self.dictionary.copy() }

    def serializeToFile( self, file, name ):
        keys = self.dictionary.keys()[:]
        keys.sort()
        for key in keys:
            file.write( "self."+name+".add("+repr(key)+", "+repr(self.dictionary[key])+")\n")

    def move( self, srckey, destkey ):
        if (srckey in self.dictionary) and (destkey not in self.dictionary):
            if self._changeWriter._writeChanges:
                self.propertySwap( srckey, destkey )
            id = self.dictionary[srckey]
            self.dictionary[destkey] = id
            self.dictionary.pop(srckey)

    def swap( self, key1, key2 ):
        if (key1 in self.dictionary) and (key2 in self.dictionary):
            if self._changeWriter._writeChanges:
                self.propertySwap( key1, key2 )
            id2, id1 = self.dictionary[key2], self.dictionary[key1]
            self.dictionary[key1], self.dictionary[key2] = id2, id1

