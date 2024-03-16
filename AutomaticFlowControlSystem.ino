#include <NewPing.h>

const int trigPin = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 4;// Echo Pin of Ultrasonic Sensor
const int relayPin = 7; //


// Create NewPing object for ultrasonic sensor
NewPing sonar(trigPin, echoPin);

// Variables for water level, time intervals, and delays
int waterLevel;
int initialWaterLevel;
unsigned long previousMillis = 0;
//const long interval = 600000;      // 10 minutes in milliseconds
const int pumpStartDelay = 5000;  // 10 seconds
const long interval = 5000;      // 5 sec in milliseconds
const int pumpOffDelay = 10000;    // 10 seconds
const int measurementDelay = 10000; // 10 seconds

// Define water level thresholds
const int lowWaterThreshold = 10;   // 10 inches
const int highWaterThreshold = 10;  // 80 inches
const int stopPumpThreshold = 5;    // 5 inches

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Set relay pin as output
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // Measure initial water level using ultrasonic sensor
  initialWaterLevel = sonar.ping_in();
  Serial.println(initialWaterLevel +"==initialWaterLevel");

  // Check if water level is already at or above the high water threshold
  if (initialWaterLevel >= highWaterThreshold)//11>=10
  {
    // Turn off the pump
    Serial.print("initialWaterLevel >= highWaterThreshold");
    Serial.println();
     Serial.print(initialWaterLevel +">="+ highWaterThreshold);
     Serial.println();
    digitalWrite(relayPin, LOW);
    delayWithCountdown(pumpOffDelay);
  } else if (initialWaterLevel < stopPumpThreshold) 
  {
    Serial.print("initialWaterLevel < stopPumpThreshold");
    Serial.println();
    Serial.print(initialWaterLevel +"<"+ stopPumpThreshold);
    // Start the pump
    digitalWrite(relayPin, HIGH);
    delayWithCountdown(pumpStartDelay);

    // Measure water level again after the delay
    waterLevel = sonar.ping_in();

    // If water level increased, continue pumping until the high water threshold
    if (waterLevel > initialWaterLevel) 
    {
      
       Serial.print("waterLevel > initialWaterLevel");
       Serial.println();
       Serial.print(waterLevel+">"+  initialWaterLevel);
       Serial.println();
      while (waterLevel < highWaterThreshold) {
        // Print water level and relay status
        Serial.print("waterLevel < highWaterThreshold(5)");
       Serial.print(waterLevel+"<" + highWaterThreshold);
        printStatus();
        // Measure water level
        waterLevel = sonar.ping_in();
        delayWithCountdown(measurementDelay);
      }
    }

    // If water level dropped to the stop pump threshold, turn off the pump
    if (waterLevel <= stopPumpThreshold) {
      digitalWrite(relayPin, LOW);
    } else {
      // Otherwise, turn off the pump after 10 minutes
      delayWithCountdown(pumpOffDelay);
      digitalWrite(relayPin, LOW);
    }
  }

  // Print water level and relay status
  printStatus();
}

// Function to print water level and relay status
void printStatus() {
  unsigned long currentMillis = millis();

  // Print water level and relay status every 10 minutes
  if (currentMillis - previousMillis >= interval) {
    Serial.print("Water Level: ");
    Serial.print(waterLevel);
    Serial.print(" inches | Relay Status: ");
    Serial.println(digitalRead(relayPin) == HIGH ? "ON" : "OFF");

    // Update the last time the values were printed
    previousMillis = currentMillis;
  }
  Serial.print(" ------------Compleate---------------------");
  Serial.println();
  Serial.println();
}

// Function to delay with countdown
void delayWithCountdown(unsigned long delayTime) {
  Serial.print("Waiting: ");
  for (int i = delayTime / 1000; i > 0; i--) {
    Serial.print(i);
    Serial.print("s ");
    delay(1000);
  }
  Serial.println();
}
