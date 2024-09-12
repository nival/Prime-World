<?php
class DraugasUsers
{
    private $sSnName = 'Draugas';

    public function snTokenRequired()
    {
        return true;
    }

    private function _processUserInfo($info)
    {
        $userInfo = array(
            'snuid' => $info->Id.'',
            'name' => $info->Name,
            'email' => isset($info->Email) ? $info->Email:'',
            'dt_birthday' => '',
            'gender' => 0,
        );
        if(isset($info->Sex) && in_array($info->Sex,array(1,0)))
        {
            if($info->Sex == 1)
            {
                $userInfo['gender'] = 1;
            }
            else
            {
                $userInfo['gender'] = 2;
            }
        }
        if(isset($info->Photos) && is_array($info->Photos))
        {
            if(count($info->Photos) > 0 )
            {
                //Assistant::logger('before '.$info->Photos[0]);
                $userInfo['photo'] = 'http:'.str_replace("nuotraukos", "crop/64x64/nuotraukos", $info->Photos[0]);
                //Assistant::logger('after '.$userInfo['photo']);

            }
            else
            {
                $userInfo['photo'] = '';
            }

        }
        else {
            $userInfo['photo'] = '';
        }


        return $userInfo;
    }

    private function _processUserFriends($friends,$snuid)
    {
        $auids = array();
        $friendRecordsIds = array();
        $friendsData = array();
        return array('friends_data' => $friendsData,'auids' => $auids, 'friend_records_ids' => $friendRecordsIds, 'message' => '');
    }

    public function validateToken($snuid, $sntoken) // $snuid is not used here, interface purpose only
    {
        $config = Zend_Registry::get('config');

        $response = Assistant::singleCurl($config->draugas_api_url.'/me',array(),false,
            array('Authorization: Bearer '.$sntoken));

        $info = json_decode($response);
        $usersModel = new Users();
        $data=$usersModel->getSnUser('dlt',$snuid,array('_id','dlt.snuid'));

        if(isset($info->Message))
        {
            if($data && isset($data['_id'])) {
                $usersModel->setSntokenExpire($data['_id'], 'dlt', 1);
                return array(
                    'error' => 4,
                    'message' => $this->sSnName . ': Invalid access token.',
                    'ext_error' => gettype($response) == 'string' ? $response : json_encode($response)
                );
            }

        }
        Assistant::logger(print_r($info,true));
        if($data && isset($data['_id']))
        {
            $userInfo = array();
            $userInfo['dlt'] = $this->_processUserInfo($info);
            $userInfo['dlt']['sntoken'] = $sntoken;
            $userInfo['dlt']['sntoken_expire'] = 0;
            $usersModel->edit($data['_id'],array('dlt' => $userInfo['dlt']));
        }
         return true;
    }

    public function requestFullUserData($snuid, $sntoken, $snRefreshToken = NULL, $set_dt = true) // $snRefreshToken and $set_dt  - for interface unification only
    {
        $config = Zend_Registry::get('config');

        $response = Assistant::singleCurl($config->draugas_api_url.'/me',array(),false,
            array('Authorization: Bearer '.$sntoken));

        $info = json_decode($response);
        if(isset($info->Message))
        {
            return array('error' => 6, 'message' => $info->Message);
        }

        if(!isset($info->Id))
        {
            return array('error' => 6, 'message' => $this->sSnName. ': error: Unknown error occurred.');
        }

        if($info->Id != $snuid)
        {
            return array('error' => 7, 'message' => 'Snuid owner does not match with sntoken owner.');
        }

        $userInfo['dt_last_login'] = time();
        $userInfo['dt_register'] = time();
        $userInfo['dlt'] = $this->_processUserInfo($info);
        $userInfo['dlt']['sntoken'] = $sntoken;
        $userInfo['friends'] = $this->_processUserFriends(array(),$snuid);
        $userInfo['snid'] = 'dlt';

        return $userInfo;
    }

    public function checkToken($snuid,$sntoken)
    {
         return $this->validateToken($snuid, $sntoken);
    }

    public function generateFriendsData($snuids)
    {
        $result = false;
        $usersModel = new Users();
        $friends = $usersModel->getSnUsers('dlt',$snuids,array('_id','dlt.snuid'));
        $auids = array();
        $snuids = array();
        foreach ($friends as $friend)
        {
            $auids[] =     $friend['_id'];
            $snuids[] = $friend['dlt']['snuid'];
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
        if (defined('FB_API_VERSION') && (FB_API_VERSION=="v2.2"))
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
