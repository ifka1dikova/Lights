#include <SoftwareSerial.h> // including the Software serial port  to be able to use the code below without switching the RX an TX from the voice module
SoftwareSerial mySerial(10, 11); //  alocating the RX, TX on the pins 10 and 11 on the arduino 


byte com = 0; //reply from voice recognition
// define LED's pins according to the pins in the arduino 

int kitchenLED=2; // RGB LED module connected to digital pin 2
int bedroomLED=3; // RGB LED module connected to digital pin 3
int livingroomLED=4; //RGB LED module connected to digital pin 4
int redLED=5;         // RGB LED module connected to digital pin 
int yellowLED=6;      // RGB LED module connected to digital pin 

//set up 
void setup() {
  
  Serial.begin(9600); // start the serial port



  // the sketch compiles and runs and on the serial monitor prints the message "working! " 

  Serial.println(" Working!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);


// pin modes for the commands where the command format is "Head + Key". "Head" is a 0xaa, and "Key" ( see ref [1])
  pinMode (kitchenLED, OUTPUT);
  pinMode (bedroomLED, OUTPUT);
  pinMode (livingroomLED, OUTPUT);
  pinMode (redLED, OUTPUT);
  pinMode (yellowLED, OUTPUT);
// set the serial port to use the commands that was already configurated 
  mySerial.write(0xAA);
// switch to the compact mode
  mySerial.write(0x37);

  delay(1000); // delay 1000 secs

  mySerial.write(0xAA); // set the serial port to use the commands that was already configurated 

  mySerial.write(0x21); // import the group 1 commands ( see ref[1])
  
  delay(1000); // delay 1000 secs
  mySerial.write(0xAA);

  mySerial.write(0x24); //  query the recorded group
while(mySerial.available()) {
  
    Serial.println(mySerial.read());  //  the serial port to print the commands on the myserial( se we do not need to switch the cables) 
  }
  delay(1000);
// delay 1000 secs
            
}

void loop() {  // run over and over again

  while(mySerial.available()) {
  Serial.println("here"); // print "here" in the serial monitor if recognize a comand
    com = mySerial.read(); // read the commands from the voice recognition 
    Serial.println(com); // print the comands from the serial port if recognize the voice

    switch(com) { // switch  from the voice recognition

      case 0x11:   //command 1 is for the kitchen light ( command-PINK)
        digitalWrite(kitchenLED, HIGH); // switch on the LED when hear/ detect  the command
        Serial.println("kitchenLED");  //from the serial print the command
        break; // return

      case 0x12:  //command 2 is for Red LED ( command-Red)
        digitalWrite(bedroomLED, HIGH); // switch on the LED when hear/ detect  the command
                Serial.println("bedroomLED");

      break; // return

      case 0x13:  //command 3 is for Yellow LED ( command-Yellow)

      digitalWrite(livingroomLED, HIGH); // switch on the LED when hear/ detect  the command
              Serial.println("livingroomLED");

      break; // return

      case 0x14:  //command 4 is for blue LED light  ( command-BLUE)
        digitalWrite(redLED, HIGH); // switch on the LED when hear/ detect  the command
                Serial.println("redLED");

      

      break; // return

      case 0x15:  //command 5 is for green LED light  ( command-GREEN)
      digitalWrite(yellowLED, HIGH); // switch on the LED when hear/ detect  the command
              Serial.println("yellowLED");
      break;  // return
      default: // use default settings 
      Serial.println ("default");

                break;


            }
      }
      
}


// [1] http://www.geeetech.com/wiki/images/6/69/Voice_Recognize_manual.pdf 
