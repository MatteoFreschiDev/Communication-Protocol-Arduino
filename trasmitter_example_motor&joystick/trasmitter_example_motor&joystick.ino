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

char* create_message() {
  // Create dinamically the space to store the string with memory allocation
  char* message = (char*)malloc(MESSAGE_LENGTH);
  // we declare the variables and assign them the values read from the joystick
  int y_axis_right = analogRead(A0);
  int y_axis_left = analogRead(A1);
  // Print to this string the values to send
  sprintf(message, "%d, %d", y_axis_left, y_axis_right);
  // Return the created string as result of the function (MUST BE FREED LATER)
  return message;
}

void setup() {
  // Serial monitor
  while (!Serial);
    Serial.begin(9600);
  // Begin radio communication
  radio.begin();
  // Set the address
  radio.openWritingPipe(address);
  // Set this module as transmitter
  radio.stopListening();
}

void loop() {
  // Create the message to send, using the create_message function
  char *to_send = create_message();
  // Print the message to the serial monitor for test purposes
  Serial.println(to_send);
  // Send this data (a text string) using the radio module
  radio.write(to_send, MESSAGE_LENGTH);
  // Free the memory (to avoid memory leaks by allocating new memory each loop)
  free(to_send);
  // Wait before repeating (time in milliseconds)
  delay(1000);
}
