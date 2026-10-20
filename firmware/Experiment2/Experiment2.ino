/* --------------------------------------------------------------
 * ET4244 Experiment 2 ​
 * Control using Arduino IDE and Python experimental hardware
 * @author student Xinyue Chang
 * Studnet number 24216291
 * -------------------------------------------------------------- */

#include <Arduino.h>
#include "HCIRNEC.h"   

#define RED 3
#define GREEN 4
#define BLUE 5
#define IR_PIN 2

#define LED_ON  LOW
#define LED_OFF HIGH

//---------8X8 LED----------

#include "LedControl.h"

#define MATRIX_DIN 11
#define MATRIX_CLK 13
#define MATRIX_CS 10

#define MATRIX_DEVICE_COUNT 1
LedControl lc = LedControl(MATRIX_DIN, MATRIX_CLK, MATRIX_CS, MATRIX_DEVICE_COUNT);


// -----------------------------------------------------------------------


#define MAX_IR_MAPS 8
struct IRMap { uint8_t cmd; char ch; bool used; };
static IRMap irMaps[MAX_IR_MAPS];

HCIRNEC HCIRNEC;

uint8_t iLed = 0;
unsigned long lastLedMs = 0;
const unsigned long LED_INTERVAL_MS = 1000UL;
unsigned long lastSampleMs = 0;
bool running = true;


String normalize(const String &s);

String normalize(const String &s) 
{
  String r = s;
  r.trim();
  r.toLowerCase();
  return r;
}

/* ----------------------------------------------------------------------------------------- */

void setup(void)
{

  Serial.begin(115200);
  while (!Serial && millis() < 2000) { /* wait */ }

  setupPins();
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);

  HCIRNEC.initRX(IR_PIN);

  Serial.print(F("[IR] HCIRNEC.initRX on pin "));
  Serial.println(IR_PIN);

  lastLedMs = millis();
  lastSampleMs = millis();

  for (int i=0;i<MAX_IR_MAPS;++i) irMaps[i].used=false;

}

/* ----------------------------------------------------------------------------------------- */

void loop(void)
{

  // Serial commands
  if (Serial.available() > 0)
  {
    String line = Serial.readStringUntil('\n');
    line.trim();

    if (line.length() == 0) return; 
    
    processCommand(line);
    
    
  }

}

/* ----------------------------------------------------------------------------------------- */

void processCommand(String cmdRaw)
{

    if (cmdRaw.length() == 1)
    {
      char c = cmdRaw.charAt(0);

      // input 6 -> 8x8 LED test
      if (c == '6') 
      { 
        LED_Matrix_Test();
        return;
      }
      // led color test/ IR remote control set
      if (c == '1') { ledSet("red"); return; }
      if (c == '2') { ledSet("green"); return; }
      if (c == '3') { ledSet("blue"); return; }
      if (c == '0') { ledOffAll(); return; }
      if (c == '4') { ledTest(); return; }
      if (c == '5') { remote(); return; }
  }

}
