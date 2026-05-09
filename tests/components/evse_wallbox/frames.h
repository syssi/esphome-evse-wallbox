#pragma once
#include <cstdint>
#include <vector>

namespace esphome::evse_wallbox::testing {

// Source: esp32-example-faker.yaml — status frame (10 registers = 20 bytes)
// output_current_setting=32A  output_current=0A  vehicle_state=1 ("Ready")
// cable_limit=5A  last_command=0  firmware=18  evse_state=1 ("12V")
// error_bitmask=0  relay=false  all error bits clear
static const std::vector<uint8_t> STATUS_FRAME = {
    0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x05, 0x00, 0x00,
    0x00, 0x12, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// Source: esp32-example-rev15-faker.yaml — status frame (7 registers = 14 bytes)
// output_current_setting=3A  output_current=5A  vehicle_state=2 ("Present")
// cable_limit=32A  last_command=0  firmware=10  evse_state=3 ("Standby")
// No error registers (firmware <= 15 early return)
static const std::vector<uint8_t> STATUS_FRAME_REV15 = {
    0x00, 0x03, 0x00, 0x05, 0x00, 0x02, 0x00, 0x20, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x03,
};

// Source: esp32-example-faker.yaml — config frame (18 registers = 36 bytes)
// output_current_default=32A  min_charging_current=5A
// config_bits=0x0209 (521): current_change_by_button=true, charging_of_vehicle_status_d=true
static const std::vector<uint8_t> CONFIG_FRAME = {
    0x00, 0x20, 0x00, 0x01, 0x00, 0x05, 0x00, 0x01, 0x00, 0x00, 0x02, 0x09, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
    0x00, 0x03, 0x00, 0x06, 0x00, 0x0A, 0x00, 0x10, 0x00, 0x19, 0x00, 0x20, 0x00, 0x30, 0x00, 0x3F, 0x00, 0x50,
};

}  // namespace esphome::evse_wallbox::testing
