/*
  Andrew O'Neil-Smith
  UHack 2014
  Zensah Arduino Flex Hack
*/

// HARDWARE:
// Make the following connections between the Arduino and the flex sensor
// Note that the flex sensor pins are interchangeable

// Sensor pin - GND
// Sensor pin - Analog In 0, with 10K resistor to +5V

// INSTRUCTIONS:
// Upload this sketch to your Arduino, then activate the Serial Monitor (control + shift + m)
// (set the Serial Monitor to 9600 baud)

#include "pitches.h";

void setup()
{
  // initialize serial communications
  Serial.begin(9600);
  //Serial1.begin(9600); 
}

void loop()
{
  int sensor, degrees; //right sensor
  int sensorL, degreesL; //left sensor
  
  // read the voltage from the voltage divider (sensor plus resistor)
  sensor = analogRead(0); //right sensor is on A0
  sensorL = analogRead(1); //left sensor is on A1
  
  // convert the voltage reading to inches
  // the first two numbers are the sensor values for straight (724) and bent (853)
  // the second two numbers are the degree readings we'll map that to (0 to 90 degrees)
  degrees = map(sensor, 724, 853, 0, 90); //right sensor
  degreesL = map(sensorL, 730, 822, 0, 90); //left sensor
  
  /* your sensor's values will vary
     to improve the accuracy, run the program, note your sensor's analog values when it's straight and bent
     insert those values into the above function.
   */
  
  //the following will be sent to Processing to be read for RGB and Arm Angle
  int val = map(sensor, 724, 853, 0, 255); // mapping the sensor (10 bit 0-1023) to RGB values (8 bit 0-255)
  
   //not allowing Right sensor values outside of 0-255 be sent to Processing
    if(val<=0)
      val = 0;
    else if (val>=255)
      val = 255;
      //Serial.println(val);  //debug    

  //not allowing Left sensor values outside of 0-255 be sent to Processing
  int valL = map(sensorL, 724, 853, 0, 255); //10 to 8 bit
    if(valL<=0)
      valL = 0;
    else if (valL>=255)
      valL = 255;
  //Serial.println(valL); //debug
  
  //Prints to the serial monitor Left and Right 0-255 values
  //will be read by Processing for RBG and Arm Angle
  Serial.print(valL);
  Serial.print(" ");
  Serial.println(val);
  
  //Right = melody
  if(degrees > 0 && degrees < 20){
    tone(8,NOTE_A4,120); //plays an A on pin 8 for 120ms
      delay(120);                     
      }
 else if(degrees >= 20 && degrees < 40){
    tone(8,NOTE_CS5,120);
      delay(120);
    }
  else if(degrees >= 40 && degrees < 50){
    tone(8,NOTE_E5,120);
    delay(120);                     
    }
  else if( degrees >= 50){
    tone(8,NOTE_A5, 120);
    delay(120);                     
    }
     
  //Left = bass
 if(degreesL > 0 && degreesL < 20){
    tone(8,NOTE_A2,200);
      delay(240);                     
      }
 else if(degreesL >= 20 && degreesL < 40){
    tone(8,NOTE_CS3,200);
      delay(240);
    }
  else if(degreesL >= 40 && degreesL < 50){
    tone(8,NOTE_E3,200);
    delay(240);                     
    }
  else if( degreesL >= 50){
    tone(8,NOTE_A3, 200);
   delay(240); 
  }
    
    
  /*
  // debug output if you want to view 
  Serial.print("analog input: ");
  Serial.print(sensor,DEC);
  Serial.print("   degrees: ");
  Serial.println(degrees,DEC);

  Serial1.print("analog input: ");
  Serial1.print(sensorL,DEC);
  Serial1.print("   degrees: ");
  Serial1.println(degreesL,DEC);  
  
  */
  
  delay(100);   // pause before taking the next reading to make datat easier to read
                    
}
