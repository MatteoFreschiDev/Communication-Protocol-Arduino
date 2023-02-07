#define echoPin 5 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 6 //attach pin D3 Arduino to pin Trig of HC-SR04

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

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
  // Print to this string the values to send
  sprintf(message, "%d", distance);
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

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
}

void loop() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(20);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(30);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Create the message to send, using the create_message function
  char *to_send = create_message();
  // Print the message to the serial monitor for test purposes
  Serial.println(to_send);
  // Send this data (a text string) using the radio module
  radio.write(to_send, MESSAGE_LENGTH);
  // Free the memory (to avoid memory leaks by allocating new memory each loop)
  free(to_send);

  // Wait before repeating (time in milliseconds)
  delay(10);
}
