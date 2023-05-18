#include <IRremote.h>
#include <LiquidCrystal_I2C.h>

int IRpin = 11;

decode_results results;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(IRpin, INPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);

  Serial.begin(9600);
  Serial.println("Initializing IR Receiver");
  IrReceiver.begin(IRpin);
  Serial.println("Initialized");
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initialized");
}

void loop() {
  if (IrReceiver.decode()) {
    long data = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(String(data) + "   =>  Required decimal ");

    char hexString[9];
    sprintf(hexString, "%08lX", data);
    Serial.print("Hexadecimal value: 0x");
    Serial.println(hexString);
    PRINT_DISPLAY(data, hexString);
    Serial.println("---------------------------------------------------------");
    delay(100);
    IrReceiver.resume(); // Receive the next value
  }
  delay(100);
}
void PRINT_DISPLAY(long data, char hexString[]) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dec: ");
  lcd.print(data);
  lcd.setCursor(0, 1);
  lcd.print("Hex: ");
  lcd.print(hexString);
}
