#include<iostream>
#include<string>
#include<list>
#include<vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int num;
    cin >> num;

    for (int i = 0; i < num; i++)
    {
        list<char> PW;
        auto cursor = PW.begin();

        string decodePW;
        cin >> decodePW;

        for (auto j : decodePW)
        {
            if (j == '<')
            {
                if (cursor != PW.begin())
                {
                    cursor--;
                }
            }

            else if (j == '>')
            {
                if (cursor != PW.end())
                {
                    cursor++;
                }
            }

            else if (j == '-')
            {
                if (cursor != PW.begin())
                {
                    cursor--;
                    cursor=PW.erase(cursor);
                }
            }

            else
            {
                PW.insert(cursor, j);
            }

        }

        for (auto c : PW)cout << c;
        cout << "\n";

    }


    return 0;
}

