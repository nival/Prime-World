<?php
class VkontakteUsers
{
	const URL_GET_APP_PERMISSIONS = 'https://api.vk.com/method/account.getAppPermissions?v=5.95&access_token=%s';
	const URL_GET_USER = 'https://api.vk.com/method/users.get?v=5.95&fields=first_name,last_name,photo,sex,bdate&access_token=%s';
	const URL_GET_FRIENDS = 'https://api.vk.com/method/friends.get?v=5.95&fields=photo,last_name,first_name&access_token=%s';
	const URL_WALL_POST = 'https://api.vk.com/method/wall.post?&v=5.95&access_token=%s';

	private $sSnName = 'Vkontakte';

	public function snTokenRequired()
	{
		return true;
	}

	private function _processUserInfo($info)
	{
		$infoObject = $info->response[0];

		if(isset($infoObject->id))
		{
			$userInfo = array(
				'snuid' => $infoObject->id.'',
				'name' => $infoObject->first_name.' '.$infoObject->last_name,
				'photo' => $infoObject->photo,
				'gender' => 0,
			);
			if(isset($infoObject->sex) && in_array($infoObject->sex,array(1,2)))
			{
				if($infoObject->sex == 2)
				{
					$userInfo['gender'] = 1;
				}
				else
				{
					$userInfo['gender'] = 2;
				}
			}
			if(isset($infoObject->bdate))
			{
				$userInfo['dt_birthday'] = $infoObject->bdate;
			}
			return $userInfo;
		}
		else
		{
			return false;
		}
	}

	private function _processUserFriends($friends, $snuid)
	{
		$auids = array();
		$friendRecordsIds = array();
		$snuids = array();
		$friendsData = array();

		if(count($friends->response->items) > 0)
		{
			$friendSnuids = array();
			foreach ($friends->response->items as $friend)
			{
				$friendSnuids[] = $friend->id.'';
			}
			$usersModel = new Users();
			$matualSnFriends = $usersModel->getSnUsers('vk',$friendSnuids,array('_id','vk.snuid'));
			foreach ($matualSnFriends as $matualSnFriend)
			{
				$auids[] = $matualSnFriend['_id'];
				$snuids[] = $matualSnFriend['vk']['snuid'];
				$friendRecordsIds[] = 'vk_'.$matualSnFriend['_id'].'_'.$snuid; # 'reverse' sn_friends record, i.e. from friend's auid to my snuid
			}
			foreach ($friends->response->items as $friend)
			{
				$friendsData[] = array(
					'snuid' => $friend->id.'',
					'name' => $friend->first_name.' '.$friend->last_name,
					'photo' => $friend->photo,
					'used' => in_array($friend->id, $snuids) ? 1 : 0,
				);
			}
		}
		return array('friends_data' => $friendsData,'auids' => $auids, 'friend_records_ids' => $friendRecordsIds);
	}

	public function validateToken($snuid, $sntoken) // $snuid is not used here, interface purpose only
	{
		$response = Assistant::singleCurl(sprintf(self::URL_GET_APP_PERMISSIONS, $sntoken), array(), false);
		$oJson=json_decode($response);

		$usersModel = new Users();
		$data=$usersModel->getSnUser('vk', $snuid, array('_id', 'vk.snuid'));

		if(isset($oJson->error))
		{
			if($data && isset($data['_id']))
			{
				$usersModel->setSntokenExpire($data['_id'],'vk',1);
			}
			return array(
				'error' => 4,
				'message' => $this->sSnName. ': Invalid access token.',
				'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
			);
		}
        if(isset($oJson->response))
        {
            $config = Zend_Registry::get('config');
            $permitionsMask = $oJson->response;
            foreach ($config->vkontakte_permitions as $permitionValue)
            {
                if(!($permitionsMask & $permitionValue))
                {
                    return array(
                        'error' => 5,
                        'message' => 'Invalid list of requested permisions.',
                        'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
                    );
                }
            }
        }
		else
		{
			return array(
				'error' => 20,
				'message' => $this->sSnName. ' error: Unknown error occurred [0x0010].',
				'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
			);
		}
		if($data && isset($data['_id']))
		{
			$usersModel->setSntokenExpire($data['_id'],'vk',0);
		}
		return true;
	}

	public function checkToken( $snuid, $sntoken )
	{
		return true;
	}

	public function requestFullUserData($snuid, $sntoken, $snRefreshToken = NULL, $set_dt = true) // $snRefreshToken - for interface unification only
	{
		$locations = array(
			'info' => sprintf(self::URL_GET_USER, $sntoken),
			'friends' => sprintf(self::URL_GET_FRIENDS, $sntoken),
		);
		$userData = Assistant::multiCurl($locations);

		$info = json_decode($userData['info']);
		if (isset($info->error))
		{
			return array('error' => 20, 'message' => $info->error->error_msg);
		}
		elseif (!isset($info->response) || !isset($info->response[0]->id))
		{
			return array('error' => 20, 'message' => 'Vkontakte error: Unknown error occurred [0x0001].');
		}
		elseif ($info->response['0']->id != $snuid)
		{
			return array('error' => 7, 'message' => $this->sSnName. 'Snuid owner does not match with sntoken owner.');
		}

		$friends = json_decode($userData['friends']);
		if(isset($friends->error))
		{
			return array('error' => 20, 'message' => $friends->error->error_msg);
		}
		if(!isset($friends->response))
		{
			return array('error' => 20, 'message' => $this->sSnName. ' error: Unknown error occurred [0x0002].');
		}

		if ($set_dt)
		{
			$userInfo['dt_last_login'] = $userInfo['dt_register'] = time();
		}

		$userData = $this->_processUserInfo($info);
		if(!$userData)
		{
			return array('error' => 20, 'message' => $this->sSnName. ' error: Unknown error occurred [0x0003].');
		}
		$userInfo['vk'] = $userData;
		$userInfo['vk']['sntoken'] = $sntoken;

		$friendsData = $this->_processUserFriends($friends, $snuid);
		if(!$friendsData)
		{
			return array('error' => 20, 'message' => $this->sSnName. ' error: Unknown error occurred [0x0004].');
		}
		$userInfo['friends'] = $friendsData;
		$userInfo['snid'] = 'vk';

		return $userInfo;
	}

	public function generateFriendsData($snuids)
	{
		$result = false;
		$usersModel = new Users();
		$friends = $usersModel->getSnUsers('vk',$snuids,array('_id','vk.snuid'));
		$auids = array();
		$snuids = array();
		foreach ($friends as $friend)
		{
			$auids[] = $friend['_id'];
			$snuids[] = $friend['vk']['snuid'];
		}
		if(count($auids) > 0)
		{
			$result['auids'] = $auids;
			$result['snuids'] = $snuids;
		}
		return $result;
	}

	/**
	 * @deprecated
	 * @param $accessToken
	 * @param $postTo
	 * @param $data
	 * @return array:string mixed
	 */
	public function post($accessToken, $postTo, $data)
	{
		$response = array();

		$params = '';
		foreach ($data as $paramName=>$paramValue)
		{
			if($paramName == 'link')
			{
				$params .= '&attachments='.urlencode($paramValue);
			}
			if($paramName == 'message')
			{
				$params .= '&message='.urlencode($paramValue);
			}
		}
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, sprintf(self::URL_WALL_POST, $accessToken, $postTo.$params));
		curl_setopt($ch, CURLOPT_HEADER, 0);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
		curl_setopt($ch, CURLOPT_TIMEOUT, 45);
		$response['result'] = json_decode(curl_exec($ch));
		if(empty($response['result']))
		{
			$response['error'] = curl_error($ch);
			if(!$response['error'])
			{
				$response['error'] = 'Unknown connection error occurred';
			}
		}
		curl_close($ch);
		return $response;
	}
}
?>
