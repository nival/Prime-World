<?php
require 'Zend/Loader/Autoloader.php';

class Bootstrap
{
    /**
     * @var int
     */
    private $_requestStartTime = null;
    /**
     * @var Zend_Config
     */
    private $_config = null;
    /**
     * @var Sa_View_Json
     */
    private $_view = null;

     /**
     * @param array $config
     */
    public function run($config)
    {
        $this->_requestStartTime = microtime(true);
        try
        {
            mb_internal_encoding($config['common']['charset']);
            $this->setLoader();
            $this->setConfig($config);
            $this->setView();
            $this->checkVersion();
            $router = $this->setRouter();
            $front = Zend_Controller_Front::getInstance();
            $front->throwexceptions(true)
                  ->setRouter($router)
                  ->registerPlugin(new Sa_Controller_Plugin_LogWriter($this->_config,$this->_view));
            $front->addModuleDirectory($this->_config->path->modules);
            $front->dispatch();
        }
        catch (Exception $e)
        {
            Error::catchException($e);
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

    public function setRouter()
    {
        require($this->_config->path->system . 'routes.php');
        if (!($router instanceof Zend_Controller_Router_Abstract))
        {
            throw new Exception('Incorrect config file: routes');
        }
        return $router;
    }

    public function setView()
    {
        $pretty = false;
        if(isset($_GET['pretty']) && $_GET['pretty'] == 1)
        {
            $pretty = true;
        }
        $this->_view = new Sa_View_Json(array('charset' => $this->_config->common->charset,'pretty' => $pretty));
        $viewRenderer = new Zend_Controller_Action_Helper_ViewRenderer();
        $viewRenderer->setView($this->_view);
        Zend_Controller_Action_HelperBroker::addHelper($viewRenderer);
        $this->_view->tm = $this->_requestStartTime;
        $this->_view->error = 0;
    }

    public function checkVersion()
    {
        $version = isset($_GET['version']) ? $_GET['version'] : null;
        {
            if($version != $this->_config->version)
            {
                Assistant::logger('Invalid version specified. Current version '.$this->_config->version,Sa_Log::INFO);
                echo json_encode(array('error'=>'Invalid version specified. Current version '.$this->_config->version));
                exit(1);
            }
        }
    }
}
?>
