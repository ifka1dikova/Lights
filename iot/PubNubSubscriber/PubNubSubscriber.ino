/*
  PubNub sample subscribe client

  This sample client will subscribe to and handle raw PubNub messages
  * Ethernet shield attached to pins 10, 11, 12, 13  [ref 1 ] 
  */

#include <SPI.h> // including the Serial Peripheral Interface (SPI) [ref 2]
#include <Ethernet.h> // including ethernet [ref 3]
#include <PubNub.h>   // including PubNup(PN) [ref 4]

// Some Ethernet shields have a MAC address printed on a sticker on the shield;
// fill the address. it needs to be unique code

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };

const int subLedPin = 8;   // constant for the ledPin 8
int redPin=3;              // Red LED,   connected to digital pin 3
int greenPin=6;         // Green LED, connected to digital pin 6
int bluePin=5;          /// Blue LED,  connected to digital pin 5
int id;
int val;
long ledVals[] = {0,0,0};   // array of variables to store the values to send to the pins


String inString="";   // string 
char tempNum[5];

  // the app details from the PN account for this specific app string
char pubkey[] = "pub-c-2f4207eb-7e62-43c2-b7a1-2c001b09c8ec";  // the pub nub key
char subkey[] = "sub-c-10b93e0e-f2fd-11e8-adf7-5a5b31762c0f";  // the sub key 
char channel[] = "ifka-channel";                                // channel name
char uuid[] = "sec-c-Yjg2YWFhNjAtMzUxZi00ODlkLWJhOGYtNTE2Njk1ZDYzZDUz";  // secret key 

void random_uuid() {  //  initializes the pseudo-random number generator [see ref 5]
	randomSeed(analogRead(4) + millis() * 1024);0
	snprintf(uuid, sizeof(uuid), "%04lx%04lx-%04lx-4444-9999-%04lx%04lx%04lx",
		random(0x10000), random(0x10000), random(0x10000),
		random(0x10000), random(0x10000), random(0x10000));
}

void setup()
{
  pinMode(redPin,OUTPUT);   // sets the digital pin as output [see ref 6] 
pinMode(greenPin, OUTPUT);  // sets the digital pin as output
pinMode(bluePin, OUTPUT);   // sets the digital pin as output

	Serial.begin(9600); // Sets the data rate in bits per second (baud) for serial data transmission [see ref 7]
	Serial.println("Serial set up");  // this messages(msg)  will be printed on the serial monitor 

	while (!Ethernet.begin(mac)) {
		Serial.println("Ethernet setup error"); 
		delay(1000); // delay 1000 sec
	}
	Serial.println("Ethernet set up");
/* connecting  the PN app  with the serial monitor to show a msg  */
	PubNub.begin(pubkey, subkey);
	random_uuid();
	PubNub.set_uuid(uuid);
	Serial.println("PubNub set up");
}

void flash(int ledPin)
{
	/* Flash LED three times. */
	for (int i = 0; i < 3; i++) {
		digitalWrite(ledPin, HIGH); /*  LED is on */
		delay(100); // delay 100 sec
		digitalWrite(ledPin, LOW); /*  LED is off */
		delay(100); // delay 100 sec
	}
}
// Main program

void loop()
{
	Ethernet.maintain();  /*  calling the ethernet  */
	
  PubSubClient *client;

  Serial.println("waiting for a message (subscribe)");  /* printing msg on serial monitor */
  client = PubNub.subscribe(channel);
  if (!client) {   /* if the client do not respond */
    Serial.println("subscription error");  /* printing msg on serial monitor */
    delay(1000);  // delay 100 sec
    return;      // return
  }
  Serial.println("Received: ");  /* if the client respond - receive the data*/
  while (client->wait_for_data()) {
    char inChar = client->read();  // read the data
     inString += inChar;   
}
client->stop();  

 int len = inString.length(); // for loop
  for(int i = 0; i < len; i++){

    // find colour channel
    if (inString[i] == 'r') {
      Serial.println("RED");  /* print msg on serial monitor */
      id = 0;                  // alocating diferent IDs for diferent colour channels
    } else if (inString[i] == 'g') {
      Serial.println("GREEN");  /* print msg on serial monitor */
      id = 1;                   // alocating diferent IDs for diferent colour channels
    } else if (inString[i] == 'b') {
      Serial.println("BLUE");  /* print msg on serial monitor */
      id = 2;                   // alocating diferent IDs for diferent colour channels
    }

    // find values
    if(inString[i+2] == ','){
//      Serial.println("comma");
      for(int j = 0; j < sizeof(tempNum); j++) {
        if(inString[i+j+3] != ']'){
          tempNum[j] = (char)inString[i+j+3];   
        } 
      }
    }

    Serial.print(inString[i]);
    Serial.print(" "); 
  }

  val = atoi(tempNum);
  Serial.println(val);
  // assign to ledVals here
  ledVals[id] = val;
  
  // clear array and string
  for(int j = 0; j < sizeof(tempNum); j++) {
    tempNum[j] = (char)0;
  }
  inString = "";
  delay(500); // delay

  Serial.println(ledVals[0]);  // reads an analog input on analog in 0, prints the value out. [see ref 8]
  Serial.println(ledVals[1]);  //   ---|| ---- ||-----
  Serial.println(ledVals[2]);  //---|| ---- ||-----

  setColor(ledVals[0], ledVals[1], ledVals[2]);

}

 /* setting up the colours of the program as red, green and blue  */
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red); /* output the colour */
  analogWrite(greenPin, green);   /* output the colour */
  analogWrite(bluePin, blue);   /* output the colour */
}
/* References 
[1] https://github.com/pubnub/pubnub-api/tree/master/arduino
[2] Serial Peripheral Interface (SPI)  https://www.arduino.cc/en/reference/SPI
[3] https://www.arduino.cc/en/reference/ethernet 
[4] https://www.pubnub.com/docs/arduino/pubnub-arduino-sdk 
[5] https://www.arduino.cc/reference/en/language/functions/random-numbers/randomseed/ 
[6] https://www.arduino.cc/en/Tutorial/DigitalPins 
[7] https://www.arduino.cc/en/serial/begin 
[8] https://www.arduino.cc/en/serial/println 



*/
