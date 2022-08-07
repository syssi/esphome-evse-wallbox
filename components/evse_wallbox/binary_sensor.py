import esphome.codegen as cg
from esphome.components import binary_sensor
import esphome.config_validation as cv
from esphome.const import CONF_ICON, CONF_ID, ICON_EMPTY

from . import CONF_EVSE_WALLBOX_ID, EVSE_WALLBOX_COMPONENT_SCHEMA

DEPENDENCIES = ["evse_wallbox"]

CODEOWNERS = ["@syssi"]

CONF_RELAY = "relay"
CONF_DIODE_CHECK_FAILED = "diode_check_failed"
CONF_VENTILATION_FAILED = "ventilation_failed"
CONF_WAITING_FOR_PILOT_RELEASE = "waiting_for_pilot_release"
CONF_RCD_TEST_IN_PROGRESS = "rcd_test_in_progress"
CONF_RCD_CHECK_ERROR = "rcd_check_error"

BINARY_SENSORS = [
    CONF_RELAY,
    CONF_DIODE_CHECK_FAILED,
    CONF_VENTILATION_FAILED,
    CONF_WAITING_FOR_PILOT_RELEASE,
    CONF_RCD_TEST_IN_PROGRESS,
    CONF_RCD_CHECK_ERROR,
]

CONFIG_SCHEMA = EVSE_WALLBOX_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_RELAY): binary_sensor.BINARY_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(binary_sensor.BinarySensor),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
            }
        ),
        cv.Optional(CONF_DIODE_CHECK_FAILED): binary_sensor.BINARY_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(binary_sensor.BinarySensor),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
            }
        ),
        cv.Optional(CONF_VENTILATION_FAILED): binary_sensor.BINARY_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(binary_sensor.BinarySensor),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
            }
        ),
        cv.Optional(
            CONF_WAITING_FOR_PILOT_RELEASE
        ): binary_sensor.BINARY_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(binary_sensor.BinarySensor),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
            }
        ),
        cv.Optional(
            CONF_RCD_TEST_IN_PROGRESS
        ): binary_sensor.BINARY_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(binary_sensor.BinarySensor),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
            }
        ),
        cv.Optional(CONF_RCD_CHECK_ERROR): binary_sensor.BINARY_SENSOR_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(binary_sensor.BinarySensor),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
            }
        ),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_EVSE_WALLBOX_ID])
    for key in BINARY_SENSORS:
        if key in config:
            conf = config[key]
            sens = cg.new_Pvariable(conf[CONF_ID])
            await binary_sensor.register_binary_sensor(sens, conf)
            cg.add(getattr(hub, f"set_{key}_binary_sensor")(sens))
