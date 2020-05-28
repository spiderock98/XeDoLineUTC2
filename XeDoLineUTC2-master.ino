//  Host: Trường Đại học Giao Thông Vận Tải - Phân hiệu tại TP. Hồ Chí Minh
//  Website: https://utc2.edu.vn/
//  Website tuyển sinh: http://tuyensinh.utc2.edu.vn/
//  Website bộ môn điện-điện tử: http://dept.utc2.edu.vn/bomondientu/

#include "Scale.h"
#include "EEPRomInt.h"
#include "adc2port.h"
#include "pinConfig.h"

unsigned int finalResult[5];

////////////// thay đổi 4 thông số sau để cải thiện tốc độ động cơ //////////////
const int defaultValue = 60;                                                   //
const int plusLevel1 = 90;                                                     //
const int plusLevel2 = 100;                                                    //
const int minusLevel1 = 40;                                                    //
//////////////////////////////////////////////////// ////////////////////////////

// biến dùng để tự động chọn chương trình rẽ TRÁI/PHẢI tuỳ theo sa hình
// leftScript = 0 : rẽ PHẢI
// leftScript = 1 : rẽ TRÁI
bool leftScript = 0;

////////////////////////////// Hàm Điều Khiển Động Cơ //////////////////////////////
// hàm đánh lái sang PHẢI CẤP 2
void onLeft2()
{
  analogWrite(leftmotor, minusLevel1);
  analogWrite(rightmotor, plusLevel2);
}
// hàm đánh lái sang PHẢI CẤP 1
void onLeft1()
{
  analogWrite(leftmotor, minusLevel1);
  analogWrite(rightmotor, plusLevel1);
}
// hàm đi THẲNG
void onStraight()
{
  analogWrite(rightmotor, defaultValue);
  analogWrite(leftmotor, defaultValue);
}
// hàm đánh lái sang TRÁI CẤP 1
void onRight1()
{
  analogWrite(rightmotor, minusLevel1);
  analogWrite(leftmotor, plusLevel1);
}
// hàm đánh lái sang TRÁI CẤP 2
void onRight2()
{
  analogWrite(rightmotor, minusLevel1);
  analogWrite(leftmotor, plusLevel2);
}
// hàm DỪNG cả hai động cơ
void onStop()
{
  digitalWrite(rightmotor, 0);
  digitalWrite(leftmotor, 0);
}
///////////////////////////////////////////////////////////////////////////

// hàm rẽ TRÁI (> 90*)
void turnLeft()
{
  while ((adc2port() & B00010) != 0)
  {
    analogWrite(rightmotor, 50);
    digitalWrite(leftmotor, 0);
  }
  onStop();
}
// hàm rẽ PHẢI (> 90*)
void turnRight()
{
  while ((adc2port() & B01000) != 0)
  {
    analogWrite(leftmotor, 50);
    digitalWrite(rightmotor, 0);
  }
  onStop();
}
// hàm xử lý NGÃ TƯ
void crossRoad()
{
  do
  {
    onStraight();
    delay(2);
  } while (((adc2port() == B11011) || (adc2port() == B10111) || (adc2port() == B11101)) == false);
}
// hàm dò line và cân bằng xe theo line dựa trên các sự kiện thu được từ 5 cảm biến
void followLine()
{
  byte port;
  while (1)
  {
    //  -> 0 LINE Trang       -> 1 LINE Den //
    port = adc2port();

    if (port == B10111)
      onLeft1();
    else if ((port == B11011) || (port == B11111))
      onStraight();
    else if (port == B11101)
      onRight1();

    else if ((port & B00001) == 0)
    {
      leftScript = 0; // tự động rẽ PHẢI
      onStop();
      break;
    }
    else if ((port & B10000) == 0)
    {
      leftScript = 1; // tự động rẽ TRÁI
      onStop();
      break;
    }
  }
}

// hàm MAIN(): toàn bộ chương trình bắt đầu từ đây
void setup()
{
  Serial.begin(115200);
  pinMode(btnScale, INPUT_PULLUP);
  pinMode(ledStart, INPUT);
  pinMode(rightmotor, OUTPUT);
  pinMode(leftmotor, OUTPUT);

  // init value from eeprom to array
  for (byte i = 0; i < 10; i += 2)
    finalResult[i / 2] = EEPROMReadInt(i);

  if (digitalRead(btnScale))
    scaleMode(); // loop here

  for (byte i = 0; i < 10; i += 2)
    Serial.println(EEPROMReadInt(i));

  while (!digitalRead(ledStart))
    ; // waiting for start signal IRLed

  // danh sách các kịch bản để xe đi hết sa hình
  followLine();
  if (leftScript)
    turnLeft();
  else
    turnRight();
  followLine();
  crossRoad();
  followLine();
  if (leftScript)
    turnLeft();
  else
    turnRight();
  followLine();
}
void loop() {}
