#include "xString.h"
xString::xString(int val)
{
    len = val;
    str = new char[len + 1];
    if(val == 0) str[0] = '\0';
    else str[len] = '\0';
    cout << "xString::xString(int val)" << endl;
}

xString::xString(const char* s)
{
    len = strlen(s);
    str = new char[len + 1];
    strcpy_s(str, len + 1, s);
    cout << "xString::xString(const char* s)" << endl;
}

xString::xString(char c) : len(1), str(new char[len + 1])
{
    str[0] = c, str[1] = '\0';
    cout << "xString::xString(char c)" << endl;
}

xString::xString(const xString& s) : len(s.len), str(new char[len + 1])
{
    strcpy_s(str, len + 1, s.str);
    cout << "xString::xString(const xString& s)" << endl;
}

xString::~xString()
{
    cout << "xString::~xString()" << endl;
}

char* xString::GetStr()
{
    return str;
}

int xString::GetLen()
{
    return len;
}

char xString::GetChar(int index)
{

    cout << "char xString::GetChar(int index)" << endl;
    if (index < len) return str[index];
    else return '\0';
}