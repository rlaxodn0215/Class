#include<iostream>
#include<vector>
#include<string>
#include"StopWatch.h"

//ios::sync_with_stdio(0);
//cin.tie(0);

using namespace std;

int compareCount=0;
int matchCount = 0;

void func(string sentence, string word)
{
    

    for (int i = 0; i <= sentence.size()-word.size(); i++)
    {
        cout << i;

        int count = 0;
        for (int j = 0; j < word.size(); j++)
        {
            cout << " ";
            if (j != 0) cout << " ";
            cout << sentence << "\n";
            cout << "  ";

            for (int t = 0; t < i; t++)
                cout << " ";

            if (sentence[i+j] == word[j])
            {

                for(int k=0;k<j;k++)
                    cout << " ";

                cout << "+" << "\n";

                cout << "  ";

                for (int k = 0; k < i; k++)
                    cout << " ";

                cout << word;
                count++;
            }

            else
            {

                for (int k = 0; k < j; k++)
                    cout << " ";

                cout << "|"<<"\n";

                cout << "  ";

                for (int k = 0; k < i; k++)
                    cout << " ";

                cout << word;
                break;
            }

            cout << "\n";

        }

        if (count == word.size())
        {
            matchCount++;
            count = 0;
        }

        compareCount++;
        cout << "\n";
    }
}


int main()
{
    string sentence = "ababcdefga";
    string word = "abc";

    func(sentence, word);

    cout << "비교를 " << compareCount << "회 시도했습니다." << "\n";
    cout << "일치한 횟수는 " << matchCount << "입니다." << "\n";

    return 0;
}

