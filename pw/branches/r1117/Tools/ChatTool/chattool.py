import os
import re
import fnmatch
import sys

loginNameId = {}
chatLog = ""
filterNames = []

def getUserName( id ):
    if id in loginNameId:
        return loginNameId[id]
    return "unknown user"
    
def parseLoginName( str ):
    m = re.search( r'user authorized \(login=(?P<login_name>\w+)\s+id=(?P<login_id>\w+)\)', str )
    if m:
        loginNameId[ m.group('login_id') ] = m.group('login_name')

def parseLoginFile( filename ):
    lines = open( filename, 'r' ).readlines();
    for line in lines:
        if ( line.find("user authorized") != -1 ):
            parseLoginName( line )

def printLogins():
    print "Unique logins: " + str(len(loginNameId))
    #for key in loginNameId.keys():
        #print key, loginNameId[key]

def parseMessage( str ):
    global chatLog
    global filterNames
    outstr = str[ 0: str.find("Message recieved") ]
    
    channel_name = ""
    user_name = ""

    m = re.search( r'channel=(?P<channel_name>\w+):', str )
    if m:
        channel_name = m.group('channel_name')

    m = re.search( r'user=(?P<user_name>\w+)\s+', str )
    if m:
        user_name = getUserName( m.group('user_name') )

    outstr += channel_name + " " + user_name + ": " + str[str.find('\"'):str.rfind('\"')+1 ]
    
    outstr += "\n"
    
    if len(filterNames):
        isFind = False
        for name in filterNames:
            if user_name.find(name) != -1:
                isFind = True
                break
        if not isFind:
            return
    chatLog += outstr

def parseChatFile( infile ):
    lines = open( infile, 'r' ).readlines();
        
    for line in lines:
        if ( line.find("Message recieved") != -1 ):
            parseMessage( line )

def matchPatterns(name, patterns, ignored = []):
    for mask in ignored:
        #TODO
        #print "MASK", mask, fnmatch.translate( mask ), name
        if re.match( fnmatch.translate( mask ), name ):
            return None
        if name.find( mask ) != -1:
            return None
    for pattern in patterns:        
        if re.match( fnmatch.translate( pattern ), name ):
            return pattern        
    return None        

def collectFiles(path, patterns, ignored = [], recursive=True, add_root=True):
    result = []
    for root, dirs, files in os.walk(path):
        for name in files:
            relativePath = os.path.join( root, name )[len(path)+1:]
            if matchPatterns(relativePath, patterns, ignored):
                value = os.path.join(root, name)
                if not add_root:
                    value = value[len(path)+1:]    
                result.append(value)
        if not recursive:
            break                    
    return result


def writeChatLog( outfilename ):
    outfile = open( outfilename, 'w' )
    outfile.write(chatLog)
    outfile.close()

def main():
    global filterNames
    if len( sys.argv ) < 2:
        print "Usage: chattool.py dirname [user1 user2 ...]\n"
        exit(1)
    dirname = sys.argv[1]
    if os.path.isdir( os.path.abspath(dirname) ):
        dirname = os.path.abspath(dirname)
    else:
        print "Usage: chattool.py dirname [user1 user2 ...]\n"
        exit(1)
    
    if sys.argv > 2:
        filterNames = sys.argv[2:]
    
    loginfiles = collectFiles( dirname, ["*Login.txt"], recursive=False )
    for loginfile in loginfiles:
        parseLoginFile( loginfile )
        
    chatfiles = collectFiles( dirname, ["*Chat.txt"], recursive=False )
    for chatfile in chatfiles:
        parseChatFile( chatfile )
    
    writeChatLog( "chat.txt" )
    printLogins()

main()
#parseLoginFile( "login.txt" )
#generateChatFile( "chat.txt", "output.txt" )
#printLogins()