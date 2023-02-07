#define echoPin 5 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 6 //attach pin D3 Arduino to pin Trig of HC-SR04


// defines variables
long duration; // variable for the duration of sound wave travel
float distance; // variable for the distance measurement
int LED = 13; // Use the onboard Uno LED
int isObstaclePin = 4; // This is our input pin
int isObstacle = HIGH; // HIGH MEANS NO OBSTACLE
bool Rollin = true;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(2,OUTPUT); //buzzer connesso al pin 2
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
  pinMode(isObstaclePin, INPUT);
  }
  
void loop() {
  isObstacle = digitalRead(isObstaclePin);

  if (isObstacle == LOW) {
    Rollin = false;
    tone(2, 500, 100);
  }

  else {
    delay(100);
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
    // Displays the distance on the Serial Monitor
    
    if (distance > 0 and distance < 200 and isObstacle == HIGH) {
      Serial.print("Distance: "); // bisogna rendere la velocità dei motori = 0 o almeno far decelerare i motori
      Serial.println(distance);
      int t = distance * 20;
      
      if (distance < 20 and distance > 10) {
        tone(2, 500, 100);
        delay(t);
      }
      else if (distance < 5) {
        Rollin = false;
        tone(2, 500, 100);
      }
    }
  }
}
