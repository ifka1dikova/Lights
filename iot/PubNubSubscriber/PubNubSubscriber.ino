/*
  PubNub sample subscribe client

  This sample client will subscribe to and handle raw PubNub messages
  (not doing any JSON decoding).  It does so with a randomly generated
  UUID.

  Circuit:
  * Ethernet shield attached to pins 10, 11, 12, 13
  * (Optional.) LED on pin 8 for reception indication.
  * Pin A4 unconnected (noise source for random number generator)

  created 23 October 2012
  by Petr Baudis

  https://github.com/pubnub/pubnub-api/tree/master/arduino
  This code is in the public domain.
  */

#include <SPI.h>
#include <Ethernet.h>
#include <PubNub.h>

// Some Ethernet shields have a MAC address printed on a sticker on the shield;
// fill in that address here, or choose your own at random:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };

const int subLedPin = 8;
int redPin=3;
int greenPin=6;
int bluePin=5;
int id;
int val;
long ledVals[] = {0,0,0};


String inString="";
char tempNum[5];


char pubkey[] = "pub-c-2f4207eb-7e62-43c2-b7a1-2c001b09c8ec";
char subkey[] = "sub-c-10b93e0e-f2fd-11e8-adf7-5a5b31762c0f";
char channel[] = "ifka-channel";
char uuid[] = "sec-c-Yjg2YWFhNjAtMzUxZi00ODlkLWJhOGYtNTE2Njk1ZDYzZDUz";

void random_uuid() {
	randomSeed(analogRead(4) + millis() * 1024);
	snprintf(uuid, sizeof(uuid), "%04lx%04lx-%04lx-4444-9999-%04lx%04lx%04lx",
		random(0x10000), random(0x10000), random(0x10000),
		random(0x10000), random(0x10000), random(0x10000));
}

void setup()
{
  pinMode(redPin,OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);

	Serial.begin(9600);
	Serial.println("Serial set up");

	while (!Ethernet.begin(mac)) {
		Serial.println("Ethernet setup error");
		delay(1000);
	}
	Serial.println("Ethernet set up");

	PubNub.begin(pubkey, subkey);
	random_uuid();
	PubNub.set_uuid(uuid);
	Serial.println("PubNub set up");
}

void flash(int ledPin)
{
	/* Flash LED three times. */
	for (int i = 0; i < 3; i++) {
		digitalWrite(ledPin, HIGH);
		delay(100);
		digitalWrite(ledPin, LOW);
		delay(100);
	}
}

void loop()
{
	Ethernet.maintain();
	
  PubSubClient *client;

  Serial.println("waiting for a message (subscribe)");
  client = PubNub.subscribe(channel);
  if (!client) {
    Serial.println("subscription error");
    delay(1000);
    return;
  }
  Serial.println("Received: ");
  while (client->wait_for_data()) {
    char inChar = client->read();
     inString += inChar;   
}
client->stop();

 int len = inString.length();
  for(int i = 0; i < len; i++){

    // find colour channel
    if (inString[i] == 'r') {
      Serial.println("RED");
      id = 0;
    } else if (inString[i] == 'g') {
      Serial.println("GREEN");
      id = 1;
    } else if (inString[i] == 'b') {
      Serial.println("BLUE");
      id = 2;
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
  delay(500);

  Serial.println(ledVals[0]);
  Serial.println(ledVals[1]);
  Serial.println(ledVals[2]);

  setColor(ledVals[0], ledVals[1], ledVals[2]);

}

 
void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
