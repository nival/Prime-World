#pragma once

namespace EditorNative 
{
	public ref class PlacementConverter
	{
	public:
		void convertPlacement(DBTypes::Placement2^ from, DBTypes::Placement^ to);
		void convertPlacement(DBTypes::Placement^ from, DBTypes::Placement2^ to);
	};
}