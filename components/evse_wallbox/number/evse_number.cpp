#include "evse_number.h"
#include "esphome/core/log.h"

// Fallback for ESPHome < 2026.10.0
#ifndef ESPHOME_LOG_TAG
#define ESPHOME_LOG_TAG(name, tag) static const char *const name = tag
#endif

namespace esphome::evse_wallbox {

ESPHOME_LOG_TAG(TAG, "evse_wallbox.number");

void EvseNumber::dump_config() { LOG_NUMBER("", "EvseWallbox Number", this); }
void EvseNumber::control(float value) {
  this->parent_->write_register(this->holding_register_, (uint16_t) (value * (1.0f / this->traits.get_step())));
}

}  // namespace esphome::evse_wallbox
