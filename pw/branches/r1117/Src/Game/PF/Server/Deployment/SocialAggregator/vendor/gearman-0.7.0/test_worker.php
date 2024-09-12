<?php
/*
 * Gearman PHP Extension
 *
 * Copyright (C) 2008 James M. Luedke <contact@jamesluedke.com>,
 *                    Eric Day <eday@oddments.org>
 * All rights reserved.
 *
 * Use and distribution licensed under the PHP license.  See
 * the LICENSE file in this directory for full text.
 */

 /* worker */
$worker = gearman_worker_create();
if (! is_object($worker))
{
    echo "gearman_worker_create() FAILED\n";
    exit(0);
}
else
    echo "gearman_worker_create() pass\n";

/*
if(! gearman_worker_add_server($worker))
{
    echo "gearman_worker_add_server() FAILED\n";
    exit(0);
}
echo "gearman_worker_add_server() pass\n";
*/

if(! gearman_worker_add_servers($worker, "127.0.0.1:4730"))
{
    echo "gearman_worker_add_servers() FAILED\n";
    exit(0);
}
echo "gearman_worker_add_servers() pass\n";


/*
$worker_new = gearman_worker_clone($worker);
if (! is_object($worker_new))
{
    echo "gearman_worker_clone() FAILED\n";
    exit(0);
}
else
    echo "gearman_worker_clone() pass\n";

unset($worker_new);
echo "unset worker pass\n";

$ret = gearman_worker_error($worker);
if ($ret != GEARMAN_SUCCESS)
{
    echo "gearman_worker_error() FAILED\n";
    exit(0);
}
else
    echo "gearman_worker_error() pass\n";

if(! gearman_worker_set_options($worker, GEARMAN_WORKER_NON_BLOCKING, 1))
{
    echo "gearman_worker_set_options() FAILED\n";
    exit(0);
}
gearman_worker_set_options($worker, GEARMAN_WORKER_NON_BLOCKING, 0);
echo "gearman_worker_set_options() pass\n";

if(! gearman_worker_register($worker, "test_one"))
{
    echo "gearman_worker_register() FAILED\n";
    exit(0);
}
gearman_worker_register($worker, "test_two");
gearman_worker_register($worker, "test_three");
echo "gearman_worker_register() pass\n";

if(! gearman_worker_unregister($worker, "test_three"))
{
    echo "gearman_worker_unregister() FAILED\n";
    exit(0);
}
echo "gearman_worker_unregister() pass\n";

if(! gearman_worker_unregister_all($worker))
{
    echo "gearman_worker_unregister_all() FAILED\n";
    exit(0);
}
echo "gearman_worker_unregister_all() pass\n";

gearman_worker_echo($worker, "gearman_worker_echo");
echo "gearman_worker_echo() pass\n";
*/

if (! gearman_worker_add_function($worker, "test_worker", "test_worker", "test_worker"))
{
    echo "gearman_worker_add_function() FAILED\n";
    exit(0);
}
gearman_worker_add_function($worker, "exit_test", "exit_test", "exit_test");

gearman_worker_add_function($worker, "test_gearman_job", "test_gearman_job", "test_gearman_job");
gearman_worker_add_function($worker, "test_set_callback_fn", "test_set_callback_fn", "test_set_callback_fn");
gearman_worker_add_function($worker, "test_tasks", "test_tasks", "test_tasks");
gearman_worker_add_function($worker, "test_tasks_background", "test_tasks_background", "test_tasks_background");
gearman_worker_add_function($worker, "test_tasks_high", "test_tasks_high", "test_tasks_high");
gearman_worker_add_function($worker, "test_tasks_low", "test_tasks_low", "test_tasks_low");
gearman_worker_add_function($worker, "test_tasks_high_background", "test_tasks_high_background", "test_tasks_high_background");
gearman_worker_add_function($worker, "test_tasks_low_background", "test_tasks_low_background", "test_tasks_low_background");
gearman_worker_add_function($worker, "test_gearman_job_status", "test_gearman_job_status", "test_status");
gearman_worker_add_function($worker, "test_gearman_job_complete", "test_gearman_job_complete", "test_complete");
gearman_worker_add_function($worker, "test_gearman_job_exception", "test_gearman_job_exception", "test_exception");
gearman_worker_add_function($worker, "test_gearman_job_fail", "test_gearman_job_fail", "test_fail");
echo "gearman_worker_add_function() pass\n";

echo "Starting Worker...\n";
$numb_test = 5;
$do_loop= true;
while ($do_loop)
{
    if (! gearman_worker_work($worker))
    {
        echo "gearman_worker_work: FAILED\n";
        exit(0);
    }
}
echo "gearman_worker_work() pass\n";


/*
 * Job Functions
 */

/* XXX finish this up once the gearman objects are added
$job = gearman_job_create();
if (! is_object($job))
{
    echo "gearman_job_create() FAILED\n";
    exit(0);
}
else
    echo "gearman_job_create() pass\n";

$data = "job_data";
gearman_job_data($job, $data);
echo "gearman_job_data() pass\n";

gearman_job_warning($job, "gearman_job_warning");
echo "gearman_job_warning() pass\n";

gearman_job_status($job, 1, 2);
gearman_job_status($job, 2, 2);
echo "gearman_job_status() pass\n";

gearman_job_complete($job, "gearman_job_complete");
echo "gearman_job_complete() pass\n";

gearman_job_exception($job, "gearman_job_exception");
echo "gearman_job_exception() pass\n";

geaman_job_fail($job, "gearman_job_fail");
echo "gearman_job_fail() pass\n";

$job_handle= gearman_job_handle($job);
if (! is_string($job_handle))
{
    echo "gearman_job_handle() FAILED\n";
    exit(0);
}
else
    echo "gearman_job_handle() pass\n";

*/

/*
 * Test Functions
 */

function exit_test($job, $data)
{
    global $do_loop;
    echo "Done Working\n";
    $do_loop=false;
}

function test_gearman_job_fail($job, $data)
{
    gearman_job_fail($job);
    echo "gearman_job_fail() pass\n";
}

function test_gearman_job_exception($job, $data)
{
    gearman_job_exception($job, "test_exception");
    echo "gearman_job_exception() pass\n";
}

function test_gearman_job_complete($job, $data)
{
    gearman_job_complete($job, "test_complete");
    echo "gearman_job_complete() pass\n";
}

function test_gearman_job_status($job, $data)
{
    gearman_job_send_data($job, "test data");
    gearman_job_send_status($job, 1, 4);
    sleep(1);
    gearman_job_send_status($job, 2, 4);
    sleep(1);
    gearman_job_send_status($job, 3, 4);
    sleep(1);
    gearman_job_send_status($job, 4, 4);
    sleep(1);
    echo "gearman_send_job_status() pass\n";
}

function test_worker($job, $data=NULL)
{
    return $job->workload();
}

function test_gearman_job($job, $data)
{
    echo "Testing Job Functions\n";
    $job_handle = gearman_job_handle($job);
    echo "\tgearman_job_handle() pass - $job_handle\n";
    $workload = gearman_job_workload($job);
    echo "\tgearman_job_workload() pass - $workload\n";
    $workload_size = gearman_job_workload_size($job);
    echo "\tgearman_job_workload_size() pass - $workload_size\n";
    $fname = gearman_job_function_name($job);
    echo "\tgearman_job_function_name() pass - $fname\n";
    return "test_set_callback_fn";
}

function test_set_callback_fn($job, $data)
{
    gearman_job_send_status($job, 1, 1);
    echo "\tgearman_job_send_status() pass\n";
    sleep(1);
    gearman_job_send_warning($job, "test_set_callback_fn warning");
    echo "\tgearman_job_send_warning() pass\n";
    sleep(1);
    gearman_job_send_exception($job, "test_set_callback_fn exception");
    echo "\tgearman_job_send_exception() pass\n";
    sleep(1);
    /* $job->set_return(GEARMAN_WORK_FAIL); == $job->fail() == */
    if(! gearman_job_send_fail($job))
        echo "\tgearman_job_send_fail() FAILED\n";
    else
        echo "\tgearman_job_send_fail() pass\n";
    sleep(1);
}

function test_tasks($job, $data)
{
    $job->sendData("foobar");
    gearman_job_send_status($job, 1, 1);
    sleep(2);
    return "test_tasks";
}

function test_tasks_background($job, $data)
{
    echo "\ttest_tasks_background() pass\n";
    gearman_job_send_status($job, 1, 2);
    sleep(4);
    gearman_job_send_status($job, 2, 2);
    return "done";
}

function test_tasks_high($job, $data)
{
    echo "\ttest_task_high() pass\n";
    sleep(1);
}

function test_tasks_low($job, $data)
{
    echo "\ttest_task_low() pass\n";
    sleep(1);
}

function test_tasks_high_background($job, $data)
{
    echo "\ttest_task_high_background() pass\n";
    sleep(1);
}

function test_tasks_low_background($job, $data)
{
    echo "\ttest_task_low_background() pass\n";
    sleep(1);
}


?>
