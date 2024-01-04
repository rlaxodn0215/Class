#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

int Sign(int num)
{
    if (num < 0)
        return -1;
    else if (num > 0)
        return 1;
    else
        return 0;
}

int solution(int h1, int m1, int s1, int h2, int m2, int s2);

int main()
{
    cout << solution(0, 0, 0, 23, 59, 59) << endl;
    return 0;
}

int solution(int h1, int m1, int s1, int h2, int m2, int s2)
{
    int answer = 0;

    int hour = 0;
    int minute = 0;
    int second = 0;

    int from = h1 * 60 * 60 + m1 * 60 + s1;
    int to = h2 * 60 * 60 + m2 * 60 + s2;

    hour = 2 * from;
    minute = (m1 * 60 + s1) * 24;
    second = s1 * 1440;

    for (int i = 0; i < to - from; i++)
    {
        //Before
        int beforeS = second;
        int beforeM = minute;
        int beforeH = hour;

        //After
        second += 1440;
        minute += 24;
        hour += 2;

        if (Sign(beforeS - beforeH) * Sign(second - hour) <= 0)
            answer++;

        if (Sign(beforeS - beforeM) * Sign(second - minute) <= 0)
            answer++;

        if (Sign(beforeS - beforeH) * Sign(second - hour) <= 0 &&
            Sign(beforeM - beforeH) * Sign(minute - hour) <= 0)
            answer--;

        second %= 86400;
        minute %= 86400;
        hour %= 86400;
    }


    return answer;
}