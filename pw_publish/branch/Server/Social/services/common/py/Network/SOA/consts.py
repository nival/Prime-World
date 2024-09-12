class Publish:
    INTERNAL = 0
    DIRECT = 1
    BALANCED = 2

class Launch:
    PYTHON_NEW_PROCESS = 0
    PYTHON_MAIN_THREAD = 1

class Keepalive:
    COORDINATOR = 0
    WATCHDOG = 1
    PID = 2
    PING = 3
