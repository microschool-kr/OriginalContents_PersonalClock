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
	clockstyles(); // 디스플레이를 시간 스타일로 표시합니다.
}

void clockstyles(void) {
	display.clearDisplay();

	display.fillRect(0,0,128,15,SSD1306_WHITE);
	display.fillRect(0,17,128,15,SSD1306_BLACK);
	display.fillRect(0,31,128,33,SSD1306_WHITE);

  	display.setCursor(1,1); 
  	display.setTextSize(2);
  	display.setTextColor(SSD1306_BLACK); 
	display.print(daysOfTheWeek[rtc.dayOfWeek()-1]);

  	display.setCursor(1,18); 
  	display.setTextSize(1);
 	display.setTextColor(SSD1306_WHITE); 
	display.print(DayMonthYear(rtc.day(),rtc.month(),rtc.year()));

  	display.setCursor(3,35); 
  	display.setTextSize(3);  
  	display.setTextColor(SSD1306_BLACK); 
	display.print(AddLeadingZero(rtc.hour()));
	display.print(":");
	display.println(AddLeadingZero(rtc.minute()));
	
	display.setCursor(100,35); 
  	display.setTextSize(2);
  	display.setTextColor(SSD1306_BLACK); 
  	display.print(AddLeadingZero(rtc.second()));

	display.display();
  	// 1초 마다 시간이 바뀌도록 수정 
  	delay(1000); 
}


