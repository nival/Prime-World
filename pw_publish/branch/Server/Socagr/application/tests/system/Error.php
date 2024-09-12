<?php
class Error
{
    /**
     * @param Exception $exception
     */
    public static function catchException(Exception $exception)
    {
        $errorMessage = $exception->getMessage();
        $trace = $exception->getTraceAsString();
        $str = "ERROR: ".$errorMessage.$trace;
        $config = Zend_Registry::get('config');
        if($config->log_level != 'off')
        {
	        $serverIdent = 'web';
	    	$version = $config->version;
	    	$date = date("Y.m.d");
	    	$fileNamePatern = $serverIdent.'-'.$version.'-'.$date;
	        $logFileArray = glob($config->path->application."log/".$fileNamePatern."-*-sa.txt", GLOB_NOSORT);
	        if(count($logFileArray))
	        {
	        	$logFile = $logFileArray[0];
	        }
	       	else
	       	{
	       		//$logFile = $config->path->application.'log/'.$serverIdent.'-'.$version.'-'.date("Y.m.d-H.i.s.u").'-sa.txt';
	       		$logFile = $config->path->application.'log/'.$serverIdent.'-'.$version.'-'.$date.'-sa.txt';
	       	}
	       	$queryString = $_SERVER['QUERY_STRING'];
	       	$message = $serverIdent.": Query string: ".$queryString."\nError message:".$errorMessage."\nTrace:".$trace;
	     	$loger =  new Sa_Log();
	       	$stream = @fopen($logFile, 'a+', false);
	       	$loger->addWriter(new Zend_Log_Writer_Stream($stream));
	       	$messageType = Sa_Log::CRIT;
	       	$loger->log($message, $messageType);
        }
        if ($config->debug)
        {
            die($str);
        }
        else
        {
            die($errorMessage);
        }
    }
}
?>