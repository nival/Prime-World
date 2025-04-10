/* -*- mode: java; tab-width: 4; insert-tabs-mode: nil; indent-tabs-mode: nil;  -*- */
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

use default namespace ESC,
    namespace ESC;

internal var profile_data = {};

function startProfile() {
    "flash.sampler"::startSampling();
}

internal function printProf()
    this.name + "\n   {self:" + this.self + ", children: " + this.children + ", new:" + this.new + "}";

internal function printCallers() {
    let s = "{";
    for each ( let v in this )
        s += v + ", ";
    s += "}";
    return s;
}

internal function printCaller()
    this.name + "= " + this.count;

internal function frame2name(s) {
    let name = s + " ";
    if (!profile_data.hasOwnProperty(name))
        profile_data[name] = {name: name, callers: { toString: printCallers }, self:0, children: 0, new:0, toString: printProf};
    return name;
}

function snapshotProfile() {
    "flash.sampler"::pauseSampling();
    let samples = "flash.sampler"::getSamples();
    for each (let sample in samples) {
        if (sample.stack) {
            let name = frame2name(sample.stack[0]);
            switch type (sample) {
            case (s: "flash.sampler"::DeleteObjectSample) { }
            case (s: "flash.sampler"::NewObjectSample) { 
                profile_data[name].new += 1; 
            }
            case (s: *) { 
                profile_data[name].self += 1;
                if (sample.stack.length > 1) {
                    let n2 = frame2name(sample.stack[1]);
                    if (!profile_data[name].callers.hasOwnProperty(n2))
                        profile_data[name].callers[n2] = { name: n2, count: 0, toString: printCaller };
                    profile_data[name].callers[n2].count += 1;
                }
                for ( let i=1 ; i < sample.stack.length ; i++ ) {
                    let parent_name = frame2name(sample.stack[i]);
                    profile_data[parent_name].children += 1;
                }
            }
            }
        }
    }
    "flash.sampler"::clearSamples();
    "flash.sampler"::startSampling();
}

function dumpProfile(filename) {
    let tmp = [];
    let s = "";

    for (let name in profile_data)
        tmp.push(profile_data[name]);

    timeProfile((function (x) x.self), "self");
    timeProfile((function (x) x.self + x.children), "subtree");

    s += "\n";
    s += "ALLOC PROFILE\n";
    s += "\n";
    s += "Allocs   Pct    Name\n";
    s += "-------- ------ -------------------------------\n";

    tmp.sort(function(a,b) b.new-a.new);

    let total = 0;

    for ( let i=0 ; i < tmp.length && tmp[i].new > 0 ; i++ )
        total += tmp[i].new;
    for ( let i=0 ; i < tmp.length && tmp[i].new > 0 ; i++ )
        s += "" + right(tmp[i].new, 8) + " " + right((100*tmp[i].new/total).toFixed(1), 5) + "% " + tmp[i].name + "\n";

    Util::writeStringToFile(s, filename);
    print("Profile written to " + filename);

    function timeProfile(val, bywhat) {
        s += "\n";
        s += "TIME PROFILE (sorted by " + bywhat + ")\n";
        s += "\n";
        s += "Self     Subtree  Pct    Name\n";
        s += "-------- -------- ------- -------------------------------\n";

        tmp.sort(function (a,b) val(b) - val(a));

        let total = 0;
        let v;

        for ( let i=0 ; i < tmp.length && val(tmp[i]) > 0 ; i++ )
            total += tmp[i].self;  // [sic]
        for ( let i=0 ; i < tmp.length && (v = val(tmp[i])) > 0 ; i++ ) {
            s += "" + right(tmp[i].self, 8) + " " + right(tmp[i].self+tmp[i].children, 8) + right((100*v/total).toFixed(1), 6) + "% " + tmp[i].name + "\n";
            /* Print the known callers of the method in arbitrary order
            if (tmp[i].name == "Array/get length() ")
                s += "      " + tmp[i].callers.toString().split(",").join("\n      ") + "\n";
            */
        }
    }

    function right(x, n) {
        x = String(x);
        return "                    ".substring(0,n).substring(x.length) + x;
    }
}

function stopProfile() {
    "flash.sampler"::stopSampling();
}
