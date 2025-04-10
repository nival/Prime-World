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
 * The Original Code is [Open Source Virtual Machine.].
 *
 * The Initial Developer of the Original Code is
 * Adobe System Incorporated.
 * Portions created by the Initial Developer are Copyright (C) 2004-2006
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

import avmplus.*;

var SECTION = 'API Versioning - classes';
var VERSION = 'AS3';

startTest();

writeHeaderToLog( SECTION );

var re:String;
var re1065:String = 'ReferenceError: Error #1065';
var re1056:String = 'ReferenceError: Error #1056';
var re1069:String = 'ReferenceError: Error #1069';

// get api version passed in using abc args
var argv = System.argv;
var apiVersion:int = int(argv[argv.length-1]);

// expected answers
var apiExpectedAns:Array = [];
re = re1069;         //   0   660   661   662   663   664   665   665   666   
apiExpectedAns[0]   = [true, true,   re,   re,   re,   re,   re,   re,   re,   re, true,   re, true];
apiExpectedAns[660] = [true, true,   re,   re,   re,   re,   re,   re,   re,   re, true,   re, true];
apiExpectedAns[661] = [true, true, true,   re,   re,   re,   re,   re,   re, true, true,   re, true];
apiExpectedAns[662] = [true, true,   re, true,   re,   re,   re,   re,   re, true, true, true, true];
apiExpectedAns[663] = [true, true, true, true, true,   re,   re,   re,   re, true, true, true, true];
apiExpectedAns[664] = [true, true, true, true, true, true,   re,   re,   re, true, true, true, true];
apiExpectedAns[665] = [true, true,   re, true,   re,   re, true,   re,   re, true, true, true, true];
apiExpectedAns[666] = [true, true, true, true, true, true, true, true,   re, true, true, true, true];
apiExpectedAns[667] = [true, true, true, true, true, true, true, true, true, true, true, true, true];

// expected answer for set
var apiExpectedSetAns:Array =[];
re = re1056; // missing set generates a 1056 ref error
apiExpectedSetAns[0]   = [true, true,   re,   re,   re,   re,   re,   re,   re,   re, true,   re, true];
apiExpectedSetAns[660] = [true, true,   re,   re,   re,   re,   re,   re,   re,   re, true,   re, true];
apiExpectedSetAns[661] = [true, true, true,   re,   re,   re,   re,   re,   re, true, true,   re, true];
apiExpectedSetAns[662] = [true, true,   re, true,   re,   re,   re,   re,   re, true, true, true, true];
apiExpectedSetAns[663] = [true, true, true, true, true,   re,   re,   re,   re, true, true, true, true];
apiExpectedSetAns[664] = [true, true, true, true, true, true,   re,   re,   re, true, true, true, true];
apiExpectedSetAns[665] = [true, true,   re, true,   re,   re, true,   re,   re, true, true, true, true];
apiExpectedSetAns[666] = [true, true, true, true, true, true, true, true,   re, true, true, true, true];
apiExpectedSetAns[667] = [true, true, true, true, true, true, true, true, true, true, true, true, true];

var classExpectedAns:Array = [];
o = 'object'
u = 'undefined';         //   0   660   661   662   663   664   665   665   666
classExpectedAns[0]   = [o, o,   u,   u,   u,   u,   u,   u,   u,   u, o,   u, o];
classExpectedAns[660] = [o, o,   u,   u,   u,   u,   u,   u,   u,   u, o,   u, o];
classExpectedAns[661] = [o, o,   o,   u,   u,   u,   u,   u,   u, o, o,   u, o];
classExpectedAns[662] = [o, o,   u, o,   u,   u,   u,   u,   u, o, o, o, o];
classExpectedAns[663] = [o, o, o, o, o,   u,   u,   u,   u, o, o, o, o];
classExpectedAns[664] = [o, o, o, o, o, o,   u,   u,   u, o, o, o, o];
classExpectedAns[665] = [o, o,   u, o,   u,   u, o,   u,   u, o, o, o, o];
classExpectedAns[666] = [o, o, o, o, o, o, o, o,   u, o, o, o, o];
classExpectedAns[667] = [o, o, o, o, o, o, o, o, o, o, o, o, o];

// set expected answers to specified api version 
var ea:Array = apiExpectedAns[apiVersion]
var ea_set:Array = apiExpectedSetAns[apiVersion]
var cea:Array = classExpectedAns[apiVersion]

var pc = new public_class();

versionTest(function() { return pc.public_var }, 'pc.public_var', ea[0]);
versionTest(function() { return pc.public_var_660 }, 'pc.public_var_660', ea[1]);
versionTest(function() { return pc.public_var_661 }, 'pc.public_var_661', ea[2]);
versionTest(function() { return pc.public_var_662 }, 'pc.public_var_662', ea[3]);
versionTest(function() { return pc.public_var_663 }, 'pc.public_var_663', ea[4]);
versionTest(function() { return pc.public_var_664 }, 'pc.public_var_664', ea[5]);
versionTest(function() { return pc.public_var_665 }, 'pc.public_var_665', ea[6]);
versionTest(function() { return pc.public_var_666 }, 'pc.public_var_666', ea[7]);
versionTest(function() { return pc.public_var_667 }, 'pc.public_var_667', ea[8]);
versionTest(function() { return pc.public_var_661_662 }, 'pc.public_var_661_662', ea[9]);
versionTest(function() { return pc.public_var_666_660 }, 'pc.public_var_666_660', ea[10]);
versionTest(function() { return pc.public_var_664_662_666 }, 'pc.public_var_664_662_666', ea[11]);
versionTest(function() { return pc.public_var_665_660_661_662 }, 'pc.public_var_665_660_661_662', ea[12]);

versionTest(function() { return pc.public_const }, 'pc.public_const', ea[0]);
versionTest(function() { return pc.public_const_660 }, 'pc.public_const_660', ea[1]);
versionTest(function() { return pc.public_const_661 }, 'pc.public_const_661', ea[2]);
versionTest(function() { return pc.public_const_662 }, 'pc.public_const_662', ea[3]);
versionTest(function() { return pc.public_const_663 }, 'pc.public_const_663', ea[4]);
versionTest(function() { return pc.public_const_664 }, 'pc.public_const_664', ea[5]);
versionTest(function() { return pc.public_const_665 }, 'pc.public_const_665', ea[6]);
versionTest(function() { return pc.public_const_666 }, 'pc.public_const_666', ea[7]);
versionTest(function() { return pc.public_const_667 }, 'pc.public_const_667', ea[8]);
versionTest(function() { return pc.public_const_661_662 }, 'pc.public_const_661_662', ea[9]);
versionTest(function() { return pc.public_const_666_660 }, 'pc.public_const_666_660', ea[10]);
versionTest(function() { return pc.public_const_664_662_666 }, 'pc.public_const_664_662_666', ea[11]);
versionTest(function() { return pc.public_const_665_660_661_662 }, 'pc.public_const_665_660_661_662', ea[12]);

versionTest(function() { return pc.public_function()}, 'pc.public_function', ea[0]);
versionTest(function() { return pc.public_function_660()}, 'pc.public_function_660', ea[1]);
versionTest(function() { return pc.public_function_661()}, 'pc.public_function_661', ea[2]);
versionTest(function() { return pc.public_function_662()}, 'pc.public_function_662', ea[3]);
versionTest(function() { return pc.public_function_663()}, 'pc.public_function_663', ea[4]);
versionTest(function() { return pc.public_function_664()}, 'pc.public_function_664', ea[5]);
versionTest(function() { return pc.public_function_665()}, 'pc.public_function_665', ea[6]);
versionTest(function() { return pc.public_function_666()}, 'pc.public_function_666', ea[7]);
versionTest(function() { return pc.public_function_667()}, 'pc.public_function_667', ea[8]);
versionTest(function() { return pc.public_function_661_662()}, 'pc.public_function_661_662', ea[9]);
versionTest(function() { return pc.public_function_666_660()}, 'pc.public_function_666_660', ea[10]);
versionTest(function() { return pc.public_function_664_662_666()}, 'pc.public_function_664_662_666', ea[11]);
versionTest(function() { return pc.public_function_665_660_661_662()}, 'pc.public_function_665_660_661_662', ea[12]);

versionTest(function() { return pc.public_getset }, 'pc.public_getset', ea[0]);
versionTest(function() { return pc.public_getset_660 }, 'pc.public_getset_660', ea[1]);
versionTest(function() { return pc.public_getset_661 }, 'pc.public_getset_661', ea[2]);
versionTest(function() { return pc.public_getset_662 }, 'pc.public_getset_662', ea[3]);
versionTest(function() { return pc.public_getset_663 }, 'pc.public_getset_663', ea[4]);
versionTest(function() { return pc.public_getset_664 }, 'pc.public_getset_664', ea[5]);
versionTest(function() { return pc.public_getset_665 }, 'pc.public_getset_665', ea[6]);
versionTest(function() { return pc.public_getset_666 }, 'pc.public_getset_666', ea[7]);
versionTest(function() { return pc.public_getset_667 }, 'pc.public_getset_667', ea[8]);
versionTest(function() { return pc.public_getset_661_662 }, 'pc.public_getset_661_662', ea[9]);
versionTest(function() { return pc.public_getset_666_660 }, 'pc.public_getset_666_660', ea[10]);
versionTest(function() { return pc.public_getset_664_662_666 }, 'pc.public_getset_664_662_666', ea[11]);
versionTest(function() { return pc.public_getset_665_660_661_662 }, 'pc.public_getset_665_660_661_662', ea[12]);

versionTest(function() { pc.public_getset = true; return true; }, 'pc.public_getset', ea_set[0]);
versionTest(function() { pc.public_getset_660 = true; return true; }, 'pc.public_getset_660', ea_set[1]);
versionTest(function() { pc.public_getset_661 = true; return true; }, 'pc.public_getset_661', ea_set[2]);
versionTest(function() { pc.public_getset_662 = true; return true; }, 'pc.public_getset_662', ea_set[3]);
versionTest(function() { pc.public_getset_663 = true; return true; }, 'pc.public_getset_663', ea_set[4]);
versionTest(function() { pc.public_getset_664 = true; return true; }, 'pc.public_getset_664', ea_set[5]);
versionTest(function() { pc.public_getset_665 = true; return true; }, 'pc.public_getset_665', ea_set[6]);
versionTest(function() { pc.public_getset_666 = true; return true; }, 'pc.public_getset_666', ea_set[7]);
versionTest(function() { pc.public_getset_667 = true; return true; }, 'pc.public_getset_667', ea_set[8]);
versionTest(function() { pc.public_getset_661_662 = true; return true; }, 'pc.public_getset_661_662', ea_set[9]);
versionTest(function() { pc.public_getset_666_660 = true; return true; }, 'pc.public_getset_666_660', ea_set[10]);
versionTest(function() { pc.public_getset_664_662_666 = true; return true; }, 'pc.public_getset_664_662_666', ea_set[11]);
versionTest(function() { pc.public_getset_665_660_661_662 = true; return true; }, 'pc.public_getset_665_660_661_662', ea_set[12]);


versionTest(function() { return String(typeof(pc)) }, 'pc', cea[0]);
versionTest(function() { return String(typeof(public_class_660)) }, 'public_class_660', cea[1]);
versionTest(function() { return String(typeof(public_class_661)) }, 'public_class_661', cea[2]);
versionTest(function() { return String(typeof(public_class_662)) }, 'public_class_662', cea[3]);
versionTest(function() { return String(typeof(public_class_663)) }, 'public_class_663', cea[4]);
versionTest(function() { return String(typeof(public_class_664)) }, 'public_class_664', cea[5]);
versionTest(function() { return String(typeof(public_class_665)) }, 'public_class_665', cea[6]);
versionTest(function() { return String(typeof(public_class_666)) }, 'public_class_666', cea[7]);
versionTest(function() { return String(typeof(public_class_667)) }, 'public_class_667', cea[8]);
versionTest(function() { return String(typeof(public_class_661_662)) }, 'public_class_661_662', cea[9]);
versionTest(function() { return String(typeof(public_class_666_660)) }, 'public_class_666_660', cea[10]);
versionTest(function() { return String(typeof(public_class_664_662_666)) }, 'public_class_664_662_666', cea[11]);
versionTest(function() { return String(typeof(public_class_665_660_661_662)) }, 'public_class_665_660_661_662', cea[12]);

versionTest(function() { return String(typeof(public_interface)) }, 'public_interface', cea[0]);
versionTest(function() { return String(typeof(public_interface_660)) }, 'public_interface_660', cea[1]);
versionTest(function() { return String(typeof(public_interface_661)) }, 'public_interface_661', cea[2]);
versionTest(function() { return String(typeof(public_interface_662)) }, 'public_interface_662', cea[3]);
versionTest(function() { return String(typeof(public_interface_663)) }, 'public_interface_663', cea[4]);
versionTest(function() { return String(typeof(public_interface_664)) }, 'public_interface_664', cea[5]);
versionTest(function() { return String(typeof(public_interface_665)) }, 'public_interface_665', cea[6]);
versionTest(function() { return String(typeof(public_interface_666)) }, 'public_interface_666', cea[7]);
versionTest(function() { return String(typeof(public_interface_667)) }, 'public_interface_667', cea[8]);
versionTest(function() { return String(typeof(public_interface_661_662)) }, 'public_interface_661_662', cea[9]);
versionTest(function() { return String(typeof(public_interface_666_660)) }, 'public_interface_666_660', cea[10]);
versionTest(function() { return String(typeof(public_interface_664_662_666)) }, 'public_interface_664_662_666', cea[11]);
versionTest(function() { return String(typeof(public_interface_665_660_661_662)) }, 'public_interface_665_660_661_662', cea[12]);

test();
