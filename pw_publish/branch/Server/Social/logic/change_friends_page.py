# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ChangeFriendsPageRequest import *
from friendsdata.FriendsData import *
class Change_friends_page( SubAction, ChangeFriendsPageRequest ):
    """action, ������� ����� ������������ ������ �����"""
    action = "change_friends_page"
  
    @model_callback
    @parse
    def onStart(self):
        """��������� ����� ��� ��������� action"""
        self.log()
        if not self.checkParams():
          return

        #ACTION LOGIC
        if not self.checkValidBoolParam("nextOrPrev"):
            return

        PAGE_SIZE = self.acc.getConfigValue("FRIENDS_PAGE_SIZE")
        debug("Change_friends_page.onStart acc.friendsdata = %r", self.acc.friendsdata.generateJsonDict())
        sorted_keys = sorted(self.acc.friendsdata.myFriends.keys()) or []
        debug("Change_friends_page.onStart sorted_keys = %r", sorted_keys)
        debug("Change_friends_page.onStart nextOrPrev =%r self.acc.model.PagesInfo.CurrBeginOfFriendsPage = %r",self.arguments.nextOrPrev, self.acc.model.PagesInfo.CurrBeginOfFriendsPage)
        good_keys = []
        if self.arguments.nextOrPrev:
            debug("Change_friends_page.onStart first = %r end = %r", self.acc.model.PagesInfo.CurrBeginOfFriendsPage + PAGE_SIZE, self.acc.model.PagesInfo.CurrBeginOfFriendsPage + 2 * PAGE_SIZE)
            good_keys = sorted_keys[self.acc.model.PagesInfo.CurrBeginOfFriendsPage + PAGE_SIZE : self.acc.model.PagesInfo.CurrBeginOfFriendsPage + 2 * PAGE_SIZE]
            self.acc.model.PagesInfo.CurrBeginOfFriendsPage = self.acc.model.PagesInfo.CurrBeginOfFriendsPage + PAGE_SIZE
        else:
            diff = self.acc.model.PagesInfo.CurrBeginOfFriendsPage - PAGE_SIZE
            debug("Change_friends_page.onStart first = %r end = %r",  diff if diff >= 0 else 0, self.acc.model.PagesInfo.CurrBeginOfFriendsPage)
            good_keys = sorted_keys[ diff if diff >= 0 else 0 : self.acc.model.PagesInfo.CurrBeginOfFriendsPage]
            self.acc.model.PagesInfo.CurrBeginOfFriendsPage = diff if diff >= 0 else 0

        debug("Change_friends_page.onStart good_keys = %r", good_keys)
        friendsData = FriendsData()
        friendsData.init(None)
        for _fid in good_keys:
            fi, fid = friendsData.newFriend()
            fr = self.acc.friendsdata.getFriendByID(_fid)
            friendsData.fillFriend(fr, fi)
            friendsData.myFriends.add(fi)

        debug("Change_friends_page.onStart friendsData = %r", friendsData.generateJsonDict())
        changes = [MakeModelChangeString("init_friendsdata", "/", "init", friendsData.generateJsonDict())]
        self.response["callback"] = ["change_friends_page"]
        self.response["FriendsData"] = changes
        self.response["ok"] = 1
        self.fin()