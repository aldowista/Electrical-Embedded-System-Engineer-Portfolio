void saveDataSDCard(){
   //Send data to SD Card
  if(dtATMega == 0){
    dtSDCard = "Motor OFF"
    }
  else if (dtATMega == 1){
    dtSDCard = "Motor ON dengan variasi kecepatan 1"
    }
  else if (dtATMega == 2){
    dtSDCard = "Motor N dengan variasi kecepatan 2"
    }
  else if (dtATMega == 3){
    dtSDCard = "Motor N dengan variasi kecepatan 3"
    }

    
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    myFile.println(dtSDCard);
    myFile.close();
  }
  else {
    Serial.println("error opening test.txt");
  }
  }
