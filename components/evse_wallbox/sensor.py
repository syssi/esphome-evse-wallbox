import esphome.codegen as cg
from esphome.components import sensor
import esphome.config_validation as cv
from esphome.const import (
    DEVICE_CLASS_CURRENT,
    DEVICE_CLASS_EMPTY,
    ENTITY_CATEGORY_DIAGNOSTIC,
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
CONF_CONFIG_BITS = "config_bits"

SENSOR_DEFS = {
    CONF_OUTPUT_CURRENT_SETTING: {
        "unit_of_measurement": UNIT_AMPERE,
        "icon": ICON_EMPTY,
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_CURRENT,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_OUTPUT_CURRENT: {
        "unit_of_measurement": UNIT_AMPERE,
        "icon": "mdi:ev-plug-type2",
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_CURRENT,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_VEHICLE_STATUS_CODE: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": "mdi:car-electric",
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_CABLE_LIMIT_DETECTED: {
        "unit_of_measurement": UNIT_AMPERE,
        "icon": "mdi:cable-data",
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_CURRENT,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_LAST_COMMAND_BITMASK: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": "mdi:remote",
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_FIRMWARE_VERSION: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": "mdi:numeric",
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_OPERATION_MODE_CODE: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": "mdi:pulse",
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_ERROR_BITMASK: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": "mdi:alert-circle",
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_ERROR_TIMEOUT_COUNTDOWN: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": "mdi:timer-remove-outline",
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_SELF_TEST_TIMEOUT_COUNTDOWN: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": "mdi:timer-remove-outline",
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
    CONF_CONFIG_BITS: {
        "unit_of_measurement": UNIT_EMPTY,
        "icon": "mdi:cog",
        "accuracy_decimals": 0,
        "device_class": DEVICE_CLASS_EMPTY,
        "state_class": STATE_CLASS_MEASUREMENT,
    },
}

CONFIG_SCHEMA = EVSE_WALLBOX_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(key): sensor.sensor_schema(**kwargs)
        for key, kwargs in SENSOR_DEFS.items()
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_EVSE_WALLBOX_ID])
    for key in SENSOR_DEFS:
        if key in config:
            conf = config[key]
            sens = await sensor.new_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_sensor")(sens))
