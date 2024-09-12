<?php
$root = dirname(__FILE__);
$root .= '/../../../';

$config = array (
    'path'  => array (
        'root'        => $root,
        'application' => $root . 'application/', //application path
        'library'     => $root . 'library/', // library path
        'modules'     => $root . 'application/frontend/modules/', //modules path
        'models'      => array(
            $root . 'application/frontend/modules/default/models/', //path to models. if need more modules add models path here
            $root . 'application/frontend/modules/facebook/models/',
            $root . 'application/frontend/modules/vkontakte/models/',
            $root . 'application/frontend/modules/odnoklassniki/models/',
            $root . 'application/frontend/modules/pwconnect/models/',
            $root . 'application/frontend/modules/steam/models/',
            $root . 'application/frontend/modules/aeria/models/',
            $root . 'application/frontend/modules/mail.ru/models/',
            $root . 'application/frontend/modules/massive/models/',
            $root . 'application/frontend/modules/arcgames/models/',
            $root . 'application/frontend/modules/zzima/models/',
            $root . 'application/frontend/modules/gamigo/models/',
            $root . 'application/frontend/modules/draugas/models/',
        ),
        'system'      => $root . 'application/frontend/system/', //system files(routes etc) path
        'settings'    => $root . 'application/frontend/settings/', //settings(this file and oher conf files if needed) path
        'logs' => $root . 'application/log/', //path to store log files. Example /var/logs/sa/ or using $root $root . 'application/log/'
    ),
    'common' => array (
        'charset' => 'utf-8',//module charset
     ),
    'debug' => true, //Verbose mode for developers
    'log_level' => 'info', //info,error,critical,off
    'version' => '0.3.93',//aplication version
    'user_info_refresh_period' => 10800, //3 hours

    'http_timeout' => 300,
    'http_connect_timeout' => 30,

    'pwc_url' => 'http://192.168.17.89:88/',
    'steam_url' => 'http://SITE.com/',
    'steam_app_id' => '123',
    'steam_key' => '123',

    'db' => array(
        'host' => '127.0.0.1', // MongoDB connect host
        'port' => '27017',// MongoDB connection port
        'name' => 'sa', // MongoDB name
        'options' => array(
            'connect' => true, //If true the constructor should connect before returning.
            //'username' => '*******', // MongoDB connection username
            //'password' => '*******', // MongoDB connection password
            //'persist' => 'foo', //If the connection should be persistent. If set, the connection will be persistent.
            //'timeout' => 300, // For how long the driver should try to connect to the database (in milliseconds).
            //'replicaSet' => true //If this hosts listed are seeds of a replica set.
        ),
     ),
    'facebook_permitions' => array('email'),
    'facebook_use_tls' => true,

    'vkontakte_permitions' => array('wall' => 8192,'offline' => 65536,'friends' => 2),

    'odnoklassniki' => array(
        'applicationId' => 123, # 123,
        'publicKey' => '123', # '123',
        'secretKey' => '123', # '123',
        'permitions' => array('VALUABLE ACCESS'),
    ),

    'aeria_base_url' => 'https://api.test.aeriagames.com/',
    'aeria_url' => 'https://api.test.aeriagames.com/services/v2/',
    'aeria_id' => '123',
    'aeria_secret' => '123',
    'aeria_paging_step' => 200, # the maximum value, according to the Aeria's manual
    'aeria_test_mode' => 1, # need for some special http header options

    'massive_base_url' => 'http://api.massive.ph/primeworld/user_verification.php',
    'massive_test_mode' => 1,

    'mru_url' => 'http://www.appsmail.ru/platform/api',
    'mru_app_id' => '123',
    'mru_secret_key' => '123',

    'arcgames_base_url' => 'http://pear-test.arcgames.com/',
    //'arcgames_base_url' => 'http://pear.arcgames.com/',
    'arcgames_server_ip' => '86.57.144.74',
    'arcgames_secret' => '123',
    'arcgames_random_chars' => '123',
    'arcgames_game' => 'pwo',
    'arcgames_test_mode' => true,

    'zzima_base_url' => 'http://SITE.com',
    'zzima_api_url' => 'http://SITE.com',
    'zzima_api_info_url' => 'http://SITE.com/version/2/info',
    'zzima_zul_login_url' => 'http://SITE.com/version/2/secure-token-info',
    'zzima_test_mode' => true,
    'zzima_client_secret' => '123',

    'gamigo_url' => 'http://SITE.com',

    'draugas_clientId' => '123',
    'draugas_client_secret' => '123',
    'draugas_base_url'=> 'http://mano.draugas.lt',
    'draugas_api_url' => 'http://mano.draugas.lt/api',

    'gearman' => array(
        'servers' => '127.0.0.1:4730', //comma separated  gearman servers example 127.0.0.1:4730,127.0.0.2:4730
        // If you run different SA versions on the same host, they MUST use different gearmans (on different ports or hosts)
    ),

    'billing' => array(
        'url' => 'http://SITE.com:8080/API/PL/ZZServiceWeb.asmx?WSDL',
        'fromServiceName' => 'pw',
        'email_pattern' => 'SITE@domain.com',
        'userName_prefix' => '',
        'reuse_account' => 1, // set it to 1 for testing deployments if using a single billing for multiple SAs
                              // always keep it 0 on a live deployment
    ),
    'test_billing' => array(
        'url' => 'http://SITE:8080/API/PL/ZZServiceWeb.asmx?WSDL',
        'fromServiceName' => 'pw',
        'email_pattern' => 'auid@playpw.com',
        'userName_prefix' => 'test',
        'reuse_account' => 1,
    ),
);
/* поменялось апи
 *   https://developers.facebook.com/docs/apps/changelog/?locale=ru_RU
 * где тестить
 *    https://developers.facebook.com/tools/explorer/123/?method=GET&path=me%2Fpermissions&version=v2.2&
 */
// define('FB_API_VERSION', 'v2.2/'); // нужно перейти
define('FB_API_VERSION', 'v2.8'); // текущая
?>
