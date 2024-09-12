import json
import os
import sys
import tarfile
import datetime
import tempfile

from fabric.context_managers import settings
from fabric.contrib.files import exists
from fabric.api import *

def EXIT(error_code = 0):
    try:
        os.remove(env.key_filename)
    except Exception, e:
        pass # nevermind, tmp file
    sys.exit(error_code)

def log(message):
    if VERBOSE:
        sys.stdout.write(message + '\n')

def log_error(message):
    sys.stderr.write(message + '\n')

def file_name_by_date(date):
    return '%s.tgz' % date.strftime('%Y.%m.%d')

def cached_archive_content(date):
    return '/tmp/%s.content' % file_name_by_date(date)

def check_files_exists(file_name):
    if not exists(file_name, verbose=VERBOSE):
        log_error('File %s not found.' % file_name)
        EXIT(1)
    return True

def exists_and_newer(file1, file2):
    result = run('test %s -nt %s' % (file1, file2))
    return result.return_code == 0

def list(date):
    log('Searching files in %s directory' % env.logs_path)
    with cd (env.logs_path):
        file_name = file_name_by_date(date)
        check_files_exists(file_name)
        log('Archive %s found.' % file_name)
        cached_file = cached_archive_content(date)
        if USE_CACHE and exists_and_newer(cached_file, file_name):
            log('Getting content from cache file')
            files = run('cat %s' % cached_file)
        else:
            command = 'tar -ztf %s | tee %s' % (file_name, cached_file)
            files = run(command, quiet=not VERBOSE)

    result = []
    for file in files.splitlines():
        if file.startswith('./'):
            result.append(file[2:])
            continue
        result.append(file)
    return '\n'.join(sorted(result))

def delete_cache():
    result = run('rm -f /tmp/*.tgz.content')
    return result.return_code

def extract(date, wildcards = None, destination = None):
    file_name = file_name_by_date(date)

    tmp_dir = run('mktemp -d', quiet=not VERBOSE)
    remote_archive_name = 'files.tgz'
    with cd(tmp_dir):
        full_file_path = env.logs_path + '/' + file_name
        log('Searching archive file %s' % full_file_path)
        check_files_exists(full_file_path)
        log('File found.')
        command = 'tar -zxf %s' % full_file_path
        if wildcards:
            wildcards = './' + wildcards
            command += ' --wildcards %s' % wildcards
        command += ' && tar cvfz %s * --remove-files' % remote_archive_name
        log('Extracting %s files from archive' % wildcards)
        run(command, quiet=not VERBOSE)
        fd, tmp_file_path = tempfile.mkstemp()
        os.close(fd)
        log('Loading %s from remote machine..' % remote_archive_name)
        get(remote_archive_name, tmp_file_path)
        log('Done')
        log('Extracting %s to %s' % (tmp_file_path, destination or 'current directory'))
        extract_local_tar(tmp_file_path, destination)
        sys.stdout.write('Done')
        os.remove(tmp_file_path)

def extract_local_tar(filename, destination = None):
    file = filename
    tar = tarfile.open(file)
    if destination:
        tar.extractall(destination)
    else:
        tar.extractall()
    tar.close()

def check_connection():
    if VERBOSE:
        sys.stdout.write('Checking connection to %s...\n' % env.host_string)
    try:
        run('uname -a', quiet=not VERBOSE)
    except Exception, e:
        log(str(e))
        sys.stderr.write('Connection failed.\n')
        EXIT(1)
    else:
        sys.stderr.write('Connection OK.\n')
    return 0

def mktmp_file_with_content(content):
    fd, filename = tempfile.mkstemp()
    os.close(fd)
    f = open(filename, 'wb')
    f.write(content)
    f.close()
    return filename

def init_environ(config_file, host_name):
    config_dict = json.load(open(config_file))
    custom_config = config_dict['servers'].get(host_name, {})

    env.user = custom_config.get('user', config_dict['default_user'])
    env.logs_path = custom_config.get('path', config_dict['default_path'])
    env.password = custom_config.get('passphrase', config_dict['default_passphrase'])
    key_string = custom_config.get('key', config_dict['default_key'])
    env.key_filename = mktmp_file_with_content(key_string)
    env.host_string = host_name


def help_exit():
    tool_name = 'get_remote_logs.exe'
    sys.stderr.write('\nUsage:  %s <server_address> - check connection with server.\n' % tool_name)
    sys.stderr.write('\t%s <server_address> <date_dd.mm.yyyy> - get list of files for specified date.\n' % tool_name)
    sys.stderr.write('\t%s <server_address> <date_dd.mm.yyyy> <file_mask> [<destination_directory] \n\t\t- extract files by mask to current (or specified) directory\n' % tool_name)
    sys.stderr.write('\t%s --delete-cache - delete all cache with archive content from server.\n' % tool_name)
    sys.stderr.write('\n\n')
    sys.stderr.write('Add --verbose parameter for debug messages\n')
    sys.stderr.write('Add --no-cache to not use cache for getting archive content\n')
    sys.stderr.write('Add --config=<config_file> parameter to specify config file (config.json in current directory using by default\n')
    sys.stderr.write('\n\n')
    sys.stderr.write('Examples:\n')
    sys.stderr.write('\t%s v160.SITE.com\n' % tool_name)
    sys.stderr.write('\t%s v160.SITE.com 27.02.2013\n' % tool_name)
    sys.stderr.write('\t%s v160.SITE.com 27.02.2013 coordinator* d:\logs --verbose\n' % tool_name)
    sys.stderr.write('\n')
    sys.exit(1)

if __name__ == '__main__':
    sys_argv = []

    VERBOSE = False
    USE_CACHE = True
    DELETE_CACHE = False
    CONFIG_FILE = 'config.json'

    for arg in sys.argv[1:]:
        if arg == '--verbose':
            VERBOSE = True
            continue
        if arg == '--no-cache':
            USE_CACHE = False
            continue
        if arg == '--delete-cache':
            DELETE_CACHE = True
            continue
        if arg.startswith('--config='):
            CONFIG_FILE = arg[len('--config='):]
            continue
        sys_argv.append(arg)

    if len(sys_argv) < 1:
        help_exit()

    if not os.path.isfile(CONFIG_FILE):
        log_error('Config file %s not found.\nUse --config=<config_file> parameter to specify config file.' % CONFIG_FILE)
        sys.exit(1)

    host_name = sys_argv[0]
    init_environ(CONFIG_FILE, host_name)

    if len(sys_argv) == 1:
        if DELETE_CACHE:
            EXIT(delete_cache())
        else:
            EXIT(check_connection())

    date_string = sys_argv[1]
    try:
        day = datetime.datetime.strptime(date_string, '%d.%m.%Y')
    except Exception, e:
        log_error('Wrong date format.')
        help_exit()

    destination = None
    if len(sys_argv) > 3:
        destination = sys_argv[3]

    with settings(hide('warnings', 'running', 'stdout', 'stderr'),warn_only=True):
        if len(sys_argv) == 2:
            sys.stdout.write(list(day) + '\n')
        else:
            wildcards = sys_argv[2]
            extract(day, wildcards, destination)
    EXIT()