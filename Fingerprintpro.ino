
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
SoftwareSerial mySerial(2,3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);
LiquidCrystal_I2C lcd(0x27, 20,4);
int fingerprintID = 0;
int motor=8;
int btn1=9;
int a=0;
int buzz=11;

void setup(void) {
  finger.begin(57600);
  lcd.begin();
  pinMode(btn1,INPUT);
  pinMode(motor,OUTPUT);
  pinMode(buzz,OUTPUT);
  lcd.setCursor(8,0);
  lcd.print("ATM");
  delay(2000);
  lcd.setCursor(2,0);
  lcd.print("Place your finger");
  startFingerprintSensor();
}

void loop() {

  fingerprintID = getFingerprintID();
  delay(50);
  if(fingerprintID == 1 ||fingerprintID ==2 ||fingerprintID == 3)
  {
    lcd.setCursor(2,2);
    lcd.print("Hi,G.John Baptist"); 
    delay(1500);
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print ("Savings:10000");
    lcd.setCursor(0,1);
    lcd.print("1.Withdraw 100 rupee");
    delay(1000);
    lcd.print("Press OK to proceed");
    delay(1300);
    digitalRead(btn1);
    delay(700);
    if(digitalRead(btn1)==LOW)
    {
      digitalWrite(buzz,HIGH);
      digitalWrite(motor,HIGH);
      delay(150);
      digitalWrite(buzz,LOW);
      delay(100);
      digitalWrite(buzz,HIGH);
      delay(50);
      digitalWrite(buzz,LOW);
      delay(100);
      digitalWrite(buzz,HIGH);
      delay(200);
      digitalWrite(motor,LOW);
      delay(100);
      digitalWrite(buzz,HIGH);
      delay(100);
      digitalWrite(buzz,LOW);
      delay(100);
      digitalWrite(buzz,HIGH);
      delay(100);
      digitalWrite(buzz,LOW);
      delay(100);
      digitalWrite(buzz,HIGH);
      delay(100);
      lcd.clear();
      digitalWrite(buzz,LOW);
      lcd.setCursor(6,0);
      lcd.print ("Savings:9900");
      delay(1600);
      lcd.clear();
      lcd.print("Place your finger");
      
     
    } 
    else
    {
      lcd.clear();
      lcd.setCursor(6,0);
      lcd.print ("Savings:10000");
      lcd.setCursor(1,2);
      lcd.print("Withdrawal failed");
      delay(2000);
      lcd.clear();
      lcd.print("Place your finger");
      
    }
  }
}

void startFingerprintSensor()
{
  Serial.begin(9600);
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor");
  }
  Serial.println("Waiting for valid finger...");
}

int getFingerprintID() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}


