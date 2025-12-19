// November 28, 2024

/* 3DChameleon Mk4.1 Firmware

Copyright 2024 William J. Steele

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated 
documentation files (the “Software”), to deal in the Software without restriction, including without limitation 
the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, 
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions 
of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED 
TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF 
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.

Single Button Press Commands (count pulses of selector)

#1 - 1
#2 - 2
#3 - 3
#4 - 4
#5 - Home and Load
#6 - Unload Last and Home
#7 - Home
#8 - Next Filament
#9 - Random Filament
 
*/

//#include <SSD1306Ascii.h> //i2C OLED
//#include <SSD1306AsciiWire.h> //i2C OLED
//#include <SparkFunSX1509.h> // sparkfun i/o expansion board - used for additional filament sensors as well as communications with secondary boards
#include <Wire.h>
#include <SPI.h>
#include <Servo.h>
#include <PololuLedStrip.h>


// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<A4> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 4
rgb_color colors[LED_COUNT];


// defines pins numbers - 3D Chameleon Board
#define extEnable 0
#define extStep 1
#define extDir 2

#define selEnable A0
#define selStep A1
#define selDir A2

#define trigger A3
#define homestop A5


const int counterclockwise = HIGH;
const int clockwise = !counterclockwise;

const int stepsPerRev = 200;  //200*16 = 1rev = 5.75mm
const int microSteps = 16;

const int speedDelaySelector = 45; //delay for selector 60
const int fastSpeed = 36;  //delay for extruder - 24us=feedrate 2245, 30us = feedrate 1796, 36us=feedrate 1496, 45us=feedrate 1197

//const int defaultBackoff = 20; //30;


Servo filamentCutter;  // create servo object to control a servo
int cutterPos = 0;    // variable to store the servo position
bool reverseServo = true;

int currentExtruder = -1;
//int nextExtruder = 0;
int lastExtruder = -1;
//int tempExtruder = -1;

int seenCommand = 0;
int prevCommand = 0;


long triggerTime = 300;
long pulseTime = (triggerTime / 2);

long pos=12800;


byte value;

long idleCount = 0;

bool T0Loaded = false;
bool T1Loaded = false;
bool T2Loaded = false;
bool T3Loaded = false;

bool homed=false;


void setup()
{

  // wait for it to start up
  delay(50);
    
  
  for(uint16_t x = 0; x < LED_COUNT; x++){
  colors[x] = rgb_color(0, 255, 0);
  ledStrip.write(colors, LED_COUNT);
  delay(200);
  }
  delay(500);
  for(uint16_t x = 0; x < LED_COUNT; x++){
  colors[x] = rgb_color(0, 0, 0);
  ledStrip.write(colors, LED_COUNT);
  delay(200);
  }
   
  seenCommand = 0;

  // Sets the two pins as Outputs
  pinMode(extEnable, OUTPUT);
  pinMode(extStep, OUTPUT);
  pinMode(extDir, OUTPUT);

  pinMode(selEnable, OUTPUT);
  pinMode(selStep, OUTPUT);
  pinMode(selDir, OUTPUT);

  // set up the button
  pinMode(trigger, INPUT_PULLUP);  // selector
  pinMode(homestop, INPUT_PULLUP);  // home endstop
  
  // lock the selector by energizing it
  digitalWrite(selEnable, HIGH);

  // make sure filament isn't blocked by gillotine
  connectGillotine();
  cutFilament();
  disconnectGillotine();
  
  prevCommand = 0;
  homeSelector();

}

int lastLoop = 0;

void loop()
{
  static uint32_t lastTime = 0;

  
  seenCommand = 0;
  idleCount++;
if(homed==false){
    colors[0] = rgb_color(255, 0, 0);
    colors[1] = rgb_color(255, 0, 0);
    colors[2] = rgb_color(255, 0, 0);
    colors[3] = rgb_color(255, 0, 0);
    ledStrip.write(colors, LED_COUNT);
}

  // process button press
  if (digitalRead(trigger) == 0)
  {
    idleCount = 0;
//    logoActive = false;
    unsigned long nextPulse;
    unsigned long pulseCount = 0;
    unsigned long commandCount = 0;

    // keep counting (and pulsing) until button is released
    while (digitalRead(trigger) == 0)
    {
      if(pulseCount<pulseTime)
      {
        pulseCount++;
        displayCommand(pulseCount);
//        if(pulseCount>1) vibrateMotor();
       
        ledStrip.write(colors, LED_COUNT);
       
      }
      delay(400);  // each pulse is 400+ milliseconds apart 
    }
    processCommand(pulseCount); // ok... execute whatever command was caught (by pulse count)
    pulseCount = 0;
  }

  // each loop adds 50ms delay, so that gets added AFTER the command is processed before the next one can start
  delay(50);
}



// display command for each button pulse
void displayCommand(long commandCount)
{

  switch(commandCount)
  {
  case 2:
    ///////////////////////////////////////////////    Switch to #1
    colors[0] = rgb_color(0, 255, 0);
    colors[1] = rgb_color(0, 0, 0);
    colors[2] = rgb_color(0, 0, 0);
    colors[3] = rgb_color(0, 0, 0);
 
    break;
  case 3:
   ///////////////////////////////////////////////     Switch to #2
    colors[0] = rgb_color(0, 0, 0);
    colors[1] = rgb_color(0, 255, 0);
    colors[2] = rgb_color(0, 0, 0);
    colors[3] = rgb_color(0, 0, 0);
    break;
  case 4:
    ///////////////////////////////////////////////    Switch to #3
    colors[0] = rgb_color(0, 0, 0);
    colors[1] = rgb_color(0, 0, 0);
    colors[2] = rgb_color(0, 255, 0);
    colors[3] = rgb_color(0, 0, 0);
    break;
  case 5:
    //////////////////////////////////////////////    Switch to #4
    colors[0] = rgb_color(0, 0, 0);
    colors[1] = rgb_color(0, 0, 0);
    colors[2] = rgb_color(0, 0, 0);
    colors[3] = rgb_color(0, 255, 0);
    break;
  case 6:
   ///////////////////////////////////////////////     Home
    colors[0] = rgb_color(0, 255, 0);
    colors[1] = rgb_color(0, 255, 0);
    colors[2] = rgb_color(0, 255, 0);
    colors[3] = rgb_color(0, 255, 0);
    break;
 
  case 7:
    ///////////////////////////////////////////////    UNLOAD and park
    colors[0] = rgb_color(255, 0, 0);
    colors[1] = rgb_color(255, 0, 0);
    colors[2] = rgb_color(255, 0, 0);
    colors[3] = rgb_color(255, 0, 0);
    break;

  default:
    ///////////////////////////////////////////////     No Command
    colors[0] = rgb_color(0, 0, 0);
    colors[1] = rgb_color(0, 0, 0);
    colors[2] = rgb_color(0, 0, 0);
    colors[3] = rgb_color(0, 0, 0);
    break;
  }
}

// execute the pulse count command
void processCommand(long commandCount)
{

  // select case for commands
  switch (commandCount)
  {
  case 2: // unload current, switch to #0, load
   ///////////////////////////////////////////////    Selected #1
    currentExtruder = 0;
    processMoves();
   ///////////////////////////////////////////////    Idle #1
     colors[0] = rgb_color(0, 255, 0);
        colors[1] = rgb_color(0, 0, 0);
        colors[2] = rgb_color(0, 0, 0);
        colors[3] = rgb_color(0, 0, 0);
     ledStrip.write(colors, LED_COUNT);
    break;

  case 3: // unload current, switch to #1, load
   ///////////////////////////////////////////////    Selected #2
    currentExtruder = 1;
    processMoves();
   ///////////////////////////////////////////////    Idle #2
    colors[0] = rgb_color(0, 0, 0);
        colors[1] = rgb_color(0, 255, 0);
        colors[2] = rgb_color(0, 0, 0);
        colors[3] = rgb_color(0, 0, 0);
            ledStrip.write(colors, LED_COUNT);
    break;

  case 4: // unload current, switch to #3, load
   ///////////////////////////////////////////////    Selected #3
    currentExtruder = 2;
    processMoves();
   ///////////////////////////////////////////////    Idle #3
    colors[0] = rgb_color(0, 0, 0);
        colors[1] = rgb_color(0, 0, 0);
        colors[2] = rgb_color(0, 255, 0);
        colors[3] = rgb_color(0, 0, 0);
            ledStrip.write(colors, LED_COUNT);
    break;

  case 5: // unload current, switch to #4, load
   ///////////////////////////////////////////////    Selected #4
    currentExtruder = 3;
    processMoves();
   ///////////////////////////////////////////////    Idle #4
colors[0] = rgb_color(0, 0, 0);
        colors[1] = rgb_color(0, 0, 0);
        colors[2] = rgb_color(0, 0, 0);
        colors[3] = rgb_color(0, 255, 0);
            ledStrip.write(colors, LED_COUNT);
    break;

  case 6: //home and reload #1
   ///////////////////////////////////////////////    Homing
    homed=false;
    homeSelector();

    break;
    
  case 7: // unload current and park
   ///////////////////////////////////////////////    Cutting
    connectGillotine();
    cutFilament();
    switch(lastExtruder)
    {
      case 0:
   ///////////////////////////////////////////////    Press to unload #1
        colors[0] = rgb_color(255, 0, 0);
        colors[1] = rgb_color(0, 0, 0);
        colors[2] = rgb_color(0, 0, 0);
        colors[3] = rgb_color(0, 0, 0);
    ledStrip.write(colors, LED_COUNT);
   rotateSelector(7467);
        break;
      case 1:
   ///////////////////////////////////////////////    Press to unload #2
    colors[0] = rgb_color(0, 0, 0);
        colors[1] = rgb_color(255, 0, 0);
        colors[2] = rgb_color(0, 0, 0);
        colors[3] = rgb_color(0, 0, 0);
    ledStrip.write(colors, LED_COUNT);
    rotateSelector(4500);
        break;
      case 2:
   ///////////////////////////////////////////////    Press to unload #3
      colors[0] = rgb_color(0, 0, 0);
        colors[1] = rgb_color(0, 0, 0);
        colors[2] = rgb_color(255, 0, 0);
        colors[3] = rgb_color(0, 0, 0);
    ledStrip.write(colors, LED_COUNT);
   rotateSelector(2250);
        break;
      case 3:
   ///////////////////////////////////////////////    Press to unload #4
      colors[0] = rgb_color(0, 0, 0);
        colors[1] = rgb_color(0, 0, 0);
        colors[2] = rgb_color(0, 0, 0);
        colors[3] = rgb_color(255, 0, 0);
    ledStrip.write(colors, LED_COUNT);
   rotateSelector(20);
        break;
    } 
      rotateExtruder(counterclockwise);
      //homed=false;
      //homeSelector();
    rotateSelector(9600);//parking position
    
    disconnectGillotine();
   ///////////////////////////////////////////////    Idle
    break;

  default:
   ///////////////////////////////////////////////    Clear (no command)
    delay(200);
homed=false;
      homeSelector();
   ///////////////////////////////////////////////    Idle
    break;
  }
}



// real work is here
void processMoves()
{

  // make sure we have a real extruder selected
  if(lastExtruder>-1)
  {

    // if so, we need to cut the filament
   ///////////////////////////////////////////////    Cutting
    connectGillotine();
    cutFilament();

    // ok... then wait for the 2nd button press to unload it
    switch(lastExtruder)
    {
      case 0:
   ///////////////////////////////////////////////    Press to unload #1 - switching
        
        colors[0] = rgb_color(255, 0, 0);
        colors[1] = rgb_color(0, 0, 0);
        colors[2] = rgb_color(0, 0, 0);
        colors[3] = rgb_color(0, 0, 0);
            ledStrip.write(colors, LED_COUNT);
         rotateSelector(7467);
        break;
      case 1:
   ///////////////////////////////////////////////    Press to unload #2 - switching
        colors[0] = rgb_color(0, 0, 0);
        colors[1] = rgb_color(255, 0, 0);
        colors[2] = rgb_color(0, 0, 0);
        colors[3] = rgb_color(0, 0, 0);
            ledStrip.write(colors, LED_COUNT);
         rotateSelector(4978);
        break;
      case 2:
   ///////////////////////////////////////////////    Press to unload #3 - switching
        colors[0] = rgb_color(0, 0, 0);
        colors[1] = rgb_color(0, 0, 0);
        colors[2] = rgb_color(255, 0, 0);
        colors[3] = rgb_color(0, 0, 0);
            ledStrip.write(colors, LED_COUNT);
           rotateSelector(2489);
        break;
      case 3:
   ///////////////////////////////////////////////    Press to unload #4 - switching
        colors[0] = rgb_color(0, 0, 0);
        colors[1] = rgb_color(0, 0, 0);
        colors[2] = rgb_color(0, 0, 0);
        colors[3] = rgb_color(255, 0, 0);
      rotateSelector(20);
            ledStrip.write(colors, LED_COUNT);
        break;
    } 


  rotateExtruder(counterclockwise);
  }
  else
  {
    lastExtruder = 0;
  }
  disconnectGillotine();
  
 // ok... filament unloaded, time to load the new... so tell the user
  switch(currentExtruder)
  {
    case 0:
   ///////////////////////////////////////////////    Press to load #1
       colors[0] = rgb_color(255, 102, 0);
        colors[1] = rgb_color(0, 0, 0);
        colors[2] = rgb_color(0, 0, 0);
        colors[3] = rgb_color(0, 0, 0);
            ledStrip.write(colors, LED_COUNT);
      rotateSelector(7467);
      break;
    case 1:
   ///////////////////////////////////////////////    Press to load #2
      colors[0] = rgb_color(0, 0, 0);
        colors[1] = rgb_color(255, 102, 0);
        colors[2] = rgb_color(0, 0, 0);
        colors[3] = rgb_color(0, 0, 0);
            ledStrip.write(colors, LED_COUNT);
      rotateSelector(4500);
      break;
    case 2:
   ///////////////////////////////////////////////    Press to load #3
      colors[0] = rgb_color(0, 0, 0);
        colors[1] = rgb_color(0, 0, 0);
        colors[2] = rgb_color(255, 102, 0);
        colors[3] = rgb_color(0, 0, 0);
            ledStrip.write(colors, LED_COUNT);
            rotateSelector(2250);
      break;
    case 3:
   ///////////////////////////////////////////////    Press to load #4
      colors[0] = rgb_color(0, 0, 0);
        colors[1] = rgb_color(0, 0, 0);
        colors[2] = rgb_color(0, 0, 0);
        colors[3] = rgb_color(255, 102, 0);
            ledStrip.write(colors, LED_COUNT);
            rotateSelector(20);
      break;
  }


  rotateExtruder(clockwise);

delay(500);
rotateSelector(9600);//parkovacia poloha

  
  // everybody remember where we parked!
  lastExtruder = currentExtruder;
}



// move the extruder motor in a specific direction for a specific distance (unless it's a "until button is not pressed")
///void rotateExtruder(bool direction, long moveDistance)
void rotateExtruder(bool direction)

{
  // note to bill:  make this acecelerate so it's very fast!!!
  
  digitalWrite(extEnable, LOW);  // lock the motor
  digitalWrite(extDir, direction); // Enables the motor to move in a particular direction
 // const int fastSpeed = speedDelay/speedFactor; // double time

  // this is depricated right now... might bring it back in the future

   // keep waiting until button is pressed
   while (digitalRead(trigger) != 0)
    {
      delay(50);
    }
    
    // Move while button is pressed
    while (digitalRead(trigger) == 0)
    {

      // this is how we pulse the motor to get it to step
      digitalWrite(extStep, HIGH);
      delayMicroseconds(fastSpeed);
      digitalWrite(extStep, LOW);
      delayMicroseconds(fastSpeed);
    }

  
  // ok, done pressing button, so make sure we're not energized (high is no, low is yes)
  digitalWrite(extEnable, HIGH);
}



// similar to extruder, but only stepping 50 (of 200) at a time
//void rotateSelector(bool direction, long workPos)
void rotateSelector(long workPos)
{

  // while we are at it... can we make this faster using the magic you invented above?
  
  digitalWrite(selEnable, LOW); // lock the selector
///  digitalWrite(selDir, direction); // Enables the motor to move in a particular direction

  while(pos!=workPos){
      if(workPos>pos){digitalWrite(selDir, 1); pos++;}
      if(workPos<pos){digitalWrite(selDir, 0); pos--;}
     
      digitalWrite(selStep, HIGH);
      delayMicroseconds(speedDelaySelector);
      digitalWrite(selStep, LOW);
      delayMicroseconds(speedDelaySelector);
      
      if(pos==workPos)break;
   
  }
  ///  digitalWrite(selEnable, HIGH);
}


// rotate the selector clockwise too far from 4, so it'll grind on the bump stop
void homeSelector()
{
    digitalWrite(selEnable, LOW); // lock the selector
    digitalWrite(selDir, 0);
    
 while (digitalRead(homestop) != 0)  //ak nie je koncak zopnuty
  {
      digitalWrite(selStep, HIGH);
      delayMicroseconds(speedDelaySelector);
      digitalWrite(selStep, LOW);
      delayMicroseconds(speedDelaySelector);
  
    if(digitalRead(homestop)==0)break;
    
    }
  
  // move just slightly to extruder 1 (this backs off a little from the hard stop)

 currentExtruder = 0;
 lastExtruder = -2;
    colors[0] = rgb_color(0, 0, 0);
    colors[1] = rgb_color(0, 0, 0);
    colors[2] = rgb_color(0, 0, 0);
    colors[3] = rgb_color(0, 0, 0);
   ledStrip.write(colors, LED_COUNT);
delay(500);

    colors[0] = rgb_color(0, 255, 0);
    colors[1] = rgb_color(0, 255, 0);
    colors[2] = rgb_color(0, 255, 0);
    colors[3] = rgb_color(0, 255, 0);
   ledStrip.write(colors, LED_COUNT);
 delay(500);
    colors[0] = rgb_color(0, 0, 0);
    colors[1] = rgb_color(0, 0, 0);
    colors[2] = rgb_color(0, 0, 0);
    colors[3] = rgb_color(0, 0, 0);
   ledStrip.write(colors, LED_COUNT);
     
   homed=true;
   pos=0;
}




/////////////////////////////////////////////////////////////////////////////
//
// GILOTINE
//
////////////////////////////////////////////////////////////////////////////
// this cycles the servo between two positions
void cutFilament() {
  digitalWrite(selEnable, LOW); // disable stepper so we have power!
  if(reverseServo==false)
  {
    openGillotine();
    closeGillotine();
  }
  else
  {
    closeGillotine();
    openGillotine();
  }
  digitalWrite(selEnable, HIGH);
}



// enable the servo
void connectGillotine()
{
  filamentCutter.attach(11);
}



// disable the servo - so it doesn't chatter when not in use
void disconnectGillotine()
{
  filamentCutter.detach();
}



// cycle servo from 135 and 180
void openGillotine()
{
    for (int pos = 125; pos <= 195; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    filamentCutter.write(pos);              // tell servo to go to position in variable 'pos'
    delayMicroseconds(25000);                       // waits 15ms for the servo to reach the position
  }
  //filamentCutter.write(3.5);       // tell servo to go to position in variable 'pos'
  delay(50);                       // waits 15ms for the servo to reach the position
}



// reverse cycle servo from 180 back to 135
void closeGillotine()
{
  for (int pos = 195; pos >= 125; pos -= 1) { // goes from 180 degrees to 0 degrees
    filamentCutter.write(pos);              // tell servo to go to position in variable 'pos'
    delayMicroseconds(25000);                       // waits 15ms for the servo to reach the position
  }
  delay(50);                       // waits 15ms for the servo to reach the position
}

// buzz buzz buzz
/*
void vibrateMotor()
{
  // oscillate selector 1 time
 /// rotateSelector(clockwise, 8);
 /// rotateSelector(!clockwise, 8);
 rotateSelector(pos+1);
 rotateSelector(pos-1);
}
*/
