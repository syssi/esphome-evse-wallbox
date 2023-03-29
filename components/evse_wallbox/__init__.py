import esphome.codegen as cg
from esphome.components import modbus
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@syssi"]

DEPENDENCIES = ["modbus"]
AUTO_LOAD = ["binary_sensor", "number", "sensor", "switch", "text_sensor"]
MULTI_CONF = True

CONF_EVSE_WALLBOX_ID = "evse_wallbox_id"

evse_wallbox_ns = cg.esphome_ns.namespace("evse_wallbox")
EvseWallbox = evse_wallbox_ns.class_(
    "EvseWallbox", cg.PollingComponent, modbus.ModbusDevice
)

EVSE_WALLBOX_COMPONENT_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_EVSE_WALLBOX_ID): cv.use_id(EvseWallbox),
    }
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(EvseWallbox),
        }
    )
    .extend(cv.polling_component_schema("5s"))
    .extend(modbus.modbus_device_schema(0x01))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await modbus.register_modbus_device(var, config)
