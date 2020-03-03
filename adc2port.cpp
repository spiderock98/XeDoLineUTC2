#include "adc2port.h"


// Hàm mô hình hoá dữ liệu ADC sang mã nhị phân 5-bit
byte adc2port(){
  //  -> 0 LINE Trang       -> 1 LINE Den  //
  
  byte port = 0;
  
  port <<= 1;
  if (analogRead(sensorS1) > finalResult[0]) port |= 1;
  else port |= 0;

  port <<= 1;
  if (analogRead(sensorS2) > finalResult[1]) port |= 1;
  else port |= 0;

  port <<= 1;
  if (analogRead(sensorS3) > finalResult[2]) port |= 1;
  else port |= 0;

  port <<= 1;
  if (analogRead(sensorS4) > finalResult[3]) port |= 1;
  else port |= 0;

  port <<= 1;
  if (analogRead(sensorS5) > finalResult[4]) port |= 1;
  else port |= 0;

  return port;
}
