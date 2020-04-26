/*Simple Arduino Smart Light, LDR Sensor and Relay Module + Firebase Database
 * Made Adi Paramartha Putra,
 * STMIK Primakara
 * April 2020
 */
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "YOUR_SSID" 
#define WIFI_PASSWORD "SSID_PASSWORD" 
#define FIREBASE_HOST "FIREBASE_HOST" 
#define FIREBASE_AUTH "FIREBASE_AUTH" 


//Variable Declaration
int relayPin = D1;  // Pin for Relay
int sensorPin = D2; // Input pin for LDR
int sensorValue = 0; // variable to store LDR sensor read value
boolean deviceCondition;
boolean ledStatus;

//Setup (Running Once)
void setup() {
  pinMode(relayPin, OUTPUT); //Set Relay Module as an OUPUT
  pinMode(sensorPin, INPUT);  //Set LDR Sensor as an INPUT
  Serial.begin(115200); //Serial Port Comm

  //Start Wi-Fi Connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  Serial.print("connecting"); 
  while (WiFi.status() != WL_CONNECTED) { 
    Serial.print("."); 
    delay(500); 
  } 
  Serial.println(); 
  Serial.print("Connected: "); 
  Serial.println(WiFi.localIP()); 
   
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 }

//Loop (Forever)
void loop() {

  deviceCondition = Firebase.getBool("devCondition/controlable");
  if(deviceCondition == true){
    controlable();
  } else{
    unControlable();
  }
  delay(1000);  //Give 1 seconds delay to read dB deviceCondition.
}


void controlable(){
  ledStatus = Firebase.getBool("ledStatusOn");
  if(ledStatus == true){
    digitalWrite(relayPin,LOW);  //Turn on Relay Module
    Serial.println("Turning On Light");
  }else{
    digitalWrite(relayPin,HIGH); //Turn off Relay Module
    Serial.println("Turning Off Light");
  }
}

void unControlable(){
  sensorValue = digitalRead(sensorPin); // Read Current Value of Sensor
  Serial.println(sensorValue); //Print in Serial Monitor
    if(sensorValue==1){ //Check Condition of sensorValue
      Serial.println("Turning On Light");      
      digitalWrite(relayPin,LOW);  //Turn on Relay Module
      updateDatabase(true);  
          
    }else{
      digitalWrite(relayPin,HIGH); //Turn off Relay Module
      Serial.println("Turning Off Light"); 
      updateDatabase(false);     
    }
    delay(5000);  //Give 5 seconds delay to read Sensor.
}

void updateDatabase( bool stats){
  //Start Write to Firebase Database
      Firebase.setBool("ledStatusOn", stats);
        if (Firebase.failed()) { 
        Serial.print("setting /message failed:"); 
        Serial.println(Firebase.error());   
        return; 
      } else{
        Serial.println("Database Upload Success");
        Serial.println(stats);
      }
}
