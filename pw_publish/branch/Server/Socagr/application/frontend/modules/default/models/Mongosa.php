<?php
/**
*/
class Mongosa
{
    private static $db = null;
    private function __construct() {}
    protected function __clone() {}
    private function __wakeup() {}

    static public function getInstance()
    {
        if (!self::$db)
        {
            $dbConfig = Zend_Registry::get('config')->db;
            $options = Zend_Registry::get('config')->db->options;
            // string $server = "mongodb://localhost:27017" [, array $options = array("connect" => TRUE) ...
            $connection = new MongoClient($dbConfig->host.':'.$dbConfig->port, $dbConfig->options->toArray());
            self::$db = $connection->selectDB($dbConfig->name);
        }
        return self::$db;
    }
}