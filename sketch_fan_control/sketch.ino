/*
  ATTINY 414
  Potentiometer connected to PINPA4, pin 0
  Timer A0, WO2/PB2
*/

#if F_CPU != 16000000
  #error "Required 16MHz for proper timer clock."
#endif

#ifdef MILLIS_USE_TIMERA0
  #error "This sketch takes over TCA0 - please use a different timer for millis"
#endif

// fmap(percent, 0, 1023, 639, 0);
float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float fmapAlt(float x)
{
  return (x * 639) / 1023;
}

void setupTimer()
{
  PORTB.DIR = (1 << 2); // TCA0.WO2, PB2

  // TCA0.SINGLE.CMP2 = ;

  TCA0.SPLIT.CTRLA = 0; //disable TCA0 and set divider to 1
  TCA0.SPLIT.CTRLESET= TCA_SPLIT_CMD_RESET_gc|0x03; //set CMD to RESET to do a hard reset of TCA0.

  delay(10);

  TCA0.SINGLE.PERBUF = 639; // period. 25kHz, for 16 MHz F_CPU
  TCA0.SINGLE.CTRLB = TCA_SINGLE_WGMODE_SINGLESLOPE_gc | (1 << TCA_SINGLE_CMP2EN_bp);
  TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | (1 << TCA_SINGLE_ENABLE_bp);
}

void setTimerPwm(short percent)
{
  short value = fmap(percent, 0, 1023, 639, 0);
  TCA0.SINGLE.CMP2 = value;
}

void setup() {
  // put your setup code here, to run once:

  setupTimer();
  
  pinMode(PIN_PA4, INPUT);
  analogReference(VDD);
}

void loop() {
  // put your main code here, to run repeatedly:

  setTimerPwm(analogRead(PIN_PA4));

}
