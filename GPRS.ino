char aux_str[100];

void setAPN(){
  Serial.println("Set APN");
  while (sendATcommand2("AT+CREG?", "+CREG: 0,1", "+CREG: 0,5", 2000) == 0);
  // sets APN , user name and password
  sendATcommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"", "OK", 2000);
  snprintf(aux_str, sizeof(aux_str), "AT+SAPBR=3,1,\"APN\",\"%s\"", apn);
  sendATcommand(aux_str, "OK", 2000);
  
  snprintf(aux_str, sizeof(aux_str), "AT+SAPBR=3,1,\"USER\",\"%s\"", user_name);
  sendATcommand(aux_str, "OK", 2000);
  
  snprintf(aux_str, sizeof(aux_str), "AT+SAPBR=3,1,\"PWD\",\"%s\"", password);
  sendATcommand(aux_str, "OK", 2000);

  while (sendATcommand("AT+SAPBR=1,1", "OK", 20000) == 0)
  {
      delay(5000);
  }
  
}

int8_t sendATcommand(char* ATcommand, char* expected_answer1, unsigned int timeout){
    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;
    memset(response, '\0', 100);    // Initialize the string
    delay(100);
    while( mySerial.available() > 0) mySerial.read();    // Clean the input buffer
    mySerial.println(ATcommand);    // Send the AT command 
    x = 0;
    previous = millis();
    // this loop waits for the answer
    do{
        if(mySerial.available() != 0){    
            response[x] = Serial.read();
            x++;
            // check if the desired answer is in the response of the module
            if (strstr(response, expected_answer1) != NULL)    
            {
                answer = 1;
            }
        }
        // Waits for the asnwer with time out
    }
    while((answer == 0) && ((millis() - previous) < timeout));    

    return answer;
}



int8_t sendATcommand2(char* ATcommand, char* expected_answer1, char* expected_answer2, unsigned int timeout){
    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;
    memset(response, '\0', 100);    // Initialize the string
    delay(100);
    while( mySerial.available() > 0) mySerial.read();    // Clean the input buffer
    mySerial.println(ATcommand);    // Send the AT command 
        x = 0;
    previous = millis();
    // this loop waits for the answer
    do{        
        if(mySerial.available() != 0){    
            response[x] = mySerial.read();
            x++;
            // check if the desired answer 1 is in the response of the module
            if (strstr(response, expected_answer1) != NULL)    
            {
                answer = 1;
            }
            // check if the desired answer 2 is in the response of the module
            if (strstr(response, expected_answer2) != NULL)    
            {
                answer = 2;
            }
        }
        // Waits for the asnwer with time out
    }while((answer == 0) && ((millis() - previous) < timeout));    

    return answer;
}
