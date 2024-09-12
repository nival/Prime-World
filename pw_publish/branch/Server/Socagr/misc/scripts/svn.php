<?php
//update to HEAD revision(replace to checkout for first time use)
exec ('svn update -rHEAD --username SVN_USERNAME --password SVN_PASSWORD SVN_URL LOCAL_SVN_FILES_PATH > SVN_LOG_FILE');
//write info to log file
echo file_get_contents('LOGFILE');
//synchronization
echo exec ('rsync -lzuogthvr --delete-before --exclude-from=EXCLUDE_FILE LOCAL_MODULE_FILES_PATH WORK_MODULE_PATH > RSYNC_LOG_FILE');
//write info to log file
echo file_get_contents('RSYNC_LOG_FILE');
?>

