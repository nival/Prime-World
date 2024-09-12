<?php
class SteamUsers
{
    public function snTokenRequired()
    {
        return false;
    }

    private function _processUserInfo($info)
    {
        $userInfo = array(
            'name' => $info->personaname,
            'photo' => $info->avatarmedium,
        );
        return $userInfo;
    }

    private function _processUserFriends($friends,$snuid)
    {
        $auids = array();
        $friendRecordsIds = array();
        $snuids = array();
        $friendsData = array();
        $message = '';

        if(isset($friends->friendslist))
        {
            $friendslist = $friends->friendslist;
            if (isset($friendslist->friends))
            {
                $friendSnuids = array();
                foreach ($friendslist->friends as $friend)
                {
                    $friendSnuids[] = $friend->steamid;
                }
                $usersModel = new Users();
                $matualSnFriends = $usersModel->getSnUsers('st', $friendSnuids, array('_id','st.snuid'));
                foreach ($matualSnFriends as $matualSnFriend)
                {
                    $auids[] = $matualSnFriend['_id'];
                    $snuids[] = $matualSnFriend['st']['snuid'];
                    $friendRecordsIds[] = 'st_'.$matualSnFriend['_id'].'_'.$snuid;
                }
                foreach ($friendslist->friends as $friend)
                {
                    $friendsData[] = array(
                        'snuid' => $friend->steamid.'',
                        'used' => in_array($friend->steamid, $snuids) ? 1 : 0,
                    );
                }
                $message = 'ok';
            }
            else
            {
                $message = 'no friends';
            }
        } else
        {
            $message = 'no friends list';
        }
        return array('friends_data' => $friendsData,'auids' => $auids, 'friend_records_ids' => $friendRecordsIds, 'message' => $message);
    }

    public function validateToken($snuid, $sntoken)
    {
        $config = Zend_Registry::get('config');
        $locations = array(
            'info' => $config->steam_url.'ISteamUserAuth/AuthenticateUserTicket/v0001/?format=json&key='.$config->steam_key.'&appid='.$config->steam_app_id.'&ticket='.$sntoken,
        );
        $response = Assistant::multiCurl($locations);
        $info = json_decode($response['info']);

        $usersModel = new Users();
        $data=$usersModel->getSnUser('st',$snuid,array('_id','st.snuid'));

        if(isset($info->response))
        {
            $res = $info->response;
            if(isset($res->params))
            {
                $params = $res->params;
                if (isset($params->result) && isset($params->steamid) && $params->result == 'OK' && $params->steamid == $snuid)
                {
                    if($data && isset($data['_id']))
                    {
                        $usersModel->setSntokenExpire($data['_id'],'st',0);
                    }
                    return true;
                }
            }
        }
        if($data && isset($data['_id']))
        {
            $usersModel->setSntokenExpire($data['_id'],'st',1);
        }
        return array(
            'error' => 6,
            'message' => 'Error validating Steam token, result'.json_encode($info),
            'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
        );
    }

    public function requestFullUserData($snuid, $sntoken, $snRefreshToken = NULL, $set_dt = true) // $snRefreshToken and $set_dt  - for interface unification only
    {
        $config = Zend_Registry::get('config');
        $locations = array(
            'info' => $config->steam_url.'ISteamUser/GetPlayerSummaries/v0002/?format=json&key='.$config->steam_key.'&steamids='.$snuid,
            'friends' => $config->steam_url.'ISteamUser/GetFriendList/v0001/?format=json&key='.$config->steam_key.'&steamid='.$snuid.'&relationship=friend',
        );
        $response = Assistant::multiCurl($locations);
        $friends = json_decode($response['friends']);
        $info = json_decode($response['info']);
        if(isset($info->response))
        {
            $res = $info->response;
            if (isset($res->players) && count($res->players) == 1)
            {
                $userInfo['dt_last_login'] = time();
                $userInfo['dt_register'] = time();
                $userInfo['st'] = $this->_processUserInfo($res->players[0]);
                $userInfo['st']['sntoken'] = '';
                $userInfo['st']['snuid'] = $snuid;
                $userInfo['friends'] = $this->_processUserFriends($friends,$snuid);
                $userInfo['snid'] = 'st';
//                return array('error' => 6, 'message' => 'Data:'.json_encode($userInfo['friends']).'->'.json_encode($userInfo['st']));
                return $userInfo;
            }
        }
        return array(
            'error' => 6,
            'message' => 'Error retrieving user data from Steam',
            'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
        );
    }

    public function checkToken($snuid,$sntoken)
    {
        return true;
    }

    public function generateFriendsData($snuids)
    {
        $result = false;
        $usersModel = new Users();
        $friends = $usersModel->getSnUsers('st',  $snuids,array('_id', 'st.snuid'));
        $auids = array();
        $snuids = array();
        foreach ($friends as $friend)
        {
            $auids[] =  $friend['_id'];
            $snuids[] = $friend['st']['snuid'];
        }
        if(count($auids) > 0)
        {
            $result['auids'] = $auids;
            $result['snuids'] = $snuids;
        }
        return $result;
    }
}
