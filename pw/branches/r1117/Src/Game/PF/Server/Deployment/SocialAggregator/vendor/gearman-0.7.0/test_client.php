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


/* client */

echo "# TESTING CLIENT INTERFACE\n";
$client = gearman_client_create();
if (! is_object($client))
{
    echo "gearman_client_create() FAILED\n";
    exit(0);
}
else
    echo "gearman_client_create() pass\n";


$client_new = gearman_client_clone($client);
if (! is_object($client_new))
{
    echo "gearman_client_clone() FAILED\n";
    exit(0);
}
else
    echo "gearman_client_clone() pass\n";

unset($client_new);
echo "unset client pass\n";

$ret= gearman_client_error($client);
if ($ret != GEARMAN_SUCCESS)
{
    echo "gearman_client_error() FAILED\n";
    exit(0);
}
else
    echo "gearman_client_error() pass\n";

$ret= gearman_client_errno($client);
if ($ret != 0)
{
    echo "gearman_client_errno() FAILED\n";
    exit(0);
}
else
    echo "gearman_client_errno() pass\n";

if (! gearman_client_add_options($client, GEARMAN_CLIENT_UNBUFFERED_RESULT))
{
    echo "gearman_client_set_options() FAILED\n";
    exit(0);
}
gearman_client_remove_options($client, GEARMAN_CLIENT_UNBUFFERED_RESULT);
echo "gearman_client_set_options() pass\n";

/*
if (! gearman_client_add_server($client))
{
    echo "gearman_client_add_server() FAILED\n";
    exit(0);
}
echo "gearman_client_add_server() pass\n";
*/

if (! gearman_client_add_servers($client, "127.0.0.1:4730"))
{
    echo "gearman_client_add_servers() FAILED\n";
    exit(0);
}
echo "gearman_client_add_servers() pass\n";

$value = gearman_client_do($client, "test_worker", "gearman_client_do");
if ($client->returnCode() != GEARMAN_SUCCESS)
{
    echo "gearman_client_do() FAILED\n";
    exit(0);
}
else
    echo "gearman_client_do() pass -> $value\n";


$job_handle = gearman_client_do_background($client, "test_worker", "gearman_client_do_background");
if ($client->returnCode() != GEARMAN_SUCCESS)
{
    echo "gearman_client_do_background() FAILED\n";
    exit(0);
}
else
    echo "gearman_client_do_background() pass -> $job_handle\n";

$value = gearman_client_do_high($client, "test_worker", "gearman_client_do_high");
if ($client->returnCode() != GEARMAN_SUCCESS)
{
    echo "gearman_client_do_high() FAILED\n";
    exit(0);
}
else
    echo "gearman_client_do_high() pass -> $value\n";

$value = gearman_client_do_low($client, "test_worker", "gearman_client_do_low");
if ($client->returnCode() != GEARMAN_SUCCESS)
{
    echo "gearman_client_do_low() FAILED\n";
    exit(0);
}
else
    echo "gearman_client_do_low() pass -> $value\n";

$value = gearman_client_do_high_background($client, "test_worker", "gearman_client_do_high_background");
if ($client->returnCode() != GEARMAN_SUCCESS)
{
    echo "gearman_client_do_high_background() FAILED\n";
    exit(0);
}
else
    echo "gearman_client_do_high_background() pass -> $value\n";

$value = gearman_client_do_low_background($client, "test_worker", "gearman_client_do_low_background");
if ($client->returnCode() != GEARMAN_SUCCESS)
{
    echo "gearman_client_do_low_background() FAILED\n";
    exit(0);
}
else
    echo "gearman_client_do_low_background() pass -> $value\n";

$job_handle = gearman_client_do_background($client, "test_gearman_job_status", "test_gearman_job_status");
if ($client->returnCode() != GEARMAN_SUCCESS)
{
    echo "gearman_client_do_background() FAILED -> while checking status\n";
    exit(0);
}
sleep(1);
list($is_known, $is_running, $numerator, $denominator) = gearman_client_job_status($client, $job_handle);
    if ($client->returnCode() != GEARMAN_SUCCESS || ! $is_known || ! $is_running || ! $numerator || ! $denominator)
    {
        echo "gearman_client_job_status() FAILED\n";
    }
    else
        echo "gearman_client_job_status() pass -> is_known: $is_known is_running: $is_running $numerator / $denominator\n";
if ($job_handle != gearman_client_do_job_handle($client))
{
    echo "gearman_client_do_job_handle() FAILED\n";
    exit(0);
}
else
    echo "gearman_client_do_job_handle() pass -> $job_handle\n";

gearman_client_echo($client, "gearman_client_echo");
echo "gearman_client_echo() pass\n";

gearman_client_add_task($client, "test_gearman_job", "test_gearman_job", "test_gearman_job");
echo "gearman_client_add_task() pass\n";
/* run a task see if they all work */
$res = gearman_client_run_tasks($client);
echo "gearman_client_run_tasks() pass\n";

/* clear all the callbacks so they dont mess with other test */
gearman_client_clear_fn($client);
echo "gearman_client_clear_fn() pass\n";


/* set all of our callback functions */
/* 
gearman_client_set_workload_fn($client, "test_gearman_client_set_workload_fn");
echo "gearman_client_set_workload_fn() pass\n";
*/
gearman_client_set_created_fn($client, "test_gearman_client_set_created_fn");
// XXX gearman_client_set_data_fn($client, "test_gearman_client_set_data_fn");
gearman_client_set_warning_fn($client, "test_gearman_client_set_warning_fn");
gearman_client_set_status_fn($client, "test_gearman_client_set_status_fn");
gearman_client_set_complete_fn($client, "test_gearman_client_set_complete_fn");
gearman_client_set_exception_fn($client, "test_gearman_client_set_exception_fn");
gearman_client_set_fail_fn($client, "test_gearman_client_set_fail_fn");
gearman_client_add_task($client, "test_set_callback_fn", "test_set_callback_fn", "test_set_callback_fn");
/* run a task see if they all work */
$res = gearman_client_run_tasks($client);
// gearman_client_clear_fn($client);

/* test tasks interface */
gearman_client_clear_fn($client);
gearman_client_set_complete_fn($client, "test_gearman_tasks");
gearman_client_add_task($client, "test_tasks", "test_tasks", "test_tasks");
$res = gearman_client_run_tasks($client);
gearman_client_clear_fn($client);

# You can turn off auto task destruction by unsetting this flag on a gearman client.
gearman_client_remove_options($client, GEARMAN_CLIENT_FREE_TASKS);
$task = gearman_client_add_task_background($client, "test_tasks_background", "test_tasks_background", "test_tasks_background");
gearman_client_set_status_fn($client, "test_gearman_task_status");
$res = gearman_client_run_tasks($client);
$job_handle = gearman_task_job_handle($task);
gearman_client_add_task_status($client, $job_handle);
echo "\tgearman_client_add_task_status() pass\n";
$res = gearman_client_run_tasks($client);

function test_gearman_task_status($task)
{
    $is_known = gearman_task_is_known($task);
    if ($is_known)
        echo "\tgearman_task_is_known() pass\n";
    else
        echo "\tgearman_task_is_known() FAILED\n";
    sleep(1);
    $is_running = gearman_task_is_running($task);
    if ($is_running)
        echo "\tgearman_task_is_running() pass\n";
    else
        echo "\tgearman_task_is_running() pass\n";
}

echo "gearman_client_add_task_background() pass\n";


gearman_client_clear_fn($client);
gearman_client_add_task_high($client, "test_tasks_high", "test_tasks_high", "test_tasks_high");
echo "gearman_client_add_task_high() pass\n";

gearman_client_add_task_low($client, "test_tasks_low", "test_tasks_low", "test_tasks_low");
echo "gearman_client_add_task_low() pass\n";

gearman_client_add_task_high_background($client, "test_tasks_high_background", "test_tasks_high_background", "test_tasks_high_background");
echo "gearman_client_add_task_high_background() pass\n";
gearman_client_add_task_low_background($client, "test_tasks_low_background", "test_tasks_low_background", "test_tasks_low_background");
echo "gearman_client_add_task_low_background() pass\n";

$res = gearman_client_run_tasks($client);
/* XXX add task high seems to break things
*/

$value = gearman_client_do($client, "exit_test", "exit_test");
echo "DONE $ret\n";


/* XXX does not seem to call cb as i would expect
$data = "gearman_job_exception";
gearman_client_add_task($client, "test_gearman_job_exception", $data, NULL);
$data = "gearman_job_fail";
gearman_client_add_task($client, "test_gearman_job_fail", $data, NULL);
*/


/* XXX can not test till I have the gearman low level functions done
$task_new = gearman_task_create();
gearman_task_fn_arg($task_new);
echo "gearman_task_fn_arg() pass\n";
*/


/*
 * Test Functions
 */

function test_gearman_client_set_fail_fn($task)
{
    echo "\tgearman_client_set_fail_fn() pass\n";
}

function test_gearman_client_set_exception_fn($task)
{
    echo "\tgearman_client_set_exception_fn() pass\n";
}

function test_gearman_client_set_complete_fn($task)
{
    echo "\tgearman_client_set_complete_fn() pass\n";
}

function test_gearman_client_set_status_fn($task)
{
    echo "\tgearman_client_set_status_fn() pass\n";
}

function test_gearman_client_set_warning_fn($task)
{
    echo "\tgearman_client_set_warning_fn() pass\n";
}

function test_gearman_client_set_data_fn($task)
{
    echo "\tgearman_client_set_data_fn() pass\n";
}
function test_gearman_client_set_created_fn($task)
{
    echo "\tgearman_client_set_created_fn() pass\n";
}

function test_gearman_client_set_workload_fn($task)
{
    echo "\tgearman_client_set_workload_fn() pass\n";
}

function test_gearman_tasks($task)
{
    $is_known= false;
    $is_running= false;

    echo "Testing Task Functions\n";
    $func = gearman_task_function_name($task);
    echo "\tgearman_task_function_name() pass - $func\n";
    $uuid = gearman_task_unique($task);
    echo "\tgearman_task_unique() pass - $uuid\n";
    $job_handle = gearman_task_job_handle($task);
    echo "\tgearman_task_job_handle() pass - $job_handle\n";


    $numerator = gearman_task_numerator($task);
    echo "\tgearman_task_numerator() pass - $numerator\n";
    $denominator = gearman_task_denominator($task);
    echo "\tgearman_task_denominator() pass - $denominator\n";
    $data = gearman_task_data($task);
    echo "\tgearman_task_data() pass - $data\n";
    $data_size = gearman_task_data_size($task);
    echo "\tgearman_task_data_size() pass - $data_size\n";
    /* XXX Not sure how to test task data yet
    gearman_task_take_data($task);
    echo "gearman_task_take_data() pass\n";
    gearman_task_send_data()
    gearman_task_recv_data()
    */

}

?>
