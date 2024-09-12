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

const uint32_t geom_abc_class_count = 10;
const uint32_t geom_abc_script_count = 1;
const uint32_t geom_abc_method_count = 142;
const uint32_t geom_abc_length = 9170;

/* thunks (19 unique signatures, 46 total) */

#ifndef AVMPLUS_INDIRECT_NATIVE_THUNKS
  #error nativegen.py: --directthunks requires AVMFEATURE_INDIRECT_NATIVE_THUNKS=1
#endif


// flash_geom_Matrix3D_pointAt
AvmBox geom_v2a_oooo_optakAvmThunkNull_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmObject
        , argoff3 = argoff2 + AvmThunkArgSize_AvmObject
    };
    (void)env;
    Matrix3DObject* const obj = (Matrix3DObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->pointAt(
        AvmThunkUnbox_AvmObject(argv[argoff1])
        , (argc < 2 ? AvmThunkCoerce_AvmBox_AvmObject(kAvmThunkNull) : AvmThunkUnbox_AvmObject(argv[argoff2]))
        , (argc < 3 ? AvmThunkCoerce_AvmBox_AvmObject(kAvmThunkNull) : AvmThunkUnbox_AvmObject(argv[argoff3]))
    );
    return kAvmThunkUndefined;
}

// flash_geom_Matrix3D_transformVectors
AvmBox geom_v2a_ooo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    Matrix3DObject* const obj = (Matrix3DObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->transformVectors(
        (DoubleVectorObject*)AvmThunkUnbox_AvmObject(argv[argoff1])
        , (DoubleVectorObject*)AvmThunkUnbox_AvmObject(argv[argoff2])
    );
    return kAvmThunkUndefined;
}

// flash_geom_PerspectiveProjection_fieldOfView_set
// flash_geom_PerspectiveProjection_focalLength_set
AvmBox geom_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_geom_Utils3D_projectVector
AvmBox geom_a2a_ooo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    Utils3DClass* const obj = (Utils3DClass*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmObject const ret = obj->projectVector(
        (Matrix3DObject*)AvmThunkUnbox_AvmObject(argv[argoff1])
        , AvmThunkUnbox_AvmObject(argv[argoff2])
    );
    return (AvmBox) ret;
}

// flash_geom_Matrix3D_decompose
AvmBox geom_a2a_os_optsAvmThunkConstant_AvmString_81_____eulerAngles_____thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)env;
    Matrix3DObject* const obj = (Matrix3DObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    ObjectVectorObject* const ret = obj->decompose(
        (argc < 1 ? AvmThunkConstant_AvmString(81)/* "eulerAngles" */ : AvmThunkUnbox_AvmString(argv[argoff1]))
    );
    return (AvmBox) ret;
}

// flash_geom_Utils3D_pointTowards
AvmBox geom_a2a_odoooo_optakAvmThunkNull_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_double
        , argoff3 = argoff2 + AvmThunkArgSize_AvmObject
        , argoff4 = argoff3 + AvmThunkArgSize_AvmObject
        , argoff5 = argoff4 + AvmThunkArgSize_AvmObject
    };
    (void)env;
    Utils3DClass* const obj = (Utils3DClass*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    Matrix3DObject* const ret = obj->pointTowards(
        AvmThunkUnbox_double(argv[argoff1])
        , (Matrix3DObject*)AvmThunkUnbox_AvmObject(argv[argoff2])
        , AvmThunkUnbox_AvmObject(argv[argoff3])
        , (argc < 4 ? AvmThunkCoerce_AvmBox_AvmObject(kAvmThunkNull) : AvmThunkUnbox_AvmObject(argv[argoff4]))
        , (argc < 5 ? AvmThunkCoerce_AvmBox_AvmObject(kAvmThunkNull) : AvmThunkUnbox_AvmObject(argv[argoff5]))
    );
    return (AvmBox) ret;
}

// flash_geom_Matrix3D_recompose
AvmBox geom_b2a_oos_optsAvmThunkConstant_AvmString_81_____eulerAngles_____thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmObject
    };
    (void)env;
    Matrix3DObject* const obj = (Matrix3DObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmBool32 const ret = obj->recompose(
        (ObjectVectorObject*)AvmThunkUnbox_AvmObject(argv[argoff1])
        , (argc < 2 ? AvmThunkConstant_AvmString(81)/* "eulerAngles" */ : AvmThunkUnbox_AvmString(argv[argoff2]))
    );
    return (AvmBox) ret;
}

// flash_geom_Transform_colorTransform_set
// flash_geom_Matrix3D_prepend
// flash_geom_Transform_matrix3D_set
// flash_geom_Transform_perspectiveProjection_set
// flash_geom_PerspectiveProjection_projectionCenter_set
// flash_geom_Matrix3D_rawData_set
// flash_geom_Transform_matrix_set
// flash_geom_Matrix3D_position_set
// flash_geom_Matrix3D_append
AvmBox geom_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_geom_Matrix3D_interpolateTo
AvmBox geom_v2a_ood_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    Matrix3DObject* const obj = (Matrix3DObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->interpolateTo(
        (Matrix3DObject*)AvmThunkUnbox_AvmObject(argv[argoff1])
        , AvmThunkUnbox_double(argv[argoff2])
    );
    return kAvmThunkUndefined;
}

// flash_geom_Matrix3D_appendTranslation
// flash_geom_Matrix3D_appendScale
// flash_geom_Matrix3D_prependTranslation
// flash_geom_Matrix3D_prependScale
AvmBox geom_v2a_oddd_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_double
        , argoff3 = argoff2 + AvmThunkArgSize_double
    };
    (void)argc;
    typedef AvmRetType_void (AvmObjectT::*FuncType)(double, double, double);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    (*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
        AvmThunkUnbox_double(argv[argoff1])
        , AvmThunkUnbox_double(argv[argoff2])
        , AvmThunkUnbox_double(argv[argoff3])
    );
    return kAvmThunkUndefined;
}

// flash_geom_Matrix3D_identity
// flash_geom_Matrix3D_transpose
AvmBox geom_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_geom_Utils3D_projectVectors
AvmBox geom_v2a_ooooo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmObject
        , argoff3 = argoff2 + AvmThunkArgSize_AvmObject
        , argoff4 = argoff3 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    Utils3DClass* const obj = (Utils3DClass*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    obj->projectVectors(
        (Matrix3DObject*)AvmThunkUnbox_AvmObject(argv[argoff1])
        , (DoubleVectorObject*)AvmThunkUnbox_AvmObject(argv[argoff2])
        , (DoubleVectorObject*)AvmThunkUnbox_AvmObject(argv[argoff3])
        , (DoubleVectorObject*)AvmThunkUnbox_AvmObject(argv[argoff4])
    );
    return kAvmThunkUndefined;
}

// flash_geom_Transform_concatenatedColorTransform_get
// flash_geom_PerspectiveProjection_toMatrix3D
// flash_geom_Transform_perspectiveProjection_get
// flash_geom_Matrix3D_rawData_get
// flash_geom_Transform_matrix3D_get
// flash_geom_Transform_pixelBounds_get
// flash_geom_Matrix3D_position_get
// flash_geom_Transform_concatenatedMatrix_get
// flash_geom_Transform_matrix_get
// flash_geom_PerspectiveProjection_projectionCenter_get
// flash_geom_Transform_colorTransform_get
AvmBox geom_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_geom_Matrix3D_invert
AvmBox geom_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
    };
    (void)argc;
    (void)env;
    Matrix3DObject* const obj = (Matrix3DObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    AvmBool32 const ret = obj->invert();
    return (AvmBox) ret;
}

// flash_geom_Matrix3D_interpolate
AvmBox geom_a2a_oood_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_AvmObject
        , argoff3 = argoff2 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    Matrix3DClass* const obj = (Matrix3DClass*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    Matrix3DObject* const ret = obj->interpolate(
        (Matrix3DObject*)AvmThunkUnbox_AvmObject(argv[argoff1])
        , (Matrix3DObject*)AvmThunkUnbox_AvmObject(argv[argoff2])
        , AvmThunkUnbox_double(argv[argoff3])
    );
    return (AvmBox) ret;
}

// flash_geom_PerspectiveProjection_focalLength_get
// flash_geom_Matrix3D_determinant_get
// flash_geom_PerspectiveProjection_fieldOfView_get
double geom_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
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

// flash_geom_Transform_getRelativeMatrix3D
AvmBox geom_a2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    (void)env;
    TransformObject* const obj = (TransformObject*)AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0]);
    Matrix3DObject* const ret = obj->getRelativeMatrix3D(
        AvmThunkUnbox_AvmBox(argv[argoff1])
    );
    return (AvmBox) ret;
}

// flash_geom_Matrix3D_prependRotation
// flash_geom_Matrix3D_appendRotation
AvmBox geom_v2a_odoo_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
        , argoff2 = argoff1 + AvmThunkArgSize_double
        , argoff3 = argoff2 + AvmThunkArgSize_AvmObject
    };
    typedef AvmRetType_void (AvmObjectT::*FuncType)(double, AvmObject, AvmObject);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    (*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
        AvmThunkUnbox_double(argv[argoff1])
        , AvmThunkUnbox_AvmObject(argv[argoff2])
        , (argc < 3 ? AvmThunkCoerce_AvmBox_AvmObject(kAvmThunkNull) : AvmThunkUnbox_AvmObject(argv[argoff3]))
    );
    return kAvmThunkUndefined;
}

// flash_geom_Matrix3D_transformVector
// flash_geom_Matrix3D_deltaTransformVector
AvmBox geom_a2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv)
{
    enum {
        argoff0 = 0
        , argoff1 = argoff0 + AvmThunkArgSize_AvmObject
    };
    (void)argc;
    typedef AvmRetType_AvmBox (AvmObjectT::*FuncType)(AvmObject);
    const FuncType func = reinterpret_cast<FuncType>(AVMTHUNK_GET_METHOD_HANDLER(env));
    return (AvmBox)(*(AvmThunkUnbox_AvmReceiver(AvmObject, argv[argoff0])).*(func))(
        AvmThunkUnbox_AvmObject(argv[argoff1])
    );
}

class SlotOffsetsAndAsserts
{
private:
    static uint32_t getSlotOffset(Traits* t, int nameId);
public:
    static const uint16_t s_slotsOffsetMatrix3DClass = 0;
    static const uint16_t s_slotsOffsetMatrix3DObject = 0;
    static void doMatrix3DClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetPerspectiveProjectionClass = 0;
    static const uint16_t s_slotsOffsetPerspectiveProjectionObject = 0;
    static void doPerspectiveProjectionClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetTransformClass = 0;
    static const uint16_t s_slotsOffsetTransformObject = 0;
    static void doTransformClassAsserts(Traits* cTraits, Traits* iTraits);
    static const uint16_t s_slotsOffsetUtils3DClass = 0;
    static const uint16_t s_slotsOffsetUtils3DObject = 0;
    static void doUtils3DClassAsserts(Traits* cTraits, Traits* iTraits);
};
REALLY_INLINE void SlotOffsetsAndAsserts::doMatrix3DClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(Matrix3DClass::EmptySlotsStruct_Matrix3DClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(Matrix3DObject::EmptySlotsStruct_Matrix3DObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doPerspectiveProjectionClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(PerspectiveProjectionClass::EmptySlotsStruct_PerspectiveProjectionClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(PerspectiveProjectionObject::EmptySlotsStruct_PerspectiveProjectionObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doTransformClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(TransformClass::EmptySlotsStruct_TransformClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(TransformObject::EmptySlotsStruct_TransformObject) >= 0);
}
REALLY_INLINE void SlotOffsetsAndAsserts::doUtils3DClassAsserts(Traits* cTraits, Traits* iTraits)
{
    (void)cTraits; (void)iTraits;
    // MMGC_STATIC_ASSERT(sizeof(Utils3DClass::EmptySlotsStruct_Utils3DClass) >= 0);
    // MMGC_STATIC_ASSERT(sizeof(Utils3DObject::EmptySlotsStruct_Utils3DObject) >= 0);
}

AVMTHUNK_NATIVE_CLASS_GLUE(Matrix3DClass, Matrix3DClass, SlotOffsetsAndAsserts::doMatrix3DClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(PerspectiveProjectionClass, PerspectiveProjectionClass, SlotOffsetsAndAsserts::doPerspectiveProjectionClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(TransformClass, TransformClass, SlotOffsetsAndAsserts::doTransformClassAsserts)
AVMTHUNK_NATIVE_CLASS_GLUE(Utils3DClass, Utils3DClass, SlotOffsetsAndAsserts::doUtils3DClassAsserts)

AVMTHUNK_BEGIN_NATIVE_TABLES(geom)
    
    AVMTHUNK_BEGIN_NATIVE_METHODS(geom)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_interpolate, Matrix3DClass::interpolate)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_transpose, Matrix3DObject::transpose)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_prependTranslation, Matrix3DObject::prependTranslation)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_rawData_set, Matrix3DObject::set_rawData)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_deltaTransformVector, Matrix3DObject::deltaTransformVector)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_position_get, Matrix3DObject::get_position)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_pointAt, Matrix3DObject::pointAt)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_transformVectors, Matrix3DObject::transformVectors)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_prependRotation, Matrix3DObject::prependRotation)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_prepend, Matrix3DObject::prepend)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_transformVector, Matrix3DObject::transformVector)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_appendScale, Matrix3DObject::appendScale)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_decompose, Matrix3DObject::decompose)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_rawData_get, Matrix3DObject::get_rawData)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_interpolateTo, Matrix3DObject::interpolateTo)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_determinant_get, Matrix3DObject::get_determinant)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_invert, Matrix3DObject::invert)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_appendTranslation, Matrix3DObject::appendTranslation)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_appendRotation, Matrix3DObject::appendRotation)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_position_set, Matrix3DObject::set_position)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_append, Matrix3DObject::append)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_prependScale, Matrix3DObject::prependScale)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_identity, Matrix3DObject::identity)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Matrix3D_recompose, Matrix3DObject::recompose)
        AVMTHUNK_NATIVE_METHOD(flash_geom_PerspectiveProjection_projectionCenter_get, PerspectiveProjectionObject::get_projectionCenter)
        AVMTHUNK_NATIVE_METHOD(flash_geom_PerspectiveProjection_toMatrix3D, PerspectiveProjectionObject::toMatrix3D)
        AVMTHUNK_NATIVE_METHOD(flash_geom_PerspectiveProjection_fieldOfView_get, PerspectiveProjectionObject::get_fieldOfView)
        AVMTHUNK_NATIVE_METHOD(flash_geom_PerspectiveProjection_projectionCenter_set, PerspectiveProjectionObject::set_projectionCenter)
        AVMTHUNK_NATIVE_METHOD(flash_geom_PerspectiveProjection_focalLength_get, PerspectiveProjectionObject::get_focalLength)
        AVMTHUNK_NATIVE_METHOD(flash_geom_PerspectiveProjection_fieldOfView_set, PerspectiveProjectionObject::set_fieldOfView)
        AVMTHUNK_NATIVE_METHOD(flash_geom_PerspectiveProjection_focalLength_set, PerspectiveProjectionObject::set_focalLength)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Transform_matrix_get, TransformObject::get_matrix)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Transform_matrix_set, TransformObject::set_matrix)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Transform_matrix3D_set, TransformObject::set_matrix3D)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Transform_colorTransform_get, TransformObject::get_colorTransform)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Transform_perspectiveProjection_get, TransformObject::get_perspectiveProjection)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Transform_concatenatedMatrix_get, TransformObject::get_concatenatedMatrix)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Transform_matrix3D_get, TransformObject::get_matrix3D)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Transform_getRelativeMatrix3D, TransformObject::getRelativeMatrix3D)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Transform_perspectiveProjection_set, TransformObject::set_perspectiveProjection)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Transform_concatenatedColorTransform_get, TransformObject::get_concatenatedColorTransform)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Transform_colorTransform_set, TransformObject::set_colorTransform)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Transform_pixelBounds_get, TransformObject::get_pixelBounds)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Utils3D_pointTowards, Utils3DClass::pointTowards)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Utils3D_projectVector, Utils3DClass::projectVector)
        AVMTHUNK_NATIVE_METHOD(flash_geom_Utils3D_projectVectors, Utils3DClass::projectVectors)
    AVMTHUNK_END_NATIVE_METHODS()
    
    AVMTHUNK_BEGIN_NATIVE_CLASSES(geom)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_geom_Matrix3D, Matrix3DClass, Matrix3DClass, SlotOffsetsAndAsserts::s_slotsOffsetMatrix3DClass, Matrix3DObject, SlotOffsetsAndAsserts::s_slotsOffsetMatrix3DObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_geom_PerspectiveProjection, PerspectiveProjectionClass, PerspectiveProjectionClass, SlotOffsetsAndAsserts::s_slotsOffsetPerspectiveProjectionClass, PerspectiveProjectionObject, SlotOffsetsAndAsserts::s_slotsOffsetPerspectiveProjectionObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_geom_Transform, TransformClass, TransformClass, SlotOffsetsAndAsserts::s_slotsOffsetTransformClass, TransformObject, SlotOffsetsAndAsserts::s_slotsOffsetTransformObject)
        AVMTHUNK_NATIVE_CLASS(abcclass_flash_geom_Utils3D, Utils3DClass, Utils3DClass, SlotOffsetsAndAsserts::s_slotsOffsetUtils3DClass, Utils3DObject, SlotOffsetsAndAsserts::s_slotsOffsetUtils3DObject)
    AVMTHUNK_END_NATIVE_CLASSES()
    
AVMTHUNK_END_NATIVE_TABLES()

AVMTHUNK_DEFINE_NATIVE_INITIALIZER(geom)

/* abc */
const uint8_t geom_abc_data[9170] = {
 16,   0,  46,   0,   3,   0,   1,   0,   2, 154, 153, 153, 153, 153, 153, 153, 
 64, 188,   1,  16, 102, 108,  97, 115, 104,  46, 103, 101, 111, 109,  58,  80, 
111, 105, 110, 116,   0,   1, 120,   9, 103, 101, 111, 109,  46,  97, 115,  36, 
 50,  10, 102, 108,  97, 115, 104,  46, 103, 101, 111, 109,   6,  79,  98, 106, 
101,  99, 116,   1, 121,   5,  80, 111, 105, 110, 116,   6,  78, 117, 109,  98, 
101, 114,   8, 115, 117,  98, 116, 114,  97,  99, 116,   6, 108, 101, 110, 103, 
116, 104,   4,  77,  97, 116, 104,   3,  99, 111, 115,   3, 115, 105, 110,   4, 
115, 113, 114, 116,   3,  40, 120,  61,   4,  44,  32, 121,  61,   1,  41,   6, 
 83, 116, 114, 105, 110, 103,   4, 118, 111, 105, 100,   7,  66, 111, 111, 108, 
101,  97, 110,  11, 105, 110, 116, 101, 114, 112, 111, 108,  97, 116, 101,   8, 
100, 105, 115, 116,  97, 110,  99, 101,   5, 112, 111, 108,  97, 114,   3,  97, 
100, 100,   8, 116, 111,  83, 116, 114, 105, 110, 103,   9, 110, 111, 114, 109, 
 97, 108, 105, 122, 101,   6, 111, 102, 102, 115, 101, 116,   5,  99, 108, 111, 
110, 101,   6, 101, 113, 117,  97, 108, 115,  25, 102, 108,  97, 115, 104,  46, 
103, 101, 111, 109,  58,  67, 111, 108, 111, 114,  84, 114,  97, 110, 115, 102, 
111, 114, 109,  13, 114, 101, 100,  77, 117, 108, 116, 105, 112, 108, 105, 101, 
114,  15, 103, 114, 101, 101, 110,  77, 117, 108, 116, 105, 112, 108, 105, 101, 
114,  14,  98, 108, 117, 101,  77, 117, 108, 116, 105, 112, 108, 105, 101, 114, 
 15,  97, 108, 112, 104,  97,  77, 117, 108, 116, 105, 112, 108, 105, 101, 114, 
  9, 114, 101, 100,  79, 102, 102, 115, 101, 116,  11, 103, 114, 101, 101, 110, 
 79, 102, 102, 115, 101, 116,  10,  98, 108, 117, 101,  79, 102, 102, 115, 101, 
116,  11,  97, 108, 112, 104,  97,  79, 102, 102, 115, 101, 116,   4, 117, 105, 
110, 116,  15,  40, 114, 101, 100,  77, 117, 108, 116, 105, 112, 108, 105, 101, 
114,  61,  18,  44,  32, 103, 114, 101, 101, 110,  77, 117, 108, 116, 105, 112, 
108, 105, 101, 114,  61,  17,  44,  32,  98, 108, 117, 101,  77, 117, 108, 116, 
105, 112, 108, 105, 101, 114,  61,  18,  44,  32,  97, 108, 112, 104,  97,  77, 
117, 108, 116, 105, 112, 108, 105, 101, 114,  61,  12,  44,  32, 114, 101, 100, 
 79, 102, 102, 115, 101, 116,  61,  14,  44,  32, 103, 114, 101, 101, 110,  79, 
102, 102, 115, 101, 116,  61,  13,  44,  32,  98, 108, 117, 101,  79, 102, 102, 
115, 101, 116,  61,  14,  44,  32,  97, 108, 112, 104,  97,  79, 102, 102, 115, 
101, 116,  61,  14,  67, 111, 108, 111, 114,  84, 114,  97, 110, 115, 102, 111, 
114, 109,   5,  99, 111, 108, 111, 114,   6,  99, 111, 110,  99,  97, 116,  17, 
102, 108,  97, 115, 104,  46, 103, 101, 111, 109,  58,  77,  97, 116, 114, 105, 
120,   1,  97,   1,  98,   1,  99,   1, 100,   2, 116, 120,   2, 116, 121,   8, 
105, 100, 101, 110, 116, 105, 116, 121,   6, 114, 111, 116,  97, 116, 101,   5, 
115,  99,  97, 108, 101,   3,  40,  97,  61,   4,  44,  32,  98,  61,   4,  44, 
 32,  99,  61,   4,  44,  32, 100,  61,   5,  44,  32, 116, 120,  61,   5,  44, 
 32, 116, 121,  61,   6,  77,  97, 116, 114, 105, 120,   3,  78,  97,  78,  19, 
100, 101, 108, 116,  97,  84, 114,  97, 110, 115, 102, 111, 114, 109,  80, 111, 
105, 110, 116,   9,  99, 114, 101,  97, 116, 101,  66, 111, 120,   9, 116, 114, 
 97, 110, 115, 108,  97, 116, 101,  14, 116, 114,  97, 110, 115, 102, 111, 114, 
109,  80, 111, 105, 110, 116,   6, 105, 110, 118, 101, 114, 116,  17,  99, 114, 
101,  97, 116, 101,  71, 114,  97, 100, 105, 101, 110, 116,  66, 111, 120,  19, 
102, 108,  97, 115, 104,  46, 103, 101, 111, 109,  58,  77,  97, 116, 114, 105, 
120,  51,  68,   8,  77,  97, 116, 114, 105, 120,  51,  68,  11,  95,  95,  65, 
 83,  51,  95,  95,  46, 118, 101,  99,   6,  86, 101,  99, 116, 111, 114,   8, 
 86, 101,  99, 116, 111, 114,  51,  68,  11, 101, 117, 108, 101, 114,  65, 110, 
103, 108, 101, 115,   7, 114,  97, 119,  68,  97, 116,  97,   8, 112, 111, 115, 
105, 116, 105, 111, 110,   7, 112, 111, 105, 110, 116,  65, 116,  18, 112, 114, 
101, 112, 101, 110, 100,  84, 114,  97, 110, 115, 108,  97, 116, 105, 111, 110, 
 16, 116, 114,  97, 110, 115, 102, 111, 114, 109,  86, 101,  99, 116, 111, 114, 
115,  15, 112, 114, 101, 112, 101, 110, 100,  82, 111, 116,  97, 116, 105, 111, 
110,   7, 112, 114, 101, 112, 101, 110, 100,  15, 116, 114,  97, 110, 115, 102, 
111, 114, 109,  86, 101,  99, 116, 111, 114,  11,  97, 112, 112, 101, 110, 100, 
 83,  99,  97, 108, 101,   9, 100, 101,  99, 111, 109, 112, 111, 115, 101,  12, 
112, 114, 101, 112, 101, 110, 100,  83,  99,  97, 108, 101,  11, 100, 101, 116, 
101, 114, 109, 105, 110,  97, 110, 116,  20, 100, 101, 108, 116,  97,  84, 114, 
 97, 110, 115, 102, 111, 114, 109,  86, 101,  99, 116, 111, 114,  14,  97, 112, 
112, 101, 110, 100,  82, 111, 116,  97, 116, 105, 111, 110,   9, 116, 114,  97, 
110, 115, 112, 111, 115, 101,   6,  97, 112, 112, 101, 110, 100,  13, 105, 110, 
116, 101, 114, 112, 111, 108,  97, 116, 101,  84, 111,  17,  97, 112, 112, 101, 
110, 100,  84, 114,  97, 110, 115, 108,  97, 116, 105, 111, 110,   9, 114, 101, 
 99, 111, 109, 112, 111, 115, 101,  24, 102, 108,  97, 115, 104,  46, 103, 101, 
111, 109,  58,  79, 114, 105, 101, 110, 116,  97, 116, 105, 111, 110,  51,  68, 
 10,  65,  88,  73,  83,  95,  65,  78,  71,  76,  69,   9,  97, 120, 105, 115, 
 65, 110, 103, 108, 101,  12,  69,  85,  76,  69,  82,  95,  65,  78,  71,  76, 
 69,  83,  10,  81,  85,  65,  84,  69,  82,  78,  73,  79,  78,  10, 113, 117, 
 97, 116, 101, 114, 110, 105, 111, 110,  13,  79, 114, 105, 101, 110, 116,  97, 
116, 105, 111, 110,  51,  68,  32, 102, 108,  97, 115, 104,  46, 103, 101, 111, 
109,  58,  80, 101, 114, 115, 112, 101,  99, 116, 105, 118, 101,  80, 114, 111, 
106, 101,  99, 116, 105, 111, 110,  16, 112, 114, 111, 106, 101,  99, 116, 105, 
111, 110,  67, 101, 110, 116, 101, 114,  11, 102, 111,  99,  97, 108,  76, 101, 
110, 103, 116, 104,  11, 102, 105, 101, 108, 100,  79, 102,  86, 105, 101, 119, 
 10, 116, 111,  77,  97, 116, 114, 105, 120,  51,  68,  21,  80, 101, 114, 115, 
112, 101,  99, 116, 105, 118, 101,  80, 114, 111, 106, 101,  99, 116, 105, 111, 
110,  20, 102, 108,  97, 115, 104,  46, 103, 101, 111, 109,  58,  82, 101,  99, 
116,  97, 110, 103, 108, 101,   5, 119, 105, 100, 116, 104,   6, 104, 101, 105, 
103, 104, 116,   9,  82, 101,  99, 116,  97, 110, 103, 108, 101,   7, 105, 115, 
 69, 109, 112, 116, 121,   3, 109, 105, 110,   3, 109,  97, 120,   8, 115, 101, 
116,  69, 109, 112, 116, 121,   4,  44,  32, 119,  61,   4,  44,  32, 104,  61, 
  5, 114, 105, 103, 104, 116,   6,  98, 111, 116, 116, 111, 109,  11,  98, 111, 
116, 116, 111, 109,  82, 105, 103, 104, 116,   4, 115, 105, 122, 101,   4, 108, 
101, 102, 116,  12, 105, 110, 102, 108,  97, 116, 101,  80, 111, 105, 110, 116, 
  5, 117, 110, 105, 111, 110,  12, 105, 110, 116, 101, 114, 115, 101,  99, 116, 
105, 111, 110,   7, 105, 110, 102, 108,  97, 116, 101,  12,  99, 111, 110, 116, 
 97, 105, 110, 115,  82, 101,  99, 116,   3, 116, 111, 112,   7, 116, 111, 112, 
 76, 101, 102, 116,   8,  99, 111, 110, 116,  97, 105, 110, 115,  13,  99, 111, 
110, 116,  97, 105, 110, 115,  80, 111, 105, 110, 116,  10, 105, 110, 116, 101, 
114, 115, 101,  99, 116, 115,  11, 111, 102, 102, 115, 101, 116,  80, 111, 105, 
110, 116,  20, 102, 108,  97, 115, 104,  46, 103, 101, 111, 109,  58,  84, 114, 
 97, 110, 115, 102, 111, 114, 109,   6, 109,  97, 116, 114, 105, 120,   8, 109, 
 97, 116, 114, 105, 120,  51,  68,  14,  99, 111, 108, 111, 114,  84, 114,  97, 
110, 115, 102, 111, 114, 109,  21, 112, 101, 114, 115, 112, 101,  99, 116, 105, 
118, 101,  80, 114, 111, 106, 101,  99, 116, 105, 111, 110,  18,  99, 111, 110, 
 99,  97, 116, 101, 110,  97, 116, 101, 100,  77,  97, 116, 114, 105, 120,  19, 
103, 101, 116,  82, 101, 108,  97, 116, 105, 118, 101,  77,  97, 116, 114, 105, 
120,  51,  68,  26,  99, 111, 110,  99,  97, 116, 101, 110,  97, 116, 101, 100, 
 67, 111, 108, 111, 114,  84, 114,  97, 110, 115, 102, 111, 114, 109,  11, 112, 
105, 120, 101, 108,  66, 111, 117, 110, 100, 115,   9,  84, 114,  97, 110, 115, 
102, 111, 114, 109,  18, 102, 108,  97, 115, 104,  46, 103, 101, 111, 109,  58, 
 85, 116, 105, 108, 115,  51,  68,  13, 112, 114, 111, 106, 101,  99, 116,  86, 
101,  99, 116, 111, 114,  12, 112, 111, 105, 110, 116,  84, 111, 119,  97, 114, 
100, 115,  14, 112, 114, 111, 106, 101,  99, 116,  86, 101,  99, 116, 111, 114, 
115,   7,  85, 116, 105, 108, 115,  51,  68,  19, 102, 108,  97, 115, 104,  46, 
103, 101, 111, 109,  58,  86, 101,  99, 116, 111, 114,  51,  68,   6,  90,  95, 
 65,  88,  73,  83,   6,  89,  95,  65,  88,  73,  83,   6,  88,  95,  65,  88, 
 73,  83,   1, 122,   4,  97,  99, 111, 115,   1, 119,   9,  86, 101,  99, 116, 
111, 114,  51,  68,  40,   2,  44,  32,  12,  97, 110, 103, 108, 101,  66, 101, 
116, 119, 101, 101, 110,  13, 108, 101, 110, 103, 116, 104,  83, 113, 117,  97, 
114, 101, 100,   6, 110, 101, 103,  97, 116, 101,   7, 115,  99,  97, 108, 101, 
 66, 121,  10, 100, 111, 116,  80, 114, 111, 100, 117,  99, 116,  10, 110, 101, 
 97, 114,  69, 113, 117,  97, 108, 115,  11, 100, 101,  99, 114, 101, 109, 101, 
110, 116,  66, 121,  12,  99, 114, 111, 115, 115,  80, 114, 111, 100, 117,  99, 
116,  11, 105, 110,  99, 114, 101, 109, 101, 110, 116,  66, 121,   7, 112, 114, 
111, 106, 101,  99, 116,  13, 102, 108,  97, 115, 104,  46, 100, 105, 115, 112, 
108,  97, 121,   6, 110,  97, 116, 105, 118, 101,   3,  99, 108, 115,  13,  77, 
 97, 116, 114, 105, 120,  51,  68,  67, 108,  97, 115, 115,   8, 105, 110, 115, 
116,  97, 110,  99, 101,  14,  77,  97, 116, 114, 105, 120,  51,  68,  79,  98, 
106, 101,  99, 116,   7, 109, 101, 116, 104, 111, 100, 115,   4,  97, 117, 116, 
111,  14,  84, 114,  97, 110, 115, 102, 111, 114, 109,  67, 108,  97, 115, 115, 
 15,  84, 114,  97, 110, 115, 102, 111, 114, 109,  79,  98, 106, 101,  99, 116, 
 26,  80, 101, 114, 115, 112, 101,  99, 116, 105, 118, 101,  80, 114, 111, 106, 
101,  99, 116, 105, 111, 110,  67, 108,  97, 115, 115,  27,  80, 101, 114, 115, 
112, 101,  99, 116, 105, 118, 101,  80, 114, 111, 106, 101,  99, 116, 105, 111, 
110,  79,  98, 106, 101,  99, 116,  12,  85, 116, 105, 108, 115,  51,  68,  67, 
108,  97, 115, 115,  13,  85, 116, 105, 108, 115,  51,  68,  79,  98, 106, 101, 
 99, 116,  34,   5,   1,   5,   4,  22,   2,  22,   5,  23,   5,  24,   1,  26, 
  1,  26,   6,   5,  31,  24,  31,  26,  31,   5,  52,  24,  52,  26,  52,   5, 
 76,  22,  78,  24,  76,  26,  76,   5, 101,  24, 101,   5, 108,  24, 108,   5, 
114,  24, 114,  26, 114,   5, 140,   1,  24, 140,   1,   5, 150,   1,  24, 150, 
  1,   5, 155,   1,  24, 155,   1,  26, 155,   1,   8, 174,   1,  10,   8,   1, 
  2,   3,   4,   5,   6,   7,   8,   8,   2,   3,   4,   5,   8,   9,  10,  11, 
  8,   2,   3,   4,   5,   8,  12,  13,  14,   9,   2,   3,   4,   5,   8,  15, 
 16,  17,  18,   8,   2,   3,   4,   5,   8,  23,  24,  25,   8,   2,   3,   4, 
  5,   8,  30,  31,  32,   4,   2,   3,   4,   5,   5,   2,   3,   4,   5,  16, 
  5,   2,   3,   4,   5,  33, 196,   1,   9,   3,   1,   9,   7,   1,   7,   4, 
  8,   7,   3,   9,   9,  10,   1,   9,  11,   1,   9,  12,   1,   9,  13,   1, 
  9,  14,   1,   9,   8,   1,   9,  15,   1,   7,   3,  19,   7,   3,  20,   7, 
  3,  21,   7,   3,  22,   7,   3,  23,   7,   3,  24,   7,   3,  25,   7,   3, 
 11,   7,   3,  26,   7,   3,  27,   7,   3,  10,   7,   3,   3,   7,   3,   7, 
  7,   3,  28,   7,   3,  29,   7,   3,  30,   7,   3,   6,   9,  32,   2,   9, 
 33,   2,   9,  34,   2,   9,  35,   2,   9,  36,   2,   9,  37,   2,   9,  38, 
  2,   9,  39,   2,   7,   3,  40,   7,   4,  49,   7,   3,  50,   7,   3,  33, 
  7,   3,  38,   7,   3,  39,   7,   3,  32,   7,   3,  36,   7,   3,  51,   7, 
  3,  34,   7,   3,  37,   7,   3,  35,   9,  53,   3,   9,  54,   3,   9,  55, 
  3,   9,  56,   3,   9,  57,   3,   9,  58,   3,   9,  59,   3,   9,  60,   3, 
  9,  61,   3,   9,  68,   3,   9,  51,   3,   9,  69,   3,   7,   4,  68,   9, 
  8,   3,   9,  70,   3,   9,   3,   3,   9,   7,   3,   9,  12,   3,   9,  13, 
  3,   9,  14,   3,   9,  71,   3,   7,   3,  53,   7,   3,  55,   7,   3,  58, 
  7,   3,  54,   7,   3,  56,   7,   3,  59,   7,   3,  72,   7,   3,  61,   7, 
  3,  57,   7,   3,  71,   7,   3,  60,   7,   3,  73,   7,   3,  74,   7,   3, 
 70,   7,   3,  75,   7,   4,  77,   7,  16,  79,  29,  86,   1,   4,   7,   4, 
 80,  29,  86,   1,  88,   9,  77,   4,   9,  82,   4,   7,   3,  83,   7,   3, 
 84,   7,   3,  82,   7,   3,  85,   7,   3,  86,   7,   3,  87,   7,   3,  88, 
  7,   3,  89,   7,   3,  90,   7,   3,  91,   7,   3,  92,   7,   3,  93,   7, 
  3,  94,   7,   3,  95,   7,   3,  96,   7,   3,  97,   7,   3,  98,   7,   3, 
 99,   7,   3, 100,   7,   3, 102,   7,   3, 104,   7,   3, 105,   7,   4, 107, 
  7,   3, 109,   7,   3, 110,   7,   3, 111,   7,   3, 112,   7,   4, 113,   9, 
  3,   5,   9,   7,   5,   9, 115,   5,   9, 116,   5,   9,   8,   5,   7,   4, 
117,   9, 118,   5,   9,  29,   5,   9, 117,   5,   9,  12,   5,   9, 119,   5, 
  9, 120,   5,   9, 121,   5,   9, 124,   5,   9, 125,   5,   7,   3, 126,   7, 
  3, 127,   7,   3, 118,   7,   3, 115,   7,   3, 128,   1,   7,   3, 129,   1, 
  7,   3, 121,   7,   3, 130,   1,   7,   3, 131,   1,   7,   3, 125,   7,   3, 
124,   7,   3, 132,   1,   7,   3, 133,   1,   7,   3, 134,   1,   7,   3, 135, 
  1,   7,   3, 136,   1,   7,   3, 116,   7,   3, 137,   1,   7,   3, 138,   1, 
  7,   3, 139,   1,   7,   3, 141,   1,   7,   3, 142,   1,   7,   3, 143,   1, 
  7,   3, 144,   1,   7,   3, 145,   1,   7,   3, 146,   1,   7,   3, 147,   1, 
  7,   3, 148,   1,   7,   4, 149,   1,   7,   3, 151,   1,   7,   3, 152,   1, 
  7,   3, 153,   1,   7,   4, 154,   1,   7,   3, 156,   1,   7,   3, 157,   1, 
  7,   3, 158,   1,   9,  10,   6,   9,  11,   6,   9,   3,   6,   9,   7,   6, 
  9, 159,   1,   6,   9,  12,   6,   9, 160,   1,   6,   9, 161,   1,   6,   9, 
 80,   6,   9,  15,   6,   7,   3, 164,   1,   7,   3, 165,   1,   7,   3, 166, 
  1,   7,   3, 167,   1,   7,   3, 168,   1,   7,   3, 169,   1,   7,   3, 170, 
  1,   7,   3, 171,   1,   7,   3, 172,   1,   7,   3, 161,   1,   7,   3, 173, 
  1,   7,   3, 159,   1,   9,   6,   7,   9,   6,   8,   9,   6,   9, 142,   1, 
  0,   0,   2,   0,   3,   3,   3,   3,   4,   2,   0,   2,   4,   3,   3,   2, 
  0,   2,   3,   4,   4,   2,   0,   2,   0,   4,   4,   2,   8,   2,   1,   3, 
  1,   3,   1,   3,   3,   2,   0,   0,   4,   2,   0,   0,  12,   2,   0,   1, 
 13,   4,   2,   0,   1,   3,   3,   2,   0,   2,  13,   4,   4,   2,   0,   0, 
  3,   2,   0,   1,  14,   3,   2,   0,   0,   0,   2,   0,   8,   0,   4,   4, 
  4,   4,   4,   4,   4,   4,   2,   8,   8,   2,   3,   2,   3,   2,   3,   2, 
  3,   1,   3,   1,   3,   1,   3,   1,   3,   0,  37,   2,   0,   1,  13,  37, 
  2,   0,   0,  12,   2,   0,   1,  13,  38,   2,   0,   0,   0,   2,   0,   6, 
  0,   4,   4,   4,   4,   4,   4,   2,   8,   6,   2,   3,   1,   3,   1,   3, 
  2,   3,   1,   3,   1,   3,   5,  13,   4,   4,   4,   4,   4,   2,   8,   3, 
  1,   3,   1,   3,   1,   3,   0,  12,   2,   0,   2,  13,   4,   4,   2,   0, 
  2,  13,   4,   4,   2,   0,   1,  13,  61,   2,   0,   0,  13,   2,   0,   1, 
  3,   3,   2,   0,   1,  13,   4,   2,   0,   1,   3,   3,   2,   0,   0,  61, 
  2,   0,   0,  13,   2,   0,   5,  13,   4,   4,   4,   4,   4,   2,   8,   3, 
  1,   3,   1,   3,   1,   3,   0,   0,   2,   0,   3,  85,  85,  85,   4,   2, 
 32,   1,   0,  87,   2,   8,   1,  12,  12,   0,  13,   2,  32,   3,  13,   4, 
  4,   4,   2,  32,   1,  13,  87,   2,  32,   1,  88,  88,   2,  32,   0,  88, 
  2,  32,   3,  13,  88,  88,  88,   2,  40,   2,  12,  12,  12,  12,   2,  13, 
 87,  87,   2,  32,   3,  13,   4,  88,  88,   2,  40,   1,  12,  12,   1,  13, 
 85,   2,  32,   1,  88,  88,   2,  32,   3,  13,   4,   4,   4,   2,  32,   1, 
 89,  12,   2,  40,   1,  81,   1,   0,  87,   2,  32,   2,  13,  85,   4,   2, 
 32,   0,   4,   2,  32,   0,  14,   2,  32,   3,  13,   4,   4,   4,   2,  32, 
  3,  13,   4,  88,  88,   2,  40,   1,  12,  12,   1,  13,  88,   2,  32,   1, 
 13,  85,   2,  32,   3,  13,   4,   4,   4,   2,  32,   0,  85,   2,   0,   0, 
 13,   2,  32,   2,  14,  89,  12,   2,  40,   1,  81,   1,   0,   0,   2,   0, 
  0,   0,   2,   0,   0,   0,   2,   0,   0,   0,   2,   0,   0,   3,   2,  32, 
  0,  85,   2,  32,   0,   4,   2,  32,   1,   0,   3,   2,  32,   0,   4,   2, 
 32,   1,  13,   4,   2,  32,   1,  13,   4,   2,  32,   0,   0,   2,   0,   4, 
  0,   4,   4,   4,   4,   2,   8,   4,   1,   3,   1,   3,   1,   3,   1,   3, 
  1,  14,   3,   2,   0,   0,   3,   2,   0,   1,  13,   3,   2,   0,   0,  14, 
  2,   0,   0,   4,   2,   0,   1,  13,   3,   2,   0,   0,  13,   2,   0,   1, 
 13,   4,   2,   0,   1, 125, 125,   2,   0,   1,  13,   4,   2,   0,   2,  13, 
  4,   4,   2,   0,   0,   4,   2,   0,   1,  13,   4,   2,   0,   1,  14, 125, 
  2,   0,   1, 125, 125,   2,   0,   0,   4,   2,   0,   0, 125,   2,   0,   2, 
 13,   4,   4,   2,   0,   1,  13,   3,   2,   0,   1,  14, 125,   2,   0,   1, 
 13,   4,   2,   0,   0,   4,   2,   0,   0,  12,   2,   0,   2,  14,   4,   4, 
  2,   0,   0,   3,   2,   0,   1,  14, 125,   2,   0,   0,   3,   2,   0,   1, 
 13,   3,   2,   0,   1,  13,   3,   2,   0,   0,   0,   2,   0,   1,   0,  28, 
  2,   0,   0,  61,   2,  32,   1,  13,  61,   2,  32,   1,   0,  85,   2,  32, 
  0,  38,   2,  32,   0, 119,   2,  32,   0,  61,   2,  32,   0,  85,   2,  32, 
  1,  85,  28,   2,  32,   1,  13, 119,   2,  32,   0,  38,   2,  32,   1,  13, 
 38,   2,  32,   0, 125,   2,  32,   0,   0,   2,   0,   5,  85,   4,  85,  88, 
 88,  88,   2,  40,   2,  12,  12,  12,  12,   2,  88,  85,  88,   2,  32,   4, 
 13,  85,  87,  87,  87,   2,  32,   0,   0,   2,   0,   0,   0,   2,   0,   2, 
  4,  88,  88,   2,   0,   2,   4,  88,  88,   2,   0,   4,   0,   4,   4,   4, 
  4,   2,   8,   4,   1,   3,   1,   3,   1,   3,   1,   3,   0,  13,   2,   0, 
  0,   4,   2,   0,   0,  13,   2,   0,   1,  88,  88,   2,   0,   1,   4,  88, 
  2,   0,   3,  14,  88,   4,  14,   2,   8,   1,  10,  10,   1,  13,   4,   2, 
  0,   1,  13,  88,   2,   0,   0,  12,   2,   0,   0,   4,   2,   0,   1,  88, 
 88,   2,   0,   1,  13,  88,   2,   0,   1,  88,  88,   2,   0,   0,   4,   2, 
  0,   0,  88,   2,   0,   2,  14,  88,  14,   2,   8,   1,  10,  10,   0,   0, 
  2,   0,   4, 175,   1,   3, 176,   1, 178,   1, 180,   1, 177,   1, 179,   1, 
181,   1, 175,   1,   3, 176,   1, 178,   1, 180,   1, 182,   1, 183,   1, 181, 
  1, 175,   1,   3, 176,   1, 178,   1, 180,   1, 184,   1, 185,   1, 181,   1, 
175,   1,   3, 176,   1, 178,   1, 180,   1, 186,   1, 187,   1, 181,   1,  10, 
  3,  28,   9,   6,   0,   4,  10,  18,   1,   0,   5,  19,   2,   0,   6,  20, 
  1,   0,   7,  21,   1,   0,   8,  22,   1,   0,   9,  23,   0,   0,   4,   0, 
 24,   0,   0,   4,   0,  25,   1,   0,  10,  26,   1,   0,  11,  27,   1,   0, 
 12,  38,  28,   9,  10,   0,  14,  12,  39,   2,   0,  15,  39,   3,   0,  16, 
 40,   0,   0,   4,   0,  41,   0,   0,   4,   0,  20,   1,   0,  17,  42,   0, 
  0,   4,   0,  43,   0,   0,   4,   0,  44,   0,   0,   4,   0,  45,   1,   0, 
 18,  46,   0,   0,   4,   0,  47,   0,   0,   4,   0,  48,   0,   0,   4,   0, 
 61,  28,   9,  13,   0,  20,  18,  70,   0,   0,   4,   0,  71,   0,   0,   4, 
  0,  72,   0,   0,   4,   0,  73,   0,   0,   4,   0,  74,   0,   0,   4,   0, 
 20,   1,   0,  22,  75,   1,   0,  31,  76,   1,   0,  23,  77,   1,   0,  24, 
 78,   0,   0,   4,   0,  45,   1,   0,  25,  26,   1,   0,  30,  79,   1,   0, 
 21,  80,   1,   0,  28,  81,   1,   0,  27,  82,   1,   0,  26,  83,   1,   0, 
 29,  84,   1,   0,  32,  85,  28,   9,  17,   0,  35,  24,  92,   3,   0,  54, 
 93,   1,   0,  41,  94,   3,   0,  38,  75,   1,   0,  58,  92,   2,   0,  40, 
 95,   1,   0,  37,  96,   1,   0,  42,  97,   1,   0,  43,  98,   1,   0,  44, 
 99,   1,   0,  45, 100,   1,   0,  46, 101,   1,   0,  47,  94,   2,   0,  48, 
102,   1,   0,  56, 103,   2,   0,  50,  82,   1,   0,  51, 104,   1,   0,  39, 
105,   1,   0,  53, 106,   1,   0,  36, 107,   1,   0,  55, 108,   1,   0,  49, 
 26,   1,   0,  57, 109,   1,   0,  52, 110,   1,   0,  59, 114,  28,  11,  20, 
  0,  61,   0, 119,  28,   9,  22,   0,  63,   7, 115,   2,   0,  64, 116,   3, 
  0,  70, 117,   2,   0,  66, 115,   3,   0,  67, 116,   2,   0,  68, 117,   3, 
  0,  69, 118,   1,   0,  65, 125,  28,   9,  24,   0,  72,  33, 135,   1,   2, 
  0,  97, 136,   1,   2,   0,  74, 136,   1,   3,   0,  75, 137,   1,   1,   0, 
 76, 138,   1,   0,   0,   4,   0, 139,   1,   2,   0,  77, 140,   1,   1,   0, 
 78, 141,   1,   1,   0,  79, 142,   1,   1,   0,  81, 143,   1,   1,   0,  87, 
 25,   1,   0,  83, 139,   1,   3,   0,  80, 144,   1,   3,   0,  85, 145,   1, 
  3,   0,  82, 145,   1,   2,   0,  88,  26,   1,   0,  89, 146,   1,   1,   0, 
 90, 135,   1,   3,   0,  91, 147,   1,   1,   0,  92, 148,   1,   2,   0,  84, 
149,   1,   3,   0, 101, 150,   1,   1,   0,  96, 151,   1,   0,   0,   4,   0, 
148,   1,   3,   0,  93, 144,   1,   2,   0,  94,  20,   1,   0,  95, 152,   1, 
  1,   0,  73, 153,   1,   1,   0,  98,  23,   0,   0,   4,   0,  24,   0,   0, 
  4,   0, 149,   1,   2,   0,  99, 154,   1,   1,   0, 100,  27,   1,   0,  86, 
163,   1,  28,   9,  27,   0, 103,  12, 155,   1,   2,   0, 104, 155,   1,   3, 
  0, 105, 156,   1,   3,   0, 106, 157,   1,   2,   0, 107, 158,   1,   2,   0, 
108, 159,   1,   2,   0, 109, 156,   1,   2,   0, 110, 160,   1,   1,   0, 111, 
158,   1,   3,   0, 112, 161,   1,   2,   0, 113, 157,   1,   3,   0, 114, 162, 
  1,   2,   0, 115, 167,   1,  28,   9,  29,   0, 120,   0,  88,  28,   9,  31, 
  0, 124,  20,  24,   0,   0,   4,   0, 182,   1,   2,   0, 126, 183,   1,   1, 
  0, 127, 184,   1,   1,   0, 131,   1, 185,   1,   1,   0, 129,   1, 186,   1, 
  1,   0, 130,   1,  18,   1,   0, 128,   1, 187,   1,   1,   0, 132,   1,  20, 
  1,   0, 133,   1,  19,   2,   0, 134,   1, 188,   1,   1,   0, 135,   1, 189, 
  1,   1,   0, 136,   1, 190,   1,   0,   0,   4,   0,  23,   0,   0,   4,   0, 
191,   1,   1,   0, 125, 192,   1,   0,   0,   4,   0,  22,   1,   0, 137,   1, 
 21,   1,   0, 138,   1,  26,   1,   0, 139,   1,  27,   1,   0, 140,   1,   0, 
  3,  15,  17,   3,   1,  16,  17,   4,   2,  17,  17,   5,   3,  13,   0,  19, 
  0,  33,   1,  15,  17,   3,  34,  60,   3, 111,   6,   1,  12, 103,   1, 112, 
  6,   2,  12,  81,   1, 113,   6,   3,  12, 106,   1,  62,   0,  71,   0, 102, 
  0, 116,   3, 164,   1,  17,   4, 118, 165,   1,  17,   3, 117, 166,   1,  17, 
  5, 119, 121,   5, 181,   1,  17,   4, 123,  16,  17,   3, 122, 168,   1,   6, 
  1,  88,   0, 169,   1,   6,   2,  88,   0, 170,   1,   6,   3,  88,   0,   1, 
141,   1,  10,  85,  68,   4,   3,   1,   0,  88,   4,  10,   9, 114,   4,   5, 
  4, 163,   1,  68,   8,   7,   1,   1, 125,   4,   7,   6,  38,   4,   2,   1, 
  3,   4,   1,   0, 119,  68,   6,   5,   1,   2, 167,   1,  68,   9,   8,   1, 
  3,  61,   4,   3,   2,  96,   0,   1,   1,   3,   4,   3, 208,  48,  71,   0, 
  0,   1,   6,   4,   3,   4,  32, 208,  48, 208, 210, 102,   1, 211, 209, 102, 
  1, 210, 102,   1, 161, 162, 160, 210, 102,   2, 211, 209, 102,   2, 210, 102, 
  2, 161, 162, 160,  66,   2,  72,   0,   0,   2,   2,   3,   3,   4,  10, 208, 
 48, 209, 210,  70,   5,   1, 102,   6,  72,   0,   0,   3,   5,   3,   3,   4, 
 26, 208,  48, 208, 209,  93,   7, 102,   7, 210,  70,   8,   1, 162, 209,  93, 
  7, 102,   7, 210,  70,   9,   1, 162,  66,   2,  72,   0,   0,   4,   2,   3, 
  4,   5,  14, 208,  48, 208,  73,   0, 208, 209, 104,   1, 208, 210, 104,   2, 
 71,   0,   0,   5,   4,   2,   4,   5,  22, 208,  48,  93,  10, 208, 102,   1, 
209, 102,   1, 160, 208, 102,   2, 209, 102,   2, 160,  74,  10,   2,  72,   0, 
  0,   6,   4,   1,   4,   5,  25, 208,  48,  93,   7, 102,   7, 208, 102,   1, 
208, 102,   1, 162, 208, 102,   2, 208, 102,   2, 162, 160,  70,  11,   1,  72, 
  0,   0,   7,   2,   1,   4,   5,  19, 208,  48,  44,  16, 208, 102,   1, 160, 
 44,  17, 160, 208, 102,   2, 160,  44,  18, 160,  72,   0,   0,   8,   3,   3, 
  4,   5,  36, 208,  48, 208, 102,   6, 130, 214, 210,  36,   0,  14,  21,   0, 
  0, 209, 210, 163, 130, 214, 208, 208, 102,   1, 210, 162,  97,   1, 208, 208, 
102,   2, 210, 162,  97,   2,  71,   0,   0,   9,   4,   2,   4,   5,  22, 208, 
 48,  93,  10, 208, 102,   1, 209, 102,   1, 161, 208, 102,   2, 209, 102,   2, 
161,  74,  10,   2,  72,   0,   0,  10,   3,   3,   4,   5,  19, 208,  48, 208, 
208, 102,   1, 209, 160,  97,   1, 208, 208, 102,   2, 210, 160,  97,   2,  71, 
  0,   0,  11,   3,   1,   4,   5,  14, 208,  48,  93,  10, 208, 102,   1, 208, 
102,   2,  74,  10,   2,  72,   0,   0,  12,   2,   2,   4,   5,  20, 208,  48, 
209, 102,   1, 208, 102,   1,  20,   0,   0,   0, 209, 102,   2, 208, 102,   2, 
171,  72,   0,   0,  13,   1,   1,   3,   4,   3, 208,  48,  71,   0,   0,  14, 
  2,   9,   4,   5,  43, 208,  48, 208,  73,   0, 208, 209, 104,  29, 208, 210, 
104,  30, 208, 211, 104,  31, 208,  98,   4, 104,  32, 208,  98,   5, 104,  33, 
208,  98,   6, 104,  34, 208,  98,   7, 104,  35, 208,  98,   8, 104,  36,  71, 
  0,   0,  15,   3,   1,   4,   5,  20, 208,  48, 208, 102,  33,  36,  16, 165, 
208, 102,  34,  36,   8, 165, 169, 208, 102,  35, 169,  72,   0,   0,  16,   3, 
  3,   4,   5,  56, 208,  48,  36,   0, 214,  36,   0, 115, 214, 208,  36,   0, 
 97,  31, 210, 115, 214, 208, 210,  97,  30, 208, 210,  97,  29, 208, 209,  36, 
 16, 166,  37, 255,   1, 168,  97,  33, 208, 209,  36,   8, 166,  37, 255,   1, 
168,  97,  34, 208, 209,  37, 255,   1, 168,  97,  35,  71,   0,   0,  17,   2, 
  1,   4,   5,  61, 208,  48,  44,  41, 208, 102,  29, 160,  44,  42, 160, 208, 
102,  30, 160,  44,  43, 160, 208, 102,  31, 160,  44,  44, 160, 208, 102,  32, 
160,  44,  45, 160, 208, 102,  33, 160,  44,  46, 160, 208, 102,  34, 160,  44, 
 47, 160, 208, 102,  35, 160,  44,  48, 160, 208, 102,  36, 160,  44,  18, 160, 
 72,   0,   0,  18,   4,   2,   4,   5,  99, 208,  48, 208, 208, 102,  36, 208, 
102,  32, 209, 102,  36, 162, 160,  97,  36, 208, 208, 102,  32, 209, 102,  32, 
162,  97,  32, 208, 208, 102,  33, 208, 102,  29, 209, 102,  33, 162, 160,  97, 
 33, 208, 208, 102,  29, 209, 102,  29, 162,  97,  29, 208, 208, 102,  34, 208, 
102,  30, 209, 102,  34, 162, 160,  97,  34, 208, 208, 102,  30, 209, 102,  30, 
162,  97,  30, 208, 208, 102,  35, 208, 102,  31, 209, 102,  35, 162, 160,  97, 
 35, 208, 208, 102,  31, 209, 102,  31, 162,  97,  31,  71,   0,   0,  19,   1, 
  1,   3,   4,   3, 208,  48,  71,   0,   0,  20,   2,   7,   4,   5,  33, 208, 
 48, 208,  73,   0, 208, 209, 104,  49, 208, 210, 104,  50, 208, 211, 104,  51, 
208,  98,   4, 104,  52, 208,  98,   5, 104,  53, 208,  98,   6, 104,  54,  71, 
  0,   0,  21,   3,   6,   4,   5,  31, 208,  48, 208,  70,  55,   0,  41, 208, 
211,  70,  56,   1,  41, 208, 209, 210,  70,  57,   2,  41, 208,  98,   4,  97, 
 53, 208,  98,   5,  97,  54,  71,   0,   0,  22,   2,   1,   4,   5,  47, 208, 
 48,  44,  62, 208, 102,  49, 160,  44,  63, 160, 208, 102,  50, 160,  44,  64, 
160, 208, 102,  51, 160,  44,  65, 160, 208, 102,  52, 160,  44,  66, 160, 208, 
102,  53, 160,  44,  67, 160, 208, 102,  54, 160,  44,  18, 160,  72,   0,   0, 
 23,   3,   3,   4,   5,  19, 208,  48, 208, 208, 102,  53, 209, 160,  97,  53, 
208, 208, 102,  54, 210, 160,  97,  54,  71,   0,   0,  24,   7,   4,   4,   5, 
 26, 208,  48,  93,  58, 209,  36,   0,  36,   0, 210,  36,   0,  36,   0,  74, 
 58,   6, 130, 215, 208, 211,  70,  59,   1,  41,  71,   0,   0,  25,   4,   9, 
  4,   5, 130,   2, 208,  48,  93,  60, 102,  60, 117, 214,  93,  60, 102,  60, 
117, 215,  93,  60, 102,  60, 117,  99,   4,  93,  60, 102,  60, 117,  99,   5, 
 93,  60, 102,  60, 117,  99,   6,  93,  60, 102,  60, 117,  99,   7, 208, 102, 
 49, 209, 102,  49, 162, 117, 214, 208, 102,  52, 209, 102,  52, 162, 117,  99, 
  5,  36,   0, 117,  99,   8,  36,   0, 117,  99,   4,  98,   8, 117, 215, 208, 
102,  53, 209, 102,  49, 162, 209, 102,  53, 160, 117,  99,   6, 208, 102,  54, 
209, 102,  52, 162, 209, 102,  54, 160, 117,  99,   7, 208, 102,  50,  36,   0, 
 20,   0,   0,   0, 208, 102,  51,  36,   0,  20,   0,   0,   0, 209, 102,  50, 
 36,   0,  20,   0,   0,   0, 209, 102,  51,  36,   0,  19,  90,   0,   0, 210, 
208, 102,  50, 209, 102,  51, 162, 160, 117, 214,  98,   5, 208, 102,  51, 209, 
102,  50, 162, 160, 117,  99,   5, 211, 208, 102,  49, 209, 102,  50, 162, 208, 
102,  50, 209, 102,  52, 162, 160, 160, 117, 215,  98,   4, 208, 102,  51, 209, 
102,  49, 162, 208, 102,  52, 209, 102,  51, 162, 160, 160, 117,  99,   4,  98, 
  6, 208, 102,  54, 209, 102,  51, 162, 160, 117,  99,   6,  98,   7, 208, 102, 
 53, 209, 102,  50, 162, 160, 117,  99,   7, 208, 210,  97,  49, 208, 211,  97, 
 50, 208,  98,   4,  97,  51, 208,  98,   5,  97,  52, 208,  98,   6,  97,  53, 
208,  98,   7,  97,  54,  71,   0,   0,  26,   4,   8,   4,   5, 240,   1, 208, 
 48,  40,  99,   7,  93,  60, 102,  60, 117, 213,  93,  60, 102,  60, 117, 214, 
 93,  60, 102,  60, 117, 215,  93,  60, 102,  60, 117,  99,   4,  93,  60, 102, 
 60, 117,  99,   5,  32, 128,   3,  99,   6, 208, 102,  50,  36,   0,  20,   0, 
  0,   0, 208, 102,  51,  36,   0,  20,  59,   0,   0, 208,  36,   1, 208, 102, 
 49, 163,  97,  49, 208,  36,   1, 208, 102,  52, 163,  97,  52,  36,   0, 117, 
 99,   7, 208,  36,   0,  97,  51, 208,  98,   7,  97,  50, 208, 208, 102,  49, 
144, 208, 102,  53, 162,  97,  53, 208, 208, 102,  52, 144, 208, 102,  54, 162, 
 97,  54,  16, 120,   0,   0, 208, 102,  49, 117, 213, 208, 102,  50, 117, 214, 
208, 102,  51, 117, 215, 208, 102,  52, 117,  99,   4, 209,  98,   4, 162, 210, 
211, 162, 161, 117,  99,   5,  98,   5,  36,   0,  20,   6,   0,   0, 208,  70, 
 55,   0,  41,  71,  36,   1,  98,   5, 163, 117,  99,   5, 208,  98,   4,  98, 
  5, 162,  97,  49, 208, 210, 144,  98,   5, 162,  97,  50, 208, 211, 144,  98, 
  5, 162,  97,  51, 208, 209,  98,   5, 162,  97,  52, 208,  93,  62, 208, 102, 
 53, 208, 102,  54,  74,  62,   2,  70,  63,   1, 128,   3,  99,   6, 208,  98, 
  6, 102,  64, 144,  97,  53, 208,  98,   6, 102,  65, 144,  97,  54,  71,   0, 
  0,  27,   5,   2,   4,   5,  46, 208,  48,  93,  62, 208, 102,  49, 209, 102, 
 64, 162, 208, 102,  51, 209, 102,  65, 162, 160, 208, 102,  53, 160, 208, 102, 
 52, 209, 102,  65, 162, 208, 102,  50, 209, 102,  64, 162, 160, 208, 102,  54, 
160,  74,  62,   2,  72,   0,   0,  28,   7,   5,   4,   5,  47, 208,  48,  93, 
 66, 102,  66, 209,  70,  67,   1, 130, 214,  93,  66, 102,  66, 209,  70,  68, 
  1, 130, 215,  93,  58, 210, 211, 211, 144, 210,  36,   0,  36,   0,  74,  58, 
  6, 130,  99,   4, 208,  98,   4,  70,  59,   1,  41,  71,   0,   0,  29,   5, 
  2,   4,   5,  38, 208,  48,  93,  62, 208, 102,  49, 209, 102,  64, 162, 208, 
102,  51, 209, 102,  65, 162, 160, 208, 102,  52, 209, 102,  65, 162, 208, 102, 
 50, 209, 102,  64, 162, 160,  74,  62,   2,  72,   0,   0,  30,   7,   1,   4, 
  5,  26, 208,  48,  93,  58, 208, 102,  49, 208, 102,  50, 208, 102,  51, 208, 
102,  52, 208, 102,  53, 208, 102,  54,  74,  58,   6,  72,   0,   0,  31,   2, 
  4,   4,   5,  42, 208,  48,  36,   1, 115, 213, 208,  36,   1,  97,  52, 208, 
209,  97,  49,  36,   0, 117, 214, 208,  36,   0,  97,  51, 208, 210,  97,  50, 
 36,   0, 117, 215, 208,  36,   0,  97,  54, 208, 211,  97,  53,  71,   0,   0, 
 32,   8,   6,   4,   5,  31, 208,  48, 208, 209,  47,   1, 163, 210,  47,   1, 
163, 211,  98,   4, 209,  36,   2, 163, 160,  98,   5, 210,  36,   2, 163, 160, 
 70,  69,   5,  41,  71,   0,   0,  33,   1,   1,   3,   4,   3, 208,  48,  71, 
  0,   0,  35,   1,   2,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0, 
 57,   2,   1,   4,   5,  11, 208,  48,  93,  90, 208, 102,  91,  74,  90,   1, 
 72,   0,   0,  60,   2,   1,   3,   4,  21, 208,  48,  94, 111,  44, 103, 104, 
111,  94, 112,  44,  81, 104, 112,  94, 113,  44, 106, 104, 113,  71,   0,   0, 
 61,   1,   1,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0,  62,   1, 
  1,   3,   4,   3, 208,  48,  71,   0,   0,  63,   1,   1,   4,   5,   6, 208, 
 48, 208,  73,   0,  71,   0,   0,  71,   1,   1,   3,   4,   3, 208,  48,  71, 
  0,   0,  72,   2,   5,   4,   5,  23, 208,  48, 208,  73,   0, 208, 209, 104, 
120, 208, 210, 104, 121, 208, 211, 104, 122, 208,  98,   4, 104, 123,  71,   0, 
  0,  73,   3,   2,   4,   5,  48, 208,  48, 209, 102, 120, 208, 102, 120,  15, 
  0,   0,   0, 209, 102, 120, 208, 102, 120, 208, 102, 122, 160,  12,   0,   0, 
  0, 209, 102, 121, 208, 102, 121,  15,   0,   0,   0, 209, 102, 121, 208, 102, 
121, 208, 102, 123, 160, 173,  72,   0,   0,  74,   3,   1,   4,   5,  14, 208, 
 48,  93, 124, 208, 102, 122, 208, 102, 123,  74, 124,   2,  72,   0,   0,  75, 
  2,   2,   4,   5,  15, 208,  48, 208, 209, 102, 120,  97, 122, 208, 209, 102, 
121,  97, 123,  71,   0,   0,  76,   2,   1,   4,   5,  18, 208,  48, 208, 102, 
122,  36,   0,  14,   0,   0,   0, 208, 102, 123,  36,   0, 174,  72,   0,   0, 
 77,   1,   1,   4,   5,   6, 208,  48, 208, 102, 120,  72,   0,   0,  78,   4, 
  2,   4,   5,  49, 208,  48, 208, 208, 102, 120, 209, 102, 120, 161,  97, 120, 
208, 208, 102, 122,  36,   2, 209, 102, 120, 162, 160,  97, 122, 208, 208, 102, 
121, 209, 102, 121, 161,  97, 121, 208, 208, 102, 123,  36,   2, 209, 102, 121, 
162, 160,  97, 123,  71,   0,   0,  79,   2,   1,   4,   5,  23, 208,  48, 208, 
 36,   0,  97, 120, 208,  36,   0,  97, 121, 208,  36,   0,  97, 122, 208,  36, 
  0,  97, 123,  71,   0,   0,  80,   4,   2,   4,   5,  19, 208,  48, 208, 208, 
102, 122, 208, 102, 120, 209, 161, 160,  97, 122, 208, 209,  97, 120,  71,   0, 
  0,  81,   5,   3,   4,   5, 144,   1, 208,  48,  32, 128, 125, 214, 208,  70, 
126,   0,  18,   5,   0,   0, 209,  70, 127,   0,  72, 209,  70, 126,   0,  18, 
  5,   0,   0, 208,  70, 127,   0,  72,  93, 128,   1,  74, 128,   1,   0, 128, 
125, 214, 210,  93, 129,   1, 102, 129,   1, 208, 102, 120, 209, 102, 120,  70, 
130,   1,   2,  97, 120, 210,  93, 129,   1, 102, 129,   1, 208, 102, 121, 209, 
102, 121,  70, 130,   1,   2,  97, 121, 210,  93, 129,   1, 102, 129,   1, 208, 
102, 120, 208, 102, 122, 160, 209, 102, 120, 209, 102, 122, 160,  70, 131,   1, 
  2, 210, 102, 120, 161,  97, 122, 210,  93, 129,   1, 102, 129,   1, 208, 102, 
121, 208, 102, 123, 160, 209, 102, 121, 209, 102, 123, 160,  70, 131,   1,   2, 
210, 102, 121, 161,  97, 123, 210,  72,   0,   0,  82,   3,   2,   4,   5,  11, 
208,  48, 208, 209, 208, 102, 120, 161,  97, 122,  71,   0,   0,  83,   3,   3, 
  4,   5,  19, 208,  48, 208, 208, 102, 120, 209, 160,  97, 120, 208, 208, 102, 
121, 210, 160,  97, 121,  71,   0,   0,  84,   1,   1,   4,   5,   6, 208,  48, 
208, 102, 121,  72,   0,   0,  85,   3,   2,   4,   5,  11, 208,  48, 208, 209, 
208, 102, 121, 161,  97, 123,  71,   0,   0,  86,   2,   2,   4,   5,  40, 208, 
 48, 209, 102, 120, 208, 102, 120,  20,   0,   0,   0, 209, 102, 121, 208, 102, 
121,  20,   0,   0,   0, 209, 102, 122, 208, 102, 122,  20,   0,   0,   0, 209, 
102, 123, 208, 102, 123, 171,  72,   0,   0,  87,   5,   3,   4,   5, 167,   1, 
208,  48,  93, 128,   1,  74, 128,   1,   0, 130, 214, 208,  70, 126,   0, 150, 
 18,   5,   0,   0, 208,  70, 126,   0,  41, 209,  70, 126,   0,  18,   8,   0, 
  0, 210,  70, 132,   1,   0,  41, 210,  72, 210,  93, 129,   1, 102, 129,   1, 
208, 102, 120, 209, 102, 120,  70, 131,   1,   2,  97, 120, 210,  93, 129,   1, 
102, 129,   1, 208, 102, 121, 209, 102, 121,  70, 131,   1,   2,  97, 121, 210, 
 93, 129,   1, 102, 129,   1, 208, 102, 120, 208, 102, 122, 160, 209, 102, 120, 
209, 102, 122, 160,  70, 130,   1,   2, 210, 102, 120, 161,  97, 122, 210,  93, 
129,   1, 102, 129,   1, 208, 102, 121, 208, 102, 123, 160, 209, 102, 121, 209, 
102, 123, 160,  70, 130,   1,   2, 210, 102, 121, 161,  97, 123, 210, 102, 122, 
 36,   0,  14,   0,   0,   0, 210, 102, 123,  36,   0,  13,   6,   0,   0, 210, 
 70, 132,   1,   0,  41, 210,  72,   0,   0,  88,   2,   1,   4,   5,  10, 208, 
 48, 208, 102, 120, 208, 102, 122, 160,  72,   0,   0,  89,   5,   1,   4,   5, 
 22, 208,  48,  93, 128,   1, 208, 102, 120, 208, 102, 121, 208, 102, 122, 208, 
102, 123,  74, 128,   1,   4,  72,   0,   0,  90,   4,   3,   4,   5,  41, 208, 
 48, 208, 208, 102, 120, 209, 161,  97, 120, 208, 208, 102, 122,  36,   2, 209, 
162, 160,  97, 122, 208, 208, 102, 121, 210, 161,  97, 121, 208, 208, 102, 123, 
 36,   2, 210, 162, 160,  97, 123,  71,   0,   0,  91,   3,   2,   4,   5,  23, 
208,  48, 208, 209, 102, 120, 208, 102, 120, 161,  97, 122, 208, 209, 102, 121, 
208, 102, 121, 161,  97, 123,  71,   0,   0,  92,   2,   6,   4,   5, 106, 208, 
 48, 209, 102, 120, 209, 102, 122, 160, 130, 214, 209, 102, 121, 209, 102, 123, 
160, 130, 215, 208, 102, 120, 208, 102, 122, 160, 130,  99,   4, 208, 102, 121, 
208, 102, 123, 160, 130,  99,   5, 209, 102, 120, 208, 102, 120,  15,   0,   0, 
  0, 209, 102, 120,  98,   4,  12,   0,   0,   0, 209, 102, 121, 208, 102, 121, 
 15,   0,   0,   0, 209, 102, 121,  98,   5,  12,   0,   0,   0, 210, 208, 102, 
120,  14,   0,   0,   0, 210,  98,   4,  13,   0,   0,   0, 211, 208, 102, 121, 
 14,   0,   0,   0, 211,  98,   5, 174,  72,   0,   0,  93,   4,   2,   4,   5, 
 19, 208,  48, 208, 208, 102, 123, 208, 102, 121, 209, 161, 160,  97, 123, 208, 
209,  97, 121,  71,   0,   0,  94,   2,   1,   4,   5,  10, 208,  48, 208, 102, 
121, 208, 102, 123, 160,  72,   0,   0,  95,   2,   1,   4,   5,  33, 208,  48, 
 44,  16, 208, 102, 120, 160,  44,  17, 160, 208, 102, 121, 160,  44, 122, 160, 
208, 102, 122, 160,  44, 123, 160, 208, 102, 123, 160,  44,  18, 160,  72,   0, 
  0,  96,   3,   3,   4,   5,  40, 208,  48, 209, 208, 102, 120,  15,   0,   0, 
  0, 209, 208, 102, 120, 208, 102, 122, 160,  12,   0,   0,   0, 210, 208, 102, 
121,  15,   0,   0,   0, 210, 208, 102, 121, 208, 102, 123, 160, 173,  72,   0, 
  0,  97,   3,   1,   4,   5,  16, 208,  48,  93, 124, 208, 102, 133,   1, 208, 
102, 134,   1,  74, 124,   2,  72,   0,   0,  98,   4,   6,   4,   5, 140,   1, 
208,  48, 208,  70, 126,   0, 150,  18,   5,   0,   0, 208,  70, 126,   0,  41, 
209,  70, 126,   0,  18,   2,   0,   0,  39,  72,  93, 129,   1, 102, 129,   1, 
208, 102, 120, 209, 102, 120,  70, 131,   1,   2, 130, 214,  93, 129,   1, 102, 
129,   1, 208, 102, 121, 209, 102, 121,  70, 131,   1,   2, 130, 215,  93, 129, 
  1, 102, 129,   1, 208, 102, 120, 208, 102, 122, 160, 209, 102, 120, 209, 102, 
122, 160,  70, 130,   1,   2, 210, 161, 130,  99,   4,  93, 129,   1, 102, 129, 
  1, 208, 102, 121, 208, 102, 123, 160, 209, 102, 121, 209, 102, 123, 160,  70, 
130,   1,   2, 211, 161, 130,  99,   5,  98,   4,  36,   0,  14,   0,   0,   0, 
 98,   5,  36,   0,  13,   2,   0,   0,  39,  72,  38,  72,   0,   0,  99,   3, 
  1,   4,   5,  14, 208,  48,  93, 124, 208, 102, 120, 208, 102, 121,  74, 124, 
  2,  72,   0,   0, 100,   3,   2,   4,   5,  23, 208,  48, 208, 208, 102, 120, 
209, 102, 120, 160,  97, 120, 208, 208, 102, 121, 209, 102, 121, 160,  97, 121, 
 71,   0,   0, 101,   4,   2,   4,   5,  43, 208,  48, 208, 208, 102, 122, 208, 
102, 120, 209, 102, 120, 161, 160,  97, 122, 208, 208, 102, 123, 208, 102, 121, 
209, 102, 121, 161, 160,  97, 123, 208, 209, 102, 120,  97, 120, 208, 209, 102, 
121,  97, 121,  71,   0,   0, 102,   1,   1,   3,   4,   3, 208,  48,  71,   0, 
  0, 103,   1,   2,   4,   5,   6, 208,  48, 208,  73,   0,  71,   0,   0, 116, 
  1,   1,   3,   4,   3, 208,  48,  71,   0,   0, 120,   1,   1,   4,   5,   6, 
208,  48, 208,  73,   0,  71,   0,   0, 121,   5,   1,   3,   4,  48, 208,  48, 
 94, 168,   1, 208,  36,   0,  36,   0,  36,   1,  66,   3, 104, 168,   1,  94, 
169,   1, 208,  36,   0,  36,   1,  36,   0,  66,   3, 104, 169,   1,  94, 170, 
  1, 208,  36,   1,  36,   0,  36,   0,  66,   3, 104, 170,   1,  71,   0,   0, 
122,   2,   3,   3,   4,  12, 208,  48, 209, 210,  70, 171,   1,   1, 102, 172, 
  1,  72,   0,   0, 123,   4,   6,   3,   4,  65, 208,  48, 209, 102, 173,   1, 
210, 102, 173,   1, 162, 209, 102, 174,   1, 210, 102, 174,   1, 162, 160, 209, 
102, 175,   1, 210, 102, 175,   1, 162, 160, 130, 215, 209, 102, 172,   1, 130, 
 99,   4, 210, 102, 172,   1, 130,  99,   5,  93, 176,   1, 102, 176,   1, 211, 
 98,   4,  98,   5, 162, 163,  70, 177,   1,   1,  72,   0,   0, 124,   2,   5, 
  4,   5,  27, 208,  48, 208,  73,   0, 208, 209, 104, 173,   1, 208, 210, 104, 
174,   1, 208, 211, 104, 175,   1, 208,  98,   4, 104, 178,   1,  71,   0,   0, 
125,   3,   2,   4,   5,  42, 208,  48,  36,   1, 208, 102, 178,   1, 163, 130, 
213, 208, 208, 102, 173,   1, 209, 162,  97, 173,   1, 208, 208, 102, 174,   1, 
209, 162,  97, 174,   1, 208, 208, 102, 175,   1, 209, 162,  97, 175,   1,  71, 
  0,   0, 126,   3,   1,   4,   5,  32, 208,  48, 208, 102, 173,   1, 208, 102, 
173,   1, 162, 208, 102, 174,   1, 208, 102, 174,   1, 162, 160, 208, 102, 175, 
  1, 208, 102, 175,   1, 162, 160,  72,   0,   0, 127,   2,   1,   4,   5,  30, 
208,  48, 208, 208, 102, 173,   1, 144,  97, 173,   1, 208, 208, 102, 174,   1, 
144,  97, 174,   1, 208, 208, 102, 175,   1, 144,  97, 175,   1,  71,   0,   0, 
128,   1,   5,   2,   4,   5,  37, 208,  48,  93, 179,   1, 208, 102, 173,   1, 
209, 102, 173,   1, 160, 208, 102, 174,   1, 209, 102, 174,   1, 160, 208, 102, 
175,   1, 209, 102, 175,   1, 160,  74, 179,   1,   3,  72,   0,   0, 129,   1, 
  3,   2,   4,   5,  32, 208,  48, 208, 102, 173,   1, 209, 102, 173,   1, 162, 
208, 102, 174,   1, 209, 102, 174,   1, 162, 160, 208, 102, 175,   1, 209, 102, 
175,   1, 162, 160,  72,   0,   0, 130,   1,   2,   7,   4,   5, 211,   1, 208, 
 48,  33, 130,  99,   6, 208, 102, 173,   1, 209, 102, 173,   1, 161, 130,  99, 
  4,  98,   4,  36,   0, 173,  18,   8,   0,   0,  98,   4, 144, 130,  16,   3, 
  0,   0,  98,   4, 130, 130,  99,   4,  98,   4, 210, 173, 130,  99,   5,  98, 
  5, 118,  18, 153,   0,   0, 208, 102, 174,   1, 209, 102, 174,   1, 161, 130, 
 99,   4,  98,   4,  36,   0, 173,  18,   8,   0,   0,  98,   4, 144, 130,  16, 
  3,   0,   0,  98,   4, 130, 130,  99,   4,  98,   4, 210, 173, 130,  99,   5, 
 98,   5, 118,  18, 104,   0,   0, 208, 102, 175,   1, 209, 102, 175,   1, 161, 
130,  99,   4,  98,   4,  36,   0, 173,  18,   8,   0,   0,  98,   4, 144, 130, 
 16,   3,   0,   0,  98,   4, 130, 130,  99,   4,  98,   4, 210, 173, 130,  99, 
  5,  98,   5, 118,  18,   0,   0,   0, 211,  18,  50,   0,   0, 209, 102, 178, 
  1, 130,  99,   6, 208, 209, 102, 178,   1,  97, 178,   1,  98,   6, 130,  99, 
  4,  98,   4,  36,   0, 173,  18,   8,   0,   0,  98,   4, 144, 130,  16,   3, 
  0,   0,  98,   4, 130, 130,  99,   4,  98,   4, 210, 173, 130,  99,   5,  98, 
  5,  72,   0,   0, 131,   1,   3,   2,   4,   5,  33, 208,  48, 208, 208, 102, 
173,   1, 209, 162,  97, 173,   1, 208, 208, 102, 174,   1, 209, 162,  97, 174, 
  1, 208, 208, 102, 175,   1, 209, 162,  97, 175,   1,  71,   0,   0, 132,   1, 
  3,   2,   4,   5,  42, 208,  48, 208, 208, 102, 173,   1, 209, 102, 173,   1, 
161,  97, 173,   1, 208, 208, 102, 174,   1, 209, 102, 174,   1, 161,  97, 174, 
  1, 208, 208, 102, 175,   1, 209, 102, 175,   1, 161,  97, 175,   1,  71,   0, 
  0, 133,   1,   2,   2,   4,   5,  38, 208,  48,  44, 162,   1, 208, 102, 173, 
  1, 160,  44, 163,   1, 160, 208, 102, 174,   1, 160,  44, 163,   1, 160, 208, 
102, 175,   1, 160, 130, 213, 209,  44,  18, 160, 130, 213, 209,  72,   0,   0, 
134,   1,   3,   2,   4,   5,  55, 208,  48, 208, 102, 173,   1, 208, 102, 173, 
  1, 162, 208, 102, 174,   1, 208, 102, 174,   1, 162, 160, 208, 102, 175,   1, 
208, 102, 175,   1, 162, 160, 130, 213, 209,  36,   0,  13,   3,   0,   0,  36, 
  0,  72,  93, 176,   1, 102, 176,   1, 209,  70, 180,   1,   1,  72,   0,   0, 
135,   1,   6,   2,   4,   5,  69, 208,  48,  93, 179,   1, 208, 102, 174,   1, 
209, 102, 175,   1, 162, 208, 102, 175,   1, 209, 102, 174,   1, 162, 161, 208, 
102, 175,   1, 209, 102, 173,   1, 162, 208, 102, 173,   1, 209, 102, 175,   1, 
162, 161, 208, 102, 173,   1, 209, 102, 174,   1, 162, 208, 102, 174,   1, 209, 
102, 173,   1, 162, 161,  36,   1,  74, 179,   1,   4,  72,   0,   0, 136,   1, 
  3,   2,   4,   5,  42, 208,  48, 208, 208, 102, 173,   1, 209, 102, 173,   1, 
160,  97, 173,   1, 208, 208, 102, 174,   1, 209, 102, 174,   1, 160,  97, 174, 
  1, 208, 208, 102, 175,   1, 209, 102, 175,   1, 160,  97, 175,   1,  71,   0, 
  0, 137,   1,   5,   2,   4,   5,  37, 208,  48,  93, 179,   1, 208, 102, 173, 
  1, 209, 102, 173,   1, 161, 208, 102, 174,   1, 209, 102, 174,   1, 161, 208, 
102, 175,   1, 209, 102, 175,   1, 161,  74, 179,   1,   3,  72,   0,   0, 138, 
  1,   3,   3,   4,   5,  63, 208,  48, 208, 102, 172,   1, 130, 213, 209,  36, 
  0, 171, 150,  18,   9,   0,   0,  36,   1, 209, 163, 130,  16,   3,   0,   0, 
 36,   0, 130, 130, 214, 208, 208, 102, 173,   1, 210, 162,  97, 173,   1, 208, 
208, 102, 174,   1, 210, 162,  97, 174,   1, 208, 208, 102, 175,   1, 210, 162, 
 97, 175,   1, 209,  72,   0,   0, 139,   1,   5,   1,   4,   5,  26, 208,  48, 
 93, 179,   1, 208, 102, 173,   1, 208, 102, 174,   1, 208, 102, 175,   1, 208, 
102, 178,   1,  74, 179,   1,   4,  72,   0,   0, 140,   1,   2,   3,   4,   5, 
 60, 208,  48, 208, 102, 173,   1, 209, 102, 173,   1,  20,   0,   0,   0, 208, 
102, 174,   1, 209, 102, 174,   1,  20,   0,   0,   0, 208, 102, 175,   1, 209, 
102, 175,   1,  20,   0,   0,   0, 210,  18,  14,   0,   0, 208, 102, 178,   1, 
209, 102, 178,   1, 171, 118,  16,   2,   0,   0,  38, 118,  72,   0,   0, 141, 
  1,   2,   1,   1,   3, 185,   1, 208,  48, 101,   0,  93,  28, 102,  28,  48, 
 93, 193,   1, 102, 193,   1,  88,   0,  29, 104,   3, 101,   0,  93,  28, 102, 
 28,  48,  93, 193,   1, 102, 193,   1,  88,   1,  29, 104,  38, 101,   0,  93, 
 28, 102,  28,  48,  93, 193,   1, 102, 193,   1,  88,   2,  29, 104,  61, 101, 
  0,  93,  28, 102,  28,  48,  93, 194,   1, 102, 194,   1,  88,   3,  29, 104, 
 85, 101,   0,  93,  28, 102,  28,  48,  93, 193,   1, 102, 193,   1,  88,   4, 
 29, 104, 114, 101,   0,  93,  28, 102,  28,  48,  93, 193,   1, 102, 193,   1, 
 88,   5,  29, 104, 119, 101,   0,  93,  28, 102,  28,  48,  93, 193,   1, 102, 
193,   1,  88,   6,  29, 104, 125, 101,   0,  93,  28, 102,  28,  48,  93, 195, 
  1, 102, 195,   1,  88,   7,  29, 104, 163,   1, 101,   0,  93,  28, 102,  28, 
 48,  93, 194,   1, 102, 194,   1,  88,   8,  29, 104, 167,   1, 101,   0,  93, 
 28, 102,  28,  48,  93, 193,   1, 102, 193,   1,  88,   9,  29, 104,  88,  71, 
  0,   0};

} }
