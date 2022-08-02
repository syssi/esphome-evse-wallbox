#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/number/number.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/modbus/modbus.h"

namespace esphome {
namespace evse_wallbox {

class EvseWallbox : public PollingComponent, public modbus::ModbusDevice {
 public:
  void set_output_binary_sensor(binary_sensor::BinarySensor *output_binary_sensor) {
    output_binary_sensor_ = output_binary_sensor;
  }

  void set_voltage_setting_number(number::Number *voltage_setting_number) {
    voltage_setting_number_ = voltage_setting_number;
  }

  void set_output_voltage_sensor(sensor::Sensor *output_voltage_sensor) {
    output_voltage_sensor_ = output_voltage_sensor;
  }

  void set_output_switch(switch_::Switch *output_switch) { output_switch_ = output_switch; }

  void set_enable_fake_traffic(bool enable_fake_traffic) { enable_fake_traffic_ = enable_fake_traffic; }

  void dump_config() override;

  void on_modbus_data(const std::vector<uint8_t> &data) override;

  void update() override;

  void write_register(uint16_t address, uint16_t value);

 protected:
  binary_sensor::BinarySensor *output_binary_sensor_;

  number::Number *voltage_setting_number_;

  sensor::Sensor *output_voltage_sensor_;

  switch_::Switch *output_switch_;

  text_sensor::TextSensor *protection_status_text_sensor_;

  bool enable_fake_traffic_;
  bool request_config_{true};
  bool check_bit_(uint16_t mask, uint16_t flag) { return (mask & flag) == flag; }

  void on_status_data_(const std::vector<uint8_t> &data);
  void on_config_data_(const std::vector<uint8_t> &data);
  void publish_state_(binary_sensor::BinarySensor *binary_sensor, const bool &state);
  void publish_state_(number::Number *number, float value);
  void publish_state_(sensor::Sensor *sensor, float value);
  void publish_state_(switch_::Switch *obj, const bool &state);
  void publish_state_(text_sensor::TextSensor *text_sensor, const std::string &state);
};

}  // namespace evse_wallbox
}  // namespace esphome
