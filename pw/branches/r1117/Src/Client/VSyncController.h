#pragma once

namespace NMainLoop
{

namespace VSyncController
{
	void WaitBeforePresent();
	int  CalculatePresentCount();
	void MarkPresentFinished();
}


}