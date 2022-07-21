#ifndef NET_H
#define NET_H

#include <string>
#include <cstdint>

namespace Net {
    using byte = std::int8_t;

    void init(std::string addr, int port);
    void send(byte *data, size_t length);
}

#endif