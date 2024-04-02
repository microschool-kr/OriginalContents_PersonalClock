#include <uRTCLib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Arduino.h"



uRTCLib rtc;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// Function to calculate the number of days between two dates
int daysBetween(uint8_t day, uint8_t month, uint8_t year, uint8_t targetDay, uint8_t targetMonth, uint8_t targetYear) {
    int days = 0;
    while (day != targetDay || month != targetMonth || year != targetYear) {
        // Increment the current day
        day++;
        if (day > 31 || (month == 2 && day > 29) || ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        days++;
    }
    return days;
}

void setup() {
    Serial.begin(9600);
    URTCLIB_WIRE.begin();

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
	Serial.println(F("SSD1306 allocation failed"));
	for (;;);
    }
    display.clearDisplay();

   }

void loop() {
    rtc.refresh();

    // Get the current date
    uint8_t currentDay = rtc.day();
    uint8_t currentMonth = rtc.month();
    uint8_t currentYear = rtc.year();

    Serial.print("Current date: ");
    Serial.print(currentDay);
    Serial.print("/");
    Serial.print(currentMonth);
    Serial.print("/");
    Serial.println(currentYear);

    // Set the target date
    uint8_t targetDay = 3;
    uint8_t targetMonth = 4;
    uint8_t targetYear = 24;

    // Calculate the number of days between the current date and the target date
    int dday = daysBetween(currentDay, currentMonth, currentYear, targetDay, targetMonth, targetYear);

    // Print the calculated D-Day
    Serial.print("D-Day: ");
    Serial.println(dday);

    display.clearDisplay();

    display.setCursor(1,1);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("D-Day: ");
    display.println(dday);

    display.display();
    delay(1000);
}

