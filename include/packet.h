#ifndef PACKET_H
#define PACKET_H

#include <cstdint>
#include "net.h"

namespace Packet {
    void DSEnable(Net::byte *data);
    void DSDisable(Net::byte *data);
}

#endif