# Data acquisition for Arduino UNO and Nano BLE 33 Sense


These codes are used to acquire data for a machine learning application that controls the temperature. The acquisition mode change is manually controlled with an infrared remote control using a *new universal protocol.


*Although the new protocol for infrared remotes doesn't have much to do with the main objective of this code, which is data acquisition for a Machine Learning model to control the temperature of a room or space, Arduino Nano BLE 33 Sense code includes all the low-level instructions to analyze frames of infrared remotes compatible with the NEC protocol, based on an example of IRMP by Frank Meyer: https://github.com/ukw100/IRMP/ . I've removed unnecessary parts and modified it to support any remote control, whether to use it as a remote control to transmit power on/off changes to the Arduino circuit or to discard incorrect codes received from other remote controls. To accomplish this, I have also programmed a new, arbitrary infrared protocol or code that can discard false positives or key presses received from other remote controls. The code is adapted to the codes of my IR remote controls (TV and AC), which makes it very simple as the circuit receives any remote control press to switch between on and off, canceling key codes that match the remote controls of my other devices. To identify these codes for false positives of keys from other remote controls different from mine, you can add an instruction such as 'Serial.println(key_s)' at the beginning of the translateIR() function.

![Screenshot](https://github.com/antor44/Acquisition4microcontrollers/blob/main/NEC_protocol.jpg)

For the part of the code sent by the infrared remotes, only an intermediate part of the frame is read with the intention of making it more compatible or universal, as some remotes I have send shorter frames or use different protocols than NEC. It may be that they are so different that this programming code reads their frames by chance. In practice, key presses from remotes of a large number of brands or other protocols may be recognized, as long as they are of the most common 38 KHz frequency model, specifically called Pulse Width Modulation (PWM), although then to send the zero or the one it will not simply be to send or not pulses at 38 KHz. But I have chosen an intermediate part of the IR frames without knowing exactly which one, so this may be the reason why I ended up with too many coincidences with the remote control of my TV, false positives, coincidental keys that need to be discarded if they are pressed with the "switch...case" instruction of the translateIR() function, to avoid changing the state of the data collection of the code with false positives, for example when changing TV channels. I do not know if the "invented" codes do not capture the most differentiating bits of the infrared frame sent by different types of remotes from other devices. I have not studied the NEC protocol or any other, but rather have been programming it based on trial and error, and I do not have time to go further. If there are other parts of the frames that are more differentiable, they can be tested by modifying the maximum and minimum values of the range [the two conditional instructions with the "> than" (greater than)] in the variable ISREdgeCounter inside the ISR measureTimingISR() function and perhaps also, if the lower value (39 by default) is modified, the value 40 in the line "key = key + pow(2,(ISREdgeCounter-40))". In other words, one can try modifying the three instructions that contain the ISREdgeCounter variable, which the IRMP library programmer uses to count the pulses of the infrared chip/receiver that the microcontroller receives through one of the digital input ports. This part of the programming code would only be valid in others to receive key codes in certain programming codes, such as one to use controllers of other devices without knowing them, no matter the protocol as long as their frames are detected by chance, or to discard false positives from other controllers as in this specific case.

This part of the programming code and the invented IR codes would not be valid for transmitting via infrared, since the electronic or electrical device always requires complete valid frames of a specific IR protocol with the exact key codes used by the manufacturer at that time. For this, libraries have tables of supported protocols, and codes are extracted by copying them from a working remote with a separate programming code. While there are online databases with codes for all existing remotes, which are used by some applications such as those included in some mobile phones with infrared ports, so that users only have to choose the brand and model of the remote control they want to emulate. I do not know why it is not used in programming codes for microcontrollers; it may be due to patent issues, since it is absurd to have to use a functional remote control in a specific program of the microcontroller in order to copy its operation in another application of the user's microcontroller, when for example the user may want to copy a broken remote or one that has disappeared from the market. This code does NOT solve this specific problem.

 
## Data acquisition for Arduino Nano BLE 33 Sense:
![Screenshot](https://github.com/antor44/microcontrollers/blob/main/Receiver_Sense/Arduino_sense_receiver.jpg)
#
![Screenshot](https://github.com/antor44/microcontrollers/blob/main/Receiver_Sense/Arduino_nano_sense_placa.jpg)

Components list:

1 Arduino Nano 33 BLE Sense

1 Breadboard

1 Remote control

1 IR Receiver Module

1 Passive Buzzer

Male-Male and Male-Female color-coded prototyping wires (22 AWG)

USB-A Male to Micro USB Male cable

#
## Data acquisition for Arduino UNO:
![Screenshot](https://github.com/antor44/microcontrollers/blob/main/Receiver_Module/Arduino_Acquisition.jpg)
#
![Screenshot](https://github.com/antor44/microcontrollers/blob/main/Receiver_Module/acquisition.jpg)

Components list:

1 Arduino UNO/Mega

1 Breadboard or a shield with mini-Breadboard

1 Remote control

1 IR Receiver Module

1 DHT11 Temperature and Humidity Sensor Module

1 Active Buzzer

1 Red and 1 Green LED

1 Photoresistor

1 10 Kohm or 1 Kohm resistor

2 220 ohm resistors

Male-Male and Male-Female color-coded prototyping wires (22 AWG)

USB-A Male to USB-B Male cable
