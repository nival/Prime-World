<?php
// Path to the directory, where database dump files are placed
$DATA_DIR = "./dump/us";

// Skip (true) or load (false) sn_friends collection. This collection 
// is huge and usually unnecessary for test purposes, and 99% of it's
// data a completly useless.
$SKIP_SN_FRIENDS = true;

// Remove (if 'false' - rename and than rename back) sn_friends.bson file
// from $DATA_DIR before loading all data into DB.
$REMOVE_SN_FRIENDS = false;

// Check, if gearman-workers are running, and stop them
$STOP_WORKERS = true;
// Start them again after data is loaded
$START_WORKERS = true;

if ($START_WORKERS && !$STOP_WORKERS)
{
    $START_WORKERS = false; // Start only if they was stopped
}
