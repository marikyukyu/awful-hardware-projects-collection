/*
    Text Entry. a "textbox".
*/

class DecimalEntry
{

public:
    DecimalEntry()
    {
        clear();
    }

    void push(char text)
    {
        if (index >= size)
            return;

        this->text[index++] = text;

        shiftRtl();
    }

    void erase() // deprecated
    {
        if (index <= 0)
            return;

        this->text[--index] = ' ';

        shiftRtl();
    }

    void clear()
    {
        for (int i = 0; i < size; i++)
        {
            this->text[i] = ' ';
        }
        index = 0;
    }

    void shiftRtl()
    {
        int skip = size - index;

        for (int i = 0; i < index; i++)
        {
            this->shifted[i + skip] = this->text[i];
        }
    }



    static const int size = 4;
    char text[size];
    char shifted[size];
    int index = 0;
};
