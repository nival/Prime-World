<?php
$root = realpath(__DIR__ . '/../../../') . '/';
$_app = $root . 'application/';
$_mod = $_app . 'frontend/modules/';

$config = array (
    'us_start_date' => 1368662400, // May 16 2013
    'db' => array(
        'host' => '127.0.0.1', // MongoDB connect host
        'port' => '27017',// MongoDB connection port
        'name_ru' => 'ru', // MongoDB name for RU cluster db
        'name_us' => 'us', // MongoDB name for US cluster db copy
        'options' => array(
            'connect' => true, //If true the constructor should connect before returning.
            //'username' => '*******', // MongoDB connection username
            //'password' => '*******', // MongoDB connection password
            //'persist' => 'foo', //If the connection should be persistent. If set, the connection will be persistent. 
            //'timeout' => 300, // For how long the driver should try to connect to the database (in milliseconds).
            //'replicaSet' => true //If this hosts listed are seeds of a replica set.
        ),
    ),
    'path'  => array (
        'root'        => $root,
        'application' => $_app, //application path
        'library'     => $root . 'library/', // library path
        'modules'     => $_mod, //modules path
        'models'      => array(
            $_mod . 'default/models/', //path to models. if need more modules add models path here
            $_mod . 'facebook/models/',
            $_mod . 'vkontakte/models/',
            $_mod . 'odnoklassniki/models/',
            $_mod . 'steam/models/',
            $_mod . 'aeria/models/',
        ),
        'system'      => $_app . 'frontend/system/', //system files(routes etc) path
        'settings'    => __DIR__, //settings(this file and oher conf files if needed) path
        'logs' => __DIR__ . '/log/', //path to store log files. Example /var/logs/sa/ or using $root $root . 'application/log/'
    ),
    'common' => array (
        'charset' => 'utf-8',//module charset
     ),
    'version' => '0.1',//aplication version
    'log_level' => 'info', //info,error,critical,off 

    'http_timeout' => 300,
	'http_connect_timeout' => 30,

    'billing' => array(
        'url' => 'http://b518.nivalnetwork.com:8080/API/PL/ZZServiceWeb.asmx?WSDL',
        'fromServiceName' => 'pwdev',
        'email_pattern' => 'auid@playpw.com',
		'userName_prefix' => '',
		'reuse_account' => 1, // set it to 1 for testing deployments if using a single billing for multiple SAs
		// always keep it 0 on a live deployment
		//RUSmerge: it's set to 1 to allow miltiple tries and reuse previous try registration
    ),
    'test_billing' => array(
        'url' => 'http://b518.nivalnetwork.com:8080/API/PL/ZZServiceWeb.asmx?WSDL',
        'fromServiceName' => 'pwdev',
        'email_pattern' => 'auid@playpw.com',
        'userName_prefix' => 'test',
		'reuse_account' => 1,
    ),
);
