#include "stdafx.h"

#include "PFApplicator.h"
#include "PFDispatch.h"
#include "PFBaseUnit.h"
#include "AdventureScreen.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Here we'll place debug commands and variables that depend on World or Adventure Screen

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LogWorldStepStatistics(const char *name, const vector<wstring> &paramsSet)
{
	using namespace NWorld;

	if (!NGameX::AdventureScreen::Instance())
		return true;

	struct StatGather
	{
		vector< pair<string, int> > statistics;

		void operator()(const PF_Core::WorldObjectBase &obj)
		{
			const char *typeName = obj.GetObjectTypeName();
			const int size = statistics.size();
			int i;
			for (i = 0; i < size; ++i)
			{
				if (statistics[i].first == typeName)
				{
					statistics[i].second++;
					break;
				}
			}

			if (i == size)
				statistics.push_back(pair<string, int>(string(typeName), 1));
		}

		void Dump()
		{
			// Output it
			const int size = statistics.size();
			DebugTrace("Objects being stepped:");
			for (int i = 0; i < size; ++i)
			{
				DebugTrace("%s %d", statistics[i].first.c_str(), statistics[i].second);
			}
		}
	} f;

	NGameX::AdventureScreen::Instance()->GetWorld()->ForAllObjectsBeingStepped(f);
	f.Dump();

	return true;
}
REGISTER_DEV_CMD(dump_world_step_stat, LogWorldStepStatistics);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LogWorldStepOrder(const char *name, const vector<wstring> &paramsSet)
{
	using namespace NWorld;

	if (!NGameX::AdventureScreen::Instance())
		return true;

	struct LogObject
	{
		void operator()(const PF_Core::WorldObjectBase &obj)
		{
			// Gather statistics
			const PFDispatch *pDisp = dynamic_cast<const PFDispatch*>(&obj);
			if (pDisp)
			{
				DebugTrace("D: %s %08X", obj.GetObjectTypeName(), (void*)pDisp->GetSender().GetPtr());
			} else
			{
				const PFBaseUnit *pUnit = dynamic_cast<const PFBaseUnit*>(&obj);
				if (pUnit)
				{
					DebugTrace("U: %s %08X", obj.GetObjectTypeName(), (void*)pUnit);
				}
			}
		}
	} f;

	DebugTrace("World step (%d) order:", NGameX::AdventureScreen::Instance()->GetWorld()->GetStepNumber());
	NGameX::AdventureScreen::Instance()->GetWorld()->ForAllObjectsBeingStepped(f);

	return true;
}
REGISTER_DEV_CMD(dump_world_step_order, LogWorldStepOrder);



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
