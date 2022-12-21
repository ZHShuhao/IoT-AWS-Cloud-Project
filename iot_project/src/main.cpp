// #include <Arduino.h>
// #include <AWS_IOT.h>
// #include <WiFi.h>
// #include <Wire.h>

// #include "DHT.h"
// #include "DHT_U.h"
// #include "heltec.h"

#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>



#include <Arduino.h>
#include <AWS_IOT.h>
#include <SPI.h>
#include <WiFi.h>
#include <Wire.h>

#include <NTPClient.h>

#include "DHT.h"
#include "DHT_U.h"
#include "heltec.h" 

#define BAND    433E6

#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define DHTPIN 13

DHT dht(DHTPIN, DHTTYPE);
AWS_IOT hornbill;

// connect to iot WIFI
char WIFI_SSID[]="Shuhao's Galaxy Z Fold3 5G";  //Shuhao's Galaxy Z Fold3 5G
char WIFI_PASSWORD[]="sils7884";    //sils7884
char HOST_ADDRESS[]="a2wfga7d77qb9w-ats.iot.us-east-2.amazonaws.com";
char CLIENT_ID[]= "LoRa_board";
char TOPIC_NAME[]= "node_1";

int status = WL_IDLE_STATUS;
int tick=0,msgCount=0,msgReceived = 0;
char pubPayLoad[512];
char payload[512];
char rcvdPayload[512];

void mySubCallBackHandler (char *topicName, int payloadLen, char *payLoad)
{
    strncpy(rcvdPayload,payLoad,payloadLen);
    rcvdPayload[payloadLen] = 0;
    msgReceived = 1;
}


byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(192,168,42,179);  // IP of the MySQL *server* here
char user[] = "root";              // MySQL user login username
char password[] = "admin";        // MySQL user login password

//char INSERT_SQL[] = "INSERT INTO  iot_data.t_h_data VALUES ('5.12','9.55')";
//char INSERT_SQL[] = "INSERT INTO  iot_data.t_h_data (Temperature,Humidity,NowTime) VALUES (%2f,%2f,%A)";
char INSERT_SQL[] = "INSERT INTO  iot_data.t_h_data_2 (DATA_TEM,DATA_HUM,NowTime) VALUES (%2f,%2f,'%s')";
char buff[128];

// WiFi card example
// char ssid[] = "Shuhao's Galaxy Z Fold3 5G";    // your SSID
// char pass[] = "sils7884";       // your SSID Password


String timer;
WiFiClient client_mysql;            // Use this for WiFi instead of EthernetClient
MySQL_Connection conn((Client *)&client_mysql);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com",60*60*8, 30*60*1000);

void setup() {
 // initial port
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  
  //initial ESP32 board
    Heltec.begin(true /*DisplayEnable Enable*/, true /*LoRa Disable*/, true /*Serial Enable*/);
    Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
    pinMode(25, OUTPUT);
    digitalWrite(25,HIGH);
    Heltec.display->clear();
    Serial.begin(9600);
    delay(2000);

    Heltec.display->drawString(0,0,String("DHT_22 task strat:"));
    Heltec.display->display();
    Heltec.display->clear();

      // AWS IOT
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
        Heltec.display->clear();
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
            // Heltec.display->drawString(0,0,String("Subscribe Successfull"));
            // Heltec.display->drawString(0,10,String(TOPIC_NAME));
            // Heltec.display->display();
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

Serial.begin(9600);
while (!Serial); // wait for serial port to connect. Needed for Leonardo only

// Begin WiFi section
while (status != WL_CONNECTED)
    {
        Serial.print("Connect to SSID: ");
        Heltec.display->drawString(0,0,String("Connect to SSID: "));
        Serial.println(WIFI_SSID);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        delay(5000);
    }
// print out info about the connection:

  Serial.println("Connected to network");
  IPAddress ip = WiFi.localIP();
  Serial.print("My IP address is: ");
  Serial.println(ip);

// End WiFi section

 Serial.println("Connecting to SQL...");
 if (conn.connect(server_addr, 3306, user, password)) {
  delay(5000);
 }
 else
 {
  Serial.println("Connection failed.");
  conn.close();
  }
}

void loop() {

    // get Temperature and Humidity form DHT22  
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    Heltec.display->drawString(0,0,String("Failed to read from DHT sensor!"));
    Heltec.display->display();
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
  Heltec.display->drawString(0,0,String("LoRa node 1:"));
  Heltec.display->drawString(0,20,String("Temperature:"));
  Heltec.display->drawString(0,30,String(hif));
  Heltec.display->drawString(30,30,String("°F"));

  Heltec.display->drawString(0,40,String("Humidity:"));
  Heltec.display->drawString(0,50,String(h));
  Heltec.display->drawString(30,50,String("%"));
  Heltec.display->display();

  LoRa.beginPacket();
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print("Temperature:\n");
  LoRa.print(hif);
  LoRa.print("°F    ");
  LoRa.print("Humidity:");
  LoRa.print(h);
  LoRa.print("%");
  LoRa.endPacket();

  Heltec.display->clear();


 //AWS IOT 
 if(msgReceived == 1)
    {
        msgReceived = 0;
        // Serial.print("Received Message:");
        // Serial.println(rcvdPayload);
    }
    if(tick >= 1)   // publish to topic every 1 seconds
    {
        tick=0;
      
        sprintf(payload,"Temputer:%.2f °F\n Humidity:%.2f %%",hif,h);
    
        if(hornbill.publish(TOPIC_NAME,payload) == 0)
        {        
            Serial.print("Publish Message:");
            Serial.println(payload);
        }
        else
        {
            Serial.println("Publish failed");
        }
    }  
    vTaskDelay(1000 / portTICK_RATE_MS); 
    tick++;


  digitalWrite(25, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  digitalWrite(25, LOW);
  delay(300);

  delay(2000);

   timeClient.update();
   timer=timeClient.getFormattedTime();
  //Send data to MYSQL 
  Serial.println("Recording data.");

  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Execute the query
  sprintf(buff,INSERT_SQL,hif,h,timer.c_str());
  cur_mem->execute(buff);
  // Note: since there are no results, we do not need to read any data
  // Deleting the cursor also frees up memory used
  delete cur_mem;
}