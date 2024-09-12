<?php
require_once dirname(__FILE__).'/../../../application/background/settings/config.php';
$paths = implode(PATH_SEPARATOR, array(
	$config['path']['library'],
	implode(PATH_SEPARATOR, $config['path']['models'])
));
set_include_path($paths);

require_once dirname(__FILE__).'/../../../application/background/Initializer.php';
require_once dirname(__FILE__).'/../../../library/Sa/Log.php';
require_once dirname(__FILE__).'/../../../application/background/workers/workerHelpers.php';
require_once dirname(__FILE__).'/../../../application/frontend/modules/default/models/Assistant.php';

$a=array();
sendToSSBackground(array(
	'host'=>$config['ss_xcoordinator']['host'],
	'port'=>$config['ss_xcoordinator']['port'],
	'path'=>$config['ss_xcoordinator']['path'],
	'timeout'=>isset($config['ss_xcoordinator']['timeout'])?$config['ss_xcoordinator']['timeout']:10,
	'wait_response'=>isset($config['ss_xcoordinator']['wait_response'])?$config['ss_xcoordinator']['wait_response']:false,
	'json'=> '{ "method" : "refresh_friends" }',
	'get'=>array(
		'action'=>'send_to_friends',
		'auid'=>3468849
	)
),$a);