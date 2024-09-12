import unittest
import os
import XmlUtils
import tempfile
import shutil
import componentAnalyzer

compiler = None

class ProjectParser:

    def __init__(self, content):
        p = XmlUtils.parseString2(content)
        for c in p.VisualStudioProject.Configurations:
            if c.Name == 'Debug|Win32':
                pass

        class Processor:
            def __init__(self):
                self.files = {}

            def process(self, item):
                if item.getName() == 'File':
                    self.files[item.RelativePath] = item
                    return True

            def incLevel(self, item):
                pass
            def decLevel(self, item):
                pass

        self.e = Processor()
        p.VisualStudioProject.Files.enum(self.e)
        
    def IsFileExists(self, name):
        return name in self.e.files        
        
class Test(unittest.TestCase):
    
    def setUp( self ):
        self.cwd = os.getcwd()
        self.folder = tempfile.mkdtemp()
        os.chdir(self.folder)
        
    def tearDown(self):
        os.chdir(self.cwd)
        shutil.rmtree(self.folder)
        
    def test_Simple(self):
        files = {
            'main.cpp' : '''void main() {}''',
            'main.application' : '''sources = ['main.cpp']''',
        }
        for name, content in files.items():
            open(name, 'wb').write(content)
        result = os.system('run main.application --compiler=%s' % compiler)
        self.assertEquals(0, result)
        content = open('.auto/main.vcproj', 'r').read()
        p = ProjectParser(content)
        self.assertEquals(True, p.IsFileExists(os.path.abspath('main.cpp')))
        self.assertEquals(True, p.IsFileExists(os.path.abspath('main.application')))
        self.assertEquals(False, p.IsFileExists(os.path.abspath('some.cpp')))


if __name__ == '__main__':
    compiler = componentAnalyzer.GetLatestCompilerInstalled()
    unittest.main()
