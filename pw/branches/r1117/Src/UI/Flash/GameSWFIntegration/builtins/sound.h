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
#pragma once

#define AVMTHUNK_VERSION 5

namespace avmplus {
    class SoundChannelClass; //flash.media::SoundChannel$
    class SoundChannelObject; //flash.media::SoundChannel
    class SoundClass; //flash.media::Sound$
    class SoundObject; //flash.media::Sound
    class SoundTransformClass; //flash.media::SoundTransform$
    class SoundTransformObject; //flash.media::SoundTransform
}

namespace avmplus { namespace NativeID {

extern const uint32_t sound_abc_class_count;
extern const uint32_t sound_abc_script_count;
extern const uint32_t sound_abc_method_count;
extern const uint32_t sound_abc_length;
extern const uint8_t sound_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(sound)

/* classes */
const uint32_t abcclass_flash_media_SoundTransform = 0;
const uint32_t abcclass_flash_media_ID3Info = 1;
const uint32_t abcclass_flash_media_SoundChannel = 2;
const uint32_t abcclass_flash_media_SoundCodec = 3;
const uint32_t abcclass_flash_media_SoundLoaderContext = 4;
const uint32_t abcclass_flash_media_Sound = 5;

/* methods */
const uint32_t flash_media_SoundTransform_rightToRight_get = 3;
const uint32_t flash_media_SoundTransform_volume_get = 4;
const uint32_t flash_media_SoundTransform_leftToLeft_get = 5;
const uint32_t flash_media_SoundTransform_rightToRight_set = 6;
const uint32_t flash_media_SoundTransform_leftToLeft_set = 7;
const uint32_t flash_media_SoundTransform_leftToRight_set = 8;
const uint32_t flash_media_SoundTransform_leftToRight_get = 9;
const uint32_t flash_media_SoundTransform_volume_set = 10;
const uint32_t flash_media_SoundTransform_rightToLeft_set = 11;
const uint32_t flash_media_SoundTransform_rightToLeft_get = 13;
const uint32_t flash_media_SoundChannel_stop = 18;
const uint32_t flash_media_SoundChannel_leftPeak_get = 19;
const uint32_t flash_media_SoundChannel_position_get = 20;
const uint32_t flash_media_SoundChannel_soundTransform_set = 21;
const uint32_t flash_media_SoundChannel_rightPeak_get = 22;
const uint32_t flash_media_SoundChannel_soundTransform_get = 23;
const uint32_t flash_media_Sound_extract = 30;
const uint32_t flash_media_Sound_private__load = 31;
const uint32_t flash_media_Sound_close = 33;
const uint32_t flash_media_Sound_url_get = 35;
const uint32_t flash_media_Sound_bytesLoaded_get = 36;
const uint32_t flash_media_Sound_play = 37;
const uint32_t flash_media_Sound_length_get = 38;
const uint32_t flash_media_Sound_id3_get = 39;
const uint32_t flash_media_Sound_bytesTotal_get = 40;
const uint32_t flash_media_Sound_isBuffering_get = 41;

extern AvmBox sound_a2a_odio_opti0_opti0_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_media_Sound_play_thunk  sound_a2a_odio_opti0_opti0_optakAvmThunkNull_thunk

extern AvmBox sound_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_media_SoundTransform_rightToLeft_set_thunk  sound_v2a_od_thunk
#define flash_media_SoundTransform_volume_set_thunk  sound_v2a_od_thunk
#define flash_media_SoundTransform_leftToLeft_set_thunk  sound_v2a_od_thunk
#define flash_media_SoundTransform_leftToRight_set_thunk  sound_v2a_od_thunk
#define flash_media_SoundTransform_rightToRight_set_thunk  sound_v2a_od_thunk

extern double sound_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_media_SoundTransform_leftToLeft_get_thunk  sound_d2d_o_thunk
#define flash_media_SoundChannel_leftPeak_get_thunk  sound_d2d_o_thunk
#define flash_media_SoundChannel_position_get_thunk  sound_d2d_o_thunk
#define flash_media_SoundChannel_rightPeak_get_thunk  sound_d2d_o_thunk
#define flash_media_SoundTransform_rightToLeft_get_thunk  sound_d2d_o_thunk
#define flash_media_SoundTransform_rightToRight_get_thunk  sound_d2d_o_thunk
#define flash_media_SoundTransform_volume_get_thunk  sound_d2d_o_thunk
#define flash_media_SoundTransform_leftToRight_get_thunk  sound_d2d_o_thunk
#define flash_media_Sound_length_get_thunk  sound_d2d_o_thunk

extern AvmBox sound_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_media_SoundChannel_soundTransform_set_thunk  sound_v2a_oo_thunk

extern double sound_d2d_oodd_opti_1_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_media_Sound_extract_thunk  sound_d2d_oodd_opti_1_thunk

extern AvmBox sound_u2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_media_Sound_bytesLoaded_get_thunk  sound_u2a_o_thunk

extern AvmBox sound_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_media_SoundChannel_stop_thunk  sound_v2a_o_thunk
#define flash_media_Sound_close_thunk  sound_v2a_o_thunk

extern AvmBox sound_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_media_Sound_id3_get_thunk  sound_a2a_o_thunk
#define flash_media_SoundChannel_soundTransform_get_thunk  sound_a2a_o_thunk

extern AvmBox sound_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_media_Sound_isBuffering_get_thunk  sound_b2a_o_thunk

extern AvmBox sound_v2a_oobd_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_media_Sound_private__load_thunk  sound_v2a_oobd_thunk

extern AvmBox sound_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_media_Sound_url_get_thunk  sound_s2a_o_thunk

extern AvmBox sound_i2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_media_Sound_bytesTotal_get_thunk  sound_i2a_o_thunk

class SlotOffsetsAndAsserts;
// flash.media::SoundTransform$
//-----------------------------------------------------------
class SoundTransformClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SoundTransformClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SoundTransformClassSlots EmptySlotsStruct_SoundTransformClass
//-----------------------------------------------------------

// flash.media::SoundTransform
//-----------------------------------------------------------
class SoundTransformObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SoundTransformObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SoundTransformObjectSlots EmptySlotsStruct_SoundTransformObject
//-----------------------------------------------------------

// flash.media::SoundChannel$
//-----------------------------------------------------------
class SoundChannelClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SoundChannelClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SoundChannelClassSlots EmptySlotsStruct_SoundChannelClass
//-----------------------------------------------------------

// flash.media::SoundChannel
//-----------------------------------------------------------
class SoundChannelObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SoundChannelObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SoundChannelObjectSlots EmptySlotsStruct_SoundChannelObject
//-----------------------------------------------------------

// flash.media::Sound$
//-----------------------------------------------------------
class SoundClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SoundClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SoundClassSlots EmptySlotsStruct_SoundClass
//-----------------------------------------------------------

// flash.media::Sound
//-----------------------------------------------------------
class SoundObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SoundObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SoundObjectSlots EmptySlotsStruct_SoundObject
//-----------------------------------------------------------

} }
