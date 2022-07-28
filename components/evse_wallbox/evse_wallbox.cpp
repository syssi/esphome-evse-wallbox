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
  // ->
  //
  // Config response
  // <-
  //
  // Data:
  //
  //
  // *Data*
  //
  // Register  Byte   Address Content: Description                      Decoded content               Coeff./Unit
  //   2000      0    0xFF 0xFF        Default current                                                1.0 A
  ESP_LOGI(TAG, "  Default current: %d A", evse_get_16bit(0));
  //   2001      2    0x00 0xFF        Modbus address
  ESP_LOGI(TAG, "  Default current: %d A", data[3]);
  //   2002      4    0xFF 0xFF        Minimum current limit                                          1.0 A
  ESP_LOGI(TAG, "  Minimum current limit: %d A", evse_get_16bit(4));
  //   2003      6    0xFF 0xFF        Analog input config
  ESP_LOGI(TAG, "  Analog input config: %d", evse_get_16bit(6));
  //   2004      8    0xFF 0xFF        Save current on button press
  ESP_LOGI(TAG, "  Save current on button press: %d", evse_get_16bit(8));
  //   2005     10    0xFF 0xFF        Config bits
  ESP_LOGI(TAG, "  Config bits: %d", evse_get_16bit(10));
  //   2006     12    0xFF 0xFF        Reserved
  //   2007     14    0xFF 0xFF        PP detection limit                                             1.0 A
  ESP_LOGI(TAG, "  PP detection limit: %d", evse_get_16bit(14));
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
  // ->
  //
  // Status response
  // <-
  //
  // Data:
  //
  //
  // *Data*
  //
  // Register  Byte   Address Content: Description                      Decoded content               Coeff./Unit
  //   1000      0    0xFF 0xFF        Current setting                                                1.0 A
  ESP_LOGI(TAG, "  Current setting: %d A", evse_get_16bit(0));
  //   1001      2    0xFF 0xFF        Current (PWM driver output)                                    1.0 A
  ESP_LOGI(TAG, "  Current (PWM driver output): %d A", evse_get_16bit(2));
  //   1002      4    0xFF 0xFF        Vehicle state
  ESP_LOGI(TAG, "  Vehicle state: %d A", evse_get_16bit(4));
  //   1003      6    0xFF 0xFF        Cable limit detected                                           1.0 A
  ESP_LOGI(TAG, "  Cable limit detected: %d A", evse_get_16bit(6));
  //   1004      8    0xFF 0xFF        Command bitmask
  ESP_LOGI(TAG, "  Command bitmask: %d", evse_get_16bit(8));
  //  1005      10    0xFF 0xFF        Firmware version                                               1.0
  ESP_LOGI(TAG, "  Firmware version: %d", evse_get_16bit(10));
  //  1006      12    0xFF 0xFF        EVSE state                                                     1.0
  ESP_LOGI(TAG, "  EVSE state: %d", evse_get_16bit(12));
  //  1007      14    0xFF 0xFF        Status and errors bitmask
  ESP_LOGI(TAG, "  Status and errors bitmask: %d", evse_get_16bit(14));
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

  /*
  if (this->enable_fake_traffic_) {
    this->on_modbus_data({0x0E, 0x10, 0x03, 0xE8, 0x0E, 0x0E, 0x00, 0xED, 0x21, 0x4F, 0x10, 0x87, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x13, 0x9C, 0x00, 0x11});
  }
   */
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
