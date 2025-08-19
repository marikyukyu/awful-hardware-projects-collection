void lcdSetup()
{
  display.setFixedFont(courier_new_font11x16_digits);
  display.begin();
  display.clear();
}

void lcdDisplaySetpoint()
{
  // display.getInterface().invertMode();
  dec2bcd(SecondsSetpoint, lcdDispSetpoint, true);
  display.printFixedN(12, 0, lcdDispSetpoint, STYLE_NORMAL, 1);
}

void lcdDisplayTime()
{
  dec2bcd(CurrentTime, lcdDispCurrentTime, colonEnable);
  display.printFixedN(12, 32, lcdDispCurrentTime, STYLE_NORMAL, 1);
}

void lcdClearSetpoint()
{
  display.printFixedN(12, 0, "     ", STYLE_NORMAL, 1);
}

void lcdClearTime()
{
  display.printFixedN(12, 32, "     ", STYLE_NORMAL, 1);
}