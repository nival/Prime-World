import os
import sys
import subprocess

path = os.path.abspath('../../tools/InspIRCd')

def _replacePort(content, port):
    li = content.find('<bind')
    if li >= 0:
        ri = content[li:].find('>')
        if ri >= 0:
            bind = content[li:li+ri]
            s = 'port="'
            li2 = bind.find(s)
            if li2 >= 0:
                ri2 = bind[li2+len(s):].find('"')
                if ri2 >= 0:
                    startIndex = li+li2+len(s)
                    endIndex = li+li2+len(s)+ri2
                    return content[:startIndex]+str(port)+content[endIndex:]
    return None

def replacePort(cfgPath, port):
    if os.path.isfile(cfgPath):
        f = open(cfgPath, 'rb')
        content = f.read()
        f.close()
        new_content = _replacePort(content, port)
        if new_content:
            if new_content != content:
                f = open(cfgPath, 'wb')
                f.write(new_content)
                f.close()
            return True
    return False

if '--start' in sys.argv:
    sys.path.append(os.path.abspath('../../cfg'))
    import chat_cfg

    cfgPath = os.path.join(path, 'conf', 'inspircd.conf')
    if replacePort(cfgPath, chat_cfg.irc_port):
        cwd = os.getcwd()
        os.chdir(path)
        if os.name in ('nt',):
            s = subprocess.Popen(args='inspircd.exe', stdout = subprocess.PIPE, stderr = subprocess.PIPE)
        else:
            s = subprocess.Popen(args='inspircd', stdout = subprocess.PIPE, stderr = subprocess.PIPE)
        print s
        os.chdir(cwd)
    else:
        sys.stderr.write('Error: can\'t configure port')
        sys.exit(1)

if '--stop' in sys.argv:
    pidPath = os.path.join(path, 'data', "inspircd.pid")
    if not os.path.isfile(pidPath):
        sys.stderr.write("Can't find pid file\n")
        sys.exit(1)
    pid = open(pidPath, 'rb').read()
    os.system('TASKKILL /F /PID %s' % pid)
