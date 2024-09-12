<?php
/**
 * https://developers.facebook.com/docs/graph-api
 *
 */
ini_set('memory_limit','1024M');
require_once dirname(__FILE__).'/../../application/tests/settings/config.php';
$paths = implode(PATH_SEPARATOR, array(
		$config['path']['library'],
		implode(PATH_SEPARATOR, $config['path']['models'])
));
set_include_path($paths);
require_once dirname(__FILE__).'/../../application/background/Initializer.php';
$initializer = new Initializer();
$initializer->initialize(array('config' => $config));

require_once dirname(__FILE__).'/../../application/frontend/modules/default/models/Assistant.php';


define('SLEEP_TIME', 10);
define('COUNT_USERS', 10);

/*
// get the app access token
$app_token_url = "https://graph.facebook.com/oauth/access_token?client_id=" . $config['facebook']['applicationId'] ."&client_secret=" . $config['facebook']['applicationSecret'] . "&grant_type=client_credentials";
echo $app_token_url."\n";
$response = file_get_contents($app_token_url);
$params = null;
parse_str($response, $params);

// this is the app access token
$app_token=$params['access_token'];

// create test user
$create_user_url = "https://graph.facebook.com/" . $appid . "/accounts/test-users?installed=true&name=John_Doe&locale=en_US&permissions=read_stream&method=post&access_token=" . $app_token;

// get all test users for an app
$get_users_url = "https://graph.facebook.com/" . $appid . "/accounts/test-users?access_token=" . $app_token;

// make one test user become friends with another test user
$test_uid_1='';
$test_uid_1_token='';
$test_uid_2='';
$test_uid_2_token='';

// create friend request from test user 1 to test user 2
$frient_user_1_url = "https://graph.facebook.com/" . $test_uid_1 . "/friends/" . $test_uid_2 . "?method=post&access_token=" . $test_uid_1_token;
// accept friend request between test user 1 and test user 2
$accept_friend_url="https://graph.facebook.com/" . $test_uid_2 . "/friends/" . $test_uid_1 . "?method=post&access_token=" . $test_uid_2_token;

// change test user's name and password
$test_uid='';
$change_info_url = "https://graph.facebook.com/" . $test_uid . "?password=NEW_PASSWORD&name=NEW_NAME&method=post&access_token=" . $app_token;

// delete a test user
$test_uid='';
$delete_test_user_url = "https://graph.facebook.com/" . $test_uid . "?method=delete&access_token=" . $app_token;
*/


$testUsers = array();
echo 'Try https://graph.facebook.com/'.$config['facebook']['applicationId'].'/accounts/test-users?access_token='.$config['facebook']['accessToken']."\n";

$ch = curl_init();
curl_setopt($ch, CURLOPT_URL, 'https://graph.facebook.com/'.$config['facebook']['applicationId'].'/accounts/test-users?access_token='.$config['facebook']['accessToken']);
curl_setopt($ch, CURLOPT_TIMEOUT, 60);
curl_setopt($ch, CURLOPT_HEADER, 0);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
$result = curl_exec($ch);
if($result === false)
{
	echo 'Connection error: ' . curl_error($ch);
	return false;
}
else
{
	$result = json_decode(curl_exec($ch));

	var_dump($result);

	if(isset($result->error))
	{
		echo 'Facebook error: '.$result->error->message;
		return false;
	}
	else
	{
		$testUsers = $result->data;
		$locations = array();
		foreach ($testUsers as $testUser)
		{
			$locations[$testUser->id] = 'https://graph.facebook.com/'.$testUser->id.'?method=delete&access_token='.$config['facebook']['accessToken'];
		}
		if(count($locations) > 0)
		{
			Assistant::multiCurl($locations,array(),true);
		}
		echo "\nClear users.OK \n";
		//sleep(720);
		sleep(SLEEP_TIME);
		$locations = array();
		for($i=0;$i<COUNT_USERS;$i++)
		{
			$locations[$i] = 'https://graph.facebook.com/'.$config['facebook']['applicationId'].'/accounts/test-users?installed=true&permissions='.$config['facebook']['permitions'].'&method=post&access_token='.$config['facebook']['accessToken'];
		}
		$testUsers = Assistant::multiCurl($locations,array(),true);
		$tempTestUsers = $testUsers;
		shuffle($tempTestUsers);
		$usersForFriendConnections = array_slice($tempTestUsers,0,5);
		$usersForFriendConnectionsArray = array();
		foreach ($usersForFriendConnections as $userForFriendConnections)
		{
			$data = json_decode($userForFriendConnections);
			if(isset($data->id) && isset($usersForFriendConnectionsArray[$data->id]))
			{
				$usersForFriendConnectionsArray[$data->id] = $data->access_token;
			}else{
				var_dump("error:",$data);
			}

		}
		$makeRequestConnectionLocations = array();
		$acceptRequests = array();
		foreach ($testUsers as $testUser)
		{
			$data = json_decode($testUser);
			if(isset($data->id) && $data->id)
			{
				foreach ($usersForFriendConnectionsArray as $id => $accessToken)
				{
					if($id != $data->id)
					{
						$makeRequestConnectionLocations[] = 'https://graph.facebook.com/'.$data->id.'/friends/'.$id.'?method=post&access_token='.$data->access_token;
						$acceptRequests[] = 'https://graph.facebook.com/'.$id.'/friends/'.$data->id.'?method=post&access_token='.$accessToken;
					}
				}
			}
		}
		echo "\n\nCreate new users.OK \n";
		//sleep(734);
		sleep(SLEEP_TIME);
		Assistant::multiCurl($makeRequestConnectionLocations,array(),true);
		echo "Make friend requests.OK \n";
		//sleep(799);
		sleep(SLEEP_TIME);
		Assistant::multiCurl($acceptRequests);
		echo "accepting a friend requests.OK \n";
		echo 'Refresh Complete.';
	}
}
?>
