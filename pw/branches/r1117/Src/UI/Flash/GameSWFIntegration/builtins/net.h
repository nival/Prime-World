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
 * Portions created by the Initial Developer are Copyright (C) 2008
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

/* machine generated file -- do not edit */
#pragma once

#define AVMTHUNK_VERSION 5

namespace avmplus {
    class URLRequestClass; //flash.net::URLRequest$
    class URLRequestObject; //flash.net::URLRequest
}

namespace avmplus { namespace NativeID {

extern const uint32_t net_abc_class_count;
extern const uint32_t net_abc_script_count;
extern const uint32_t net_abc_method_count;
extern const uint32_t net_abc_length;
extern const uint8_t net_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(net)

/* classes */
const uint32_t abcclass_flash_net_URLRequest = 0;

/* methods */
const uint32_t flash_net_URLRequest_method_get = 3;
const uint32_t flash_net_URLRequest_method_set = 4;
const uint32_t flash_net_URLRequest_digest_get = 5;
const uint32_t flash_net_URLRequest_contentType_set = 6;
const uint32_t flash_net_URLRequest_digest_set = 7;
const uint32_t flash_net_URLRequest_data_get = 8;
const uint32_t flash_net_URLRequest_requestHeaders_set = 9;
const uint32_t flash_net_URLRequest_url_get = 10;
const uint32_t flash_net_URLRequest_data_set = 11;
const uint32_t flash_net_URLRequest_requestHeaders_get = 12;
const uint32_t flash_net_URLRequest_contentType_get = 13;
const uint32_t flash_net_URLRequest_url_set = 14;

extern AvmBox net_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_net_URLRequest_requestHeaders_set_thunk  net_v2a_oo_thunk

extern AvmBox net_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_net_URLRequest_requestHeaders_get_thunk  net_a2a_o_thunk
#define flash_net_URLRequest_data_get_thunk  net_a2a_o_thunk

extern AvmBox net_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_net_URLRequest_contentType_set_thunk  net_v2a_os_thunk
#define flash_net_URLRequest_digest_set_thunk  net_v2a_os_thunk
#define flash_net_URLRequest_url_set_thunk  net_v2a_os_thunk
#define flash_net_URLRequest_method_set_thunk  net_v2a_os_thunk

extern AvmBox net_v2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_net_URLRequest_data_set_thunk  net_v2a_oa_thunk

extern AvmBox net_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_net_URLRequest_url_get_thunk  net_s2a_o_thunk
#define flash_net_URLRequest_contentType_get_thunk  net_s2a_o_thunk
#define flash_net_URLRequest_method_get_thunk  net_s2a_o_thunk
#define flash_net_URLRequest_digest_get_thunk  net_s2a_o_thunk

class SlotOffsetsAndAsserts;
// flash.net::URLRequest$
//-----------------------------------------------------------
class URLRequestClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_URLRequestClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::URLRequestClassSlots EmptySlotsStruct_URLRequestClass
//-----------------------------------------------------------

// flash.net::URLRequest
//-----------------------------------------------------------
class URLRequestObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_URLRequestObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::URLRequestObjectSlots EmptySlotsStruct_URLRequestObject
//-----------------------------------------------------------

} }
