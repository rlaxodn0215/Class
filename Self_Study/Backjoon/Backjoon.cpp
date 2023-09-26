#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
#include<string>

using namespace std;

stack<char> EndCal(string& Q);
string Ans(stack<char>& tempQ);

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);

	string question = "3+2*4-9/3";
	stack<char> tempQuestion = EndCal(question);
	
	cout << Ans(tempQuestion) << endl;

	return 0;
}

stack<char> EndCal(string & Q)
{
	stack<char> sign;
	stack<char> temp;

	for (int i = 0; i < Q.size(); i++)
	{
		if (Q[i] >= '0' && Q[i] <= '9')
		{
			temp.push(Q[i]);
		}

		else
		{
			if (sign.empty())
			{
				sign.push(Q[i]);
			}

			else
			{
				switch (Q[i])
				{
				case '+':
					while (!sign.empty())
					{
						temp.push(sign.top());
						sign.pop();
					}
					sign.push(Q[i]);
					break;
				case '-':
					while (!sign.empty())
					{
						temp.push(sign.top());
						sign.pop();
					}
					sign.push(Q[i]);
					break;
				case '*':
					sign.push(Q[i]);
					break;
				case '/':
					sign.push(Q[i]);
					break;
				default:
					break;
				}
			}
		}
	}

	while (!sign.empty())
	{
		temp.push(sign.top());
		sign.pop();
	}

	return temp;
}

string Ans(stack<char> & tempQ)
{
	stack<char> sign;
	stack<int> num;
	string temp = "";
	int hasNum = 0;

	while(!tempQ.empty())
	{
		char q = tempQ.top();
		tempQ.pop();

		if (q >= '0' && q <= '9')
		{
			num.push(q - '0');

			if (num.size() == hasNum + 2)
			{
				char s = sign.top();
				sign.pop();

				int numOne = num.top();
				num.pop();
				int numTwo = num.top();
				num.pop();

				int sum;
				switch (s)
				{
				case '+':
					sum = numOne + numTwo;
					break;
				case '-':
					sum = numOne - numTwo;
					break;
				case '*':
					sum = numOne * numTwo;
					break;
				case '/':
					if (numTwo == 0) return "Impossible";
					sum = numOne / numTwo;
					break;
				default:
					break;
				}
				num.push(sum);
				hasNum++;
			}
		}

		else
		{
			sign.push(q);
		}

	}

	while (num.size()>1)
	{
		int temp1 = num.top();
		num.pop();
		int temp2 = num.top();
		num.pop();
		int number;
		switch (sign.top())
		{
		case '+':
			number = temp1 + temp2;
			break;
		case '-':
			number = temp1 - temp2;
			break;
		case '*':
			number = temp1 * temp2;
			break;
		case '/':
			if (temp2 == 0) return "Impossible";
			number = temp1/temp2;
			break;
		default:
			break;
		}
		sign.pop();
		num.push(number);
	}

	return to_string(num.top());
}


