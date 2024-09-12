# -*- coding: utf-8 -*-
import sys, smtplib, socket, time, hashlib, logging
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.utils import formataddr, formatdate

import traceback, socket
from logging import info, error as err

_TOADDR = u'danvorobiev@list.ru'
_TOADDR2 = 'danila.vorobyov@nivalnetwork.com'
AUID = 12345
#_msg = 'No prob at all, Dan...\n Send more gibberish, and a lot of unnecessary MIME headers.\n --\nWBR, Dan'

MAIL_PATH = "../mail"

#~ # ------------------------------------
USE_SSL = 0
SMTP_HOST = 'smtp.mail.ru'
SMTP_PORT = 2525
SMTP_TIMEOUT = 20

SMTP_USERNAME = '225580980'
SMTP_PWD = '089080'
SMTP_FROMNAME = 'Prime World'
SMTP_FROMADDR = '225580980@mail.ru'

#~ # ------------------------------------
#~ USE_SSL = 1
#~ SMTP_HOST = 'smtp.mastermail.ru'
#~ SMTP_PORT = 465
#~ SMTP_TIMEOUT = 20

#~ SMTP_USERNAME = 'pwconnect@testpw.com'
#~ SMTP_PWD = 'ZRbhhGcBPiYigc'
#~ SMTP_FROMNAME = 'Prime World'
#~ SMTP_FROMADDR = 'pwconnect@testpw.com'

# ------------------------------------
COORDINATOR_PWC_STATIC_IMAGE_PATH = "."
COORDINATOR_PWC_WEBFACE = "http://ru.pwcastle.nivalnetwork.com:88/pwc"
#COORDINATOR_PWC_WEBFACE = "http://ru.castle.nivalnetwork.com:88/pwc"

##--------------------------------------------------------------------------------------------------------------------------------------
## словарик, к ключам которого можно обращаться как к полям объекта, dict.name 
class ClassDict(dict):
    """Dictionary behaving like an object."""
    def __getattr__(self, key):
        try:
            return self.get(key)
        except KeyError:
            raise AttributeError(key)

    def __getattrPickle__(self, key):
        try:
            if key == "__getstate__":
                return self.__getstate__
            else:
                return self[key]
        except KeyError:
            raise AttributeError(key)
            
    def __setattr__(self, key, value):
        self.__setitem__(key, value)

    def __getstate__(self):
        print "__getstate__ called"
        return self.__dict__
        
## объединяем и распечатываем exception info
def printException(exceptionInfoList):
    exceptionType, exceptionValue, exceptionTraceback = exceptionInfoList
    strList = traceback.format_exception(exceptionType, exceptionValue, exceptionTraceback)
    strOutput = "catch:"
    for s in strList:
        strOutput += s
    return strOutput 
    
def catch():
    res = printException(sys.exc_info())
    err( res )
    return res
    
def md5( arg ):
    return hashlib.md5( str(arg) ).hexdigest()

def randomMD5():
    return hashlib.md5( str(time.time()) ).hexdigest()

## ------------------------------------------------------------
## полностью эмулируем генерацию и отправку письма из PWConnect
class ISMTPSender:
    def sendMail( self, toaddr, subj, msgtext, plaintext, **kwargs ):
        try:
            local_hostname = socket.gethostname()
            if USE_SSL:
                smtp = smtplib.SMTP_SSL( SMTP_HOST, SMTP_PORT, local_hostname, timeout=SMTP_TIMEOUT )
            else:
                smtp = smtplib.SMTP( SMTP_HOST, SMTP_PORT, local_hostname, SMTP_TIMEOUT )
            info( "smtp connect: %s" % smtp )
            
            result = smtp.login( str(SMTP_USERNAME), str(SMTP_PWD) ) 
            info( "smtp.login result: %s" % str(result) )

            # Record the MIME types of both parts - text/plain and text/html.
            msg = MIMEMultipart('alternative')
            part1 = MIMEText(plaintext, 'plain', 'utf8')
            part2 = MIMEText(msgtext, 'html', 'utf8')
            
            # Attach parts into message container.
            # According to RFC 2046, the last part of a multipart message, in this case
            # the HTML message, is best and preferred.
            msg.attach(part1)
            msg.attach(part2)

            msg['Subject'] = subj
            msg['From'] = formataddr( (SMTP_FROMNAME, SMTP_FROMADDR) )
            msg['To'] = toaddr
            msg['Date'] = formatdate( localtime=True )

            msg_string = msg.as_string()
            dumpfile = open("msgdump.%s.txt" % int(time.time()), "wt")
            dumpfile.write( msg_string )
            dumpfile.close()
            
            sendresult = smtp.sendmail( SMTP_FROMADDR, toaddr, msg_string )
            info( "smtp.sendmail result: %s" % sendresult )
            
            smtp.quit()
            
            # если что-то пойдет не так, smtp.login/sendmail бросят exception
        except:
            catch()
        
        
class PWCEmulation:
    """ """
    EMAIL_ENCODINGS = ['utf8']
    EMAIL_LENGTH = xrange(5, 65) # от 5 до 64 символов включительно
    DEFAULT_MESSAGES = {
        'title': {
            'confirm': u"[Confirm registration]",
            'reset_pwd': u"[Reset Password]",
            'change_pwd_link': u"[Reset Password Link]",
        },
        'body': {
            'confirm': u"Activation code %s\n \nClick this link to activate:\n%s",
            'reset_pwd': u"New password:\n%s",
            'change_pwd_link': u"Click this link to change password:\n%s",
        },
    }
    
    def __init__(self, locale="RU"):
        self.locale = locale
        self.I = ClassDict( SMTP=ISMTPSender() ) 
        
    def importLocaleMessagePart( self, msg_type, msg_part, locale=None ):
        if not locale:
            locale = self.locale
        filename = "%s/%s.%s.%s" % (MAIL_PATH, locale, msg_type, msg_part)
        try:
            msg_file = open(filename, "rt")
            msg_unicode = unicode(msg_file.read(), "utf8")
            msg_unicode = msg_unicode.replace("@@@imagepath", COORDINATOR_PWC_STATIC_IMAGE_PATH)
            msg_unicode = msg_unicode.replace("@@@webface", COORDINATOR_PWC_WEBFACE)
            msg_utf8 = msg_unicode.encode("utf8")
            return msg_utf8
        except:
            catch()
            warn("fail opening message template file %r" % filename)
            PARTS = self.DEFAULT_MESSAGES.get(msg_part, {})
            return PARTS.get(msg_type, "")
            
    def sendConfirmEmail( self, pwc, message_type="confirm" ):
        # TODO: текст письма должен быть красивый и правильно локализованный, а линк должен вести на веб-морду, которая сама исполнит запрос к соц.серверу и выдаст красивый ok/fail
        activation_params = "action=pwc_confirm_pretty&snuid=%s&confirm=%s&locale=%s" % (pwc.email_md5, pwc.confirm_token, self.locale)
        msg_header = self.importLocaleMessagePart("all", "header") 
        msg_footer = self.importLocaleMessagePart("all", "footer") 
        msg_template = self.importLocaleMessagePart(message_type, "body") 
        msg_title = self.importLocaleMessagePart(message_type, "title")
        msg_plain = self.importLocaleMessagePart(message_type, "plain") 
        
        # заменяем параметры
        info("msg_template: %r\n msg_template class: %s" % (msg_template, msg_template.__class__))
        msg_body = unicode(msg_template, "utf8")
        msg_body = msg_body.replace("@@@acc", pwc.email)
        msg_body = msg_body.replace("@@@params", activation_params)
        msg_body_utf8 = msg_body.encode("utf8")
        
        msg_plain = unicode(msg_plain, "utf8")
        msg_plain = msg_plain.replace("@@@acc", pwc.email)
        msg_plain = msg_plain.replace("@@@params", activation_params)
        msg_plain_utf8 = msg_plain.encode("utf8")
        
        try:
            msg_body = msg_header + msg_body_utf8 + msg_footer
        except:
            catch()
            
        # и отправляем юзеру по почте
        self.I.SMTP.sendMail( pwc.email, msg_title, msg_body, msg_plain_utf8 )


# ---------------------------

logging.basicConfig( level=logging.INFO, format='[%(asctime)s %(levelname)8s] %(message)s' )

email_unicode = _TOADDR
email_md5 = md5(email_unicode)

user = ClassDict( email=email_unicode, email_md5=email_md5, auid=AUID, confirm_token=randomMD5() )
pwc = PWCEmulation()
pwc.sendConfirmEmail( user, message_type="confirm" )

