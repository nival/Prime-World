from os import path
from codecs import open
import re

nodeNames = ['dispatchEffect', 'applyEffect', 'effect']

effectIdToLink = {
'Empty' : '',
'Revival' : '/Effects/Revival/_1.EFFT',
'LevelUp' : '/Effects/LevelUp/_.EFFT',
'TestBullet' : '/Effects/Spells/TestSpell/_.EFFT',
'TestAura' : '/Effects/Selection/Sylvan.EFFT',
'TestAura1' : '/Effects/Selection/Heven.EFFT',
'TestAura2' : '/Effects/Selection/Necropolis.EFFT',
'TestAura3' : '/Effects/Selection/Inferno.EFFT',
'TestAreaSpell' : '/Effects/Spells/TestAreaSpell1/_.EFFT',
'TestBuffSpell' : '/Effects/Spells/TestBuffSpell/_.EFFT',
'TestMeleeSound' : '/Effects/Spells/TestMeleeSound/_.EFFT',
'TestSwordEffect' : '/Test/SwordFX/_.EFFT',
'ClickOnTerrain' : '/UI/Effects/PathDestination/_.EFFT',
'Revival2' : '/Effects/Revival/_2.EFFT',
'ComplexAuraBlue' : '/Effects/Aura/_Blue.EFFT',
'ComplexAuraRed' : '/Effects/Aura/_Red.EFFT',
'Stun' : '/Effects/Spells/TestBuffSpell/_1.EFFT',
'Taunt' : '/Effects/Spells/TestBuffSpell/_2.EFFT',
'Poisoned' : '/Effects/Spells/TestBuffSpell/_3.EFFT',
'Earthquake' : '/Effects/Spells/TestAreaSpell1/_1.EFFT',
'Lightning' : '',
'ScaleColor' : '',
'GrowBuff' : '/Effects/ScaleAndColor/GrowBuff.EFFT',
}

class LinkReplacer(object):
  def __init__(self, name):
    self.name = name
    
  def __call__(self, matchobj):
    if effectIdToLink.has_key(matchobj.group(1)):
      return r'<%s href = "%s" />' % (self.name, effectIdToLink[matchobj.group(1)])
    
    return matchobj.group(0)

def xdb_visit(visitor, dirname, names):
    for n in names:
        if n.endswith('xdb'):
            visitor(path.join(dirname, n))

class XdbVisitor(object):
    def __init__(self):
        pass
    def __call__(self, file_name):
        print file_name
        fh = open(file_name, 'r', 'utf-8')
        text = fh.read()
        fh.close()
        
        for name in nodeNames:
          pattern = re.compile(r'<%s>(.*?)</%s>' % (name, name))
          text = re.sub(pattern, LinkReplacer(name), text)
        
        fh = open(file_name, 'w', 'utf-8')
        fh.write(text)
        fh.close()


data_path = path.normpath(path.join(path.dirname(__file__), '../../../Data'))

print data_path
path.walk(data_path, xdb_visit, XdbVisitor())
