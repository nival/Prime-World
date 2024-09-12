import exc_handle
import base64
import string
import os
import tokenize
import os
import cStringIO
import json


def ExtractContent(_content):
    return base64.b64decode(_content)

def ExtractToFolder(folder, files):
    path = None
    for name, _content in files:
        content = ExtractContent(_content)
        fname = os.path.join(folder, name)
        f = open(fname, 'wb')
        f.write(content)
        if path == None:
            path = fname
    return path

class InMemoryFS:

    def __init__(self, files):
        self.files = files

    def Load(self, name):
        for _name, content in self.files:
            if _name == name:
                return ExtractContent(content)
        raise Exception('File not found (name=%r)' % name)


class DiskFS:

    def __init__(self, folder):
        self.folder = folder

    def Load(self, name):
        fname = os.path.join(self.folder, name)
        if os.path.isfile(fname):
            f = open(fname, 'rb')
            return f.read()
        raise Exception('File not found (name=%r)' % name)

class _Config(object):

    def __init__(self, fs, name, cglobals={}):
        self.fs = fs
        self.processed = []
        self.failed = []
        self.data = {}
        self.errors = []
        self.acquire = None
        self._name = name
        self.Refresh(cglobals)

    def _Reset(self):
        self.data.clear()
        self.processed = []
        self.failed = []
    
    def GetRaw(self):
        return self.data
    
    def Acquire(self, what, default=None):
        if self.acquire:
            result = self.acquire(what, default)
            if result == None:
                return default
            return result
        return default

    def Refresh(self, cglobals={}, acquire=None):
        self.acquire = acquire
        self.cglobals = cglobals
        self._Reset()
        self.Include(self._name)
        return self.data

    def Include(self, name):
        try:    
            if name not in self.processed:
                content = self.fs.Load(name)
                if content != None:
                    content = content.replace('\r', '')
                    self.processed.append(name)
                    repeat = True
                    globalVars = dict(self.cglobals)
                    globalVars['include'] = self.Include                         
                    globalVars['acquire'] = self.Acquire
                    while repeat:
                        try:
                            exec(content, globalVars, self.data)    
                            repeat = False
                        except NameError, details:
                            s = str(details)
                            p = "name '"
                            i = s.find(p)
                            if i >= 0:
                                j = s.rfind("'")
                                if j >= 0:
                                    globalVars[s[i+len(p):j]] = '<null>'
                else:
                    self.failed.append(name)
        except Exception:
            self.errors.append( (name, str(exc_handle.getException())) )
            return False
        return True

    def __getattr__(self, name):
        if name in self.data:
            return self.data[name]
        return self.__dict__.get(name, None)

    def __getitem__(self, name):
        return self.data.get(name, None)

class Config(_Config):

    def __init__(self, files, cglobals={}):
        super(Config, self).__init__(InMemoryFS(files), files[0][0], cglobals)

class SimpleConfig(_Config):

    def __init__(self, content, cglobals={}):
        super(SimpleConfig, self).__init__(InMemoryFS([('<root>', base64.b64encode(content))]), '<root>', cglobals)

class DiskConfig(_Config):

    def __init__(self, name, cglobals={}):
        head, tail = os.path.split(name)
        super(DiskConfig, self).__init__(DiskFS(head), tail, cglobals)

class RawConfigWrapper:

    def __init__(self, data={}):
        self.data = data

    def __getitem__(self, name):
        item = self.data.get(name, None)
        if type(item) == dict:
            return RawConfigWrapper(item)
        return item

    def __getattr__(self, name):
        result = self.data.get(name)
        if type(result) == dict:
            return RawConfigWrapper(result)
        return result

    def __str__(self):
        return self.data.__str__()

    def __nonzero__(self):
        return len(self.data) > 0

    def items(self):
        result = []
        for key, value in self.data.items():
            if type(value) == dict:
                result.append( (key, RawConfigWrapper(value)) )
            else:
                result.append( (key, value) )
        return result

    def keys(self):
        return self.data.keys()

    def get(self, name, default=None):
        item = self.data.get(name, None)
        if not item:
            return default
        if type(item) == dict:
            return RawConfigWrapper(item)
        return item

    def __iter__(self):
        return self.data.__iter__()
        
    def __contains__(self, item):
        return self.data.__contains__(item)
        

class RawConfig:

    def __init__(self, data):
        if type(data) == str:
            f = open(data, 'rb')
            self.data = json.load(f)
        else:
            self.data = data

    def __getattr__(self, name):
        result = self.data.get(name)
        if type(result) == dict:
            return RawConfigWrapper(result)
        return result
        
    def __str__(self):
        return self.data.__str__()

    def GetRaw(self):
        return self.data
        