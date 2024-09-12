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
    class EventClass; //flash.events::Event$
    class EventDispatcherClass; //flash.events::EventDispatcher$
    class EventDispatcherObject; //flash.events::EventDispatcher
    class EventObject; //flash.events::Event
    class InteractiveObjectObject; //flash.display::InteractiveObject
    class KeyboardEventClass; //flash.events::KeyboardEvent$
    class KeyboardEventObject; //flash.events::KeyboardEvent
    class MouseEventClass; //flash.events::MouseEvent$
    class MouseEventObject; //flash.events::MouseEvent
    class String; //String
    class TimerEventClass; //flash.events::TimerEvent$
    class TimerEventObject; //flash.events::TimerEvent
    class WeakMethodClosureClass; //flash.events::WeakMethodClosure$
    class WeakMethodClosureObject; //flash.events::WeakMethodClosure
}

namespace avmplus { namespace NativeID {

extern const uint32_t events_abc_class_count;
extern const uint32_t events_abc_script_count;
extern const uint32_t events_abc_method_count;
extern const uint32_t events_abc_length;
extern const uint8_t events_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(events)

/* classes */
const uint32_t abcclass_flash_events_Event = 0;
const uint32_t abcclass_flash_events_IEventDispatcher = 1;
const uint32_t abcclass_flash_events_EventPhase = 2;
const uint32_t abcclass_flash_events_WeakFunctionClosure = 3;
const uint32_t abcclass_flash_events_WeakMethodClosure = 4;
const uint32_t abcclass_flash_events_TextEvent = 5;
const uint32_t abcclass_flash_events_ActivityEvent = 6;
const uint32_t abcclass_flash_events_ContextMenuEvent = 7;
const uint32_t abcclass_flash_events_FocusEvent = 8;
const uint32_t abcclass_flash_events_HTTPStatusEvent = 9;
const uint32_t abcclass_flash_events_KeyboardEvent = 10;
const uint32_t abcclass_flash_events_MouseEvent = 11;
const uint32_t abcclass_flash_events_NetFilterEvent = 12;
const uint32_t abcclass_flash_events_NetStatusEvent = 13;
const uint32_t abcclass_flash_events_ProgressEvent = 14;
const uint32_t abcclass_flash_events_SampleDataEvent = 15;
const uint32_t abcclass_flash_events_ShaderEvent = 16;
const uint32_t abcclass_flash_events_StatusEvent = 17;
const uint32_t abcclass_flash_events_SyncEvent = 18;
const uint32_t abcclass_flash_events_TimerEvent = 19;
const uint32_t abcclass_flash_events_EventDispatcher = 20;
const uint32_t abcclass_flash_events_ErrorEvent = 21;
const uint32_t abcclass_flash_events_DataEvent = 22;
const uint32_t abcclass_flash_events_IMEEvent = 23;
const uint32_t abcclass_flash_events_FullScreenEvent = 24;
const uint32_t abcclass_flash_events_AsyncErrorEvent = 25;
const uint32_t abcclass_flash_events_IOErrorEvent = 26;
const uint32_t abcclass_flash_events_SecurityErrorEvent = 27;

/* methods */
const uint32_t flash_events_Event_private_Init = 2;
const uint32_t flash_events_Event_isDefaultPrevented = 3;
const uint32_t flash_events_Event_eventPhase_get = 4;
const uint32_t flash_events_Event_bubbles_get = 7;
const uint32_t flash_events_Event_preventDefault = 8;
const uint32_t flash_events_Event_stopPropagation = 9;
const uint32_t flash_events_Event_target_get = 11;
const uint32_t flash_events_Event_cancelable_get = 12;
const uint32_t flash_events_Event_currentTarget_get = 13;
const uint32_t flash_events_Event_type_get = 14;
const uint32_t flash_events_Event_stopImmediatePropagation = 15;
const uint32_t flash_events_WeakMethodClosure_private_savedThis_get = 29;
const uint32_t flash_events_KeyboardEvent_updateAfterEvent = 74;
const uint32_t flash_events_MouseEvent_updateAfterEvent = 91;
const uint32_t flash_events_MouseEvent_localX_get = 93;
const uint32_t flash_events_MouseEvent_localY_get = 94;
const uint32_t flash_events_MouseEvent_private_getStageY = 95;
const uint32_t flash_events_MouseEvent_private_getStageX = 97;
const uint32_t flash_events_MouseEvent_localX_set = 98;
const uint32_t flash_events_MouseEvent_localY_set = 100;
const uint32_t flash_events_TimerEvent_updateAfterEvent = 167;
const uint32_t flash_events_EventDispatcher_willTrigger = 171;
const uint32_t flash_events_EventDispatcher_removeEventListener = 172;
const uint32_t flash_events_EventDispatcher_private_dispatchEventFunction = 174;
const uint32_t flash_events_EventDispatcher_hasEventListener = 175;
const uint32_t flash_events_EventDispatcher_addEventListener = 176;
const uint32_t flash_events_EventDispatcher_private_listeners_get = 177;

extern AvmBox events_v2a_osob_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_EventDispatcher_removeEventListener_thunk  events_v2a_osob_optbfalse_thunk

extern AvmBox events_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_MouseEvent_localX_set_thunk  events_v2a_od_thunk
#define flash_events_MouseEvent_localY_set_thunk  events_v2a_od_thunk

extern AvmBox events_v2a_osobib_optbfalse_opti0_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_EventDispatcher_addEventListener_thunk  events_v2a_osobib_optbfalse_opti0_optbfalse_thunk

extern AvmBox events_b2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_EventDispatcher_private_dispatchEventFunction_thunk  events_b2a_oo_thunk

extern AvmBox events_u2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_Event_eventPhase_get_thunk  events_u2a_o_thunk

extern AvmBox events_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_TimerEvent_updateAfterEvent_thunk  events_v2a_o_thunk
#define flash_events_Event_stopPropagation_thunk  events_v2a_o_thunk
#define flash_events_MouseEvent_updateAfterEvent_thunk  events_v2a_o_thunk
#define flash_events_Event_preventDefault_thunk  events_v2a_o_thunk
#define flash_events_Event_stopImmediatePropagation_thunk  events_v2a_o_thunk
#define flash_events_KeyboardEvent_updateAfterEvent_thunk  events_v2a_o_thunk

extern AvmBox events_b2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_EventDispatcher_willTrigger_thunk  events_b2a_os_thunk
#define flash_events_EventDispatcher_hasEventListener_thunk  events_b2a_os_thunk

extern AvmBox events_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_Event_target_get_thunk  events_a2a_o_thunk
#define flash_events_WeakMethodClosure_private_savedThis_get_thunk  events_a2a_o_thunk
#define flash_events_EventDispatcher_private_listeners_get_thunk  events_a2a_o_thunk
#define flash_events_Event_currentTarget_get_thunk  events_a2a_o_thunk

extern AvmBox events_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_Event_cancelable_get_thunk  events_b2a_o_thunk
#define flash_events_Event_bubbles_get_thunk  events_b2a_o_thunk
#define flash_events_Event_isDefaultPrevented_thunk  events_b2a_o_thunk

extern AvmBox events_v2a_osbb_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_Event_private_Init_thunk  events_v2a_osbb_thunk

extern AvmBox events_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_Event_type_get_thunk  events_s2a_o_thunk

extern double events_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_events_MouseEvent_localY_get_thunk  events_d2d_o_thunk
#define flash_events_MouseEvent_private_getStageX_thunk  events_d2d_o_thunk
#define flash_events_MouseEvent_localX_get_thunk  events_d2d_o_thunk
#define flash_events_MouseEvent_private_getStageY_thunk  events_d2d_o_thunk

class SlotOffsetsAndAsserts;
// flash.events::Event$
//-----------------------------------------------------------
class EventClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmString get_ACTIVATE() const { return m_ACTIVATE; }
    REALLY_INLINE AvmString get_SELECT() const { return m_SELECT; }
    REALLY_INLINE AvmString get_ENTER_FRAME() const { return m_ENTER_FRAME; }
    REALLY_INLINE AvmString get_SOUND_COMPLETE() const { return m_SOUND_COMPLETE; }
    REALLY_INLINE AvmString get_INIT() const { return m_INIT; }
    REALLY_INLINE AvmString get_RENDER() const { return m_RENDER; }
    REALLY_INLINE AvmString get_TAB_ENABLED_CHANGE() const { return m_TAB_ENABLED_CHANGE; }
    REALLY_INLINE AvmString get_ADDED_TO_STAGE() const { return m_ADDED_TO_STAGE; }
    REALLY_INLINE AvmString get_FRAME_CONSTRUCTED() const { return m_FRAME_CONSTRUCTED; }
    REALLY_INLINE AvmString get_TAB_CHILDREN_CHANGE() const { return m_TAB_CHILDREN_CHANGE; }
    REALLY_INLINE AvmString get_CUT() const { return m_CUT; }
    REALLY_INLINE AvmString get_CLEAR() const { return m_CLEAR; }
    REALLY_INLINE AvmString get_RESIZE() const { return m_RESIZE; }
    REALLY_INLINE AvmString get_COMPLETE() const { return m_COMPLETE; }
    REALLY_INLINE AvmString get_FULLSCREEN() const { return m_FULLSCREEN; }
    REALLY_INLINE AvmString get_SELECT_ALL() const { return m_SELECT_ALL; }
    REALLY_INLINE AvmString get_CHANGE() const { return m_CHANGE; }
    REALLY_INLINE AvmString get_REMOVED() const { return m_REMOVED; }
    REALLY_INLINE AvmString get_CONNECT() const { return m_CONNECT; }
    REALLY_INLINE AvmString get_SCROLL() const { return m_SCROLL; }
    REALLY_INLINE AvmString get_OPEN() const { return m_OPEN; }
    REALLY_INLINE AvmString get_CLOSE() const { return m_CLOSE; }
    REALLY_INLINE AvmString get_MOUSE_LEAVE() const { return m_MOUSE_LEAVE; }
    REALLY_INLINE AvmString get_ADDED() const { return m_ADDED; }
    REALLY_INLINE AvmString get_REMOVED_FROM_STAGE() const { return m_REMOVED_FROM_STAGE; }
    REALLY_INLINE AvmString get_EXIT_FRAME() const { return m_EXIT_FRAME; }
    REALLY_INLINE AvmString get_TAB_INDEX_CHANGE() const { return m_TAB_INDEX_CHANGE; }
    REALLY_INLINE AvmString get_PASTE() const { return m_PASTE; }
    REALLY_INLINE AvmString get_COPY() const { return m_COPY; }
    REALLY_INLINE AvmString get_ID3() const { return m_ID3; }
    REALLY_INLINE AvmString get_CANCEL() const { return m_CANCEL; }
    REALLY_INLINE AvmString get_DEACTIVATE() const { return m_DEACTIVATE; }
    REALLY_INLINE AvmString get_UNLOAD() const { return m_UNLOAD; }
private:
    DRCWB(AvmString) m_ACTIVATE;
    DRCWB(AvmString) m_SELECT;
    DRCWB(AvmString) m_ENTER_FRAME;
    DRCWB(AvmString) m_SOUND_COMPLETE;
    DRCWB(AvmString) m_INIT;
    DRCWB(AvmString) m_RENDER;
    DRCWB(AvmString) m_TAB_ENABLED_CHANGE;
    DRCWB(AvmString) m_ADDED_TO_STAGE;
    DRCWB(AvmString) m_FRAME_CONSTRUCTED;
    DRCWB(AvmString) m_TAB_CHILDREN_CHANGE;
    DRCWB(AvmString) m_CUT;
    DRCWB(AvmString) m_CLEAR;
    DRCWB(AvmString) m_RESIZE;
    DRCWB(AvmString) m_COMPLETE;
    DRCWB(AvmString) m_FULLSCREEN;
    DRCWB(AvmString) m_SELECT_ALL;
    DRCWB(AvmString) m_CHANGE;
    DRCWB(AvmString) m_REMOVED;
    DRCWB(AvmString) m_CONNECT;
    DRCWB(AvmString) m_SCROLL;
    DRCWB(AvmString) m_OPEN;
    DRCWB(AvmString) m_CLOSE;
    DRCWB(AvmString) m_MOUSE_LEAVE;
    DRCWB(AvmString) m_ADDED;
    DRCWB(AvmString) m_REMOVED_FROM_STAGE;
    DRCWB(AvmString) m_EXIT_FRAME;
    DRCWB(AvmString) m_TAB_INDEX_CHANGE;
    DRCWB(AvmString) m_PASTE;
    DRCWB(AvmString) m_COPY;
    DRCWB(AvmString) m_ID3;
    DRCWB(AvmString) m_CANCEL;
    DRCWB(AvmString) m_DEACTIVATE;
    DRCWB(AvmString) m_UNLOAD;
};
#define DECLARE_SLOTS_EventClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmString get_ACTIVATE() const { return m_slots_EventClass.get_ACTIVATE(); } \
        REALLY_INLINE AvmString get_SELECT() const { return m_slots_EventClass.get_SELECT(); } \
        REALLY_INLINE AvmString get_ENTER_FRAME() const { return m_slots_EventClass.get_ENTER_FRAME(); } \
        REALLY_INLINE AvmString get_SOUND_COMPLETE() const { return m_slots_EventClass.get_SOUND_COMPLETE(); } \
        REALLY_INLINE AvmString get_INIT() const { return m_slots_EventClass.get_INIT(); } \
        REALLY_INLINE AvmString get_RENDER() const { return m_slots_EventClass.get_RENDER(); } \
        REALLY_INLINE AvmString get_TAB_ENABLED_CHANGE() const { return m_slots_EventClass.get_TAB_ENABLED_CHANGE(); } \
        REALLY_INLINE AvmString get_ADDED_TO_STAGE() const { return m_slots_EventClass.get_ADDED_TO_STAGE(); } \
        REALLY_INLINE AvmString get_FRAME_CONSTRUCTED() const { return m_slots_EventClass.get_FRAME_CONSTRUCTED(); } \
        REALLY_INLINE AvmString get_TAB_CHILDREN_CHANGE() const { return m_slots_EventClass.get_TAB_CHILDREN_CHANGE(); } \
        REALLY_INLINE AvmString get_CUT() const { return m_slots_EventClass.get_CUT(); } \
        REALLY_INLINE AvmString get_CLEAR() const { return m_slots_EventClass.get_CLEAR(); } \
        REALLY_INLINE AvmString get_RESIZE() const { return m_slots_EventClass.get_RESIZE(); } \
        REALLY_INLINE AvmString get_COMPLETE() const { return m_slots_EventClass.get_COMPLETE(); } \
        REALLY_INLINE AvmString get_FULLSCREEN() const { return m_slots_EventClass.get_FULLSCREEN(); } \
        REALLY_INLINE AvmString get_SELECT_ALL() const { return m_slots_EventClass.get_SELECT_ALL(); } \
        REALLY_INLINE AvmString get_CHANGE() const { return m_slots_EventClass.get_CHANGE(); } \
        REALLY_INLINE AvmString get_REMOVED() const { return m_slots_EventClass.get_REMOVED(); } \
        REALLY_INLINE AvmString get_CONNECT() const { return m_slots_EventClass.get_CONNECT(); } \
        REALLY_INLINE AvmString get_SCROLL() const { return m_slots_EventClass.get_SCROLL(); } \
        REALLY_INLINE AvmString get_OPEN() const { return m_slots_EventClass.get_OPEN(); } \
        REALLY_INLINE AvmString get_CLOSE() const { return m_slots_EventClass.get_CLOSE(); } \
        REALLY_INLINE AvmString get_MOUSE_LEAVE() const { return m_slots_EventClass.get_MOUSE_LEAVE(); } \
        REALLY_INLINE AvmString get_ADDED() const { return m_slots_EventClass.get_ADDED(); } \
        REALLY_INLINE AvmString get_REMOVED_FROM_STAGE() const { return m_slots_EventClass.get_REMOVED_FROM_STAGE(); } \
        REALLY_INLINE AvmString get_EXIT_FRAME() const { return m_slots_EventClass.get_EXIT_FRAME(); } \
        REALLY_INLINE AvmString get_TAB_INDEX_CHANGE() const { return m_slots_EventClass.get_TAB_INDEX_CHANGE(); } \
        REALLY_INLINE AvmString get_PASTE() const { return m_slots_EventClass.get_PASTE(); } \
        REALLY_INLINE AvmString get_COPY() const { return m_slots_EventClass.get_COPY(); } \
        REALLY_INLINE AvmString get_ID3() const { return m_slots_EventClass.get_ID3(); } \
        REALLY_INLINE AvmString get_CANCEL() const { return m_slots_EventClass.get_CANCEL(); } \
        REALLY_INLINE AvmString get_DEACTIVATE() const { return m_slots_EventClass.get_DEACTIVATE(); } \
        REALLY_INLINE AvmString get_UNLOAD() const { return m_slots_EventClass.get_UNLOAD(); } \
    private: \
        avmplus::NativeID::EventClassSlots m_slots_EventClass
//-----------------------------------------------------------

// flash.events::Event
//-----------------------------------------------------------
class EventObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_EventObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::EventObjectSlots EmptySlotsStruct_EventObject
//-----------------------------------------------------------

// flash.events::WeakMethodClosure$
//-----------------------------------------------------------
class WeakMethodClosureClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_WeakMethodClosureClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::WeakMethodClosureClassSlots EmptySlotsStruct_WeakMethodClosureClass
//-----------------------------------------------------------

// flash.events::WeakMethodClosure
//-----------------------------------------------------------
class WeakMethodClosureObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_WeakMethodClosureObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::WeakMethodClosureObjectSlots EmptySlotsStruct_WeakMethodClosureObject
//-----------------------------------------------------------

// flash.events::KeyboardEvent$
//-----------------------------------------------------------
class KeyboardEventClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmString get_KEY_DOWN() const { return m_KEY_DOWN; }
    REALLY_INLINE AvmString get_KEY_UP() const { return m_KEY_UP; }
private:
    DRCWB(AvmString) m_KEY_DOWN;
    DRCWB(AvmString) m_KEY_UP;
};
#define DECLARE_SLOTS_KeyboardEventClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmString get_KEY_DOWN() const { return m_slots_KeyboardEventClass.get_KEY_DOWN(); } \
        REALLY_INLINE AvmString get_KEY_UP() const { return m_slots_KeyboardEventClass.get_KEY_UP(); } \
    private: \
        avmplus::NativeID::KeyboardEventClassSlots m_slots_KeyboardEventClass
//-----------------------------------------------------------

// flash.events::KeyboardEvent
//-----------------------------------------------------------
class KeyboardEventObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmBool32 get_private_m_altKey() const { return m_private_m_altKey; }
    void set_private_m_altKey(AvmBool32 newVal);
    REALLY_INLINE AvmBool32 get_private_m_shiftKey() const { return m_private_m_shiftKey; }
    void set_private_m_shiftKey(AvmBool32 newVal);
    REALLY_INLINE uint32_t get_private_m_keyCode() const { return m_private_m_keyCode; }
    void set_private_m_keyCode(uint32_t newVal);
    REALLY_INLINE uint32_t get_private_m_keyLocation() const { return m_private_m_keyLocation; }
    void set_private_m_keyLocation(uint32_t newVal);
    REALLY_INLINE AvmBool32 get_private_m_ctrlKey() const { return m_private_m_ctrlKey; }
    void set_private_m_ctrlKey(AvmBool32 newVal);
    REALLY_INLINE uint32_t get_private_m_charCode() const { return m_private_m_charCode; }
    void set_private_m_charCode(uint32_t newVal);
private:
    AvmBool32 m_private_m_altKey;
    AvmBool32 m_private_m_shiftKey;
    uint32_t m_private_m_keyCode;
    uint32_t m_private_m_keyLocation;
    AvmBool32 m_private_m_ctrlKey;
    uint32_t m_private_m_charCode;
};
REALLY_INLINE void KeyboardEventObjectSlots::set_private_m_altKey(AvmBool32 newVal) { m_private_m_altKey = newVal; }
REALLY_INLINE void KeyboardEventObjectSlots::set_private_m_shiftKey(AvmBool32 newVal) { m_private_m_shiftKey = newVal; }
REALLY_INLINE void KeyboardEventObjectSlots::set_private_m_keyCode(uint32_t newVal) { m_private_m_keyCode = newVal; }
REALLY_INLINE void KeyboardEventObjectSlots::set_private_m_keyLocation(uint32_t newVal) { m_private_m_keyLocation = newVal; }
REALLY_INLINE void KeyboardEventObjectSlots::set_private_m_ctrlKey(AvmBool32 newVal) { m_private_m_ctrlKey = newVal; }
REALLY_INLINE void KeyboardEventObjectSlots::set_private_m_charCode(uint32_t newVal) { m_private_m_charCode = newVal; }
#define DECLARE_SLOTS_KeyboardEventObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmBool32 get_private_m_altKey() const { return m_slots_KeyboardEventObject.get_private_m_altKey(); } \
        REALLY_INLINE void set_private_m_altKey(AvmBool32 newVal) { m_slots_KeyboardEventObject.set_private_m_altKey(newVal); } \
        REALLY_INLINE AvmBool32 get_private_m_shiftKey() const { return m_slots_KeyboardEventObject.get_private_m_shiftKey(); } \
        REALLY_INLINE void set_private_m_shiftKey(AvmBool32 newVal) { m_slots_KeyboardEventObject.set_private_m_shiftKey(newVal); } \
        REALLY_INLINE uint32_t get_private_m_keyCode() const { return m_slots_KeyboardEventObject.get_private_m_keyCode(); } \
        REALLY_INLINE void set_private_m_keyCode(uint32_t newVal) { m_slots_KeyboardEventObject.set_private_m_keyCode(newVal); } \
        REALLY_INLINE uint32_t get_private_m_keyLocation() const { return m_slots_KeyboardEventObject.get_private_m_keyLocation(); } \
        REALLY_INLINE void set_private_m_keyLocation(uint32_t newVal) { m_slots_KeyboardEventObject.set_private_m_keyLocation(newVal); } \
        REALLY_INLINE AvmBool32 get_private_m_ctrlKey() const { return m_slots_KeyboardEventObject.get_private_m_ctrlKey(); } \
        REALLY_INLINE void set_private_m_ctrlKey(AvmBool32 newVal) { m_slots_KeyboardEventObject.set_private_m_ctrlKey(newVal); } \
        REALLY_INLINE uint32_t get_private_m_charCode() const { return m_slots_KeyboardEventObject.get_private_m_charCode(); } \
        REALLY_INLINE void set_private_m_charCode(uint32_t newVal) { m_slots_KeyboardEventObject.set_private_m_charCode(newVal); } \
    private: \
        avmplus::NativeID::KeyboardEventObjectSlots m_slots_KeyboardEventObject
//-----------------------------------------------------------

// flash.events::MouseEvent$
//-----------------------------------------------------------
class MouseEventClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmString get_MOUSE_WHEEL() const { return m_MOUSE_WHEEL; }
    REALLY_INLINE AvmString get_MOUSE_DOWN() const { return m_MOUSE_DOWN; }
    REALLY_INLINE AvmString get_CLICK() const { return m_CLICK; }
    REALLY_INLINE AvmString get_MOUSE_MOVE() const { return m_MOUSE_MOVE; }
    REALLY_INLINE AvmString get_ROLL_OUT() const { return m_ROLL_OUT; }
    REALLY_INLINE AvmString get_MOUSE_OVER() const { return m_MOUSE_OVER; }
    REALLY_INLINE AvmString get_MOUSE_OUT() const { return m_MOUSE_OUT; }
    REALLY_INLINE AvmString get_MOUSE_UP() const { return m_MOUSE_UP; }
    REALLY_INLINE AvmString get_DOUBLE_CLICK() const { return m_DOUBLE_CLICK; }
    REALLY_INLINE AvmString get_ROLL_OVER() const { return m_ROLL_OVER; }
private:
    DRCWB(AvmString) m_MOUSE_WHEEL;
    DRCWB(AvmString) m_MOUSE_DOWN;
    DRCWB(AvmString) m_CLICK;
    DRCWB(AvmString) m_MOUSE_MOVE;
    DRCWB(AvmString) m_ROLL_OUT;
    DRCWB(AvmString) m_MOUSE_OVER;
    DRCWB(AvmString) m_MOUSE_OUT;
    DRCWB(AvmString) m_MOUSE_UP;
    DRCWB(AvmString) m_DOUBLE_CLICK;
    DRCWB(AvmString) m_ROLL_OVER;
};
#define DECLARE_SLOTS_MouseEventClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmString get_MOUSE_WHEEL() const { return m_slots_MouseEventClass.get_MOUSE_WHEEL(); } \
        REALLY_INLINE AvmString get_MOUSE_DOWN() const { return m_slots_MouseEventClass.get_MOUSE_DOWN(); } \
        REALLY_INLINE AvmString get_CLICK() const { return m_slots_MouseEventClass.get_CLICK(); } \
        REALLY_INLINE AvmString get_MOUSE_MOVE() const { return m_slots_MouseEventClass.get_MOUSE_MOVE(); } \
        REALLY_INLINE AvmString get_ROLL_OUT() const { return m_slots_MouseEventClass.get_ROLL_OUT(); } \
        REALLY_INLINE AvmString get_MOUSE_OVER() const { return m_slots_MouseEventClass.get_MOUSE_OVER(); } \
        REALLY_INLINE AvmString get_MOUSE_OUT() const { return m_slots_MouseEventClass.get_MOUSE_OUT(); } \
        REALLY_INLINE AvmString get_MOUSE_UP() const { return m_slots_MouseEventClass.get_MOUSE_UP(); } \
        REALLY_INLINE AvmString get_DOUBLE_CLICK() const { return m_slots_MouseEventClass.get_DOUBLE_CLICK(); } \
        REALLY_INLINE AvmString get_ROLL_OVER() const { return m_slots_MouseEventClass.get_ROLL_OVER(); } \
    private: \
        avmplus::NativeID::MouseEventClassSlots m_slots_MouseEventClass
//-----------------------------------------------------------

// flash.events::MouseEvent
//-----------------------------------------------------------
class MouseEventObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmBool32 get_private_m_buttonDown() const { return m_private_m_buttonDown; }
    void set_private_m_buttonDown(AvmBool32 newVal);
    REALLY_INLINE AvmBool32 get_private_m_altKey() const { return m_private_m_altKey; }
    void set_private_m_altKey(AvmBool32 newVal);
    REALLY_INLINE AvmBool32 get_private_m_shiftKey() const { return m_private_m_shiftKey; }
    void set_private_m_shiftKey(AvmBool32 newVal);
    REALLY_INLINE AvmBool32 get_private_m_ctrlKey() const { return m_private_m_ctrlKey; }
    void set_private_m_ctrlKey(AvmBool32 newVal);
    REALLY_INLINE int32_t get_private_m_delta() const { return m_private_m_delta; }
    void set_private_m_delta(int32_t newVal);
    REALLY_INLINE AvmBool32 get_private_m_isRelatedObjectInaccessible() const { return m_private_m_isRelatedObjectInaccessible; }
    void set_private_m_isRelatedObjectInaccessible(AvmBool32 newVal);
    REALLY_INLINE InteractiveObjectObject* get_private_m_relatedObject() const { return m_private_m_relatedObject; }
    void set_private_m_relatedObject(MouseEventObject* obj, InteractiveObjectObject* newVal);
private:
    AvmBool32 m_private_m_buttonDown;
    AvmBool32 m_private_m_altKey;
    AvmBool32 m_private_m_shiftKey;
    AvmBool32 m_private_m_ctrlKey;
    int32_t m_private_m_delta;
    AvmBool32 m_private_m_isRelatedObjectInaccessible;
    DRCWB(InteractiveObjectObject*) m_private_m_relatedObject;
};
REALLY_INLINE void MouseEventObjectSlots::set_private_m_buttonDown(AvmBool32 newVal) { m_private_m_buttonDown = newVal; }
REALLY_INLINE void MouseEventObjectSlots::set_private_m_altKey(AvmBool32 newVal) { m_private_m_altKey = newVal; }
REALLY_INLINE void MouseEventObjectSlots::set_private_m_shiftKey(AvmBool32 newVal) { m_private_m_shiftKey = newVal; }
REALLY_INLINE void MouseEventObjectSlots::set_private_m_ctrlKey(AvmBool32 newVal) { m_private_m_ctrlKey = newVal; }
REALLY_INLINE void MouseEventObjectSlots::set_private_m_delta(int32_t newVal) { m_private_m_delta = newVal; }
REALLY_INLINE void MouseEventObjectSlots::set_private_m_isRelatedObjectInaccessible(AvmBool32 newVal) { m_private_m_isRelatedObjectInaccessible = newVal; }
REALLY_INLINE void MouseEventObjectSlots::set_private_m_relatedObject(MouseEventObject* obj, InteractiveObjectObject* newVal)
{
    m_private_m_relatedObject.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_MouseEventObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmBool32 get_private_m_buttonDown() const { return m_slots_MouseEventObject.get_private_m_buttonDown(); } \
        REALLY_INLINE void set_private_m_buttonDown(AvmBool32 newVal) { m_slots_MouseEventObject.set_private_m_buttonDown(newVal); } \
        REALLY_INLINE AvmBool32 get_private_m_altKey() const { return m_slots_MouseEventObject.get_private_m_altKey(); } \
        REALLY_INLINE void set_private_m_altKey(AvmBool32 newVal) { m_slots_MouseEventObject.set_private_m_altKey(newVal); } \
        REALLY_INLINE AvmBool32 get_private_m_shiftKey() const { return m_slots_MouseEventObject.get_private_m_shiftKey(); } \
        REALLY_INLINE void set_private_m_shiftKey(AvmBool32 newVal) { m_slots_MouseEventObject.set_private_m_shiftKey(newVal); } \
        REALLY_INLINE AvmBool32 get_private_m_ctrlKey() const { return m_slots_MouseEventObject.get_private_m_ctrlKey(); } \
        REALLY_INLINE void set_private_m_ctrlKey(AvmBool32 newVal) { m_slots_MouseEventObject.set_private_m_ctrlKey(newVal); } \
        REALLY_INLINE int32_t get_private_m_delta() const { return m_slots_MouseEventObject.get_private_m_delta(); } \
        REALLY_INLINE void set_private_m_delta(int32_t newVal) { m_slots_MouseEventObject.set_private_m_delta(newVal); } \
        REALLY_INLINE AvmBool32 get_private_m_isRelatedObjectInaccessible() const { return m_slots_MouseEventObject.get_private_m_isRelatedObjectInaccessible(); } \
        REALLY_INLINE void set_private_m_isRelatedObjectInaccessible(AvmBool32 newVal) { m_slots_MouseEventObject.set_private_m_isRelatedObjectInaccessible(newVal); } \
        REALLY_INLINE InteractiveObjectObject* get_private_m_relatedObject() const { return m_slots_MouseEventObject.get_private_m_relatedObject(); } \
        REALLY_INLINE void set_private_m_relatedObject(InteractiveObjectObject* newVal) { m_slots_MouseEventObject.set_private_m_relatedObject(this, newVal); } \
    private: \
        avmplus::NativeID::MouseEventObjectSlots m_slots_MouseEventObject
//-----------------------------------------------------------

// flash.events::TimerEvent$
//-----------------------------------------------------------
class TimerEventClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmString get_TIMER_COMPLETE() const { return m_TIMER_COMPLETE; }
    REALLY_INLINE AvmString get_TIMER() const { return m_TIMER; }
private:
    DRCWB(AvmString) m_TIMER_COMPLETE;
    DRCWB(AvmString) m_TIMER;
};
#define DECLARE_SLOTS_TimerEventClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmString get_TIMER_COMPLETE() const { return m_slots_TimerEventClass.get_TIMER_COMPLETE(); } \
        REALLY_INLINE AvmString get_TIMER() const { return m_slots_TimerEventClass.get_TIMER(); } \
    private: \
        avmplus::NativeID::TimerEventClassSlots m_slots_TimerEventClass
//-----------------------------------------------------------

// flash.events::TimerEvent
//-----------------------------------------------------------
class TimerEventObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TimerEventObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TimerEventObjectSlots EmptySlotsStruct_TimerEventObject
//-----------------------------------------------------------

// flash.events::EventDispatcher$
//-----------------------------------------------------------
class EventDispatcherClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_EventDispatcherClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::EventDispatcherClassSlots EmptySlotsStruct_EventDispatcherClass
//-----------------------------------------------------------

// flash.events::EventDispatcher
//-----------------------------------------------------------
class EventDispatcherObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_EventDispatcherObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::EventDispatcherObjectSlots EmptySlotsStruct_EventDispatcherObject
//-----------------------------------------------------------

} }
