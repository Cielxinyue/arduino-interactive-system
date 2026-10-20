/* -------------------------------------------------------------- 
 * LED_Matrix_functions
 * -------------------------------------------------------------*/
uint8_t i = 0;

/* --------------------------------------------------------------
 * void setup(void)
 * Setup code to run once
 * -------------------------------------------------------------- */

void LED_Matrix_Test()
{
  Serial.println("***LED_Matrix_test***");
    // initialization
    lc.shutdown(0, false);
    lc.setIntensity(0, 8);
    lc.clearDisplay(0);

  for (uint8_t i=0; i<8; i++)
  {

    switch (i)
    {
      case 0:
        lc.setRow(0, i, 1);
        break;
      case 1:
        lc.setRow(0, i, 3);
        break;
      case 2:
        lc.setRow(0, i, 7);
        break;
      case 3:
        lc.setRow(0, i, 15);
        break;
      case 4:
        lc.setRow(0, i, 31);
        break;
      case 5:
        lc.setRow(0, i, 63);
        break;
      case 6:
        lc.setRow(0, i, 127);
        break;
      case 7:
        lc.setRow(0, i, 255);
        break;
      default:
      lc.setRow(0, i, 0);
    }

    delay(500);

  }

  for (uint8_t i=0; i<8; i++)
  {
    lc.setRow(0, i, 0);
    delay(500);
  }

  delay(500);

}



/* --------------------------------------------------------------
 * End of file
 * -------------------------------------------------------------- */
