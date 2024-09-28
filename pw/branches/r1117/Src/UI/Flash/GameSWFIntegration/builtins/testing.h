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

#define AVMTHUNK_VERSION 5

namespace avmplus {
    class ArrayObject; //Array
    class CoreWrapperClass; //testing::CoreWrapper$
    class CoreWrapperObject; //testing::CoreWrapper
    class String; //String
    class TestingFacilityClass; //testing::TestingFacility$
    class TestingFacilityObject; //testing::TestingFacility
}

namespace avmplus { namespace NativeID {

extern const uint32_t testing_abc_class_count;
extern const uint32_t testing_abc_script_count;
extern const uint32_t testing_abc_method_count;
extern const uint32_t testing_abc_length;
extern const uint8_t testing_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(testing)

/* classes */
const uint32_t abcclass_testing_TestInfo = 0;
const uint32_t abcclass_testing_TestingFacility = 1;
const uint32_t abcclass_testing_CoreWrapper = 2;

/* methods */
const uint32_t testing_TestingFacility_AssertImpl = 4;
const uint32_t testing_CoreWrapper_Advance = 10;

extern AvmBox testing_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define testing_CoreWrapper_Advance_thunk  testing_v2a_od_thunk

extern AvmBox testing_a2a_obs_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define testing_TestingFacility_AssertImpl_thunk  testing_a2a_obs_thunk

class SlotOffsetsAndAsserts;
// testing::TestingFacility$
//-----------------------------------------------------------
class TestingFacilityClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmString get_currentTestName() const { return m_currentTestName; }
    void set_currentTestName(TestingFacilityClass* obj, AvmString newVal);
private:
    DRCWB(AvmString) m_currentTestName;
};
REALLY_INLINE void TestingFacilityClassSlots::set_currentTestName(TestingFacilityClass* obj, AvmString newVal)
{
    m_currentTestName.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_TestingFacilityClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmString get_currentTestName() const { return m_slots_TestingFacilityClass.get_currentTestName(); } \
        REALLY_INLINE void set_currentTestName(AvmString newVal) { m_slots_TestingFacilityClass.set_currentTestName(this, newVal); } \
    private: \
        avmplus::NativeID::TestingFacilityClassSlots m_slots_TestingFacilityClass
//-----------------------------------------------------------

// testing::TestingFacility
//-----------------------------------------------------------
class TestingFacilityObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE ArrayObject* get_private_tests() const { return m_private_tests; }
    void set_private_tests(TestingFacilityObject* obj, ArrayObject* newVal);
private:
    DRCWB(ArrayObject*) m_private_tests;
};
REALLY_INLINE void TestingFacilityObjectSlots::set_private_tests(TestingFacilityObject* obj, ArrayObject* newVal)
{
    m_private_tests.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_TestingFacilityObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE ArrayObject* get_private_tests() const { return m_slots_TestingFacilityObject.get_private_tests(); } \
        REALLY_INLINE void set_private_tests(ArrayObject* newVal) { m_slots_TestingFacilityObject.set_private_tests(this, newVal); } \
    private: \
        avmplus::NativeID::TestingFacilityObjectSlots m_slots_TestingFacilityObject
//-----------------------------------------------------------

// testing::CoreWrapper$
//-----------------------------------------------------------
class CoreWrapperClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_CoreWrapperClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::CoreWrapperClassSlots EmptySlotsStruct_CoreWrapperClass
//-----------------------------------------------------------

// testing::CoreWrapper
//-----------------------------------------------------------
class CoreWrapperObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_CoreWrapperObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::CoreWrapperObjectSlots EmptySlotsStruct_CoreWrapperObject
//-----------------------------------------------------------

} }
