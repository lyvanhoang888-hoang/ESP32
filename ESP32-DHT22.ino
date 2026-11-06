
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ===== CAU HINH CAM BIEN DHT22 =====
#define DHTPIN 13
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// ===== CAU HINH LCD I2C =====
#define SDA_PIN 23
#define SCL_PIN 22

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ===== SETUP =====
void setup() {
  Serial.begin(115200);

  // Khoi dong I2C cho ESP32
  Wire.begin(SDA_PIN, SCL_PIN);

  // Khoi dong DHT22
  dht.begin();

  // Khoi dong LCD
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("HE THONG DHT22");

  lcd.setCursor(0, 1);
  lcd.print("ESP32 STARTING");

  delay(2000);
  lcd.clear();

  Serial.println("HE THONG DO NHIET DO VA DO AM");
  Serial.println("--------------------------------");
}

// ===== LOOP =====
void loop() {

  // Doc nhiet do va do am
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Kiem tra loi cam bien
  if (isnan(temperature) || isnan(humidity)) {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LOI CAM BIEN!");

    Serial.println("Khong doc duoc DHT22!");

    delay(2000);
    return;
  }

  // Hien thi nhiet do len LCD
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do: ");
  lcd.print(temperature, 1);
  lcd.write(223);
  lcd.print("C ");

  // Hien thi do am len LCD
  lcd.setCursor(0, 1);
  lcd.print("Do am: ");
  lcd.print(humidity, 1);
  lcd.print("%    ");

  // In du lieu ra Serial Monitor
  Serial.print("Nhiet do: ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Do am: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.println("-------------------------");

  // Cap nhat moi 2 giay
  delay(2000);
}
