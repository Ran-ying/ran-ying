#pragma once
#include <iostream>
using namespace std;
class xString
{
protected:
    char* str;
    int len;

public:
    xString(int = 0);
    xString(const char*);
    xString(char);
    xString(const xString&);
    ~xString();
    char* GetStr();
    int GetLen();
    char GetChar(int = 0);
};