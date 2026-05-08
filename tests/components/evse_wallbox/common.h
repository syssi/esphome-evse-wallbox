#pragma once
#include <cstdint>
#include <vector>
#include "esphome/components/evse_wallbox/evse_wallbox.h"

namespace esphome::evse_wallbox::testing {

class TestableEvseWallbox : public EvseWallbox {
 public:
  using EvseWallbox::on_status_data_;
  using EvseWallbox::on_config_data_;
};

}  // namespace esphome::evse_wallbox::testing
