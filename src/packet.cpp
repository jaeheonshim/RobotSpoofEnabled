#include "packet.h"

#include "net.h"
#include <cstdint>

struct DSToRioUDP {
    int control;             // control mode. (Enabled/Estop/etc.)
    int request = 0x10;      // restart rio/code requests (default: DS_CONNECTED "no action")
    int allianceStation = 0;  // alliance station identifier. (default: RED_1)

    // normally, this datagram would contain time/date info, as well as joystick input.
    // these are optional though.
};

namespace Packet {
    void DSEnable(Net::byte *data) {
        static short incrementor{ 0 };
        data[0] = static_cast<Net::byte>(incrementor >> 8);
        data[1] = static_cast<Net::byte>(incrementor);
        data[2] = 0x01; // general data tag
        data[3] = 0x04; // teleop enabled
        data[4] = 0x10; // normal data request
        data[5] = 0x00; // red 1 station

        ++incrementor;
    }

    void DSDisable(Net::byte *data) {
        DSEnable(data);
        data[3] = 0x00;
    }
}