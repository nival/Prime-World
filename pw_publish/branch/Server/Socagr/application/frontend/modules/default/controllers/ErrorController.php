<?php
class ErrorController extends Zend_Controller_Action
{
    public function errorAction()
    {
    	$errors = $this->_getParam('error_handler');
        if ($errors)
        {
        	$this->view->error = 1;
	    	$this->view->message = 'Application error.';
	    	$config = Zend_Registry::get('config');
	    	if($config->debug)
	    	{
            	$this->view->env = $this->getInvokeArg('env');
            	$this->view->exception = array(
                	'message' => $errors->exception->getMessage(),
                	'trace-as-string' => $errors->exception->getTraceAsString(),
            	);
            	$this->view->request = $errors->request->getParams();
	    	}
        }
		else
		{
		    $this->view->error = 2;
		    $this->view->message = 'Invalid action specified.';
		}
    }
}
?>
