import subprocess, time


def call(*popenargs, **kwargs):
    return process.pid


process = subprocess.Popen(["PW_Game.exe", "-crashrpt_disable"], stdout=subprocess.PIPE)
pid = process.pid
f = open("pid.txt", "w")
f.write(str(pid))
f.close()

secondsCountDown = 3600
secondsToSleep = 10
retcode = None

while ( secondsCountDown > 0 and retcode == None):
    time.sleep(secondsToSleep)
    secondsCountDown = secondsCountDown - secondsToSleep
    retcode = process.poll()
