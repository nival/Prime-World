<?php
/**
 * https://confluence.nivalnetwork.com/display/prog/Social+Aggregator+Service
 * https://confluence.nivalnetwork.com/display/prog/Social+Aggregator+Specification
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
 * API https://confluence.nivalnetwork.com/display/prog/Social+Aggregator+Specification#SocialAggregatorSpecification-Getinfo%28%D0%BF%D0%BE%D0%BB%D1%83%D1%87%D0%B5%D0%BD%D0%B8%D0%B5%D0%BF%D0%B5%D1%80%D1%81%D0%BE%D0%BD%D0%B0%D0%BB%D1%8C%D0%BD%D0%BE%D0%B9%D0%B8%D0%BD%D1%84%D0%BE%D1%80%D0%BC%D0%B0%D1%86%D0%B8%D0%B8%29
 *
 *   join
 *
 */

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

ini_set('display_errors', true);
define('GAME', 'PWO');
define('SECRET', '9e9c8dc4e7fc3147ff2bbdc38632539c');
define('FORMAT', 'json'); // xml
define('RANDOM_CHARS', '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ');
define('RANDOM_LENGTH', 6);

define('SNID', 'arc');

$red="\033[31m";
$green="\033[32m";
$yellow="\033[33m";
$NC="\033[37m";

$sSocAgrPath = "217.174.109.183:89";

// $userAccount = 'shtest999';
// $userAccount = 'shtest177';
// $userAccount = 'shtest129';
$userAccount = 'shtest310';
$userPassword = 'test123';

$userIp = '86.57.144.74';
//$userToken  = 'PMXVgdroo6mfY7Z9' ;
$url='http://pear-test.arcgames.com';

echo "API\n";
$request = array();
$request['method'] = 'user.gettoken';
$request['params'] = array();
$request['params']['account'] = $userAccount;
$request['params']['password'] = $userPassword;
$response = sendRequest($request,$url);
$sntoken = $response['data']['token'];

//login
$url="http://{$sSocAgrPath}/?action=login&snid=".SNID."&snuid=".$userAccount."&sntoken=".$sntoken."&version=0.3.93&auto=0&snrefresh_token=None&use_billing=0&referral=RU/RU0";
$cont = file_get_contents($url);
echo "{$green}try reg user [{$userAccount}]:\n{$url}{$NC}\n";
$aCont=json_decode($cont,true);
echo "\n";

echo "{$red}user [{$aCont['auid']}]:\n{$NC}\n";

if(!isset($aCont['auid']))
{
	//register
	$url = "http://{$sSocAgrPath}/?action=register&snid=".SNID."&snuid=".$userAccount."&sntoken=".$sntoken."&version=0.3.93&snrefresh_token=None&use_billing=0&referral=RU/RU0";
	$cont = file_get_contents($url);
	echo "{$green}try register user [{$userAccount}]:\n{$url}{$NC}\n";
	var_dump($cont);
	echo "\n";

	//login
	$url="http://{$sSocAgrPath}/?action=login&snid=".SNID."&snuid=".$userAccount."&sntoken=".$sntoken."&version=0.3.93&auto=0&snrefresh_token=None&use_billing=0&referral=RU/RU0";
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
$url="http://{$sSocAgrPath}/?action=get_info&snid=".SNID."&auid=".$auid."&include_secure_data=1&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_info include_secure_data=1 [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// get_info &include_secure_data=0
$url="http://{$sSocAgrPath}/?action=get_info&snid=".SNID."&auid=".$auid."&include_secure_data=0&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_info include_secure_data=0 [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_infos (получение персональной информации по списку пользователей)
$url="http://{$sSocAgrPath}/?action=get_infos&snid=".SNID."&auids=".$frend_auid.",".$auid."&include_secure_data=0&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_infos [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Add_friend (установление связи "друзья" между двумя аккаунтами)
$url="http://{$sSocAgrPath}/?action=add_friend&auid=".$auid."&friend_auid=".$frend_auid."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try Add_friend [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// get_edge_status Возвращает, есть ли связь в агрегаторе между двумя игроками.
$url="http://{$sSocAgrPath}/?action=get_edge_status&auid1=2&auid2=".$auid."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_edge_status [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

//get_friends
$url="http://{$sSocAgrPath}/?action=get_friends&auid=".$auid."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_friends [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_friends_info_all (получение персональной информации по всем друзьям)
$url="http://{$sSocAgrPath}/?action=get_friends_info_all&auid=".$auid."&snid=".SNID."&include_secure_data=1&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_friends_info_all [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_candidates_info_all (получение списка кандидатов в друзья)
$url="http://{$sSocAgrPath}/?action=get_candidates_info_all&auid=".$auid."&snid=".SNID."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_candidates_info_all [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_candidates_info_all (получение списка кандидатов в друзья)
$url="http://{$sSocAgrPath}/?action=get_candidates_info_all&auid=".$auid."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_candidates_info_all [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// 'fb','vk' only {{{
// Post (пост на стену игрока)
$url="http://{$sSocAgrPath}/?action=post&auid=".$auid."&snid=".SNID."&message=TEST&link=test.com&picture=none&caption=caption&description=sss&source=I am&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try post [{$userAccount}]:\n{$url}{$NC}\n";
var_dump($cont);
echo "\n\n";

//Post_to_friend (пост на стену друга игрока)
$url="http://{$sSocAgrPath}/?action=post_to_friend&from_auid=".$auid."&friend_snid=".SNID."&friend_snuid=".SNID."&message=TEST&link=test.com&picture=none&caption=caption&description=sss&source=I am&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try post_to_friend [{$userAccount}]:\n{$url}{$NC}\n";
var_dump($cont);
echo "\n\n";
// }}}

// Set_property (установить значение свойства аккаунта)
$url="http://{$sSocAgrPath}/?action=set_property&auid=".$auid."&property_name=fraction&property_value=0&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try Set_property [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_property (получить значение свойства)
$url="http://{$sSocAgrPath}/?action=get_property&auid=".$auid."&property_name=fraction&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try Set_property [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_all_properties (получить значение всех установленных свойств аккаунта)
$url="http://{$sSocAgrPath}/?action=get_all_properties&auid=".$auid."&property_name=fraction&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try Set_property [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Find_user (поиск пользователя по snuid)
$url="http://{$sSocAgrPath}/?action=find_user&snid=".SNID."&snuid=".$userAccount."&property_name=fraction&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try Find_user [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// Get_users_count (получение общего кол-ва аккаунтов)
$url="http://{$sSocAgrPath}/?action=get_users_count&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_users_count :\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

/*******************************************************************************
 * system
*/
// Get_options (получение значений настроек из конфига)
// $url="http://{$sSocAfrPath}/?action=get_options&version=0.3.93";
// $cont = file_get_contents($url);
// echo "{$green}try get_options :\n{$url}{$NC}\n";
// var_dump(json_decode($cont,true));
// echo "\n\n";

/*******************************************************************************
 * TO || FROM SS
*/

echo '<pre>';var_dump(1);echo '</pre>';exit();

// Get_edge_property (получить значение свойства связи между игроками)
$url="http://{$sSocAgrPath}/?action=set_property&auid=".$auid."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try get_edge_property [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// set_edge_property
$url="http://{$sSocAgrPath}/?action=set_edge_property&snid=".SNID."&snuid=".$userAccount."&sntoken=".$sntoken."&version=0.3.93&auto=0&snrefresh_token=None&use_billing=0&referral=RU/RU0";
$cont = file_get_contents($url);
echo "{$green}try get_info [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

// post_to_friend
$url="http://{$sSocAgrPath}/?action=post_to_friend&snid=".SNID."&snuid=".$userAccount."&sntoken=".$sntoken."&version=0.3.93&auto=0&snrefresh_token=None&use_billing=0&referral=RU/RU0";
$cont = file_get_contents($url);
echo "{$green}try get_info [{$userAccount}]:\n{$url}{$NC}\n";
var_dump($cont);
echo "\n\n";

$url="http://{$sSocAgrPath}/?action=delete_friend&auid=".$auid."&friend_auid=".$frend_auid."&version=0.3.93";
$cont = file_get_contents($url);
echo "{$green}try Delete_friend [{$userAccount}]:\n{$url}{$NC}\n";
var_dump(json_decode($cont,true));
echo "\n\n";

