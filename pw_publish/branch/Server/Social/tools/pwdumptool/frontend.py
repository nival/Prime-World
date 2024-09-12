# -"- coding: utf-8 -"-
from flask import Flask, request, session, g, redirect, url_for, abort, \
    render_template, flash, make_response, stream_with_context, Response, \
    send_file

#from flask_pymongo import PyMongo
from thrift import Thrift
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol
from bson.json_util import dumps
import logging
from logging import FileHandler
from logging import Formatter
import MySQLdb, ujson, zlib
import re
import sys, os, datetime
import ConfigParser
import time
from pymongo import Connection
reload(sys)
sys.setdefaultencoding('utf-8')
#os.chdir(os.path.dirname(__file__))
sys.path.append('thrift_pw/account_management/gen-py/AccountManagementAPI')
import AccountManagement
import ttypes
from tornado.httpclient import HTTPRequest, HTTPClient
import tempfile
from flask_simpleldap import LDAP
from functions.replays import *
from functions.tracers import *


app = Flask(__name__)
app.secret_key = 'ÞUl®C46~×ò<ø`íß÷µ[ã>à5E-&ñû= hð;FuaNéwôfÝ9½X^$@â'

#config section
app.secret_key = 'rho8x_FG8j/5YpVvdT6izy!NTAq96HCn/,?GE34Vo'
FULL_PATH= os.path.dirname(os.path.abspath(__file__))

config = ConfigParser.ConfigParser()
config.read(os.path.join(FULL_PATH, 'config.cfg'))

app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024
dump_extensions = set(['pwdump'])
mo_extensions = set(['txt','csv'])

# logging configuration

logfile = config.get('DEFAULT', 'logfile')
file_handler = SafeWatchedFileHandler(logfile)
file_handler.setLevel(logging.INFO)
app.logger.addHandler(file_handler)
file_handler.setFormatter(Formatter('[%(levelname)1.1s %(asctime)s.%(msecs)d %(module)s:%(lineno)d]%(message)s'))

# LDAP Auth configuration

app.config['LDAP_ON'] = config.getboolean('DEFAULT', 'LDAP_ON')
app.config['LDAP_BASE_DN'] = config.get('DEFAULT', 'LDAP_BASE_DN')
app.config['LDAP_USERNAME'] = config.get('DEFAULT', 'LDAP_USERNAME')
app.config['LDAP_PASSWORD'] = config.get('DEFAULT', 'LDAP_PASSWORD')
app.config['LDAP_HOST'] = config.get('DEFAULT', 'LDAP_HOST')
app.config['LDAP_PORT'] = config.get('DEFAULT', 'LDAP_PORT')
app.config['LDAP_SCHEMA'] = config.get('DEFAULT', 'LDAP_SCHEMA')
app.config['LDAP_USE_TLS'] = config.get('DEFAULT', 'LDAP_USE_TLS')
app.config['LDAP_USE_SSL'] = config.get('DEFAULT', 'LDAP_USE_SSL')
#app.config['LDAP_OBJECTS_DN'] = 'sAMAccountName'
#app.config['LDAP_USER_FIELDS'] = 'sAMAccountName'
app.config['LDAP_USER_OBJECT_FILTER'] = config.get('DEFAULT', 'LDAP_USER_OBJECT_FILTER')
#app.config['LDAP_GROUP_OBJECT_FILTER'] = config.get('DEFAULT', 'LDAP_GROUP_OBJECT_FILTER')

ldap = LDAP(app)

# connect to Dumptool MongoDB

host = config.get('DEFAULT', 'host')
port = int(config.get('DEFAULT', 'port'))
sourcehost = config.get('DEFAULT', 'sourcehost')
sourceport =  int(config.get('DEFAULT', 'sourceport'))
dbName = config.get('DEFAULT', 'dbName')
sourcetable = config.get('DEFAULT', 'sourcetable')

app.config['MONGO_HOST'] = host
app.config['MONGO_PORT'] = port
app.config['MONGO_DBNAME'] = dbName

connection = Connection(host, port)
db = connection[dbName]
#mongo = PyMongo(app, config_prefix='MONGO')
##############################

# connect to Dumptool MongoDB
sahost = config.get('DEFAULT', 'sahost')
saport = int(config.get('DEFAULT', 'saport'))
sadbName = config.get('DEFAULT', 'sadbName')
sa_connection = Connection(sahost, saport)
sadb = sa_connection[sadbName]
##############################

# connect to live mysql (pwlobby1)
mysqlhost = config.get('DEFAULT', 'mysqlhost')
mysqlport = int(config.get('DEFAULT', 'mysqlport'))
mysqluser = config.get('DEFAULT', 'mysqluser')
mysqlpassword = config.get('DEFAULT', 'mysqlpassword')
mysqldbName = config.get('DEFAULT', 'mysqldbName')
mysqltable = config.get('DEFAULT', 'mysqltable')
##############################

#connect to Live Thrift
thrifturl = config.get('DEFAULT', 'thrifturl')

# replays coniguration
replays_dir = config.get('DEFAULT', 'replays_dir')


@app.before_request
def before_request():
    g.user = None
    if 'user_id' in session:
        # This is where you'd query your database to get the user info.
        g.user = {}
        # Create a global with the LDAP groups the user is a member of.
        g.ldap_groups = ldap.get_user_groups(user=session['user_id'])

@app.route('/login', methods=['GET', 'POST'])
def login():
    if g.user:
        return redirect(url_for('index'))
    if request.method == 'POST':
        user = request.form['user']
        passwd = request.form['passwd']
        test = ldap.bind_user(user, passwd)

        if not passwd or test is None:
            return "You're not the character of our tale"
        else:
            session['user_id'] = request.form['user']
            return redirect('/')
    return """<form action="" method="post">
                <table>
                <tr>
                <td colspan=2>Please log in with your domain account</td>
                </tr>
                <tr>
                <td>user: </td> <td> <input name="user" required></td>
                </tr>
                <tr>
                <td>password: </td> <td><input type="password" name="passwd" required></td>
                </tr>
                <tr>
                <td><input type="submit" value="Submit"></td>
                </tr>
                </table>
                </form>"""

@app.route('/logout')
def logout():
    session.pop('user_id', None)
    return redirect(url_for('root'))

def Thrift_common(method, *args):
    try:
        send_transport = TTransport.TMemoryBuffer()
        send_protocol = TBinaryProtocol.TBinaryProtocol( send_transport )
        client = AccountManagement.Client( send_protocol )
        send_transport.open()

        send_methodname = "send_%s" % method
        send_method = getattr(client, send_methodname, None)
        send_method( *args )
        send_string = send_transport.getvalue()


        request = HTTPRequest( thrifturl, method="POST", body=send_string )
        HTTP = HTTPClient()
        response = HTTP.fetch(request)
        #request=client.method(*args)
        return_transport = TTransport.TMemoryBuffer( response.body )
        return_protocol = TBinaryProtocol.TBinaryProtocol( return_transport )
        client_return = AccountManagement.Client( return_protocol )

        recv_methodname = "recv_%s" % method
        recv_method = getattr( client_return, recv_methodname, None )
        send_transport.close()
        return recv_method()
    except Thrift.TException as tx:
        app.logger.error(tx.message)
        catch(app)
        return '%s' % (tx.message)
    except Exception as e:
        app.logger.error(tx.message)
        catch(app)
        return e.message

def SentToThrift(method, id):
    try:
        transport = THttpClient.THttpClient(thrifturl)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()
        #request=client.GetAccountByAuid(7783)
        #request=client.FindNicknameExact('Xr0n1ck')
        #request=client.GetAccountBySNUid( "fb", "100001347319613" )
        requesttype = 'accountInfo'
        if method=='ApplyFullUserDump':
            request=client.ApplyFullUserDump(id[0], id[1])
            return str(request)
        if method=='GetAccountByAuid':
            request=client.GetAccountByAuid(int(id))
        elif method=='FindNicknameExact':
            id=u"%s" % id
            request=client.FindNicknameExact(id.encode("utf8"))
            requesttype = 'foundAccount'
        elif method=='GetAccountBySNUid':
            request=client.GetAccountBySNUid(id[0], id[1])

        app.logger.info("SentToThrift: request %r", request)
        if request.result !=0:
            app.logger.warning("SentToThrift:  Account is not found! request.result=%r acc data %r ", request.result, id)
            return ("exception", "Account is not found")
        d = {}
        if requesttype == 'accountInfo':
            d = []
            attr_order = ('auid', 'login', 'nickname', 'joinedSnids', 'guildid', 'guildBuildingLevel', 'registerdate', 'email', 'banned', 'banFlag', 'muted', 'muteFlag', 'fame', 'fraction', 'fractinChanges', 'fractionChangesFree', 'nickChanges', 'nickChangesFree', 'gender', 'location', 'reliability', 'currentsession', 'premiumAccountDate', 'lordRating', 'dailyRating', 'guardRating', 'numberOfWins', 'dodges', 'retiredTime', 'isRegularMMAllowed', 'isDeveloper', 'isSpectator', 'online', 'snid', 'snuid', 'hasLamp', 'lastPaymentTime', 'lastLampDropTime', 'gold', 'silver', 'resource1', 'resource2', 'resource3', 'perl', 'redPerl')
            for attr in attr_order:
                if attr in ('registerdate', 'premiumAccountDate', 'lastPaymentTime', 'lastLampDropTime') and getattr(request.accountInfo, attr, 0):
                    request.accountInfo.__dict__[attr] = datetime.datetime.fromtimestamp(float(getattr(request.accountInfo, attr, 0)))
                d.append({attr: getattr(request.accountInfo, attr, 0)})
        else:
            d = request.foundAccount.__dict__
        transport.close()

        app.logger.info("SentToThrift:  request.result=%r acc data %r ", request.result, d)
        return d
    except Thrift.TException as tx:
        app.logger.error(tx.message)
        catch(app)
        return ("exception", "%s" % tx.message)
    except Exception:
        app.logger.error("SentToThrift: Ooops! Who yet are detected...")
        catch(app)
        return ("exception", "Ooops! Who yet are detected...")

def mysql_getid(login):
    db=MySQLdb.connect(host=mysqlhost,port=mysqlport,user=mysqluser,passwd=mysqlpassword,db=mysqldbName,use_unicode=True)
    db.set_character_set('utf8')
    c=db.cursor()
    c.execute('select id from %s where login=\'%s\' ;' % (mysqltable, login))
    data =  c.fetchall()
    db.close()
    dataid= "data_" + str(int(data[0][0]))
    return dataid

def mysql_getid_by_nick(nick):
    try:
        db=MySQLdb.connect(host=mysqlhost,port=mysqlport,user=mysqluser,passwd=mysqlpassword,db=mysqldbName,use_unicode=True)
        db.set_character_set('utf8')
        c=db.cursor()
        c.execute('select id from %s where nick=\'%s\' ;' % ('tbl_nick', nick))
        data =  c.fetchall()
        c.execute('select login from %s where id=\'%s\' ;' % (mysqltable, str(int(data[0][0]))))
        login =  c.fetchall()
        db.close()
        dataid= "data_" + str(int(data[0][0]))
        login =  str(login[0][0])
        return dataid, login
    except Exception:
        return ("exception", "Ooops! Who yet are detected...")

def mysql_pwc_activate(email):
    try:
        db=MySQLdb.connect(host=mysqlhost,port=mysqlport,user=mysqluser,passwd=mysqlpassword,db=mysqldbName,use_unicode=True)
        db.set_character_set('utf8')
        c=db.cursor()
        c.execute('select count(*) from %s where email=\'%s\';' % ('tbl_pwconnect', email))
        search_res =  c.fetchall()
        search_res = int(search_res[0][0])
        if search_res == 1:
            c.execute('select active from %s where email=\'%s\';' % ('tbl_pwconnect', email))
            active = c.fetchall()
            active = int(active[0][0])
            if active == 1:
                db.close()
                return ("exception", "No need to activate. This email is already activated ...")
            else:
                c.execute('update %s set active="1" where email=\'%s\';' % ('tbl_pwconnect', email))
                db.close()
                return ("success", "Email successfully activated")
        elif search_res > 1:
            db.close()
            return ("exception", "WTF?!!! More than 1 email found")
        else:
            db.close()
            return ("exception", "No email found")
        db.close()
        return ("exception", "Unknown shit")
    except Exception, e:
        return ("exception", "Ooops! Who yet are detected: %s" % e.message)

def mysql_flush_server_id(login):
    try:
        db=MySQLdb.connect(host=mysqlhost,port=mysqlport,user=mysqluser,passwd=mysqlpassword,db=mysqldbName,use_unicode=True)
        db.set_character_set('utf8')
        c=db.cursor()
        c.execute('select count(*) from %s where login=\'%s\';' % ('tbl_login', login))
        search_res =  c.fetchall()
        search_res = int(search_res[0][0])
        if search_res == 1:
            c.execute('select server_id from %s where login=\'%s\';' % ('tbl_login', login))
            server_id = c.fetchall()
            server_id = int(server_id[0][0])
            if server_id == 0:
                db.close()
                return ("exception", "No need to flush server_id. It's already 0 for")
            else:
                c.execute('update %s set server_id=0 where login=\'%s\';' % ('tbl_login', login))
                db.close()
                return ("success", "server_id successfully set to 0 for %s")
        elif search_res > 1:
            db.close()
            return ("exception", "WTF?!!! More than 1 login found for")
        else:
            db.close()
            return ("exception", "No login found for")
        db.close()
        return ("exception", "Unknown shit with")
    except Exception as e:
        app.logger.error("Ooops! Who yet are detected: %s for" % (e))
        catch(app)
        return ("exception", "Ooops! Who yet are detected: %s for" % (e))

def allowed_dates():
    colls=[]
    for collection in db.collection_names():
        if re.search(sourcetable+"_\d\d\d\d-\d\d-\d\d", collection):
            colls.append(collection)
    colls.sort()
    colls.reverse()
    return colls

def allowed_file(filename, ext):
    return '.' in filename and \
           filename.rsplit('.', 1)[1] in ext


@app.route('/')
@ldap.login_required
def root():
    return render_template('layout.html')

@app.route('/search_account', methods=['GET', 'POST'])
@ldap.login_required
def search_account():
    error = None
    #return "%s" % SentToThrift('GetAccountByAuid', 7783)
    if request.method == 'POST':
        return redirect(url_for('show_account'))
    return render_template('select_account.html', error=error)

@app.route('/show_account', methods=['GET', 'POST'])
@ldap.login_required
def show_account():
    colls=allowed_dates()
    if request.method == 'POST':
#        #return "%s" % SentToThrift('GetAccountByAuid', 7783)
        if request.form['auid']:
            account = SentToThrift('GetAccountByAuid', request.form['auid'])
        elif request.form['nickname']:
            preaccount = SentToThrift('FindNicknameExact', request.form['nickname'])
            #account = SentToThrift('FindNicknameExact', request.form['nickname'])
            if preaccount != ("exception", "Account is not found"):
                snid = (preaccount['snid'], preaccount['snuid'])
                account = SentToThrift('GetAccountBySNUid', snid)
            else:
                account = preaccount
        elif request.form['snid'] and request.form['snuid']:
            snid = (request.form['snid'], request.form['snuid'])
            account = SentToThrift('GetAccountBySNUid', snid)
        else:
            return render_template('show_error.html', error="what?")
        #account = SentToThrift('GetAccountByAuid', int(request.form['auid']))
        #return redirect(url_for('show'))
        return render_template('show_account.html', account=account, tables=colls)
        #return str(request.form['auid'])


@app.route('/show', methods=['GET', 'POST'])
@ldap.login_required
def show():
    if request.method == 'POST':
        if request.form['type'] == "get":
            date = request.form['Date']
            login = request.form['login']
            dataid = mysql_getid(login)
            dump=db[date].find({"key" : dataid})
            dump = dumps(dump)
            dump = dump[1:-1]
            dump = dump.encode("utf8")
            try:
                dump = ujson.decode(dump)
            except Exception:
                app.logger.warning("Could not get the dump" % (e))
                catch(app)
                return  render_template('show_error.html', error="Could not get the dump")
            user_data = dump.get("data", {})
            encoded_user_data = user_data[4:].encode('latin1')
            encoded_user_data = zlib.decompress(encoded_user_data)
            if request.form['submit'] == "Download dump":
                response = make_response(encoded_user_data)
                response.headers['Content-Type'] = 'application/zip'
                response.headers["Content-Disposition"] = "attachment; filename=%s" % (login+".pwdump")
                return response
            if request.form['submit'] == "Apply dump":
                send_dump = (request.form['login'], encoded_user_data)
                apply_dump = SentToThrift('ApplyFullUserDump', send_dump)
                return redirect(url_for('dump_apply_result', result=apply_dump, auid=request.form['auid']))
        elif request.form['type'] == "send":
            file = request.files['file']
            if file and allowed_file(file.filename, dump_extensions):
                data = file.read()
                send_dump = (request.form['login'], data)
                apply_dump = SentToThrift('ApplyFullUserDump', send_dump)
                return redirect(url_for('dump_apply_result', result=apply_dump, auid=request.form['auid']))
            else:
                return render_template('show_error.html', error="Unrecognized file extension. Allows *.pwdump files only.")
        #return encoded_user_data
        #return render_template('show_table.html', table=request.form['Date'], login=request.form['login'])
        elif request.form['type'] == "fsn":
            sadb['users'].update({'_id':int(request.form['auid'])},{'$set':{'fsn' : request.form["fsn"]}},upsert=False, multi=False)
            if sadb.last_status()['updatedExisting'] == True and sadb.last_status()['ok'] == 1.0 and sadb.last_status()['err'] == None and sadb.last_status()['n'] == 1:
                return redirect(url_for('dump_apply_result', result="FSN Successfully changed", auid=request.form['auid']))
            else:
               return render_template('show_error.html', error=sadb.last_status())
    return "nothing"

@app.route('/dump_apply_result/auid<auid>_result<result>')
@ldap.login_required
def dump_apply_result(result, auid):
#def dump_apply_result():
    if result == "0":
        result = "Dump successfully applied for auid=%s" % auid
    elif result == "FSN Successfully changed":
        pass
    else:
        result = "Opps! Something went wrong"
    return render_template('dump_apply_result.html', result=result, auid=auid)

@app.route('/broken_account', methods=['GET', 'POST'])
@ldap.login_required
def broken_account():
    colls=allowed_dates()
    #return "%s" % SentToThrift('GetAccountByAuid', 7783)
    return render_template('broken_account.html', tables=colls)

@app.route('/get_broken_dump', methods=['GET', 'POST'])
@ldap.login_required
def get_broken_dump():
    if request.method == 'POST':
        if request.form['snid'] and request.form['snuid']:
            login = "%s#%s" % (request.form['snid'], request.form['snuid'])
            dataid = mysql_getid(login)
        elif request.form['nickname']:
            nickname = request.form['nickname']
            mysql_res = mysql_getid_by_nick(nickname)
            dataid = mysql_res[0]
            login = mysql_res[1]
        else:
            return  render_template('show_error.html', error="Could not get the dump")
        date = request.form['Date']
        dump=db[date].find({"key" : dataid})
        dump = dumps(dump)
        dump = dump[1:-1]
        dump = dump.encode("utf8")
        try:
            dump = ujson.decode(dump)
        except Exception:
            app.logger.warning("Could not get the dump" % (e))
            catch(app)
            return  render_template('show_error.html', error="Could not get the dump")
        user_data = dump.get("data", {})
        encoded_user_data = user_data[4:].encode('latin1')
        encoded_user_data = zlib.decompress(encoded_user_data)
        response = make_response(encoded_user_data)
        response.headers['Content-Type'] = 'application/zip'
        response.headers["Content-Disposition"] = "attachment; filename=%s" % (login+".pwdump")
        return response
    return "nothing"

@app.route('/pwc_activate', methods=['GET', 'POST'])
@ldap.login_required
def pwc_activate():
    if request.method == 'POST':
        try_to_activate = mysql_pwc_activate(request.form['email'])
        if try_to_activate[0] == "exception":
            return render_template('show_error.html', error=try_to_activate[1])
        elif try_to_activate[0] == "success":
            return render_template('common_result.html', result=try_to_activate[1])
        else:
            return render_template('show_error.html', error="Shit")


####################################################################################
### mass operations ###
@app.route('/mass_operations', methods=['GET', 'POST'])
@ldap.login_required
@ldap.group_required(groups=['PWgms_mass_operations'])
def mass_operations():
    return render_template('mass_operations.html')



@app.route('/mo_get_list', methods=['GET', 'POST'])
@ldap.login_required
@ldap.group_required(groups=['PWgms_mass_operations'])
def mo_get_list():
    if request.method == 'POST':
        if request.form['source']=='file':
            file = request.files['file']
            if file and allowed_file(file.filename, mo_extensions):
                #data = file.read()
                #list = data.split("\r\n")
                list = [line.strip() for line in file.readlines()]
            else:
                return render_template('show_error.html', error="Unrecognized file extension. Allows *.txt and *.csv files only.")
        if request.form['source']=='copypaste':
            list = request.form['list'].split("\r\n")
        try:
            if request.form.get('heterogeneous'):
                #Spike or FlushServerId
                no_subject_list = [{'auid': l.split(";")[0], 'operation': l.split(";")[1], 'subject': ""} for l in list if l and len(l.split(";")) >= 2 and l.split(";")[1] == "FlushServerId"]
                list = [{'auid': l.split(";")[0], 'operation': l.split(";")[1], 'subject': l.split(";")[2]} for l in list if l and len(l.split(";")) >= 3 ]
                if no_subject_list:
                    list += no_subject_list
            else:
                if request.form['operation'] in ["GiveLamp", "EditAccount", "AddBuilding"]:
                    subject = request.form['subject'] + "," + request.form['subject1'] + "," + request.form['subject2'] + "," + request.form['subject3'] + "," + request.form['subject4'] + "," + request.form['subject5'] + "," + request.form['subject6']
                else:
                    subject = request.form['subject']
                list = [{'auid': l, 'operation': request.form['operation'], 'subject': subject} for l in list if l]
        except Exception as e:
            app.logger.error(str(e)+": "+e.message)
            catch(app)
            return render_template('show_error.html', error=str(e)+": "+e.message)
        if not list:
            return render_template('show_error.html', error="List is empty or not valid")
        operationlog = tempfile.NamedTemporaryFile(delete=False)
        starttime = datetime.datetime.now()
        def generate():
            total = len(list)
            processed = 0
            for row in list:
                auid = row['auid']
                operation = row['operation']
                subject = row['subject']
                auid_operation = complete_mass_operation(auid,  operation,  subject)
                operationlog.write(str(auid_operation) + '\n')
                processed += 1
                percents = int(float(processed) / total * 100)
                yield [auid_operation, percents, "Cancel and get operation log"]
            elapsedtime = datetime.datetime.now() - starttime
            time.sleep(5)
            yield ["All operations finished", percents, "Get operation log"]
            operationlog.write('Processed at %s \n' % elapsedtime)
            operationlog.close()
        return Response(stream_with_context(stream_template('mo_result.html', data=generate(), oplog=operationlog.name)))

def complete_mass_operation(auid,  operation, subject):
    #return Thrift_common('GetAccountByAuid', int(auid))
    try:
        auid = int(auid)
    except Exception:
        app.logger.error("Auid %s is not valid"% auid)
        catch(app)
        return "Auid %s is not valid" % auid
    try:
        login_request = Thrift_common('GetAccountByAuid', auid)
        login = login_request.accountInfo.login
    except Exception as e:
        app.logger.error("Thrift failed on auid %s with %s" % (auid, e.message))
        catch(app)
        return "Thrift failed on auid %s with %s" % (auid, e.message)
    if login and login_request.result == 0:
        try:
            ############ UnlockFlag ############
            if operation == 'UnlockFlag':

                flags = Thrift_common('GetAccountFlags', login)
                if subject not in [flag.flagPersistentId for flag in flags.ownedFlags]:
                    result = Thrift_common('UnlockFlag', login, subject, 'dumptool')
                    if result == 0:
                        return "Flag %s is successfully unlocked for auid %s" % (subject, auid)
                    else:
                        return "Fail to unlock flag %s for auid %s with errorcode %s" % (subject, auid, result)
                else:
                    return "Auid %s already has a flag %s "  % (auid, subject)

            ############ LockFlag ############
            elif operation == 'LockFlag':
                flags = Thrift_common('GetAccountFlags', login)
                if subject not in [flag.flagPersistentId for flag in flags.notOwnedFlags]:
                    result = Thrift_common('LockFlag', login, subject, 'dumptool')
                    if result == 0:
                        return "Flag %s is successfully locked for auid %s" % (subject, auid)
                    else:
                        return "Fail to lock flag %s for auid %s with errorcode %s" % (subject, auid, result)
                else:
                    return "Auid %s has no flag %s "  % (auid, subject)
            ############ Add single Talent ############
            elif operation == 'AddTalent':
                if subject.lstrip("-").isdigit():
                    result = Thrift_common('AddTalent', login, int(subject), 'dumptool')
                    if result == 0:
                        return "Talent %s is successfully added for auid %s" % (subject, auid)
                    else:
                        return "Fail to add talent %s for auid %s with errorcode %s" % (subject, auid, result)
                else:
                    return "Talent %s could not be parsed as integer for auid %s" % (subject, auid)
            ############ Add list of Talents############
            elif operation == 'AddTalents':
                talentlist = [int(l.strip()) for l in subject.lstrip("[").rstrip("]").split(",") if l.strip().lstrip("-").isdigit()]
                if talentlist:
                    result = Thrift_common('AddTalents', login, talentlist, 'dumptool')
                    if result == 0:
                        return "List of talents %s is successfully added for auid %s" % (talentlist, auid)
                    else:
                        return "Fail to add list of talents %s for auid %s with errorcode %s" % (talentlist, auid, result)
                else:
                    return "Could not parse talentlist %s for auid %s" % (subject, auid)
                    ############ Add PremiumAccount ############
            elif operation == 'PremiumAccount':
                if subject.lstrip("-").isdigit():
                    result = Thrift_common('PayService', login, 1, int(subject))
                    if result == 0:
                        return "%s days of premium account successfully added for auid %s" % (subject, auid)
                    else:
                        return "Fail to add %s days of premium account for auid %s with errorcode %s" % (subject, auid, result)
                else:
                    return "%s could not be parsed as integer number of premium account days for auid %s" % (subject, auid)
                    ############ Send Message To User ############
            elif operation == 'SendMessageToUser':
                result = Thrift_common('SendMessageToUser', login, auid, "Message", subject.encode("utf8"), 'dumptool')
                if result == 0:
                    return "Message successfully sent for auid %s" % (auid)
                else:
                    return "Fail to send message for auid %s with errorcode %s" % (auid, result)
                    ############ GiveLamp ############
            elif operation == 'GiveLamp':
                try:
                    subject = [int(l.strip()) for l in subject.lstrip("[").rstrip("]").split(",")[0:4]]
                    lamp = ttypes.LampInfo()
                    lamp.Bonus = int(subject[0])
                    lamp.GoldBonus = int(subject[1])
                    lamp.Transaction = int(subject[2])
                    lamp.Duration = int(subject[3])
                except Exception:
                    return "Wrong lamp parameters %s for auid %s" % (subject.lstrip("[").rstrip("]").split(",")[0:4], auid)
                result = Thrift_common('GiveLamp', login, lamp, 'dumptool')
                if result == 0:
                    return "Lamp %s is successfully given for auid %s" % (subject, auid)
                else:
                    return "Fail to give lamp %s for auid %s with errorcode %s" % (subject, auid, result)
                    ############ AddSkin ############
            elif operation == 'AddSkin':
                skins = Thrift_common('GetAccountSkins', auid)
                unavailable = [skin.persistentId for skin in skins.skins if not skin.available]
                owned = [skin.persistentId for skin in skins.skins if skin.owned]
                notOwned = [skin.persistentId for skin in skins.skins if not skin.owned]
                if subject in unavailable:
                    return "Skin %s is unavailable for auid %s" % (subject, auid)
                elif subject in owned:
                    return "Skin %s is already owned for auid %s" % (subject, auid)
                elif subject in notOwned:
                    result = Thrift_common('AddSkin', auid, subject, 'dumptool')
                    if result == 0:
                        return "Skin %s is successfully added for auid %s" % (subject, auid)
                    else:
                        return "Fail to add skin %s for auid %s with errorcode %s" % (subject, auid, result)
                else:
                    return "Wrong skin id %s for auid %s" % (subject, auid)
                    ############ DeleteSkin ############
            elif operation == 'DeleteSkin':
                skins = Thrift_common('GetAccountSkins', auid)
                unavailable = [skin.persistentId for skin in skins.skins if not skin.available]
                owned = [skin.persistentId for skin in skins.skins if skin.owned]
                notOwned = [skin.persistentId for skin in skins.skins if not skin.owned]
                if subject in notOwned:
                    return "Skin %s is not owned for auid %s" % (subject, auid)
                elif subject in owned:
                    result = Thrift_common('DeleteSkin', auid, subject, 'dumptool')
                    if result == 0:
                        return "Skin %s is successfully deleted for auid %s" % (subject, auid)
                    else:
                        return "Fail to delete skin %s for auid %s with errorcode %s" % (subject, auid, result)
                else:
                    return "Wrong skin id %s for auid %s" % (subject, auid)
                    ############ UnlockHero ############
            elif operation == 'UnlockHero':
                if subject.lstrip("-").isdigit():
                    heroes = Thrift_common('GetAccountHeroes', login).heroesList
                    if int(subject) not in [hero.heroClassId for hero in heroes]:
                        result = Thrift_common('UnlockHero', login, int(subject), "dumptool")
                        if result == 0:
                            return "Hero %s is successfully unlocked for auid %s" % (subject, auid)
                        else:
                            return "Fail to unlock hero %s for auid %s with errorcode %s" % (subject, auid, result)
                    else:
                        return "Hero %s is already unlocked for auid %s" % (subject, auid)
                else:
                    return "Hero id %s is not integer for auid %s" % (subject, auid)
                    ############ LockHero ############
            elif operation == 'LockHero':
                if subject.lstrip("-").isdigit():
                    heroes = Thrift_common('GetAccountHeroes', login).heroesList
                    if int(subject) in [hero.heroClassId for hero in heroes]:
                        heroInstanceId = [hero.heroInstanceId for hero in heroes if hero.heroClassId == int(subject)][0]
                        result = Thrift_common('LockHero', login, heroInstanceId, "dumptool")
                        if result == 0:
                            return "Hero %s is successfully locked for auid %s" % (subject, auid)
                        else:
                            return "Fail to lock hero %s for auid %s with errorcode %s" % (subject, auid, result)
                    else:
                        return "Hero %s is already locked for auid %s" % (subject, auid)
                else:
                    return "Hero id %s is not integer for auid %s" % (subject, auid)
                    ############ AddBuilding ############
            elif operation == 'AddBuilding':
                try:
                    subject = [int(l.strip()) for l in subject.lstrip("[").rstrip("]").split(",")[0:2]]
                    building_id = int(subject[0])
                    building_level = int(subject[1])-1
                    if building_level < 0:
                        return "Wrong building level in building parameters [%s] for auid %s" % (subject, auid)
                except Exception:
                    app.logger.error("Wrong building parameters %s for auid %s" % (subject.lstrip("[").rstrip("]").split(",")[0:2], auid))
                    catch(app)
                    return "Wrong building parameters %s for auid %s" % (subject.lstrip("[").rstrip("]").split(",")[0:2], auid)
                result = Thrift_common('AddBuilding', auid, building_id, building_level, 'dumptool')
                if result == 0:
                    return "Building %s is successfully added for auid %s" % (subject, auid)
                else:
                    return "Fail to add building %s for auid %s with errorcode %s" % (subject, auid, result)
                    ############ EditAccount ############
            elif operation == 'EditAccount':
                try:
                    account_old = Thrift_common('GetAccountByAuid', auid).accountInfo
                except Exception as e:
                    app.logger.error("Could not get account info for auid %s with error: %s" % ( auid, e.message))
                    catch(app)
                    return "Could not get account info for auid %s with error: %s" % ( auid, e.message)
                try:
                    subject = [l.strip() for l in subject.lstrip("[").rstrip("]").split(",")[0:7]]
                    account_new = ttypes.AccountEdit()
                    for attr, value in account_new.__dict__.items():
                        if attr in account_old.__dict__.keys():
                            account_new.__dict__[attr] = getattr(account_old, attr)
                    perl = subject[0]
                    silver = subject[1]
                    resource1 = subject[2]
                    resource2 = subject[3]
                    resource3 = subject[4]
                    fraction = subject[5]
                    cwplayerpoints = subject[6]
                    success = []
                    if perl and perl.lstrip("-").isdigit() and (account_new.perl + int(perl)) >= 0:
                        account_new.perl += int(perl)
                        success.append("perl: %s" % int(perl))
                    if silver and silver.lstrip("-").isdigit() and (account_new.silver + int(silver)) >= 0:
                        account_new.silver += int(silver)
                        success.append("silver: %s" % int(silver))
                    if resource1 and resource1.lstrip("-").isdigit() and (account_new.resource1 + int(resource1)) >= 0:
                        account_new.resource1 += int(resource1)
                        success.append("resource1: %s" % int(resource1))
                    if resource2 and resource2.lstrip("-").isdigit() and (account_new.resource2 + int(resource2)) >= 0:
                        account_new.resource2 += int(resource2)
                        success.append("resource2: %s" % int(resource2))
                    if resource3 and resource3.lstrip("-").isdigit() and (account_new.resource3 + int(resource3)) >= 0:
                        account_new.resource3 += int(resource3)
                        success.append("resource3: %s" % int(resource3))
                    if cwplayerpoints and cwplayerpoints.lstrip("-").isdigit() and (account_new.cwplayerpoints + int(cwplayerpoints)) >= 0:
                        account_new.cwplayerpoints += int(cwplayerpoints)
                        success.append("cwplayerpoints: %s" % int(cwplayerpoints))
                    fractions = {"doct": 0, "adornian": 1}
                    if fraction in fractions.keys():
                        account_new.fraction = fractions[fraction]
                        success.append("fraction: %s" % fraction)
                except Exception as e:
                    app.logger.error("Wrong account parameters %s for auid %s cause of: %s" % (subject.lstrip("[").rstrip("]").split(",")[0:7], auid, e.message))
                    catch(app)
                    return "Wrong account parameters %s for auid %s cause of: %s" % (subject.lstrip("[").rstrip("]").split(",")[0:7], auid, e.message)
                if account_new and account_old and success:
                    result = Thrift_common('EditAccount', login, account_new, 'dumptool')
                    if result == 0:
                        return "%s is successfully added for auid %s" % (success, auid)
                    else:
                        return "Fail to add %s for auid %s with errorcode %s" % (success, auid, result)
                else:
                    return "Non-applicable account parameters %s for auid %s" % (subject, auid)

                    ############ FlushServerId ############
            elif operation == 'FlushServerId':
                result = mysql_flush_server_id(login)
                if result:
                    return "%s auid %s" % (result[1], auid)
                else:
                    return "Fail to execute mysql function for auid %s" % (auid)
                #########################################
            else:
                return "Weird operation %s for auid %s" % (operation, auid)
        except Exception as e:
            app.logger.error("Thrift failed on auid %s with error: %s" % (auid, e.message))
            catch(app)
            return "Thrift failed on auid %s with error: %s" % (auid, e.message)
    else:
        return "Could not find auid %s" % auid


@app.route('/mo_return_log', methods=['GET', 'POST'])
@ldap.login_required
@ldap.group_required(groups=['PWgms_mass_operations'])
def mo_return_log():
        if os.path.isfile(request.form['oplog']):
            result = open(request.form['oplog'], 'r').read()
            os.remove(request.form['oplog'])
            response = make_response(result)
            response.headers['Content-Type'] = 'application/zip'
            #response.headers["Content-Disposition"] = "attachment; filename=%s" % (request.form['operation']+".log")
            response.headers["Content-Disposition"] = "attachment; filename=%s" % (request.form['oplog']+"_mass_operation.log")
            return response
        else:
            return render_template('show_error.html', error="Could not find the logfile. Don't ask me why. I don't know.")

@app.route('/mo_return_without_log', methods=['GET', 'POST'])
@ldap.login_required
@ldap.group_required(groups=['PWgms_mass_operations'])
def mo_return_without_log():
        if os.path.isfile(request.form['oplog']):
            os.remove(request.form['oplog'])
        return """
        <script type="text/javascript">
            function back() {
                window.location.replace = history.go(-2);
            }
        </script>
        <body onLoad="setTimeout('back()', 1)">
        """

@app.route('/hetero_help', methods=['GET', 'POST'])
@ldap.login_required
@ldap.group_required(groups=['PWgms_mass_operations'])
def hetero_help():
        return render_template('hetero_help.html')

def stream_template(template_name, **context):
    app.update_template_context(context)
    t = app.jinja_env.get_template(template_name)
    rv = t.stream(context)
    # uncomment if you don't need immediate reaction
    ##rv.enable_buffering(2)
    return rv


####################################################################################
### pw replays ###
@app.route('/replays', methods=['GET', 'POST'])
@ldap.login_required
def replays():
    return render_template('replays.html')

@app.route('/show_replays', methods=['GET', 'POST'])
@ldap.login_required
def show_replays():
    if request.method == 'POST':
        if request.form['SessionId']:
            fs_args = {"wildcard" : request.form['SessionId']}
            if request.form['hostname']:
                fs_args["level1"] = request.form['hostname']
            if request.form['date']:
                fs_args["level2"] = request.form['date']
            session_list = files_search(replays_dir, **fs_args)
            if len(session_list) <= 10:
                return render_template('select_replay.html', session_list=session_list)
            else:
                return render_template('show_error.html', error="Too many entries found with this SessionId. Please try another one.")
        else:
            return render_template('show_error.html', error="SessionId is empty or not valid")

@app.route('/download_replay', methods=['GET', 'POST'])
@ldap.login_required
def download_replay():
    if request.method == 'POST':
        if request.form['replay']:
            file = os.path.join(replays_dir, request.form['replay'].lstrip("\\"))
            filename = os.path.basename(file)
            return send_file(file, as_attachment= True, attachment_filename = filename)

if __name__ == '__main__':
    #app.config["TESTING"] =True
    app.run(debug = False)