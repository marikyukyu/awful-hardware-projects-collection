void IOSetup()
{
	btnUp.setRepeatPressesInterval(50);
	btnUp.setRepeatInitialOffsetDelay(200);

	btnDown.setRepeatPressesInterval(50);
	btnDown.setRepeatInitialOffsetDelay(200);

	pinMode(LED_BLAST_INDICATOR, OUTPUT); // ACTIVE HIGH
}

void timer1Setup()
{
	// TIMER 1 for interrupt frequency 2 Hz:
	cli(); // stop interrupts
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0; // set entire TCCR1A register to 0

	// interrupt channel
	OCR1A = 31249; // = 16000000 / (64 * 2) - 1 (must be <65536)
	// turn on CTC mode
	TCCR1B |= (1 << WGM12);
	// 1024 prescaler
	TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	sei(); // allow interrupts
}

void disableTimer()
{
	TIMSK1 = 0 << OCIE1A;
	TCNT1 = 0;
	tick == false;
	colonEnable = true;
}

void enableTimer()
{
	TIMSK1 = 1 << OCIE1A;
	TCNT1 = 0;
}

void startBlasting()
{
	buttonEnable = false; // disable modification
	CurrentTime = SecondsSetpoint;
	lcdDisplayTime();

	enableTimer();

	digitalWrite(LED_BLAST_INDICATOR, HIGH);
}

void stopBlasting()
{
	buttonEnable = true;
	CurrentTime = 0;
	lcdDisplayTime();

	disableTimer();

	digitalWrite(LED_BLAST_INDICATOR, LOW);
}

// reminder that it ticks for 500ms
void handleTimeloop()
{
	if (tick == false) // set TRUE by TIMER1_COMPA_vect interrupt
		return;

	if (CurrentTime != 0)
	{
		if (colonEnable)
		{
			CurrentTime -= 1;
			colonEnable = false;
		}
		else
		{
			colonEnable = true;
		}

		lcdDisplayTime();

		tick = false;

		return;
	}

	tick = false;
	stopBlasting();
}

void crementSetpoint(bool inc)
{
	if (!buttonEnable)
		return;
	SecondsSetpoint += inc ? 1 : -1;
	SecondsSetpoint = constrain(SecondsSetpoint, 1, 600);

	lcdDisplaySetpoint();
}

void buttonsLoop()
{
	// TODO:
	/*
		This is incredibly bloated. Seriously horrible.
		My standards for programming sure got s*******
		the moment I start to deal with states.
		When there's things you're unsure of,
		this happens. Lots of cargo cult programming.

		Fix this with a state machine.
	*/

	btnStart.refreshStatus();
	btnCancel.refreshStatus();

	btnUp.refreshStatus();
	btnDown.refreshStatus();

	if (btnUp.onPressed())
		crementSetpoint(true);

	if (btnDown.onPressed())
		crementSetpoint(false);

	if (btnStart.onPressed())
		startBlasting();

	if (btnCancel.onPressed())
		stopBlasting();
}

ISR(TIMER1_COMPA_vect)
{
	tick = true;
}