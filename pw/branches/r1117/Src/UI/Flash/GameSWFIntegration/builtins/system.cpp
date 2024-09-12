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

const uint32_t system_abc_class_count = 11;
const uint32_t system_abc_script_count = 1;
const uint32_t system_abc_method_count = 89;
const uint32_t system_abc_length = 4238;

/* thunks (15 unique signatures, 64 total) */

#ifndef AVMPLUS_INDIRECT_NATIVE_THUNKS
  #error nativegen.py: --directthunks requires AVMFEATURE_INDIRECT_NATIVE_THUNKS=1
#endif


// flash_system_FSCommand__fscommand
AvmBox system_v2a_oss_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmString
    };
    (void)argc;
    (void)env;
    FSCommandClass* const obj = (FSCommandClass*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->_fscommand(
        AvmThunkUnbox_AvmString(argv[argoff1])
        , AvmThunkUnbox_AvmString(argv[argoff2])
    );
    return kAvmThunkUndefined;
}

// flash_system_IME_constructOK_set
// flash_system_System_useCodePage_set
// flash_system_IME_enabled_set
// flash_system_Security_exactSettings_set
// flash_system_Security_disableAVM1Loading_set
AvmBox system_v2a_ob_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    typedef AvmRetType_void (AvmObjectT::*FuncType)(AvmBool32);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    (*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
        AvmThunkUnbox_AvmBool32(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_system_Security_showSettings
AvmBox system_v2a_os_optsAvmThunkConstant_AvmString_89_____default_____thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)env;
    SecurityClass* const obj = (SecurityClass*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->showSettings(
        (argc < 1 ? AvmThunkConstant_AvmString(89)/* "default" */ : AvmThunkUnbox_AvmString(argv[argoff1]))
    );
    return kAvmThunkUndefined;
}

// flash_system_ApplicationDomain_domainMemory_set
AvmBox system_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    ApplicationDomainObject* const obj = (ApplicationDomainObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->set_domainMemory(
        (ByteArrayObject*)AvmThunkUnbox_AvmObject(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_system_ApplicationDomain_getDefinition
AvmBox system_a2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    ApplicationDomainObject* const obj = (ApplicationDomainObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmBox const ret = obj->getDefinition(
        AvmThunkUnbox_AvmString(argv[argoff1])
    );
    return (AvmBox) ret;
}

// flash_system_Security_allowDomain
// flash_system_Security_allowInsecureDomain
AvmBox system_v2a_o_rest_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    const uint32_t argoffV = argoff0 + AvmThunkArgSize_AvmObject;
    typedef AvmRetType_void (AvmObjectT::*FuncType)(AvmBox*, uint32_t);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    (*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
        (argc <= 0 ? NULL : argv + argoffV)
        , (argc <= 0 ? 0 : argc - 0)
    );
    return kAvmThunkUndefined;
}

// flash_system_Capabilities__internal_get
// flash_system_ApplicationDomain_MIN_DOMAIN_MEMORY_LENGTH_get
// flash_system_System_totalMemory_get
AvmBox system_u2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_system_System_pause
// flash_system_System_gc
// flash_system_System_resume
// flash_system_IME_doConversion
AvmBox system_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_system_ApplicationDomain_hasDefinition
AvmBox system_b2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    ApplicationDomainObject* const obj = (ApplicationDomainObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmBool32 const ret = obj->hasDefinition(
        AvmThunkUnbox_AvmString(argv[argoff1])
    );
    return (AvmBox) ret;
}

// flash_system_SecurityDomain_currentDomain_get
// flash_system_ApplicationDomain_currentDomain_get
// flash_system_ApplicationDomain_domainMemory_get
// flash_system_ApplicationDomain_parentDomain_get
AvmBox system_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_system_Capabilities_hasPrinting_get
// flash_system_Capabilities_hasScreenBroadcast_get
// flash_system_Capabilities_hasIME_get
// flash_system_System_useCodePage_get
// flash_system_Security_disableAVM1Loading_get
// flash_system_Capabilities_hasStreamingVideo_get
// flash_system_Capabilities_isEmbeddedInAcrobat_get
// flash_system_Capabilities_hasTLS_get
// flash_system_Capabilities_hasMP3_get
// flash_system_Capabilities_hasVideoEncoder_get
// flash_system_Capabilities_avHardwareDisable_get
// flash_system_Capabilities_localFileReadDisable_get
// flash_system_Capabilities_hasEmbeddedVideo_get
// flash_system_Security_exactSettings_get
// flash_system_Capabilities_hasScreenPlayback_get
// flash_system_Capabilities_hasStreamingAudio_get
// flash_system_Capabilities_hasAudio_get
// flash_system_Capabilities_hasAudioEncoder_get
// flash_system_Capabilities_hasAccessibility_get
// flash_system_Capabilities_isDebugger_get
// flash_system_IME_enabled_get
AvmBox system_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_system_IME_conversionMode_set
// flash_system_System_setClipboard
// flash_system_IME_setCompositionString
// flash_system_Security_loadPolicyFile
AvmBox system_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_system_Capabilities_os_get
// flash_system_Capabilities_version_get
// flash_system_Security_sandboxType_get
// flash_system_Capabilities_maxLevelIDC_get
// flash_system_IME_conversionMode_get
// flash_system_System_vmVersion_get
// flash_system_Capabilities_serverString_get
// flash_system_Capabilities_playerType_get
// flash_system_Capabilities_screenColor_get
// flash_system_Capabilities_manufacturer_get
// flash_system_Capabilities_language_get
AvmBox system_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_system_System_exit
AvmBox system_v2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    SystemClass* const obj = (SystemClass*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->exit(
        AvmThunkUnbox_uint32_t(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_system_Capabilities_pixelAspectRatio_get
// flash_system_Capabilities_screenResolutionY_get
// flash_system_Capabilities_screenDPI_get
// flash_system_Capabilities_screenResolutionX_get
double system_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

class SlotOffsetsAndAsserts
{
private:
    static uint32_t getSlotOffset(Traits* t, int nameId);
public:
    static const uint16_t s_slotsOffsetApplicationDomainClass = 0;
    static const uint16_t s_slotsOffsetApplicationDomainObject = 0;
    static void doApplicationDomainClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetCapabilitiesClass = 0;
    static const uint16_t s_slotsOffsetCapabilitiesObject = 0;
    static void doCapabilitiesClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetFSCommandClass = 0;
    static const uint16_t s_slotsOffsetFSCommandObject = 0;
    static void doFSCommandClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetIMEClass = 0;
    static const uint16_t s_slotsOffsetIMEObject = 0;
    static void doIMEClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetSecurityClass = offsetof(SecurityClass, m_slots_SecurityClass);
    static const uint16_t s_slotsOffsetSecurityObject = 0;
    static void doSecurityClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetSecurityDomainClass = 0;
    static const uint16_t s_slotsOffsetSecurityDomainObject = 0;
    static void doSecurityDomainClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetSystemClass = offsetof(SystemClass, m_slots_SystemClass);
    static const uint16_t s_slotsOffsetSystemObject = 0;
    static void doSystemClassAsserts(Traits* cTraits, Traits* iTraits);
};
REALLY_INLINE void SlotOffsetsAndAsserts::doApplicationDomainClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(ApplicationDomainClass::EmptySlotsStruct_ApplicationDomainClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(ApplicationDomainObject::EmptySlotsStruct_ApplicationDomainObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doCapabilitiesClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(CapabilitiesClass::EmptySlotsStruct_CapabilitiesClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(CapabilitiesObject::EmptySlotsStruct_CapabilitiesObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doFSCommandClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(FSCommandClass::EmptySlotsStruct_FSCommandClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(FSCommandObject::EmptySlotsStruct_FSCommandObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doIMEClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(IMEClass::EmptySlotsStruct_IMEClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(IMEObject::EmptySlotsStruct_IMEObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doSecurityClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    MMGC_STATIC_ASSERT(offsetof(SecurityClass, m_slots_SecurityClass) == s_slotsOffsetSecurityClass);
    MMGC_STATIC_ASSERT(offsetof(SecurityClass, m_slots_SecurityClass) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(SecurityClass) <= 0xFFFF);
    AvmAssert(getSlotOffset(cTraits, 73) == (offsetof(SecurityClass, m_slots_SecurityClass) + offsetof(SecurityClassSlots, m_LOCAL_TRUSTED)));
    AvmAssert(getSlotOffset(cTraits, 74) == (offsetof(SecurityClass, m_slots_SecurityClass) + offsetof(SecurityClassSlots, m_REMOTE)));
    AvmAssert(getSlotOffset(cTraits, 75) == (offsetof(SecurityClass, m_slots_SecurityClass) + offsetof(SecurityClassSlots, m_LOCAL_WITH_FILE)));
    AvmAssert(getSlotOffset(cTraits, 76) == (offsetof(SecurityClass, m_slots_SecurityClass) + offsetof(SecurityClassSlots, m_LOCAL_WITH_NETWORK)));
    // MMGC_STATIC_ASSERT(sizeof(SecurityObject::EmptySlotsStruct_SecurityObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doSecurityDomainClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(SecurityDomainClass::EmptySlotsStruct_SecurityDomainClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(SecurityDomainObject::EmptySlotsStruct_SecurityDomainObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doSystemClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    MMGC_STATIC_ASSERT(offsetof(SystemClass, m_slots_SystemClass) == s_slotsOffsetSystemClass);
    MMGC_STATIC_ASSERT(offsetof(SystemClass, m_slots_SystemClass) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(SystemClass) <= 0xFFFF);
    AvmAssert(getSlotOffset(cTraits, 93) == (offsetof(SystemClass, m_slots_SystemClass) + offsetof(SystemClassSlots, m_private_theIME)));
    // MMGC_STATIC_ASSERT(sizeof(SystemObject::EmptySlotsStruct_SystemObject) >= 0);
}

AVMTHUNK_NATIVE_CLASS_GLUE(ApplicationDomainClass, ApplicationDomainClass, SlotOffsetsAndAsserts::doApplicationDomainClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(CapabilitiesClass, CapabilitiesClass, SlotOffsetsAndAsserts::doCapabilitiesClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(FSCommandClass, FSCommandClass, SlotOffsetsAndAsserts::doFSCommandClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(IMEClass, IMEClass, SlotOffsetsAndAsserts::doIMEClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(SecurityClass, SecurityClass, SlotOffsetsAndAsserts::doSecurityClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(SecurityDomainClass, SecurityDomainClass, SlotOffsetsAndAsserts::doSecurityDomainClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(SystemClass, SystemClass, SlotOffsetsAndAsserts::doSystemClassAsserts)

AVMTHUNK_BEGIN_NATIVE_TABLES(system)
    
    AVMTHUNK_BEGIN_NATIVE_METHODS(system)
        AVMTHUNK_NATIVE_METHOD(flash_system_ApplicationDomain_currentDomain_get, ApplicationDomainClass::get_currentDomain)
        AVMTHUNK_NATIVE_METHOD(flash_system_ApplicationDomain_MIN_DOMAIN_MEMORY_LENGTH_get, ApplicationDomainClass::get_MIN_DOMAIN_MEMORY_LENGTH)
        AVMTHUNK_NATIVE_METHOD(flash_system_ApplicationDomain_domainMemory_get, ApplicationDomainObject::get_domainMemory)
        AVMTHUNK_NATIVE_METHOD(flash_system_ApplicationDomain_getDefinition, ApplicationDomainObject::getDefinition)
        AVMTHUNK_NATIVE_METHOD(flash_system_ApplicationDomain_domainMemory_set, ApplicationDomainObject::set_domainMemory)
        AVMTHUNK_NATIVE_METHOD(flash_system_ApplicationDomain_hasDefinition, ApplicationDomainObject::hasDefinition)
        AVMTHUNK_NATIVE_METHOD(flash_system_ApplicationDomain_parentDomain_get, ApplicationDomainObject::get_parentDomain)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_hasTLS_get, CapabilitiesClass::get_hasTLS)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_hasScreenBroadcast_get, CapabilitiesClass::get_hasScreenBroadcast)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_hasIME_get, CapabilitiesClass::get_hasIME)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_maxLevelIDC_get, CapabilitiesClass::get_maxLevelIDC)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_hasStreamingAudio_get, CapabilitiesClass::get_hasStreamingAudio)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_hasPrinting_get, CapabilitiesClass::get_hasPrinting)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_screenDPI_get, CapabilitiesClass::get_screenDPI)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_hasAccessibility_get, CapabilitiesClass::get_hasAccessibility)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_hasMP3_get, CapabilitiesClass::get_hasMP3)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_hasEmbeddedVideo_get, CapabilitiesClass::get_hasEmbeddedVideo)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_manufacturer_get, CapabilitiesClass::get_manufacturer)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_hasVideoEncoder_get, CapabilitiesClass::get_hasVideoEncoder)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_hasAudio_get, CapabilitiesClass::get_hasAudio)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_screenColor_get, CapabilitiesClass::get_screenColor)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_language_get, CapabilitiesClass::get_language)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_hasAudioEncoder_get, CapabilitiesClass::get_hasAudioEncoder)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_hasScreenPlayback_get, CapabilitiesClass::get_hasScreenPlayback)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities__internal_get, CapabilitiesClass::get__internal)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_os_get, CapabilitiesClass::get_os)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_version_get, CapabilitiesClass::get_version)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_screenResolutionY_get, CapabilitiesClass::get_screenResolutionY)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_avHardwareDisable_get, CapabilitiesClass::get_avHardwareDisable)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_pixelAspectRatio_get, CapabilitiesClass::get_pixelAspectRatio)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_screenResolutionX_get, CapabilitiesClass::get_screenResolutionX)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_isDebugger_get, CapabilitiesClass::get_isDebugger)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_hasStreamingVideo_get, CapabilitiesClass::get_hasStreamingVideo)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_serverString_get, CapabilitiesClass::get_serverString)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_localFileReadDisable_get, CapabilitiesClass::get_localFileReadDisable)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_playerType_get, CapabilitiesClass::get_playerType)
        AVMTHUNK_NATIVE_METHOD(flash_system_Capabilities_isEmbeddedInAcrobat_get, CapabilitiesClass::get_isEmbeddedInAcrobat)
        AVMTHUNK_NATIVE_METHOD(flash_system_FSCommand__fscommand, FSCommandClass::_fscommand)
        AVMTHUNK_NATIVE_METHOD(flash_system_IME_setCompositionString, IMEClass::setCompositionString)
        AVMTHUNK_NATIVE_METHOD(flash_system_IME_enabled_get, IMEClass::get_enabled)
        AVMTHUNK_NATIVE_METHOD(flash_system_IME_conversionMode_set, IMEClass::set_conversionMode)
        AVMTHUNK_NATIVE_METHOD(flash_system_IME_constructOK_set, IMEClass::set_constructOK)
        AVMTHUNK_NATIVE_METHOD(flash_system_IME_doConversion, IMEClass::doConversion)
        AVMTHUNK_NATIVE_METHOD(flash_system_IME_conversionMode_get, IMEClass::get_conversionMode)
        AVMTHUNK_NATIVE_METHOD(flash_system_IME_enabled_set, IMEClass::set_enabled)
        AVMTHUNK_NATIVE_METHOD(flash_system_Security_showSettings, SecurityClass::showSettings)
        AVMTHUNK_NATIVE_METHOD(flash_system_Security_sandboxType_get, SecurityClass::get_sandboxType)
        AVMTHUNK_NATIVE_METHOD(flash_system_Security_exactSettings_get, SecurityClass::get_exactSettings)
        AVMTHUNK_NATIVE_METHOD(flash_system_Security_exactSettings_set, SecurityClass::set_exactSettings)
        AVMTHUNK_NATIVE_METHOD(flash_system_Security_allowDomain, SecurityClass::allowDomain)
        AVMTHUNK_NATIVE_METHOD(flash_system_Security_allowInsecureDomain, SecurityClass::allowInsecureDomain)
        AVMTHUNK_NATIVE_METHOD(flash_system_Security_loadPolicyFile, SecurityClass::loadPolicyFile)
        AVMTHUNK_NATIVE_METHOD(flash_system_Security_disableAVM1Loading_set, SecurityClass::set_disableAVM1Loading)
        AVMTHUNK_NATIVE_METHOD(flash_system_Security_disableAVM1Loading_get, SecurityClass::get_disableAVM1Loading)
        AVMTHUNK_NATIVE_METHOD(flash_system_SecurityDomain_currentDomain_get, SecurityDomainClass::get_currentDomain)
        AVMTHUNK_NATIVE_METHOD(flash_system_System_useCodePage_get, SystemClass::get_useCodePage)
        AVMTHUNK_NATIVE_METHOD(flash_system_System_totalMemory_get, SystemClass::get_totalMemory)
        AVMTHUNK_NATIVE_METHOD(flash_system_System_useCodePage_set, SystemClass::set_useCodePage)
        AVMTHUNK_NATIVE_METHOD(flash_system_System_vmVersion_get, SystemClass::get_vmVersion)
        AVMTHUNK_NATIVE_METHOD(flash_system_System_resume, SystemClass::resume)
        AVMTHUNK_NATIVE_METHOD(flash_system_System_setClipboard, SystemClass::setClipboard)
        AVMTHUNK_NATIVE_METHOD(flash_system_System_pause, SystemClass::pause)
        AVMTHUNK_NATIVE_METHOD(flash_system_System_gc, SystemClass::gc)
        AVMTHUNK_NATIVE_METHOD(flash_system_System_exit, SystemClass::exit)
    AVMTHUNK_END_NATIVE_METHODS()
    
    AVMTHUNK_BEGIN_NATIVE_CLASSES(system)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_system_ApplicationDomain, ApplicationDomainClass, ApplicationDomainClass, SlotOffsetsAndAsserts::s_slotsOffsetApplicationDomainClass, ApplicationDomainObject, SlotOffsetsAndAsserts::s_slotsOffsetApplicationDomainObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_system_Capabilities, CapabilitiesClass, CapabilitiesClass, SlotOffsetsAndAsserts::s_slotsOffsetCapabilitiesClass, CapabilitiesObject, SlotOffsetsAndAsserts::s_slotsOffsetCapabilitiesObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_system_FSCommand, FSCommandClass, FSCommandClass, SlotOffsetsAndAsserts::s_slotsOffsetFSCommandClass, FSCommandObject, SlotOffsetsAndAsserts::s_slotsOffsetFSCommandObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_system_IME, IMEClass, IMEClass, SlotOffsetsAndAsserts::s_slotsOffsetIMEClass, IMEObject, SlotOffsetsAndAsserts::s_slotsOffsetIMEObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_system_Security, SecurityClass, SecurityClass, SlotOffsetsAndAsserts::s_slotsOffsetSecurityClass, SecurityObject, SlotOffsetsAndAsserts::s_slotsOffsetSecurityObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_system_SecurityDomain, SecurityDomainClass, SecurityDomainClass, SlotOffsetsAndAsserts::s_slotsOffsetSecurityDomainClass, SecurityDomainObject, SlotOffsetsAndAsserts::s_slotsOffsetSecurityDomainObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_system_System, SystemClass, SystemClass, SlotOffsetsAndAsserts::s_slotsOffsetSystemClass, SystemObject, SlotOffsetsAndAsserts::s_slotsOffsetSystemObject)
    AVMTHUNK_END_NATIVE_CLASSES()
    
AVMTHUNK_END_NATIVE_TABLES()

AVMTHUNK_DEFINE_NATIVE_INITIALIZER(system)

/* abc */
const uint8_t system_abc_data[4238] = {
 16,   0,  46,   0,   2,   0,   0,   0, 149,   1,  10,  95, 102, 115,  99, 111, 
109, 109,  97, 110, 100,  11, 115, 121, 115, 116, 101, 109,  46,  97, 115,  36, 
 53,   0,  12, 102, 108,  97, 115, 104,  46, 115, 121, 115, 116, 101, 109,   6, 
 83, 116, 114, 105, 110, 103,  30, 102, 108,  97, 115, 104,  46, 115, 121, 115, 
116, 101, 109,  58,  65, 112, 112, 108, 105,  99,  97, 116, 105, 111, 110,  68, 
111, 109,  97, 105, 110,  17,  65, 112, 112, 108, 105,  99,  97, 116, 105, 111, 
110,  68, 111, 109,  97, 105, 110,   4, 117, 105, 110, 116,  11, 102, 108,  97, 
115, 104,  46, 117, 116, 105, 108, 115,   9,  66, 121, 116, 101,  65, 114, 114, 
 97, 121,   6,  79,  98, 106, 101,  99, 116,   7,  66, 111, 111, 108, 101,  97, 
110,  13,  99, 117, 114, 114, 101, 110, 116,  68, 111, 109,  97, 105, 110,  24, 
 77,  73,  78,  95,  68,  79,  77,  65,  73,  78,  95,  77,  69,  77,  79,  82, 
 89,  95,  76,  69,  78,  71,  84,  72,  12, 100, 111, 109,  97, 105, 110,  77, 
101, 109, 111, 114, 121,  13, 103, 101, 116,  68, 101, 102, 105, 110, 105, 116, 
105, 111, 110,  13, 104,  97, 115,  68, 101, 102, 105, 110, 105, 116, 105, 111, 
110,  12, 112,  97, 114, 101, 110, 116,  68, 111, 109,  97, 105, 110,  25, 102, 
108,  97, 115, 104,  46, 115, 121, 115, 116, 101, 109,  58,  67,  97, 112,  97, 
 98, 105, 108, 105, 116, 105, 101, 115,   6,  78, 117, 109,  98, 101, 114,   6, 
104,  97, 115,  84,  76,  83,  10, 112, 108,  97, 121, 101, 114,  84, 121, 112, 
101,   6, 104,  97, 115,  73,  77,  69,  11, 109,  97, 120,  76, 101, 118, 101, 
108,  73,  68,  67,  17, 104,  97, 115,  83, 116, 114, 101,  97, 109, 105, 110, 
103,  65, 117, 100, 105, 111,  11, 104,  97, 115,  80, 114, 105, 110, 116, 105, 
110, 103,   9, 115,  99, 114, 101, 101, 110,  68,  80,  73,  16, 104,  97, 115, 
 65,  99,  99, 101, 115, 115, 105,  98, 105, 108, 105, 116, 121,   6, 104,  97, 
115,  77,  80,  51,  16, 104,  97, 115,  69, 109,  98, 101, 100, 100, 101, 100, 
 86, 105, 100, 101, 111,  12, 109,  97, 110, 117, 102,  97,  99, 116, 117, 114, 
101, 114,  15, 104,  97, 115,  86, 105, 100, 101, 111,  69, 110,  99, 111, 100, 
101, 114,   9,  95, 105, 110, 116, 101, 114, 110,  97, 108,  11, 115,  99, 114, 
101, 101, 110,  67, 111, 108, 111, 114,   7, 118, 101, 114, 115, 105, 111, 110, 
 15, 104,  97, 115,  65, 117, 100, 105, 111,  69, 110,  99, 111, 100, 101, 114, 
 17, 104,  97, 115,  83,  99, 114, 101, 101, 110,  80, 108,  97, 121,  98,  97, 
 99, 107,   8, 104,  97, 115,  65, 117, 100, 105, 111,   2, 111, 115,  17, 115, 
 99, 114, 101, 101, 110,  82, 101, 115, 111, 108, 117, 116, 105, 111, 110,  88, 
 17, 115,  99, 114, 101, 101, 110,  82, 101, 115, 111, 108, 117, 116, 105, 111, 
110,  89,  17,  97, 118,  72,  97, 114, 100, 119,  97, 114, 101,  68, 105, 115, 
 97,  98, 108, 101,  16, 112, 105, 120, 101, 108,  65, 115, 112, 101,  99, 116, 
 82,  97, 116, 105, 111,   8, 108,  97, 110, 103, 117,  97, 103, 101,  10, 105, 
115,  68, 101,  98, 117, 103, 103, 101, 114,  17, 104,  97, 115,  83, 116, 114, 
101,  97, 109, 105, 110, 103,  86, 105, 100, 101, 111,  12, 115, 101, 114, 118, 
101, 114,  83, 116, 114, 105, 110, 103,  20, 108, 111,  99,  97, 108,  70, 105, 
108, 101,  82, 101,  97, 100,  68, 105, 115,  97,  98, 108, 101,  18, 104,  97, 
115,  83,  99, 114, 101, 101, 110,  66, 114, 111,  97, 100,  99,  97, 115, 116, 
 19, 105, 115,  69, 109,  98, 101, 100, 100, 101, 100,  73, 110,  65,  99, 114, 
111,  98,  97, 116,  12,  67,  97, 112,  97,  98, 105, 108, 105, 116, 105, 101, 
115,  22, 102, 108,  97, 115, 104,  46, 115, 121, 115, 116, 101, 109,  58,  70, 
 83,  67, 111, 109, 109,  97, 110, 100,   4, 118, 111, 105, 100,   9,  70,  83, 
 67, 111, 109, 109,  97, 110, 100,  16, 102, 108,  97, 115, 104,  46, 115, 121, 
115, 116, 101, 109,  58,  73,  77,  69,  14,  99, 111, 110, 118, 101, 114, 115, 
105, 111, 110,  77, 111, 100, 101,   7, 101, 110,  97,  98, 108, 101, 100,  11, 
 99, 111, 110, 115, 116, 114, 117,  99, 116,  79,  75,  12, 100, 111,  67, 111, 
110, 118, 101, 114, 115, 105, 111, 110,  20, 115, 101, 116,  67, 111, 109, 112, 
111, 115, 105, 116, 105, 111, 110,  83, 116, 114, 105, 110, 103,   3,  73,  77, 
 69,  12, 102, 108,  97, 115, 104,  46, 101, 118, 101, 110, 116, 115,  15,  69, 
118, 101, 110, 116,  68, 105, 115, 112,  97, 116,  99, 104, 101, 114,  30, 102, 
108,  97, 115, 104,  46, 115, 121, 115, 116, 101, 109,  58,  73,  77,  69,  67, 
111, 110, 118, 101, 114, 115, 105, 111, 110,  77, 111, 100, 101,  17,  65,  76, 
 80,  72,  65,  78,  85,  77,  69,  82,  73,  67,  95,  72,  65,  76,  70,   6, 
 75,  79,  82,  69,  65,  78,   7,  85,  78,  75,  78,  79,  87,  78,  17,  74, 
 65,  80,  65,  78,  69,  83,  69,  95,  72,  73,  82,  65,  71,  65,  78,  65, 
  7,  67,  72,  73,  78,  69,  83,  69,  22,  74,  65,  80,  65,  78,  69,  83, 
 69,  95,  75,  65,  84,  65,  75,  65,  78,  65,  95,  70,  85,  76,  76,  22, 
 74,  65,  80,  65,  78,  69,  83,  69,  95,  75,  65,  84,  65,  75,  65,  78, 
 65,  95,  72,  65,  76,  70,  17,  65,  76,  80,  72,  65,  78,  85,  77,  69, 
 82,  73,  67,  95,  70,  85,  76,  76,  17,  73,  77,  69,  67, 111, 110, 118, 
101, 114, 115, 105, 111, 110,  77, 111, 100, 101,  26, 102, 108,  97, 115, 104, 
 46, 115, 121, 115, 116, 101, 109,  58,  76, 111,  97, 100, 101, 114,  67, 111, 
110, 116, 101, 120, 116,  15,  99, 104, 101,  99, 107,  80, 111, 108, 105,  99, 
121,  70, 105, 108, 101,  17,  97, 112, 112, 108, 105,  99,  97, 116, 105, 111, 
110,  68, 111, 109,  97, 105, 110,  14, 115, 101,  99, 117, 114, 105, 116, 121, 
 68, 111, 109,  97, 105, 110,  14,  83, 101,  99, 117, 114, 105, 116, 121,  68, 
111, 109,  97, 105, 110,  13,  76, 111,  97, 100, 101, 114,  67, 111, 110, 116, 
101, 120, 116,  21, 102, 108,  97, 115, 104,  46, 115, 121, 115, 116, 101, 109, 
 58,  83, 101,  99, 117, 114, 105, 116, 121,  13,  76,  79,  67,  65,  76,  95, 
 84,  82,  85,  83,  84,  69,  68,  12, 108, 111,  99,  97, 108,  84, 114, 117, 
115, 116, 101, 100,   6,  82,  69,  77,  79,  84,  69,   6, 114, 101, 109, 111, 
116, 101,  15,  76,  79,  67,  65,  76,  95,  87,  73,  84,  72,  95,  70,  73, 
 76,  69,  13, 108, 111,  99,  97, 108,  87, 105, 116, 104,  70, 105, 108, 101, 
 18,  76,  79,  67,  65,  76,  95,  87,  73,  84,  72,  95,  78,  69,  84,  87, 
 79,  82,  75,  16, 108, 111,  99,  97, 108,  87, 105, 116, 104,  78, 101, 116, 
119, 111, 114, 107,   7, 100, 101, 102,  97, 117, 108, 116,  12, 115, 104, 111, 
119,  83, 101, 116, 116, 105, 110, 103, 115,  13, 101, 120,  97,  99, 116,  83, 
101, 116, 116, 105, 110, 103, 115,  11, 115,  97, 110, 100,  98, 111, 120,  84, 
121, 112, 101,  18, 100, 105, 115,  97,  98, 108, 101,  65,  86,  77,  49,  76, 
111,  97, 100, 105, 110, 103,  19,  97, 108, 108, 111, 119,  73, 110, 115, 101, 
 99, 117, 114, 101,  68, 111, 109,  97, 105, 110,  11,  97, 108, 108, 111, 119, 
 68, 111, 109,  97, 105, 110,  14, 108, 111,  97, 100,  80, 111, 108, 105,  99, 
121,  70, 105, 108, 101,   8,  83, 101,  99, 117, 114, 105, 116, 121,  27, 102, 
108,  97, 115, 104,  46, 115, 121, 115, 116, 101, 109,  58,  83, 101,  99, 117, 
114, 105, 116, 121,  68, 111, 109,  97, 105, 110,  26, 102, 108,  97, 115, 104, 
 46, 115, 121, 115, 116, 101, 109,  58,  83, 101,  99, 117, 114, 105, 116, 121, 
 80,  97, 110, 101, 108,   7,  68,  69,  70,  65,  85,  76,  84,   6,  67,  65, 
 77,  69,  82,  65,   6,  99,  97, 109, 101, 114,  97,  13,  76,  79,  67,  65, 
 76,  95,  83,  84,  79,  82,  65,  71,  69,  12, 108, 111,  99,  97, 108,  83, 
116, 111, 114,  97, 103, 101,   7,  80,  82,  73,  86,  65,  67,  89,   7, 112, 
114, 105, 118,  97,  99, 121,  10,  77,  73,  67,  82,  79,  80,  72,  79,  78, 
 69,  10, 109, 105,  99, 114, 111, 112, 104, 111, 110, 101,  16,  83,  69,  84, 
 84,  73,  78,  71,  83,  95,  77,  65,  78,  65,  71,  69,  82,  15, 115, 101, 
116, 116, 105, 110, 103, 115,  77,  97, 110,  97, 103, 101, 114,   7,  68,  73, 
 83,  80,  76,  65,  89,   7, 100, 105, 115, 112, 108,  97, 121,  13,  83, 101, 
 99, 117, 114, 105, 116, 121,  80,  97, 110, 101, 108,  19, 102, 108,  97, 115, 
104,  46, 115, 121, 115, 116, 101, 109,  58,  83, 121, 115, 116, 101, 109,   6, 
116, 104, 101,  73,  77,  69,   3, 105, 109, 101,  11, 117, 115, 101,  67, 111, 
100, 101,  80,  97, 103, 101,  11, 116, 111, 116,  97, 108,  77, 101, 109, 111, 
114, 121,   9, 118, 109,  86, 101, 114, 115, 105, 111, 110,   6, 114, 101, 115, 
117, 109, 101,  12, 115, 101, 116,  67, 108, 105, 112,  98, 111,  97, 114, 100, 
  5, 112,  97, 117, 115, 101,   2, 103,  99,   4, 101, 120, 105, 116,   6,  83, 
121, 115, 116, 101, 109,  30, 102, 108,  97, 115, 104,  46, 115, 121, 115, 116, 
101, 109,  58,  74,  80,  69,  71,  76, 111,  97, 100, 101, 114,  67, 111, 110, 
116, 101, 120, 116,  16, 100, 101,  98, 108, 111,  99, 107, 105, 110, 103,  70, 
105, 108, 116, 101, 114,  17,  74,  80,  69,  71,  76, 111,  97, 100, 101, 114, 
 67, 111, 110, 116, 101, 120, 116,   6, 110,  97, 116, 105, 118, 101,   3,  99, 
108, 115,  22,  65, 112, 112, 108, 105,  99,  97, 116, 105, 111, 110,  68, 111, 
109,  97, 105, 110,  67, 108,  97, 115, 115,   8, 105, 110, 115, 116,  97, 110, 
 99, 101,  23,  65, 112, 112, 108, 105,  99,  97, 116, 105, 111, 110,  68, 111, 
109,  97, 105, 110,  79,  98, 106, 101,  99, 116,   7, 109, 101, 116, 104, 111, 
100, 115,   4,  97, 117, 116, 111,  19,  83, 101,  99, 117, 114, 105, 116, 121, 
 68, 111, 109,  97, 105, 110,  67, 108,  97, 115, 115,  20,  83, 101,  99, 117, 
114, 105, 116, 121,  68, 111, 109,  97, 105, 110,  79,  98, 106, 101,  99, 116, 
 11,  83, 121, 115, 116, 101, 109,  67, 108,  97, 115, 115,  12,  83, 121, 115, 
116, 101, 109,  79,  98, 106, 101,  99, 116,  13,  83, 101,  99, 117, 114, 105, 
116, 121,  67, 108,  97, 115, 115,  14,  83, 101,  99, 117, 114, 105, 116, 121, 
 79,  98, 106, 101,  99, 116,   8,  73,  77,  69,  67, 108,  97, 115, 115,   9, 
 73,  77,  69,  79,  98, 106, 101,  99, 116,  14,  70,  83,  67, 111, 109, 109, 
 97, 110, 100,  67, 108,  97, 115, 115,  15,  70,  83,  67, 111, 109, 109,  97, 
110, 100,  79,  98, 106, 101,  99, 116,  17,  67,  97, 112,  97,  98, 105, 108, 
105, 116, 105, 101, 115,  67, 108,  97, 115, 115,  18,  67,  97, 112,  97,  98, 
105, 108, 105, 116, 105, 101, 115,  79,  98, 106, 101,  99, 116,   9, 102, 115, 
 99, 111, 109, 109,  97, 110, 100,  33,   5,   2,  22,   3,  22,   4,  23,   4, 
  5,   6,  22,   9,  24,   6,   5,  19,  24,  19,   5,  52,  24,  52,   5,  55, 
 22,  62,  24,  55,   5,  64,  24,  64,   5,  74,  24,  74,  26,  74,  26,  11, 
  5,  80,  24,  80,   5,  98,  24,  98,   5,  99,  24,  99,   5, 114,  24, 114, 
 26, 114,   5, 126,  24, 126,  26, 126,   7,   4,   1,   2,   3,   4,   8,   1, 
  2,   3,   4,  17,  18,  19,  20,   8,   1,   2,   3,   4,  20,  27,  28,  29, 
  9,   1,   2,   3,   4,  19,  20,  30,  31,  32,   5,   1,   2,   3,   4,   6, 
  5,   1,   2,   3,   4,  13, 114,   9,   1,   1,   7,   2,   5,   7,   3,   7, 
  7,   2,   8,   7,   6,  10,   7,   2,  11,   7,   2,  12,   7,   2,  13,   7, 
  2,  14,   7,   2,  15,   7,   2,  16,   7,   2,  17,   7,   2,  18,   7,   2, 
 20,   7,   2,  21,   7,   2,  22,   7,   2,  23,   7,   2,  24,   7,   2,  25, 
  7,   2,  26,   7,   2,  27,   7,   2,  28,   7,   2,  29,   7,   2,  30,   7, 
  2,  31,   7,   2,  32,   7,   2,  33,   7,   2,  34,   7,   2,  35,   7,   2, 
 36,   7,   2,  37,   7,   2,  38,   7,   2,  39,   7,   2,  40,   7,   2,  41, 
  7,   2,  42,   7,   2,  43,   7,   2,  44,   7,   2,  45,   7,   2,  46,   7, 
  2,  47,   7,   2,  48,   7,   2,  49,   7,   2,  50,   7,   3,  51,   7,   2, 
 53,   7,   2,   1,   7,   4,  54,   7,   2,  56,   7,   2,  57,   7,   2,  58, 
  7,   2,  59,   7,   2,  60,   7,   3,  61,   7,  13,  63,   7,   2,  65,   7, 
  2,  66,   7,   2,  67,   7,   2,  68,   7,   2,  69,   7,   2,  70,   7,   2, 
 71,   7,   2,  72,   7,   3,  73,   9,  75,   2,   9,  76,   2,   9,  77,   2, 
  7,   3,  78,   7,   2,  77,   7,   2,  75,   7,   2,  76,   7,   3,  79,   7, 
  2,  81,   7,   2,  83,   7,   2,  85,   7,   2,  87,   7,   2,  90,   7,   2, 
 91,   7,   2,  92,   7,   2,  93,   7,   2,  94,   7,   2,  95,   7,   2,  96, 
  7,   3,  97,   7,   2, 100,   7,   2, 101,   7,   2, 103,   7,   2, 105,   7, 
  2, 107,   7,   2, 109,   7,   2, 111,   7,   3, 113,   7,  27, 115,   9, 115, 
  3,   9,  58,   3,   9,  61,   3,   7,   2, 116,   7,   2, 117,   7,   2, 118, 
  7,   2, 119,   7,   2, 120,   7,   2, 121,   7,   2, 122,   7,   2, 123,   7, 
  2, 124,   7,   3, 125,   9, 127,   4,   7,   2, 127,   7,   3, 128,   1,   9, 
 11,   5,   9,  11,   1,   9,  63,   6,   7,   3, 148,   1,  89,   2,   0,   2, 
  2,   3,   8,   1,   3,   1,   0,   0,   3,   0,   0,   3,   3,  32,   0,   4, 
  3,  32,   1,   0,   3,   3,   8,   1,  12,  12,   0,   5,   3,  32,   1,   6, 
  2,   3,  32,   1,   0,   5,   3,  32,   1,   7,   2,   3,  32,   0,   3,   3, 
 32,   0,   0,   3,   0,   0,   7,   3,  32,   0,   7,   3,  32,   0,   7,   3, 
 32,   0,   2,   3,  32,   0,   7,   3,  32,   0,   7,   3,  32,   0,  14,   3, 
 32,   0,   7,   3,  32,   0,   7,   3,  32,   0,   7,   3,  32,   0,   2,   3, 
 32,   0,   7,   3,  32,   0,   7,   3,  32,   0,   2,   3,  32,   0,   2,   3, 
 32,   0,   7,   3,  32,   0,   7,   3,  32,   0,   4,   3,  32,   0,   2,   3, 
 32,   0,   2,   3,  32,   0,  14,   3,  32,   0,   7,   3,  32,   0,  14,   3, 
 32,   0,  14,   3,  32,   0,   7,   3,  32,   0,   7,   3,  32,   0,   2,   3, 
 32,   0,   7,   3,  32,   0,   2,   3,  32,   0,   7,   3,  32,   0,   0,   3, 
  0,   0,   0,   3,   0,   2,  46,   2,   2,   3,  32,   0,   0,   3,   0,   0, 
  0,   3,   0,   1,  46,   2,   3,  32,   0,   7,   3,  32,   1,  46,   2,   3, 
 32,   1,  46,   7,   3,  32,   0,  46,   3,  32,   0,   2,   3,  32,   1,  46, 
  7,   3,  32,   0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   3,   0,   0, 
  0,   3,   0,   3,   0,   7,   3,  68,   3,   8,   3,  10,  10,  12,  12,  12, 
 12,   0,   0,   3,   0,   1,  46,   2,   3,  40,   1,  89,   1,   0,   2,   3, 
 32,   0,   7,   3,  32,   1,  46,   7,   3,  32,   0,  46,   3,  36,   0,  46, 
  3,  36,   1,  46,   2,   3,  32,   1,  46,   7,   3,  32,   0,   7,   3,  32, 
  0,   0,   3,   0,   0,   0,   3,   0,   0,  68,   3,  32,   0,   0,   3,   0, 
  0,   0,   3,   0,   0,   0,   3,   0,   0,   0,   3,   0,   0,  54,   3,   0, 
  0,   7,   3,  32,   0,   4,   3,  32,   1,  46,   7,   3,  32,   0,   2,   3, 
 32,   0,  46,   3,  32,   1,  46,   2,   3,  32,   0,  46,   3,  32,   0,  46, 
  3,  32,   1,  46,   4,   3,  32,   0,   0,   3,   0,   0,   0,   3,   0,   4, 
  0,  14,   7,   3,  68,   3,   8,   4,   1,   3,  10,  10,  12,  12,  12,  12, 
  0,   0,   3,   0,   7, 129,   1,   3, 130,   1, 132,   1, 134,   1, 131,   1, 
133,   1, 135,   1, 129,   1,   3, 130,   1, 132,   1, 134,   1, 136,   1, 137, 
  1, 135,   1, 129,   1,   3, 130,   1, 132,   1, 134,   1, 138,   1, 139,   1, 
135,   1, 129,   1,   3, 130,   1, 132,   1, 134,   1, 140,   1, 141,   1, 135, 
  1, 129,   1,   3, 130,   1, 132,   1, 134,   1, 142,   1, 143,   1, 135,   1, 
129,   1,   3, 130,   1, 132,   1, 134,   1, 144,   1, 145,   1, 135,   1, 129, 
  1,   3, 130,   1, 132,   1, 134,   1, 146,   1, 147,   1, 135,   1,  11,   3, 
  6,  11,   7,   0,   4,   5,  10,   2,   0,   5,  11,   1,   0,   6,  10,   3, 
  0,   7,  12,   1,   0,   8,  13,   2,   0,   9,  45,   6,  11,   9,   0,  41, 
  0,  48,   6,  11,  11,   0,  44,   0,  54,  55,  11,  14,   0,  53,   0,  64, 
  6,  11,  16,   0,  55,   0,  72,   6,   9,  18,   0,  57,   3,  69,   0,   0, 
 68,  12,  12,  70,   0,   0,   7,  10,  10,  71,   0,   0,   3,  12,  12,  84, 
  6,  11,  22,   0,  68,   0,  68,   6,   9,  24,   0,  71,   0,  92,   6,  11, 
 26,   0,  73,   0, 106,   6,  11,  28,   0,  85,   0, 109,  72,   9,  31,   0, 
 87,   1, 108,   0,   0,  14,   1,   3,   1,   2,   8,  18,   3,   2,   9,  18, 
  4,   3,  10,  30,  15,  18,   3,  11,  16,  18,  31,  39,  17,  18,   5,  13, 
 18,  18,   6,  14,  19,  18,   7,  15,  20,  18,   8,  16,  21,  18,   9,  17, 
 22,  18,  10,  18,  23,  18,  11,  19,  24,  18,  12,  20,  25,  18,  13,  21, 
 26,  18,  14,  22,  27,  18,  20,  28,  28,  18,  16,  24,  29,  18,  22,  30, 
 30,  18,  18,  26,  31,  18,  19,  27,  32,  18,  15,  23,  33,  18,  21,  29, 
 34,  18,  26,  34,  35,  18,  23,  31,  36,  18,  24,  32,  37,  18,  25,  33, 
 38,  18,  17,  25,  39,  18,  27,  35,  40,  18,  28,  36,  41,  18,  29,  37, 
 42,  18,  30,  38,  43,  18,   4,  12,  44,  18,  32,  40,  42,   1,  47,  17, 
  3,  43,  45,   7,  49,  18,   8,  51,  50,  18,   4,  47,  50,  19,   9,  52, 
 51,  19,   6,  49,  52,  17,   7,  50,  53,  17,   3,  46,  49,  19,   5,  48, 
 54,   8,  56,   6,   1,   2,  65,   1,  57,   6,   2,   2,  66,   1,  58,   6, 
  3,   2,  67,   1,  59,   6,   4,   2,  68,   1,  60,   6,   5,   2,  69,   1, 
 61,   6,   6,   2,  70,   1,  62,   6,   7,   2,  71,   1,  63,   6,   8,   2, 
 72,   1,  56,   0,  58,  13,  77,  17,   3,  59,  75,   6,   3,   2,  86,   1, 
 73,   6,   1,   2,  82,   1,  78,  19,   6,  62,  74,   6,   2,   2,  84,   1, 
 79,  18,   4,  60,  76,   6,   4,   2,  88,   1,  80,  18,  11,  67,  81,  17, 
  8,  64,  78,  18,   5,  61,  82,  17,   7,  63,  80,  19,  10,  66,  83,  17, 
  9,  65,  69,   1,   8,  18,   3,  70,  72,   7,  85,   6,   1,   2,  89,   1, 
 91,   6,   7,   2, 112,   1,  86,   6,   2,   2, 102,   1,  87,   6,   3,   2, 
104,   1,  88,   6,   4,   2, 106,   1,  90,   6,   6,   2, 110,   1,  89,   6, 
  5,   2, 108,   1,  74,  11,  97,  18,   3,  75,  98,  18,   4,  76,  99,  18, 
  5,  77,  98,  19,   6,  78, 100,  18,   7,  79, 101,  17,   8,  80,  93,   0, 
  1,  54,  12,  12, 102,  17,   9,  81, 103,  17,  10,  82, 104,  17,  11,  83, 
105,  17,  12,  84,  86,   0,   1,  88,  12,   3,  68,   1,   0,   1,   0,  68, 
 68,   9,   7,   1,   1, 106,  68,  11,   9,   1,   2,  84,  68,   8,   6,   1, 
  3,  92,   4,  10,   8, 109,   4,   7,  10,  54,  68,   4,   3,   1,   4,  48, 
 68,   3,   2,   1,   5,  45,  68,   2,   1,   1,   6,  64,   4,   5,   4, 113, 
  1,   1,   0,  72,   4,   6,   5,  25,   0,   3,   3,   1,   2,  12, 208,  48, 
100, 108,   3, 209, 210,  70,   1,   2,  41,  71,   0,   0,   1,   1,   1,   3, 
  4,   3, 208,  48,  71,   0,   0,   4,   1,   2,   4,   5,   6, 208,  48, 208, 
 73,   0,  71,   0,   0,  10,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0, 
 41,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  42,   1, 
  1,   3,   4,   3, 208,  48,  71,   0,   0,  44,   1,   1,   4,   5,   6, 208, 
 48, 208,  73,   0,  71,   0,   0,  45,   1,   1,   4,   5,   3, 208,  48,  71, 
  0,   0,  53,   1,   1,   5,   6,   6, 208,  48, 208,  73,   0,  71,   0,   0, 
 54,   2,   1,   3,   4,  51, 208,  48,  94,  56,  44,  65, 104,  56,  94,  57, 
 44,  66, 104,  57,  94,  58,  44,  67, 104,  58,  94,  59,  44,  68, 104,  59, 
 94,  60,  44,  69, 104,  60,  94,  61,  44,  70, 104,  61,  94,  62,  44,  71, 
104,  62,  94,  63,  44,  72, 104,  63,  71,   0,   0,  55,   1,   1,   4,   5, 
  6, 208,  48, 208,  73,   0,  71,   0,   0,  56,   1,   1,   3,   4,   3, 208, 
 48,  71,   0,   0,  57,   2,   4,   4,   5,  18, 208,  48, 208,  73,   0, 208, 
209, 104,  65, 208, 210, 104,  66, 208, 211, 104,  67,  71,   0,   0,  58,   2, 
  1,   3,   4,  27, 208,  48,  94,  73,  44,  82, 104,  73,  94,  74,  44,  84, 
104,  74,  94,  75,  44,  86, 104,  75,  94,  76,  44,  88, 104,  76,  71,   0, 
  0,  68,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  69, 
  1,   1,   3,   4,   3, 208,  48,  71,   0,   0,  71,   1,   1,   4,   5,   6, 
208,  48, 208,  73,   0,  71,   0,   0,  72,   2,   1,   3,   4,  45, 208,  48, 
 94,  85,  44,  89, 104,  85,  94,  86,  44, 102, 104,  86,  94,  87,  44, 104, 
104,  87,  94,  88,  44, 106, 104,  88,  94,  89,  44, 108, 104,  89,  94,  90, 
 44, 110, 104,  90,  94,  91,  44, 112, 104,  91,  71,   0,   0,  73,   1,   1, 
  4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  74,   2,   1,   3,   4, 
  8, 208,  48,  94,  93,  32,  97,  93,  71,   0,   0,  75,   2,   1,   3,   4, 
 37, 208,  48,  93,  94, 102,  94, 150,  18,  21,   0,   0, 100, 108,   4,  38, 
 97,  95,  94,  94,  93,  96,  74,  96,   0,  97,  94, 100, 108,   4,  39,  97, 
 95,  93,  94, 102,  94,  72,   0,   0,  85,   1,   1,   4,   5,   6, 208,  48, 
208,  73,   0,  71,   0,   0,  86,   1,   1,   4,   5,   3, 208,  48,  71,   0, 
  0,  87,   4,   5,   5,   6,  14, 208,  48, 208, 210, 211,  98,   4,  73,   3, 
208, 209, 104, 107,  71,   0,   0,  88,   2,   1,   1,   4, 190,   1, 208,  48, 
101,   0,  93,   6, 102,   6,  48,  93, 110, 102, 110,  88,   0,  29, 104,   3, 
101,   0,  93,   6, 102,   6,  48,  93, 111, 102, 111,  88,   1,  29, 104,  45, 
101,   0,  93,   6, 102,   6,  48,  93, 111, 102, 111,  88,   2,  29, 104,  48, 
101,   0,  93,   6, 102,   6,  48,  93,  55, 102,  55,  48,  93, 112, 102, 112, 
 88,   3,  29,  29, 104,  54, 101,   0,  93,   6, 102,   6,  48,  93, 111, 102, 
111,  88,   4,  29, 104,  64, 101,   0,  93,   6, 102,   6,  48,  93, 111, 102, 
111,  88,   5,  29, 104,  72, 101,   0,  93,   6, 102,   6,  48,  93,  72, 102, 
 72,  48, 100, 108,   6,  88,  10,  29,  29, 104, 109, 101,   0,  93,   6, 102, 
  6,  48,  93, 111, 102, 111,  88,   6,  29, 104,  84, 101,   0,  93,   6, 102, 
  6,  48,  93, 111, 102, 111,  88,   7,  29, 104,  68, 101,   0,  93,   6, 102, 
  6,  48,  93, 111, 102, 111,  88,   8,  29, 104,  92, 101,   0,  93,   6, 102, 
  6,  48,  93, 111, 102, 111,  88,   9,  29, 104, 106,  71,   0,   0};

} }
