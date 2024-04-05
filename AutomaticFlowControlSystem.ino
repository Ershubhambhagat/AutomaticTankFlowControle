const int pingPin = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 5;// Echo Pin of Ultrasonic Sensor
const int relayPin = 8; //



int FirstWaterLableCheck;
//const long interval = 300000;      // 5 minutes in milliseconds
const long WaitForIncreaseWater =5000;  //5 sec  
const long intervaloraginal = 300;      // 3 sec in milliseconds
const long DeepSleep = 300;  
const int OnMotor15 = 15;   // 15 FirstWaterLableCheck
const int OffMotor10 = 10;  // 80 FirstWaterLableCheck
const int SensorNotWorking35 = 35;

 
void setup() {
  pinMode(relayPin, OUTPUT);
  
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
    Serial.print("Going To Deep Sleep");
    Serial.println();
    //delay(DeepSleep);
  }

  // Pump On Logic 
  else if ( OnMotor15 <= WaterLevel1 ) //15<24
  {
    long duration,WaterCheckAfterMin;
    digitalWrite(relayPin, HIGH);
    Serial.print("Relay On" );
    Serial.println();

    Serial.print("Low Water Level Going to Start Motor" );
    Serial.println();
   
    Serial.print("Checkig ......" );

    Serial.println();
    delay(WaitForIncreaseWater);//WaitForIncreaseWater
    long WaterLevel1;
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
   if (WaterCheckAfterMin > WaterLevel1)
   
   {
    Serial.print("Water not Increase after Min ");
    Serial.println();

    Serial.print("Motor Off Please ");
    Serial.println();

    Serial.print("Again Wait For Increase Water ");
    Serial.println();

   Serial.print(WaterCheckAfterMin);


    delay(WaitForIncreaseWater);//WaitForIncreaseWater


    
   }
   else if (WaterCheckAfterMin < WaterLevel1) //18<28 , 13<30
      {
    Serial.print("Water Increase after Min ");
    Serial.println();
    long duration, WaterCheckAfterMin;//18>10
    while (WaterCheckAfterMin >= OffMotor10)//23>10 ,13>10,17>10
    {

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

