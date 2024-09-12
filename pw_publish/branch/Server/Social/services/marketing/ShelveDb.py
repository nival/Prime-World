import time
import shelve

class PersistentEventsQueue:
    def __init__(self, db):
        self.db = db

    def Push(self, auid, data):
        eid = self.db.get('eid', 0)
        eid += 1
        self.db['eid'] = eid

        self.db['e' + str(eid)] = data

        key = 'a' + str(auid)
        queue = self.db[key]
        if queue is None:
            queue = []
            self.db['ucount'] = self.db.get('ucount', 0) + 1
        self.db['ecount'] = self.db.get('ecount', 0) + 1
        queue.append(eid)
        self.db[key] = queue
        return len(queue)

    def GetAllAuids(self):
        result = []
        for k in self.db.keys():
            if k.startswith('a'):
                result.append(int(k[1:]))
        print result
        return result


    def Retrieve(self, auid):
        key = 'a' + str(auid)
        _queue = self.db[key]
        if _queue is None:
            return []

        queue = []
        for eid in _queue:
            data = self.db['e' + str(eid)]
            if data:
                queue.append(data)
        return queue

    def Clear(self, auid):
        key = 'a' + str(auid)
        _queue = self.db[key]
        if _queue is None:
            return
        if len(_queue) > 0:
            for eid in _queue:
                try:
                    del self.db['e' + str(eid)]
                except:
                    pass
            del self.db[key]
            self.db['ucount'] = self.db.get('ucount', 0) - 1
            self.db['ecount'] = self.db.get('ecount', 0) - len(_queue)

from logging import debug
class ShelveDatabase:

    def __init__(self, path, flush_period):
        self.db = shelve.open(path)
        self.flushTime = time.time() + flush_period
        self.flushPeriod = flush_period
        self.isDirty = False
        self.isClosed = False

    def __getitem__(self, key):
        return self.db.get(key, None)

    def __setitem__(self, key, value):
        self.db[key] = value
        self.isDirty = True

    def __delitem__(self, key):
        del self.db[key]
        self.isDirty = True

    def has_key(self, key):
        return self.db.has_key(key)

    def keys(self):
        return self.db.keys()

    def get(self, key, default=None):
        return self.db.get(key, default)

    def Stop(self):
        self.Flush(True)

    def Flush(self, close=False):
        if self.isClosed:
            return
        if close:
            self.isClosed = True
            self.db.close()
        elif self.isDirty:
            self.db.sync()
            self.isDirty = False

    def Update(self):
        curTime = time.time()
        if curTime > self.flushTime and self.isDirty:
            self.Flush(False)
            self.flushTime = curTime + self.flushPeriod

    def IsClosed(self):
        return self.isClosed
