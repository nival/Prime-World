#include "stdafx.h"
#include "IDbTypesRegistrator.h"

namespace NDb
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	DbTypesRegistrator &GetDbTypesRegistrator()
	{
		static DbTypesRegistrator dbTypesRegistrator;
		return dbTypesRegistrator;
	}
}	// namespace NDb
