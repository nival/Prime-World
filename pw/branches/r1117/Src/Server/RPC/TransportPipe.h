#pragma once

#include "Interfaces.h"
#include "Packets.h"
#include <Network/Transport.h>

namespace rpc
{
rpc::IPacketPipe::PipeInfo::Status ConvertStatus(Transport::IChannel* channel);
}
