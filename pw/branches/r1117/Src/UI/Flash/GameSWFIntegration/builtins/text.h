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
    class ArrayObject; //Array
    class ContentElementClass; //flash.text.engine::ContentElement$
    class ContentElementObject; //flash.text.engine::ContentElement
    class EastAsianJustifierClass; //flash.text.engine::EastAsianJustifier$
    class EastAsianJustifierObject; //flash.text.engine::EastAsianJustifier
    class ElementFormatClass; //flash.text.engine::ElementFormat$
    class ElementFormatObject; //flash.text.engine::ElementFormat
    class FontClass; //flash.text::Font$
    class FontDescriptionClass; //flash.text.engine::FontDescription$
    class FontDescriptionObject; //flash.text.engine::FontDescription
    class FontObject; //flash.text::Font
    class GraphicElementClass; //flash.text.engine::GraphicElement$
    class GraphicElementObject; //flash.text.engine::GraphicElement
    class GroupElementClass; //flash.text.engine::GroupElement$
    class GroupElementObject; //flash.text.engine::GroupElement
    class SpaceJustifierClass; //flash.text.engine::SpaceJustifier$
    class SpaceJustifierObject; //flash.text.engine::SpaceJustifier
    class StaticTextClass; //flash.text::StaticText$
    class StaticTextObject; //flash.text::StaticText
    class StyleSheetClass; //flash.text::StyleSheet$
    class StyleSheetObject; //flash.text::StyleSheet
    class TabStopClass; //flash.text.engine::TabStop$
    class TabStopObject; //flash.text.engine::TabStop
    class TextBlockClass; //flash.text.engine::TextBlock$
    class TextBlockObject; //flash.text.engine::TextBlock
    class TextElementClass; //flash.text.engine::TextElement$
    class TextElementObject; //flash.text.engine::TextElement
    class TextFieldClass; //flash.text::TextField$
    class TextFieldObject; //flash.text::TextField
    class TextFormatClass; //flash.text::TextFormat$
    class TextFormatObject; //flash.text::TextFormat
    class TextJustifierClass; //flash.text.engine::TextJustifier$
    class TextJustifierObject; //flash.text.engine::TextJustifier
    class TextLineClass; //flash.text.engine::TextLine$
    class TextLineMirrorRegionClass; //flash.text.engine::TextLineMirrorRegion$
    class TextLineMirrorRegionObject; //flash.text.engine::TextLineMirrorRegion
    class TextLineObject; //flash.text.engine::TextLine
    class TextRendererClass; //flash.text::TextRenderer$
    class TextRendererObject; //flash.text::TextRenderer
    class TextSnapshotClass; //flash.text::TextSnapshot$
    class TextSnapshotObject; //flash.text::TextSnapshot
}

namespace avmplus { namespace NativeID {

extern const uint32_t text_abc_class_count;
extern const uint32_t text_abc_script_count;
extern const uint32_t text_abc_method_count;
extern const uint32_t text_abc_length;
extern const uint8_t text_abc_data[];
AVMTHUNK_DECLARE_NATIVE_INITIALIZER(text)

/* classes */
const uint32_t abcclass_flash_text_engine_TextJustifier = 0;
const uint32_t abcclass_flash_text_engine_BreakOpportunity = 1;
const uint32_t abcclass_flash_text_engine_CFFHinting = 2;
const uint32_t abcclass_flash_text_engine_ContentElement = 3;
const uint32_t abcclass_flash_text_engine_DigitCase = 4;
const uint32_t abcclass_flash_text_engine_DigitWidth = 5;
const uint32_t abcclass_flash_text_engine_ElementFormat = 6;
const uint32_t abcclass_flash_text_engine_FontDescription = 7;
const uint32_t abcclass_flash_text_engine_FontLookup = 8;
const uint32_t abcclass_flash_text_engine_FontMetrics = 9;
const uint32_t abcclass_flash_text_engine_FontPosture = 10;
const uint32_t abcclass_flash_text_engine_FontWeight = 11;
const uint32_t abcclass_flash_text_engine_JustificationStyle = 12;
const uint32_t abcclass_flash_text_engine_Kerning = 13;
const uint32_t abcclass_flash_text_engine_LigatureLevel = 14;
const uint32_t abcclass_flash_text_engine_LineJustification = 15;
const uint32_t abcclass_flash_text_engine_RenderingMode = 16;
const uint32_t abcclass_flash_text_engine_TabAlignment = 17;
const uint32_t abcclass_flash_text_engine_TabStop = 18;
const uint32_t abcclass_flash_text_engine_TextBaseline = 19;
const uint32_t abcclass_flash_text_engine_TextBlock = 20;
const uint32_t abcclass_flash_text_engine_TextLine = 21;
const uint32_t abcclass_flash_text_engine_TextLineCreationResult = 22;
const uint32_t abcclass_flash_text_engine_TextLineMirrorRegion = 23;
const uint32_t abcclass_flash_text_engine_TextLineValidity = 24;
const uint32_t abcclass_flash_text_engine_TextRotation = 25;
const uint32_t abcclass_flash_text_engine_TypographicCase = 26;
const uint32_t abcclass_flash_text_AntiAliasType = 27;
const uint32_t abcclass_flash_text_CSMSettings = 28;
const uint32_t abcclass_flash_text_Font = 29;
const uint32_t abcclass_flash_text_FontStyle = 30;
const uint32_t abcclass_flash_text_FontType = 31;
const uint32_t abcclass_flash_text_GridFitType = 32;
const uint32_t abcclass_flash_text_StaticText = 33;
const uint32_t abcclass_flash_text_StyleSheet = 34;
const uint32_t abcclass_flash_text_TextColorType = 35;
const uint32_t abcclass_flash_text_TextDisplayMode = 36;
const uint32_t abcclass_flash_text_TextExtent = 37;
const uint32_t abcclass_flash_text_TextField = 38;
const uint32_t abcclass_flash_text_TextFieldAutoSize = 39;
const uint32_t abcclass_flash_text_TextFieldType = 40;
const uint32_t abcclass_flash_text_TextFormat = 41;
const uint32_t abcclass_flash_text_TextFormatAlign = 42;
const uint32_t abcclass_flash_text_TextFormatDisplay = 43;
const uint32_t abcclass_flash_text_TextLineMetrics = 44;
const uint32_t abcclass_flash_text_TextRenderer = 45;
const uint32_t abcclass_flash_text_TextRun = 46;
const uint32_t abcclass_flash_text_TextSnapshot = 47;
const uint32_t abcclass_flash_text_engine_EastAsianJustifier = 48;
const uint32_t abcclass_flash_text_engine_SpaceJustifier = 49;
const uint32_t abcclass_flash_text_engine_GraphicElement = 50;
const uint32_t abcclass_flash_text_engine_GroupElement = 51;
const uint32_t abcclass_flash_text_engine_TextElement = 52;

/* methods */
const uint32_t flash_text_engine_TextJustifier_lineJustification_set = 3;
const uint32_t flash_text_engine_TextJustifier_locale_get = 4;
const uint32_t flash_text_engine_TextJustifier_private_setLocale = 5;
const uint32_t flash_text_engine_TextJustifier_lineJustification_get = 7;
const uint32_t flash_text_engine_ContentElement_textBlock_get = 14;
const uint32_t flash_text_engine_ContentElement_elementFormat_set = 15;
const uint32_t flash_text_engine_ContentElement_textBlockBeginIndex_get = 16;
const uint32_t flash_text_engine_ContentElement_textRotation_get = 17;
const uint32_t flash_text_engine_ContentElement_text_get = 18;
const uint32_t flash_text_engine_ContentElement_eventMirror_set = 19;
const uint32_t flash_text_engine_ContentElement_elementFormat_get = 20;
const uint32_t flash_text_engine_ContentElement_textRotation_set = 21;
const uint32_t flash_text_engine_ContentElement_eventMirror_get = 22;
const uint32_t flash_text_engine_ContentElement_rawText_get = 23;
const uint32_t flash_text_engine_ContentElement_groupElement_get = 24;
const uint32_t flash_text_engine_ElementFormat_baselineShift_set = 31;
const uint32_t flash_text_engine_ElementFormat_trackingLeft_set = 32;
const uint32_t flash_text_engine_ElementFormat_baselineShift_get = 33;
const uint32_t flash_text_engine_ElementFormat_dominantBaseline_get = 34;
const uint32_t flash_text_engine_ElementFormat_color_set = 35;
const uint32_t flash_text_engine_ElementFormat_alignmentBaseline_get = 36;
const uint32_t flash_text_engine_ElementFormat_dominantBaseline_set = 37;
const uint32_t flash_text_engine_ElementFormat_textRotation_get = 38;
const uint32_t flash_text_engine_ElementFormat_kerning_get = 39;
const uint32_t flash_text_engine_ElementFormat_alignmentBaseline_set = 40;
const uint32_t flash_text_engine_ElementFormat_trackingRight_set = 41;
const uint32_t flash_text_engine_ElementFormat_breakOpportunity_get = 42;
const uint32_t flash_text_engine_ElementFormat_textRotation_set = 43;
const uint32_t flash_text_engine_ElementFormat_kerning_set = 44;
const uint32_t flash_text_engine_ElementFormat_digitWidth_get = 45;
const uint32_t flash_text_engine_ElementFormat_fontDescription_set = 46;
const uint32_t flash_text_engine_ElementFormat_locked_set = 47;
const uint32_t flash_text_engine_ElementFormat_alpha_get = 49;
const uint32_t flash_text_engine_ElementFormat_ligatureLevel_set = 50;
const uint32_t flash_text_engine_ElementFormat_fontSize_set = 51;
const uint32_t flash_text_engine_ElementFormat_locale_get = 52;
const uint32_t flash_text_engine_ElementFormat_locked_get = 53;
const uint32_t flash_text_engine_ElementFormat_color_get = 54;
const uint32_t flash_text_engine_ElementFormat_trackingRight_get = 55;
const uint32_t flash_text_engine_ElementFormat_breakOpportunity_set = 56;
const uint32_t flash_text_engine_ElementFormat_fontDescription_get = 57;
const uint32_t flash_text_engine_ElementFormat_typographicCase_set = 58;
const uint32_t flash_text_engine_ElementFormat_fontSize_get = 59;
const uint32_t flash_text_engine_ElementFormat_digitWidth_set = 60;
const uint32_t flash_text_engine_ElementFormat_locale_set = 61;
const uint32_t flash_text_engine_ElementFormat_trackingLeft_get = 62;
const uint32_t flash_text_engine_ElementFormat_ligatureLevel_get = 63;
const uint32_t flash_text_engine_ElementFormat_digitCase_set = 64;
const uint32_t flash_text_engine_ElementFormat_typographicCase_get = 65;
const uint32_t flash_text_engine_ElementFormat_alpha_set = 66;
const uint32_t flash_text_engine_ElementFormat_digitCase_get = 67;
const uint32_t flash_text_engine_ElementFormat_getFontMetrics = 68;
const uint32_t flash_text_engine_FontDescription_isFontCompatible = 70;
const uint32_t flash_text_engine_FontDescription_fontLookup_set = 72;
const uint32_t flash_text_engine_FontDescription_fontWeight_get = 73;
const uint32_t flash_text_engine_FontDescription_fontLookup_get = 74;
const uint32_t flash_text_engine_FontDescription_locked_get = 75;
const uint32_t flash_text_engine_FontDescription_fontWeight_set = 76;
const uint32_t flash_text_engine_FontDescription_renderingMode_get = 77;
const uint32_t flash_text_engine_FontDescription_cffHinting_set = 78;
const uint32_t flash_text_engine_FontDescription_fontPosture_set = 79;
const uint32_t flash_text_engine_FontDescription_fontName_set = 80;
const uint32_t flash_text_engine_FontDescription_cffHinting_get = 81;
const uint32_t flash_text_engine_FontDescription_fontPosture_get = 82;
const uint32_t flash_text_engine_FontDescription_fontName_get = 83;
const uint32_t flash_text_engine_FontDescription_locked_set = 84;
const uint32_t flash_text_engine_FontDescription_renderingMode_set = 86;
const uint32_t flash_text_engine_TabStop_position_set = 109;
const uint32_t flash_text_engine_TabStop_alignment_get = 110;
const uint32_t flash_text_engine_TabStop_alignment_set = 111;
const uint32_t flash_text_engine_TabStop_decimalAlignmentToken_get = 112;
const uint32_t flash_text_engine_TabStop_position_get = 113;
const uint32_t flash_text_engine_TabStop_decimalAlignmentToken_set = 114;
const uint32_t flash_text_engine_TextBlock_getTextLineAtCharIndex = 120;
const uint32_t flash_text_engine_TextBlock_firstLine_get = 121;
const uint32_t flash_text_engine_TextBlock_content_get = 123;
const uint32_t flash_text_engine_TextBlock_private_getTextJustifier = 124;
const uint32_t flash_text_engine_TextBlock_findPreviousAtomBoundary = 125;
const uint32_t flash_text_engine_TextBlock_baselineZero_get = 126;
const uint32_t flash_text_engine_TextBlock_findNextAtomBoundary = 127;
const uint32_t flash_text_engine_TextBlock_findNextWordBoundary = 128;
const uint32_t flash_text_engine_TextBlock_baselineFontDescription_set = 129;
const uint32_t flash_text_engine_TextBlock_lineRotation_get = 130;
const uint32_t flash_text_engine_TextBlock_findPreviousWordBoundary = 131;
const uint32_t flash_text_engine_TextBlock_applyNonLinearFontScaling_get = 132;
const uint32_t flash_text_engine_TextBlock_bidiLevel_get = 133;
const uint32_t flash_text_engine_TextBlock_private_getTabStops = 134;
const uint32_t flash_text_engine_TextBlock_baselineZero_set = 135;
const uint32_t flash_text_engine_TextBlock_baselineFontSize_get = 136;
const uint32_t flash_text_engine_TextBlock_private_setTabStops = 138;
const uint32_t flash_text_engine_TextBlock_lineRotation_set = 140;
const uint32_t flash_text_engine_TextBlock_applyNonLinearFontScaling_set = 141;
const uint32_t flash_text_engine_TextBlock_lastLine_get = 142;
const uint32_t flash_text_engine_TextBlock_baselineFontDescription_get = 143;
const uint32_t flash_text_engine_TextBlock_bidiLevel_set = 144;
const uint32_t flash_text_engine_TextBlock_baselineFontSize_set = 145;
const uint32_t flash_text_engine_TextBlock_content_set = 146;
const uint32_t flash_text_engine_TextBlock_dump = 147;
const uint32_t flash_text_engine_TextBlock_private_DoCreateTextLine = 148;
const uint32_t flash_text_engine_TextBlock_firstInvalidLine_get = 150;
const uint32_t flash_text_engine_TextBlock_textLineCreationResult_get = 151;
const uint32_t flash_text_engine_TextBlock_private_setTextJustifier = 152;
const uint32_t flash_text_engine_TextBlock_releaseLines = 153;
const uint32_t flash_text_engine_TextLine_mirrorRegions_get = 156;
const uint32_t flash_text_engine_TextLine_descent_get = 157;
const uint32_t flash_text_engine_TextLine_getAtomGraphic = 158;
const uint32_t flash_text_engine_TextLine_getBaselinePosition = 159;
const uint32_t flash_text_engine_TextLine_nextLine_get = 160;
const uint32_t flash_text_engine_TextLine_previousLine_get = 162;
const uint32_t flash_text_engine_TextLine_dump = 163;
const uint32_t flash_text_engine_TextLine_private_doGetAtomIndexAtPoint = 164;
const uint32_t flash_text_engine_TextLine_getAtomBidiLevel = 165;
const uint32_t flash_text_engine_TextLine_unjustifiedTextWidth_get = 167;
const uint32_t flash_text_engine_TextLine_textWidth_get = 169;
const uint32_t flash_text_engine_TextLine_ascent_get = 170;
const uint32_t flash_text_engine_TextLine_textBlock_get = 173;
const uint32_t flash_text_engine_TextLine_getAtomWordBoundaryOnLeft = 174;
const uint32_t flash_text_engine_TextLine_getAtomTextBlockBeginIndex = 175;
const uint32_t flash_text_engine_TextLine_getAtomBounds = 176;
const uint32_t flash_text_engine_TextLine_validity_set = 177;
const uint32_t flash_text_engine_TextLine_textBlockBeginIndex_get = 179;
const uint32_t flash_text_engine_TextLine_hasGraphicElement_get = 180;
const uint32_t flash_text_engine_TextLine_getAtomTextBlockEndIndex = 181;
const uint32_t flash_text_engine_TextLine_validity_get = 182;
const uint32_t flash_text_engine_TextLine_textHeight_get = 183;
const uint32_t flash_text_engine_TextLine_specifiedWidth_get = 184;
const uint32_t flash_text_engine_TextLine_getAtomTextRotation = 186;
const uint32_t flash_text_engine_TextLine_rawTextLength_get = 188;
const uint32_t flash_text_engine_TextLine_getAtomCenter = 189;
const uint32_t flash_text_engine_TextLine_atomCount_get = 190;
const uint32_t flash_text_engine_TextLine_flushAtomData = 191;
const uint32_t flash_text_engine_TextLineMirrorRegion_textLine_get = 196;
const uint32_t flash_text_engine_TextLineMirrorRegion_bounds_get = 197;
const uint32_t flash_text_engine_TextLineMirrorRegion_nextRegion_get = 198;
const uint32_t flash_text_engine_TextLineMirrorRegion_previousRegion_get = 199;
const uint32_t flash_text_engine_TextLineMirrorRegion_element_get = 200;
const uint32_t flash_text_engine_TextLineMirrorRegion_mirror_get = 201;
const uint32_t flash_text_Font_enumerateFonts = 213;
const uint32_t flash_text_Font_registerFont = 214;
const uint32_t flash_text_Font_fontType_get = 216;
const uint32_t flash_text_Font_fontStyle_get = 217;
const uint32_t flash_text_Font_fontName_get = 218;
const uint32_t flash_text_Font_hasGlyphs = 219;
const uint32_t flash_text_StaticText_text_get = 228;
const uint32_t flash_text_StyleSheet_private__update = 231;
const uint32_t flash_text_StyleSheet_private__styles_get = 232;
const uint32_t flash_text_StyleSheet_private__styles_set = 233;
const uint32_t flash_text_StyleSheet_private__parseCSSFontFamily = 234;
const uint32_t flash_text_StyleSheet_private__parseCSSInternal = 237;
const uint32_t flash_text_StyleSheet_private__parseColor = 241;
const uint32_t flash_text_TextField_isFontCompatible = 252;
const uint32_t flash_text_TextField_alwaysShowSelection_set = 254;
const uint32_t flash_text_TextField_replaceText = 255;
const uint32_t flash_text_TextField_sharpness_set = 256;
const uint32_t flash_text_TextField_wordWrap_get = 257;
const uint32_t flash_text_TextField_setTextFormat = 258;
const uint32_t flash_text_TextField_getLineLength = 259;
const uint32_t flash_text_TextField_gridFitType_set = 261;
const uint32_t flash_text_TextField_getTextRuns = 262;
const uint32_t flash_text_TextField_caretIndex_get = 263;
const uint32_t flash_text_TextField_wordWrap_set = 264;
const uint32_t flash_text_TextField_borderColor_get = 265;
const uint32_t flash_text_TextField_condenseWhite_set = 266;
const uint32_t flash_text_TextField_numLines_get = 267;
const uint32_t flash_text_TextField_scrollH_get = 268;
const uint32_t flash_text_TextField_getLineOffset = 269;
const uint32_t flash_text_TextField_maxScrollH_get = 270;
const uint32_t flash_text_TextField_autoSize_set = 271;
const uint32_t flash_text_TextField_defaultTextFormat_get = 272;
const uint32_t flash_text_TextField_getImageReference = 273;
const uint32_t flash_text_TextField_textWidth_get = 274;
const uint32_t flash_text_TextField_scrollV_get = 275;
const uint32_t flash_text_TextField_backgroundColor_set = 276;
const uint32_t flash_text_TextField_embedFonts_get = 277;
const uint32_t flash_text_TextField_border_get = 278;
const uint32_t flash_text_TextField_multiline_get = 279;
const uint32_t flash_text_TextField_background_get = 280;
const uint32_t flash_text_TextField_maxChars_set = 281;
const uint32_t flash_text_TextField_selectable_set = 282;
const uint32_t flash_text_TextField_maxScrollV_get = 283;
const uint32_t flash_text_TextField_borderColor_set = 284;
const uint32_t flash_text_TextField_displayAsPassword_set = 285;
const uint32_t flash_text_TextField_getLineText = 286;
const uint32_t flash_text_TextField_getFirstCharInParagraph = 287;
const uint32_t flash_text_TextField_mouseWheelEnabled_get = 288;
const uint32_t flash_text_TextField_textHeight_get = 289;
const uint32_t flash_text_TextField_restrict_get = 290;
const uint32_t flash_text_TextField_scrollH_set = 291;
const uint32_t flash_text_TextField_getRawText = 293;
const uint32_t flash_text_TextField_alwaysShowSelection_get = 294;
const uint32_t flash_text_TextField_sharpness_get = 295;
const uint32_t flash_text_TextField_getCharBoundaries = 296;
const uint32_t flash_text_TextField_gridFitType_get = 297;
const uint32_t flash_text_TextField_styleSheet_get = 298;
const uint32_t flash_text_TextField_useRichTextClipboard_get = 299;
const uint32_t flash_text_TextField_type_get = 300;
const uint32_t flash_text_TextField_defaultTextFormat_set = 301;
const uint32_t flash_text_TextField_replaceSelectedText = 302;
const uint32_t flash_text_TextField_condenseWhite_get = 303;
const uint32_t flash_text_TextField_getParagraphLength = 304;
const uint32_t flash_text_TextField_textColor_get = 305;
const uint32_t flash_text_TextField_displayAsPassword_get = 306;
const uint32_t flash_text_TextField_autoSize_get = 307;
const uint32_t flash_text_TextField_setSelection = 308;
const uint32_t flash_text_TextField_scrollV_set = 309;
const uint32_t flash_text_TextField_useRichTextClipboard_set = 310;
const uint32_t flash_text_TextField_backgroundColor_get = 311;
const uint32_t flash_text_TextField_selectable_get = 312;
const uint32_t flash_text_TextField_antiAliasType_set = 313;
const uint32_t flash_text_TextField_border_set = 314;
const uint32_t flash_text_TextField_maxChars_get = 315;
const uint32_t flash_text_TextField_multiline_set = 316;
const uint32_t flash_text_TextField_background_set = 318;
const uint32_t flash_text_TextField_embedFonts_set = 319;
const uint32_t flash_text_TextField_getCharIndexAtPoint = 320;
const uint32_t flash_text_TextField_text_set = 321;
const uint32_t flash_text_TextField_selectionEndIndex_get = 322;
const uint32_t flash_text_TextField_selectionBeginIndex_get = 323;
const uint32_t flash_text_TextField_mouseWheelEnabled_set = 324;
const uint32_t flash_text_TextField_length_get = 325;
const uint32_t flash_text_TextField_antiAliasType_get = 327;
const uint32_t flash_text_TextField_styleSheet_set = 328;
const uint32_t flash_text_TextField_textColor_set = 329;
const uint32_t flash_text_TextField_htmlText_set = 331;
const uint32_t flash_text_TextField_text_get = 333;
const uint32_t flash_text_TextField_thickness_get = 334;
const uint32_t flash_text_TextField_getLineIndexAtPoint = 335;
const uint32_t flash_text_TextField_thickness_set = 336;
const uint32_t flash_text_TextField_htmlText_get = 337;
const uint32_t flash_text_TextField_getLineMetrics = 338;
const uint32_t flash_text_TextField_getTextFormat = 339;
const uint32_t flash_text_TextField_type_set = 340;
const uint32_t flash_text_TextField_getLineIndexOfChar = 341;
const uint32_t flash_text_TextField_bottomScrollV_get = 342;
const uint32_t flash_text_TextField_restrict_set = 343;
const uint32_t flash_text_TextField_userInput_set = 344;
const uint32_t flash_text_TextField_userInput_get = 345;
const uint32_t flash_text_TextFormat_size_get = 352;
const uint32_t flash_text_TextFormat_bullet_get = 353;
const uint32_t flash_text_TextFormat_bullet_set = 354;
const uint32_t flash_text_TextFormat_align_get = 355;
const uint32_t flash_text_TextFormat_color_set = 356;
const uint32_t flash_text_TextFormat_display_get = 357;
const uint32_t flash_text_TextFormat_bold_set = 358;
const uint32_t flash_text_TextFormat_display_set = 359;
const uint32_t flash_text_TextFormat_bold_get = 360;
const uint32_t flash_text_TextFormat_leading_get = 361;
const uint32_t flash_text_TextFormat_font_get = 362;
const uint32_t flash_text_TextFormat_align_set = 363;
const uint32_t flash_text_TextFormat_leading_set = 364;
const uint32_t flash_text_TextFormat_rightMargin_set = 365;
const uint32_t flash_text_TextFormat_leftMargin_get = 366;
const uint32_t flash_text_TextFormat_indent_set = 367;
const uint32_t flash_text_TextFormat_blockIndent_get = 368;
const uint32_t flash_text_TextFormat_size_set = 369;
const uint32_t flash_text_TextFormat_kerning_get = 370;
const uint32_t flash_text_TextFormat_tabStops_get = 371;
const uint32_t flash_text_TextFormat_font_set = 372;
const uint32_t flash_text_TextFormat_kerning_set = 373;
const uint32_t flash_text_TextFormat_italic_set = 374;
const uint32_t flash_text_TextFormat_target_set = 375;
const uint32_t flash_text_TextFormat_color_get = 376;
const uint32_t flash_text_TextFormat_underline_get = 377;
const uint32_t flash_text_TextFormat_url_set = 378;
const uint32_t flash_text_TextFormat_underline_set = 379;
const uint32_t flash_text_TextFormat_target_get = 380;
const uint32_t flash_text_TextFormat_leftMargin_set = 381;
const uint32_t flash_text_TextFormat_indent_get = 382;
const uint32_t flash_text_TextFormat_url_get = 383;
const uint32_t flash_text_TextFormat_italic_get = 384;
const uint32_t flash_text_TextFormat_rightMargin_get = 385;
const uint32_t flash_text_TextFormat_blockIndent_set = 386;
const uint32_t flash_text_TextFormat_tabStops_set = 387;
const uint32_t flash_text_TextFormat_letterSpacing_set = 388;
const uint32_t flash_text_TextFormat_letterSpacing_get = 389;
const uint32_t flash_text_TextRenderer_maxLevel_set = 397;
const uint32_t flash_text_TextRenderer_displayMode_get = 398;
const uint32_t flash_text_TextRenderer_setAdvancedAntiAliasingTable = 399;
const uint32_t flash_text_TextRenderer_maxLevel_get = 400;
const uint32_t flash_text_TextRenderer_antiAliasType_get = 401;
const uint32_t flash_text_TextRenderer_displayMode_set = 402;
const uint32_t flash_text_TextRenderer_antiAliasType_set = 403;
const uint32_t flash_text_TextSnapshot_getSelected = 409;
const uint32_t flash_text_TextSnapshot_getText = 410;
const uint32_t flash_text_TextSnapshot_setSelected = 411;
const uint32_t flash_text_TextSnapshot_setSelectColor = 412;
const uint32_t flash_text_TextSnapshot_findText = 413;
const uint32_t flash_text_TextSnapshot_charCount_get = 414;
const uint32_t flash_text_TextSnapshot_hitTestTextNearPos = 415;
const uint32_t flash_text_TextSnapshot_getTextRunInfo = 416;
const uint32_t flash_text_TextSnapshot_getSelectedText = 417;
const uint32_t flash_text_engine_EastAsianJustifier_justificationStyle_set = 421;
const uint32_t flash_text_engine_EastAsianJustifier_justificationStyle_get = 422;
const uint32_t flash_text_engine_SpaceJustifier_letterSpacing_set = 425;
const uint32_t flash_text_engine_SpaceJustifier_letterSpacing_get = 427;
const uint32_t flash_text_engine_GraphicElement_graphic_set = 430;
const uint32_t flash_text_engine_GraphicElement_elementHeight_get = 431;
const uint32_t flash_text_engine_GraphicElement_elementWidth_set = 432;
const uint32_t flash_text_engine_GraphicElement_elementHeight_set = 433;
const uint32_t flash_text_engine_GraphicElement_graphic_get = 434;
const uint32_t flash_text_engine_GraphicElement_elementWidth_get = 435;
const uint32_t flash_text_engine_GroupElement_getElementAt = 438;
const uint32_t flash_text_engine_GroupElement_getElementAtCharIndex = 439;
const uint32_t flash_text_engine_GroupElement_elementCount_get = 440;
const uint32_t flash_text_engine_GroupElement_splitTextElement = 442;
const uint32_t flash_text_engine_GroupElement_groupElements = 443;
const uint32_t flash_text_engine_GroupElement_setElements = 444;
const uint32_t flash_text_engine_GroupElement_replaceElements = 445;
const uint32_t flash_text_engine_GroupElement_mergeTextElements = 446;
const uint32_t flash_text_engine_GroupElement_ungroupElements = 447;
const uint32_t flash_text_engine_TextElement_replaceText = 450;
const uint32_t flash_text_engine_TextElement_text_set = 451;

extern AvmBox text_s2a_ob_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextSnapshot_getSelectedText_thunk  text_s2a_ob_optbfalse_thunk

extern AvmBox text_i2a_oisb_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextSnapshot_findText_thunk  text_i2a_oisb_thunk

extern AvmBox text_a2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_StyleSheet_private__parseCSSInternal_thunk  text_a2a_os_thunk
#define flash_text_TextField_getImageReference_thunk  text_a2a_os_thunk

extern AvmBox text_b2a_oii_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextSnapshot_getSelected_thunk  text_b2a_oii_thunk

extern AvmBox text_u2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_StyleSheet_private__parseColor_thunk  text_u2a_os_thunk

extern AvmBox text_u2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_backgroundColor_get_thunk  text_u2a_o_thunk
#define flash_text_TextField_borderColor_get_thunk  text_u2a_o_thunk
#define flash_text_TextField_textColor_get_thunk  text_u2a_o_thunk
#define flash_text_engine_ElementFormat_color_get_thunk  text_u2a_o_thunk

extern AvmBox text_a2a_oii_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_GroupElement_mergeTextElements_thunk  text_a2a_oii_thunk
#define flash_text_engine_GroupElement_groupElements_thunk  text_a2a_oii_thunk
#define flash_text_TextSnapshot_getTextRunInfo_thunk  text_a2a_oii_thunk
#define flash_text_engine_GroupElement_splitTextElement_thunk  text_a2a_oii_thunk

extern AvmBox text_i2a_odd_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_TextLine_private_doGetAtomIndexAtPoint_thunk  text_i2a_odd_thunk
#define flash_text_TextField_getCharIndexAtPoint_thunk  text_i2a_odd_thunk
#define flash_text_TextField_getLineIndexAtPoint_thunk  text_i2a_odd_thunk

extern AvmBox text_v2a_oi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_scrollV_set_thunk  text_v2a_oi_thunk
#define flash_text_engine_GroupElement_ungroupElements_thunk  text_v2a_oi_thunk
#define flash_text_TextRenderer_maxLevel_set_thunk  text_v2a_oi_thunk
#define flash_text_engine_TextBlock_bidiLevel_set_thunk  text_v2a_oi_thunk
#define flash_text_TextField_maxChars_set_thunk  text_v2a_oi_thunk
#define flash_text_TextField_scrollH_set_thunk  text_v2a_oi_thunk

extern AvmBox text_s2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_ElementFormat_textRotation_get_thunk  text_s2a_o_thunk
#define flash_text_engine_FontDescription_renderingMode_get_thunk  text_s2a_o_thunk
#define flash_text_engine_TabStop_decimalAlignmentToken_get_thunk  text_s2a_o_thunk
#define flash_text_TextFormat_font_get_thunk  text_s2a_o_thunk
#define flash_text_engine_TextJustifier_locale_get_thunk  text_s2a_o_thunk
#define flash_text_engine_TextBlock_baselineZero_get_thunk  text_s2a_o_thunk
#define flash_text_engine_FontDescription_fontWeight_get_thunk  text_s2a_o_thunk
#define flash_text_engine_ContentElement_text_get_thunk  text_s2a_o_thunk
#define flash_text_engine_TextBlock_lineRotation_get_thunk  text_s2a_o_thunk
#define flash_text_engine_ElementFormat_locale_get_thunk  text_s2a_o_thunk
#define flash_text_engine_ElementFormat_dominantBaseline_get_thunk  text_s2a_o_thunk
#define flash_text_Font_fontStyle_get_thunk  text_s2a_o_thunk
#define flash_text_engine_ElementFormat_digitWidth_get_thunk  text_s2a_o_thunk
#define flash_text_engine_TextLine_dump_thunk  text_s2a_o_thunk
#define flash_text_engine_FontDescription_fontLookup_get_thunk  text_s2a_o_thunk
#define flash_text_TextField_getRawText_thunk  text_s2a_o_thunk
#define flash_text_engine_ContentElement_rawText_get_thunk  text_s2a_o_thunk
#define flash_text_StaticText_text_get_thunk  text_s2a_o_thunk
#define flash_text_TextRenderer_antiAliasType_get_thunk  text_s2a_o_thunk
#define flash_text_engine_FontDescription_fontName_get_thunk  text_s2a_o_thunk
#define flash_text_TextField_text_get_thunk  text_s2a_o_thunk
#define flash_text_TextFormat_display_get_thunk  text_s2a_o_thunk
#define flash_text_engine_FontDescription_cffHinting_get_thunk  text_s2a_o_thunk
#define flash_text_engine_ElementFormat_alignmentBaseline_get_thunk  text_s2a_o_thunk
#define flash_text_TextFormat_url_get_thunk  text_s2a_o_thunk
#define flash_text_Font_fontType_get_thunk  text_s2a_o_thunk
#define flash_text_TextField_htmlText_get_thunk  text_s2a_o_thunk
#define flash_text_engine_ContentElement_textRotation_get_thunk  text_s2a_o_thunk
#define flash_text_engine_ElementFormat_breakOpportunity_get_thunk  text_s2a_o_thunk
#define flash_text_engine_TextJustifier_lineJustification_get_thunk  text_s2a_o_thunk
#define flash_text_engine_ElementFormat_typographicCase_get_thunk  text_s2a_o_thunk
#define flash_text_TextField_autoSize_get_thunk  text_s2a_o_thunk
#define flash_text_engine_ElementFormat_digitCase_get_thunk  text_s2a_o_thunk
#define flash_text_engine_TextBlock_dump_thunk  text_s2a_o_thunk
#define flash_text_engine_FontDescription_fontPosture_get_thunk  text_s2a_o_thunk
#define flash_text_TextField_type_get_thunk  text_s2a_o_thunk
#define flash_text_TextFormat_align_get_thunk  text_s2a_o_thunk
#define flash_text_engine_TextLine_validity_get_thunk  text_s2a_o_thunk
#define flash_text_TextFormat_target_get_thunk  text_s2a_o_thunk
#define flash_text_engine_TabStop_alignment_get_thunk  text_s2a_o_thunk
#define flash_text_TextField_gridFitType_get_thunk  text_s2a_o_thunk
#define flash_text_TextRenderer_displayMode_get_thunk  text_s2a_o_thunk
#define flash_text_engine_EastAsianJustifier_justificationStyle_get_thunk  text_s2a_o_thunk
#define flash_text_engine_ElementFormat_ligatureLevel_get_thunk  text_s2a_o_thunk
#define flash_text_TextField_antiAliasType_get_thunk  text_s2a_o_thunk
#define flash_text_Font_fontName_get_thunk  text_s2a_o_thunk
#define flash_text_engine_ElementFormat_kerning_get_thunk  text_s2a_o_thunk
#define flash_text_engine_TextBlock_textLineCreationResult_get_thunk  text_s2a_o_thunk
#define flash_text_TextField_restrict_get_thunk  text_s2a_o_thunk

extern AvmBox text_a2a_oii_opti0_opti2147483647_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_getTextRuns_thunk  text_a2a_oii_opti0_opti2147483647_thunk

extern AvmBox text_a2a_ob_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_Font_enumerateFonts_thunk  text_a2a_ob_optbfalse_thunk

extern AvmBox text_v2a_ooii_opti_1_opti_1_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_setTextFormat_thunk  text_v2a_ooii_opti_1_opti_1_thunk

extern double text_d2d_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_TextLine_textWidth_get_thunk  text_d2d_o_thunk
#define flash_text_engine_ElementFormat_alpha_get_thunk  text_d2d_o_thunk
#define flash_text_engine_TextLine_unjustifiedTextWidth_get_thunk  text_d2d_o_thunk
#define flash_text_engine_GraphicElement_elementHeight_get_thunk  text_d2d_o_thunk
#define flash_text_engine_TabStop_position_get_thunk  text_d2d_o_thunk
#define flash_text_engine_TextLine_descent_get_thunk  text_d2d_o_thunk
#define flash_text_engine_TextLine_ascent_get_thunk  text_d2d_o_thunk
#define flash_text_TextField_textWidth_get_thunk  text_d2d_o_thunk
#define flash_text_engine_ElementFormat_trackingRight_get_thunk  text_d2d_o_thunk
#define flash_text_engine_TextLine_specifiedWidth_get_thunk  text_d2d_o_thunk
#define flash_text_TextField_sharpness_get_thunk  text_d2d_o_thunk
#define flash_text_engine_GraphicElement_elementWidth_get_thunk  text_d2d_o_thunk
#define flash_text_TextField_thickness_get_thunk  text_d2d_o_thunk
#define flash_text_engine_TextBlock_baselineFontSize_get_thunk  text_d2d_o_thunk
#define flash_text_TextField_textHeight_get_thunk  text_d2d_o_thunk
#define flash_text_engine_ElementFormat_trackingLeft_get_thunk  text_d2d_o_thunk
#define flash_text_engine_ElementFormat_baselineShift_get_thunk  text_d2d_o_thunk
#define flash_text_engine_TextLine_textHeight_get_thunk  text_d2d_o_thunk
#define flash_text_engine_ElementFormat_fontSize_get_thunk  text_d2d_o_thunk

extern AvmBox text_v2a_ooo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_TextBlock_releaseLines_thunk  text_v2a_ooo_thunk

extern AvmBox text_a2a_oiio_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_GroupElement_replaceElements_thunk  text_a2a_oiio_thunk

extern AvmBox text_v2a_ossso_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextRenderer_setAdvancedAntiAliasingTable_thunk  text_v2a_ossso_thunk

extern AvmBox text_s2a_oi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_TextLine_getAtomTextRotation_thunk  text_s2a_oi_thunk
#define flash_text_TextField_getLineText_thunk  text_s2a_oi_thunk

extern AvmBox text_a2a_oii_opti_1_opti_1_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_getTextFormat_thunk  text_a2a_oii_opti_1_opti_1_thunk

extern AvmBox text_i2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_caretIndex_get_thunk  text_i2a_o_thunk
#define flash_text_TextField_maxScrollH_get_thunk  text_i2a_o_thunk
#define flash_text_TextRenderer_maxLevel_get_thunk  text_i2a_o_thunk
#define flash_text_TextField_length_get_thunk  text_i2a_o_thunk
#define flash_text_TextField_selectionBeginIndex_get_thunk  text_i2a_o_thunk
#define flash_text_TextField_bottomScrollV_get_thunk  text_i2a_o_thunk
#define flash_text_TextField_maxChars_get_thunk  text_i2a_o_thunk
#define flash_text_engine_ContentElement_textBlockBeginIndex_get_thunk  text_i2a_o_thunk
#define flash_text_engine_TextBlock_bidiLevel_get_thunk  text_i2a_o_thunk
#define flash_text_engine_TextLine_textBlockBeginIndex_get_thunk  text_i2a_o_thunk
#define flash_text_TextField_numLines_get_thunk  text_i2a_o_thunk
#define flash_text_TextSnapshot_charCount_get_thunk  text_i2a_o_thunk
#define flash_text_engine_TextLine_rawTextLength_get_thunk  text_i2a_o_thunk
#define flash_text_engine_GroupElement_elementCount_get_thunk  text_i2a_o_thunk
#define flash_text_TextField_maxScrollV_get_thunk  text_i2a_o_thunk
#define flash_text_engine_TextLine_atomCount_get_thunk  text_i2a_o_thunk
#define flash_text_TextField_scrollH_get_thunk  text_i2a_o_thunk
#define flash_text_TextField_scrollV_get_thunk  text_i2a_o_thunk
#define flash_text_TextField_selectionEndIndex_get_thunk  text_i2a_o_thunk

extern AvmBox text_v2a_ou_opti16776960_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextSnapshot_setSelectColor_thunk  text_v2a_ou_opti16776960_thunk

extern AvmBox text_s2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_StyleSheet_private__parseCSSFontFamily_thunk  text_s2a_os_thunk

extern AvmBox text_v2a_oiis_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_TextElement_replaceText_thunk  text_v2a_oiis_thunk
#define flash_text_TextField_replaceText_thunk  text_v2a_oiis_thunk

extern AvmBox text_b2a_oi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_TextLine_getAtomWordBoundaryOnLeft_thunk  text_b2a_oi_thunk

extern double text_d2d_oddd_opti0_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextSnapshot_hitTestTextNearPos_thunk  text_d2d_oddd_opti0_thunk

extern AvmBox text_b2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_Font_hasGlyphs_thunk  text_b2a_os_thunk

extern AvmBox text_a2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_TextBlock_firstLine_get_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_leading_get_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_italic_get_thunk  text_a2a_o_thunk
#define flash_text_engine_GraphicElement_graphic_get_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_indent_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextLineMirrorRegion_bounds_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextBlock_firstInvalidLine_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextLine_nextLine_get_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_letterSpacing_get_thunk  text_a2a_o_thunk
#define flash_text_engine_ContentElement_elementFormat_get_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_leftMargin_get_thunk  text_a2a_o_thunk
#define flash_text_StyleSheet_private__styles_get_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_bold_get_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_underline_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextBlock_private_getTextJustifier_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_kerning_get_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_bullet_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextLineMirrorRegion_nextRegion_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextBlock_baselineFontDescription_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextLineMirrorRegion_mirror_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextLine_previousLine_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextLine_textBlock_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextBlock_content_get_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_size_get_thunk  text_a2a_o_thunk
#define flash_text_engine_ContentElement_groupElement_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextBlock_lastLine_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextLine_mirrorRegions_get_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_rightMargin_get_thunk  text_a2a_o_thunk
#define flash_text_engine_ContentElement_textBlock_get_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_blockIndent_get_thunk  text_a2a_o_thunk
#define flash_text_engine_ElementFormat_getFontMetrics_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_tabStops_get_thunk  text_a2a_o_thunk
#define flash_text_TextField_defaultTextFormat_get_thunk  text_a2a_o_thunk
#define flash_text_engine_ContentElement_eventMirror_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextLineMirrorRegion_element_get_thunk  text_a2a_o_thunk
#define flash_text_TextField_styleSheet_get_thunk  text_a2a_o_thunk
#define flash_text_TextFormat_color_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextLineMirrorRegion_previousRegion_get_thunk  text_a2a_o_thunk
#define flash_text_engine_ElementFormat_fontDescription_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextLineMirrorRegion_textLine_get_thunk  text_a2a_o_thunk
#define flash_text_engine_TextBlock_private_getTabStops_thunk  text_a2a_o_thunk

extern AvmBox text_v2a_oii_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_setSelection_thunk  text_v2a_oii_thunk

extern AvmBox text_s2a_oiib_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextSnapshot_getText_thunk  text_s2a_oiib_optbfalse_thunk

extern AvmBox text_v2a_oiib_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextSnapshot_setSelected_thunk  text_v2a_oiib_thunk

extern AvmBox text_a2a_ooddb_opti0_optbfalse_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_TextBlock_private_DoCreateTextLine_thunk  text_a2a_ooddb_opti0_optbfalse_thunk

extern AvmBox text_i2a_oi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_TextLine_getAtomTextBlockBeginIndex_thunk  text_i2a_oi_thunk
#define flash_text_TextField_getLineIndexOfChar_thunk  text_i2a_oi_thunk
#define flash_text_engine_TextBlock_findNextAtomBoundary_thunk  text_i2a_oi_thunk
#define flash_text_engine_TextBlock_findPreviousAtomBoundary_thunk  text_i2a_oi_thunk
#define flash_text_TextField_getLineLength_thunk  text_i2a_oi_thunk
#define flash_text_engine_TextBlock_findPreviousWordBoundary_thunk  text_i2a_oi_thunk
#define flash_text_TextField_getParagraphLength_thunk  text_i2a_oi_thunk
#define flash_text_TextField_getLineOffset_thunk  text_i2a_oi_thunk
#define flash_text_TextField_getFirstCharInParagraph_thunk  text_i2a_oi_thunk
#define flash_text_engine_TextLine_getAtomTextBlockEndIndex_thunk  text_i2a_oi_thunk
#define flash_text_engine_TextBlock_findNextWordBoundary_thunk  text_i2a_oi_thunk
#define flash_text_engine_TextLine_getAtomBidiLevel_thunk  text_i2a_oi_thunk

extern AvmBox text_v2a_od_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_GraphicElement_elementHeight_set_thunk  text_v2a_od_thunk
#define flash_text_engine_ElementFormat_alpha_set_thunk  text_v2a_od_thunk
#define flash_text_engine_ElementFormat_trackingLeft_set_thunk  text_v2a_od_thunk
#define flash_text_engine_TabStop_position_set_thunk  text_v2a_od_thunk
#define flash_text_engine_GraphicElement_elementWidth_set_thunk  text_v2a_od_thunk
#define flash_text_engine_TextBlock_baselineFontSize_set_thunk  text_v2a_od_thunk
#define flash_text_engine_ElementFormat_baselineShift_set_thunk  text_v2a_od_thunk
#define flash_text_TextField_sharpness_set_thunk  text_v2a_od_thunk
#define flash_text_engine_ElementFormat_fontSize_set_thunk  text_v2a_od_thunk
#define flash_text_TextField_thickness_set_thunk  text_v2a_od_thunk
#define flash_text_engine_ElementFormat_trackingRight_set_thunk  text_v2a_od_thunk

extern AvmBox text_v2a_ob_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_useRichTextClipboard_set_thunk  text_v2a_ob_thunk
#define flash_text_TextField_condenseWhite_set_thunk  text_v2a_ob_thunk
#define flash_text_TextField_displayAsPassword_set_thunk  text_v2a_ob_thunk
#define flash_text_engine_ElementFormat_locked_set_thunk  text_v2a_ob_thunk
#define flash_text_TextField_wordWrap_set_thunk  text_v2a_ob_thunk
#define flash_text_TextField_userInput_set_thunk  text_v2a_ob_thunk
#define flash_text_TextField_embedFonts_set_thunk  text_v2a_ob_thunk
#define flash_text_engine_FontDescription_locked_set_thunk  text_v2a_ob_thunk
#define flash_text_TextField_multiline_set_thunk  text_v2a_ob_thunk
#define flash_text_engine_TextBlock_applyNonLinearFontScaling_set_thunk  text_v2a_ob_thunk
#define flash_text_engine_SpaceJustifier_letterSpacing_set_thunk  text_v2a_ob_thunk
#define flash_text_TextField_alwaysShowSelection_set_thunk  text_v2a_ob_thunk
#define flash_text_TextField_background_set_thunk  text_v2a_ob_thunk
#define flash_text_TextField_mouseWheelEnabled_set_thunk  text_v2a_ob_thunk
#define flash_text_TextField_border_set_thunk  text_v2a_ob_thunk
#define flash_text_TextField_selectable_set_thunk  text_v2a_ob_thunk

extern AvmBox text_v2a_oa_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextFormat_bold_set_thunk  text_v2a_oa_thunk
#define flash_text_TextFormat_blockIndent_set_thunk  text_v2a_oa_thunk
#define flash_text_TextFormat_leading_set_thunk  text_v2a_oa_thunk
#define flash_text_TextFormat_leftMargin_set_thunk  text_v2a_oa_thunk
#define flash_text_TextFormat_size_set_thunk  text_v2a_oa_thunk
#define flash_text_StyleSheet_private__styles_set_thunk  text_v2a_oa_thunk
#define flash_text_TextFormat_color_set_thunk  text_v2a_oa_thunk
#define flash_text_TextFormat_italic_set_thunk  text_v2a_oa_thunk
#define flash_text_TextFormat_indent_set_thunk  text_v2a_oa_thunk
#define flash_text_TextFormat_letterSpacing_set_thunk  text_v2a_oa_thunk
#define flash_text_TextFormat_underline_set_thunk  text_v2a_oa_thunk
#define flash_text_TextFormat_kerning_set_thunk  text_v2a_oa_thunk
#define flash_text_TextFormat_bullet_set_thunk  text_v2a_oa_thunk
#define flash_text_TextFormat_rightMargin_set_thunk  text_v2a_oa_thunk

extern AvmBox text_b2a_osss_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_FontDescription_isFontCompatible_thunk  text_b2a_osss_thunk

extern AvmBox text_v2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_TextLine_flushAtomData_thunk  text_v2a_o_thunk
#define flash_text_StyleSheet_private__update_thunk  text_v2a_o_thunk

extern double text_d2d_oi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_TextLine_getAtomCenter_thunk  text_d2d_oi_thunk

extern AvmBox text_v2a_oo_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_defaultTextFormat_set_thunk  text_v2a_oo_thunk
#define flash_text_engine_GroupElement_setElements_thunk  text_v2a_oo_thunk
#define flash_text_engine_TextBlock_content_set_thunk  text_v2a_oo_thunk
#define flash_text_engine_ContentElement_eventMirror_set_thunk  text_v2a_oo_thunk
#define flash_text_TextFormat_tabStops_set_thunk  text_v2a_oo_thunk
#define flash_text_engine_TextBlock_private_setTabStops_thunk  text_v2a_oo_thunk
#define flash_text_engine_GraphicElement_graphic_set_thunk  text_v2a_oo_thunk
#define flash_text_engine_TextBlock_baselineFontDescription_set_thunk  text_v2a_oo_thunk
#define flash_text_engine_ElementFormat_fontDescription_set_thunk  text_v2a_oo_thunk
#define flash_text_TextField_styleSheet_set_thunk  text_v2a_oo_thunk
#define flash_text_engine_ContentElement_elementFormat_set_thunk  text_v2a_oo_thunk
#define flash_text_Font_registerFont_thunk  text_v2a_oo_thunk
#define flash_text_engine_TextBlock_private_setTextJustifier_thunk  text_v2a_oo_thunk

extern AvmBox text_b2a_o_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_displayAsPassword_get_thunk  text_b2a_o_thunk
#define flash_text_TextField_wordWrap_get_thunk  text_b2a_o_thunk
#define flash_text_TextField_multiline_get_thunk  text_b2a_o_thunk
#define flash_text_TextField_useRichTextClipboard_get_thunk  text_b2a_o_thunk
#define flash_text_TextField_userInput_get_thunk  text_b2a_o_thunk
#define flash_text_TextField_embedFonts_get_thunk  text_b2a_o_thunk
#define flash_text_TextField_mouseWheelEnabled_get_thunk  text_b2a_o_thunk
#define flash_text_engine_ElementFormat_locked_get_thunk  text_b2a_o_thunk
#define flash_text_TextField_alwaysShowSelection_get_thunk  text_b2a_o_thunk
#define flash_text_engine_FontDescription_locked_get_thunk  text_b2a_o_thunk
#define flash_text_TextField_background_get_thunk  text_b2a_o_thunk
#define flash_text_TextField_condenseWhite_get_thunk  text_b2a_o_thunk
#define flash_text_engine_TextBlock_applyNonLinearFontScaling_get_thunk  text_b2a_o_thunk
#define flash_text_engine_SpaceJustifier_letterSpacing_get_thunk  text_b2a_o_thunk
#define flash_text_engine_TextLine_hasGraphicElement_get_thunk  text_b2a_o_thunk
#define flash_text_TextField_selectable_get_thunk  text_b2a_o_thunk
#define flash_text_TextField_border_get_thunk  text_b2a_o_thunk

extern AvmBox text_a2a_oi_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_GroupElement_getElementAt_thunk  text_a2a_oi_thunk
#define flash_text_TextField_getCharBoundaries_thunk  text_a2a_oi_thunk
#define flash_text_engine_TextBlock_getTextLineAtCharIndex_thunk  text_a2a_oi_thunk
#define flash_text_TextField_getLineMetrics_thunk  text_a2a_oi_thunk
#define flash_text_engine_GroupElement_getElementAtCharIndex_thunk  text_a2a_oi_thunk
#define flash_text_engine_TextLine_getAtomGraphic_thunk  text_a2a_oi_thunk
#define flash_text_engine_TextLine_getAtomBounds_thunk  text_a2a_oi_thunk

extern AvmBox text_v2a_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_ElementFormat_dominantBaseline_set_thunk  text_v2a_os_thunk
#define flash_text_engine_ContentElement_textRotation_set_thunk  text_v2a_os_thunk
#define flash_text_TextFormat_url_set_thunk  text_v2a_os_thunk
#define flash_text_engine_FontDescription_cffHinting_set_thunk  text_v2a_os_thunk
#define flash_text_engine_ElementFormat_digitWidth_set_thunk  text_v2a_os_thunk
#define flash_text_engine_ElementFormat_alignmentBaseline_set_thunk  text_v2a_os_thunk
#define flash_text_TextField_restrict_set_thunk  text_v2a_os_thunk
#define flash_text_engine_TextElement_text_set_thunk  text_v2a_os_thunk
#define flash_text_TextField_text_set_thunk  text_v2a_os_thunk
#define flash_text_engine_ElementFormat_breakOpportunity_set_thunk  text_v2a_os_thunk
#define flash_text_engine_FontDescription_fontLookup_set_thunk  text_v2a_os_thunk
#define flash_text_engine_FontDescription_fontName_set_thunk  text_v2a_os_thunk
#define flash_text_engine_ElementFormat_locale_set_thunk  text_v2a_os_thunk
#define flash_text_TextFormat_target_set_thunk  text_v2a_os_thunk
#define flash_text_TextField_gridFitType_set_thunk  text_v2a_os_thunk
#define flash_text_TextField_replaceSelectedText_thunk  text_v2a_os_thunk
#define flash_text_engine_TextJustifier_lineJustification_set_thunk  text_v2a_os_thunk
#define flash_text_engine_ElementFormat_typographicCase_set_thunk  text_v2a_os_thunk
#define flash_text_TextField_autoSize_set_thunk  text_v2a_os_thunk
#define flash_text_TextField_antiAliasType_set_thunk  text_v2a_os_thunk
#define flash_text_engine_TabStop_decimalAlignmentToken_set_thunk  text_v2a_os_thunk
#define flash_text_TextRenderer_displayMode_set_thunk  text_v2a_os_thunk
#define flash_text_engine_FontDescription_renderingMode_set_thunk  text_v2a_os_thunk
#define flash_text_engine_TextJustifier_private_setLocale_thunk  text_v2a_os_thunk
#define flash_text_engine_FontDescription_fontWeight_set_thunk  text_v2a_os_thunk
#define flash_text_TextField_type_set_thunk  text_v2a_os_thunk
#define flash_text_TextFormat_align_set_thunk  text_v2a_os_thunk
#define flash_text_engine_TextBlock_baselineZero_set_thunk  text_v2a_os_thunk
#define flash_text_TextField_htmlText_set_thunk  text_v2a_os_thunk
#define flash_text_engine_TextBlock_lineRotation_set_thunk  text_v2a_os_thunk
#define flash_text_engine_TabStop_alignment_set_thunk  text_v2a_os_thunk
#define flash_text_engine_ElementFormat_textRotation_set_thunk  text_v2a_os_thunk
#define flash_text_TextFormat_font_set_thunk  text_v2a_os_thunk
#define flash_text_engine_ElementFormat_kerning_set_thunk  text_v2a_os_thunk
#define flash_text_engine_EastAsianJustifier_justificationStyle_set_thunk  text_v2a_os_thunk
#define flash_text_engine_ElementFormat_digitCase_set_thunk  text_v2a_os_thunk
#define flash_text_engine_FontDescription_fontPosture_set_thunk  text_v2a_os_thunk
#define flash_text_engine_TextLine_validity_set_thunk  text_v2a_os_thunk
#define flash_text_TextRenderer_antiAliasType_set_thunk  text_v2a_os_thunk
#define flash_text_TextFormat_display_set_thunk  text_v2a_os_thunk
#define flash_text_engine_ElementFormat_ligatureLevel_set_thunk  text_v2a_os_thunk

extern double text_d2d_os_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_engine_TextLine_getBaselinePosition_thunk  text_d2d_os_thunk

extern AvmBox text_b2a_oss_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_isFontCompatible_thunk  text_b2a_oss_thunk

extern AvmBox text_v2a_ou_thunk(AvmMethodEnv env, uint32_t argc, AvmBox* argv);
#define flash_text_TextField_borderColor_set_thunk  text_v2a_ou_thunk
#define flash_text_TextField_textColor_set_thunk  text_v2a_ou_thunk
#define flash_text_engine_ElementFormat_color_set_thunk  text_v2a_ou_thunk
#define flash_text_TextField_backgroundColor_set_thunk  text_v2a_ou_thunk

class SlotOffsetsAndAsserts;
// flash.text.engine::TextJustifier$
//-----------------------------------------------------------
class TextJustifierClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextJustifierClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextJustifierClassSlots EmptySlotsStruct_TextJustifierClass
//-----------------------------------------------------------

// flash.text.engine::TextJustifier
//-----------------------------------------------------------
class TextJustifierObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextJustifierObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextJustifierObjectSlots EmptySlotsStruct_TextJustifierObject
//-----------------------------------------------------------

// flash.text.engine::ContentElement$
//-----------------------------------------------------------
class ContentElementClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE uint32_t get_GRAPHIC_ELEMENT() const { return m_GRAPHIC_ELEMENT; }
private:
    uint32_t m_GRAPHIC_ELEMENT;
};
#define DECLARE_SLOTS_ContentElementClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE uint32_t get_GRAPHIC_ELEMENT() const { return m_slots_ContentElementClass.get_GRAPHIC_ELEMENT(); } \
    private: \
        avmplus::NativeID::ContentElementClassSlots m_slots_ContentElementClass
//-----------------------------------------------------------

// flash.text.engine::ContentElement
//-----------------------------------------------------------
class ContentElementObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmBox get_userData() const { return m_userData; }
    void set_userData(ContentElementObject* obj, AvmBox newVal);
private:
    ATOM_WB m_userData;
};
REALLY_INLINE void ContentElementObjectSlots::set_userData(ContentElementObject* obj, AvmBox newVal)
{
    m_userData.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_ContentElementObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmBox get_userData() const { return m_slots_ContentElementObject.get_userData(); } \
        REALLY_INLINE void set_userData(AvmBox newVal) { m_slots_ContentElementObject.set_userData(this, newVal); } \
    private: \
        avmplus::NativeID::ContentElementObjectSlots m_slots_ContentElementObject
//-----------------------------------------------------------

// flash.text.engine::ElementFormat$
//-----------------------------------------------------------
class ElementFormatClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ElementFormatClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ElementFormatClassSlots EmptySlotsStruct_ElementFormatClass
//-----------------------------------------------------------

// flash.text.engine::ElementFormat
//-----------------------------------------------------------
class ElementFormatObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_ElementFormatObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::ElementFormatObjectSlots EmptySlotsStruct_ElementFormatObject
//-----------------------------------------------------------

// flash.text.engine::FontDescription$
//-----------------------------------------------------------
class FontDescriptionClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_FontDescriptionClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::FontDescriptionClassSlots EmptySlotsStruct_FontDescriptionClass
//-----------------------------------------------------------

// flash.text.engine::FontDescription
//-----------------------------------------------------------
class FontDescriptionObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_FontDescriptionObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::FontDescriptionObjectSlots EmptySlotsStruct_FontDescriptionObject
//-----------------------------------------------------------

// flash.text.engine::TabStop$
//-----------------------------------------------------------
class TabStopClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TabStopClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TabStopClassSlots EmptySlotsStruct_TabStopClass
//-----------------------------------------------------------

// flash.text.engine::TabStop
//-----------------------------------------------------------
class TabStopObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TabStopObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TabStopObjectSlots EmptySlotsStruct_TabStopObject
//-----------------------------------------------------------

// flash.text.engine::TextBlock$
//-----------------------------------------------------------
class TextBlockClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextBlockClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextBlockClassSlots EmptySlotsStruct_TextBlockClass
//-----------------------------------------------------------

// flash.text.engine::TextBlock
//-----------------------------------------------------------
class TextBlockObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmBox get_userData() const { return m_userData; }
    void set_userData(TextBlockObject* obj, AvmBox newVal);
private:
    ATOM_WB m_userData;
};
REALLY_INLINE void TextBlockObjectSlots::set_userData(TextBlockObject* obj, AvmBox newVal)
{
    m_userData.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_TextBlockObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmBox get_userData() const { return m_slots_TextBlockObject.get_userData(); } \
        REALLY_INLINE void set_userData(AvmBox newVal) { m_slots_TextBlockObject.set_userData(this, newVal); } \
    private: \
        avmplus::NativeID::TextBlockObjectSlots m_slots_TextBlockObject
//-----------------------------------------------------------

// flash.text.engine::TextLine$
//-----------------------------------------------------------
class TextLineClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE int32_t get_MAX_LINE_WIDTH() const { return m_MAX_LINE_WIDTH; }
private:
    int32_t m_MAX_LINE_WIDTH;
};
#define DECLARE_SLOTS_TextLineClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE int32_t get_MAX_LINE_WIDTH() const { return m_slots_TextLineClass.get_MAX_LINE_WIDTH(); } \
    private: \
        avmplus::NativeID::TextLineClassSlots m_slots_TextLineClass
//-----------------------------------------------------------

// flash.text.engine::TextLine
//-----------------------------------------------------------
class TextLineObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmBox get_userData() const { return m_userData; }
    void set_userData(TextLineObject* obj, AvmBox newVal);
private:
    ATOM_WB m_userData;
};
REALLY_INLINE void TextLineObjectSlots::set_userData(TextLineObject* obj, AvmBox newVal)
{
    m_userData.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_TextLineObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmBox get_userData() const { return m_slots_TextLineObject.get_userData(); } \
        REALLY_INLINE void set_userData(AvmBox newVal) { m_slots_TextLineObject.set_userData(this, newVal); } \
    private: \
        avmplus::NativeID::TextLineObjectSlots m_slots_TextLineObject
//-----------------------------------------------------------

// flash.text.engine::TextLineMirrorRegion$
//-----------------------------------------------------------
class TextLineMirrorRegionClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextLineMirrorRegionClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextLineMirrorRegionClassSlots EmptySlotsStruct_TextLineMirrorRegionClass
//-----------------------------------------------------------

// flash.text.engine::TextLineMirrorRegion
//-----------------------------------------------------------
class TextLineMirrorRegionObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextLineMirrorRegionObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextLineMirrorRegionObjectSlots EmptySlotsStruct_TextLineMirrorRegionObject
//-----------------------------------------------------------

// flash.text::Font$
//-----------------------------------------------------------
class FontClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_FontClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::FontClassSlots EmptySlotsStruct_FontClass
//-----------------------------------------------------------

// flash.text::Font
//-----------------------------------------------------------
class FontObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_FontObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::FontObjectSlots EmptySlotsStruct_FontObject
//-----------------------------------------------------------

// flash.text::StaticText$
//-----------------------------------------------------------
class StaticTextClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_StaticTextClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::StaticTextClassSlots EmptySlotsStruct_StaticTextClass
//-----------------------------------------------------------

// flash.text::StaticText
//-----------------------------------------------------------
class StaticTextObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_StaticTextObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::StaticTextObjectSlots EmptySlotsStruct_StaticTextObject
//-----------------------------------------------------------

// flash.text::StyleSheet$
//-----------------------------------------------------------
class StyleSheetClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_StyleSheetClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::StyleSheetClassSlots EmptySlotsStruct_StyleSheetClass
//-----------------------------------------------------------

// flash.text::StyleSheet
//-----------------------------------------------------------
class StyleSheetObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE AvmBox get_private__css() const { return m_private__css; }
    void set_private__css(StyleSheetObject* obj, AvmBox newVal);
private:
    ATOM_WB m_private__css;
};
REALLY_INLINE void StyleSheetObjectSlots::set_private__css(StyleSheetObject* obj, AvmBox newVal)
{
    m_private__css.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_StyleSheetObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE AvmBox get_private__css() const { return m_slots_StyleSheetObject.get_private__css(); } \
        REALLY_INLINE void set_private__css(AvmBox newVal) { m_slots_StyleSheetObject.set_private__css(this, newVal); } \
    private: \
        avmplus::NativeID::StyleSheetObjectSlots m_slots_StyleSheetObject
//-----------------------------------------------------------

// flash.text::TextField$
//-----------------------------------------------------------
class TextFieldClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
    REALLY_INLINE ArrayObject* get_private_richTextFields() const { return m_private_richTextFields; }
    void set_private_richTextFields(TextFieldClass* obj, ArrayObject* newVal);
private:
    DRCWB(ArrayObject*) m_private_richTextFields;
};
REALLY_INLINE void TextFieldClassSlots::set_private_richTextFields(TextFieldClass* obj, ArrayObject* newVal)
{
    m_private_richTextFields.set(((ScriptObject*)obj)->gc(), obj, newVal);
}
#define DECLARE_SLOTS_TextFieldClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
    protected: \
        REALLY_INLINE ArrayObject* get_private_richTextFields() const { return m_slots_TextFieldClass.get_private_richTextFields(); } \
        REALLY_INLINE void set_private_richTextFields(ArrayObject* newVal) { m_slots_TextFieldClass.set_private_richTextFields(this, newVal); } \
    private: \
        avmplus::NativeID::TextFieldClassSlots m_slots_TextFieldClass
//-----------------------------------------------------------

// flash.text::TextField
//-----------------------------------------------------------
class TextFieldObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextFieldObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextFieldObjectSlots EmptySlotsStruct_TextFieldObject
//-----------------------------------------------------------

// flash.text::TextFormat$
//-----------------------------------------------------------
class TextFormatClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextFormatClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextFormatClassSlots EmptySlotsStruct_TextFormatClass
//-----------------------------------------------------------

// flash.text::TextFormat
//-----------------------------------------------------------
class TextFormatObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextFormatObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextFormatObjectSlots EmptySlotsStruct_TextFormatObject
//-----------------------------------------------------------

// flash.text::TextRenderer$
//-----------------------------------------------------------
class TextRendererClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextRendererClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextRendererClassSlots EmptySlotsStruct_TextRendererClass
//-----------------------------------------------------------

// flash.text::TextRenderer
//-----------------------------------------------------------
class TextRendererObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextRendererObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextRendererObjectSlots EmptySlotsStruct_TextRendererObject
//-----------------------------------------------------------

// flash.text::TextSnapshot$
//-----------------------------------------------------------
class TextSnapshotClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextSnapshotClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextSnapshotClassSlots EmptySlotsStruct_TextSnapshotClass
//-----------------------------------------------------------

// flash.text::TextSnapshot
//-----------------------------------------------------------
class TextSnapshotObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextSnapshotObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextSnapshotObjectSlots EmptySlotsStruct_TextSnapshotObject
//-----------------------------------------------------------

// flash.text.engine::EastAsianJustifier$
//-----------------------------------------------------------
class EastAsianJustifierClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_EastAsianJustifierClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::EastAsianJustifierClassSlots EmptySlotsStruct_EastAsianJustifierClass
//-----------------------------------------------------------

// flash.text.engine::EastAsianJustifier
//-----------------------------------------------------------
class EastAsianJustifierObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_EastAsianJustifierObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::EastAsianJustifierObjectSlots EmptySlotsStruct_EastAsianJustifierObject
//-----------------------------------------------------------

// flash.text.engine::SpaceJustifier$
//-----------------------------------------------------------
class SpaceJustifierClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SpaceJustifierClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SpaceJustifierClassSlots EmptySlotsStruct_SpaceJustifierClass
//-----------------------------------------------------------

// flash.text.engine::SpaceJustifier
//-----------------------------------------------------------
class SpaceJustifierObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_SpaceJustifierObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::SpaceJustifierObjectSlots EmptySlotsStruct_SpaceJustifierObject
//-----------------------------------------------------------

// flash.text.engine::GraphicElement$
//-----------------------------------------------------------
class GraphicElementClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_GraphicElementClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::GraphicElementClassSlots EmptySlotsStruct_GraphicElementClass
//-----------------------------------------------------------

// flash.text.engine::GraphicElement
//-----------------------------------------------------------
class GraphicElementObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_GraphicElementObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::GraphicElementObjectSlots EmptySlotsStruct_GraphicElementObject
//-----------------------------------------------------------

// flash.text.engine::GroupElement$
//-----------------------------------------------------------
class GroupElementClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_GroupElementClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::GroupElementClassSlots EmptySlotsStruct_GroupElementClass
//-----------------------------------------------------------

// flash.text.engine::GroupElement
//-----------------------------------------------------------
class GroupElementObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_GroupElementObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::GroupElementObjectSlots EmptySlotsStruct_GroupElementObject
//-----------------------------------------------------------

// flash.text.engine::TextElement$
//-----------------------------------------------------------
class TextElementClassSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextElementClass \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextElementClassSlots EmptySlotsStruct_TextElementClass
//-----------------------------------------------------------

// flash.text.engine::TextElement
//-----------------------------------------------------------
class TextElementObjectSlots
{
    friend class SlotOffsetsAndAsserts;
public:
private:
};
#define DECLARE_SLOTS_TextElementObject \
    private: \
        friend class avmplus::NativeID::SlotOffsetsAndAsserts; \
        typedef avmplus::NativeID::TextElementObjectSlots EmptySlotsStruct_TextElementObject
//-----------------------------------------------------------

} }
