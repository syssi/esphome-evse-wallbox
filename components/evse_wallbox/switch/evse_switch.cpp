#include "evse_switch.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace evse_wallbox {

static const char *const TAG = "evse_wallbox.switch";

void EvseSwitch::dump_config() { LOG_SWITCH("", "EvseWallbox Switch", this); }
void EvseSwitch::write_state(bool state) { this->parent_->write_register(this->holding_register_, (uint16_t) state); }

}  // namespace evse_wallbox
}  // namespace esphome
