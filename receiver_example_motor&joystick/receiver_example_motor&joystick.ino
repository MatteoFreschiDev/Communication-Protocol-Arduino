/** INCLUDES **/
// Include the libraries for using the module (must intall RF24 by TMRh20)
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <AFMotor.h>
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
  int y_axis_right, y_axis_left; 
};


/**--------------------------------**/

struct read_values parse_message(char* message) {
  // Variable where to store the parsed values
  struct read_values values;
  // Read the values from the string and store them in the struct
  sscanf(message, "%d, %d", &(values.y_axis_right), &(values.y_axis_left));
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
  /*
-------------------------------------------------------------------------------
  */
 
  
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
    Serial.print(new_values.y_axis_right);
    Serial.print(" ");
    Serial.println(new_values.y_axis_left);
  

  
  }
  
  int speed_left, speed_right;
  speed_left=(y_axis_left-512)/2;
  speed_right=(y_axis_right-512)/2;
  motor1.setSpeed(abs (speed_left));
  motro4.setSpeed(abs (speed_left));
  motor2.setSpeed(abs (speed_right));
  motor3.setSpeed(abs (speed_right));
  if(y_axis_left>525){
    motor1.run(FORWARD);
    motor4.run(FORWARD);
  }
  
  if(y_axis_right>525){
    motor2.run(FORWARD);
    motor3.run(FORWARD);
  }

      
}
