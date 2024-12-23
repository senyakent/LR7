#include <iostream>





bool del(long long a, int s, int p)
{
    long long b, c;
    bool ch = true;

    while (true) //O()
    {
        b = a >> 1;

        if (b + b != a)
        {
            ch = false;
        }
        else
        {
            ch = true;
        }

        a = a >> 1;

        if (ch == false)
        {
            a += s;
        }

        if (a == p)
        {
            return 1;
        }

        if (a < p)
        {
            return 0;
        }
    }
}

