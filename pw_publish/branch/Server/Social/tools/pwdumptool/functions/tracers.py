# -*- coding: utf-8 -*-
import os
from stat import ST_DEV, ST_INO
import errno

import logging
import logging.handlers

import traceback, sys


## объединяем и распечатываем exception info
def printException(exceptionInfoList):
    exceptionType, exceptionValue, exceptionTraceback = exceptionInfoList
    strList = traceback.format_exception(exceptionType, exceptionValue, exceptionTraceback)
    return "catch: " + (''.join(strList))


def catch(app, msg=None, *args):
    res = printException(sys.exc_info())
    if msg is None:
        app.logger.error(res)
    elif args:
        app.logger.error(msg + "\n%s", *(args + (res,)))
    else:
        app.logger.error("%s\n%s", msg, res)
    return res


class SafeWatchedFileHandler( logging.handlers.WatchedFileHandler ):
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
            pass

