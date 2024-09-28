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

const uint32_t sound_abc_class_count = 6;
const uint32_t sound_abc_script_count = 1;
const uint32_t sound_abc_method_count = 43;
const uint32_t sound_abc_length = 2138;

/* thunks (12 unique signatures, 26 total) */

#ifndef AVMPLUS_INDIRECT_NATIVE_THUNKS
  #error nativegen.py: --directthunks requires AVMFEATURE_INDIRECT_NATIVE_THUNKS=1
#endif


// flash_media_Sound_play
AvmBox sound_a2a_odio_opti0_opti0_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_double
        , argoff3 = argoff2 + AvmThunkArgSize_int32_t
    };
    (void)env;
    SoundObject* const obj = (SoundObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    SoundChannelObject* const ret = obj->play(
        (argc < 1 ? AvmThunkCoerce_int32_t_double(0) : AvmThunkUnbox_double(argv[argoff1]))
        , (argc < 2 ? 0 : AvmThunkUnbox_int32_t(argv[argoff2]))
        , (SoundTransformObject*)(argc < 3 ? AvmThunkCoerce_AvmBox_AvmObject(kAvmThunkNull) : (SoundTransformObject*)AvmThunkUnbox_AvmObject(argv[argoff3]))
    );
    return (AvmBox) ret;
}

// flash_media_SoundTransform_rightToLeft_set
// flash_media_SoundTransform_volume_set
// flash_media_SoundTransform_leftToLeft_set
// flash_media_SoundTransform_leftToRight_set
// flash_media_SoundTransform_rightToRight_set
AvmBox sound_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_media_SoundTransform_leftToLeft_get
// flash_media_SoundChannel_leftPeak_get
// flash_media_SoundChannel_position_get
// flash_media_SoundChannel_rightPeak_get
// flash_media_SoundTransform_rightToLeft_get
// flash_media_SoundTransform_rightToRight_get
// flash_media_SoundTransform_volume_get
// flash_media_SoundTransform_leftToRight_get
// flash_media_Sound_length_get
double sound_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_media_SoundChannel_soundTransform_set
AvmBox sound_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    SoundChannelObject* const obj = (SoundChannelObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->set_soundTransform(
        (SoundTransformObject*)AvmThunkUnbox_AvmObject(argv[argoff1])
    );
    return kAvmThunkUndefined;
}

// flash_media_Sound_extract
double sound_d2d_oodd_opti_1_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmObject
        , argoff3 = argoff2 + AvmThunkArgSize_double
    };
    (void)env;
    SoundObject* const obj = (SoundObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    double const ret = obj->extract(
        (ByteArrayObject*)AvmThunkUnbox_AvmObject(argv[argoff1])
        , AvmThunkUnbox_double(argv[argoff2])
        , (argc < 3 ? AvmThunkCoerce_int32_t_double(-1) : AvmThunkUnbox_double(argv[argoff3]))
    );
    return ret;
}

// flash_media_Sound_bytesLoaded_get
AvmBox sound_u2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    SoundObject* const obj = (SoundObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    uint32_t const ret = obj->get_bytesLoaded();
    return (AvmBox) ret;
}

// flash_media_SoundChannel_stop
// flash_media_Sound_close
AvmBox sound_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_media_Sound_id3_get
// flash_media_SoundChannel_soundTransform_get
AvmBox sound_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_media_Sound_isBuffering_get
AvmBox sound_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    SoundObject* const obj = (SoundObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmBool32 const ret = obj->get_isBuffering();
    return (AvmBox) ret;
}

// flash_media_Sound_private__load
AvmBox sound_v2a_oobd_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmObject
        , argoff3 = argoff2 + AvmThunkArgSize_AvmBool32
    };
    (void)argc;
    (void)env;
    SoundObject* const obj = (SoundObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->_load(
        (URLRequestObject*)AvmThunkUnbox_AvmObject(argv[argoff1])
        , AvmThunkUnbox_AvmBool32(argv[argoff2])
        , AvmThunkUnbox_double(argv[argoff3])
    );
    return kAvmThunkUndefined;
}

// flash_media_Sound_url_get
AvmBox sound_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    SoundObject* const obj = (SoundObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmString const ret = obj->get_url();
    return (AvmBox) ret;
}

// flash_media_Sound_bytesTotal_get
AvmBox sound_i2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    SoundObject* const obj = (SoundObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    int32_t const ret = obj->get_bytesTotal();
    return (AvmBox) ret;
}

class SlotOffsetsAndAsserts
{
private:
    static uint32_t getSlotOffset(Traits* t, int nameId);
public:
    static const uint16_t s_slotsOffsetSoundTransformClass = 0;
    static const uint16_t s_slotsOffsetSoundTransformObject = 0;
    static void doSoundTransformClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetSoundChannelClass = 0;
    static const uint16_t s_slotsOffsetSoundChannelObject = 0;
    static void doSoundChannelClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetSoundClass = 0;
    static const uint16_t s_slotsOffsetSoundObject = 0;
    static void doSoundClassAsserts(Traits* cTraits, Traits* iTraits);
};
REALLY_INLINE void SlotOffsetsAndAsserts::doSoundTransformClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(SoundTransformClass::EmptySlotsStruct_SoundTransformClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(SoundTransformObject::EmptySlotsStruct_SoundTransformObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doSoundChannelClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(SoundChannelClass::EmptySlotsStruct_SoundChannelClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(SoundChannelObject::EmptySlotsStruct_SoundChannelObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doSoundClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(SoundClass::EmptySlotsStruct_SoundClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(SoundObject::EmptySlotsStruct_SoundObject) >= 0);
}

AVMTHUNK_NATIVE_CLASS_GLUE(SoundTransformClass, SoundTransformClass, SlotOffsetsAndAsserts::doSoundTransformClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(SoundChannelClass, SoundChannelClass, SlotOffsetsAndAsserts::doSoundChannelClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(SoundClass, SoundClass, SlotOffsetsAndAsserts::doSoundClassAsserts)

AVMTHUNK_BEGIN_NATIVE_TABLES(sound)
    
    AVMTHUNK_BEGIN_NATIVE_METHODS(sound)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundTransform_rightToRight_get, SoundTransformObject::get_rightToRight)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundTransform_volume_get, SoundTransformObject::get_volume)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundTransform_leftToLeft_get, SoundTransformObject::get_leftToLeft)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundTransform_rightToRight_set, SoundTransformObject::set_rightToRight)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundTransform_leftToLeft_set, SoundTransformObject::set_leftToLeft)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundTransform_leftToRight_set, SoundTransformObject::set_leftToRight)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundTransform_leftToRight_get, SoundTransformObject::get_leftToRight)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundTransform_volume_set, SoundTransformObject::set_volume)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundTransform_rightToLeft_set, SoundTransformObject::set_rightToLeft)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundTransform_rightToLeft_get, SoundTransformObject::get_rightToLeft)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundChannel_stop, SoundChannelObject::stop)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundChannel_leftPeak_get, SoundChannelObject::get_leftPeak)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundChannel_position_get, SoundChannelObject::get_position)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundChannel_soundTransform_set, SoundChannelObject::set_soundTransform)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundChannel_rightPeak_get, SoundChannelObject::get_rightPeak)
        AVMTHUNK_NATIVE_METHOD(flash_media_SoundChannel_soundTransform_get, SoundChannelObject::get_soundTransform)
        AVMTHUNK_NATIVE_METHOD(flash_media_Sound_extract, SoundObject::extract)
        AVMTHUNK_NATIVE_METHOD(flash_media_Sound_private__load, SoundObject::_load)
        AVMTHUNK_NATIVE_METHOD(flash_media_Sound_close, SoundObject::close)
        AVMTHUNK_NATIVE_METHOD(flash_media_Sound_url_get, SoundObject::get_url)
        AVMTHUNK_NATIVE_METHOD(flash_media_Sound_bytesLoaded_get, SoundObject::get_bytesLoaded)
        AVMTHUNK_NATIVE_METHOD(flash_media_Sound_play, SoundObject::play)
        AVMTHUNK_NATIVE_METHOD(flash_media_Sound_length_get, SoundObject::get_length)
        AVMTHUNK_NATIVE_METHOD(flash_media_Sound_id3_get, SoundObject::get_id3)
        AVMTHUNK_NATIVE_METHOD(flash_media_Sound_bytesTotal_get, SoundObject::get_bytesTotal)
        AVMTHUNK_NATIVE_METHOD(flash_media_Sound_isBuffering_get, SoundObject::get_isBuffering)
    AVMTHUNK_END_NATIVE_METHODS()
    
    AVMTHUNK_BEGIN_NATIVE_CLASSES(sound)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_media_SoundTransform, SoundTransformClass, SoundTransformClass, SlotOffsetsAndAsserts::s_slotsOffsetSoundTransformClass, SoundTransformObject, SlotOffsetsAndAsserts::s_slotsOffsetSoundTransformObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_media_SoundChannel, SoundChannelClass, SoundChannelClass, SlotOffsetsAndAsserts::s_slotsOffsetSoundChannelClass, SoundChannelObject, SlotOffsetsAndAsserts::s_slotsOffsetSoundChannelObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_media_Sound, SoundClass, SoundClass, SlotOffsetsAndAsserts::s_slotsOffsetSoundClass, SoundObject, SlotOffsetsAndAsserts::s_slotsOffsetSoundObject)
    AVMTHUNK_END_NATIVE_CLASSES()
    
AVMTHUNK_END_NATIVE_TABLES()

AVMTHUNK_DEFINE_NATIVE_INITIALIZER(sound)

/* abc */
const uint8_t sound_abc_data[2138] = {
 16,   0,  46,   0,   5,   1,   0, 232,   7, 255, 255, 255, 255,  15,   0,   0, 
 79,  26, 102, 108,  97, 115, 104,  46, 109, 101, 100, 105,  97,  58,  83, 111, 
117, 110, 100,  84, 114,  97, 110, 115, 102, 111, 114, 109,   0,   6, 118, 111, 
108, 117, 109, 101,  10, 115, 111, 117, 110, 100,  46,  97, 115,  36,  54,  11, 
102, 108,  97, 115, 104,  46, 109, 101, 100, 105,  97,   6,  79,  98, 106, 101, 
 99, 116,   3, 112,  97, 110,   6,  78, 117, 109,  98, 101, 114,   4,  77,  97, 
116, 104,   4, 115, 113, 114, 116,  10, 108, 101, 102, 116,  84, 111,  76, 101, 
102, 116,  11, 108, 101, 102, 116,  84, 111,  82, 105, 103, 104, 116,  12, 114, 
105, 103, 104, 116,  84, 111,  82, 105, 103, 104, 116,  11, 114, 105, 103, 104, 
116,  84, 111,  76, 101, 102, 116,   4, 118, 111, 105, 100,  14,  83, 111, 117, 
110, 100,  84, 114,  97, 110, 115, 102, 111, 114, 109,  19, 102, 108,  97, 115, 
104,  46, 109, 101, 100, 105,  97,  58,  73,  68,  51,  73, 110, 102, 111,   8, 
115, 111, 110, 103,  78,  97, 109, 101,   6,  83, 116, 114, 105, 110, 103,   5, 
103, 101, 110, 114, 101,   6,  97, 114, 116, 105, 115, 116,   5, 116, 114,  97, 
 99, 107,   5,  97, 108,  98, 117, 109,   4, 121, 101,  97, 114,   7,  99, 111, 
109, 109, 101, 110, 116,   7,  73,  68,  51,  73, 110, 102, 111,  24, 102, 108, 
 97, 115, 104,  46, 109, 101, 100, 105,  97,  58,  83, 111, 117, 110, 100,  67, 
104,  97, 110, 110, 101, 108,   4, 115, 116, 111, 112,   8, 108, 101, 102, 116, 
 80, 101,  97, 107,   8, 112, 111, 115, 105, 116, 105, 111, 110,  14, 115, 111, 
117, 110, 100,  84, 114,  97, 110, 115, 102, 111, 114, 109,   9, 114, 105, 103, 
104, 116,  80, 101,  97, 107,  12,  83, 111, 117, 110, 100,  67, 104,  97, 110, 
110, 101, 108,  12, 102, 108,  97, 115, 104,  46, 101, 118, 101, 110, 116, 115, 
 15,  69, 118, 101, 110, 116,  68, 105, 115, 112,  97, 116,  99, 104, 101, 114, 
 22, 102, 108,  97, 115, 104,  46, 109, 101, 100, 105,  97,  58,  83, 111, 117, 
110, 100,  67, 111, 100, 101,  99,   5,  83,  80,  69,  69,  88,   5,  83, 112, 
101, 101, 120,  10,  78,  69,  76,  76,  89,  77,  79,  83,  69,  82,  10,  78, 
101, 108, 108, 121,  77, 111, 115, 101, 114,  10,  83, 111, 117, 110, 100,  67, 
111, 100, 101,  99,  30, 102, 108,  97, 115, 104,  46, 109, 101, 100, 105,  97, 
 58,  83, 111, 117, 110, 100,  76, 111,  97, 100, 101, 114,  67, 111, 110, 116, 
101, 120, 116,  15,  99, 104, 101,  99, 107,  80, 111, 108, 105,  99, 121,  70, 
105, 108, 101,  10,  98, 117, 102, 102, 101, 114,  84, 105, 109, 101,   7,  66, 
111, 111, 108, 101,  97, 110,  18,  83, 111, 117, 110, 100,  76, 111,  97, 100, 
101, 114,  67, 111, 110, 116, 101, 120, 116,  17, 102, 108,  97, 115, 104,  46, 
109, 101, 100, 105,  97,  58,  83, 111, 117, 110, 100,   4, 108, 111,  97, 100, 
  9, 102, 108,  97, 115, 104,  46, 110, 101, 116,  11, 102, 108,  97, 115, 104, 
 46, 117, 116, 105, 108, 115,  28, 102, 108,  97, 115, 104,  46, 101, 118, 101, 
110, 116, 115,  58,  69, 118, 101, 110, 116,  68, 105, 115, 112,  97, 116,  99, 
104, 101, 114,  10,  85,  82,  76,  82, 101, 113, 117, 101, 115, 116,   9,  66, 
121, 116, 101,  65, 114, 114,  97, 121,  19,  95,  98, 117, 105, 108, 100,  76, 
111,  97, 100, 101, 114,  67, 111, 110, 116, 101, 120, 116,   5,  95, 108, 111, 
 97, 100,   4, 117, 105, 110, 116,   3, 105, 110, 116,   7, 101, 120, 116, 114, 
 97,  99, 116,  11, 105, 115,  66, 117, 102, 102, 101, 114, 105, 110, 103,   3, 
117, 114, 108,  11,  98, 121, 116, 101, 115,  76, 111,  97, 100, 101, 100,   4, 
112, 108,  97, 121,   6, 108, 101, 110, 103, 116, 104,   3, 105, 100,  51,  10, 
 98, 121, 116, 101, 115,  84, 111, 116,  97, 108,   5,  99, 108, 111, 115, 101, 
  5,  83, 111, 117, 110, 100,   6, 110,  97, 116, 105, 118, 101,   3,  99, 108, 
115,  17,  83, 111, 117, 110, 100,  67, 104,  97, 110, 110, 101, 108,  67, 108, 
 97, 115, 115,   8, 105, 110, 115, 116,  97, 110,  99, 101,  18,  83, 111, 117, 
110, 100,  67, 104,  97, 110, 110, 101, 108,  79,  98, 106, 101,  99, 116,   7, 
109, 101, 116, 104, 111, 100, 115,   4,  97, 117, 116, 111,  19,  83, 111, 117, 
110, 100,  84, 114,  97, 110, 115, 102, 111, 114, 109,  67, 108,  97, 115, 115, 
 20,  83, 111, 117, 110, 100,  84, 114,  97, 110, 115, 102, 111, 114, 109,  79, 
 98, 106, 101,  99, 116,  10,  83, 111, 117, 110, 100,  67, 108,  97, 115, 115, 
 11,  83, 111, 117, 110, 100,  79,  98, 106, 101,  99, 116,  25,   5,   1,   5, 
  4,  22,   2,  22,   5,  23,   5,  24,   1,  26,   1,  26,   6,   5,  17,  24, 
 17,   5,  27,  22,  34,  24,  27,   5,  36,  24,  36,   5,  42,  24,  42,  26, 
 42,   5,  47,  22,  49,  22,  50,  24,  47,  26,  47,  26,  51,   7,   8,   1, 
  2,   3,   4,   5,   6,   7,   8,   8,   2,   3,   4,   5,   8,  16,  17,  18, 
 12,   2,   3,   4,   5,   8,  12,  19,  20,  21,  22,  23,  24,   4,   2,   3, 
  4,   5,   5,   2,   3,   4,   5,  12,   7,   2,   3,   4,   5,  12,  20,  21, 
 70,   9,   3,   1,   9,   7,   1,   7,   3,   8,   9,   9,   1,   9,  10,   1, 
  9,  11,   1,   9,  12,   1,   9,  13,   1,   9,  14,   1,   7,   3,  15,   7, 
  3,   3,   7,   3,  14,   7,   3,  13,   7,   3,  11,   7,   3,   7,   7,   3, 
 12,   7,   4,  16,   7,   3,   6,   7,   3,  18,   7,   3,  19,   7,   3,  20, 
  7,   3,  21,   7,   3,  22,   7,   3,  23,   7,   3,  24,   7,   3,  25,   7, 
  4,  26,   7,   3,  28,   7,   3,  29,   7,   3,  30,   7,   3,  31,   7,   3, 
 32,   7,   4,  33,   7,  12,  35,   7,   3,  37,   7,   3,  39,   7,   4,  41, 
  9,  43,   2,   9,  44,   2,   7,   3,  45,   7,   3,  44,   7,   3,  43,   7, 
  4,  46,   9,  48,   3,   7,  20,  52,   7,  21,  53,   9,  54,   3,   9,  43, 
  3,   9,  44,   3,   9,  55,   3,   9,  46,   3,   7,   3,  56,   7,   3,  57, 
  7,   3,  58,   7,  19,  55,   7,   3,  48,   7,   3,  59,   7,  19,  54,   7, 
  3,  60,   7,   3,  61,   7,   3,  62,   7,   3,  63,   7,   3,  64,   7,   3, 
 65,   7,   3,  66,   7,   4,  67,   9,   6,   4,   9,  35,   5,   9,  35,   6, 
 43,   0,   0,   2,   0,   2,   0,   3,   3,   2,   8,   2,   1,   3,   2,   3, 
  1,  10,   3,   2,   0,   0,   3,   2,  32,   0,   3,   2,  32,   0,   3,   2, 
 32,   1,  10,   3,   2,  32,   1,  10,   3,   2,  32,   1,  10,   3,   2,  32, 
  0,   3,   2,  32,   1,  10,   3,   2,  32,   1,  10,   3,   2,  32,   0,   3, 
  2,   0,   0,   3,   2,  32,   0,   0,   2,   0,   0,   0,   2,   0,   0,   0, 
  2,   0,   0,   0,   2,   0,   0,  10,   2,  32,   0,   3,   2,  32,   0,   3, 
  2,  32,   1,  10,  17,   2,  32,   0,   3,   2,  32,   0,  17,   2,  32,   0, 
  0,   2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   2,   0,   3,  40,   2, 
  8,   2,   3,   3,  10,  10,   0,   0,   2,   0,   2,   0,  45,  43,   2,   8, 
  2,  12,  12,  12,  12,   3,   3,  46,   3,   3,   2,  40,   1,   4,   3,   3, 
 10,  45,  40,   3,   2,  32,   2,  10,  45,  43,   2,   8,   1,  12,  12,   0, 
 10,   2,  32,   1,  43,  43,   2,   0,   0,  20,   2,  32,   0,  52,   2,  32, 
  3,  33,   3,  53,  17,   2,  40,   3,   2,   3,   2,   3,  12,  12,   0,   3, 
  2,  32,   0,  27,   2,  32,   0,  53,   2,  32,   0,  40,   2,  32,   0,   0, 
  2,   0,   3,  68,   3,  69,  71,  73,  70,  72,  74,  68,   3,  69,  71,  73, 
 75,  76,  74,  68,   3,  69,  71,  73,  77,  78,  74,   6,  17,  18,  11,   6, 
  0,   1,  12,  11,   2,   0,   4,  12,   3,   0,  11,  13,   2,   0,   3,  14, 
  2,   0,   5,  13,   3,   0,   6,  14,   3,   0,   7,  11,   3,   0,  10,  15, 
  3,   0,   2,  16,   3,   0,   8,  16,   2,   0,   9,  15,   2,   0,  12,  12, 
  2,   0,  13,  27,  18,  10,  10,   0,  15,   7,  19,   0,   0,  20,   0,  21, 
  0,   0,  20,   0,  22,   0,   0,  20,   0,  23,   0,   0,  20,   0,  24,   0, 
  0,  20,   0,  25,   0,   0,  20,   0,  26,   0,   0,  20,   0,  33,  34,  11, 
 13,   0,  17,   6,  28,   1,   0,  18,  29,   2,   0,  19,  30,   2,   0,  20, 
 31,   3,   0,  21,  32,   2,   0,  22,  31,   2,   0,  23,  37,  18,  11,  15, 
  0,  25,   0,  43,  18,   9,  17,   0,  27,   2,  41,   0,   0,   3,   3,   3, 
 42,   0,   0,  40,  10,  10,  66,  34,   9,  22,   0,  29,  12,  54,   1,   0, 
 30,  55,   1,   0,  31,  56,   1,   0,  32,  57,   2,   0,  41,  58,   1,   0, 
 34,  59,   2,   0,  35,  60,   2,   0,  36,  61,   1,   0,  37,  62,   2,   0, 
 38,  63,   2,   0,  39,  64,   2,   0,  40,  65,   1,   0,  33,   0,   0,  14, 
  0,  16,   0,  24,   2,  35,   6,   1,  20,  38,   1,  36,   6,   2,  20,  40, 
  1,  26,   0,  28,   0,   1,  42,   6,  33,  68,   3,   2,   1,   0,  17,  68, 
  1,   0,   1,   1,  27,   4,   2,   1,  43,   4,   5,   4,  37,   4,   4,   3, 
 66,  68,   6,   5,   1,   2,  17,   0,   1,   1,   3,   4,   3, 208,  48,  71, 
  0,   0,   1,   2,   3,   4,   5,  14, 208,  48, 208,  73,   0, 208, 209, 104, 
  1, 208, 210, 104,   2,  71,   0,   0,   2,   4,   2,   4,   5,  41, 208,  48, 
208,  93,   4, 102,   4,  36,   1, 209, 161,  70,   5,   1,  97,   6, 208,  36, 
  0,  97,   7, 208,  93,   4, 102,   4,  36,   1, 209, 160,  70,   5,   1,  97, 
  8, 208,  36,   0,  97,   9,  71,   0,   0,  12,   3,   1,   4,   5,  34, 208, 
 48, 208, 102,   7,  36,   0,  20,   0,   0,   0, 208, 102,   9,  36,   0,  20, 
 11,   0,   0,  36,   1, 208, 102,   6, 208, 102,   6, 162, 161,  72,  36,   0, 
 72,   0,   0,  14,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,  15,   1, 
  1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  16,   1,   1,   4, 
  5,   3, 208,  48,  71,   0,   0,  17,   1,   1,   5,   6,   6, 208,  48, 208, 
 73,   0,  71,   0,   0,  24,   2,   1,   3,   4,  15, 208,  48,  94,  35,  44, 
 38, 104,  35,  94,  36,  44,  40, 104,  36,  71,   0,   0,  25,   1,   1,   4, 
  5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  26,   1,   1,   3,   4,   3, 
208,  48,  71,   0,   0,  27,   2,   3,   4,   5,  14, 208,  48, 208,  73,   0, 
208, 210, 104,  38, 208, 209, 104,  39,  71,   0,   0,  28,   1,   1,   4,   5, 
  3, 208,  48,  71,   0,   0,  29,   3,   3,   5,   6,  13, 208,  48, 208,  73, 
  0, 208, 209, 210,  70,  44,   2,  41,  71,   0,   0,  32,   4,   4,   5,   6, 
 22, 208,  48, 208, 210,  70,  47,   1, 130, 215, 208, 209, 211, 102,  48, 211, 
102,  49,  70,  50,   3,  41,  71,   0,   0,  34,   2,   2,   5,   6,  18, 208, 
 48, 209,  32,  20,   8,   0,   0,  93,  51,  74,  51,   0, 128,  43, 213, 209, 
 72,   0,   0,  42,   2,   1,   1,   4, 111, 208,  48, 101,   0,  93,  18, 102, 
 18,  48,  93,  67, 102,  67,  88,   0,  29, 104,  17, 101,   0,  93,  18, 102, 
 18,  48,  93,  67, 102,  67,  88,   1,  29, 104,  27, 101,   0,  93,  18, 102, 
 18,  48,  93,  34, 102,  34,  48,  93,  68, 102,  68,  88,   2,  29,  29, 104, 
 33, 101,   0,  93,  18, 102,  18,  48,  93,  67, 102,  67,  88,   3,  29, 104, 
 37, 101,   0,  93,  18, 102,  18,  48,  93,  67, 102,  67,  88,   4,  29, 104, 
 43, 101,   0,  93,  18, 102,  18,  48,  93,  34, 102,  34,  48,  93,  69, 102, 
 69,  88,   5,  29,  29, 104,  66,  71,   0,   0};

} }
