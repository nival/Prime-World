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
    class AccessibilityClass; //flash.accessibility::Accessibility$
    class AccessibilityObject; //flash.accessibility::Accessibility
}

namespace avmplus { namespace NativeID {

extern const uint32_t accessibility_abc_class_count;
extern const uint32_t accessibility_abc_script_count;
extern const uint32_t accessibility_abc_method_count;
extern const uint32_t accessibility_abc_length;
extern const uint8_t accessibility_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(accessibility)

/* classes */
const uint32_t abcclass_flash_accessibility_Accessibility = 0;
const uint32_t abcclass_flash_accessibility_AccessibilityImplementation = 1;
const uint32_t abcclass_flash_accessibility_AccessibilityProperties = 2;

/* methods */
const uint32_t flash_accessibility_Accessibility_sendEvent = 1;
const uint32_t flash_accessibility_Accessibility_updateProperties = 2;
const uint32_t flash_accessibility_Accessibility_active_get = 3;

extern AvmBox accessibility_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_accessibility_Accessibility_active_get_thunk  accessibility_b2a_o_thunk

extern AvmBox accessibility_v2a_oouub_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_accessibility_Accessibility_sendEvent_thunk  accessibility_v2a_oouub_optbfalse_thunk

extern AvmBox accessibility_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_accessibility_Accessibility_updateProperties_thunk  accessibility_v2a_o_thunk

class SlotOffsetsAndAsserts;
// flash.accessibility::Accessibility$
//-----------------------------------------------------------
class AccessibilityClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_AccessibilityClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::AccessibilityClassSlots EmptySlotsStruct_AccessibilityClass
//-----------------------------------------------------------

// flash.accessibility::Accessibility
//-----------------------------------------------------------
class AccessibilityObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_AccessibilityObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::AccessibilityObjectSlots EmptySlotsStruct_AccessibilityObject
//-----------------------------------------------------------

} }
