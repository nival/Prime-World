<?php
class ZzimaUsers
{
    const SN_NAME = 'Zzima';
    const SNID = 'zzma';

    private $oUserTokenInfo = false;
    private $zul = false;

    public function snTokenRequired()
    {
        return true;
    }

    public function setZul($val)
    {
        $this->zul = $val;
    }

    private function _processUserInfo($info)
    {
        if(isset($info->user->userid))
        {
            $userInfo = array(
                'snuid' => $info->user->userid.'',
                'name'  => $info->user->displayName,
                'email' => $info->user->email,
                'userName' => $info->user->userName,
//                     ["zzgold"]=>             int(0)
//                     ["userhash"]=>           f9caff197ead6d051132a7ea42d7c03e3ef05a86
//                     ["userid"]=>             int(6897048)
//                     ["email"]=>              string(15) "test@inbox.ru"
//                     ["userName"]=>string(5) "test"
//                     ["referalCode"]=>        string(0) ""
//                     ["creationDate"]=>string(25) "2014-08-05T12:37:09+04:00"
//                     ["displayName"]=>string(5)   "test"
//                     ["partner"]=>                 NULL
//                     ["agreementAccepted"]=>       bool(false)
//                     ["banSn"]=> bool(false)
//                     ["password"]=>NULL
//                     ["status"]=>object(stdClass)#84 (2) {
//                         ["status"]=>string(5) "basic"
//                         ["progressPoints"]=>
                //'creationDate'  => $info->user->creationDate,
                //'photo' => $infoObject->photo,
                //'gender' => 1,
            );
            return $userInfo;
        }
        else
        {
            return false;
        }
    }

    private function _processUserFriends($friends,$snuid)
    {
        return null;
    }

    public function validateToken($snuid, $sntoken)
    {
        /*
        // force zimma
        $oJson = json_decode('{"status":"ok", "user" : {"userid" : "6897048", "displayName"  : "destroyer2014", "email" : "destroyer2014@x.xom","userName" : "destroyer2014"}}');
        $this->oUserTokenInfo = $oJson;
        return true;
        */
        global $config;
        $response = Assistant::singleCurl($this->zul?
            ($config['zzima_zul_login_url'].'?secureToken='.$sntoken) :
            ($config['zzima_api_info_url'].'?userhash='.$sntoken)
            ,array(),false
        );
        $oJson = json_decode($response);
        if(isset($oJson->error))
        {
            return array(
                'error' => 4,
                'message' => 'Invalid access token.',
                'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
            );
        }elseif(!$oJson)
        {
            return array(
                'error' => 23,
                'message' => 'Zzima error: Unknown error occurred.',
                'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
            );
        }
        $this->oUserTokenInfo = $oJson;
        return true;
    }

    public function requestFullUserData($snuid, $sntoken, $snRefreshToken = NULL, $set_dt = true) // $snRefreshToken and $set_dt  - for interface unification only
    {
        if(!$this->oUserTokenInfo){
            $this->validateToken($snuid, $sntoken);
        }

        if ($this->oUserTokenInfo)
        {
            if (isset( $this->oUserTokenInfo->error )
                || (isset( $this->oUserTokenInfo->status ) && $this->oUserTokenInfo->status=='failure' )
            ){
                return array(
                    'error' => 6,
                    'message' => 'Error retrieving user data from '.self::SN_NAME.': ' . $this->oUserTokenInfo->error->code . ': ' . $this->oUserTokenInfo->error->message
                );
            }

            if (isset( $this->oUserTokenInfo ))
            {
                $userInfo['dt_last_login'] = time();
                $userInfo['dt_register'] = time();
                $userInfo[self::SNID] = $this->_processUserInfo($this->oUserTokenInfo);
                $userInfo[self::SNID]['sntoken'] = $sntoken;

                //$userInfo['friends'] = $this->_processUserFriends($friends,$snuid);
                $userInfo['friends'] = array(
                    'friends_data'=>array(),
                    'auids'=> array(),
                    'friend_records_ids'=> array()
                );
                $userInfo['snid'] = self::SNID;
                return $userInfo;
            }
        }
        return array(
            'error' => 6,
            'message' => 'Error retrieving user data from '.self::SN_NAME.': '
        );
    }

    public function generateFriendsData($snuids)
    {
        return null;
    }
}
