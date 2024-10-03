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

#
![Screenshot](https://github.com/antor44/Acquisition4microcontrollers/blob/main/edge_impulse_create_impulse.jpg)
## Building an AI Application for Arduino and Nano 33 BLE Sense with Edge Impulse

This article will guide you through developing an AI application using Arduino Uno/Mega/Nano and Nano 33 BLE Sense, leveraging the Edge Impulse online platform. We will focus on training a Machine Learning model, and deploying it back to the microcontroller for real-time inference. **The example scenario of an intelligent air conditioner control system serves primarily as a proof of concept, illustrating the process and potential of deploying AI on microcontrollers. This foundation can then be adapted for other practical applications and projects.**

### Introduction
Edge Impulse is a powerful online platform for developing and deploying machine learning models on edge devices, including microcontrollers like Arduino Nano 33 BLE Sense, although ArduinoUNO/mega/Nano are not supported. It simplifies the process of collecting sensor data, training models, and deploying them to resource-constrained devices. This allows developers to build intelligent applications for the Internet of Things (IoT) without extensive machine learning expertise.

### Hardware and Software Requirements
* Arduino Nano 33 BLE Sense
* Computer with internet access
* Edge Impulse account (free tier available)
* Arduino IDE

### Project Overview
This article will focus on building a basic AI application using the Arduino Nano 33 BLE Sense and Edge Impulse. The example scenario will be an intelligent air conditioner control system.  However, the principles and steps outlined can be easily adapted for other applications and sensors. 

### Data Collection and Preprocessing
* **Sensor Data Acquisition:** Connect the necessary sensors to your Arduino Nano 33 BLE Sense. Utilize the Arduino IDE to collect data from these sensors. 
* **Data Formatting:** Format the collected data into a suitable format for Edge Impulse.
* **Dataset Upload:** Create a new project in Edge Impulse and upload the formatted sensor data.

### Model Training and Selection
* **Impulse Creation:** Define the structure of your AI pipeline within Edge Impulse's "Create Impulse" section. This involves selecting appropriate data preprocessing blocks and choosing a suitable learning algorithm.
* **Algorithm Selection:** Edge Impulse offers various algorithms, including Neural Networks, Convolutional Neural Networks (CNNs), and classical Machine Learning algorithms. For numerical data, like our temperature control scenario, Regression or Classification algorithms are suitable.
* **Model Training:** Train the selected model using the uploaded dataset. Edge Impulse provides options for customizing network architecture, hyperparameters, and training epochs.
* **Model Optimization (Optional):** Utilize the EON Tuner to automatically find optimal model configurations by testing various hyperparameters and settings.
* **Model Performance Evaluation:** Evaluate the trained model's performance using Edge Impulse's testing tools. Analyze metrics like accuracy, precision, and recall to assess its effectiveness.

### Model Deployment and Application
Edge Impulse offers several ways to test and deploy your trained model:

* **Live Testing:** Test your model in real-time using a web browser, mobile device, or directly on the target hardware. Data from connected sensors can be streamed to Edge Impulse for live inference and visualization.
* **Dataset Testing:** Evaluate the model's performance using the dedicated "Test" dataset within Edge Impulse. This provides detailed metrics and graphs to assess accuracy and identify potential issues.
* **Deployment Packages:** Generate optimized deployment packages tailored for your specific hardware platform, such as Arduino boards.
* **Code Export:** Download the model code for integration into your own projects. Edge Impulse supports various programming languages like C++ for Arduino and Python for platforms like Raspberry Pi.

For microcontroller deployment, the Arduino IDE is used to upload the generated code, incorporating the trained model. For instance, in a Keyword Spotting application, the Arduino Nano 33 BLE Sense can be programmed to illuminate an LED based on detected voice commands. The LED could turn green when the activation word is recognized and remain red otherwise. Additionally, actions like controlling a relay to switch electrical appliances on or off can be implemented based on the model's output.

**Applying the Model to the Air Conditioner Control System**

While the intelligent air conditioner control system is a simplified example, it showcases how the model can be deployed for practical use.  The hardware setup used for data collection can be adapted for the final application. In this case, the infrared receiver used to gather user temperature preferences can be replaced with an infrared LED. This LED would send on/off commands to the air conditioner or heater based on the AI's predictions.

However, this method has limitations. Determining if the infrared LED successfully transmitted the command to the appliance requires additional sensors or relying on classic programming logic.  For instance, the code could monitor the temperature trend and retry sending the command if the temperature doesn't adjust as expected.

A more reliable approach is to use a relay to control the appliance's power supply directly. A relay suitable for 220V AC and compatible with the 3.3V output of the Arduino Nano 33 BLE Sense would be required. While this method ensures control over the appliance, it's a more "forceful" approach and might not be appropriate for all applications.

**Alternative Control Methods:**

Smart home devices offer alternative control solutions. Devices like Xiaomi's remote button can be controlled via microcontrollers, minicomputers, or even over the internet if they utilize compatible protocols. Integrating such devices can be achieved using platforms like Home Assistant, which supports a wide range of smart home ecosystems.

### Practical Considerations and Limitations
While promising on paper, the performance of AI-based systems on resource-constrained devices should be carefully evaluated. Theoretical results may not always translate directly to real-world scenarios due to factors like sensor noise, environmental variations, and the limitations of simplified models.

In the case of our air conditioner control system, the accuracy and generalizability of the model might be limited by factors not captured in the training data. While Edge Impulse indicated efficient resource utilization on the Arduino Nano 33 BLE Sense, even with more complex neural network architectures, deploying similar algorithms on less powerful boards like the Arduino UNO presents further challenges.

Classical Machine Learning algorithms, such as regression models, might be more suitable for resource-constrained devices like the Arduino UNO. These algorithms generally require less processing power and memory compared to neural networks. While examples of running basic neural networks on Arduino UNO exist, the limited 2 KB RAM and 1 KB ROM necessitate careful model design and potentially external memory solutions like microSD cards.

### Conclusion
Developing AI applications for microcontrollers like Arduino is becoming increasingly accessible with platforms like Edge Impulse. By following the steps outlined in this article, you can leverage the power of machine learning to build intelligent and responsive IoT applications without extensive machine learning expertise. Remember to experiment with different algorithms, model configurations, and sensor data to optimize your application's performance and achieve the desired functionality. When working with resource-constrained devices, carefully consider the trade-offs between model complexity, accuracy, and hardware limitations to select the most suitable approach for your application. 

