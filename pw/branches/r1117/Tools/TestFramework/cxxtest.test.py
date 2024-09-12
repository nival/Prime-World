import os
import shutil
import tempfile
import subprocess
import unittest

class Test_CxxTestbackwardCompatibility(unittest.TestCase):

    def setUp(self):
        self.cwd = os.getcwd()
        self.folder = tempfile.mkdtemp( dir = self.cwd )
        os.chdir(self.folder)
        
    def tearDown(self):
        os.chdir(self.cwd)
        shutil.rmtree(self.folder)
        
    def testDefines( self ):
        text = '''
#include <cxxtest/TestSuite.h>

class MegaOldAnimatedTest : public CxxTest::TestSuite
{
public:
    void TestBackwardCompatibility()
    {
        printf("Hello, world !");
    }
};

CXX_REGISTER_TEST_SUITE( MegaOldAnimatedTest )
{
    CXX_REGISTER_TEST_FUNCTION( TestBackwardCompatibility );
}
'''
        f = open('example.cpp', 'wb')
        f.write(text)             
        f.close()

        args = ['run.cmd', 'example.cpp']
        a = subprocess.Popen(
            ' '.join(args),
            shell = True,
            stdin = subprocess.PIPE,
            stderr = subprocess.PIPE,
            stdout = subprocess.PIPE)
        text0 = a.stdout.read()
        text1 = a.stderr.read()
        a.wait()
        result = a.returncode
        assert result == 0
        assert 'Hello, world !' in text0
        
    def testMultipleBuild( self ):
        text = '''
#include <cxxtest/TestSuite.h>

class MultiCallParamTest : public CxxTest::TestSuite
{
public:
    void TestBackwardCompatibility()
    {
        printf("Call !");
    }
};
'''
        f = open('example.cpp', 'wb')
        f.write(text)             
        f.close()

        args = ['run.cmd', 'example.cpp', '--count=2']
        a = subprocess.Popen(
            ' '.join(args),
            shell = True,
            stdin = subprocess.PIPE,
            stderr = subprocess.PIPE,
            stdout = subprocess.PIPE)
        text0 = a.stdout.read()
        text1 = a.stderr.read()
        a.wait()
        result = a.returncode
        assert result == 0
        self.assertEquals(2, text0.count("Call !"))
        
if __name__ == '__main__':
    unittest.main()
