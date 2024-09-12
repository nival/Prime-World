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
    class Matrix3DClass; //flash.geom::Matrix3D$
    class Matrix3DObject; //flash.geom::Matrix3D
    class PerspectiveProjectionClass; //flash.geom::PerspectiveProjection$
    class PerspectiveProjectionObject; //flash.geom::PerspectiveProjection
    class TransformClass; //flash.geom::Transform$
    class TransformObject; //flash.geom::Transform
    class Utils3DClass; //flash.geom::Utils3D$
    class Utils3DObject; //flash.geom::Utils3D
}

namespace avmplus { namespace NativeID {

extern const uint32_t geom_abc_class_count;
extern const uint32_t geom_abc_script_count;
extern const uint32_t geom_abc_method_count;
extern const uint32_t geom_abc_length;
extern const uint8_t geom_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(geom)

/* classes */
const uint32_t abcclass_flash_geom_Point = 0;
const uint32_t abcclass_flash_geom_ColorTransform = 1;
const uint32_t abcclass_flash_geom_Matrix = 2;
const uint32_t abcclass_flash_geom_Matrix3D = 3;
const uint32_t abcclass_flash_geom_Orientation3D = 4;
const uint32_t abcclass_flash_geom_PerspectiveProjection = 5;
const uint32_t abcclass_flash_geom_Rectangle = 6;
const uint32_t abcclass_flash_geom_Transform = 7;
const uint32_t abcclass_flash_geom_Utils3D = 8;
const uint32_t abcclass_flash_geom_Vector3D = 9;

/* methods */
const uint32_t flash_geom_Matrix3D_interpolate = 34;
const uint32_t flash_geom_Matrix3D_transpose = 36;
const uint32_t flash_geom_Matrix3D_prependTranslation = 37;
const uint32_t flash_geom_Matrix3D_rawData_set = 38;
const uint32_t flash_geom_Matrix3D_deltaTransformVector = 39;
const uint32_t flash_geom_Matrix3D_position_get = 40;
const uint32_t flash_geom_Matrix3D_pointAt = 41;
const uint32_t flash_geom_Matrix3D_transformVectors = 42;
const uint32_t flash_geom_Matrix3D_prependRotation = 43;
const uint32_t flash_geom_Matrix3D_prepend = 44;
const uint32_t flash_geom_Matrix3D_transformVector = 45;
const uint32_t flash_geom_Matrix3D_appendScale = 46;
const uint32_t flash_geom_Matrix3D_decompose = 47;
const uint32_t flash_geom_Matrix3D_rawData_get = 48;
const uint32_t flash_geom_Matrix3D_interpolateTo = 49;
const uint32_t flash_geom_Matrix3D_determinant_get = 50;
const uint32_t flash_geom_Matrix3D_invert = 51;
const uint32_t flash_geom_Matrix3D_appendTranslation = 52;
const uint32_t flash_geom_Matrix3D_appendRotation = 53;
const uint32_t flash_geom_Matrix3D_position_set = 54;
const uint32_t flash_geom_Matrix3D_append = 55;
const uint32_t flash_geom_Matrix3D_prependScale = 56;
const uint32_t flash_geom_Matrix3D_identity = 58;
const uint32_t flash_geom_Matrix3D_recompose = 59;
const uint32_t flash_geom_PerspectiveProjection_projectionCenter_get = 64;
const uint32_t flash_geom_PerspectiveProjection_toMatrix3D = 65;
const uint32_t flash_geom_PerspectiveProjection_fieldOfView_get = 66;
const uint32_t flash_geom_PerspectiveProjection_projectionCenter_set = 67;
const uint32_t flash_geom_PerspectiveProjection_focalLength_get = 68;
const uint32_t flash_geom_PerspectiveProjection_fieldOfView_set = 69;
const uint32_t flash_geom_PerspectiveProjection_focalLength_set = 70;
const uint32_t flash_geom_Transform_matrix_get = 104;
const uint32_t flash_geom_Transform_matrix_set = 105;
const uint32_t flash_geom_Transform_matrix3D_set = 106;
const uint32_t flash_geom_Transform_colorTransform_get = 107;
const uint32_t flash_geom_Transform_perspectiveProjection_get = 108;
const uint32_t flash_geom_Transform_concatenatedMatrix_get = 109;
const uint32_t flash_geom_Transform_matrix3D_get = 110;
const uint32_t flash_geom_Transform_getRelativeMatrix3D = 111;
const uint32_t flash_geom_Transform_perspectiveProjection_set = 112;
const uint32_t flash_geom_Transform_concatenatedColorTransform_get = 113;
const uint32_t flash_geom_Transform_colorTransform_set = 114;
const uint32_t flash_geom_Transform_pixelBounds_get = 115;
const uint32_t flash_geom_Utils3D_pointTowards = 117;
const uint32_t flash_geom_Utils3D_projectVector = 118;
const uint32_t flash_geom_Utils3D_projectVectors = 119;

extern AvmBox geom_v2a_oooo_optakAvmThunkNull_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Matrix3D_pointAt_thunk  geom_v2a_oooo_optakAvmThunkNull_optakAvmThunkNull_thunk

extern AvmBox geom_v2a_ooo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Matrix3D_transformVectors_thunk  geom_v2a_ooo_thunk

extern AvmBox geom_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_PerspectiveProjection_fieldOfView_set_thunk  geom_v2a_od_thunk
#define flash_geom_PerspectiveProjection_focalLength_set_thunk  geom_v2a_od_thunk

extern AvmBox geom_a2a_ooo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Utils3D_projectVector_thunk  geom_a2a_ooo_thunk

extern AvmBox geom_a2a_os_optsAvmThunkConstant_AvmString_81_____eulerAngles_____thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Matrix3D_decompose_thunk  geom_a2a_os_optsAvmThunkConstant_AvmString_81_____eulerAngles_____thunk

extern AvmBox geom_a2a_odoooo_optakAvmThunkNull_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Utils3D_pointTowards_thunk  geom_a2a_odoooo_optakAvmThunkNull_optakAvmThunkNull_thunk

extern AvmBox geom_b2a_oos_optsAvmThunkConstant_AvmString_81_____eulerAngles_____thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Matrix3D_recompose_thunk  geom_b2a_oos_optsAvmThunkConstant_AvmString_81_____eulerAngles_____thunk

extern AvmBox geom_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Transform_colorTransform_set_thunk  geom_v2a_oo_thunk
#define flash_geom_Matrix3D_prepend_thunk  geom_v2a_oo_thunk
#define flash_geom_Transform_matrix3D_set_thunk  geom_v2a_oo_thunk
#define flash_geom_Transform_perspectiveProjection_set_thunk  geom_v2a_oo_thunk
#define flash_geom_PerspectiveProjection_projectionCenter_set_thunk  geom_v2a_oo_thunk
#define flash_geom_Matrix3D_rawData_set_thunk  geom_v2a_oo_thunk
#define flash_geom_Transform_matrix_set_thunk  geom_v2a_oo_thunk
#define flash_geom_Matrix3D_position_set_thunk  geom_v2a_oo_thunk
#define flash_geom_Matrix3D_append_thunk  geom_v2a_oo_thunk

extern AvmBox geom_v2a_ood_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Matrix3D_interpolateTo_thunk  geom_v2a_ood_thunk

extern AvmBox geom_v2a_oddd_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Matrix3D_appendTranslation_thunk  geom_v2a_oddd_thunk
#define flash_geom_Matrix3D_appendScale_thunk  geom_v2a_oddd_thunk
#define flash_geom_Matrix3D_prependTranslation_thunk  geom_v2a_oddd_thunk
#define flash_geom_Matrix3D_prependScale_thunk  geom_v2a_oddd_thunk

extern AvmBox geom_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Matrix3D_identity_thunk  geom_v2a_o_thunk
#define flash_geom_Matrix3D_transpose_thunk  geom_v2a_o_thunk

extern AvmBox geom_v2a_ooooo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Utils3D_projectVectors_thunk  geom_v2a_ooooo_thunk

extern AvmBox geom_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Transform_concatenatedColorTransform_get_thunk  geom_a2a_o_thunk
#define flash_geom_PerspectiveProjection_toMatrix3D_thunk  geom_a2a_o_thunk
#define flash_geom_Transform_perspectiveProjection_get_thunk  geom_a2a_o_thunk
#define flash_geom_Matrix3D_rawData_get_thunk  geom_a2a_o_thunk
#define flash_geom_Transform_matrix3D_get_thunk  geom_a2a_o_thunk
#define flash_geom_Transform_pixelBounds_get_thunk  geom_a2a_o_thunk
#define flash_geom_Matrix3D_position_get_thunk  geom_a2a_o_thunk
#define flash_geom_Transform_concatenatedMatrix_get_thunk  geom_a2a_o_thunk
#define flash_geom_Transform_matrix_get_thunk  geom_a2a_o_thunk
#define flash_geom_PerspectiveProjection_projectionCenter_get_thunk  geom_a2a_o_thunk
#define flash_geom_Transform_colorTransform_get_thunk  geom_a2a_o_thunk

extern AvmBox geom_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Matrix3D_invert_thunk  geom_b2a_o_thunk

extern AvmBox geom_a2a_oood_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Matrix3D_interpolate_thunk  geom_a2a_oood_thunk

extern double geom_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_PerspectiveProjection_focalLength_get_thunk  geom_d2d_o_thunk
#define flash_geom_Matrix3D_determinant_get_thunk  geom_d2d_o_thunk
#define flash_geom_PerspectiveProjection_fieldOfView_get_thunk  geom_d2d_o_thunk

extern AvmBox geom_a2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Transform_getRelativeMatrix3D_thunk  geom_a2a_oa_thunk

extern AvmBox geom_v2a_odoo_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Matrix3D_prependRotation_thunk  geom_v2a_odoo_optakAvmThunkNull_thunk
#define flash_geom_Matrix3D_appendRotation_thunk  geom_v2a_odoo_optakAvmThunkNull_thunk

extern AvmBox geom_a2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_geom_Matrix3D_transformVector_thunk  geom_a2a_oo_thunk
#define flash_geom_Matrix3D_deltaTransformVector_thunk  geom_a2a_oo_thunk

class SlotOffsetsAndAsserts;
// flash.geom::Matrix3D$
//-----------------------------------------------------------
class Matrix3DClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_Matrix3DClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::Matrix3DClassSlots EmptySlotsStruct_Matrix3DClass
//-----------------------------------------------------------

// flash.geom::Matrix3D
//-----------------------------------------------------------
class Matrix3DObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_Matrix3DObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::Matrix3DObjectSlots EmptySlotsStruct_Matrix3DObject
//-----------------------------------------------------------

// flash.geom::PerspectiveProjection$
//-----------------------------------------------------------
class PerspectiveProjectionClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_PerspectiveProjectionClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::PerspectiveProjectionClassSlots EmptySlotsStruct_PerspectiveProjectionClass
//-----------------------------------------------------------

// flash.geom::PerspectiveProjection
//-----------------------------------------------------------
class PerspectiveProjectionObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_PerspectiveProjectionObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::PerspectiveProjectionObjectSlots EmptySlotsStruct_PerspectiveProjectionObject
//-----------------------------------------------------------

// flash.geom::Transform$
//-----------------------------------------------------------
class TransformClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TransformClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TransformClassSlots EmptySlotsStruct_TransformClass
//-----------------------------------------------------------

// flash.geom::Transform
//-----------------------------------------------------------
class TransformObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TransformObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TransformObjectSlots EmptySlotsStruct_TransformObject
//-----------------------------------------------------------

// flash.geom::Utils3D$
//-----------------------------------------------------------
class Utils3DClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_Utils3DClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::Utils3DClassSlots EmptySlotsStruct_Utils3DClass
//-----------------------------------------------------------

// flash.geom::Utils3D
//-----------------------------------------------------------
class Utils3DObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_Utils3DObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::Utils3DObjectSlots EmptySlotsStruct_Utils3DObject
//-----------------------------------------------------------

} }
