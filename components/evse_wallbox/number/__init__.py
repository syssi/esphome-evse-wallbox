import esphome.codegen as cg
from esphome.components import number
import esphome.config_validation as cv
from esphome.const import (
    CONF_ENTITY_CATEGORY,
    CONF_ICON,
    CONF_ID,
    CONF_MAX_VALUE,
    CONF_MIN_VALUE,
    CONF_MODE,
    CONF_STEP,
    CONF_UNIT_OF_MEASUREMENT,
    ENTITY_CATEGORY_CONFIG,
    ICON_EMPTY,
    UNIT_AMPERE,
)

from .. import CONF_EVSE_WALLBOX_ID, EVSE_WALLBOX_COMPONENT_SCHEMA, evse_wallbox_ns

DEPENDENCIES = ["evse_wallbox"]

CODEOWNERS = ["@syssi"]

DEFAULT_STEP = 1

CONF_OUTPUT_CURRENT_SETTING = "output_current_setting"
CONF_OUTPUT_CURRENT_DEFAULT = "output_current_default"
CONF_MIN_CHARGING_CURRENT = "min_charging_current"

NUMBERS = {
    CONF_OUTPUT_CURRENT_SETTING: 1000,
    CONF_OUTPUT_CURRENT_DEFAULT: 2000,
    CONF_MIN_CHARGING_CURRENT: 2002,
}

EvseNumber = evse_wallbox_ns.class_("EvseNumber", number.Number, cg.Component)

EVSE_NUMBER_SCHEMA = number.NUMBER_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(EvseNumber),
        cv.Optional(CONF_ICON, default=ICON_EMPTY): number.icon,
        cv.Optional(CONF_STEP, default=0.01): cv.float_,
        cv.Optional(CONF_UNIT_OF_MEASUREMENT, default=UNIT_AMPERE): cv.string_strict,
        cv.Optional(CONF_MODE, default="BOX"): cv.enum(number.NUMBER_MODES, upper=True),
        cv.Optional(
            CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG
        ): cv.entity_category,
    }
).extend(cv.COMPONENT_SCHEMA)

CONFIG_SCHEMA = EVSE_WALLBOX_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_OUTPUT_CURRENT_SETTING): EVSE_NUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=0.0): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=80.0): cv.float_,
            }
        ),
        cv.Optional(CONF_OUTPUT_CURRENT_DEFAULT): EVSE_NUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=6.0): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=80.0): cv.float_,
            }
        ),
        cv.Optional(CONF_MIN_CHARGING_CURRENT): EVSE_NUMBER_SCHEMA.extend(
            {
                cv.Optional(CONF_MIN_VALUE, default=0.0): cv.float_,
                cv.Optional(CONF_MAX_VALUE, default=13.0): cv.float_,
            }
        ),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_EVSE_WALLBOX_ID])
    for key, address in NUMBERS.items():
        if key in config:
            conf = config[key]
            var = cg.new_Pvariable(conf[CONF_ID])
            await cg.register_component(var, conf)
            await number.register_number(
                var,
                conf,
                min_value=conf[CONF_MIN_VALUE],
                max_value=conf[CONF_MAX_VALUE],
                step=conf[CONF_STEP],
            )
            cg.add(getattr(hub, f"set_{key}_number")(var))
            cg.add(var.set_parent(hub))
            cg.add(var.set_holding_register(address))
