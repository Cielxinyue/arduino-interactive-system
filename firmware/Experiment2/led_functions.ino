/* ----------------------------------------------------------------------------------------- 
 * RGB_led_functions
 * -----------------------------------------------------------------------------------------*/

void setupPins()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  
}

/* ----------------------------------------------------------------------------------------- */

void ledOffAll() 
{
  digitalWrite(RED, LED_OFF);
  digitalWrite(GREEN, LED_OFF);
  digitalWrite(BLUE, LED_OFF);
  Serial.println(F("[LED] ALL OFF"));
}


void ledTest() 
{
  Serial.println(F("[LED] Running LEDTEST: red -> green -> blue"));
  digitalWrite(RED, HIGH); digitalWrite(GREEN, LOW); digitalWrite(BLUE, LOW); delay(300);
  digitalWrite(RED, LOW); digitalWrite(GREEN, HIGH); digitalWrite(BLUE, LOW); delay(300);
  digitalWrite(RED, LOW); digitalWrite(GREEN, LOW); digitalWrite(BLUE, HIGH); delay(300);
  ledOffAll();
  Serial.println(F("[LED] LEDTEST completed"));
}

void ledSet(const char* color)
 {
  if (strcmp(color, "red")==0) 
  {
    digitalWrite(RED, LED_ON);   digitalWrite(GREEN, LED_OFF); digitalWrite(BLUE, LED_OFF);
  } 
  else if (strcmp(color, "green")==0) 
  {
    digitalWrite(RED, LED_OFF);  digitalWrite(GREEN, LED_ON);  digitalWrite(BLUE, LED_OFF);
  } 
  else if (strcmp(color, "blue")==0) 
  {
    digitalWrite(RED, LED_OFF);  digitalWrite(GREEN, LED_OFF); digitalWrite(BLUE, LED_ON);
  }
  Serial.print(F("[LED] ")); Serial.print(color); Serial.println(F(" ON"));
}

void applyLedState(uint8_t idx) 
{
  switch (idx) 
  {
    case 0: // Red only
      digitalWrite(RED, LED_ON);
      digitalWrite(GREEN, LED_OFF);
      digitalWrite(BLUE, LED_OFF);
      break;
    case 1: // Green only
      digitalWrite(RED, LED_OFF);
      digitalWrite(GREEN, LED_ON);
      digitalWrite(BLUE, LED_OFF);
      break;
    case 2: // Blue only
      digitalWrite(RED, LED_OFF);
      digitalWrite(GREEN, LED_OFF);
      digitalWrite(BLUE, LED_ON);
      break;
    default: // safe fallback -> all off
      digitalWrite(RED, LED_OFF);
      digitalWrite(GREEN, LED_OFF);
      digitalWrite(BLUE, LED_OFF);
      break;
  }
}
