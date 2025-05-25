import esphome.codegen as cg
from esphome.components import button
import esphome.config_validation as cv
from esphome.const import CONF_ID, ICON_EMPTY

from .. import CONF_EVSE_WALLBOX_ID, EVSE_WALLBOX_COMPONENT_SCHEMA, evse_wallbox_ns

DEPENDENCIES = ["evse_wallbox"]

CODEOWNERS = ["@syssi"]

CONF_TURN_OFF_CHARGING = "turn_off_charging"
CONF_START_SELF_TEST = "start_self_test"
CONF_CLEAR_RCD_ERROR = "clear_rcd_error"

BUTTONS = {
    CONF_TURN_OFF_CHARGING: [1004, 1],
    CONF_START_SELF_TEST: [1004, 2],
    CONF_CLEAR_RCD_ERROR: [1004, 4],
}

EvseButton = evse_wallbox_ns.class_("EvseButton", button.Button, cg.Component)

CONFIG_SCHEMA = EVSE_WALLBOX_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_TURN_OFF_CHARGING): button.button_schema(
            EvseButton, icon=ICON_EMPTY
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_START_SELF_TEST): button.button_schema(
            EvseButton, icon=ICON_EMPTY
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_CLEAR_RCD_ERROR): button.button_schema(
            EvseButton, icon=ICON_EMPTY
        ).extend(cv.COMPONENT_SCHEMA),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_EVSE_WALLBOX_ID])
    for key, address in BUTTONS.items():
        if key in config:
            conf = config[key]
            var = cg.new_Pvariable(conf[CONF_ID])
            await cg.register_component(var, conf)
            await button.register_button(var, conf)
            cg.add(var.set_parent(hub))
            cg.add(var.set_holding_register(address[0]))
            cg.add(var.set_payload(address[1]))
