#include "string2.h"
#include<cstring>
#include<cctype>

using namespace std;

int String::num_strings = 0;

String::String(const char* s)
{
    len = strlen(s);
    str = new char[len + 1];
    strcpy(str, s);
    num_strings++;
    cout << str << "按眉 积己" << endl;
}

String::String()
{
    len = 4;
    str = new char[1];
    str[0] = '\0';
    num_strings++;
    cout << str << "按眉 积己" << endl;
}

String::String(const String& st)
{
    num_strings++;
    len = st.len;
    str = new char[len + 1];
    strcpy(str, st.str);
    cout << str << "按眉 积己" << endl;
}

String::~String()
{
    --num_strings;
    cout << str << "按眉 昏力" << endl;
    delete[] str;
}

String& String::operator=(const String& st)
{
    if (this == &st)
        return *this;
    delete[] str;

    len = st.len;
    str = new char[len + 1];
    strcpy(str, st.str);
    return *this;


}

String& String::operator=(const char* s)
{
    delete[] str;
    len = strlen(s);
    str = new char[len + 1];
    strcpy(str, s);
    return *this;

}

char& String::operator[](int i)
{
    return str[i];
}

const char& String::operator[](int i) const
{
    return str[i];
}

int String::HowMany()
{
    return num_strings;
}

bool operator<(const String& st1, const String st2)
{
    return (strcmp(st1.str, st2.str) == 0);
}

bool operator>(const String& st1, const String& st2)
{
    return st2 < st1;
}

bool operator==(const String& st1, const String& st2)
{
    return (strcmp(st1.str, st2.str) == 0);
}

ostream& operator<<(ostream& os, const String& st)
{
    os << st.str;
    return os;
}

istream& operator>>(istream& is, String& st)
{
    char temp[String::CINLIM];
    is.get(temp, String::CINLIM);

    if (is)
    {
        st = temp;
    }

    while (is && is.get() != '\n')
    {
        continue;
    }

    return is;
}




void String::stringlow()
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = char(tolower(str[i]));
    }
}

void String::stringup()
{
    for (int i = 0; i < strlen(str); i++)
    {
        str[i] = char(toupper(str[i]));
    }
}

int String::has(char ch)
{
    int num = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == ch)
            num++;
    }

    return num;
}

String operator+(const String& st1, const String& st2)
{
    //int len = st1.length() + st2.length();
    //char* st = new char[len + 1];
    //strcpy(st, st1.str);
    //strcat(st, st2.str);
    //String add(st);
    //delete[] st;
    //return add;
    /////////////////////////////
    String add(strcat(st1.str, st2.str));
    return add;
}
