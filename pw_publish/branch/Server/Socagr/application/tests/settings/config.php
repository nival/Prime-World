<?php
$root = dirname(__FILE__);
$root .= '/../../../';

$config = array (
    'path'  => array (
        'root'        => $root,
        'application' => $root . 'application/',
        'library'     => $root . 'library/',
        'modules'     => $root . 'application/tests/modules/',
        'models'      => array(
            $root . 'application/frontend/modules/default/models/',
            $root . 'application/tests/modules/default/models/',
            $root . 'application/tests/modules/facebook/models/',
            $root . 'application/frontend/modules/facebook/models/', 
            $root . 'application/frontend/modules/vkontakte/models/',
            $root . 'application/frontend/modules/odnoklassniki/models/',                       
        ),
        'settings'    => $root . 'application/tests/settings/',
		'system'      => $root . 'application/tests/system/',
        'logs' => $root . 'application/log/', //path to store log files. Example /var/logs/sa/ or using $root $root . 'application/log/'
     ),
    'common' => array (
        'charset' => 'utf-8',
     ),
    'debug' => true,
    'log_level' => 'off', //info,error,critical,off 
    'version' => '0.1.5',
    'db' => array(
    	'host' => '192.168.1.16', // MongoDB connect host
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
    'facebook' => array(
         'applicationId' => '208700029168914',
         'apiKey' => 'decf9bb5d0f9cc2949c9bb27fa92e89c',
         'applicationSecret' => 'ff84983cd9a6931195bce99c003ce5ff',
     	 'accessToken' => '208700029168914|jBqOaxeBLATdkhIaVrcK1jrMWfI',
     	 'permitions' => 'user_birthday,email,publish_stream,offline_access',
     	 'test_users_count' => 30, 		
     ),
     'vkontakte' => array(
     	'applicationId' => '2481574',
     	'applicationSecret' => '0RJ7Xz0YCFJDHbyZUAmy',
     	'accessToken' => 'f90d285ff90d285ff9cce07ec6f928f5f97f90df90d285fcad34f6a52d119a7',
     	'permitions' => array('wall' => 8192,'offline' => 65536,'friends' => 2),
     ),
     'vkontakte_test_users' => array(
     	'56894468' => '86a08a4e85c4ae4a85c4ae4ac885e173ec085c485c58e48fbd88c237b88f1e8', //snuid=>sntoken
     ),
     
     'odnoklassniki' => array(
    	'applicationId' => 4545792,
     	'publicKey' => 'CBAOFGEBABABABABA',
     	'secretKey' => '67FEB20DD44968E65016FDD6',
     	'permitions' => array('VALUABLE ACCESS'),
     ),
     
     'odnoklassniki_test_users' => array(
     	'334159022354' => '15536NeKr5a7bNZjP61_3OfGs_c05NbGr166zPcKP83f2Lfkt5346Sfjw5', //snuid=>snrefresh_token
     ),
     
     'load_test' => array(
     	'login' => 100,//max unlimited
     	'register' => 100,//max 450
     	'get_info' => 50,//max unlimited
     	'get_infos' => 50,//max unlimited
     	'add_friend' => 50,//max (register*register-1)/2 . Example register = 50. max for add_friend = 50*49/2=1225
        'delete_friend' => 50,//max (register*register-1)/2 . Example register = 50. max for delete_friend = 50*49/2=1225.
     	'get_edge_status' => 50,//max unlimited
     	'get_friends' => 50,//max unlimited
     	'get_friends_info_all' => 50,//max unlimited
     	'get_candidates_info_all' => 50,//max unlimited
     	'set_edge_property' => 100,//max unlimited
     	'get_edge_property' => 1000,//max unlimited
     	'find_user' => 10,//max unlimited
     	'get_users_count' => 10,//max unlimited
     	'set_property' => 100,//max unlimited
     	'get_property' => 50,//max unlimited
     	'get_all_properties' => 100,//max unlimited
     	'get_billing_status' => 5,//max unlimited
     	'retry_billing_registration' => 5,//max unlimited
     	'join' => 100,//max unlimited
     	'merge' => 50,//max unlimited
     	'logout' => 10,//max unlimited
     )
);
?>
