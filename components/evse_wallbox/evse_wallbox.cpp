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
static const uint16_t REGISTERS_STATUS_COUNT = 9;
static const uint16_t REGISTERS_CONFIG_START = 2000;
static const uint16_t REGISTERS_CONFIG_COUNT = 18;

void EvseWallbox::on_modbus_data(const std::vector<uint8_t> &data) {
  /*
  if (data.size() == 26) {
    this->on_status_data_(data);
    return;
  }

  if (data.size() == 4) {
    this->on_acknowledge_data_(data);
    return;
  }
  */

  ESP_LOGW(TAG, "Invalid size (%zu) for EVSE wallbox frame!", data.size());
  ESP_LOGW(TAG, "Payload: %s", format_hex_pretty(&data.front(), data.size()).c_str());
}

void EvseWallbox::on_config_data_(const std::vector<uint8_t> &data) {
  //  auto evse_get_16bit = [&](size_t i) -> uint16_t {
  //    return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
  //  };
}

void EvseWallbox::on_status_data_(const std::vector<uint8_t> &data) {
  //  auto evse_get_16bit = [&](size_t i) -> uint16_t {
  //    return (uint16_t(data[i + 0]) << 8) | (uint16_t(data[i + 1]) << 0);
  //  };

  ESP_LOGI(TAG, "Status frame received");

  // Status request (read register 0...13)
  // -> 0x01 0x03 0x00 0x00 0x00 0x0D 0x84 0x0F
  //
  // Status response
  // <- 0x01 0x03 0x1A 0x0E 0x10 0x03 0xE8 0x0E 0x0E 0x00 0xED 0x21 0x4F 0x10 0x87 0x00
  //    0x00 0x00 0x00 0x00 0x00 0x00 0x01 0x00 0x00 0x13 0x9C 0x00 0x11 0x87 0xBD
  //
  // Data: 0x0E 0x10 0x03 0xE8 0x0E 0x0E 0x00 0xED 0x21 0x4F 0x10 0x87 0x00
  //       0x00 0x00 0x00 0x00 0x00 0x00 0x01 0x00 0x00 0x13 0x9C 0x00 0x11
  //
  // *Data*
  //
  // Byte   Address Content: Description                      Decoded content               Coeff./Unit
  //   0    0x0E 0x10        Voltage setting                  3600 * 0.01 = 36.00V          0.01 V
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
