#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<list>

using namespace std;

const int MX = 600002;
char dat[MX];
int pre[MX];
int nxt[MX];
int unused = 1;
int cursor = 0;

void insert(int addr, char letter)
{
    dat[unused] = letter;
    pre[unused] = addr;
    nxt[unused] = nxt[addr];

    if (nxt[addr] != -1) pre[nxt[addr]] = unused;
    nxt[addr] = unused;

    unused++;
}

void erase(int addr)
{
    nxt[pre[addr]] = nxt[addr];
    if (nxt[addr] != -1) pre[nxt[addr]] = pre[addr];
}

void traverse()
{
    int cur = nxt[0];
    while (cur != -1)
    {
        cout << dat[cur];
        cur = nxt[cur];
    }

    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    fill(pre, pre + MX, -1);
    fill(nxt, nxt + MX, -1);

    string word;
    cin >> word;

    for (int i = 0; i < word.size(); i++)
    {
        insert(i, word[i]);
        cursor++;
    }

    int num;
    char order, addletter;
    cin >> num;
    

    for (int i = 0; i < num; i++)
    {
        cin >> order;

        if (order == 'L')
        {
            if (pre[cursor] !=-1)
            {
                cursor=pre[cursor];
            }
        }

        else if (order == 'D')
        {
            if (nxt[cursor]!=-1)
            {
                cursor=nxt[cursor];
            }
        }

        else if (order == 'B')
        {
            if (cursor > 0)
            {
                erase(cursor);
                cursor=pre[cursor];
            }
        }

        else //order=='P'
        {
            cin >> addletter;
            insert(cursor, addletter);
            cursor=nxt[cursor];
        }

    }

    traverse();

    return 0;
}