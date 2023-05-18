#include "xString_ID.h"
xString_ID::xString_ID(int val) : xString(val)
{

    cout << "xString_ID::xString_ID(int val)" << endl;
}

xString_ID::xString_ID(const char* s) : xString(s)
{
    if (!((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z')))
    {

        cout << "bad symbol str[0]=" << str[0] << endl;
        if (str) delete[] str;
        len = 0;
        str = new char[len + 1];
        str[0] = '\0';
        return;
    }
    for (int i = 1; i < len; i++)
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_' || (str[i] >= '0' || str[i] <= '9')))
        {
            cout << "bad symbol str[" << i << "]=" << str[i] << endl;

            if (str) delete[] str;
            len = 0;
            str = new char[len + 1];
            str[0] = '\0';
            return;
        }
    }
    cout << "xString_ID::xString_ID(const char* s)" << endl;
}

xString_ID::xString_ID(char c) : xString(c)
{
    if ((str[0] >= 'a' && str[0] <= 'z') || (str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_');
    else
    {
        cout << "bad symbol char=" << str[0] << endl;
        delete[] str;
        len = 0;
        str = new char[len + 1];
        str[0] = '\0';
    }
    cout << "xString_ID::xString_ID(char c)" << endl;
}

xString_ID::xString_ID(const xString_ID& s) : xString(s)
{
    cout << "xString_ID::xString_ID(const xString_ID& s)" << endl;
}

xString_ID::~xString_ID()
{
    cout << "xString_ID::~xString_ID()" << endl;
}

char xString_ID::GetFirstChar()
{
    cout << "char xString_ID::GetFirstChar()" << endl;
    return str[0];
}

xString_ID& xString_ID::operator=(const xString_ID& S)
{
    if (&S != this)
    {
        delete[] str;
        len = S.len;
        str = new char[len + 1];
        strcpy_s(str, len + 1, S.str);
    }
    cout << "xString_ID& xString_ID::operator=(const xString_ID& S)" << endl;
    return *this;
}

xString_ID operator+(const xString_ID& S1, const xString_ID& S2)
{
    xString_ID tmp(S1.len + S2.len);
    int i = 0;
    while (tmp.str[i] = S1.str[i++]);
    int j = 0;
    i--;
    while (tmp.str[i++] = S2.str[j++]);
    cout << "xString_ID operator+(const xString_ID& S1, const xString_ID& S2)" << endl;
    return tmp;
}
char xString_ID::operator[](int index)
{
    cout << "char xString_ID::operator[](int index)" << endl;
    if (index < len) return str[index];
    else return '\0';
}