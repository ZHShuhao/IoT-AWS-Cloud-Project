#include <Arduino.h>
#include <AWS_IOT.h>
#include <WiFi.h>
#include <Wire.h>
#include "heltec.h"



AWS_IOT hornbill;

/**********************************************  WIFI Client 注意编译时要设置此值 *********************************
 * wifi client
 */

// const char* ssid = "211211"; //replace "xxxxxx" with your WIFI's ssid
// const char* password = "123211456"; //replace "xxxxxx" with your WIFI's password

char WIFI_SSID[]="Shuhao's Galaxy Z Fold3 5G";  //Shuhao's Galaxy Z Fold3 5G
char WIFI_PASSWORD[]="sils7884";    //sils7884
char HOST_ADDRESS[]="a2wfga7d77qb9w-ats.iot.us-east-2.amazonaws.com";
char CLIENT_ID[]= "LoRa_board";
char TOPIC_NAME[]= "Topic/env_data";

int status = WL_IDLE_STATUS;
int tick=0,msgCount=0,msgReceived = 0;
char payload[512];
char rcvdPayload[512];

void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
    strncpy(rcvdPayload,payLoad,payloadLen);
    rcvdPayload[payloadLen] = 0;
    msgReceived = 1;
}



void setup() {
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
    pinMode(25, OUTPUT);
    digitalWrite(25,HIGH);
    Heltec.display->clear();
    Serial.begin(115200);
    delay(2000);

    while (status != WL_CONNECTED)
    {
        Serial.print("Connect to SSID: ");
        Heltec.display->drawString(0,0,String("Connect to SSID: "));
        Serial.println(WIFI_SSID);
        Heltec.display->drawString(0,10,String(WIFI_SSID));
        Heltec.display->display();
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        // wait 5 seconds for connection:
        delay(5000);
    }

    Serial.println("Connected to wifi");
    Heltec.display->drawString(0,20,"Connected to wifi");
    Heltec.display->display();

    if(hornbill.connect(HOST_ADDRESS,CLIENT_ID)== 0)
    {
        Heltec.display->clear();
        Serial.println("Connected to AWS successfully!");
        Heltec.display->drawString(0,0,String("Connected to AWS successfully!"));
        Heltec.display->display();
        delay(3000);
        
        Heltec.display->clear();

        if(0==hornbill.subscribe(TOPIC_NAME,mySubCallBackHandler))
        {
            Heltec.display->drawString(0,0,String("Subscribe Successfull"));
            Heltec.display->drawString(0,10,String(TOPIC_NAME));
            // Heltec.display->drawString(0,30,String("Temperature:"));
            // Heltec.display->drawString(0,40,String("Humidity:"));
            Heltec.display->display();
            Serial.println("Subscribe Successfull");
        }
        else
        {  
            Heltec.display->drawString(0,0,String("Subscribe Failed, Check the Thing Name and Certificates"));
            Heltec.display->display();
            Serial.println("Subscribe Failed, Check the Thing Name and Certificates");
            while(1);
        }
    }
    else
    {   
        Heltec.display->drawString(0,0,String("AWS connection failed, Check the HOST Address"));
        Heltec.display->display();
        Serial.println("AWS connection failed, Check the HOST Address");
        while(1);
    }

    delay(5000);

    digitalWrite(25, LOW);

}

void loop() {

    if(msgReceived == 1)
    {
       // Code for LoRa_1 board to get message from ioT device
        msgReceived = 0;
        Heltec.display->clear();
        Heltec.display->drawString(0,0,String("Subscribe Successfull"));
        Heltec.display->drawString(0,10,String(TOPIC_NAME));
        Heltec.display->drawString(0,30,String("Received Message:"));
        Heltec.display->drawString(0,40,String(rcvdPayload));
        Heltec.display->display();
        Serial.print("Received Message:");
        Serial.println(rcvdPayload);
         digitalWrite(25, HIGH);   // turn the LED on (HIGH is the voltage level)
         delay(200);                       // wait for a second
         digitalWrite(25, LOW);
         delay(300);
    }
}