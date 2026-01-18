#include <avr/pgmspace.h>

// DACO output ==> D4 on board
void setup() {
  analogReference(DEFAULT);  // 5v
  pinMode(DAC0, ANALOG);

  DAL0 = 127;
}


/*
  32kHz, unsigned 8bit PCM audio.
*/
static const unsigned char samples[] PROGMEM = {};



void loop()
{
  DAL0 = 0x7f;

  for (long i = 0; i <= sizeof(samples); i++) {
    DAL0 = pgm_read_byte_near(samples + i);
    delayMicroseconds(31);
  }
  
  DAL0 = 0x7f;
  delay(2000);
}
