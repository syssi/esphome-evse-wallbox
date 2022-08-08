#pragma once

#include "../evse_wallbox.h"
#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"

namespace esphome {
namespace evse_wallbox {

class EvseWallbox;

class EvseSwitch : public switch_::Switch, public Component {
 public:
  void set_parent(EvseWallbox *parent) { this->parent_ = parent; };
  void set_holding_register(uint16_t holding_register) { this->holding_register_ = holding_register; };
  void set_bit_field(uint16_t bit_field) { this->bit_field_ = bit_field; };
  void dump_config() override;
  void loop() override {}
  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  void write_state(bool state) override;
  EvseWallbox *parent_;
  uint16_t holding_register_;
  uint16_t bit_field_;
};

}  // namespace evse_wallbox
}  // namespace esphome
