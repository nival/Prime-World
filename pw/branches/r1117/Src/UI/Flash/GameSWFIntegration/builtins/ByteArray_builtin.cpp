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

const uint32_t ByteArray_builtin_abc_class_count = 3;
const uint32_t ByteArray_builtin_abc_script_count = 1;
const uint32_t ByteArray_builtin_abc_method_count = 87;
const uint32_t ByteArray_builtin_abc_length = 2003;

/* thunks (17 unique signatures, 41 total) */

#ifndef AVMPLUS_INDIRECT_NATIVE_THUNKS
  #error nativegen.py: --directthunks requires AVMFEATURE_INDIRECT_NATIVE_THUNKS=1
#endif


// flash_utils_ByteArray_writeMultiByte
AvmBox ByteArray_builtin_v2a_oss_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmString
    };
    (void)argc;
    (void)env;
    ByteArrayObject* const obj = (ByteArrayObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->writeMultiByte(
        AvmThunkUnbox_AvmString(argv[argoff1])
        , AvmThunkUnbox_AvmString(argv[argoff2])
    );
    return kAvmThunkUndefined;
}

// flash_utils_ByteArray_writeFloat
// flash_utils_ByteArray_writeDouble
AvmBox ByteArray_builtin_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    typedef AvmRetType_void (AvmObjectT::*FuncType)(double);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    (*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
        AvmThunkUnbox_double(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_utils_ByteArray_readFloat
// flash_utils_ByteArray_readDouble
double ByteArray_builtin_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    typedef AvmRetType_double (AvmObjectT::*FuncType)();
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    return (*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
    );
}

// flash_utils_ByteArray_writeObject
AvmBox ByteArray_builtin_v2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    ByteArrayObject* const obj = (ByteArrayObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->writeObject(
        AvmThunkUnbox_AvmBox(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_utils_ByteArray_writeBytes
// flash_utils_ByteArray_readBytes
AvmBox ByteArray_builtin_v2a_oouu_opti0_opti0_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmObject
        , argoff3 = argoff2 + AvmThunkArgSize_uint32_t
    };
    typedef AvmRetType_void (AvmObjectT::*FuncType)(AvmObject, uint32_t, uint32_t);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    (*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
        AvmThunkUnbox_AvmObject(argv[argoff1])
        , (argc < 2 ? AvmThunkCoerce_int32_t_uint32_t(0) : AvmThunkUnbox_uint32_t(argv[argoff2]))
        , (argc < 3 ? AvmThunkCoerce_int32_t_uint32_t(0) : AvmThunkUnbox_uint32_t(argv[argoff3]))
    );
    return kAvmThunkUndefined;
}

// flash_utils_ByteArray_readBoolean
AvmBox ByteArray_builtin_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    ByteArrayObject* const obj = (ByteArrayObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmBool32 const ret = obj->readBoolean();
    return (AvmBox) ret;
}

// flash_utils_ByteArray_readUnsignedShort
// flash_utils_ByteArray_defaultObjectEncoding_get
// flash_utils_ByteArray_bytesAvailable_get
// flash_utils_ByteArray_length_get
// flash_utils_ByteArray_readUnsignedInt
// flash_utils_ByteArray_readUnsignedByte
// flash_utils_ByteArray_objectEncoding_get
// flash_utils_ByteArray_position_get
AvmBox ByteArray_builtin_u2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    typedef AvmRetType_uint32_t (AvmObjectT::*FuncType)();
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    return (AvmBox)(*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
    );
}

// flash_utils_ByteArray_writeByte
// flash_utils_ByteArray_writeInt
// flash_utils_ByteArray_writeShort
AvmBox ByteArray_builtin_v2a_oi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    typedef AvmRetType_void (AvmObjectT::*FuncType)(int32_t);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    (*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
        AvmThunkUnbox_int32_t(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_utils_ByteArray_readObject
AvmBox ByteArray_builtin_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    ByteArrayObject* const obj = (ByteArrayObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmBox const ret = obj->readObject();
    return (AvmBox) ret;
}

// flash_utils_ByteArray_objectEncoding_set
// flash_utils_ByteArray_position_set
// flash_utils_ByteArray_defaultObjectEncoding_set
// flash_utils_ByteArray_length_set
// flash_utils_ByteArray_writeUnsignedInt
AvmBox ByteArray_builtin_v2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    typedef AvmRetType_void (AvmObjectT::*FuncType)(uint32_t);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    (*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
        AvmThunkUnbox_uint32_t(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_utils_ByteArray_writeUTF
// flash_utils_ByteArray_endian_set
// flash_utils_ByteArray_private__compress
// flash_utils_ByteArray_private__uncompress
// flash_utils_ByteArray_writeUTFBytes
AvmBox ByteArray_builtin_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_utils_ByteArray_clear
AvmBox ByteArray_builtin_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    ByteArrayObject* const obj = (ByteArrayObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->clear();
    return kAvmThunkUndefined;
}

// flash_utils_ByteArray_readUTFBytes
AvmBox ByteArray_builtin_s2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    ByteArrayObject* const obj = (ByteArrayObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmString const ret = obj->readUTFBytes(
        AvmThunkUnbox_uint32_t(argv[argoff1])
    );
    return (AvmBox) ret;
}

// flash_utils_ByteArray_readUTF
// flash_utils_ByteArray_toString
// flash_utils_ByteArray_endian_get
AvmBox ByteArray_builtin_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_utils_ByteArray_readInt
// flash_utils_ByteArray_readShort
// flash_utils_ByteArray_readByte
AvmBox ByteArray_builtin_i2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    typedef AvmRetType_int32_t (AvmObjectT::*FuncType)();
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    return (AvmBox)(*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
    );
}

// flash_utils_ByteArray_readMultiByte
AvmBox ByteArray_builtin_s2a_ous_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_uint32_t
    };
    (void)argc;
    (void)env;
    ByteArrayObject* const obj = (ByteArrayObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmString const ret = obj->readMultiByte(
        AvmThunkUnbox_uint32_t(argv[argoff1])
        , AvmThunkUnbox_AvmString(argv[argoff2])
    );
    return (AvmBox) ret;
}

// flash_utils_ByteArray_writeBoolean
AvmBox ByteArray_builtin_v2a_ob_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    ByteArrayObject* const obj = (ByteArrayObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->writeBoolean(
        AvmThunkUnbox_AvmBool32(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

class SlotOffsetsAndAsserts
{
private:
    static uint32_t getSlotOffset(Traits* t, int nameId);
public:
    static const uint16_t s_slotsOffsetByteArrayClass = 0;
    static const uint16_t s_slotsOffsetByteArrayObject = 0;
    static void doByteArrayClassAsserts(Traits* cTraits, Traits* iTraits);
};
REALLY_INLINE void SlotOffsetsAndAsserts::doByteArrayClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(ByteArrayClass::EmptySlotsStruct_ByteArrayClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(ByteArrayObject::EmptySlotsStruct_ByteArrayObject) >= 0);
}

AVMTHUNK_NATIVE_CLASS_GLUE(ByteArrayClass, ByteArrayClass, SlotOffsetsAndAsserts::doByteArrayClassAsserts)

AVMTHUNK_BEGIN_NATIVE_TABLES(ByteArray_builtin)
    
    AVMTHUNK_BEGIN_NATIVE_METHODS(ByteArray_builtin)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_defaultObjectEncoding_get, ByteArrayClass::get_defaultObjectEncoding)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_defaultObjectEncoding_set, ByteArrayClass::set_defaultObjectEncoding)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_writeUTFBytes, ByteArrayObject::writeUTFBytes)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readShort, ByteArrayObject::readShort)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_writeByte, ByteArrayObject::writeByte)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_writeDouble, ByteArrayObject::writeDouble)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readUnsignedShort, ByteArrayObject::readUnsignedShort)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readDouble, ByteArrayObject::readDouble)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_writeInt, ByteArrayObject::writeInt)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_private__uncompress, ByteArrayObject::_uncompress)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_endian_get, ByteArrayObject::get_endian)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_bytesAvailable_get, ByteArrayObject::get_bytesAvailable)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readObject, ByteArrayObject::readObject)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_position_get, ByteArrayObject::get_position)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readBoolean, ByteArrayObject::readBoolean)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_endian_set, ByteArrayObject::set_endian)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readUTF, ByteArrayObject::readUTF)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readUTFBytes, ByteArrayObject::readUTFBytes)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_writeFloat, ByteArrayObject::writeFloat)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_writeMultiByte, ByteArrayObject::writeMultiByte)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readUnsignedInt, ByteArrayObject::readUnsignedInt)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readByte, ByteArrayObject::readByte)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_objectEncoding_get, ByteArrayObject::get_objectEncoding)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_writeBytes, ByteArrayObject::writeBytes)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_clear, ByteArrayObject::clear)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_writeUTF, ByteArrayObject::writeUTF)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_writeBoolean, ByteArrayObject::writeBoolean)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_position_set, ByteArrayObject::set_position)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_private__compress, ByteArrayObject::_compress)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readUnsignedByte, ByteArrayObject::readUnsignedByte)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_writeUnsignedInt, ByteArrayObject::writeUnsignedInt)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_writeShort, ByteArrayObject::writeShort)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_length_get, ByteArrayObject::get_length)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_toString, ByteArrayObject::toString)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_length_set, ByteArrayObject::set_length)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_objectEncoding_set, ByteArrayObject::set_objectEncoding)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readFloat, ByteArrayObject::readFloat)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readInt, ByteArrayObject::readInt)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readMultiByte, ByteArrayObject::readMultiByte)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_readBytes, ByteArrayObject::readBytes)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ByteArray_writeObject, ByteArrayObject::writeObject)
    AVMTHUNK_END_NATIVE_METHODS()
    
    AVMTHUNK_BEGIN_NATIVE_CLASSES(ByteArray_builtin)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_utils_ByteArray, ByteArrayClass, ByteArrayClass, SlotOffsetsAndAsserts::s_slotsOffsetByteArrayClass, ByteArrayObject, SlotOffsetsAndAsserts::s_slotsOffsetByteArrayObject)
    AVMTHUNK_END_NATIVE_CLASSES()
    
AVMTHUNK_END_NATIVE_TABLES()

AVMTHUNK_DEFINE_NATIVE_INITIALIZER(ByteArray_builtin)

/* abc */
const uint8_t ByteArray_builtin_abc_data[2003] = {
 16,   0,  46,   0,   2,   0,   0,   0,  66,   0,   4, 117, 105, 110, 116,   3, 
105, 110, 116,   6,  78, 117, 109,  98, 101, 114,   6,  83, 116, 114, 105, 110, 
103,   7,  66, 111, 111, 108, 101,  97, 110,   4, 118, 111, 105, 100,  11, 102, 
108,  97, 115, 104,  46, 117, 116, 105, 108, 115,   9,  66, 121, 116, 101,  65, 
114, 114,  97, 121,  22, 102, 108,  97, 115, 104,  46, 117, 116, 105, 108, 115, 
 58,  73,  68,  97, 116,  97,  73, 110, 112, 117, 116,   7, 114, 101,  97, 100, 
 73, 110, 116,  12, 114, 101,  97, 100,  85,  84,  70,  66, 121, 116, 101, 115, 
 15, 114, 101,  97, 100,  85, 110, 115, 105, 103, 110, 101, 100,  73, 110, 116, 
  8, 114, 101,  97, 100,  66, 121, 116, 101,   9, 114, 101,  97, 100,  83, 104, 
111, 114, 116,  10, 114, 101,  97, 100,  68, 111, 117,  98, 108, 101,  13, 114, 
101,  97, 100,  77, 117, 108, 116, 105,  66, 121, 116, 101,   9, 114, 101,  97, 
100,  70, 108, 111,  97, 116,  17, 114, 101,  97, 100,  85, 110, 115, 105, 103, 
110, 101, 100,  83, 104, 111, 114, 116,  14, 111,  98, 106, 101,  99, 116,  69, 
110,  99, 111, 100, 105, 110, 103,   9, 114, 101,  97, 100,  66, 121, 116, 101, 
115,   6, 101, 110, 100, 105,  97, 110,   7, 114, 101,  97, 100,  85,  84,  70, 
 11, 114, 101,  97, 100,  66, 111, 111, 108, 101,  97, 110,  16, 114, 101,  97, 
100,  85, 110, 115, 105, 103, 110, 101, 100,  66, 121, 116, 101,  10, 114, 101, 
 97, 100,  79,  98, 106, 101,  99, 116,  14,  98, 121, 116, 101, 115,  65, 118, 
 97, 105, 108,  97,  98, 108, 101,  10,  73,  68,  97, 116,  97,  73, 110, 112, 
117, 116,  23, 102, 108,  97, 115, 104,  46, 117, 116, 105, 108, 115,  58,  73, 
 68,  97, 116,  97,  79, 117, 116, 112, 117, 116,  14, 119, 114, 105, 116, 101, 
 77, 117, 108, 116, 105,  66, 121, 116, 101,  13, 119, 114, 105, 116, 101,  85, 
 84,  70,  66, 121, 116, 101, 115,   9, 119, 114, 105, 116, 101,  66, 121, 116, 
101,   8, 119, 114, 105, 116, 101,  85,  84,  70,  12, 119, 114, 105, 116, 101, 
 66, 111, 111, 108, 101,  97, 110,  16, 119, 114, 105, 116, 101,  85, 110, 115, 
105, 103, 110, 101, 100,  73, 110, 116,  10, 119, 114, 105, 116, 101,  66, 121, 
116, 101, 115,   8, 119, 114, 105, 116, 101,  73, 110, 116,  10, 119, 114, 105, 
116, 101,  70, 108, 111,  97, 116,  11, 119, 114, 105, 116, 101,  68, 111, 117, 
 98, 108, 101,  10, 119, 114, 105, 116, 101,  83, 104, 111, 114, 116,  11, 119, 
114, 105, 116, 101,  79,  98, 106, 101,  99, 116,  11,  73,  68,  97, 116,  97, 
 79, 117, 116, 112, 117, 116,  21, 102, 108,  97, 115, 104,  46, 117, 116, 105, 
108, 115,  58,  66, 121, 116, 101,  65, 114, 114,  97, 121,   7, 100, 101, 102, 
108,  97, 116, 101,   9,  95,  99, 111, 109, 112, 114, 101, 115, 115,  22,  66, 
121, 116, 101,  65, 114, 114,  97, 121,  95,  98, 117, 105, 108, 116, 105, 110, 
 46,  97, 115,  36,  50,   6,  79,  98, 106, 101,  99, 116,  11,  95, 117, 110, 
 99, 111, 109, 112, 114, 101, 115, 115,   4, 122, 108, 105,  98,  21, 100, 101, 
102,  97, 117, 108, 116,  79,  98, 106, 101,  99, 116,  69, 110,  99, 111, 100, 
105, 110, 103,  21,  66, 121, 116, 101,  65, 114, 114,  97, 121,  95, 105, 109, 
112, 111, 114, 116,  46,  97, 115,  36,  49,   7, 105, 110, 102, 108,  97, 116, 
101,   8, 112, 111, 115, 105, 116, 105, 111, 110,   5,  99, 108, 101,  97, 114, 
  6, 108, 101, 110, 103, 116, 104,   8,  99, 111, 109, 112, 114, 101, 115, 115, 
  8, 116, 111,  83, 116, 114, 105, 110, 103,  10, 117, 110,  99, 111, 109, 112, 
114, 101, 115, 115,   6, 110,  97, 116, 105, 118, 101,   3,  99, 108, 115,  14, 
 66, 121, 116, 101,  65, 114, 114,  97, 121,  67, 108,  97, 115, 115,   8, 105, 
110, 115, 116,  97, 110,  99, 101,  15,  66, 121, 116, 101,  65, 114, 114,  97, 
121,  79,  98, 106, 101,  99, 116,   7, 109, 101, 116, 104, 111, 100, 115,   4, 
 97, 117, 116, 111,  12,  22,   1,  22,   8,   8,  10,   8,  29,   5,  43,   5, 
 46,  23,   8,  24,  43,  26,  43,  26,  47,   5,  51,   4,   8,   1,   2,   5, 
  6,   7,   8,   9,  10,   4,   1,   2,   7,  11,   4,   1,   2,   6,   7,  89, 
  7,   1,   2,   7,   1,   3,   7,   1,   4,   7,   1,   5,   7,   1,   6,   7, 
  1,   7,   7,   2,   9,   7,   3,  11,   7,   3,  12,   7,   3,  13,   7,   3, 
 14,   7,   3,  15,   7,   3,  16,   7,   3,  17,   7,   3,  18,   7,   3,  19, 
  7,   3,  20,   7,   3,  21,   7,   3,  22,   7,   3,  23,   7,   3,  24,   7, 
  3,  25,   7,   3,  26,   7,   3,  27,   7,   2,  28,   7,   4,  30,   7,   4, 
 31,   7,   4,  20,   7,   4,  32,   7,   4,  33,   7,   4,  34,   7,   4,  35, 
  7,   4,  36,   7,   4,  37,   7,   4,  38,   7,   4,  22,   7,   4,  39,   7, 
  4,  40,   7,   4,  41,   7,   2,  42,   9,  45,   1,   9,  48,   1,   7,   1, 
 50,   9,  28,   2,   9,  42,   2,   9,  28,   3,   9,  42,   3,   7,   1,  21, 
  7,   1,  41,   7,   1,  52,   7,   1,  31,   7,   1,  15,   7,   1,  32,   7, 
  1,  37,   7,   1,  19,   7,   1,  16,   7,   1,  39,   7,   5,  48,   7,   1, 
 22,   7,   1,  27,   7,   1,  53,   7,   1,  44,   7,   1,  23,   7,   1,  20, 
  7,   1,  38,   7,   1,  30,   7,   1,  13,   7,   1,  33,   7,   1,  24,   7, 
  1,  54,   7,   1,  34,   7,   1,  12,   7,   1,  36,   7,   1,  25,   7,   1, 
 40,   7,   1,  14,   7,   5,  45,   7,   1,  55,   7,   1,  56,   7,   1,  35, 
  7,   1,  57,   7,   1,  18,   7,   1,  17,   7,   1,  26,   7,   1,  11,   7, 
  1,  58,   7,   1,  47,   9,  47,   3,  87,   0,   0,   1,   0,   0,   0,   1, 
  0,   0,   1,   1,   0,   0,   1,   1,   0,   0,   1,   1,   0,   0,   2,   1, 
  0,   0,   3,   1,   0,   2,   4,   1,   4,   1,   0,   0,   3,   1,   0,   0, 
  1,   1,   0,   0,   5,   1,   0,   0,   1,   1,   0,   3,   6,   7,   1,   1, 
  1,   8,   2,   1,   3,   1,   3,   1,   6,   4,   1,   0,   0,   4,   1,   0, 
  0,   2,   1,   0,   1,   4,   1,   1,   0,   0,   4,   1,   0,   0,   0,   1, 
  0,   1,   6,   1,   1,   0,   0,   2,   1,   0,   0,   0,   1,   0,   0,   0, 
  1,   0,   2,   6,   4,   4,   1,   0,   1,   6,   4,   1,   0,   1,   6,   2, 
  1,   0,   1,   6,   2,   1,   0,   1,   6,   4,   1,   0,   1,   6,   5,   1, 
  0,   0,   4,   1,   0,   1,   6,   1,   1,   0,   3,   6,   7,   1,   1,   1, 
  8,   2,   1,   3,   1,   3,   1,   6,   2,   1,   0,   0,   1,   1,   0,   1, 
  6,   4,   1,   0,   1,   6,   3,   1,   0,   1,   6,   1,   1,   0,   1,   6, 
  3,   1,   0,   1,   6,   0,   1,   0,   0,   0,   1,   0,   0,   1,   1,  32, 
  1,   6,   1,   1,  32,   0,   0,   1,   0,   1,   6,   4,   1,  32,   0,   2, 
  1,  32,   1,   6,   2,   1,  32,   1,   6,   3,   1,  32,   0,   1,   1,  32, 
  0,   3,   1,  32,   1,   6,   2,   1,  32,   1,   6,   4,   1,  32,   0,   4, 
  1,  32,   0,   1,   1,  32,   0,   0,   1,  32,   0,   6,   1,   0,   0,   1, 
  1,  32,   0,   5,   1,  32,   0,   6,   1,   0,   1,   6,   4,   1,  32,   0, 
  4,   1,  32,   1,   4,   1,   1,  32,   1,   6,   3,   1,  32,   2,   6,   4, 
  4,   1,  32,   0,   1,   1,  32,   0,   2,   1,  32,   0,   1,   1,  32,   3, 
  6,   7,   1,   1,   1,  40,   2,   1,   3,   1,   3,   0,   6,   1,  32,   1, 
  6,   4,   1,  32,   1,   6,   5,   1,  32,   1,   6,   1,   1,  32,   1,   6, 
  4,   1,  32,   0,   1,   1,  32,   1,   6,   1,   1,  32,   1,   6,   2,   1, 
 32,   0,   1,   1,  32,   0,   6,   1,   0,   0,   4,   1,  32,   1,   6,   1, 
  1,  32,   1,   6,   1,   1,  32,   0,   3,   1,  32,   0,   2,   1,  32,   2, 
  4,   1,   4,   1,  32,   0,   6,   1,   0,   3,   6,   7,   1,   1,   1,  40, 
  2,   1,   3,   1,   3,   1,   6,   0,   1,  32,   0,   0,   1,   0,   1,  59, 
  3,  60,  62,  64,  61,  63,  65,   3,  25,   0,   5,   0,   1,  19,   8,   1, 
  0,  15,   9,   1,   0,  16,  10,   1,   0,   3,  11,   1,   0,  20,  12,   1, 
  0,   5,  13,   1,   0,   6,  14,   1,   0,   7,  15,   1,   0,   8,  16,   1, 
  0,   9,  17,   2,   0,   2,  18,   1,   0,  12,  19,   3,   0,  13,  20,   1, 
  0,  14,  21,   1,   0,  10,  22,   1,   0,  11,  19,   2,   0,  17,  23,   1, 
  0,  18,  17,   3,   0,  19,  24,   2,   0,   4,  40,   0,   5,   0,  22,  16, 
 26,   1,   0,  23,  27,   1,   0,  24,  28,   3,   0,  30,  29,   1,   0,  26, 
 30,   1,   0,  27,  31,   1,   0,  28,  32,   1,   0,  36,  33,   1,   0,  31, 
 34,   1,   0,  32,  28,   2,   0,  33,  35,   1,   0,  37,  36,   3,   0,  34, 
 37,   1,   0,  35,  36,   2,   0,  29,  38,   1,   0,  25,  39,   1,   0,  38, 
  7,  87,   9,   8,   4,  44,  45,  46,  47,  42,  43,  48,   1,   0,  84,  49, 
  1,   0,  85,  50,   1,   0,  57,  51,   1,   0,  43,  52,   1,   0,  44,  53, 
  1,   0,  45,  54,   1,   0,  49,  55,   1,   0,  47,  56,   1,   0,  48,  57, 
  1,   0,  46,  58,   1,   0,  50,  59,   2,   0,  51,  60,   2,   0,  52,  61, 
  2,   0,  55,  62,   1,   0,  54,  63,   1,   0,  59,  64,   2,   0,  65,  65, 
  1,   0,  61,  66,   1,   0,  62,  67,   1,   0,  63,  59,   3,   0,  58,  68, 
  1,   0,  68,  69,   1,   0,  56,  70,   1,   0,  67,  71,   1,   0,  69,  72, 
  1,   0,  60,  73,   1,   0,  66,  61,   3,   0,  70,  74,   1,   0,  72,  75, 
  1,   0,  74,  76,   1,   0,  64,  77,   1,   0,  71,  78,   2,   0,  75,  79, 
  1,   0,  76,  80,   1,   0,  73,  64,   3,   0,  79,  81,   1,   0,  77,  82, 
  1,   0,  80,  78,   3,   0,  78,  83,   1,   0,  82,  84,   1,   0,  53,  85, 
  1,   0,  81,  86,   1,   0,  83,   0,   0,  21,   0,  39,   2,  43,  18,   3, 
 40,  43,  19,   4,  41,   1,  86,   3,   7,  68,   3,   2,   1,   0,  40,   4, 
  2,   1,  25,   4,   1,   0,   9,   0,   0,   1,   3,   3,   1,  71,   0,   0, 
 21,   0,   1,   3,   3,   1,  71,   0,   0,  39,   1,   1,   3,   4,   3, 208, 
 48,  71,   0,   0,  42,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71, 
  0,   0,  54,   2,   1,   4,   5,  10, 208,  48, 208,  44,  44,  70,  41,   1, 
 41,  71,   0,   0,  57,   2,   1,   4,   5,  10, 208,  48, 208,  44,  44,  70, 
 42,   1,  41,  71,   0,   0,  76,   2,   1,   4,   5,  10, 208,  48, 208,  44, 
 49,  70,  41,   1,  41,  71,   0,   0,  83,   2,   1,   4,   5,  10, 208,  48, 
208,  44,  49,  70,  42,   1,  41,  71,   0,   0,  86,   2,   1,   1,   3,  33, 
208,  48, 101,   0,  32,  88,   0, 104,  25, 101,   0,  32,  88,   1, 104,  40, 
101,   0,  93,  87, 102,  87,  48,  93,  88, 102,  88,  88,   2,  29, 104,   7, 
 71,   0,   0};

} }
