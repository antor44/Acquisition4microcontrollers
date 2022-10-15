//Author: Antonio R.
//27/8/2021


/*
Learning Temperatures for Arduino 33 BLE Sense - Collecting Sensor Data for an Arduino Machine Learning System.

Copyright (C) 2021 Antonio R.

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses>.
*/


/* Partially Based on code from the Elegoo Kit: www.elegoo.com
   and IRMP examples of Frank Meyer :https://github.com/ukw100/IRMP/
   and Arduino Nano 33 BLE Sense default sensors libraries */


#include <Arduino.h>

#define IR_INPUT_PIN    3

/*
 * Helper macro for getting a macro definition as string
 */
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#include "pitches.h"

int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6 };
int duration = 500;  // 500 miliseconds


int x;


#define RED 22     
#define BLUE 24     
#define GREEN 23


#include <Arduino_HTS221.h>
#include <Arduino_LPS22HB.h>
#include <Arduino_APDS9960.h>



void measureTimingISR(void);


uint8_t ISREdgeCounter = 0;
volatile uint32_t LastMicros;

volatile uint32_t key_s = 0;
volatile uint32_t key = 0;
int Fail = 0;



void translateIR() // takes action based on arbitrary IR code received

// arbitrary IR codes, this are for Elegoo remote control 

{
  Fail=0;
  switch(key_s)

  {
  case 557570: break;
  case 532994: break;
  case 524802: break;
//  case 565762: break;
  case 696832: break;
  case 655872: break;
//  case 524290: break;
//  case 557090: break;
//  case 163848: break;
//  case 532514: break;
  case 163880: break;
//  case 32778: break;
//  case 40970: break;
  case 172072: break;
  case 8746: break;
//  case 172040: break;
  case 41002: break;
  case 139816: break;
  case 664064: break;
  case 664096: break;
  case 139784: break;

  default:
    key_s=0;
    Fail=1;

  }// End Case
  
  delay(500); // Do not get immediate repeat

} //END translateIR



/*----( SETUP: RUNS ONCE )----*/

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);

    attachInterrupt(digitalPinToInterrupt(IR_INPUT_PIN), measureTimingISR, CHANGE);
    
    delay(5000);
  
  /* 
   * Initialises the colour sensor, and starts the 
   * periodic reading of the sensor using a Mbed OS thread. 
   * The data is placed in a circular buffer and can be read whenever.
   */
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor.");
  }
  /* 
   * Initialises the temperature sensor, and starts the 
   * periodic reading of the sensor using a Mbed OS thread. 
   * The data is placed in a circular buffer and can be read whenever.
   */
  if (!HTS.begin()) {
    Serial.println("Failed to initialize temperature/humidity sensor!");
    while (1);
  }
   /* 
    * Initialises the pressure sensor, and starts the 
    * periodic reading of the sensor using a Mbed OS thread. 
    * The data is placed in a circular buffer and can be read whenever.
    */
  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }
  
  Serial.println("....................Initialized....................");

 // intitialize the digital LEDs Pin as an output
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, LOW); // turn the RED LED on
  digitalWrite(GREEN, HIGH);

}
/*--(end setup )---*/




/*----( LOOP: RUNS CONSTANTLY )----*/

void loop()
{
  float temperature = HTS.readTemperature();
  float humidity    = HTS.readHumidity();
  float pressure = BARO.readPressure();
  static unsigned long sequences;
  static unsigned long X0_time;
  static unsigned long X1_time;
  static unsigned long X0_millis;
  static unsigned long X1_millis;
  int r, g, b, a;

  X0_time=millis()-X0_millis;
  X1_time=millis()-X1_millis;
  
  translateIR(); 
  
    if (key_s>0 && Fail==0 && x==1){
      sequences=sequences+1;
      x=0;
      key_s=0;
      X0_millis=millis();
      digitalWrite(RED, LOW); // turn the RED LED on (HIGH is the voltage level)
      digitalWrite(GREEN, HIGH);
      
      //output an frequency
      for (int thisNote = 0; thisNote < 8; thisNote++) {
        // pin8 output the voice, every scale is 0.5 sencond
        tone(8, NOTE_A4, 80);
     
        delay(120);
      }


     }else if (key_s>0 && Fail==0){ 
      sequences=sequences+1;
      x=1;
      key_s=0;
      X1_millis=millis();
      digitalWrite(GREEN, LOW); // turn the GREEN LED on (HIGH is the voltage level)
      digitalWrite(RED, HIGH);
      
      //output an frequency
      for (int thisNote = 0; thisNote < 8; thisNote++) {
        // pin8 output the voice, every scale is 0.5 sencond
        tone(8, melody[thisNote], duration);
     
        delay(120);
      }

     }



  // check if a color reading is available
  while (! APDS.colorAvailable()) {
    delay(5);
  }
  
  // read the color
  APDS.readColor(r, g, b, a);
            

    Serial.print(sequences);
    Serial.print( ", " );        
    Serial.print(temperature, 4);
    Serial.print( ", " );
    Serial.print(humidity, 4);
    Serial.print( ", " );
    Serial.print(pressure, 4);
    Serial.print( ", " );   
    Serial.print(a);
    Serial.print( ", " );    
    if (x==0){
        Serial.print(X0_time);
      }else{
        Serial.print(X1_time);
    }
    Serial.print( ", " );
    Serial.println(x);
    
   delay(1000);
}

/* --(end main loop )-- */





/*
 * The interrupt handler.
 * Just add to the appropriate timing structure.
 */
void measureTimingISR()

{
    uint32_t tMicros = micros();
    uint32_t tMicrosDelta = tMicros - LastMicros;
    LastMicros = tMicros;


    /*
     * read level and give feedback
     */
    uint8_t tInputLevel = digitalRead(IR_INPUT_PIN);
    digitalWrite(LED_BUILTIN, !tInputLevel);

    if (tMicrosDelta > 10000)
    {
        // gap > 10 ms detected, reset counter to first detected edge and initialize timing structures
        ISREdgeCounter = 1;
        key=0;
    }
    else
    {
        ISREdgeCounter++;
    }

    /*
     * Skip header mark and space and first bit mark and space
     */
    if (ISREdgeCounter > 39)
    {
        if (tInputLevel != LOW)
        {
            // Mark ended
            if (ISREdgeCounter > 59){
               key_s=key;
               key=0;
               ISREdgeCounter = 1;                             
            }
        }
        else
        {
            // Space ended

            if (tMicrosDelta > 1000)
            {
                // long space - logical 1
                key = key + pow(2,(ISREdgeCounter-40));
            }
            else
            {
                // short space - logical 0
            }
        }
    }
}
