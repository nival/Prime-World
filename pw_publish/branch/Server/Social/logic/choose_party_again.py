# -*- coding: utf-8 -*-
from party_action import *
from logic.requests.ChoosePartyAgainRequest import *

class Choose_party_again(Party_action, ChoosePartyAgainRequest):
    """action, который будет обрабатывать данный класс"""
    action = "choose_party_again"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.is_leader = 0
        self.old_party = []
        self.session_id = self.getIntParam("session_id", 0)
        if not self.session_id:
            warn("ChoosePartyAgainAction session_id is empty!")

        self.post_data = json_loads(self.getParam('post_data', "{}"))
        self.lock_end_time = self.post_data.get("lock_end_time", 0) + int(time.time()) + self.acc.getConfig().AFTERPARTY_TIMEOUT
        self.agreed = self.post_data.get("agreed", 0)
        self.allies_keys = json_dumps(",".join(str(auid) for auid in self.post_data.get("allies_keys", "")))
        self.old_party_id = self.new_party_id = 0
        self.acc.model.game_type = self.acc.model.LordInfo.LastStartedMap.MapId
        if self.agreed:
            if not self.acc.party_id:
                info("ChoosePartyAgainAction (auid=%s): issuing temp party_id=%s", self.acc.auid, self.new_party_id)
                self.addArguments(is_temp_party_id=1)
            else:
                debug("ChoosePartyAgainAction PartyData for auid %d: %r", self.acc.auid, self.acc.partydata.generateJsonDict())
                if (self.acc.partydata.owner.get() and self.acc.partydata.owner.person.get()
                    and self.acc.partydata.owner.person.person_uid == self.acc.auid):
                    self.is_leader = 1
                    self.old_party_id = self.acc.party_id

                    for _id, member in self.acc.partydata.members.items():
                        self.old_party.append(member.person.person_uid)

        self.I.PS.getAfterpartyId(self.acc.auid, self.session_id, self.allies_keys, self.old_party_id, self.onPartyResponse)
        return

    def onPartyResponse(self, response):
        info("Choose_party_again.onPartyResponse response: %r", response)
        if response and response.get('ok'):
            # Если игрок соглашается, нужно сразу проставить ему новый party_id в acc
            self.new_party_id = response.get("party_id")
            if self.agreed:
                self.acc.party_id = self.new_party_id
            else:
                if self.acc.party_id:
                    self.old_party_id = self.acc.party_id
                    self.is_leader = 1
            leaver = True if LordStatus.Leaver == self.acc.model.getInternalUserStatus(self.acc.getConfig()) else False
            tournamentDynQuestId, dependedTournamentQuests = self.acc.model.getActualTournamentQuestPersistentId()


            self.addArguments(party_id=self.new_party_id,
                              session_id=self.session_id,
                              flagType=self.acc.model.FlagInfo.FlagType,
                              flagPersistentId=self.acc.model.FlagInfo.PersistentId,
                              isMMAllowed=self.acc.db.isRegularMMAllowed,
                              isInventoryFull=self.acc.model.isInventoryFull(),
                              lock_end_time=self.lock_end_time,
                              is_leader=self.is_leader,
                              agreed=self.agreed,
                              allies_keys=self.allies_keys,
                              game_type=self.acc.model.game_type,
                              old_party_id=self.old_party_id,
                              old_party=",".join(str(x)for x in self.old_party),
                              isLeaver=leaver,
                              tournamentDynQuestId = tournamentDynQuestId,
                              dependedTournamentQuests = dependedTournamentQuests
                              )
            # Ну принято же называть всё с party_ сначала! =(
            self.action = 'party_choose_again'
            return Party_action.onStart(self)
        else:
            self.errorResponse(EC.INTERNAL_SERVER_ERROR, "Bad response from party service")
            return
