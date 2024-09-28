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
    class ObjectInputClass; //flash.utils::ObjectInput$
    class ObjectInputObject; //flash.utils::ObjectInput
    class ObjectOutputClass; //flash.utils::ObjectOutput$
    class ObjectOutputObject; //flash.utils::ObjectOutput
    class ProxyClass; //flash.utils::Proxy$
    class ProxyObject; //flash.utils::Proxy
    class TimerClass; //flash.utils::Timer$
    class TimerObject; //flash.utils::Timer
}

namespace avmplus { namespace NativeID {

extern const uint32_t utils_abc_class_count;
extern const uint32_t utils_abc_script_count;
extern const uint32_t utils_abc_method_count;
extern const uint32_t utils_abc_length;
extern const uint8_t utils_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(utils)

/* classes */
const uint32_t abcclass_flash_utils_Dictionary = 0;
const uint32_t abcclass_flash_utils_Endian = 1;
const uint32_t abcclass_flash_utils_IExternalizable = 2;
const uint32_t abcclass_flash_utils_Proxy = 3;
const uint32_t abcclass_flash_utils_Timer = 4;
const uint32_t abcclass_flash_utils_ObjectInput = 5;
const uint32_t abcclass_flash_utils_ObjectOutput = 6;
const uint32_t abcclass_flash_utils_SetIntervalTimer = 7;

/* methods */
const uint32_t native_script_function_trace = 0;
const uint32_t native_script_function_flash_utils_unescapeMultiByte = 1;
const uint32_t native_script_function_flash_utils_setTimeout = 2;
const uint32_t native_script_function_flash_utils_setInterval = 3;
const uint32_t native_script_function_flash_utils_getTimer = 4;
const uint32_t native_script_function_flash_utils_getQualifiedSuperclassName = 5;
const uint32_t native_script_function_flash_utils_getQualifiedClassName = 6;
const uint32_t native_script_function_flash_utils_getDefinitionByName = 7;
const uint32_t native_script_function_flash_utils_escapeMultiByte = 8;
const uint32_t native_script_function_flash_utils_describeType = 9;
const uint32_t native_script_function_flash_utils_clearTimeout = 10;
const uint32_t native_script_function_flash_utils_clearInterval = 11;
const uint32_t flash_utils_Proxy_flash_utils_isAttribute = 23;
const uint32_t flash_utils_Timer_private__timerDispatch = 34;
const uint32_t flash_utils_Timer_private__start = 38;
const uint32_t flash_utils_Timer_stop = 43;
const uint32_t flash_utils_Timer_running_get = 45;
const uint32_t flash_utils_ObjectInput_readUnsignedInt = 48;
const uint32_t flash_utils_ObjectInput_readByte = 49;
const uint32_t flash_utils_ObjectInput_readShort = 50;
const uint32_t flash_utils_ObjectInput_readDouble = 51;
const uint32_t flash_utils_ObjectInput_readBoolean = 52;
const uint32_t flash_utils_ObjectInput_readUnsignedByte = 53;
const uint32_t flash_utils_ObjectInput_objectEncoding_get = 54;
const uint32_t flash_utils_ObjectInput_readObject = 55;
const uint32_t flash_utils_ObjectInput_readUnsignedShort = 56;
const uint32_t flash_utils_ObjectInput_endian_get = 57;
const uint32_t flash_utils_ObjectInput_bytesAvailable_get = 58;
const uint32_t flash_utils_ObjectInput_objectEncoding_set = 59;
const uint32_t flash_utils_ObjectInput_readMultiByte = 60;
const uint32_t flash_utils_ObjectInput_readFloat = 61;
const uint32_t flash_utils_ObjectInput_readUTF = 62;
const uint32_t flash_utils_ObjectInput_endian_set = 63;
const uint32_t flash_utils_ObjectInput_readInt = 64;
const uint32_t flash_utils_ObjectInput_readUTFBytes = 65;
const uint32_t flash_utils_ObjectInput_readBytes = 66;
const uint32_t flash_utils_ObjectOutput_writeMultiByte = 69;
const uint32_t flash_utils_ObjectOutput_writeUTFBytes = 70;
const uint32_t flash_utils_ObjectOutput_writeObject = 71;
const uint32_t flash_utils_ObjectOutput_writeBoolean = 72;
const uint32_t flash_utils_ObjectOutput_writeBytes = 73;
const uint32_t flash_utils_ObjectOutput_writeByte = 74;
const uint32_t flash_utils_ObjectOutput_writeUTF = 75;
const uint32_t flash_utils_ObjectOutput_writeDouble = 76;
const uint32_t flash_utils_ObjectOutput_writeUnsignedInt = 77;
const uint32_t flash_utils_ObjectOutput_writeShort = 78;
const uint32_t flash_utils_ObjectOutput_writeInt = 79;
const uint32_t flash_utils_ObjectOutput_endian_get = 80;
const uint32_t flash_utils_ObjectOutput_objectEncoding_set = 81;
const uint32_t flash_utils_ObjectOutput_objectEncoding_get = 82;
const uint32_t flash_utils_ObjectOutput_endian_set = 83;
const uint32_t flash_utils_ObjectOutput_writeFloat = 84;

extern AvmBox utils_func_a2a_o_rest_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define native_script_function_trace_thunk  utils_func_a2a_o_rest_thunk

extern double utils_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectInput_readFloat_thunk  utils_d2d_o_thunk
#define flash_utils_ObjectInput_readDouble_thunk  utils_d2d_o_thunk

extern AvmBox utils_v2a_odo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_Timer_private__start_thunk  utils_v2a_odo_thunk

extern AvmBox utils_v2a_oouu_opti0_opti0_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectOutput_writeBytes_thunk  utils_v2a_oouu_opti0_opti0_thunk
#define flash_utils_ObjectInput_readBytes_thunk  utils_v2a_oouu_opti0_opti0_thunk

extern AvmBox utils_u2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectInput_readUnsignedInt_thunk  utils_u2a_o_thunk
#define flash_utils_ObjectInput_bytesAvailable_get_thunk  utils_u2a_o_thunk
#define flash_utils_ObjectInput_readUnsignedShort_thunk  utils_u2a_o_thunk
#define flash_utils_ObjectInput_objectEncoding_get_thunk  utils_u2a_o_thunk
#define flash_utils_ObjectInput_readUnsignedByte_thunk  utils_u2a_o_thunk
#define flash_utils_ObjectOutput_objectEncoding_get_thunk  utils_u2a_o_thunk

extern AvmBox utils_func_s2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define native_script_function_flash_utils_getQualifiedClassName_thunk  utils_func_s2a_oa_thunk
#define native_script_function_flash_utils_getQualifiedSuperclassName_thunk  utils_func_s2a_oa_thunk

extern AvmBox utils_func_s2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define native_script_function_flash_utils_escapeMultiByte_thunk  utils_func_s2a_os_thunk
#define native_script_function_flash_utils_unescapeMultiByte_thunk  utils_func_s2a_os_thunk

extern AvmBox utils_v2a_oi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectOutput_writeByte_thunk  utils_v2a_oi_thunk
#define flash_utils_ObjectOutput_writeShort_thunk  utils_v2a_oi_thunk
#define flash_utils_ObjectOutput_writeInt_thunk  utils_v2a_oi_thunk

extern AvmBox utils_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectInput_readUTF_thunk  utils_s2a_o_thunk
#define flash_utils_ObjectInput_endian_get_thunk  utils_s2a_o_thunk
#define flash_utils_ObjectOutput_endian_get_thunk  utils_s2a_o_thunk

extern AvmBox utils_func_v2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define native_script_function_flash_utils_clearInterval_thunk  utils_func_v2a_ou_thunk
#define native_script_function_flash_utils_clearTimeout_thunk  utils_func_v2a_ou_thunk

extern AvmBox utils_v2a_oss_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectOutput_writeMultiByte_thunk  utils_v2a_oss_thunk

extern AvmBox utils_func_i2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define native_script_function_flash_utils_getTimer_thunk  utils_func_i2a_o_thunk

extern AvmBox utils_i2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectInput_readInt_thunk  utils_i2a_o_thunk
#define flash_utils_ObjectInput_readShort_thunk  utils_i2a_o_thunk
#define flash_utils_ObjectInput_readByte_thunk  utils_i2a_o_thunk

extern AvmBox utils_b2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_Proxy_flash_utils_isAttribute_thunk  utils_b2a_oa_thunk

extern AvmBox utils_s2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectInput_readUTFBytes_thunk  utils_s2a_ou_thunk

extern AvmBox utils_func_a2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define native_script_function_flash_utils_describeType_thunk  utils_func_a2a_oa_thunk

extern AvmBox utils_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_Timer_running_get_thunk  utils_b2a_o_thunk
#define flash_utils_ObjectInput_readBoolean_thunk  utils_b2a_o_thunk

extern AvmBox utils_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectInput_readObject_thunk  utils_a2a_o_thunk

extern AvmBox utils_func_a2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define native_script_function_flash_utils_getDefinitionByName_thunk  utils_func_a2a_os_thunk

extern AvmBox utils_func_u2a_ood_rest_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define native_script_function_flash_utils_setTimeout_thunk  utils_func_u2a_ood_rest_thunk
#define native_script_function_flash_utils_setInterval_thunk  utils_func_u2a_ood_rest_thunk

extern AvmBox utils_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectOutput_writeDouble_thunk  utils_v2a_od_thunk
#define flash_utils_ObjectOutput_writeFloat_thunk  utils_v2a_od_thunk

extern AvmBox utils_v2a_ob_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectOutput_writeBoolean_thunk  utils_v2a_ob_thunk

extern AvmBox utils_v2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectOutput_writeObject_thunk  utils_v2a_oa_thunk

extern AvmBox utils_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_Timer_stop_thunk  utils_v2a_o_thunk
#define flash_utils_Timer_private__timerDispatch_thunk  utils_v2a_o_thunk

extern AvmBox utils_v2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectInput_objectEncoding_set_thunk  utils_v2a_ou_thunk
#define flash_utils_ObjectOutput_objectEncoding_set_thunk  utils_v2a_ou_thunk
#define flash_utils_ObjectOutput_writeUnsignedInt_thunk  utils_v2a_ou_thunk

extern AvmBox utils_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectInput_endian_set_thunk  utils_v2a_os_thunk
#define flash_utils_ObjectOutput_writeUTFBytes_thunk  utils_v2a_os_thunk
#define flash_utils_ObjectOutput_writeUTF_thunk  utils_v2a_os_thunk
#define flash_utils_ObjectOutput_endian_set_thunk  utils_v2a_os_thunk

extern AvmBox utils_s2a_ous_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ObjectInput_readMultiByte_thunk  utils_s2a_ous_thunk

class SlotOffsetsAndAsserts;
// flash.utils::Proxy$
//-----------------------------------------------------------
class ProxyClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ProxyClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ProxyClassSlots EmptySlotsStruct_ProxyClass
//-----------------------------------------------------------

// flash.utils::Proxy
//-----------------------------------------------------------
class ProxyObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ProxyObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ProxyObjectSlots EmptySlotsStruct_ProxyObject
//-----------------------------------------------------------

// flash.utils::Timer$
//-----------------------------------------------------------
class TimerClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TimerClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TimerClassSlots EmptySlotsStruct_TimerClass
//-----------------------------------------------------------

// flash.utils::Timer
//-----------------------------------------------------------
class TimerObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE int32_t get_private_m_repeatCount() const { return m_private_m_repeatCount; }
    void set_private_m_repeatCount(int32_t newVal);
    REALLY_INLINE int32_t get_private_m_iteration() const { return m_private_m_iteration; }
    void set_private_m_iteration(int32_t newVal);
    REALLY_INLINE double get_private_m_delay() const { return m_private_m_delay; }
    void set_private_m_delay(double newVal);
private:
    int32_t m_private_m_repeatCount;
    int32_t m_private_m_iteration;
    double m_private_m_delay;
};
REALLY_INLINE void TimerObjectSlots::set_private_m_repeatCount(int32_t newVal) { m_private_m_repeatCount = newVal; }
REALLY_INLINE void TimerObjectSlots::set_private_m_iteration(int32_t newVal) { m_private_m_iteration = newVal; }
REALLY_INLINE void TimerObjectSlots::set_private_m_delay(double newVal) { m_private_m_delay = newVal; }
#define DECLARE_SLOTS_TimerObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE int32_t get_private_m_repeatCount() const { return m_slots_TimerObject.get_private_m_repeatCount(); } \
        REALLY_INLINE void set_private_m_repeatCount(int32_t newVal) { m_slots_TimerObject.set_private_m_repeatCount(newVal); } \
        REALLY_INLINE int32_t get_private_m_iteration() const { return m_slots_TimerObject.get_private_m_iteration(); } \
        REALLY_INLINE void set_private_m_iteration(int32_t newVal) { m_slots_TimerObject.set_private_m_iteration(newVal); } \
        REALLY_INLINE double get_private_m_delay() const { return m_slots_TimerObject.get_private_m_delay(); } \
        REALLY_INLINE void set_private_m_delay(double newVal) { m_slots_TimerObject.set_private_m_delay(newVal); } \
    private: \
        avmplus::NativeID::TimerObjectSlots m_slots_TimerObject
//-----------------------------------------------------------

// flash.utils::ObjectInput$
//-----------------------------------------------------------
class ObjectInputClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ObjectInputClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ObjectInputClassSlots EmptySlotsStruct_ObjectInputClass
//-----------------------------------------------------------

// flash.utils::ObjectInput
//-----------------------------------------------------------
class ObjectInputObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ObjectInputObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ObjectInputObjectSlots EmptySlotsStruct_ObjectInputObject
//-----------------------------------------------------------

// flash.utils::ObjectOutput$
//-----------------------------------------------------------
class ObjectOutputClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ObjectOutputClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ObjectOutputClassSlots EmptySlotsStruct_ObjectOutputClass
//-----------------------------------------------------------

// flash.utils::ObjectOutput
//-----------------------------------------------------------
class ObjectOutputObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ObjectOutputObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ObjectOutputObjectSlots EmptySlotsStruct_ObjectOutputObject
//-----------------------------------------------------------

} }
