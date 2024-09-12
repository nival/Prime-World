<?php
$gmc= new GearmanClient();
$gmc->addServer();

$gmc->setCreatedCallback("reverse_created");
$gmc->setStatusCallback("reverse_status");
$gmc->setCompleteCallback("reverse_complete");
$gmc->setFailCallback("reverse_fail");
$task= $gmc->addTask("reverse", "this is a test", NULL);

if (! $gmc->runTasks())
{
    echo "ERROR " . $gmc->error() . "\n";
    exit;
}
echo "DONE\n";

function reverse_created($task)
{
    echo "CREATED: " . $task->jobHandle() . "\n";
}

function reverse_status($task)
{
    echo "STATUS: " . $task->jobHandle() . " - " . $task->taskNumerator() . 
         "/" . $task->taskDenominator() . "\n";
}

function reverse_complete($task)
{
    echo "COMPLETE: " . $task->jobHandle() . "\n";
}

function reverse_fail($task)
{
    echo "FAILED: " . $task->jobHandle() . "\n";
}
?>
