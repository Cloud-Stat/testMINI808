void setgps(void){
   Serial.println("Setting up GPS...");
   //Enable GPS  
   Serial.print(sendData( "AT+CGNSPWR=1",1000,DEBUG));
   //gps reset HOT
   Serial.print(sendData( "AT+CGPSRST=1",1000,DEBUG));  
   //Send data received from GNSS to AT UART 
   Serial.print(sendData( "AT+CGNSTST=1",1000,DEBUG)); 
   //Define the last NMEA sentence that parsed 
   //Serial.print(sendData( "AT+CGNSSEQ=RMC",1000,DEBUG)); 
   //Enable NMEA $CPGGA data output  
   Serial.print(sendData( "AT+CGPSOUT=98",1000,DEBUG));
   Serial.println("GPS setup ready");
}

void getGPS(){
  queryGPS=true;
  sendData( "AT+CGNSINF",1000,DEBUG);
  queryGPS=false;
   if (gps.location.isUpdated()){
    Serial.print(" LATITUDE="); Serial.print(gps.location.lat(), 6);
    Serial.print(" LONGITUDE="); Serial.print(gps.location.lng(), 6);
    Serial.print(" SPEED=");Serial.print(gps.speed.kmph());Serial.print(" km/h"); // Speed in kilometers per hour (double)
    Serial.print(" HDOP=");Serial.print(float(gps.hdop.value())/100);Serial.print(" m"); 
    Serial.print(" SAT=");Serial.println(gps.satellites.value());
  }else {
    displayInfo();
  }   
}
