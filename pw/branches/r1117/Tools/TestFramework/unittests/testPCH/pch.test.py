import unittest
import os
import subprocess

class CodegenTest( unittest.TestCase ):

    directory = os.path.dirname( os.path.realpath( __file__ ) )
    
    def setUp( self ):
        self.previousDirectory = os.getcwd()
        if not os.path.isdir( ".auto/.pch" ):
            os.makedirs( ".auto/.pch" )
        os.chdir( ".auto/.pch" )
        os.system( "run.cmd --cleanup" )
    
    def tearDown( self ):
        os.chdir( self.previousDirectory )


    def testCodegen( self ):
        component = self.directory + '\\data\\one.component'
        process = subprocess.Popen(
            "run.cmd {0} --buildcomponent --output=bin".format( component ),
            shell = True,
            stdin = subprocess.PIPE,
            stderr = subprocess.PIPE,
            stdout = subprocess.PIPE
        )
        out = process.stdout.read()
        err = process.stderr.read()
        process.wait()
        
        assert out.find( ': error' ) == -1 and out.find( 'fatal error' ) == -1 and err == '', "\n*** build report:\n{0}\n{1}".format( out, err )
        assert( os.path.isfile( '.auto/bin/one.exe' ) )


if __name__ == '__main__':
    unittest.main()