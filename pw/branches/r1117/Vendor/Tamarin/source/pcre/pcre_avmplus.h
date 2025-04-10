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

#ifndef __pcre_avmplus_h__
#define __pcre_avmplus_h__

// https://bugzilla.mozilla.org/show_bug.cgi?id=529407

#define _pcre_OP_lengths avmplus__pcre_OP_lengths
#define _pcre_default_tables avmplus__pcre_default_tables
#define _pcre_utf8_table1 avmplus__pcre_utf8_table1
#define _pcre_utf8_table1_size avmplus__pcre_utf8_table1_size
#define _pcre_utf8_table2 avmplus__pcre_utf8_table2
#define _pcre_utf8_table3 avmplus__pcre_utf8_table3
#define _pcre_utf8_table4 avmplus__pcre_utf8_table4
#define _pcre_utt avmplus__pcre_utt
#define _pcre_utt_size avmplus__pcre_utt_size
#define pcre_callout avmplus_pcre_callout
#define pcre_compile avmplus_pcre_compile
#define pcre_compile2 avmplus_pcre_compile2
#define pcre_config avmplus_pcre_config
#define pcre_copy_named_substring avmplus_pcre_copy_named_substring
#define pcre_copy_substring avmplus_pcre_copy_substring
#define pcre_exec avmplus_pcre_exec
#define pcre_free_substring avmplus_pcre_free_substring
#define pcre_free_substring_list avmplus_pcre_free_substring_list
#define pcre_fullinfo avmplus_pcre_fullinfo
#define pcre_get_named_substring avmplus_pcre_get_named_substring
#define pcre_get_stringnumber avmplus_pcre_get_stringnumber
#define pcre_get_stringtable_entries avmplus_pcre_get_stringtable_entries
#define pcre_get_substring avmplus_pcre_get_substring
#define pcre_get_substring_list avmplus_pcre_get_substring_list
#define pcre_info avmplus_pcre_info
#define pcre_refcount avmplus_pcre_refcount
#define pcre_study avmplus_pcre_study
#define pcre_version avmplus_pcre_version

#endif
