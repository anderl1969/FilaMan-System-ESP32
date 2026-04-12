# Piezo Buzzer - Acoustic Signals

## Description
Optional support for a passive piezo buzzer. Enables acoustic signaling of successfully completed operations or failure in case of errors.

## Setup / Installation
### Hardware
The wiring of the hardware is basically identical to the original FilaMan scale.
**Additionally, a passive piezo buzzer is connected to PIN18.**

<sub>(The 10k pull-up resistor on pin 16 (RX2) shown in the circuit diagram is optional.
It increases reliability when detecting a missing HX711. However, it should also work without the pull-up resistor.)</sub>

![Circuit diagram with buzzer](../img/Schaltplan%20with%20Buzzer.png)

| Component    | ESP32 Pin |
| ----         | ----      |
| HX711 DOUT<br><sub>10k Pull-up (opt.)</sub>  | 16        |
| HX711 SCK    | 17        |
| PIEZO BUZZER | 18        |
| OLED SDA     | 21        |
| OLED SCL     | 22        |
| PN532 IRQ    | 32        |
| PN532 RESET  | 33        |
| PN532 SDA    | 21        |
| PN532 SCL    | 22        |
| TTP223 I/O   | 25        |

#### HX711
- Connect `VCC` to 5V

#### Piezo Buzzer
- Connect `+` to PIN18 and `-` to GND

#### PN532
- **!! Make sure the DIP switches of the PN532 are set to I2C**
- Connect `VCC` to 5V

#### OLED
- Connect `VCC` to 3.3V

#### TTP223
- **!! Use 3V3 to power the touch sensor**
- Connect `VCC` to 3.3V

#### 10k Resistor (optional)
- Connect the resistor to PIN 16 (in addition to the HX711's DOUT) and 5V

### Software
Follow the instructions in the [main documentation](../README.md#step-by-step-installation).
