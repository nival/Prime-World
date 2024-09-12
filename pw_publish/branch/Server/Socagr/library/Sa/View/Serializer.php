<?php
class Sa_View_Serializer
{
    /**
     * @var string
     */
    private $_htmlDoc = null;
    /**
     *  @var boolean
     */
    private $_includePageHead = null;
    
    public function __construct($includePageHead = true)
    {
    	$this->_includePageHead = $includePageHead;
    	if($includePageHead)
    	{
	    	$this->_htmlDoc = '<html><head>
	    		<link href="css/default.css" type="text/css" rel="stylesheet">
	    	<head>
	    	<body>
	    	<div id = "json">';
    	}
    }
    
    public function Serialize($inst)
    {
        $this->_htmlDoc .= '{<ul class = "obj">';
    	if (is_object($inst))
        {  
            $this->SerializeObject($inst);
        }
        elseif (is_array($inst))
        {
            $this->SerializeArray($inst);
        }
        $this->_htmlDoc .= '</ul>}'. ($this->_includePageHead ? '</div></body></html>' : '');
        return $this->_htmlDoc;
    }

    private function SerializeObject($inst)
    {
        $obj = new ReflectionObject($inst);
        $properties = $obj->getProperties();
        foreach ($properties as $prop)
        {
            if (!$prop->isPrivate() && !$prop->isProtected())
            {
               $this->SerializeData($prop->getName(), $prop->getValue($inst));
            }
        }
    }

    private function SerializeArray($array)
    {
       // Check for associative array
       if (!empty($array) && (array_keys($array) !== range(0, count($array) - 1))) 
       {
           // Associative array
	       foreach ($array as $key => $val)
	       {
	           $this->SerializeData($key, $val);
	       }
       } 
       else 
       {
           // Indexed array
           $length = count($array);
           for ($i = 0; $i < $length; $i++) 
           {
               $this->SerializeData(null, $array[$i]);
           }
       }
    }

    private function SerializeData($key, $val)
    {
        if (is_object($val))
        {
            $propNodeName = get_class($val);
            $this->_htmlDoc.= '<li><span class="prop">'.$propNodeName.'</span>:{<ul class="obj">';
            $this->SerializeObject($val, $propNodeName);
            $this->_htmlDoc.= '</ul>}</li>';
        }
        elseif (is_array($val))
        {
            $this->_htmlDoc.= '<li><span class="prop">'.$key.'</span>:{<ul class="obj">';
        	$this->SerializeArray($val, $key);
        	$this->_htmlDoc.= '</ul>}</li>';
        }
        else
        {   
        	if(isset($key))
        	{
        		$this->_htmlDoc.= '<li><span class="prop">'.$key.'</span>: <span class="'.(is_string($val) ? 'string' : 'num').'">'.$val.'</span></li>';
        	}
        	else 
        	{
        		$this->_htmlDoc.= '<li><span class="'.(is_string($val) ? 'string' : 'num').'">'.$val.'</span></li>';	
        	}
        }
    }
}
?>