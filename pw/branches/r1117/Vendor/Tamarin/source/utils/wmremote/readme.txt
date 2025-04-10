/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is [Open Source Virtual Machine].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2007-2008
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Adobe AS3 Team
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

Compiling Utilities:
* Add the following directory to the  VC++ Directories (Tools->Options->Projects and Solutions)
    
    Platform:               Win32
    Show Directories For:   Include files
    Directory:              C:\Program Files\Windows Mobile 6 SDK\Active

    Platform:               Win32
    Show Directories For:   Library files
    Directory:              C:\Program Files\Windows Mobile 6 SDK\Activesync\Lib

    Platform:               Windows Mobile 6 Profession SDK
    Show Directories For:   Include files
    Directory:              C:\Program Files\Windows Mobile 6 SDK\Active

    Platform:               Windows Mobile 6 Profession SDK
    Show Directories For:   Library files
    Directory:              C:\Program Files\Windows Mobile 6 SDK\Activesync\Lib



Unlocking the Device:
* Install the Microsoft Security Configuration Manager application 
http://www.microsoft.com/downloads/details.aspx?FamilyID=7E92628C-D587-47E0-908B-09FEE6EA517A&displaylang=en
* Provision the device with a "Security Off" configuration
* NOTE: You made need to provision the device twice in order for it to work. The first time it may fail, possibly just updating certificates. 


Shell Setup:
* Compile 
* Copy avmremote.dll into the "Windows" folder on the device
    + in activesync click on Explore
    + click My Windows Mobile/Windows
    + drag avmremote.dll there, confirm it's there and about 5k (matches filesize) 
* On device create the following directory /Program Files/shell
* Compile the avmplus shell for Windows Mobile or download from ftp://ftp.mozilla.org/pub/js/tamarin/builds/
* On desktop pc run ceremotedeployer.exe <path_to_avmshell_arm.exe>
* Confirm on device shell/avmshell.exe exists (It will be renamed to avmshell.exe on the device)
* Note: you can also manually copy avmshell.exe to /Program Files/shell (it must be called avmshell.exe)
* Confirm that the shell is running correctly on device
    + Download or build ceremoteshell.exe
    + On desktop pc run $> ceremoteshell.exe version.abc
    + This should return the version string from the shell that is on the device 

Emulator Setup:
* Compile wmrunner target for Windows Mobile
* by default test/acceptance/runtests.py looks for wmrunner.exe in util/wmremote/wmrunner/Release
  + if wmrunner.exe is in another location set CERUNNER environment variable to the wmrunner.exe path
* required setup: Microsoft Device Emulator
  + download http://www.microsoft.com/downloads/details.aspx?FamilyID=a6f6adaf-12e3-4b2f-a394-356e2c2fb114&DisplayLang=en
  + if not installed to default c:/Program Files/Microsoft Device Emulator/1.0/DeviceEmulator.exe
    set EMULATOR to the path to DeviceEmulator.exe
* required setup: Emulator Image
  + download Professional v 6.1.4 images http://www.microsoft.com/downloads/details.aspx?familyid=1A7A6B52-F89E-4354-84CE-5D19C204498A&displaylang=en 
  + default image is c:/Program Files/Windows Mobile 6 SDK/PocketPC/DeviceemulationV614/0409/PPC_USA_GSM_VR.BIN
  + if you would like to test a different image or have a different path set EMULATORIMAGE environment variable to the full path
   
* set AVM to <path_to_avmshell.exe>
* use ./test/acceptance/runtests.py as for testing other shell executables
* multiple instances of the emulator can be run by setting --threads=n to runtests.py
  + as guidance use --threads= the number of cores/processors in the machine, also each emulator uses about 350MB of memory
* once an emulator is running with wmrunner.exe, any .abc file can be run remotely on the emulator:
  $ test/util/wmemulatorshell.py <vmargs> <path_to_abc>

