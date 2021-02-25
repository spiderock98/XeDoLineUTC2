# Xe Dò Line UTC2 - Đại Học Giao Thông Vận Tải - Phân Hiệu Tại TP.HCM | Mã Tuyển Sinh: GSA

<p align="center">
  <img src="resources/images/utclogo.ico">
</p>

## Phần Mềm Cần Thiết

* Arduino IDE | [Windows](https://downloads.arduino.cc/arduino-1.8.12-windows.exe) | [MacOS](https://downloads.arduino.cc/arduino-1.8.12-macosx.zip) | [Linux](https://downloads.arduino.cc/arduino-1.8.12-linux64.tar.xz)
* Phần mềm giải nén tập tin * *.zip*

## Sơ Đồ Kết Nối Phần Cứng

![schematic](resources/images/schematic.jpg)

## Sân Thi Đấu [PDF](resources/docs/SANTHIDAU_2.pdf) | [CorelDRAW](resources/docs/CHINHTHUC_SANTHIDAU_2.cdr)
**Lưu ý khi in lại sân phải giữ đúng tỉ lệ file gốc**

## Cài đặt và thiết lập

1. Khởi động Arduino IDE lần đầu tiên để cài các driver và thư viện cần thiết

2. Tải xuống mã nguồn đầy đủ của chương trình [tại đây](https://github.com/spiderock98/XeDoLineUTC2/archive/master.zip) ![clone-repo](resources/images/clone-repo.png)

3. Giải nén file *XeDoLineUTC2-master.zip* vừa tải về

4. Khởi động Arduino IDE chọn *File >> Open* và trỏ đường dẫn đến file *[XeDoLineUTC2-master.ino](XeDoLineUTC2-master.ino)* trong thư mục *XeDoLineUTC2-master* vừa xả nén

5. Cắm cáp kết nối ArduinoNano và PC

6. Tại giao diện phần mềm ArduinoIDE. Chọn board:  *Tools >> Board >> **Arduino Nano***

7. Chọn loại vi xử lý: *Tools >> Processor >> **ATmega328P (Old Bootloader)***

8. Chọn cổng giao tiếp: *Tools >> Port >> COMxx* 

9. Nạp chương trình đầu tiên từ PC xuống Arduino: *Sketch >> Upload*

10. Chờ phần mềm báo *Done Uploading* là đã nạp thành công code xuống ArduinoNano
![done-uploading](resources/images/done-upload.png)

## Cân Chỉnh 5 Mắt Cảm Biến Dò Line

```
Chương trình sẽ tự lưu lại các giá trị cảm biến sau khi cân chỉnh và tự động nạp lại trong những lần khởi động kế tiếp
Do đó chỉ cần thực hiện lại quy trình này khi xe có dấu hiệu hay trượt mất line do điều kiện ánh sáng ngoài trời thay đổi
```

### Vào chế độ cân chỉnh
* Tắt nguồn động cơ xe
* Cắm cáp kết nối ArduinoNano và PC
* Nhấn và giữ nút cân chỉnh - (nút nhấn đặt phía trước cảm biến dò line)
* *Vẫn nhấn giữ nút cân chỉnh* đồng thời nhấn vào biểu tượng kính lúp ![magnify-icon](resources/images/magnify-icon.png) ở góc trên bên phải phần mềm ArduinoIDE để bật màn hình Serial Monitor
* Thả nút cân chỉnh khi vào đến màn hình **Welcome Screen**

### Cân chỉnh cảm biến theo sân thi đấu
* Đặt xe vào sân thi đấu
* Quan sát Serial Monitor và làm theo hướng dẫn
* Khi đạt được giá trị cảm biến ổn định thì *nhấn giữ nút cân chỉnh để xác nhận*
* Tiếp tục cân chỉnh cho đến hết cảm biến S5
* Rút cáp kết nối

## FAQs - LƯU Ý QUAN TRỌNG NÈ

* ***KHÔNG ĐƯỢC PHÉP LẮP NGƯỢC CỰC DƯƠNG(+) ÂM(-) CỦA PIN VÀO MẠCH SẠC CŨNG NHƯ MẠCH ĐỘNG CƠ***
* ***PIN NẾU CẮM NGƯỢC CỰC NGAY CẢ KHI CHƯA BẬT NGUỒN CŨNG SẼ GÂY CHÁY NỔ***
* ***SỐ LƯỢNG PIN CÓ HẠN***
* Nếu cắm cáp kết nối Arduino sáng đèn nguồn nhưng không tìm thấy port trong *Tools >> Port >> COMxx* thì tải xuống và cài đặt [Driver mạch nạp CH340C](https://sparks.gogo.co.nz/assets/_site_/downloads/CH34x_Install_Windows_v3_4.zip)
* Nếu cảm biến dò line khi lắp vào có dấu hiệu cong vênh thì dùng kìm bấm linh kiện bấm sát các mối hàn và mắt đọc
* Nếu gặp tình trạng Serial Monitor nhảy ký tự linh tinh hoặc không hiện bất kỳ ký tự nào ![error2](resources/images/err2.png)
thì chỉnh lại **baudrate ở góc phải bên dưới thành 9600** ![error3](resources/images/err3.png)
* Trong quá trình UPLOAD nếu ArduinoIDE ném ra lỗi *An error occureed uploading the sketch* thì chọn *Tools >> Verify/Compile* **NHIỀU LẦN** cho đến khi hết lỗi ![error1](resources/images/error1.jpg)

## Giải Thích Các Hàm
```
void followLine() {
    while (1) {
        ...
        else if ((port & B00001) == 0) { // S5 rơi vào line trắng
          leftScript = 0; // tự động rẽ PHẢI
          onStop();
          break; // thoát khỏi vòng lặp
        }
        else if ((port & B10000) == 0 ){ // S1 rơi vào line trắng
          leftScript = 1; // tự động rẽ TRÁI
          onStop();
          break; // thoát khỏi vòng lặp
        }
    }
}
```
#### Hàm đi line
* gần như xuyên suốt trong chương trình chính
* chương trình chạy vòng lặp
* liên tục bắt các sự kiện để dò theo line
#### Điều kiện thoát vòng lặp - `break`
* **S1** hoặc **S5** nằm trên line trắng. Không quan tâm **S2 S3 S4**
* trước khi thoát kéo cờ `leftScript` lên `0` hoặc `1` để xe tự phân biệt đội A hay đội B

```
if (port==B10111){
  analogWrite(leftmotor, 40);
  analogWrite(rightmotor, 90);
}
```
##### Sự kiện
* đánh lái sang **TRÁI**
* khi **S2** nằm trên line trắng (lệch **PHẢI**)
* đồng thời **S1 S3 S4 S5** nằm trên line đen

```
if (port==B11101){
  analogWrite(rightmotor, 40);
  analogWrite(leftmotor, 90);
}
```
##### Sự kiện
* đánh lái sang **PHẢI**
* khi **S4** nằm trên line trắng (lệch **TRÁI**)
* đồng thời **S1 S2 S3 S5** nằm trên line đen

```
if (port==B11011)
  analogWrite(rightmotor, 50);
  analogWrite(leftmotor, 50);
```
##### Sự kiện
* đi **THẲNG** bằng cách cân bằng 2 động cơ
* khi **S3** nằm trên line trắng. Đồng thời **S1 S2 S4 S5** nằm trên line đen

```
void turnLeft(){
  while ((adc2port() & B00010) != 0){
    analogWrite(rightmotor, 50);
    digitalWrite(leftmotor, 0);
  }
  onStop();
}
```
#### Hàm xử lý ngã ba (rẽ trái)
* động cơ trái dừng, động cơ phải hoạt động
* chương trình chạy vòng lặp
#### Điều kiện thoát vòng lặp - `break`
* động cơ quay đến khi **S4** nằm trong line trắng thì thoát. Không quan tâm **S1 S2 S3 S5**
* sau đó dừng hẳn 2 động cơ `onStop();` 

```
void turnRight(){
  while ((adc2port() & B01000) != 0){
    analogWrite(leftmotor, 50);
    digitalWrite(rightmotor, 0);
  }
  onStop();
}
```
#### Hàm xử lý ngã ba (rẽ phải)
* động cơ phải dừng, động cơ trái hoạt động
* chương trình chạy vòng lặp
#### Điều kiện thoát vòng lặp - `break`
* động cơ quay đến khi **S2** nằm trong line trắng thì thoát. Không quan tâm **S1 S3 S4 S5**
* sau đó dừng hẳn 2 động cơ `onStop();` 

```
void crossRoad(){
  do {
    analogWrite(rightmotor, 50);
    analogWrite(leftmotor, 50);
  } while (adc2port() != B11011);
}
```
#### Hàm xử lý ngã tư
* 2 động cơ quay đều `onStraight();`
* chương trình chạy vòng lặp
#### Điều kiện thoát vòng lặp - `break`
* 2 động cơ xoay đến khi **S3** vào line trắng. Đồng thời **S1 S2 S4 S5** nằm trên line đen

```
Kịch bản mẫu cho ĐỘI XANH
followLine();
turnLeft();
followLine();
crossRoad();
followLine();
turnLeft();
followLine();
```

## Video Hướng Dẫn

### Giới thiệu và hướng dẫn lắp ráp phần cứng
[<img title="" src="http://img.youtube.com/vi/Fn5SZk5CloU/0.jpg" alt="demo2" data-align="center">](http://www.youtube.com/watch?v=Fn5SZk5CloU "Demo 17/04/2020")

### Hướng dẫn cân chỉnh cảm biến
[<img title="" src="http://img.youtube.com/vi/3UzgURIa8rw/0.jpg" alt="demo2" data-align="center">](http://www.youtube.com/watch?v=3UzgURIa8rw "Demo 17/04/2020")

## Một số hình ảnh cuộc thi sáng 07/06/2020

<img src="https://scontent.fsgn5-1.fna.fbcdn.net/v/t1.0-9/101128894_2566647840330890_7250677181091676160_o.jpg?_nc_cat=107&_nc_sid=cdbe9c&_nc_oc=AQk4PpSP-k8rCeH0EHhoaK9tA8Vd3-FQ6yoS7hleuUR60sQRpmYY9YV4iIr7YohIIzY&_nc_ht=scontent.fsgn5-1.fna&oh=a8dd495630611b1ea07b6fee9d3772d7&oe=5F02C34E" width="30%"> <img src="https://scontent.fsgn5-5.fna.fbcdn.net/v/t1.0-9/101581411_2566648616997479_2019607198694375424_o.jpg?_nc_cat=100&_nc_sid=cdbe9c&_nc_oc=AQnjs90Ry0ByhCvsD3QDub_ERmaUbuxBcO-06WhumP0D2-H0b_HDJ4J98BL5Zpa7L_g&_nc_ht=scontent.fsgn5-5.fna&oh=4197af585aaea77f654f5ba5a73c1f60&oe=5F007006" width="30%"> <img src="https://scontent.fsgn5-4.fna.fbcdn.net/v/t1.0-9/101508548_2566648686997472_2463112724339490816_o.jpg?_nc_cat=102&_nc_sid=cdbe9c&_nc_oc=AQlIPpH5xEzb9GLu9nzeumw6vQWxgAddLSmo1JaKrwcYTOJQuezMdF5ftoYzxGjxs6M&_nc_ht=scontent.fsgn5-4.fna&oh=e12c10d73ea8d82e3b908cc61b96aaae&oe=5F044B86" width="30%"> <img src="https://scontent.fsgn5-4.fna.fbcdn.net/v/t1.0-9/100740260_2566648796997461_3568717656578064384_o.jpg?_nc_cat=102&_nc_sid=cdbe9c&_nc_oc=AQm5HDhXH8N9R6jKYdQfthKpCLDtzR68yfCmWIXEgskx40t8KVubD9xPv49RPOPr1DA&_nc_ht=scontent.fsgn5-4.fna&oh=abb5938a09711f6c0f6656124b5cd0db&oe=5F016376" width="30%"> <img src="https://scontent.fsgn5-1.fna.fbcdn.net/v/t1.0-9/101242262_2566935780302096_8744307815541112832_o.jpg?_nc_cat=101&_nc_sid=cdbe9c&_nc_oc=AQleePQKttoyPsDEeW569MFArbsm7BB1j3S2Y3zOJPUNu17YPhfge4tjKAnWzPdznG0&_nc_ht=scontent.fsgn5-1.fna&oh=64d487f20568013c0d4d7a499a0ea446&oe=5F00977E" width="30%"> <img src="https://scontent.fsgn5-2.fna.fbcdn.net/v/t1.0-9/78419978_2566935936968747_8274454121528950784_o.jpg?_nc_cat=105&_nc_sid=cdbe9c&_nc_oc=AQlUySf4ZLMb53BMahIx_WIe0Ohsjpxv892kN4vBvWFMsa880EpKE-El_2BGNx-ukss&_nc_ht=scontent.fsgn5-2.fna&oh=251cc6f16c405a547ce79efc57caa02f&oe=5F02FC0A" width="30%"> <img src="https://scontent.fsgn5-5.fna.fbcdn.net/v/t1.0-9/101574515_2566934330302241_3538922703941533696_o.jpg?_nc_cat=108&_nc_sid=cdbe9c&_nc_oc=AQk8D_OqN4R5rRBSNrz5BhT7lxPK5SdNmlH_xZC4NLg7J0_PIHkvRLITarAsw3zXkmQ&_nc_ht=scontent.fsgn5-5.fna&oh=9981a92e535f7e25c853c1022d3d8a80&oe=5F020345" width="30%"> <img src="https://scontent.fsgn5-5.fna.fbcdn.net/v/t1.0-9/78493909_2566912713637736_2594132716043632640_o.jpg?_nc_cat=100&_nc_sid=cdbe9c&_nc_oc=AQkYxAEJaKiRGXkLlZ49NrGRCfrWsoYW--zDNpwQSrDph4hd_ixQcvIwXK0snRsRPX0&_nc_ht=scontent.fsgn5-5.fna&oh=c071c747172c752530a5a534531eee2b&oe=5F027759" width="30%"> <img src="https://scontent.fsgn5-4.fna.fbcdn.net/v/t1.0-9/102760158_2566912793637728_2161231237019074560_o.jpg?_nc_cat=104&_nc_sid=cdbe9c&_nc_oc=AQmB99ETQDlxl7jZ-FA_CtIeojrnsfW44d9N6cQvKJ418qr1Yfn2TrMXZA9lRutmLoI&_nc_ht=scontent.fsgn5-4.fna&oh=eba8bf935c1203993029f1888bc7ea4b&oe=5F045821" width="30%"> <img src="https://scontent.fsgn5-6.fna.fbcdn.net/v/t1.0-9/101169989_2566912916971049_4697182492120055808_o.jpg?_nc_cat=106&_nc_sid=cdbe9c&_nc_oc=AQkEaIn2yLlCENnbLuyBIhm_go7QfOkeUbh_HeJTQb-RBcKbtAaWZzKU0IEBj-E76aE&_nc_ht=scontent.fsgn5-6.fna&oh=a83a54a9a479474bae750da6a61c5247&oe=5F03BFB9" width="30%">

### Live Stream

[![1](https://scontent.fsgn5-3.fna.fbcdn.net/v/t15.5256-10/75641952_2577136975833774_653349318017771941_n.jpg?_nc_cat=110&_nc_sid=ad6a45&_nc_oc=AQk2f9OpmqGxzG0_hGjo0UrysiCphOimcuSSDvs0viloYGRSox59dgApmKfTLKX2i-k&_nc_ht=scontent.fsgn5-3.fna&oh=ef7d97e76b776213992be8d471aeff15&oe=5F00EF8D)](https://www.facebook.com/thanhnienutc2/videos/2577135562500582)

[![2](https://scontent-sin6-1.xx.fbcdn.net/v/t1.0-9/102263894_2657990474305222_3323357479761127256_o.jpg?_nc_cat=106&_nc_sid=cdbe9c&_nc_oc=AQm5fzDPYE7xh-sNg8McbzzFoYj4NoePwpuWb_Qtk0jPq4I0IWyJ4OMdVug6rtM0y1Y&_nc_ht=scontent-sin6-1.xx&oh=bce473a728813811df0b78e4b4d26c44&oe=5F051EB9)](https://www.facebook.com/1480845382244480/videos/534037287265061)

[![2](https://scontent.fsgn5-2.fna.fbcdn.net/v/t1.0-9/102606909_1162679250763910_2578241723335595603_n.jpg?_nc_cat=105&_nc_sid=8bfeb9&_nc_oc=AQkrxb3TJ3qdeq9yiQIgI2emQ0tqptz_acKSR46tZgc1Q8KmwxdbVNhpUGL8uRc0mts&_nc_ht=scontent.fsgn5-2.fna&oh=184cf81c58a7e7bb2f98dc7efa2e88c8&oe=5F018AD6)]

## Built With

* [Arduino Nano](https://store.arduino.cc/usa/arduino-nano) - Main Dev Hardware
* [Arduino IDE](https://www.arduino.cc/reference/en/) - The compiler for Arduino Nano

## Contributors

* **Th.s Võ Thiện Lĩnh**-*Team Leader* - [Facebook](https://www.facebook.com/MR.DUACHUOT)
* **Th.s Lê Mạnh Tuấn**-*Chuyên gia cố vấn cấp cao* - [Facebook](https://www.facebook.com/leemanhtuan)
* **Bùi Đình Trung** - [Facebook](https://www.facebook.com/park.buitrung) [Email](mailto:5751062060@st.utc2.edu.vn)
* **Trần Bách Khoa** - [Facebook](https://www.facebook.com/khoa.tranbach.16) [Email](mailto:5751062034@st.utc2.edu.vn)
* **Nguyễn Minh Tiến** - [Facebook](https://www.facebook.com/spiderock98) [Email](mailto:5751062057@st.utc2.edu.vn) [GitHub](https://github.com/spiderock98)
* **Nguyễn Minh Trung** - [Facebook](https://www.facebook.com/trungnguyen239) [Email](mailto:5751062061@st.utc2.edu.vn)

## Ban Tổ Chức
**Trường Đại học Giao Thông Vận Tải - Phân hiệu tại TP. Hồ Chí Minh** | **Mã tuyển sinh: GSA**
