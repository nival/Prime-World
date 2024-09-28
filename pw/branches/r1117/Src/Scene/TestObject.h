#pragma once

namespace NScene
{

class TestObject : public CObjectBase
{
	OBJECT_BASIC_METHODS( TestObject );

public:

	Placement pos;
	float opacity;
	int skin;
	bool isShow;

	void SetPlacement( const Placement& place )
	{
		pos = place;
	}

	void SetOpacity( float k )
	{
		opacity = k;
	}

	void ShowSkin( int k, bool v )
	{
		skin = k;
		isShow = v;
	}

};

}
