<?php
/** Zend_Controller_Router_Route_Abstract */
require_once 'Zend/Controller/Router/Route/Abstract.php';

class Sa_Controller_Router_Route_Params extends Zend_Controller_Router_Route_Abstract
{

    protected $_route = null;
    protected $_defaults = array();
    protected $_params = array();	

    public function getVersion() {
        return 1;
    }
    
    /**
     * Instantiates route based on passed Zend_Config structure
     *
     * @param Zend_Config $config Configuration object
     */
    public static function getInstance(Zend_Config $config)
    {
        $defs = ($config->defaults instanceof Zend_Config) ? $config->defaults->toArray() : array();
        return new self($config->route, $defs);
    }

    /**
     * Prepares the route for mapping.
     *
     * @param string $route Map used to match with later submitted URL path
     * @param array $defaults Defaults for map variables with keys as variable names
     */
    public function __construct($route, $defaults = array(), $params = array())
    {
        $this->_route = trim($route, '/');
        $this->_defaults = (array) $defaults;
	$this->_params = (array) $params;
    }

    /**
     * Matches a user submitted path with a previously defined route.
     * Assigns and returns an array of defaults on a successful match.
     *
     * @param string $path Path used to match against this routing map
     * @return array|false An array of assigned values or a false on a mismatch
     */
    public function match($path, $partial = false)
    {
	if ($partial) {
            if (substr($path, 0, strlen($this->_route)) === $this->_route) {
                $this->setMatchedPath($this->_route);
                return $this->_defaults;
            }
        } else {
            if (trim($path, '/') == $this->_route) {
		$queryParams = (array)$_GET;		
		if(count($this->_params) > 0)
		{
		     foreach($this->_params as $param => $paramValue)
		     {
			if(!isset($queryParams[$param]) || $queryParams[$param] != $paramValue)
			{
			  return false;	
			}	
		     }			    	    	
                }
		return $this->_defaults;
            }
        }
        
        return false;
    }

    /**
     * Assembles a URL path defined by this route
     *
     * @param array $data An array of variable and value pairs used as parameters
     * @return string Route path with user submitted parameters
     */
    public function assemble($data = array(), $reset = false, $encode = false)
    {
        return $this->_route;
    }

    /**
     * Return a single parameter of route's defaults
     *
     * @param string $name Array key of the parameter
     * @return string Previously set default
     */
    public function getDefault($name) {
        if (isset($this->_defaults[$name])) {
            return $this->_defaults[$name];
        }
        return null;
    }

    /**
     * Return an array of defaults
     *
     * @return array Route defaults
     */
    public function getDefaults() {
        return $this->_defaults;
    }

}
