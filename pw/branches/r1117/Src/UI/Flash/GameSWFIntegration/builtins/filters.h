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
    class BevelFilterClass; //flash.filters::BevelFilter$
    class BevelFilterObject; //flash.filters::BevelFilter
    class BitmapFilterClass; //flash.filters::BitmapFilter$
    class BitmapFilterObject; //flash.filters::BitmapFilter
    class BlurFilterClass; //flash.filters::BlurFilter$
    class BlurFilterObject; //flash.filters::BlurFilter
    class ColorMatrixFilterClass; //flash.filters::ColorMatrixFilter$
    class ColorMatrixFilterObject; //flash.filters::ColorMatrixFilter
    class ConvolutionFilterClass; //flash.filters::ConvolutionFilter$
    class ConvolutionFilterObject; //flash.filters::ConvolutionFilter
    class DisplacementMapFilterClass; //flash.filters::DisplacementMapFilter$
    class DisplacementMapFilterObject; //flash.filters::DisplacementMapFilter
    class DropShadowFilterClass; //flash.filters::DropShadowFilter$
    class DropShadowFilterObject; //flash.filters::DropShadowFilter
    class GlowFilterClass; //flash.filters::GlowFilter$
    class GlowFilterObject; //flash.filters::GlowFilter
    class GradientBevelFilterClass; //flash.filters::GradientBevelFilter$
    class GradientBevelFilterObject; //flash.filters::GradientBevelFilter
    class GradientGlowFilterClass; //flash.filters::GradientGlowFilter$
    class GradientGlowFilterObject; //flash.filters::GradientGlowFilter
    class ShaderFilterClass; //flash.filters::ShaderFilter$
    class ShaderFilterObject; //flash.filters::ShaderFilter
}

namespace avmplus { namespace NativeID {

extern const uint32_t filters_abc_class_count;
extern const uint32_t filters_abc_script_count;
extern const uint32_t filters_abc_method_count;
extern const uint32_t filters_abc_length;
extern const uint8_t filters_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(filters)

/* classes */
const uint32_t abcclass_flash_filters_BitmapFilter = 0;
const uint32_t abcclass_flash_filters_BitmapFilterQuality = 1;
const uint32_t abcclass_flash_filters_BitmapFilterType = 2;
const uint32_t abcclass_flash_filters_DisplacementMapFilterMode = 3;
const uint32_t abcclass_flash_filters_BevelFilter = 4;
const uint32_t abcclass_flash_filters_BlurFilter = 5;
const uint32_t abcclass_flash_filters_ColorMatrixFilter = 6;
const uint32_t abcclass_flash_filters_ConvolutionFilter = 7;
const uint32_t abcclass_flash_filters_DisplacementMapFilter = 8;
const uint32_t abcclass_flash_filters_DropShadowFilter = 9;
const uint32_t abcclass_flash_filters_GlowFilter = 10;
const uint32_t abcclass_flash_filters_GradientBevelFilter = 11;
const uint32_t abcclass_flash_filters_GradientGlowFilter = 12;
const uint32_t abcclass_flash_filters_ShaderFilter = 13;

/* methods */
const uint32_t flash_filters_BevelFilter_strength_get = 11;
const uint32_t flash_filters_BevelFilter_strength_set = 12;
const uint32_t flash_filters_BevelFilter_shadowColor_set = 13;
const uint32_t flash_filters_BevelFilter_knockout_get = 14;
const uint32_t flash_filters_BevelFilter_highlightAlpha_get = 15;
const uint32_t flash_filters_BevelFilter_highlightColor_get = 16;
const uint32_t flash_filters_BevelFilter_blurX_get = 17;
const uint32_t flash_filters_BevelFilter_blurY_get = 18;
const uint32_t flash_filters_BevelFilter_angle_get = 19;
const uint32_t flash_filters_BevelFilter_highlightAlpha_set = 20;
const uint32_t flash_filters_BevelFilter_highlightColor_set = 22;
const uint32_t flash_filters_BevelFilter_blurX_set = 23;
const uint32_t flash_filters_BevelFilter_shadowColor_get = 24;
const uint32_t flash_filters_BevelFilter_blurY_set = 25;
const uint32_t flash_filters_BevelFilter_shadowAlpha_get = 26;
const uint32_t flash_filters_BevelFilter_angle_set = 27;
const uint32_t flash_filters_BevelFilter_distance_set = 28;
const uint32_t flash_filters_BevelFilter_type_set = 29;
const uint32_t flash_filters_BevelFilter_distance_get = 30;
const uint32_t flash_filters_BevelFilter_type_get = 31;
const uint32_t flash_filters_BevelFilter_knockout_set = 32;
const uint32_t flash_filters_BevelFilter_shadowAlpha_set = 33;
const uint32_t flash_filters_BevelFilter_quality_set = 34;
const uint32_t flash_filters_BevelFilter_quality_get = 35;
const uint32_t flash_filters_BlurFilter_blurX_get = 38;
const uint32_t flash_filters_BlurFilter_blurX_set = 39;
const uint32_t flash_filters_BlurFilter_blurY_set = 40;
const uint32_t flash_filters_BlurFilter_blurY_get = 41;
const uint32_t flash_filters_BlurFilter_quality_set = 43;
const uint32_t flash_filters_BlurFilter_quality_get = 44;
const uint32_t flash_filters_ColorMatrixFilter_matrix_get = 47;
const uint32_t flash_filters_ColorMatrixFilter_matrix_set = 48;
const uint32_t flash_filters_ConvolutionFilter_matrix_get = 52;
const uint32_t flash_filters_ConvolutionFilter_matrix_set = 53;
const uint32_t flash_filters_ConvolutionFilter_color_get = 54;
const uint32_t flash_filters_ConvolutionFilter_preserveAlpha_set = 55;
const uint32_t flash_filters_ConvolutionFilter_alpha_get = 56;
const uint32_t flash_filters_ConvolutionFilter_color_set = 57;
const uint32_t flash_filters_ConvolutionFilter_bias_set = 58;
const uint32_t flash_filters_ConvolutionFilter_alpha_set = 59;
const uint32_t flash_filters_ConvolutionFilter_matrixX_set = 60;
const uint32_t flash_filters_ConvolutionFilter_matrixY_set = 61;
const uint32_t flash_filters_ConvolutionFilter_preserveAlpha_get = 62;
const uint32_t flash_filters_ConvolutionFilter_clamp_set = 63;
const uint32_t flash_filters_ConvolutionFilter_matrixX_get = 64;
const uint32_t flash_filters_ConvolutionFilter_matrixY_get = 65;
const uint32_t flash_filters_ConvolutionFilter_bias_get = 66;
const uint32_t flash_filters_ConvolutionFilter_clamp_get = 67;
const uint32_t flash_filters_ConvolutionFilter_divisor_set = 68;
const uint32_t flash_filters_ConvolutionFilter_divisor_get = 70;
const uint32_t flash_filters_DisplacementMapFilter_componentY_get = 73;
const uint32_t flash_filters_DisplacementMapFilter_alpha_get = 75;
const uint32_t flash_filters_DisplacementMapFilter_mode_set = 76;
const uint32_t flash_filters_DisplacementMapFilter_mapPoint_set = 77;
const uint32_t flash_filters_DisplacementMapFilter_alpha_set = 78;
const uint32_t flash_filters_DisplacementMapFilter_mode_get = 79;
const uint32_t flash_filters_DisplacementMapFilter_mapBitmap_get = 80;
const uint32_t flash_filters_DisplacementMapFilter_color_set = 81;
const uint32_t flash_filters_DisplacementMapFilter_scaleX_get = 82;
const uint32_t flash_filters_DisplacementMapFilter_scaleY_get = 83;
const uint32_t flash_filters_DisplacementMapFilter_color_get = 84;
const uint32_t flash_filters_DisplacementMapFilter_mapPoint_get = 85;
const uint32_t flash_filters_DisplacementMapFilter_componentX_set = 86;
const uint32_t flash_filters_DisplacementMapFilter_componentY_set = 87;
const uint32_t flash_filters_DisplacementMapFilter_componentX_get = 88;
const uint32_t flash_filters_DisplacementMapFilter_scaleX_set = 89;
const uint32_t flash_filters_DisplacementMapFilter_mapBitmap_set = 90;
const uint32_t flash_filters_DisplacementMapFilter_scaleY_set = 91;
const uint32_t flash_filters_DropShadowFilter_hideObject_get = 94;
const uint32_t flash_filters_DropShadowFilter_blurX_set = 95;
const uint32_t flash_filters_DropShadowFilter_color_get = 96;
const uint32_t flash_filters_DropShadowFilter_blurY_set = 97;
const uint32_t flash_filters_DropShadowFilter_quality_set = 98;
const uint32_t flash_filters_DropShadowFilter_angle_set = 99;
const uint32_t flash_filters_DropShadowFilter_strength_get = 100;
const uint32_t flash_filters_DropShadowFilter_hideObject_set = 101;
const uint32_t flash_filters_DropShadowFilter_distance_set = 102;
const uint32_t flash_filters_DropShadowFilter_inner_set = 103;
const uint32_t flash_filters_DropShadowFilter_color_set = 104;
const uint32_t flash_filters_DropShadowFilter_strength_set = 105;
const uint32_t flash_filters_DropShadowFilter_blurX_get = 106;
const uint32_t flash_filters_DropShadowFilter_blurY_get = 107;
const uint32_t flash_filters_DropShadowFilter_angle_get = 108;
const uint32_t flash_filters_DropShadowFilter_knockout_set = 109;
const uint32_t flash_filters_DropShadowFilter_distance_get = 110;
const uint32_t flash_filters_DropShadowFilter_inner_get = 111;
const uint32_t flash_filters_DropShadowFilter_knockout_get = 112;
const uint32_t flash_filters_DropShadowFilter_alpha_set = 113;
const uint32_t flash_filters_DropShadowFilter_alpha_get = 115;
const uint32_t flash_filters_DropShadowFilter_quality_get = 116;
const uint32_t flash_filters_GlowFilter_strength_get = 119;
const uint32_t flash_filters_GlowFilter_blurX_set = 120;
const uint32_t flash_filters_GlowFilter_color_get = 121;
const uint32_t flash_filters_GlowFilter_blurY_set = 122;
const uint32_t flash_filters_GlowFilter_quality_set = 123;
const uint32_t flash_filters_GlowFilter_color_set = 124;
const uint32_t flash_filters_GlowFilter_strength_set = 125;
const uint32_t flash_filters_GlowFilter_inner_set = 126;
const uint32_t flash_filters_GlowFilter_blurX_get = 127;
const uint32_t flash_filters_GlowFilter_blurY_get = 128;
const uint32_t flash_filters_GlowFilter_knockout_set = 129;
const uint32_t flash_filters_GlowFilter_inner_get = 130;
const uint32_t flash_filters_GlowFilter_knockout_get = 131;
const uint32_t flash_filters_GlowFilter_alpha_set = 132;
const uint32_t flash_filters_GlowFilter_alpha_get = 134;
const uint32_t flash_filters_GlowFilter_quality_get = 135;
const uint32_t flash_filters_GradientBevelFilter_colors_set = 138;
const uint32_t flash_filters_GradientBevelFilter_strength_get = 139;
const uint32_t flash_filters_GradientBevelFilter_blurX_set = 140;
const uint32_t flash_filters_GradientBevelFilter_blurY_set = 141;
const uint32_t flash_filters_GradientBevelFilter_angle_set = 142;
const uint32_t flash_filters_GradientBevelFilter_type_get = 143;
const uint32_t flash_filters_GradientBevelFilter_ratios_get = 144;
const uint32_t flash_filters_GradientBevelFilter_strength_set = 145;
const uint32_t flash_filters_GradientBevelFilter_alphas_set = 146;
const uint32_t flash_filters_GradientBevelFilter_colors_get = 147;
const uint32_t flash_filters_GradientBevelFilter_blurX_get = 148;
const uint32_t flash_filters_GradientBevelFilter_blurY_get = 149;
const uint32_t flash_filters_GradientBevelFilter_angle_get = 150;
const uint32_t flash_filters_GradientBevelFilter_knockout_set = 151;
const uint32_t flash_filters_GradientBevelFilter_distance_get = 152;
const uint32_t flash_filters_GradientBevelFilter_ratios_set = 153;
const uint32_t flash_filters_GradientBevelFilter_distance_set = 154;
const uint32_t flash_filters_GradientBevelFilter_knockout_get = 155;
const uint32_t flash_filters_GradientBevelFilter_type_set = 156;
const uint32_t flash_filters_GradientBevelFilter_alphas_get = 157;
const uint32_t flash_filters_GradientBevelFilter_quality_set = 159;
const uint32_t flash_filters_GradientBevelFilter_quality_get = 160;
const uint32_t flash_filters_GradientGlowFilter_colors_set = 163;
const uint32_t flash_filters_GradientGlowFilter_strength_get = 164;
const uint32_t flash_filters_GradientGlowFilter_blurX_set = 165;
const uint32_t flash_filters_GradientGlowFilter_blurY_set = 166;
const uint32_t flash_filters_GradientGlowFilter_angle_set = 167;
const uint32_t flash_filters_GradientGlowFilter_type_get = 168;
const uint32_t flash_filters_GradientGlowFilter_ratios_get = 169;
const uint32_t flash_filters_GradientGlowFilter_strength_set = 170;
const uint32_t flash_filters_GradientGlowFilter_alphas_set = 171;
const uint32_t flash_filters_GradientGlowFilter_colors_get = 172;
const uint32_t flash_filters_GradientGlowFilter_blurX_get = 173;
const uint32_t flash_filters_GradientGlowFilter_blurY_get = 174;
const uint32_t flash_filters_GradientGlowFilter_angle_get = 175;
const uint32_t flash_filters_GradientGlowFilter_knockout_set = 176;
const uint32_t flash_filters_GradientGlowFilter_alphas_get = 177;
const uint32_t flash_filters_GradientGlowFilter_ratios_set = 178;
const uint32_t flash_filters_GradientGlowFilter_distance_set = 179;
const uint32_t flash_filters_GradientGlowFilter_knockout_get = 180;
const uint32_t flash_filters_GradientGlowFilter_type_set = 181;
const uint32_t flash_filters_GradientGlowFilter_distance_get = 182;
const uint32_t flash_filters_GradientGlowFilter_quality_set = 184;
const uint32_t flash_filters_GradientGlowFilter_quality_get = 185;
const uint32_t flash_filters_ShaderFilter_private__extendBy_set = 188;
const uint32_t flash_filters_ShaderFilter_shader_get = 190;
const uint32_t flash_filters_ShaderFilter_shader_set = 193;
const uint32_t flash_filters_ShaderFilter_private__extendBy_get = 197;

extern AvmBox filters_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_filters_ConvolutionFilter_divisor_set_thunk  filters_v2a_od_thunk
#define flash_filters_GradientBevelFilter_angle_set_thunk  filters_v2a_od_thunk
#define flash_filters_GradientBevelFilter_distance_set_thunk  filters_v2a_od_thunk
#define flash_filters_GradientGlowFilter_blurX_set_thunk  filters_v2a_od_thunk
#define flash_filters_DropShadowFilter_alpha_set_thunk  filters_v2a_od_thunk
#define flash_filters_BevelFilter_blurX_set_thunk  filters_v2a_od_thunk
#define flash_filters_DropShadowFilter_distance_set_thunk  filters_v2a_od_thunk
#define flash_filters_DropShadowFilter_angle_set_thunk  filters_v2a_od_thunk
#define flash_filters_DisplacementMapFilter_scaleY_set_thunk  filters_v2a_od_thunk
#define flash_filters_ConvolutionFilter_matrixY_set_thunk  filters_v2a_od_thunk
#define flash_filters_DisplacementMapFilter_alpha_set_thunk  filters_v2a_od_thunk
#define flash_filters_BlurFilter_blurX_set_thunk  filters_v2a_od_thunk
#define flash_filters_ConvolutionFilter_bias_set_thunk  filters_v2a_od_thunk
#define flash_filters_ConvolutionFilter_matrixX_set_thunk  filters_v2a_od_thunk
#define flash_filters_GradientGlowFilter_angle_set_thunk  filters_v2a_od_thunk
#define flash_filters_GradientGlowFilter_strength_set_thunk  filters_v2a_od_thunk
#define flash_filters_DropShadowFilter_blurY_set_thunk  filters_v2a_od_thunk
#define flash_filters_GradientBevelFilter_strength_set_thunk  filters_v2a_od_thunk
#define flash_filters_BevelFilter_distance_set_thunk  filters_v2a_od_thunk
#define flash_filters_GradientBevelFilter_blurX_set_thunk  filters_v2a_od_thunk
#define flash_filters_BevelFilter_highlightAlpha_set_thunk  filters_v2a_od_thunk
#define flash_filters_DropShadowFilter_blurX_set_thunk  filters_v2a_od_thunk
#define flash_filters_BevelFilter_strength_set_thunk  filters_v2a_od_thunk
#define flash_filters_BevelFilter_blurY_set_thunk  filters_v2a_od_thunk
#define flash_filters_GlowFilter_blurY_set_thunk  filters_v2a_od_thunk
#define flash_filters_BevelFilter_angle_set_thunk  filters_v2a_od_thunk
#define flash_filters_GradientGlowFilter_blurY_set_thunk  filters_v2a_od_thunk
#define flash_filters_GradientGlowFilter_distance_set_thunk  filters_v2a_od_thunk
#define flash_filters_BevelFilter_shadowAlpha_set_thunk  filters_v2a_od_thunk
#define flash_filters_BlurFilter_blurY_set_thunk  filters_v2a_od_thunk
#define flash_filters_GradientBevelFilter_blurY_set_thunk  filters_v2a_od_thunk
#define flash_filters_DisplacementMapFilter_scaleX_set_thunk  filters_v2a_od_thunk
#define flash_filters_GlowFilter_strength_set_thunk  filters_v2a_od_thunk
#define flash_filters_DropShadowFilter_strength_set_thunk  filters_v2a_od_thunk
#define flash_filters_ConvolutionFilter_alpha_set_thunk  filters_v2a_od_thunk
#define flash_filters_GlowFilter_blurX_set_thunk  filters_v2a_od_thunk
#define flash_filters_GlowFilter_alpha_set_thunk  filters_v2a_od_thunk

extern AvmBox filters_v2a_ob_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_filters_GlowFilter_knockout_set_thunk  filters_v2a_ob_thunk
#define flash_filters_BevelFilter_knockout_set_thunk  filters_v2a_ob_thunk
#define flash_filters_ConvolutionFilter_preserveAlpha_set_thunk  filters_v2a_ob_thunk
#define flash_filters_DropShadowFilter_knockout_set_thunk  filters_v2a_ob_thunk
#define flash_filters_GradientBevelFilter_knockout_set_thunk  filters_v2a_ob_thunk
#define flash_filters_DropShadowFilter_inner_set_thunk  filters_v2a_ob_thunk
#define flash_filters_DropShadowFilter_hideObject_set_thunk  filters_v2a_ob_thunk
#define flash_filters_ConvolutionFilter_clamp_set_thunk  filters_v2a_ob_thunk
#define flash_filters_GlowFilter_inner_set_thunk  filters_v2a_ob_thunk
#define flash_filters_GradientGlowFilter_knockout_set_thunk  filters_v2a_ob_thunk

extern AvmBox filters_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_filters_DisplacementMapFilter_mapPoint_set_thunk  filters_v2a_oo_thunk
#define flash_filters_ShaderFilter_shader_set_thunk  filters_v2a_oo_thunk
#define flash_filters_GradientGlowFilter_ratios_set_thunk  filters_v2a_oo_thunk
#define flash_filters_DisplacementMapFilter_mapBitmap_set_thunk  filters_v2a_oo_thunk
#define flash_filters_ShaderFilter_private__extendBy_set_thunk  filters_v2a_oo_thunk
#define flash_filters_GradientBevelFilter_alphas_set_thunk  filters_v2a_oo_thunk
#define flash_filters_GradientBevelFilter_colors_set_thunk  filters_v2a_oo_thunk
#define flash_filters_ConvolutionFilter_matrix_set_thunk  filters_v2a_oo_thunk
#define flash_filters_GradientBevelFilter_ratios_set_thunk  filters_v2a_oo_thunk
#define flash_filters_GradientGlowFilter_colors_set_thunk  filters_v2a_oo_thunk
#define flash_filters_ColorMatrixFilter_matrix_set_thunk  filters_v2a_oo_thunk
#define flash_filters_GradientGlowFilter_alphas_set_thunk  filters_v2a_oo_thunk

extern AvmBox filters_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_filters_GlowFilter_knockout_get_thunk  filters_b2a_o_thunk
#define flash_filters_DropShadowFilter_knockout_get_thunk  filters_b2a_o_thunk
#define flash_filters_ConvolutionFilter_preserveAlpha_get_thunk  filters_b2a_o_thunk
#define flash_filters_GradientBevelFilter_knockout_get_thunk  filters_b2a_o_thunk
#define flash_filters_DropShadowFilter_inner_get_thunk  filters_b2a_o_thunk
#define flash_filters_DropShadowFilter_hideObject_get_thunk  filters_b2a_o_thunk
#define flash_filters_GradientGlowFilter_knockout_get_thunk  filters_b2a_o_thunk
#define flash_filters_GlowFilter_inner_get_thunk  filters_b2a_o_thunk
#define flash_filters_ConvolutionFilter_clamp_get_thunk  filters_b2a_o_thunk
#define flash_filters_BevelFilter_knockout_get_thunk  filters_b2a_o_thunk

extern AvmBox filters_u2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_filters_DropShadowFilter_color_get_thunk  filters_u2a_o_thunk
#define flash_filters_DisplacementMapFilter_componentX_get_thunk  filters_u2a_o_thunk
#define flash_filters_BevelFilter_highlightColor_get_thunk  filters_u2a_o_thunk
#define flash_filters_BevelFilter_shadowColor_get_thunk  filters_u2a_o_thunk
#define flash_filters_GlowFilter_color_get_thunk  filters_u2a_o_thunk
#define flash_filters_DisplacementMapFilter_componentY_get_thunk  filters_u2a_o_thunk
#define flash_filters_DisplacementMapFilter_color_get_thunk  filters_u2a_o_thunk
#define flash_filters_ConvolutionFilter_color_get_thunk  filters_u2a_o_thunk

extern AvmBox filters_v2a_oi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_filters_GlowFilter_quality_set_thunk  filters_v2a_oi_thunk
#define flash_filters_BlurFilter_quality_set_thunk  filters_v2a_oi_thunk
#define flash_filters_BevelFilter_quality_set_thunk  filters_v2a_oi_thunk
#define flash_filters_GradientBevelFilter_quality_set_thunk  filters_v2a_oi_thunk
#define flash_filters_DropShadowFilter_quality_set_thunk  filters_v2a_oi_thunk
#define flash_filters_GradientGlowFilter_quality_set_thunk  filters_v2a_oi_thunk

extern AvmBox filters_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_filters_DisplacementMapFilter_mapBitmap_get_thunk  filters_a2a_o_thunk
#define flash_filters_GradientGlowFilter_ratios_get_thunk  filters_a2a_o_thunk
#define flash_filters_ShaderFilter_private__extendBy_get_thunk  filters_a2a_o_thunk
#define flash_filters_ConvolutionFilter_matrix_get_thunk  filters_a2a_o_thunk
#define flash_filters_DisplacementMapFilter_mapPoint_get_thunk  filters_a2a_o_thunk
#define flash_filters_GradientGlowFilter_alphas_get_thunk  filters_a2a_o_thunk
#define flash_filters_GradientGlowFilter_colors_get_thunk  filters_a2a_o_thunk
#define flash_filters_GradientBevelFilter_alphas_get_thunk  filters_a2a_o_thunk
#define flash_filters_ShaderFilter_shader_get_thunk  filters_a2a_o_thunk
#define flash_filters_GradientBevelFilter_colors_get_thunk  filters_a2a_o_thunk
#define flash_filters_ColorMatrixFilter_matrix_get_thunk  filters_a2a_o_thunk
#define flash_filters_GradientBevelFilter_ratios_get_thunk  filters_a2a_o_thunk

extern AvmBox filters_v2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_filters_DisplacementMapFilter_componentX_set_thunk  filters_v2a_ou_thunk
#define flash_filters_BevelFilter_highlightColor_set_thunk  filters_v2a_ou_thunk
#define flash_filters_DropShadowFilter_color_set_thunk  filters_v2a_ou_thunk
#define flash_filters_BevelFilter_shadowColor_set_thunk  filters_v2a_ou_thunk
#define flash_filters_GlowFilter_color_set_thunk  filters_v2a_ou_thunk
#define flash_filters_DisplacementMapFilter_color_set_thunk  filters_v2a_ou_thunk
#define flash_filters_DisplacementMapFilter_componentY_set_thunk  filters_v2a_ou_thunk
#define flash_filters_ConvolutionFilter_color_set_thunk  filters_v2a_ou_thunk

extern AvmBox filters_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_filters_DisplacementMapFilter_mode_set_thunk  filters_v2a_os_thunk
#define flash_filters_BevelFilter_type_set_thunk  filters_v2a_os_thunk
#define flash_filters_GradientBevelFilter_type_set_thunk  filters_v2a_os_thunk
#define flash_filters_GradientGlowFilter_type_set_thunk  filters_v2a_os_thunk

extern AvmBox filters_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_filters_GradientBevelFilter_type_get_thunk  filters_s2a_o_thunk
#define flash_filters_DisplacementMapFilter_mode_get_thunk  filters_s2a_o_thunk
#define flash_filters_GradientGlowFilter_type_get_thunk  filters_s2a_o_thunk
#define flash_filters_BevelFilter_type_get_thunk  filters_s2a_o_thunk

extern AvmBox filters_i2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_filters_BlurFilter_quality_get_thunk  filters_i2a_o_thunk
#define flash_filters_GradientBevelFilter_quality_get_thunk  filters_i2a_o_thunk
#define flash_filters_BevelFilter_quality_get_thunk  filters_i2a_o_thunk
#define flash_filters_GlowFilter_quality_get_thunk  filters_i2a_o_thunk
#define flash_filters_GradientGlowFilter_quality_get_thunk  filters_i2a_o_thunk
#define flash_filters_DropShadowFilter_quality_get_thunk  filters_i2a_o_thunk

extern double filters_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_filters_GradientBevelFilter_strength_get_thunk  filters_d2d_o_thunk
#define flash_filters_GlowFilter_blurY_get_thunk  filters_d2d_o_thunk
#define flash_filters_BevelFilter_angle_get_thunk  filters_d2d_o_thunk
#define flash_filters_DropShadowFilter_blurX_get_thunk  filters_d2d_o_thunk
#define flash_filters_BevelFilter_highlightAlpha_get_thunk  filters_d2d_o_thunk
#define flash_filters_BevelFilter_distance_get_thunk  filters_d2d_o_thunk
#define flash_filters_GradientBevelFilter_angle_get_thunk  filters_d2d_o_thunk
#define flash_filters_GlowFilter_alpha_get_thunk  filters_d2d_o_thunk
#define flash_filters_GradientGlowFilter_blurX_get_thunk  filters_d2d_o_thunk
#define flash_filters_BevelFilter_blurY_get_thunk  filters_d2d_o_thunk
#define flash_filters_DropShadowFilter_alpha_get_thunk  filters_d2d_o_thunk
#define flash_filters_GlowFilter_strength_get_thunk  filters_d2d_o_thunk
#define flash_filters_ConvolutionFilter_matrixX_get_thunk  filters_d2d_o_thunk
#define flash_filters_BlurFilter_blurY_get_thunk  filters_d2d_o_thunk
#define flash_filters_DropShadowFilter_distance_get_thunk  filters_d2d_o_thunk
#define flash_filters_BevelFilter_shadowAlpha_get_thunk  filters_d2d_o_thunk
#define flash_filters_DisplacementMapFilter_scaleX_get_thunk  filters_d2d_o_thunk
#define flash_filters_GradientGlowFilter_distance_get_thunk  filters_d2d_o_thunk
#define flash_filters_GradientBevelFilter_blurX_get_thunk  filters_d2d_o_thunk
#define flash_filters_GradientGlowFilter_blurY_get_thunk  filters_d2d_o_thunk
#define flash_filters_BlurFilter_blurX_get_thunk  filters_d2d_o_thunk
#define flash_filters_DisplacementMapFilter_scaleY_get_thunk  filters_d2d_o_thunk
#define flash_filters_GradientGlowFilter_strength_get_thunk  filters_d2d_o_thunk
#define flash_filters_ConvolutionFilter_alpha_get_thunk  filters_d2d_o_thunk
#define flash_filters_GradientBevelFilter_distance_get_thunk  filters_d2d_o_thunk
#define flash_filters_DropShadowFilter_angle_get_thunk  filters_d2d_o_thunk
#define flash_filters_BevelFilter_blurX_get_thunk  filters_d2d_o_thunk
#define flash_filters_DropShadowFilter_strength_get_thunk  filters_d2d_o_thunk
#define flash_filters_ConvolutionFilter_divisor_get_thunk  filters_d2d_o_thunk
#define flash_filters_GlowFilter_blurX_get_thunk  filters_d2d_o_thunk
#define flash_filters_ConvolutionFilter_matrixY_get_thunk  filters_d2d_o_thunk
#define flash_filters_BevelFilter_strength_get_thunk  filters_d2d_o_thunk
#define flash_filters_DropShadowFilter_blurY_get_thunk  filters_d2d_o_thunk
#define flash_filters_GradientGlowFilter_angle_get_thunk  filters_d2d_o_thunk
#define flash_filters_ConvolutionFilter_bias_get_thunk  filters_d2d_o_thunk
#define flash_filters_GradientBevelFilter_blurY_get_thunk  filters_d2d_o_thunk
#define flash_filters_DisplacementMapFilter_alpha_get_thunk  filters_d2d_o_thunk

class SlotOffsetsAndAsserts;
// flash.filters::BitmapFilter$
//-----------------------------------------------------------
class BitmapFilterClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_BitmapFilterClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::BitmapFilterClassSlots EmptySlotsStruct_BitmapFilterClass
//-----------------------------------------------------------

// flash.filters::BitmapFilter
//-----------------------------------------------------------
class BitmapFilterObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_BitmapFilterObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::BitmapFilterObjectSlots EmptySlotsStruct_BitmapFilterObject
//-----------------------------------------------------------

// flash.filters::BevelFilter$
//-----------------------------------------------------------
class BevelFilterClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_BevelFilterClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::BevelFilterClassSlots EmptySlotsStruct_BevelFilterClass
//-----------------------------------------------------------

// flash.filters::BevelFilter
//-----------------------------------------------------------
class BevelFilterObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_BevelFilterObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::BevelFilterObjectSlots EmptySlotsStruct_BevelFilterObject
//-----------------------------------------------------------

// flash.filters::BlurFilter$
//-----------------------------------------------------------
class BlurFilterClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_BlurFilterClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::BlurFilterClassSlots EmptySlotsStruct_BlurFilterClass
//-----------------------------------------------------------

// flash.filters::BlurFilter
//-----------------------------------------------------------
class BlurFilterObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_BlurFilterObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::BlurFilterObjectSlots EmptySlotsStruct_BlurFilterObject
//-----------------------------------------------------------

// flash.filters::ColorMatrixFilter$
//-----------------------------------------------------------
class ColorMatrixFilterClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ColorMatrixFilterClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ColorMatrixFilterClassSlots EmptySlotsStruct_ColorMatrixFilterClass
//-----------------------------------------------------------

// flash.filters::ColorMatrixFilter
//-----------------------------------------------------------
class ColorMatrixFilterObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ColorMatrixFilterObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ColorMatrixFilterObjectSlots EmptySlotsStruct_ColorMatrixFilterObject
//-----------------------------------------------------------

// flash.filters::ConvolutionFilter$
//-----------------------------------------------------------
class ConvolutionFilterClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ConvolutionFilterClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ConvolutionFilterClassSlots EmptySlotsStruct_ConvolutionFilterClass
//-----------------------------------------------------------

// flash.filters::ConvolutionFilter
//-----------------------------------------------------------
class ConvolutionFilterObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ConvolutionFilterObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ConvolutionFilterObjectSlots EmptySlotsStruct_ConvolutionFilterObject
//-----------------------------------------------------------

// flash.filters::DisplacementMapFilter$
//-----------------------------------------------------------
class DisplacementMapFilterClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_DisplacementMapFilterClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::DisplacementMapFilterClassSlots EmptySlotsStruct_DisplacementMapFilterClass
//-----------------------------------------------------------

// flash.filters::DisplacementMapFilter
//-----------------------------------------------------------
class DisplacementMapFilterObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_DisplacementMapFilterObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::DisplacementMapFilterObjectSlots EmptySlotsStruct_DisplacementMapFilterObject
//-----------------------------------------------------------

// flash.filters::DropShadowFilter$
//-----------------------------------------------------------
class DropShadowFilterClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_DropShadowFilterClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::DropShadowFilterClassSlots EmptySlotsStruct_DropShadowFilterClass
//-----------------------------------------------------------

// flash.filters::DropShadowFilter
//-----------------------------------------------------------
class DropShadowFilterObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_DropShadowFilterObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::DropShadowFilterObjectSlots EmptySlotsStruct_DropShadowFilterObject
//-----------------------------------------------------------

// flash.filters::GlowFilter$
//-----------------------------------------------------------
class GlowFilterClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_GlowFilterClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::GlowFilterClassSlots EmptySlotsStruct_GlowFilterClass
//-----------------------------------------------------------

// flash.filters::GlowFilter
//-----------------------------------------------------------
class GlowFilterObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_GlowFilterObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::GlowFilterObjectSlots EmptySlotsStruct_GlowFilterObject
//-----------------------------------------------------------

// flash.filters::GradientBevelFilter$
//-----------------------------------------------------------
class GradientBevelFilterClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_GradientBevelFilterClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::GradientBevelFilterClassSlots EmptySlotsStruct_GradientBevelFilterClass
//-----------------------------------------------------------

// flash.filters::GradientBevelFilter
//-----------------------------------------------------------
class GradientBevelFilterObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_GradientBevelFilterObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::GradientBevelFilterObjectSlots EmptySlotsStruct_GradientBevelFilterObject
//-----------------------------------------------------------

// flash.filters::GradientGlowFilter$
//-----------------------------------------------------------
class GradientGlowFilterClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_GradientGlowFilterClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::GradientGlowFilterClassSlots EmptySlotsStruct_GradientGlowFilterClass
//-----------------------------------------------------------

// flash.filters::GradientGlowFilter
//-----------------------------------------------------------
class GradientGlowFilterObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_GradientGlowFilterObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::GradientGlowFilterObjectSlots EmptySlotsStruct_GradientGlowFilterObject
//-----------------------------------------------------------

// flash.filters::ShaderFilter$
//-----------------------------------------------------------
class ShaderFilterClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShaderFilterClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShaderFilterClassSlots EmptySlotsStruct_ShaderFilterClass
//-----------------------------------------------------------

// flash.filters::ShaderFilter
//-----------------------------------------------------------
class ShaderFilterObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ShaderFilterObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ShaderFilterObjectSlots EmptySlotsStruct_ShaderFilterObject
//-----------------------------------------------------------

} }
