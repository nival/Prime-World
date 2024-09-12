import hashlib
import CC
import EC
from base.helpers import info
from subaction import SubAction, action_timing
from ext_pw.sexchange import FindNickSnidAction


class FindNicknameBySnuidAction(SubAction):
    action = "find_nickname_by_login"

    def onStart(self):
        info("FindNicknameBySnuidAction.onStart : %r" % self.arguments)

        self.snuid = self.arguments.get('snuid')
        if not self.snuid:
            self.errorResponse(EC.BAD_PARAM, "not snuid defined")
            return

        # TODO: Find login id
        self.fin()


class FindPlayerByNicknameAction(SubAction):
    action = "player_find_by_nick"

    @action_timing
    def onStart(self):
        info('FindPlayerByNicknameAction.onStart : %r' % self.arguments)

        nickname = self.arguments.get('nickname')
        if not nickname:
            self.errorResponse(EC.NICK_BAD_PARAMS, "empty nickname")
            return
        self.response['nickname'] = nickname

        action = FindNickSnidAction(nick=nickname, I=self.I, fin_callback=self.onFindNickSnid)
        return action.onStart()

    def onFindNickSnid(self, response):
        info('FindPlayerByNicknameAction.onFindNickSnid : %r' % response)

        self.response['ok'] = 1
        if not response.get('ok'):
            self.response['found'] = False
            self.fin()
            return

        self.response['snid'] = response.get('snid', '')
        self.response['snuid'] = response.get('snuid', '')
        self.response['login'] = response.get('login', '')
        self.response['email'] = ''
        self.response['found'] = True
        if self.response['snid'] != 'pwc' or not self.response['snuid']:
            self.fin()
            return

        return self.I.SQL.pwcGetByPwcSnuid(self.response['snuid'], callback=self.onPwcGet)

    def onPwcGet(self, response):
        info('FindPlayerByNicknameAction.onPwcGet : %r' % response)

        if 'r' in response and len(response['r']) > 0:
            result = response['r'][0]
            self.response['email'] = result.email.encode('utf8')
        self.fin()

class FindPlayerByEmailAction(SubAction):
    action = "player_find_by_email"

    @action_timing
    def onStart(self):
        email = self.arguments.get('email', None)
        if not email:
            self.errorResponse(EC.PWC_BAD_EMAIL, "empty email")
            return
        self.response['email'] = email
        email_md5 = hashlib.md5(email).hexdigest()
        return self.I.SQL.pwcGet(email_md5, callback=self.onPwcGet)

    def onPwcGet(self, response):
        self.response['ok'] = 1
        if 'r' not in response or len(response['r']) == 0:
            self.response['found'] = False
            self.fin()
            return
        result = response['r'][0]
        self.response['auid'] = result.auid
        self.response['snid'] = 'pwc'
        self.response['snuid'] = result.pwc_snuid
        self.response['login'] = '%s#%s' % (self.response['snid'], self.response['snuid'])
        self.response['nickname'] = ''
        # TODO: Search login_id by login in tbl_login tables
        # TODO: Search nick by login_id in tbl_nick tables
        self.response['found'] = True
        self.fin()

    def onFindLogin(self, response):
        pass

    def onFindNick(self, response):
        pass

class ChangePlayerCredentialsAction(SubAction):
    action = "player_change_credentials"
    RESULT_FAIL = 0
    RESULT_SUCCESS = 1
    RESULT_WRONG_EMAIL = 2
    RESULT_WRONG_NEW_EMAIL = 3
    RESULT_WRONG_NEW_PASS = 4

    @action_timing
    def onStart(self):
        info("ChangePlayerCredentialsAction.onStart : %r" % self.arguments)
        self.response['ok'] = 1

        old_email = self.arguments.get('email')
        if not old_email:
            self.response['action_result'] = self.RESULT_WRONG_EMAIL
            self.fin()
            return
        self.old_email = old_email

        new_email = self.arguments.get('newEmail')
        if not new_email or new_email == old_email:
            self.response['action_result'] = self.RESULT_WRONG_NEW_EMAIL
            self.fin()
            return
        self.new_email = new_email

        new_pass = self.arguments.get('newPass')
        if not new_pass:
            self.response['action_result'] = self.RESULT_WRONG_NEW_PASS
            self.fin()
            return
        self.new_pass = new_pass

        # Find snuid by email
        self.old_email_md5 = hashlib.md5(old_email).hexdigest()
        return self.I.SQL.pwcGet(self.old_email_md5, callback=self.onFindPwc)

    def onFindPwc(self, response):
        info("ChangePlayerCredentialsAction.onFindPwc : %r" % response)

        if 'r' not in response or len(response['r']) == 0:
            self.response['action_result'] = self.RESULT_WRONG_EMAIL
            self.fin()
            return
        self.pwc = response['r'][0]

        # Set new email by pwc_snuid
        self.response['snuid'] = self.pwc.pwc_snuid
        self.new_email_md5 = hashlib.md5(self.new_email).hexdigest()
        return self.I.SQL.pwcChangeEmail(self.pwc.pwc_snuid, self.new_email, self.old_email_md5, self.new_email_md5, self.pwc, callback=self.onChangeEmail)

    def onChangeEmail(self, response):
        info("ChangePlayerCredentialsAction.onChangeEmail : %r" % response)

        self.response['snid'] = 'pwc'
        self.response['login'] = '%s#%s' % (self.response['snid'], self.response['snuid'])
        self.response['email'] = self.new_email
        self.response['action_result'] = self.RESULT_SUCCESS
        self.fin()
        # TODO: Find nick by email

class WipePlayerProgressionAction(SubAction):
    action = "player_wipe_progression"
    RESULT_FAIL = 0
    RESULT_SUCCESS = 1
    RESULT_WRONG_PAIR = 2

    @action_timing
    def onStart(self):
        self.fin()
