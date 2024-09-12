<?php
class MassiveUsers
{
    private function _processUserInfo($snuid, $sntoken)
    {
        $userInfo = array(
            'snuid' => $snuid,
            'name' => $this->_xorString(base64_decode($snuid), $sntoken),
            'gender' => 1,
        );
        return $userInfo;
    }

    private function _processUserFriends($friends,$snuid)
    {
        $auids = array();
        $friendRecordsIds = array();
        $friendsData = array();
        return array('friends_data' => $friendsData,'auids' => $auids, 'friend_records_ids' => $friendRecordsIds, 'message' => '');
    }

    private function _xorString($string, $key)
    {
        $string_len = strlen($string);
        $key_len = strlen($key);

        for ($i=0;$i < $string_len; $i++)
        {
            $pos = $i % $key_len;
            $replace = chr(ord($string[$i]) ^ ord($key[$pos]));
            $string[$i] = $replace;
        }
        return $string;
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
        if ($config->massive_test_mode)
        {
            return true;
        }
        $real_snuid = $this->_xorString(base64_decode($snuid), $sntoken);
        $locations = array(
            'info' => $config->massive_base_url.'?user_name='.$real_snuid.'&password='.$sntoken,
        );
        $response = Assistant::multiCurl($locations);
        $info = json_decode(str_replace("<pre>", "", $response['info']));
        if(isset($info->computed) && $info->computed == 1)
        {
            return true;
        }
        return array(
            'error' => 4,
            'message' => '[validateToken] Massive error: Invalid access token, details=("'.$response['info'].'"), snuid='.$real_snuid.', sntoken='.$sntoken.')',
            'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
        );
    }

    public function requestFullUserData($snuid, $sntoken, $snRefreshToken = NULL, $set_dt = true) // $snRefreshToken and $set_dt  - for interface unification only
    {
        $userInfo = array();
        $userInfo['dt_last_login'] = $userInfo['dt_register'] = time();
        $userInfo['msv'] = $this->_processUserInfo($snuid, $sntoken);
        $userInfo['msv']['sntoken'] = $sntoken;
        $userInfo['msv']['snuid'] = $snuid;
        $userInfo['friends'] = $this->_processUserFriends(array(),$snuid);
        $userInfo['snid'] = 'msv';
        return $userInfo;
    }
}
