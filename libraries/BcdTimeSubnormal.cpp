// bcdTime - With subnormal Support!
/*
    What is 'subnormal'?

    Time 00:90 is actually 1 minute and 30 seconds
    You could enter 01:30 that instead.
    my microwave supports that and i like it...
*/
class BcdTime
{
public:
    signed char bcd[4] = {
        0, //
        0, //
        0, //
        0, //
    };

    BcdTime()
    {
    }

    // Note: isZero is actually funny. do not use lol!!
    bool isZero = false;

    void int2bcd(int number)
    {
        // 00 00
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

        // char second_1 = timerTemp;

        bcd[0] = minute_10;
        bcd[1] = minute_1;
        bcd[2] = second_10;
        bcd[3] = timerTemp;
    }

    void increment()
    {
        // TODO: Implement increment.
    }

    void decrement()
    {

        /*
        there are multiple ways to skin this cat
        but we want to support subnormal bcd, so
        i believe we only have one way to do it.
        */

        // decrement MUST be saturating. it shall never have sign.

        // OKAY this is getting annoying. supporting abnormal values is getting stupid.

        bcd[3] = bcd[3] - 1;
        if (bcd[3] <= -1)
        {
            bcd[2] = bcd[2] - 1;
            bcd[3] = 9;
        }

        if (bcd[2] <= -1)
        {
            bcd[1] = bcd[1] - 1;
            bcd[2] = 5;
        }

        if (bcd[1] <= -1)
        {
            bcd[0] = bcd[0] - 1;
            bcd[1] = 9;
        }

        if (bcd[0] <= -1)
        {
            isZero = true;
            bcd[0] = 0;
            bcd[1] = 0;
            bcd[2] = 0;
            bcd[3] = 0;
        }
    }

    void clearLeadingZeroes()
    {
        // TODO: Implement clearLeadingZeroes.
        //       essentially set it to empty when it is zero only until >1
    }
};
