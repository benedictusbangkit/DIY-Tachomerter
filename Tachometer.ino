//Import Library % file Bitmap gambar saat startup
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "tacho.h"
//Definisi ukuran layar dan reset layar
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
//Buat objek display dengan library ssd1306
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//Buat varibel
const int sensorPin = 12; // Pin input sensor IR
unsigned long startTime = 0; // Waktu awal deteksi objek
unsigned long duration = 0; // Durasi deteksi objek

void setup() {
  pinMode(sensorPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //Tampilkan gambar Bitmap ketika startup
  display.drawBitmap(10,10, epd_bitmap_Tacometer, 128, 64, WHITE);
  display.display();
  display.clearDisplay();
}

void loop() {
  //Setup ukuran, dan warna yang akan ditampilkan oled
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  //Panggil function durasi
  durasi();
}
void durasi(){
  int sensorValue = digitalRead(sensorPin);
  //Ketika sensor mendeteksi objek & Timer 0, program akan memulai millis() untuk merekam durasi objek terdeteksi
  if (sensorValue == LOW && startTime == 0){
    startTime = millis();
    display.setCursor(10, 1);
    display.println("Counting . . .");
    display.display();
    display.clearDisplay();
  }
  //Ketika sensor tidak mendeteksi objek & timer sudah berjalan, program akan mengambil waktu timer dan akan memasukan nilainya kedalam rumus rpm, setelah itu timer direset kembali ke 0
  else if (sensorValue == HIGH && startTime !=0){
    duration = millis() - startTime;
    int rpm = 60000 / duration;
    display.setCursor(10, 1);
    display.println(rpm);
    display.display();
    display.clearDisplay();
    startTime = 0;
    delay(6000);
  }
}
