#include <SPI.h>
#include <RFID.h>
#include <Wire.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);
char msg[100] = " ";
char *stt = "status";
int serNum[5];
int cards[][5] =
    {
        {215, 75, 253, 103, 6},
        {96, 90, 124, 108, 42}};

String idin;

bool access = false;

void disp(bool check);
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}

void loop()
{
  
    if (rfid.isCard())
    {
      if (rfid.readCardSerial())
      {
        //Chuyển đổi ID thẻ sang String
        idin = "";
        for (int i = 0; i < sizeof(rfid.serNum); i++)
        {
          idin += String(rfid.serNum[i]);
          // Serial.print(rfid.serNum[i]);
        }
        Serial.println(idin);
        //So sánh ID thẻ với ID có thể truy nhập
        for (int x = 0; x < sizeof(cards); x++)
        {
          for (int i = 0; i < sizeof(rfid.serNum); i++)
          {
            access = true;
            //Nếu khác thì gán quyền truy cập = False
            if (rfid.serNum[i] != cards[x][i])
            {
              access = false;
              break;
            }
          }
          if (access)
            break;
        }
      }
      disp(access);
    }
    rfid.halt(); //Dừng đọc
  }


void disp(bool check)
{
  if (check)
  {
    // sprintf(msg,"{\"%s\":%d}",stt,1);
    // Serial.println(msg);
    // open door in here source code
    Serial.println("Open door");
  }
  else
  {
    // sprintf(msg,"{\"%s\":%d}",stt,0);
    // Serial.println(msg);
  }
  delay(1000);
}
