#pragma once

namespace EditorNative {
namespace Manipulators {
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public ref class TransformParameters sealed
	{
	public:
		static initonly TransformParameters^ Disabled = gcnew TransformParameters();
		static initonly TransformParameters^ FullEnabled = gcnew TransformParameters( float::MinValue, float::MaxValue );

	private:
		bool isEnabled;
		float minValue;
		float maxValue;

	private:
		TransformParameters() {}

	public:
		TransformParameters( float minValue, float maxValue );

	public:
		property bool IsEnabled
		{
			bool get() { return isEnabled; }
		}

		property float MinValue
		{
			float get() { return minValue; }
		}

		property float MaxValue
		{
			float get() { return maxValue; }
		}
	};
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}	// namespace Manipulators
}	// namespace EditorNative
