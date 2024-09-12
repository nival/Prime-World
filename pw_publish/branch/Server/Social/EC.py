# -*- coding: utf-8 -*-

#!/usr/bin/env python

##---------------------------
## response["ec"] error codes

OK = 0

INTERNAL_SERVER_ERROR =  -4 # внутренняя ошибка сервера

# процесс десериализации аккаунта
ACCOUNT_LOCKED = 1
ACCOUNT_NOT_LOADED = 2
ACCOUNT_FAILED = 3
BAD_SESSION = 4
ACCOUNT_BANNED = 5
ALREADY_LOGGED_ON_DIFF_SERVER = 6  # юзер уже залоган на другом рабочем сервере
ALREADY_LOGGED = 7  # юзер уже залоган, на этом же рабочем сервере (возможно, застрял в pvx)
NOT_A_REGISTERED_AP_USER = 8  # юзер не добавлен в табличку разрешенных facebook id
AGGREGATOR_LOGIN_FAIL = 9


# set_nickname
NICKNAME_NOT_UNIQUE = 10  # запрос к sql прошел нормально, но установка ника в базе не прошла (видимо, дубликат)
NICKNAME_OPERATION_FAILED = 11  # фейл в общении с sql
NICK_BAD_PARAMS = 12  # фейл на этапе разбора и проверки параметров action=set_nickname

BAD_PARAM = 13

BAD_SIGNATURE = 14  # неправильная подпись запроса (logged action)
SUBLOGIN_FAIL = 15  # внутренняя ошибка на этапе SocAggLoginAction.subLgin

CLIENT_KICKED = 16

BAD_CLIENT_VERSION = 20  # не совпадают циферки hi.low
BAD_CLIENT_VERSION_FORMAT = 21  # вообще плохой формат

MM_CANCEL_INGAME = 30  # нельзя делать mm_cancel, пока статус "идет pvx сессия"
MM_NO_ACTIVE_SESSIONS = 31  # no active matchmaking sessions

CHAT_SERVICE_NOT_AVAILABLE = 32  # requested service is not available

BAD_ACTION_NAME = 33  # сервер не обрабатывает такой action
ACTION_HANDLER_EXCEPTION = 34  # ошибка при обработке action

AGGREGATOR_JOIN_USER_EXISTS = 35
AGGREGATOR_MERGE_FAIL = 36
AGGREGATOR_HTTP_ERROR = 37

HERO_IN_MATCHMAKING = 38  # невозможно выполнить действие - герой в матчмейкинге
NOT_ENOUGH_TALENTS = 39  # недостаточно талантов в талантсете для начала матчмейкинга

ACCOUNT_BANNED_FOREVER = 40  # пользователь забанен навсегда
ACCOUNT_AUTOBAN = 41  # пользователь забанен автобаном

TOO_MANY_COMPLAINTS = 42  # слишком много жалоб от этого игрока
BAD_POST_PARAM_IN_COMPLAINTS = 43  # не дошёл лог чата

NOT_ENOUGH_RESOURCES = 50  # недостаточно ресурсов
FRACTION_CHANGE_DISABLED = 51  # смена фракции заблокированна в конфиге
NOT_ENOUGH_GOLD = 52  # недостаточно золота
USER_INVENTORY_LIMIT = 53  # библиотека переполнена
FAVORITE_FRIENDS_LIMIT = 54  # любимые друзья переполнены
BILLING_FAILED = 55  # развалился биллинг
BILLING_ACCOUNT_PROBLEM = 56  # биллинг недоступен перманентно для этого аккаунта, служба поддержки спешит на помощь
BILLING_BUSY = 57  # запрос в биллинг уже ушел, но необработан, повторять тот же самый запрос не надо
DEBUG_REQUEST = 58  # попытка запустить дебаг реквест на не дебаг сервере
NOT_DEFINED_IN_SD = 59  # нет определения в static data

MM_BAD_MMID = 60  # "bad matchmaking session id"
MM_SESSION_NOT_VALID = 61  # "matchmaking session is not current (is_valid=0)"
MM_WRONG_SESSION_PROGRESS = 62  # "wrong matchmaking session progress, must be in [..progress state list..]"
CMD_NOT_SUPPORTED = 63  # command not supported (например, не включен реконнект в конфиге)
MM_USER_HAS_PARTY = 64  # нельзя стартовать соло матчмейкинг: у юзера есть партия
MM_USER_HAS_SESSSION = 65  # нельзя стартовать матчмейкинг: у юзера уже есть матчмейкинг-сессия

TOKEN_NOT_FOUND = 66  # token не найден
FRIEND_FROM_OPPOSITE_FRACTION = 67  # операция невозможна потому что в ней задействован друг из другой фракции
CAN_NOT_COLLECT_PRODUCTION = 68  # Невозможно собрать продукцию со здания

MM_MAP_HAS_CHANGED = 69  # сменилась карта матчмейкинга

PWC_BAD_USER = 70  # не зарегистрирован юзер (с таким email)
PWC_BAD_SIGNATURE = 71  # неправильная подпись запроса (т.е. скорее всего неправильный клиентский пароль использован для генерации подписи)
PWC_BAD_SQL_REGISTER = 72  # при регистрации нового PWConnect-юзера mysql ответил отказом (обычно по причине неуникального email)
PWC_BAD_SA_REGISTER = 73  # при регистрации нового PWConnect-юзера social aggregator ответил отказом
PWC_ACTIVATION_EXPIRED = 74  # истек срок активации аккаунта (через confirm code), больше не пускаем
PWC_BAD_EMAIL = 75  # doesnt look like email
PWC_CANT_DECODE_EMAIL = 76  # "can't decode email (bad encoding?)
PWC_BAD_EMAIL_LENGTH = 77  # ну укладывается в ограничения по длине email
PWC_BAD_CHALLENGE = 78  # wrong challenge (pwtoken)
PWC_BAD_PWD_DIGEST = 79  # что-то не так с длиной или символами pwd md5
PWC_BAD_SNUID_MASK = 80  # что-то не так с длиной или символами pwc email md5
PWC_BAD_CONFIRM_MASK = 81  # что-то не так с длиной или символами confirm token
PWC_RESEND_TOO_OFTEN = 82  # слишком часто запрашиваем операцию (не чаще раза в N секунд)
PWC_NO_PWC_TOKEN = 83  # нету pwc-токена для данного юзера (наверно, не выполнен l_who с pwc-реквизитами)

MERGE_BILLING_TRANSFER_BAD_RESPONSE = 84  # как минимум для одного из объединяемых аккаунтов не удалось достать billing balance
MERGE_BILLING_TRANSFER_FAILED = 85  # не удалось перевести золото при объединении аккаунтов
MERGE_PWC_UPDATE_FAILED = 86  # не удалось обновить статус pwc-аккаунта при мерже

USER_LIMIT_EXCEEDED = 88  # слишком много юзеров на сервере

PARTY_BAD_RATING_RANGE = 90

MM_WRONG_SESSION_PROGRESS_FOR_ACCEPT = 92  # пытаемся принимать сессию не в статусе 100 (WAITING_FOR_ACCEPT)

NON_FULL_AWARD_FOR_SOME_PARTY_MEMBERS = 93  # Кто-то в пати получит не полную награду

ONLY_MODERATOR_CAN_OPERATE = 94  # Данное действие доступно только модераторам

DEBUG_MESSAGE = 100 # ошибка которая не должна показываться пользователю - только записываться в лог в дебаг целях

# -- social exchange errors ----
XS_BAD_SQL_LOGIN = 110
XS_ALREADY_LOGGED = 111
XS_BAD_SQL_USER_ID = 112
XS_BAD_SQL_REPLY = 113
XS_BAD_PROJECT = 114
XS_BAD_AUID = 115
XS_BAD_SESSION_AUID = 116
XS_BAD_AUID = 117
XS_NO_SESSION = 118
XS_BAD_SESSION_ID = 119
XS_FAIL_LOGIN_ACC = 120
XS_GET_MESSAGES_ERROR = 121
XS_BAD_DEST_PROJECT = 122
XS_BAD_DEST_AUID = 123
XS_NO_DEST_LOGIN = 124
XS_NO_DEST_PEER_SERVER = 125
XS_BAD_SEND_MESSAGE_BODY = 126
XS_NESTED_REDIRECT = 127
XS_NO_MESSAGES_TO_DELETE = 128
XS_NO_SUCH_MESSAGE = 129
XS_BAD_PURGE_MESSAGE_BODY = 130
XS_SQL_DELETE_FAIL = 131
XS_NO_MESSAGES = 132
XS_DEST_NOT_READY = 133

FIND_NICK_NO_UID = 140
FIND_NICK_NO_LOGIN = 141
FIND_NICK_NO_AUID = 142

GUARDS_ALREADY_READY = 150  # уже присылали isTamburReady
HERO_NOT_FOUND = 151  # нет такого героя в ModelData
HERO_BAD_CRC = 152  # не совпадает hero_crc (PersistentID) для указанного hero_id
READY_BAD_MATCHMAKING_STATE = 154  # mm_ready пришло не в состоянии гвардейского лобби (может, уже ушли в сессию по таймауту?)
NOT_ENOUGH_FORCE = 155  # не достаточно мощи для старта режима
HERO_STATS_ARE_ALREADY_RESET = 156  # нельзя сбросить стат-поинты героя: сбраывать уже нечего
HERO_ALREADY_OWNED = 157  # Герой уже куплен
SKIN_ALREADY_OWNED = 158  # Скин уже куплен
NO_HERO_FOR_SKIN = 159  # Нет подходящего героя

# chat_service
CHAT_NOT_CONNECTED = 161
CHAT_MISMATCHED_KEY = 162
CHAT_CONTEXT_NOT_FOUND = 163
CHAT_CONTEXT_NOT_SPECIFIED = 164
CHAT_TIMESTAMP_CHECK_FAILED = 165
CHAT_ADMIN_CONTEXT_NOT_FOUND = 166
CHAT_CONTEXT_CREATION_FAILED = 167
CHAT_EMPTY_MESSAGE = 168
CHAT_DEPRECATED_PROTOCOL = 169
CHAT_SEND_FAILED = 170

CANT_COLLECT_RESOURCES = 180

FRIEND_NOT_FOUND = 201  # Друг по нику не найден
ACTION_CANNOT_BE_USED = 202  # нельзя поучаствовать в акции
BAD_TOKEN = 203  # плохой token ( возможно не перегенерился при рестарте сервера )

RETIRED_LORD = 205  # у нас слишком много ливов и не можем ММкаться
FRIEND_SERVER_CRASHED = 206  # почему-то пришла пустая friendsdata от сервера

FRIENDS_BAD_PARTY_CMD = 210
FRIENDS_NO_ACC = 211
GENERIC_PARTY_ERROR = 212  # ставим, когда отвечаем через replyPartyError
GENERIC_INVITE_ERROR = 213  # ставим, когда отвечаем через replyInviteError

NOT_ALLOWED_SPECTATOR = 220  # нету флажка IsSpectator (ставится через GM Tools)
BAD_SPECTATOR_NICKNAME = 221  # плохая кодировка ника и т.п.
NO_GAME_TO_SPECTATE = 222  # Игрок, которого хотят спектейтить, сейчас не в бою
CANT_SPECTATE_SPECTATOR = 223  # Игрок, которого хотят наблюджать, итак спектатор

IN_GUILD = 301  # Уже в гильдии ( нельзя создать новую )
NOT_IN_GUILD = 302  # Не в гилдьдии ( нельзя уйти, пригласить и тд )
BAD_GUILD_SHORT_NAME = 303
BAD_GUILD_FULL_NAME = 304
GUILD_FULLNAME_NOT_UNIQUE = 305
GUILD_SHORTNAME_NOT_UNIQUE = 306
FRIEND_IS_IN_YOUR_GUILD = 307
DOUBLE_CREATE_GUILD = 308
GUILD_OVERCROWDED = 309
GUILD_BANK_CANNOT_ADD_TALENT = 310  # Не получилось добавить талант от игрока в гильдию
GUILD_BANK_OVERCROWDED = 311  # Банк гильдии переполнен
GUILD_BANK_DAY_PUT_LIMIT_EXCEEDED = 312  # Исчерпан лимит талантов, которых можно положить в банк
GUILD_BANK_DAY_TAKE_LIMIT_EXCEEDED = 313  # Исчерпан лимит талантов, которе можно взять из банка
GUILD_BANK_TALENT_IS_MISSING = 314  # Талант, который пытаются забрать, отсутствует в банке
GUILD_BANK_CANNOT_TAKE_USER_INVENTORY_LIMIT = 315  # Нельзя забрать талант, потому что бибилиотека уже переполнена
GUILD_BANK_GUILD_TALENTS_LIMIT_IN_TS_EXCEEDED = 316  # Исчерпан лимит гильдийских талантов в TalentSet
GUILD_BANK_TALENT_IMPROPER_USE = 317  # Попытка продать гильдийский талант или заточить им другой талант
GUILD_BANK_CANNOT_GIVE_BACK_TALENT = 318  # Нельзя вернуть талант, если ты не офицер или не главой клана
GUILD_BANK_TALENT_REMOVED_FROM_TALENTSET = 319  # Из героя изъяли гильдийский талант, пока тот стоял в поиске ММ
GUILD_SHOP_ITEM_DAY_LIMIT_EXCEEDED = 320  # Товар в магазине на сегодня закончился
GUILD_SHOP_CANNOT_BUY_GUILD_POINTS_ONLY_ITEM = 321  # Нельзя купить клановый товар, если ты не глава и не советник
GUILD_SHOP_CANNOT_BUY_HIGH_LEVEL_ITEMS = 322 # Нельзя купить това, пока не достиг нужного уроня магазина
GUILD_SUZERAININVITES_IS_ALWAYS_ADDED = 323 # прошение на сюзеренство мы уже отправили, и его срок не истек
GUILD_CANNOT_NOTIFY = 325  # не могу уведомить вассала или сюзерена о изменениях произошешдших с ними
GUILD_MAX_VASSAL_SIZE = 326  # максимальное количество вассалов у клана
GUILD_HAVE_ACTIVE_SIEGE = 327  # у вас есть уже активные осады
GUILD_YOU_MUST_START_SIEGE = 328  # для захвата вассала необходимо осадить замок его сюзерена
GUILD_YOU_MUST_JOIN_SIEGE = 329  # для захвата вассала необходимо присоеденитсся к осаде его сюзерена

GUILD_ONLY_OFFICER_CAN_OPERATE = 330  # Только глава или советник имеют полномочия на это действие
SIEGE_NO_DATA_IN_DATABASE = 331  # Проблема в подключении к базе данных
GUILD_IS_LOCKED_BY_GM = 332  # ГМ что-то делает с кланом
GUILD_CANT_SIEGE_RECENTLY_LOST_GUILD = 333  # Нельзя сразу же захватывать клан, осада за который была недавно проиграна
GUILD_CANT_SIEGE_EX_VASSAL = 334  # Нельзя сразу же захватывать экс-вассала

RECRUIT_IN_GUILD = 335 # игрок уже в гильдии, нельзя подавать заяки на вступление и т.п.
RECRUIT_NO_RECRUIT = 336 # нет такой заявки, игрок уже в клане или не найден - ответы на операции клана с заявками игрока
RECRUIT_NO_GUILD = 337 # нет такого клана
RECRUIT_GUILD_OVERCROWDED = 338 # клан переполнен
RECRUIT_REQUESTS_LIMIT = 339 # превышен лимит заявок о игрока
RECRUIT_DECLINED = 340 # заявка в этот клан уже есть, была отклонена и ещё не протухла
RECRUIT_STILL_WAITING = 341 # заявка в этот клан уже подана и ждёт ответа

FLAG_NOT_FOUND = 350  # Такой флаг не найден в списке флагов стран или особенных флагов
FLAG_IS_ALREADY_OWNED = 351  # Пользователь уже купил такой флаг
FLAG_IS_NOT_OWNED = 352  # Нельзя выбрать такой флаг, поскольку он не куплен

REROLL_SHOP_ITEM_ALREADY_BOUGHT = 360  # Слот в магазине уже выкуплен
REROLL_SHOP_NO_PREMIUM = 361  # Попытка купить товар из премиум слота без премиума

OLD_USER = 362  # игрок был выброшен, при логине с другого компьютера

NOT_A_ALLOWED_AP_USER = 400  # пользователю запрещен вход по location/ip
STEAM_BILLING_ERROR = 401
STEAM_BILLING_PROCESSING_ERROR = 402
STEAM_TRANSACTION_NOT_FOUND = 403
STEAM_LOCAL_REDIS_FAILURE = 404
STEAM_LOCAL_MONGO_FAILURE = STEAM_LOCAL_REDIS_FAILURE
STEAM_OPERATION_FAILURE = 405

STEAM_DLC_IS_ALREADY_APPLIED = 406
STEAM_DLC_APPLY_ERROR = 407
STEAM_DLC_IS_NOT_EXIST = 408

PAYMENT_SYSTEM_FAILURE = 409

AERIA_OPERATION_FAILURE = 410
AERIA_LOCAL_SA_FAILURE = 411
AERIA_NOT_ENOUGH_AP = 412
AERIA_BILLING_ERROR = 413
AERIA_TOKEN_EXPIRED = 414
AERIA_PURCHASE_TIMED_OUT = 415

###ARCGAMES ERRORS
ARCGAMES_OPERATION_FAILURE = 416
ARCGAMES_LOCAL_SA_FAILURE = 417
ARCGAMES_PURCHASE_TIMED_OUT = 418
ARCGAMES_INTERNAL_ERROR = 419
ARCGAMES_NOT_ENOUGH_ZEN = 420

###ZZIMA ERRORS
ZZIMA_OPERATION_FAILURE = 421
ZZIMA_LOCAL_SA_FAILURE = 422
ZZIMA_PURCHASE_TIMED_OUT = 423
ZZIMA_INTERNAL_ERROR = 424
ZZIMA_NOT_ENOUGH_ZZGOLD = 425


REFORGE_WRONG_TALENT_RARITY = 450  # На реролл прислали талант с неправильным раром
REFORGE_WRONG_TRANSMUTATION_LEVEL_FOR_REROLL = 451  # Уровень кузницы слишком мал для реролла
REFORGE_UPGRADE_WRONG_TALENT_RARITY = 452  # Уровень кузницы слишком мал для улучшения

QLOGIN_CONTEXT_EXPIRED = 500
QLOGIN_CONTEXT_ALREADY_PENDING = 501
AUTH_REGISTER_LOGIN_FAILED = 502
QLOGIN_CONTEXT_IS_NOT_PRIMARY = 503

MAINTENANCE_STAGE_PENDING = 600
MAINTENANCE_STAGE_ONGOING = 601

TOURNAMENT_TICKET_NOT_BUY = 700  # Если пытаемся залогиниться при не купленом билете на турнирный сервер
CANT_SELL_TALENTS_IN_TOURNAMENT = 701  # Если пытаемся залогиниться при не купленом билете на турнирный сервер
TOURNAMENT_IS_OVER = 702  # Проиграл, не можешь зайти на турнирный сервер
TOURNAMENT_SPECTATOR_CANNOT_BUY_TICKET = 703  # Спектатор не может покупать билет на турнир
TOURNAMENT_SPECTATOR_CANNOT_INVITE = 704  # Спектатор не может приглашать в группу и быть приглашенным
TOURNAMENT_CANNOT_PLAY_SECOND_GAME = 705  # Нельзя играть больше одной игры в день
TOURNAMENT_CANNOT_MM_GAME_LOST_OR_SPECTATOR = 706  # Не могу вставать в ММ, тк проиграл или спектатор
TOURNAMENT_NOT_STARTED = 707  # Турнир еще не вступил в фазу боев
TOURNAMENT_BUY_FAIL = 708  # Не удалось купить билет ( проблема со свзью у нас )
CANNOT_USE_ACC_FOR_MM = 709  # Нельзя идти в обычный ММ турнирным аккаунтом

DYNAMIC_QUSET_LIFETIME_IS_OVER = 800  # Пытаемся завершить квест, который уже закончился
QUEST_IS_NOT_READY_YET = 801  # Квест ещё не закончен, нельзя завершить
DYNAMIC_QUEST_AWARD_ALREADY_OWNED = 802  # У пользователя уже есть такая награда

ALREADY_SIEGE_PARTICIPANT = 900  # Клан уже участвует в осаде данной цели
NO_SIEGE_FOR_TARGET       = 901  # Осада с данным таргетом не найдена на сидж-сервисе
# 902 - not used
PARTICIPANT_NOT_FOUND     = 903  # No such participant in this siege
SIEGE_FINISHED            = 904  # The siege is finished already (may be responded during a gap)
CANT_START_SIEGE_FOR_VASSAL_OR_SELF = 905  # Нельзя начинать осаду на своего вассала или на себя
SIEGE_TIMEOUT_FOR_LOST_VASSAL = 906  # Нельзя отбирать захваченного вассала, пока не прошёл таймаут
SIEGE_TIMEOUT_FOR_LOSS = 907  # Нельзя ещё раз сражаться за гильдий, пока не прошёл тайм аут

SIEGE_BACK_FORBIDDEN = 908  # Клану А нельзя осаждать Б, если Б уже осаждает клан А.

RESET_ACCOUNT_ERROR = 909 # Игрок недавно уже сбрасывал аккаунт

PWC_ACCOUNT_BAN = 910 # Аккаунт забанен так как была зафиксирована попытка брутфорсинга аккаунта

