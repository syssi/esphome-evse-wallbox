import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import ENTITY_CATEGORY_DIAGNOSTIC, ICON_EMPTY

from . import CONF_EVSE_WALLBOX_ID, EVSE_WALLBOX_COMPONENT_SCHEMA

DEPENDENCIES = ["evse_wallbox"]

CODEOWNERS = ["@syssi"]

CONF_RELAY = "relay"
CONF_DIODE_CHECK_FAILED = "diode_check_failed"
CONF_VENTILATION_FAILED = "ventilation_failed"
CONF_WAITING_FOR_PILOT_RELEASE = "waiting_for_pilot_release"
CONF_RCD_TEST_IN_PROGRESS = "rcd_test_in_progress"
CONF_RCD_CHECK_ERROR = "rcd_check_error"

BINARY_SENSOR_DEFS = {
    CONF_RELAY: {"icon": ICON_EMPTY, "entity_category": ENTITY_CATEGORY_DIAGNOSTIC},
    CONF_DIODE_CHECK_FAILED: {
        "icon": ICON_EMPTY,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_VENTILATION_FAILED: {
        "icon": ICON_EMPTY,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_WAITING_FOR_PILOT_RELEASE: {
        "icon": ICON_EMPTY,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_RCD_TEST_IN_PROGRESS: {
        "icon": ICON_EMPTY,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
    CONF_RCD_CHECK_ERROR: {
        "icon": ICON_EMPTY,
        "entity_category": ENTITY_CATEGORY_DIAGNOSTIC,
    },
}

CONFIG_SCHEMA = EVSE_WALLBOX_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(key): binary_sensor.binary_sensor_schema(**kwargs)
        for key, kwargs in BINARY_SENSOR_DEFS.items()
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_EVSE_WALLBOX_ID])
    for key in BINARY_SENSOR_DEFS:
        if key in config:
            conf = config[key]
            sens = await binary_sensor.new_binary_sensor(conf)
            cg.add(getattr(hub, f"set_{key}_binary_sensor")(sens))
