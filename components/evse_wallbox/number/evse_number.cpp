#include "evse_number.h"
#include "esphome/core/log.h"

namespace esphome {
namespace evse_wallbox {

static const char *const TAG = "evse_wallbox.number";

void EvseNumber::dump_config() { LOG_NUMBER("", "EvseWallbox Number", this); }
void EvseNumber::control(float value) {
  this->parent_->write_register(this->holding_register_, (uint16_t) (value * (1.0f / this->traits.get_step())));
}

}  // namespace evse_wallbox
}  // namespace esphome
