#ifndef NET_H
#define NET_H

#include <cstdint>
#include <cstdlib>

namespace Net {
    using byte = std::int8_t;

    void init(const char *addr, int port);
    void send(byte *data, size_t length);
}

#endif