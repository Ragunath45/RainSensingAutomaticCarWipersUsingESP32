#include <ESP32Servo.h>
#include "FirebaseESP32.h"
#include<WiFi.h>
#define FIREBASE_HOST "https://rainsensingcarautomaticwipers-default-rtdb.firebaseio.com/" 

#define FIREBASE_AUTH "pFvxbtHhKwdxbQSRfxB5NZp2LBpN6iN2klevMx0i"

#define WIFI_SSID "Ragunath"

#define WIFI_PASSWORD "Ragunath"

FirebaseData firebaseData;

const int rainSensorPin = 2;
const int servoPin = 26;
Servo servo;


void setup() {
   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Serial.begin(115200);
  pinMode(rainSensorPin, INPUT);
   servo.attach(servoPin);
   
}

void loop() {
  // Read the rain sensor value
  int rainValue = digitalRead(rainSensorPin);
 
  delay(1000);

  if (rainValue == HIGH) {
    Serial.println("no Rain detected!");
    Firebase.setString(firebaseData,"Rain","not Raining,Wipers not Started ...!");
    
  } else {
     Serial.println(" rain detected.");
     Firebase.setString(firebaseData,"Rain","Rain detected..! Wipers Started");
     servo.write(0);
  delay(1000); // Wait for 1 second
  
  // Move the servo to 90 degrees
  servo.write(90);
  delay(1000); // Wait for 1 second
  
  // Move the servo to 180 degrees
  servo.write(180);
  delay(1000); 
   
  }

  delay(1000); // Delay for 1 second before checking again
}
