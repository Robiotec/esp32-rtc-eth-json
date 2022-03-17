/*
   ****************************** NetBell Fargo R4  *******************************
   ******************** Ethernet&RTC Communication With ESP32  ********************
   By: Yandri J. Uchuari
   Reviewed: XXXXXXXXXX
   More information: https://acortar.link/zQRwKJ
   Repository:
   Created : 15/02/2022 
   Version: v5.0  -> 24/02/2022
   Platafor: Platformio.io
   Framework: Arduino
*/

//Libraries
#include <Arduino.h>
#include <SPI.h>
#include "Ethernet_Config.h"
#include "RTC_Config.h"
#include "DataJson.h"
#include "HTTPRespond.h"
#include "SDCard.h"


#define LED 2

 
void setup () {
  pinMode(LED, OUTPUT);
 

  //Starting conmmunication for Serial port
  Serial.begin(115200);
  //Verify the communication for RTC module
  RctVerify();
  //Start the commnication with of Ethernet Module (Define GPIO 5) for this case
  initEthernet(5);
  //Reset the Ethernet module
  WizReset();
  //Starting ETHERNET connection
  beginEthernet();
  //Sanity checks for W5500 and cable connection.
  CheckConnection();
  //Server Listening for communication
  //server.begin();
   
}


void loop () {
  
  //Ceate a Client for communication HTTP
  client = server.available();
  //Serial.write(client);
  //client.setTimeout(1000);

  //Get the time the RTC module  
  DateTime now = rtc.now();
  String time_clock = String(now.year(), DEC) + '/' + String(now.month(), DEC) + '/' + String(now.day(), DEC) + " " + String(now.hour(), DEC) + ':' + String(now.minute(), DEC) + ':' + String(now.second(), DEC);
  
  //Create Json for Time
  doc["Fecha"][0] = String(now.year(), DEC);
  doc["Fecha"][1] = String(now.month(), DEC);
  doc["Fecha"][2] = String(now.day(), DEC);
  doc["Hora"][0] = String(now.hour(), DEC);
  doc["Hora"][1] = String(now.minute(), DEC);
  doc["Hora"][2] = String(now.second(), DEC);
  
  if(client){
    String requestType = client.readStringUntil(' ');
    String requestUrl = client.readStringUntil(' ');
    String requestVersion = client.readStringUntil('\n');
    String response;

    if(requestType=="POST"){

      String data = client.readString();
      
      Serial.println("process POST");
      Serial.print("Request URL: ");
      Serial.println(requestUrl);

      if (requestUrl == "/data"){
      
        
        client.println(F("HTTP/1.0 201 OK"));
        client.println(F("Content-Type: application/json"));
        client.println("Connection: close");
        client.println();
        
        //String datos = data.substring(235,-1);
        int indice = data.indexOf('{');
        String json = data.substring(indice, -1);
        //Serial.println(json);
        DeserializationError error = deserializeJson(doc1, json);
        Serial.println(error.c_str());

        
        TimeClock();
        RTCAdjst(year,month,day,hour,minute,second);
        DataWork();

        


        /*
        digitalWrite(LED,HIGH);
        delay(3000);
        digitalWrite(LED, 0x0);*/
        
      
      }else{
        response = create404();
      }
      

    }else if(requestType=="GET"){
      //Serial.println(client.readString());
      Serial.println("process GET");
      Serial.print("Request URL: ");
      Serial.println(requestUrl);
      if (requestUrl == "/info"){

        // Write response headers
        client.println(F("HTTP/1.0 200 OK"));
        client.println(F("Content-Type: application/json"));
        client.println(F("Connection: close"));
        client.print(F("Content-Length: "));
        client.println(measureJsonPretty(doc));
        client.println();
        // Write JSON document
        serializeJsonPretty(doc, client);

        iniciarSD();

      }else{
        response = create404();
      }
      
    }else{
      response = create404();
    }
  //sendResponse(response, client);

  client.stop();
  Serial.println("Client Disonnected");
  }  
  Serial.println(time_clock);
  delay(500);
}

