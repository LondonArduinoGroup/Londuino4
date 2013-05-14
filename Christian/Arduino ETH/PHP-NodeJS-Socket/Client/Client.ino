/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 modified 9 Apr 2012
 by David A. Mellis
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(192,168,1,64); // Google

int LED = 8;
// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 1338)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /search?q=arduino HTTP/1.0");
    client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  pinMode(LED,OUTPUT);
}

void loop()
{
  // if there are incoming bytes available 
  // from the server, read them and print them:
  String output = "";
  if (client.available()) {
    while(client.available()) {
      char c = client.read();
      output += c;
      //Serial.print(c);
    }
  }
  if (output.length() > 0) {
    Serial.print("output: "); Serial.println(output);
    //Serial.println(output.indexOf("on"));
    if (output.indexOf("on") >= 0) turnOn();
    else if (output.indexOf("off") >= 0) turnOff();
  }

  
}


void turnOn() {
  digitalWrite(LED,HIGH);
}


void turnOff() {
  digitalWrite(LED,LOW);
}
