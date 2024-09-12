import __init__
import unittest
import os

workdir = ''

class Directory:
    
    def __init__( self, directory ):
        self.previousDirectory = os.getcwd()
        os.chdir( directory )
    
    def __del__( self ):
        os.chdir( self.previousDirectory )


def changeScope( path = '.auto' ):
    #change path to temp dir    
    if not os.path.isdir( path ): 
        os.makedirs( path )
    return Directory( path )


class Test(unittest.TestCase):

    def testFuncParsing( self ):
        parser = __init__.Parser( os.path.abspath( workdir+'unittests/funcstest.cpp' ) )
        parser.parseNamespace()
        parser.parseClass( 'SimpleRabbit' )
        parser.parseFunction( 'GetServerDef' )
        parser.parseFunction( 'AddRoute' )
        parser.parseFunction( 'RemoveRoute' )
        parser.parseFunction( 'InitialUpdateEnd' )
        parser.parseFunction( 'processVector' )

    def testEvgenBug( self ):
        parser = __init__.Parser( os.path.abspath( workdir+'unittests/evgenbug.cpp' ) )
        parser.parseNamespace()
        parser.parseClass( 'RemoteApi' )
        parser.parseFunction( 'callRemote' )
        parser.parseFunction( 'finc' )
        parser.parseFunction( 'GetServerDef' )

    '''def testGen( self ):
        parser = __init__.Parser( os.path.abspath( workdir+'unittests/GenTest.cpp' ) )

        parser.parseNamespace()

        classes = parser.getAllClasses()

        for c in classes:
            parser.parseClass( c )

            funcs = parser.getAllFuncs()

            for func in funcs:
                parser.parseFunction( func )

            codegen = __init__.CodeGenRPC( parser )
            codegen.generateRClass()
            codegen.generateLClass()

        file = open( workdir+'unittests/LGenTest.h', 'r' )
        lgentest_orig = file.read()
        file.close()
        file = open( workdir+'unittests/RGenTest.h', 'r' )
        rgentest_orig = file.read()
        file.close()

        file = open( workdir+'unittests/LBenderTest.h', 'r' )
        lbendertest_orig = file.read()
        file.close()
        file = open( workdir+'unittests/RBenderTest.h', 'r' )
        rbendertest_orig = file.read()
        file.close()


        file = open( workdir+'unittests/LGenTest.auto.h', 'r' )
        lgentest_gen = file.read()
        file.close()
        file = open( workdir+'unittests/RGenTest.auto.h', 'r' )
        rgentest_gen = file.read()
        file.close()
        file = open( workdir+'unittests/LBenderTest.auto.h', 'r' )
        lbendertest_gen = file.read()
        file.close()
        file = open( workdir+'unittests/RBenderTest.auto.h', 'r' )
        rbendertest_gen = file.read()
        file.close()

        #os.remove( workdir+'unittests/LGenTest.auto.h' )
        #os.remove( workdir+'unittests/RGenTest.auto.h' )
        #os.remove( workdir+'unittests/LGenTest.auto.cpp' )
        #os.remove( workdir+'unittests/RGenTest.auto.cpp' )
        
        #os.remove( workdir+'unittests/LBenderTest.auto.h' )
        #os.remove( workdir+'unittests/RBenderTest.auto.h' )
        #os.remove( workdir+'unittests/LBenderTest.auto.cpp' )
        #os.remove( workdir+'unittests/RBenderTest.auto.cpp' )

        assert lgentest_orig == lgentest_gen
        assert rgentest_orig == rgentest_gen
        assert lbendertest_orig == lbendertest_gen
        assert rbendertest_orig == rbendertest_gen'''

    def testComment( self ):
        original = '''
//////////////////
test();
//////////////////
/*
Com
*/
/*
Vlo
/*
*/
printf("/*Not comment*/");
/////////////////////
/**********
printf("/*Com comment*/'''
        expected = '''

test();



printf("/*Not comment*/");

'''

        actual = __init__.comment_remover(original)
        self.assertEquals(actual, expected)

    def testRealCpp( self ):
        text = '''
struct DummyParent {};        

REMOTE struct HelloWorld : DummyParent
{
  ; // if we remove this symbol, parsing will work infinitely
  REMOTE int Print( const char* message )
  {
    printf("");
  }
};
'''        
        parser = __init__._Parser('test.txt', text, text)
        parser.parseNamespace()
        classes = parser.getAllClasses()
        assert 1 == len(classes)
        assert 'HelloWorld' == classes[0]
        
        parser.parseClass( classes[0] )
        funcs = parser.getAllFuncs()
        assert 1 == len(funcs)
        assert 'Print' == funcs[0]
        
    def testRealCppWithTemplatedVectorAsReturnValue( self ):
        text = '''
struct DummyParent {};        

REMOTE struct HelloWorld : DummyParent
{
  RPC_ID(0x1); 
  
  REMOTE const nstl::vector<byte>& GetFileChunk(const string& fileName, int chunkSize, int chunkId);
};
'''        
        parser = __init__._Parser('test.txt', text, text)
        parser.parseNamespace()
        classes = parser.getAllClasses()
        assert 1 == len(classes)
        assert 'HelloWorld' == classes[0]
        
        parser.parseClass( classes[0] )
        funcs = parser.getAllFuncs()
        assert 1 == len(funcs)
        assert 'GetFileChunk' == funcs[0]
        
        parser.parseFunction(funcs[0])
        
    def testRealCppWithLongLongAsParam( self ):
        text = '''
struct DummyParent {};        

REMOTE struct HelloWorld : DummyParent
{
  RPC_ID(0x1); 
  
  REMOTE long long GetFileChunk(long long value);
};
'''        
        parser = __init__._Parser('test.txt', text, text)
        parser.parseNamespace()
        classes = parser.getAllClasses()
        assert 1 == len(classes)
        assert 'HelloWorld' == classes[0]
        
        parser.parseClass( classes[0] )
        funcs = parser.getAllFuncs()
        assert 1 == len(funcs)
        assert 'GetFileChunk' == funcs[0]
        
        parser.parseFunction(funcs[0])
        
    def test_ReturnValuesByValue(self):
        text = '''
struct MyStruct 
{
};
struct DummyParent {};        

REMOTE struct HelloWorld : DummyParent
{
  RPC_ID(0x1); 
  
  REMOTE MyStruct GetFileChunk();
};
'''        
        parser = __init__._Parser( os.path.abspath('test.txt'), text, text )

        parser.parseNamespace()

        classes = parser.getAllClasses()

        for c in classes:
            parser.parseClass( c )

            funcs = parser.getAllFuncs()

            for func in funcs:
                parser.parseFunction( func )

            codegen = __init__.CodeGenRPC( parser )
            r_files = codegen.generateRClass()
            l_files = codegen.generateLClass()
        

if __name__ == '__main__':
    workdir = os.path.dirname( os.path.realpath( __file__ ) )
    if workdir: workdir += '/'
    else: workdir = '../'
    dir = changeScope()
    unittest.main()
    del dir
    #os.system( "run.cmd --cleanup" )
