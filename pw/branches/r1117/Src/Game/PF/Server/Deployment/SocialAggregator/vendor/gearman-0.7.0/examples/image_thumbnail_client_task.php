<?php
/*
 * Gearman PHP Extension
 *
 * Copyright (C) 2008 James M. Luedke (jluedke@jamesluedke.com)
 *                           Eric Day (eday@oddments.org)
 * All rights reserved.
 *
 * Use and distribution licensed under the PHP license.  See
 * the LICENSE file in this directory for full text.
 */

/* create our object */
$gmc= new GearmanClient();

/* add the default server */
$gmc->addServer();

/* set a few callbacks */
$gmc->setCreatedCallback("thumb_created");
$gmc->setCompleteCallback("thumb_complete");
$gmc->setFailCallback("thumb_fail");

for ($x= 0; $x<20; $x++)
{
    $data[$x]['src']= $_SERVER['argv'][1];
    $data[$x]['dest']= "$x.jpg";
    $data[$x]['x']= ((80+1)*($x+1));
    $data[$x]['y']= NULL;
}

/* fire off each job */
foreach ($data as $img)
{
    /* NOTE: if you want to asynchronously queue jobs use
    ** $task= $gmc->add_task_background("shrink_image", serialize($img));
    ** however keep in mind that your complete callback will not get called */
    if (! $gmc->addTask("shrink_image", serialize($img)))
    {
        echo "ERROR RET: " . $gmc->error() . "\n";
        exit;
    }
}

if (! $gmc->runTasks())
{
    echo "ERROR RET:" . $gmc->error() . "\n";
    exit;
}
echo "DONE\n";
exit;

function thumb_created($task)
{
    echo "CREATED -> job: " . $task->jobHandle() . "\n";
}

function thumb_complete($task)
{
    echo "COMPLETE -> job: " . $task->jobHandle() . 
         " new_file: " . $task->data() . "\n";
}

function thumb_fail($task)
{
    echo "FAIL job: " . $task->jobHandle() . "\n";
}

?>
