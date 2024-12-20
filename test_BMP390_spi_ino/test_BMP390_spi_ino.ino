//example code for KAmodESP32 POW RS485 and KAmod BMP390
//https://wiki.kamamilabs.com/index.php?title=KAmodESP32_POW_RS485_(PL)

//ino board: ESP32-WROOM-DA Module

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP3XX.h>

//LED
#define LED_PIN       2 
#define MY_DELAY      2000

//I2C
#define I2C_SDA       33
#define I2C_SCL       32

//SPI
#define SPI_MOSI      13
#define SPI_MISO      12
#define SPI_SCK       14    //no a 11 - a small mistake in the description on the pcb
#define SPI_CS        15

//TwoWire I2CBMP = TwoWire(0);
Adafruit_BMP3XX bmp390;

int status;
int i;

void setup() {
  Serial.begin(115200);
  Serial.println("\r\r\rHello. KAmod BMP390 test start");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  //I2CBMP.begin(I2C_SDA, I2C_SCL, 100000);

  status = 0;
  while (status == 0){
    status = bmp390.begin_SPI(SPI_CS, SPI_SCK, SPI_MISO, SPI_MOSI);
    if (!status) {
      Serial.println(F("Something wrong..."));
      delay(3000);
    }
  }

  bmp390.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp390.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp390.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp390.setOutputDataRate(BMP3_ODR_50_HZ);
}

void loop() {
  i++;
  digitalWrite(LED_PIN, (i&1));

  if (bmp390.performReading()) {
    Serial.print(F("Temperature = "));
    Serial.print(bmp390.temperature);
    Serial.print(" *C;  ");

    Serial.print(F("Pressure = "));
    Serial.print(bmp390.pressure);
    Serial.println(" Pa");
  } else {
    Serial.println("Failed to reading...");
  }

  Serial.println();
  delay(MY_DELAY);
}
