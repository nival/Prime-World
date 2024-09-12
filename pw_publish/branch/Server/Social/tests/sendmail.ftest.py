import smtplib, socket, time
from email.mime.text import MIMEText

_toaddr = 'danvorobiev@list.ru'
_toaddr2 = 'danila.vorobyov@nivalnetwork.com'
_msg = 'No prob at all, Dan...\n Send more gibberish, and a lot of unnecessary MIME headers.\n --\nWBR, Dan'

#~ SMTP_HOST = 'smtp.mail.ru'
#~ SMTP_PORT = 2525
#~ SMTP_TIMEOUT = 20

#~ SMTP_USERNAME = '225580980'
#~ SMTP_PWD = '089080'
#~ SMTP_FROMADDR = '225580980@mail.ru'

SMTP_HOST = 'smtp.mastermail.ru'
SMTP_PORT = 465
SMTP_TIMEOUT = 20

SMTP_USERNAME = 'pwconnect@testpw.com'
SMTP_PWD = 'ZRbhhGcBPiYigc'
SMTP_FROMADDR = 'pwconnect@testpw.com'


#-----------------------
# Create a text/plain message
msg = MIMEText( _msg )

# me == the sender's email address
# you == the recipient's email address
msg['Subject'] = 'Test message'
msg['From'] = SMTP_FROMADDR
msg['To'] = _toaddr

t0 = time.clock()
#-----------------------
# create connection
local_hostname = socket.gethostname()
print "local_hostname: %s" % local_hostname 
#smtp = smtplib.SMTP(SMTP_HOST, SMTP_PORT, local_hostname, SMTP_TIMEOUT)
smtp = smtplib.SMTP_SSL(SMTP_HOST, SMTP_PORT, local_hostname, timeout=SMTP_TIMEOUT)
print "SMTP OBJECT: ", smtp

t1 = time.clock()
#-----------------------
# authorise
result = smtp.login(SMTP_USERNAME, SMTP_PWD) 
print "LOGIN RESULT: ", result

#smtp.set_debuglevel(1)

t2 = time.clock()
#-----------------------
# send
smtp.sendmail(SMTP_FROMADDR, _toaddr, msg.as_string())
print "SENDMAIL RESULT: ", result

t3 = time.clock()

msg['Subject'] = 'Test message 2'
msg['To'] = _toaddr2
#-----------------------
# send
smtp.sendmail(SMTP_FROMADDR, _toaddr, msg.as_string())
print "SENDMAIL RESULT: ", result

t4 = time.clock()

smtp.quit()

print "TIMING: create %.4f, login %.4f, send %.4f, send2 %.4f" % (t1-t0, t2-t1, t3-t2, t4-t3)
# ----------------
# TIMING: create 0.0134, login 0.0209, send 2.0670
# ----------------
