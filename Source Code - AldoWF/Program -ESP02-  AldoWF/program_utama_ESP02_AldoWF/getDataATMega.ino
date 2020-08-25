void getDataATMega(){
   //Get data from ATMega
 if(Serial.available()>0)    //Checks is there any data in buffer 
  {
    Serial.print("Data :");
    dtATMega = Serial.read();
    Serial.print(char(Serial.read()));  //Read serial data byte and send back to serial monitor
  }
  else
  {
    Serial.println("No Data"); 
    delay(1000);                      // Wait for a second
  }
  }
