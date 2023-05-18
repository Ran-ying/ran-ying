#pragma once
#include "xString.h"
class xString_BIT : public xString
{
private:
    /* data */
public:
    xString_BIT(int = 0);
    xString_BIT(const char*);
    xString_BIT(const xString_BIT&);
    ~xString_BIT();
    char* Reverse(void);
    xString_BIT& operator=(const xString_BIT&);
    friend xString_BIT operator+(const xString_BIT&, const xString_BIT&);
    friend xString_BIT operator/(const xString_BIT&, const xString_BIT&);
};