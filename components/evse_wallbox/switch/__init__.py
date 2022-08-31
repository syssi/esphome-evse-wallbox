import esphome.codegen as cg
from esphome.components import switch
import esphome.config_validation as cv
from esphome.const import (
    CONF_ENTITY_CATEGORY,
    CONF_ICON,
    CONF_ID,
    ENTITY_CATEGORY_CONFIG,
    ICON_EMPTY,
)

from .. import CONF_EVSE_WALLBOX_ID, EVSE_WALLBOX_COMPONENT_SCHEMA, evse_wallbox_ns

DEPENDENCIES = ["evse_wallbox"]

CODEOWNERS = ["@syssi"]

CONF_CURRENT_CHANGE_BY_BUTTON = "current_change_by_button"
CONF_STOP_CHARGING_ON_BUTTON_PRESS = "stop_charging_on_button_press"
CONF_PILOT_READY_STATE_LED_ALWAYS_ON = "pilot_ready_state_led_always_on"
CONF_CHARGING_OF_VEHICLE_STATUS_D = "charging_of_vehicle_status_d"
CONF_RCD_FEEDBACK_ON_MCLR_PIN = "rcd_feedback_on_mclr_pin"
CONF_AUTO_CLEAR_RCD_ERROR = "auto_clear_rcd_error"
CONF_AN_INTERNAL_PULLUP = "an_internal_pullup"
CONF_DISABLE_EVSE_AFTER_CHARGE = "disable_evse_after_charge"
CONF_DISABLE_EVSE = "disable_evse"
CONF_BOOTLOADER_MODE = "bootloader_mode"

SWITCHES = {
    CONF_CURRENT_CHANGE_BY_BUTTON: [2005, 1],
    CONF_STOP_CHARGING_ON_BUTTON_PRESS: [2005, 2],
    CONF_PILOT_READY_STATE_LED_ALWAYS_ON: [2005, 4],
    CONF_CHARGING_OF_VEHICLE_STATUS_D: [2005, 8],
    CONF_RCD_FEEDBACK_ON_MCLR_PIN: [2005, 16],
    CONF_AUTO_CLEAR_RCD_ERROR: [2005, 32],
    CONF_AN_INTERNAL_PULLUP: [2005, 64],
    CONF_DISABLE_EVSE_AFTER_CHARGE: [2005, 8192],
    CONF_DISABLE_EVSE: [2005, 16384],
    CONF_BOOTLOADER_MODE: [2005, 32768],
}

EvseSwitch = evse_wallbox_ns.class_("EvseSwitch", switch.Switch, cg.Component)

CONFIG_SCHEMA = EVSE_WALLBOX_COMPONENT_SCHEMA.extend(
    {
        cv.Optional(CONF_CURRENT_CHANGE_BY_BUTTON): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(EvseSwitch),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
                cv.Optional(
                    CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG
                ): cv.entity_category,
            }
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_STOP_CHARGING_ON_BUTTON_PRESS): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(EvseSwitch),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
                cv.Optional(
                    CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG
                ): cv.entity_category,
            }
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_PILOT_READY_STATE_LED_ALWAYS_ON): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(EvseSwitch),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
                cv.Optional(
                    CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG
                ): cv.entity_category,
            }
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_CHARGING_OF_VEHICLE_STATUS_D): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(EvseSwitch),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
                cv.Optional(
                    CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG
                ): cv.entity_category,
            }
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_RCD_FEEDBACK_ON_MCLR_PIN): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(EvseSwitch),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
                cv.Optional(
                    CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG
                ): cv.entity_category,
            }
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_AUTO_CLEAR_RCD_ERROR): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(EvseSwitch),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
                cv.Optional(
                    CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG
                ): cv.entity_category,
            }
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_AN_INTERNAL_PULLUP): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(EvseSwitch),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
                cv.Optional(
                    CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG
                ): cv.entity_category,
            }
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_DISABLE_EVSE_AFTER_CHARGE): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(EvseSwitch),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
                cv.Optional(
                    CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG
                ): cv.entity_category,
            }
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_DISABLE_EVSE): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(EvseSwitch),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
                cv.Optional(
                    CONF_ENTITY_CATEGORY, default=ENTITY_CATEGORY_CONFIG
                ): cv.entity_category,
            }
        ).extend(cv.COMPONENT_SCHEMA),
        cv.Optional(CONF_BOOTLOADER_MODE): switch.SWITCH_SCHEMA.extend(
            {
                cv.GenerateID(): cv.declare_id(EvseSwitch),
                cv.Optional(CONF_ICON, default=ICON_EMPTY): cv.icon,
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
            cg.add(var.set_holding_register(address[0]))
            cg.add(var.set_bit_field(address[1]))
