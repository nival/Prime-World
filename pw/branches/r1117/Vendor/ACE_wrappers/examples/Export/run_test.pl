eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id: run_test.pl 80826 2008-03-04 14:51:23Z wotte $
# -*- perl -*-

use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::Run_Test;

$TEST = new PerlACE::Process ("test");

$status = $TEST->SpawnWaitKill (20);

$status = 1 if ($status < 0);

exit $status;
