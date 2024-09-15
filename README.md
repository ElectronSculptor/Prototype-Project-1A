
# Variable Distance Digital Code Lock

This project involves designing a contactless, proximity-based digital code lock system that uses capacitive sensors to detect the distance of a user’s hand from the sensors. The lock system supports complex, multi-position authentication codes that enhance security while maintaining hygiene by eliminating physical contact.


## Date

- September 15, 2024

## Project Objectives

The goal of the project was to address the limitations of traditional digital code locks, such as susceptibility to code theft through button wear and the potential transmission of bacteria. This new system offers:
- **Improved Security**: The system allows for more complex combinations by detecting the proximity of the user's hand to sensors, making it harder to steal access codes.
- **Hygiene**: A contactless interface reduces the risk of transmitting diseases.
- **Intuitiveness**: The system is easy to use with a simple, natural interface.

## Key Components

### 1. Capacitive Sensors
The system uses capacitive sensors to detect proximity and distinguish between two positions: near and far.

### 2. Signal Conditioning Circuit
The conditioner processes signals from the sensors using:
- Constant current charging for accurate capacitance measurement.
- An oscillator with a hysteresis comparator to detect the proximity threshold.

### 3. STM32 Microcontroller
An STM32 microcontroller handles the acquisition and processing of capacitance signals, converting them into digital data and determining combinations of sensor inputs.

### 4. PCB Design
The project’s electronics were designed using KiCAD to create a printed circuit board (PCB) integrating the sensors, microcontroller, and related components.

## System Architecture

1. **Capacitive Sensors**: Detect hand proximity in two positions (near/far).
2. **Conditioner**: A signal conditioner charges the capacitors and measures the charging time to deduce proximity.
3. **STM32 Microcontroller**: Handles the signal acquisition and processes input data for the multi-position code lock system.

## Testing and Results

- Testing was performed using the designed conditioners and the STM32.
- The system successfully detected two positions (near and far) and responded by lighting up LEDs in different colors to confirm the correct hand position.
- A servo motor was used as the final actuator to simulate opening a door.

## Challenges and Solutions

### PCB Design Issues
- The initial PCB design could not be fully tested due to a shortage of components.
- A revised routing method using pre-made conditioners was adopted to address manufacturing issues.

### Signal Acquisition
- Various issues were encountered with signal acquisition due to UART configuration, which was solved by using alternative UART ports.

## Conclusion

Although some objectives were not fully achieved due to technical difficulties, the project demonstrates significant progress in creating a secure, intuitive, and contactless digital code lock. Further improvements can be made in:
- Optimizing the conditioner for better detection range.
- Enhancing the user interface for ease of use.
- Expanding the application to other access control systems.

## Appendices

1. **Capacitor Code for PartQuest Simulation**
2. **STM32 Microcontroller Code**
3. **Demonstrations and Additional Calculations**

