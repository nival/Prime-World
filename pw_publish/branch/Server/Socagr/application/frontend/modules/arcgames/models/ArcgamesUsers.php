<?php
class ArcgamesUsers
{
    const SN_NAME = 'ArcGames';
    const SNID = 'arc';

    const RANDOM_CHARS = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
    const RANDOM_LENGTH = 6;
    const VERSION = 2;
    const FORMAT = 'json';

    private $random=false;
    private $time;
    private $oUserTokenInfo=false;

    private static $_testModeOptions = array(
        CURLOPT_USERAGENT => 'PWServer'
    );

    private function _httpOptions( $config )
    {
        return $config->arcgames_test_mode
            ? self::$_testModeOptions
            : array(
                CURLOPT_USERAGENT => 'PWServer'
            );
    }

    private function _checkError( $response )
    {
        $code = 0;
        $message = '';
        if (isset( $response->error->code ))
        {
            $code = $response->error->code;
            $message = $response->error->message.', detail: '.json_encode($response->error);
        }
        // 4   INTERNAL_ERROR
        // 11  RESOUCE_NOT_FOUND    user not exists
        // 12  TEMP_BAN    Requested same account too many times in short amount time
        // 13  INVALID_LOGIN    Invalid token
        // 14  INVALID_PARAM    Some of the provided parameter values are invalid
        // Arc  SA  Описание ошибки
        // 4    31  Arc internal error	<- нужно завести новую
        // 14   31  Arc internal error	<- нужно завести новую
        // 13   4   Invalid access token
        switch ($code)
        {
            case 0 :
                break;
            case 13 :
                return array(
                    'error' => 4,
                    'message' => self::SN_NAME.' Invalid access token ['.gettype($response) == 'string' ? $response : json_encode($response).']',
                    'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
                );
            case 4 :
            case 14 :
                return array(
                    'error' => 31,
                    'message' => self::SN_NAME.' internal error ['.gettype($response) == 'string' ? $response : json_encode($response).']',
                    'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
                );
            default :
                return array(
                    'error' => 27,
                    'message' => self::SN_NAME.' error ' . $code . ': ' . $message,
                    'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
                );
        }
        if (isset( $response->error ))
            return array(
                'error' => 1,
                'message' => self::SN_NAME.' error: ' . json_encode($response->error),
                'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
            );
        Return false;
    }

    private function _processUserInfo( $info )
    {
        $userInfo = array(
            'snuid' => $info->account,
            'name' => $info->nickname,
            'account' => $info->account,
            'passportid' => $info->id,
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
     * @param $sntoken
     */
    public function validateToken( $snuid, $sntoken)
    {
        if($this->oUserTokenInfo)
        {
            return $this->oUserTokenInfo;
        }
        /*
            object(ArcgamesUsers)#78 (2) {
                ["random":"ArcgamesUsers":private]=>bool(false)
                ["time":"ArcgamesUsers":private]=>NULL
            }
            string(9) "shtest129"
            string(16) "OnkHad0X2PeCp0ZZ"
        */
        $config = Zend_Registry::get('config');

        // if ($config->arcgames_test_mode) return true;

        if(!$this->random)
        {
            $this->random = $this->getRandonString(self::RANDOM_CHARS, self::RANDOM_LENGTH);
        }
        if(!$this->time)
        {
            $this->time = time();
        }
        $request = array(
            'method' => 'user.tokenlogin',
            'params' => array(
                'account'=> $snuid,
                'token'=> $sntoken,
            ),
        );
        $data = json_encode($request);
        $params = array(
            'f' => self::FORMAT,
            'r' => $this->random ,
            't' => $this->time,
            'v' => self::VERSION,
            'g' => $config->arcgames_game,
            'sig' => hash_hmac(
                'sha1',
                $this->random.$this->time.
                self::VERSION.
                $config->arcgames_game.$data,
                $config->arcgames_secret
            ),
        );
        $params_encodes = array();
        foreach($params as $k => $v)
        {
            $params_encodes[] = $k.'='.urlencode($v);
        }
        $locations = array(
            'info' => array(
                'url'=>$config->arcgames_base_url . '?'.join('&', $params_encodes),
                'post'=>$data
            ),
        );
        $response = Assistant::multiCurl( $locations, $this->_httpOptions( $config ) );
        $oInfo = new stdClass();
        if(isset($response['info']))
        {
            $oInfo = json_decode($response['info']);
            $oInfo->data->snuid=$snuid;
            $oInfo->data->account=$snuid;
        }

        $error = $this->_checkError( $oInfo );
        if ($error)
        {
            return $error;
        }

        if (!isset($oInfo->data->id))
        {
            return array(
                'error' => 4,
                'message' => '[validateToken] '.self::SN_NAME.' error: Invalid access token',
                'ext_error'=> gettype($response) == 'string' ? $response : json_encode($response)
            );
        }
        $this->oUserTokenInfo = $oInfo;
        return true;
    }

    public function refreshToken( $snRefreshToken )
    {
    }

    // by user.tokenlogin
    public function requestFullUserData( $snuid, $sntoken, $snRefreshToken = NULL, $set_dt = true) // $snRefreshToken and $set_dt  - for interface unification only
    {
        $config = Zend_Registry::get( 'config' );

        if(!$this->oUserTokenInfo)
        {
            $this->validateToken($snuid, $sntoken);
        }

        if ($this->oUserTokenInfo)
        {
            if (isset( $this->oUserTokenInfo->error ) || (isset( $this->oUserTokenInfo->status ) && $this->oUserTokenInfo->status=='failure' ))
            {
                return array(
                    'error' => 6,
                    'message' => 'Error retrieving user data from '.self::SN_NAME.': ' . $this->oUserTokenInfo->error->code . ': ' . $this->oUserTokenInfo->error->message
                );
            }
            if (isset( $this->oUserTokenInfo->data ))
            {
                $userInfo['dt_last_login'] = time();
                $userInfo['dt_register'] = time();
                $userInfo[self::SNID] = $this->_processUserInfo($this->oUserTokenInfo->data);
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

    /**
     * all md5 is binary
     * @param string $password
     * @param string $salt
     * @param string $token
     * @return string
     */
    protected function hashClientPassword($password, $salt, $token){
        $hash_stage1 = md5($salt.$password, true);
        $hash_stage2 = md5(pack('H*',$token).md5($hash_stage1, true),true);
        return bin2hex($hash_stage1 ^ $hash_stage2);
    }

    /**
     * @param string $alphabet
     * @param int    $length
     * @return string
     */
    protected function getRandonString($alphabet, $length){
        $random = '';
        $l = strlen($alphabet)-1;
        for($i =0; $i<$length;$i++)
        {
            $random .= $alphabet[rand(0, $l)];
        }
        return $random;
    }
}
