<?php
class Sa_Controller_Plugin_LogWriter extends Zend_Controller_Plugin_Abstract
{
/**
     * @var Zend_Config
     **/
    protected $_config;

    /**
     * @var Sa_View_Json
     **/
     protected $_view;

    /**
     * @param Zend_Config $config
     */
    public function __construct(Zend_Config $config,Sa_View_Json $view)
    {
        $this->_config = $config;
        $this->_view = $view;
    }

    public function postDispatch(Zend_Controller_Request_Abstract $request=Null)
    {
        if($this->_config->log_level == 'info' || ($this->_config->log_level == 'error' && (int)$this->_view->error > 0))
        {
    		$serverIdent = 'web';
    		$version = $this->_config->version;
    		$date = date("Y.m.d");
    		$fileNamePatern = $serverIdent.'-'.$version.'-'.$date;
        	$logFileArray = glob($this->_config->path->logs.$fileNamePatern."-*-sa.txt", GLOB_NOSORT);
        	if(count($logFileArray))
        	{
        		$logFile = $logFileArray[0];
        	}
        	else
        	{
        		//$logFile = $this->_config->path->logs.$serverIdent.'-'.$version.'-'.date("Y.m.d-H.i.s.u").'-sa.txt';
        		$logFile = $this->_config->path->logs.$serverIdent.'-'.$version.'-'.$date.'-sa.txt';
        	}
        	$queryString = $_SERVER['QUERY_STRING'];
        	//$responce = $this->getResponse()->getBody();
        	$message = $serverIdent.': Query string: '.$queryString;
        	if((int)$this->_view->error > 0)
        	{
        		$message .= ' Error code:'.$this->_view->error.'. Error message:'.$this->_view->message;
        	}
    		$loger =  new Sa_Log();
        	$stream = @fopen($logFile, 'a+', false);
        	$loger->addWriter(new Zend_Log_Writer_Stream($stream));
        	$messageType = ((int)$this->_view->error > 0) ? Sa_Log::ERR : Sa_Log::INFO;
        	$loger->log($message, $messageType);
        }
	}
}
?>