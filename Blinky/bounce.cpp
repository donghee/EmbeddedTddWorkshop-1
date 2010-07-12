#include <WProgram.h>
#include <math.h>


int ledPin =  13;    // LED connected to digital pin 13

int aPin = 3;
int bPin = 5;
int cPin = 6;
int dPin = 7;
int ePin = 8;

boolean A,B,C,D,E;

// The setup() method runs once, when the sketch starts
void setup()   {
  // initialize the digital pin as an output:
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);
  pinMode(cPin, INPUT);
  pinMode(dPin, INPUT);
  pinMode(ePin, INPUT);

  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  
}

void bUpdate() {
    
}

boolean bRead(int pin) {
    boolean value;
    value = digitalRead(pin);
    return value;
}

int main(void) {

  init();
  setup();
  for (;;) {
      bUpdate();
      A = bRead(aPin);
      digitalWrite(ledPin, !A);
  } // end for
} // end main
