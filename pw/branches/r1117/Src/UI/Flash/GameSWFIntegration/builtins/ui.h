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
    class ContextMenuClass; //flash.ui::ContextMenu$
    class ContextMenuItemClass; //flash.ui::ContextMenuItem$
    class ContextMenuItemObject; //flash.ui::ContextMenuItem
    class ContextMenuObject; //flash.ui::ContextMenu
    class KeyboardClass; //flash.ui::Keyboard$
    class KeyboardObject; //flash.ui::Keyboard
    class MouseClass; //flash.ui::Mouse$
    class MouseObject; //flash.ui::Mouse
}

namespace avmplus { namespace NativeID {

extern const uint32_t ui_abc_class_count;
extern const uint32_t ui_abc_script_count;
extern const uint32_t ui_abc_method_count;
extern const uint32_t ui_abc_length;
extern const uint8_t ui_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(ui)

/* classes */
const uint32_t abcclass_flash_ui_ContextMenu = 0;
const uint32_t abcclass_flash_ui_ContextMenuBuiltInItems = 1;
const uint32_t abcclass_flash_ui_ContextMenuClipboardItems = 2;
const uint32_t abcclass_flash_ui_ContextMenuItem = 3;
const uint32_t abcclass_flash_ui_Keyboard = 4;
const uint32_t abcclass_flash_ui_KeyLocation = 5;
const uint32_t abcclass_flash_ui_Mouse = 6;
const uint32_t abcclass_flash_ui_MouseCursor = 7;

/* methods */
const uint32_t flash_ui_ContextMenu_builtInItems_set = 2;
const uint32_t flash_ui_ContextMenu_builtInItems_get = 3;
const uint32_t flash_ui_ContextMenu_private_cloneLinkAndClipboardProperties = 4;
const uint32_t flash_ui_ContextMenu_clipboardItems_get = 5;
const uint32_t flash_ui_ContextMenu_customItems_get = 6;
const uint32_t flash_ui_ContextMenu_clipboardMenu_set = 7;
const uint32_t flash_ui_ContextMenu_link_set = 8;
const uint32_t flash_ui_ContextMenu_clipboardMenu_get = 9;
const uint32_t flash_ui_ContextMenu_link_get = 10;
const uint32_t flash_ui_ContextMenu_clipboardItems_set = 11;
const uint32_t flash_ui_ContextMenu_private_initLinkAndClipboardProperties = 12;
const uint32_t flash_ui_ContextMenu_customItems_set = 14;
const uint32_t flash_ui_ContextMenuItem_enabled_get = 24;
const uint32_t flash_ui_ContextMenuItem_enabled_set = 25;
const uint32_t flash_ui_ContextMenuItem_separatorBefore_get = 26;
const uint32_t flash_ui_ContextMenuItem_caption_get = 27;
const uint32_t flash_ui_ContextMenuItem_separatorBefore_set = 28;
const uint32_t flash_ui_ContextMenuItem_visible_get = 29;
const uint32_t flash_ui_ContextMenuItem_visible_set = 30;
const uint32_t flash_ui_ContextMenuItem_caption_set = 31;
const uint32_t flash_ui_Keyboard_capsLock_get = 34;
const uint32_t flash_ui_Keyboard_isAccessible = 35;
const uint32_t flash_ui_Keyboard_numLock_get = 36;
const uint32_t flash_ui_Mouse_hide = 41;
const uint32_t flash_ui_Mouse_cursor_set = 42;
const uint32_t flash_ui_Mouse_show = 43;
const uint32_t flash_ui_Mouse_cursor_get = 44;

extern AvmBox ui_v2a_ob_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_ui_ContextMenuItem_enabled_set_thunk  ui_v2a_ob_thunk
#define flash_ui_ContextMenuItem_separatorBefore_set_thunk  ui_v2a_ob_thunk
#define flash_ui_ContextMenu_clipboardMenu_set_thunk  ui_v2a_ob_thunk
#define flash_ui_ContextMenuItem_visible_set_thunk  ui_v2a_ob_thunk

extern AvmBox ui_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_ui_ContextMenu_private_cloneLinkAndClipboardProperties_thunk  ui_v2a_oo_thunk
#define flash_ui_ContextMenu_customItems_set_thunk  ui_v2a_oo_thunk
#define flash_ui_ContextMenu_link_set_thunk  ui_v2a_oo_thunk
#define flash_ui_ContextMenu_builtInItems_set_thunk  ui_v2a_oo_thunk
#define flash_ui_ContextMenu_clipboardItems_set_thunk  ui_v2a_oo_thunk

extern AvmBox ui_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_ui_ContextMenu_private_initLinkAndClipboardProperties_thunk  ui_v2a_o_thunk
#define flash_ui_Mouse_hide_thunk  ui_v2a_o_thunk
#define flash_ui_Mouse_show_thunk  ui_v2a_o_thunk

extern AvmBox ui_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_ui_ContextMenu_link_get_thunk  ui_a2a_o_thunk
#define flash_ui_ContextMenu_builtInItems_get_thunk  ui_a2a_o_thunk
#define flash_ui_ContextMenu_customItems_get_thunk  ui_a2a_o_thunk
#define flash_ui_ContextMenu_clipboardItems_get_thunk  ui_a2a_o_thunk

extern AvmBox ui_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_ui_ContextMenuItem_separatorBefore_get_thunk  ui_b2a_o_thunk
#define flash_ui_ContextMenuItem_visible_get_thunk  ui_b2a_o_thunk
#define flash_ui_Keyboard_numLock_get_thunk  ui_b2a_o_thunk
#define flash_ui_ContextMenu_clipboardMenu_get_thunk  ui_b2a_o_thunk
#define flash_ui_Keyboard_isAccessible_thunk  ui_b2a_o_thunk
#define flash_ui_ContextMenuItem_enabled_get_thunk  ui_b2a_o_thunk
#define flash_ui_Keyboard_capsLock_get_thunk  ui_b2a_o_thunk

extern AvmBox ui_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_ui_Mouse_cursor_set_thunk  ui_v2a_os_thunk
#define flash_ui_ContextMenuItem_caption_set_thunk  ui_v2a_os_thunk

extern AvmBox ui_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_ui_Mouse_cursor_get_thunk  ui_s2a_o_thunk
#define flash_ui_ContextMenuItem_caption_get_thunk  ui_s2a_o_thunk

class SlotOffsetsAndAsserts;
// flash.ui::ContextMenu$
//-----------------------------------------------------------
class ContextMenuClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ContextMenuClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ContextMenuClassSlots EmptySlotsStruct_ContextMenuClass
//-----------------------------------------------------------

// flash.ui::ContextMenu
//-----------------------------------------------------------
class ContextMenuObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ContextMenuObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ContextMenuObjectSlots EmptySlotsStruct_ContextMenuObject
//-----------------------------------------------------------

// flash.ui::ContextMenuItem$
//-----------------------------------------------------------
class ContextMenuItemClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ContextMenuItemClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ContextMenuItemClassSlots EmptySlotsStruct_ContextMenuItemClass
//-----------------------------------------------------------

// flash.ui::ContextMenuItem
//-----------------------------------------------------------
class ContextMenuItemObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ContextMenuItemObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ContextMenuItemObjectSlots EmptySlotsStruct_ContextMenuItemObject
//-----------------------------------------------------------

// flash.ui::Keyboard$
//-----------------------------------------------------------
class KeyboardClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE uint32_t get_LEFT() const { return m_LEFT; }
    REALLY_INLINE uint32_t get_CONTROL() const { return m_CONTROL; }
    REALLY_INLINE uint32_t get_NUMPAD_DECIMAL() const { return m_NUMPAD_DECIMAL; }
    REALLY_INLINE uint32_t get_NUMPAD_ENTER() const { return m_NUMPAD_ENTER; }
    REALLY_INLINE uint32_t get_PAGE_UP() const { return m_PAGE_UP; }
    REALLY_INLINE uint32_t get_PAGE_DOWN() const { return m_PAGE_DOWN; }
    REALLY_INLINE uint32_t get_BACKSPACE() const { return m_BACKSPACE; }
    REALLY_INLINE uint32_t get_SHIFT() const { return m_SHIFT; }
    REALLY_INLINE uint32_t get_TAB() const { return m_TAB; }
    REALLY_INLINE uint32_t get_ESCAPE() const { return m_ESCAPE; }
    REALLY_INLINE uint32_t get_NUMPAD_ADD() const { return m_NUMPAD_ADD; }
    REALLY_INLINE uint32_t get_UP() const { return m_UP; }
    REALLY_INLINE uint32_t get_DOWN() const { return m_DOWN; }
    REALLY_INLINE uint32_t get_NUMPAD_DIVIDE() const { return m_NUMPAD_DIVIDE; }
    REALLY_INLINE uint32_t get_F3() const { return m_F3; }
    REALLY_INLINE uint32_t get_F4() const { return m_F4; }
    REALLY_INLINE uint32_t get_F5() const { return m_F5; }
    REALLY_INLINE uint32_t get_F6() const { return m_F6; }
    REALLY_INLINE uint32_t get_F7() const { return m_F7; }
    REALLY_INLINE uint32_t get_F1() const { return m_F1; }
    REALLY_INLINE uint32_t get_ENTER() const { return m_ENTER; }
    REALLY_INLINE uint32_t get_INSERT() const { return m_INSERT; }
    REALLY_INLINE uint32_t get_F9() const { return m_F9; }
    REALLY_INLINE uint32_t get_F2() const { return m_F2; }
    REALLY_INLINE uint32_t get_NUMPAD_0() const { return m_NUMPAD_0; }
    REALLY_INLINE uint32_t get_NUMPAD_1() const { return m_NUMPAD_1; }
    REALLY_INLINE uint32_t get_NUMPAD_2() const { return m_NUMPAD_2; }
    REALLY_INLINE uint32_t get_F8() const { return m_F8; }
    REALLY_INLINE uint32_t get_END() const { return m_END; }
    REALLY_INLINE uint32_t get_DELETE() const { return m_DELETE; }
    REALLY_INLINE uint32_t get_NUMPAD_6() const { return m_NUMPAD_6; }
    REALLY_INLINE uint32_t get_NUMPAD_7() const { return m_NUMPAD_7; }
    REALLY_INLINE uint32_t get_NUMPAD_8() const { return m_NUMPAD_8; }
    REALLY_INLINE uint32_t get_NUMPAD_9() const { return m_NUMPAD_9; }
    REALLY_INLINE uint32_t get_NUMPAD_3() const { return m_NUMPAD_3; }
    REALLY_INLINE uint32_t get_NUMPAD_4() const { return m_NUMPAD_4; }
    REALLY_INLINE uint32_t get_NUMPAD_5() const { return m_NUMPAD_5; }
    REALLY_INLINE uint32_t get_CAPS_LOCK() const { return m_CAPS_LOCK; }
    REALLY_INLINE uint32_t get_NUMPAD_SUBTRACT() const { return m_NUMPAD_SUBTRACT; }
    REALLY_INLINE uint32_t get_NUMPAD_MULTIPLY() const { return m_NUMPAD_MULTIPLY; }
    REALLY_INLINE uint32_t get_HOME() const { return m_HOME; }
    REALLY_INLINE uint32_t get_F10() const { return m_F10; }
    REALLY_INLINE uint32_t get_F11() const { return m_F11; }
    REALLY_INLINE uint32_t get_F12() const { return m_F12; }
    REALLY_INLINE uint32_t get_F13() const { return m_F13; }
    REALLY_INLINE uint32_t get_F14() const { return m_F14; }
    REALLY_INLINE uint32_t get_SPACE() const { return m_SPACE; }
    REALLY_INLINE uint32_t get_F15() const { return m_F15; }
    REALLY_INLINE uint32_t get_RIGHT() const { return m_RIGHT; }
private:
    uint32_t m_LEFT;
    uint32_t m_CONTROL;
    uint32_t m_NUMPAD_DECIMAL;
    uint32_t m_NUMPAD_ENTER;
    uint32_t m_PAGE_UP;
    uint32_t m_PAGE_DOWN;
    uint32_t m_BACKSPACE;
    uint32_t m_SHIFT;
    uint32_t m_TAB;
    uint32_t m_ESCAPE;
    uint32_t m_NUMPAD_ADD;
    uint32_t m_UP;
    uint32_t m_DOWN;
    uint32_t m_NUMPAD_DIVIDE;
    uint32_t m_F3;
    uint32_t m_F4;
    uint32_t m_F5;
    uint32_t m_F6;
    uint32_t m_F7;
    uint32_t m_F1;
    uint32_t m_ENTER;
    uint32_t m_INSERT;
    uint32_t m_F9;
    uint32_t m_F2;
    uint32_t m_NUMPAD_0;
    uint32_t m_NUMPAD_1;
    uint32_t m_NUMPAD_2;
    uint32_t m_F8;
    uint32_t m_END;
    uint32_t m_DELETE;
    uint32_t m_NUMPAD_6;
    uint32_t m_NUMPAD_7;
    uint32_t m_NUMPAD_8;
    uint32_t m_NUMPAD_9;
    uint32_t m_NUMPAD_3;
    uint32_t m_NUMPAD_4;
    uint32_t m_NUMPAD_5;
    uint32_t m_CAPS_LOCK;
    uint32_t m_NUMPAD_SUBTRACT;
    uint32_t m_NUMPAD_MULTIPLY;
    uint32_t m_HOME;
    uint32_t m_F10;
    uint32_t m_F11;
    uint32_t m_F12;
    uint32_t m_F13;
    uint32_t m_F14;
    uint32_t m_SPACE;
    uint32_t m_F15;
    uint32_t m_RIGHT;
};
#define DECLARE_SLOTS_KeyboardClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE uint32_t get_LEFT() const { return m_slots_KeyboardClass.get_LEFT(); } \
        REALLY_INLINE uint32_t get_CONTROL() const { return m_slots_KeyboardClass.get_CONTROL(); } \
        REALLY_INLINE uint32_t get_NUMPAD_DECIMAL() const { return m_slots_KeyboardClass.get_NUMPAD_DECIMAL(); } \
        REALLY_INLINE uint32_t get_NUMPAD_ENTER() const { return m_slots_KeyboardClass.get_NUMPAD_ENTER(); } \
        REALLY_INLINE uint32_t get_PAGE_UP() const { return m_slots_KeyboardClass.get_PAGE_UP(); } \
        REALLY_INLINE uint32_t get_PAGE_DOWN() const { return m_slots_KeyboardClass.get_PAGE_DOWN(); } \
        REALLY_INLINE uint32_t get_BACKSPACE() const { return m_slots_KeyboardClass.get_BACKSPACE(); } \
        REALLY_INLINE uint32_t get_SHIFT() const { return m_slots_KeyboardClass.get_SHIFT(); } \
        REALLY_INLINE uint32_t get_TAB() const { return m_slots_KeyboardClass.get_TAB(); } \
        REALLY_INLINE uint32_t get_ESCAPE() const { return m_slots_KeyboardClass.get_ESCAPE(); } \
        REALLY_INLINE uint32_t get_NUMPAD_ADD() const { return m_slots_KeyboardClass.get_NUMPAD_ADD(); } \
        REALLY_INLINE uint32_t get_UP() const { return m_slots_KeyboardClass.get_UP(); } \
        REALLY_INLINE uint32_t get_DOWN() const { return m_slots_KeyboardClass.get_DOWN(); } \
        REALLY_INLINE uint32_t get_NUMPAD_DIVIDE() const { return m_slots_KeyboardClass.get_NUMPAD_DIVIDE(); } \
        REALLY_INLINE uint32_t get_F3() const { return m_slots_KeyboardClass.get_F3(); } \
        REALLY_INLINE uint32_t get_F4() const { return m_slots_KeyboardClass.get_F4(); } \
        REALLY_INLINE uint32_t get_F5() const { return m_slots_KeyboardClass.get_F5(); } \
        REALLY_INLINE uint32_t get_F6() const { return m_slots_KeyboardClass.get_F6(); } \
        REALLY_INLINE uint32_t get_F7() const { return m_slots_KeyboardClass.get_F7(); } \
        REALLY_INLINE uint32_t get_F1() const { return m_slots_KeyboardClass.get_F1(); } \
        REALLY_INLINE uint32_t get_ENTER() const { return m_slots_KeyboardClass.get_ENTER(); } \
        REALLY_INLINE uint32_t get_INSERT() const { return m_slots_KeyboardClass.get_INSERT(); } \
        REALLY_INLINE uint32_t get_F9() const { return m_slots_KeyboardClass.get_F9(); } \
        REALLY_INLINE uint32_t get_F2() const { return m_slots_KeyboardClass.get_F2(); } \
        REALLY_INLINE uint32_t get_NUMPAD_0() const { return m_slots_KeyboardClass.get_NUMPAD_0(); } \
        REALLY_INLINE uint32_t get_NUMPAD_1() const { return m_slots_KeyboardClass.get_NUMPAD_1(); } \
        REALLY_INLINE uint32_t get_NUMPAD_2() const { return m_slots_KeyboardClass.get_NUMPAD_2(); } \
        REALLY_INLINE uint32_t get_F8() const { return m_slots_KeyboardClass.get_F8(); } \
        REALLY_INLINE uint32_t get_END() const { return m_slots_KeyboardClass.get_END(); } \
        REALLY_INLINE uint32_t get_DELETE() const { return m_slots_KeyboardClass.get_DELETE(); } \
        REALLY_INLINE uint32_t get_NUMPAD_6() const { return m_slots_KeyboardClass.get_NUMPAD_6(); } \
        REALLY_INLINE uint32_t get_NUMPAD_7() const { return m_slots_KeyboardClass.get_NUMPAD_7(); } \
        REALLY_INLINE uint32_t get_NUMPAD_8() const { return m_slots_KeyboardClass.get_NUMPAD_8(); } \
        REALLY_INLINE uint32_t get_NUMPAD_9() const { return m_slots_KeyboardClass.get_NUMPAD_9(); } \
        REALLY_INLINE uint32_t get_NUMPAD_3() const { return m_slots_KeyboardClass.get_NUMPAD_3(); } \
        REALLY_INLINE uint32_t get_NUMPAD_4() const { return m_slots_KeyboardClass.get_NUMPAD_4(); } \
        REALLY_INLINE uint32_t get_NUMPAD_5() const { return m_slots_KeyboardClass.get_NUMPAD_5(); } \
        REALLY_INLINE uint32_t get_CAPS_LOCK() const { return m_slots_KeyboardClass.get_CAPS_LOCK(); } \
        REALLY_INLINE uint32_t get_NUMPAD_SUBTRACT() const { return m_slots_KeyboardClass.get_NUMPAD_SUBTRACT(); } \
        REALLY_INLINE uint32_t get_NUMPAD_MULTIPLY() const { return m_slots_KeyboardClass.get_NUMPAD_MULTIPLY(); } \
        REALLY_INLINE uint32_t get_HOME() const { return m_slots_KeyboardClass.get_HOME(); } \
        REALLY_INLINE uint32_t get_F10() const { return m_slots_KeyboardClass.get_F10(); } \
        REALLY_INLINE uint32_t get_F11() const { return m_slots_KeyboardClass.get_F11(); } \
        REALLY_INLINE uint32_t get_F12() const { return m_slots_KeyboardClass.get_F12(); } \
        REALLY_INLINE uint32_t get_F13() const { return m_slots_KeyboardClass.get_F13(); } \
        REALLY_INLINE uint32_t get_F14() const { return m_slots_KeyboardClass.get_F14(); } \
        REALLY_INLINE uint32_t get_SPACE() const { return m_slots_KeyboardClass.get_SPACE(); } \
        REALLY_INLINE uint32_t get_F15() const { return m_slots_KeyboardClass.get_F15(); } \
        REALLY_INLINE uint32_t get_RIGHT() const { return m_slots_KeyboardClass.get_RIGHT(); } \
    private: \
        avmplus::NativeID::KeyboardClassSlots m_slots_KeyboardClass
//-----------------------------------------------------------

// flash.ui::Keyboard
//-----------------------------------------------------------
class KeyboardObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_KeyboardObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::KeyboardObjectSlots EmptySlotsStruct_KeyboardObject
//-----------------------------------------------------------

// flash.ui::Mouse$
//-----------------------------------------------------------
class MouseClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_MouseClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::MouseClassSlots EmptySlotsStruct_MouseClass
//-----------------------------------------------------------

// flash.ui::Mouse
//-----------------------------------------------------------
class MouseObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_MouseObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::MouseObjectSlots EmptySlotsStruct_MouseObject
//-----------------------------------------------------------

} }
