// FCPU MUST BE 16MHz

#include <AcksenButton.h>
#include "lcdgfx.h"

#include "globalvars.h"
#include "dec2bcd.h"
#include "lcd.h"
#include "main.h"

void setup()
{
  IOSetup();
  lcdSetup();
  timer1Setup();


  lcdDisplaySetpoint();
  lcdDisplayTime();
}

void loop()
{
  buttonsLoop();
  handleTimeloop();

  // delay(50);
}