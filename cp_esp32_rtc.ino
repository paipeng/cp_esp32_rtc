
#include <Arduino.h>
#include <Ds1302.h>

#define PIN_RST 2
#define PIN_DAT 4
#define PIN_CLK 5


// DS1302 RTC instance
Ds1302 rtc(PIN_RST, PIN_CLK, PIN_DAT); // rst/ce, dat/io, clk/sclk



const static char* WeekDays[] =
{
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday",
    "Sunday"
};


void setup() {
  delay(1000);
  Serial.begin(115200);

  Serial.println("Serial inited");

  // initialize the RTC
  rtc.init();


  // test if clock is halted and set a date-time (see example 2) to start it
  if (rtc.isHalted()) {
    Serial.println("RTC is halted. Setting time...");

    Ds1302::DateTime dt = {
      .year = 23,
      .month = Ds1302::MONTH_NOV,
      .day = 27,
      .hour = 21,
      .minute = 48,
      .second = 30,
      .dow = Ds1302::DOW_TUE
    };

    rtc.setDateTime(&dt);
    Serial.println("rtc set time success");
  }
}


void loop() {
  // get the current time
  Ds1302::DateTime now;
  rtc.getDateTime(&now);

  static uint8_t last_second = 0;
  if (last_second != now.second) {
    last_second = now.second;

    Serial.print("20");
    Serial.print(now.year);  // 00-99
    Serial.print('-');
    if (now.month < 10) Serial.print('0');
    Serial.print(now.month);  // 01-12
    Serial.print('-');
    if (now.day < 10) Serial.print('0');
    Serial.print(now.day);  // 01-31
    Serial.print(' ');
    Serial.print(WeekDays[now.dow - 1]);  // 1-7
    Serial.print(' ');
    if (now.hour < 10) Serial.print('0');
    Serial.print(now.hour);  // 00-23
    Serial.print(':');
    if (now.minute < 10) Serial.print('0');
    Serial.print(now.minute);  // 00-59
    Serial.print(':');
    if (now.second < 10) Serial.print('0');
    Serial.print(now.second);  // 00-59
    Serial.println();
  }

  delay(1000);
}
