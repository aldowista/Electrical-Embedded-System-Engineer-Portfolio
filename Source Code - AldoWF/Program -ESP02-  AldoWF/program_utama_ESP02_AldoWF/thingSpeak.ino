void thingSpeak(){
    //Send Data to ThingSpeak
  int x = ThingSpeak.writeField(myChannelNumber, 1, dtATMega, myWriteAPIKey);
    // Check the return code
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  number++;
  if(number > 99){
    number = 0;
  }
  delay(20000); // Wait 20 seconds before sending a new value
  }
