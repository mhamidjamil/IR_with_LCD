#include <IRremote.h>
#include <LiquidCrystal_I2C.h>

int IRpin = 11;

decode_results results;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(IRpin, INPUT);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);

  Serial.begin(9600);
  // Serial.begin(115200);
  Serial.println("Initializing IR Receiver");
  IrReceiver.begin(IRpin);
  // IrReceiver.enableIRIn(); // Start the receiver
  Serial.println("Initialized");
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initialized");
}

void loop() {

  // if (irrecv.decode(&results))
  if (IrReceiver.decode()) {
    // String ircode = String(IrReceiver.decodedIRData.protocol,HEX);
    Serial.println(sizeof(IrReceiver.decodedIRData.decodedRawDataArray));
    size_t n = sizeof(IrReceiver.decodedIRData.decodedRawDataArray) /
               sizeof(IrReceiver.decodedIRData.decodedRawDataArray[0]);
    Serial.println(IrReceiver.decodedIRData.decodedRawData);
    for (int i = 0; i < n; i++)
      Serial.println(IrReceiver.decodedIRData.decodedRawDataArray[i]);
    IrReceiver.printIRResultAsCVariables(&Serial);
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRResultRawFormatted(&Serial, true);
    // Serial.println(IrReceiver.decodeSony());
    // if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
    //     // We have an unknown protocol here, print more info
    //     //IrReceiver.printIRResultRawFormatted(&Serial, true);
    //     Serial.println("Unknown protocol");
    // }
    // if (IrReceiver.decodedIRData.protocol == NEC) {  // SAMSUNG
    //   Serial.print("Command: 0x");
    // 	Serial.println(IrReceiver.decodedIRData.command,HEX);
    // }

    delay(100);
    IrReceiver.resume(); // Receive the next value
  }
  delay(100);
  // else
  // Serial.println("no");
}
