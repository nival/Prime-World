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

namespace avmplus { namespace NativeID {

const uint32_t net_abc_class_count = 1;
const uint32_t net_abc_script_count = 1;
const uint32_t net_abc_method_count = 16;
const uint32_t net_abc_length = 549;

/* thunks (5 unique signatures, 12 total) */

#ifndef AVMPLUS_INDIRECT_NATIVE_THUNKS
  #error nativegen.py: --directthunks requires AVMFEATURE_INDIRECT_NATIVE_THUNKS=1
#endif


// flash_net_URLRequest_requestHeaders_set
AvmBox net_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    URLRequestObject* const obj = (URLRequestObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->set_requestHeaders(
        (ArrayObject*)AvmThunkUnbox_AvmObject(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_net_URLRequest_requestHeaders_get
// flash_net_URLRequest_data_get
AvmBox net_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    typedef AvmRetType_AvmBox (AvmObjectT::*FuncType)();
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    return (AvmBox)(*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
    );
}

// flash_net_URLRequest_contentType_set
// flash_net_URLRequest_digest_set
// flash_net_URLRequest_url_set
// flash_net_URLRequest_method_set
AvmBox net_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    typedef AvmRetType_void (AvmObjectT::*FuncType)(AvmString);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    (*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
        AvmThunkUnbox_AvmString(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_net_URLRequest_data_set
AvmBox net_v2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    URLRequestObject* const obj = (URLRequestObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->set_data(
        AvmThunkUnbox_AvmBox(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_net_URLRequest_url_get
// flash_net_URLRequest_contentType_get
// flash_net_URLRequest_method_get
// flash_net_URLRequest_digest_get
AvmBox net_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    typedef AvmRetType_AvmString (AvmObjectT::*FuncType)();
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    return (AvmBox)(*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
    );
}

class SlotOffsetsAndAsserts
{
private:
    static uint32_t getSlotOffset(Traits* t, int nameId);
public:
    static const uint16_t s_slotsOffsetURLRequestClass = 0;
    static const uint16_t s_slotsOffsetURLRequestObject = 0;
    static void doURLRequestClassAsserts(Traits* cTraits, Traits* iTraits);
};
REALLY_INLINE void SlotOffsetsAndAsserts::doURLRequestClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(URLRequestClass::EmptySlotsStruct_URLRequestClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(URLRequestObject::EmptySlotsStruct_URLRequestObject) >= 0);
}

AVMTHUNK_NATIVE_CLASS_GLUE(URLRequestClass, URLRequestClass, SlotOffsetsAndAsserts::doURLRequestClassAsserts)

AVMTHUNK_BEGIN_NATIVE_TABLES(net)
    
    AVMTHUNK_BEGIN_NATIVE_METHODS(net)
        AVMTHUNK_NATIVE_METHOD(flash_net_URLRequest_method_get, URLRequestObject::get_method)
        AVMTHUNK_NATIVE_METHOD(flash_net_URLRequest_method_set, URLRequestObject::set_method)
        AVMTHUNK_NATIVE_METHOD(flash_net_URLRequest_digest_get, URLRequestObject::get_digest)
        AVMTHUNK_NATIVE_METHOD(flash_net_URLRequest_contentType_set, URLRequestObject::set_contentType)
        AVMTHUNK_NATIVE_METHOD(flash_net_URLRequest_digest_set, URLRequestObject::set_digest)
        AVMTHUNK_NATIVE_METHOD(flash_net_URLRequest_data_get, URLRequestObject::get_data)
        AVMTHUNK_NATIVE_METHOD(flash_net_URLRequest_requestHeaders_set, URLRequestObject::set_requestHeaders)
        AVMTHUNK_NATIVE_METHOD(flash_net_URLRequest_url_get, URLRequestObject::get_url)
        AVMTHUNK_NATIVE_METHOD(flash_net_URLRequest_data_set, URLRequestObject::set_data)
        AVMTHUNK_NATIVE_METHOD(flash_net_URLRequest_requestHeaders_get, URLRequestObject::get_requestHeaders)
        AVMTHUNK_NATIVE_METHOD(flash_net_URLRequest_contentType_get, URLRequestObject::get_contentType)
        AVMTHUNK_NATIVE_METHOD(flash_net_URLRequest_url_set, URLRequestObject::set_url)
    AVMTHUNK_END_NATIVE_METHODS()
    
    AVMTHUNK_BEGIN_NATIVE_CLASSES(net)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_net_URLRequest, URLRequestClass, URLRequestClass, SlotOffsetsAndAsserts::s_slotsOffsetURLRequestClass, URLRequestObject, SlotOffsetsAndAsserts::s_slotsOffsetURLRequestObject)
    AVMTHUNK_END_NATIVE_CLASSES()
    
AVMTHUNK_END_NATIVE_TABLES()

AVMTHUNK_DEFINE_NATIVE_INITIALIZER(net)

/* abc */
const uint8_t net_abc_data[549] = {
 16,   0,  46,   0,   0,   0,   0,  25,  20, 102, 108,  97, 115, 104,  46, 110, 
101, 116,  58,  85,  82,  76,  82, 101, 113, 117, 101, 115, 116,   0,   3, 117, 
114, 108,   8, 110, 101, 116,  46,  97, 115,  36,  50,   9, 102, 108,  97, 115, 
104,  46, 110, 101, 116,   6,  79,  98, 106, 101,  99, 116,  14, 114, 101, 113, 
117, 101, 115, 116,  72, 101,  97, 100, 101, 114, 115,   6,  83, 116, 114, 105, 
110, 103,   7,  66, 111, 111, 108, 101,  97, 110,   4, 118, 111, 105, 100,   5, 
 65, 114, 114,  97, 121,  22, 115, 104, 111, 117, 108, 100,  70, 105, 108, 116, 
101, 114,  72,  84,  84,  80,  72, 101,  97, 100, 101, 114,   6, 109, 101, 116, 
104, 111, 100,   6, 100, 105, 103, 101, 115, 116,  11,  99, 111, 110, 116, 101, 
110, 116,  84, 121, 112, 101,   4, 100,  97, 116,  97,  10,  85,  82,  76,  82, 
101, 113, 117, 101, 115, 116,   6, 110,  97, 116, 105, 118, 101,   3,  99, 108, 
115,  15,  85,  82,  76,  82, 101, 113, 117, 101, 115, 116,  67, 108,  97, 115, 
115,   8, 105, 110, 115, 116,  97, 110,  99, 101,  16,  85,  82,  76,  82, 101, 
113, 117, 101, 115, 116,  79,  98, 106, 101,  99, 116,   7, 109, 101, 116, 104, 
111, 100, 115,   4,  97, 117, 116, 111,   9,   5,   1,   5,   4,  22,   2,  22, 
  5,  23,   5,  24,   1,  26,   1,  26,   6,   3,   8,   1,   2,   3,   4,   5, 
  6,   7,   8,   4,   2,   3,   4,   5,  17,   9,   3,   1,   9,   7,   1,   7, 
  3,   8,   7,   3,   9,   7,   3,  10,   7,   3,   6,   7,   3,  11,   7,   1, 
 12,   7,   3,  13,   7,   3,  14,   7,   3,  15,   7,   3,  16,   7,   3,   7, 
  7,   3,   3,   7,   4,  17,   9,   6,   2,  16,   0,   0,   2,   0,   1,   0, 
  3,   2,   8,   1,  12,  12,   1,   4,   3,   2,   0,   0,   3,   2,  32,   1, 
  5,   3,   2,  32,   0,   3,   2,  32,   1,   5,   3,   2,  32,   1,   5,   3, 
  2,  32,   0,   6,   2,  32,   1,   5,   7,   2,  32,   0,   3,   2,  32,   1, 
  5,   6,   2,  32,   0,   7,   2,  32,   0,   3,   2,  32,   1,   5,   3,   2, 
 32,   0,   0,   2,   0,   1,  18,   3,  19,  21,  23,  20,  22,  24,   1,  15, 
  6,  11,   6,   0,   1,  13,   8,   1,   0,   2,   9,   2,   0,   3,   9,   3, 
  0,   4,  10,   2,   0,   5,  11,   3,   0,   6,  10,   3,   0,   7,  12,   2, 
  0,   8,  13,   3,   0,   9,  14,   2,   0,  10,  12,   3,   0,  11,  13,   2, 
  0,  12,  11,   2,   0,  13,  14,   3,   0,  14,   0,   0,   1,  15,   1,  15, 
 68,   1,   0,   1,   0,   4,   0,   1,   1,   3,   4,   3, 208,  48,  71,   0, 
  0,   1,   2,   2,   4,   5,  21, 208,  48, 208,  73,   0, 209,  32,  19,   4, 
  0,   0, 208, 209, 104,   1, 208,  86,   0, 104,   2,  71,   0,   0,   2,   1, 
  2,   4,   5,   4, 208,  48,  39,  72,   0,   0,  15,   2,   1,   1,   3,  19, 
208,  48, 101,   0,  93,   6, 102,   6,  48,  93,  16, 102,  16,  88,   0,  29, 
104,  15,  71,   0,   0};

} }
