// SETTINGS
#define BTN_UP 6
#define BTN_DOWN 7

#define BTN_BLAST 5
#define BTN_CANCEL 8

#define LED_BLAST_INDICATOR 9 // funny, but the LED blast might aswell also be the UV led itself

long SecondsSetpoint = 20;

long CurrentTime = 0;

#define ACKSENCREM ACKSEN_BUTTON_MODE_REPEAT, 20, INPUT_PULLUP
#define ACKSENNBTN ACKSEN_BUTTON_MODE_NORMAL, 200, INPUT_PULLUP

AcksenButton btnUp = AcksenButton(BTN_UP, ACKSENCREM);
AcksenButton btnDown = AcksenButton(BTN_DOWN, ACKSENCREM);
AcksenButton btnStart = AcksenButton(BTN_BLAST, ACKSENNBTN);
AcksenButton btnCancel = AcksenButton(BTN_CANCEL, ACKSENNBTN);

DisplaySSD1306_128x64_I2C display(-1);

bool buttonEnable = true;

char lcdDispSetpoint[6];
char lcdDispCurrentTime[6];

bool colonEnable = true;

bool tick = false;