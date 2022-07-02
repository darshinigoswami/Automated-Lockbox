#include <stdio.h>
#include <stdlib.h>
#define LED1 46 //LED1 indicating package in compartment 1
#define LED2 47 //LED2 indicating package in compartment 2

const int pushbutton = 38; //Pin Connection for Pushbutton

const int irs1 = A1; //Pin Connection for IR Sensor 1
const int irs2 = A2; //Pin Connection for IR Sensor 2

const int lock1 = 2; //Pin Connection for Lock 1
const int lock2 = 3; //Pin Connection for Lock 2

const int actuator11 = 22; //Pin Connection to extend Actuator 1 
const int actuator12 = 23; // Pin Connection to Retract Actuator 1
const int actuator21 = 24; //Pin Connection to Extend Actuator 2
const int actuator22 = 25; //Pin Connection to Retract Actuator 2

const int actuator31 = 26; //Pin Connection to Extend Actuator 3
const int actuator32 = 27; //Pin Connection to Retract Actuator 3
const int actuator41 = 28; //Pin Connection to Retract Actuator 4
const int actuator42 = 29; //Pin Connection to Retract Actuator 4


void setup() 
{
  
    pinMode(pushbutton,INPUT); //Pushbutton as INPUT
    
    pinMode(LED1, OUTPUT); // LED1 as OUTPUT
    pinMode(LED2, OUTPUT);// LED2 as OUTPUT 
    
    digitalWrite(LED1, LOW); // Set LED1 as LOW
    digitalWrite(LED2, LOW); // Set LED2 as LOW
    
    pinMode(irs1, INPUT); //IR Sensor 1 as INPUT, HIGH indicates there is a package in the lockbox
    pinMode(irs2, INPUT); //IR Sensor 2 as INPUT, HIGH indicates there is a package in the lockbox
    
    pinMode(lock1, OUTPUT); //Lock 1 as OUTPUT
    pinMode(lock2, OUTPUT); //Lock 2 as OUTPUT
    
    digitalWrite(lock1, HIGH); //Engage Lock 1
    digitalWrite(lock2, HIGH); //Engage Lock 2
    
    pinMode(actuator11, OUTPUT); //Actuator 1 Extender as OUTPUT                                                                                                                                                                                 r 1 as OUTPUT
    pinMode(actuator12, OUTPUT); //Actuator 1 Retractor as OUTPUT
    
    pinMode(actuator21, OUTPUT); //Actuator 2 Extender as OUTPUT                                                                                                                                                                                  r 1 as OUTPUT
    pinMode(actuator22, OUTPUT); //Actuator 2 Retractor as OUTPUT
    
    pinMode(actuator31, OUTPUT); //Actuator 3 Extender as OUTPUT                                                                                                                                                                                 r 1 as OUTPUT
    pinMode(actuator32, OUTPUT); //Actuator 3 Retractor as OUTPUT
    
    pinMode(actuator41, OUTPUT); //Actuator 4 Extender as OUTPUT                                                                                                                                                                                  r 1 as OUTPUT
    pinMode(actuator42, OUTPUT); //Actuator 4 Retractor as OUTPUT
    
    digitalWrite(actuator11, HIGH); //Initializing Actuator 1 Extender to remain closed
    digitalWrite(actuator12, HIGH); //Initializing Actuator 1 Reractor to remain closed
    
    digitalWrite(actuator21, HIGH); //Initializing Actuator 2 Extender to remain closed
    digitalWrite(actuator22, HIGH); //Initializing Actuator 2 retractor to remian closed
    
    digitalWrite(actuator31, HIGH); //Initializing Actuator 3 Extender to remain closed
    digitalWrite(actuator32, HIGH); //Initializing Actuator 3 Reractor to remain closed
    
    digitalWrite(actuator41, HIGH); //Initializing Actuator 4 Extender to remain closed
    digitalWrite(actuator42, HIGH); //Initializing Actuator 4 retractor to remian closed    
    

    
    attachInterrupt(digitalPinToInterrupt (pushbutton), button_pressed, HIGH); //Interrupt function button_pressed
    
}

void loop() {
  
    
}

void button_pressed() 
{
  if (irs1 == HIGH) 
  { //If the IR sensor in compartment 1 senses a package
    
    digitalWrite(LED1, HIGH); // Turn LED1 on to indicate a package is in compartment 1
    
       if (irs2 == HIGH)
        { 
        //If the IR sensor in compartment 2 also senses a package
         digitalWrite(LED2, HIGH); // Turn LED2 on to indicate a package is in compartment 2
        }
    
         if (irs2 == LOW)
          { //If the IR sensor in compartment 2 does NOT sense  a package
    
           digitalWrite(lock2, LOW); //Open lock 2 
    
           delay(1000); //give lock 2 second to open
    
           //Extend Actuator 3
           digitalWrite(actuator31, LOW); //Set Actuator 3 Extender to LOW in order to allow the top relay to be energized
           digitalWrite(actuator32, HIGH); //Set Actuator 3 Retractor to HIGH
           
           //Extend Actuator 4
           digitalWrite(actuator41, LOW); //Set Actuator 4 Extender to LOW in order to allow the top relay to be energized
           digitalWrite(actuator42, HIGH); //Set Actuator 4 Retractor to HIGH
      
           delay(5000); //give 3 seconds for Actuators 3 & 4 to open 
    
           // Stop Actuator 3
           digitalWrite(actuator31, HIGH); //Stop Actuator 3
           digitalWrite(actuator32, HIGH); //Stop Actuator 3
           
           // Stop Actuator 4
           digitalWrite(actuator41, HIGH); //Stop Actuator 4
           digitalWrite(actuator42, HIGH); //Stop Actuator 4
    
           delay(20000); // Wait 20 seconds for package to be placed inside compartment 2
    
           // Retract Actuator 3
           digitalWrite(actuator31, HIGH); // Set Actuator 3 to HIGH
           digitalWrite(actuator32, LOW); //Set Actuator 3 Retractor to LOW in order to allow second relay to be energized
           
           // Retract Actuator 4
           digitalWrite(actuator41, HIGH); // Set Actuator 4 to HIGH
           digitalWrite(actuator42, LOW); //Set Actuator 4 Retractor to LOW in order to allow second relay to be energized
           
           obstacle2(); //Check if there is something interfering   
           
           // Retract Actuator 3
           digitalWrite(actuator31, HIGH); // Set Actuator 3 to HIGH
           digitalWrite(actuator32, LOW); //Set Actuator 3 Retractor to LOW in order to allow second relay to be energized
           
           // Retract Actuator 4
           digitalWrite(actuator41, HIGH); // Set Actuator 4 to HIGH
           digitalWrite(actuator42, LOW); //Set Actuator 4 Retractor to LOW in order to allow second relay to be energized
           delay(5000); //give 3 seconds for Actuator 2 to close
           
           digitalWrite(lock2, HIGH); // Lock compartment 2
           digitalWrite(LED2, HIGH); // Turn LED2 on to indicate a package is in compartment 2
           }
    
  }
  
  if (irs1 == LOW) 
  {
  //If the IR sensor in compartment 1 does NOT sense  a package
  
   digitalWrite(lock1, LOW); //Open lock 1 
    
           delay(1000); //give lock 1 second to open
    
          //Extend Actuator 1
           digitalWrite(actuator11, LOW); //Set Actuator 1 Extender to LOW in order to allow the top relay to be energized
           digitalWrite(actuator12, HIGH); //Set Actuator 1 Retractor to HIGH
      
          //Extend Actuator 2
           digitalWrite(actuator21, LOW); //Set Actuator 2 Extender to LOW in order to allow the top relay to be energized
           digitalWrite(actuator22, HIGH); //Set Actuator 2 Retractor to HIGH
           delay(5000); //give 3 seconds for Actuator 1 & 2 to open 
    
          // Stop Actuator 1
           digitalWrite(actuator11, HIGH); //Stop Actuator 1
           digitalWrite(actuator12, HIGH); //Stop Actuator 1
    
          // Stop Actuator 2
           digitalWrite(actuator21, HIGH); //Stop Actuator 2
           digitalWrite(actuator22, HIGH); //Stop Actuator 2
           delay(20000); // Wait 20 seconds for package to be placed inside compartment 1
    
          // Retract Actuator 1
           digitalWrite(actuator11, HIGH); // Set Actuator 1 to HIGH
           digitalWrite(actuator12, LOW); //Set Actuator 1 Retractor to LOW in order to allow second relay to be energized
           
           // Retract Actuator 2
           digitalWrite(actuator21, HIGH); // Set Actuator 2 to HIGH
           digitalWrite(actuator22, LOW); //Set Actuator 2 Retractor to LOW in order to allow second relay to be energized
           
           obstacle1();    //Check if there is something interfering   
           
           // Retract Actuator 1
           digitalWrite(actuator11, HIGH); // Set Actuator 1 to HIGH
           digitalWrite(actuator12, LOW); //Set Actuator 1 Retractor to LOW in order to allow second relay to be energized
           
           // Retract Actuator 2
           digitalWrite(actuator21, HIGH); // Set Actuator 2 to HIGH
           digitalWrite(actuator22, LOW); //Set Actuator 2 Retractor to LOW in order to allow second relay to be energized
           
           delay(5000); //give 3 seconds for Actuator 1 to close
           
           digitalWrite(lock1, HIGH); // Lock compartment 1
           digitalWrite(LED1, HIGH); // Turn LED1 on to indicate a package is in compartment 1
    
  }
}

void obstacle1()
{
  while (irs1 == HIGH)
  {
    // Stop Actuator 1
           digitalWrite(actuator11, HIGH); //Stop Actuator 1
           digitalWrite(actuator12, HIGH); //Stop Actuator 1
           
    // Stop Actuator 2
           digitalWrite(actuator21, HIGH); //Stop Actuator 2
           digitalWrite(actuator22, HIGH); //Stop Actuator 2
           
    delay(2000);
    
    //Extend Actuator 1
           digitalWrite(actuator11, LOW); //Set Actuator 1 Extender to LOW in order to allow the top relay to be energized
           digitalWrite(actuator12, HIGH); //Set Actuator 1 Retractor to HIGH
           
   //Extend Actuator 2
           digitalWrite(actuator21, LOW); //Set Actuator 2 Extender to LOW in order to allow the top relay to be energized
           digitalWrite(actuator22, HIGH); //Set Actuator 2 Retractor to HIGH
           
    delay(5000);
    
    // Stop Actuator 1
           digitalWrite(actuator11, HIGH); //Stop Actuator 1
           digitalWrite(actuator12, HIGH); //Stop Actuator 1
           
    // Stop Actuator 2
           digitalWrite(actuator21, HIGH); //Stop Actuator 1
           digitalWrite(actuator22, HIGH); //Stop Actuator 1
  }
}

void obstacle2()
{
  while (irs2 == HIGH)
  {
    // Stop Actuator 3
           digitalWrite(actuator31, HIGH); //Stop Actuator 3
           digitalWrite(actuator32, HIGH); //Stop Actuator 3
           
   // Stop Actuator 4
           digitalWrite(actuator41, HIGH); //Stop Actuator 4
           digitalWrite(actuator42, HIGH); //Stop Actuator 4
           
    delay(200); //Give actuator 3 & 4 time to stop 
    
    //Extend Actuator 3
           digitalWrite(actuator31, LOW); //Set Actuator 3 Extender to LOW in order to allow the top relay to be energized
           digitalWrite(actuator32, HIGH); //Set Actuator 3 Retractor to HIGH
           
    //Extend Actuator 4
           digitalWrite(actuator41, LOW); //Set Actuator 4 Extender to LOW in order to allow the top relay to be energized
           digitalWrite(actuator42, HIGH); //Set Actuator 4 Retractor to HIGH
    delay(5000);
    
    // Stop Actuator 3
           digitalWrite(actuator31, HIGH); //Stop Actuator 3
           digitalWrite(actuator32, HIGH); //Stop Actuator 3
           
      // Stop Actuator 4
           digitalWrite(actuator41, HIGH); //Stop Actuator 4
           digitalWrite(actuator42, HIGH); //Stop Actuator 4
  }
}
