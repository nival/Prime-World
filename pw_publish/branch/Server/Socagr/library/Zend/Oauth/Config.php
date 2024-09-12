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
 * @version    $Id: Config.php 20053 2010-01-03 15:15:48Z padraic $
 */

/** Zend_Oauth */
require_once 'Zend/Oauth.php';

/** Zend_Uri */
require_once 'Zend/Uri.php';

/** Zend_Oauth_Config_Interface */
require_once 'Zend/Oauth/Config/Interface.php';

/**
 * @category   Zend
 * @package    Zend_Oauth
 * @copyright  Copyright (c) 2005-2008 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://framework.zend.com/license/new-bsd     New BSD License
 */
class Zend_Oauth_Config implements Zend_Oauth_Config_Interface
{

    /**
     * Signature method used when signing all parameters for an HTTP request
     *
     * @var string
     */
    protected $_signatureMethod = 'HMAC-SHA1';

    /**
     * Three request schemes are defined by OAuth, of which passing
     * all OAuth parameters by Header is preferred. The other two are
     * POST Body and Query String.
     *
     * @var string
     */
    protected $_requestScheme = Zend_Oauth::REQUEST_SCHEME_HEADER;

    /**
     * Preferred request Method - one of GET or POST - which Zend_Oauth
     * will enforce as standard throughout the library. Generally a default
     * of POST works fine unless a Provider specifically requires otherwise.
     *
     * @var string
     */
    protected $_requestMethod = Zend_Oauth::POST;

    /**
     * OAuth Version; This defaults to 1.0 - Must not be changed!
     *
     * @var string
     */
    protected $_version = '1.0';

    /**
     * This optional value is used to define where the user is redirected to
     * after authorising a Request Token from an OAuth Providers website.
     * It's optional since a Provider may ask for this to be defined in advance
     * when registering a new application for a Consumer Key.
     *
     * @var string
     */
    protected $_callbackUrl = null;

    /**
     * The URL root to append default OAuth endpoint paths.
     *
     * @var string
     */
    protected $_siteUrl = null;

    /**
     * The URL to which requests for a Request Token should be directed.
     * When absent, assumed siteUrl+'/request_token'
     *
     * @var string
     */
    protected $_requestTokenUrl = null;

    /**
     * The URL to which requests for an Access Token should be directed.
     * When absent, assumed siteUrl+'/access_token'
     *
     * @var string
     */
    protected $_accessTokenUrl = null;

    /**
     * The URL to which users should be redirected to authorise a Request Token.
     * When absent, assumed siteUrl+'/authorize'
     *
     * @var string
     */
    protected $_authorizeUrl = null;

    /**
     * An OAuth application's Consumer Key.
     *
     * @var string
     */
    protected $_consumerKey = null;

    /**
     * Every Consumer Key has a Consumer Secret unless you're in RSA-land.
     *
     * @var string
     */
    protected $_consumerSecret = null;

    /**
     * If relevant, a PEM encoded RSA private key encapsulated as a
     * Zend_Crypt_Rsa Key
     *
     * @var Zend_Crypt_Rsa_Key_Private
     */
    protected $_rsaPrivateKey = null;

    /**
     * If relevant, a PEM encoded RSA public key encapsulated as a
     * Zend_Crypt_Rsa Key
     *
     * @var Zend_Crypt_Rsa_Key_Public
     */
    protected $_rsaPublicKey = null;

    /**
     * Generally this will nearly always be an Access Token represented as a
     * Zend_Oauth_Token_Access object.
     *
     * @var Zend_Oauth_Token
     */
    protected $_token = null;

    /**
     * Constructor; create a new object with an optional array|Zend_Config
     * instance containing initialising options.
     *
     * @param array|Zend_Config $options
     * @return void
     */
    public function __construct($options = null)
    {
        if (!is_null($options)) {
            if ($options instanceof Zend_Config) {
                $options = $options->toArray();
            }
            $this->setOptions($options);
        }
    }

    /**
     * Parse option array or Zend_Config instance and setup options using their
     * relevant mutators.
     *
     * @param array|Zend_Config $options
     * @return void
     */
    public function setOptions(array $options)
    {
        foreach ($options as $key=>$value) {
            switch ($key) {
                case 'consumerKey':
                    $this->setConsumerKey($value);
                    break;
                case 'consumerSecret':
                    $this->setConsumerSecret($value);
                    break;
                case 'signatureMethod':
                    $this->setSignatureMethod($value);
                    break;
                case 'version':
                    $this->setVersion($value);
                    break;
                case 'callbackUrl':
                    $this->setCallbackUrl($value);
                    break;
                case 'siteUrl':
                    $this->setSiteUrl($value);
                    break;
                case 'requestTokenUrl':
                    $this->setRequestTokenUrl($value);
                    break;
                case 'accessTokenUrl':
                    $this->setAccessTokenUrl($value);
                    break;
                case 'userAuthorisationUrl':
                    $this->setUserAuthorisationUrl($value);
                    break;
                case 'authorizeUrl':
                    $this->setAuthorizeUrl($value);
                    break;
                case 'requestMethod':
                    $this->setRequestMethod($value);
                    break;
                case 'rsaPrivateKey':
                    $this->setRsaPrivateKey($value);
                    break;
                case 'rsaPublicKey':
                    $this->setRsaPublicKey($value);
                    break;
            }
        }
        if (isset($options['requestScheme'])) {
            $this->setRequestScheme($options['requestScheme']);
        }
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param string
     * @return void
     */
    public function setConsumerKey($key)
    {
        $this->_consumerKey = $key;
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return string
     */
    public function getConsumerKey()
    {
        return $this->_consumerKey;
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param string
     * @return void
     */
    public function setConsumerSecret($secret)
    {
        $this->_consumerSecret = $secret;
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return string
     */
    public function getConsumerSecret()
    {
        if (!is_null($this->_rsaPrivateKey)) {
            return $this->_rsaPrivateKey;
        }
        return $this->_consumerSecret;
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param string
     * @return void
     */
    public function setSignatureMethod($method)
    {
        $method = strtoupper($method);
        if (!in_array($method, array(
            'HMAC-SHA1', 'HMAC-SHA256', 'RSA-SHA1', 'PLAINTEXT'
        ))) {
            require_once 'Zend/Oauth/Exception.php';
            throw new Zend_Oauth_Exception('Unsupported signature method: '
            . $method
            . '. Supported are HMAC-SHA1, RSA-SHA1, PLAINTEXT and HMAC-SHA256');
        }
        $this->_signatureMethod = $method;;
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return string
     */
    public function getSignatureMethod()
    {
        return $this->_signatureMethod;
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param string
     * @return void
     */
    public function setRequestScheme($scheme)
    {
        $scheme = strtolower($scheme);
        if (!in_array($scheme, array(
                Zend_Oauth::REQUEST_SCHEME_HEADER,
                Zend_Oauth::REQUEST_SCHEME_POSTBODY,
                Zend_Oauth::REQUEST_SCHEME_QUERYSTRING
            ))) {
            require_once 'Zend/Oauth/Exception.php';
            throw new Zend_Oauth_Exception(
                '\'' . $scheme . '\' is an unsupported request scheme'
            );
        }
        if ($scheme == Zend_Oauth::REQUEST_SCHEME_POSTBODY
            && $this->getRequestMethod() == Zend_Oauth::GET) {
            require_once 'Zend/Oauth/Exception.php';
            throw new Zend_Oauth_Exception(
                'Cannot set POSTBODY request method if HTTP method set to GET'
            );
        }
        $this->_requestScheme = $scheme;
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return string
     */
    public function getRequestScheme()
    {
        return $this->_requestScheme;
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param string
     * @return void
     */
    public function setVersion($version)
    {
        $this->_version = $version;
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return string
     */
    public function getVersion()
    {
        return $this->_version;
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param string
     * @return void
     */
    public function setCallbackUrl($url)
    {
        if (!Zend_Uri::check($url)) {
            require_once 'Zend/Oauth/Exception.php';
            throw new Zend_Oauth_Exception(
                '\'' . $url . '\' is not a valid URI'
            );
        }
        $this->_callbackUrl = $url;
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return string
     */
    public function getCallbackUrl()
    {
        return $this->_callbackUrl;
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param string
     * @return void
     */
    public function setSiteUrl($url)
    {
        if (!Zend_Uri::check($url)) {
            require_once 'Zend/Oauth/Exception.php';
            throw new Zend_Oauth_Exception(
                '\'' . $url . '\' is not a valid URI'
            );
        }
        $this->_siteUrl = $url;
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return string
     */
    public function getSiteUrl()
    {
        return $this->_siteUrl;
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param string
     * @return void
     */
    public function setRequestTokenUrl($url)
    {
        if (!Zend_Uri::check($url)) {
            require_once 'Zend/Oauth/Exception.php';
            throw new Zend_Oauth_Exception(
                '\'' . $url . '\' is not a valid URI'
            );
        }
        $this->_requestTokenUrl = rtrim($url, '/');
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return string
     */
    public function getRequestTokenUrl()
    {
        if (!$this->_requestTokenUrl && $this->_siteUrl) {
            return $this->_siteUrl . '/request_token';
        }
        return $this->_requestTokenUrl;
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param string
     * @return void
     */
    public function setAccessTokenUrl($url)
    {
        if (!Zend_Uri::check($url)) {
            require_once 'Zend/Oauth/Exception.php';
            throw new Zend_Oauth_Exception(
                '\'' . $url . '\' is not a valid URI'
            );
        }
        $this->_accessTokenUrl = rtrim($url, '/');
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return string
     */
    public function getAccessTokenUrl()
    {
        if (!$this->_accessTokenUrl && $this->_siteUrl) {
            return $this->_siteUrl . '/access_token';
        }
        return $this->_accessTokenUrl;
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param string
     * @return void
     */
    public function setUserAuthorisationUrl($url)
    {
        return $this->setAuthorizeUrl($url);
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param string
     * @return void
     */
    public function setAuthorizeUrl($url)
    {
        if (!Zend_Uri::check($url)) {
            require_once 'Zend/Oauth/Exception.php';
            throw new Zend_Oauth_Exception(
                '\'' . $url . '\' is not a valid URI'
            );
        }
        $this->_authorizeUrl = rtrim($url, '/');
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return string
     */
    public function getUserAuthorisationUrl()
    {
        return $this->getAuthorizeUrl();
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return string
     */
    public function getAuthorizeUrl()
    {
        if (!$this->_authorizeUrl && $this->_siteUrl) {
            return $this->_siteUrl . '/authorize';
        }
        return $this->_authorizeUrl;
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param string
     * @return void
     */
    public function setRequestMethod($method)
    {
        $method = strtoupper($method);
        if (!in_array($method, array(Zend_Oauth::GET, Zend_Oauth::POST, Zend_Oauth::PUT, Zend_Oauth::DELETE))) {
            require_once 'Zend/Oauth/Exception.php';
            throw new Zend_Oauth_Exception('Invalid method: '.$method);
        }
        $this->_requestMethod = $method;
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return string
     */
    public function getRequestMethod()
    {
        return $this->_requestMethod;
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param Zend_Crypt_Rsa_Key_Public
     * @return void
     */
    public function setRsaPublicKey(Zend_Crypt_Rsa_Key_Public $key)
    {
        $this->_rsaPublicKey = $key;
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return Zend_Crypt_Rsa_Key_Public
     */
    public function getRsaPublicKey()
    {
        return $this->_rsaPublicKey;
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param Zend_Crypt_Rsa_Key_Private
     * @return void
     */
    public function setRsaPrivateKey(Zend_Crypt_Rsa_Key_Private $key)
    {
        $this->_rsaPrivateKey = $key;
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return Zend_Crypt_Rsa_Key_Private
     */
    public function getRsaPrivateKey()
    {
        return $this->_rsaPrivateKey;
    }

    /**
     * Generic mutator for an option value recognised in this class.
     *
     * @param string
     * @return void
     */
    public function setToken(Zend_Oauth_Token $token)
    {
        $this->_token = $token;
    }

    /**
     * Generic accessor for an option value recognised in this class.
     *
     * @return Zend_Oauth_Token
     */
    public function getToken()
    {
        return $this->_token;
    }

}
