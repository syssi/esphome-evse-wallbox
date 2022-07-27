#pragma once

#include "../evse_wallbox.h"
#include "esphome/core/component.h"
#include "esphome/components/number/number.h"

namespace esphome {
namespace evse_wallbox {

class EvseWallbox;

class EvseNumber : public number::Number, public Component {
 public:
  void set_parent(EvseWallbox *parent) { this->parent_ = parent; };
  void set_holding_register(uint16_t holding_register) { this->holding_register_ = holding_register; };
  void dump_config() override;

 protected:
  void control(float value) override;

  EvseWallbox *parent_;
  uint16_t holding_register_;
};

}  // namespace evse_wallbox
}  // namespace esphome
