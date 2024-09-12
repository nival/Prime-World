# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RecalcHeroForcesRequest import *



class Recalc_hero_forces( SubAction, RecalcHeroForcesRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "recalc_hero_forces"
  
    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
          return

        hero = self.arguments.hero

        if hero and hero.Hired:
            for tsIdx in xrange(len(hero.TalentSets)):
                hero.CalcForce(self.acc.model, self.I.WS, self.acc, tsIdx)

        self.response["ok"] = 1
        self.fin()

