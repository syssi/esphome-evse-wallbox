#include "evse_button.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome::evse_wallbox {

static const char *const TAG = "evse_wallbox.button";

void EvseButton::dump_config() { LOG_BUTTON("", "EvseWallbox Button", this); }
void EvseButton::press_action() { this->parent_->write_register(this->holding_register_, this->payload_); }

}  // namespace esphome::evse_wallbox
