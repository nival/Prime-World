from fabric.api import *
from fabric.colors import *
from fabric.contrib.console import confirm
from fabric.state import output
from fabric.contrib.files import exists

# Main settings
env.user='pwctl'
env.key_filename='/opt/pwctl/pwctl.rsa.key'
svnwcopy='/opt/pwcastle'
ip='192.168.29.35'

env.warn_only=True
output.running=False
output.status=False

# Assign servers roles
env.roledefs = {
	'loadbalancer' : [ip],
	'coordinator' : [ip],
	'xcoordinator' : [ip],
	'thrift' : [ip],
	'cf' : [ip],
	'connect' : [ip],
	'mirror' : [ip],
	'statistic' : [ip],
	'ms' : [ip],

	'ws' : ['192.168.50.3', '192.168.50.4', '192.168.50.5'],
	'xs' : ['192.168.50.3', '192.168.50.4', '192.168.50.5'],

	'chat' : ['192.168.50.6'],
	'friends' : ['192.168.50.6'],
	'guild' : ['192.168.50.6'],
	'party' : ['192.168.50.6'],

	'es' : ['192.168.50.7'],

	'ALL' : [ip, '192.168.50.3', '192.168.50.4', '192.168.50.5', '192.168.50.6', '192.168.50.7'],
}

@roles('ALL')
def run_command(cmd):
	"""
	Run command on all boxes of cluster.
	"""
	with show('running', 'output'):
		run(cmd)

@roles('ALL')
def put_file(local, remote="/tmp/", user='root', group='root'):
	"""
	Put file on all boxes of cluster.
	"""
	with show('running', 'output'):
		file_list=put(local, remote, use_sudo=True, mirror_local_mode=True)
	for file_name in file_list:
		sudo('chown ' + user + ':' + group + ' ' + file_name)

@roles('ALL')
def get_file(remote):
	"""
	Get file from all boxes of cluster.
	"""
	with show('running', 'output'):
		get(remote)


@roles('ALL')
def svn_info():
	"""
	Check svn workcopy revision on all hosts.
	"""
	with hide('running', 'status'):
		sudo("svn info " + svnwcopy + "| grep 'Revision:'")

@roles('ALL')
def svn_status():
	"""
	Check svn workcopy status on all hosts.
	"""
	with hide('running', 'status'):
		puts(magenta("===>\t" + env.host))
		sudo("svn status -q " + svnwcopy )

@roles('loadbalancer')
def close():
        """
        Enable maintenance mode to PWCastle cluster.
        """
        with hide('running', 'status'):
                if not confirm(yellow("Do you really want close PWCastle cluster?"), default=False):
                        abort("Aborting at user request.")
                if exists("/var/run/pwcastle_maintenance.lock"):
                        puts(yellow("Maintenance mode already enabled!"))
                        exit(0)
                else:
                        with hide('warnings','output'):
                                sudo("iptables -D INPUT -p tcp -m tcp --dport 88 -j MAINTENANCE")
                                if sudo("iptables -I INPUT 3 -p tcp -m tcp --dport 88 -j MAINTENANCE"):
                                        abort(red("Error: Maintenance mode wasn't enalbed!"))

                                sudo("touch /var/run/pwcastle_maintenance.lock")
                                puts(green("Maintenance mode was enalbed!"))

@roles('loadbalancer')
def open():
        """
        Disable maintenance mode to PWCastle cluster.
        """
        with hide('running', 'status'):
                if not confirm(yellow("Do you really want open PWCastle cluster?"), default=False):
                        abort("Aborting at user request.")
                if not exists("/var/run/pwcastle_maintenance.lock"):
                        puts(yellow("Maintenance mode already disabled!"))
                        exit(0)
                else:
                        with hide('warnings','output'):
                                if sudo("iptables -D INPUT -p tcp -m tcp --dport 88 -j MAINTENANCE"):
                                        abort(red("Error: Maintenance mode wasn't enalbed!"))

                                sudo("rm /var/run/pwcastle_maintenance.lock")
                                puts(green("Maintenance mode was disabled!"))

def do_service(service, action):
	with hide('warnings','running'):
		result=sudo('/etc/init.d/' + service + ' ' + action)
		if action == 'start' and result.failed and not confirm(red("Starting failed. Continue anyway?")):
			abort("Aborting at user request.")

@parallel
def do_service_parallel(service, action):
	with hide('warnings','running','stdout'):
		result=sudo('/etc/init.d/' + service + ' ' + action)
		puts("out: " + result)
		if action == 'start' and result.failed and not confirm(red("Starting failed. Continue anyway?")):
			abort("Aborting at user request.")


def status():
	"""
	Check ALL services status. 
	"""
	puts(cyan("===> Check service status <==="))
	execute(do_service,'pw-coordinator', 'status', role='coordinator')
	execute(do_service,'pw-xcoordinator', 'status', role='xcoordinator')
	execute(do_service,'pw-thrift', 'status', role='thrift')
	execute(do_service,'pw-cf', 'status', role='cf')
	execute(do_service,'pw-connect', 'status', role='connect')
	execute(do_service,'pw-mirror', 'status', role='mirror')
	execute(do_service,'pw-statistic', 'status', role='statistic')
	execute(do_service,'pw-ms', 'status', role='ms')

	execute(do_service,'pw-ws', 'status', role='ws')
	execute(do_service,'pw-xs', 'status', role='xs')

	execute(do_service,'pw-chat', 'status', role='chat')
	execute(do_service,'pw-friends', 'status', role='friends')
	execute(do_service,'pw-guild', 'status', role='guild')
	execute(do_service,'pw-party', 'status', role='party')

	execute(do_service,'pw-es', 'status', role='es')


def stop():
	"""
	Stop ALL PWCaslte services. 
	"""
	if not confirm(yellow("Do you really want stop PWCastle cluster?"), default=False):
		abort("Aborting at user request.")

	puts(cyan("===> Stopping PWCastle cluster <==="))
	execute(do_service,'pw-coordinator', 'stop', role='coordinator')
	execute(do_service,'pw-xcoordinator', 'stop', role='xcoordinator')
	execute(do_service,'pw-thrift', 'stop', role='thrift')
	execute(do_service,'pw-cf', 'stop', role='cf')
	execute(do_service,'pw-connect', 'stop', role='connect')
	execute(do_service,'pw-mirror', 'stop', role='mirror')
	execute(do_service,'pw-statistic', 'stop', role='statistic')
	execute(do_service,'pw-ms', 'stop', role='ms')

	execute(do_service_parallel,'pw-ws', 'stop', role='ws')
	execute(do_service_parallel,'pw-xs', 'stop', role='xs')

	execute(do_service,'pw-chat', 'stop', role='chat')
	execute(do_service,'pw-friends', 'stop', role='friends')
	execute(do_service,'pw-guild', 'stop', role='guild')
	execute(do_service,'pw-party', 'stop', role='party')

	execute(do_service,'pw-es', 'stop', role='es')

def start():
	"""
	Start ALL PWCaslte services. 
	"""
	puts(cyan("===> Starting PWCastle cluster <==="))
	execute(do_service,'pw-coordinator', 'start', role='coordinator')
	execute(do_service,'pw-xcoordinator', 'start', role='xcoordinator')
	execute(do_service,'pw-thrift', 'start', role='thrift')
	execute(do_service,'pw-cf', 'start', role='cf')
	execute(do_service,'pw-connect', 'start', role='connect')
	execute(do_service,'pw-mirror', 'start', role='mirror')
	execute(do_service,'pw-statistic', 'start', role='statistic')
	execute(do_service,'pw-ms', 'start', role='ms')

	execute(do_service_parallel,'pw-ws', 'start', role='ws')
	execute(do_service_parallel,'pw-xs', 'start', role='xs')

	execute(do_service,'pw-chat', 'start', role='chat')
	execute(do_service,'pw-friends', 'start', role='friends')
	execute(do_service,'pw-guild', 'start', role='guild')
	execute(do_service,'pw-party', 'start', role='party')

	execute(do_service,'pw-es', 'start', role='es')

