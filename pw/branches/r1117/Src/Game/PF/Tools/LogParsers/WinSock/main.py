import sys
import xml.etree.ElementTree
import cStringIO

class XmlAccessor:

    def __init__(self, element):
        self.element = element

    def __str__(self):
        return str(self.element)

    def __getattr__(self, name):
        for e in self.element.getchildren():
            if e.tag.endswith(name):
                return XmlAccessor(e)
        return self.element.get(name)

    def text(self):
        return self.element.text.strip()

    def __iter__(self):    
        for e in self.element:
            yield XmlAccessor(e)

class XmlTree(XmlAccessor):

    def __init__(self, io):
        tree = xml.etree.ElementTree.ElementTree()
        XmlAccessor.__init__(self, tree.parse(io))

if len(sys.argv) == 4:
    src = open(sys.argv[1], 'rb')
    level = sys.argv[2]
    process = sys.argv[3]
else:
    print 'Usage: main.py <log file> <log level> <process id>'
    sys.exit(1)

print '<Events>'

content = ''
eventStarted = False
for line in src.readlines():
    if line.startswith('<Event '):
        eventStarted = True
    if eventStarted:
        content += line
    if line.startswith('</Event>'):
        eventStarted = False
        event = XmlTree(cStringIO.StringIO(content))
        s = event.System
		ed = event.EventData

    if s.Level.text() == level :
        for d in ed:
				    if d.Name == "Process" and d.text() == process:
            		sys.stdout.write(content)
				        break

        #    e = event.EventData
        #    for d in e:        
        #        print d.Name, d.text()
        content = ''
print '</Events>'
