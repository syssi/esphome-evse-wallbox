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
  void set_relay_binary_sensor(binary_sensor::BinarySensor *relay_binary_sensor) {
    relay_binary_sensor_ = relay_binary_sensor;
  }
  void set_diode_check_failed_binary_sensor(binary_sensor::BinarySensor *diode_check_failed_binary_sensor) {
    diode_check_failed_binary_sensor_ = diode_check_failed_binary_sensor;
  }
  void set_ventilation_failed_binary_sensor(binary_sensor::BinarySensor *ventilation_failed_binary_sensor) {
    ventilation_failed_binary_sensor_ = ventilation_failed_binary_sensor;
  }
  void set_waiting_for_pilot_release_binary_sensor(
      binary_sensor::BinarySensor *waiting_for_pilot_release_binary_sensor) {
    waiting_for_pilot_release_binary_sensor_ = waiting_for_pilot_release_binary_sensor;
  }
  void set_rcd_test_in_progress_binary_sensor(binary_sensor::BinarySensor *rcd_test_in_progress_binary_sensor) {
    rcd_test_in_progress_binary_sensor_ = rcd_test_in_progress_binary_sensor;
  }
  void set_rcd_check_error_binary_sensor(binary_sensor::BinarySensor *rcd_check_error_binary_sensor) {
    rcd_check_error_binary_sensor_ = rcd_check_error_binary_sensor;
  }

  void set_output_current_setting_number(number::Number *output_current_setting_number) {
    output_current_setting_number_ = output_current_setting_number;
  }
  void set_output_current_default_number(number::Number *output_current_default_number) {
    output_current_default_number_ = output_current_default_number;
  }
  void set_min_charging_current_number(number::Number *min_charging_current_number) {
    min_charging_current_number_ = min_charging_current_number;
  }

  void set_output_current_setting_sensor(sensor::Sensor *output_current_setting_sensor) {
    output_current_setting_sensor_ = output_current_setting_sensor;
  }
  void set_output_current_sensor(sensor::Sensor *output_current_sensor) {
    output_current_sensor_ = output_current_sensor;
  }
  void set_vehicle_status_code_sensor(sensor::Sensor *vehicle_status_code_sensor) {
    vehicle_status_code_sensor_ = vehicle_status_code_sensor;
  }
  void set_cable_limit_detected_sensor(sensor::Sensor *cable_limit_detected_sensor) {
    cable_limit_detected_sensor_ = cable_limit_detected_sensor;
  }
  void set_last_command_bitmask_sensor(sensor::Sensor *last_command_bitmask_sensor) {
    last_command_bitmask_sensor_ = last_command_bitmask_sensor;
  }
  void set_firmware_version_sensor(sensor::Sensor *firmware_version_sensor) {
    firmware_version_sensor_ = firmware_version_sensor;
  }
  void set_operation_mode_code_sensor(sensor::Sensor *operation_mode_code_sensor) {
    operation_mode_code_sensor_ = operation_mode_code_sensor;
  }
  void set_error_bitmask_sensor(sensor::Sensor *error_bitmask_sensor) { error_bitmask_sensor_ = error_bitmask_sensor; }
  void set_error_timeout_countdown_sensor(sensor::Sensor *error_timeout_countdown_sensor) {
    error_timeout_countdown_sensor_ = error_timeout_countdown_sensor;
  }
  void set_self_test_timeout_countdown_sensor(sensor::Sensor *self_test_timeout_countdown_sensor) {
    self_test_timeout_countdown_sensor_ = self_test_timeout_countdown_sensor;
  }
  void set_config_bits_sensor(sensor::Sensor *config_bits_sensor) { config_bits_sensor_ = config_bits_sensor; }

  void set_vehicle_status_text_sensor(text_sensor::TextSensor *vehicle_status_text_sensor) {
    vehicle_status_text_sensor_ = vehicle_status_text_sensor;
  }
  void set_last_command_text_sensor(text_sensor::TextSensor *last_command_text_sensor) {
    last_command_text_sensor_ = last_command_text_sensor;
  }
  void set_operation_mode_text_sensor(text_sensor::TextSensor *operation_mode_text_sensor) {
    operation_mode_text_sensor_ = operation_mode_text_sensor;
  }
  void set_errors_text_sensor(text_sensor::TextSensor *errors_text_sensor) { errors_text_sensor_ = errors_text_sensor; }

  void set_current_change_by_button_switch(switch_::Switch *current_change_by_button_switch) {
    current_change_by_button_switch_ = current_change_by_button_switch;
  }
  void set_stop_charging_on_button_press_switch(switch_::Switch *stop_charging_on_button_press_switch) {
    stop_charging_on_button_press_switch_ = stop_charging_on_button_press_switch;
  }
  void set_pilot_ready_state_led_always_on_switch(switch_::Switch *pilot_ready_state_led_always_on_switch) {
    pilot_ready_state_led_always_on_switch_ = pilot_ready_state_led_always_on_switch;
  }
  void set_charging_of_vehicle_status_d_switch(switch_::Switch *charging_of_vehicle_status_d_switch) {
    charging_of_vehicle_status_d_switch_ = charging_of_vehicle_status_d_switch;
  }
  void set_rcd_feedback_on_mclr_pin_switch(switch_::Switch *rcd_feedback_on_mclr_pin_switch) {
    rcd_feedback_on_mclr_pin_switch_ = rcd_feedback_on_mclr_pin_switch;
  }
  void set_auto_clear_rcd_error_switch(switch_::Switch *auto_clear_rcd_error_switch) {
    auto_clear_rcd_error_switch_ = auto_clear_rcd_error_switch;
  }
  void set_an_internal_pullup_switch(switch_::Switch *an_internal_pullup_switch) {
    an_internal_pullup_switch_ = an_internal_pullup_switch;
  }
  void set_disable_evse_after_charge_switch(switch_::Switch *disable_evse_after_charge_switch) {
    disable_evse_after_charge_switch_ = disable_evse_after_charge_switch;
  }
  void set_disable_evse_switch(switch_::Switch *disable_evse_switch) { disable_evse_switch_ = disable_evse_switch; }
  void set_bootloader_mode_switch(switch_::Switch *bootloader_mode_switch) {
    bootloader_mode_switch_ = bootloader_mode_switch;
  }

  void set_enable_fake_traffic(bool enable_fake_traffic) { enable_fake_traffic_ = enable_fake_traffic; }

  void dump_config() override;

  void on_modbus_data(const std::vector<uint8_t> &data) override;

  void update() override;

  void write_register(uint16_t address, uint16_t value);

 protected:
  binary_sensor::BinarySensor *relay_binary_sensor_;
  binary_sensor::BinarySensor *diode_check_failed_binary_sensor_;
  binary_sensor::BinarySensor *ventilation_failed_binary_sensor_;
  binary_sensor::BinarySensor *waiting_for_pilot_release_binary_sensor_;
  binary_sensor::BinarySensor *rcd_test_in_progress_binary_sensor_;
  binary_sensor::BinarySensor *rcd_check_error_binary_sensor_;

  number::Number *output_current_setting_number_;
  number::Number *output_current_default_number_;
  number::Number *min_charging_current_number_;

  sensor::Sensor *output_current_setting_sensor_;
  sensor::Sensor *output_current_sensor_;
  sensor::Sensor *vehicle_status_code_sensor_;
  sensor::Sensor *cable_limit_detected_sensor_;
  sensor::Sensor *last_command_bitmask_sensor_;
  sensor::Sensor *firmware_version_sensor_;
  sensor::Sensor *operation_mode_code_sensor_;
  sensor::Sensor *error_bitmask_sensor_;
  sensor::Sensor *error_timeout_countdown_sensor_;
  sensor::Sensor *self_test_timeout_countdown_sensor_;
  sensor::Sensor *config_bits_sensor_;

  switch_::Switch *current_change_by_button_switch_;
  switch_::Switch *stop_charging_on_button_press_switch_;
  switch_::Switch *pilot_ready_state_led_always_on_switch_;
  switch_::Switch *charging_of_vehicle_status_d_switch_;
  switch_::Switch *rcd_feedback_on_mclr_pin_switch_;
  switch_::Switch *auto_clear_rcd_error_switch_;
  switch_::Switch *an_internal_pullup_switch_;
  switch_::Switch *disable_evse_after_charge_switch_;
  switch_::Switch *disable_evse_switch_;
  switch_::Switch *bootloader_mode_switch_;

  text_sensor::TextSensor *vehicle_status_text_sensor_;
  text_sensor::TextSensor *last_command_text_sensor_;
  text_sensor::TextSensor *operation_mode_text_sensor_;
  text_sensor::TextSensor *errors_text_sensor_;

  bool enable_fake_traffic_;
  bool request_config_{true};
  bool check_bit_(uint16_t mask, uint16_t flag) { return (mask & flag) == flag; }

  std::string error_bits_to_string_(uint16_t bitmask);

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
