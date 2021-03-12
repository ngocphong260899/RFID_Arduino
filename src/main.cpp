#include <SPI.h>
#include <RFID.h>
#include <Wire.h>


//Khai báo chân SDA và RST
#define SS_PIN 10
#define RST_PIN 9

//Khai báo màn hình LCD và RFID

RFID rfid(SS_PIN, RST_PIN);
char msg[100] = " ";
char* stt = "status";
int serNum[5];              //Biến lưu id thẻ đang đọc
int cards[][5] =            //Những thẻ được phép mở
{
  {215, 75, 253, 103, 6},
  {96, 90, 124, 108, 42}
};

String idin;                //Biến lưu id thẻ đang đọc để xuất lcd

bool access = false;        //Biến lưu quyền truy nhập
void disp(bool check);
void setup()
{
  Serial.begin(9600);       //Mở Serial có Baudrate 9600
  SPI.begin();              //Khởi tạo giao tiếp SPI
  rfid.init();              //Khởi tạo RFid


}

void loop()
{
  if (rfid.isCard())        //Nếu có thẻ 
  {
    if (rfid.readCardSerial())  //Đọc thẻ
    {
      //Chuyển đổi ID thẻ sang String
      idin = "";
      // for (int i = 0; i < sizeof(rfid.serNum); i++ )
      // {
      //   idin += String(rfid.serNum[i]);
      //   Serial.print(rfid.serNum[i]);
      //   Serial.print(" ");
      // }

      //So sánh ID thẻ với ID có thể truy nhập
      for (int x = 0; x < sizeof(cards); x++)
      {
        for (int i = 0; i < sizeof(rfid.serNum); i++ )
        {
          access = true;
          //Nếu khác thì gán quyền truy cập = False
          if (rfid.serNum[i] != cards[x][i])
          {
            access = false;
            break;
          }
        }
        if (access) break;
      }
    }
    disp(access); 
  }
  rfid.halt();    //Dừng đọc
}

void disp(bool check)
{
  
  if (check)            //Nếu đúng ID
  {
    sprintf(msg,"{\"%s\":%d}",stt,1);
    Serial.println(msg);
  }
  else                  //Ngược lại
  {
    sprintf(msg,"{\"%s\":%d}",stt,0);
    Serial.println(msg);
  }
  Serial.println();
  delay(1000);          //Chờ 1s
}
