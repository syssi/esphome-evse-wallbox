import esphome.codegen as cg
from esphome.components import switch
import esphome.config_validation as cv
from esphome.const import (
    CONF_ENTITY_CATEGORY,
    CONF_ICON,
    CONF_ID,
    CONF_OUTPUT,
    ENTITY_CATEGORY_CONFIG,
)

from .. import CONF_EVSE_WALLBOX_ID, EVSE_WALLBOX_COMPONENT_SCHEMA, evse_wallbox_ns

DEPENDENCIES = ["evse_wallbox"]

CODEOWNERS = ["@syssi"]

# CONF_OUTPUT from const

ICON_OUTPUT = "mdi:power"
ICON_KEY_LOCK = "mdi:play-box-lock-outline"

SWITCHES = {
    CONF_OUTPUT: 0x0009,
}

EvseSwitch = evse_wallbox_ns.class_("EvseSwitch", switch.Switch, cg.Component)

CONFIG_SCHEMA = EVSE_WALLBOX_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_OUTPUT): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(EvseSwitch),
                cv.Optional(CONF_ICON, default=ICON_OUTPUT): switch.icon,
                cv.Optional(
                    CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG
                ): cv.entity_category,
            }
        ).extend(cv.COMPONENT_SCHEMA),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_EVSE_WALLBOX_ID])
    for key, address in SWITCHES.items():
        if key in config:
            conf = config[key]
            var = cg.new_Pvariable(conf[CONF_ID])
            await cg.register_component(var, conf)
            await switch.register_switch(var, conf)
            cg.add(getattr(hub, f"set_{key}_switch")(var))
            cg.add(var.set_parent(hub))
            cg.add(var.set_holding_register(address))
