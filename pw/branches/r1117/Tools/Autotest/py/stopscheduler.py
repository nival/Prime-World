# -*- coding: cp1251 -*-
from autotestcommon import *

fStopFile = open(stopSchedulerFileName, "w")
fStopFile.close()

PrintMessage( "Scheduler stop requested" )
