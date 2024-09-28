# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, time

##----------------------------------------------------------------------------------------------------------------------
class IInstrumentation:
    """ Интерфейс для отметки времени исполнения запросов (он же пустая болванка для отмены instrumentation). """
    @staticmethod
    def tstart( response ):
        pass
        
    @staticmethod
    def tsadd( response, key ):
        pass
        
    @staticmethod
    def tend( response, key=None ):
        pass
    
##----------------------------------------------------------------------------------------------------------------------
class TimeInstrumentation( IInstrumentation ):
    """ Реальный механизм для отмечания времени исполнения запросов. """

    ## добавим в запрос время начала "t0"
    @staticmethod
    def tstart( response ):
        response["t0"] = time.time()

    ## добавим в запрос новый словарик, а в него уже время начала "t0"
    @staticmethod
    def tsadd( response, key ):
        response[key] = { "t0":time.time() }
        
    ## если в запросе есть время начала "t0", заменим на время исполнения "tm"; иначе добавим время окончания "t1"
    @staticmethod
    def tend( response, key=None ):
        res = response if not key else response[key]
            
        t1 = time.time()
        t0 = res.get("t0", 0)
        if t0:
            res.pop("t0")
            elapsed = t1-t0
            res["tm"] = "%0.2f ms" % ((t1-t0)*1000) # округлим до сотых долей ms
            return elapsed
        else:
            if not res.get("tm", 0): # уже есть такой замер
                res["t1"] = t1
    
##----------------------------------------------------------------------------------------------------------------------
## global
#~ instr = IInstrumentation() # отключаем, заменяем заглушкой
instr = TimeInstrumentation
