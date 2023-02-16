int piezo=5;
int led=7;
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

/** STRUCTS **/
// A struct is just a bunch of variables in a trenchcoat
struct read_values{
  // In this struct there are two variables
  int distance, infrared_message;
};


/**--------------------------------**/

struct read_values parse_message(char* message) {
  // Variable where to store the parsed values
  struct read_values values;
  // Read the values from the string and store them in the struct
  sscanf(message, "%d, %d", &(values.distance), &(values.infrared_message));
  // Return the struct as result of the function
  return values;
}

void setup() {
  // Serial monitor
  while (!Serial);
    Serial.begin(9600);
  // Begin radio communication
  radio.begin();
  // Set the address
  radio.openReadingPipe(0, address);
  // Set module as receiver
  radio.startListening();

    pinMode(piezo, OUTPUT); //buzzer connesso al pin 2
    pinMode(led, OUTPUT);
}

void loop() {
  // If available, read the transmitted data into a text buffer
  if (radio.available())  {
    char text[MESSAGE_LENGTH] = {0};
    // Read the data from the radio module
    radio.read(&text, sizeof(text));
    // Parse the received text to a structured variable (defined above)
    struct read_values new_values = parse_message(text);
    // Print the values that were parsed
    Serial.print(new_values.distance);
    Serial.print("\n");
    Serial.print(new_values.infrared_message);
    Serial.print("\n");

  if (new_values.distance < 30&&new_values.distance> 20) {
    tone(piezo, 500, 200);
  }
  else if(new_values.distance <19 && new_values.distance> 10) {
  tone(piezo, 500, 120);
  }  
  else if(new_values.distance <9 && new_values.distance> 0) {
  tone(piezo, 500, 50);
  }

  if (new_values.infrared_message==1){
  digitalWrite(led, HIGH);
  }
  else{
    digitalWrite(led, LOW);
    }
  
  
  }
      
}
