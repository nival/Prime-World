-- UICommon.lua

-- Blend animation types
--
BLEND_NONE = 0
BLEND_LINEAR = 1
BLEND_SPEEDUP = 2
BLEND_SLOWDOWN = 3
BLEND_SMOOTH = 4
BLEND_PAUSED = 5

-- Drag'n'drop
--
DRAGMODE_START = 0
DRAGMODE_DROP = 1
DRAGMODE_HSTART = 2
DRAGMODE_HEND = 3

-- Events
--
WINDOW_EVENT_ENABLE = 1
WINDOW_EVENT_SHOW = 2
WINDOW_EVENT_CONTROL = 3
WINDOW_EVENT_CURSOR_OVER = 4
WINDOW_EVENT_CURSOR_MOVE = 5
WINDOW_EVENT_ACTION_BEGIN = 6
WINDOW_EVENT_ACTION_END = 7
WINDOW_EVENT_DRAGDROP = 8
WINDOW_EVENT_TOOLTIP = 9

WINDOW_ACTION_MAIN = 0
WINDOW_ACTION_EXT = 1

-- Text aligns
--
TEXT_VALIGN_TOP = 0
TEXT_VALIGN_CENTER = 1
TEXT_VALIGN_BOTTOM = 2

TEXT_HALIGN_RIGHT = 0
TEXT_HALIGN_CENTER = 1
TEXT_HALIGN_LEFT = 2
TEXT_HALIGN_JUSTIFY = 3
TEXT_HALIGN_FULLJUSTIFY = 4

-- ImageLabel shape types
--
IMAGELABEL_SHAPE_EMPTY = 0
IMAGELABEL_SHAPE_SIMPLEBOX = 1
IMAGELABEL_SHAPE_BYTEXT = 5

-- Text clip modes
--
TEXT_CLIP_NORMAL = 0
TEXT_CLIP_ELLIPSIS = 1
TEXT_CLIP_WRAP = 2
TEXT_CLIP_FORCEWRAP = 3

-- FX Particles params
--
FX_PP_X = 0
FX_PP_Y = 1
FX_PP_W = 2
FX_PP_H = 3
FX_PP_ANGLE = 4
FX_PP_SCALE = 5
FX_PP_COEF3 = 6
FX_PP_COEF4 = 7
FX_PP_OPACITY = 8

-- Common Functions
--
function Common_Clamp( x, a, b )
	if x < a then return a end
	if x > b then return b end
	return x
end

function Common_Min( a, b )
	if a < b then return a end
	return b
end

function Common_Max( a, b )
	if a > b then return a end
	return b
end

function Common_Select1( flag1, x1, x0 )
	if flag1 then return x1 end
	return x0
end

function Common_Select2( flag1, flag2, x1, x2, x0 )
	if flag1 then return x1 end
	if flag2 then return x2 end
	return x0
end

function Common_Fits( start, step, maxCount )
	if not start or not step or not maxCount then return -1 end
	if step <= 0 then return -1 end
	if start > maxCount then return 0 end
	local count = start
	local value = start * step
	while value + step <= maxCount do
		value = value + step
		count = count + 1
	end
	return count
end

function Common_PosMin( a, b )
	if a < 0 then
		if b < 0 then return -1 end
		return b
	end
	if b < 0 then return a end
	if a < b then return a end
	return b
end
