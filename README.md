![img](https://nerdytechy.com/wp-content/uploads/2021/02/arduino-rtc-5-1024x677.png)

[![YouTube Channel Views](https://img.shields.io/youtube/channel/views/UCz5BOU9J9pB_O0B8-rDjCWQ?label=YouTube&style=social)](https://youtu.be/E6wkvTG2Ofs?si=k_IFc8MM8aGpZE7J)

# 시계만들기 

[실시간 시계](https://ko.wikipedia.org/wiki/%EC%8B%A4%EC%8B%9C%EA%B0%84_%EC%8B%9C%EA%B3%84)의 개념을 활용해서 아두이노로 시계를 만들어볼 것이다.

# 하드웨어 

- 아두이노 우노  
- SSD1306 OLED
- DS3231 RTC module
- CR2032 코인베터리
- M-M 점퍼선 8개 
- USB 2.0 케이블 Type A/B


**주의: 점퍼선 연결시 케이블을 제거하고 진행합니다.**

## 선 작업 

| [Arduino UNO GPIO](https://docs.arduino.cc/resources/pinouts/A000066-full-pinout.pdf) | DS3231 |
|-----------|------|
|   D19     | SCL  |
|   D18     | SDA  |
|   5V      | VCC  |
|   GND     | GND  |

| [Arduino UNO GPIO](https://docs.arduino.cc/resources/pinouts/A000066-full-pinout.pdf) | SSD1306 |
|-----------|------|
|   A5      | SCL  |
|   A4      | SDA  |
|   5V      | VCC  |
|   GND     | GND  |

## 구입처 

The stl files for an enclosure are on thingiverse [here](https://www.thingiverse.com/thing:6125748) (Thanks Ryan!).

# 코드 다운로드 

    git clone https://

## 라이브러리  
1. Library 
2. Search
3. Install

## 컴파일   

1. open
2. compile

## 업로드  
1. upload

# 동작영상 

Here's a video outlining how it works and a timelapse of it looking after a plant for a week:

[![Mod demo](https://img.youtube.com/vi/E6wkvTG2Ofs/0.jpg)](https://www.youtube.com/watch?v=E6wkvTG2Ofs "Video Title")

# 라이센스 
[GPL 3.0](https://olis.or.kr/license/Detailselect.do?lId=1072&mapCode=010072)
