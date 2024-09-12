#pragma once

namespace Render
{
	/// Интерфейс запросов
	class IQuery
	{
	public:
		IQuery() {}
		virtual ~IQuery() {};
		
		virtual void Begin() = 0;
		virtual void End() = 0;
		virtual void AcquireData() = 0;
		virtual DWORD GetData() const = 0;
	};
}; // namespace Render
