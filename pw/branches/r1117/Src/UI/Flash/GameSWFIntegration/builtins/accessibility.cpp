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

const uint32_t accessibility_abc_class_count = 3;
const uint32_t accessibility_abc_script_count = 1;
const uint32_t accessibility_abc_method_count = 22;
const uint32_t accessibility_abc_length = 1504;

/* thunks (3 unique signatures, 3 total) */

#ifndef AVMPLUS_INDIRECT_NATIVE_THUNKS
  #error nativegen.py: --directthunks requires AVMFEATURE_INDIRECT_NATIVE_THUNKS=1
#endif


// flash_accessibility_Accessibility_active_get
AvmBox accessibility_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    AccessibilityClass* const obj = (AccessibilityClass*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmBool32 const ret = obj->get_active();
    return (AvmBox) ret;
}

// flash_accessibility_Accessibility_sendEvent
AvmBox accessibility_v2a_oouub_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmObject
        , argoff3 = argoff2 + AvmThunkArgSize_uint32_t
        , argoff4 = argoff3 + AvmThunkArgSize_uint32_t
    };
    (void)env;
    AccessibilityClass* const obj = (AccessibilityClass*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->sendEvent(
        (DisplayObjectObject*)AvmThunkUnbox_AvmObject(argv[argoff1])
        , AvmThunkUnbox_uint32_t(argv[argoff2])
        , AvmThunkUnbox_uint32_t(argv[argoff3])
        , (argc < 4 ? false : AvmThunkUnbox_AvmBool32(argv[argoff4]))
    );
    return kAvmThunkUndefined;
}

// flash_accessibility_Accessibility_updateProperties
AvmBox accessibility_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    AccessibilityClass* const obj = (AccessibilityClass*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->updateProperties();
    return kAvmThunkUndefined;
}

class SlotOffsetsAndAsserts
{
private:
    static uint32_t getSlotOffset(Traits* t, int nameId);
public:
    static const uint16_t s_slotsOffsetAccessibilityClass = 0;
    static const uint16_t s_slotsOffsetAccessibilityObject = 0;
    static void doAccessibilityClassAsserts(Traits* cTraits, Traits* iTraits);
};
REALLY_INLINE void SlotOffsetsAndAsserts::doAccessibilityClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(AccessibilityClass::EmptySlotsStruct_AccessibilityClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(AccessibilityObject::EmptySlotsStruct_AccessibilityObject) >= 0);
}

AVMTHUNK_NATIVE_CLASS_GLUE(AccessibilityClass, AccessibilityClass, SlotOffsetsAndAsserts::doAccessibilityClassAsserts)

AVMTHUNK_BEGIN_NATIVE_TABLES(accessibility)
    
    AVMTHUNK_BEGIN_NATIVE_METHODS(accessibility)
        AVMTHUNK_NATIVE_METHOD(flash_accessibility_Accessibility_sendEvent, AccessibilityClass::sendEvent)
        AVMTHUNK_NATIVE_METHOD(flash_accessibility_Accessibility_updateProperties, AccessibilityClass::updateProperties)
        AVMTHUNK_NATIVE_METHOD(flash_accessibility_Accessibility_active_get, AccessibilityClass::get_active)
    AVMTHUNK_END_NATIVE_METHODS()
    
    AVMTHUNK_BEGIN_NATIVE_CLASSES(accessibility)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_accessibility_Accessibility, AccessibilityClass, AccessibilityClass, SlotOffsetsAndAsserts::s_slotsOffsetAccessibilityClass, AccessibilityObject, SlotOffsetsAndAsserts::s_slotsOffsetAccessibilityObject)
    AVMTHUNK_END_NATIVE_CLASSES()
    
AVMTHUNK_END_NATIVE_TABLES()

AVMTHUNK_DEFINE_NATIVE_INITIALIZER(accessibility)

/* abc */
const uint8_t accessibility_abc_data[1504] = {
 16,   0,  46,   0,   0,   0,   0,  51,  33, 102, 108,  97, 115, 104,  46,  97, 
 99,  99, 101, 115, 115, 105,  98, 105, 108, 105, 116, 121,  58,  65,  99,  99, 
101, 115, 115, 105,  98, 105, 108, 105, 116, 121,   0,   4, 118, 111, 105, 100, 
 13, 102, 108,  97, 115, 104,  46, 100, 105, 115, 112, 108,  97, 121,  13,  68, 
105, 115, 112, 108,  97, 121,  79,  98, 106, 101,  99, 116,   4, 117, 105, 110, 
116,   7,  66, 111, 111, 108, 101,  97, 110,   9, 115, 101, 110, 100,  69, 118, 
101, 110, 116,  16, 117, 112, 100,  97, 116, 101,  80, 114, 111, 112, 101, 114, 
116, 105, 101, 115,   6,  97,  99, 116, 105, 118, 101,  19, 102, 108,  97, 115, 
104,  46,  97,  99,  99, 101, 115, 115, 105,  98, 105, 108, 105, 116, 121,  13, 
 65,  99,  99, 101, 115, 115, 105,  98, 105, 108, 105, 116, 121,   6,  79,  98, 
106, 101,  99, 116,  47, 102, 108,  97, 115, 104,  46,  97,  99,  99, 101, 115, 
115, 105,  98, 105, 108, 105, 116, 121,  58,  65,  99,  99, 101, 115, 115, 105, 
 98, 105, 108, 105, 116, 121,  73, 109, 112, 108, 101, 109, 101, 110, 116,  97, 
116, 105, 111, 110,   4, 115, 116, 117,  98,  19,  97,  99,  99, 101, 115, 115, 
105,  98, 105, 108, 105, 116, 121,  46,  97, 115,  36,  49,  55,  10, 102, 108, 
 97, 115, 104,  46, 103, 101, 111, 109,   5, 101, 114, 114, 110, 111,   6,  83, 
116, 114, 105, 110, 103,   5,  65, 114, 114,  97, 121,   5,  69, 114, 114, 111, 
114,  10, 116, 104, 114, 111, 119,  69, 114, 114, 111, 114,  11, 105, 115,  76, 
 97,  98, 101, 108, 101, 100,  66, 121,  11, 103, 101, 116,  95,  97,  99,  99, 
 78,  97, 109, 101,  12, 103, 101, 116,  95,  97,  99,  99,  70, 111,  99, 117, 
115,  12, 103, 101, 116,  95,  97,  99,  99,  83, 116,  97, 116, 101,  18,  97, 
 99,  99,  68, 111,  68, 101, 102,  97, 117, 108, 116,  65,  99, 116, 105, 111, 
110,  11, 103, 101, 116,  95,  97,  99,  99,  82, 111, 108, 101,  16, 103, 101, 
116,  95,  97,  99,  99,  83, 101, 108, 101,  99, 116, 105, 111, 110,  11,  97, 
 99,  99,  76, 111,  99,  97, 116, 105, 111, 110,  15, 103, 101, 116,  67, 104, 
105, 108, 100,  73,  68,  65, 114, 114,  97, 121,  12, 103, 101, 116,  95,  97, 
 99,  99,  86,  97, 108, 117, 101,   9,  97,  99,  99,  83, 101, 108, 101,  99, 
116,  20, 103, 101, 116,  95,  97,  99,  99,  68, 101, 102,  97, 117, 108, 116, 
 65,  99, 116, 105, 111, 110,  27,  65,  99,  99, 101, 115, 115, 105,  98, 105, 
108, 105, 116, 121,  73, 109, 112, 108, 101, 109, 101, 110, 116,  97, 116, 105, 
111, 110,  43, 102, 108,  97, 115, 104,  46,  97,  99,  99, 101, 115, 115, 105, 
 98, 105, 108, 105, 116, 121,  58,  65,  99,  99, 101, 115, 115, 105,  98, 105, 
108, 105, 116, 121,  80, 114, 111, 112, 101, 114, 116, 105, 101, 115,   4, 110, 
 97, 109, 101,  11, 100, 101, 115,  99, 114, 105, 112, 116, 105, 111, 110,   8, 
115, 104, 111, 114, 116,  99, 117, 116,   6, 115, 105, 108, 101, 110, 116,  11, 
102, 111, 114,  99, 101,  83, 105, 109, 112, 108, 101,  14, 110, 111,  65, 117, 
116, 111,  76,  97,  98, 101, 108, 105, 110, 103,  23,  65,  99,  99, 101, 115, 
115, 105,  98, 105, 108, 105, 116, 121,  80, 114, 111, 112, 101, 114, 116, 105, 
101, 115,   6, 110,  97, 116, 105, 118, 101,   3,  99, 108, 115,  18,  65,  99, 
 99, 101, 115, 115, 105,  98, 105, 108, 105, 116, 121,  67, 108,  97, 115, 115, 
  8, 105, 110, 115, 116,  97, 110,  99, 101,  19,  65,  99,  99, 101, 115, 115, 
105,  98, 105, 108, 105, 116, 121,  79,  98, 106, 101,  99, 116,   7, 109, 101, 
116, 104, 111, 100, 115,   4,  97, 117, 116, 111,  16,   5,   1,  22,   2,  22, 
  4,  22,  11,  24,   1,   5,  14,   5,  16,  23,  11,  22,  17,  24,  14,  26, 
 14,  26,  13,   5,  36,  24,  36,  26,  36,   7,   9,   2,   4,   6,   7,   8, 
  9,  10,  11,  12,   8,   2,   4,   7,   8,  12,  13,  14,  15,   1,   4,   5, 
  2,   3,   4,   7,   8,   5,   2,   4,   7,   8,   9,   4,   2,   4,   7,   8, 
 50,   7,   2,   3,   7,   3,   5,   7,   2,   6,   7,   2,   7,   7,   2,   8, 
  7,   2,   9,   7,   2,  10,   7,   4,  12,   7,   2,  13,   9,  15,   1,   9, 
 18,   1,   7,   2,  19,   7,   2,  20,   9,  21,   1,   9,  22,   1,   7,   2, 
 23,   7,   2,  24,   7,   2,  18,   7,   2,  25,   7,   2,  26,   7,   2,  27, 
  7,   2,  28,   7,   2,  29,   7,   2,  15,   7,   2,  30,   7,   2,  31,   7, 
  2,  32,   7,   2,  33,   7,   2,  34,   7,   4,  35,   9,  37,   2,   9,  38, 
  2,   9,  39,   2,   9,  40,   2,   9,  41,   2,   9,  42,   2,   7,   2,  39, 
  7,   2,  37,   7,   2,  40,   7,   2,  38,   7,   2,  41,   7,   2,  42,   7, 
  4,  43,   9,  12,   3,   9,  13,   4,   9,  35,   3,   9,  13,   5,   9,  43, 
  3,   9,  13,   6,  22,   0,   0,   2,   0,   4,   1,   2,   3,   3,   4,   2, 
 40,   1,  10,  10,   0,   1,   2,  32,   0,   4,   2,  32,   0,   0,   2,   0, 
  0,   0,   2,   0,   0,   0,   2,   0,   1,   4,   9,   2,   0,   1,  12,   3, 
  2,   0,   0,   3,   2,   0,   1,  12,   3,   2,   0,   1,   1,   3,   2,   0, 
  0,  13,   2,   0,   1,   3,   3,   2,   0,   1,   0,   3,   2,   0,   0,  13, 
  2,   0,   1,   3,   3,   2,   0,   2,   1,   3,   3,   2,   0,   1,  12,   3, 
  2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   1,  44, 
  3,  45,  47,  49,  46,  48,  50,   3,   8,   9,  11,   5,   0,   4,   0,  30, 
  9,   9,  10,   0,   6,  14,  16,   1,   0,   7,  17,   1,   0,   8,  18,   0, 
  0,   3,   0,  19,   1,   0,   9,  20,   1,   0,  16,  21,   1,   0,  11,  22, 
  1,   0,  13,  23,   1,   0,  12,  24,   0,   0,   4,   0,  25,   1,   0,  14, 
 26,   1,   0,  15,  27,   1,   0,  10,  28,   1,   0,  17,  29,   1,   0,  18, 
 43,   9,   9,  14,   0,  20,   6,  37,   0,   0,  12,   0,  38,   0,   0,  12, 
  0,  39,   0,   0,   4,   0,  40,   0,   0,  12,   0,  41,   0,   0,   4,   0, 
 42,   0,   0,   4,   0,   0,   3,   5,  17,   3,   1,   6,  17,   4,   2,   7, 
 18,   5,   3,   5,   0,  19,   0,   1,  21,   3,  30,   4,   0,   1,  43,   4, 
  0,   2,   8,  68,   0,   0,   1,   0,  19,   0,   1,   1,   3,   4,   3, 208, 
 48,  71,   0,   0,   4,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71, 
  0,   0,   5,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,   6,   2,   1, 
  4,   5,  15, 208,  48, 208,  73,   0, 208,  39, 104,  10, 208,  36,   0, 104, 
 11,  71,   0,   0,   7,   1,   2,   4,   5,   4, 208,  48,  39,  72,   0,   0, 
  8,   1,   2,   4,   5,   4, 208,  48,  32,  72,   0,   0,   9,   1,   1,   4, 
  5,   5, 208,  48,  36,   0,  72,   0,   0,  10,   1,   2,   4,   5,   4, 208, 
 48,  32,  72,   0,   0,  11,   1,   2,   4,   5,   3, 208,  48,  71,   0,   0, 
 12,   1,   1,   4,   5,   4, 208,  48,  32,  72,   0,   0,  13,   3,   2,   4, 
  5,  19, 208,  48,  93,  14, 102,  14,  93,  14, 102,  14,  37, 223,  16,  70, 
 15,   2,  41,  32,  72,   0,   0,  14,   1,   2,   4,   5,   4, 208,  48,  32, 
 72,   0,   0,  15,   1,   1,   4,   5,   4, 208,  48,  32,  72,   0,   0,  16, 
  3,   2,   4,   5,  19, 208,  48,  93,  14, 102,  14,  93,  14, 102,  14,  37, 
224,  16,  70,  15,   2,  41,  32,  72,   0,   0,  17,   1,   3,   4,   5,   3, 
208,  48,  71,   0,   0,  18,   1,   2,   4,   5,   4, 208,  48,  32,  72,   0, 
  0,  19,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,  20,   2,   1,   4, 
  5,  33, 208,  48, 208,  73,   0, 208,  44,   2, 104,  31, 208,  44,   2, 104, 
 32, 208,  44,   2, 104,  33, 208,  39, 104,  34, 208,  39, 104,  35, 208,  39, 
104,  36,  71,   0,   0,  21,   2,   1,   1,   3,  51, 208,  48,  93,  44,  93, 
  9, 102,   9,  48,  93,  45, 102,  45,  88,   0,  29, 104,   8,  93,  46,  93, 
  9, 102,   9,  48,  93,  47, 102,  47,  88,   1,  29, 104,  30,  93,  48,  93, 
  9, 102,   9,  48,  93,  49, 102,  49,  88,   2,  29, 104,  43,  71,   0,   0
};

} }
