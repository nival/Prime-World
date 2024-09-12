#pragma once

namespace Render
{
	template<typename T>
	class DeferredKicker
	{
		typedef nstl::vector<T*> TSacrifices;
		TSacrifices sacrifices;
	public:
		DeferredKicker() 
		{ 
			sacrifices.reserve(1024); 
		}

		void AddSacrifice(T* pSacrifice)	
		{ 
			ASSERT(pSacrifice);
			//OutputDebugString(NStr::StrFmt("added %x\n", pSacrifice));
			sacrifices.push_back(pSacrifice);
		}

		void Sacrifice() 
		{
			if(sacrifices.size() == 0)
				return;
			for(TSacrifices::iterator it = sacrifices.begin(); it != sacrifices.end(); ++it )
			{
				it->Release();
				//OutputDebugString(NStr::StrFmt("deleted %x\n", *it));
			}
			sacrifices.resize(0);
		}

	};
};