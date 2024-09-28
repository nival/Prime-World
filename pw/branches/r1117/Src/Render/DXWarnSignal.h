#pragma once
#include "..\System\SimpleSignalST.h"

struct DXWarnTag {};

typedef SimpleSignalST<int, DXWarnTag> DXWarnSignal;
