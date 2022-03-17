#include <ArduinoJson.h>
#include <RTClib.h>


RTC_DS3231 rtc1;

//CReate Dynamic Json lenght 1024
DynamicJsonDocument doc(1024);
//DynamicJsonDocument doc1(2048);
DynamicJsonDocument doc1(1024);
int year;
int month;
int day;
int hour;
int minute;
int second;

int ciclos;
String startHour;
String fishHour;
String timeOn;
String timeOff;

void TimeClock(){
    
    year   = doc1["Fecha"][0].as<String>().toInt();
    month  = doc1["Fecha"][1].as<String>().toInt();
    day    = doc1["Fecha"][2].as<String>().toInt();
    hour   = doc1["Hora"][0].as<String>().toInt();
    minute = doc1["Hora"][1].as<String>().toInt();
    second = doc1["Hora"][2].as<String>().toInt();

 }

 void DataWork(){
    
    ciclos = doc1["Ciclos"].as<String>().toInt(); 
    String h;

    for (int i=0; i<ciclos; i++) {
        
        String tStart = doc1["Hora Inicio"][i].as<String>();
        int hStart =tStart.substring(0,2).toInt();
        int mStart =tStart.substring(3,5).toInt();
        

        String tFinish = doc1["Hora Final"][i].as<String>();
        int hFinish =tFinish.substring(0,2).toInt();
        int mFinish=tFinish.substring(3,5).toInt();

        int tOn = doc1["Tiempo Encendido"][i].as<String>().toInt();
        int tOff = doc1["Tiempo Apagado"][i].as<String>().toInt();
        
        int nveces = ((hFinish - hStart)*60 + (mFinish - mStart))/tOff;
        
        /*Serial.print(hStart);
        Serial.print(" ");
        Serial.print(hFinish);
        Serial.print(" - ");
        Serial.print(tOn);
        Serial.print(" ");
        Serial.print(tOff);
        Serial.print(" / ");
        Serial.println(nveces);
        */
       int hora =hStart;
       int minutos =mStart;

       for(int j=0; j<nveces; j++){

           int sMinutes = minutos + tOff;

           if(sMinutes<60){
               minutos = sMinutes;
           }else if (sMinutes == 60){
               hora+=1;
               minutos = 0;
           }else{
               hora+=1;
               minutos = sMinutes-60;
           }
           h+=String(i+1)+"/"+String(hora)+":"+String(minutos)+":00"+"/"+String(tOn)+"\n";
           //h=String(i+1)+"/"+String(hora)+":"+String(minutos)+":00"+"/"+String(tOn)+"\n";
           

           //appendFile(SD, "/hello.txt",  "hola");
           //Serial.println(String(hora)+"-"+String(minutos));
        
       }
       
        //Serial.println(h);
        
    }
    Serial.println(h);
   
    
 }







    