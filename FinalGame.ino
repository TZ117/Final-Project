#include <Adafruit_NeoPixel.h>
#define PIN            7
#define NUMPIXELS      8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second


/*
  State change detection (edge detection)

  Often, you don't need to know the state of a digital input all the time, but
  you just need to know when the input changes from one state to another.
  For example, you want to know when a button goes from OFF to ON. This is called
  state change detection, or edge detection.

  This example shows how to detect when a button or button changes from off to on
  and on to off.

  The circuit:
  - pushbutton attached to pin 2 from +5V
  - 10 kilohm resistor attached to pin 2 from ground
  - LED attached from pin 13 to ground (or use the built-in LED on most
    Arduino boards)

  created  27 Sep 2005
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ButtonStateChange
*/

// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int buttonPin2 = 4;
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int buttonState2 = 0;         // current state of the button
int lastButtonState2 = 0;     // previous state of the button
int pixelposition = 4; //pixel position


int score = 4;
int lowerbound = 0;
int maxbound = 7;
void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
  for (int i = 0; i < NUMPIXELS / 2; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
  for (int i = 4; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
  }


}

void loop() {
  // HANDLE FIRST BUTTON
  // For a set of NeoPixels the first NeoPixel is 0, second is 1.

  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  //compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      Serial.println("Button1 pressed");
      score = score + 1;//score up


    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;


  // HANDLE SECOND BUTTON
  buttonState2 = digitalRead(buttonPin2);

  //compare the buttonState to its previous state
  if (buttonState2 != lastButtonState2) {
    // if the state has changed, increment the counter
    if (buttonState2 == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      Serial.println("Button2 pressed");
      score = score - 1; //score down

    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState2 = buttonState2;



  Serial.println(score);
  for (int i = 0; i < NUMPIXELS; i++) {
    if(i<score){
      pixels.setPixelColor(i, pixels.Color(255, 0, 0)); // Moderately bright green color.
    }else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 255)); // Moderately bright green color
    }
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
 

  //button1 win:
  if (score <= 0 ) {
    Serial.print("Player 1 Wins!");
  }
  //button2 win:
  if (score >= 7 ) {
    Serial.print("Player 2 Wins!");
  }



}
