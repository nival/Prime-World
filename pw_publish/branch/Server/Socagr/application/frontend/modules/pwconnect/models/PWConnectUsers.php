<?php
class PWConnectUsers
{
	public function snTokenRequired()
	{
		return false;
	}

    private function _processUserInfo($info)
    {
        $userInfo = array(
            'email' => isset($info->email)?$info->email:'',
            'birthday' => isset($info->birthdate)?$info->birthdate:'',
            'gender' => isset($info->gender)?$info->gender:'',
        );
        return $userInfo;
    }

    private function _processUserFriends($friends,$snuid)
    {
        $auids = array();
        $friendRecordsIds = array();
        $snuids = array();
        $friendsData = array();
        return array('friends_data' => $friendsData,'auids' => $auids, 'friend_records_ids' => $friendRecordsIds);
    }

    public function validateToken($snuid, $sntoken)
    {
        return true;
    }

    public function requestFullUserData($snuid, $sntoken, $snRefreshToken = NULL, $set_dt = true) // $snRefreshToken and $set_dt  - for interface unification only
    {
        $config = Zend_Registry::get('config');
        /*
         * запрашивает данные у SS->mysql по пользователю, возвращает:
         * {"gender":1,"error":0,"ec":0,"server":"one","tm":0,"birthdate":1,"tmg":0.0,"email":"dev_registration_vg_sept25_1@nivalnetwork.com"}
         */
        $locations = array(
            'info' => $config->pwc_url.'?action=pwc_get_info&snuid='.$snuid,
        );
        $userData = Assistant::multiCurl($locations);
        $info = json_decode($userData['info']);
        if(isset($info->error))
        {
            if ($info->error > 0)
            {
                return array('error' => 6, 'message' => $info->message);
            }
        }
        $friends = array();
        $userInfo['dt_last_login'] = time();
        $userInfo['dt_register'] = time();
        $userInfo['pwc'] = $this->_processUserInfo($info);
        if (!empty($sntoken))
        {
            $userInfo['pwc']['sntoken'] = $sntoken;
        }
        $userInfo['pwc']['snuid'] = $snuid;
        $userInfo['friends'] = $this->_processUserFriends($friends,$snuid);
        $userInfo['snid'] = 'pwc';
        return $userInfo;
    }

    public function checkToken($snuid,$sntoken)
    {
        return true;
    }

    public function generateFriendsData($snuids)
    {
        $result = false;
        return $result;
    }
}
