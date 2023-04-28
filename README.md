# Data acquisition for Arduino UNO and Nano BLE 33 Sense


Codes are used to acquire data for a machine learning application that controls the temperature. The acquisition mode change is manually controlled with an infrared remote control using a *new universal protocol.


*Although the new protocol for infrared remotes doesn't have much to do with the main objective of this code, which is data acquisition for a Machine Learning model to control the temperature of a room or space, Arduino Nano BLE 33 Sense code includes all the low-level instructions to analyze frames of infrared remotes compatible with the NEC protocol. I've removed unnecessary parts and modified it to support any remote control, whether to use it as a remote control to transmit power on/off changes to the Arduino circuit or to discard incorrect codes received from other remote controls. To accomplish this, I have also programmed a new, arbitrary infrared protocol or code that can discard false positives or key presses received from other remote controls. The code is adapted to the codes of my remote controls, which makes it very simple as the circuit receives any remote control press to switch between on and off, canceling key codes that match the remote controls of my other devices. To identify these codes for false positives of keys from other remote controls different from mine, you can add an instruction such as 'Serial.println(key_s)' at the beginning of the translateIR() function.

*For the part of the code sent by the infrared controllers, only an intermediate part of the frame is read with the intention of making it more compatible or universal, since some controllers send shorter frames or use protocols different from NEC. These protocols may be so different that this programming code reads their frames by chance. In practice, key presses from remote controls of a large number of brands or other protocols may be recognized, as long as they use the most common frequency model of 38 KHz, which is specifically called Pulse Width Modulation (PWM), or perhaps is Pulse Position Modulation (PPM). However, I have chosen an intermediate part of the IR frames without knowing exactly which one, so this may be why too many keys on my TV remote coincided in the end - false positives - which need to be discarded if they are pressed with the "switch...case" instruction in the translateIR() function to prevent changing the state of the data collection code with false positives, for example, when switching TV channels. I am not aware if the "invented" codes do not capture the most differentiating bits of the infrared frame sent by the different types of controllers of other devices. I have not studied the NEC protocol or any other; instead, I have been programming it through trial and error, and I do not have time to go any further. If there are other parts of the frames that are more differentiable, one can try modifying the maximum and minimum values of the range (the two conditional instructions with the ">" sign) in the ISREdgeCounter variable inside the ISR measureTimingISR() function and perhaps also modifying the lower value (39 by default), the value of 40 in the line "key = key + pow(2,(ISREdgeCounter-40))". In other words, one can try modifying the three instructions that contain the ISREdgeCounter variable, which the original library programmer uses to count the pulses of the infrared chip/receiver that the microcontroller receives through one of the digital input ports. This part of the programming code would only be valid in others to receive key codes in certain programming codes, such as one to use controllers of other devices without knowing them, no matter the protocol as long as their frames are detected by chance, or to discard false positives from other controllers as in this specific case.

*This part of the programming code or the invented IR codes would not be valid for transmitting by infrared, as electronic or household devices always require complete valid frames of a specific IR protocol with the exact key codes used by the manufacturer. For this, the libraries have tables of supported protocols, and the codes are extracted by copying them from a functioning remote control with a separate programming code. Although there are online databases with the codes of all existing remote controls, which are used by some applications such as those included in some mobile phones with infrared ports, so that the user only has to choose the brand and model of the remote control they want to emulate, I am not sure why they are not used in microcontroller programming codes. It may be due to patent issues, as it is absurd to have to use a functional remote control in a specific microcontroller program to copy its operation in another application of the user's microcontroller, when, for example, the user may want to copy a broken or discontinued remote control. This code does not solve this specific problem.

## Data acquisition for Arduino Nano BLE 33 Sense:
![Screenshot](https://github.com/antor44/microcontrollers/blob/main/Receiver_Sense/Arduino_sense_receiver.jpg)
#
![Screenshot](https://github.com/antor44/microcontrollers/blob/main/Receiver_Sense/Arduino_nano_sense_placa.jpg)
#
## Data acquisition for Arduino UNO:
![Screenshot](https://github.com/antor44/microcontrollers/blob/main/Receiver_Module/Arduino_Acquisition.jpg)
#
![Screenshot](https://github.com/antor44/microcontrollers/blob/main/Receiver_Module/acquisition.jpg)
