import sys
import os
import utils
import cPickle

fab = utils.Fab(r'sa.pem', [('192.168.56.4', 22)], 'user', 'user')

fab.identify()

server_name = '192.168.56.4'
svn_url = 'https://svn.SITE.com/socagr/tags/Final_i5'
svn_user = '***'
svn_pwd = '***'
svn_rev = 'HEAD'
os_name = 'ubuntu'

dest = '/var/www/Final_i5'

# Списки библиотек, необходимых для разных ОС
libs = {}
libs['debian'] = ['curl', 'uuid-dev', 'libevent-dev']
libs['ubuntu'] = ['curl', 'uuid-dev', 'libevent-dev', 'make']

if 'install' in sys.argv:
    fab.install(os_name=os_name, server_name=server_name, ser_libs=cPickle.dumps(libs) )

if 'checkout' in sys.argv:
    fab.checkout(url=svn_url, dest=dest, user=svn_user, password=svn_pwd, revision=svn_rev, os_name=os_name)

if 'update' in sys.argv:
    fab.update(url=svn_url, dest=dest, user=svn_user, password=svn_pwd, revision=svn_rev, os_name=os_name)

if 'init_db' in sys.argv:
    fab.init_db(dest=dest)    
    
try:
    index = sys.argv.index('stop')  
    if index > 0:
        if index + 1 < len(sys.argv):
            fab.stop(pid=sys.argv[index+1])
        else:
            fab.stop()
except:
    pass

if 'start' in sys.argv:
    fab.start(dest=dest, os_name=os_name)

