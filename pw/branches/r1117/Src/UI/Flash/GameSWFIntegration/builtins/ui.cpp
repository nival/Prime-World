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

const uint32_t ui_abc_class_count = 8;
const uint32_t ui_abc_script_count = 1;
const uint32_t ui_abc_method_count = 49;
const uint32_t ui_abc_length = 3980;

/* thunks (7 unique signatures, 27 total) */

#ifndef AVMPLUS_INDIRECT_NATIVE_THUNKS
  #error nativegen.py: --directthunks requires AVMFEATURE_INDIRECT_NATIVE_THUNKS=1
#endif


// flash_ui_ContextMenuItem_enabled_set
// flash_ui_ContextMenuItem_separatorBefore_set
// flash_ui_ContextMenu_clipboardMenu_set
// flash_ui_ContextMenuItem_visible_set
AvmBox ui_v2a_ob_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_ui_ContextMenu_private_cloneLinkAndClipboardProperties
// flash_ui_ContextMenu_customItems_set
// flash_ui_ContextMenu_link_set
// flash_ui_ContextMenu_builtInItems_set
// flash_ui_ContextMenu_clipboardItems_set
AvmBox ui_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    typedef AvmRetType_void (AvmObjectT::*FuncType)(AvmObject);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    (*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
        AvmThunkUnbox_AvmObject(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_ui_ContextMenu_private_initLinkAndClipboardProperties
// flash_ui_Mouse_hide
// flash_ui_Mouse_show
AvmBox ui_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_ui_ContextMenu_link_get
// flash_ui_ContextMenu_builtInItems_get
// flash_ui_ContextMenu_customItems_get
// flash_ui_ContextMenu_clipboardItems_get
AvmBox ui_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_ui_ContextMenuItem_separatorBefore_get
// flash_ui_ContextMenuItem_visible_get
// flash_ui_Keyboard_numLock_get
// flash_ui_ContextMenu_clipboardMenu_get
// flash_ui_Keyboard_isAccessible
// flash_ui_ContextMenuItem_enabled_get
// flash_ui_Keyboard_capsLock_get
AvmBox ui_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_ui_Mouse_cursor_set
// flash_ui_ContextMenuItem_caption_set
AvmBox ui_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_ui_Mouse_cursor_get
// flash_ui_ContextMenuItem_caption_get
AvmBox ui_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

class SlotOffsetsAndAsserts
{
private:
    static uint32_t getSlotOffset(Traits* t, int nameId);
public:
    static const uint16_t s_slotsOffsetContextMenuClass = 0;
    static const uint16_t s_slotsOffsetContextMenuObject = 0;
    static void doContextMenuClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetContextMenuItemClass = 0;
    static const uint16_t s_slotsOffsetContextMenuItemObject = 0;
    static void doContextMenuItemClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetKeyboardClass = offsetof(KeyboardClass, m_slots_KeyboardClass);
    static const uint16_t s_slotsOffsetKeyboardObject = 0;
    static void doKeyboardClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetMouseClass = 0;
    static const uint16_t s_slotsOffsetMouseObject = 0;
    static void doMouseClassAsserts(Traits* cTraits, Traits* iTraits);
};
REALLY_INLINE void SlotOffsetsAndAsserts::doContextMenuClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(ContextMenuClass::EmptySlotsStruct_ContextMenuClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(ContextMenuObject::EmptySlotsStruct_ContextMenuObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doContextMenuItemClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(ContextMenuItemClass::EmptySlotsStruct_ContextMenuItemClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(ContextMenuItemObject::EmptySlotsStruct_ContextMenuItemObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doKeyboardClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    MMGC_STATIC_ASSERT(offsetof(KeyboardClass, m_slots_KeyboardClass) == s_slotsOffsetKeyboardClass);
    MMGC_STATIC_ASSERT(offsetof(KeyboardClass, m_slots_KeyboardClass) <= 0xFFFF);
    MMGC_STATIC_ASSERT(sizeof(KeyboardClass) <= 0xFFFF);
    AvmAssert(getSlotOffset(cTraits, 77) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_ESCAPE)));
    AvmAssert(getSlotOffset(cTraits, 78) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_RIGHT)));
    AvmAssert(getSlotOffset(cTraits, 79) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_LEFT)));
    AvmAssert(getSlotOffset(cTraits, 80) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_7)));
    AvmAssert(getSlotOffset(cTraits, 81) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_TAB)));
    AvmAssert(getSlotOffset(cTraits, 82) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_ADD)));
    AvmAssert(getSlotOffset(cTraits, 83) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_SPACE)));
    AvmAssert(getSlotOffset(cTraits, 84) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_DOWN)));
    AvmAssert(getSlotOffset(cTraits, 85) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_UP)));
    AvmAssert(getSlotOffset(cTraits, 86) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F1)));
    AvmAssert(getSlotOffset(cTraits, 87) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F2)));
    AvmAssert(getSlotOffset(cTraits, 88) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F3)));
    AvmAssert(getSlotOffset(cTraits, 89) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F4)));
    AvmAssert(getSlotOffset(cTraits, 90) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F5)));
    AvmAssert(getSlotOffset(cTraits, 91) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F6)));
    AvmAssert(getSlotOffset(cTraits, 92) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F7)));
    AvmAssert(getSlotOffset(cTraits, 93) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_DELETE)));
    AvmAssert(getSlotOffset(cTraits, 94) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F9)));
    AvmAssert(getSlotOffset(cTraits, 95) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_ENTER)));
    AvmAssert(getSlotOffset(cTraits, 96) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_INSERT)));
    AvmAssert(getSlotOffset(cTraits, 97) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_DIVIDE)));
    AvmAssert(getSlotOffset(cTraits, 98) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_END)));
    AvmAssert(getSlotOffset(cTraits, 99) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_CONTROL)));
    AvmAssert(getSlotOffset(cTraits, 100) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_1)));
    AvmAssert(getSlotOffset(cTraits, 101) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_2)));
    AvmAssert(getSlotOffset(cTraits, 102) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F8)));
    AvmAssert(getSlotOffset(cTraits, 103) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_4)));
    AvmAssert(getSlotOffset(cTraits, 104) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_5)));
    AvmAssert(getSlotOffset(cTraits, 105) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_8)));
    AvmAssert(getSlotOffset(cTraits, 106) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_9)));
    AvmAssert(getSlotOffset(cTraits, 107) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_3)));
    AvmAssert(getSlotOffset(cTraits, 108) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_CAPS_LOCK)));
    AvmAssert(getSlotOffset(cTraits, 109) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_6)));
    AvmAssert(getSlotOffset(cTraits, 110) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_0)));
    AvmAssert(getSlotOffset(cTraits, 111) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_ENTER)));
    AvmAssert(getSlotOffset(cTraits, 112) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_DECIMAL)));
    AvmAssert(getSlotOffset(cTraits, 113) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_BACKSPACE)));
    AvmAssert(getSlotOffset(cTraits, 114) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_PAGE_DOWN)));
    AvmAssert(getSlotOffset(cTraits, 115) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_PAGE_UP)));
    AvmAssert(getSlotOffset(cTraits, 116) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F10)));
    AvmAssert(getSlotOffset(cTraits, 117) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_HOME)));
    AvmAssert(getSlotOffset(cTraits, 118) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F12)));
    AvmAssert(getSlotOffset(cTraits, 119) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F13)));
    AvmAssert(getSlotOffset(cTraits, 120) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F14)));
    AvmAssert(getSlotOffset(cTraits, 121) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F15)));
    AvmAssert(getSlotOffset(cTraits, 122) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_SHIFT)));
    AvmAssert(getSlotOffset(cTraits, 123) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_SUBTRACT)));
    AvmAssert(getSlotOffset(cTraits, 124) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_F11)));
    AvmAssert(getSlotOffset(cTraits, 125) == (offsetof(KeyboardClass, m_slots_KeyboardClass) + offsetof(KeyboardClassSlots, m_NUMPAD_MULTIPLY)));
    // MMGC_STATIC_ASSERT(sizeof(KeyboardObject::EmptySlotsStruct_KeyboardObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doMouseClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(MouseClass::EmptySlotsStruct_MouseClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(MouseObject::EmptySlotsStruct_MouseObject) >= 0);
}

AVMTHUNK_NATIVE_CLASS_GLUE(ContextMenuClass, ContextMenuClass, SlotOffsetsAndAsserts::doContextMenuClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(ContextMenuItemClass, ContextMenuItemClass, SlotOffsetsAndAsserts::doContextMenuItemClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(KeyboardClass, KeyboardClass, SlotOffsetsAndAsserts::doKeyboardClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(MouseClass, MouseClass, SlotOffsetsAndAsserts::doMouseClassAsserts)

AVMTHUNK_BEGIN_NATIVE_TABLES(ui)
    
    AVMTHUNK_BEGIN_NATIVE_METHODS(ui)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenu_builtInItems_set, ContextMenuObject::set_builtInItems)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenu_builtInItems_get, ContextMenuObject::get_builtInItems)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenu_private_cloneLinkAndClipboardProperties, ContextMenuObject::cloneLinkAndClipboardProperties)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenu_clipboardItems_get, ContextMenuObject::get_clipboardItems)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenu_customItems_get, ContextMenuObject::get_customItems)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenu_clipboardMenu_set, ContextMenuObject::set_clipboardMenu)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenu_link_set, ContextMenuObject::set_link)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenu_clipboardMenu_get, ContextMenuObject::get_clipboardMenu)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenu_link_get, ContextMenuObject::get_link)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenu_clipboardItems_set, ContextMenuObject::set_clipboardItems)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenu_private_initLinkAndClipboardProperties, ContextMenuObject::initLinkAndClipboardProperties)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenu_customItems_set, ContextMenuObject::set_customItems)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenuItem_enabled_get, ContextMenuItemObject::get_enabled)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenuItem_enabled_set, ContextMenuItemObject::set_enabled)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenuItem_separatorBefore_get, ContextMenuItemObject::get_separatorBefore)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenuItem_caption_get, ContextMenuItemObject::get_caption)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenuItem_separatorBefore_set, ContextMenuItemObject::set_separatorBefore)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenuItem_visible_get, ContextMenuItemObject::get_visible)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenuItem_visible_set, ContextMenuItemObject::set_visible)
        AVMTHUNK_NATIVE_METHOD(flash_ui_ContextMenuItem_caption_set, ContextMenuItemObject::set_caption)
        AVMTHUNK_NATIVE_METHOD(flash_ui_Keyboard_capsLock_get, KeyboardClass::get_capsLock)
        AVMTHUNK_NATIVE_METHOD(flash_ui_Keyboard_isAccessible, KeyboardClass::isAccessible)
        AVMTHUNK_NATIVE_METHOD(flash_ui_Keyboard_numLock_get, KeyboardClass::get_numLock)
        AVMTHUNK_NATIVE_METHOD(flash_ui_Mouse_hide, MouseClass::hide)
        AVMTHUNK_NATIVE_METHOD(flash_ui_Mouse_cursor_set, MouseClass::set_cursor)
        AVMTHUNK_NATIVE_METHOD(flash_ui_Mouse_show, MouseClass::show)
        AVMTHUNK_NATIVE_METHOD(flash_ui_Mouse_cursor_get, MouseClass::get_cursor)
    AVMTHUNK_END_NATIVE_METHODS()
    
    AVMTHUNK_BEGIN_NATIVE_CLASSES(ui)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_ui_ContextMenu, ContextMenuClass, ContextMenuClass, SlotOffsetsAndAsserts::s_slotsOffsetContextMenuClass, ContextMenuObject, SlotOffsetsAndAsserts::s_slotsOffsetContextMenuObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_ui_ContextMenuItem, ContextMenuItemClass, ContextMenuItemClass, SlotOffsetsAndAsserts::s_slotsOffsetContextMenuItemClass, ContextMenuItemObject, SlotOffsetsAndAsserts::s_slotsOffsetContextMenuItemObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_ui_Keyboard, KeyboardClass, KeyboardClass, SlotOffsetsAndAsserts::s_slotsOffsetKeyboardClass, KeyboardObject, SlotOffsetsAndAsserts::s_slotsOffsetKeyboardObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_ui_Mouse, MouseClass, MouseClass, SlotOffsetsAndAsserts::s_slotsOffsetMouseClass, MouseObject, SlotOffsetsAndAsserts::s_slotsOffsetMouseObject)
    AVMTHUNK_END_NATIVE_CLASSES()
    
AVMTHUNK_END_NATIVE_TABLES()

AVMTHUNK_DEFINE_NATIVE_INITIALIZER(ui)

/* abc */
const uint8_t ui_abc_data[3980] = {
 16,   0,  46,   0,  54,  37,  17, 110, 108,  33,  34,   8,  16,   9,  27, 107, 
 38,  40, 111, 114, 115, 116, 117, 118, 112,  13,  45, 120, 113,  96,  97,  98, 
119,  35,  46, 102, 103, 104, 105,  99, 100, 101,  20, 109, 106,  36, 121, 122, 
123, 124, 125,  32, 126,  39,   1,   3,   2,   0,   0,   0, 138,   1,  20, 102, 
108,  97, 115, 104,  46, 117, 105,  58,  67, 111, 110, 116, 101, 120, 116,  77, 
101, 110, 117,   0,  23,  67, 111, 110, 116, 101, 120, 116,  77, 101, 110, 117, 
 66, 117, 105, 108, 116,  73, 110,  73, 116, 101, 109, 115,   7, 117, 105,  46, 
 97, 115,  36,  54,   8, 102, 108,  97, 115, 104,  46, 117, 105,  12, 102, 108, 
 97, 115, 104,  46, 101, 118, 101, 110, 116, 115,   9, 102, 108,  97, 115, 104, 
 46, 110, 101, 116,  28, 102, 108,  97, 115, 104,  46, 101, 118, 101, 110, 116, 
115,  58,  69, 118, 101, 110, 116,  68, 105, 115, 112,  97, 116,  99, 104, 101, 
114,   6,  79,  98, 106, 101,  99, 116,  12,  98, 117, 105, 108, 116,  73, 110, 
 73, 116, 101, 109, 115,   5,  65, 114, 114,  97, 121,  11,  99, 117, 115, 116, 
111, 109,  73, 116, 101, 109, 115,  30, 105, 110, 105, 116,  76, 105, 110, 107, 
 65, 110, 100,  67, 108, 105, 112,  98, 111,  97, 114, 100,  80, 114, 111, 112, 
101, 114, 116, 105, 101, 115,   4, 118, 111, 105, 100,  11,  67, 111, 110, 116, 
101, 120, 116,  77, 101, 110, 117,  25,  67, 111, 110, 116, 101, 120, 116,  77, 
101, 110, 117,  67, 108, 105, 112,  98, 111,  97, 114, 100,  73, 116, 101, 109, 
115,   7,  66, 111, 111, 108, 101,  97, 110,  10,  85,  82,  76,  82, 101, 113, 
117, 101, 115, 116,   5,  99, 108, 111, 110, 101,  31,  99, 108, 111, 110, 101, 
 76, 105, 110, 107,  65, 110, 100,  67, 108, 105, 112,  98, 111,  97, 114, 100, 
 80, 114, 111, 112, 101, 114, 116, 105, 101, 115,   4, 112, 117, 115, 104,   6, 
108, 101, 110, 103, 116, 104,   4, 115,  97, 118, 101,   4, 122, 111, 111, 109, 
  7, 113, 117,  97, 108, 105, 116, 121,   4, 112, 108,  97, 121,   4, 108, 111, 
111, 112,   6, 114, 101, 119, 105, 110, 100,  14, 102, 111, 114, 119,  97, 114, 
100,  65, 110, 100,  66,  97,  99, 107,   5, 112, 114, 105, 110, 116,   4, 108, 
105, 110, 107,  14,  99, 108, 105, 112,  98, 111,  97, 114, 100,  73, 116, 101, 
109, 115,  13,  99, 108, 105, 112,  98, 111,  97, 114, 100,  77, 101, 110, 117, 
 16, 104, 105, 100, 101,  66, 117, 105, 108, 116,  73, 110,  73, 116, 101, 109, 
115,  15,  69, 118, 101, 110, 116,  68, 105, 115, 112,  97, 116,  99, 104, 101, 
114,  32, 102, 108,  97, 115, 104,  46, 117, 105,  58,  67, 111, 110, 116, 101, 
120, 116,  77, 101, 110, 117,  66, 117, 105, 108, 116,  73, 110,  73, 116, 101, 
109, 115,  34, 102, 108,  97, 115, 104,  46, 117, 105,  58,  67, 111, 110, 116, 
101, 120, 116,  77, 101, 110, 117,  67, 108, 105, 112,  98, 111,  97, 114, 100, 
 73, 116, 101, 109, 115,   3,  99, 117, 116,   4,  99, 111, 112, 121,   5, 112, 
 97, 115, 116, 101,   5,  99, 108, 101,  97, 114,   9, 115, 101, 108, 101,  99, 
116,  65, 108, 108,  24, 102, 108,  97, 115, 104,  46, 117, 105,  58,  67, 111, 
110, 116, 101, 120, 116,  77, 101, 110, 117,  73, 116, 101, 109,   7,  99,  97, 
112, 116, 105, 111, 110,  15, 115, 101, 112,  97, 114,  97, 116, 111, 114,  66, 
101, 102, 111, 114, 101,   7, 101, 110,  97,  98, 108, 101, 100,   7, 118, 105, 
115, 105,  98, 108, 101,   6,  83, 116, 114, 105, 110, 103,  15,  67, 111, 110, 
116, 101, 120, 116,  77, 101, 110, 117,  73, 116, 101, 109,  17, 102, 108,  97, 
115, 104,  46, 117, 105,  58,  75, 101, 121,  98, 111,  97, 114, 100,   6,  69, 
 83,  67,  65,  80,  69,   5,  82,  73,  71,  72,  84,   4,  76,  69,  70,  84, 
  8,  78,  85,  77,  80,  65,  68,  95,  55,   3,  84,  65,  66,  10,  78,  85, 
 77,  80,  65,  68,  95,  65,  68,  68,   5,  83,  80,  65,  67,  69,   4,  68, 
 79,  87,  78,   2,  85,  80,   2,  70,  49,   2,  70,  50,   2,  70,  51,   2, 
 70,  52,   2,  70,  53,   2,  70,  54,   2,  70,  55,   6,  68,  69,  76,  69, 
 84,  69,   2,  70,  57,   5,  69,  78,  84,  69,  82,   6,  73,  78,  83,  69, 
 82,  84,  13,  78,  85,  77,  80,  65,  68,  95,  68,  73,  86,  73,  68,  69, 
  3,  69,  78,  68,   7,  67,  79,  78,  84,  82,  79,  76,   8,  78,  85,  77, 
 80,  65,  68,  95,  49,   8,  78,  85,  77,  80,  65,  68,  95,  50,   2,  70, 
 56,   8,  78,  85,  77,  80,  65,  68,  95,  52,   8,  78,  85,  77,  80,  65, 
 68,  95,  53,   8,  78,  85,  77,  80,  65,  68,  95,  56,   8,  78,  85,  77, 
 80,  65,  68,  95,  57,   8,  78,  85,  77,  80,  65,  68,  95,  51,   9,  67, 
 65,  80,  83,  95,  76,  79,  67,  75,   8,  78,  85,  77,  80,  65,  68,  95, 
 54,   8,  78,  85,  77,  80,  65,  68,  95,  48,  12,  78,  85,  77,  80,  65, 
 68,  95,  69,  78,  84,  69,  82,  14,  78,  85,  77,  80,  65,  68,  95,  68, 
 69,  67,  73,  77,  65,  76,   9,  66,  65,  67,  75,  83,  80,  65,  67,  69, 
  9,  80,  65,  71,  69,  95,  68,  79,  87,  78,   7,  80,  65,  71,  69,  95, 
 85,  80,   3,  70,  49,  48,   4,  72,  79,  77,  69,   3,  70,  49,  50,   3, 
 70,  49,  51,   3,  70,  49,  52,   3,  70,  49,  53,   5,  83,  72,  73,  70, 
 84,  15,  78,  85,  77,  80,  65,  68,  95,  83,  85,  66,  84,  82,  65,  67, 
 84,   3,  70,  49,  49,  15,  78,  85,  77,  80,  65,  68,  95,  77,  85,  76, 
 84,  73,  80,  76,  89,   4, 117, 105, 110, 116,  12, 105, 115,  65,  99,  99, 
101, 115, 115, 105,  98, 108, 101,   8,  99,  97, 112, 115,  76, 111,  99, 107, 
  7, 110, 117, 109,  76, 111,  99, 107,   8,  75, 101, 121,  98, 111,  97, 114, 
100,  20, 102, 108,  97, 115, 104,  46, 117, 105,  58,  75, 101, 121,  76, 111, 
 99,  97, 116, 105, 111, 110,   7,  78,  85,  77,  95,  80,  65,  68,   8,  83, 
 84,  65,  78,  68,  65,  82,  68,  11,  75, 101, 121,  76, 111,  99,  97, 116, 
105, 111, 110,  14, 102, 108,  97, 115, 104,  46, 117, 105,  58,  77, 111, 117, 
115, 101,   4, 104, 105, 100, 101,   6,  99, 117, 114, 115, 111, 114,   4, 115, 
104, 111, 119,   5,  77, 111, 117, 115, 101,  20, 102, 108,  97, 115, 104,  46, 
117, 105,  58,  77, 111, 117, 115, 101,  67, 117, 114, 115, 111, 114,   6,  66, 
 85,  84,  84,  79,  78,   6,  98, 117, 116, 116, 111, 110,   4,  72,  65,  78, 
 68,   4, 104,  97, 110, 100,   5,  73,  66,  69,  65,  77,   5, 105,  98, 101, 
 97, 109,   5,  65,  82,  82,  79,  87,   5,  97, 114, 114, 111, 119,   4,  65, 
 85,  84,  79,   4,  97, 117, 116, 111,  11,  77, 111, 117, 115, 101,  67, 117, 
114, 115, 111, 114,   6, 110,  97, 116, 105, 118, 101,   3,  99, 108, 115,  13, 
 75, 101, 121,  98, 111,  97, 114, 100,  67, 108,  97, 115, 115,   8, 105, 110, 
115, 116,  97, 110,  99, 101,  14,  75, 101, 121,  98, 111,  97, 114, 100,  79, 
 98, 106, 101,  99, 116,   7, 109, 101, 116, 104, 111, 100, 115,  10,  77, 111, 
117, 115, 101,  67, 108,  97, 115, 115,  11,  77, 111, 117, 115, 101,  79,  98, 
106, 101,  99, 116,  16,  67, 111, 110, 116, 101, 120, 116,  77, 101, 110, 117, 
 67, 108,  97, 115, 115,  17,  67, 111, 110, 116, 101, 120, 116,  77, 101, 110, 
117,  79,  98, 106, 101,  99, 116,  20,  67, 111, 110, 116, 101, 120, 116,  77, 
101, 110, 117,  73, 116, 101, 109,  67, 108,  97, 115, 115,  21,  67, 111, 110, 
116, 101, 120, 116,  77, 101, 110, 117,  73, 116, 101, 109,  79,  98, 106, 101, 
 99, 116,  29,   5,   1,   5,   4,  22,   2,  22,   5,  23,   5,  22,   6,  22, 
  7,  24,   1,  26,   1,  26,   8,  26,   9,   5,  36,  24,  36,  26,  36,   5, 
 37,  24,  37,  26,  37,   5,  43,  24,  43,  26,  43,   5,  50,  24,  50,   5, 
105,  24, 105,   5, 109,  24, 109,   5, 114,  24, 114,   8,  11,   1,   2,   3, 
  4,   5,   6,   7,   8,   9,  10,  11,   8,   2,   3,   4,   5,  11,  12,  13, 
 14,   8,   2,   3,   4,   5,  11,  15,  16,  17,  10,   2,   3,   4,   5,   6, 
 10,  11,  18,  19,  20,   6,   2,   3,   4,   5,   6,   7,   4,   2,   3,   4, 
  5,   5,   2,   3,   4,   5,   6, 147,   1,   9,   3,   1,   9,  10,   1,   9, 
 11,   1,   9,  12,   1,   9,  13,   1,   7,   3,  14,   7,   4,   3,   7,   4, 
 15,   7,   4,  16,   7,   3,  11,   7,   3,  17,   7,   7,  18,   9,  15,   1, 
  9,  19,   1,   9,  20,   1,  27,   1,   9,  21,   1,   9,  22,   1,   9,  23, 
  1,   9,  24,   1,   9,  25,   1,   9,  26,   1,   9,  27,   1,   9,  28,   1, 
  9,  29,   1,   9,  30,   1,   7,   3,  31,   7,   3,  19,   7,   1,  20,   7, 
  3,  32,   7,   3,  12,   7,   3,  33,   7,   3,  10,   7,   1,  13,   7,   3, 
 34,   7,   6,  35,   9,   3,   2,   9,  23,   2,   9,  24,   2,   9,  25,   2, 
  9,  26,   2,   9,  27,   2,   9,  28,   2,   9,  29,   2,   9,  30,   2,   7, 
  3,  27,   7,   3,  30,   7,   3,  24,   7,   3,  26,   7,   3,  29,   7,   3, 
 28,   7,   3,  23,   7,   3,  25,   7,   3,   9,   9,  16,   3,   9,  38,   3, 
  9,  39,   3,   9,  40,   3,   9,  41,   3,   9,  42,   3,   7,   3,  38,   7, 
  3,  40,   7,   3,  39,   7,   3,  42,   7,   3,  41,   9,  44,   4,   9,  45, 
  4,   9,  46,   4,   9,  47,   4,   7,   3,  48,   9,  49,   4,   7,   4,  49, 
  7,   3,  46,   7,   3,  45,   7,   3,  44,   7,   3,  47,   7,   3,  51,   7, 
  3,  52,   7,   3,  53,   7,   3,  54,   7,   3,  55,   7,   3,  56,   7,   3, 
 57,   7,   3,  58,   7,   3,  59,   7,   3,  60,   7,   3,  61,   7,   3,  62, 
  7,   3,  63,   7,   3,  64,   7,   3,  65,   7,   3,  66,   7,   3,  67,   7, 
  3,  68,   7,   3,  69,   7,   3,  70,   7,   3,  71,   7,   3,  72,   7,   3, 
 73,   7,   3,  74,   7,   3,  75,   7,   3,  76,   7,   3,  77,   7,   3,  78, 
  7,   3,  79,   7,   3,  80,   7,   3,  81,   7,   3,  82,   7,   3,  83,   7, 
  3,  84,   7,   3,  85,   7,   3,  86,   7,   3,  87,   7,   3,  88,   7,   3, 
 89,   7,   3,  90,   7,   3,  91,   7,   3,  92,   7,   3,  93,   7,   3,  94, 
  7,   3,  95,   7,   3,  96,   7,   3,  97,   7,   3,  98,   7,   3,  99,   7, 
  3, 100,   7,   3, 101,   7,   3, 102,   7,   3, 103,   7,   4, 104,   7,   3, 
106,   7,   3, 107,   7,   4, 108,   7,   3, 110,   7,   3, 111,   7,   3, 112, 
  7,   4, 113,   7,   3, 115,   7,   3, 117,   7,   3, 119,   7,   3, 121,   7, 
  3, 123,   7,   4, 125,   9,  35,   5,   9,   9,   6,   9,  35,   7,  49,   0, 
  0,   2,   0,   0,   0,   2,   0,   1,   6,   7,   2,  32,   0,   7,   2,  32, 
  1,   6,   8,   2,  32,   0,   9,   2,  32,   0,  10,   2,  32,   1,   6,  11, 
  2,  32,   1,   6,  12,   2,  32,   0,  11,   2,  32,   0,  12,   2,  32,   1, 
  6,   9,   2,  32,   0,   6,   2,  32,   0,   8,   2,   0,   1,   6,  10,   2, 
 32,   0,   6,   2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   7,   2, 
  0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   9,   2,   0,   0,   0,   2, 
  0,   4,   0,  70,  11,  11,  11,   2,   8,   3,  10,  10,  11,  11,  11,  11, 
  0,  11,   2,  32,   1,   6,  11,   2,  32,   0,  11,   2,  32,   0,  70,   2, 
 32,   1,   6,  11,   2,  32,   0,  11,   2,  32,   1,   6,  11,   2,  32,   1, 
  6,  70,   2,  32,   0,  72,   2,   0,   0,   0,   2,   0,   0,  11,   2,  32, 
  0,  11,   2,  32,   0,  11,   2,  32,   0,   0,   2,   0,   0,   0,   2,   0, 
  0,   0,   2,   0,   0,   0,   2,   0,   0,   6,   2,  32,   1,   6,  70,   2, 
 32,   0,   6,   2,  32,   0,  70,   2,  32,   0,   0,   2,   0,   0,   0,   2, 
  0,   0,   0,   2,   0,   0,   0,   2,   0,   4, 126,   3, 127, 129,   1, 131, 
  1, 128,   1, 130,   1, 124, 126,   3, 127, 129,   1, 131,   1, 132,   1, 133, 
  1, 124, 126,   3, 127, 129,   1, 131,   1, 134,   1, 135,   1, 124, 126,   3, 
127, 129,   1, 131,   1, 136,   1, 137,   1, 124,   8,   8,  36,  11,   8,   0, 
  1,  14,  27,   2,   0,  10,  28,   1,   0,  13,  29,   1,   0,   4,  30,   2, 
  0,   5,  31,   2,   0,   6,  32,   3,   0,   7,  27,   3,   0,   8,  32,   2, 
  0,   9,  33,   3,   0,   2,  30,   3,   0,  11,  34,   1,   0,  12,  33,   2, 
  0,   3,  31,   3,   0,  14,  35,   1,   0,  15,   7,  54,  11,  13,   0,  17, 
  9,  46,   0,   0,  11,  11,  11,  28,   1,   0,  18,  47,   0,   0,  11,  11, 
 11,  48,   0,   0,  11,  11,  11,  49,   0,   0,  11,  11,  11,  50,   0,   0, 
 11,  11,  11,  51,   0,   0,  11,  11,  11,  52,   0,   0,  11,  11,  11,  53, 
  0,   0,  11,  11,  11,   9,  54,  11,  16,   0,  20,   6,  61,   0,   0,  11, 
 10,  10,  62,   0,   0,  11,  10,  10,  63,   0,   0,  11,  10,  10,  64,   0, 
  0,  11,  11,  11,  65,   0,   0,  11,  10,  10,  28,   1,   0,  21,  72,  36, 
 11,  19,   0,  23,   9,  73,   2,   0,  24,  73,   3,   0,  25,  74,   2,   0, 
 26,  75,   2,   0,  27,  74,   3,   0,  28,  76,   2,   0,  29,  76,   3,   0, 
 30,  75,   3,   0,  31,  28,   1,   0,  32, 130,   1,  54,  11,  22,   0,  37, 
  0, 133,   1,  54,  11,  24,   0,  39,   0, 137,   1,  54,  11,  26,   0,  45, 
  0, 143,   1,  54,  11,  28,   0,  47,   0,   0,   0,  16,   0,  19,   0,  22, 
  0,  33,  52,  79,   6,   3, 126,   1,   3,  99,   6,  23, 126,   2,   3, 112, 
  6,  36, 126,   3,   3, 111,   6,  35, 126,   4,   3, 115,   6,  39, 126,   5, 
  3, 114,   6,  38, 126,   6,   3, 113,   6,  37, 126,   7,   3, 122,   6,  46, 
126,   8,   3,  81,   6,   5, 126,   9,   3,  77,   6,   1, 126,  10,   3, 127, 
 17,   4,  35,  82,   6,   6, 126,  11,   3,  85,   6,   9, 126,  12,   3,  84, 
  6,   8, 126,  13,   3,  97,   6,  21, 126,  14,   3, 128,   1,  18,   3,  34, 
 88,   6,  12, 126,  15,   3,  89,   6,  13, 126,  16,   3,  90,   6,  14, 126, 
 17,   3,  91,   6,  15, 126,  18,   3,  92,   6,  16, 126,  19,   3,  86,   6, 
 10, 126,  20,   3,  95,   6,  19, 126,  21,   3,  96,   6,  20, 126,  22,   3, 
 94,   6,  18, 126,  23,   3,  87,   6,  11, 126,  24,   3, 110,   6,  34, 126, 
 25,   3, 100,   6,  24, 126,  26,   3, 101,   6,  25, 126,  27,   3, 102,   6, 
 26, 126,  28,   3,  98,   6,  22, 126,  29,   3,  93,   6,  17, 126,  30,   3, 
109,   6,  33, 126,  31,   3,  80,   6,   4, 126,  32,   3, 105,   6,  29, 126, 
 33,   3, 106,   6,  30, 126,  34,   3, 107,   6,  31, 126,  35,   3, 103,   6, 
 27, 126,  36,   3, 104,   6,  28, 126,  37,   3, 108,   6,  32, 126,  38,   3, 
123,   6,  47, 126,  39,   3, 125,   6,  49, 126,  40,   3, 129,   1,  18,   5, 
 36, 117,   6,  41, 126,  41,   3, 116,   6,  40, 126,  42,   3, 124,   6,  48, 
126,  43,   3, 118,   6,  42, 126,  44,   3, 119,   6,  43, 126,  45,   3, 120, 
  6,  44, 126,  46,   3,  83,   6,   7, 126,  47,   3, 121,   6,  45, 126,  48, 
  3,  78,   6,   2, 126,  49,   3,  38,   4,  79,   6,   2, 126,  50,   3, 131, 
  1,   6,   1, 126,  51,   3,  78,   6,   3, 126,  52,   3, 132,   1,   6,   4, 
126,  53,   3,  40,   4, 134,   1,  17,   3,  41, 135,   1,  19,   4,  42, 136, 
  1,  17,   5,  43, 135,   1,  18,   6,  44,  46,   5, 141,   1,   6,   4,  70, 
122,   1, 138,   1,   6,   1,  70, 116,   1, 142,   1,   6,   5,  70, 124,   1, 
140,   1,   6,   3,  70, 120,   1, 139,   1,   6,   2,  70, 118,   1,   1,  48, 
  8, 130,   1,  68,   5,   4,   1,   0, 133,   1,   4,   6,   5, 143,   1,   4, 
  8,   7, 137,   1,  68,   7,   6,   1,   1,   8,  68,   1,   0,   1,   2,  72, 
 68,   4,   3,   1,   3,   7,   4,   2,   1,   9,   4,   3,   2,  22,   0,   1, 
  1,   4,   5,   3, 208,  48,  71,   0,   0,   1,   2,   1,   5,   6,  27, 208, 
 48, 208,  73,   0, 208,  93,   1,  74,   1,   0, 104,   2, 208,  93,   3,  74, 
  3,   0, 104,   4, 208,  70,   5,   0,  41,  71,   0,   0,  13,   3,   3,   5, 
  6,  67, 208,  48,  93,  13,  74,  13,   0, 130, 213, 209, 208, 102,   2,  70, 
 14,   0,  97,   2, 208, 209,  70,  15,   1,  41,  36,   0, 115, 214,  16,  23, 
  0,   0,   9, 209, 102,   4, 208, 102,   4, 210, 102,  16,  70,  14,   0,  70, 
 17,   1,  41, 210,  36,   1, 160, 115, 214, 210, 208, 102,   4, 102,  18,  21, 
223, 255, 255, 209,  72,   0,   0,  15,   2,   1,   5,   6,  51, 208,  48, 208, 
102,   2,  39,  97,  19, 208, 102,   2,  39,  97,  20, 208, 102,   2,  39,  97, 
 21, 208, 102,   2,  39,  97,  22, 208, 102,   2,  39,  97,  23, 208, 102,   2, 
 39,  97,  24, 208, 102,   2,  39,  97,  25, 208, 102,   2,  39,  97,  26,  71, 
  0,   0,  16,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,  17,   1,   1, 
  4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  18,   2,   2,   4,   5, 
 59, 208,  48,  93,  37,  74,  37,   0, 130, 213, 209, 208, 102,  38,  97,  38, 
209, 208, 102,  39,  97,  39, 209, 208, 102,  40,  97,  40, 209, 208, 102,  41, 
 97,  41, 209, 208, 102,  42,  97,  42, 209, 208, 102,  43,  97,  43, 209, 208, 
102,  44,  97,  44, 209, 208, 102,  45,  97,  45, 209,  72,   0,   0,  19,   1, 
  1,   3,   4,   3, 208,  48,  71,   0,   0,  20,   1,   1,   4,   5,   6, 208, 
 48, 208,  73,   0,  71,   0,   0,  21,   2,   2,   4,   5,  41, 208,  48,  93, 
 55,  74,  55,   0, 130, 213, 209, 208, 102,  56,  97,  56, 209, 208, 102,  57, 
 97,  57, 209, 208, 102,  58,  97,  58, 209, 208, 102,  59,  97,  59, 209, 208, 
102,  60,  97,  60, 209,  72,   0,   0,  22,   1,   1,   4,   5,   3, 208,  48, 
 71,   0,   0,  23,   2,   5,   5,   6,  23, 208,  48, 208,  73,   0, 208, 209, 
104,  66, 208, 210, 104,  67, 208, 211, 104,  68, 208,  98,   4, 104,  69,  71, 
  0,   0,  32,   5,   2,   5,   6,  23, 208,  48,  93,  71, 208, 102,  66, 208, 
102,  67, 208, 102,  68, 208, 102,  69,  74,  71,   4, 130, 213, 209,  72,   0, 
  0,  33,   2,   1,   3,   4, 169,   2, 208,  48,  94,  77,  36,  27, 104,  77, 
 94,  78,  36,  39, 104,  78,  94,  79,  36,  37, 104,  79,  94,  80,  36, 103, 
104,  80,  94,  81,  36,   9, 104,  81,  94,  82,  36, 107, 104,  82,  94,  83, 
 36,  32, 104,  83,  94,  84,  36,  40, 104,  84,  94,  85,  36,  38, 104,  85, 
 94,  86,  36, 112, 104,  86,  94,  87,  36, 113, 104,  87,  94,  88,  36, 114, 
104,  88,  94,  89,  36, 115, 104,  89,  94,  90,  36, 116, 104,  90,  94,  91, 
 36, 117, 104,  91,  94,  92,  36, 118, 104,  92,  94,  93,  36,  46, 104,  93, 
 94,  94,  36, 120, 104,  94,  94,  95,  36,  13, 104,  95,  94,  96,  36,  45, 
104,  96,  94,  97,  36, 111, 104,  97,  94,  98,  36,  35, 104,  98,  94,  99, 
 36,  17, 104,  99,  94, 100,  36,  97, 104, 100,  94, 101,  36,  98, 104, 101, 
 94, 102,  36, 119, 104, 102,  94, 103,  36, 100, 104, 103,  94, 104,  36, 101, 
104, 104,  94, 105,  36, 104, 104, 105,  94, 106,  36, 105, 104, 106,  94, 107, 
 36,  99, 104, 107,  94, 108,  36,  20, 104, 108,  94, 109,  36, 102, 104, 109, 
 94, 110,  36,  96, 104, 110,  94, 111,  36, 108, 104, 111,  94, 112,  36, 110, 
104, 112,  94, 113,  36,   8, 104, 113,  94, 114,  36,  34, 104, 114,  94, 115, 
 36,  33, 104, 115,  94, 116,  36, 121, 104, 116,  94, 117,  36,  36, 104, 117, 
 94, 118,  36, 123, 104, 118,  94, 119,  36, 124, 104, 119,  94, 120,  36, 125, 
104, 120,  94, 121,  36, 126, 104, 121,  94, 122,  36,  16, 104, 122,  94, 123, 
 36, 109, 104, 123,  94, 124,  36, 122, 104, 124,  94, 125,  36, 106, 104, 125, 
 71,   0,   0,  37,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0, 
  0,  38,   2,   1,   3,   4,  31, 208,  48,  94, 131,   1,  36,   3, 104, 131, 
  1,  94,  79,  36,   1, 104,  79,  94,  78,  36,   2, 104,  78,  94, 132,   1, 
 36,   0, 104, 132,   1,  71,   0,   0,  39,   1,   1,   4,   5,   6, 208,  48, 
208,  73,   0,  71,   0,   0,  40,   1,   1,   3,   4,   3, 208,  48,  71,   0, 
  0,  45,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  46, 
  2,   1,   3,   4,  43, 208,  48,  94, 138,   1,  44, 116, 104, 138,   1,  94, 
139,   1,  44, 118, 104, 139,   1,  94, 140,   1,  44, 120, 104, 140,   1,  94, 
141,   1,  44, 122, 104, 141,   1,  94, 142,   1,  44, 124, 104, 142,   1,  71, 
  0,   0,  47,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0, 
 48,   2,   1,   1,   4, 163,   1, 208,  48, 101,   0,  93,  54, 102,  54,  48, 
 93,  36, 102,  36,  48,  93, 144,   1, 102, 144,   1,  88,   0,  29,  29, 104, 
  8, 101,   0,  93,  54, 102,  54,  48,  93, 145,   1, 102, 145,   1,  88,   1, 
 29, 104,   7, 101,   0,  93,  54, 102,  54,  48,  93, 145,   1, 102, 145,   1, 
 88,   2,  29, 104,   9, 101,   0,  93,  54, 102,  54,  48,  93,  36, 102,  36, 
 48,  93, 146,   1, 102, 146,   1,  88,   3,  29,  29, 104,  72, 101,   0,  93, 
 54, 102,  54,  48,  93, 145,   1, 102, 145,   1,  88,   4,  29, 104, 130,   1, 
101,   0,  93,  54, 102,  54,  48,  93, 145,   1, 102, 145,   1,  88,   5,  29, 
104, 133,   1, 101,   0,  93,  54, 102,  54,  48,  93, 145,   1, 102, 145,   1, 
 88,   6,  29, 104, 137,   1, 101,   0,  93,  54, 102,  54,  48,  93, 145,   1, 
102, 145,   1,  88,   7,  29, 104, 143,   1,  71,   0,   0};

} }
