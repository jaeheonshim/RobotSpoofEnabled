#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>

namespace Console {
    inline void updateStatusLine(unsigned long long count) {
        std::cout << "\rSending \"enable\" packets to robot... " << count << " packets sent so far." << std::flush; 
    }
}

#endif