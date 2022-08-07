#pragma once

#include "../evse_wallbox.h"
#include "esphome/core/component.h"
#include "esphome/components/button/button.h"

namespace esphome {
namespace evse_wallbox {

class EvseWallbox;

class EvseButton : public button::Button, public Component {
 public:
  void set_parent(EvseWallbox *parent) { this->parent_ = parent; };
  void set_holding_register(uint16_t holding_register) { this->holding_register_ = holding_register; };
  void set_payload(uint16_t payload) { this->payload_ = payload; };
  void dump_config() override;
  void loop() override {}
  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  void press_action() override;
  EvseWallbox *parent_;
  uint16_t holding_register_;
  uint16_t payload_;
};

}  // namespace evse_wallbox
}  // namespace esphome
