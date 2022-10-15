//Author: Antonio R.
//17/8/2021


/*
Learning Temperatures - Collecting Sensor Data for an Arduino Machine Learning System.

Copyright (C) 2021 Antonio R.

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses>.
*/


/* Partially Based on code from the Elegoo Kit: www.elegoo.com */

#include "IRremote.h"
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11
#define GREEN 5
#define RED 6

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );

int receiver = 11; // Pin of IR receiver to Digital Pin 11
int buzzer = 12;//the pin of the active buzzer
int lightPin = 0;
int x;
int Fail;

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // instance of 'decode_results'




/*-----( Function )-----*/


void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{

  switch(results.value)

  {
  case 0xFFA25D: break;
  case 0xFFE21D: break;
  case 0xFF629D: break;
  case 0xFF22DD: break;
  case 0xFF02FD: break;
  case 0xFFC23D: break;
  case 0xFFE01F: break;
  case 0xFFA857: break;
  case 0xFF906F: break;
  case 0xFF9867: break;
  case 0xFFB04F: break;
  case 0xFF6897: break;
  case 0xFF30CF: break;
  case 0xFF18E7: break;
  case 0xFF7A85: break;
  case 0xFF10EF: break;
  case 0xFF38C7: break;
  case 0xFF5AA5: break;
  case 0xFF42BD: break;
  case 0xFF4AB5: break;
  case 0xFF52AD: break;
  case 0xFFFFFFFF: Fail=1;break;  

  default: 
    Fail=1;

  }// End Case
  
  delay(500); // Do not get immediate repeat

} //END translateIR


/*
 * Poll for a measurement temp/humi, keeping the state alive.
 * Returns true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}




void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  Serial.println("....................Initialized....................");
  irrecv.enableIRIn(); // Start the receiver
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, LOW);

  pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output

}/*--(end setup )---*/





void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  float temperature;
  float humidity;
  unsigned char i;
  int reading  = analogRead(lightPin);
  static unsigned long sequences;
  static unsigned long X0_time;
  static unsigned long X1_time;
  static unsigned long X0_millis;
  static unsigned long X1_millis;

  X0_time=millis()-X0_millis;
  X1_time=millis()-X1_millis;
  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity ) == true )
  {
    Serial.print(sequences);
    Serial.print( ", " );        
    Serial.print( temperature, 1 );
    Serial.print( ", " );
    Serial.print( humidity, 1 );
    Serial.print( ", " );
    Serial.print(reading);
    Serial.print( ", " );    
    if (x==0){
        Serial.print(X0_time);
      }else{
        Serial.print(X1_time);
    }
    Serial.print( ", " );
    Serial.println(x);
  }
  
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR();
    if (x==1 && Fail==0){
      sequences=sequences+1;
      x=0;
      X0_millis=millis();
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, LOW);
      //output an frequency
      for(i=0;i<180;i++)
        {
          digitalWrite(buzzer,HIGH);
          delay(1);//wait for 1ms
          digitalWrite(buzzer,LOW);
          delay(1);//wait for 1ms
        }
    }else if (Fail==0){
      sequences=sequences+1;
      x=1;
      X1_millis=millis();
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, HIGH);
      //output another frequency
      for(i=0;i<200;i++)
        {
          digitalWrite(buzzer,HIGH);
          delay(2);//wait for 4ms
          digitalWrite(buzzer,LOW);
          delay(2);//wait for 4ms
        }     
    }
    irrecv.resume(); // receive the next value
    Fail=0;
  }  
}/* --(end main loop )-- */
