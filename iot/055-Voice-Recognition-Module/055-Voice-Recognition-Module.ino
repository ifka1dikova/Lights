#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX


byte com = 0; //reply from voice recognition
// define LED's pins

int kitchenLED=2;
int bedroomLED=3;
int livingroomLED=4;
int redLED=5;
int yellowLED=6;


void setup() {
  
  Serial.begin(9600);



  

  Serial.println(" Working!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);



  pinMode (kitchenLED, OUTPUT);
  pinMode (bedroomLED, OUTPUT);
  pinMode (livingroomLED, OUTPUT);
  pinMode (redLED, OUTPUT);
  pinMode (yellowLED, OUTPUT);

  mySerial.write(0xAA);

  mySerial.write(0x37);

  delay(1000);

  mySerial.write(0xAA);

  mySerial.write(0x21);
  
  delay(1000);
  mySerial.write(0xAA);

  mySerial.write(0x24);
while(mySerial.available()) {
  
    Serial.println(mySerial.read());
  }
  delay(1000);

//  digitalWrite(kitchenLED, HIGH);
//       digitalWrite(bedroomLED, HIGH);
//      digitalWrite(livingroomLED, HIGH);
//      digitalWrite(redLED, HIGH);
//      digitalWrite(yellowLED, HIGH);
// delay(500);
//
//        digitalWrite(kitchenLED, LOW);
//       digitalWrite(bedroomLED, LOW);
//        digitalWrite(livingroomLED, LOW);
//        digitalWrite(redLED, LOW);
//        digitalWrite(yellowLED, LOW);


            
}

void loop() {
// mySerial.write(0xAA);
//
//  mySerial.write(0xbb);



//  if (Serial.available()) {
//    mySerial.write(Serial.read());
//  }
//
//
//
//
//
//
//  

  while(mySerial.available()) {
  Serial.println("here");
    com = mySerial.read();
    Serial.println(com);

    switch(com) {
      case 0x11:   //command 1 is for Green LED 
        digitalWrite(kitchenLED, HIGH);
        Serial.println("kitchenLED");
        break;

      case 0x12:  //command 2 is for Red LED
        digitalWrite(bedroomLED, HIGH);
                Serial.println("bedroomLED");

      break;

      case 0x13:  //command 3 is for Yellow LED

      digitalWrite(livingroomLED, HIGH);
              Serial.println("livingroomLED");

      break;

      case 0x14:  //command 4 is for Servo motor
        digitalWrite(redLED, HIGH);
                Serial.println("redLED");

      

      break;

      case 0x15:  //command 5 is for Servo Motor
      digitalWrite(yellowLED, HIGH);
              Serial.println("yellowLED");

      
      

      break;
      default:
      Serial.println ("default");
//       digitalWrite(kitchenLED, HIGH);
//       digitalWrite(bedroomLED, HIGH);
//      digitalWrite(livingroomLED, HIGH);
//      digitalWrite(redLED, HIGH);
//       digitalWrite(yellowLED, HIGH);
                break;


            }
      }
      
}
