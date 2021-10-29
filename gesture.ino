 a#include <SparkFun_APDS9960.h>
#include <PubSubSslClient.h>
#include <DateTimeLibrary.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <driverlib/timer.h>

#include "config.h"
#define APDS9960_INT    2 // Needs to be an interrupt pin
time_t   myEpochRTC;
boolean isConnected;
boolean timeSetFromNtp;

WiFiClient client;
PubSubSslClient mqttClient(client);
DateTime myRTC;
SparkFun_APDS9960 apds = SparkFun_APDS9960();
int isr_flag = 0;
char DATA_RIGHT[] = "{\"gesture\":\"RIGHT\"}";
char DATA_LEFT[] = "{\"gesture\":\"LEFT\"}";
char DATA_FAR[] = "{\"gesture\":\"FAR\"}";



/* *****************************************************************
 * Callback for MQTT and Interrupt
 * *****************************************************************/
void callback(char* topic, byte* payload, unsigned int length) 
{
  // We are only interested in one topic
  if(strcmp(topic, "sensor/cc3200/cmd") != 0)
    return;
  
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) 
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  
} 
/////////////////////
void handleGesture() {
    if ( apds.isGestureAvailable() ) {
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        mqttClient.publish("sensor/cc3200/cmd", DATA_FAR);
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        mqttClient.publish("sensor/cc3200/cmd", DATA_LEFT);
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        mqttClient.publish("sensor/cc3200/cmd", DATA_RIGHT);
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        mqttClient.publish("sensor/cc3200/cmd", DATA_FAR);
        break;
      case DIR_FAR:
        Serial.println("FAR");
        mqttClient.publish("sensor/cc3200/cmd", DATA_FAR);
        break;
      default:
        Serial.println("NONE");
        mqttClient.publish("sensor/cc3200/cmd", DATA_FAR);
    }
  }
}

void interruptRoutine() {
  isr_flag = 1;
}

/* *****************************************************************
 * Mainloop
 * *****************************************************************/
void loop() {     
  
    mqttClient.loop();
/////////////////////////////////////////////////////////////////////  
    if( isr_flag == 1 ) {
    detachInterrupt(2);
    handleGesture();
    isr_flag = 0;
    attachInterrupt(2, interruptRoutine, FALLING);
  }
////////////////////////////////////////////////////////////////////////
    //Serial.println("Disconnecting from MQTT...");
    //mqttClient.disconnect();
    
  

  
}
