# Smart Water Tank Monitoring System

An Arduino-based water-level monitoring prototype using an HC-SR04 ultrasonic sensor, four LED indicators, and a buzzer. It reports the measured distance and water-level status in the Serial Monitor. At the configured full-level threshold, all LEDs turn on, the buzzer sounds, and the monitor displays **“ACTION: TURN WATER OFF NOW!”**

## Features
- Measures distance to the water surface with an HC-SR04.
- Uses LEDs to indicate low, medium, high, and full states.
- Sounds a buzzer at the full-level threshold.
- Prints status messages and an overflow warning in the Serial Monitor.
- Reports invalid sensor readings instead of treating them as a full tank.

## Components
- Arduino UNO
- HC-SR04 ultrasonic sensor
- 4 LEDs
- 4 × 220 Ω resistors (one per LED)
- Buzzer
- Jumper wires
- Breadboard (optional)

## Connections

| Component | Arduino connection |
|---|---|
| HC-SR04 VCC | 5V |
| HC-SR04 GND | GND |
| HC-SR04 TRIG | D9 |
| HC-SR04 ECHO | D10 |
| Low LED anode | D2 through 220 Ω resistor |
| Medium LED anode | D3 through 220 Ω resistor |
| High LED anode | D4 through 220 Ω resistor |
| Full LED anode | D5 through 220 Ω resistor |
| All LED cathodes | GND |
| Buzzer positive | D6 |
| Buzzer negative | GND |

Use one resistor in series with each LED. All grounds must be common.

## Example thresholds
- More than 30 cm: low
- More than 20 cm and up to 30 cm: medium
- More than 10 cm and up to 20 cm: high
- 10 cm or less: full warning and buzzer

These are demonstration thresholds only. Calibrate them for your tank height and sensor mounting position.

## Run in Wokwi
1. Create an Arduino UNO project.
2. Add an HC-SR04, four LEDs, four 220 Ω resistors, and a buzzer.
3. Connect the components according to the table above.
4. Copy `sketch.ino` into the Wokwi code editor.
5. Start the simulation, adjust the sensor's simulated distance, and open the Serial Monitor.

Wokwi: https://wokwi.com/

## Limitations
- This prototype alerts the user but does **not** automatically switch off a pump or valve. Automatic shutoff requires a suitably rated relay/driver and a correctly designed control circuit.
- An ultrasonic sensor measures distance to a surface; it does not directly measure water level.
- This is a learning prototype, not a safety-certified overflow-prevention system.
