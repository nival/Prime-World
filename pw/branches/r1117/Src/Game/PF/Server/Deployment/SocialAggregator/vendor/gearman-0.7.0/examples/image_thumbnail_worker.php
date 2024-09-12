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

echo "Starting Thumbnail creator\n";

$gmw= new GearmanWorker();
$gmw->addServer();

# optional config paramsj
$args;

$gmw->addFunction("shrink_image", "resize_image", $args);

while($gmw->work())
{
    switch ($gmw->returnCode())
    {
        case GEARMAN_SUCCESS:
            break;
        default:
            echo "ERROR RET: " . $gmc->returnCode() . "\n";
            exit;
    }
}
echo "DONE\n";


/* simple function to resize an image
 * Requires the Imagick extension */
function resize_image($job, $args)
{
    $wrk= $job->workload();
    $data= unserialize($wrk);
    if (! $data['src'] || ! $data['dest'] || ! $data['x']) 
    { $job->sendFail(); print_r($data); return; }
    echo $job->handle() . " - creating: $data[dest] x:$data[x] y:$data[y]\n";
    $im= new Imagick();
    $im->readimage($data['src']);
    $im->thumbnailImage($data['x'], $data['y']);
    $im->writeImage($data['dest']);
    $im->destroy();
    $job->sendStatus(1, 1);

    return $data['dest'];
}
?>
