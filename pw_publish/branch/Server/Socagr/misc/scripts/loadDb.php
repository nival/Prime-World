<?php

if ($argc >= 2 && ($argv[1] == '-?' || $argv[1] == '-h' || $argv[1] == '--help')) 
{
    echo "USAGE:\n";
    echo "\tphp $argv[0] [DATA_FILES_PATH]\n\n";
    echo "Where DATA_FILES_PATH is a path where mongo dump files are placed.\n";
    echo "If not specified, DATA_FILES_PATH is taken from loadDb_cfg.php\n";
    exit(1);
}

require "loadDb_cfg.php";
$app = realpath(__DIR__ . '/../../application/');
$wrkpath = $app . "/background/workers";
require  $app . '/frontend/settings/config.php';
$dbConfig = $config['db'];


$data_dir = getDataDir();

$workers = stopWorkers();

if ($SKIP_SN_FRIENDS)
{
    $sn_fname = $data_dir . '/sn_friends.bson';
    if (file_exists($sn_fname))
    {
        echo "The sn_friends collection will be skipped.\n";
        if ($REMOVE_SN_FRIENDS)
        {
            echo "Removing $sn_fname\n";
            if (!unlink($sn_fname))
            {
                $err = error_get_last();
                echo "Error: " . $err['message'] . "\n";
                exit(1);
                //TODO научить при ошибке загружать пофайлово
            }
        }
        else
        {
            $sn_new_fname = $data_dir . '/.sn_friends.bson';
            echo "Renaming $sn_fname => $sn_new_fname\n";
            if (!rename($sn_fname, $sn_new_fname))
            {
                $err = error_get_last();
                echo "Error renaming: " . $err['message'] . "\n";
                exit(1);
                //TODO научить при ошибке загружать пофайлово
            }
        }
    }
    else
    {
        $SKIP_SN_FRIENDS = false; // чтобы не дёргаться на этот счёт в конце
    }
}

try 
{
    perform();
    #echo "Skipping main perform....\n";
} 
catch (Exception $e)
{
    echo "Data loading FAILED: " . $e->getMessage() . "\n";
} 

if ($SKIP_SN_FRIENDS && !$REMOVE_SN_FRIENDS)
{
    echo "Renaming back $sn_fname\n";
    if (!rename($sn_new_fname, $sn_fname))
    {
        $err = error_get_last();
        echo "Error renaming back: " . $err['message'] . "\n";
        echo "(Remember: $sn_fname was renamed to $sn_new_fname\n";
        exit(1);
        //TODO научить при ошибке загружать пофайлово
    }
}

if ($workers && $START_WORKERS)
{
    startWorkers();
}

###########################################

function getDataDir()
{
    global $argc, $argv, $DATA_DIR;
    $data_dir = $argc > 1 ? $argv[1] : $DATA_DIR;
    if (!file_exists($data_dir))
    {
        echo "Path $data_dir doesn't exist!\n";
        exit(1);
    }
    if (!is_dir($data_dir))
    {
        echo "$data_dir isn't a directory!\n";
        exit(1);
    }
    echo "Using dumps from $data_dir\n";
    return $data_dir;
}


function checkWorkers()
{
    $out = array();
    $retcode = 0;
    global $wrkpath;
    exec("ps x|grep 'php $wrkpath'|grep Worker.php|grep -v grep", $out, $retcode);
    #print implode("\n", $out);
    return $retcode == 0;
}

function stopWorkers()
{
    $w = checkWorkers();
    if ($w)
    {
        global $STOP_WORKERS;
        if ($STOP_WORKERS)
        {
            echo "Stopping workers...\n";
            global $app;
            exec("php $app/background/stopWorkers.php");
            sleep(1);
            if (checkWorkers())
            {
                echo "Can't stop workers! You should check it manually and run me again.\n";
                exit(1);
            }
            return true;
        }
        else
        {
            echo "Workers were run and \$STOP_WORKERS=false! Set \$STOP_WORKERS=true for stopping workers.\n";
            exit(1);
        }
    }
    return false;
}

function startWorkers()
{
    echo "Starting workers...\n";
    global $app;
    exec("php $app/background/startWorkers.php");
    sleep(1);
    if (!checkWorkers())
    {
        echo "Can't restart workers! You should start them manually.\n";
    }
}

function perform()
{
    global $dbConfig, $data_dir;
    echo "Using mongo DB " . $dbConfig['name'] . " at " . $dbConfig['host'].':'.$dbConfig['port'] . "\n";
    $host = "--host " . escapeshellarg($dbConfig['host']) . " --port " . escapeshellarg($dbConfig['port']);
    $retcode = 0;

    // dropping old db content
    $cmd = "mongo " . $host . " --eval 'db.dropDatabase();' " . escapeshellarg($dbConfig['name']);
    echo "Rub: $cmd\n";
    system($cmd, $retcode);
    if ($retcode)
    {
        throw new Exception("Mongo call returns $retcode.");
    }

    // loading data
    $cmd = "mongorestore " . $host . " --db " . escapeshellarg($dbConfig['name']) . " --drop " . escapeshellarg($data_dir);
    echo "Run: $cmd\n";
    system($cmd, $retcode);
    if ($retcode)
    {
        throw new Exception("Mongorestore call returns $retcode.");
    }
    echo "Checking indexes\n";
    system("php checkIndex.php");
}
