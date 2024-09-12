# -*- coding: utf-8 -*-

NICK_EMPTY = "-" # вместо пустого ника (который не примет соц.аггрегатор) будем использовать минус

AGG_SOCIAL_NETWORK_NAMES = ['fb', 'ok', 'vk', 'st', 'ae', 'mru', 'msv', 'arc', 'zzma', 'gmg', 'dlt'] # l_who авторизует вот такой набор соц.сетей, плюс отдельно 'pwe' через pwconnect
LOGIN_SOCIAL_NETWORK_NAMES = AGG_SOCIAL_NETWORK_NAMES+['pwc'] # l_login, l_join понимают такой набор соц.сетей
BONUS_SOCIAL_NETWORK_NAMES = ['fb', 'ok', 'vk'] # бонусы за привязку соц.сетей проверяем по этому списку

REPEATING_TIMEOUT = 30
ADMINMESSAGE_TIMEOUT = 60

SN_BONUS_PROPERTY = "snbonus"

SOCAGG_LOGIN_CHECK_EX = "[^0-9A-Za-z_\.\=\-@]" # только символы, допустимые в именах
SOCAGG_TOKEN_CHECK_EX = "[^0-9A-Za-z_|.\-]"

MONGO_READ_RETRY_COUNT = 3

PWCONNECT_LAUNCHER_SNID = 'pwe'
PWCONNECT_AGGREGATOR_SNID = 'pwc'
SIGNATURE_CHECKED = '#&' # передать такую штуку по HTTP нельзя, только как параметр во внутренних субкомандах

MD5_LENGTH = 32
MD5_MASK = "[^A-Fa-f0-9]"

# Login Types
LT_LOGIN = 0
LT_RELOGIN = 1
LT_FRACTION_CHANGE = 2

EXCHANGE_PROJECTS = ['pw', 'pwg', 'em', 'al', 'td']

SEX_PW_PROJECT = 'pw'
SEX_PW_GUILD_PROJECT = 'pwg'
SEX_BALANCER_NAME = 'se'

SEX_KEEPALIVE_CHECK_PERIOD = 60 # раз в минуту пробегаемся по юзерам
SEX_KEEPALIVE_PERIOD = 60*30 # раз в полчаса для каждого юзера шлем I.SEX.touch или retry login

#~ ##### DEBUG
#~ SEX_KEEPALIVE_CHECK_PERIOD = 5 # DEBUG: каждые 5 секунд пробегаемся по юзерам
#~ SEX_KEEPALIVE_PERIOD = 10 # DEBUG: каждые 10 секунд для каждого юзера шлем I.SEX.touch или retry login
#~ ##### DEBUG

TEXT_NOT_A_REGISTERED_AP_USER = "Sorry, you cannot login at the moment. Probable reasons:\n1. The server is currently offline. Learn about the schedule and follow the news at www.playpw.com.\n2. You don't have access to Prime World Beta. Please enter your Beta Key or apply for Beta via 'My Account' page at www.playpw.com."
TEXT_NOT_A_ALLOWED_AP_USER = "Sorry but service is unavailable for your region."

SERVICE_ALIVE_SET_PERIOD = 5
SERVICE_ALIVE_TTL = 10
OTHER_MUID = '<other>'

NPC_VASSAL_AUID = -1
NPC_SUZERAIN_AUID = -1
GUILD_NEUTRAL_AUID = -1  # дефолтный ауид для работы над гильдией со стороны сервера или ГМтулзы

PLAYER_GUILD_REQUESTS_DATA = "pgreq"  # mongo collection name for player's guild membership applications
DYNAMIC_QUESTS_DATA = "quests"  # mongo collection for dynamic quests (actual and old ones)
RECENT_ALLIES_DATA = "recent_allies"  # mongo collection for recent allies list
EVENTS_DATA = "events"                # mongo collection for operator actions and events
GUILDWAR_EVENTS_DATA = "gw_events"    # mongo collection for store data of periodical clanwars' events
HELPER_VARIABLES_DATA = "vars"
PUNISHED_BY_CLAIM = "punished"        # mongo collection for counter of players, that were banned by claims from current player
BANNED_BY_BRUTEFORCE = "broodforce_accounts"        # mongo collection for counter of players, that were banned by claims from current player
BANNED_BY_IP = "bruteforce_ip"        # mongo collection for ip which was banned by resoan for bruteforce
IP_WHITE_LIST = "ip_white_list"       # mongo collection for ip_white_list


DEFAULT_DEFENCE_POINTS_PRSENT = 0.05 # Guild Wars: default for start point for defending guild (as a part of it's current rating)

GULD_RATINGS_UPDATE_CHECK_PERIOD = 30 # period for checking updates for siegedata in guild_service
GULD_RATINGS_CHECK_USERS_COUNT = 100  # amount of guilds for checking per one tick

max_talent_refine_rate = 10000  # max refine rate to gm tool

REROLL_DAILY_WEIGHTS = "default_weights"  # Текущие веса, храним, чтобы знать, если их изменят ГМы
REROLL_DAILY_PROBABILITIES = "daily_probabilities"  # Вероятности для чистого реролла (1 раз в день, честного)
REROLL_ADDITIONAL_PROBABILITIES = "additional_percents" # Вероятности, перешедшие с прошлого раза (для дробных процентов)
