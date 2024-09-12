using SS;
using System.Collections.Generic;

class dummy0
{
	public void load(cluster_cfg cfg)
	{
	    //----------------------------------------------------------------------------------------------------------------------
	    // общедоступный (внешний) адрес балансера, на который могут ломиться снаружи клиенты
	    cfg.COORDINATOR_BALANCER_EXTERNAL = "127.0.0.1:88";
	    //----------------------------------------------------------------------------------------------------------------------
	    // общедоступный (внешний) адрес балансера, на который по SSL могут ломиться клиенты, с запросами к PW Connect
	    cfg.COORDINATOR_BALANCER_PWCONNECT = "127.0.0.1:888";
	    //----------------------------------------------------------------------------------------------------------------------
	    // внутренний (закрытый) адрес балансера, на который можно ломиться только изнутри кластера (например, чтобы попасть со служебной командой на свой же чат-сервер)
	    cfg.COORDINATOR_BALANCER_INTERNAL = "127.0.0.1:8888";
	    //----------------------------------------------------------------------------------------------------------------------
	    // настройки "активных серверов" [name] -> server_id, port...
	    cfg.COORDINATOR_WS_SERVERS = new Dictionary<string, cluster_cfg.ws_server_cfg> { 
	        { "one", new cluster_cfg.ws_server_cfg { addr = "127.0.0.1:8801", ka = 0, max_users = 1500 } },
	        { "two", new cluster_cfg.ws_server_cfg { addr = "127.0.0.1:8802", ka = 0, max_users = 1500 } }
	    };
	    //----------------------------------------------------------------------------------------------------------------------
	    // настройки memcache-серверов
	    cfg.COORDINATOR_MC_SERVER_LIST = new List<string>();
	    //----------------------------------------------------------------------------------------------------------------------
	    // кластерные настройки sql-серверов
	    cfg.COORDINATOR_SQL_CONFIG = new List<cluster_cfg.sql_server_cfg>() {
	        // внимание! в развертываниях бранчей должна быть только одна база pw1
	        new cluster_cfg.sql_server_cfg { sql_host = "localhost:3306", sql_base = "pw1", sql_user = "pw", sql_pass = "123" },
	        new cluster_cfg.sql_server_cfg { sql_host = "localhost:3306", sql_base = "pw2", sql_user = "pw", sql_pass = "123" }
	    };
	    //----------------------------------------------------------------------------------------------------------------------
	    // кластерные настройки mongoDB-серверов
	    cfg.COORDINATOR_MONGO_CONFIG = new List<cluster_cfg.mongo_server_cfg>() {
	    // внимание! в развертываниях бранчей должна быть только одна база pw1
	        new cluster_cfg.mongo_server_cfg { mongo_addr = "localhost", mongo_port = 27017, mongo_base = "pw1", network_timeout = 10 },
	        new cluster_cfg.mongo_server_cfg { mongo_addr = "localhost", mongo_port = 27017, mongo_base = "pw2", network_timeout = 10 }
	    };
	    //----------------------------------------------------------------------------------------------------------------------
	    // количество рабочих ниток/коннектов
	    cfg.COORDINATOR_HTTP_CURL_WORKERS = 32;
	    cfg.COORDINATOR_HTTP_CURL_CONNECTIONS = 16;
	    cfg.COORDINATOR_ZZIMA_BILLING_THREADS = 2;
	    cfg.COORDINATOR_SQL_THREADS = 2;
	    cfg.COORDINATOR_MEMCACHE_THREADS = 2;
	    cfg.COORDINATOR_MONGO_THREADS = 2;
	    cfg.COORDINATOR_PWC_SMTP_THREADS = 8;
	    cfg.COORDINATOR_SERIAL_MODEL_DATA_THREADS = 2;
	    // ограничение по количеству одновременных http-запросов к одному адресу, по одному API (например, кол-во одновременно висящих обращений к одной WS по self.I.WSX)
	    cfg.COORDINATOR_HTTP_REQUEST_LIMIT = 12;
	    //----------------------------------------------------------------------------------------------------------------------
	    // data mirroring config
	    cfg.COORDINATOR_MIRROR_QUEUE_CONFIG = new cluster_cfg.sql_server_cfg { sql_host = "localhost:3306", sql_base = "pw_mirror", sql_user = "pwm", sql_pass = "123" };
	    cfg.COORDINATOR_MIRROR_QUEUE_THREADS = 2;
	    cfg.COORDINATOR_MIRROR_EXPORT_CONFIG = new cluster_cfg.sql_server_cfg { sql_host = "localhost:3306", sql_base = "pw_stat", sql_user = "pws", sql_pass = "123" };
	    cfg.COORDINATOR_MIRROR_EXPORT_THREADS = 2;
	    //----------------------------------------------------------------------------------------------------------------------
	    // IP:порты pvx кластера
	    // внешний порт, на который должен ломиться pvx клиент для старта сессии
	    cfg.COORDINATOR_PVX_LOGIN_ADDRESS = "SITE.com:35001" ;
	    // внутренние порты, на которых экземпляры pvx gateway слушают http (по умолчанию pvx запускает два gateway на двух последовательных портах)
	    // каждой локали соответствует список адресов pvx gateway, на которые должен более-менее равномерно разбрасываться matchmaking-трафик от юзеров с этой локалью
	    cfg.COORDINATOR_MATCHMAKER_LOCALES = new Dictionary<string,List<string>> {
	        { "ALL", new List<string> { "SITE.com:34000", "SITE.com:34001" } }
	    };
	    cfg.COORDINATOR_MATCHMAKER_DEFAULT_LOCALE = "RU";
	    //# Значение, которое подставляется при отправке в мачмейкинг филиппинским игрокам,
	    //# коих мы опознаём по snid = 'msv'.
	    //# Требуется для особой обработке их мачмейкером.
	    cfg.COORDINATOR_MATCHMAKER_MSV_LOCALE = "MASSIVE";
	    cfg.COORDINATOR_MATCHMAKER_MSV_GEOLOCATION = "MASSIVE";
	    //----------------------------------------------------------------------------------------------------------------------
	    // IP:порт и схема для обращения через soap-клиент к ZZima billing
	    //#~ # TEST
	    cfg.COORDINATOR_ZZIMA_WSDL = "http://SITE:8080/API/PL/ZZServiceWeb.asmx?WSDL";
	    cfg.COORDINATOR_ZZIMA_SERVICE_NAME = "pwdev";
	    cfg.COORDINATOR_ZZIMA_SERVICE_PASSWORD = "123";
	    cfg.COORDINATOR_ZZIMA_PAYMENT_SYSTEM = "BONUSES";
	    cfg.COORDINATOR_AGG_BILLING_PREFIX = "devqa_";
	    cfg.COORDINATOR_ZZIMA_STEAM_PAYMENT_SYSTEM = "STEAM";
	    cfg.COORDINATOR_BILLING_CHECK_BALANCE_PERIOD = 120;// # примерно раз в N секунд переcпрашиваем баланс юзера
	    //----------------------------------------------------------------------------------------------------------------------
	    // IP и ключи для обращения через HTTP POST к ZZimaAPI
	    //# БОЕВОЙ zzima api:
	    cfg.COORDINATOR_ZZIMA_API_URL = "http://SITE.com/zzimaApi";
	    cfg.COORDINATOR_ZZIMA_API_KEY = "123";
	    cfg.COORDINATOR_ZZIMA_API_SECRET = "123";
	    //----------------------------------------------------------------------------------------------------------------------
	    // адрес social aggregator (обычно узнаём у координатора)
	    //# COORDINATOR_SOCIAL_AGGREGATOR_ADDRESS = # AP9.1 аггрегатор с поддержкой PWC
	    cfg.COORDINATOR_SOCIAL_AGGREGATOR_ADDRESS = "SITE.com:88";
	    //----------------------------------------------------------------------------------------------------------------------
	    // адрес person server (обычно узнаём у координатора)
	    cfg.COORDINATOR_PERSON_SERVER_ADDRESS = "127.0.0.1:8713";// #! BAD ADDRESS, пусть все запросы к старому PS просто фейлятся
	    //----------------------------------------------------------------------------------------------------------------------
	    // адреса новых person-сервисов
	    cfg.COORDINATOR_FRIEND_SERVICES = new List<string>{ "127.0.0.1:8714", "127.0.0.1:8715" };
	    cfg.COORDINATOR_PARTY_SERVICES = new List<string>{ "127.0.0.1:8716", "127.0.0.1:8717" };
	    cfg.COORDINATOR_GUILD_SERVICES = new List<string>{ "127.0.0.1:8718", "127.0.0.1:8719" };
	    cfg.COORDINATOR_SIEGE_SERVICES = new List<string>{ "127.0.0.1:8741", "127.0.0.1:8742" };
	    //----------------------------------------------------------------------------------------------------------------------
	    // адреса распараллеленных chat-сервисов
		cfg.COORDINATOR_CHAT_SERVICES = new List<string>{ "127.0.0.1:8720" };//, "127.0.0.1:8721" };
	    //----------------------------------------------------------------------------------------------------------------------
	    // адреса events-сервисов (для начала используем для отправки high-severity логов по http)
	    cfg.COORDINATOR_EVENT_SERVICES = new List<string>{ "127.0.0.1:8722" };
	    //----------------------------------------------------------------------------------------------------------------------
	    // адрес сервиса, принимающего снаружи thrift-трафик (запросы от GM Tools и сайта)
	    cfg.COORDINATOR_THRIFT_AGENT_URL = "127.0.0.1:8706";
	    //----------------------------------------------------------------------------------------------------------------------
	    // адрес компоненты stats agent (посредник, пересылающий данные по thrift в сторону внешней статистики)
	    cfg.COORDINATOR_STATS_AGENT_URL = "127.0.0.1:8709";
	    //----------------------------------------------------------------------------------------------------------------------
	    // адрес внешнего сервера статистики (обычно узнаём у координатора) -- статистика логинов/логаутов и т.п.
	    cfg.COORDINATOR_STATS_URL = "http://127.0.0.1:35922";
	    //----------------------------------------------------------------------------------------------------------------------
	    // адрес сервера CleanSpeak (мат-фильтр)
	    cfg.COORDINATOR_CLEANSPEAK_FILTER_ADDRESS = "123.com:8001";// # pwn
	    //----------------------------------------------------------------------------------------------------------------------
	    // таймаут на http-запросы к серверу CleanSpeak (если его нет или он не отвечает, чат не должен ждать 20 сек таймаут)
	    cfg.COORDINATOR_CHAT_FILTER_TIMEOUT = 3.0;
	    //----------------------------------------------------------------------------------------------------------------------
	    // флаг, нужно ли ограничивать доступ facebook юзеров (через список fb_users и батник add_fb_users.bat)
	    cfg.COORDINATOR_RESTRICT_FACEBOOK_USERS = 0;
	    //----------------------------------------------------------------------------------------------------------------------
	    // флаг, нужно ли ограничивать доступ пользователей по location и ip
	    cfg.COORDINATOR_RESTRICT_LOCATIONS = 0;
	    //----------------------------------------------------------------------------------------------------------------------
	    // список разрешенных locations
	    cfg.COORDINATOR_RESTRICT_LOCATIONS_ALLOWED = new List<string> { "RU0" };
	    //----------------------------------------------------------------------------------------------------------------------
	    // можно ли реконнектиться в идущую pvx-сессию
	    cfg.COORDINATOR_PVX_CAN_RECONNECT = 1;
	    //----------------------------------------------------------------------------------------------------------------------
	    // проверять подписи всех logged-запросов, отказывать при несовпадении подписи
	    cfg.COORDINATOR_STRICT_SIGN_CHECK = 1;
	    //----------------------------------------------------------------------------------------------------------------------
	    // срок активации PWC-аккаунта, в секундах
	    cfg.COORDINATOR_PWC_ACTIVATION_TERM = 2 * (24 * 60 * 60); // двое суток
	    //----------------------------------------------------------------------------------------------------------------------
	    // не чаще чем раз в столько времени можно высылать новый код активации для PWC
	    cfg.COORDINATOR_PWC_RETRY_CONFIRM_PERIOD = 60 * 60; // час
	    //----------------------------------------------------------------------------------------------------------------------
	    // не чаще чем раз в столько времени можно ресетить PWC password
	    cfg.COORDINATOR_PWC_RESET_PWD_PERIOD = 60 * 60; // час
	    //----------------------------------------------------------------------------------------------------------------------
	    // по такому пути должны лежать картинки для писем
	    cfg.COORDINATOR_PWC_STATIC_IMAGE_PATH = "http://SITE.com/pw_connect_images";
	    //#COORDINATOR_PWC_STATIC_IMAGE_PATH = "file://localhost/C:/Work/_MAIL_TEMPLATE"
	    //----------------------------------------------------------------------------------------------------------------------
	    // по такому адресу должны обращаться линки из рассылаемых писем (адрес промежуточной веб-морды или адрес pw connect соц.сервера)
	    cfg.COORDINATOR_PWC_WEBFACE = "http://127.0.0.1:88/";
	    //----------------------------------------------------------------------------------------------------------------------
	    // на такие адреса делаем redirect при подтверждении PWC-аккаунта (ok/fail)
	    cfg.COORDINATOR_PWC_CONFIRM_OK = "http://playpw.com/pwcf/confirm_ok.html";
	    cfg.COORDINATOR_PWC_CONFIRM_FAIL = "http://playpw.com/pwcf/confirm_fail.html";
	    //# по такому адресу происходит смена пароля пользователя PWC (через ссылку в письме, функция "забыл пароль")
	    cfg.COORDINATOR_PWC_CHANGE_PWD = "http://127.0.0.1:88/pwcf/changepwd";
	    //----------------------------------------------------------------------------------------------------------------------
	    // посылать ли письмо
	    cfg.COORDINATOR_PWC_CONFIRM = true;
	    //----------------------------------------------------------------------------------------------------------------------
	    // сессии, по которым нет подтвержденных mm-пингов в течении стольки секунд, считаем !valid
	    cfg.COORDINATOR_MM_VALIDATION_SECONDS = 300;
	    //----------------------------------------------------------------------------------------------------------------------
	    // после N фейлов подряд на конкретном gateway_addr -- считаем этот гейт нерабочим, и впредь беспокоим его только запросами статуса
	    // (остальной matchmaking трафик отправляем на рабочие гейты)
	    cfg.COORDINATOR_MM_MAX_INDIVIDUAL_GATEWAY_FAILS = 1000000;
	    //----------------------------------------------------------------------------------------------------------------------
	    // адрес social exchange service (balancer)
	    cfg.COORDINATOR_SOCIAL_EXCHANGE_URL = "127.0.0.1:8888";
	    //----------------------------------------------------------------------------------------------------------------------
	    // периодичность garbage collection (в секундах) для WS и PS
	    cfg.COORDINATOR_DEFAULT_GC_PERIOD = 60.0;
	    //----------------------------------------------------------------------------------------------------------------------
	    // Паттерн имени иконки и URL WebDav сервера, который принимает иконки и делает их доступными через CDN.
	    cfg.GUILD_ICONS_UPLOAD_URL_PATTERN = "http://SITE.com/guild_logo/{guild_id}_{changes_count}.png";
	    //----------------------------------------------------------------------------------------------------------------------
	    // Список разрешенных ревизий клиента (если пустой, разрешаем любые ревизии)
	    cfg.COORDINATOR_CLIENT_REVISIONS = new List<string> {};
	    cfg.COORDINATOR_STEAM_APPID = "123";
	    cfg.COORDINATOR_STEAM_URL = "https://SITE.com/";
	    cfg.COORDINATOR_STEAM_SANDBOX_MODE = true;
	    cfg.COORDINATOR_STEAM_BILLING_BASE = 1;
	    cfg.COORDINATOR_STEAM_APPKEY = "123";
	    cfg.COORDINATOR_STEAM_BILLING_OFFSET = 0;
	    cfg.COORDINATOR_STEAM_PAYMENTS_URL = "http://localhost:8723";
	    cfg.COORDINATOR_STEAM_PAYMENTS_SECRET = "123";
	    cfg.COORDINATOR_AERIA_PAYMENTS_URL = "http://localhost:8723";
	    cfg.COORDINATOR_AERIA_PAYMENTS_SECRET = "123";
	    cfg.COORDINATOR_AERIA_IS_TEST = 1;// # 1 - access test AeriaGames site, 0 - access live AeriaGames site
	    if(cfg.COORDINATOR_AERIA_IS_TEST == 1)
	    {
	        cfg.COORDINATOR_AERIA_URL = "https://user:name@domain.com/";
	        cfg.COORDINATOR_AERIA_APPID = "123";
	        cfg.COORDINATOR_AERIA_KEY = "123";
	    }
	    else
	    {
	        cfg.COORDINATOR_AERIA_URL = "https://api.aeriagames.com/";
	        cfg.COORDINATOR_AERIA_APPID = "123";
	        cfg.COORDINATOR_AERIA_KEY = "123";
	    }
	    cfg.COORDINATOR_ZZIMA_AERIA_PAYMENT_SYSTEM = "AERIA";
	    cfg.COORDINATOR_SKIP_LIMIT_CHECK = true;
	    // -------------------------------ArcGames ---------------------------------------------------------------------------//
	    cfg.COORDINATOR_ARCGAMES_PAYMENTS_URL = "http://localhost:8723";
	    cfg.COORDINATOR_ARCGAMES_PAYMENTS_SECRET = "123";
	    cfg.COORDINATOR_ARCGAMES_IS_TEST = 1;
	    if(cfg.COORDINATOR_ARCGAMES_IS_TEST == 1)
	    {
	        cfg.COORDINATOR_ARCGAMES_URL = "http://pear-test.arcgames.com/";
	        cfg.COORDINATOR_ARCGAMES_APPABBR = "PWO";
	        cfg.COORDINATOR_ARCGAMES_APPID = 4600;
	        cfg.COORDINATOR_ARCGAMES_ZONEID = 4601;
	        cfg.COORDINATOR_ARCGAMES_APP_SECRET = "123";
	        cfg.COORDINATOR_ARCGAMES_BILLING_URL = "https://SITE.com/";
	    }
	    else
	    {
	        //#TODO: adding data for production application
	        cfg.COORDINATOR_ARCGAMES_URL = "http://pear.arcgames.com/";
	        cfg.COORDINATOR_ARCGAMES_APPABBR = "";
	        cfg.COORDINATOR_ARCGAMES_APPID = 0;
	        cfg.COORDINATOR_ARCGAMES_ZONEID =0;
	        cfg.COORDINATOR_ARCGAMES_APP_SECRET = "";
	        cfg.COORDINATOR_ARCGAMES_BILLING_URL = "https://kiwi.arcgames.com/";
	    }
	    cfg.COORDINATOR_ZZIMA_ARCGAMES_PAYMENT_SYSTEM = "ARCGAMES";
	    // -------------------------------End ArcGames -----------------------------------------------------------------------//
	    // -------------------------------zzima.com ---------------------------------------------------------------------------//
	    cfg.COORDINATOR_ZZIMACOM_PAYMENTS_URL = "http://localhost:8723";
	    cfg.COORDINATOR_ZZIMACOM_PAYMENTS_SECRET = "123";
	    cfg.COORDINATOR_ZZIMACOM_IS_TEST = 1;
	    if(cfg.COORDINATOR_ZZIMACOM_IS_TEST == 1)
	    {
	        cfg.COORDINATOR_ZZIMACOM_URL = "http://SITE.com:8082/API/PL/ZZServiceWeb.asmx?wsdl";
	        cfg.COORDINATOR_ZZIMACOM_SERVICE_NAME = "pw";
	        cfg.COORDINATOR_ZZIMACOM_PAYMENT_SYSTEM = "CBT";
	    }
	    else
	    {
	        cfg.COORDINATOR_ZZIMACOM_URL = "http:/SITE.com:8080/API/PL/ZZServiceWeb.asmx?wsdl";
	        cfg.COORDINATOR_ZZIMACOM_SERVICE_NAME = "pw";
	        cfg.COORDINATOR_ZZIMACOM_PAYMENT_SYSTEM = "CBT";
	    }
	    cfg.COORDINATOR_ZZIMA_ZZIMACOM_PAYMENT_SYSTEM = "ZZIMA";
	    // -------------------------------End zzima.com---------------------------------------------------------------------------//
	    //----------------------------------------------------------------------------------------------------------------------
	    // Список DLC
	    // 255250 - 255254 Steam
	    // aeria_initial_dlc - Gift for Aeria new users. id hardcoded
	    cfg.COORDINATOR_DLCS = @"{
	        '255250' : { 'Gold' : 100, 'Premium' : 14, 'Houses' : ['FirstBuy_Dog'] , 'Resources': {'Perl' : 50, 'Resource1': 5000, 'Resource2': 5000, 'Resource3': 5000, 'Silver' : 5000 } },
	        '255251' : { 'Gold' : 200, 'Premium' : 28, 'Houses' : ['FirstBuy_Dog'] , 'Resources': {'Perl' : 100, 'Resource1': 10000, 'Resource2': 10000, 'Resource3': 10000, 'Silver' : 10000 } },
	        '255252' : { 'Gold' : 400, 'Premium' : 42, 'Houses' : ['FirstBuy_Dog'] , 'Resources': {'Perl' : 150, 'Resource1': 15000, 'Resource2': 10000, 'Resource3': 15000, 'Silver' : 15000 } },
	        '255253' : {},
	        '255254' : { 'Heroes' : [ 'witch' ], 'Skins' : [ 'ghostlord_S2_A', 'ghostlord_S2_B' ] },
	        'aeria_initial_dlc' : { 'Resources': { 'Perl' : 5, 'Resource1': 5000, 'Resource2': 5000, 'Resource3': 5000, 'Silver' : 10000 } },
	        'tournament0_ticket_dlc' : { 'RandomTalents' : { 'Count' : 1, 'Rarity' : 4 } },
	        'dlc_for_test' : { 'Resources': { 'Silver' : 10000 } },
	        'dlc_for_test_multi' : { 'Resources': { 'Silver' : 10000 }, 'MultiApply' : 1 },
	        'ref_resources': { 'Resources': { 'Resource1': 5000, 'Resource2': 5000, 'Resource3': 5000, 'Silver': 5000 }, 'MultiApply' : 1 },
	        'ref_premium': { 'Premium' : 3, 'MultiApply' : 1 },
	        'ref_prince_unique_skin_a': { 'Skins': [ 'prince_S2_A' ], 'MultiApply' : 1 },
	        'ref_prince_unique_skin_b': { 'Skins': [ 'prince_S2_B' ], 'MultiApply' : 1 },
	        'ref_crystals': { 'Resources': { 'Perl' : 30 }, 'MultiApply' : 1 },
	        'ref_random_rar4_talent': { 'RandomTalents' : { 'Count' : 1, 'Rarity' : 4 }, 'MultiApply' : 1 },
	        'ref_random_rar5_talent': { 'RandomTalents' : { 'Count' : 1, 'Rarity' : 5 }, 'MultiApply' : 1 }
	    }";
	  
	    cfg.COORDINATOR_MUID_TO_DLCS = new Dictionary<string,List<string>> { 
	        { "cenega", new List<string> { "123" } },
	        { "testmuid", new List<string> { "123", "123", "123", "tournament0_ticket_dlc", "tournament0_ticket_dlc" } }
	    };
	    cfg.COORDINATOR_DEPLOY_NAME = "RU";
	    cfg.COORDINATOR_TOURNAMENT_SERVER = false;
	    cfg.COORDINATOR_TOURNAMENT_SERVER_ADDR = "http://192.168.1.181:88";
	    cfg.COORDINATOR_TOURNAMENT_XSERVER_ADDR = "http://192.168.1.181:8888";
	    cfg.COORDINATOR_TOURNAMENT_SPECTATOR_AUIDS = new List<long> { 122 };
	    cfg.COORDINATOR_TOURNAMENT_APPLY_RESULTS = true;
	    cfg.COORDINATOR_PWC_INFO_URL = "http://localhost:88";
	    cfg.COORDINATOR_BILLING_RESERVE_ENABLED = false;
	    cfg.COORDINATOR_GEO_DATA_PATH = "vendor/pygeoip/data/GeoIPCity.dat";
	    cfg.COORDINATOR_BILLING_MERGE_DISABLED_PS = new List<string> {};
	    cfg.COORDINATOR_REDIS_CONFIG = new cluster_cfg.redis_server_cfg { redis_addr = "localhost", redis_port = 8379, redis_base = 0 };
	    cfg.COORDINATOR_META_MUIDS = new List<string> { "mailru", "zzima", "aeria", "amazon", "cenega", "steam", "arc", "zzma" };
	    cfg.BROADCASTER_URL = "http://localhost:8699";
	}
}