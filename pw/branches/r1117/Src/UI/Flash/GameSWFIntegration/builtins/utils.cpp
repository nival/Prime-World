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

const uint32_t utils_abc_class_count = 8;
const uint32_t utils_abc_script_count = 1;
const uint32_t utils_abc_method_count = 91;
const uint32_t utils_abc_length = 4675;

/* thunks (27 unique signatures, 52 total) */

#ifndef AVMPLUS_INDIRECT_NATIVE_THUNKS
  #error nativegen.py: --directthunks requires AVMFEATURE_INDIRECT_NATIVE_THUNKS=1
#endif


// native_script_function_trace
AvmBox utils_func_a2a_o_rest_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    const uint32_t argoffV = argoff0 + AvmThunkArgSize_AvmObject;
    (void)env;
    ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmBox const ret = UtilsScripts::trace(obj
        , (argc <= 0 ? NULL : argv + argoffV)
        , (argc <= 0 ? 0 : argc - 0)
    );
    return (AvmBox) ret;
}

// flash_utils_ObjectInput_readFloat
// flash_utils_ObjectInput_readDouble
double utils_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_utils_Timer_private__start
AvmBox utils_v2a_odo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_double
    };
    (void)argc;
    (void)env;
    TimerObject* const obj = (TimerObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->_start(
        AvmThunkUnbox_double(argv[argoff1])
        , (FunctionObject*)AvmThunkUnbox_AvmObject(argv[argoff2])
    );
    return kAvmThunkUndefined;
}

// flash_utils_ObjectOutput_writeBytes
// flash_utils_ObjectInput_readBytes
AvmBox utils_v2a_oouu_opti0_opti0_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_utils_ObjectInput_readUnsignedInt
// flash_utils_ObjectInput_bytesAvailable_get
// flash_utils_ObjectInput_readUnsignedShort
// flash_utils_ObjectInput_objectEncoding_get
// flash_utils_ObjectInput_readUnsignedByte
// flash_utils_ObjectOutput_objectEncoding_get
AvmBox utils_u2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// native_script_function_flash_utils_getQualifiedClassName
// native_script_function_flash_utils_getQualifiedSuperclassName
AvmBox utils_func_s2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    typedef AvmRetType_AvmString (*FuncType)(AvmObject, AvmBox);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_FUNCTION_HANDLER(env));
    return (AvmBox)(*func)(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])
        , AvmThunkUnbox_AvmBox(argv[argoff1])
    );
}

// native_script_function_flash_utils_escapeMultiByte
// native_script_function_flash_utils_unescapeMultiByte
AvmBox utils_func_s2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    typedef AvmRetType_AvmString (*FuncType)(AvmObject, AvmString);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_FUNCTION_HANDLER(env));
    return (AvmBox)(*func)(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])
        , AvmThunkUnbox_AvmString(argv[argoff1])
    );
}

// flash_utils_ObjectOutput_writeByte
// flash_utils_ObjectOutput_writeShort
// flash_utils_ObjectOutput_writeInt
AvmBox utils_v2a_oi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_utils_ObjectInput_readUTF
// flash_utils_ObjectInput_endian_get
// flash_utils_ObjectOutput_endian_get
AvmBox utils_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// native_script_function_flash_utils_clearInterval
// native_script_function_flash_utils_clearTimeout
AvmBox utils_func_v2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    typedef AvmRetType_void (*FuncType)(AvmObject, uint32_t);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_FUNCTION_HANDLER(env));
    (*func)(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])
        , AvmThunkUnbox_uint32_t(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_utils_ObjectOutput_writeMultiByte
AvmBox utils_v2a_oss_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmString
    };
    (void)argc;
    (void)env;
    ObjectOutputObject* const obj = (ObjectOutputObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->writeMultiByte(
        AvmThunkUnbox_AvmString(argv[argoff1])
        , AvmThunkUnbox_AvmString(argv[argoff2])
    );
    return kAvmThunkUndefined;
}

// native_script_function_flash_utils_getTimer
AvmBox utils_func_i2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    int32_t const ret = UtilsScripts::getTimer(obj);
    return (AvmBox) ret;
}

// flash_utils_ObjectInput_readInt
// flash_utils_ObjectInput_readShort
// flash_utils_ObjectInput_readByte
AvmBox utils_i2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_utils_Proxy_flash_utils_isAttribute
AvmBox utils_b2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    ProxyObject* const obj = (ProxyObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmBool32 const ret = obj->isAttribute(
        AvmThunkUnbox_AvmBox(argv[argoff1])
    );
    return (AvmBox) ret;
}

// flash_utils_ObjectInput_readUTFBytes
AvmBox utils_s2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    ObjectInputObject* const obj = (ObjectInputObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmString const ret = obj->readUTFBytes(
        AvmThunkUnbox_uint32_t(argv[argoff1])
    );
    return (AvmBox) ret;
}

// native_script_function_flash_utils_describeType
AvmBox utils_func_a2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    XMLObject* const ret = UtilsScripts::describeType(obj
        , AvmThunkUnbox_AvmBox(argv[argoff1])
    );
    return (AvmBox) ret;
}

// flash_utils_Timer_running_get
// flash_utils_ObjectInput_readBoolean
AvmBox utils_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    typedef AvmRetType_AvmBool32 (AvmObjectT::*FuncType)();
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    return (AvmBox)(*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
    );
}

// flash_utils_ObjectInput_readObject
AvmBox utils_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    ObjectInputObject* const obj = (ObjectInputObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmBox const ret = obj->readObject();
    return (AvmBox) ret;
}

// native_script_function_flash_utils_getDefinitionByName
AvmBox utils_func_a2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    ScriptObject* const obj = AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmBox const ret = UtilsScripts::getDefinitionByName(obj
        , AvmThunkUnbox_AvmString(argv[argoff1])
    );
    return (AvmBox) ret;
}

// native_script_function_flash_utils_setTimeout
// native_script_function_flash_utils_setInterval
AvmBox utils_func_u2a_ood_rest_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmObject
    };
    const uint32_t argoffV = argoff2 + AvmThunkArgSize_double;
    typedef AvmRetType_uint32_t (*FuncType)(AvmObject, AvmObject, double, AvmBox*, uint32_t);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_FUNCTION_HANDLER(env));
    return (AvmBox)(*func)(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])
        , AvmThunkUnbox_AvmObject(argv[argoff1])
        , AvmThunkUnbox_double(argv[argoff2])
        , (argc <= 2 ? NULL : argv + argoffV)
        , (argc <= 2 ? 0 : argc - 2)
    );
}

// flash_utils_ObjectOutput_writeDouble
// flash_utils_ObjectOutput_writeFloat
AvmBox utils_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_utils_ObjectOutput_writeBoolean
AvmBox utils_v2a_ob_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    ObjectOutputObject* const obj = (ObjectOutputObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->writeBoolean(
        AvmThunkUnbox_AvmBool32(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_utils_ObjectOutput_writeObject
AvmBox utils_v2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    ObjectOutputObject* const obj = (ObjectOutputObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->writeObject(
        AvmThunkUnbox_AvmBox(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_utils_Timer_stop
// flash_utils_Timer_private__timerDispatch
AvmBox utils_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    typedef AvmRetType_void (AvmObjectT::*FuncType)();
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    (*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
    );
    return kAvmThunkUndefined;
}

// flash_utils_ObjectInput_objectEncoding_set
// flash_utils_ObjectOutput_objectEncoding_set
// flash_utils_ObjectOutput_writeUnsignedInt
AvmBox utils_v2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_utils_ObjectInput_endian_set
// flash_utils_ObjectOutput_writeUTFBytes
// flash_utils_ObjectOutput_writeUTF
// flash_utils_ObjectOutput_endian_set
AvmBox utils_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_utils_ObjectInput_readMultiByte
AvmBox utils_s2a_ous_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_uint32_t
    };
    (void)argc;
    (void)env;
    ObjectInputObject* const obj = (ObjectInputObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmString const ret = obj->readMultiByte(
        AvmThunkUnbox_uint32_t(argv[argoff1])
        , AvmThunkUnbox_AvmString(argv[argoff2])
    );
    return (AvmBox) ret;
}

class SlotOffsetsAndAsserts
{
private:
    static uint32_t getSlotOffset(Traits* t, int nameId);
public:
    static const uint16_t s_slotsOffsetProxyClass = 0;
    static const uint16_t s_slotsOffsetProxyObject = 0;
    static void doProxyClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetTimerClass = 0;
    static const uint16_t s_slotsOffsetTimerObject = offsetof(TimerObject, m_slots_TimerObject);
    static void doTimerClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetObjectInputClass = 0;
    static const uint16_t s_slotsOffsetObjectInputObject = 0;
    static void doObjectInputClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetObjectOutputClass = 0;
    static const uint16_t s_slotsOffsetObjectOutputObject = 0;
    static void doObjectOutputClassAsserts(Traits* cTraits, Traits* iTraits);
};
REALLY_INLINE void SlotOffsetsAndAsserts::doProxyClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(ProxyClass::EmptySlotsStruct_ProxyClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(ProxyObject::EmptySlotsStruct_ProxyObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doTimerClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(TimerClass::EmptySlotsStruct_TimerClass) >= 0);
    MMGC_STATIC_ASSERT(offsetof(TimerObject, m_slots_TimerObject) == s_slotsOffsetTimerObject);
    MMGC_STATIC_ASSERT(offsetof(TimerObject, m_slots_TimerObject) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(TimerObject) <= 0xFFFF);
    AvmAssert(getSlotOffset(iTraits, 50) == (offsetof(TimerObject, m_slots_TimerObject) + offsetof(TimerObjectSlots, m_private_m_repeatCount)));
    AvmAssert(getSlotOffset(iTraits, 55) == (offsetof(TimerObject, m_slots_TimerObject) + offsetof(TimerObjectSlots, m_private_m_iteration)));
    AvmAssert(getSlotOffset(iTraits, 57) == (offsetof(TimerObject, m_slots_TimerObject) + offsetof(TimerObjectSlots, m_private_m_delay)));
}
REALLY_INLINE void SlotOffsetsAndAsserts::doObjectInputClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(ObjectInputClass::EmptySlotsStruct_ObjectInputClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(ObjectInputObject::EmptySlotsStruct_ObjectInputObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doObjectOutputClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(ObjectOutputClass::EmptySlotsStruct_ObjectOutputClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(ObjectOutputObject::EmptySlotsStruct_ObjectOutputObject) >= 0);
}

AVMTHUNK_NATIVE_CLASS_GLUE(ProxyClass, ProxyClass, SlotOffsetsAndAsserts::doProxyClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(TimerClass, TimerClass, SlotOffsetsAndAsserts::doTimerClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(ObjectInputClass, ObjectInputClass, SlotOffsetsAndAsserts::doObjectInputClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(ObjectOutputClass, ObjectOutputClass, SlotOffsetsAndAsserts::doObjectOutputClassAsserts)

AVMTHUNK_BEGIN_NATIVE_TABLES(utils)
    
    AVMTHUNK_BEGIN_NATIVE_METHODS(utils)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_trace, UtilsScripts::trace)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_utils_unescapeMultiByte, UtilsScripts::unescapeMultiByte)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_utils_setTimeout, UtilsScripts::setTimeout)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_utils_setInterval, UtilsScripts::setInterval)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_utils_getTimer, UtilsScripts::getTimer)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_utils_getQualifiedSuperclassName, UtilsScripts::getQualifiedSuperclassName)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_utils_getQualifiedClassName, UtilsScripts::getQualifiedClassName)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_utils_getDefinitionByName, UtilsScripts::getDefinitionByName)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_utils_escapeMultiByte, UtilsScripts::escapeMultiByte)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_utils_describeType, UtilsScripts::describeType)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_utils_clearTimeout, UtilsScripts::clearTimeout)
        AVMTHUNK_NATIVE_FUNCTION(native_script_function_flash_utils_clearInterval, UtilsScripts::clearInterval)
        AVMTHUNK_NATIVE_METHOD(flash_utils_Proxy_flash_utils_isAttribute, ProxyObject::isAttribute)
        AVMTHUNK_NATIVE_METHOD(flash_utils_Timer_private__timerDispatch, TimerObject::_timerDispatch)
        AVMTHUNK_NATIVE_METHOD(flash_utils_Timer_private__start, TimerObject::_start)
        AVMTHUNK_NATIVE_METHOD(flash_utils_Timer_stop, TimerObject::stop)
        AVMTHUNK_NATIVE_METHOD(flash_utils_Timer_running_get, TimerObject::get_running)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readUnsignedInt, ObjectInputObject::readUnsignedInt)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readByte, ObjectInputObject::readByte)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readShort, ObjectInputObject::readShort)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readDouble, ObjectInputObject::readDouble)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readBoolean, ObjectInputObject::readBoolean)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readUnsignedByte, ObjectInputObject::readUnsignedByte)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_objectEncoding_get, ObjectInputObject::get_objectEncoding)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readObject, ObjectInputObject::readObject)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readUnsignedShort, ObjectInputObject::readUnsignedShort)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_endian_get, ObjectInputObject::get_endian)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_bytesAvailable_get, ObjectInputObject::get_bytesAvailable)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_objectEncoding_set, ObjectInputObject::set_objectEncoding)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readMultiByte, ObjectInputObject::readMultiByte)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readFloat, ObjectInputObject::readFloat)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readUTF, ObjectInputObject::readUTF)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_endian_set, ObjectInputObject::set_endian)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readInt, ObjectInputObject::readInt)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readUTFBytes, ObjectInputObject::readUTFBytes)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectInput_readBytes, ObjectInputObject::readBytes)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_writeMultiByte, ObjectOutputObject::writeMultiByte)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_writeUTFBytes, ObjectOutputObject::writeUTFBytes)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_writeObject, ObjectOutputObject::writeObject)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_writeBoolean, ObjectOutputObject::writeBoolean)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_writeBytes, ObjectOutputObject::writeBytes)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_writeByte, ObjectOutputObject::writeByte)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_writeUTF, ObjectOutputObject::writeUTF)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_writeDouble, ObjectOutputObject::writeDouble)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_writeUnsignedInt, ObjectOutputObject::writeUnsignedInt)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_writeShort, ObjectOutputObject::writeShort)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_writeInt, ObjectOutputObject::writeInt)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_endian_get, ObjectOutputObject::get_endian)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_objectEncoding_set, ObjectOutputObject::set_objectEncoding)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_objectEncoding_get, ObjectOutputObject::get_objectEncoding)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_endian_set, ObjectOutputObject::set_endian)
        AVMTHUNK_NATIVE_METHOD(flash_utils_ObjectOutput_writeFloat, ObjectOutputObject::writeFloat)
    AVMTHUNK_END_NATIVE_METHODS()
    
    AVMTHUNK_BEGIN_NATIVE_CLASSES(utils)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_utils_Proxy, ProxyClass, ProxyClass, SlotOffsetsAndAsserts::s_slotsOffsetProxyClass, ProxyObject, SlotOffsetsAndAsserts::s_slotsOffsetProxyObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_utils_Timer, TimerClass, TimerClass, SlotOffsetsAndAsserts::s_slotsOffsetTimerClass, TimerObject, SlotOffsetsAndAsserts::s_slotsOffsetTimerObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_utils_ObjectInput, ObjectInputClass, ObjectInputClass, SlotOffsetsAndAsserts::s_slotsOffsetObjectInputClass, ObjectInputObject, SlotOffsetsAndAsserts::s_slotsOffsetObjectInputObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_utils_ObjectOutput, ObjectOutputClass, ObjectOutputClass, SlotOffsetsAndAsserts::s_slotsOffsetObjectOutputClass, ObjectOutputObject, SlotOffsetsAndAsserts::s_slotsOffsetObjectOutputObject)
    AVMTHUNK_END_NATIVE_CLASSES()
    
AVMTHUNK_END_NATIVE_TABLES()

AVMTHUNK_DEFINE_NATIVE_INITIALIZER(utils)

/* abc */
const uint8_t utils_abc_data[4675] = {
 16,   0,  46,   0,   2,   0,   0,   0, 151,   1,   0,   6,  83, 116, 114, 105, 
110, 103,   4, 117, 105, 110, 116,   8,  70, 117, 110,  99, 116, 105, 111, 110, 
  6,  78, 117, 109,  98, 101, 114,   3, 105, 110, 116,   6,  79,  98, 106, 101, 
 99, 116,   3,  88,  77,  76,   4, 118, 111, 105, 100,  22, 102, 108,  97, 115, 
104,  46, 117, 116, 105, 108, 115,  58,  68, 105,  99, 116, 105, 111, 110,  97, 
114, 121,   7,  66, 111, 111, 108, 101,  97, 110,  11, 102, 108,  97, 115, 104, 
 46, 117, 116, 105, 108, 115,  10,  68, 105,  99, 116, 105, 111, 110,  97, 114, 
121,  18, 102, 108,  97, 115, 104,  46, 117, 116, 105, 108, 115,  58,  69, 110, 
100, 105,  97, 110,  10,  66,  73,  71,  95,  69,  78,  68,  73,  65,  78,   9, 
 98, 105, 103,  69, 110, 100, 105,  97, 110,  13,  76,  73,  84,  84,  76,  69, 
 95,  69,  78,  68,  73,  65,  78,  12, 108, 105, 116, 116, 108, 101,  69, 110, 
100, 105,  97, 110,   6,  69, 110, 100, 105,  97, 110,  10,  73,  68,  97, 116, 
 97,  73, 110, 112, 117, 116,  11,  73,  68,  97, 116,  97,  79, 117, 116, 112, 
117, 116,  27, 102, 108,  97, 115, 104,  46, 117, 116, 105, 108, 115,  58,  73, 
 69, 120, 116, 101, 114, 110,  97, 108, 105, 122,  97,  98, 108, 101,  12, 114, 
101,  97, 100,  69, 120, 116, 101, 114, 110,  97, 108,  13, 119, 114, 105, 116, 
101,  69, 120, 116, 101, 114, 110,  97, 108,  15,  73,  69, 120, 116, 101, 114, 
110,  97, 108, 105, 122,  97,  98, 108, 101,  17, 102, 108,  97, 115, 104,  46, 
117, 116, 105, 108, 115,  58,  80, 114, 111, 120, 121,   5,  69, 114, 114, 111, 
114,  10, 117, 116, 105, 108, 115,  46,  97, 115,  36,  53,  21,  73, 108, 108, 
101, 103,  97, 108,  79, 112, 101, 114,  97, 116, 105, 111, 110,  69, 114, 114, 
111, 114,  10, 116, 104, 114, 111, 119,  69, 114, 114, 111, 114,  14, 100, 101, 
108, 101, 116, 101,  80, 114, 111, 112, 101, 114, 116, 121,  11, 105, 115,  65, 
116, 116, 114, 105,  98, 117, 116, 101,  13, 110, 101, 120, 116,  78,  97, 109, 
101,  73, 110, 100, 101, 120,   9, 110, 101, 120, 116,  86,  97, 108, 117, 101, 
 11, 115, 101, 116,  80, 114, 111, 112, 101, 114, 116, 121,  14, 103, 101, 116, 
 68, 101, 115,  99, 101, 110, 100,  97, 110, 116, 115,  12,  99,  97, 108, 108, 
 80, 114, 111, 112, 101, 114, 116, 121,  11, 103, 101, 116,  80, 114, 111, 112, 
101, 114, 116, 121,   8, 110, 101, 120, 116,  78,  97, 109, 101,  11, 104,  97, 
115,  80, 114, 111, 112, 101, 114, 116, 121,   5,  80, 114, 111, 120, 121,  17, 
102, 108,  97, 115, 104,  46, 117, 116, 105, 108, 115,  58,  84, 105, 109, 101, 
114,   8, 105, 115,  70, 105, 110, 105, 116, 101,  12, 102, 108,  97, 115, 104, 
 46, 101, 118, 101, 110, 116, 115,  28, 102, 108,  97, 115, 104,  46, 101, 118, 
101, 110, 116, 115,  58,  69, 118, 101, 110, 116,  68, 105, 115, 112,  97, 116, 
 99, 104, 101, 114,  10,  82,  97, 110, 103, 101,  69, 114, 114, 111, 114,   7, 
109,  95, 100, 101, 108,  97, 121,  13, 109,  95, 114, 101, 112, 101,  97, 116, 
 67, 111, 117, 110, 116,   7, 114, 117, 110, 110, 105, 110, 103,   4, 115, 116, 
111, 112,   5, 115, 116,  97, 114, 116,  11, 109,  95, 105, 116, 101, 114,  97, 
116, 105, 111, 110,  14,  95, 116, 105, 109, 101, 114,  68, 105, 115, 112,  97, 
116,  99, 104,  13, 100, 105, 115, 112,  97, 116,  99, 104,  69, 118, 101, 110, 
116,  10,  84, 105, 109, 101, 114,  69, 118, 101, 110, 116,  14,  84,  73,  77, 
 69,  82,  95,  67,  79,  77,  80,  76,  69,  84,  69,   4, 116, 105,  99, 107, 
  6,  95, 115, 116,  97, 114, 116,  12,  99, 117, 114, 114, 101, 110, 116,  67, 
111, 117, 110, 116,   5, 100, 101, 108,  97, 121,  11, 114, 101, 112, 101,  97, 
116,  67, 111, 117, 110, 116,   5, 114, 101, 115, 101, 116,   5,  84, 105, 109, 
101, 114,  15,  69, 118, 101, 110, 116,  68, 105, 115, 112,  97, 116,  99, 104, 
101, 114,  23, 102, 108,  97, 115, 104,  46, 117, 116, 105, 108, 115,  58,  79, 
 98, 106, 101,  99, 116,  73, 110, 112, 117, 116,   9,  66, 121, 116, 101,  65, 
114, 114,  97, 121,  11, 114, 101,  97, 100,  66, 111, 111, 108, 101,  97, 110, 
 13, 114, 101,  97, 100,  77, 117, 108, 116, 105,  66, 121, 116, 101,  15, 114, 
101,  97, 100,  85, 110, 115, 105, 103, 110, 101, 100,  73, 110, 116,   8, 114, 
101,  97, 100,  66, 121, 116, 101,   9, 114, 101,  97, 100,  83, 104, 111, 114, 
116,  10, 114, 101,  97, 100,  68, 111, 117,  98, 108, 101,   7, 114, 101,  97, 
100,  73, 110, 116,  12, 114, 101,  97, 100,  85,  84,  70,  66, 121, 116, 101, 
115,  17, 114, 101,  97, 100,  85, 110, 115, 105, 103, 110, 101, 100,  83, 104, 
111, 114, 116,  16, 114, 101,  97, 100,  85, 110, 115, 105, 103, 110, 101, 100, 
 66, 121, 116, 101,   9, 114, 101,  97, 100,  66, 121, 116, 101, 115,   6, 101, 
110, 100, 105,  97, 110,  14, 111,  98, 106, 101,  99, 116,  69, 110,  99, 111, 
100, 105, 110, 103,  14,  98, 121, 116, 101, 115,  65, 118,  97, 105, 108,  97, 
 98, 108, 101,   9, 114, 101,  97, 100,  70, 108, 111,  97, 116,   7, 114, 101, 
 97, 100,  85,  84,  70,  10, 114, 101,  97, 100,  79,  98, 106, 101,  99, 116, 
 11,  79,  98, 106, 101,  99, 116,  73, 110, 112, 117, 116,  24, 102, 108,  97, 
115, 104,  46, 117, 116, 105, 108, 115,  58,  79,  98, 106, 101,  99, 116,  79, 
117, 116, 112, 117, 116,  14, 119, 114, 105, 116, 101,  77, 117, 108, 116, 105, 
 66, 121, 116, 101,  10, 119, 114, 105, 116, 101,  70, 108, 111,  97, 116,   9, 
119, 114, 105, 116, 101,  66, 121, 116, 101,   8, 119, 114, 105, 116, 101,  85, 
 84,  70,  12, 119, 114, 105, 116, 101,  66, 111, 111, 108, 101,  97, 110,  13, 
119, 114, 105, 116, 101,  85,  84,  70,  66, 121, 116, 101, 115,  10, 119, 114, 
105, 116, 101,  66, 121, 116, 101, 115,   8, 119, 114, 105, 116, 101,  73, 110, 
116,  10, 119, 114, 105, 116, 101,  83, 104, 111, 114, 116,  11, 119, 114, 105, 
116, 101,  68, 111, 117,  98, 108, 101,  16, 119, 114, 105, 116, 101,  85, 110, 
115, 105, 103, 110, 101, 100,  73, 110, 116,  11, 119, 114, 105, 116, 101,  79, 
 98, 106, 101,  99, 116,  12,  79,  98, 106, 101,  99, 116,  79, 117, 116, 112, 
117, 116,  28, 102, 108,  97, 115, 104,  46, 117, 116, 105, 108, 115,  58,  83, 
101, 116,  73, 110, 116, 101, 114, 118,  97, 108,  84, 105, 109, 101, 114,   9, 
105, 110, 116, 101, 114, 118,  97, 108, 115,   7,  99, 108, 111, 115, 117, 114, 
101,   4, 114, 101, 115, 116,  16,  97, 100, 100,  69, 118, 101, 110, 116,  76, 
105, 115, 116, 101, 110, 101, 114,   5,  84,  73,  77,  69,  82,   7, 111, 110, 
 84, 105, 109, 101, 114,   6, 108, 101, 110, 103, 116, 104,   2, 105, 100,   4, 
112, 117, 115, 104,   5,  65, 114, 114,  97, 121,   5,  97, 112, 112, 108, 121, 
 15,  99, 108, 101,  97, 114,  65, 114, 114,  97, 121,  69, 110, 116, 114, 121, 
  5,  69, 118, 101, 110, 116,  13,  99, 108, 101,  97, 114,  73, 110, 116, 101, 
114, 118,  97, 108,  16,  83, 101, 116,  73, 110, 116, 101, 114, 118,  97, 108, 
 84, 105, 109, 101, 114,   6, 110,  97, 116, 105, 118, 101,   3,  99, 108, 115, 
 10,  84, 105, 109, 101, 114,  67, 108,  97, 115, 115,   8, 105, 110, 115, 116, 
 97, 110,  99, 101,  11,  84, 105, 109, 101, 114,  79,  98, 106, 101,  99, 116, 
  7, 109, 101, 116, 104, 111, 100, 115,   4,  97, 117, 116, 111,  19, 103, 101, 
116,  68, 101, 102, 105, 110, 105, 116, 105, 111, 110,  66, 121,  78,  97, 109, 
101,  33,  85, 116, 105, 108, 115,  83,  99, 114, 105, 112, 116, 115,  58,  58, 
103, 101, 116,  68, 101, 102, 105, 110, 105, 116, 105, 111, 110,  66, 121,  78, 
 97, 109, 101,  27,  85, 116, 105, 108, 115,  83,  99, 114, 105, 112, 116, 115, 
 58,  58,  99, 108, 101,  97, 114,  73, 110, 116, 101, 114, 118,  97, 108,  17, 
 79,  98, 106, 101,  99, 116,  79, 117, 116, 112, 117, 116,  67, 108,  97, 115, 
115,  18,  79,  98, 106, 101,  99, 116,  79, 117, 116, 112, 117, 116,  79,  98, 
106, 101,  99, 116,   5, 116, 114,  97,  99, 101,  19,  85, 116, 105, 108, 115, 
 83,  99, 114, 105, 112, 116, 115,  58,  58, 116, 114,  97,  99, 101,  11, 115, 
101, 116,  73, 110, 116, 101, 114, 118,  97, 108,  25,  85, 116, 105, 108, 115, 
 83,  99, 114, 105, 112, 116, 115,  58,  58, 115, 101, 116,  73, 110, 116, 101, 
114, 118,  97, 108,  10,  80, 114, 111, 120, 121,  67, 108,  97, 115, 115,  11, 
 80, 114, 111, 120, 121,  79,  98, 106, 101,  99, 116,  12,  99, 108, 101,  97, 
114,  84, 105, 109, 101, 111, 117, 116,  26,  85, 116, 105, 108, 115,  83,  99, 
114, 105, 112, 116, 115,  58,  58,  99, 108, 101,  97, 114,  84, 105, 109, 101, 
111, 117, 116,  15, 101, 115,  99,  97, 112, 101,  77, 117, 108, 116, 105,  66, 
121, 116, 101,  29,  85, 116, 105, 108, 115,  83,  99, 114, 105, 112, 116, 115, 
 58,  58, 101, 115,  99,  97, 112, 101,  77, 117, 108, 116, 105,  66, 121, 116, 
101,  26, 103, 101, 116,  81, 117,  97, 108, 105, 102, 105, 101, 100,  83, 117, 
112, 101, 114,  99, 108,  97, 115, 115,  78,  97, 109, 101,  40,  85, 116, 105, 
108, 115,  83,  99, 114, 105, 112, 116, 115,  58,  58, 103, 101, 116,  81, 117, 
 97, 108, 105, 102, 105, 101, 100,  83, 117, 112, 101, 114,  99, 108,  97, 115, 
115,  78,  97, 109, 101,   8, 103, 101, 116,  84, 105, 109, 101, 114,  22,  85, 
116, 105, 108, 115,  83,  99, 114, 105, 112, 116, 115,  58,  58, 103, 101, 116, 
 84, 105, 109, 101, 114,  10, 115, 101, 116,  84, 105, 109, 101, 111, 117, 116, 
 24,  85, 116, 105, 108, 115,  83,  99, 114, 105, 112, 116, 115,  58,  58, 115, 
101, 116,  84, 105, 109, 101, 111, 117, 116,  12, 100, 101, 115,  99, 114, 105, 
 98, 101,  84, 121, 112, 101,  26,  85, 116, 105, 108, 115,  83,  99, 114, 105, 
112, 116, 115,  58,  58, 100, 101, 115,  99, 114, 105,  98, 101,  84, 121, 112, 
101,  17, 117, 110, 101, 115,  99,  97, 112, 101,  77, 117, 108, 116, 105,  66, 
121, 116, 101,  31,  85, 116, 105, 108, 115,  83,  99, 114, 105, 112, 116, 115, 
 58,  58, 117, 110, 101, 115,  99,  97, 112, 101,  77, 117, 108, 116, 105,  66, 
121, 116, 101,  16,  79,  98, 106, 101,  99, 116,  73, 110, 112, 117, 116,  67, 
108,  97, 115, 115,  17,  79,  98, 106, 101,  99, 116,  73, 110, 112, 117, 116, 
 79,  98, 106, 101,  99, 116,  21, 103, 101, 116,  81, 117,  97, 108, 105, 102, 
105, 101, 100,  67, 108,  97, 115, 115,  78,  97, 109, 101,  35,  85, 116, 105, 
108, 115,  83,  99, 114, 105, 112, 116, 115,  58,  58, 103, 101, 116,  81, 117, 
 97, 108, 105, 102, 105, 101, 100,  67, 108,  97, 115, 115,  78,  97, 109, 101, 
 26,  22,   1,   5,  10,  22,  12,  24,  10,   5,  14,  24,  14,   8,  22,   5, 
 26,   5,  28,  23,  12,  24,  26,  26,  26,  26,   7,   5,  42,  22,  44,  24, 
 42,  26,  42,  26,  45,   5,  65,  24,  65,   5,  85,  24,  85,   5,  99,  24, 
 99,  26,  99,   6,   8,   1,   3,   8,   9,  10,  11,  12,  13,  10,   1,   3, 
  9,  10,  13,  14,  15,  16,  17,  18,   4,   1,   3,   9,  10,  11,   1,   3, 
  9,  10,  13,  15,  17,  18,  23,  24,  25,   5,   1,   3,   9,  10,  15, 138, 
  1,   7,   1,   2,   7,   1,   3,   7,   1,   4,   7,   1,   5,   7,   1,   6, 
  7,   1,   7,   7,   1,   8,   7,   1,   9,   7,   1,  11,   7,   3,  13,   7, 
  1,  15,   7,   1,  17,   7,   3,  19,   7,   3,  20,   7,   3,  21,   7,   7, 
 23,   7,   7,  24,   7,   3,  25,   9,  27,   1,   9,  29,   1,   9,  30,   1, 
  7,  10,  31,   7,  10,  32,   7,  10,  33,   7,  10,  34,   7,  10,  35,   7, 
 10,  36,   7,  10,  37,   7,  10,  38,   7,  10,  39,   7,  10,  40,   7,   3, 
 41,   9,  43,   2,   9,  27,   2,   9,  46,   2,   9,  30,   2,   9,  47,   2, 
  9,  48,   2,   9,  49,   2,   9,  50,   2,   9,  51,   2,   9,  52,   2,   9, 
 53,   2,   9,  54,   2,   9,  55,   2,   9,  56,   2,   9,  57,   2,   9,  58, 
  2,   7,  14,  53,   7,  14,  48,   7,  14,  58,   7,   1,  59,   7,   1,  60, 
  7,   1,  61,   7,  14,  52,   7,   1,  62,   7,  14,  47,   7,   1,  51,   7, 
  1,  50,   7,  14,  57,   7,   1,  49,   7,   3,  63,   7,  15,  64,   7,   3, 
 66,   9,  20,   3,   7,   1,  67,   7,   1,  68,   7,   1,  69,   7,   1,  70, 
  7,   1,  71,   7,   1,  72,   7,   1,  73,   7,   1,  74,   7,   1,  75,   7, 
  1,  76,   7,   1,  77,   7,   1,  78,   7,   1,  79,   7,   1,  80,   7,   1, 
 81,   7,   1,  82,   7,   1,  83,   7,  10,  84,   9,  21,   3,   7,   1,  86, 
  7,   1,  87,   7,   1,  88,   7,   1,  89,   7,   1,  90,   7,   1,  91,   7, 
  1,  92,   7,   1,  93,   7,   1,  94,   7,   1,  95,   7,   1,  96,   7,   1, 
 97,   7,  10,  98,   7,  23, 100,   9, 100,   4,  27,   4,   9,  50,   4,   9, 
101,   4,   9, 102,   4,   9, 103,   4,   9,  55,   4,   9, 104,   4,   9, 105, 
  4,   9,  51,   4,   9, 106,   4,   9, 107,   4,   9, 108,   4,   7,   1, 109, 
  9, 110,   4,   9,  61,   4,   9, 111,   4,   7,  15, 112,   7,  10, 113,   7, 
 23, 101,   7,  23, 102,   7,  23, 105,   7,  10, 107,   7,  10, 111,   7,  10, 
114,   9,   7,   3,   9,  64,   5,   7,   3, 122,   7,   3, 113,   7,   1, 127, 
  7,   3, 129,   1,   7,   3, 133,   1,   7,   3, 135,   1,   7,   3, 137,   1, 
  7,   3, 139,   1,   7,   3, 141,   1,   7,   3, 143,   1,   7,   3, 145,   1, 
  7,   3, 149,   1,  91,   0,   0,   1,  36,   1,   1,   1,   1,  32,   2,   2, 
  3,   4,   1,  36,   2,   2,   3,   4,   1,  36,   0,   5,   1,  32,   1,   1, 
  0,   1,  32,   1,   1,   0,   1,  32,   1,   6,   1,   1,  32,   1,   1,   1, 
  1,  32,   1,   7,   0,   1,  32,   1,   8,   2,   1,  32,   1,   8,   2,   1, 
 32,   0,   0,   1,   0,   1,   0,   9,   1,   8,   1,  10,  10,   0,   0,   1, 
  0,   0,   0,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   1,   8,  14, 
  1,   0,   1,   8,  15,   1,   0,   0,   0,   1,   0,   0,   0,   1,   0,   1, 
  9,   0,   1,   0,   1,   9,   0,   1,  32,   1,   0,   0,   1,   4,   1,   5, 
  5,   1,   0,   1,   1,   5,   1,   0,   1,   0,   0,   1,   0,   1,   0,   0, 
  1,   0,   1,   0,   5,   1,   0,   2,   8,   0,   0,   1,   0,   1,   9,   0, 
  1,   0,   0,   0,   1,   0,   2,   0,   4,   5,   1,   8,   1,   1,   3,   0, 
  8,   1,  32,   0,   4,   1,   0,   1,   8,   4,   1,   0,   1,   8,   5,   1, 
  0,   2,   8,   4,   3,   1,  32,   0,   8,   1,   0,   0,   8,   1,   0,   0, 
  5,   1,   0,   0,   8,   1,   0,   0,   8,   1,  32,   0,   5,   1,   0,   0, 
  9,   1,  32,   0,   0,   1,   0,   0,   0,   1,   0,   0,   2,   1,  32,   0, 
  5,   1,  32,   0,   5,   1,  32,   0,   4,   1,  32,   0,   9,   1,  32,   0, 
  2,   1,  32,   0,   2,   1,  32,   0,   0,   1,  32,   0,   2,   1,  32,   0, 
  1,   1,  32,   0,   2,   1,  32,   1,   8,   2,   1,  32,   2,   1,   2,   1, 
  1,  32,   0,   4,   1,  32,   0,   1,   1,  32,   1,   8,   1,   1,  32,   0, 
  5,   1,  32,   1,   1,   2,   1,  32,   3,   8,  64,   2,   2,   1,  40,   2, 
  1,   3,   1,   3,   0,   0,   1,   0,   0,   0,   1,   0,   2,   8,   1,   1, 
  1,  32,   1,   8,   1,   1,  32,   1,   8,   0,   1,  32,   1,   8,   9,   1, 
 32,   3,   8,  64,   2,   2,   1,  40,   2,   1,   3,   1,   3,   1,   8,   5, 
  1,  32,   1,   8,   1,   1,  32,   1,   8,   4,   1,  32,   1,   8,   2,   1, 
 32,   1,   8,   5,   1,  32,   1,   8,   5,   1,  32,   0,   1,   1,  32,   1, 
  8,   2,   1,  32,   0,   2,   1,  32,   1,   8,   1,   1,  32,   1,   8,   4, 
  1,  32,   0,   0,   1,   0,   1,   8,   2,   1,   0,   4,   0,   3,   4,   9, 
112,   1,   0,   1,   8, 116,   1,   0,   0,   8,   1,   0,   0,   0,   1,   0, 
 16, 115,   3, 116, 118, 120, 117, 119, 121, 115,   1,   0, 123, 115,   1,   0, 
124, 115,   3, 116, 118, 120, 125, 126, 121, 115,   1,   0, 128,   1, 115,   1, 
  0, 130,   1, 115,   3, 116, 118, 120, 131,   1, 132,   1, 121, 115,   1,   0, 
134,   1, 115,   1,   0, 136,   1, 115,   1,   0, 138,   1, 115,   1,   0, 140, 
  1, 115,   1,   0, 142,   1, 115,   1,   0, 144,   1, 115,   1,   0, 146,   1, 
115,   3, 116, 118, 120, 147,   1, 148,   1, 121, 115,   1,   0, 150,   1,   8, 
 10,   6,   8,   4,   0,  13,   0,  13,   6,  11,   6,   0,  15,   0,  18,   0, 
  5,   0,  17,   2,  16,   1,   0,  18,  17,   1,   0,  19,  32,   6,   9,  11, 
  0,  21,  10,  22,   1,   0,  22,  23,   1,   0,  23,  24,   1,   0,  25,  25, 
  1,   0,  29,  26,   1,   0,  30,  27,   1,   0,  27,  28,   1,   0,  24,  29, 
  1,   0,  28,  30,   1,   0,  26,  31,   1,   0,  31,  62,  63,   9,  16,   0, 
 33,  15,  49,   1,   0,  34,  50,   0,   0,   5,   0,  51,   1,   0,  38,  52, 
  2,   0,  44,  53,   3,   0,  36,  54,   3,   0,  37,  53,   2,   0,  35,  55, 
  0,   0,   5,   0,  56,   1,   0,  40,  57,   0,   0,   4,   0,  54,   2,   0, 
 41,  58,   1,   0,  42,  59,   1,   0,  43,  60,   1,   0,  39,  61,   2,   0, 
 45,  83,   6,   9,  20,   1,  65,  47,  19,  66,   1,   0,  52,  67,   1,   0, 
 60,  68,   1,   0,  48,  69,   1,   0,  49,  70,   1,   0,  50,  71,   1,   0, 
 51,  72,   1,   0,  64,  73,   1,   0,  65,  74,   1,   0,  56,  75,   1,   0, 
 53,  76,   1,   0,  66,  77,   2,   0,  57,  78,   3,   0,  59,  79,   2,   0, 
 58,  80,   1,   0,  61,  78,   2,   0,  54,  77,   3,   0,  63,  81,   1,   0, 
 62,  82,   1,   0,  55,  97,   6,   9,  22,   1,  84,  68,  16,  85,   1,   0, 
 69,  86,   1,   0,  84,  87,   1,   0,  74,  88,   1,   0,  75,  89,   1,   0, 
 72,  90,   1,   0,  70,  91,   1,   0,  73,  92,   1,   0,  79,  77,   2,   0, 
 80,  93,   1,   0,  78,  94,   1,   0,  76,  95,   1,   0,  77,  78,   3,   0, 
 81,  77,   3,   0,  83,  78,   2,   0,  82,  96,   1,   0,  71, 123,  62,  11, 
 24,   0,  87,   5, 118,   0,   0,   3,   0, 119,   0,   0, 112,   0, 120,   1, 
  0,  88, 121,   0,   0,   2,   0, 122,   1,   0,  89,  12,   0,  14,   2,  11, 
  6,   1,   1,  16,   1,  12,   6,   2,   1,  18,   1,  16,   0,  20,   0,  32, 
  0,  46,   0,  67,   0,  85,   2, 117,  17,   3,  86,  98,   0,   1, 112,   0, 
  1,  90,  20,  62,  68,   7,   4,   1,   0, 126,  65,   5,   7,   1,   1, 127, 
 65,   1,  11,   1,   2,  18,   4,   3,   2,  97,  68,   5,   6,   1,   3, 128, 
  1,  65,  12,   0,   1,   4, 129,   1,  65,   9,   3,   1,   5,  32,  68,   6, 
  3,   1,   6, 130,   1,  65,   2,  10,   1,   7, 123,   4,   8,   7, 131,   1, 
 65,   4,   8,   1,   8, 132,   1,  65,   7,   5,   1,   9, 133,   1,  65,   8, 
  4,   1,  10, 134,   1,  65,  10,   2,   1,  11, 135,   1,  65,   3,   9,   1, 
 12, 136,   1,  65,  11,   1,   1,  13,  83,  68,   4,   5,   1,  14,  10,   4, 
  1,   0,  13,   4,   2,   1, 137,   1,  65,   6,   6,   1,  15,  36,  12,   1, 
  1,   3,   4,   3, 208,  48,  71,   0,   0,  13,   1,   2,   4,   5,   6, 208, 
 48, 208,  73,   0,  71,   0,   0,  14,   2,   1,   3,   4,  15, 208,  48,  94, 
 11,  44,  16, 104,  11,  94,  12,  44,  18, 104,  12,  71,   0,   0,  15,   1, 
  1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  16,   0,   1,   3, 
  3,   1,  71,   0,   0,  20,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0, 
 21,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  22,   3, 
  2,   4,   5,  19, 208,  48,  93,  19, 102,  19,  93,  20, 102,  20,  37, 172, 
 16,  70,  21,   2,  41,  32,  72,   0,   0,  24,   3,   3,   4,   5,  19, 208, 
 48,  93,  19, 102,  19,  93,  20, 102,  20,  37, 170,  16,  70,  21,   2,  41, 
 32,  72,   0,   0,  25,   3,   2,   4,   5,  19, 208,  48,  93,  19, 102,  19, 
 93,  20, 102,  20,  37, 185,  16,  70,  21,   2,  41,  32,  72,   0,   0,  26, 
  3,   2,   4,   5,  19, 208,  48,  93,  19, 102,  19,  93,  20, 102,  20,  37, 
186,  16,  70,  21,   2,  41,  32,  72,   0,   0,  27,   3,   2,   4,   5,  19, 
208,  48,  93,  19, 102,  19,  93,  20, 102,  20,  37, 173,  16,  70,  21,   2, 
 41,  32,  72,   0,   0,  28,   3,   2,   4,   5,  18, 208,  48,  93,  19, 102, 
 19,  93,  20, 102,  20,  37, 168,  16,  70,  21,   2,  41,  71,   0,   0,  29, 
  3,   2,   4,   5,  19, 208,  48,  93,  19, 102,  19,  93,  20, 102,  20,  37, 
187,  16,  70,  21,   2,  41,  32,  72,   0,   0,  30,   3,   3,   4,   5,  18, 
208,  48,  93,  19, 102,  19,  93,  20, 102,  20,  37, 169,  16,  70,  21,   2, 
 41,  71,   0,   0,  31,   3,   2,   4,   5,  19, 208,  48,  93,  19, 102,  19, 
 93,  20, 102,  20,  37, 171,  16,  70,  21,   2,  41,  32,  72,   0,   0,  32, 
  1,   1,   4,   5,   3, 208,  48,  71,   0,   0,  33,   3,   3,   5,   6,  47, 
208,  48, 208,  73,   0, 209,  36,   0,  15,   0,   0,   0,  93,  33, 209,  70, 
 33,   1, 150,  18,  15,   0,   0,  93,  34, 102,  34,  93,  35, 102,  35,  37, 
146,  16,  70,  36,   2,  41, 208, 209, 104,  37, 208, 210, 104,  38,  71,   0, 
  0,  35,   1,   1,   5,   6,   6, 208,  48, 208, 102,  37,  72,   0,   0,  36, 
  3,   2,   5,   6,  57, 208,  48, 209,  36,   0,  15,   0,   0,   0,  93,  33, 
209,  70,  33,   1, 150,  18,  15,   0,   0,  93,  34, 102,  34,  93,  35, 102, 
 35,  37, 146,  16,  70,  36,   2,  41, 208, 209,  97,  37, 208, 102,  39,  18, 
 10,   0,   0, 208,  70,  40,   0,  41, 208,  70,  41,   0,  41,  71,   0,   0, 
 37,   2,   2,   5,   6,  38, 208,  48, 208, 209,  97,  38, 208, 102,  39,  18, 
  0,   0,   0, 208, 102,  38,  36,   0,  19,   0,   0,   0, 208, 102,  42, 208, 
102,  38,  15,   5,   0,   0, 208,  70,  40,   0,  41,  71,   0,   0,  39,   5, 
  3,   5,   6,  57, 208,  48, 208,  42, 213, 102,  42, 192, 214, 209, 210,  97, 
 42,   8,   2,   8,   1, 208,  70,  43,   0,  41, 208, 102,  42, 208, 102,  38, 
 15,  24,   0,   0, 208,  70,  40,   0,  41,  93,  44,  93,  45,  93,  45, 102, 
 45, 102,  46,  39,  39,  74,  45,   3,  70,  44,   1,  41,  71,   0,   0,  40, 
  2,   1,   5,   6,  20, 208,  48, 208, 102,  39,  18,   5,   0,   0, 208,  70, 
 40,   0,  41, 208,  36,   0,  97,  42,  71,   0,   0,  41,   1,   1,   5,   6, 
  6, 208,  48, 208, 102,  38,  72,   0,   0,  42,   3,   1,   5,   6,  22, 208, 
 48, 208, 102,  39, 150,  18,  11,   0,   0, 208, 208, 102,  37, 208, 102,  47, 
 70,  48,   2,  41,  71,   0,   0,  44,   1,   1,   5,   6,   6, 208,  48, 208, 
102,  42,  72,   0,   0,  46,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0, 
 47,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  67,   1, 
  1,   3,   4,   3, 208,  48,  71,   0,   0,  68,   1,   1,   4,   5,   6, 208, 
 48, 208,  73,   0,  71,   0,   0,  85,   2,   1,   5,   6,   9, 208,  48,  94, 
 98,  86,   0,  97,  98,  71,   0,   0,  86,   2,   2,   5,   6,  43, 208,  48, 
209,  36,   1, 161, 116, 213,  93,  99, 102,  99, 209, 102, 100, 100, 108,   8, 
179,  18,  19,   0,   0,  93,  99, 102,  99, 209, 102, 100,  70, 101,   0,  41, 
 93,  99, 102,  99, 209, 106, 100,  41,  71,   0,   0,  87,   3,   5,   6,   7, 
 73, 208,  48, 208, 210, 211,  18,   7,   0,   0,  36,   0, 115,  16,   3,   0, 
  0,  36,   1, 115,  73,   2, 208, 209, 104, 102, 208,  98,   4, 104, 103,  93, 
104,  93, 105, 102, 105, 102, 106, 208, 102, 107,  70, 104,   2,  41,  93, 108, 
 70, 108,   0,  41, 208,  93,  99, 102,  99, 102, 109,  36,   1, 160, 104, 110, 
 93,  99, 102,  99, 208,  70, 111,   1,  41,  71,   0,   0,  88,   3,   2,   6, 
  7,  29, 208,  48, 208, 102, 102,  32, 208, 102, 103,  70, 113,   2,  41,  93, 
114, 102, 114,  36,   1,  20,   5,   0,   0, 208,  70, 115,   0,  41,  71,   0, 
  0,  89,   3,   2,   6,   7,  54, 208,  48,  36,   0, 115, 213,  16,  32,   0, 
  0,   9,  93,  99, 102,  99, 209, 102, 100, 208,  20,  13,   0,   0,  93,  99, 
102,  99, 209,  36,   0,  97, 100,  16,  17,   0,   0, 209,  36,   1, 160, 115, 
213, 209,  93,  99, 102,  99, 102, 109,  21, 213, 255, 255,  71,   0,   0,  90, 
  2,   1,   1,   5, 139,   1, 208,  48, 101,   0,  93,   6, 102,   6,  48,  93, 
124, 102, 124,  88,   0,  29, 104,  10, 101,   0,  93,   6, 102,   6,  48,  93, 
124, 102, 124,  88,   1,  29, 104,  13, 101,   0,  32,  88,   2, 104,  18, 101, 
  0,  93,   6, 102,   6,  48,  93, 124, 102, 124,  88,   5,  29, 104,  83, 101, 
  0,  93,   6, 102,   6,  48,  93, 124, 102, 124,  88,   6,  29, 104,  97, 101, 
  0,  93,   6, 102,   6,  48,  93, 124, 102, 124,  88,   3,  29, 104,  32, 101, 
  0,  93,   6, 102,   6,  48,  93,  63, 102,  63,  48,  93, 125, 102, 125,  88, 
  4,  29,  29, 104,  62, 101,   0,  93,   6, 102,   6,  48,  93,  63, 102,  63, 
 48,  93,  62, 102,  62,  48, 100, 108,   7,  88,   7,  29,  29,  29, 104, 123, 
 71,   0,   0};

} }
