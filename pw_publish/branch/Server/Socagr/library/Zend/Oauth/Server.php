<?php
/**
 * Zend Framework
 *
 * LICENSE
 *
 * This source file is subject to the new BSD license that is bundled
 * with this package in the file LICENSE.txt.
 * It is also available through the world-wide-web at this URL:
 * http://framework.zend.com/license/new-bsd
 * If you did not receive a copy of the license and are unable to
 * obtain it through the world-wide-web, please send an email
 * to license@zend.com so we can send you a copy immediately.
 *
 * @category   Zend
 * @package    Zend_Oauth
 * @copyright  Copyright (c) 2005-2008 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://framework.zend.com/license/new-bsd     New BSD License
 * @version    $Id: Server.php 10020 2008-07-10 08:24:14Z padraic $
 */

/** Zend_Oauth */
require_once 'Zend/Oauth.php';

/** Zend_Uri */
require_once 'Zend/Uri.php';

/** Zend_Oauth_Config */
require_once 'Zend/Oauth/Config.php';

/**
 * @category   Zend
 * @package    Zend_Oauth
 * @copyright  Copyright (c) 2005-2008 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://framework.zend.com/license/new-bsd     New BSD License
 */
class Zend_Oauth_Server extends Zend_Oauth implements Zend_Oauth_Config_Interface
{

    protected $_config = null;

    public function __construct($options = null)
    {
        $this->_config = new Zend_Oauth_Config;
        if (!is_null($options)) {
            if ($options instanceof Zend_Config) {
                $options = $options->toArray();
            }
            $this->_config->setOptions($options);
        }
    }

    public function createRequestToken()
    {
        if (strtoupper($_SERVER['REQUEST_METHOD']) == Zend_Oauth::POST) {
            
        } elseif (strtoupper($_SERVER['REQUEST_METHOD']) == Zend_Oauth::GET) {

        }
        require_once 'Zend/Oauth/Exception.php';
        throw new Zend_Oauth_Exception('Unsupported method: '
        . strtoupper($_SERVER['REQUEST_METHOD']));
    }

    public function createAccessToken() 
    {
    }

    public function getRedirectUrl() 
    {
    }

    public function redirect() 
    {
    }

    public function isAuthorised() 
    {
    }

    public function __call($method, $args) 
    {
        if (method_exists($this->_config, $method)) {
            return call_user_func_array(array($this->_config,$method), $args);
        }
        require_once 'Zend/Oauth/Exception.php';
        throw new Zend_Oauth_Exception('Method does not exist: '.$method);
    }

}