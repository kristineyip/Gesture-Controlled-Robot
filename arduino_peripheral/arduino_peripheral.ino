// Arduino Line Follower Robot Code

#include <ArduinoBLE.h>
#include "lfr.h"


const int ledPin = LED_BUILTIN; 
#define enA 3//Enable1 L293 Pin enA 
#define in1 2 //Motor1  L293 Pin in1 
#define in2 4 //Motor1  L293 Pin in1 
#define in3 6 //Motor2  L293 Pin in1 
#define in4 7 //Motor2  L293 Pin in1 
#define enB 5 //Enable2 L293 Pin enB 
#define R_S 8//ir sensor Right
#define L_S 9 //ir sensor Left

#define LEDR 22     
#define LEDB 24     
#define LEDG 23
  
enum {
  ANOMALY = -1,
  IDLE = 3,
  FORWARD = 2,
  BACKWARD = 0,
  RIGHT = 5,
  LEFT = 4,
  CIRCLE = 1,
  SQUIGGLE = 6
};

char input;
const char* deviceServiceUuid = "19b10000-e8f2-537e-4f6c-d104768a1214";
const char* deviceServiceCharacteristicUuid = "19b10001-e8f2-537e-4f6c-d104768a1214";

int gesture = 0; // set initialized gesture to idle
BLEService gestureService(deviceServiceUuid); 
BLEByteCharacteristic gestureCharacteristic(deviceServiceCharacteristicUuid, BLERead | BLEWrite);

void setup(){ 
  Serial.begin(9600);
  while(!Serial);
  
  //setting pinModes for each of the above defined pins
  pinMode(R_S, INPUT); 
  pinMode(L_S, INPUT); 
  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
  pinMode(enB, OUTPUT);
  
  
  //for the Motor driver to be able to send commands we need to ENABLE it
  digitalWrite(enA, HIGH); 
  digitalWrite(enB, HIGH); 
  
  //defining pinmodes for LEDs
  pinMode(LED_BUILTIN, OUTPUT);  
  pinMode(LEDR, OUTPUT); 
  pinMode(LEDB, OUTPUT); 
  pinMode(LEDG, OUTPUT); 
  
  
  //setting all inputs to the motor to zero
  digitalWrite(in1, LOW); //Right Motor forward Pin 
  digitalWrite(in2, LOW);  //Right Motor backward Pin 
  digitalWrite(in3, LOW);  //Left Motor backward Pin 
  digitalWrite(in4, LOW); //Left Motor forward Pin 

  if (!BLE.begin()) {
    Serial.println("- Starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  BLE.setLocalName("Arduino Nano 33 BLE (Peripheral)");
  BLE.setAdvertisedService(gestureService);
  gestureService.addCharacteristic(gestureCharacteristic);
  BLE.addService(gestureService);
  gestureCharacteristic.writeValue(-1);
  BLE.advertise();

  Serial.println("Nano 33 BLE (Peripheral Device)");
  Serial.println(" ");

}

void loop(){  
  lights_off();
  
  // connect to the central BLE device
  BLEDevice central = BLE.central();
  Serial.println("- Discovering central device...");
  delay(500);

  if (central) {
    Serial.println("* Connected to central device!");
    Serial.print("* Device MAC address: ");
    Serial.println(central.address());
    Serial.println(" ");

    while (central.connected()) {
      if (gestureCharacteristic.written()) {
         gesture = gestureCharacteristic.value();
         makeMovement(gesture);
       }
    }
    
    Serial.println("* Disconnected from central device!");
  }
  
  // in 1 and in2 are a pair
  // in 3 and in4 are a pair
  // main_lfr();
  
  // test code for robot movements
  // if (Serial.available()) {
  //   input = Serial.read();
  //   Serial.print("input:");
  //   Serial.print(input);

  //   if (input == 'a') {
  //     forward();
  //   } else if (input == 's') {
  //     Stop();
  //   } else if (input == 'q') {
  //       forward();
  //       turnRight(); 
  //       delay(150);
  //       Stop();
  //       forward();
  //       turnLeft();
  //       delay(150);
  //       forward();
  //       turnRight(); 
  //       delay(150);
  //       Stop();
  //       forward();
  //       turnLeft();
  //       delay(150);
  //       forward();
  //       turnRight(); 
  //       delay(150);
  //       Stop();
  //       forward();
  //       turnLeft();
  //       delay(150);
  // }

  // }
  
}

void makeMovement(int gesture) {
    Serial.print("Recieved gesture: ");
    Serial.print(gesture);

    switch(gesture) {
      case FORWARD:
        forward();
        delay(1000);
        Stop();
        break;
      case BACKWARD:
        
        break;

      case LEFT:
        turnLeft();
        delay(500);
        Stop();
        break;

      case RIGHT:
        turnRight();
        delay(500);
        Stop();
        break;
        
      case CIRCLE: // CIRCLE == U_TURN/360 TURN
        turnRight();
        delay(1000);
        Stop();
        break;

      case SQUIGGLE:
        forward();
        turnRight(); 
        delay(150);
        Stop();
        forward();
        turnLeft();
        delay(150);
        forward();
        turnRight(); 
        delay(150);
        Stop();
        forward();
        turnLeft();
        delay(150);
        forward();
        turnRight(); 
        delay(150);
        Stop();
        forward();
        turnLeft();
        delay(150);
        break;

      case IDLE:
        Stop();
        break;

      case ANOMALY: // turn on the anomaly light
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(1000);                       // wait for a second
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW

        break;
    }
}