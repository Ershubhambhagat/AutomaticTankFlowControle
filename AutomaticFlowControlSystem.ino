const int pingPin = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 5;// Echo Pin of Ultrasonic Sensor
const int relayPin = 8; //
// Define the LED pins
const int ledPins[] = {7, 6, 3,9,11};
const int numLeds = sizeof(ledPins) / sizeof(int);

const long WaitForIncreaseWater =300000;  //5 sec  
const long intervaloraginal = 300;      // 3 sec in milliseconds
const long DeepSleep = 3000000;  
const int OnMotor15 = 15;   // 15 FirstWaterLableCheck
const int OffMotor10 = 10;  // 80 FirstWaterLableCheck
const int SensorNotWorking35 = 35;
void setup() {
  pinMode(relayPin, OUTPUT);
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600); // Starting Serial Terminal
}
void loop() {
   long duration, WaterLevel1;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   WaterLevel1 = microsecondsToInches(duration);
   Serial.print("Top  Check:");
   Serial.print(WaterLevel1);
   Serial.print("inch");
   Serial.println();
  
   //delay(500);
  if ( 10 >=WaterLevel1)// 10==>11
  {
    digitalWrite(ledPins[3], HIGH);
    digitalWrite(relayPin, LOW);
    Serial.print("Relay OFF water is already 10 inch" );
    Serial.println();
    Serial.print("Now Lable is :"+WaterLevel1 );
    Serial.println();
  }
 else if (WaterLevel1 >=SensorNotWorking35) ///36>=35
  {
    Serial.println("Sensor Not Working");
    Serial.println();
    digitalWrite(ledPins[3], HIGH);
     digitalWrite(relayPin, LOW);
    Serial.print("Going To Deep Sleep");
    Serial.println();
    //delay(DeepSleep);
  }
  // ++++++++++++++++++++Pump On Logic ++++++++++++++++++++
  else if ( OnMotor15 <= WaterLevel1 ) //15<24
  //Light Chesser
  {
    for (int i    = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[i], LOW);
  }
   for (int i = numLeds - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[i], LOW);
  }
  //Light Chesser
    long duration,WaterCheckAfterMin;
    digitalWrite(relayPin, HIGH);
    Serial.print("Relay On" );
    Serial.println();
    Serial.print("Low Water Level Going to Start Motor" );
    Serial.println();
    Serial.print("Checkig for 5 Min ...... " );
    Serial.println();
    digitalWrite(ledPins[4], HIGH);

    delay(WaitForIncreaseWater);//WaitForIncreaseWater

    WaterCheckAfterMin;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   WaterCheckAfterMin = microsecondsToInches(duration);
   Serial.print("New Water Lavel:- ");
   Serial.print(WaterCheckAfterMin);
    Serial.println();
   //delay(100);
    digitalWrite(ledPins[4], LOW);

   if (WaterCheckAfterMin >= WaterLevel1)//21>=22
   {
    Serial.print("Water not Increase after Min ");
    Serial.println();
    digitalWrite(ledPins[3], HIGH);

     digitalWrite(relayPin, LOW);
    Serial.print("Motor Off Please ");
    Serial.println();
    Serial.println();
   Serial.print(WaterCheckAfterMin);
    delay(WaitForIncreaseWater);//WaitForIncreaseWater
   }
   else if (WaterLevel1>WaterCheckAfterMin) // 18 < 21< 22 18<28 , 13<30
      {
    Serial.print("Water Increase after Min ");
    Serial.println();
    long duration, WaterCheckAfterMin;//18>10
    while (WaterCheckAfterMin >= OffMotor10)//
    //Light Chesser
    {
      for (int i    = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[i], LOW);
  }
   for (int i = numLeds - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(250); // Wait for 250 milliseconds
    digitalWrite(ledPins[i], LOW);
  }
  //Light Chesser
      pinMode(pingPin, OUTPUT);
      delayMicroseconds(2);
      digitalWrite(pingPin, HIGH);
      digitalWrite(pingPin, LOW);
      delayMicroseconds(10);
      pinMode(echoPin, INPUT);
      duration = pulseIn(echoPin, HIGH);
      WaterCheckAfterMin = microsecondsToInches(duration);
      Serial.print(WaterCheckAfterMin);
      Serial.print("inch");
      Serial.println();
     // delay(500);
      Serial.print("IN WHILE LOOP:-");
      Serial.println();
    }
      }   
  }
  else
  {
    Serial.print("Else ..........");
    Serial.println();
    digitalWrite(ledPins[3], HIGH);

    Serial.print("Tank is Full or Water Not Increase:= ");
    Serial.println();
    digitalWrite(relayPin, LOW);
    Serial.print(WaterLevel1);
    //delay(intervaloraginal);
  }
}
long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}
