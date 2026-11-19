#include "evse_button.h"

namespace esphome::evse_wallbox {

void EvseButton::press_action() { this->parent_->write_register(this->holding_register_, this->payload_); }

}  // namespace esphome::evse_wallbox
