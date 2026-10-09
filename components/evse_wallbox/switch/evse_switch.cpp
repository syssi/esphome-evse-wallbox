#include "evse_switch.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

// Fallback for ESPHome < 2026.10.0
#ifndef ESPHOME_LOG_TAG
#define ESPHOME_LOG_TAG(name, tag) static const char *const name = tag
#endif

namespace esphome::evse_wallbox {

ESPHOME_LOG_TAG(TAG, "evse_wallbox.switch");

void EvseSwitch::dump_config() { LOG_SWITCH("", "EvseWallbox Switch", this); }
void EvseSwitch::write_state(bool state) {
  if (this->holding_register_ == 2005) {
    this->parent_->write_config_bits(this->bit_field_, state);
    return;
  }

  ESP_LOGE(TAG, "The holding register (%d) isn't supported by the switch entity yet.", this->holding_register_);
}

}  // namespace esphome::evse_wallbox
