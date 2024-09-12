#pragma once


namespace Render
{
	struct Rect 
	{
		unsigned int left, top, right, bottom;
		Rect() : left(0), right(0), top(0), bottom(0) {}
		Rect( unsigned int _left, unsigned int _right, unsigned int _top, unsigned int _bottom) 
			: left(_left), right(_right), top(_top), bottom(_bottom)
		{}

    operator const RECT&() const // It is less safe to copy RECT to Rect, hence const qualifier
    {
      NI_STATIC_ASSERT( sizeof( Rect ) == sizeof( RECT ), SizeOfRect_Differ_From_SizeOfRECT );
      return reinterpret_cast<const RECT&>(*this);
    }
	};
};