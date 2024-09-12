<?php
class Sa_View_Json extends Zend_View_Abstract
{
     /**
     * @var string $_charset
     */
    private $_charset = 'utf-8';
    /**
     * @var bool $_pretty
     */
    private $_pretty = false;
    
    public function __construct($options = array())
    {
		if(isset($options['pretty']))
		{
		    $this->_pretty = $options['pretty']; 	    	
	    }
		if(isset($options['charset']))
		{
		    $this->_charset = $options['charset']; 	    	
        }
    }
    
    protected function _script($name)
    {
		return false;
    }
		
    protected function _run()
    {
		$this->tm = round((microtime(true) - $this->tm)*1000);
		if($this->_pretty)
		{
		    $response = Zend_Controller_Front::getInstance()->getResponse();
	        $response->setHeader('Content-type','text/html;charset='.$this->_charset.';');
		    echo $this->_transform($this);		
		}
		else
		{
		    $response = Zend_Controller_Front::getInstance()->getResponse();
		    $response->setHeader('Content-Type', 'application/json;charset='.$this->_charset.';');
	        echo Zend_Json::encode($this);
		}
    }

    private function _transform($data)
    {
        $serializer = new Sa_View_Serializer();
		return $serializer->Serialize($data);
    }
}
?>
