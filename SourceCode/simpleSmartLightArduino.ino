/*Simple Arduino Smart Light, LDR Sensor and Relay Module
 * Made Adi Paramartha Putra,
 * STMIK Primakara
 * April 2020
 */

//Variable Declaration
int sensorPin = 2; // Input pin for LDR
int relayPin = 8;
int sensorValue = 0; // variable to store LDR sensor read value

//Setup (Running Once)
void setup() {
pinMode(8, OUTPUT); //Set Relay Module as an OUPUT
pinMode(2, INPUT);  //Set LDR Sensor as an INPUT
Serial.begin(9600); //Serial Port Comm
}

//Loop (Forever)
void loop() {
sensorValue = digitalRead(sensorPin); // Read Current Value of Sensor
Serial.println(sensorValue); //Print in Serial Monitor
  if(sensorValue==1){ //Check Condition of sensorValue
    digitalWrite(8,LOW);  //Turn off Relay Module
  }else{
    digitalWrite(8,HIGH); //Turn on Relay Module
  }
delay(5000);  //Give 5 seconds delay to read.

}
