<?php
ini_set('display_errors', true);
define('GAME', 'PWO');
define('SECRET', '9e9c8dc4e7fc3147ff2bbdc38632539c');
define('FORMAT', 'json'); // xml
define('RANDOM_CHARS', '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ');
define('RANDOM_LENGTH', 6);

$sSocAgrPath = "217.174.109.183:89";
$use_billing = 1;

// $userAccount = 'shtest999';
// $userAccount = 'shtest177';
// $userAccount = 'shtest129';
$userAccount = 'shtest101';
$userPassword = 'test123';

$userIp = '86.57.144.74';
$userToken  = 'PMXVgdroo6mfY7Z9' ;

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
	$data = json_encode($request);

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
	$response = json_decode($output, true);
	return $response;
}

echo "API\n";
$request = array();
$request['method'] = 'user.gettoken';
$request['params'] = array();
$request['params']['account'] = $userAccount;
$request['params']['password'] = $userPassword;
$response = sendRequest($request) ;
$sntoken = $response['data']['token'];


$utl="http://{$sSocAgrPath}/?action=login&snid=arc&snuid=".$userAccount."&sntoken=".$sntoken."&version=0.3.93&auto=0&snrefresh_token=None&use_billing=".$use_billing."&referral=RU/RU0";
$cont = file_get_contents($utl);
echo "try reg user [{$userAccount}]:\n{$utl}\n";
var_dump($cont);
echo "\n";

$url = "http://{$sSocAgrPath}/?action=register&snid=arc&snuid=".$userAccount."&sntoken=".$sntoken."&version=0.3.93&snrefresh_token=None&use_billing=".$use_billing."&referral=RU/RU0";
$cont = file_get_contents($url);
echo "try login user [{$userAccount}]:\n{$url}\n";
var_dump($cont);
echo "\n";

$utl="http://{$sSocAgrPath}/?action=login&snid=arc&snuid=".$userAccount."&sntoken=".$sntoken."&version=0.3.93&auto=0&snrefresh_token=None&use_billing=".$use_billing."&referral=RU/RU0";
$cont = file_get_contents($utl);
echo "try reg user [{$userAccount}]:\n{$utl}\n";
var_dump($cont);
echo "\n\n";