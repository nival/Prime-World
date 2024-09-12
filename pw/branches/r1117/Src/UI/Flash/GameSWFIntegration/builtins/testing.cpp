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

const uint32_t testing_abc_class_count = 3;
const uint32_t testing_abc_script_count = 1;
const uint32_t testing_abc_method_count = 13;
const uint32_t testing_abc_length = 1048;

/* thunks (2 unique signatures, 2 total) */

#ifndef AVMPLUS_INDIRECT_NATIVE_THUNKS
  #error nativegen.py: --directthunks requires AVMFEATURE_INDIRECT_NATIVE_THUNKS=1
#endif


// testing_CoreWrapper_Advance
AvmBox testing_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    CoreWrapperClass* const obj = (CoreWrapperClass*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->Advance(
        AvmThunkUnbox_double(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// testing_TestingFacility_AssertImpl
AvmBox testing_a2a_obs_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmBool32
    };
    (void)argc;
    (void)env;
    TestingFacilityClass* const obj = (TestingFacilityClass*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmBox const ret = obj->AssertImpl(
        AvmThunkUnbox_AvmBool32(argv[argoff1])
        , AvmThunkUnbox_AvmString(argv[argoff2])
    );
    return (AvmBox) ret;
}

class SlotOffsetsAndAsserts
{
private:
    static uint32_t getSlotOffset(Traits* t, int nameId);
public:
    static const uint16_t s_slotsOffsetTestingFacilityClass = offsetof(TestingFacilityClass, m_slots_TestingFacilityClass);
    static const uint16_t s_slotsOffsetTestingFacilityObject = offsetof(TestingFacilityObject, m_slots_TestingFacilityObject);
    static void doTestingFacilityClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetCoreWrapperClass = 0;
    static const uint16_t s_slotsOffsetCoreWrapperObject = 0;
    static void doCoreWrapperClassAsserts(Traits* cTraits, Traits* iTraits);
};
REALLY_INLINE void SlotOffsetsAndAsserts::doTestingFacilityClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    MMGC_STATIC_ASSERT(offsetof(TestingFacilityClass, m_slots_TestingFacilityClass) == s_slotsOffsetTestingFacilityClass);
    MMGC_STATIC_ASSERT(offsetof(TestingFacilityClass, m_slots_TestingFacilityClass) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(TestingFacilityClass) <= 0xFFFF);
    AvmAssert(getSlotOffset(cTraits, 12) == (offsetof(TestingFacilityClass, m_slots_TestingFacilityClass) + offsetof(TestingFacilityClassSlots, m_currentTestName)));
    MMGC_STATIC_ASSERT(offsetof(TestingFacilityObject, m_slots_TestingFacilityObject) == s_slotsOffsetTestingFacilityObject);
    MMGC_STATIC_ASSERT(offsetof(TestingFacilityObject, m_slots_TestingFacilityObject) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(TestingFacilityObject) <= 0xFFFF);
    AvmAssert(getSlotOffset(iTraits, 26) == (offsetof(TestingFacilityObject, m_slots_TestingFacilityObject) + offsetof(TestingFacilityObjectSlots, m_private_tests)));
}
REALLY_INLINE void SlotOffsetsAndAsserts::doCoreWrapperClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(CoreWrapperClass::EmptySlotsStruct_CoreWrapperClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(CoreWrapperObject::EmptySlotsStruct_CoreWrapperObject) >= 0);
}

AVMTHUNK_NATIVE_CLASS_GLUE(TestingFacilityClass, TestingFacilityClass, SlotOffsetsAndAsserts::doTestingFacilityClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(CoreWrapperClass, CoreWrapperClass, SlotOffsetsAndAsserts::doCoreWrapperClassAsserts)

AVMTHUNK_BEGIN_NATIVE_TABLES(testing)
    
    AVMTHUNK_BEGIN_NATIVE_METHODS(testing)
        AVMTHUNK_NATIVE_METHOD(testing_TestingFacility_AssertImpl, TestingFacilityClass::AssertImpl)
        AVMTHUNK_NATIVE_METHOD(testing_CoreWrapper_Advance, CoreWrapperClass::Advance)
    AVMTHUNK_END_NATIVE_METHODS()
    
    AVMTHUNK_BEGIN_NATIVE_CLASSES(testing)
        AVMTHUNK_NATIVE_CLASS(abcclass_testing_TestingFacility, TestingFacilityClass, TestingFacilityClass, SlotOffsetsAndAsserts::s_slotsOffsetTestingFacilityClass, TestingFacilityObject, SlotOffsetsAndAsserts::s_slotsOffsetTestingFacilityObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_testing_CoreWrapper, CoreWrapperClass, CoreWrapperClass, SlotOffsetsAndAsserts::s_slotsOffsetCoreWrapperClass, CoreWrapperObject, SlotOffsetsAndAsserts::s_slotsOffsetCoreWrapperObject)
    AVMTHUNK_END_NATIVE_CLASSES()
    
AVMTHUNK_END_NATIVE_TABLES()

AVMTHUNK_DEFINE_NATIVE_INITIALIZER(testing)

/* abc */
const uint8_t testing_abc_data[1048] = {
 16,   0,  46,   0,   0,   0,   0,  43,  15,  99, 117, 114, 114, 101, 110, 116, 
 84, 101, 115, 116,  78,  97, 109, 101,  12, 116, 101, 115, 116, 105, 110, 103, 
 46,  97, 115,  36,  50,   0,   7, 116, 101, 115, 116, 105, 110, 103,   3,  32, 
 58,  32,  10,  65, 115, 115, 101, 114, 116,  73, 109, 112, 108,   7,  66, 111, 
111, 108, 101,  97, 110,   6,  83, 116, 114, 105, 110, 103,  16, 116, 101, 115, 
116, 105, 110, 103,  58,  84, 101, 115, 116,  73, 110, 102, 111,   4, 116, 101, 
115, 116,   6,  79,  98, 106, 101,  99, 116,   4, 110,  97, 109, 101,   8,  70, 
117, 110,  99, 116, 105, 111, 110,   8,  84, 101, 115, 116,  73, 110, 102, 111, 
 23, 116, 101, 115, 116, 105, 110, 103,  58,  84, 101, 115, 116, 105, 110, 103, 
 70,  97,  99, 105, 108, 105, 116, 121,  13, 110, 111, 116,  32, 115, 112, 101, 
 99, 105, 102, 105, 101, 100,   5, 116, 101, 115, 116, 115,   4, 112, 117, 115, 
104,   4, 118, 111, 105, 100,  23,  84, 101, 115, 116,  32, 110,  97, 109, 101, 
 32, 110, 111, 116,  32, 115, 112, 101,  99, 105, 102, 105, 101, 100,   4,  99, 
 97, 108, 108,   3, 105, 110, 116,   5,  65, 114, 114,  97, 121,  13,  82, 117, 
110,  83, 105, 110, 103, 108, 101,  84, 101, 115, 116,   7, 102, 111, 114,  69, 
 97,  99, 104,   8,  82, 117, 110,  84, 101, 115, 116, 115,   7,  65, 100, 100, 
 84, 101, 115, 116,  15,  84, 101, 115, 116, 105, 110, 103,  70,  97,  99, 105, 
108, 105, 116, 121,  19, 116, 101, 115, 116, 105, 110, 103,  58,  67, 111, 114, 
101,  87, 114,  97, 112, 112, 101, 114,   6,  78, 117, 109,  98, 101, 114,   7, 
 65, 100, 118,  97, 110,  99, 101,  11,  67, 111, 114, 101,  87, 114,  97, 112, 
112, 101, 114,  11,  70, 108,  97, 115, 104,  65, 115, 115, 101, 114, 116,   6, 
110,  97, 116, 105, 118, 101,   3,  99, 108, 115,  20,  84, 101, 115, 116, 105, 
110, 103,  70,  97,  99, 105, 108, 105, 116, 121,  67, 108,  97, 115, 115,   8, 
105, 110, 115, 116,  97, 110,  99, 101,  21,  84, 101, 115, 116, 105, 110, 103, 
 70,  97,  99, 105, 108, 105, 116, 121,  79,  98, 106, 101,  99, 116,   7, 109, 
101, 116, 104, 111, 100, 115,   4,  97, 117, 116, 111,  16,  67, 111, 114, 101, 
 87, 114,  97, 112, 112, 101, 114,  67, 108,  97, 115, 115,  17,  67, 111, 114, 
101,  87, 114,  97, 112, 112, 101, 114,  79,  98, 106, 101,  99, 116,  14,   5, 
  2,  22,   3,  22,   4,  23,   4,   5,   9,  24,   9,  26,   9,  26,  11,   5, 
 15,  24,  15,  26,  15,   5,  29,  24,  29,   4,   4,   1,   2,   3,   4,   8, 
  1,   2,   3,   4,   5,   6,   7,   8,   8,   1,   2,   3,   4,   8,   9,  10, 
 11,  37,   9,   1,   1,   9,   6,   1,   7,   2,   7,   7,   2,   8,   9,  10, 
  2,   9,  12,   2,   7,   2,  13,   7,   2,  10,   7,   2,  12,   7,   4,  14, 
  7,   2,  11,   7,   2,   1,   9,  17,   3,   9,  14,   3,   9,  18,   3,   7, 
  2,  19,   9,  10,   3,   9,   1,   3,   9,  12,   3,   9,  21,   3,   7,   2, 
 22,   7,   2,  23,   9,  24,   3,   9,  25,   3,   9,  23,   3,   7,   9,  17, 
  7,   2,   6,   7,   9,  24,   7,   2,  26,   7,   2,  27,   7,   3,  28,   7, 
  2,  30,   7,   2,  31,   7,   3,  32,   9,  11,   1,   7,   3,  33,  13,   2, 
  0,   3,   4,   3,   0,   0,   0,   3,   0,   2,   0,   7,   4,   3,   0,   0, 
  0,   3,   0,   2,   0,   3,   4,   3,  32,   2,  16,   7,   4,   3,   8,   1, 
 20,   1,   3,  16,   0,  21,  22,   3,   0,   0,  16,   3,   0,   0,   0,   3, 
  0,   0,   0,   3,   0,   1,  16,  32,   3,  32,   0,   0,   3,   0,   0,   0, 
  3,   0,   2,  34,   3,  35,  37,  39,  36,  38,  40,  34,   3,  35,  37,  39, 
 41,  42,  40,   3,  10,  11,   9,   6,   0,   2,   2,   8,   0,   0,   7,   0, 
  9,   0,   0,   4,   0,  31,  11,   9,  10,   0,   8,   4,  26,   0,   0,  22, 
  0,  28,   1,   0,   6,  29,   1,   0,   7,  30,   1,   0,   5,  34,  11,   9, 
 13,   0,  11,   0,   1,   0,   3,   2,  27,  17,   3,   4,  12,   0,   1,   4, 
 16,   1,   9,   1,  33,  17,   3,  10,   1,  12,   4,  36,   1,   1,   0,  10, 
  4,   1,   0,  31,  68,   2,   1,   1,   0,  34,  68,   3,   2,   1,   1,  11, 
  0,   4,   3,   1,   2,  21, 208,  48, 100, 108,   2, 209, 100, 108,   2, 102, 
  1,  44,   5, 160, 210, 160,  70,   2,   2,  41,  71,   0,   0,   1,   1,   1, 
  3,   4,   3, 208,  48,  71,   0,   0,   2,   2,   3,   4,   5,  14, 208,  48, 
208,  73,   0, 208, 209, 104,   5, 208, 210, 104,   6,  71,   0,   0,   3,   2, 
  1,   3,   4,   9, 208,  48,  94,  12,  44,  16,  97,  12,  71,   0,   0,   5, 
  4,   3,   4,   5,  17, 208,  48, 208, 102,  13,  93,  14, 209, 210,  74,  14, 
  2,  70,  15,   1,  41,  71,   0,   0,   6,   2,   5,   4,   5,  25, 208,  48, 
209, 102,  17, 128,   7,  99,   4,  94,  18, 209, 102,  19,  97,  18,  98,   4, 
 98,   4,  70,  20,   1,  41,  71,   0,   0,   7,   2,   1,   4,   5,  13, 208, 
 48, 208, 102,  13, 208, 102,  23,  70,  24,   1,  41,  71,   0,   0,   8,   2, 
  1,   4,   5,  14, 208,  48, 208,  93,  25,  74,  25,   0, 104,  26, 208,  73, 
  0,  71,   0,   0,   9,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,  11, 
  1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  12,   2,   1, 
  1,   3,  51, 208,  48, 101,   0,  93,  11, 102,  11,  48,  93,  35, 102,  35, 
 88,   0,  29, 104,  10, 101,   0,  93,  11, 102,  11,  48,  93,  35, 102,  35, 
 88,   1,  29, 104,  31, 101,   0,  93,  11, 102,  11,  48,  93,  35, 102,  35, 
 88,   2,  29, 104,  34,  71,   0,   0};

} }
