"""Schema structure tests for evse_wallbox ESPHome component modules."""

import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), ".."))

import components.evse_wallbox as hub  # noqa: E402
from components.evse_wallbox import (  # noqa: E402
    binary_sensor,
    button,  # noqa: E402
    number,  # noqa: E402
    sensor,
    switch,  # noqa: E402
    text_sensor,
)


class TestHubConstants:
    def test_conf_evse_wallbox_id_defined(self):
        assert hub.CONF_EVSE_WALLBOX_ID == "evse_wallbox_id"


class TestSensorDefs:
    def test_sensor_defs_completeness(self):
        assert sensor.CONF_OUTPUT_CURRENT_SETTING in sensor.SENSOR_DEFS
        assert sensor.CONF_OUTPUT_CURRENT in sensor.SENSOR_DEFS
        assert sensor.CONF_VEHICLE_STATUS_CODE in sensor.SENSOR_DEFS
        assert sensor.CONF_ERROR_BITMASK in sensor.SENSOR_DEFS
        assert sensor.CONF_FIRMWARE_VERSION in sensor.SENSOR_DEFS
        assert sensor.CONF_OPERATION_MODE_CODE in sensor.SENSOR_DEFS
        assert len(sensor.SENSOR_DEFS) == 11


class TestBinarySensorDefs:
    def test_binary_sensor_defs_completeness(self):
        assert binary_sensor.CONF_RELAY in binary_sensor.BINARY_SENSOR_DEFS
        assert binary_sensor.CONF_DIODE_CHECK_FAILED in binary_sensor.BINARY_SENSOR_DEFS
        assert binary_sensor.CONF_VENTILATION_FAILED in binary_sensor.BINARY_SENSOR_DEFS
        assert binary_sensor.CONF_RCD_CHECK_ERROR in binary_sensor.BINARY_SENSOR_DEFS
        assert len(binary_sensor.BINARY_SENSOR_DEFS) == 6


class TestTextSensors:
    def test_text_sensors_list(self):
        assert text_sensor.CONF_VEHICLE_STATUS in text_sensor.TEXT_SENSORS
        assert text_sensor.CONF_LAST_COMMAND in text_sensor.TEXT_SENSORS
        assert text_sensor.CONF_OPERATION_MODE in text_sensor.TEXT_SENSORS
        assert text_sensor.CONF_ERRORS in text_sensor.TEXT_SENSORS
        assert len(text_sensor.TEXT_SENSORS) == 4


class TestSwitchConstants:
    def test_switches_dict(self):
        assert switch.CONF_DISABLE_EVSE in switch.SWITCHES
        assert switch.CONF_BOOTLOADER_MODE in switch.SWITCHES
        assert switch.CONF_CURRENT_CHANGE_BY_BUTTON in switch.SWITCHES
        assert len(switch.SWITCHES) == 10

    def test_switch_values_are_lists(self):
        for val in switch.SWITCHES.values():
            assert isinstance(val, list)
            assert len(val) == 2


class TestNumberConstants:
    def test_numbers_dict(self):
        assert number.CONF_OUTPUT_CURRENT_SETTING in number.NUMBERS
        assert number.CONF_OUTPUT_CURRENT_DEFAULT in number.NUMBERS
        assert number.CONF_MIN_CHARGING_CURRENT in number.NUMBERS
        assert len(number.NUMBERS) == 3

    def test_number_addresses_are_unique(self):
        addresses = list(number.NUMBERS.values())
        assert len(addresses) == len(set(addresses))


class TestButtonConstants:
    def test_buttons_dict(self):
        assert button.CONF_TURN_OFF_CHARGING in button.BUTTONS
        assert button.CONF_START_SELF_TEST in button.BUTTONS
        assert button.CONF_CLEAR_RCD_ERROR in button.BUTTONS
        assert len(button.BUTTONS) == 3
