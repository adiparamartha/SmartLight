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
int sensorPin = D0; // Input pin for LDR
int relayPin = D1;  // Pin for Relay
int sensorValue = 0; // variable to store LDR sensor read value

//Setup (Running Once)
void setup() {
  pinMode(D0, OUTPUT); //Set Relay Module as an OUPUT
  pinMode(D1, INPUT);  //Set LDR Sensor as an INPUT
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
  
  sensorValue = digitalRead(sensorPin); // Read Current Value of Sensor
  Serial.println(sensorValue); //Print in Serial Monitor
    if(sensorValue==1){ //Check Condition of sensorValue
      digitalWrite(8,LOW);  //Turn off Relay Module
      updateDatabase(false);  
          
    }else{
      digitalWrite(8,HIGH); //Turn on Relay Module
      updateDatabase(true);
    }
    
  delay(5000);  //Give 5 seconds delay to read.

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
