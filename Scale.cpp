////////////////////////////// Chương trình cân chỉnh 5 mắt cảm biến dò line bằng nút nhấn //////////////////////////////
#include "Scale.h"


void scaleMode(){
  byte count = 0;
  unsigned int startPress = 65535, holdSecond = 2, repeatADC = 10, sum=0, analogVal[5], blackResult[5], whiteResult[5];
  bool currentBtnState = 0, lastBtnState = 0, eventConfirmed = 0;
  while(1) {
    currentBtnState = digitalRead(btnScale); // mostly 0
    if (currentBtnState != lastBtnState){
      delay(10);
      if (currentBtnState != lastBtnState){
        if (currentBtnState == 1) startPress = millis()/1000;
        // pressed and release
        else {
          if ((millis()/1000 - startPress) < holdSecond)
            if (count%2) count+=2;
            else ++count;
            if (count == 11 ) break;
            eventConfirmed = false;
            startPress = 65535;
        }
        lastBtnState = currentBtnState;
      }
    }
    // pressed and hold
    if ((millis()/1000 - startPress) == holdSecond){
      eventConfirmed = true;
      startPress = 65535;
    }

    if (millis()/1000 - startPress == 5) break;

    switch (count){
      case 0:
        Serial.println("**********************************");
        delay(500);
        Serial.println("*         Welcome Screen         *");
        delay(500);
        Serial.println("*                                *");
        delay(500);
        Serial.println("*    !!! Release Scale Button    *");
        delay(500);
        Serial.println("*          SCALING MODE          *");
        delay(500);
        Serial.println("*                                *");
        delay(500);
        Serial.println("*            UTC-HCMC            *");
        delay(500);
        Serial.println("**********************************");
        delay(500);
        ++count;
        break;
      case 1:
        // S1 line TRANG
        Serial.print("S1 TRANG: ");
        Serial.println(analogRead(sensorS1));
        delay(300);

        if (eventConfirmed){
          eventConfirmed = false;
          sum = 0 ; //reset var
          
          for (byte i=0; i<repeatADC; i++){
            analogVal[i] = analogRead(sensorS1);
            sum += analogVal[i];
            delay(10);
          }
          Serial.print("CONFIRMED S1 TRANG: ");
          whiteResult[0] = sum/repeatADC;
          Serial.println(whiteResult[0]);
          
          ++count;
        }
        break;
        
      case 2:
        // S1 line DEN
        Serial.print("S1 DEN: ");
        Serial.println(analogRead(sensorS1));
        delay(300);

        if (eventConfirmed){
          eventConfirmed = false;
          sum = 0 ; //reset var
          
          for (byte i=0; i<repeatADC; i++){
            analogVal[i] = analogRead(sensorS1);
            sum += analogVal[i];
            delay(10);
          }
          Serial.print("CONFIRMED S1 DEN: ");
          blackResult[0] = sum/repeatADC;
          Serial.println(blackResult[0]);

          // address: 0, arrIndex: 0, value: average S1
          finalResult[0] = (blackResult[0] + whiteResult[0]) / 2;
          EEPROMWriteInt(0, finalResult[0]);
          
          ++count;
        }
        break;
        
      case 3:
        // S2 line TRANG
        Serial.print("S2 TRANG: ");
        Serial.println(analogRead(sensorS2));
        delay(300);

        if (eventConfirmed){
          eventConfirmed = false;
          sum = 0 ; //reset var
          
          for (byte i=0; i<repeatADC; i++){
            analogVal[i] = analogRead(sensorS2);
            sum += analogVal[i];
            delay(10);
          }
          Serial.print("CONFIRMED S2 TRANG: ");
          whiteResult[1] = sum/repeatADC;
          Serial.println(whiteResult[1]);
          
          ++count;
        }
        break;

      case 4:
        // S2 line DEN
        Serial.print("S2 DEN: ");
        Serial.println(analogRead(sensorS2));
        delay(300);

        if (eventConfirmed){
          eventConfirmed = false;
          sum = 0 ; //reset var
          
          for (byte i=0; i<repeatADC; i++){
            analogVal[i] = analogRead(sensorS2);
            sum += analogVal[i];
            delay(10);
          }
          Serial.print("CONFIRMED S2 DEN: ");
          blackResult[1] = sum/repeatADC;
          Serial.println(blackResult[1]);

          // address: 1, arrIndex: 1, value: average S2
          finalResult[1] = (blackResult[1] + whiteResult[1]) / 2;
          EEPROMWriteInt(2, finalResult[1]);
          
          ++count;
        }
        break;

      case 5:
        // S3 line TRANG
        Serial.print("S3 TRANG: ");
        Serial.println(analogRead(sensorS3));
        delay(300);

        if (eventConfirmed){
          eventConfirmed = false;
          sum = 0 ; //reset var
          
          for (byte i=0; i<repeatADC; i++){
            analogVal[i] = analogRead(sensorS3);
            sum += analogVal[i];
            delay(10);
          }
          Serial.print("CONFIRMED S3 TRANG: ");
          whiteResult[2] = sum/repeatADC;
          Serial.println(whiteResult[2]);
          
          ++count;
        }
        break;

      case 6:
        // S3 line DEN
        Serial.print("S3 DEN: ");
        Serial.println(analogRead(sensorS3));
        delay(300);

        if (eventConfirmed){
          eventConfirmed = false;
          sum = 0 ; //reset var
          
          for (byte i=0; i<repeatADC; i++){
            analogVal[i] = analogRead(sensorS3);
            sum += analogVal[i];
            delay(10);
          }
          Serial.print("CONFIRMED S3 DEN: ");
          blackResult[2] = sum/repeatADC;
          Serial.println(blackResult[2]);

          // address: 2, arrIndex: 2, value: average S3
          finalResult[2] = (blackResult[2] + whiteResult[2]) / 2;
          EEPROMWriteInt(4, finalResult[2]);
          
          ++count;
        }
        break;
        
      case 7:
        // S4 line TRANG
        Serial.print("S4 TRANG: ");
        Serial.println(analogRead(sensorS4));
        delay(300);

        if (eventConfirmed){
          eventConfirmed = false;
          sum = 0 ; //reset var
          
          for (byte i=0; i<repeatADC; i++){
            analogVal[i] = analogRead(sensorS4);
            sum += analogVal[i];
            delay(10);
          }
          Serial.print("CONFIRMED S4 TRANG: ");
          whiteResult[3] = sum/repeatADC;
          Serial.println(whiteResult[3]);
          
          ++count;
        }
        break;

      case 8:
        // S4 line DEN
        Serial.print("S4 DEN: ");
        Serial.println(analogRead(sensorS4));
        delay(300);

        if (eventConfirmed){
          eventConfirmed = false;
          sum = 0 ; //reset var
          
          for (byte i=0; i<repeatADC; i++){
            analogVal[i] = analogRead(sensorS4);
            sum += analogVal[i];
            delay(10);
          }
          Serial.print("CONFIRMED S4 DEN: ");
          blackResult[3] = sum/repeatADC;
          Serial.println(blackResult[3]);

          // address: 3, arrIndex: 3, value: average S4
          finalResult[3] = (blackResult[3] + whiteResult[3]) / 2;
          EEPROMWriteInt(6, finalResult[3]);
          
          ++count;
        }
        break;

      case 9:
        // S5 line TRANG
        Serial.print("S5 TRANG: ");
        Serial.println(analogRead(sensorS5));
        delay(300);

        if (eventConfirmed){
          eventConfirmed = false;
          sum = 0 ; //reset var
          
          for (byte i=0; i<repeatADC; i++){
            analogVal[i] = analogRead(sensorS5);
            sum += analogVal[i];
            delay(10);
          }
          Serial.print("CONFIRMED S5 TRANG: ");
          whiteResult[4] = sum/repeatADC;
          Serial.println(whiteResult[4]);
          
          ++count;
        }
        break;

      case 10:
        // S5 line DEN
        Serial.print("S5 DEN: ");
        Serial.println(analogRead(sensorS5));
        delay(300);

        if (eventConfirmed){
          eventConfirmed = false;
          sum = 0 ; //reset var
          
          for (byte i=0; i<repeatADC; i++){
            analogVal[i] = analogRead(sensorS5);
            sum += analogVal[i];
            delay(10);
          }
          Serial.print("CONFIRMED S5 DEN: ");
          blackResult[4] = sum/repeatADC;
          Serial.println(blackResult[4]);

          // address: 4, arrIndex: 4, value: average S5
          finalResult[4] = (blackResult[4] + whiteResult[4]) / 2;
          EEPROMWriteInt(8, finalResult[4]);
          
          ++count;
        }
        break;
    }
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
