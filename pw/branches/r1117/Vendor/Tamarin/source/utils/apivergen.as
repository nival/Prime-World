/* -*- mode: java -*- */
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
 * Portions created by the Initial Developer are Copyright (C) 2009
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

package apivergen {
import avmplus.*;

    /**
	 * find the coordinates of a value in an n-dim matrix
	 *
	 * v = value to look for
	 * m = array of array of ... of value
	 * dim = dimensionality of m
	 */

    function find(v, m, dim)
	{
		if (dim == 0)
			return m == v ? [] : null;
		for ( var i=0 ; i < m.length ; i++ ) {
			var probe = find(v, m[i], dim-1);
			if (probe) {
				probe.unshift(i);
				return probe;
			}
		}
		return null;
	}

	/**
	 * emit the values in positions outside of a given position
	 * in an n-dim matrix
	 *
	 * m = array of array of ... of value
	 * coord = array of int
	 * dim = dimensionality of m; length of coord
	 * f = function to call on each value
	 */

	function gen(m, coord, dim, f): void
	{
		if (dim == 0) {
			f(m);
			return;
		}
		for (var i=coord[coord.length-dim] ; i < m.length ; i++)
			gen(m[i], coord, dim-1, f);
	}
	
	function process (fname) {
		var api = new XML (File.read (fname));
		var versions = api.versions;
		var uris = api.uris;
		var releases = versions..release;
		var products = releases[releases.length()-1]..product;
		var profiles = products[products.length()-1]..profile;
		var release_ids = [];
		var product_ids = [];
		var profile_ids = [];
		for each (var v in releases) {
			release_ids.push(v.@id);
		}

		for each (var v in products) {
			product_ids.push(v.@id);
		}

		for each (var v in profiles) {
			profile_ids.push(v.@id);
		}

		var default_version = -1; // default

		// build the compatiblity matrix (emitting a comment on which
		// versions are which)

		var frag = [];
		var out = "" +
			"/* ***** BEGIN LICENSE BLOCK *****\n"	 +
            " * Version: MPL 1.1/GPL 2.0/LGPL 2.1\n" +
            " *\n" +
            " * The contents of this file are subject to the Mozilla Public License Version\n" +
            " * 1.1 (the \"License+\"); you may not use this file except in compliance with\n" +
            " * the License. You may obtain a copy of the License at\n" +
            " * http://www.mozilla.org/MPL/\n" +
            " *\n" +
            " * Software distributed under the License is distributed on an \"AS IS\" basis,\n" +
            " * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License\n" +
            " * for the specific language governing rights and limitations under the\n" +
            " * License.\n" +
            " *\n" +
            " * The Original Code is [Open Source Virtual Machine].\n" +
            " *\n" +
            " * The Initial Developer of the Original Code is\n" +
            " * Adobe System Incorporated.\n" +
            " * Portions created by the Initial Developer are Copyright (C) 2008\n" +
            " * the Initial Developer. All Rights Reserved.\n" +
            " *\n" +
            " * Contributor(s):\n" +
            " *   Adobe AS3 Team\n" +
            " *\n" +
            " * Alternatively, the contents of this file may be used under the terms of\n" +
            " * either the GNU General Public License Version 2 or later (the \"GPL+\"), or\n" +
            " * the GNU Lesser General Public License Version 2.1 or later (the \"LGPL\"),\n" +
            " * in which case the provisions of the GPL or the LGPL are applicable instead\n" +
            " * of those above. If you wish to allow use of your version of this file only\n" +
            " * under the terms of either the GPL or the LGPL, and not to allow others to\n" +
            " * use your version of this file under the terms of the MPL, indicate your\n" +
            " * decision by deleting the provisions above and replace them with the notice\n" +
            " * and other provisions required by the GPL or the LGPL. If you do not delete\n" +
            " * the provisions above, a recipient may use your version of this file under\n" +
            " * the terms of any one of the MPL, the GPL or the LGPL.\n" +
            " *\n" +
            " * ***** END LICENSE BLOCK ***** */\n" +
			"\n" +
			"/* this file is generated by apivergen.abc. do no edit */\n/*\n"
		var d1 = [];
		var min_version = Number.MAX_VALUE;
		var max_version = 0;
		for each (var release_id in release_ids) {
			var d2 = [];
			d1.push(d2);
			//print ("release_id="+release_id);
			var release = versions.release.(@id == release_id);
			default_version = release.version==void 0 ? default_version : release.version.@id;
			for each (var product_id in product_ids) {
			var d3 = [];
				d2.push(d3);
				product = release.product.(@id == product_id);
				var default_version = product.version==void 0 ? default_version : product.version.@id;
				for each (var profile_id in profile_ids) {
				    var profile = product.profile.(@id == profile_id);
					//print ("profile_id="+profile_id);
					var version = profile.version==void 0 ? default_version : profile.version.@id;
					if(version >= 0) 
						out += "["+release_id+","+product_id+","+profile_id+"]="+version+":"+profile.version.@alias+"\n";
					d3.push(version);
					if (version > max_version) {
						max_version = version;
					}
					if (version >=0 && version < min_version) {
						min_version = version;
					}
				}
			}
		}
		out += "*/\n\n";
		frag[0] = out;
		out = "";

		// emit the array of versions_count array
		var version_count;
		// out += "static const uint32_t _versions_count [] = {";
		out += "[] = {";
		for (var v = min_version; v <= max_version; ++v) {
			version_count = 0;
			gen(d1,find(v,d1,3),3, function (x) { if(x>=0) version_count += 1 });
			out += version_count + ", ";
		}
		out += "};\n\n";
		frag[1] = out;
		out = "";

		// emit the versions matrix
		//out += "static const uint32_t _versions []["+(Number(max_version)+1)+"] = {\n";
		frag[2] = "["+(Number(max_version)-Number(min_version)+1)+"]";
		out += "{\n";
		for (var v = min_version; v <= max_version; ++v) {
			out += "  {";
			gen(d1,find(v,d1,3),3, function (x) { if(x>=0) out += x + ", " });
			out += "},\n";
		}
		out += "};\n";
		frag[3] = out;

		frag[4] = "" + uris.uri.length() + ";\n";
		out = "{\n";
		for each (var v in uris.uri) {
			out += "  \"" + v.@id + "\",\n";
		}
		out += "};\n";
		frag[5] = out;
		frag[6] = min_version + ";\n";
		frag[7] = max_version + ";\n";

		out = "{";
		for (var v = min_version; v <= max_version; ++v) {
			var api = 0;
			//out += "  {";
			gen(d1,find(v,d1,3),3, function (x) { if(x>=0) api |= 0x1 << x-min_version });
			//out += "},\n";
			out += "0x" + api.toString(16) + ", ";
		}
		out += "};\n";
		print(out);
		frag[8] = out;

		return frag;
	}


	/*
	  emit c code
	*/

	function emitc(frag) {
		var out = frag[0];
		out += "static const uint32_t _min_version_num = " + frag[6];
		out += "static const uint32_t _max_version_num = " + frag[7];
		out += "static const uint32_t _versions_count" + frag[1];
		out += "static const uint32_t _versions []" + frag[2];
		out += " = " + frag[3];
		out += "static const uint32_t _uris_count = " + frag[4];
		out += "static const char* _uris [] = " + frag[5];
		out += "static const int32_t _api_compat [] = " + frag[8];
		return out;
	}

	/*
	  emit java
	*/

	function emitj(frag) {
		var out = frag[0];
		out += "package macromedia.asc.util;\n";
		out += "public class APIVersions {\n";
		out += "public static int min_version_num = " + frag[6];
		out += "public static int max_version_num = " + frag[7];
		out += "public static int versions [][]";
		out += " = " + frag[3];
		out += "public static String uris [] = " + frag[5];
		out += "public static int api_compat [] = " + frag[8];
		out += "};\n";
		print (out);
		return out;
	}

	/*
	  get file name from the command-line and go. ignore all but the last 
	  argument, which is treated as the file name
	*/

	var argv = System.argv;
	var fname = argv[argv.length-1];
	var frags = process(fname);
	var cname = fname+".h";
	var jname = fname+".java";
	File.write(cname, emitc(frags));
	File.write(jname, emitj(frags));
}

