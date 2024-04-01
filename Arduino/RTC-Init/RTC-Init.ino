#include "Arduino.h"
#include "uRTCLib.h"

// uRTCLib 클래스의 인스턴스를 생성하고, RTC 모듈의 I2C 주소로 초기화합니다.
uRTCLib rtc(0x68);

// 요일 문자열 배열
char daysOfTheWeek[7][12] = {"일", "월", "화", "수", "목", "금", "토"};

void setup() {
	// 시리얼 통신을 초기화하고, 5초간 대기합니다.
	Serial.begin(9600);
	delay(5000); 
	Serial.println("Serial 준비 완료");

	// I2C 통신을 초기화합니다.
	URTCLIB_WIRE.begin();

	// RTC 모듈의 시간을 설정합니다.
	// rtc.set(초, 분, 시, 요일, 일, 월, 년);
	// 요일(1=일요일, 7=토요일)
	rtc.set(00, 51, 13, 2, 26, 03, 24);

	// RTC 모듈의 시간을 읽어와 시리얼 통신으로 출력합니다.
	rtc.refresh();
	Serial.print("세팅된 날짜와 시간: ");
	// 년, 월, 일을 출력합니다.
	Serial.print(rtc.year());
	Serial.print('/');
	Serial.print(rtc.month());
	Serial.print('/');
	Serial.print(rtc.day());

	// 요일을 출력합니다.
	Serial.print(" (");
	Serial.print(daysOfTheWeek[rtc.dayOfWeek()-1]);
	Serial.print(") ");

	// 시간을 출력합니다.
	Serial.print(rtc.hour());
	Serial.print(':');
	Serial.print(rtc.minute());
	Serial.print(':');
	Serial.println(rtc.second());

	Serial.println();


}

void loop() {

}
