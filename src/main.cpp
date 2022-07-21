#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <cstdlib>

#include "net.h"
#include "packet.h"
#include "console.h"

using byte = std::int8_t;

constexpr const char* LOCALHOST = "127.0.0.1";
constexpr int delay{ 20 }; // delay between packet send, in ms

void cleanup(int signal) {
    std::cout << "\nExit. Sending \"disable\" packet to robot...\n";
    Net::byte data[6];
    Packet::DSDisable(data);

    for(int i{ 0 }; i < 50; ++i) {
        Net::send(data, 6);
    }

    std::exit(0);
}

int main(int argc, char**argv) {
    const char *addr;

    if(argc > 1) {
        addr = argv[1];
    } else {
        addr = LOCALHOST;
    }

    std::cout << "Using address: " << addr << '\n';

    std::signal(SIGINT, cleanup);
    Net::init(addr, 1110);

    unsigned long long count{ 0 };
    Net::byte data[6];

    while(true) {
        Packet::DSEnable(data);
        Net::send(data, 6);
        count++;

        if(count % 25 == 0) {
            Console::updateStatusLine(count);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}