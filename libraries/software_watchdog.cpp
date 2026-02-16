class Watchdog
{

private:
    void (*timeoutCallback)(void);
    uint16_t previousMillis = 0;

    
public:

uint16_t timeout = 0;
bool isAngry = false;


    Watchdog(uint16_t _timeout, void (*_timeoutCallback)(void))
    {
        this->timeoutCallback = _timeoutCallback;
        this->timeout = _timeout;
    }

    void tick()
    {
        uint16_t currentMillis = millis();
        if (currentMillis - previousMillis >= timeout)
        {
            isAngry = true;
            timeoutCallback();
        }
    }

    void feed()
    {
        previousMillis = millis();
    }
};
