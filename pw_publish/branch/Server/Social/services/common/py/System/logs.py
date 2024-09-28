# -*- coding: utf-8 -*-
import os
from stat import ST_DEV, ST_INO
import errno

import logging
import logging.handlers
from base.helpers import addRelPath

addRelPath("tornado")
from tornado.log import LogFormatter
logLevels = {
    'debug': logging.DEBUG,
    'info': logging.INFO,
    'warning': logging.WARNING,
    'error': logging.ERROR,
    'critical': logging.CRITICAL
}

class SafeWatchedFileHandler( logging.handlers.WatchedFileHandler ):
    """ в питоне 2.6.6 почему-то не подперта возможная ошибка при flush() уже закрытого старого лог-стрима
    """
    def emit(self, record):
        """
        Emit a record.

        First check if the underlying file has changed, and if it
        has, close the old stream and reopen the file to get the
        current stream.
        """
        # Reduce the chance of race conditions by stat'ing by path only
        # once and then fstat'ing our new fd if we opened a new log stream.
        # See issue #14632: Thanks to John Mulligan for the problem report
        # and patch.
        try:
            try:
                # stat the file by path, checking for existence
                sres = os.stat(self.baseFilename)
            except OSError as err:
                if err.errno == errno.ENOENT:
                    sres = None
                else:
                    raise
            # compare file system stat with that of our stream file handle
            if not sres or sres[ST_DEV] != self.dev or sres[ST_INO] != self.ino:
                if self.stream is not None:
                    # we have an open file handle, clean it up
                    try:
                        self.stream.flush()
                        self.stream.close()
                        self.stream = None  # See Issue #21742: _open () might fail.
                        # open a new file handle and get new stat info from that fd
                    except:
                        self.stream = None
                    self.stream = self._open()
                    self._statstream()
            logging.FileHandler.emit(self, record)
        except:
            pass # не хочется, чтобы код боевых серверов падал в произвольных местах из-за отсутствия места на диске; поэтому подпираем наглухо.


def getLoggingLevel( strLogLevel ):
    return logLevels.get(str(strLogLevel).lower(), 0)

def setupLoggerLevel(logger, logLevel):
    logger.setLevel(logLevels[logLevel])

def setupLogger(logger, logFile, logLevel=None, rotate=0):
    if logFile:
        if rotate > 0:
            handler = logging.handlers.TimedRotatingFileHandler( filename=logFile, when='M', interval=rotate )
        else:
            handler = SafeWatchedFileHandler( filename=logFile ) # под линуксом будем поддерживать переоткрытие файла при его изменении (утилитой logrotate)
    else:
        handler = logging.StreamHandler()
    #logFormat = "(%(thread)d) %(asctime)s.%(msecs)d %(levelname)s: %(message)s"
    #dateFormat = '%H:%M:%S'
    formatter = LogFormatter() #logging.Formatter(logFormat, dateFormat)
    handler.setFormatter(formatter)
    logger.addHandler(handler)
    if logLevel:
        setupLoggerLevel(logger, logLevel)
    logging.info( "main logging handler class: %s" % handler.__class__.__name__ )

def setup(logFile, logLevel, rotate=0, name=""):
    if name:
        setupLogger(logging.getLogger(name), logFile, logLevel, rotate)
    else:
        setupLogger(logging.getLogger(), logFile, logLevel, rotate)

def setupLevel(logLevel, name=""):
    if name:
        setupLoggerLevel(logging.getLogger(name), logLevel)
    else:
        setupLoggerLevel(logging.getLogger(), logLevel)


def setupParserArgs(parser):
    parser.add_argument('--log', default=None, help='Log file name')
    parser.add_argument('--loglevel', choices=['debug', 'info','warning','error', 'critical'], default='info', help='Logging severity level')
    parser.add_argument('--logrotate', type=int, default=0, help='Logging rotation')
    parser.add_argument('--log_http', type=int, default=1, help='Use http logger, 0/1')
    parser.add_argument('--log_http_level', choices=['debug', 'info','warning','error', 'critical'], default='warning', \
        help='Http logging severity level')
    parser.add_argument('--log_http_max_count', type=int, default=1000, help='Http logger max buffered messages count')
