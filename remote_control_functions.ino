/* -------------------------------------------------------------- 
 * remote_control_functions
 * Calculate addition and subtraction
 * -------------------------------------------------------------*/
char remote_mapping(int x)
{

  char my_char;

  switch (x)
  {
    case 0x45:
    my_char = '1';
    break;

    case 0x46:
    my_char = '2';
    break;

    case 0x47:
    my_char = '3';
    break;

    case 0x44:
    my_char = '4';
    break;

    case 0x40:
    my_char = '5';
    break;

    case 0x43:
    my_char = '6';
    break;

    case 0x7:
    my_char = '7';
    break;

    case 0x15:
    my_char = '8';
    break;

    case 0x9:
    my_char = '9';
    break;

    case 0x19:
    my_char = '0';
    break;

    case 0x18:
    my_char = '+';
    break;

    case 0x52:
    my_char = '-';
    break;

    case 0x5A:
    my_char = '=';
    break;

    


    default:
    my_char = '!';
    break;
  }

  return my_char;

}


void remote()
{

  char local_char;
  String my_string = "";

  // Store cumulative results
  long result = 0;       
  char last_op = '+';    

  Serial.println("***Remote control function***");

  // Check for a new code
  byte state = HCIRNEC.newCode();

  while (state == NOCODE)
  {
    state = HCIRNEC.newCode();
  }


  while (HCIRNEC.command!=0x1C)
  {
    switch(state)
    {
      case(NEWCODE): 
      local_char = remote_mapping(HCIRNEC.command);

        
      if (local_char != '!')
      { 
        if (local_char >= '0' && local_char <= '9')
        {
          my_string += local_char;     
          Serial.print(local_char);  
        }
        else if (local_char == '+' || local_char == '-') 
        {
          if (my_string.length() > 0)
          {
            long num = my_string.toInt();  
            if (last_op == '+') result += num;
            else if (last_op == '-') result -= num;
            my_string = "";    // Clear spliced ​​numbers
          }
          last_op = local_char;
          Serial.print(local_char);       
        }
        else if (local_char == '=') 
        {

          if (my_string.length() > 0)
          {
            long num = my_string.toInt();  
            if (last_op == '+') result += num;
            else if (last_op == '-') result -= num;
          }
          Serial.print("=");               
          Serial.println(result);    // Print results and wrap       

          // Reset state and prepare for next input
          my_string = "";
          result = 0;
          last_op = '+';
        }
      }
      break;


      case(REPEATCODE):
      break;

      case(RECEIVEERROR): // An invalid code had been received
      Serial.println("Invalid code received"); 
      break;
   }
   state = HCIRNEC.newCode();

   while (state == NOCODE)
   {
    state = HCIRNEC.newCode();
   }
  }
  Serial.println(my_string);
  Serial.println("***End Remote Control function***");

}
