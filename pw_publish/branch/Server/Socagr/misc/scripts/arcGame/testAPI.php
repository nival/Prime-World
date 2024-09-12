<?php
ini_set('display_errors', false);
header('Content-type: text/plain');
// require 'f.php';
// define('GAME', 'boi');
define('GAME', 'PWO');
define('SECRET', '9e9c8dc4e7fc3147ff2bbdc38632539c');
define('FORMAT', 'json');
#define('FORMAT', 'xml');
define('RANDOM_CHARS', '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ');
define('RANDOM_LENGTH', 6);

// $userAccount = 'shtest999';
// $userAccount = 'shtest177';
// $userAccount = 'shtest129';
$userAccount = 'shtest349';
$userPassword = 'test123';

// (user= 'shtest999', pwd='test123')

$userIp = '86.57.144.74';
$userToken  = 'PMXVgdroo6mfY7Z9' ;


// Game Abbr = PWO
// Game ID = 4600
// Secret Key = 9e9c8dc4e7fc3147ff2bbdc38632539c

/**
 * all md5 is binary
 * @param string $password
 * @param string $salt
 * @param string $token
 * @return string
 */
function hashClientPassword($password, $salt, $token){
	$hash_stage1 = md5($salt.$password, true);
	$hash_stage2 = md5(pack('H*',$token).md5($hash_stage1, true),true);
	return bin2hex($hash_stage1 ^ $hash_stage2);
}

/**
 * @param string $alphabet
 * @param int    $length
 * @return string
 */
function getRandonString($alphabet, $length){
	$random = '';
	$l = strlen($alphabet)-1;
	for($i =0; $i<$length;$i++){
		$random .= $alphabet[rand(0, $l)];
	}
	return $random;
}

/**
 * @param array $request formatted into json/xml, send as post body
 * @return array
 */
function sendRequest($request){
	$data = FORMAT=='json' ? json_encode($request) : @ArrayXmlConverter::toXML($request, 'document')->asXML();

	$random = getRandonString(RANDOM_CHARS, RANDOM_LENGTH);
	$time = time();
	$version = 1;
	$game = GAME;
	$key = SECRET;
	$sig = hash_hmac('sha1', $random.$time.$version.$game.$data, $key);

	$params = array();
	$params['f'] = FORMAT;
	$params['r'] = $random;
	$params['t'] = $time;
	$params['v'] = $version;
	$params['g'] = $game;
	$params['sig'] = $sig;
	$params_encodes = array();
	foreach($params as $k => $v){
		$params_encodes[] = $k.'='.urlencode($v);
	}

	$url = 'http://pear-test.arcgames.com/?'.join('&', $params_encodes);
	//$url = 'http://pear.arcgames.com/?'.join('&', $params_encodes);

	printf("CALL METHOD: %s", $request['method']);
	print_r("\n---------------------------------------------------\n");
	printf("URL: \n%s\n", $url);
	printf("BODY: \n%s\n", $data);

	$ch = curl_init();
	curl_setopt($ch, CURLOPT_URL, $url);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($ch, CURLOPT_HEADER, 0);
	curl_setopt($ch, CURLOPT_POST, 1);
	curl_setopt($ch, CURLOPT_POSTFIELDS, $data);
	$output = curl_exec($ch);
	curl_close($ch);
	printf("RESULT: \n%s\n", $output);
	echo "\n\n\n";
	$response = FORMAT=='json' ? json_decode($output, true) : @ArrayXmlConverter::toArray($output);
	return $response;
}

/*$request = array();
$request['method'] = 'user.prelogin';
$request['params'] = array();
$request['params']['account'] = $userAccount;
$request['params']['ip'] = $userIp;
$response = sendRequest($request);

$request = array();
$request['method'] = 'user.login';
$request['params'] = array();
$request['params']['account'] = $userAccount;
$request['params']['password'] = hashClientPassword($userPassword, $response['data']['salt'], $response['data']['token']);
$request['params']['ip'] = $userIp;
$response = sendRequest($request);

$request = array();
$request['method'] = 'user.info';
$request['params'] = array();
$request['params']['id'] = $response['data']['id'];
$response = sendRequest($request);

$request = array();
$request['method'] = 'log.purchaseitem';
$request['params'] = array();
$request['params']['userId'] = 'ramdon user id';
$request['params']['itemName'] = 'test item';
$request['params']['itemQuantity'] = 10;
$request['params']['totalPrice'] = 83.19;
$request['params']['currency'] = 'usd';
$request['params']['transactionId'] = '#abc';
$request['params']['transactionDate'] = time();
$response = sendRequest($request);
 */

echo "API\n";
$request = array();
$request['method'] = 'user.gettoken';
$request['params'] = array();
$request['params']['account'] = $userAccount;
$request['params']['password'] = $userPassword;
$response = sendRequest($request) ;
$token = $response['data']['token'];

echo '<pre>';var_dump(1);echo '</pre>';exit();

echo "API server - NOT USE!!!\n";
$request = array();
$request['method'] = 'user.tokenlogin';
$request['params'] = array();
$request['params']['account'] = $userAccount;
$request['params']['token'] = $token;
$response = sendRequest($request) ;

// echo "API server - NOT USE!!!\n";
// $request = array();
// $request['method'] = 'user.tokenlogin';
// $request['params'] = array();
// $request['params']['account'] = $userAccount;
// $request['params']['token'] = $token;
// $response = sendRequest($request) ;
echo '<pre>';var_dump(1);echo '</pre>';exit();

echo "API\n";
$request = array();
$request['method'] = 'user.prelogin';
$request['params'] = array();
$request['params']['account'] = $userAccount;
$request['params']['ip'] = $userIp;
$response = sendRequest($request);


echo "API\n";
$request = array();
$request['method'] = 'user.login';
$request['params'] = array();
$request['params']['account'] = $userAccount;
$request['params']['password'] = hashClientPassword($userPassword, $response['data']['salt'], $response['data']['token']);
$request['params']['ip'] = $userIp;
$response = sendRequest($request);

echo "API\n";
var_dump($response);
$request['method'] = 'log.purchaseitem';
$request['params'] = array();
$request['params']['userId'] = (int)$response['data']['id'];
$request['params']['itemName'] = 'MonsterCard';
$request['params']['itemQuantity'] = '1';
$request['params']['totalPrice'] = '0.99';
$request['params']['currency'] = 'usd';
$request['params']['transactionId'] = 'WYSD1223KKS';
$request['params']['transactionDate'] = '1372829445';
$response = sendRequest($request);
var_dump($response);

echo "API\n";
$id = isset($response['data']['id'])?$response['data']['id']:0;
echo "for {$id}:\n";
$request = array();
$request['method'] = 'user.info';
$request['params'] = array();
$request['params']['id'] = $id;
$response = sendRequest($request) ;

echo "API\n";
echo "for 43671433:\n";
$request = array();
$request['method'] = 'user.info';
$request['params'] = array();
$request['params']['id'] = '43671433';
$response = sendRequest($request) ;

echo "API\n";
echo "for 1:\n";
$request = array();
$request['method'] = 'user.info';
$request['params'] = array();
$request['params']['id'] = '1';
$response = sendRequest($request) ;
