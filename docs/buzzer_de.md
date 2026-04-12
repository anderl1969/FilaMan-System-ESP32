# Piezo Summer - Akustische Signale

## Beschreibung
Optionale Unterstützung eines passiven Piezo Summers. Ermöglicht die akustische Signalisierung von erfolgreich abgeschlossenen Vorgängen oder im Fehlerfall das Scheitern.

## Aufbau / Installation
### Hardware
Die Verkabelung der Hardware ist grundsätzliche identisch zur originalen FilaMan-Waage.
**Zusätzlich wird ein passiver Piezo-Summer an PIN18 angeschlossen.**

<sub>(Der auf dem Schaltbild gezeigte 10k Pull-up-Widerstand an Pin 16 (RX2) ist optional.
Er erhöht die Zuverlässigkeit beim Erkennen eines fehlenden HX711. Ohne Pull-up-Widerstand sollte es aber ebenfalls funktionieren.)</sub>

![Schaltplan mit Pull-Up](../img/Schaltplan%20with%20Buzzer.png)

| Komponente   | ESP32 Pin |
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
- Verbinde `VCC` mit 5V

#### Piezo Summer
- Verbinde `+` mit PIN18 und `-` mit GND

#### PN532
- **!! Stelle sicher, dass die DIP-Schalter des PN532 auf I2C gestellt sind**
- Verbinde `VCC` mit 5V

#### OLED
- Verbinde `VCC` mit 3,3V

#### TTP223
- **!! Verwende 3V3 zur Versorgung des Touch-Sensors**
- Verbinde `VCC` mit 3,3V

#### 10k Widerstand (optional)
- Verbinde den Widerstand mit PIN 16 (zusätzlich zum DOUT des HX711) und 5V

### Software
Folge den Anweisungen in der [Hauptdokumentation](../README.de.md#schritt-für-schritt-installation).
