# -*- coding: utf-8 -*-
from base.helpers import *

'''
скрипт для перевода ключей текущей прогрессии TradeEvent аккаунтов c PersistentId евента на TradeEventGuid евента 
(на момент выполнения скрипта TradeEventGuid захардкожена как "1") 
PF-107387
'''

class ModifyTradeEventProgression:
    def convertModelData( self, env, acc, md, dict ):
        info('ModifyTradeEventProgression script md TradeEvents before {}'.format([event_id for event_id in md.TradeEvents]))

        progressionPersistentId = next(iter([x.PersistentId for _, x in md.TradeEvents.iteritems()]), None)
        if not progressionPersistentId:
            return md, acc.db
        md.TradeEvents.move(progressionPersistentId, 1)
        md.TradeEvents[1].PersistentId = 1

        info('ModifyTradeEventProgression script md TradeEvents after {}'.format([event_id for event_id in md.TradeEvents]))
        return md, acc.db






