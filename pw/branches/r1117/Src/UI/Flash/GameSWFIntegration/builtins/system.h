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
    class ApplicationDomainClass; //flash.system::ApplicationDomain$
    class ApplicationDomainObject; //flash.system::ApplicationDomain
    class CapabilitiesClass; //flash.system::Capabilities$
    class CapabilitiesObject; //flash.system::Capabilities
    class FSCommandClass; //flash.system::FSCommand$
    class FSCommandObject; //flash.system::FSCommand
    class IMEClass; //flash.system::IME$
    class IMEObject; //flash.system::IME
    class SecurityClass; //flash.system::Security$
    class SecurityDomainClass; //flash.system::SecurityDomain$
    class SecurityDomainObject; //flash.system::SecurityDomain
    class SecurityObject; //flash.system::Security
    class String; //String
    class SystemClass; //flash.system::System$
    class SystemObject; //flash.system::System
}

namespace avmplus { namespace NativeID {

extern const uint32_t system_abc_class_count;
extern const uint32_t system_abc_script_count;
extern const uint32_t system_abc_method_count;
extern const uint32_t system_abc_length;
extern const uint8_t system_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(system)

/* classes */
const uint32_t abcclass_flash_system_ApplicationDomain = 0;
const uint32_t abcclass_flash_system_Capabilities = 1;
const uint32_t abcclass_flash_system_FSCommand = 2;
const uint32_t abcclass_flash_system_IME = 3;
const uint32_t abcclass_flash_system_IMEConversionMode = 4;
const uint32_t abcclass_flash_system_LoaderContext = 5;
const uint32_t abcclass_flash_system_Security = 6;
const uint32_t abcclass_flash_system_SecurityDomain = 7;
const uint32_t abcclass_flash_system_SecurityPanel = 8;
const uint32_t abcclass_flash_system_System = 9;
const uint32_t abcclass_flash_system_JPEGLoaderContext = 10;

/* methods */
const uint32_t flash_system_ApplicationDomain_currentDomain_get = 2;
const uint32_t flash_system_ApplicationDomain_MIN_DOMAIN_MEMORY_LENGTH_get = 3;
const uint32_t flash_system_ApplicationDomain_domainMemory_get = 5;
const uint32_t flash_system_ApplicationDomain_getDefinition = 6;
const uint32_t flash_system_ApplicationDomain_domainMemory_set = 7;
const uint32_t flash_system_ApplicationDomain_hasDefinition = 8;
const uint32_t flash_system_ApplicationDomain_parentDomain_get = 9;
const uint32_t flash_system_Capabilities_hasTLS_get = 11;
const uint32_t flash_system_Capabilities_hasScreenBroadcast_get = 12;
const uint32_t flash_system_Capabilities_hasIME_get = 13;
const uint32_t flash_system_Capabilities_maxLevelIDC_get = 14;
const uint32_t flash_system_Capabilities_hasStreamingAudio_get = 15;
const uint32_t flash_system_Capabilities_hasPrinting_get = 16;
const uint32_t flash_system_Capabilities_screenDPI_get = 17;
const uint32_t flash_system_Capabilities_hasAccessibility_get = 18;
const uint32_t flash_system_Capabilities_hasMP3_get = 19;
const uint32_t flash_system_Capabilities_hasEmbeddedVideo_get = 20;
const uint32_t flash_system_Capabilities_manufacturer_get = 21;
const uint32_t flash_system_Capabilities_hasVideoEncoder_get = 22;
const uint32_t flash_system_Capabilities_hasAudio_get = 23;
const uint32_t flash_system_Capabilities_screenColor_get = 24;
const uint32_t flash_system_Capabilities_language_get = 25;
const uint32_t flash_system_Capabilities_hasAudioEncoder_get = 26;
const uint32_t flash_system_Capabilities_hasScreenPlayback_get = 27;
const uint32_t flash_system_Capabilities__internal_get = 28;
const uint32_t flash_system_Capabilities_os_get = 29;
const uint32_t flash_system_Capabilities_version_get = 30;
const uint32_t flash_system_Capabilities_screenResolutionY_get = 31;
const uint32_t flash_system_Capabilities_avHardwareDisable_get = 32;
const uint32_t flash_system_Capabilities_pixelAspectRatio_get = 33;
const uint32_t flash_system_Capabilities_screenResolutionX_get = 34;
const uint32_t flash_system_Capabilities_isDebugger_get = 35;
const uint32_t flash_system_Capabilities_hasStreamingVideo_get = 36;
const uint32_t flash_system_Capabilities_serverString_get = 37;
const uint32_t flash_system_Capabilities_localFileReadDisable_get = 38;
const uint32_t flash_system_Capabilities_playerType_get = 39;
const uint32_t flash_system_Capabilities_isEmbeddedInAcrobat_get = 40;
const uint32_t flash_system_FSCommand__fscommand = 43;
const uint32_t flash_system_IME_setCompositionString = 46;
const uint32_t flash_system_IME_enabled_get = 47;
const uint32_t flash_system_IME_conversionMode_set = 48;
const uint32_t flash_system_IME_constructOK_set = 49;
const uint32_t flash_system_IME_doConversion = 50;
const uint32_t flash_system_IME_conversionMode_get = 51;
const uint32_t flash_system_IME_enabled_set = 52;
const uint32_t flash_system_Security_showSettings = 59;
const uint32_t flash_system_Security_sandboxType_get = 60;
const uint32_t flash_system_Security_exactSettings_get = 61;
const uint32_t flash_system_Security_exactSettings_set = 62;
const uint32_t flash_system_Security_allowDomain = 63;
const uint32_t flash_system_Security_allowInsecureDomain = 64;
const uint32_t flash_system_Security_loadPolicyFile = 65;
const uint32_t flash_system_Security_disableAVM1Loading_set = 66;
const uint32_t flash_system_Security_disableAVM1Loading_get = 67;
const uint32_t flash_system_SecurityDomain_currentDomain_get = 70;
const uint32_t flash_system_System_useCodePage_get = 76;
const uint32_t flash_system_System_totalMemory_get = 77;
const uint32_t flash_system_System_useCodePage_set = 78;
const uint32_t flash_system_System_vmVersion_get = 79;
const uint32_t flash_system_System_resume = 80;
const uint32_t flash_system_System_setClipboard = 81;
const uint32_t flash_system_System_pause = 82;
const uint32_t flash_system_System_gc = 83;
const uint32_t flash_system_System_exit = 84;

extern AvmBox system_v2a_oss_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_FSCommand__fscommand_thunk  system_v2a_oss_thunk

extern AvmBox system_v2a_ob_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_IME_constructOK_set_thunk  system_v2a_ob_thunk
#define flash_system_System_useCodePage_set_thunk  system_v2a_ob_thunk
#define flash_system_IME_enabled_set_thunk  system_v2a_ob_thunk
#define flash_system_Security_exactSettings_set_thunk  system_v2a_ob_thunk
#define flash_system_Security_disableAVM1Loading_set_thunk  system_v2a_ob_thunk

extern AvmBox system_v2a_os_optsAvmThunkConstant_AvmString_89_____default_____thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_Security_showSettings_thunk  system_v2a_os_optsAvmThunkConstant_AvmString_89_____default_____thunk

extern AvmBox system_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_ApplicationDomain_domainMemory_set_thunk  system_v2a_oo_thunk

extern AvmBox system_a2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_ApplicationDomain_getDefinition_thunk  system_a2a_os_thunk

extern AvmBox system_v2a_o_rest_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_Security_allowDomain_thunk  system_v2a_o_rest_thunk
#define flash_system_Security_allowInsecureDomain_thunk  system_v2a_o_rest_thunk

extern AvmBox system_u2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_Capabilities__internal_get_thunk  system_u2a_o_thunk
#define flash_system_ApplicationDomain_MIN_DOMAIN_MEMORY_LENGTH_get_thunk  system_u2a_o_thunk
#define flash_system_System_totalMemory_get_thunk  system_u2a_o_thunk

extern AvmBox system_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_System_pause_thunk  system_v2a_o_thunk
#define flash_system_System_gc_thunk  system_v2a_o_thunk
#define flash_system_System_resume_thunk  system_v2a_o_thunk
#define flash_system_IME_doConversion_thunk  system_v2a_o_thunk

extern AvmBox system_b2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_ApplicationDomain_hasDefinition_thunk  system_b2a_os_thunk

extern AvmBox system_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_SecurityDomain_currentDomain_get_thunk  system_a2a_o_thunk
#define flash_system_ApplicationDomain_currentDomain_get_thunk  system_a2a_o_thunk
#define flash_system_ApplicationDomain_domainMemory_get_thunk  system_a2a_o_thunk
#define flash_system_ApplicationDomain_parentDomain_get_thunk  system_a2a_o_thunk

extern AvmBox system_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_Capabilities_hasPrinting_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_hasScreenBroadcast_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_hasIME_get_thunk  system_b2a_o_thunk
#define flash_system_System_useCodePage_get_thunk  system_b2a_o_thunk
#define flash_system_Security_disableAVM1Loading_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_hasStreamingVideo_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_isEmbeddedInAcrobat_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_hasTLS_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_hasMP3_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_hasVideoEncoder_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_avHardwareDisable_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_localFileReadDisable_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_hasEmbeddedVideo_get_thunk  system_b2a_o_thunk
#define flash_system_Security_exactSettings_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_hasScreenPlayback_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_hasStreamingAudio_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_hasAudio_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_hasAudioEncoder_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_hasAccessibility_get_thunk  system_b2a_o_thunk
#define flash_system_Capabilities_isDebugger_get_thunk  system_b2a_o_thunk
#define flash_system_IME_enabled_get_thunk  system_b2a_o_thunk

extern AvmBox system_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_IME_conversionMode_set_thunk  system_v2a_os_thunk
#define flash_system_System_setClipboard_thunk  system_v2a_os_thunk
#define flash_system_IME_setCompositionString_thunk  system_v2a_os_thunk
#define flash_system_Security_loadPolicyFile_thunk  system_v2a_os_thunk

extern AvmBox system_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_Capabilities_os_get_thunk  system_s2a_o_thunk
#define flash_system_Capabilities_version_get_thunk  system_s2a_o_thunk
#define flash_system_Security_sandboxType_get_thunk  system_s2a_o_thunk
#define flash_system_Capabilities_maxLevelIDC_get_thunk  system_s2a_o_thunk
#define flash_system_IME_conversionMode_get_thunk  system_s2a_o_thunk
#define flash_system_System_vmVersion_get_thunk  system_s2a_o_thunk
#define flash_system_Capabilities_serverString_get_thunk  system_s2a_o_thunk
#define flash_system_Capabilities_playerType_get_thunk  system_s2a_o_thunk
#define flash_system_Capabilities_screenColor_get_thunk  system_s2a_o_thunk
#define flash_system_Capabilities_manufacturer_get_thunk  system_s2a_o_thunk
#define flash_system_Capabilities_language_get_thunk  system_s2a_o_thunk

extern AvmBox system_v2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_System_exit_thunk  system_v2a_ou_thunk

extern double system_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_system_Capabilities_pixelAspectRatio_get_thunk  system_d2d_o_thunk
#define flash_system_Capabilities_screenResolutionY_get_thunk  system_d2d_o_thunk
#define flash_system_Capabilities_screenDPI_get_thunk  system_d2d_o_thunk
#define flash_system_Capabilities_screenResolutionX_get_thunk  system_d2d_o_thunk

class SlotOffsetsAndAsserts;
// flash.system::ApplicationDomain$
//-----------------------------------------------------------
class ApplicationDomainClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ApplicationDomainClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ApplicationDomainClassSlots EmptySlotsStruct_ApplicationDomainClass
//-----------------------------------------------------------

// flash.system::ApplicationDomain
//-----------------------------------------------------------
class ApplicationDomainObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ApplicationDomainObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ApplicationDomainObjectSlots EmptySlotsStruct_ApplicationDomainObject
//-----------------------------------------------------------

// flash.system::Capabilities$
//-----------------------------------------------------------
class CapabilitiesClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_CapabilitiesClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::CapabilitiesClassSlots EmptySlotsStruct_CapabilitiesClass
//-----------------------------------------------------------

// flash.system::Capabilities
//-----------------------------------------------------------
class CapabilitiesObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_CapabilitiesObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::CapabilitiesObjectSlots EmptySlotsStruct_CapabilitiesObject
//-----------------------------------------------------------

// flash.system::FSCommand$
//-----------------------------------------------------------
class FSCommandClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_FSCommandClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::FSCommandClassSlots EmptySlotsStruct_FSCommandClass
//-----------------------------------------------------------

// flash.system::FSCommand
//-----------------------------------------------------------
class FSCommandObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_FSCommandObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::FSCommandObjectSlots EmptySlotsStruct_FSCommandObject
//-----------------------------------------------------------

// flash.system::IME$
//-----------------------------------------------------------
class IMEClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_IMEClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::IMEClassSlots EmptySlotsStruct_IMEClass
//-----------------------------------------------------------

// flash.system::IME
//-----------------------------------------------------------
class IMEObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_IMEObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::IMEObjectSlots EmptySlotsStruct_IMEObject
//-----------------------------------------------------------

// flash.system::Security$
//-----------------------------------------------------------
class SecurityClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmString get_LOCAL_WITH_FILE() const { return m_LOCAL_WITH_FILE; }
    REALLY_INLINE AvmString get_LOCAL_TRUSTED() const { return m_LOCAL_TRUSTED; }
    REALLY_INLINE AvmString get_REMOTE() const { return m_REMOTE; }
    REALLY_INLINE AvmString get_LOCAL_WITH_NETWORK() const { return m_LOCAL_WITH_NETWORK; }
private:
    DRCWB(AvmString) m_LOCAL_WITH_FILE;
    DRCWB(AvmString) m_LOCAL_TRUSTED;
    DRCWB(AvmString) m_REMOTE;
    DRCWB(AvmString) m_LOCAL_WITH_NETWORK;
};
#define DECLARE_SLOTS_SecurityClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmString get_LOCAL_WITH_FILE() const { return m_slots_SecurityClass.get_LOCAL_WITH_FILE(); } \
        REALLY_INLINE AvmString get_LOCAL_TRUSTED() const { return m_slots_SecurityClass.get_LOCAL_TRUSTED(); } \
        REALLY_INLINE AvmString get_REMOTE() const { return m_slots_SecurityClass.get_REMOTE(); } \
        REALLY_INLINE AvmString get_LOCAL_WITH_NETWORK() const { return m_slots_SecurityClass.get_LOCAL_WITH_NETWORK(); } \
    private: \
        avmplus::NativeID::SecurityClassSlots m_slots_SecurityClass
//-----------------------------------------------------------

// flash.system::Security
//-----------------------------------------------------------
class SecurityObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SecurityObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SecurityObjectSlots EmptySlotsStruct_SecurityObject
//-----------------------------------------------------------

// flash.system::SecurityDomain$
//-----------------------------------------------------------
class SecurityDomainClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SecurityDomainClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SecurityDomainClassSlots EmptySlotsStruct_SecurityDomainClass
//-----------------------------------------------------------

// flash.system::SecurityDomain
//-----------------------------------------------------------
class SecurityDomainObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SecurityDomainObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SecurityDomainObjectSlots EmptySlotsStruct_SecurityDomainObject
//-----------------------------------------------------------

// flash.system::System$
//-----------------------------------------------------------
class SystemClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE IMEObject* get_private_theIME() const { return m_private_theIME; }
    void set_private_theIME(SystemClass* obj, IMEObject* newVal);
private:
    DRCWB(IMEObject*) m_private_theIME;
};
REALLY_INLINE void SystemClassSlots::set_private_theIME(SystemClass* obj, IMEObject* newVal)
{
    m_private_theIME.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_SystemClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE IMEObject* get_private_theIME() const { return m_slots_SystemClass.get_private_theIME(); } \
        REALLY_INLINE void set_private_theIME(IMEObject* newVal) { m_slots_SystemClass.set_private_theIME(this, newVal); } \
    private: \
        avmplus::NativeID::SystemClassSlots m_slots_SystemClass
//-----------------------------------------------------------

// flash.system::System
//-----------------------------------------------------------
class SystemObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SystemObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SystemObjectSlots EmptySlotsStruct_SystemObject
//-----------------------------------------------------------

} }
