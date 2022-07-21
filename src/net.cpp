#include "net.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>
#include <cassert>
#include <cstdint>

namespace Net {
    using std::string;

    static int socket{ -1 };
    static struct sockaddr_in servaddr;

    void init(string addr, int port) {
        assert(socket == -1 && "Socket already initialized");

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = htons(port);

        assert((socket = ::socket(AF_INET, SOCK_DGRAM, 0)) >= 0 && "Socket connection failed");
    }

    void send(byte *data, size_t length) {
        assert(::sendto(socket, data, length, 0, (struct sockaddr *) &servaddr, sizeof(servaddr)) >= 0 && "Failed to send");
    }
}