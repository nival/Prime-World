<?php
abstract class Common
{
	public $config = null;
	public $params = null;
	public $isTest = false;
	public $ru_db, $us_db;
	public $ruUsers, $usUsers;
	public $ruFriends, $usFriends;
	private $start_ts = 0;

	public $JSON_ERRORS = array(
		JSON_ERROR_DEPTH => "Достигнута максимальная глубина стека",
		JSON_ERROR_STATE_MISMATCH => "Неверный или не корректный JSON",
		JSON_ERROR_CTRL_CHAR => "Ошибка управляющего символа, возможно неверная кодировка",
		JSON_ERROR_SYNTAX => "Синтаксическая ошибка",
		JSON_ERROR_UTF8 => "Некорректные символы UTF-8, возможно неверная кодировка"
	);
    
    public function __construct($config)
	{
		set_include_path(
			implode(PATH_SEPARATOR, array(
				get_include_path(),
		    	$config['path']['library'],
		    	implode(PATH_SEPARATOR, $config['path']['models'])
			)));
		require_once 'Zend/Loader/Autoloader.php';

		if (isset($config['test']) && $config['test'])
		{
			$this->isTest = true;
			print "Test mode is ON\n";
		}

        $dbConfig = $config['db'];
		print "Connectiong mongo: " . $dbConfig['host'].':'.$dbConfig['port'] . "\n";
        $connection = new Mongo($dbConfig['host'].':'.$dbConfig['port'],$dbConfig['options']);
		print "Done\n";
        $this->ru_db = $connection->selectDB($dbConfig['name_ru']); 
		$this->us_db = $connection->selectDB($dbConfig['name_us']); 
		print "DB handlers created\n";

    	$this->setLoader();
        $this->setConfig($config);
		mb_internal_encoding($config['common']['charset']);
		require __DIR__ . '/lib.php';
	}

    public function setLoader() 
    {
        $loader = Zend_Loader_Autoloader::getInstance();
        $loader->setFallbackAutoloader(true)
               ->suppressNotFoundWarnings(false)
               ->registerNamespace('SA_');
    }
    
    public function setConfig($config)
    {
        $this->config = new Zend_Config($config);
        Zend_Registry::set('config', $this->config);
	}

	public function parse_options($shortOptions, $longOptions)
	{
		$params = getopt($shortOptions, $longOptions);	
		if (array_key_exists('h', $params) || array_key_exists('help', $params))
		{
			$this->help(); // it exits pocess
		}
		if (array_key_exists('test', $params))
		{
			$this->isTest = true;
			print "Test mode ON\n";
		}
		$this->params = $params;
	}
    
	function prepare()
	{
		$this->parse_options("h", array("help", "test"));
		$this->ruUsers = new UsersExt($this->ru_db);
		$this->usUsers = new UsersExt($this->us_db);
		$this->ruFriends = new FriendsExt($this->ru_db);
		$this->usFriends = new FriendsExt($this->us_db);
		$this->start_ts = microtime(true);
	}
    
	public function help()
	{
		print "Sorry, help isn't ready yet.\n";
		exit(1);
	}

	public function run()
	{
		$this->prepare();
		$this->perform();
		$this->finalize();
	}

	abstract public function perform();
	abstract public function finalize();

	public function load_json_file($fname)
	{
		if (!file_exists($fname))
		{
			printf("ERROR: file %s does not exist!\n", $fname);
			exit(2);
		}
		$json_data = file_get_contents($fname, "r");
		if (strlen($json_data) == 0)
		{
			print "ERROR! Error reading or empty file!\n";
			exit(2);
		}
		$data = json_decode($json_data, true);
		if ($data == NULL)
		{
			$code = json_last_error();
			$text = isset($this->JSON_ERRORS[$code]) ? $this->JSON_ERRORS[$code] : ("Unknown code " . $code);
			print "ERROR decoding json data: " . $text;
			exit(2);
		}
		return $data;
	}
}

