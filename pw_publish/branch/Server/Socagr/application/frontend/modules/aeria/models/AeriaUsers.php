<?php
class AeriaUsers
{
	static private $_testModeOptions = array (
		CURLOPT_HTTPAUTH => CURLAUTH_BASIC,
		CURLOPT_USERPWD => 'user',
		CURLOPT_USERAGENT => 'PWServer',
		CURLOPT_SSL_VERIFYPEER => false,
		CURLOPT_SSL_VERIFYHOST => false,
	);

	private function _httpOptions($config)
	{
		return $config->aeria_test_mode ? AeriaUsers::$_testModeOptions : array(CURLOPT_USERAGENT => 'PWServer');
	}

	private function _checkError($response)
	{
		if (isset($response['error']))
		{
			return array(
				'error' => 27,
				'message' => 'AeriaGames error: '.$response['error'],
				'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
			);
		}
		$code = 0;
		$message = '';
		if (isset($response['result']->error_code))
		{
			$code = $response['result']->error_code;
			$message = $response['result']->error_msg;
		}
		elseif (isset($response['result']->error))
		{
			$code = $response['result']->error->code;
			$message = $response['result']->error->message;
		}
		switch ($code)
		{
			case 0:
				break;
			case 190:
				return array(
					'error' => 4,
					'message' => 'AeriaGames error: Invalid access token',
					'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
				);
			case 192:
				return array(
					'error' => 28,
					'message' => 'AeriaGames error: Invalid refresh token',
					'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
				);
			default:
				return array(
					'error' => 27,
					'message' => 'AeriaGames error '.$code.': '.$message,
					'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
				);
		}
		return false;
	}

	private function _processUserInfo($info)
	{
		if (empty($info->fname))
		{
			$name = empty($info->lname) ? $info->username : $info->lname;
		}
		else
		{
			$name = empty($info->lname) ? $info->fname : ($info->fname . ' ' . $info->lname);
		}
		$userInfo = array(
			'snuid' => $info->uid,
			'name' => $name,
			'photo' => 'http:'.$info->picture_url,
		);
		if (isset($info->gender) && $info->gender != '')
		{
			$userInfo['gender'] = $info->gender == 'M' ? 1 : ($info->gender == 'F' ? 2 : 1);
		}
		if(isset($info->birth) && $info->birth != '') // "Unix timestamp, may be negative, may be blank"
		{
			$d = new DateTime();
			$d->setTimestamp($info->birth);
			$userInfo['dt_birthday'] = $d->format('m/d/Y'); //XXX don't know is it correct or I should assing $d itself. check it!
		}

		return $userInfo;
	}

	private function _processUserFriends($friends,$snuid)
	{
		$auids = array();
		$friendRecordsIds = array();
		$snuids = array();
		$friendsData = array();
		$message = '';
		$friendSnuids = array();
		while (isset($friends) && isset($friends->data) && !empty($friends->data))
		{
			foreach ($friends->data as $f)
			{
				$friendSnuids[] = $f->uid;
			}
			// AeriaGames uses paging returning lists and the 'limit' parameter has maximum of 200.
			// We need to check if there the next page and request it.
			if (!(isset($friends->paging) && isset($friends->paging->next)))
			{
				break;
			}
			$friends = Assistant::singleCurl($friends->paging->next);
		}
		if (empty($friendSnuids))
		{
			$message = 'no friends';
		}
		else
		{
			$usersModel = new Users();
			$matualSnFriends = $usersModel->getSnUsers('ae', $friendSnuids, array('_id','ae.snuid'));
			foreach ($matualSnFriends as $matualSnFriend)
			{
				$auids[] = $matualSnFriend['_id'];
				$snuids[] = $matualSnFriend['ae']['snuid'];
				$friendRecordsIds[] = 'ae_'.$matualSnFriend['_id'].'_'.$snuid;
			}
			foreach ($friendSnuids as $friend)
			{
				$friendsData[] = array(
					'snuid' => $friend.'',
					'used' => in_array($friend, $snuids) ? 1 : 0,
				);
			}
			$message = 'ok';
		}
		return array('friends_data' => $friendsData,'auids' => $auids, 'friend_records_ids' => $friendRecordsIds, 'message' => $message);
	}


	public function snTokenRequired()
	{
		return true;
	}

	public function checkToken($snuid,$sntoken)
	{
		return true;
	}

	public function validateToken($snuid, $sntoken)
	{
		$config = Zend_Registry::get('config');
		$response = Assistant::singleCurlCheckError($config->aeria_url.'user/me?access_token='.$sntoken.'&fields=uid', $this->_httpOptions($config));
		$error = $this->_checkError($response);

		$usersModel = new Users();
		$data=$usersModel->getSnUser('ae',$snuid,array('_id','ae.snuid'));

		if ($error)
		{
			return $error;
		}
		if ($response['result']->data->uid != $snuid)
		{
			if($data && isset($data['_id']))
			{
				$usersModel->setSntokenExpire($data['_id'],'ae',1);
			}
			return array(
				'error' => 4,
				'message' => '[validateToken] AeriaGames error: Invalid access token',
				'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
			);
		}
		if($data && isset($data['_id']))
		{
			$usersModel->setSntokenExpire($data['_id'],'ae',0);
		}
		return true;
	}

	public function refreshToken($snRefreshToken)
	{
		$config = Zend_Registry::get('config');
		$fields = array(
			'grant_type' => 'refresh_token',
			'refresh_token' => $snRefreshToken,
			'client_id' => $config->aeria_id,
		);
		$res = Assistant::singleCurlCheckError($config->aeria_base_url.'oauth/access_token?'.Assistant::mkParamString($fields), $this->_httpOptions($config));
		$error = $this->_checkError($res);
		if ($error)
		{
			return $error;
		}
		return array(
			'access_token' => $res['result']->access_token,
			'refresh_token' => $res['result']->refresh_token,
			'expires_in' => $res['result']->expires_in,
		);
	}

	public function requestFullUserData($snuid, $sntoken, $snRefreshToken = NULL, $set_dt = true) // $snRefreshToken and $set_dt  - for interface unification only
	{
		$config = Zend_Registry::get('config');
		$locations = array(
			'info' => $config->aeria_url.'user/me?access_token='.$sntoken.'&fields=uid,username,fname,lname,gender,birth,picture_url',
			'friends' => $config->aeria_url.'user/me/friend?access_token='.$sntoken.'&fields=uid&limit='.$config->aeria_paging_step,
		);
		$response = Assistant::multiCurl($locations, $this->_httpOptions($config));
		$friends = json_decode($response['friends']); #FIXME there is no check for this request result
		$info = json_decode($response['info']);
		if(isset($info))
		{
			if (isset($info->error))
			{
				return array(
					'error' => 6,
					'message' => 'Error retrieving user data from Aeria Games: ' . $info->error->code . ': ' . $info->error->message,
					'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
				);
				# . print_r($response, true));
			}
			if (isset($info->data))
			{
				$userInfo['dt_last_login'] = $userInfo['dt_register'] = time();
				$userInfo['ae'] = $this->_processUserInfo($info->data);
				$userInfo['ae']['sntoken'] = $sntoken;
				$userInfo['ae']['snrefresh_token'] = $snRefreshToken;
				$userInfo['ae']['snuid'] = $snuid;
				$userInfo['friends'] = $this->_processUserFriends($friends,$snuid);
				$userInfo['snid'] = 'ae';
				#return array('error' => 6, 'message' => 'Data:'.json_encode($userInfo['friends']).'->'.json_encode($userInfo['ae']));
				return $userInfo;
			}
		}
		return array(
			'error' => 6,
			'message' => 'Error retrieving user data from Aeria Games: ',
			'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
		); # . print_r($response, true));
	}

//	public function generateFriendsData($snuids)
//	{
//	}
}