#include <gtest/gtest.h>
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "common.h"
#include "frames.h"

namespace esphome::evse_wallbox::testing {

class EvseStatusTest : public ::testing::Test {
 protected:
  TestableEvseWallbox wallbox_;
  sensor::Sensor output_current_setting_;
  sensor::Sensor output_current_;
  sensor::Sensor vehicle_status_code_;
  sensor::Sensor cable_limit_detected_;
  sensor::Sensor last_command_bitmask_;
  sensor::Sensor firmware_version_;
  sensor::Sensor operation_mode_code_;
  sensor::Sensor error_bitmask_;
  sensor::Sensor error_timeout_countdown_;
  sensor::Sensor self_test_timeout_countdown_;
  binary_sensor::BinarySensor relay_;
  binary_sensor::BinarySensor diode_check_failed_;
  binary_sensor::BinarySensor ventilation_failed_;
  binary_sensor::BinarySensor rcd_check_error_;
  text_sensor::TextSensor vehicle_status_;
  text_sensor::TextSensor operation_mode_;
  text_sensor::TextSensor errors_;

  void SetUp() override {
    wallbox_.set_output_current_setting_sensor(&output_current_setting_);
    wallbox_.set_output_current_sensor(&output_current_);
    wallbox_.set_vehicle_status_code_sensor(&vehicle_status_code_);
    wallbox_.set_cable_limit_detected_sensor(&cable_limit_detected_);
    wallbox_.set_last_command_bitmask_sensor(&last_command_bitmask_);
    wallbox_.set_firmware_version_sensor(&firmware_version_);
    wallbox_.set_operation_mode_code_sensor(&operation_mode_code_);
    wallbox_.set_error_bitmask_sensor(&error_bitmask_);
    wallbox_.set_error_timeout_countdown_sensor(&error_timeout_countdown_);
    wallbox_.set_self_test_timeout_countdown_sensor(&self_test_timeout_countdown_);
    wallbox_.set_relay_binary_sensor(&relay_);
    wallbox_.set_diode_check_failed_binary_sensor(&diode_check_failed_);
    wallbox_.set_ventilation_failed_binary_sensor(&ventilation_failed_);
    wallbox_.set_rcd_check_error_binary_sensor(&rcd_check_error_);
    wallbox_.set_vehicle_status_text_sensor(&vehicle_status_);
    wallbox_.set_operation_mode_text_sensor(&operation_mode_);
    wallbox_.set_errors_text_sensor(&errors_);
  }
};

TEST_F(EvseStatusTest, OutputCurrentSetting) {
  wallbox_.on_status_data_(STATUS_FRAME);
  EXPECT_FLOAT_EQ(output_current_setting_.state, 32.0f);
}

TEST_F(EvseStatusTest, OutputCurrentZero) {
  wallbox_.on_status_data_(STATUS_FRAME);
  EXPECT_FLOAT_EQ(output_current_.state, 0.0f);
}

TEST_F(EvseStatusTest, VehicleStateReady) {
  wallbox_.on_status_data_(STATUS_FRAME);
  EXPECT_FLOAT_EQ(vehicle_status_code_.state, 1.0f);
  EXPECT_EQ(vehicle_status_.state, "Ready");
}

TEST_F(EvseStatusTest, CableLimitDetected) {
  wallbox_.on_status_data_(STATUS_FRAME);
  EXPECT_FLOAT_EQ(cable_limit_detected_.state, 5.0f);
}

TEST_F(EvseStatusTest, FirmwareVersion) {
  wallbox_.on_status_data_(STATUS_FRAME);
  EXPECT_FLOAT_EQ(firmware_version_.state, 18.0f);
}

TEST_F(EvseStatusTest, OperationMode12V) {
  wallbox_.on_status_data_(STATUS_FRAME);
  EXPECT_FLOAT_EQ(operation_mode_code_.state, 1.0f);
  EXPECT_EQ(operation_mode_.state, "12V");
}

TEST_F(EvseStatusTest, ErrorBitmaskZero) {
  wallbox_.on_status_data_(STATUS_FRAME);
  EXPECT_FLOAT_EQ(error_bitmask_.state, 0.0f);
  EXPECT_EQ(errors_.state, "");
}

TEST_F(EvseStatusTest, RelayFalse) {
  wallbox_.on_status_data_(STATUS_FRAME);
  EXPECT_FALSE(relay_.state);
}

TEST_F(EvseStatusTest, NoErrorBinaryFalse) {
  wallbox_.on_status_data_(STATUS_FRAME);
  EXPECT_FALSE(diode_check_failed_.state);
  EXPECT_FALSE(ventilation_failed_.state);
  EXPECT_FALSE(rcd_check_error_.state);
}

TEST_F(EvseStatusTest, Rev15VehicleStatePresent) {
  wallbox_.on_status_data_(STATUS_FRAME_REV15);
  EXPECT_FLOAT_EQ(vehicle_status_code_.state, 2.0f);
  EXPECT_EQ(vehicle_status_.state, "Present");
}

TEST_F(EvseStatusTest, Rev15OperationModeStandby) {
  wallbox_.on_status_data_(STATUS_FRAME_REV15);
  EXPECT_FLOAT_EQ(operation_mode_code_.state, 3.0f);
  EXPECT_EQ(operation_mode_.state, "Standby");
}

TEST_F(EvseStatusTest, Rev15OutputCurrentSetting) {
  wallbox_.on_status_data_(STATUS_FRAME_REV15);
  EXPECT_FLOAT_EQ(output_current_setting_.state, 3.0f);
}

TEST_F(EvseStatusTest, NullSensorSafe) {
  TestableEvseWallbox bare;
  EXPECT_NO_FATAL_FAILURE(bare.on_status_data_(STATUS_FRAME));
}

class EvseConfigTest : public ::testing::Test {
 protected:
  TestableEvseWallbox wallbox_;
  sensor::Sensor config_bits_;

  void SetUp() override { wallbox_.set_config_bits_sensor(&config_bits_); }
};

TEST_F(EvseConfigTest, ConfigBits) {
  wallbox_.on_config_data_(CONFIG_FRAME);
  EXPECT_FLOAT_EQ(config_bits_.state, 0x0209);
}

TEST_F(EvseConfigTest, NullSensorSafe) {
  TestableEvseWallbox bare;
  EXPECT_NO_FATAL_FAILURE(bare.on_config_data_(CONFIG_FRAME));
}

}  // namespace esphome::evse_wallbox::testing
