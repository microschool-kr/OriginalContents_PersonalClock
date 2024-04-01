#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Arduino.h"
#include "uRTCLib.h"

// uRTCLib 클래스의 인스턴스를 생성하고, RTC 모듈의 I2C 주소로 초기화합니다.
uRTCLib rtc(0x68);

// 요일 문자열 배열
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

#define SCREEN_WIDTH 128 //OLED 의 가로 크기 
#define SCREEN_HEIGHT 64 // OLED 의 세로 크기 

#define OLED_RESET     -1 // 리셋 핀이 없다면 -1을 사용합니다. 
#define SCREEN_ADDRESS 0x3C // OLED의 I2C 주소
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // OLED 디스플레이를 초기화합니다.

// D-day를 계산하는 함수
int calculateDday() {
  // 현재 날짜와 이벤트 날짜 사이의 일수 차이를 계산합니다.
  int currentYear = rtc.year();
  int currentMonth = rtc.month();
  int currentDay = rtc.day();

  int eventYear = 2024;
  int eventMonth = 4;
  int eventDay = 3;

  // 현재 날짜와 이벤트 날짜 사이의 일수 차이를 계산합니다.
  int dday = getDays(currentYear, currentMonth, currentDay, eventYear, eventMonth, eventDay);

  return dday;
}

// 두 날짜 간의 일수 차이를 계산하는 함수
int getDays(int currentYear, int currentMonth, int currentDay, int eventYear, int eventMonth, int eventDay) {
  int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  int dday = 0;

  // 현재 날짜부터 이벤트 날짜까지의 일수를 계산합니다.
  while (currentYear != eventYear || currentMonth != eventMonth || currentDay != eventDay) {
    // 현재 날짜를 하루씩 증가시킵니다.
    currentDay++;
    // 해당 월의 마지막 날짜를 고려하여 처리합니다.
    if (currentDay > daysInMonth[currentMonth - 1]) {
      if (currentMonth == 2 && isLeapYear(currentYear)) {
        // 윤년일 때 2월의 마지막 날짜를 29일로 설정합니다.
        currentDay = 29;
      } else {
        currentDay = 1;
        currentMonth++;
        if (currentMonth > 12) {
          currentMonth = 1;
          currentYear++;
        }
      }
    }
    dday++;
  }

  return dday;
}

// 윤년 여부를 확인하는 함수
bool isLeapYear(int year) {
  if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    return true;
  else
    return false;
}



//// D-day를 계산하는 함수
//int calculateDday() {
//  // 현재 날짜와 이벤트 날짜 사이의 일수 차이를 계산합니다.
//  int currentYear = rtc.year();
//  int currentMonth = rtc.month();
//  int currentDay = rtc.day();
//
//  int eventYear = 2024;
//  int eventMonth = 12;
//  int eventDay = 25;
//
//  int dday = 0;
//
//  // 현재 날짜와 이벤트 날짜 사이의 일수 차이를 계산합니다.
//  while (currentYear != eventYear || currentMonth != eventMonth || currentDay != eventDay) {
//    // 현재 날짜를 하루씩 증가시킵니다.
//    currentDay++;
//    // 해당 월의 마지막 날짜를 고려하여 처리합니다.
//    if (currentDay > daysInMonth(currentYear, currentMonth)) {
//      currentDay = 1;
//      currentMonth++;
//      if (currentMonth > 12) {
//        currentMonth = 1;
//        currentYear++;
//      }
//    }
//    dday++;
//  }
//
//  return dday;
//}
//
//// 해당 월의 마지막 날짜를 반환하는 함수
//int daysInMonth(int year, int month) {
//  if (month == 2) {
//    // 윤년을 고려하여 2월의 마지막 날짜를 반환합니다.
//    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
//      return 29;
//    else
//      return 28;
//  } else if (month == 4 || month == 6 || month == 9 || month == 11) {
//    return 30;
//  } else {
//    return 31;
//  }
//}



// 요일, 월, 년을 문자열로 변환하는 함수
String DayMonthYear(uint8_t Day,uint8_t Month,uint16_t Year){
  String DayMonthYearText;
  if (Month==1)  DayMonthYearText="JAN ";
  if (Month==2)  DayMonthYearText="FEB ";
  if (Month==3)  DayMonthYearText="MAR ";
  if (Month==4)  DayMonthYearText="APR ";
  if (Month==5)  DayMonthYearText="MAY ";
  if (Month==6)  DayMonthYearText="JUN ";
  if (Month==7)  DayMonthYearText="JUL ";
  if (Month==8)  DayMonthYearText="AUG ";
  if (Month==9)  DayMonthYearText="SEP ";
  if (Month==10)  DayMonthYearText="OCT ";
  if (Month==11)  DayMonthYearText="NOV ";
  if (Month==12)  DayMonthYearText="DEC ";

  DayMonthYearText=DayMonthYearText+Day;
  if (Day==1)DayMonthYearText=DayMonthYearText+"st ";
  if (Day==2)DayMonthYearText=DayMonthYearText+"nd ";
  if (Day>2)DayMonthYearText=DayMonthYearText+"th ";

  DayMonthYearText=DayMonthYearText+Year;
  
  return DayMonthYearText;
}

// 시, 분, 초를 문자열로 변환하는 함수
String AddLeadingZero(uint8_t x){
  String AddLeadingZeroText;
  if(x<10) AddLeadingZeroText="0"; 
  else AddLeadingZeroText=""; 
  AddLeadingZeroText=AddLeadingZeroText+x;
  return AddLeadingZeroText;
}

//// D-day를 계산하는 함수
//int calculateDday() {
//  // 현재 날짜와 이벤트 날짜 사이의 일수 차이를 계산합니다.
//  int currentDate = rtc.getDays(rtc.year(), rtc.month(), rtc.day());
//  int eventDate = rtc.getDays(eventYear, eventMonth, eventDay);
//  int dday = eventDate - currentDate;
//  return dday;
//}

void setup() { 

  // 시리얼 통신을 초기화합니다. 
  Serial.begin(9600);
 
  // RTC의 I2C 통신을 초기화합니다.
  URTCLIB_WIRE.begin();

  // SSD1306 디스플레이를 초기화합니다.
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // RTC 모듈의 시간을 설정합니다.(초, 분, 시, 요일, 일, 월, 년)
  //rtc.set(0, 0, 22, 2, 1, 4, 24);

  // 디스플레이를 초기화합니다.
  display.clearDisplay();
}

void loop() {
  rtc.refresh(); // RTC 모듈의 시간을 읽어옵니다.
  dday(); // 디스플레이에 D-day를 표시합니다.
}

void dday() {
  display.clearDisplay();

  //display.fillRect(0,0,128,15,SSD1306_WHITE);
  //display.fillRect(0,17,128,15,SSD1306_BLACK);
  //display.fillRect(0,31,128,33,SSD1306_WHITE);

  //display.setCursor(1,1); 
  //display.setTextSize(2);
  //display.setTextColor(SSD1306_BLACK); 
  //display.print(daysOfTheWeek[rtc.dayOfWeek()-1]);

  display.setCursor(1,18); 
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE); 
  display.print(DayMonthYear(rtc.day(),rtc.month(),rtc.year()));

  //display.setCursor(3,35); 
  //display.setTextSize(3);  
  //display.setTextColor(SSD1306_BLACK); 
  //display.print(AddLeadingZero(rtc.hour()));
  //display.print(":");
  //display.println(AddLeadingZero(rtc.minute()));

  //display.setCursor(100,35); 
  //display.setTextSize(2);
  //display.setTextColor(SSD1306_BLACK); 
  //display.print(AddLeadingZero(rtc.second()));

  // D-day를 계산하고 표시합니다.
  int dday = calculateDday();
  display.setCursor(3, 35);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("D-day: ");
  display.print(dday);
  display.print(" days");

  display.display();
  // 1초 마다 시간이 바뀌도록 수정 
  delay(1000); 
}

