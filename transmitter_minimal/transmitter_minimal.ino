/** INCLUDES **/
// Include the libraries for using the module (must intall RF24 by TMRh20)
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/** DEFINES **/
#define MESSAGE_LENGTH 20

/** MODULE SPECIFIC CODE **/
// Create an RF24 object, specifying CE and CSN
RF24 radio(9, 8);
// Create a variable to store the address through which two modules communicate
const byte address[6] = "00001";

/**--------------------------------**/

void setup() {
  // Begin radio communication
  radio.begin();
  // Set the address
  radio.openWritingPipe(address);
  // Set this module as transmitter
  radio.stopListening();
}

void loop() {
  const char text[] = "Hello World";
  // Send this data (a text string) using the radio module
  radio.write(&text, sizeof(text));
  // Wait before repeating (time in milliseconds)
  delay(1000);
}
