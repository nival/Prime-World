<?php
class OdnoklassnikiUsers
{
	public function snTokenRequired()
	{
		return true;
	}

	private function _processUserInfo($info)
	{
		if(isset($info->uid))
		{
			$userInfo = array(
				'snuid' => $info->uid.'',
				'name' => $info->name,
				'photo' => $info->pic_1,
				'gender' => 0,
			);
			if(isset($info->gender) && in_array($info->gender,array('male','female')))
			{
				if($info->gender == 'male')
				{
					$userInfo['gender'] = 1;
				}
				else
				{
					$userInfo['gender'] = 2;
				}
			}
			if(isset($info->birthday))
			{
				$userInfo['dt_birthday'] = $info->birthday;
			}
			return $userInfo;
		}
		else
		{
			return false;
		}
	}

	private function _processUserFriends($friends,$snuid,$sntoken)
	{
		$auids = array();
		$friendRecordsIds = array();
		$snuids = array();
		$friendsData = array();
		$friendsCount = count($friends);
		if($friendsCount > 0)
		{
			$iterationCounter = 100;
			$iterationCount = ceil($friendsCount/$iterationCounter);
			$config = Zend_Registry::get('config');
			$locations = array();
			for($i=0;$i<$iterationCount;$i++)
			{
				$currentIterationFriends = array_slice($friends,$i*$iterationCounter,$iterationCounter);
				if(is_array($currentIterationFriends))
				{
					$idsStr = implode(',',$currentIterationFriends);
					$fields_string = '';
					$fields = array(
						'sig' => md5('application_key='.$config->odnoklassniki->publicKey.'client_id='.$config->odnoklassniki->applicationId.'fields=uid,name,gender,pic_1format=JSONmethod=users.getInfouids='.$idsStr.md5($sntoken.$config->odnoklassniki->secretKey)),
						'client_id' => $config->odnoklassniki->applicationId,
						'format' => 'JSON',
						'method' => 'users.getInfo',
						'application_key' => $config->odnoklassniki->publicKey,
						'access_token' => $sntoken,
						'uids' => $idsStr,
						'fields' => 'uid,name,gender,pic_1',
					);
					//url-ify the data for the POST
					foreach($fields as $key=>$value)
					{
						$fields_string .= $key.'='.$value.'&';
					}
					$fields_string = rtrim($fields_string,'&');
					$locations[$i]['url'] = 'http://api.ok.ru/fb.do';
					$locations[$i]['post'] = $fields_string;
				}
			}
			if(count($locations) > 0)
			{
				$friendsRawDataArray = Assistant::multiCurl($locations,array(CURLOPT_TIMEOUT => 45));
			}
			$friendSnuids = array();
			foreach ($friends as $friend)
			{
				$friendSnuids[] = $friend.'';
			}
			$usersModel = new Users();
			$matualSnFriends = $usersModel->getSnUsers('ok',$friendSnuids,array('_id','ok.snuid'));
			foreach ($matualSnFriends as $matualSnFriend)
			{
				$auids[] = $matualSnFriend['_id'];
				$snuids[] = $matualSnFriend['ok']['snuid'];
				$friendRecordsIds[] = 'ok_'.$matualSnFriend['_id'].'_'.$snuid;
			}
			foreach ($friendsRawDataArray as $friendsRawData)
			{
				if($friendsRawData)
				{
					$friendsDataJson = json_decode($friendsRawData);
					foreach ($friendsDataJson as $friend)
					{
						if(isset($friend->uid))
						{
							$friendsData[] = array(
								'snuid' => $friend->uid.'',
								'name' => $friend->name,
								'photo' => $friend->pic_1,
								'used' => in_array($friend->uid,$snuids) ? 1 : 0,
							);
						}
					}
				}
			}
		}
		return array('friends_data' => $friendsData,'auids' => $auids, 'friend_records_ids' => $friendRecordsIds);
	}

	public function validateToken($snuid, $sntoken) // $snuid is not used here, interface purpose only
	{
		$config = Zend_Registry::get('config');
		$currentPermitions = $config->odnoklassniki->permitions;

		$usersModel = new Users();
		$data=$usersModel->getSnUser('ok',$snuid,array('_id','ok.snuid'));

		foreach ($currentPermitions as $currentPermition)
		{
			$fields_string = '';
			$fields = array(
				'sig' => md5('application_key='.$config->odnoklassniki->publicKey.'client_id='.$config->odnoklassniki->applicationId.'ext_perm='.$currentPermition.'format=JSONmethod=users.hasAppPermission'.md5($sntoken.$config->odnoklassniki->secretKey)),
				'client_id' => $config->odnoklassniki->applicationId,
				'format' => 'JSON',
				'ext_perm' => $currentPermition,
				'method' => 'users.hasAppPermission',
				'application_key' => $config->odnoklassniki->publicKey,
				'access_token' => $sntoken,
			);
			//url-ify the data for the POST
			foreach($fields as $key=>$value)
			{
				$fields_string .= $key.'='.$value.'&';
			}
			$fields_string = rtrim($fields_string,'&');

			$response = Assistant::singleCurl(
				array(
					'url' => 'http://api.ok.ru/fb.do',
					'post'=> $fields_string,
				),
				array(),false
			);

			if($response)
			{
				$oJson=json_decode($response);
				if(isset($oJson->error_code))
				{
					if($oJson->error_code == '103')
					{
						if($data && isset($data['_id']))
						{
							$usersModel->setSntokenExpire($data['_id'],'ok',1);
						}
						return array(
							'error' => 4,
							'message' => 'Invalid access token.',
							'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
						);
					}
					else
					{
						if(isset($oJson->error_msg))
						{
							$message = $oJson->error_msg;
						}
						else
						{
							$message = 'Odnoklassniki error: Unknown error occurred.';
						}
						$message .= ' Code = '.$oJson->error_code.'.';
						return array(
							'error' => 23,
							'message' => $message,
							'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
						);
					}
				}
				if(!$oJson)
				{
					return array(
						'error' => 5,
						'message' => 'Invalid list of requested permisions.',
						'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
					);
				}
			}
			else
			{
				return array(
					'error' => 23,
					'message' => 'Odnoklassniki error: Unknown error occurred.',
					'ext_error'=> 'error in response'
				);
			}
		}
		if($data && isset($data['_id']))
		{
			$usersModel->setSntokenExpire($data['_id'],'ok',0);
		}
		return true;
	}

	public function requestFullUserData($snuid,$sntoken,$snRefreshToken, $set_dt = true) // $set_dt  - for interface unification only
	{
		$config = Zend_Registry::get('config');
		$fields_string = '';
		$fields = array(
			'sig' => md5('application_key='.$config->odnoklassniki->publicKey.'client_id='.$config->odnoklassniki->applicationId.'format=JSONmethod=users.getCurrentUser'.md5($sntoken.$config->odnoklassniki->secretKey)),
			'client_id' => $config->odnoklassniki->applicationId,
			'format' => 'JSON',
			'method' => 'users.getCurrentUser',
			'application_key' => $config->odnoklassniki->publicKey,
			'access_token' => $sntoken,
		);
		//url-ify the data for the POST
		foreach($fields as $key=>$value)
		{
			$fields_string .= $key.'='.$value.'&';
		}
		$fields_string = rtrim($fields_string,'&');
		$locations['info']['url'] = 'http://api.ok.ru/fb.do';
		$locations['info']['post'] = $fields_string;
		$fields_string = '';
		$fields = array(
			'sig' => md5('application_key='.$config->odnoklassniki->publicKey.'client_id='.$config->odnoklassniki->applicationId.'format=JSONmethod=friends.get'.md5($sntoken.$config->odnoklassniki->secretKey)),
			'client_id' => $config->odnoklassniki->applicationId,
			'format' => 'JSON',
			'method' => 'friends.get',
			'application_key' => $config->odnoklassniki->publicKey,
			'access_token' => $sntoken,
		);
		//url-ify the data for the POST
		foreach($fields as $key=>$value)
		{
			$fields_string .= $key.'='.$value.'&';
		}
		$fields_string = rtrim($fields_string,'&');
		$locations['friends']['url'] = 'http://api.ok.ru/fb.do';
		$locations['friends']['post'] = $fields_string;
		$userData = Assistant::multiCurl($locations,array(CURLOPT_TIMEOUT => 45));
		if(!$userData['info'])
		{
			return array('error' => 23, 'message' => 'Odnoklassniki error: Unknown error occurred.');
		}
		if(!$userData['friends'])
		{
			return array('error' => 23, 'message' => 'Odnoklassniki error: Unknown error occurred.');
		}
		$info = json_decode($userData['info']);
		if(isset($info->error_code))
		{
			if(isset($info->error_msg))
			{
				$message = $info->error_msg;
			}
			else
			{
				$message = 'Odnoklassniki error: Unknown error occurred.';
			}
			$message .= ' Code = '.$info->error_code.'.';
			return array('error' => 23, 'message' => $message);
		}
		if(!isset($info->uid))
		{
			return array('error' => 23, 'message' => 'Odnoklassniki error: Unknown error occurred.');
		}
		if($info->uid != $snuid)
		{
			return array('error' => 7, 'message' => 'Snuid owner does not match with sntoken owner.');
		}
		$friends = json_decode($userData['friends']);
		if(isset($friends->error_code))
		{
			if(isset($friends->error_msg))
			{
				$message = $friends->error_msg;
			}
			else
			{
				$message = 'Odnoklassniki error: Unknown error occurred.';
			}
			$message .= ' Code = '.$friends->error_code.'.';
			return array('error' => 23, 'message' => $message);
		}
		$userInfo['dt_last_login'] = time();
		$userInfo['dt_register'] = time();
		$userData = $this->_processUserInfo($info);
		if(!$userData)
		{
			return array('error' => 23, 'message' => 'Odnoklassniki error: Unknown error occurred.');
		}
		$userInfo['ok'] = $userData;
		$userInfo['ok']['sntoken'] = $sntoken;
		$userInfo['ok']['snrefresh_token'] = $snRefreshToken;
		$userInfo['ok']['dt_request_sntoken'] = time();
		$userInfo['ok']['dt_request_snrefresh_token'] = time();
		$friendsData = $this->_processUserFriends($friends,$snuid,$sntoken);
		if(!$friendsData)
		{
			return array('error' => 20, 'message' => 'Odnoklassniki error: Unknown error occurred.');
		}
		$userInfo['friends'] = $friendsData;
		$userInfo['snid'] = 'ok';
		return $userInfo;
	}

	public function refreshToken($snRefreshToken)
	{
		$config = Zend_Registry::get('config');
		$fields_string = '';
		$fields = array(
			'client_id' => $config->odnoklassniki->applicationId,
			'refresh_token' => $snRefreshToken,
			'grant_type' => 'refresh_token',
			'client_secret' => $config->odnoklassniki->secretKey,
		);
		//url-ify the data for the POST
		foreach($fields as $key=>$value)
		{
			$fields_string .= $key.'='.$value.'&';
		}
		$fields_string = rtrim($fields_string,'&');

		$response = Assistant::singleCurl(
			array(
				'url' => 'https://api.ok.ru/oauth/token.do',
				'post'=> $fields_string,
			),
			array(),false
		);

		if($response)
		{
			$oJson = json_decode($response);
			if(isset($oJson->error))
			{
				if(isset($oJson->error_description))
				{
					$message = $oJson->error_description;
				}
				else
				{
					$message = 'Odnoklassniki error: Unknown error occurred.';
				}
				$message .= '. '.$oJson->error.'.';
				return array(
					'error' => 23,
					'message' => $message,
					'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
				);
			}
			else
			{
				if(isset($oJson->access_token))
				{
					return $oJson->access_token;
				}
				else
				{
					return array(
						'error' => 23,
						'message' => 'Odnoklassniki error: Unknown error occurred.',
						'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
					);
				}
			}
		}
		else
		{
			return array('error' => 23, 'message' => 'Odnoklassniki error: Unknown error occurred.');
		}
	}
}
?>
