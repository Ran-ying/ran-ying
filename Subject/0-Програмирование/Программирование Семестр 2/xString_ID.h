#pragma once
#include "xString.h"
class xString_ID : public xString
{
private:
    /* data */
public:
    xString_ID(int = 0);
    xString_ID(const char*);
    xString_ID(char);
    xString_ID(const xString_ID&);
    ~xString_ID();
    char GetFirstChar();
    xString_ID& operator=(const xString_ID&);
    friend xString_ID operator+(const xString_ID&, const xString_ID&);
    char operator[](int);
};