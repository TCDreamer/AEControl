# AEControl
Controller for exhaust valve actuator. Handles initializing and cycling through and indicating 3 valve states using PWM. Specifically for OEM actuators found in vehicles like Ford GT350, Dodge, Audi, etc.

This actuator must be installed to function correctly. If the actuator attempts to calibrate and does not encounter resistance, it goes into a paused state and will need to have power toggled to restart. To test on a bench, you can insert the actuator into a vice and put a rod in the spring mount and manually hold it from rotating.
