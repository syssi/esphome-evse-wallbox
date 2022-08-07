import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_EMPTY,
    ICON_EMPTY,
    STATE_CLASS_MEASUREMENT,
    UNIT_AMPERE,
    UNIT_EMPTY,
)

from . import CONF_EVSE_WALLBOX_ID, EVSE_WALLBOX_COMPONENT_SCHEMA

DEPENDENCIES = ["evse_wallbox"]

CODEOWNERS = ["@syssi"]

CONF_OUTPUT_CURRENT_SETTING = "output_current_setting"
CONF_OUTPUT_CURRENT = "output_current"
CONF_VEHICLE_STATUS_CODE = "vehicle_status_code"
CONF_CABLE_LIMIT_DETECTED = "cable_limit_detected"
CONF_LAST_COMMAND_BITMASK = "last_command_bitmask"
CONF_FIRMWARE_VERSION = "firmware_version"
CONF_OPERATION_MODE_CODE = "operation_mode_code"
CONF_ERROR_BITMASK = "error_bitmask"
CONF_ERROR_TIMEOUT_COUNTDOWN = "error_timeout_countdown"
CONF_SELF_TEST_TIMEOUT_COUNTDOWN = "self_test_timeout_countdown"

SENSORS = [
    CONF_OUTPUT_CURRENT_SETTING,
    CONF_OUTPUT_CURRENT,
    CONF_VEHICLE_STATUS_CODE,
    CONF_CABLE_LIMIT_DETECTED,
    CONF_LAST_COMMAND_BITMASK,
    CONF_FIRMWARE_VERSION,
    CONF_OPERATION_MODE_CODE,
    CONF_ERROR_BITMASK,
    CONF_ERROR_TIMEOUT_COUNTDOWN,
    CONF_SELF_TEST_TIMEOUT_COUNTDOWN,
]

# pylint: disable=too-many-function-args
CONFIG_SCHEMA = EVSE_WALLBOX_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_OUTPUT_CURRENT_SETTING): sensor.sensor_schema(
            unit_of_measurement=UNIT_AMPERE,
            icon=ICON_EMPTY,
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_CURRENT,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_OUTPUT_CURRENT): sensor.sensor_schema(
            unit_of_measurement=UNIT_AMPERE,
            icon="mdi:ev-plug-type2",
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_CURRENT,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_VEHICLE_STATUS_CODE): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon="mdi:car-electric",
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_CABLE_LIMIT_DETECTED): sensor.sensor_schema(
            unit_of_measurement=UNIT_AMPERE,
            icon="mdi:cable-data",
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_CURRENT,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_LAST_COMMAND_BITMASK): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon="mdi:remote",
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_FIRMWARE_VERSION): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon="mdi:numeric",
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_OPERATION_MODE_CODE): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon="mdi:pulse",
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_ERROR_BITMASK): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon="mdi:alert-circle",
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_ERROR_TIMEOUT_COUNTDOWN): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon="mdi:timer-remove-outline",
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
        cv.Optional(CONF_SELF_TEST_TIMEOUT_COUNTDOWN): sensor.sensor_schema(
            unit_of_measurement=UNIT_EMPTY,
            icon="mdi:timer-remove-outline",
            accuracy_decimals=0,
            device_class=DEVICE_CLASS_EMPTY,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_EVSE_WALLBOX_ID])
    for key in SENSORS:
        if key in config:
            conf = config[key]
            sens = await sensor.new_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_sensor")(sens))
