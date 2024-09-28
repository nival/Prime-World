--TEST--
Check for gearman  presence
--SKIPIF--
<?php if (!extension_loaded("gearman")) print "skip"; ?>
--FILE--
<?php 
echo "gearman extension is available";
?>
--EXPECT--
gearman extension is available
