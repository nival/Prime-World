from logging import debug

class ConnectionError(Exception):
    pass

class MockRedisPipe:
    
    def __init__(self, client):
        self.items = []
        self.client = client

    def setex(self, *args):
        self.items.append( ('setex', args) )

    def incr(self, *args):
        self.items.append( ('incr', args) )

    def hset(self, *args):
        self.items.append( ('hset', args) )

    def hdel(self, *args):
        self.items.append( ('hdel', args) )

    def incrby(self, *args):
        self.items.append( ('incrby', args) )

    def lrem(self, *args):
        self.items.append( ('lrem', args) )

    def mget(self, *args):
        self.items.append( ('mget', args) )

    def setbit(self, *args):
        self.items.append( ('setbit', args) )

    def get(self, *args):
        self.items.append( ('get', args) )

    def ttl(self, *args):
        self.items.append( ('ttl', args) )

    def hincrby(self, *args):
        self.items.append( ('hincrby', args) )

    def hmget(self, *args):
        self.items.append( ('hmget', args) )

    def hmset(self, *args):
        self.items.append( ('hmset', args) )

    def hget(self, *args):
        self.items.append( ('hget', args) )

    def lpush(self, *args):
        self.items.append( ('lpush', args) )

    def rpoplpush(self, *args):
        self.items.append( ('rpoplpush', args) )

    def llen(self, *args):
        self.items.append( ('llen', args) )

    def expire(self, *args):
        self.items.append( ('expire', args) )

    def persist(self, *args):
        self.items.append( ('persist', args) )

    def execute(self, callback=None):
        results = []
        for name, value in self.items:
            func = getattr(self.client, '_'+name)
            result = func(*value)
            debug('-> %r', result)
            results.append(result)
        self.items = []
        if callback:
            callback(results)

class MockRedisClient:

    def __init__(self):
        self.items = {}
        self._expires = {}
        self.isTimedOut = False

    def Reset(self):
        self.items.clear()
        self._expires.clear()

    def _setnx(self, key, value):
        debug('setnx(%r, %r)', key, value)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")

        if key in self.items:
            return False
        else:
            self.items[key] = value
            return True

    def setnx(self, key, value, callback=None):
        result = self._setnx(key, value)
        debug('-> %r', result)
        if callback:
            callback(result)

    def incr(self, key, callback):
        self.incrby(key, 1, callback)

    def _lrem(self, key, value, count):
        debug('lrem(%r, %r, %r)', key, value, count)
        l = self.items.get(key, [])
        if len(l) == 0:
            return 0
        result = 0
        if count == 0:
            count = len(l)
        while count > 0:
            try:
                i = l.index(value)
                del l[i]
                result += 1
                count -= 1
            except ValueError:
                break
        return result

    def _lpush(self, key, value):
        debug('lpush(%r, %r)', key, value)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")
        if key not in self.items:
            self.items[key] = []

        self.items[key].append(value)
        return len(self.items[key])

    def lpush(self, key, value, callback=None):
        result = self._lpush(key, value)
        debug('-> %r', result)
        if callback:
            callback(result)

    def lrem(self, key, count, value, callback=None):
        result = self._lrem(key, count, value)
        debug('-> %r', result)
        if callback:
            callback(result)

    def _setex(self, key, expire, value):
        debug('setex(%r, %r, %r)', key, expire, value)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")
        self.items[key] = value
        self._expires[key] = expire
        return True

    def setex(self, key, expire, value, callback=None):
        result = self._setex(key, expire, value)
        debug('-> %r', result)
        if callback:
            callback(result)

    def pipeline(self):
        return MockRedisPipe(self)

    def _mget(self, keys):
        debug('mget(%r)', keys)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")

        result = []
        for key in keys:
            value = self.items.get(key, None)
            if value != None:
                result.append(str(value))
            else:
                result.append(value)
        return result
                        
    def _incr(self, key):
        return self._incrby(key, 1)
        
    def _incrby(self, key, value):
        debug('incrby(%r, %r)', key, value)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")

        if key not in self.items:
            self.items[key] = 0
        self.items[key] += value
        return self.items[key]

    def _hincrby(self, key, field, value):
        debug('hincrby(%r, %r, %r)', key, field, value)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")

        if key not in self.items:
            self.items[key] = {}
        if field not in self.items[key]:
            self.items[key][field] = 0
        self.items[key][field] += value
        return self.items[key][field]

    def _hset(self, key, field, value):
        debug('hset(%r, %r, %r)', key, field, value)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")

        if key not in self.items:
            self.items[key] = {}
        result = 0
        if field not in self.items[key]:
            result = 1
        self.items[key][field] = value
        return result

    def _hdel(self, key, *fields):
        debug('hdel(%r, %r)', key, fields)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")

        if key not in self.items:
            return 0

        result = 0
        for field in fields:
            if field in self.items[key]:
                result += 1
                del self.items[key][field] 
        return result

    def _get(self, key):
        debug('get(%r)', key)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")

        return self.items.get(key, None)

    def get(self, key, callback):
        result = self._get(key)
        debug('-> %r', result)
        if callback:
            callback(result)

    def _ttl(self, key):
        debug('ttl(%r)', key)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")
        return self._expires.get(key, -1)

    def ttl(self, key, callback=None):
        result = self._ttl(key)
        debug('-> %r', result)
        if callback:
            callback(result)
        else:
            return result

    def _expire(self, key, value):
        debug('expire(%r, %r)', key, value)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")
        if key in self.items:
            self._expires[key] = value
            return 1
        return 0

    def _persist(self, key):
        debug('persist(%r)', key)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")
        if key in self.items and key in self._expires:
            del self._expires[key]
            return 1
        return 0

    def expire(self, key, value, callback=None):
        result = self._expire(key, value)
        debug('-> %r', result)
        if callback:
            callback(result)

    def incrby(self, key, value, callback):
        result = self._incrby(key, value)
        debug('-> %r', result)
        if callback:
            callback(result)

    def hincrby(self, key, field, value, callback=None):
        result = self._hincrby(key, field, value)
        debug('-> %r', result)
        if callback:
            callback(result)

    def hset(self, key, field, value, callback=None):
        result = self._hset(key, field, value)
        debug('-> %r', result)
        if callback:
            callback(result)

    def hdel(self, key, fields,callback=None):
        result = self._hdel(key, fields)
        debug('-> %r', result)
        if callback:
            callback(result)

    def _setbit(self, key, offset, value):
        debug('setbit(%r, %r, %r)', key, offset, value)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")

        index = offset / 32
        shift = offset % 32
        data = self.items.get(key, None)
        if type(data) != list:
            data = [0]*(index+1)
            self.items[key] = data
        if index >= len(data):
            data.extend([0]*(index-len(data)+1))
        pvalue = ((data[index] & (1 << shift)) >> shift)
        if value == 0:
            data[index] = (data[index] & ~(1 << shift))
        else:
            data[index] = (data[index] | (1 << shift))
        return pvalue

    def _getbit(self, key, offset):
        debug('getbit(%r, %r)', key, offset)
        if self.isTimedOut:
            raise ConnectionError("Redis timed out")

        index = offset / 32
        shift = offset % 32
        data = self.items.get(key, None)
        if data == None:
            return 0
        if type(data) != list:
            return None
        if index >= len(data):
            return 0
        pvalue =  (data[index] & (1 << shift)) >> shift
        return pvalue 

    def setbit(self, key, offset, value, callback):
        result = self._setbit(key, offset, value)
        debug('-> %r', result)
        if callback:
            callback(result)

    def getbit(self, key, offset, callback):
        result = self._getbit(key, offset)
        debug('-> %r', result)
        if callback:
            callback(result)
        
    def mget(self, keys, callback):
        result = self._mget(keys)
        debug('-> %r', result)
        if callback:
            callback(result)

    def _hmget(self, key, fields):
        debug('hmget(%r, %r)', key, fields)
        if self.isTimedOut:           
            raise ConnectionError("Redis timed out")

        result = {}
        for field in fields:
            result[field] = self.items.get(key, {}).get(field, None)
        return result

    def _hmset(self, key, fields):
        debug('hmset(%r, %r)', key, fields)
        if self.isTimedOut:           
            raise ConnectionError("Redis timed out")

        for field, value in fields.items():
            self.items[key][field] = value
        return 1

    def _hget(self, key, field):
        debug('hget(%r, %r)', key, field)
        if self.isTimedOut:           
            raise ConnectionError("Redis timed out")

        return self.items.get(key, {}).get(field, None)

    def hmget(self, key, fields, callback=None):
        result = self._hmget(key, fields)
        debug('-> %r', result)
        if callback:
            callback(result)
        
    def hget(self, key, field, callback=None):
        result = self._hget(key, field)
        debug('-> %r', result)
        if callback:
            callback(result)
        else:
            return result

    def _llen(self, key):
        debug('llen(%r)', key)
        if self.isTimedOut:           
            raise ConnectionError("Redis timed out")

        d = self.items.get(key, None)
        if d != None:
            return len(d)

    def llen(self, key, callback=None):
        result = self._llen(key)
        debug('-> %r', result)
        if callback:
            callback(result)

    def _rpoplpush(self, src, dst):
        debug('rpoplpush(%r, %r)', src, dst)
        if self.isTimedOut:           
            raise ConnectionError("Redis timed out")
        
        s = self.items.get(src, None)
        if s == None:
            return None
        if len(s) == 0:
            return None
        d = self.items.get(dst, None)
        if d == s:
            v = s.pop()
            d.insert(0, v)
            return v
        else:
            if d == None:
                d = []
                self.items[dst] = d
            v = s.pop()
            d.append(v)
            return v    

    def rpoplpush(self, src, dst, callback=None):
        result = self._rpoplpush(src, dst)
        debug('-> %r', result)
        if callback:
            callback(result)
