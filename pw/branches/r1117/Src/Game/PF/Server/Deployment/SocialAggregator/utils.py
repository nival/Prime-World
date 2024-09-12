import subprocess
from fabric.api import run, sudo, cd
from fabric.operations import put

def runbg( command, out_file="/dev/null", err_file=None, shell=True, pty=False ):
    run('nohup %s > %s 2>%s </dev/null &' % (command, out_file, err_file or '&1'), shell, pty)

def runbg2( command, out_file="/dev/null", err_file=None, shell=True, pty=False ):
    run('nohup %s > "%s" 2> "%s" < /dev/null &' % (command, out_file, err_file or out_file), shell, pty)

class SVN:

    def __init__(self, user, password, revision=None):
        self.args = [
            'sudo',
            'svn',
            '--trust-server-cert',
            '--non-interactive',
        ]
        if user:
            self.args.extend(['--username', user])
            if password:
                self.args.extend(['--password', password])
        self.revision = revision

    def do(self, dest, _args, use_revision=True):
        args = self.args+_args
        args.append(dest)
        if use_revision and self.revision:
            args.extend(['--revision', self.revision])
        run(' '.join(args))

class Fab:


    def __init__(self, key, hosts, login, password):
        self.key = key
        self.host = hosts[0][0]
        self.port = hosts[0][1]
        self.login = login
        self.password = password

    def _do(self, arg):
        args = [    
            'fab',
            '-H',
            self.host,
            '--port',
            str(self.port),
            '--no-keys',
            '-i',   
            self.key, 
            '--abort-on-prompts',
            '--user=' + self.login,
            '--password=' + self.password,
            '--shell="/bin/bash -l -c"',
            arg,  
        ]
        s = subprocess.Popen(' '.join(args), stderr = subprocess.PIPE)
        s.wait()

    def _call(self, name, args):
        arg = name
        if len(args) > 0:
            arg += ':'
            arg += ','.join([pname+'='+pvalue for pname, pvalue in args.items()])
        self._do(arg)

    class Callback:

        def __init__(self, name, callback):
            self.name = name 
            self.callback = callback

        def __call__(self, **args):
            return self.callback(self.name, args)

    def __getattr__(self, name):
        return Fab.Callback(name, self._call)


def make_install_php_ext(ext_name, dir_name):
    put('./vendor/' + ext_name, '/usr/src/' + ext_name, use_sudo=True)
    sudo('tar -xvf /usr/src/' + ext_name + ' -C /usr/src')
    with cd('/usr/src/' + dir_name):
        sudo('phpize')

    run('/usr/src/' + dir_name + '/configure')
    sudo('make')
    sudo('make install')
    sudo('apt-get update -y')
