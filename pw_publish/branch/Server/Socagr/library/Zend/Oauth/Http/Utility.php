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
 * @version    $Id: Utility.php 10526 2008-07-29 11:07:19Z padraic $
 */

/** Zend_Oauth */
require_once 'Zend/Oauth.php';

/** Zend_Oauth_Http */
require_once 'Zend/Oauth/Http.php';

/**
 * @category   Zend
 * @package    Zend_Oauth
 * @copyright  Copyright (c) 2005-2008 Zend Technologies USA Inc. (http://www.zend.com)
 * @license    http://framework.zend.com/license/new-bsd     New BSD License
 */
class Zend_Oauth_Http_Utility
{

    /**
     * Assemble all parameters for a generic OAuth request - i.e. no special
     * params other than the defaults expected for any OAuth query.
     *
     * @param string $url
     * @param Zend_Oauth_Config_Interface $config
     * @param array $serviceProviderParams
     * @return array
     */
    public function assembleParams($url, Zend_Oauth_Config_Interface $config,
        array $serviceProviderParams = null)
    {
        $params = array();
        $params['oauth_consumer_key'] = $config->getConsumerKey();
        $params['oauth_nonce'] = $this->generateNonce();
        $params['oauth_signature_method'] = $config->getSignatureMethod();
        $params['oauth_timestamp'] = $this->generateTimestamp();
        $params['oauth_token'] = $config->getToken()->getToken();
        $params['oauth_version'] = $config->getVersion();
        if (!is_null($serviceProviderParams)) {
            $params = array_merge($params, $serviceProviderParams);
        }
        $params['oauth_signature'] = $this->sign(
            $params,
            $config->getSignatureMethod(),
            $config->getConsumerSecret(),
            $config->getToken()->getTokenSecret(),
            $config->getRequestMethod(),
            $url
        );
        return $params;
    }

    /**
     * Given both OAuth parameters and any custom parametere, generate an
     * encoded query string. This method expects parameters to have been
     * assembled and signed beforehand.
     *
     * @param array $params
     * @param bool $customParamsOnly Ignores OAuth params e.g. for requests using OAuth Header
     * @return string
     */
    public function toEncodedQueryString(array $params, $customParamsOnly = false)
    {
        if ($customParamsOnly) {
            foreach ($params as $key=>$value) {
                if (preg_match("/^oauth_/", $key)) {
                    unset($params[$key]);
                }
            }
        }
        $encodedParams = array();
        foreach ($params as $key => $value) {
            $encodedParams[] =
                self::urlEncode($key) . '=' . self::urlEncode($value);
        }
        return implode('&', $encodedParams);
    }

    public function toAuthorizationHeader(array $params, $realm = null, $excludeCustomParams = true)
    {
        $headerValue = array();
        $headerValue[] = 'OAuth realm="' . $realm . '"';
        foreach ($params as $key => $value) {
            if ($excludeCustomParams) {
                if (!preg_match("/^oauth_/", $key)) {
                    continue;
                }
            }
            $headerValue[] =
                self::urlEncode($key) . '="'
                . self::urlEncode($value) . '"';
        }
        return implode(",", $headerValue);
    }

    public function sign(array $params, $signatureMethod, $consumerSecret, $tokenSecret = null, $method = null, $url = null)
    {
        $className = '';
        $hashAlgo = null;
        $parts = explode('-', $signatureMethod);
        if (count($parts) > 1) {
            $className = 'Zend_Oauth_Signature_' . ucfirst(strtolower($parts[0]));
            $hashAlgo = $parts[1];
        } else {
            $className = 'Zend_Oauth_Signature_' . ucfirst(strtolower($signatureMethod));
        }
        require_once str_replace('_','/',$className) . '.php';
        $signatureObject = new $className($consumerSecret, $tokenSecret, $hashAlgo);
        return $signatureObject->sign($params, $method, $url);
    }

    public function parseQueryString($query)
    {
        $params = array();
        if (empty($query)) {
            return array();
        }
        // not remotely perfect but beats parse_str() which converts
        // periods and uses urldecode, not rawurldecode.
        $parts = explode('&', $query);
        foreach ($parts as $pair) {
            $kv = explode('=', $pair);
            $params[rawurldecode($kv[0])] = rawurldecode($kv[1]);
        }
        return $params;
    }

    public function generateNonce()
    {
        return md5(uniqid(rand(), true));
    }

    public function generateTimestamp()
    {
        return time();
    }

    public static function urlEncode($value)
    {
        $encoded = rawurlencode($value);
        $encoded = str_replace('%7E','~',$encoded);
        return $encoded;
    }
}