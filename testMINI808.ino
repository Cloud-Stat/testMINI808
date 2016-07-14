#include <SoftwareSerial.h>
#include<stdio.h>
#include<string.h>
#include <TinyGPS++.h>

#define DEBUG true

SoftwareSerial mySerial(10,11); 
TinyGPSPlus gps;

boolean queryGPS = false;

//char pin[]="*******";
char apn[]="prepago.ancel";
char user_name[]="bam";
char password[]="bam";

long bauds = 38400;
        
void setup(){
  Serial.begin(115200);
  /*mySerial.begin(9600); 
  Serial.println(sendData( "AT+IPR=38400",1000,DEBUG));
  delay(5000);*/
  mySerial.begin(bauds);
  Serial.println("Serial ready");
  setgps();
  //setAPN();
  Serial.println("\n --------APN READY--------");
}

void loop(){ 
  getGPS();
  delay(10);
}

String sendData(String command, const int timeout, boolean debug){
    /*Read software serial (SIM808) and print it on Serial monitor (if debug is on)
      It can also pass received string to caller.*/
    String response = "";    
    mySerial.println(command); 
    long int time = millis();   
    while( (time+timeout) > millis()){
      while(mySerial.available()){       
        char c = mySerial.read(); 
        if (queryGPS==true)
          gps.encode(c);
        response+=c;
      }  
    }    
    if(true){
      Serial.print(response);
    }    
    return response;
}


