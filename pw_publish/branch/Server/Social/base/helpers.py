# -*- coding: utf-8 -*-

import traceback, sys, os, random, hashlib, time, urllib, urlparse, string, re
import logging, json, ujson, socket, inspect, pprint, collections, types, signal

# This module is designed to export ALL it's non-local names, so no __all__ specified
# and it's OK to use: from base.helpers import *

# для краткости:
log = logging.debug 
debug = logging.debug 
info = logging.info
warn = logging.warning
err = logging.error
error = logging.error

#-------------------------------------------------------------------------
# чтобы питон правильно понимал относительные пути модулей:
def addModPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)
    else:
        pass
        #print "DEBUG: Unneccessary addModPath('%s') call (importPath=%s):" % (strPath, importPath)
        #print "Traceback: " + (''.join(traceback.format_stack()[:-1]))

#-------------------------------------------------------------------------
def addRelPath(*subPaths):
    file = inspect.getmodule(inspect.stack()[1][0]).__file__
    for subPath in subPaths:
        importPath = os.path.join(os.path.dirname(file), subPath)
        if not (importPath in sys.path):
            sys.path.append(importPath)
        else:
            pass
            #print "DEBUG: Unneccessary addRelPath('%s') call (importPath=%s):" % (subPath, importPath)
            #print "Traceback: " + (''.join(traceback.format_stack()[:-1]))

#-------------------------------------------------------------------------

#-------------------------------------------------------------------------

def json_loads(data_string):
    if isinstance( data_string, unicode ):
        data_string = data_string.encode("utf8")
    return ujson.decode( data_string )

#-------------------------------------------------------------------------
def json_dumps(data):
    try:
        return ujson.encode(data)
    except OverflowError:
        analize_ujson_fail(data)
        raise
    except Exception:
        err("ujson.encode error. data=%r", data)
        catch()
        raise

def analize_ujson_fail(data, path=''):
    if isinstance(data, collections.Mapping):
        dt = type(data).__name__
        for k, v in data.iteritems():
            analize_ujson_fail(k, path+('/%s:key' % dt))
            analize_ujson_fail(v, path+('/%s[%r]' % (dt, k)))
    elif isinstance(data, collections.Sequence) and not isinstance(data, types.StringTypes):
        dt = type(data).__name__
        for i, v in enumerate(data):
            analize_ujson_fail(v, path+('/%s[%d]' % (dt, i)))
    else:
        try:
            ujson.encode(data)
        except Exception:
            err("ujson.encode fails for path %s on %r\n%s", path, data, excString())

#-------------------------------------------------------------------------
# pretty json format
def pretty( obj ):
    return json.dumps(obj, indent=4, sort_keys=True)

json_pretty = pretty

#-------------------------------------------------------------------------
def urlQuote(s):
    if s:
        return urllib.quote(s)
    else:
        return s

#-------------------------------------------------------------------------
#-------------------------------------------------------------------------
# ищем в иерархии словарей-списков ключи числового вида (например "123":...) и преобразуем их к интам
def recurse_xform_int_keys( cont ):
    if cont:
        changed = 0
        if isinstance( cont, dict ):
            for key, val in cont.items():
                unquoted = recurse_xform_int_keys(val)
                if unquoted:
                    cont[key] = unquoted
                    
                try:
                    if isinstance(key, long):
                      key_int = long(key)
                    else:
                      key_int = int(key)
                    value = cont.pop( key )
                    cont[key_int] = value
                except Exception:
                    pass
                    
        elif isinstance( cont, list ):
            for i, val in enumerate(cont):
                unquoted = recurse_xform_int_keys(val)
                if unquoted:
                    cont[i] = unquoted
            
    return cont
    
    
#-------------------------------------------------------------------------
# заменяем unicode-ключи на их str() аналог в кодироке utf8
def deunicode_keys( unicode_dict ):
    for k,v in unicode_dict.items():
        if k.__class__ == unicode:
            unicode_dict.pop(k)
            unicode_dict[ k.encode('utf8') ] = v

#-------------------------------------------------------------------------
# заменяем unicode-ключи и значения на их str() аналог в кодироке utf8
def deunicode_dict( unicode_dict ):
    for k,v in unicode_dict.items():
        if v.__class__ == unicode:
            v = v.encode('utf8')
            unicode_dict.pop(k)
            if k.__class__ == unicode:
                k = k.encode('utf8')
            unicode_dict[ k ] = v
        elif k.__class__ == unicode:
            unicode_dict.pop(k)
            unicode_dict[ k.encode('utf8') ] = v

            
#-------------------------------------------------------------------------
# парсинг с заменой "символьных числовых" ключей (key="12345") на просто числовые (key=12345)
def json_load_transform( data_string ):
    if isinstance( data_string, unicode ):
        data_string = data_string.encode("utf8")
    data = ujson.decode( data_string )
    return recurse_xform_int_keys( data )
    
#-------------------------------------------------------------------------

def loggingSeverity( name ):
    return getattr( logging, name.upper(), 0) if name else 0

## объединяем и распечатываем exception info
def printException(exceptionInfoList):
    exceptionType, exceptionValue, exceptionTraceback = exceptionInfoList
    strList = traceback.format_exception(exceptionType, exceptionValue, exceptionTraceback)
    return "catch: " + (''.join(strList))

def get_stack(stopAt=None):
    st = traceback.extract_stack()[:-2]
    if stopAt:
        pos = 0
        for i, frame in enumerate(reversed(st)):
            if frame[2] == stopAt:
                pos = len(st) - i
                break
        if pos > 0:
            del st[:pos-1]
    return st

# Вывести исключение и стек до самого верха, а не только до точки поимки исключения
def printExceptionFullStack(exceptionInfoList, stopAt=None):
    exceptionType, exceptionValue, exceptionTraceback = exceptionInfoList
    st = get_stack(stopAt)[:-2]
    lines = traceback.format_list(st + traceback.extract_tb(exceptionTraceback))
    lines[len(st):len(st)] = ["  ---[Catch point]---\n", ]
    return "catch: Traceback (most recent call last):\n" + (''.join(lines + traceback.format_exception_only(exceptionType, exceptionValue)))


def excString():
    excType, excValue = sys.exc_info()[:2]
    return "%s: %s" % (excType.__name__, excValue)


def catch(msg=None, *args):
    res = printException(sys.exc_info())
    if msg is None:
        err(res)
    elif args:
        err(msg + "\n%s", *(args + (res,)))
    else:
        err("%s\n%s", msg, res)
    return res


def catchFull(msg=None, *args, **kwargs):
    res = printExceptionFullStack(sys.exc_info(), stopAt=kwargs.get('stopAt'))
    if msg is None:
        err(res)
    elif args:
        err(msg + "\n%s", *(args + (res,)))
    else:
        err("%s\n%s", msg, res)
    return res


def _mk_trace_func(meth=warn, name=None):
    def _trace(msg=None, *args, **kwargs):
        res = "Traceback (most recent call last):\n" + (''.join(traceback.format_list(get_stack(kwargs.get('stopAt')))))
        if msg is None:
            meth(res)
        elif args:
            meth(msg + "\n%s", *(args + (res,)))
        else:
            meth("%s\n%s", msg, res)
        return res
    _trace.func_name = name if name is not None else (meth.func_name + '_trace')
    return _trace

info_trace = _mk_trace_func(info, 'info_trace')
warn_trace = _mk_trace_func(warn, 'warn_trace')
err_trace = _mk_trace_func(err, 'err_trace')


def exc():
    exceptionType, exceptionValue, exceptionTraceback = sys.exc_info()
    strOutput = "exc: " + traceback.format_exception_only(exceptionType, exceptionValue)[-1]
    warn( strOutput )
    return exceptionValue


def printExceptionOnly(exceptionInfoList):
    exceptionType, exceptionValue, exceptionTraceback = exceptionInfoList
    excValueOutput = traceback.format_exception_only(exceptionType, exceptionValue)[-1]
    return excValueOutput

def errStack( error_string="" ):
    tb = traceback.extract_stack()
    tb_strings = traceback.format_list( tb[:-1] )
    return "Traceback: %s\n" % error_string + string.join(tb_strings)


## проверяем, что x успешно приводится к числу (int)
def digit(x):
    try:
        int(x)
        return True
    except Exception:
        return False

## проверяем, что x успешно приводится к float
def testfloat(x):
    try:
        float(x)
        return True
    except Exception:
        return False


## str -> bool
def str2bool(v):
  if isinstance( v, bool ):
    return v
  return isinstance(v, basestring) and (v.lower() in ("yes", "true", "t", "1"))


## чистим список
def clear(list):
    del list[:]
    
## знак
def sign(what):
    try:
        if what > 0:
            return 1
        elif what < 0:
            return -1
    except Exception:
        pass
    return 0

## модуль
def abs(what):
    try:
        if what < 0:
            return -what
    except Exception:
        pass
    return what


## безопасно преобразовываем нечто к int, отлавливаем возможный exception
def toint(something, default=0):
    try:
        return int(something)
    except Exception:
        #log("toint exception: %s" % str(something))
        return default
    
## безопасно преобразовываем нечто к signed int32, отлавливаем возможный exception 
MIN_INT32 = -0x7FFFFFFF-1
MAX_INT32 = 0x7FFFFFFF
def toint32(input, log=True):
  try:
    val = int(input)
    if MIN_INT32 <= val <= MAX_INT32:
        return val
    if log:
        warn(errStack("oversized value for toint32: %r" % input))
    return 0
  except Exception:
    warn( errStack( "bad int32 %r" % input ))
    return 0

def fit_i32(value):
    if type(value) in (int, bool):
        return value
    elif value > MAX_INT32:
        return MAX_INT32
    elif value < MIN_INT32:
        return MIN_INT32
    elif MIN_INT32 < value < MAX_INT32:
        return int(value)
    return 0

## безопасно преобразовываем нечто к long int, отлавливаем возможный exception 
def tolong(something):
    try:
        return long(something)
    except Exception:
        return 0

## безопасно преобразовываем нечто к long int, отлавливаем возможный exception 
def tofloat(something):
    try:
        return float(something)
    except Exception:
        return 0.0

def md5( arg ):
    return hashlib.md5( str(arg) ).hexdigest()
    
## делаем из строки более-менее уникальный crc64 (== первые 8 байт от md5)
def md5_int64( src_string ):
    digest16 = hashlib.md5( src_string ).hexdigest()
    digest8 = digest16[:16]
    int64 = long(digest8, 16)
    return int64
    
## "сжимаем" строчку hexdigest вдвое, преобразуя hex-пары "00".."ff" в числа \x00..\x255
def md5_digest2binary( src ):
    res = ""
    while src:
        try:
            nibble = int( src[0:2],16 ) # преобразуем строчку "00".."ff" к числу 0..255
            src = src[2:]
            res += chr(nibble)
        except Exception:
            res = ""
    return res
            
def toETalentRarity(intRarity):
    if intRarity == 0:
        return "Class"
    elif intRarity == 1:
        return "ordinary"
    elif intRarity == 2:
        return "good"
    elif intRarity == 3:
        return "excellent"
    elif intRarity == 4:
        return "magnificent"
    elif intRarity == 5:
        return "exclusive"
    elif intRarity == 6:
        return "outstanding"
    return ""

def fromETalentRarity(strRarity):
    if strRarity == "Class":
        return 0
    elif strRarity == "ordinary":
        return 1
    elif strRarity == "good":
        return 2
    elif strRarity == "excellent":
        return 3
    elif strRarity == "magnificent":
        return 4
    elif strRarity == "exclusive":
        return 5
    elif strRarity == "outstanding":
        return 6
    return 0
        
## свой вариант escapeQuotes, для краткости     
# @param str        строка, в которой хочется заменить все символы ' на \'
def esc(str):
    str1 = str.replace("\\", "\\\\")
    return str1.replace("'", "\\'")

## сообщение об удачном завершении операции дублируем в stdout (чтобы сразу было видно в консоли)
def success( msg ):
    print "SUCCESS:", msg
    info( msg )
    
## фатальные ошибки запуска дублируем в stdout (чтобы сразу было видно в консоли)
def fatal( er ):
    print "ERROR:", er
    err( er )

## серьезные варнинги тоже дублируем в stdout (чтобы сразу было видно в консоли)
def bad_warn( wrn ):
    print "WARNING:", wrn
    warn( wrn )

## если какая ошибка, или header не соответствует, возвращаем None
def strip(strLong, strHeader, strFooter=None):
    #~ log("strip(strLong='%s', strHeader='%s', strFooter='%s')" % (str(strLong), str(strHeader), str(strFooter)) )
    try:
        ln = len(strHeader)
        if strLong[:ln] != strHeader:
            #~ log("strip: bad head")
            return None

        ln2 = 0
        if strFooter:
            ln2 = len(strFooter)
            if strLong[-ln2:] != strFooter:
                #~ log("strip: bad foot")
                return None
                
        if ln2:
            strCut = strLong[ln:-ln2]
        else:
            strCut = strLong[ln:]
            
        #~ log("strip: return '%s'" % (str(strCut)) )
        return strCut 
        
    except Exception:
        #~ log("strip: exception")
        #~ raise
        return None
    
    
## если какая ошибка, или header не соответствует, возвращаем пустую строчку ("")
def stripStr(strLong, strHeader, strFooter=None):
    strCut = strip(strLong, strHeader, strFooter)
    if not strCut:
        strCut = ""
    return strCut

# отрезаем весь конец строчки, после ПЕРВОГО вхождения определенной ключевой подстроки
def stripAfter(strLong, strCutOff):
    ncut = strLong.find(strCutOff)
    if ncut >= 0:
        return strLong[:ncut]
    return strLong

# отрезаем весь конец строчки, после ПОСЛЕДНЕГО вхождения определенной ключевой подстроки
def stripAfterLast(strLong, strCutOff):
    ncut = strLong.rfind(strCutOff)
    if ncut >= 0:
        return strLong[:ncut]
    return strLong


## helper: выбираем случайный элемент из списка
def pickRandom(list):
    if list and len(list):
        index = random.randint( 0, len(list)-1 )
        return list[index]
    return 0

## helper: выбираем случайный элемент из словаря (возвращаем пару "key, value")
def pickRandomPair(dict):
    key = pickRandom( dict.keys() )
    value = dict[key]
    return key,value
    

## вытаскиваем из тела HTTPResponse json-параметры (если не ок, вернем {})
def jsonResult(response):
    ret = {}
    if response and response.code == 200:
        ret = json_loads( response.body )
    return ret

## парсим из тела HTTPResponse json-response (если не ок, вернем {} и ошибку)
def parseResponse(http_reply):
    response = {}
    error = None
    try:
        if http_reply and (not http_reply.error):
            unquote_body = urllib.unquote( http_reply.body )
            json_reply = json_load_transform( unquote_body )
            if json_reply:
                response = json_reply.get("response", {})
        else:
            error = "BAD http reply: %s" % http_reply
    except Exception:
        catch()
        error = "EXCEPTION on http reply: %s" % http_reply
    return response, error


##------------------------------------------------------------------------
# привести float значения секунд в опр.словаре к красивым печатным миллисекундам
def times2msec( dct ):
    copy_dct = dict( dct )
    # приведем float к печатному виду
    for k,v in copy_dct.iteritems():
        if isinstance(v, float):
            copy_dct[k] = "%.2f ms" % (v*1000)
    return copy_dct


##------------------------------------------------------------------------
## специализированный словарик для подсчета количества (для отсутствующих ключей подразумеваем/заводим 0)
class IncDict(dict):
    """Dictionary for inc-counting."""
    def inc( self, key ):
        return self.add( key, 1 )

    def dec( self, key ):
        return self.add( key, -1 )

    # этим методом можно накапливать и float-значения
    def add( self, key, add_val ):
        val = self.get(key, 0) + add_val
        self[key] = val
        return val

    def pick( self, key ):
        return self.get( key, 0 )

    # обнуление ключа эквивалентно удалению
    def reset( self, key ):
        self.pop( key, 0 )

    # для случая, когда у нас есть внешний источник guid-ов, и нужно ставить nextUid = max( current_local_uid, some_external_uid )
    def _upd_max( self, key, value ):
        current = self.get( key, 0 )
        _max = max(value, current)
        self[key] = _max
        return _max


##------------------------------------------------------------------------
## словарик, к ключам которого можно обращаться как к полям объекта, dict.name 
class ClassDict(dict):
    """Dictionary behaving like an object."""
    def __getattr__(self, key):
        try:
            return self.get(key)
        except KeyError:
            raise AttributeError(key)

    def __getattrPickle__(self, key):
        try:
            if key == "__getstate__":
                return self.__getstate__
            else:
                return self[key]
        except KeyError:
            raise AttributeError(key)
            
    def __setattr__(self, key, value):
        self.__setitem__(key, value)

    def __getstate__(self):
        print "__getstate__ called"
        return self.__dict__

        

class ClassDictX(ClassDict):
    """ тот же ClassDict, только без строчного дампа """
    def __str__(self):
        # для случаев, когда у нас немеряных размеров словарь, дампить который целиком никуда не хочется. пишем только размер словаря
        return "ClassDictX(size %d)" % len(self)
        
    def __repr__(self):
        # для случаев, когда у нас немеряных размеров словарь, дампить который целиком никуда не хочется. пишем только размер словаря
        return "ClassDictX(size %d)" % len(self)


##------------------------------------------------------------------------
##------------------------------------------------------------------------

class ClassDictList:
    """encapsulates ClassDict, which must serialize in JSON as a list of values."""
    def __init__(self, json_list=[]):
        self.dct = ClassDict()
        self.load(json_list)
        
    def load(self, json_list):
        if isinstance(json_list, list) and len(json_list) and str( json_list[-1] ) == "$dict":
            self.dct.clear()
            json_list.pop() # выкидываем маркер $dict
            for val in json_list:
                self[ val ] = val
                
    def dump(self):
        val_list = self.dct.values()
        val_list.append( "$dict" )
        return val_list
                
    ####################################
    def __getitem__(self, key):
        return self.dct.__getitem__(key)
    
    def __setitem__(self, key, value):
        return self.dct.__setitem__(key, value)
        
    def __str__(self):
        return str(self.dct)

    def __repr__(self):
        return str(self.dct)
        
    def get(self, key, default=None):
        return self.dct.get(key, default)
        
    def pop(self, key, default=None):
        return self.dct.pop(key, default)
        
    def len(self):
        return len(self.dct)
        
    def keys(self):
        return self.dct.keys()
        
        

class DictListEncoder( json.JSONEncoder ):
    """сериализуем ClassDictList в список"""
    def default(self, obj):
        ## warn( "obj:" + str(obj))
        if isinstance(obj, ClassDictList):
            ## warn( "ClassDictList:list" )
            val_list = obj.dump()
            return val_list
        return json.JSONEncoder.default(self, obj)
        
        
class DictListNormalEncoder( json.JSONEncoder ):
    """сериализуем ClassDictList в нормальный словарь"""
    def default(self, obj):
        ## warn( "obj:" + str(obj))
        if isinstance(obj, ClassDictList):
            ## warn( "ClassDictList:normal" )
            return obj.dct
        return json.JSONEncoder.default(self, obj)


# специальный helper для "числовых ключей": если символьный ключ содержит только цифры, это, как ни странно, ЧИСЛОВОЙ ключ
def key2int(key):
    try:
        key_int = int(key)
        return key_int
    except Exception:
        return key


def enum2String( enumCls, value ):
    for k,v in vars(enumCls).iteritems():
        if v==value:
            return k
  

##------------------------------------------------------------------------
## helper для создания сильно вложенной иерархии словарей (и вставки значения на нужный уровень)
def subInsert( dct, key_tuple, value, force_int_keys=False ):
    try:
        subdict = dct
        nest_level = len(key_tuple)-1
        for key in key_tuple:
            if force_int_keys:
                key = key2int(key) # если символьный ключ содержит только цифры ("12345"), преобразуем к ЧИСЛОВОМУ ключу
            if nest_level:
                # раскапываем иерархию вложенных словарей (а там где словаря соотв. уровня нет, создаем новый)
                subdict[key] = subdict.get(key) or {}
                subdict = subdict[key]
                nest_level -= 1
            else:
                # все, докопали до дна; вставляем значение
                subdict[key] = value
                return subdict[key]
    except Exception:
        catch()

def index_exists(ls, i):
    return i < len(ls)

##------------------------------------------------------------------------
## helper для удаления из сильно вложенной иерархии словарей (с нужного уровня)
def subDelete( dct, key_tuple, force_int_keys=False ):
    try:
        subdict = dct
        nest_level = len(key_tuple)-1
        for key in key_tuple:
            if force_int_keys:
                key = key2int(key) # если символьный ключ содержит только цифры ("12345"), преобразуем к ЧИСЛОВОМУ ключу
            if nest_level:
                # раскапываем иерархию вложенных словарей (если какого-то уровня нет, возвращаем None: не удалили)
                subdict = subdict.get(key)
                if subdict:
                    nest_level -= 1
                else:
                    return None # not found
            else:
                # все, докопали до дна; удаляем значение (вернем value если оно было, иначе None)
                return subdict.pop(key, None)
    except Exception:
        #~ catch() ####
        return None

##------------------------------------------------------------------------
## helper для проверки существования сильно вложенной иерархии словарей (есть ли все ключи, вплоть до нужного уровня)
def subFind( dct, key_tuple, force_int_keys=False ):
    try:
        ##log( "subFind: tuple '%s', subdict %s" % (str(key_tuple), str(dct)) ) ####
        
        subdict = dct
        for key in key_tuple:
            if force_int_keys:
                key = key2int(key) # если символьный ключ содержит только цифры ("12345"), преобразуем к ЧИСЛОВОМУ ключу
            
            # раскапываем иерархию вложенных словарей (а там где словаря соотв. уровня нет, создаем новый)
            ##log( "subFind: key '%s', subdict %s" % (key, str(subdict)) ) ####
            
            #страхуемся от key == ''
            if key:
                subdict = subdict.get(key)
           
            if subdict is None:
                return None # not found
        
        # все, раскопали всю указанную иерархию; все ключи на месте, success (возвращаем последний раскопанный под-словарь)
        ##log( "subFind: fin subdict %s" % (str(subdict)) )
        return subdict
    except Exception:
        ##catch() ####
        return None
        

##------------------------------------------------------------------------
## те же самые операции, только не с кортежами, а с путями (типа "ItemsKeeper/Items/123/itemKey")
##  причем по умолчанию, если некий символьный ключ содержит только цифры ("12345"), преобразуем его к ЧИСЛОВОМУ ключу 
# ------------------------------------------------------------------------
# helper для создания сильно вложенной иерархии словарей (и вставки значения на нужный уровень)
def pathInsert( dct, path, value, force_int_keys=True ): # force_int_keys: если символьный ключ содержит только цифры ("12345"), преобразуем к ЧИСЛОВОМУ ключу
    return subInsert( dct, path.split('/'), value, force_int_keys ) 
# ------------------------------------------------------------------------
# helper для удаления из сильно вложенной иерархии словарей (с нужного уровня)
def pathDelete( dct, path, force_int_keys=True ): # force_int_keys: если символьный ключ содержит только цифры ("12345"), преобразуем к ЧИСЛОВОМУ ключу
    return subDelete( dct, path.split('/'), force_int_keys ) 
# ------------------------------------------------------------------------
# helper для проверки существования сильно вложенной иерархии словарей (есть ли все ключи, вплоть до нужного уровня)
def pathFind( dct, path, force_int_keys=True ): # force_int_keys: если символьный ключ содержит только цифры ("12345"), преобразуем к ЧИСЛОВОМУ ключу
    return subFind( dct, path.split('/'), force_int_keys )

##------------------------------------------------------------------------
## helper для создания сильно вложенной иерархии словарей или классов (и вставки значения на нужный уровень)
def subInsertKeyAttr( dct, key_tuple, value, force_int_keys=False ):
    try:
        subdict = dct
        nest_level = len(key_tuple)-1
        for key in key_tuple:
            if force_int_keys:
                key = key2int(key) # если символьный ключ содержит только цифры ("12345"), преобразуем к ЧИСЛОВОМУ ключу
            if nest_level:
                # раскапываем иерархию вложенных словарей (а там где словаря соотв. уровня нет, создаем новый)
                try:
                    subdict[key] = subdict.get(key) or {}
                    subdict = subdict[key]
                except Exception:
                    # dict-style (dict[key]) не получилось, попробуем class-style (obj.attr)
                    setattr( subdict, key, getattr(subdict, key, None) or {} )
                    subdict = getattr(subdict, key, None)
                    
                nest_level -= 1
            else:
                # все, докопали до дна; вставляем значение
                try:
                    subdict[key] = value
                    return subdict[key]
                except Exception:
                    # dict-style (dict[key]) не получилось, попробуем class-style (obj.attr)
                    setattr( subdict, key, value )
                    return getattr( subdict, key, None)
    except Exception:
        catch()

# helper для создания сильно вложенной иерархии словарей (и вставки значения на нужный уровень)
def pathInsertKeyAttr( dct, path, value, force_int_keys=True ): # force_int_keys: если символьный ключ содержит только цифры ("12345"), преобразуем к ЧИСЛОВОМУ ключу
    return subInsertKeyAttr( dct, path.split('/'), value, force_int_keys ) 

# ------------------------------------------------------------------------
# helper: разобьем путь на "родительский" и "дочерний" (== путь к родителю указанного объекта + ключ самого объекта)
def pathParentChild( path, force_int_keys=True ):
    ncut = path.rfind('/')
    if ncut >= 0:
        parent = path[:ncut]
        key = path[(ncut+1):]
    else:
        # если нету слэша, путь у нас "верхнего уровня"; значит "родительский" для него путь будет пустой (==корень Model Data), а дочерний ключ == самому пути
        parent = ""
        key = path
    
    if force_int_keys:
        key = key2int( key ) # если ключ числовой, вернем сразу число
    
    return parent, key 
    
# ------------------------------------------------------------------------
# helper: вернем путь "на один элемент выше" (==путь к родителю указанного объекта)
def pathParent( path, force_int_keys=True ):
    return pathParentChild( path, force_int_keys )[0]

# ------------------------------------------------------------------------
# helper: вытащим из пути "корневой" элемент 
def pathRoot( path, force_int_keys=True ):
    ncut = path.find('/')
    if ncut >= 0:
        root = path[:ncut]
    else:
        # если нету слэша, путь у нас "верхнего уровня"; значит "родительский" для него путь будет пустой (==корень Model Data), а дочерний ключ == самому пути
        root = path
        
    if force_int_keys:
        root = key2int( root ) # если ключ числовой, вернем сразу число -- хотя вообще-то на корневом уровне Model Data id-шек нет.. ну да мало ли потом.
        
    return root
    

#-------------------------------------------
# helper: выполняем srcDict.update( fromDict ) НЕ переписывая существующие значения, являющиеся словарями 
# (чтобы не поломать классы-наследники dict: ClassDict, ClassDictList.. по умолчанию update заменит их на простые dict)
def subDictUpdate( srcDict, fromDict ):
    for from_key, from_val in fromDict.iteritems():
        src_val = srcDict.get(from_key)
        ## warn( "key: %s, src_val: %s (class %s), from_val: %s (class %s)" % ( from_key, src_val, str(src_val.__class__), from_val, str(from_val.__class__) )  )
        
        if (src_val is not None) and isinstance(src_val, dict):
            # DICT: recurse
            subDictUpdate( src_val, from_val )
        else:
            # all other values: insert/replace
            srcDict[from_key] = from_val
            
def subDictUpdateListsAppend( srcDict, fromDict ):
    for from_key, from_val in fromDict.iteritems():
        src_val = srcDict.get(from_key)
        ## warn( "key: %s, src_val: %s (class %s), from_val: %s (class %s)" % ( from_key, src_val, str(src_val.__class__), from_val, str(from_val.__class__) )  )
        
        if (src_val is not None) and isinstance(src_val, dict):
            # DICT: recurse
            subDictUpdate( src_val, from_val )
        elif isinstance(src_val, list) and isinstance(from_val, list):
            # LIST: append list values
            src_val.extend( from_val )
        else:
            # all other values: insert/replace
            srcDict[from_key] = from_val


#-------------------------------------------
# helper: создаем из иерархии вложенных обычных словарей новую иерархию, в которой все словари ClassDict
def createClassDict( fromDict ):
    cdict = ClassDict()
    for from_key, from_val in fromDict.iteritems():
        if isinstance(from_val, dict):
            cdict[from_key] = createClassDict( from_val )
        else:
            cdict[from_key] = from_val
    return cdict
            
# ------------------------------------------------------------------------
# удобно для задания словарей в классах, чтобы они наследовались (собирали наборы key:value) от нескольких словарей сразу
def mergeDicts( *varargs ):
    res = dict()
    for dct in varargs:
        res.update( dct )
    return res


# ------------------------------------------------------------------------
# как ни странно, у словаря нету метода, возвращающего первую (любую) пару k,v без разрушения
def getFirstPair(dct):
    if dct:
        for k,v in dct.iteritems():
            return k,v
    return None,None

# ------------------------------------------------------------------------
# возвращаем первый по алфавиту ключ (и его value)
def getFirstSortedPair(dct):
    keys = sorted( dct.keys() )
    if keys:
        k = keys[0]
        return k, dct.get(k)
    return None,None

##------------------------------------------------------------------------
## http parameter packing, "&key=value&..."
def makeParamString( param_list ):
    param_string = ""
    if param_list:
        for key,arg in param_list.iteritems():
            param_string += "&%s=%s" % (key, arg)
        ##info( "param_list: %r, param_string: %r" % (param_list, param_string) )
    return param_string

def strList(list_, divider=','):
    return divider.join(map(str, list_)) if list_ else ''

def reprList(list_, divider=','):
    return divider.join(map(repr, list_)) if list_ else ''

##------------------------------------------------------------------------

def makeSignedRequest( params, secret="" ):
    request, sign = _makeSignedRequest( params, secret=secret )
    return request

def _makeSignedRequest( params, secret="" ):
    encoded_request = urllib.urlencode(params)
    reversed_params_dict = urlparse.parse_qs(encoded_request)

    sign = "-"
    if reversed_params_dict:
        md5_concat = ""
        for k in sorted(reversed_params_dict.keys()):
            vlist = reversed_params_dict[k]
            md5_concat += str(k) + (''.join(map(str, vlist)))
        # на конце остается лишний '&', как раз для подписи
        md5_concat += str(secret)
        debug("_makeSignedRequest: md5_concat=%s", md5_concat)
        sign = hashlib.md5( md5_concat ).hexdigest()
        encoded_request += "&sign=%s" % sign
    return encoded_request, sign

def makeParamsSignature( params, secret="" ):
    request, sign = _makeSignedRequest( params, secret=secret )
    return sign


def checkParamsSignature( params, secret="" ):
    if params:
        original_sign = params.pop("sign", "")
        params.pop( "post_data", "" )
        check_sign = makeParamsSignature( params, secret )
        (debug if original_sign==check_sign else info)(
            "orig. sign: %r, check sign: %r, match: %s", original_sign, check_sign, (original_sign==check_sign))
        return original_sign == check_sign

##------------------------------------------------------------------------

# ищем в иерархии словарей-списков urllib-quoted строчки (с символами %7C %20 и т.п.) и unquote их
def recurse_unquote( cont ):
    if cont:
        changed = 0
        if isinstance( cont, dict ):
            for key, val in cont.iteritems():
                unquoted = recurse_unquote(val)
                if unquoted:
                    cont[key] = unquoted
                    changed = 1
                    
        elif isinstance( cont, list ):
            for i, val in enumerate(cont):
                unquoted = recurse_unquote(val)
                if unquoted:
                    cont[i] = unquoted
                    changed = 1
            
        elif isinstance( cont, basestring ):
            try:
                unquoted = urllib.unquote(cont)
                if unquoted != cont:
                    info( "UNQUOTED: %r, was %r", unquoted, cont)
                    return unquoted
            except Exception:
                pass

        if changed:
            return cont
        

# ищем в иерархии словарей-списков ключи вида "json_xxx" и распаковываем их из json
def recurse_unjson( cont, json_load_function=json_load_transform ):
    if cont:
        changed = 0
        if isinstance( cont, dict ):
            for key, val in cont.items():
                if isinstance(key, basestring) and (key[:5] == "json_"):
                    try:
                        unquoted = json_load_function( val ) 
                        new_key = key[5:]
                        cont.pop( key )
                        cont[ new_key ] = unquoted
                        changed = 1
                    except Exception:
                        catch()
                        pass
                    
        elif isinstance( cont, list ):
            for i, val in enumerate(cont):
                unquoted = recurse_unjson(val)
                if unquoted:
                    cont[i] = unquoted
                    changed = 1
            
        if changed:
            return cont
    
##------------------------------------------------------------------------
## keepalive helper (апдейтим timestamp в словаре acc[], по смысле -- продлеваем время активной сессии текущего юзера)
def touch( acc, stamp=0 ):
    if acc:
        if not stamp:
            stamp = int(time.time())
        if acc.get("ka", 0) < stamp:
            acc["ka"] = stamp

##------------------------------------------------------------------------
def utf8convert( value ):
    if isinstance(value, unicode):
        return value.encode("utf8")
    else:
        return str(value)
    
def uniConvert( value ):
    if isinstance(value, unicode):
        return value
    else:
        return unicode(value, "utf8")

def latin2utf(value):
    return unicode(value, 'latin1').encode('utf8')

##------------------------------------------------------------------------
def isAddressInternal(address):
    tokens = address.split('.')
    if len(tokens) > 0:
        if int(tokens[0]) in [10, 192, 127]:
            return True
    return False

def getHost(useExternal=False, useOpposite=False):
    name = socket.gethostname()
    name, aliases, ips = socket.gethostbyname_ex(socket.gethostname())
    if len(ips) > 0:
        internal = []
        external = [] 
        for ip in ips:
            if isAddressInternal(ip):
                internal.append(ip)
            else:
                external.append(ip)
        if useExternal:
            if len(external) > 0:
                return external[0]
            elif useOpposite:
                return internal[0]
        else:
            if len(internal) > 0:
                return internal[0]
            elif useOpposite:
                return external[0]
    raise Exception('No host found (external=%d ips=%s)' % (useExternal, ips))

HTTP_PREFIX = "http://"
LEN_HTTP_PREFIX = len(HTTP_PREFIX)

def http_prefix(url):
    if url[ :LEN_HTTP_PREFIX ] != HTTP_PREFIX:
        return HTTP_PREFIX + url
    return url

# ------------------------------------------------------
def randomMD5():
    return hashlib.md5( str(time.time()) ).hexdigest()

def dumpResponse( response ):
    info("dumpResponse: %r" % response )
    
# ------------------------------------------------------
def tryInc(obj, key, inc_value):
    if key not in obj:
        obj[key] = 0
    obj[key] += inc_value

def tryexcept(func):
    def silenceit(*args,**kwargs):
        try:
            return func(*args,**kwargs)
        except Exception:
            catchFull()
    return silenceit

# ------------------------------------------------------
# xor two strings of different lengths
def strxor(a, b):     
    if len(a) > len(b):
        return "".join([chr(ord(x) ^ ord(y)) for (x, y) in zip(a[:len(b)], b)])
    else:
        return "".join([chr(ord(x) ^ ord(y)) for (x, y) in zip(a, b[:len(a)])])


def loadTechsFromFile():
    ####
    # Returns doct of
    # revision => {
    #     compensationType => seconds,
    #     ...
    # }
    techs = {}
    path = os.path.dirname(os.path.realpath(__file__))
    techsFile = os.path.normpath( os.path.join(path, "../config/techs.txt"))
    try:
        file = open(techsFile, "r")
        lines = file.readlines()
        file.close()
    except IOError, e:
        err("Can't load techs: %s", e)
        return techs
    line_num = 0
    for line in lines:
        line_num += 1
        try:
            tokens = line.split()
            if len(tokens) < 3:
                raise Exception("Bad techs.txt format in line %d, skip: %r", line_num, line)
            revision = int(tokens[0])
            compensationTypes = tokens[1].split(',')
            tech = techs.get(revision, {}) # multiple lines for one revision (and different types) are possible
            seconds = int(tokens[2])
            for compensationType in compensationTypes:
                if compensationType in ("lamp", "premium", "rating", "guild_buffs", "sieges"):
                    tech[compensationType] = seconds
                else:
                    warn("loadTechsFromFile: Unknown compensationType '%s' in line %s", compensationType, line_num)
            if tech:
                techs[revision] = tech
        except Exception, e:
            if len(e.args) > 1 and type(e.args[0]) is str:
                err(*e)
            else:
                err(e)
    return techs


def timeouts_iterator(it):
    "Iterates over all values in 'it', further repeat the last element endlesly"
    save = None
    for p in it:
        save = p
        yield p
    while True:
        yield save

# Wrapper classses for use in logging calls.
# Postpone data formatting for a logging string formatting time, so
# if loglevel prevent that string output, time consuming formatting wont be called.

class PostponeStr:
    __slots__ = ('method', 'data')
    def __init__(self, method, data):
        self.method = method
        self.data = data

    def __str__(self):
        return self.method(self.data)


class PostponePretty:
    __slots__ = ('data')
    def __init__(self, data):
        self.data = data

    def __str__(self):
        return pretty(self.data)


def SendStats(ISTATS):
    if ISTATS:
        ts = time.clock()
        try:
            ISTATS.Send()
        except:
            catch()
        ts = time.clock()-ts
        if ts > 0.005:
            info("STATS.Send time: %.3f", ts)

class AllResponseCollector(object):
    def __init__(self, peers_count, callback):
        self.count = peers_count
        self.ready = 0
        self.data = []
        self.callback = callback

    def onResponse(self, response, peer):
        if response:
            if response.get("ok"):
                self.addResponse(response, peer)
            elif response.get("ec"):
                self.addError(response, peer)
        self.ready += 1
        if self.ready == self.count:
            info("AllResponseCollector.onResponse callback data %r" % self.data)
            self.callback(self.data)

    def addResponse(self, response, peer):
        pass # TO OVERRIDE

    def addError(selfself, error, peer):
        pass

def nextMsgID():
    if hasattr(signal, "getitimer"):
        good_timer_function = time.time
    else:
        good_timer_function = time.clock
    return long( good_timer_function() * 10000000 )