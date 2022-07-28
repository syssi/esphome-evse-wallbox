# esphome-evse-wallbox

![GitHub actions](https://github.com/syssi/esphome-evse-wallbox/actions/workflows/ci.yaml/badge.svg)
![GitHub stars](https://img.shields.io/github/stars/syssi/esphome-evse-wallbox)
![GitHub forks](https://img.shields.io/github/forks/syssi/esphome-evse-wallbox)
![GitHub watchers](https://img.shields.io/github/watchers/syssi/esphome-evse-wallbox)
[!["Buy Me A Coffee"](https://img.shields.io/badge/buy%20me%20a%20coffee-donate-yellow.svg)](https://www.buymeacoffee.com/syssi)

ESPHome component to monitor and control a EVSE wallbox via RS485 (Modbus).

## Supported devices

TBD.

## Schematics

TBD.

## Installation

You can install this component with [ESPHome external components feature](https://esphome.io/components/external_components.html) like this:
```yaml
external_components:
  - source: github://syssi/esphome-evse-wallbox@main
```

or just use the `esp32-example.yaml` as proof of concept:

```bash
# Install esphome
pip3 install esphome

# Clone this external component
git clone https://github.com/syssi/esphome-evse-wallbox.git
cd esphome-evse-wallbox

# Create a secrets.yaml containing some setup specific secrets
cat > secrets.yaml <<EOF
wifi_ssid: MY_WIFI_SSID
wifi_password: MY_WIFI_PASSWORD
EOF

# Validate the configuration, create a binary, upload it, and start logs
# If you use a esp8266 run the esp8266-examle.yaml
esphome run esp32-example.yaml
```

## Example response all sensors enabled

```
TBD.
```

## Known issues

None.

## Debugging

If this component doesn't work out of the box for your device please update your configuration to enable the debug output of the UART component and increase the log level to the see outgoing and incoming serial traffic:

```
logger:
  level: DEBUG

uart:
  id: uart0
  baud_rate: 9600
  tx_pin: GPIO4
  rx_pin: GPIO5
  debug:
    direction: BOTH
```

## References

* https://github.com/kortas87/evse-scripts/
* https://github.com/CurtRod/SimpleEVSE-WiFi/
* http://evracing.cz/evse/evse-wallbox/
