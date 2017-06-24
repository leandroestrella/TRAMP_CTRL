/*
	 HID Joystick Mouse Example by Jim Lindblom [01/12/2012]
   Modified by Leandro Estrella for TRAMP [24/06/2017]
   license: MIT License - Feel free to use this code for any purpose.
   No restrictions. Just keep this license if you go on to use this
   code in your future endeavors! Reuse and share.
*/

/* libraries */
#include <Mouse.h>
#include <Keyboard.h>

int horzPin = A0;  // analog output of horizontal joystick pin
int vertPin = A1;  // analog output of vertical joystick pin
int jumpPin = 9;   // select button pin from joystick
int walkPin = 2;   // walk pin from external button

int vertZero, horzZero;     // stores the initial value of each axis, usually around 512
int vertValue, horzValue;   // stores current analog output of each axis
const int sensitivity = 50; // higher sensitivity value = slower mouse, should be <= about 500

void setup()
{
  pinMode(horzPin, INPUT);         // set both analog pins as inputs
  pinMode(vertPin, INPUT);
  pinMode(jumpPin, INPUT);         // set button select pin as input
  digitalWrite(jumpPin, HIGH);     // pull button select pin high
  pinMode(walkPin, INPUT);         // set button select pin as input
  digitalWrite(walkPin, HIGH);     // pull button select pin high
  delay(1000);                     // short delay to let outputs settle
  vertZero = analogRead(vertPin);  // get the initial values
  horzZero = analogRead(horzPin);  // joystick should be in neutral position when reading these
}

void loop()
{
  vertValue = (analogRead(vertPin) - vertZero) * -1;  // read vertical offset and invert it
  horzValue = analogRead(horzPin) - horzZero;         // read horizontal offset

  if (vertValue != 0) Mouse.move(0, vertValue / sensitivity, 0); // move mouse on y axis
  if (horzValue != 0) Mouse.move(horzValue / sensitivity, 0, 0); // move mouse on x axis
  if (digitalRead(jumpPin) == LOW)       // if joystick button is pressed
  {
    Keyboard.press(32);     // press SPACE (ASCII decimal code)
  }
  else if (digitalRead(jumpPin) == HIGH) // if joystick button is not pressed
  {
    Keyboard.release(32);   // release SPACE (ASCII decimal code)
  }

  if (digitalRead(walkPin) == LOW)       // if walk button is not pressed
  {
    Keyboard.press(218);    // press KEY_UP_ARROW (ASCII decimal code)
    Keyboard.write(218);    // write KEY_UP_ARROW (ASCII decimal code)
  }
  else if (digitalRead(walkPin) == HIGH) // if walk button is not pressed
  {
    Keyboard.release(218);  // release KEY_UP_ARROW (ASCII decimal code)
  }
}
