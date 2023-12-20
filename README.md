# DS3231 Arduino 

## 알게된 사실
### 1. 코인베터리가 충전용이 아닐경우에는 충전이 안되도록 사진의 저항을 제거해야한다.   
<img src=https://lastminuteengineers.com/wp-content/uploads/arduino/DS3231-Module-Problem-Fix.jpg>  

### 2. SCL과 SDA 핀에는 이미 4.7k 저항으로 풀업이 되어있다.   
<img src=https://lastminuteengineers.com/wp-content/uploads/arduino/DS3231-Module-I2C-Pins-for-Daisy-Chaining.jpg>  

### 3. Adruino의 uRTCLib 라이브러리에서는 내부온도를 출력할 수 있다. 
```arduino
  Serial.print("Temperature: ");
  Serial.print(rtc.temp()  / 100);
  Serial.print("\xC2\xB0");   //shows degrees character
  Serial.println("C");
  ```
<img src=https://lastminuteengineers.com/wp-content/uploads/arduino/DS3231-RTC-Arduino-Output.png>

### 4. 32byte EEPROM(AT24C32)에 데이터를 저장할 수 있고 전원이꺼져도 남아있는다.  
- [Example scketch](/Arduino/EEPROM.ino)  
<img src=https://lastminuteengineers.com/wp-content/uploads/arduino/24C32-EEPROM-Arduino-Output.png>



# 참고 
- [Interface DS3231 Precision RTC Module with Arduino](https://lastminuteengineers.com/ds3231-rtc-arduino-tutorial/)
- [Hardware | RTC DS3231 부품 사용기 - 1](https://chocoball.tistory.com/entry/Hardware-RTC-usning-DS3231-1)
- [uRTClib](https://github.com/Naguissa/uRTCLib)
