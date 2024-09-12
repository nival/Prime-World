#pragma once

#include "stdafx.h"
#pragma warning(disable: 4805)
#include <string>
#include "DBAdvMap.h"

namespace NGameX
{
    struct ReplayInfo
    {
    public:
      ReplayInfo() :
            auid(0),
            isWon(false),
            kills(0),
            assists(0),
            deaths(0)
        {
        }

        int auid;
        bool isWon;
        std::string heroId;
        NDb::EMapType mapType;
        std::string mapName;
        int kills;
        int assists;
        int deaths;
    };
}
