import os
import __init__
import sys

if len(sys.argv) < 3:
    print "Usage: <definitions file> <wrappers type>"
    sys.exit(1)

try:    
    path = sys.argv[1]
    target = sys.argv[2].lower()
        
    parser = __init__.Parser( os.path.abspath( path ) )

    parser.parseNamespace()

    classes = parser.getAllClasses()

    rcode_h = ""
    rcode_cpp = ""
    lcode_h = ""
    lcode_cpp = ""
    rcodecs = ""
    lcodecs = ""

    for c in classes:
        parser.parseClass( c )
        funcs = parser.getAllFuncs()
        data = parser.getAllData()
        for func in funcs:
            parser.parseFunction( func )
        parser.parseData( data )

        codegen = __init__.CodeGenRPC( parser )

        if target == 'remote' or target == 'both':
            rcode_h += codegen.generateRClassH()
            rcode_cpp += codegen.generateRClassCpp()
        if target == 'local' or target == 'both':
            lcode_h += codegen.generateLClassH()
            lcode_cpp += codegen.generateLClassCpp()
        if target == 'csremote' or target == 'both':
            rcodecs += codegen.generateRClassCS()
        if target == 'cslocal' or target == 'both':
            lcodecs += codegen.generateLClassCS()

    metacodegen = __init__.MetaCodeGenRPC( os.path.dirname( os.path.abspath( path ) ), parser.filename, rcode_h, rcode_cpp, lcode_h, lcode_cpp, rcodecs, lcodecs )
    
    if target == 'remote' or target == 'both':
        metacodegen.generateRFiles()
    if target == 'local' or target == 'both':
        metacodegen.generateLFiles()
    if target == 'csremote' or target == 'both':
        metacodegen.generateRCSFiles()
    if target == 'cslocal' or target == 'both':
        metacodegen.generateLCSFiles()
                
except:
    import traceback
    traceback.print_tb( sys.exc_traceback )
    sys.exit(1)
            