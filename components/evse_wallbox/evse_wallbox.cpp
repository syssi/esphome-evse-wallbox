#include "evse_wallbox.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"

namespace esphome {
namespace evse_wallbox {

static const char *const TAG = "evse_wallbox";

static const uint8_t FUNCTION_READ_REGISTERS = 0x03;
static const uint8_t FUNCTION_WRITE_SINGLE_REGISTER = 0x06;
static const uint8_t FUNCTION_WRITE_MULTIPLE_REGISTERS = 0x10;

static const uint16_t REGISTERS_STATUS_START = 1000;
static const uint16_t REGISTERS_STATUS_COUNT = 10;
static const uint16_t REGISTERS_CONFIG_START = 2000;
static const uint16_t REGISTERS_CONFIG_COUNT = 18;

static const uint8_t VEHICLE_STATES_SIZE = 6;
static const char *const VEHICLE_STATES[VEHICLE_STATES_SIZE] = {
    "",                           // 0x00
    "Ready",                      // 0x01
    "Present",                    // 0x02
    "Charging",                   // 0x03
    "Charging with ventilation",  // 0x04
    "Error",                      // 0x05
};

static const uint8_t EVSE_STATES_SIZE = 4;
static const char *const EVSE_STATES[EVSE_STATES_SIZE] = {
    "",     // 0x00
    "12V",  // 0x01
    "PWM",  // 0x02
    "Off",  // 0x03
};

void EvseWallbox::on_modbus_data(const std::vector<uint8_t> &data) {
  if (data.size() == REGISTERS_CONFIG_COUNT * 2) {
    this->on_config_data_(data);
    return;
  }

  if (data.size() == REGISTERS_STATUS_COUNT * 2) {
    this->on_status_data_(data);
    return;
  }

  ESP_LOGW(TAG, "Invalid size (%zu) for EVSE wallbox frame!", data.size());
  ESP_LOGW(TAG, "Payload: %s", format_hex_pretty(&data.front(), data.size()).c_str());
}

void EvseWallbox::on_config_data_(const std::vector<uint8_t> &data) {
  auto evse_get_16bit = [&](size_t i) -> uint16_t {
    return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
  };

  ESP_LOGI(TAG, "Config frame received");

  // Config request (read register 2000...1018)
  // 0x01 0x03 0x07 0xD0 0x00 0x12 0xC5 0x4A
  //
  // Config response
  // 0x01 0x03 0x24 0x00 0x20 0x00 0x01 0x00 0x05 0x00 0x01 0x00 0x00 0x02 0x09 0x00 0x00 0x00 0x00 0xFF 0xFF
  // 0x00 0x03 0x00 0x06 0x00 0x0A 0x00 0x10 0x00 0x19 0x00 0x20 0x00 0x30 0x00 0x3F 0x00 0x50 0x42 0xEE
  //
  // Data:          0x00 0x20 0x00 0x01 0x00 0x05 0x00 0x01 0x00 0x00 0x02 0x09 0x00 0x00 0x00 0x00 0xFF 0xFF
  //                0x00 0x03 0x00 0x06 0x00 0x0A 0x00 0x10 0x00 0x19 0x00 0x20 0x00 0x30 0x00 0x3F 0x00 0x50
  //
  // *Data*
  //
  // Register  Byte   Address Content: Description                      Decoded content               Coeff./Unit
  //   2000      0    0xFF 0xFF        Default current                                                1.0 A
  ESP_LOGI(TAG, "  Default current: %d A", evse_get_16bit(0));
  //   2001      2    0x00 0xFF        Modbus address
  ESP_LOGI(TAG, "  Modbus address: %d", data[3]);
  //   2002      4    0xFF 0xFF        Minimum current                                                1.0 A
  ESP_LOGI(TAG, "  Minimum current: %d A", evse_get_16bit(4));
  //   2003      6    0xFF 0xFF        Analog input config
  ESP_LOGI(TAG, "  Analog input config: %d", evse_get_16bit(6));
  //   2004      8    0xFF 0xFF        Save current on button press
  ESP_LOGI(TAG, "  Save current on button press: %d", evse_get_16bit(8));
  //   2005     10    0xFF 0xFF        Config bits
  uint16_t raw_config_bits = evse_get_16bit(10);
  ESP_LOGI(TAG, "  Config bits: %d", raw_config_bits);
  ESP_LOGI(TAG, "    Enable button for current change: %s", YESNO(check_bit_(raw_config_bits, 1)));
  ESP_LOGI(TAG, "    Stop charging when button pressed: %s", YESNO(check_bit_(raw_config_bits, 2)));
  ESP_LOGI(TAG, "    Pilot ready state LED always on: %s", YESNO(check_bit_(raw_config_bits, 4)));
  ESP_LOGI(TAG, "    Enable charging on vehicle status D: %s", YESNO(check_bit_(raw_config_bits, 8)));
  ESP_LOGI(TAG, "    Enable RCD feedback on MCLR pin (pin 4): %s", YESNO(check_bit_(raw_config_bits, 16)));
  ESP_LOGI(TAG, "    Auto clear RCD error: %s", YESNO(check_bit_(raw_config_bits, 32)));
  ESP_LOGI(TAG, "    AN internal pull-up enabled: %s", YESNO(check_bit_(raw_config_bits, 64)));
  ESP_LOGI(TAG, "    Disable EVSE after charge: %s", YESNO(check_bit_(raw_config_bits, 8192)));
  ESP_LOGI(TAG, "    Disable EVSE: %s", YESNO(check_bit_(raw_config_bits, 16384)));
  ESP_LOGI(TAG, "    Bootloader mode enabled: %s", YESNO(check_bit_(raw_config_bits, 32768)));

  //   2006     12    0xFF 0xFF        Current sharing mode
  //   2007     14    0xFF 0xFF        PP detection limit                                             1.0 A
  ESP_LOGI(TAG, "  PP detection limit: %d A", evse_get_16bit(14));
  //   2008     16    0xFF 0xFF        Reserved
  //   2009     18    0xFF 0xFF        Bootloader version
  ESP_LOGI(TAG, "  Bootloader version: %d", evse_get_16bit(18));
  //   2010     20    0xFF 0xFF        Amps value 1                                                   1.0 A
  ESP_LOGI(TAG, "  Amps value 1: %d A", evse_get_16bit(20));
  //   2011     22    0xFF 0xFF        Amps value 2                                                   1.0 A
  ESP_LOGI(TAG, "  Amps value 2: %d A", evse_get_16bit(22));
  //   2012     24    0xFF 0xFF        Amps value 3                                                   1.0 A
  ESP_LOGI(TAG, "  Amps value 3: %d A", evse_get_16bit(24));
  //   2013     26    0xFF 0xFF        Amps value 4                                                   1.0 A
  ESP_LOGI(TAG, "  Amps value 4: %d A", evse_get_16bit(26));
  //   2014     28    0xFF 0xFF        Amps value 5                                                   1.0 A
  ESP_LOGI(TAG, "  Amps value 5: %d A", evse_get_16bit(28));
  //   2015     30    0xFF 0xFF        Amps value 6                                                   1.0 A
  ESP_LOGI(TAG, "  Amps value 6: %d A", evse_get_16bit(30));
  //   2016     32    0xFF 0xFF        Amps value 7                                                   1.0 A
  ESP_LOGI(TAG, "  Amps value 7: %d A", evse_get_16bit(32));
  //   2017     34    0xFF 0xFF        Amps value 8                                                   1.0 A
  ESP_LOGI(TAG, "  Amps value 8: %d A", evse_get_16bit(34));
}

void EvseWallbox::on_status_data_(const std::vector<uint8_t> &data) {
  auto evse_get_16bit = [&](size_t i) -> uint16_t {
    return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
  };

  ESP_LOGI(TAG, "Status frame received");

  // Status request (read register 1000...1009)
  // 0x01 0x03 0x03 0xE8 0x00 0x09 0x05 0xBC
  //
  // Status response
  // 0x01 0x03 0x14 0x00 0x20 0x00 0x00 0x00 0x01 0x00 0x05 0x00 0x00 0x00 0x12 0x00 0x01 0x00 0x00 0x00 0x00 0x00 0x00
  // 0x21 0xC5
  //
  // Data:          0x00 0x20 0x00 0x00 0x00 0x01 0x00 0x05 0x00 0x00 0x00 0x12 0x00 0x01 0x00 0x00 0x00 0x00 0x00 0x00
  //
  //
  // *Data*
  //
  // Register  Byte   Address Content: Description                      Decoded content               Coeff./Unit
  //   1000      0    0xFF 0xFF        Current setting                                                1.0 A
  ESP_LOGI(TAG, "  Current setting: %d A", evse_get_16bit(0));

  //   1001      2    0xFF 0xFF        Output current (PWM driver output)                             1.0 A
  ESP_LOGI(TAG, "  Output Current (PWM driver): %d A", evse_get_16bit(2));

  //   1002      4    0xFF 0xFF        Vehicle state
  uint16_t raw_vehicle_state = evse_get_16bit(4);
  if (raw_vehicle_state < VEHICLE_STATES_SIZE) {
    ESP_LOGI(TAG, "  Vehicle state: %s (%d)", VEHICLE_STATES[raw_vehicle_state], raw_vehicle_state);
  } else {
    ESP_LOGI(TAG, "  Vehicle state: %s (%d)", "Unknown", raw_vehicle_state);
  }

  //   1003      6    0xFF 0xFF        Cable limit detected                                           1.0 A
  ESP_LOGI(TAG, "  Cable limit detected: %d A", evse_get_16bit(6));

  //   1004      8    0xFF 0xFF        Command bitmask
  uint16_t raw_command_bitmask = evse_get_16bit(8);
  ESP_LOGI(TAG, "  Command bitmask: %d", raw_command_bitmask);
  ESP_LOGI(TAG, "    Turn off charging now: %s", YESNO(check_bit_(raw_command_bitmask, 1)));
  ESP_LOGI(TAG, "    Run RCD test procedure: %s", YESNO(check_bit_(raw_command_bitmask, 2)));
  ESP_LOGI(TAG, "    Clear RCD error: %s", YESNO(check_bit_(raw_command_bitmask, 4)));

  //  1005      10    0xFF 0xFF        Firmware version                                               1.0
  ESP_LOGI(TAG, "  Firmware version: %d", evse_get_16bit(10));

  //  1006      12    0xFF 0xFF        EVSE state                                                     1.0
  uint16_t raw_evse_state = evse_get_16bit(12);
  if (raw_evse_state < EVSE_STATES_SIZE) {
    ESP_LOGI(TAG, "  EVSE state: %s (%d)", EVSE_STATES[raw_evse_state], raw_evse_state);
  } else {
    ESP_LOGI(TAG, "  EVSE state: %s (%d)", "Unknown", raw_evse_state);
  }

  //  1007      14    0xFF 0xFF        Status and errors bitmask
  uint16_t raw_status_bitmask = evse_get_16bit(14);
  ESP_LOGI(TAG, "  Status and errors bitmask: %d", raw_status_bitmask);
  ESP_LOGI(TAG, "    Relay on: %s", YESNO(check_bit_(raw_status_bitmask, 1)));
  ESP_LOGI(TAG, "    Diode check failed: %s", YESNO(check_bit_(raw_status_bitmask, 2)));
  ESP_LOGI(TAG, "    Ventilation failed: %s", YESNO(check_bit_(raw_status_bitmask, 4)));
  ESP_LOGI(TAG, "    Waiting for pilot release (err recovery delay): %s", YESNO(check_bit_(raw_status_bitmask, 8)));
  ESP_LOGI(TAG, "    RCD test in progress: %s", YESNO(check_bit_(raw_status_bitmask, 16)));
  ESP_LOGI(TAG, "    RCD check error: %s", YESNO(check_bit_(raw_status_bitmask, 32)));

  //  1008      16    0xFF 0xFF        Error timeout countdown                                        1.0
  ESP_LOGI(TAG, "  Error timeout countdown: %d", evse_get_16bit(16));

  //  1009      18    0xFF 0xFF        Self-test timeout countdown                                     1.0
  ESP_LOGI(TAG, "  Self-test timeout countdown: %d", evse_get_16bit(18));
}

void EvseWallbox::update() {
  if (this->request_config_) {
    this->send(FUNCTION_READ_REGISTERS, REGISTERS_CONFIG_START, REGISTERS_CONFIG_COUNT);
  } else {
    this->send(FUNCTION_READ_REGISTERS, REGISTERS_STATUS_START, REGISTERS_STATUS_COUNT);
  }
  this->request_config_ = !this->request_config_;

  if (this->enable_fake_traffic_) {
    // Config frame
    this->on_modbus_data({0x00, 0x20, 0x00, 0x01, 0x00, 0x05, 0x00, 0x01, 0x00, 0x00, 0x02, 0x09,
                          0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x03, 0x00, 0x06, 0x00, 0x0A,
                          0x00, 0x10, 0x00, 0x19, 0x00, 0x20, 0x00, 0x30, 0x00, 0x3F, 0x00, 0x50});

    // Status frame
    this->on_modbus_data({0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x05, 0x00, 0x00,
                          0x00, 0x12, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00});
  }
}

void EvseWallbox::write_register(uint16_t address, uint16_t value) {
  uint8_t payload[2];
  payload[0] = value >> 8;
  payload[1] = value & 0xff;
  this->send(FUNCTION_WRITE_MULTIPLE_REGISTERS, address, 0x0001, sizeof(payload), payload);
}

void EvseWallbox::publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state) {
  if (binary_sensor == nullptr)
    return;

  binary_sensor->publish_state(state);
}

void EvseWallbox::publish_state_(number::Number *number, float value) {
  if (number == nullptr)
    return;

  number->publish_state(value);
}

void EvseWallbox::publish_state_(sensor::Sensor *sensor, float value) {
  if (sensor == nullptr)
    return;

  sensor->publish_state(value);
}

void EvseWallbox::publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state) {
  if (text_sensor == nullptr)
    return;

  text_sensor->publish_state(state);
}

void EvseWallbox::publish_state_(switch_::Switch *obj, const bool &state) {
  if (obj == nullptr)
    return;

  obj->publish_state(state);
}

void EvseWallbox::dump_config() {  // NOLINT(google-readability-function-size,readability-function-size)
  ESP_LOGCONFIG(TAG, "EvseWallbox:");
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
}

}  // namespace evse_wallbox
}  // namespace esphome
