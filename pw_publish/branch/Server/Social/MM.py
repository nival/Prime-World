# -*- coding: utf-8 -*-

#!/usr/bin/env python

from base.helpers import ClassDict

# --------------------------------------------
# статус игрока (нуб, обычный, гвардеец)
ELordStatus = ClassDict(
    NEWBIE = 0,
    NORMAL = 1,
    LEAVER = 2,
)

# --------------------------------------------
# номер команды (стороны, расы)
ETeam = ClassDict(
    NONE = -1,
    TEAM1 = 0,
    TEAM2 = 1
) 

# --------------------------------------------
# типы наград (из результатов игровой сессии)
EAwardType = ClassDict(
    NONE = 0,
    TALENT = 1,
    SILVER = 2,
    HERO = 3,
    HERO_RATING = 4,
    RELIABILITY = 5,
    EXPERIENCE = 6,
    RESOURCE1 = 7,
    RESOURCE2 = 8,
    HERO_ENERGY = 9,
    FAME = 10,
    RESOURCE3 = 11,
    PEARL = 12,
    NEW_SEED = 13,
    LORD_RATING = 14,
    DODGE_POINTS = 15,
    GUARD_RATING = 16,
    GUILD_WAR_EVENT_POINTS = 17,
    GUILD_RESOURCE = 18,
    MARKETING_EVENT = 19,
    CWPOINTS_PLAYER = 20,
    CWPOINTS_CLAN = 21,
    RED_PEARL = 22,
    SHARD = 23,
    CUSTOM_CURRENCY = 24
)

ESex = ClassDict(
    NONE = 0,
    MALE = 1,
    FEMALE = 2,
    OTHER = 3,
    TUTORIAL = 4, # PF-95124, used in ModelDataCustom.addCustomHero call for temporary tutorial hero
)

## статусы друзей
FriendStatus = ClassDict(
    NONE = 0,         # НЕ ЗАДАН
    NOTINGAME = 1,    # НЕ В ИГРЕ
    INCASTLE = 2,     # В ЗАМКЕ
    INBATTLE = 3,     # В БИТВЕ
    INTRAINING = 4,   # В ТРЕНИРОВКЕ
    ONDRAGONRIDE = 5, # В ПОХОДЕ НА ГОРЫНЫЧА
    INMATCHMAKING = 6,# В ПОИСКЕ БОЯ
    AFK = 7,           # АФК =)
    LOADING = 13,     # Онлайн, но замок еще не загружен (после запуска клиента или после pvx сессии)
)

GameType2FriendStatus = {
    "pvp": FriendStatus.INBATTLE,
    "pvp1x1": FriendStatus.INBATTLE,
    "pvp2x2": FriendStatus.INBATTLE,
    "pvb": FriendStatus.INTRAINING, # этот формат подразумевает, что могут прийти игроки, а могут и не прийти (тогда против ботов); т.к. мы должны сказать сразу по mm_add, говорим "InTraining"
    "train": FriendStatus.INTRAINING,
    # "?? горыныч ??": FriendStatus.ONDRAGONRIDE,
}


## статусы матчмейкинг- (и pvx-) сессии
STATUS_NONE = 0
STATUS_NEW = 1
STATUS_GATEWAY_ADDED = 2
STATUS_LOBBY_ADDED = 3
STATUS_INLINE = 50
STATUS_WAITING_ACCEPT = 100
STATUS_ACCEPTED_SOCSERVER = 103 # фейковый статус, который ставит соц.сервер после получения accept от клиента (но до получения статуса 101 от gateway)
STATUS_ACCEPTED_PVX = 101
STATUS_WAITING_IN_LOBBY = 102
STATUS_IN_GAME = 104
STATUS_CLIENT_DROPPED = 107
STATUS_WAITING_FOR_PARTY = 108
STATUS_GAME_FINISHED = 106
STATUS_WAITING_GAME_FINISH = 109
STATUS_GUARDS_LOBBY = 110 # "гвардейский тамбур"
STATUS_ACCEPT_TIMED_OUT = 200
STATUS_INCOMPLETE_PARTY = 201
STATUS_PARTY_CAME_APART = 202
STATUS_NOT_IN_CASTLE = 203 # фейковый статус, который возвращает соц.сервер, если у кого-то из членов партии неживой клиент замка (не шлет keepalive)

## LEGACY значения, для mock matchmaker
MAX_PROGRESS = STATUS_WAITING_ACCEPT
PROGRESS_ACCEPTED = STATUS_ACCEPTED_PVX # значение >100% используем как признак "сессия уже accepted"

## специальное значение "для всех сессий данного юзера"
PING_ALL = "0"
CANCEL_ALL = "0"
    
## эти статусы соц.сервер ставит в свое собственное поле session["confirm"]
CONFIRM_NONE = 0
CONFIRM_NEW = 300
CONFIRM_ACCEPT = 301
CONFIRM_RECONNECT = 302
CONFIRM_LEAVE = 303
CONFIRM_RESULTS_APPLIED = 304
    
GAME_TYPES = ["pvp", "pvp1x1", "pvp2x2", "train", "pvb", "ctf"] # pvb = player vs bots, к которому однако могут присоединиться и другие игроки (если успеют); ctf=поход на Горыныча
FRACTION_TYPES = {"N":-1, "A":0, "B":1}
    
## Сколько секунд ждать между посылками fame на person server (PF-50061)
FAME_PERIOD = 666.6

## значения, которые на АП8+ нужно апдейтить из pvx кластера (спрашивать через gateway)
PVX_ACCEPT_TIMEOUT = 60.0
PVX_AVERAGE_MM_TIME = 0.0 # 5*60.0
## PVX_CAN_RECONNECT = 1 --> в cfg.py
PVX_RECONNECT_TIMEOUT = 15*60.0 # ReconnectToMatchTimeout 
PVX_NETWORK_DELAY = 5.0 # NetworkDelayTime 
PVX_GUARD_LOBBY_TIMEOUT = 60.0
AFTER_PVX_TIMEOUT = 10*60.0 # после pvx сессии разрешаем 10 минут любоваться на окно статистики прежде чем пнем с соц.сервера по таймауту

## (default) раз в столько секунд для каждой активной matchmaking-сессии генерируется ping (запрос статуса у PvX mm-сервера)
PING_PERIOD = 0.8 # seconds

## (default) раз в столько секунд пингуем статус идущей pvx-сессии (при типичной продолжительности игры полчаса как-то странно пинговать каждую секунду)
INGAME_PING_PERIOD = 10.0 # seconds

## (default) минимум столько секунд не запрашиваем пинги после mm_add (чтобы не получить преждевременный progress 0)
MIN_ADD_PERIOD = 2.0 # seconds

## (default) МАКСИМУМ столько секунд не запрашиваем пинги после mm_add; если получим ответ на mm_add ("add":<uid>:1), игнорируем этот таймаут
MAX_ADD_PERIOD = 8.0 # seconds 

## (default) если за столько секунд matchmaking-сессия не дождалась статуса is_valid:1 (т.е. нам ни разу не ответил про нее матчмейкер), она убивается
#VALID_TIMEOUT = 15.0 # seconds
VALID_TIMEOUT = 60*60.0 # 1 hour

## (default) раз в столько секунд запрашиваем server status (среднее время матчмейкинга и т.п.)
SERVER_STATUS_PERIOD = 10.0 # seconds

## (default) за столько секунд суммируем инфу о потерянных/доставленных пакетах, чтобы составить представление об общем уровне проблем (зеленый/красный/желтый)
MATCHMAKING_STATUS_SUMMARY_PERIOD = 30

## (default) столько результатов партий (0/1) храним в acc.db.win_lose_hist
MAX_WIN_LOSE_LENGTH = 10

## если за MATCHMAKING_STATUS_SUMMARY_PERIOD имеем <= столько прошедших пакетов, объявляем "красный" статус
SUMMARY_PASSED_THRESHOLD = 0

## если за MATCHMAKING_STATUS_SUMMARY_PERIOD имеем больше чем столько ошибок пакетов, объявляем "желтый" статус
SUMMARY_FAILED_THRESHOLD = 3 

## при рейтингах >= данного, флаг маневров для соло и партий включается принудительно, вне зависимости от галки в клиенте
MAX_NO_MANOEUVRE_RATING = 1800

## после N фейлов подряд на конкретном gateway_addr -- считаем этот гейт нерабочим, и впредь беспокоим его только запросами статуса 
## (остальной matchmaking трафик отправляем на рабочие гейты)
## MAX_INDIVIDUAL_GATEWAY_FAILS = 2 -- переезжает в конфиг coord_cfg

## если для всех локалей используются одинаковый набор pvx gateways, можно объявить этот набор для DEFAULT_LOCALE="ALL"
DEFAULT_LOCALE = "ALL"

## все подразделы session_roll должны иметь такой db_version (разделы с несоответствующими версиями удаляем при загрузке)
ROLL_DB_VERSION = 3

ESummaryState = ClassDict(
    GREEN = 0,
    YELLOW = 1,
    RED = 2,
)

# через сколько секунд повторять недоставленные пакеты, в зависимости от Summary MM State
PACKET_RETRY_TIMEOUTS = {
    ESummaryState.GREEN:    0.0,
    ESummaryState.YELLOW:   3.0,
    ESummaryState.RED:      15.0,
}

# --------------------------------------------
# DEBUG: тестовые наборы данных
TEST_SESSION_RESULTS = [
    {
            "victoriousFaction": ETeam.TEAM1,
            "playerIsLeaver":0,
            "session_roll":'{"pvp":{"version": 234,"default": {"items":[{"dbid": "Server/CTE.MODEROLL.xdb:60A740DC-FF57-4071-A3CC-F197B9EDF495","probability": 4300}],},"premium":{"items":[{"dbid": "Server/CTE.MODEROLL.xdb:60A740DC-FF57-4071-A3CC-F197B9EDF495","probability": 4300}]}},"gen_index":123}',
            "awards":[
                { "type": EAwardType.TALENT,        "id":-1828546151, "count":1, }, # id=TALENT_CRC32, -1828546151==crc32("G015")
                { "type": EAwardType.SILVER,        "id":1,         "count":22, },
                { "type": EAwardType.GUARD_RATING,  "id":1160508680,         "count":33, },
                { "type": EAwardType.LORD_RATING,   "id":1160508680,         "count":44, },
                { "type": EAwardType.RELIABILITY,   "id":1160508680,         "count":11, },
                { "type": EAwardType.EXPERIENCE,    "id":1160508680,         "count":6, }, # id==HERO_ID -- выдаем герою экспу
                { "type": EAwardType.HERO_ENERGY,   "id":1160508680,         "count":-40, }, 
                { "type": EAwardType.RESOURCE1,     "id":1,         "count":44, }, 
                { "type": EAwardType.RESOURCE2,     "id":1,         "count":55, }, 
                { "type": EAwardType.RESOURCE3,     "id":1,         "count":66, }, 
                { "type": EAwardType.PEARL,         "id":1,         "count":77, }, 
                { "type": EAwardType.NEW_SEED,      "id":1,         "count":88, }, 
            ]
    },
]


