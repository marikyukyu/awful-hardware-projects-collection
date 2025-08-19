// VALIDATED

void dec2bcd(int *number, char lcdDispArr[], bool colonEnable)
{
	// 0 00
	// min seconds

	// convert seconds to number array

	int timerTemp = number;

	char minute_10 = 0;
	char minute_1 = 0;

	char second_10 = 0;
	// char second_1 = 0;

	while (timerTemp >= 600)
	{
		timerTemp -= 600;
		minute_10 += 1;
	}

	while (timerTemp >= 60)
	{
		timerTemp -= 60;
		minute_1 += 1;
	}

	while (timerTemp >= 10)
	{
		timerTemp -= 10;
		second_10 += 1;
	}

	lcdDispArr[0] = minute_10 + '0';
	lcdDispArr[1] = minute_1 + '0';
	lcdDispArr[2] = colonEnable ? ':' : ' ';
	lcdDispArr[3] = second_10 + '0';
	lcdDispArr[4] = timerTemp + '0';
	lcdDispArr[5] = 0;
}