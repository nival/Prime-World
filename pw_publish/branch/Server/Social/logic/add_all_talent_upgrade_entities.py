# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddAllTalentUpgradeEntitiesRequest import *

class Add_all_talent_upgrade_entities( SubAction, AddAllTalentUpgradeEntitiesRequest ):
    """action, ������� ����� ������������ ������ �����"""
    action = "add_all_talent_upgrade_entities"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """��������� ����� ��� ��������� action"""
        self.log()
        if not self.checkParams():
          return

        #ACTION LOGIC

        entities = []
        for entPersistentId in self.acc.SD.data['TalentUpgradeEntities']:
            staticEnt = self.acc.SD.getStaticTalentUpgradeEntityById(entPersistentId)
            if staticEnt and entPersistentId != 0:
                entities.append(entPersistentId)

        #entities.sort()

        for i in xrange(0, len(entities)):
            self.acc.model.addTalentUpgradeEntity(entities[i])

        self.response["ok"] = 1
        self.fin()