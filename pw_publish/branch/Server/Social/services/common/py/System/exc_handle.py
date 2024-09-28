from logging import error

import sys, traceback

def printException(exceptionInfoList, detailed):
    exceptionType, exceptionValue, exceptionTraceback = exceptionInfoList
    if not detailed:
        exceptionTraceback = []
    strList = traceback.format_exception(exceptionType, exceptionValue, exceptionTraceback)
    return ''.join(strList)

def catch(detailed=True):
    error(getException(detailed))

def getException(detailed=True):
    return printException(sys.exc_info(), detailed)
