#-*- coding: cp1251 -*-
import smtplib
import os
import sys
import time
from email.MIMEMultipart import MIMEMultipart
from email.MIMEBase import MIMEBase
from email.MIMEText import MIMEText
from email.Utils import COMMASPACE, formatdate
from email import Encoders
import ZDATAChecker
import pysvn

#Skype based error reports
try:
    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../ScriptRunner")))
    from SkypeInterface import SkypeManager
except:
    class SkypeManager():
        def __init__(self):
            pass
        def sendMessage(self, msg):
            print msg
    print "can't find skypeInterface, continue with dummy output"

#create svn client
client = pysvn.Client()
PFFolder = os.path.abspath(os.path.split(os.path.abspath(__file__))[0] + "/../../")

def send_mail(send_from, send_to, subject, text, files=[], server="10.0.0.3"):
  assert type(send_to)==list
  assert type(files)==list

  msg = MIMEMultipart()
  msg['From'] = send_from
  msg['To'] = COMMASPACE.join(send_to)
  msg['Date'] = formatdate(localtime=True)
  msg['Subject'] = subject

  msg.attach( MIMEText(text) )

  for f in files:
    part = MIMEBase('application', "octet-stream")
    part.set_payload( open(file,"rb").read() )
    Encoders.encode_base64(part)
    part.add_header('Content-Disposition', 'attachment; filename="%s"' % os.path.basename(f))
    msg.attach(part)

  smtp = smtplib.SMTP(server)
  smtp.sendmail(send_from, send_to, msg.as_string())
  smtp.close()

ReportFileName = "report.txt"
Mail_From = "TestSrv@d-inter.ru"
Mail_To = ["matthew@d-inter.ru", "ibragimov@d-inter.ru", "oleg@d-inter.ru", "eugbel@d-inter.ru"]
PrevRevision = -1
eh = SkypeManager()
OneSuccesfullIteration = True

def main():
    global PrevRevision, OneSuccesfullIteration
    sys.stdout.write("Updating PF... " + PFFolder)
    client.update(PFFolder, revision=pysvn.Revision(pysvn.opt_revision_kind.head), recurse=True)
    currentRevision = client.info2(PFFolder, revision=pysvn.Revision(pysvn.opt_revision_kind.head), recurse=False)[0][1].rev.number
    sys.stdout.write("\nok\n")

    if PrevRevision == currentRevision:
        return "Done! No new commits, ver = " + str(currentRevision)
    PrevRevision = currentRevision

    sys.stdout.write("Starting whole project check... ")
    if ZDATAChecker.runToFile(ReportFileName) > 0:
        with open(ReportFileName, "r") as reportFile:
            linestring = reportFile.read()
        OneSuccesfullIteration = False
        eh.sendMessage("[scr/zdata] check FAIL on rev = " + str(currentRevision) + "\n" + linestring)
        #send_mail(Mail_From, Mail_To, "[scr/zdata] check FAIL on rev = " + str(currentRevision), linestring)
        sys.stdout.write("FAIL\n")
    else:
        if OneSuccesfullIteration == False:
            eh.sendMessage("[scr/zdata] all errors FIXED on rev = " + str(currentRevision))
        OneSuccesfullIteration = True
        sys.stdout.write("ok\n")
        #send_mail(Mail_From, Mail_To, "[scr/zdata] check OK on rev = " + str(currentRevision), "")

    return "Done! ver = " + str(currentRevision)

if __name__ == "__main__":
    while (1):
        print "\n\nZDATA check...\n----------------------\n\n"
        msg = main()
        print msg + "\n"
        print "\nSleeping from: " + time.strftime("%H:%M")
        time.sleep(60*60*3)
