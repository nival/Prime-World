SMTESTDIR=../../../../mtn/com.mozilla.es4.smlnj/tests/spidermonkey/
DIR=../../test/acceptance

$DIR/runtests.py -v --ext=.js --esc --escbin=../bin/ $SMTESTDIR
