import sys, os, cPickle

from fabric.api import run, local
from fabric.api import task, run, cd, get, sudo
from fabric.operations import put

import utils

php_ini_path = "/etc/php5/fpm"
nginx_config_path = "/etc/nginx/sites-available/default"
php_fpm_config_path = "/etc/php5/fpm/php-fpm.conf"

@task
def install(os_name, server_name, ser_libs):
    
    libs = cPickle.loads(ser_libs)

    sudo('apt-get update -y')
    
    # библиотеки
    for lib in libs[os_name]:
        sudo('apt-get install ' + lib + ' -y')
    
    # svn
    sudo('apt-get install subversion -y')
    
    # nginx
    sudo('apt-get install nginx -y')
    sudo('rm ' + nginx_config_path)
    put('./configs/nginx/default', nginx_config_path, use_sudo=True)
    
    # php-dev + mongo + gearman
    sudo('apt-get install gearman libgearman-dev mongodb -y')
    
    # php + gearman extension
    sudo('apt-get install php5-cli php5-common php5-suhosin php5-curl -y')
    
    if os_name == 'ubuntu':
        pass
        #sudo('add-apt-repository ppa:brianmercer/php5')
        # в последний версиях Ubuntu php-fpm включен в репозитории по умолчанию. Для старых раскомментить!
    elif os_name == 'debian':
        sudo('echo "\n\ndeb http://packages.dotdeb.org squeeze all" >> /etc/apt/sources.list')
        sudo('wget http://www.dotdeb.org/dotdeb.gpg')
        sudo('cat dotdeb.gpg | sudo apt-key add -')
    
    sudo('apt-get update -y')
    sudo('apt-get install php5-fpm php5-dev php-pear php5-gd php5-mysql -y')
    
    if os_name == 'debian':
        sudo("sed -i 's/\/usr\/lib\/libuuid.la/-luuid/g' /usr/lib/libgearman.la")
    
    sudo('pecl install channel://pecl.php.net/gearman-0.7.0')
       
    # php extensions (mongo, eaccelerator)
    sudo('pecl install mongo')

    sudo('echo "\n\nextension=mongo.so" >>  ' + php_ini_path + '/php.ini')

    utils.make_install_php_ext('eaccelerator-0.9.6.1.tar.bz2', 'eaccelerator-0.9.6.1')
    
    sudo('echo "\n\nextension=gearman.so" >> ' + php_ini_path + '/php.ini')

    put('./vendor/sphinx-2.0.4.tar.bz2', '/usr/src/sphinx-2.0.4.tar.bz2', use_sudo=True)
    sudo('tar -xvf /usr/src/sphinx-2.0.4.tar.bz2 -C /usr/src')
    sudo('chmod -R 777 /usr/src/sphinx-2.0.4')
    #sudo('/usr/src/sphinx-2.0.4/api/libsphinxclient/buildconf.sh') Не нужно для релиз-версии. Если используется beta - раскомментить
    sudo('/usr/src/sphinx-2.0.4/api/libsphinxclient/configure && make install')
        
    with cd('/usr/src/sphinx-2.0.4/api/libsphinxclient'): 
        sudo('pecl install sphinx')

    sudo('echo "\n\nextension=sphinx.so" >> ' + php_ini_path + '/php.ini')
    
    put('./configs/sphinx/sphinx.conf', '/usr/local/etc/sphinx.conf', use_sudo=True)
    
    put('./configs/eaccelerator/php_part.ini', php_ini_path + '/php_part.ini', use_sudo=True)
    sudo('cat ' + php_ini_path + '/php_part.ini >> ' + php_ini_path + '/php.ini')
    
    sudo('apt-get install rsync -y')
    
    sudo('apt-get update -y')
    
    # nginx document root
    sudo("sed -i 's/DOCUMENT_ROOT/" + dest.replace("/", "\\/") + "\/www/g' " + nginx_config_path)
    sudo("sed -i 's/SERVER_NAME/" +  + "\/www/g' " + nginx_config_path)
    
    # Файл настроек php-fpm
    put('./configs/php-fpm/php-fpm.conf', php_fpm_config_path, use_sudo=True)
    

paths = [
    '',
]

@task
def checkout(url=None, dest=None, os_user=None, os_user_group=None, svn_user=None, password=None, revision=None, os_name=None, sa_version=None):
    
    # checkout
    
    svn = utils.SVN(svn_user, password, revision)
    for path in paths:
        fpath = dest+'/'+path
        svn.do(fpath, ['checkout', url+'/'+path])
    
    sudo('chown -R ' + os_user + ':' + os_user_group + ' ' + dest)
    sudo('chown -R ' + os_user + ':www-data ' + dest + '/application/log')
    sudo('chmod -R 777 ' + dest + '/application/log')
    
    # Костыль, подменяющий адрес сервера БД. В дальнейшем заменить на нормальное решение!!! 
    sudo("sed -i 's/192.168.1.16/127.0.0.1/g' " + dest + "/misc/scripts/initDb.php")
    sudo("sed -i 's/192.168.1.16/127.0.0.1/g' " + dest + "/application/frontend/settings/config.php")
    sudo("sed -i 's/192.168.1.16/127.0.0.1/g' " + dest + "/application/tests/settings/config.php")
    sudo("sed -i 's/192.168.1.16/127.0.0.1/g' " + dest + "/application/background/settings/config.php")
    
    sudo("sed -i 's/0.1.5/" + sa_version + "/g' " + dest + "/application/frontend/settings/config.php")
    sudo("sed -i 's/0.1.5/" + sa_version + "/g' " + dest + "/application/tests/settings/config.php")
    sudo("sed -i 's/0.1.5/" + sa_version + "/g' " + dest + "/application/background/settings/config.php")    
    
    
@task
def update(url=None, dest=None, os_user=None, os_user_group=None, svn_user=None, password=None, revision=None, os_name=None):
    svn = utils.SVN(svn_user, password, revision)
    for path in paths:
        fpath = dest+'/'+path
        svn.do(fpath, ['revert', '-R'], False)
        svn.do(fpath, ['update'])
    
    
def init_db(dest=None):
    
    # Запускаем mongo как демона и создаем базу специальным скриптом
    sudo("mongod --fork --logpath /var/log/mongodb.log --logappend --dbpath /var/lib/mongodb/")
    
    # Создаем чистую БД
    sudo("php -c " + php_ini_path + " " + dest + "/misc/scripts/initDb.php")
    
'''
@task
def stop(pid=None):
    if pid == None:
        run('ps -A -f | grep python')
    else:
        run('sudo kill -2 %s' % pid)
'''     
        
@task
def start(dest=None, os_name=None):

    # Остановка сервисов, если они уже запущены
    sudo("searchd --stop")

    # nginx + fpm + mongo
    sudo("/etc/init.d/nginx restart")    
    sudo("mongod --fork --logpath /var/log/mongodb.log --logappend --dbpath /var/lib/mongodb/")
    sudo("/etc/init.d/php5-fpm restart")
    sudo("gearmand -u root -d")
    sudo("searchd --config /usr/local/etc/sphinx.conf")

    # php workers
    sudo("php -c " + php_ini_path + " " + dest + "/application/background/startWorkers.php")

