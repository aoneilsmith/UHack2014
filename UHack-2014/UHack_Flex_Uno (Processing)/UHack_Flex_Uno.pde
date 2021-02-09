/*
  Andrew O'Neil-Smith
  UHack 2014
  Zensah Arduino Flex Hack
*/

import org.firmata.*;
import cc.arduino.*;
import processing.serial.*;

Serial myPort;
float greenness;
float seglength = 100;
float x, y;
float angle1 = 0.0;
float angle2 = 0.0;
float segLength = 100;

void setup()
{
 size(640,360); //window size
 
 //setting the port to read COM 3. change based on what COM port your arduino comes in on.
 //COM port is called something different if you are using Mac OS
 myPort= new Serial(this, "COM3", 9600);
 
 myPort.bufferUntil('\n'); //doesnt read data until it starts streaming from arduino
 
 //arm setup
 strokeWeight(30);
 stroke(255, 160);
 x = width * 0.3;
 y = height * 0.5;
}

void draw()
{
  
  background(0,greenness,0); //draws background with RGB colors
  
  angle1 = (mouseX/float(width) - 0.5) * -PI;  //angle 1 rotation is mapped to mouse movement on X axis
  //angle2 = (mouseY/float(height) - 0.5) * PI; // this will get drawn later
  
  //println(mouseY); //debug
  
  pushMatrix();
  segment(x, y, angle1); 
  segment(segLength,0,angle2);
  popMatrix();
}

//every time there is a serial event, this gets called
void serialEvent(Serial myPort)
{
  greenness = float(myPort.readStringUntil(' ')); //the Green RGB value is mapped to the first column of data coming from arduino
  angle2 = float(myPort.readStringUntil('\n'))/255 * -PI; //the arm angle is mapped to the second column of data coming from the arduino
  //redness = float(myPort2.readStringUntil('\n')); //
  segment(x,y,angle2); //draws the forearm segment
  //println(angle2); //debug
  //println(redness);
}

//draw segment funciton
void segment(float x, float y, float a) {
  translate(x, y);
  rotate(a);
  line(0, 0, segLength, 0);
}


