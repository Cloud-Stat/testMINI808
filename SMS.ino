boolean sendSMS(String phone, String message){
  mySerial.print("\r");
  delay(1000);                    //Wait for a second while the modem sends an "OK"
  mySerial.print("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
  delay(1000);
  mySerial.print("AT+CMGS=\"+");mySerial.print(phone);mySerial.print("\"\r");    //Start accepting the text for the message
  //to be sent to the number specified.
  //Replace this number with the target mobile number.
  delay(1000);
  mySerial.print(message);mySerial.print("\r");   //The text for the message
  delay(1000);
  mySerial.write(0x1A);  //Equivalent to sending Ctrl+Z 
}
