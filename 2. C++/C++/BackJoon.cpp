#include<iostream>
#include<stack>
#include<string>

using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    stack<int> st;

    int num;
    cin >> num;

    string order;
    for (int i = 0; i < num; i++)
    {
        cin >> order;

        if (order == "push")
        {
            int n;
            cin >> n;
            st.push(n);
        }

        else if (order == "pop")
        {
            if (st.empty())
            {
                cout << -1;
                cout << "\n";
            }

            else
            {
                cout << st.top();
                cout << "\n";
                st.pop();
            }
        }

        else if (order == "size")
        {
            cout << st.size();
            cout << "\n";
        }

        else if (order == "empty")
        {
            if (st.empty())
            {
                cout << 1;
            }

            else
            {
                cout << 0;
            }
            cout << "\n";
        }

        else if (order == "top")
        {
            if (st.empty())
            {
                cout << -1;
            }

            else
            {
                cout << st.top();
            }
            cout << "\n";
        }

    }


    return 0;
}

