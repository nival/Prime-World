# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import signal

#import tornado.options
#from tornado.options import define, options

##------------------
##---------------------------------------------------------------------------------------------------
class IAbstractModelData:
    # ---------------------------------------------------------------------------------------------------
    # создаем иерархию и (если указаны параметры) слегка населяем слотами, случайными героями и случайными вещами
    def create(self, XDB, create_version="x", **kwargs):
        raise NotImplementedError()
    
    # ---------------------------------------------------------------------------------------------------
    # загружаемся из json-словаря (подразумеваем что иерархия классов уже создана через __init__; проходимся по всем словарям, апдейтим значения ключей, не являющихся subdict)
    def load(self, model_data_dict):
        raise NotImplementedError()
        
    # ---------------------------------------------------------------------------------------------------
    # сериализуемся до вида словаря (или даже строки); возвращаемый результат должен проходить через стандартный JSON-сериализатор    
    def save(self):
        raise NotImplementedError()

    # ---------------------------------------------------------------------------------------------------
    # сохраняем себя в json-словарь
    def save( self ):
        raise NotImplementedError()


##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------
class IModelData( IAbstractModelData, ClassDict ):
    """ ЗАГЛУШЕЧНАЯ иерархия Model Data для отдельного клиента (игрока) """
    _STRUCTURE = { 
        "SubKey": { 
            "SubKeyList":{} # ID: Hero
        },
        "ListKey":[] # здесь будет ClassDictList, вида { id1:id1, id2:id2 }
    }
    
    # ---------------------------------------------------------------------------------------------------
    # умеем делать слепок со _STRUCTURE
    def recurse_create(self, subdict, STRUCTURE):
        for key,value in STRUCTURE.iteritems():
            if isinstance(value, dict):
                subdict[key] = ClassDict()
                self.recurse_create( subdict[key], value )
            elif isinstance(value, list):
                subdict[key] = ClassDictList()
        
    # ---------------------------------------------------------------------------------------------------
    # создаем иерархию и (если указаны параметры) слегка населяем слотами, случайными героями и случайными вещами
    def create(self, XDB, create_version="x", **kwargs):
        # создаем внутри себя копию иерархии _STRUCTURE, только на каждом уровне не простые словари, а ClassDict, 
        #  чтобы можно было адресовать всю иерархию как объект: "self.HeroesKeeper.HeroesList.123.property = xxx"
        self.recurse_create( self, self._STRUCTURE )
        
        self.create_version = create_version
    
    # ---------------------------------------------------------------------------------------------------
    # загружаемся из json-словаря (подразумеваем что иерархия классов уже создана через __init__; проходимся по всем словарям, апдейтим значения ключей, не являющихся subdict)
    def load(self, model_data_dict):
        subDictUpdate( self, model_data_dict ) 

    # сериализуемся до вида словаря (или даже строки); возвращаемый результат должен проходить через стандартный JSON-сериализатор    
    def save(self):
        return self # мы и есть словарь
        
##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

from subaction import SubAction

class IDataManager( object ):
    """ Заглушка, умеет только заворачивать JSON-данные. """
    # ---------------------------------------------------------------------------------------------------
    def __init__(self):
        pass
                    
    # этим методом будут пользоваться сервера для заворачивания данных клиентам 
    def toJson(self, save_data, forClient=True, **kwargs):
        SubAction.convertResponseObjects(save_data)
        return json_dumps( save_data )
        
    def pretty(self, save_data):
        SubAction.convertResponseObjects(save_data)
        return json_pretty( save_data )

    def reloadAllEvents( self ):
        pass

        
##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class IRequestChangeWriter:
    """ абстрактный интерфейс для заворачивания model changes, внутри RequestHandler """
    def writeStringToResponse( self, key, comment, path, op, val ):
        pass

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class IUserDataManager( IDataManager ):
    """ Заглушка, умеет создавать пустую модель данных. """
    # ---------------------------------------------------------------------------------------------------
    def newModel(self, acc, xdb, server_version, **kwargs):
        info( "i newModel" )
        acc.model = IModelData()
        acc.pending = IRequestChangeWriter()
        acc.model.create( xdb, acc, server_version, sex = acc.sex, guest = acc.guest)
        
    # ---------------------------------------------------------------------------------------------------
    def emptyModel(self, acc, iDict, server_version, **kwargs):
        info( "i clearModel" )
        acc.model = IModelData() 
        acc.pending = IRequestChangeWriter()
        acc.model.create( iDict, acc, server_version, sex = acc.sex, guest = acc.guest)
        
    # ---------------------------------------------------------------------------------------------------
    def loadModel(self, acc, load_string, xdb, server_version, **kwargs):
        info( "i loadModel" )
        acc.model = IModelData()
        acc.pending = IRequestChangeWriter()
        acc.model.create( xdb, acc, create_version="", sex = acc.sex, guest = acc.guest )
        acc.model.load( load_string )
        
    

