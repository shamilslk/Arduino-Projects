#include <LiquidCrystal.h> 
#include <Wire.h> 
#include <I2CKeyPad.h> 
#include <LiquidCrystal_I2C.h> 

const uint8_t KEYPAD_ADDRESS = 0x20; // Set your keypad's I2C address 
I2CKeyPad keyPad(KEYPAD_ADDRESS); 
LiquidCrystal_I2C lcd(0x27, 16, 2); 

int i=0; 
char pincode[6]; 
// Set output condition for each Gate output
int g1 = 1; 
int g2 = 1; 
int g3 = 1; 
int g4 = 1; 


const int pin1 = 0; 
const int pin2 = 1; 
const int pin3 = 2; 
const int pin4 = 3; 
const int pin5 = 4;
const int pin6 = 5;
const int pin7 = 6; 
const int pin8 = 7;
const int pin9 = 8;
const int pin10 = 9; 
const int pin11 = 10;
const int pin12 = 11; 
const int pin13 = 12; 
const int pin14 = 13;

void setup() { 
  Serial.begin(115200); 
  Wire.begin(); 
  Wire.setClock(100000); // Fast I2C speed (400kHz) 

  lcd.begin(16,2); 
  lcd.backlight(); 
  lcd.print("Enter IC No."); 

  if (!keyPad.begin()) { 
    Serial.println("Error: Cannot communicate with keypad."); 
    while (1); 
  } 
  Serial.println("I2C Keypad Ready"); 
} 

 
void loop() { 

  char keys[] = "123A456B789C*0#DNF"; // Define the characters associated with each key 
  char index = keyPad.getKey();    // Get the key index from the keypad 

  if (index != I2C_KEYPAD_NOKEY) { // Check if a valid key was pressed 

    if (index >= 0 && index < sizeof(keys) - 1) { 

      if(keys[index]=='A'){          //for testing the ic 
        
        lcd.clear(); 
        lcd.setCursor(0,0); 
        lcd.print("Testing "); 
        lcd.print(pincode); 

        testing(); 

        g1=1; 
        g2=1; 
        g3=1; 
        g4=1; 

      } 

      else if(keys[index]=='C'){      //clearing or reset 
        lcd.clear(); 
        lcd.setCursor(0,0); 
        lcd.print("Enter pin code"); 

        i=0; 

        g1=1; 
        g2=1; 
        g3=1; 
        g4=1; 

        resetpins();

        delay(200);

      } 

      else if(keys[index]){            //for displaying the key input 

        lcd.setCursor(i,1); 
        lcd.print(keys[index]); 
        pincode[i]=keys[index]; 
        keys[index]=""; 
        i++; 

        delay(100); 

      } 
    } else { 
      lcd.print("Invalid"); // Fallback in case of an out-of-range index 
    } 
  } 
  delay(100); // Add a short delay for debounce 
} 

 
// For searching the ic in the input
void testing() { 

  if (atoi(pincode) == 7400) { 

  testingic(pin1,pin2,pin3,
            pin4,pin5,pin6,
            pin10,pin9,pin8,
            pin13,pin12,pin11,
            pin14,pin13,
            1,1,1,0);

} else if (atoi(pincode) == 7432) { 

  testingic(pin1,pin2,pin3,
            pin4,pin5,pin6,
            pin10,pin9,pin8,
            pin13,pin12,pin11,
            pin14,pin13,
            0,1,1,1);

} else if (atoi(pincode) == 7408) { 

  testingic(pin1,pin2,pin3,
            pin4,pin5,pin6,
            pin10,pin9,pin8,
            pin13,pin12,pin11,
            pin14,pin13,
            0,0,0,1);

  } else if (atoi(pincode) == 7486) {

  testingic(pin1,pin2,pin3,
            pin4,pin5,pin6,
            pin10,pin9,pin8,
            pin13,pin12,pin11,
            pin14,pin13,
            0,1,1,0); 

  } else { 

    lcd.clear(); 

    lcd.print("This IC has not added"); 

  } 

   //check result 

  if (g1 && g2 && g3 && g4) { 

    passTest(); 

  } else { 

    failTest(); 

  } 
} 

void passTest() { 

  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Test Passed"); 
  lcd.setCursor(0, 1); 
  lcd.print(" Good"); 

} 

void failTest() { 

  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("Test Failed"); 
  lcd.setCursor(0, 1); 
  lcd.print(" Bad"); 
  
  delay(2000); 
  
  gate_check(); 

} 

 

void gate_check(){ 

  lcd.clear(); 
  lcd.setCursor(0, 0); 
  lcd.print("G1:"); 
  lcd.print(g1 ? "Good" : "Bad"); 

  lcd.setCursor(8, 0); 
  lcd.print("G2:"); 
  lcd.print(g2 ? "Good" : "Bad"); 

  lcd.setCursor(0, 1); 
  lcd.print("G3:"); 
  lcd.print(g3 ? "Good" : "Bad"); 

  lcd.setCursor(8, 1); 
  lcd.print("G4:"); 
  lcd.print(g4 ? "Good" : "Bad"); 

} 

void testingic(int inA1,int inB1,int outY1,
              int inA2,int inB2,int outY2,
              int inA3,int inB3,int outY3,
              int inA4,int inB4,int outY4,
              int VCC,int GND,
              bool out1,bool out2,bool out3,bool out4){
    pinMode(inA1, OUTPUT); 
    pinMode(inB1, OUTPUT); 
    pinMode(outY1, INPUT); 
    pinMode(inA2, OUTPUT); 
    pinMode(inB2, OUTPUT); 
    pinMode(outY2, INPUT); 
    pinMode(inA3, OUTPUT);
    pinMode(inB3, OUTPUT); 
    pinMode(outY3, INPUT); 
    pinMode(inA4, OUTPUT); 
    pinMode(inB4, OUTPUT); 
    pinMode(outY4, INPUT); 
    pinMode(VCC, OUTPUT); 
    pinMode(GND, OUTPUT);

    digitalWrite(VCC, HIGH); 
    digitalWrite(GND, LOW);

    setinput(0,0, inA1, inB1, outY1,
               inA2, inB2, outY2,
               inA3, inB3, outY3,
               inA4, inB4, outY4);  

    delay(100); 

    checkoutput(out1,outY1,outY2,outY3,outY4);

    setinput(0,1, inA1, inB1, outY1,
               inA2, inB2, outY2,
               inA3, inB3, outY3,
               inA4, inB4, outY4);

    delay(100); 

    checkoutput(out2,outY1,outY2,outY3,outY4); 

    setinput(1,0, inA1, inB1, outY1,
               inA2, inB2, outY2,
               inA3, inB3, outY3,
               inA4, inB4, outY4);

    delay(100);

    checkoutput(out3,outY1,outY2,outY3,outY4); 

    setinput(1,1, inA1, inB1, outY1,
               inA2, inB2, outY2,
               inA3, inB3, outY3,
               inA4, inB4, outY4); 

    delay(100); 

    checkoutput(out4,outY1,outY2,outY3,outY4); 
}

void setinput(bool state1,bool state2,
            int inA1,int inB1,int outY1,
            int inA2,int inB2,int outY2,
            int inA3,int inB3,int outY3,
            int inA4,int inB4,int outY4){ 

    digitalWrite(inA1, state1); 
    digitalWrite(inB1, state2); 
    digitalWrite(inA2, state1); 
    digitalWrite(inB2, state2); 
    digitalWrite(inA3, state1); 
    digitalWrite(inB3, state2); 
    digitalWrite(inA4, state1); 
    digitalWrite(inB4, state2);  
}

void checkoutput(bool out,int outY1,int outY2,int outY3,int outY4){
  if (digitalRead(outY1) != out) g1 = 0; 

  if (digitalRead(outY2) != out) g2 = 0; 

  if (digitalRead(outY3) != out) g3 = 0; 

  if (digitalRead(outY4) != out) g4 = 0;
}

void resetpins(){  
  digitalWrite(pin1, LOW); 
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW); 
  digitalWrite(pin4, LOW); 
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, LOW); 
  digitalWrite(pin7, LOW); 
  digitalWrite(pin8, LOW);
  digitalWrite(pin9, LOW); 
  digitalWrite(pin10, LOW); 
  digitalWrite(pin11, LOW);
  digitalWrite(pin12, LOW);
  digitalWrite(pin13, LOW);
  digitalWrite(pin14, LOW);
}
