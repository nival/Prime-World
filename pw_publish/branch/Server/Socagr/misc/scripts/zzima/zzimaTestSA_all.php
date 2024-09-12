<?php
/**
 * @todo - автологин проверить !!!
 *
 * API
 *   https://confluence.nivalnetwork.com/display/prog/Social+Aggregator+Specification#SocialAggregatorSpecification-Getinfo%28%D0%BF%D0%BE%D0%BB%D1%83%D1%87%D0%B5%D0%BD%D0%B8%D0%B5%D0%BF%D0%B5%D1%80%D1%81%D0%BE%D0%BD%D0%B0%D0%BB%D1%8C%D0%BD%D0%BE%D0%B9%D0%B8%D0%BD%D1%84%D0%BE%D1%80%D0%BC%D0%B0%D1%86%D0%B8%D0%B8%29
 * zzima
 *   https://confluence.nivalnetwork.com/display/DevMinsk/OAuth2+ZZima.com
 *
 * https://confluence.nivalnetwork.com/display/prog/Social+Aggregator+Service
 *   В таблице приведены требуемые значения нагрузки по основным вызовам:
 *   Вызовы	Средняя нагрузка (1/сек)	Пиковая нагрузка (1/сек)
 *   login                    50  1000   +
 *   register                 50  1000   +
 *   get_info                 50  1000
 *   get_infos                50  1000
 *   get_edge_status          50  1000
 *   get_friends              50  1000
 *   get_friends_info_all     50  1000
 *   get_candidates_info_all  10  100
 *   add_friend               10  100
 *   delete_friend            10  100
 *   set_edge_property        10  1000
 *   get_edge_property        100 2000
 *   post                     50  1000
 *   post_to_friend           10  100
 *
 *
 * curl -v "http://217.174.109.183:81/oauthp/web/lockdin/token" -d "grant_type=password&client_id=demoapp&client_secret=demopass&username=demouser&password=testpass"
 * curl -v "http://217.174.109.183:81/oauthp/web/lockdin/authorize?response_type=code&client_id=demoapp&redirect_uri=http%3A%2F%2F217.174.109.183%3A81%2Foauthp%2Fweb%2Fclient%2Freceive_authcode&state=htkmsphc28229dmcmu003ogvv2"
 */
ini_set('display_errors', true);
require  dirname(__FILE__). '/../../../application/frontend/settings/config.php';
global $config;

function sendRequest($request,$url,$get=false){

	$data = json_encode($request);
	foreach($request['params'] as $k => $v){
		$params_encodes[] = $k.'='.urlencode($v);
		$params_encodes2[$k] = urlencode($v);
	}
	$url = $url.join('&', $params_encodes);

	printf("CALL METHOD: %s", $request['method']);
	print_r("\n---------------------------------------------------\n");
	printf("URL: \n%s\n", $url);
	printf("BODY: \n%s\n", $data);

	$ch = curl_init();
	curl_setopt($ch, CURLOPT_URL, $url);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($ch, CURLOPT_HEADER, 0);
	if(!$get){
		curl_setopt($ch, CURLOPT_POST, 1);
		curl_setopt($ch, CURLOPT_POSTFIELDS, $params_encodes2);
	}else
		curl_setopt($ch, CURLOPT_POSTFIELDS, $params_encodes);

	$output = curl_exec($ch);
	curl_close($ch);
	printf("RESULT: \n%s\n", $output);
	echo "\n\n\n";
	$response = json_decode($output, true);
	return $response;
}

define('SNID', 'zzma');
// ID snuid - id внешнего пользователя
$userAccount=1;
// $sSocAfrPath = "217.174.109.183:89";
$sSocAgrPath = 'http://oauth.dduka.pwwebdev.nivalnetwork.com';
//$sSocAfrPath = $config['zzima_base_url'];

$red="\033[31m";
$green="\033[32m";
$yellow="\033[33m";
$NC="\033[37m";

// 1 получить код
// curl -L "http://account.aobergan.webdev.nivalnetwork.com/oauth/authorize?client_id=1&redirect_uri=http:\/\/oauth.dduka.pwwebdev.nivalnetwork.com\/get_post.php&response_type=code"

// код на получение токена пользователя
$code = '6529428f5cb37995e29d3ab7348b2b832154e176';
$client_secret = $config['zzima_client_secret'];
$sntoken=false;

// 2 по коду получить token
$url = $config['zzima_base_url'].'/oauth/access-token?';

if( (isset($argv[1])&&$argv[1]==='1') || isset($_GET['t']))
{
	echo "access-token \n";
	// =1&client_secret=123&code=cfd4bdf14b6a456f32a7482aabc197f8a7977e31&redirect_uri=http://oauth.dduka.pwwebdev.nivalnetwork.com/
	$request = array();
	$request['method'] = 'get token';
	$request['params'] = array();
	$request['params']['client_id'] = $userAccount;
	$request['params']['client_secret'] = $client_secret;
	$request['params']['code'] = $code;
	$request['params']['redirect_uri'] = 'http://oauth.dduka.pwwebdev.nivalnetwork.com/get_post.php';
	$response = sendRequest($request,$url) ;
	$sntoken = isset($response['access_token'])?$response['access_token']:false;
	/*
		 {
		  ["access_token"]=>
		  string(40) "f9caff197ead6d051132a7ea42d7c03e3ef05a86"
		  ["expires_in"]=>
		  int(2590000)
		  ["user_id"]=>
		  string(7) "6897048"
		}
	*/
}

$sntoken = $sntoken ? $sntoken : 'f9caff197ead6d051132a7ea42d7c03e3ef05a86';

echo "{$red}userToken: {$sntoken} , path: {$config['zzima_base_url']}{$NC}\n";

// по токену получить INFO http://auth2.qa.nivalnetwork.com/version/2/info?userhash=f9caff197ead6d051132a7ea42d7c03e3ef05a86
if((isset($argv[2])&&$argv[2]==='1') || isset($_GET['info']))
{
	echo "access-token \n";
	$url = $config['zzima_api_url'].'/version/2/info?';
	$request = array();
	$request['method'] = 'get token';
	$request['params'] = array();
	$request['params']['userhash'] = $sntoken;
	$response = sendRequest($request,$url,true) ;
	echo '<pre>';var_dump($response);echo '</pre>';
}


echo "\n\n{$red} Start Test SA {$NC}\n\n";

// login
$url="{$sSocAgrPath}/?action=login&snid=".SNID."&snuid=".$userAccount."&sntoken=".$sntoken."&version=0.3.93&auto=0&snrefresh_token=None&use_billing=0&referral=RU/RU0";
$cont = file_get_contents($url);
echo "{$green}try login [{$userAccount}]:\n{$url}{$NC}\n";
$aCont=json_decode($cont,true);
echo '<pre>';var_dump($aCont);echo '</pre>';
echo "\n";

if(!isset($aCont['auid']))
{
	//register error
	$url = "{$sSocAgrPath}/?action=register&snid=".SNID."&snuid=".$userAccount."&sntoken=".$sntoken.'11'."&version=0.3.93&snrefresh_token=None&use_billing=0&referral=RU/RU0";
	$cont = file_get_contents($url);
	echo "{$green}try register user [{$userAccount}]:\n{$url}{$NC}\n";
	var_dump($cont);
	echo "\n";

	//register
	$url = "{$sSocAgrPath}/?action=register&snid=".SNID."&snuid=".$userAccount."&sntoken=".$sntoken."&version=0.3.93&snrefresh_token=None&use_billing=0&referral=RU/RU0";
	$cont = file_get_contents($url);
	echo "{$green}try register user [{$userAccount}]:\n{$url}{$NC}\n";
	var_dump($cont);
	echo "\n";
	exit();

	//login
	$url="{$sSocAgrPath}/?action=login&snid=".SNID."&snuid=".$userAccount."&sntoken=".$sntoken."&version=0.3.93&auto=0&snrefresh_token=None&use_billing=0&referral=RU/RU0";
	$cont = file_get_contents($url);
	echo "{$green}try reg user [{$userAccount}]:\n{$url}{$NC}\n";
	$aCont=json_decode($cont,true);
	echo "\n";
}

$auid = isset($aCont['auid']) ? $aCont['auid'] : false;
$frend_auid = 2;
if(!$auid){
	echo "\nERROR reg user !!!\n\n";
	exit();
}

// get_info &include_secure_data=1
$url="{$sSocAgrPath}/?action=get_info&snid=".SNID."&auid=".$auid."&include_secure_data=1&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_info include_secure_data=1 [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// get_info &include_secure_data=0
$url="{$sSocAgrPath}/?action=get_info&snid=".SNID."&auid=".$auid."&include_secure_data=0&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_info include_secure_data=0 [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_infos (получение персональной информации по списку пользователей)
$url="{$sSocAgrPath}/?action=get_infos&snid=".SNID."&auids=".$frend_auid.",".$auid."&include_secure_data=0&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_infos [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Add_friend (установление связи "друзья" между двумя аккаунтами)
$url="{$sSocAgrPath}/?action=add_friend&auid=".$auid."&friend_auid=".$frend_auid."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try Add_friend [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// get_edge_status Возвращает, есть ли связь в агрегаторе между двумя игроками.
$url="{$sSocAgrPath}/?action=get_edge_status&auid1=2&auid2=".$auid."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_edge_status [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

//get_friends
$url="{$sSocAgrPath}/?action=get_friends&auid=".$auid."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_friends [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_friends_info_all (получение персональной информации по всем друзьям)
$url="{$sSocAgrPath}/?action=get_friends_info_all&auid=".$auid."&snid=".SNID."&include_secure_data=1&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_friends_info_all [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_candidates_info_all (получение списка кандидатов в друзья)
$url="{$sSocAgrPath}/?action=get_candidates_info_all&auid=".$auid."&snid=".SNID."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_candidates_info_all [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_candidates_info_all (получение списка кандидатов в друзья)
$url="{$sSocAgrPath}/?action=get_candidates_info_all&auid=".$auid."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_candidates_info_all [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// 'fb','vk' only {{{
// Post (пост на стену игрока)
$url="{$sSocAgrPath}/?action=post&auid=".$auid."&snid=".SNID."&message=TEST&link=test.com&picture=none&caption=caption&description=sss&source=I am&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try post [{$userAccount}]:\n{$url}{$NC}\n";
var_dump($cont);
echo "\n\n";

//Post_to_friend (пост на стену друга игрока)
$url="{$sSocAgrPath}/?action=post_to_friend&from_auid=".$auid."&friend_snid=".SNID."&friend_snuid=".SNID."&message=TEST&link=test.com&picture=none&caption=caption&description=sss&source=I am&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try post_to_friend [{$userAccount}]:\n{$url}{$NC}\n";
var_dump($cont);
echo "\n\n";
// }}}

// Set_property (установить значение свойства аккаунта)
$url="{$sSocAgrPath}/?action=set_property&auid=".$auid."&property_name=fraction&property_value=0&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try Set_property [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_property (получить значение свойства)
$url="{$sSocAgrPath}/?action=get_property&auid=".$auid."&property_name=fraction&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try Set_property [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_all_properties (получить значение всех установленных свойств аккаунта)
$url="{$sSocAgrPath}/?action=get_all_properties&auid=".$auid."&property_name=fraction&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try Set_property [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Find_user (поиск пользователя по snuid)
$url="{$sSocAgrPath}/?action=find_user&snid=".SNID."&snuid=".$userAccount."&property_name=fraction&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try Find_user [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_users_count (получение общего кол-ва аккаунтов)
$url="{$sSocAgrPath}/?action=get_users_count&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_users_count :\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

/*******************************************************************************
 * system
*/
// Get_options (получение значений настроек из конфига)
// $url="{$sSocAfrPath}/?action=get_options&version=0.3.93";
// $cont = file_get_contents($url);
// echo "{$green}try get_options :\n{$url}{$NC}\n";
// var_dump(json_decode($cont,true));
// echo "\n\n";

/*******************************************************************************
 * TO || FROM SS
*/

echo '<pre>';var_dump(1);echo '</pre>';exit();

// Get_edge_property (получить значение свойства связи между игроками)
$url="{$sSocAgrPath}/?action=set_property&auid=".$auid."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_edge_property [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// set_edge_property
$url="{$sSocAgrPath}/?action=set_edge_property&snid=".SNID."&snuid=".$userAccount."&sntoken=".$sntoken."&version=0.3.93&auto=0&snrefresh_token=None&use_billing=0&referral=RU/RU0";
$cont = file_get_contents($url);
echo "{$green}try get_info [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// post_to_friend
$url="{$sSocAgrPath}/?action=post_to_friend&snid=".SNID."&snuid=".$userAccount."&sntoken=".$sntoken."&version=0.3.93&auto=0&snrefresh_token=None&use_billing=0&referral=RU/RU0";
$cont = file_get_contents($url);
echo "{$green}try get_info [{$userAccount}]:\n{$url}{$NC}\n";
var_dump($cont);
echo "\n\n";

// Delete_friend (удаление связи "друзья" между двумя аккаунтами)
$url="{$sSocAgrPath}/?action=delete_friend&auid=".$auid."&friend_auid=".$frend_auid."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try Delete_friend [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

