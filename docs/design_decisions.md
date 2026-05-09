## SMD Footprint Size

Revised design (v2) standardized the footprint of all surface mount devices to be 0603 [1608 Metric]. This change was implemented to increase the symmetricality of the board when worn to maximize visual appeal.

## LED Current Calculation Evolution

Initial design (v1) only considered the current passing through the red LED, and assigned the same resistor value to both the red and blue LEDs. Initial powering of the PCB revealed that the blue LEDs were much brighter than the red, and both colors of LEDs were too bright. After reviewing the LED datasheets, the resistor values were revised (v2) to reflect a more optimal operation point.