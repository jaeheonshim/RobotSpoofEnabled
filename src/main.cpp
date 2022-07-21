#include <iostream>
#include <chrono>
#include <thread>
#include <csignal>
#include <cstdlib>

#include "net.h"
#include "packet.h"
#include "console.h"

using byte = std::int8_t;

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

int main() {
    std::signal(SIGINT, cleanup);
    Net::init("127.0.0.1", 1110);

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