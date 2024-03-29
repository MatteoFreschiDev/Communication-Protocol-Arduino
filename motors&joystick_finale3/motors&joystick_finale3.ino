/** INCLUDES **/
// Include the libraries for using the module (must intall RF24 by TMRh20)
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <math.h>
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
  int x, y; 
};

// Declaration of variables
int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 4;
int motor2pin2 = 5;

int motor3pin1 = 14;
int motor3pin2 = 15;
int motor4pin1 = 16;
int motor4pin2 = 17;
int dx, sx, obstacle_front;
int infrared_sensor_front = 7; 


/**--------------------------------**/

struct read_values parse_message(char* message) {
  // Variable where to store the parsed values
  struct read_values values;
  // Read the values from the string and store them in the struct
  sscanf(message, "%d, %d", &(values.x), &(values.y));
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
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(motor3pin1, OUTPUT);
  pinMode(motor3pin2, OUTPUT);
  pinMode(motor4pin1, OUTPUT);
  pinMode(motor4pin2, OUTPUT);
  pinMode(infrared_sensor_front, INPUT);
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
    Serial.print(new_values.x);
    Serial.print(" ");
    Serial.println(new_values.y);
  

  dx=new_values.x;
  sx=new_values.y;
  obstacle_front = digitalRead(infrared_sensor_front);
  
  if (dx>=600){
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor3pin1, HIGH);
  digitalWrite(motor3pin2, LOW);

  }
 else if (dx>400 && dx<600 ){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW); 
  digitalWrite(motor3pin1, LOW);
  digitalWrite(motor3pin2, LOW);
  }
  else if (dx<=400 && obstacle_front==HIGH){
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
 
  digitalWrite(motor3pin1, LOW);
  digitalWrite(motor3pin2, HIGH);

  }
   if (sx>600){
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  digitalWrite(motor4pin1, LOW);
  digitalWrite(motor4pin2, HIGH);

  }
  else if (sx>400 && sx<600){
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

  digitalWrite(motor4pin1, LOW);
  digitalWrite(motor4pin2, LOW);
  }
  else if (sx<=400 && obstacle_front==HIGH){
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  digitalWrite(motor4pin1, HIGH);
  digitalWrite(motor4pin2, LOW);
  }
}    
   delay (100);   
}  