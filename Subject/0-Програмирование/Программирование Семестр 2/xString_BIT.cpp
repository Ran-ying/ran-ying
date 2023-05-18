#include "xString_BIT.h"
xString_BIT::xString_BIT(int val) : xString(val)
{
    cout << "xString_ID operator+(const xString_ID& S1, const xString_ID& S2)" << endl;
}
xString_BIT::xString_BIT(const char* s) : xString(s)
{
    for (int i = 0; i < len; i++)
        if (str[i] != '0' && str[i] != '1')
        {
            cout << "bad symbol, str[" << i << "]=" << str[i] << endl;
            if (str) delete[] str;
            len = 1;
            str = new char[len + 1];
            str[0] = '0';
            str[1] = '\0';
            return;
        }
    cout << "xString_BIT::xString_BIT(const char* s)" << endl;
}
xString_BIT::xString_BIT(const xString_BIT& S) : xString(S)
{
    cout << "xString_BIT::xString_BIT(const xString_BIT& S)" << endl;
}
xString_BIT::~xString_BIT()
{
    cout << "xString_BIT::~xString_BIT()" << endl;
}
char* xString_BIT::Reverse(void)
{
    for (int i = 0; i < len; i++)
        str[i] = str[i] == '0' ? '1' : '0';
    int x = 0;
    if (str[len - 1] == '1')
    {
        str[len - 1] = '0';
        x = 1;
    }
    else str[len - 1] = '1';
    for (int i = len - 2; i >= 0; i--)
        if (x == 0 && str[i] == '0');
        else if (x == 0 && str[i] == '1');
        else if (x == 1 && str[i] == '0') {str[i] = '1'; x = 0; }
        else if (x == 1 && str[i] == '1') str[i] = '0';
    cout << "void xString_BIT::Reverse(void)" << endl;
    return str;
}
xString_BIT& xString_BIT::operator=(const xString_BIT& S)
{
    if (&S != this)
    {
        delete[] str;
        len = strlen(S.str);
        str = new char[len + 1];
        strcpy_s(str, len + 1, S.str);
    }
    cout << "xString_BIT& xString_BIT::operator=(const xString_BIT& S)" << endl;
    return *this;
}
xString_BIT operator+(const xString_BIT& n1, const xString_BIT& n2)
{
    int longLen, shortLen;
    char* longStr, * shortStr;
    if (n1.len > n2.len)
    {
        longLen = n1.len;
        shortLen = n2.len;
        longStr = n1.str;
        shortStr = n2.str;
    }
    else
    {
        longLen = n2.len;
        shortLen = n1.len;
        longStr = n2.str;
        shortStr = n1.str;
    }
    char* str = (char*)malloc(sizeof(char) * longLen + 1);
    int x = 0;
    for (int i = 1; i <= longLen; i++)
    {
        if (i <= shortLen)
        {
            if (x + longStr[longLen - i] + shortStr[shortLen - i] - '0' - '0' == 3)
            {
                str[longLen - i] = '1';
                x = 1;
            }
            else if (x + longStr[longLen - i] + shortStr[shortLen - i] - '0' - '0' == 2)
            {
                str[longLen - i] = '0';
                x = 1;
            }
            else if (x + longStr[longLen - i] + shortStr[shortLen - i] - '0' - '0' == 1)
            {
                str[longLen - i] = '1';
                x = 0;
            }
            else if (x + longStr[longLen - i] + shortStr[shortLen - i] - '0' - '0' == 0)
            {
                str[longLen - i] = '0';
                x = 0;
            }
        }
        else
        {
            if (x + longStr[longLen - i] - '0' == 2)
            {
                x = 1;
                str[longLen - i] = '0';
            }
            else if (x + longStr[longLen - i] - '0' == 1)
            {
                x = 0;
                str[longLen - i] = '1';
            }
            else if (x + longStr[longLen - i] - '0' == 0)
            {
                x = 0;
                str[longLen - i] = '0';
            }
        }
    }
    cout << "xString_BIT operator+(const xString_BIT& n1, const xString_BIT& n2)" << endl;
    str[longLen] = '\0';
    return xString_BIT(str);
}
xString_BIT operator/(const xString_BIT& n1, const xString_BIT& n2)
{

    int longLen, shortLen;
    char* longStr, * shortStr;
    if (n1.len > n2.len)
    {
        longLen = n1.len;
        shortLen = n2.len;
        longStr = n1.str;
        shortStr = n2.str;
    }
    else
    {
        longLen = n2.len;
        shortLen = n1.len;
        longStr = n2.str;
        shortStr = n1.str;
    }
    char* str = (char*)malloc(sizeof(char) * (longLen));
    for (int i = 1; i <= longLen; i++)
    {
        if (i <= shortLen)
        {
            str[longLen - i] = (char)
                (
                    (int)(longStr[longLen - i] - '0') |
                    (int)(shortStr[shortLen - i] - '0') + (int)'0'
                    );
        }
        else
        {
            str[longLen - i] = longStr[longLen - i];
        }
    }
    str[longLen] = '\0';
    cout << "xString_BIT operator/(const xString_BIT& n1, const xString_BIT& n2)" << endl;
    return xString_BIT(str);
}