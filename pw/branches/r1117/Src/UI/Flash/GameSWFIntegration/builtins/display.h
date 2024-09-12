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
    class AVM1MovieClass; //flash.display::AVM1Movie$
    class AVM1MovieObject; //flash.display::AVM1Movie
    class BitmapClass; //flash.display::Bitmap$
    class BitmapDataClass; //flash.display::BitmapData$
    class BitmapDataObject; //flash.display::BitmapData
    class BitmapObject; //flash.display::Bitmap
    class DisplayObjectClass; //flash.display::DisplayObject$
    class DisplayObjectContainerClass; //flash.display::DisplayObjectContainer$
    class DisplayObjectContainerObject; //flash.display::DisplayObjectContainer
    class DisplayObjectObject; //flash.display::DisplayObject
    class GraphicsClass; //flash.display::Graphics$
    class GraphicsObject; //flash.display::Graphics
    class InteractiveObjectClass; //flash.display::InteractiveObject$
    class InteractiveObjectObject; //flash.display::InteractiveObject
    class LoaderClass; //flash.display::Loader$
    class LoaderInfoClass; //flash.display::LoaderInfo$
    class LoaderInfoObject; //flash.display::LoaderInfo
    class LoaderObject; //flash.display::Loader
    class MorphShapeClass; //flash.display::MorphShape$
    class MorphShapeObject; //flash.display::MorphShape
    class MovieClipClass; //flash.display::MovieClip$
    class MovieClipObject; //flash.display::MovieClip
    class ShaderClass; //flash.display::Shader$
    class ShaderDataClass; //flash.display::ShaderData$
    class ShaderDataObject; //flash.display::ShaderData
    class ShaderInputClass; //flash.display::ShaderInput$
    class ShaderInputObject; //flash.display::ShaderInput
    class ShaderJobClass; //flash.display::ShaderJob$
    class ShaderJobObject; //flash.display::ShaderJob
    class ShaderObject; //flash.display::Shader
    class ShaderParameterClass; //flash.display::ShaderParameter$
    class ShaderParameterObject; //flash.display::ShaderParameter
    class ShapeClass; //flash.display::Shape$
    class ShapeObject; //flash.display::Shape
    class SimpleButtonClass; //flash.display::SimpleButton$
    class SimpleButtonObject; //flash.display::SimpleButton
    class SpriteClass; //flash.display::Sprite$
    class SpriteObject; //flash.display::Sprite
    class StageClass; //flash.display::Stage$
    class StageObject; //flash.display::Stage
}

namespace avmplus { namespace NativeID {

extern const uint32_t display_abc_class_count;
extern const uint32_t display_abc_script_count;
extern const uint32_t display_abc_method_count;
extern const uint32_t display_abc_length;
extern const uint8_t display_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(display)

/* classes */
const uint32_t abcclass_flash_display_IBitmapDrawable = 0;
const uint32_t abcclass_flash_display_ActionScriptVersion = 1;
const uint32_t abcclass_flash_display_BitmapDataChannel = 2;
const uint32_t abcclass_flash_display_BlendMode = 3;
const uint32_t abcclass_flash_display_CapsStyle = 4;
const uint32_t abcclass_flash_display_ColorCorrection = 5;
const uint32_t abcclass_flash_display_ColorCorrectionSupport = 6;
const uint32_t abcclass_flash_display_FrameLabel = 7;
const uint32_t abcclass_flash_display_GradientType = 8;
const uint32_t abcclass_flash_display_Graphics = 9;
const uint32_t abcclass_flash_display_IGraphicsFill = 10;
const uint32_t abcclass_flash_display_IGraphicsData = 11;
const uint32_t abcclass_flash_display_IGraphicsPath = 12;
const uint32_t abcclass_flash_display_GraphicsPathCommand = 13;
const uint32_t abcclass_flash_display_GraphicsPathWinding = 14;
const uint32_t abcclass_flash_display_IGraphicsStroke = 15;
const uint32_t abcclass_flash_display_InterpolationMethod = 16;
const uint32_t abcclass_flash_display_JointStyle = 17;
const uint32_t abcclass_flash_display_LineScaleMode = 18;
const uint32_t abcclass_flash_display_LoaderInfo = 19;
const uint32_t abcclass_flash_display_PixelSnapping = 20;
const uint32_t abcclass_flash_display_Scene = 21;
const uint32_t abcclass_flash_display_Shader = 22;
const uint32_t abcclass_flash_display_ShaderData = 23;
const uint32_t abcclass_flash_display_ShaderInput = 24;
const uint32_t abcclass_flash_display_ShaderJob = 25;
const uint32_t abcclass_flash_display_ShaderParameter = 26;
const uint32_t abcclass_flash_display_ShaderParameterType = 27;
const uint32_t abcclass_flash_display_ShaderPrecision = 28;
const uint32_t abcclass_flash_display_SpreadMethod = 29;
const uint32_t abcclass_flash_display_StageAlign = 30;
const uint32_t abcclass_flash_display_StageDisplayState = 31;
const uint32_t abcclass_flash_display_StageQuality = 32;
const uint32_t abcclass_flash_display_StageScaleMode = 33;
const uint32_t abcclass_flash_display_SWFVersion = 34;
const uint32_t abcclass_flash_display_TriangleCulling = 35;
const uint32_t abcclass_flash_display_DisplayObject = 36;
const uint32_t abcclass_flash_display_BitmapData = 37;
const uint32_t abcclass_flash_display_GraphicsBitmapFill = 38;
const uint32_t abcclass_flash_display_GraphicsEndFill = 39;
const uint32_t abcclass_flash_display_GraphicsGradientFill = 40;
const uint32_t abcclass_flash_display_GraphicsShaderFill = 41;
const uint32_t abcclass_flash_display_GraphicsSolidFill = 42;
const uint32_t abcclass_flash_display_GraphicsPath = 43;
const uint32_t abcclass_flash_display_GraphicsTrianglePath = 44;
const uint32_t abcclass_flash_display_GraphicsStroke = 45;
const uint32_t abcclass_flash_display_AVM1Movie = 46;
const uint32_t abcclass_flash_display_Bitmap = 47;
const uint32_t abcclass_flash_display_InteractiveObject = 48;
const uint32_t abcclass_flash_display_MorphShape = 49;
const uint32_t abcclass_flash_display_Shape = 50;
const uint32_t abcclass_flash_display_DisplayObjectContainer = 51;
const uint32_t abcclass_flash_display_SimpleButton = 52;
const uint32_t abcclass_flash_display_Loader = 53;
const uint32_t abcclass_flash_display_Sprite = 54;
const uint32_t abcclass_flash_display_Stage = 55;
const uint32_t abcclass_flash_display_MovieClip = 56;

/* methods */
const uint32_t flash_display_Graphics_drawTriangles = 22;
const uint32_t flash_display_Graphics_drawRect = 23;
const uint32_t flash_display_Graphics_drawPath = 24;
const uint32_t flash_display_Graphics_curveTo = 25;
const uint32_t flash_display_Graphics_beginFill = 26;
const uint32_t flash_display_Graphics_clear = 27;
const uint32_t flash_display_Graphics_lineTo = 28;
const uint32_t flash_display_Graphics_beginShaderFill = 29;
const uint32_t flash_display_Graphics_lineGradientStyle = 30;
const uint32_t flash_display_Graphics_beginBitmapFill = 31;
const uint32_t flash_display_Graphics_beginGradientFill = 32;
const uint32_t flash_display_Graphics_lineStyle = 33;
const uint32_t flash_display_Graphics_drawRoundRectComplex = 35;
const uint32_t flash_display_Graphics_moveTo = 38;
const uint32_t flash_display_Graphics_drawRoundRect = 39;
const uint32_t flash_display_Graphics_lineBitmapStyle = 41;
const uint32_t flash_display_Graphics_lineShaderStyle = 42;
const uint32_t flash_display_Graphics_endFill = 45;
const uint32_t flash_display_Graphics_copyFrom = 46;
const uint32_t flash_display_LoaderInfo_getLoaderInfoByDefinition = 66;
const uint32_t flash_display_LoaderInfo_private__getArgs = 69;
const uint32_t flash_display_LoaderInfo_width_get = 70;
const uint32_t flash_display_LoaderInfo_height_get = 71;
const uint32_t flash_display_LoaderInfo_parentAllowsChild_get = 72;
const uint32_t flash_display_LoaderInfo_bytes_get = 74;
const uint32_t flash_display_LoaderInfo_frameRate_get = 75;
const uint32_t flash_display_LoaderInfo_url_get = 76;
const uint32_t flash_display_LoaderInfo_bytesLoaded_get = 77;
const uint32_t flash_display_LoaderInfo_sameDomain_get = 78;
const uint32_t flash_display_LoaderInfo_contentType_get = 79;
const uint32_t flash_display_LoaderInfo_applicationDomain_get = 80;
const uint32_t flash_display_LoaderInfo_swfVersion_get = 81;
const uint32_t flash_display_LoaderInfo_actionScriptVersion_get = 82;
const uint32_t flash_display_LoaderInfo_bytesTotal_get = 83;
const uint32_t flash_display_LoaderInfo_loader_get = 84;
const uint32_t flash_display_LoaderInfo_content_get = 85;
const uint32_t flash_display_LoaderInfo_loaderURL_get = 86;
const uint32_t flash_display_LoaderInfo_sharedEvents_get = 87;
const uint32_t flash_display_LoaderInfo_childAllowsParent_get = 88;
const uint32_t flash_display_Shader_data_set = 99;
const uint32_t flash_display_Shader_precisionHint_get = 100;
const uint32_t flash_display_Shader_data_get = 101;
const uint32_t flash_display_Shader_precisionHint_set = 102;
const uint32_t flash_display_ShaderData_private__setByteCode = 105;
const uint32_t flash_display_ShaderInput_channels_get = 108;
const uint32_t flash_display_ShaderInput_index_get = 109;
const uint32_t flash_display_ShaderInput_input_set = 110;
const uint32_t flash_display_ShaderInput_width_get = 111;
const uint32_t flash_display_ShaderInput_height_get = 112;
const uint32_t flash_display_ShaderInput_input_get = 113;
const uint32_t flash_display_ShaderInput_width_set = 114;
const uint32_t flash_display_ShaderInput_height_set = 115;
const uint32_t flash_display_ShaderJob_start = 118;
const uint32_t flash_display_ShaderJob_shader_get = 119;
const uint32_t flash_display_ShaderJob_width_get = 120;
const uint32_t flash_display_ShaderJob_height_get = 121;
const uint32_t flash_display_ShaderJob_target_set = 122;
const uint32_t flash_display_ShaderJob_shader_set = 123;
const uint32_t flash_display_ShaderJob_width_set = 124;
const uint32_t flash_display_ShaderJob_progress_get = 125;
const uint32_t flash_display_ShaderJob_height_set = 126;
const uint32_t flash_display_ShaderJob_target_get = 127;
const uint32_t flash_display_ShaderJob_cancel = 128;
const uint32_t flash_display_ShaderParameter_value_get = 131;
const uint32_t flash_display_ShaderParameter_value_set = 132;
const uint32_t flash_display_ShaderParameter_type_get = 133;
const uint32_t flash_display_ShaderParameter_index_get = 134;
const uint32_t flash_display_DisplayObject_visible_get = 155;
const uint32_t flash_display_DisplayObject_rotation_get = 156;
const uint32_t flash_display_DisplayObject_private__hitTest = 157;
const uint32_t flash_display_DisplayObject_localToGlobal = 158;
const uint32_t flash_display_DisplayObject_name_get = 159;
const uint32_t flash_display_DisplayObject_width_set = 160;
const uint32_t flash_display_DisplayObject_globalToLocal = 161;
const uint32_t flash_display_DisplayObject_blendMode_get = 162;
const uint32_t flash_display_DisplayObject_scale9Grid_get = 163;
const uint32_t flash_display_DisplayObject_name_set = 164;
const uint32_t flash_display_DisplayObject_rotationX_get = 165;
const uint32_t flash_display_DisplayObject_rotationY_get = 166;
const uint32_t flash_display_DisplayObject_scaleX_set = 167;
const uint32_t flash_display_DisplayObject_scaleY_set = 168;
const uint32_t flash_display_DisplayObject_scaleZ_set = 169;
const uint32_t flash_display_DisplayObject_accessibilityProperties_get = 170;
const uint32_t flash_display_DisplayObject_scrollRect_set = 171;
const uint32_t flash_display_DisplayObject_rotationZ_get = 172;
const uint32_t flash_display_DisplayObject_height_get = 173;
const uint32_t flash_display_DisplayObject_blendMode_set = 174;
const uint32_t flash_display_DisplayObject_scale9Grid_set = 175;
const uint32_t flash_display_DisplayObject_getBounds = 176;
const uint32_t flash_display_DisplayObject_blendShader_set = 177;
const uint32_t flash_display_DisplayObject_opaqueBackground_get = 178;
const uint32_t flash_display_DisplayObject_parent_get = 179;
const uint32_t flash_display_DisplayObject_cacheAsBitmap_get = 180;
const uint32_t flash_display_DisplayObject_rotationX_set = 181;
const uint32_t flash_display_DisplayObject_rotationY_set = 182;
const uint32_t flash_display_DisplayObject_rotationZ_set = 183;
const uint32_t flash_display_DisplayObject_local3DToGlobal = 184;
const uint32_t flash_display_DisplayObject_alpha_set = 185;
const uint32_t flash_display_DisplayObject_globalToLocal3D = 186;
const uint32_t flash_display_DisplayObject_accessibilityProperties_set = 187;
const uint32_t flash_display_DisplayObject_width_get = 188;
const uint32_t flash_display_DisplayObject_cacheAsBitmap_set = 190;
const uint32_t flash_display_DisplayObject_scaleX_get = 191;
const uint32_t flash_display_DisplayObject_scaleY_get = 192;
const uint32_t flash_display_DisplayObject_scaleZ_get = 193;
const uint32_t flash_display_DisplayObject_scrollRect_get = 194;
const uint32_t flash_display_DisplayObject_mouseX_get = 195;
const uint32_t flash_display_DisplayObject_mouseY_get = 196;
const uint32_t flash_display_DisplayObject_height_set = 197;
const uint32_t flash_display_DisplayObject_mask_set = 198;
const uint32_t flash_display_DisplayObject_getRect = 199;
const uint32_t flash_display_DisplayObject_alpha_get = 200;
const uint32_t flash_display_DisplayObject_transform_set = 201;
const uint32_t flash_display_DisplayObject_loaderInfo_get = 202;
const uint32_t flash_display_DisplayObject_root_get = 203;
const uint32_t flash_display_DisplayObject_visible_set = 204;
const uint32_t flash_display_DisplayObject_opaqueBackground_set = 205;
const uint32_t flash_display_DisplayObject_mask_get = 207;
const uint32_t flash_display_DisplayObject_x_set = 208;
const uint32_t flash_display_DisplayObject_y_set = 209;
const uint32_t flash_display_DisplayObject_transform_get = 210;
const uint32_t flash_display_DisplayObject_z_set = 211;
const uint32_t flash_display_DisplayObject_filters_set = 212;
const uint32_t flash_display_DisplayObject_x_get = 213;
const uint32_t flash_display_DisplayObject_y_get = 214;
const uint32_t flash_display_DisplayObject_z_get = 215;
const uint32_t flash_display_DisplayObject_filters_get = 216;
const uint32_t flash_display_DisplayObject_rotation_set = 217;
const uint32_t flash_display_DisplayObject_stage_get = 218;
const uint32_t flash_display_BitmapData_private__Init = 221;
const uint32_t flash_display_BitmapData_copyPixels = 222;
const uint32_t flash_display_BitmapData_setPixel = 223;
const uint32_t flash_display_BitmapData_hitTest = 224;
const uint32_t flash_display_BitmapData_applyFilter = 225;
const uint32_t flash_display_BitmapData_fillRect = 226;
const uint32_t flash_display_BitmapData_colorTransform = 227;
const uint32_t flash_display_BitmapData_draw = 228;
const uint32_t flash_display_BitmapData_width_get = 230;
const uint32_t flash_display_BitmapData_copyChannel = 231;
const uint32_t flash_display_BitmapData_getPixel = 232;
const uint32_t flash_display_BitmapData_generateFilterRect = 233;
const uint32_t flash_display_BitmapData_transparent_get = 234;
const uint32_t flash_display_BitmapData_unlock = 235;
const uint32_t flash_display_BitmapData_scroll = 236;
const uint32_t flash_display_BitmapData_getColorBoundsRect = 237;
const uint32_t flash_display_BitmapData_pixelDissolve = 238;
const uint32_t flash_display_BitmapData_noise = 239;
const uint32_t flash_display_BitmapData_clone = 240;
const uint32_t flash_display_BitmapData_private__setVector = 241;
const uint32_t flash_display_BitmapData_dispose = 242;
const uint32_t flash_display_BitmapData_floodFill = 243;
const uint32_t flash_display_BitmapData_setPixel32 = 244;
const uint32_t flash_display_BitmapData_compare = 246;
const uint32_t flash_display_BitmapData_perlinNoise = 247;
const uint32_t flash_display_BitmapData_height_get = 248;
const uint32_t flash_display_BitmapData_paletteMap = 249;
const uint32_t flash_display_BitmapData_getPixels = 250;
const uint32_t flash_display_BitmapData_threshold = 251;
const uint32_t flash_display_BitmapData_getPixel32 = 252;
const uint32_t flash_display_BitmapData_lock = 253;
const uint32_t flash_display_BitmapData_setPixels = 254;
const uint32_t flash_display_BitmapData_merge = 255;
const uint32_t flash_display_BitmapData_private__getVector = 257;
const uint32_t flash_display_BitmapData_histogram = 258;
const uint32_t flash_display_AVM1Movie_private__setCallAS3 = 298;
const uint32_t flash_display_AVM1Movie_private__callAS2 = 301;
const uint32_t flash_display_AVM1Movie_private__interopAvailable_get = 302;
const uint32_t flash_display_Bitmap_private__Init = 306;
const uint32_t flash_display_Bitmap_bitmapData_set = 307;
const uint32_t flash_display_Bitmap_pixelSnapping_get = 308;
const uint32_t flash_display_Bitmap_pixelSnapping_set = 309;
const uint32_t flash_display_Bitmap_smoothing_set = 310;
const uint32_t flash_display_Bitmap_bitmapData_get = 311;
const uint32_t flash_display_Bitmap_smoothing_get = 312;
const uint32_t flash_display_InteractiveObject_accessibilityImplementation_get = 315;
const uint32_t flash_display_InteractiveObject_focusRect_get = 316;
const uint32_t flash_display_InteractiveObject_focusRect_set = 317;
const uint32_t flash_display_InteractiveObject_doubleClickEnabled_get = 318;
const uint32_t flash_display_InteractiveObject_contextMenu_set = 319;
const uint32_t flash_display_InteractiveObject_tabEnabled_get = 320;
const uint32_t flash_display_InteractiveObject_contextMenu_get = 321;
const uint32_t flash_display_InteractiveObject_accessibilityImplementation_set = 322;
const uint32_t flash_display_InteractiveObject_doubleClickEnabled_set = 323;
const uint32_t flash_display_InteractiveObject_mouseEnabled_set = 324;
const uint32_t flash_display_InteractiveObject_tabIndex_set = 325;
const uint32_t flash_display_InteractiveObject_mouseEnabled_get = 326;
const uint32_t flash_display_InteractiveObject_tabIndex_get = 327;
const uint32_t flash_display_InteractiveObject_tabEnabled_set = 328;
const uint32_t flash_display_Shape_graphics_get = 333;
const uint32_t flash_display_DisplayObjectContainer_mouseChildren_get = 336;
const uint32_t flash_display_DisplayObjectContainer_numChildren_get = 337;
const uint32_t flash_display_DisplayObjectContainer_contains = 338;
const uint32_t flash_display_DisplayObjectContainer_swapChildrenAt = 339;
const uint32_t flash_display_DisplayObjectContainer_getChildByName = 340;
const uint32_t flash_display_DisplayObjectContainer_removeChildAt = 341;
const uint32_t flash_display_DisplayObjectContainer_getChildIndex = 342;
const uint32_t flash_display_DisplayObjectContainer_addChildAt = 343;
const uint32_t flash_display_DisplayObjectContainer_tabChildren_set = 344;
const uint32_t flash_display_DisplayObjectContainer_textSnapshot_get = 345;
const uint32_t flash_display_DisplayObjectContainer_swapChildren = 346;
const uint32_t flash_display_DisplayObjectContainer_tabChildren_get = 347;
const uint32_t flash_display_DisplayObjectContainer_getObjectsUnderPoint = 348;
const uint32_t flash_display_DisplayObjectContainer_mouseChildren_set = 349;
const uint32_t flash_display_DisplayObjectContainer_removeChild = 350;
const uint32_t flash_display_DisplayObjectContainer_getChildAt = 351;
const uint32_t flash_display_DisplayObjectContainer_addChild = 352;
const uint32_t flash_display_DisplayObjectContainer_areInaccessibleObjectsUnderPoint = 353;
const uint32_t flash_display_DisplayObjectContainer_setChildIndex = 354;
const uint32_t flash_display_SimpleButton_enabled_get = 357;
const uint32_t flash_display_SimpleButton_enabled_set = 358;
const uint32_t flash_display_SimpleButton_hitTestState_get = 359;
const uint32_t flash_display_SimpleButton_hitTestState_set = 360;
const uint32_t flash_display_SimpleButton_private__updateButton = 361;
const uint32_t flash_display_SimpleButton_upState_set = 362;
const uint32_t flash_display_SimpleButton_downState_get = 363;
const uint32_t flash_display_SimpleButton_soundTransform_set = 364;
const uint32_t flash_display_SimpleButton_soundTransform_get = 365;
const uint32_t flash_display_SimpleButton_upState_get = 366;
const uint32_t flash_display_SimpleButton_useHandCursor_set = 367;
const uint32_t flash_display_SimpleButton_overState_set = 368;
const uint32_t flash_display_SimpleButton_useHandCursor_get = 369;
const uint32_t flash_display_SimpleButton_trackAsMenu_get = 370;
const uint32_t flash_display_SimpleButton_overState_get = 371;
const uint32_t flash_display_SimpleButton_downState_set = 372;
const uint32_t flash_display_SimpleButton_trackAsMenu_set = 373;
const uint32_t flash_display_Loader_contentLoaderInfo_get = 376;
const uint32_t flash_display_Loader_private__load = 377;
const uint32_t flash_display_Loader_private__getJPEGLoaderContextdeblockingfilter = 380;
const uint32_t flash_display_Loader_private__loadBytes = 386;
const uint32_t flash_display_Loader_close = 387;
const uint32_t flash_display_Loader_content_get = 388;
const uint32_t flash_display_Loader_private__unload = 391;
const uint32_t flash_display_Sprite_dropTarget_get = 395;
const uint32_t flash_display_Sprite_soundTransform_get = 396;
const uint32_t flash_display_Sprite_private_constructChildren = 397;
const uint32_t flash_display_Sprite_hitArea_get = 398;
const uint32_t flash_display_Sprite_buttonMode_set = 399;
const uint32_t flash_display_Sprite_graphics_get = 400;
const uint32_t flash_display_Sprite_useHandCursor_get = 401;
const uint32_t flash_display_Sprite_hitArea_set = 402;
const uint32_t flash_display_Sprite_buttonMode_get = 403;
const uint32_t flash_display_Sprite_stopDrag = 404;
const uint32_t flash_display_Sprite_useHandCursor_set = 405;
const uint32_t flash_display_Sprite_soundTransform_set = 406;
const uint32_t flash_display_Sprite_startDrag = 407;
const uint32_t flash_display_Stage_stageFocusRect_set = 411;
const uint32_t flash_display_Stage_align_get = 412;
const uint32_t flash_display_Stage_isFocusInaccessible = 415;
const uint32_t flash_display_Stage_stageHeight_set = 416;
const uint32_t flash_display_Stage_scaleMode_get = 418;
const uint32_t flash_display_Stage_showDefaultContextMenu_get = 420;
const uint32_t flash_display_Stage_showDefaultContextMenu_set = 422;
const uint32_t flash_display_Stage_align_set = 425;
const uint32_t flash_display_Stage_scaleMode_set = 426;
const uint32_t flash_display_Stage_swapChildrenAt = 428;
const uint32_t flash_display_Stage_colorCorrection_get = 431;
const uint32_t flash_display_Stage_fullScreenWidth_get = 438;
const uint32_t flash_display_Stage_focus_set = 439;
const uint32_t flash_display_Stage_fullScreenSourceRect_set = 440;
const uint32_t flash_display_Stage_quality_set = 442;
const uint32_t flash_display_Stage_colorCorrection_set = 448;
const uint32_t flash_display_Stage_stageHeight_get = 451;
const uint32_t flash_display_Stage_invalidate = 455;
const uint32_t flash_display_Stage_removeChildAt = 456;
const uint32_t flash_display_Stage_stageWidth_set = 460;
const uint32_t flash_display_Stage_private_requireOwnerPermissions = 462;
const uint32_t flash_display_Stage_focus_get = 463;
const uint32_t flash_display_Stage_frameRate_set = 464;
const uint32_t flash_display_Stage_fullScreenSourceRect_get = 468;
const uint32_t flash_display_Stage_fullScreenHeight_get = 469;
const uint32_t flash_display_Stage_displayState_set = 471;
const uint32_t flash_display_Stage_stageWidth_get = 473;
const uint32_t flash_display_Stage_frameRate_get = 474;
const uint32_t flash_display_Stage_colorCorrectionSupport_get = 475;
const uint32_t flash_display_Stage_displayState_get = 476;
const uint32_t flash_display_Stage_stageFocusRect_get = 485;
const uint32_t flash_display_Stage_quality_get = 486;
const uint32_t flash_display_MovieClip_private__Init = 489;
const uint32_t flash_display_MovieClip_currentFrameLabel_get = 490;
const uint32_t flash_display_MovieClip_prevFrame = 491;
const uint32_t flash_display_MovieClip_stop = 492;
const uint32_t flash_display_MovieClip_scenes_get = 493;
const uint32_t flash_display_MovieClip_gotoAndPlay = 494;
const uint32_t flash_display_MovieClip_enabled_set = 495;
const uint32_t flash_display_MovieClip_totalFrames_get = 496;
const uint32_t flash_display_MovieClip_framesLoaded_get = 497;
const uint32_t flash_display_MovieClip_enabled_get = 498;
const uint32_t flash_display_MovieClip_nextScene = 499;
const uint32_t flash_display_MovieClip_currentFrame_get = 500;
const uint32_t flash_display_MovieClip_currentScene_get = 501;
const uint32_t flash_display_MovieClip_gotoAndStop = 502;
const uint32_t flash_display_MovieClip_addFrameScript = 503;
const uint32_t flash_display_MovieClip_trackAsMenu_set = 504;
const uint32_t flash_display_MovieClip_prevScene = 505;
const uint32_t flash_display_MovieClip_nextFrame = 506;
const uint32_t flash_display_MovieClip_play = 507;
const uint32_t flash_display_MovieClip_trackAsMenu_get = 508;
const uint32_t flash_display_MovieClip_currentLabel_get = 509;

extern AvmBox display_v2a_ooobb_optakAvmThunkNull_optbtrue_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Graphics_beginBitmapFill_thunk  display_v2a_ooobb_optakAvmThunkNull_optbtrue_optbfalse_thunk
#define flash_display_Graphics_lineBitmapStyle_thunk  display_v2a_ooobb_optakAvmThunkNull_optbtrue_optbfalse_thunk

extern AvmBox display_a2a_oso_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_AVM1Movie_private__callAS2_thunk  display_a2a_oso_thunk

extern AvmBox display_v2a_oooooob_optakAvmThunkNull_optakAvmThunkNull_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_copyPixels_thunk  display_v2a_oooooob_optakAvmThunkNull_optakAvmThunkNull_optbfalse_thunk

extern AvmBox display_a2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObjectContainer_getChildByName_thunk  display_a2a_os_thunk

extern AvmBox display_a2a_ooi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObjectContainer_addChildAt_thunk  display_a2a_ooi_thunk

extern AvmBox display_v2a_obb_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Loader_private__unload_thunk  display_v2a_obb_thunk

extern AvmBox display_a2a_ooo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_generateFilterRect_thunk  display_a2a_ooo_thunk

extern AvmBox display_v2a_o_rest_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_MovieClip_addFrameScript_thunk  display_v2a_o_rest_thunk

extern AvmBox display_a2a_oi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObjectContainer_getChildAt_thunk  display_a2a_oi_thunk
#define flash_display_DisplayObjectContainer_removeChildAt_thunk  display_a2a_oi_thunk
#define flash_display_Stage_removeChildAt_thunk  display_a2a_oi_thunk

extern AvmBox display_v2a_oooosob_optakAvmThunkNull_optakAvmThunkNull_optakAvmThunkNull_optakAvmThunkNull_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_draw_thunk  display_v2a_oooosob_optakAvmThunkNull_optakAvmThunkNull_optakAvmThunkNull_optakAvmThunkNull_optbfalse_thunk

extern AvmBox display_a2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_getPixels_thunk  display_a2a_oo_thunk
#define flash_display_DisplayObjectContainer_addChild_thunk  display_a2a_oo_thunk
#define flash_display_DisplayObjectContainer_removeChild_thunk  display_a2a_oo_thunk
#define flash_display_BitmapData_compare_thunk  display_a2a_oo_thunk
#define flash_display_DisplayObject_getRect_thunk  display_a2a_oo_thunk
#define flash_display_DisplayObject_globalToLocal3D_thunk  display_a2a_oo_thunk
#define flash_display_DisplayObject_localToGlobal_thunk  display_a2a_oo_thunk
#define flash_display_DisplayObject_globalToLocal_thunk  display_a2a_oo_thunk
#define flash_display_DisplayObjectContainer_getObjectsUnderPoint_thunk  display_a2a_oo_thunk
#define flash_display_DisplayObject_getBounds_thunk  display_a2a_oo_thunk
#define flash_display_DisplayObject_local3DToGlobal_thunk  display_a2a_oo_thunk

extern AvmBox display_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObject_name_get_thunk  display_s2a_o_thunk
#define flash_display_Stage_scaleMode_get_thunk  display_s2a_o_thunk
#define flash_display_Shader_precisionHint_get_thunk  display_s2a_o_thunk
#define flash_display_LoaderInfo_loaderURL_get_thunk  display_s2a_o_thunk
#define flash_display_Stage_colorCorrectionSupport_get_thunk  display_s2a_o_thunk
#define flash_display_LoaderInfo_url_get_thunk  display_s2a_o_thunk
#define flash_display_Stage_quality_get_thunk  display_s2a_o_thunk
#define flash_display_Bitmap_pixelSnapping_get_thunk  display_s2a_o_thunk
#define flash_display_Stage_colorCorrection_get_thunk  display_s2a_o_thunk
#define flash_display_MovieClip_currentFrameLabel_get_thunk  display_s2a_o_thunk
#define flash_display_ShaderParameter_type_get_thunk  display_s2a_o_thunk
#define flash_display_LoaderInfo_contentType_get_thunk  display_s2a_o_thunk
#define flash_display_MovieClip_currentLabel_get_thunk  display_s2a_o_thunk
#define flash_display_Stage_align_get_thunk  display_s2a_o_thunk
#define flash_display_DisplayObject_blendMode_get_thunk  display_s2a_o_thunk
#define flash_display_Stage_displayState_get_thunk  display_s2a_o_thunk

extern AvmBox display_v2a_oooooooo_optakAvmThunkNull_optakAvmThunkNull_optakAvmThunkNull_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_paletteMap_thunk  display_v2a_oooooooo_optakAvmThunkNull_optakAvmThunkNull_optakAvmThunkNull_optakAvmThunkNull_thunk

extern AvmBox display_a2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_LoaderInfo_getLoaderInfoByDefinition_thunk  display_a2a_oa_thunk

extern AvmBox display_v2a_odddddddd_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Graphics_drawRoundRectComplex_thunk  display_v2a_odddddddd_thunk

extern AvmBox display_a2a_ooiiii_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_private__getVector_thunk  display_a2a_ooiiii_thunk

extern double display_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObject_scaleY_get_thunk  display_d2d_o_thunk
#define flash_display_ShaderJob_progress_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_rotationY_get_thunk  display_d2d_o_thunk
#define flash_display_Stage_frameRate_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_mouseY_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_rotationX_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_mouseX_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_scaleZ_get_thunk  display_d2d_o_thunk
#define flash_display_LoaderInfo_frameRate_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_z_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_alpha_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_width_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_height_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_rotation_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_rotationZ_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_scaleX_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_x_get_thunk  display_d2d_o_thunk
#define flash_display_DisplayObject_y_get_thunk  display_d2d_o_thunk

extern AvmBox display_v2a_oooouu_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_copyChannel_thunk  display_v2a_oooouu_thunk

extern AvmBox display_i2a_ooooiiu_opti0_opti0_opti0_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_pixelDissolve_thunk  display_i2a_ooooiiu_opti0_opti0_opti0_thunk

extern AvmBox display_v2a_odddd_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Graphics_drawRect_thunk  display_v2a_odddd_thunk
#define flash_display_Graphics_curveTo_thunk  display_v2a_odddd_thunk

extern AvmBox display_v2a_ooi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObjectContainer_setChildIndex_thunk  display_v2a_ooi_thunk

extern AvmBox display_v2a_ooooo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_applyFilter_thunk  display_v2a_ooooo_thunk

extern AvmBox display_a2a_ouub_optbtrue_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_getColorBoundsRect_thunk  display_a2a_ouub_optbtrue_thunk

extern AvmBox display_v2a_oiuuub_opti0_opti255_opti7_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_noise_thunk  display_v2a_oiuuub_opti0_opti255_opti7_optbfalse_thunk

extern AvmBox display_u2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Stage_fullScreenWidth_get_thunk  display_u2a_o_thunk
#define flash_display_LoaderInfo_actionScriptVersion_get_thunk  display_u2a_o_thunk
#define flash_display_LoaderInfo_swfVersion_get_thunk  display_u2a_o_thunk
#define flash_display_LoaderInfo_bytesLoaded_get_thunk  display_u2a_o_thunk
#define flash_display_LoaderInfo_bytesTotal_get_thunk  display_u2a_o_thunk
#define flash_display_Stage_fullScreenHeight_get_thunk  display_u2a_o_thunk

extern AvmBox display_u2a_oii_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_getPixel32_thunk  display_u2a_oii_thunk
#define flash_display_BitmapData_getPixel_thunk  display_u2a_oii_thunk

extern AvmBox display_v2a_oas_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_MovieClip_gotoAndPlay_thunk  display_v2a_oas_optakAvmThunkNull_thunk
#define flash_display_MovieClip_gotoAndStop_thunk  display_v2a_oas_optakAvmThunkNull_thunk

extern AvmBox display_v2a_osoooossd_optakAvmThunkNull_optsAvmThunkConstant_AvmString_96_____pad_____optsAvmThunkConstant_AvmString_97_____rgb_____opti0_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Graphics_beginGradientFill_thunk  display_v2a_osoooossd_optakAvmThunkNull_optsAvmThunkConstant_AvmString_96_____pad_____optsAvmThunkConstant_AvmString_97_____rgb_____opti0_thunk
#define flash_display_Graphics_lineGradientStyle_thunk  display_v2a_osoooossd_optakAvmThunkNull_optsAvmThunkConstant_AvmString_96_____pad_____optsAvmThunkConstant_AvmString_97_____rgb_____opti0_thunk

extern AvmBox display_v2a_odudbsssd_opti0_opti1_optbfalse_optsAvmThunkConstant_AvmString_35_____normal_____optakAvmThunkNull_optakAvmThunkNull_opti3_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Graphics_lineStyle_thunk  display_v2a_odudbsssd_opti0_opti1_optbfalse_optsAvmThunkConstant_AvmString_35_____normal_____optakAvmThunkNull_optakAvmThunkNull_opti3_thunk

extern AvmBox display_v2a_oosb_optakAvmThunkNull_optsAvmThunkConstant_AvmString_238_____auto_____optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Bitmap_private__Init_thunk  display_v2a_oosb_optakAvmThunkNull_optsAvmThunkConstant_AvmString_238_____auto_____optbfalse_thunk

extern AvmBox display_v2a_oou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_fillRect_thunk  display_v2a_oou_thunk

extern AvmBox display_i2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_ShaderJob_height_get_thunk  display_i2a_o_thunk
#define flash_display_LoaderInfo_width_get_thunk  display_i2a_o_thunk
#define flash_display_InteractiveObject_tabIndex_get_thunk  display_i2a_o_thunk
#define flash_display_ShaderInput_width_get_thunk  display_i2a_o_thunk
#define flash_display_ShaderInput_channels_get_thunk  display_i2a_o_thunk
#define flash_display_ShaderInput_height_get_thunk  display_i2a_o_thunk
#define flash_display_MovieClip_framesLoaded_get_thunk  display_i2a_o_thunk
#define flash_display_MovieClip_currentFrame_get_thunk  display_i2a_o_thunk
#define flash_display_ShaderJob_width_get_thunk  display_i2a_o_thunk
#define flash_display_MovieClip_totalFrames_get_thunk  display_i2a_o_thunk
#define flash_display_ShaderParameter_index_get_thunk  display_i2a_o_thunk
#define flash_display_BitmapData_height_get_thunk  display_i2a_o_thunk
#define flash_display_Stage_stageWidth_get_thunk  display_i2a_o_thunk
#define flash_display_ShaderInput_index_get_thunk  display_i2a_o_thunk
#define flash_display_BitmapData_width_get_thunk  display_i2a_o_thunk
#define flash_display_DisplayObjectContainer_numChildren_get_thunk  display_i2a_o_thunk
#define flash_display_Stage_stageHeight_get_thunk  display_i2a_o_thunk
#define flash_display_LoaderInfo_height_get_thunk  display_i2a_o_thunk

extern AvmBox display_v2a_odduibbubo_opti7_optbfalse_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_perlinNoise_thunk  display_v2a_odduibbubo_opti7_optbfalse_optakAvmThunkNull_thunk

extern AvmBox display_v2a_ob_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_ShaderJob_start_thunk  display_v2a_ob_optbfalse_thunk

extern AvmBox display_v2a_odddddd_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Graphics_drawRoundRect_thunk  display_v2a_odddddd_thunk

extern AvmBox display_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Graphics_endFill_thunk  display_v2a_o_thunk
#define flash_display_MovieClip_stop_thunk  display_v2a_o_thunk
#define flash_display_Loader_close_thunk  display_v2a_o_thunk
#define flash_display_MovieClip_nextFrame_thunk  display_v2a_o_thunk
#define flash_display_Stage_private_requireOwnerPermissions_thunk  display_v2a_o_thunk
#define flash_display_BitmapData_lock_thunk  display_v2a_o_thunk
#define flash_display_MovieClip_prevFrame_thunk  display_v2a_o_thunk
#define flash_display_Sprite_stopDrag_thunk  display_v2a_o_thunk
#define flash_display_MovieClip_prevScene_thunk  display_v2a_o_thunk
#define flash_display_Sprite_private_constructChildren_thunk  display_v2a_o_thunk
#define flash_display_MovieClip_private__Init_thunk  display_v2a_o_thunk
#define flash_display_Stage_invalidate_thunk  display_v2a_o_thunk
#define flash_display_MovieClip_play_thunk  display_v2a_o_thunk
#define flash_display_SimpleButton_private__updateButton_thunk  display_v2a_o_thunk
#define flash_display_Graphics_clear_thunk  display_v2a_o_thunk
#define flash_display_MovieClip_nextScene_thunk  display_v2a_o_thunk
#define flash_display_BitmapData_dispose_thunk  display_v2a_o_thunk
#define flash_display_ShaderJob_cancel_thunk  display_v2a_o_thunk

extern AvmBox display_v2a_oooos_optakAvmThunkNull_optakAvmThunkNull_optsAvmThunkConstant_AvmString_50_____none_____thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Graphics_drawTriangles_thunk  display_v2a_oooos_optakAvmThunkNull_optakAvmThunkNull_optsAvmThunkConstant_AvmString_50_____none_____thunk

extern AvmBox display_v2a_oooouuuu_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_merge_thunk  display_v2a_oooouuuu_thunk

extern AvmBox display_v2a_oud_opti1_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Graphics_beginFill_thunk  display_v2a_oud_opti1_thunk

extern AvmBox display_u2a_oooosuuub_opti0_opti1_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_threshold_thunk  display_u2a_oooosuuub_opti0_opti1_optbfalse_thunk

extern AvmBox display_v2a_odd_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Graphics_lineTo_thunk  display_v2a_odd_thunk
#define flash_display_Graphics_moveTo_thunk  display_v2a_odd_thunk

extern AvmBox display_b2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObjectContainer_areInaccessibleObjectsUnderPoint_thunk  display_b2a_oo_thunk
#define flash_display_DisplayObjectContainer_contains_thunk  display_b2a_oo_thunk

extern AvmBox display_v2a_ooo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_colorTransform_thunk  display_v2a_ooo_thunk
#define flash_display_DisplayObjectContainer_swapChildren_thunk  display_v2a_ooo_thunk
#define flash_display_BitmapData_setPixels_thunk  display_v2a_ooo_thunk

extern AvmBox display_v2a_oiiu_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_floodFill_thunk  display_v2a_oiiu_thunk
#define flash_display_BitmapData_setPixel32_thunk  display_v2a_oiiu_thunk
#define flash_display_BitmapData_setPixel_thunk  display_v2a_oiiu_thunk

extern AvmBox display_v2a_oiibu_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_private__Init_thunk  display_v2a_oiibu_thunk

extern AvmBox display_v2a_oobood_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Loader_private__load_thunk  display_v2a_oobood_thunk
#define flash_display_Loader_private__loadBytes_thunk  display_v2a_oobood_thunk

extern AvmBox display_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_ShaderInput_input_get_thunk  display_a2a_o_thunk
#define flash_display_BitmapData_clone_thunk  display_a2a_o_thunk
#define flash_display_DisplayObject_stage_get_thunk  display_a2a_o_thunk
#define flash_display_Sprite_dropTarget_get_thunk  display_a2a_o_thunk
#define flash_display_SimpleButton_upState_get_thunk  display_a2a_o_thunk
#define flash_display_LoaderInfo_loader_get_thunk  display_a2a_o_thunk
#define flash_display_LoaderInfo_sharedEvents_get_thunk  display_a2a_o_thunk
#define flash_display_ShaderJob_shader_get_thunk  display_a2a_o_thunk
#define flash_display_DisplayObject_scrollRect_get_thunk  display_a2a_o_thunk
#define flash_display_DisplayObject_scale9Grid_get_thunk  display_a2a_o_thunk
#define flash_display_Bitmap_bitmapData_get_thunk  display_a2a_o_thunk
#define flash_display_MovieClip_scenes_get_thunk  display_a2a_o_thunk
#define flash_display_DisplayObject_accessibilityProperties_get_thunk  display_a2a_o_thunk
#define flash_display_DisplayObject_transform_get_thunk  display_a2a_o_thunk
#define flash_display_SimpleButton_overState_get_thunk  display_a2a_o_thunk
#define flash_display_SimpleButton_downState_get_thunk  display_a2a_o_thunk
#define flash_display_DisplayObject_filters_get_thunk  display_a2a_o_thunk
#define flash_display_Stage_fullScreenSourceRect_get_thunk  display_a2a_o_thunk
#define flash_display_Sprite_hitArea_get_thunk  display_a2a_o_thunk
#define flash_display_LoaderInfo_applicationDomain_get_thunk  display_a2a_o_thunk
#define flash_display_LoaderInfo_content_get_thunk  display_a2a_o_thunk
#define flash_display_LoaderInfo_private__getArgs_thunk  display_a2a_o_thunk
#define flash_display_Loader_contentLoaderInfo_get_thunk  display_a2a_o_thunk
#define flash_display_Shader_data_get_thunk  display_a2a_o_thunk
#define flash_display_ShaderJob_target_get_thunk  display_a2a_o_thunk
#define flash_display_Stage_focus_get_thunk  display_a2a_o_thunk
#define flash_display_ShaderParameter_value_get_thunk  display_a2a_o_thunk
#define flash_display_Loader_content_get_thunk  display_a2a_o_thunk
#define flash_display_DisplayObjectContainer_textSnapshot_get_thunk  display_a2a_o_thunk
#define flash_display_InteractiveObject_accessibilityImplementation_get_thunk  display_a2a_o_thunk
#define flash_display_Sprite_soundTransform_get_thunk  display_a2a_o_thunk
#define flash_display_DisplayObject_opaqueBackground_get_thunk  display_a2a_o_thunk
#define flash_display_Shape_graphics_get_thunk  display_a2a_o_thunk
#define flash_display_InteractiveObject_contextMenu_get_thunk  display_a2a_o_thunk
#define flash_display_Sprite_graphics_get_thunk  display_a2a_o_thunk
#define flash_display_SimpleButton_hitTestState_get_thunk  display_a2a_o_thunk
#define flash_display_DisplayObject_root_get_thunk  display_a2a_o_thunk
#define flash_display_SimpleButton_soundTransform_get_thunk  display_a2a_o_thunk
#define flash_display_LoaderInfo_bytes_get_thunk  display_a2a_o_thunk
#define flash_display_MovieClip_currentScene_get_thunk  display_a2a_o_thunk
#define flash_display_DisplayObject_loaderInfo_get_thunk  display_a2a_o_thunk
#define flash_display_DisplayObject_parent_get_thunk  display_a2a_o_thunk
#define flash_display_DisplayObject_mask_get_thunk  display_a2a_o_thunk
#define flash_display_InteractiveObject_focusRect_get_thunk  display_a2a_o_thunk

extern AvmBox display_v2a_oii_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Stage_swapChildrenAt_thunk  display_v2a_oii_thunk
#define flash_display_BitmapData_scroll_thunk  display_v2a_oii_thunk
#define flash_display_DisplayObjectContainer_swapChildrenAt_thunk  display_v2a_oii_thunk

extern AvmBox display_v2a_ooo_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Graphics_lineShaderStyle_thunk  display_v2a_ooo_optakAvmThunkNull_thunk
#define flash_display_Graphics_beginShaderFill_thunk  display_v2a_ooo_optakAvmThunkNull_thunk

extern AvmBox display_v2a_ooiiii_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_private__setVector_thunk  display_v2a_ooiiii_thunk

extern AvmBox display_v2a_obo_optbfalse_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Sprite_startDrag_thunk  display_v2a_obo_optbfalse_optakAvmThunkNull_thunk

extern AvmBox display_v2a_ooos_optsAvmThunkConstant_AvmString_91_____evenOdd_____thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Graphics_drawPath_thunk  display_v2a_ooos_optsAvmThunkConstant_AvmString_91_____evenOdd_____thunk

extern AvmBox display_i2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObjectContainer_getChildIndex_thunk  display_i2a_oo_thunk

extern AvmBox display_b2a_oouaou_optakAvmThunkNull_opti1_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_hitTest_thunk  display_b2a_oouaou_optakAvmThunkNull_opti1_thunk

extern AvmBox display_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObject_rotationY_set_thunk  display_v2a_od_thunk
#define flash_display_DisplayObject_z_set_thunk  display_v2a_od_thunk
#define flash_display_DisplayObject_rotation_set_thunk  display_v2a_od_thunk
#define flash_display_DisplayObject_scaleY_set_thunk  display_v2a_od_thunk
#define flash_display_Stage_frameRate_set_thunk  display_v2a_od_thunk
#define flash_display_DisplayObject_scaleZ_set_thunk  display_v2a_od_thunk
#define flash_display_DisplayObject_y_set_thunk  display_v2a_od_thunk
#define flash_display_DisplayObject_width_set_thunk  display_v2a_od_thunk
#define flash_display_DisplayObject_scaleX_set_thunk  display_v2a_od_thunk
#define flash_display_DisplayObject_rotationX_set_thunk  display_v2a_od_thunk
#define flash_display_DisplayObject_x_set_thunk  display_v2a_od_thunk
#define flash_display_DisplayObject_alpha_set_thunk  display_v2a_od_thunk
#define flash_display_DisplayObject_height_set_thunk  display_v2a_od_thunk
#define flash_display_DisplayObject_rotationZ_set_thunk  display_v2a_od_thunk

extern AvmBox display_v2a_ob_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_SimpleButton_trackAsMenu_set_thunk  display_v2a_ob_thunk
#define flash_display_DisplayObjectContainer_tabChildren_set_thunk  display_v2a_ob_thunk
#define flash_display_DisplayObjectContainer_mouseChildren_set_thunk  display_v2a_ob_thunk
#define flash_display_Stage_showDefaultContextMenu_set_thunk  display_v2a_ob_thunk
#define flash_display_DisplayObject_cacheAsBitmap_set_thunk  display_v2a_ob_thunk
#define flash_display_SimpleButton_useHandCursor_set_thunk  display_v2a_ob_thunk
#define flash_display_Bitmap_smoothing_set_thunk  display_v2a_ob_thunk
#define flash_display_SimpleButton_enabled_set_thunk  display_v2a_ob_thunk
#define flash_display_DisplayObject_visible_set_thunk  display_v2a_ob_thunk
#define flash_display_Sprite_useHandCursor_set_thunk  display_v2a_ob_thunk
#define flash_display_Sprite_buttonMode_set_thunk  display_v2a_ob_thunk
#define flash_display_InteractiveObject_doubleClickEnabled_set_thunk  display_v2a_ob_thunk
#define flash_display_InteractiveObject_mouseEnabled_set_thunk  display_v2a_ob_thunk
#define flash_display_Stage_stageFocusRect_set_thunk  display_v2a_ob_thunk
#define flash_display_MovieClip_trackAsMenu_set_thunk  display_v2a_ob_thunk
#define flash_display_MovieClip_enabled_set_thunk  display_v2a_ob_thunk
#define flash_display_InteractiveObject_tabEnabled_set_thunk  display_v2a_ob_thunk

extern AvmBox display_v2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObject_opaqueBackground_set_thunk  display_v2a_oa_thunk
#define flash_display_ShaderJob_target_set_thunk  display_v2a_oa_thunk
#define flash_display_InteractiveObject_focusRect_set_thunk  display_v2a_oa_thunk
#define flash_display_ShaderInput_input_set_thunk  display_v2a_oa_thunk

extern double display_d2d_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Loader_private__getJPEGLoaderContextdeblockingfilter_thunk  display_d2d_oa_thunk

extern AvmBox display_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObject_transform_set_thunk  display_v2a_oo_thunk
#define flash_display_SimpleButton_overState_set_thunk  display_v2a_oo_thunk
#define flash_display_ShaderParameter_value_set_thunk  display_v2a_oo_thunk
#define flash_display_SimpleButton_hitTestState_set_thunk  display_v2a_oo_thunk
#define flash_display_DisplayObject_mask_set_thunk  display_v2a_oo_thunk
#define flash_display_DisplayObject_blendShader_set_thunk  display_v2a_oo_thunk
#define flash_display_AVM1Movie_private__setCallAS3_thunk  display_v2a_oo_thunk
#define flash_display_SimpleButton_soundTransform_set_thunk  display_v2a_oo_thunk
#define flash_display_Stage_focus_set_thunk  display_v2a_oo_thunk
#define flash_display_Bitmap_bitmapData_set_thunk  display_v2a_oo_thunk
#define flash_display_InteractiveObject_accessibilityImplementation_set_thunk  display_v2a_oo_thunk
#define flash_display_Graphics_copyFrom_thunk  display_v2a_oo_thunk
#define flash_display_DisplayObject_scale9Grid_set_thunk  display_v2a_oo_thunk
#define flash_display_DisplayObject_accessibilityProperties_set_thunk  display_v2a_oo_thunk
#define flash_display_ShaderData_private__setByteCode_thunk  display_v2a_oo_thunk
#define flash_display_Stage_fullScreenSourceRect_set_thunk  display_v2a_oo_thunk
#define flash_display_DisplayObject_scrollRect_set_thunk  display_v2a_oo_thunk
#define flash_display_SimpleButton_downState_set_thunk  display_v2a_oo_thunk
#define flash_display_Shader_data_set_thunk  display_v2a_oo_thunk
#define flash_display_Sprite_hitArea_set_thunk  display_v2a_oo_thunk
#define flash_display_SimpleButton_upState_set_thunk  display_v2a_oo_thunk
#define flash_display_DisplayObject_filters_set_thunk  display_v2a_oo_thunk
#define flash_display_ShaderJob_shader_set_thunk  display_v2a_oo_thunk
#define flash_display_InteractiveObject_contextMenu_set_thunk  display_v2a_oo_thunk
#define flash_display_Sprite_soundTransform_set_thunk  display_v2a_oo_thunk

extern AvmBox display_a2a_oo_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_histogram_thunk  display_a2a_oo_optakAvmThunkNull_thunk

extern AvmBox display_v2a_oi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Stage_stageHeight_set_thunk  display_v2a_oi_thunk
#define flash_display_Stage_stageWidth_set_thunk  display_v2a_oi_thunk
#define flash_display_ShaderJob_height_set_thunk  display_v2a_oi_thunk
#define flash_display_ShaderInput_width_set_thunk  display_v2a_oi_thunk
#define flash_display_ShaderInput_height_set_thunk  display_v2a_oi_thunk
#define flash_display_ShaderJob_width_set_thunk  display_v2a_oi_thunk
#define flash_display_InteractiveObject_tabIndex_set_thunk  display_v2a_oi_thunk

extern AvmBox display_b2a_obddbo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_DisplayObject_private__hitTest_thunk  display_b2a_obddbo_thunk

extern AvmBox display_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_MovieClip_trackAsMenu_get_thunk  display_b2a_o_thunk
#define flash_display_MovieClip_enabled_get_thunk  display_b2a_o_thunk
#define flash_display_DisplayObjectContainer_mouseChildren_get_thunk  display_b2a_o_thunk
#define flash_display_DisplayObject_cacheAsBitmap_get_thunk  display_b2a_o_thunk
#define flash_display_Bitmap_smoothing_get_thunk  display_b2a_o_thunk
#define flash_display_Sprite_useHandCursor_get_thunk  display_b2a_o_thunk
#define flash_display_Stage_showDefaultContextMenu_get_thunk  display_b2a_o_thunk
#define flash_display_Stage_stageFocusRect_get_thunk  display_b2a_o_thunk
#define flash_display_LoaderInfo_parentAllowsChild_get_thunk  display_b2a_o_thunk
#define flash_display_InteractiveObject_tabEnabled_get_thunk  display_b2a_o_thunk
#define flash_display_InteractiveObject_doubleClickEnabled_get_thunk  display_b2a_o_thunk
#define flash_display_Sprite_buttonMode_get_thunk  display_b2a_o_thunk
#define flash_display_Stage_isFocusInaccessible_thunk  display_b2a_o_thunk
#define flash_display_DisplayObjectContainer_tabChildren_get_thunk  display_b2a_o_thunk
#define flash_display_DisplayObject_visible_get_thunk  display_b2a_o_thunk
#define flash_display_AVM1Movie_private__interopAvailable_get_thunk  display_b2a_o_thunk
#define flash_display_LoaderInfo_sameDomain_get_thunk  display_b2a_o_thunk
#define flash_display_BitmapData_transparent_get_thunk  display_b2a_o_thunk
#define flash_display_SimpleButton_useHandCursor_get_thunk  display_b2a_o_thunk
#define flash_display_InteractiveObject_mouseEnabled_get_thunk  display_b2a_o_thunk
#define flash_display_SimpleButton_enabled_get_thunk  display_b2a_o_thunk
#define flash_display_LoaderInfo_childAllowsParent_get_thunk  display_b2a_o_thunk
#define flash_display_SimpleButton_trackAsMenu_get_thunk  display_b2a_o_thunk

extern AvmBox display_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_Shader_precisionHint_set_thunk  display_v2a_os_thunk
#define flash_display_Stage_quality_set_thunk  display_v2a_os_thunk
#define flash_display_Stage_displayState_set_thunk  display_v2a_os_thunk
#define flash_display_Stage_scaleMode_set_thunk  display_v2a_os_thunk
#define flash_display_DisplayObject_name_set_thunk  display_v2a_os_thunk
#define flash_display_Bitmap_pixelSnapping_set_thunk  display_v2a_os_thunk
#define flash_display_Stage_align_set_thunk  display_v2a_os_thunk
#define flash_display_Stage_colorCorrection_set_thunk  display_v2a_os_thunk
#define flash_display_DisplayObject_blendMode_set_thunk  display_v2a_os_thunk

extern AvmBox display_v2a_oo_optakAvmThunkNull_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_display_BitmapData_unlock_thunk  display_v2a_oo_optakAvmThunkNull_thunk

class SlotOffsetsAndAsserts;
// flash.display::Graphics$
//-----------------------------------------------------------
class GraphicsClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_GraphicsClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::GraphicsClassSlots EmptySlotsStruct_GraphicsClass
//-----------------------------------------------------------

// flash.display::Graphics
//-----------------------------------------------------------
class GraphicsObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_GraphicsObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::GraphicsObjectSlots EmptySlotsStruct_GraphicsObject
//-----------------------------------------------------------

// flash.display::LoaderInfo$
//-----------------------------------------------------------
class LoaderInfoClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_LoaderInfoClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::LoaderInfoClassSlots EmptySlotsStruct_LoaderInfoClass
//-----------------------------------------------------------

// flash.display::LoaderInfo
//-----------------------------------------------------------
class LoaderInfoObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_LoaderInfoObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::LoaderInfoObjectSlots EmptySlotsStruct_LoaderInfoObject
//-----------------------------------------------------------

// flash.display::Shader$
//-----------------------------------------------------------
class ShaderClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShaderClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShaderClassSlots EmptySlotsStruct_ShaderClass
//-----------------------------------------------------------

// flash.display::Shader
//-----------------------------------------------------------
class ShaderObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShaderObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShaderObjectSlots EmptySlotsStruct_ShaderObject
//-----------------------------------------------------------

// flash.display::ShaderData$
//-----------------------------------------------------------
class ShaderDataClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShaderDataClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShaderDataClassSlots EmptySlotsStruct_ShaderDataClass
//-----------------------------------------------------------

// flash.display::ShaderData
//-----------------------------------------------------------
class ShaderDataObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShaderDataObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShaderDataObjectSlots EmptySlotsStruct_ShaderDataObject
//-----------------------------------------------------------

// flash.display::ShaderInput$
//-----------------------------------------------------------
class ShaderInputClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShaderInputClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShaderInputClassSlots EmptySlotsStruct_ShaderInputClass
//-----------------------------------------------------------

// flash.display::ShaderInput
//-----------------------------------------------------------
class ShaderInputObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShaderInputObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShaderInputObjectSlots EmptySlotsStruct_ShaderInputObject
//-----------------------------------------------------------

// flash.display::ShaderJob$
//-----------------------------------------------------------
class ShaderJobClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShaderJobClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShaderJobClassSlots EmptySlotsStruct_ShaderJobClass
//-----------------------------------------------------------

// flash.display::ShaderJob
//-----------------------------------------------------------
class ShaderJobObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShaderJobObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShaderJobObjectSlots EmptySlotsStruct_ShaderJobObject
//-----------------------------------------------------------

// flash.display::ShaderParameter$
//-----------------------------------------------------------
class ShaderParameterClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShaderParameterClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShaderParameterClassSlots EmptySlotsStruct_ShaderParameterClass
//-----------------------------------------------------------

// flash.display::ShaderParameter
//-----------------------------------------------------------
class ShaderParameterObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShaderParameterObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShaderParameterObjectSlots EmptySlotsStruct_ShaderParameterObject
//-----------------------------------------------------------

// flash.display::DisplayObject$
//-----------------------------------------------------------
class DisplayObjectClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_DisplayObjectClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::DisplayObjectClassSlots EmptySlotsStruct_DisplayObjectClass
//-----------------------------------------------------------

// flash.display::DisplayObject
//-----------------------------------------------------------
class DisplayObjectObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_DisplayObjectObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::DisplayObjectObjectSlots EmptySlotsStruct_DisplayObjectObject
//-----------------------------------------------------------

// flash.display::BitmapData$
//-----------------------------------------------------------
class BitmapDataClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_BitmapDataClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::BitmapDataClassSlots EmptySlotsStruct_BitmapDataClass
//-----------------------------------------------------------

// flash.display::BitmapData
//-----------------------------------------------------------
class BitmapDataObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_BitmapDataObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::BitmapDataObjectSlots EmptySlotsStruct_BitmapDataObject
//-----------------------------------------------------------

// flash.display::AVM1Movie$
//-----------------------------------------------------------
class AVM1MovieClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_AVM1MovieClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::AVM1MovieClassSlots EmptySlotsStruct_AVM1MovieClass
//-----------------------------------------------------------

// flash.display::AVM1Movie
//-----------------------------------------------------------
class AVM1MovieObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmBox get_private_callbackTable() const { return m_private_callbackTable; }
    void set_private_callbackTable(AVM1MovieObject* obj, AvmBox newVal);
private:
    ATOM_WB m_private_callbackTable;
};
REALLY_INLINE void AVM1MovieObjectSlots::set_private_callbackTable(AVM1MovieObject* obj, AvmBox newVal)
{
    m_private_callbackTable.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_AVM1MovieObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmBox get_private_callbackTable() const { return m_slots_AVM1MovieObject.get_private_callbackTable(); } \
        REALLY_INLINE void set_private_callbackTable(AvmBox newVal) { m_slots_AVM1MovieObject.set_private_callbackTable(this, newVal); } \
    private: \
        avmplus::NativeID::AVM1MovieObjectSlots m_slots_AVM1MovieObject
//-----------------------------------------------------------

// flash.display::Bitmap$
//-----------------------------------------------------------
class BitmapClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_BitmapClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::BitmapClassSlots EmptySlotsStruct_BitmapClass
//-----------------------------------------------------------

// flash.display::Bitmap
//-----------------------------------------------------------
class BitmapObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_BitmapObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::BitmapObjectSlots EmptySlotsStruct_BitmapObject
//-----------------------------------------------------------

// flash.display::InteractiveObject$
//-----------------------------------------------------------
class InteractiveObjectClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_InteractiveObjectClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::InteractiveObjectClassSlots EmptySlotsStruct_InteractiveObjectClass
//-----------------------------------------------------------

// flash.display::InteractiveObject
//-----------------------------------------------------------
class InteractiveObjectObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_InteractiveObjectObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::InteractiveObjectObjectSlots EmptySlotsStruct_InteractiveObjectObject
//-----------------------------------------------------------

// flash.display::MorphShape$
//-----------------------------------------------------------
class MorphShapeClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_MorphShapeClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::MorphShapeClassSlots EmptySlotsStruct_MorphShapeClass
//-----------------------------------------------------------

// flash.display::MorphShape
//-----------------------------------------------------------
class MorphShapeObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_MorphShapeObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::MorphShapeObjectSlots EmptySlotsStruct_MorphShapeObject
//-----------------------------------------------------------

// flash.display::Shape$
//-----------------------------------------------------------
class ShapeClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShapeClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShapeClassSlots EmptySlotsStruct_ShapeClass
//-----------------------------------------------------------

// flash.display::Shape
//-----------------------------------------------------------
class ShapeObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShapeObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShapeObjectSlots EmptySlotsStruct_ShapeObject
//-----------------------------------------------------------

// flash.display::DisplayObjectContainer$
//-----------------------------------------------------------
class DisplayObjectContainerClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_DisplayObjectContainerClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::DisplayObjectContainerClassSlots EmptySlotsStruct_DisplayObjectContainerClass
//-----------------------------------------------------------

// flash.display::DisplayObjectContainer
//-----------------------------------------------------------
class DisplayObjectContainerObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_DisplayObjectContainerObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::DisplayObjectContainerObjectSlots EmptySlotsStruct_DisplayObjectContainerObject
//-----------------------------------------------------------

// flash.display::SimpleButton$
//-----------------------------------------------------------
class SimpleButtonClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SimpleButtonClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SimpleButtonClassSlots EmptySlotsStruct_SimpleButtonClass
//-----------------------------------------------------------

// flash.display::SimpleButton
//-----------------------------------------------------------
class SimpleButtonObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SimpleButtonObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SimpleButtonObjectSlots EmptySlotsStruct_SimpleButtonObject
//-----------------------------------------------------------

// flash.display::Loader$
//-----------------------------------------------------------
class LoaderClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_LoaderClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::LoaderClassSlots EmptySlotsStruct_LoaderClass
//-----------------------------------------------------------

// flash.display::Loader
//-----------------------------------------------------------
class LoaderObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_LoaderObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::LoaderObjectSlots EmptySlotsStruct_LoaderObject
//-----------------------------------------------------------

// flash.display::Sprite$
//-----------------------------------------------------------
class SpriteClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SpriteClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SpriteClassSlots EmptySlotsStruct_SpriteClass
//-----------------------------------------------------------

// flash.display::Sprite
//-----------------------------------------------------------
class SpriteObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SpriteObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SpriteObjectSlots EmptySlotsStruct_SpriteObject
//-----------------------------------------------------------

// flash.display::Stage$
//-----------------------------------------------------------
class StageClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_StageClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::StageClassSlots EmptySlotsStruct_StageClass
//-----------------------------------------------------------

// flash.display::Stage
//-----------------------------------------------------------
class StageObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_StageObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::StageObjectSlots EmptySlotsStruct_StageObject
//-----------------------------------------------------------

// flash.display::MovieClip$
//-----------------------------------------------------------
class MovieClipClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_MovieClipClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::MovieClipClassSlots EmptySlotsStruct_MovieClipClass
//-----------------------------------------------------------

// flash.display::MovieClip
//-----------------------------------------------------------
class MovieClipObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_MovieClipObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::MovieClipObjectSlots EmptySlotsStruct_MovieClipObject
//-----------------------------------------------------------

} }
