# esphome-evse-wallbox

![GitHub actions](https://github.com/syssi/esphome-evse-wallbox/actions/workflows/ci.yaml/badge.svg)
![GitHub stars](https://img.shields.io/github/stars/syssi/esphome-evse-wallbox)
![GitHub forks](https://img.shields.io/github/forks/syssi/esphome-evse-wallbox)
![GitHub watchers](https://img.shields.io/github/watchers/syssi/esphome-evse-wallbox)
[!["Buy Me A Coffee"](https://img.shields.io/badge/buy%20me%20a%20coffee-donate-yellow.svg)](https://www.buymeacoffee.com/syssi)

ESPHome component to monitor and control a EVSE wallbox via RS485 (Modbus).

## Supported devices

* EVSE Wallbox
* EVSE DIN

## Schematics

### EVSE DIN

```
┌──────── 5V
│┌───────────── GND
││┌──────────── RX (`tx_pin: GPIO4`)
│││┌─────────── TX (`rx_pin: GPIO5`)
││││┌──── GND
│││││┌─── 5V
││││││┌── MCLR
ooooooo
ooooooo
││││││└── 5V-12V
│││││└─── GND
││││└──── DRVEN
│││└───── TEST
││└────── REL
│└─────── RC2
└──────── +12V
```

See also [EVSE DIN schematics photo.](images/schematics-evse-din.png "EVSE DIN schematics")

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
[I][evse_wallbox:067]: Config frame received
[I][evse_wallbox:083]:   Output current default: 32 A
[D][number:012]: 'evse-wallbox output current default': Sending state 32.000000
[I][evse_wallbox:087]:   Modbus address: 1
[I][evse_wallbox:089]:   Minimum charging current: 5 A
[D][number:012]: 'evse-wallbox minimum charging current': Sending state 5.000000
[I][evse_wallbox:093]:   Analog input config: 1
[I][evse_wallbox:095]:   Save current on button press: 0
[D][sensor:124]: 'evse-wallbox config config bits': Sending state 521.00000  with 0 decimals of accuracy
[D][switch:037]: 'evse-wallbox config current change by button': Sending state ON
[D][switch:037]: 'evse-wallbox config stop charging on button press': Sending state OFF
[D][switch:037]: 'evse-wallbox config pilot ready state led always on': Sending state OFF
[D][switch:037]: 'evse-wallbox config charging of vehicle status d': Sending state ON
[D][switch:037]: 'evse-wallbox config rcd feedback on mclr pin': Sending state OFF
[D][switch:037]: 'evse-wallbox config auto clear rcd error': Sending state OFF
[D][switch:037]: 'evse-wallbox config an internal pullup': Sending state OFF
[D][switch:037]: 'evse-wallbox config disable evse after charge': Sending state OFF
[D][switch:037]: 'evse-wallbox config disable evse': Sending state OFF
[D][switch:037]: 'evse-wallbox config bootloader mode': Sending state OFF
[I][evse_wallbox:114]:   PP detection limit: 0 A
[I][evse_wallbox:117]:   Bootloader version: 3
[I][evse_wallbox:119]:   Amps value 1: 6 A
[I][evse_wallbox:121]:   Amps value 2: 10 A
[I][evse_wallbox:123]:   Amps value 3: 16 A
[I][evse_wallbox:125]:   Amps value 4: 25 A
[I][evse_wallbox:127]:   Amps value 5: 32 A
[I][evse_wallbox:129]:   Amps value 6: 48 A
[I][evse_wallbox:131]:   Amps value 7: 63 A
[I][evse_wallbox:133]:   Amps value 8: 80 A
[I][evse_wallbox:141]: Status frame received
[D][sensor:124]: 'evse-wallbox output current setting': Sending state 32.00000 A with 0 decimals of accuracy
[D][number:012]: 'evse-wallbox output current setting': Sending state 32.000000
[D][sensor:124]: 'evse-wallbox output current': Sending state 0.00000 A with 0 decimals of accuracy
[D][sensor:124]: 'evse-wallbox vehicle status code': Sending state 1.00000  with 0 decimals of accuracy
[D][text_sensor:067]: 'evse-wallbox vehicle status': Sending state 'Ready'
[D][sensor:124]: 'evse-wallbox cable limit detected': Sending state 5.00000 A with 0 decimals of accuracy
[D][sensor:124]: 'evse-wallbox last command bitmask': Sending state 0.00000  with 0 decimals of accuracy
[I][evse_wallbox:180]:   Command bitmask: 0
[I][evse_wallbox:181]:     Turn off charging now: NO
[I][evse_wallbox:182]:     Run RCD test procedure: NO
[I][evse_wallbox:183]:     Clear RCD error: NO
[D][sensor:124]: 'evse-wallbox firmware version': Sending state 18.00000  with 0 decimals of accuracy
[D][sensor:124]: 'evse-wallbox operation mode code': Sending state 1.00000  with 0 decimals of accuracy
[D][text_sensor:067]: 'evse-wallbox operation mode': Sending state '12V'
[D][sensor:124]: 'evse-wallbox error bitmask': Sending state 0.00000  with 0 decimals of accuracy
[D][text_sensor:067]: 'evse-wallbox errors': Sending state ''
[D][binary_sensor:036]: 'evse-wallbox relay': Sending state OFF
[D][binary_sensor:036]: 'evse-wallbox diode check failed': Sending state OFF
[D][binary_sensor:036]: 'evse-wallbox ventilation failed': Sending state OFF
[D][binary_sensor:036]: 'evse-wallbox waiting for pilot release': Sending state OFF
[D][binary_sensor:036]: 'evse-wallbox rcd test in progress': Sending state OFF
[D][binary_sensor:036]: 'evse-wallbox rcd check error': Sending state OFF
[D][sensor:124]: 'evse-wallbox error timeout countdown': Sending state 0.00000  with 0 decimals of accuracy
[D][sensor:124]: 'evse-wallbox self-test timeout countdown': Sending state 0.00000  with 0 decimals of accuracy
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
