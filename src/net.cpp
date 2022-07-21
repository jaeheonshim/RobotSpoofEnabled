#include "net.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <cassert>
#include <cstdint>
#include <cstdlib>

namespace Net {
    static int socket{ -1 };
    static struct sockaddr_in servaddr;

    void init(const char *addr, int port) {
        assert(socket == -1 && "Socket already initialized");

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr(addr);
        servaddr.sin_port = htons(port);

        assert((socket = ::socket(AF_INET, SOCK_DGRAM, 0)) >= 0 && "Socket connection failed");
    }

    void send(byte *data, std::size_t length) {
        assert(::sendto(socket, data, length, 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) >= 0 && "Failed to send");
    }
}