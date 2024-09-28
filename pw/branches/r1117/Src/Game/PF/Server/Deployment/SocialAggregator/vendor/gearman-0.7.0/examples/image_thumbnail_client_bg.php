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

for ($x=0; $x<20; $x++)
{
    $data[$x]['src']= $_SERVER['argv'][1];
    $data[$x]['dest']= "$x.jpg";
    $data[$x]['x']= ((80+1)*($x+1));
    $data[$x]['y']= NULL;
}

/* fire off each job */
foreach ($data as $img)
{
    $job_handle[]= $gmc->doBackground("shrink_image", serialize($img));
    if ($gmc->returnCode() != GEARMAN_SUCCESS)
    {
        echo "ERROR RET: " . $gmc->error() . "\n";
        exit;
    }
}

echo "DONE\n";
