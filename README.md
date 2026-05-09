## PCB Earrings

### Overview

This project implements a wearable LED earring system built around an STM32 microcontroller, designed to drive LED lighting patterns on a custom PCB while maintaining constraints on size, power consumption, and wearability.

The hardware design focuses on balancing compact form factor, low-power operation, and visual appeal.

---

### System Architecture

The system consists of three primary subsystems:

- **Microcontroller (STM32)**  
  Handles LED sequencing, timing control, and GPIO-based output driving.

- **LED Array**  
  Radially arranged LEDs designed to create a myriad of different lighting effects.

- **Power System**  
  Low-voltage regulated supply designed for safe wearable operation and stable LED driving.

---

### PCB Design Constraints

The PCB was designed under the following constraints:

- Compact form factor suitable for wearable earrings  
- Radial symmetry for consistent visual aesthetics  
- Minimal trace length and optimized routing for small footprints  
- GPIO current limitations respected for direct LED driving  
- 3.0V logic compatibility with STM32 outputs  

These constraints directly influenced both component selection and board layout decisions.

---

### LED Current Design

LED current was calculated using Ohm’s law:

$$
I_{LED} = \frac{V_{CC} - V_f}{R}
$$

Where:
- $V_{CC}$ is the supply voltage (3.0V)
- $V_f$ is the LED forward voltage (~1.8–2.3V depending on component)
- $R$ is the current-limiting resistor

Initial (V1) and revised (V2) calculations were performed to refine resistor values and achieve the desired luminous intensities of the LEDs.

All supporting calculations are documented in `docs/calculations/`.

---

### Power Considerations

Power design priorities:

- Drive LEDs directly from GPIO within safe current limits  
- Limit peak current draw to extend battery life
- Conservative resistor sizing based on worst-case forward voltage  

These considerations ensure stable operation under battery-powered conditions.

---

### Bill of Materials (BOM)

A full Bill of Materials is included in `hardware/media/exports/`.
