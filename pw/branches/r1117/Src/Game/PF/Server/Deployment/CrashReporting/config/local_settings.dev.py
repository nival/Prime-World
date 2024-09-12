# -*- coding: utf-8 -*-

SITE_ADDRESS = 'http://%(server_name)s'
MEDIA_URL = SITE_ADDRESS + '/media/'

EMAIL_HOST = '%(email_host)s'
EMAIL_HOST_USER = '%(email_host_user)s'
EMAIL_HOST_PASSWORD = '%(email_host_password)s'

MAIL_FROM = '%(email_from)s'
MAIL_TO = ['%(email_to)s']

ADMIN_USERNAME = '%(admin_username)s'
ADMIN_EMAIL = '%(admin_email)s'
ADMIN_PASSWORD = 'XXXXXX' # этот пароль не используется, если доступ ограничен AD на уровне Apache

DATABASES = {
    'default':
        {
            'HOST': 'localhost',
            'NAME': '%(db_name)s',
            'PORT': '',
            'ENGINE': 'django.db.backends.postgresql_psycopg2',
            'USER': '%(db_user)s',
            'PASSWORD': '%(db_password)s',
        }
}

JIRA_ADDRESS = '%(jira_url)s'

CALLSTACK_SERVER = "%(callstack_server)s"

ADMINS = (
    ('%(admin_username)s', '%(admin_email)s'),
)

# вместо отправки писем, они складываются на сервере как отдельные файлы
EMAIL_BACKEND = 'django.core.mail.backends.filebased.EmailBackend'
EMAIL_FILE_PATH = '%(deploy_code_dir)s/emails'