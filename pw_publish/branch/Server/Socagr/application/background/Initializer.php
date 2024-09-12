<?php
require_once 'Zend/Loader/Autoloader.php';
class Initializer
{
    /**
     * @var Zend_Config
     */
    private $_config = null;

    public function initialize($params = array())
    {
    	$this->setLoader();
        if(isset($params['config']))
        {
            $this->setConfig($params['config']);
            mb_internal_encoding($params['config']['common']['charset']);
        }
    }

    public function setLoader()
    {
        $loader = Zend_Loader_Autoloader::getInstance();
        $loader->setFallbackAutoloader(true)
               ->suppressNotFoundWarnings(false)
               ->registerNamespace('SA_');
    }

 	/**
     * @param array $config
     */
    public function setConfig($config)
    {
        $config = new Zend_Config($config);
        $this->_config = $config;
        Zend_Registry::set('config', $config);
    }
}
?>