#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include"IntStackChar.h"
#include"IntStackNum.h"
#include"IntQueueChar.h"
#include"IntQueueNum.h"

using namespace std;

int main()
{
	IntStackChar Operator_Stack;
	IntStackNum Operand_Stack;
	IntQueueChar PostFix_Queue_Char;
	IntQueueNum PostFix_Queue_Num;

	ifstream readFile;
	readFile.open("Calc2.txt", ios_base::in);
	string clac;
	getline(readFile, clac);

	std::cout << clac << " = ";
	
	Initialize(&PostFix_Queue_Char, 2*clac.size());
	Initialize(&PostFix_Queue_Num, 2*clac.size());
	Initialize(&Operand_Stack, 2*clac.size());
	Initialize(&Operator_Stack, 2*clac.size());

	char letter;
	double Num = 0;
	bool isDec = false;
	double ten = 1;
	double tenrev = 0.1;

	for (int i = 0; i < clac.size(); i++)
	{
		letter = clac[i];

		if (letter >= 48 && letter <= 57) // ���� �� ��
		{
			if (isDec == false) //���� �ڸ�
			{
				if (clac[i + 1] >= 48 && clac[i + 1] <= 57) //���� ���ڰ� ������ ��
				{
					Num = ten * Num + (letter - 48);
					ten *= 10;
				}

				else
				{
					Num = letter - 48;
				}
			}

			else //�Ҽ� �ڸ�
			{
				if (clac[i + 1] >= 48 && clac[i + 1] <= 57) //���� ���ڰ� ������ ��
				{
					Num += tenrev *(letter - 48);
					tenrev *= 0.1;
				}

				else
				{
					Num = tenrev*(letter - 48);
				}
			}

			
			//Enque(&PostFix_Queue, letter);
		}

		else if (letter == 46) //���϶�
		{
			isDec=true;
		}


		else //���� ��ȣ �� ��
		{
			Num = 0;
			isDec = false;
			ten = 1;
			tenrev = 0.1;

			switch ((int)letter)
			{
			case (int)'(':
			{
				Push(&Operator_Stack, letter);
			}
			break;
			case (int)')':
			{
				char popLetter=')';
				while (popLetter != '(')
				{
					Pop(&Operator_Stack, &popLetter);

					if (popLetter != '(')
					{
						Enque(&PostFix_Queue_Char, popLetter);
						Enque(&PostFix_Queue_Num, ' ');
					}
				}
				
			}
			break;
			case (int)'*':
			{
				char oper;
				Peek(&Operator_Stack, &oper);

				while (oper == '*' || oper == '/')
				{
					Pop(&Operator_Stack, &oper);
					Enque(&PostFix_Queue, oper);
					Peek(&Operator_Stack, &oper);
				}

				Push(&Operator_Stack, letter);

			}
				break;
			case(int)'/':
			{
				char oper;
				Peek(&Operator_Stack, &oper);

				while (oper == '*' || oper == '/')
				{
					Pop(&Operator_Stack, &oper);
					Enque(&PostFix_Queue, oper);
					Peek(&Operator_Stack, &oper);
				}

				Push(&Operator_Stack, letter);
				
			}
			break;
			case (int)'+':
			{
				char sign = clac[0];

				if (i >= 1)
				{
					sign = clac[i - 1];
				}

				if (sign >= 48 && sign <= 57)
				{
					char oper;
					Peek(&Operator_Stack, &oper);

					while (oper == '*' || oper == '/' || oper == '+' || oper == '-')
					{
						Pop(&Operator_Stack, &oper);
						Enque(&PostFix_Queue, oper);
						Peek(&Operator_Stack, &oper);
					}

					Push(&Operator_Stack, letter);
				}

				else //��ȣ�� ���� ��
				{
					break;
				}
			}
				break;

			case (int)'-':
			{
				char sign = clac[0];

				if (i >= 1)
				{
					sign = clac[i - 1];
				}

				if (sign >= 48 && sign <= 57)
				{
					char oper;
					Peek(&Operator_Stack, &oper);

					while (oper == '*' || oper == '/' || oper == '+' || oper == '-')
					{
						Pop(&Operator_Stack, &oper);
						Enque(&PostFix_Queue, oper);
						Peek(&Operator_Stack, &oper);
					}

					Push(&Operator_Stack, letter);
				}

				else
				{

				}
			}
			break;
			}
		}
	}

	//Print(&PostFix_Queue);

	char Nums;
	int NumLength = 0;
	for (int i = 0; i < strlen(PostFix_Queue.que); i++)
	{
		Deque(&PostFix_Queue, &Nums);

		if (Nums >= 48 && Nums <= 57)
		{
			Push(&Operand_Stack, double(Nums-48));
			NumLength++;
		}

		else if (Nums==' ')
		{
			double k = 10;
			while (NumLength > 1)
			{
				double num1,num2;
				Pop(&Operand_Stack, &num1);
				Pop(&Operand_Stack, &num2);
				Push(&Operand_Stack, k* num2 + num1);
				k *= 10;
				NumLength--;
			}

			NumLength = 0;
		}

		else
		{
			NumLength = 0;

			if (Nums == '*')
			{
				double num1, num2;
				Pop(&Operand_Stack, &num1);
				Pop(&Operand_Stack, &num2);
				Push(&Operand_Stack, num1* num2);

			}

			else if (Nums == '/')
			{
				double num1, num2;
				Pop(&Operand_Stack, &num1);
				Pop(&Operand_Stack, &num2);
				Push(&Operand_Stack, num1 / num2);
			}

			else if (Nums == '+')
			{
				double num1, num2;
				Pop(&Operand_Stack, &num1);
				Pop(&Operand_Stack, &num2);
				Push(&Operand_Stack, num1+ num2);
			}

			else
			{
				double num1, num2;
				Pop(&Operand_Stack, &num1);
				Pop(&Operand_Stack, &num2);
				Push(&Operand_Stack, num1- num2);
			}
		}
	}

	double answer;
	Pop(&Operand_Stack, &answer);

	std::cout << answer << endl;

	Terminate(&PostFix_Queue);
	Terminate1(&Operand_Stack);
	Terminate1(&Operator_Stack);

	readFile.close();

	return 0;
}