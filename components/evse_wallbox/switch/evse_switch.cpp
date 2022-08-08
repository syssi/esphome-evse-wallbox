#include "evse_switch.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace evse_wallbox {

static const char *const TAG = "evse_wallbox.switch";

void EvseSwitch::dump_config() { LOG_SWITCH("", "EvseWallbox Switch", this); }
void EvseSwitch::write_state(bool state) {
  if (this->holding_register_ == 2005) {
    this->parent_->write_config_bits(this->holding_register_, state);
  }
  return;
}

ESP_LOGE(TAG, "The holding register (%d) isn't supported by the switch entity yet.", this->holding_register_);
}  // namespace evse_wallbox
}  // namespace esphome
