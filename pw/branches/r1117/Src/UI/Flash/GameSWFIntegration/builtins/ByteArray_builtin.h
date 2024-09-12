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
    class ByteArrayClass; //flash.utils::ByteArray$
    class ByteArrayObject; //flash.utils::ByteArray
}

namespace avmplus { namespace NativeID {

extern const uint32_t ByteArray_builtin_abc_class_count;
extern const uint32_t ByteArray_builtin_abc_script_count;
extern const uint32_t ByteArray_builtin_abc_method_count;
extern const uint32_t ByteArray_builtin_abc_length;
extern const uint8_t ByteArray_builtin_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(ByteArray_builtin)

/* classes */
const uint32_t abcclass_flash_utils_IDataInput = 0;
const uint32_t abcclass_flash_utils_IDataOutput = 1;
const uint32_t abcclass_flash_utils_ByteArray = 2;

/* methods */
const uint32_t flash_utils_ByteArray_defaultObjectEncoding_get = 40;
const uint32_t flash_utils_ByteArray_defaultObjectEncoding_set = 41;
const uint32_t flash_utils_ByteArray_writeUTFBytes = 43;
const uint32_t flash_utils_ByteArray_readShort = 44;
const uint32_t flash_utils_ByteArray_writeByte = 45;
const uint32_t flash_utils_ByteArray_writeDouble = 46;
const uint32_t flash_utils_ByteArray_readUnsignedShort = 47;
const uint32_t flash_utils_ByteArray_readDouble = 48;
const uint32_t flash_utils_ByteArray_writeInt = 49;
const uint32_t flash_utils_ByteArray_private__uncompress = 50;
const uint32_t flash_utils_ByteArray_endian_get = 51;
const uint32_t flash_utils_ByteArray_bytesAvailable_get = 52;
const uint32_t flash_utils_ByteArray_readObject = 53;
const uint32_t flash_utils_ByteArray_position_get = 55;
const uint32_t flash_utils_ByteArray_readBoolean = 56;
const uint32_t flash_utils_ByteArray_endian_set = 58;
const uint32_t flash_utils_ByteArray_readUTF = 59;
const uint32_t flash_utils_ByteArray_readUTFBytes = 60;
const uint32_t flash_utils_ByteArray_writeFloat = 61;
const uint32_t flash_utils_ByteArray_writeMultiByte = 62;
const uint32_t flash_utils_ByteArray_readUnsignedInt = 63;
const uint32_t flash_utils_ByteArray_readByte = 64;
const uint32_t flash_utils_ByteArray_objectEncoding_get = 65;
const uint32_t flash_utils_ByteArray_writeBytes = 66;
const uint32_t flash_utils_ByteArray_clear = 67;
const uint32_t flash_utils_ByteArray_writeUTF = 68;
const uint32_t flash_utils_ByteArray_writeBoolean = 69;
const uint32_t flash_utils_ByteArray_position_set = 70;
const uint32_t flash_utils_ByteArray_private__compress = 71;
const uint32_t flash_utils_ByteArray_readUnsignedByte = 72;
const uint32_t flash_utils_ByteArray_writeUnsignedInt = 73;
const uint32_t flash_utils_ByteArray_writeShort = 74;
const uint32_t flash_utils_ByteArray_length_get = 75;
const uint32_t flash_utils_ByteArray_toString = 77;
const uint32_t flash_utils_ByteArray_length_set = 78;
const uint32_t flash_utils_ByteArray_objectEncoding_set = 79;
const uint32_t flash_utils_ByteArray_readFloat = 80;
const uint32_t flash_utils_ByteArray_readInt = 81;
const uint32_t flash_utils_ByteArray_readMultiByte = 82;
const uint32_t flash_utils_ByteArray_readBytes = 84;
const uint32_t flash_utils_ByteArray_writeObject = 85;

extern AvmBox ByteArray_builtin_v2a_oss_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_writeMultiByte_thunk  ByteArray_builtin_v2a_oss_thunk

extern AvmBox ByteArray_builtin_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_writeFloat_thunk  ByteArray_builtin_v2a_od_thunk
#define flash_utils_ByteArray_writeDouble_thunk  ByteArray_builtin_v2a_od_thunk

extern double ByteArray_builtin_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_readFloat_thunk  ByteArray_builtin_d2d_o_thunk
#define flash_utils_ByteArray_readDouble_thunk  ByteArray_builtin_d2d_o_thunk

extern AvmBox ByteArray_builtin_v2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_writeObject_thunk  ByteArray_builtin_v2a_oa_thunk

extern AvmBox ByteArray_builtin_v2a_oouu_opti0_opti0_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_writeBytes_thunk  ByteArray_builtin_v2a_oouu_opti0_opti0_thunk
#define flash_utils_ByteArray_readBytes_thunk  ByteArray_builtin_v2a_oouu_opti0_opti0_thunk

extern AvmBox ByteArray_builtin_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_readBoolean_thunk  ByteArray_builtin_b2a_o_thunk

extern AvmBox ByteArray_builtin_u2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_readUnsignedShort_thunk  ByteArray_builtin_u2a_o_thunk
#define flash_utils_ByteArray_defaultObjectEncoding_get_thunk  ByteArray_builtin_u2a_o_thunk
#define flash_utils_ByteArray_bytesAvailable_get_thunk  ByteArray_builtin_u2a_o_thunk
#define flash_utils_ByteArray_length_get_thunk  ByteArray_builtin_u2a_o_thunk
#define flash_utils_ByteArray_readUnsignedInt_thunk  ByteArray_builtin_u2a_o_thunk
#define flash_utils_ByteArray_readUnsignedByte_thunk  ByteArray_builtin_u2a_o_thunk
#define flash_utils_ByteArray_objectEncoding_get_thunk  ByteArray_builtin_u2a_o_thunk
#define flash_utils_ByteArray_position_get_thunk  ByteArray_builtin_u2a_o_thunk

extern AvmBox ByteArray_builtin_v2a_oi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_writeByte_thunk  ByteArray_builtin_v2a_oi_thunk
#define flash_utils_ByteArray_writeInt_thunk  ByteArray_builtin_v2a_oi_thunk
#define flash_utils_ByteArray_writeShort_thunk  ByteArray_builtin_v2a_oi_thunk

extern AvmBox ByteArray_builtin_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_readObject_thunk  ByteArray_builtin_a2a_o_thunk

extern AvmBox ByteArray_builtin_v2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_objectEncoding_set_thunk  ByteArray_builtin_v2a_ou_thunk
#define flash_utils_ByteArray_position_set_thunk  ByteArray_builtin_v2a_ou_thunk
#define flash_utils_ByteArray_defaultObjectEncoding_set_thunk  ByteArray_builtin_v2a_ou_thunk
#define flash_utils_ByteArray_length_set_thunk  ByteArray_builtin_v2a_ou_thunk
#define flash_utils_ByteArray_writeUnsignedInt_thunk  ByteArray_builtin_v2a_ou_thunk

extern AvmBox ByteArray_builtin_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_writeUTF_thunk  ByteArray_builtin_v2a_os_thunk
#define flash_utils_ByteArray_endian_set_thunk  ByteArray_builtin_v2a_os_thunk
#define flash_utils_ByteArray_private__compress_thunk  ByteArray_builtin_v2a_os_thunk
#define flash_utils_ByteArray_private__uncompress_thunk  ByteArray_builtin_v2a_os_thunk
#define flash_utils_ByteArray_writeUTFBytes_thunk  ByteArray_builtin_v2a_os_thunk

extern AvmBox ByteArray_builtin_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_clear_thunk  ByteArray_builtin_v2a_o_thunk

extern AvmBox ByteArray_builtin_s2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_readUTFBytes_thunk  ByteArray_builtin_s2a_ou_thunk

extern AvmBox ByteArray_builtin_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_readUTF_thunk  ByteArray_builtin_s2a_o_thunk
#define flash_utils_ByteArray_toString_thunk  ByteArray_builtin_s2a_o_thunk
#define flash_utils_ByteArray_endian_get_thunk  ByteArray_builtin_s2a_o_thunk

extern AvmBox ByteArray_builtin_i2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_readInt_thunk  ByteArray_builtin_i2a_o_thunk
#define flash_utils_ByteArray_readShort_thunk  ByteArray_builtin_i2a_o_thunk
#define flash_utils_ByteArray_readByte_thunk  ByteArray_builtin_i2a_o_thunk

extern AvmBox ByteArray_builtin_s2a_ous_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_readMultiByte_thunk  ByteArray_builtin_s2a_ous_thunk

extern AvmBox ByteArray_builtin_v2a_ob_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_utils_ByteArray_writeBoolean_thunk  ByteArray_builtin_v2a_ob_thunk

class SlotOffsetsAndAsserts;
// flash.utils::ByteArray$
//-----------------------------------------------------------
class ByteArrayClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ByteArrayClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ByteArrayClassSlots EmptySlotsStruct_ByteArrayClass
//-----------------------------------------------------------

// flash.utils::ByteArray
//-----------------------------------------------------------
class ByteArrayObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ByteArrayObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ByteArrayObjectSlots EmptySlotsStruct_ByteArrayObject
//-----------------------------------------------------------

} }
