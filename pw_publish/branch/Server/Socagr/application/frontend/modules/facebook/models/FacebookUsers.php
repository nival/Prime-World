<?php
class FacebookUsers
{
    private $sSnName = 'Facebook';

    private function _httpOptions( $config )
    {
        return $config->facebook_use_tls
            ? []
            : array(
                CURLOPT_SSL_CIPHER_LIST => 'TLSv1'
            );
    }
    
    public function snTokenRequired()
    {
        return true;
    }

    private function _processUserInfo($info)
    {
        $userInfo = array(
            'snuid' => $info->id.'',
            'name' => $info->name,
            'email' => isset($info->email)?$info->email:'',
            'dt_birthday' => isset($info->birthday)?$info->birthday:'',
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
        return $userInfo;
    }

    private function _loadNextFriendsPage($url)
    {
        $ret = array();
        $info = Assistant::singleCurl($url);
        if(isset($info->error))
        {
            return array();
        }

        if (count($info->data) > 0 && isset($info->paging) && isset($info->paging->next) )
        {
            $friends = $this->_loadNextFriendsPage($info->paging->next);
            $ret =  array_merge ($info->data, $friends);
        }
        return $ret;
    }


    private function _processUserFriends($friends,$snuid)
    {
        $auids = array();
        $friendRecordsIds = array();
        $snuids = array();
        $friendsData = array();
        if(isset($friends->data) && count($friends->data) > 0)
        {
            if (isset($friends->paging) && isset($friends->paging->next) )
            {
                $temp = $this->_loadNextFriendsPage($friends->paging->next);
                $friends->data = array_merge ($friends->data, $temp );

                #unset($friends->paging);
            }

            $friendSnuids = array();
            foreach ($friends->data as $friend)
            {
                $friendSnuids[] = $friend->id;
            }
            $usersModel = new Users();
            $matualSnFriends = $usersModel->getSnUsers('fb',$friendSnuids,array('_id','fb.snuid'));
            foreach ($matualSnFriends as $matualSnFriend)
            {
                $auids[] = $matualSnFriend['_id'];
                $snuids[] = $matualSnFriend['fb']['snuid'];
                $friendRecordsIds[] = 'fb_'.$matualSnFriend['_id'].'_'.$snuid;
            }
            foreach ($friends->data as $friend)
            {
                $friendsData[] = array(
                    'snuid' => $friend->id.'',
                    'name' => $friend->name,
                    'used' => in_array($friend->id,$snuids) ? 1 : 0,
                );
            }
        }
        return array('friends_data' => $friendsData,'auids' => $auids, 'friend_records_ids' => $friendRecordsIds);
    }

    public function validateToken($snuid, $sntoken) // $snuid is not used here, interface purpose only
    {
        $fb_api = '';
        $fb_api_ver = '';
        if (defined('FB_API_VERSION') && ((FB_API_VERSION=="v2.2") || (FB_API_VERSION=="v2.8")))
        {
            $fb_api = FB_API_VERSION . '/';
            $fb_api_ver = FB_API_VERSION;
        }

        $response = Assistant::singleCurl('https://graph.facebook.com/'.$fb_api.'me/permissions?access_token='.$sntoken,array(),false);
        $oJson=json_decode($response);
        $usersModel = new Users();
        $data=$usersModel->getSnUser('fb',$snuid,array('_id','fb.snuid'));

        if(isset($oJson->error))
        {
            if($data && isset($data['_id']))
            {
                $usersModel->setSntokenExpire($data['_id'],'fb',1);
            }
            return array(
                'error' => 4,
                'message' => $this->sSnName. ': Invalid access token.',
                'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
            );
        }
        switch ($fb_api_ver) {
            case 'v2.2':
            case 'v2.8':
                if(isset($oJson->data))
                {
                    foreach ($oJson->data as $v)
                    {
                        $permitionsArray[$v->permission]=$v->status;
                    }
                    $config = Zend_Registry::get('config');
                    foreach ($config->facebook_permitions as $permition)
                    {
                        if( !isset($permitionsArray[$permition]) || !$permitionsArray[$permition] == 'granted' )
                        {
                            return array(
                                'error' => 5,
                                'message' => 'Invalid list of requested permissions.',
                                'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
                            );
                        }
                    }
                }
                else
                {
                    return array(
                        'error' => 20,
                        'message' => $this->sSnName. ' error: Unknown error occurred.',
                        'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
                    );
                }
            break;
            case '':
            default:
                if(isset($oJson->data[0]))
                {
                    $config = Zend_Registry::get('config');
                    $permitionsArray = (array)$oJson->data[0];
                    foreach ($config->facebook_permitions as $permition)
                    {

                        if( (!isset($permitionsArray[$permition]) || $permitionsArray[$permition] == 0))
                        {
                            return array(
                                'error' => 5,
                                'message' => 'Invalid list of requested permissions.',
                                'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
                            );
                        }
                    }
                }
                else
                {
                    return array(
                        'error' => 20,
                        'message' => $this->sSnName. ' error: Unknown error occurred.',
                        'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
                    );
                }
            break;
        }

        if($data && isset($data['_id']))
        {
            $usersModel->setSntokenExpire($data['_id'],'fb',0);
        }
        return true;
    }

    public function requestFullUserData($snuid, $sntoken, $snRefreshToken = NULL, $set_dt = true) // $snRefreshToken and $set_dt  - for interface unification only
    {
        $fb_api = '';
        if (defined('FB_API_VERSION') && ((FB_API_VERSION=="v2.2") || (FB_API_VERSION=="v2.8")))
            $fb_api = FB_API_VERSION . '/';

        if (defined('FB_API_VERSION') && (FB_API_VERSION=="v2.8"))
        {
          $locations = array(
              'friends' => 'https://graph.facebook.com/'.$fb_api.'me/friends?access_token='.$sntoken,
              'info' => 'https://graph.facebook.com/'.$fb_api.'me/?fields=id%2Cname%2Cemail%2Cbirthday%2Cgender&access_token='.$sntoken,
          );
        }
        else {
          $locations = array(
              'friends' => 'https://graph.facebook.com/'.$fb_api.'me/friends?access_token='.$sntoken,
              'info' => 'https://graph.facebook.com/'.$fb_api.'me/?access_token='.$sntoken,
          );
        }
        $config = Zend_Registry::get('config');
        $userData = Assistant::multiCurl($locations, $this->_httpOptions( $config ));
        $info = json_decode($userData['info']);
        if(isset($info->error))
        {
            return array('error' => 6, 'message' => $info->error->message);
        }
        $friends = json_decode($userData['friends']);
        if(isset($friends->error))
        {
            return array('error' => 6, 'message' => $friends->error->message);
        }
        if(!isset($info->id))
        {
            return array('error' => 6, 'message' => $this->sSnName. ': error: Unknown error occurred.');
        }
        if($info->id != $snuid)
        {
            return array('error' => 7, 'message' => 'Snuid owner does not match with sntoken owner.');
        }
        $userInfo['dt_last_login'] = time();
        $userInfo['dt_register'] = time();
        $userInfo['fb'] = $this->_processUserInfo($info);
        $userInfo['fb']['sntoken'] = $sntoken;
        $userInfo['friends'] = $this->_processUserFriends($friends,$snuid);
        $userInfo['snid'] = 'fb';
        return $userInfo;
    }

    public function checkToken($snuid,$sntoken)
    {
        $fb_api = '';
        if (defined('FB_API_VERSION') && ((FB_API_VERSION=="v2.2") || (FB_API_VERSION=="v2.8")))
            $fb_api = FB_API_VERSION.'/';

        $response = Assistant::singleCurl('https://graph.facebook.com/'.$fb_api.'me/?&access_token='.$sntoken);
        if(isset($response->error))
        {
            return array(
                'error' => 6,
                'message' => $response->error->message,
                'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
            );
        }
        if(!isset($response->id))
        {
            return array(
                'error' => 6,
                'message' => 'Facebook error: Unknown error occurred.',
                'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
            );
        }
        if($response->id != $snuid)
        {
            return array(
                'error' => 7,
                'message' => 'Snuid owner does not match with sntoken owner.',
                'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
            );
        }
        return true;
    }

    public function generateFriendsData($snuids)
    {
        $result = false;
        $usersModel = new Users();
        $friends = $usersModel->getSnUsers('fb',$snuids,array('_id','fb.snuid'));
        $auids = array();
        $snuids = array();
        foreach ($friends as $friend)
        {
            $auids[] =     $friend['_id'];
            $snuids[] = $friend['fb']['snuid'];
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
     * @return mixed
     */
    public function post($accessToken,$postTo,$data)
    {
        $fields_string = '';
        $fields = array();
        foreach ($data as $fieldName => $fieldValue)
        {
            $fields[$fieldName] = urlencode($fieldValue);
        }
        $fields['access_token'] = $accessToken;
        foreach($fields as $key=>$value)
        {
            $fields_string .= $key.'='.$value.'&';
        }
        $fields_string = rtrim($fields_string,'&');
        $ch = curl_init();
        $fb_api = '';
        if (defined('FB_API_VERSION') && ((FB_API_VERSION=="v2.2") || (FB_API_VERSION=="v2.8")))
            $fb_api = FB_API_VERSION.'/';

        curl_setopt($ch, CURLOPT_URL, 'https://graph.facebook.com/'.$fb_api.$postTo.'/feed');
        curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_POST,count($fields));
        curl_setopt($ch, CURLOPT_POSTFIELDS,$fields_string);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
        $response = json_decode(curl_exec($ch));
        curl_close($ch);
        return $response;
    }
}
?>
