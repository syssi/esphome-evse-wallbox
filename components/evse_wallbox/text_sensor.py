import esphome.codegen as cg
from esphome.components import text_sensor
import esphome.config_validation as cv
from esphome.const import CONF_ID

from . import CONF_EVSE_WALLBOX_ID, EVSE_WALLBOX_COMPONENT_SCHEMA

DEPENDENCIES = ["evse_wallbox"]

CODEOWNERS = ["@syssi"]

CONF_VEHICLE_STATUS = "vehicle_status"
CONF_LAST_COMMAND = "last_command"
CONF_OPERATION_MODE = "operation_mode"
CONF_ERRORS = "errors"

TEXT_SENSORS = [
    CONF_VEHICLE_STATUS,
    CONF_LAST_COMMAND,
    CONF_OPERATION_MODE,
    CONF_ERRORS,
]

CONFIG_SCHEMA = EVSE_WALLBOX_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_VEHICLE_STATUS): text_sensor.text_sensor_schema(
            text_sensor.TextSensor, icon="mdi:car-electric"
        ),
        cv.Optional(CONF_LAST_COMMAND): text_sensor.text_sensor_schema(
            text_sensor.TextSensor, icon="mdi:remote"
        ),
        cv.Optional(CONF_OPERATION_MODE): text_sensor.text_sensor_schema(
            text_sensor.TextSensor, icon="mdi:pulse"
        ),
        cv.Optional(CONF_ERRORS): text_sensor.text_sensor_schema(
            text_sensor.TextSensor, icon="mdi:alert-circle"
        ),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_EVSE_WALLBOX_ID])
    for key in TEXT_SENSORS:
        if key in config:
            conf = config[key]
            sens = cg.new_Pvariable(conf[CONF_ID])
            await text_sensor.register_text_sensor(sens, conf)
            cg.add(getattr(hub, f"set_{key}_text_sensor")(sens))
