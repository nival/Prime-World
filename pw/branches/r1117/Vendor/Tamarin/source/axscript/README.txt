This is the readme for axtam - Active Scripting implemented using Tamarin.
--------------------------------------------------------------------------

This is a README for the Tamarin source code and is focussed on building
and testing Tamarin.  Binary installations of Tamarin install 
README.hta - please see that file for information targetted at *using* 
Tamarin.

This directory is a functioning ActiveScript engine using Tamarin.  With some 
limitations, it works with Internet Explorer and the Windows Script Host.

Building
---------

* Build the standard tamarim 'avmplus' project.  This will create the core
  tamarin static libraries used by axtam.

* Load vc8/axtam.dsp into Microsoft Visual Studio 2005 - there is no support 
  for earlier versions.  Select the same configuration you used for avmplus.

* Build it - a custom build step will also register the engine.  Only debug 
  builds work - release builds fail in strange ways.

After this, engines named 'application/ecmascript;version=4' and 
'application/javascript;version=2' are available - they are currently 
identical.  Note that no file extension is currently registered for this 
engine, so the engine name will need to be explicitly specified.

To create a binary
------------------

The NSIS installer is used - if you have installed the mozilla build tools,
then you have NSIS available.  The current binary is built using the command:

  %MOZ_BUILD_TOOLS%\nsis-2.33u\makensisu.exe axtam.nsi

which will create setup-axtam-YYYYMMDD.exe

Test it
--------

See README.txt in the test directory.

Contact Us, Bugs, etc
----------------------

The mailing list at https://mail.mozilla.org/listinfo/tamarin-devel is 
currrently used for all Tamarin related traffic, including this AXScript
engine.  If you wish to report a bug or submit a patch, please use Bugzilla at
https://bugzilla.mozilla.org/enter_bug.cgi?product=Tamarin&component=ScreamingMonkey
