# -*- coding: cp1251 -*-
import unittest
import XmlUtils

class Test_Parse(unittest.TestCase):

    def testSimple(self):
        text = r'''<?xml version="1.0" encoding="utf-8"?>
<StaticMesh>
    <srcFileName>Terrain/Elements/Abyss_S2_D.mb</srcFileName>
</StaticMesh>'''
        c = XmlUtils.parseString2(text)
        assert 'Terrain/Elements/Abyss_S2_D.mb' == c.StaticMesh.srcFileName
        assert 1 == len(c.StaticMesh)
        assert 0 == len(c.StaticMesh.srcFileName)
        assert True == c.has('StaticMesh')
                        
    def testOldMethod(self):
        text = r'''<?xml version="1.0" encoding="utf-8"?>
<StaticMesh>
    <srcFileName>Terrain/Elements/Abyss_S2_D.mb</srcFileName>
</StaticMesh>'''
        c = XmlUtils.parseString2(text)
        assert 'Terrain/Elements/Abyss_S2_D.mb' == c['StaticMesh']['srcFileName']
        
    def testAttributes(self):
        text = r'''<?xml version="1.0" encoding="utf-8"?>
<StaticMesh>
    <BackLink DBID="Maps/FPP/_.TERN.xdb" Count="24" />
</StaticMesh>'''
        c = XmlUtils.parseString2(text)
        assert 'Maps/FPP/_.TERN.xdb' == c.StaticMesh.BackLink.DBID
        assert '24' == c.StaticMesh.BackLink.Count
        
    def testSubAttrs(self):
        text = r'''<?xml version="1.0" encoding="utf-8"?>
<StaticMesh>
    <aabb>
        <minX>-5</minX>
        <maxX>5</maxX>
    </aabb>
</StaticMesh>'''
        c = XmlUtils.parseString2(text)
        assert '-5' == c.StaticMesh.aabb.minX
        assert '5' == c.StaticMesh.aabb.maxX
        
        assert 2 == len(c.StaticMesh.aabb)
        for index, item in enumerate(c.StaticMesh.aabb):
            if index == 0:
                assert '-5' == item
            if index == 1:
                assert '5' == item
        
    def testEnum(self):
        text = r'''<?xml version="1.0" encoding="utf-8"?>
<StaticMesh>
    <aabb>
        <minX>-5</minX>
        <maxX>5</maxX>
    </aabb>
</StaticMesh>'''
        c = XmlUtils.parseString2(text)
        class Processor:
        
            def __init__(self):
                self.sections = []
                
            def process(self, section):
                self.sections.append(section)
                
            def incLevel(self, item):
                pass
                
            def decLevel(self, item):
                pass
                            
        p = Processor()                
        c.enum(p)
        assert p.sections[0].getName() == '<root>'
        assert p.sections[1].getName() == 'StaticMesh'
        assert p.sections[2].getName() == 'aabb'
        assert p.sections[3].getName() == 'minX'
        assert p.sections[4].getName() == 'maxX'
        assert 5 == len(p.sections)
        
    def testEnumReturnValue(self):
        text = r'''<?xml version="1.0" encoding="utf-8"?>
<StaticMesh>
    <aabb>
        <minX>-5</minX>
        <maxX>5</maxX>
    </aabb>
</StaticMesh>'''
        c = XmlUtils.parseString2(text)
        class Processor:
        
            def __init__(self):
                self.sections = []
                
            def process(self, section):
                self.sections.append(section)
                if section.getName() == 'aabb':
                    return True
                
            def incLevel(self, item):
                pass
                
            def decLevel(self, item):
                pass
                            
        p = Processor()                
        c.enum(p)
        assert p.sections[0].getName() == '<root>'
        assert p.sections[1].getName() == 'StaticMesh'
        assert p.sections[2].getName() == 'aabb'
        assert 3 == len(p.sections)
if __name__ == '__main__':
    unittest.main()
