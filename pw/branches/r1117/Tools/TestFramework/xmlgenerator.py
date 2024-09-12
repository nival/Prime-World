import os
from ComponentsSystem import utils
from shutil import copy2
import resultgen

file_directory = os.path.dirname( os.path.realpath( __file__ ) )

def addNUnitXMLReport():
    nunitreport_filename = '../nunit.report.xml'
    if not os.path.isfile( nunitreport_filename ):
        return ''
    reportfile = open( nunitreport_filename, 'r' )
    report = reportfile.read()
    reportfile.close()
    startindex = report.find( '<test-suite ' )
    endindex = report.rfind( '</test-suite>' )
    if startindex == -1 or endindex == -1:
        return ''
    endindex += len( '</test-suite>' )
    return report[startindex:endindex]


def createXmlDoc( outfilename, Log, timeToRun ):

    dir = utils.changeScope( ".auto/.xml" )
    
    report = "tests_report.xsl"
    try:
        #copy xsl template to working directory
        source = "{0}/Vendors/xslt/{1}".format( file_directory, report ) 
        copy2( source, report )
    except:
        # TODO: proccess error handliing
        raise
    
    string = '<?xml-stylesheet type="text/xsl" href="{0}"?>\n'.format( report )
    #string = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    
    if Log.memoryLeaks:
        res = resultgen.TestResult()
        res.dirname = './'
        res.filename = 'MemoryLeaks'
        res.testtime = 0
        res.errorstr = Log.memoryLeaks
        res.testcase = 'MemoryLeaks'
        Log.results.append( res )


    alltests = len( Log.results )

    failtests = 0
    for res in Log.results:
        if res.errorstr:
            failtests += 1

    string += "<test-results name=\"%s\" total=\"%d\" failures=\"%d\">\n" % ( 'Tests', alltests, failtests )

    string += "<components total=\"%d\">\n" % ( len( Log.components ) )
    for cmpname in Log.components:
        string += "<component><![CDATA[ %s ]]></component>\n" % ( cmpname )
    string += "</components>\n"
    string += "<buildLog><![CDATA[ %s ]]></buildLog>\n" % ( Log.buildLog )
    string += "<textLog><![CDATA[ %s ]]></textLog>\n" % ( Log.rawText )

    string += "<imagesPath>{0}/Vendors/xslt</imagesPath>\n".format( file_directory )

    string += addNUnitXMLReport()

    filenames = set()

    for res in Log.results:
        if res.dirname+'/'+res.filename in filenames:
            continue
        filenames.add( res.dirname+'/'+res.filename )

    for flname in filenames:
        isSuccess = "True"
        testtime = 0
        for res in Log.results:
            if res.dirname+'/'+res.filename == flname:
                testtime = res.testtime
                if res.errorstr:
                    isSuccess = "False"
        string += "  <test-suite name=\"%s\" executed=\"True\" success=\"%s\" time=\"%f\">\n" % ( flname, isSuccess, float(testtime) )
        string += "    <results>\n"


        for res in Log.results:
            if res.dirname+'/'+res.filename == flname:
                isSuccessCase = "True"
                if res.errorstr:
                    isSuccessCase = "False"
                string += "      <test-case name=\"%s\" executed=\"True\" success=\"%s\" time=\"%f\"" % ( res.testcase, isSuccessCase, (float)(res.testtime) )
                if isSuccessCase == "True":
                    string += "/>\n"
                else:
                    string += ">\n"
                    string += "        <failure>\n"
                    string += "          <message><![CDATA["
                    string += res.errorstr
                    string += "]]></message>\n"
                    string += "          <stack-trace><![CDATA["
                    string += "%s (%s)" % ( res.filename, res.testline )
                    string += "\n]]></stack-trace>\n"
                    string += "        </failure>\n"
                    string += "      </test-case>\n"
        
        string += "    </results>\n"
        string += "  </test-suite>\n"

    string += "</test-results>\n"

    file = open( outfilename, 'w' )
    file.write( string )
    file.close()
