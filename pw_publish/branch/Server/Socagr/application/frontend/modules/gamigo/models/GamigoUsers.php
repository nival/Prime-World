<?php
class GamigoUsers
{
    const SN_NAME = 'Gamigo';
    const SNID = 'gmg';
    const VERSION = 1;
    const FORMAT = 'json';

    private function _httpOptions( $config )
    {
    }

    private function _checkError( $response )
    {
        return true;
    }

    private function _processUserInfo( $info )
    {
        $userInfo = array(
            'snuid' => strtolower($info['snUserId']),
            'name'  => $info['snUserId'],
            'first_login'  => $info['snUserId'], // логин, при регистрации (вдруг понадобится), в веденном пользователем регистре
            'passportid' => $info['gmguid'],
            // 'locale' => isset($info['locale'])?$info['locale']:'',
            // 'firstName' => isset($info['firstName'])?$info['firstName']:'',
            // 'lastName' => isset($info['lastName'])?$info['lastName']:'',
            // 'gender' => isset($info['gender'])?$info['gender']:'',
        );
        return $userInfo;
    }
    private function _processUserFriends( $friends, $snuid )
    {
        return null;
    }

    public function snTokenRequired()
    {
        return true;
    }

    public function checkToken( $snuid, $sntoken )
    {
        return true;
    }

    /**
     * @param $snuid
     * @param $sntoken - на самом деле пароль !!!
     */
    public function validateToken($snuid, $sntoken)
    {
        $config = Zend_Registry::get('config');
        // шлем запрос в наш апи, он стучит в гамигу, получает ответ, пересылает его нам
        $response = Assistant::singleCurl(
            array(
                'url'=> $config->gamigo_url.'/game-server/verify-login',
                'post'=> 'sntoken='.str_replace(' ','+',$sntoken).'&snuid='.$snuid
            ),array(),false);
        $oJson=json_decode($response);
        if(isset($oJson->error) || !$response || !$oJson)
        {
            return array(
                'error' => 4,
                'message' => self::SN_NAME. ': gamigo error responce '.(isset($oJson->message) ? ': [ '.$oJson->message.' ]' : ''),
                'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
            );
        }
        if(isset($oJson->auid))
        {
            $usersModel = new Users();
            $data=$usersModel->getByAuid($oJson->auid);
            if(!$data)
            {
                return array(
                    'error' => 8,
                    'message' => self::SN_NAME. 'User with auid = '.$oJson->auid.' not found.'.(isset($oJson->message) ? ' Responce: [ '.$oJson->message.' ]' : ''),
                    'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
                );
            }
        }
        return true;
    }

    public function refreshToken( $snRefreshToken )
    {
    }

    public function requestFullUserData( $snuid, $sntoken=NULL, $snRefreshToken = NULL, $set_dt = true, $aExtParams=array()) // $snRefreshToken and $set_dt  - for interface unification only
    {
        $userInfo['dt_last_login'] = time();
        $userInfo['dt_register'] = time();
        $aExtParams = $aExtParams + array('snUserId' => $snuid,);
        $userInfo[self::SNID] = $this->_processUserInfo($aExtParams);

        $userInfo[self::SNID]['sntoken'] = $sntoken;
        $userInfo['friends'] = array();
        $userInfo['snid'] = self::SNID;

        return $userInfo;
    }
}
