import xml.sax
import xml.sax.handler

class Container:

    def __init__(self, name, attributes):
        self.__attributes = attributes
        self.__parent = None
        self.__name = name 
        self.__content = ''
        
    def addChild(self, name, container):
        if name in self.__dict__:
            self.__dict__[name].append(container)
        else:
            self.__dict__[name] = [container]
        container.parent = self            
                
    def __getitem__(self, name):
        if type(name) == str:
            return self.__dict__[name][0]
        else:            
            return self.parent.__dict__[self.__name][name]
            
    def has(self, name):
        return name in self.__dict__        
        
    def __call__(self, name):
        return self.__attributes[name]
        
    def addCharacters(self, content):
        self.__content += content

    def get(self):
        return self.__content
        
    def getName(self):
        return self.__name
        
    def getAttributes(self):
        return self.__attributes        
                
                        
class Parser(xml.sax.handler.ContentHandler):

    def __init__(self):
        self.stack = [Container('root', {})]
        self.root = self.stack[-1]
        self.error = None
        
    def startElement(self, name, attrs):
        c = Container(name, attrs)
        self.stack[-1].addChild(name, c)
        self.stack.append(c)

    def characters(self, content):
        self.stack[-1].addCharacters(content)        

    def endElement(self, name):
        self.stack.pop()
        
    def __getitem__(self, name):
        return self.__dict__[name]        
        
    def setError(self, error):
        self.error = error        

def parseString(text):        
    p = Parser()
    try:
        xml.sax.parseString(text, p)
    except xml.sax.SAXParseException, details:
        p.setError(details)
    return p    
            
class Container2:

    def __init__(self, name, attrs=None):   
        self._name = name
        self._content = ''
        self._attrs = attrs
        self._sections = []
        
    def getName(self):
        return self._name        
        
    def enum(self, processor):
        if not processor.process(self):
            processor.incLevel(self)
            for section in self._sections:
                section.enum(processor)
            processor.decLevel(self)
        
    def addChild(self, child):
        self.__dict__[child.getName()] = child
        self._sections.append(child)

    def has(self, name):
        return name in self.__dict__
        
    def __getattr__(self, name):
        if name in self.__dict__:
            return self.__dict__[name]
        return self._attrs[name]            
        
    def __eq__(self, other):
        return other == self._content
        
    def __getitem__(self, key):
        return self.__dict__[key]
        
    def __str__(self):
        return self._content        
        
    def __iter__(self):
        for section in self._sections:
            yield section        
        
    def __len__(self):
        return len(self._sections)
        
    def __repr__(self):
        return '%s at %x' % (self._name, id(self))         
            
class Parser2(xml.sax.handler.ContentHandler):

    def __init__(self):
        self._tokens = [Container2('<root>')]

    def startElement(self, name, attrs):
        container = Container2(name, attrs)
        self._tokens[-1].addChild(container)
        self._tokens.append(container)

    def characters(self, content):
        self._tokens[-1].__dict__['_content'] += content

    def endElement(self, name):
        self._tokens.pop()
        
    def setError(self, error):
        self.error = error
        
    def __getattr__(self, name):
        return self._tokens[0].__getattr__(name)

    def enum(self, processor):
        self._tokens[0].enum(processor)
                
    def __getitem__(self, key):
        return self._tokens[0].__getitem__(key)
        
    def has(self, name):
        return self._tokens[0].has(name)        
                        
def parseString2(text):
    p = Parser2()
    try:
        xml.sax.parseString(text, p)
    except xml.sax.SAXParseException, details:
        p.setError(details)
    return p    
    