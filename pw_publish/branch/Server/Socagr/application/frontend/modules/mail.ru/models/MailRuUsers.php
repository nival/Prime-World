<?php
class MailRuUsers
{

    private function sign_server_server(array $request_params, $secret_key) {
      ksort($request_params);
      $params = '';
      foreach ($request_params as $key => $value) {
        $params .= "$key=$value";
      }
      return md5($params . $secret_key);
    }

    private function _processUserInfo($info)
    {
        $userInfo = array(
            'snuid' => $info->uid.'',
            'name' => $info->nick,
        );
        if(isset($info->sex) && in_array($info->sex,array(0, 1)))
        {
            if($info->sex == 0)
            {
                $userInfo['gender'] = 1;
            }
            else
            {
                $userInfo['gender'] = 2;
            }
        }
        else
        {
            $userInfo['gender'] = 0;
        }
        if(isset($info->birthday))
        {
            $userInfo['dt_birthday'] = $info->birthday;
        }
        if(isset($info->email))
        {
            $userInfo['email'] = $info->email;
        }
        if(isset($info->pic))
        {
            $userInfo['photo'] = $info->pic;
        }
        return $userInfo;
    }

    private function _processUserFriends($friends, $snuid, $sntoken)
    {
        $auids = array();
        $friendsData = array();
        $friendRecordsIds = array();

        if(!$friends || isset($friends->error))
        {
            return array('friends_data' => $friendsData,'auids' => $auids, 'friend_records_ids' => $friendRecordsIds);
        }
        $snuids = array();
        $friendsCount = count($friends);

        if($friendsCount > 0)
        {
            $iterationCounter = 100;
            $iterationCount = ceil($friendsCount/$iterationCounter);
            $config = Zend_Registry::get('config');
            $locations = array();
            for($i=0;$i<$iterationCount;$i++)
            {
                $currentIterationFriends = array_slice($friends, $i*$iterationCounter, $iterationCounter);
                if(is_array($currentIterationFriends))
                {
                    $idsStr = implode(',',$currentIterationFriends);
                    $fields = array(
                        'method' => 'users.getInfo',
                        'app_id' => $config->mru_app_id,
                        'session_key' => $sntoken,
                        'secure' => 1,
                        'uids' => $idsStr
                    );
                    $fields['sig'] = $this->sign_server_server($fields, $config->mru_secret_key);

                    $locations[$i]['url'] = $config->mru_url;
                    $locations[$i]['post'] = http_build_query($fields);
                }
            }
            if(count($locations) > 0)
            {
                $friendsRawDataArray = Assistant::multiCurl($locations, array(CURLOPT_TIMEOUT => 45));
            }
            $friendSnuids = array();
            foreach ($friends as $friend)
            {
                $friendSnuids[] = $friend.'';
            }

            $usersModel = new Users();
            $matualSnFriends = $usersModel->getSnUsers('mru',$friendSnuids,array('_id','mru.snuid'));
            foreach ($matualSnFriends as $matualSnFriend)
            {
                $auids[] = $matualSnFriend['_id'];
                $snuids[] = $matualSnFriend['mru']['snuid'];
                $friendRecordsIds[] = 'mru_'.$matualSnFriend['_id'].'_'.$snuid;
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
                            $userInfo = array(
                                'snuid' => $friend->uid.'',
                                'name' => $friend->nick,
                                'used' => in_array($friend->uid, $snuids) ? 1 : 0,
                            );
                            if(isset($info->pic))
                            {
                                $userInfo['photo'] = $friend->pic;
                            }
                            $friendsData[] = $userInfo;
                        }
                    }
                }
            }
        }
        return array('friends_data' => $friendsData,'auids' => $auids, 'friend_records_ids' => $friendRecordsIds);
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

        $usersModel = new Users();
        $data=$usersModel->getSnUser('mru',$snuid,array('_id','mru.snuid'));

        $params = array(
            'method' => 'users.isAppUser',
            'app_id' => $config->mru_app_id,
            'session_key' => $sntoken,
            'secure' => 1
        );
        $params['sig'] = $this->sign_server_server($params, $config->mru_secret_key);

        $locations = array(
            'info' => $config->mru_url.'?'.http_build_query($params),
        );
        $response = Assistant::multiCurl($locations);
        $info = json_decode($response['info']);

        if($info && isset($info->isAppUser) && $info->isAppUser == 1)
        {
            if($data && isset($data['_id']))
            {
                $usersModel->setSntokenExpire($data['_id'],'mru',0);
            }
            return true;
        }
        if($data && isset($data['_id']))
        {
            $usersModel->setSntokenExpire($data['_id'],'mru',1);
        }
        return array(
            'error' => 6,
            'message' => 'Error validating Mail.Ru token, result="'.json_encode($info).'"',
            'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
        );
    }

    public function requestFullUserData($snuid, $sntoken, $snRefreshToken = NULL, $set_dt = true) // $snRefreshToken and $set_dt  - for interface unification only
    {
        $config = Zend_Registry::get('config');
//        $config = (object) array('mru_url' => 'http://www.appsmail.ru/platform/api', 'mru_app_id' => '714376', 'mru_secret_key' => 'c6206e130188b7d6ac9fdfa82a8564e4');

        $params_friends = array(
            'method' => 'friends.get',
            'app_id' => $config->mru_app_id,
            'session_key' => $sntoken,
            'secure' => 1
        );
        $params_friends['sig'] = $this->sign_server_server($params_friends, $config->mru_secret_key);

        $params_info = array(
            'method' => 'users.getInfo',
            'app_id' => $config->mru_app_id,
            'session_key' => $sntoken,
            'secure' => 1
        );
        $params_info['sig'] = $this->sign_server_server($params_info, $config->mru_secret_key);

        $locations = array(
            'friends' => $config->mru_url.'?'.http_build_query($params_friends),
            'info' => $config->mru_url.'?'.http_build_query($params_info),
        );
        $userData = Assistant::multiCurl($locations);
        $info = json_decode($userData['info']);
        if(!$info || isset($info->error) || count($info) == 0)
        {
            return array('error' => 6, 'message' => $info->error->error_msg);
        }

        $info = $info[0];
        if(!isset($info->uid))
        {
            return array('error' => 6, 'message' => 'Mail.Ru error: Unknown error occurred.');
        }

        if($info->uid != $snuid)
        {
            return array('error' => 7, 'message' => 'Snuid owner does not match with sntoken owner.');
        }

        $friends = json_decode($userData['friends']);

        $userInfo['dt_last_login'] = time();
        $userInfo['dt_register'] = time();
        $userInfo['mru'] = $this->_processUserInfo($info);
        $userInfo['mru']['sntoken'] = $sntoken;
        $userInfo['friends'] = $this->_processUserFriends($friends, $snuid, $sntoken);
        $userInfo['snid'] = 'mru';
        return $userInfo;
    }
}
?>