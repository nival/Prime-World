# -*- coding: utf-8 -*-
import datetime
from StringIO import StringIO
from fabric.api import env, sudo, run, put, cd
from fabric.contrib.files import sed


def install_nginx_with_upload_module():
    # extras содержит необходимый модуль upload
    sudo('apt-get install -y nginx-extras')
    # После установки желательно запретить nginx обновляться,
    # иначе он обновится на ванильную версию из репозитория
    # и все перестанет работать. (Н. Комаров)
    sudo('echo "nginx-common hold" | dpkg --set-selections')
    sudo('echo "nginx-extras hold" | dpkg --set-selections')


def install_apache():
    sudo('apt-get install -y apache2 libapache2-mod-wsgi')


def install_postgres():
    sudo('apt-get install -y postgresql')


def install_rabbitmq():
    sudo('apt-get install -y erlang-nox')
    put('packets/rabbitmq-server_2.7.1-1_all.deb', 'rabbitmq-server_2.7.1-1_all.deb')
    sudo('dpkg -i rabbitmq-server_2.7.1-1_all.deb')
    run('rm rabbitmq-server_2.7.1-1_all.deb')


def install_pip():
    sudo('apt-get install -y python-setuptools')
    sudo('apt-get install -y python-pip')


def install_python_packages():
    # все зависимые пакеты храним локально для ускорения деплоя
    sudo('apt-get install -y libpq-dev python-dev')
    sudo('apt-get install -y python-lxml')

    TMP_DIR = '/tmp/tmp_python_packages'
    run('mkdir -p %s' % TMP_DIR)
    for packet in [
        'amqp-1.0.11.tar.gz',
        'anyjson-0.3.3.tar.gz',
        'billiard-2.7.3.28.tar.gz',
        'celery-3.0.19.tar.gz',
        'Django-1.4.tar.gz',
        'django-celery-3.0.17.tar.gz',
        'django-debug-toolbar-0.9.4.tar.gz',
        'kombu-2.5.10.tar.gz',
        'poster-0.8.1.tar.gz',
        'psycopg2-2.5.tar.gz',
        'python-dateutil-2.1.tar.gz',
        'pytz-2013b.tar.gz',
        'six-1.3.0.tar.gz',
        'South-0.8.1.tar.gz',
        'django-pagination-1.0.7.tar.gz',
        'django-annoying-0.7.7.tar.gz',
        'suds-0.4.tar.gz',
    ]:
        put('packets/%s' % packet, TMP_DIR)
    put('config/requirements.txt', 'requirements.txt')
    sudo('pip install --no-index --find-links=file://%s -r requirements.txt' % TMP_DIR)
    sudo('rm requirements.txt')
    sudo('rm -rf %s' % TMP_DIR)


def config_nginx():
    env.dist_packages_path = sudo('python -c "import os; import django; print os.path.dirname(django.__file__)"')
    nginx_config = open('config/nginx_crash_report.conf').read()
    put(StringIO(nginx_config % env), '/etc/nginx/sites-available/crash_report.conf', use_sudo=True)
    sudo('ln -s -f /etc/nginx/sites-available/crash_report.conf /etc/nginx/sites-enabled/crash_report.conf')


def config_apache():
    apache_config_name = 'apache_crash_report.conf'
    apach_config = open('config/apache_crash_report.%s.conf' % env.mode).read()
    put(StringIO(apach_config % env), '/etc/apache2/sites-available/' + apache_config_name, use_sudo=True)
    sudo('ln -s -f  /etc/apache2/sites-available/%s /etc/apache2/sites-enabled/%s' % (apache_config_name, apache_config_name))
    sudo('a2enmod authnz_ldap')
    sed('/etc/apache2/ports.conf', 'NameVirtualHost \*:80$', 'NameVirtualHost *:8080', use_sudo=True)
    sed('/etc/apache2/ports.conf', 'Listen 80$', 'Listen 8080', use_sudo=True)
    sudo('echo "ServerName localhost" >> /etc/apache2/apache2.conf')


def config_postgres():
    db_init_command = open('config/db_init_tmp.sql').read()
    db_init_file = 'db_init_tmp.sql'
    put(StringIO(db_init_command % dict(env)), db_init_file)
    sudo("su postgres -c 'psql -f %s'" % db_init_file)
    sudo('rm %s' % db_init_file)


def config_celery():
    celeryd_config = open('config/celeryd').read()
    put(StringIO(celeryd_config % env), '/etc/init.d/celeryd', use_sudo=True)
    # celeryevcam - чтобы в админке можно было видеть состояние задач celery
    celeryevcam_config = open('config/celeryevcam').read()
    put(StringIO(celeryevcam_config % env), '/etc/init.d/celeryevcam', use_sudo=True)
    sudo('update-rc.d celeryd defaults')
    sudo('chmod +x /etc/init.d/celeryd')
    sudo('chmod +x /etc/init.d/celeryevcam')


def deploy_code():
    sudo('apt-get install -y subversion')
    run('svn --version')  # auto-create ~/.subversion
    sed('~/.subversion/servers', '# store-passwords = no', 'store-passwords = no')
    
    place_to_deploy = env.deploy_code_dir
    sudo('mkdir -p %s' % place_to_deploy)
    with cd(place_to_deploy):
        sudo('mkdir -p logs')
        # echo p = dirty hack for "(R)eject, accept (t)emporarily or accept (p)ermanently?" message
        sudo(' echo p | svn co --username %s --password %s %s .' %
             (env.svn_user, env.svn_password, env.svn_url))
        # TODO: вот тут оно иногда спрашивает про сохранение plaintext password, необходимо это обрабатывать
    sudo('chown -R %s:%s %s' % (env.user, env.user, place_to_deploy))
    local_settings = open('config/local_settings.%s.py' % env.mode).read()
    put(StringIO(local_settings % env), env.manage_dir + '/local_settings.py', use_sudo=True)


def init_django_db():
    with cd(env.manage_dir):
        sudo('python manage.py syncdb')
        sudo('python manage.py migrate')
    sudo('chown %s:%s -R %s' % (env.web_user, env.web_user, env.deploy_code_dir))


def config_crontab():
    celeryd_config = open('config/cronfile').read()
    put(StringIO(celeryd_config % env), '/etc/cron.d/crashreport', use_sudo=True)
    sudo('chown root:root /etc/cron.d/crashreport')
    sudo('chmod 400 /etc/cron.d/crashreport')


def restart_services():
    sudo('/etc/init.d/apache2 stop', pty=False)
    sudo('/etc/init.d/nginx start', pty=False)
    sudo('/etc/init.d/apache2 start', pty=False)
    sudo('/etc/init.d/celeryd start', pty=False)
    sudo('/etc/init.d/celeryevcam start', pty=False)

def update():
    with cd(env.manage_dir):
        sudo('svn up --username %s --password %s .' % (env.svn_user, env.svn_password))
    restart_services()
    
    
def deploy():
    start = datetime.datetime.now()
    sudo('apt-get update')
    
    install_nginx_with_upload_module()
    install_apache()
    install_postgres()
    install_rabbitmq()
    install_pip()
    install_python_packages()

    config_nginx()
    config_apache()
    config_postgres()
    config_celery()

    deploy_code()
    init_django_db()
    config_crontab()

    restart_services()
    print 'Deployed in %s' % (datetime.datetime.now() - start)
